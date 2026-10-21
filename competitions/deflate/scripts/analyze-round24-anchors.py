"""Audit original measurements and expose family-anchor disagreement without selecting it away."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,itertools,json,statistics as st
from round3 import load_scorer
from round10_payability import load_flat_rows,validate_policy_for_replay
ROOT=Path(__file__).resolve().parents[1]
def read(p):return json.loads(p.read_bytes())
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def main():
    ap=argparse.ArgumentParser();ap.add_argument('receipts',nargs='+',type=Path);ap.add_argument('--capture',required=True,type=Path);ap.add_argument('--output',required=True,type=Path);a=ap.parse_args();assert not a.output.exists()
    comp,ctx,rows=load_flat_rows(a.capture);policy=comp['policy'];sc=load_scorer(ROOT/'evidence/round24/official-rules-start/validator--scoring--pareto.py');check=validate_policy_for_replay(policy,rows,sc);formal={str(r['id']):r for r in rows};bounds=sc.Boundaries(policy['max_balanced_time_ratio'],policy['max_mean_file_compression_pct']);front=[sc.Point(str(r['id']),r['metrics']['balanced_time_ratio'],r['metrics']['mean_file_compression_pct'])for r in rows if (r.get('score')or{}).get('on_frontier')]
    def score(points):
        good=[sc.Point(n,x,y)for n,x,y in points if 0<x<=bounds.time_s and 0<y<=bounds.ratio_pct and not any(q.time_s<=x and q.ratio_pct<=y for q in front)]
        nf=sc.pareto_front(front+good);ws=sc.local_global_improvement_space_log_weights(nf,bounds);return {n:100*policy['pareto_share']*ws.get(n,0)for n,_,_ in points}
    measurements=[];backtest=[];observations=[];joint=[];audits=[]
    for folder in a.receipts:
        folder=folder.resolve();assert folder.is_relative_to((ROOT/'evidence/round24').resolve());state=read(folder/'state.json');ci=read(folder/'ci-run.json');assert ci['status']=='completed' and ci['conclusion']=='success' and ci['headSha']==state['git_sha'] and str(ci['databaseId'])==state['run_id']
        for file,v in read(folder/'raw-artifact-files.json')['files'].items():
            p=(folder/file).resolve();assert p.is_relative_to(folder) and p.stat().st_size==v['bytes'] and sha(p)==v['sha256']
        es={e['name']:e for e in state['spec']['entries']};by={}
        for m in state['metrics']:
            n,b=m['candidate'],m['round'];p=folder/f'round{b}-{n}.jsonl';data=[json.loads(x)for x in p.read_text().splitlines()];meta=data[0];fs=[x for x in data if x['kind']=='file'];assert meta['corpus']=='corpus-stage1' and meta['measured_rounds']==11 and meta['warmup_rounds']==1 and len(fs)==28
            assert meta['methods'][n]['source_sha256']==es[n]['hashes']['parse.rs']==m['source_sha256'];xs=[];ys=[]
            for f in fs:
                vals={}
                for k in [n,'incumbent']:
                    d=f['methods'][k];assert d['deterministic'] and not d['errors'];ts=[x['total_s']for x in d['reps']if x['phase']=='measured'];assert len(ts)==11 and min(ts)>0;vals[k]=st.median(ts)
                xs.append(vals[n]/vals['incumbent']);ys.append(100*f['methods'][n]['output_bytes']/f['raw_bytes'])
            x,y=st.mean(xs),st.mean(ys);assert abs(x-m['time'])<1e-12 and abs(y-m['size_pct'])<1e-12;by[n,b]=(x,y);audits.append({'path':p.relative_to(ROOT).as_posix(),'sha256':sha(p)})
        anchors=[n for n,e in es.items()if e.get('formal_id') in ['607','609']]
        # Keep609shadow as a separate same-source view; never double sample size.
        if 'public609-shadow'in es:
            assert es['public609-shadow']['hashes']==es['public609']['hashes'];anchors.append('public609-shadow')
        for b in sorted({b for n,b in by}):
            available=[n for n in anchors if (n,b)in by]
            for n in available:
                fid=es[n].get('formal_id')or es[n.removesuffix('-shadow')]['formal_id'];fm=formal[fid]['metrics'];px,py=by[n,b];measurements.append({'run_id':state['run_id'],'block':b,'anchor':n,'formal_id':fid,'public_time':px,'public_size_pct':py,'time_factor':fm['balanced_time_ratio']/px,'size_factor':fm['mean_file_compression_pct']/py})
                for target in [x for x in available if not x.endswith('-shadow') and es[x].get('formal_id')!=fid]:
                    tf=formal[es[target]['formal_id']]['metrics'];tx,ty=by[target,b];x=fm['balanced_time_ratio']*tx/px;y=fm['mean_file_compression_pct']*ty/py
                    backtest.append({'run_id':state['run_id'],'block':b,'anchor':n,'target':target,'predicted_time':x,'actual_formal_time':tf['balanced_time_ratio'],'time_error_pct':100*(x/tf['balanced_time_ratio']-1),'predicted_size_pct':y,'actual_formal_size_pct':tf['mean_file_compression_pct'],'size_error_pp':y-tf['mean_file_compression_pct']})
                points=[]
                for name,e in es.items():
                    if e.get('control')or(name,b)not in by:continue
                    tx,ty=by[name,b];x=fm['balanced_time_ratio']*tx/px;y=fm['mean_file_compression_pct']*ty/py;points.append((name,x,y));observations.append({'run_id':state['run_id'],'block':b,'role':state['spec'].get('r18_role','discovery'),'candidate':name,'files':e['hashes'],'anchor':n,'formal_id':fid,'projected_time':x,'projected_size_pct':y,'single_share_pct':score([(name,x,y)])[name]})
                for pair in itertools.combinations(points,2):joint.append({'run_id':state['run_id'],'block':b,'anchor':n,'candidates':[p[0]for p in pair],'points':pair,'simultaneous_share_pct':score(pair)})
    summaries=[]
    for name,anchor in sorted({(r['candidate'],r['anchor'])for r in observations}):
        rs=[r for r in observations if r['candidate']==name and r['anchor']==anchor];v=[r['single_share_pct']for r in rs];summaries.append({'candidate':name,'anchor':anchor,'blocks':len(v),'runners':len({r['run_id']for r in rs}),'minimum_pct':min(v),'median_pct':st.median(v),'best_pct':max(v),'zero_count':sum(x==0 for x in v),'at_least_10_count':sum(x>=10 for x in v),'at_least_15_count':sum(x>=15 for x in v)})
    result={'status':'VERIFIED_RAW_ANCHOR_BACKTEST_CONDITIONAL_PROJECTIONS','snapshot':ctx,'calculated_utc':datetime.now(timezone.utc).isoformat(),'capture':str(a.capture),'policy_check':check,'anchor_measurements':measurements,'reference_backtest':backtest,'candidate_observations':observations,'candidate_summaries':summaries,'pairwise_joint':joint,'raw_audits':audits,'limits':['Primarydeclared609anchor is retained;607is a separately reported related-family sensitivity view, never selected by higherreward.','Reference cross-errors combine public/private workload transfer and measurement differences. They are not an errorbound or formal success probability.','All anchors in a given run/block reuse the same candidate measurement and do not increase independent sample count.','No privatecandidate result, admission or payable reward has been observed.']}
    a.output.write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps({'snapshot':ctx,'reference_backtest':backtest,'candidate_summaries':summaries},indent=2))
if __name__=='__main__':main()
