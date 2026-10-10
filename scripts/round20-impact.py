"""Replay real frozen observations or bounded geometry, keeping every incumbent."""
from pathlib import Path
import argparse, json, statistics, sys
import round10_payability as h

ROOT=Path(__file__).resolve().parents[1]
if not h.SCORER_PATH.exists():
    h.SCORER_PATH=ROOT.parents[1]/'sources/conjectures-optimisation-deflate/validator/scoring/pareto.py'

def context(capture):
    comp,ctx,rows=h.load_flat_rows(capture);s=h.load_official_scorer()
    check=h.validate_policy_for_replay(comp['policy'],rows,s)
    b=s.Boundaries(comp['policy']['max_balanced_time_ratio'],comp['policy']['max_mean_file_compression_pct'])
    f=[s.Point(str(r['id']),r['metrics']['balanced_time_ratio'],r['metrics']['mean_file_compression_pct'])for r in rows if(r.get('score')or{}).get('on_frontier')]
    top=max(rows,key=lambda r:float((r.get('score')or{}).get('payable_weight')or 0))
    return comp,ctx,rows,s,b,f,top,check

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--capture',type=Path,default=ROOT/'evidence/round20/official-start');ap.add_argument('--analysis',type=Path);ap.add_argument('--output',type=Path,required=True);a=ap.parse_args()
    comp,ctx,rows,s,b,f,top,check=context(a.capture);topid=str(top['id']);base=100*top['score']['payable_weight']
    def calc(x,y):
        points=f+[s.Point('__new__',x,y)] if 0<x<=b.time_s and 0<y<=b.ratio_pct and not any(p.time_s<=x and p.ratio_pct<=y for p in f) else f
        nf=s.pareto_front(points);w=s.local_global_improvement_space_log_weights(nf,b)
        new=100*w.get('__new__',0);after=100*w.get(topid,0)
        return {'time':x,'size_pct':y,'new_share_pct':new,'top1_after_pct':after,'top1_reduction_pp':base-after,'candidate_becomes_top1':new>max((100*v for k,v in w.items()if k!='__new__'),default=0),'top1_dominated':topid not in {p.name for p in nf},'new_frontier_ids':[p.name for p in nf]}
    result={'snapshot':ctx,'status':'CONDITIONAL_GEOMETRY_NOT_FORMAL_RESULT','policy_validation':check,'current_top1':{'id':topid,'metrics':top['metrics'],'payable_share_pct':base},'observations':[]}
    if a.analysis:
        data=json.loads(a.analysis.read_bytes())
        for c in data['candidates']:
            for o in c['observations']:
                r=calc(o['projected_time'],o['projected_size_pct']);r.update(candidate=c['candidate'],run_id=o['run_id'],block=o['block'],calibration=o['calibration'],role=o['role']);result['observations'].append(r)
        result['summaries']=[]
        for name in sorted({r['candidate']for r in result['observations']}):
            for cal in ['primary','shadow']:
                rs=[r for r in result['observations']if r['candidate']==name and r['calibration']==cal]
                if not rs:continue
                item={'candidate':name,'calibration':cal,'n':len(rs),'top1_count':sum(r['candidate_becomes_top1']for r in rs),'top1_dominated_count':sum(r['top1_dominated']for r in rs),'zero_count':sum(r['new_share_pct']==0 for r in rs)}
                for k in ['new_share_pct','top1_after_pct','top1_reduction_pp']:
                    vs=[r[k]for r in rs];item[k]={'median':statistics.median(vs),'min':min(vs),'max':max(vs)}
                result['summaries'].append(item)
        # Insert the actual same-block candidate coordinates together. This is
        # not a sum of separately normalized single-candidate forecasts.
        result['joint_observations']=[]
        candidate_names=sorted({r['candidate']for r in result['observations']})
        if len(candidate_names)>1:
            keys=sorted({(r['run_id'],r['block'],r['calibration'])for r in result['observations']})
            for run,block,cal in keys:
                rs=[r for r in result['observations']if(r['run_id'],r['block'],r['calibration'])==(run,block,cal)]
                if len(rs)!=len(candidate_names):continue
                extras=[s.Point(r['candidate'],r['time'],r['size_pct'])for r in rs if 0<r['time']<=b.time_s and 0<r['size_pct']<=b.ratio_pct and not any(p.time_s<=r['time'] and p.ratio_pct<=r['size_pct']for p in f)]
                nf=s.pareto_front(f+extras);w=s.local_global_improvement_space_log_weights(nf,b)
                result['joint_observations'].append({'run_id':run,'block':block,'calibration':cal,'candidate_shares_pct':{n:100*w.get(n,0)for n in candidate_names},'top1_after_pct':100*w.get(topid,0),'top1_reduction_pp':base-100*w.get(topid,0),'existing_owned_geometric_pct':{n:100*w.get(n,0)for n in ['573','603']},'scope':'Conditional geometric shares; distinct eligible identities assumed. Same-hotkey, admission, registration and bounty gates remain separate.'})
    else:
        for y in [36.63644740383624,36.57814279549815,36.5653,36.5,36.2,35.5,34.1]:
            rs=[calc(0.425+i*.00001,y)for i in range(1501)]
            best=max(rs,key=lambda x:x['new_share_pct']);affected=[r for r in rs if r['top1_reduction_pp']>=5]
            result['observations'].append({'size_pct':y,'best_grid_point':best,'grid_points_dropping_top1_at_least5pp':len(affected),'scope':'Synthetic geometry grid, not performance observations, not an error bound or success probability.'})
    a.output.write_text(json.dumps(result,indent=2)+'\n');print(json.dumps({k:result[k]for k in ('snapshot','current_top1','summaries')if k in result},indent=2))

if __name__=='__main__':main()
