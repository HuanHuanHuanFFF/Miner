"""Retain every original-protocol observation of the exact selected Rust."""
from pathlib import Path
import argparse,hashlib,json,statistics as st
from importlib import import_module
impact=import_module('round20-impact')
ROOT=Path(__file__).resolve().parents[1]
NAME='r20-539-csv-singlehead'

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--capture',type=Path,required=True);ap.add_argument('--output',type=Path,required=True);a=ap.parse_args()
    comp,ctx,rows,s,b,front,top,check=impact.context(a.capture);fm=next(r for r in rows if str(r['id'])=='539')['metrics'];base=100*top['score']['payable_weight'];wanted=hashlib.sha256((ROOT/'candidates'/NAME/'parse.rs').read_bytes()).hexdigest();obs=[];audits={}
    def metrics(folder,filename,name):
        p=folder/filename;raw=p.read_bytes();inv=json.loads((folder/'raw-artifact-files.json').read_bytes());v=inv['files'][filename];assert hashlib.sha256(raw).hexdigest()==v['sha256'] and len(raw)==v['bytes'];records=[json.loads(l)for l in raw.splitlines()];meta=records[0];assert meta['warmup_rounds']==1 and meta['measured_rounds']==11
        fs=[r for r in records if r['kind']=='file'];assert len(fs)==28;xs=[];ys=[]
        for f in fs:
            med={}
            for method in [name,'incumbent']:
                x=f['methods'][method];assert x['deterministic'] and not x['errors'];rr=[r['total_s']for r in x['reps']if r['phase']=='measured'];assert len(rr)==11;med[method]=st.median(rr)
            xs.append(med[name]/med['incumbent']);ys.append(100*f['methods'][name]['output_bytes']/f['raw_bytes'])
        audits[p.relative_to(ROOT).as_posix()]=v
        return st.mean(xs),st.mean(ys),meta['methods'][name]['source_sha256']
    def add(run,block,role,cv,c,refs):
        assert c[2]==wanted
        for cal,ref in refs.items():
            x=fm['balanced_time_ratio']*c[0]/ref[0];y=fm['mean_file_compression_pct']*c[1]/ref[1]
            ps=front+[s.Point('__new__',x,y)]if not any(p.time_s<=x and p.ratio_pct<=y for p in front)else front
            w=s.local_global_improvement_space_log_weights(s.pareto_front(ps),b);own=100*w.get('__new__',0);after=100*w.get(str(top['id']),0)
            obs.append({'run_id':run,'block':block,'role':role,'candidate_view':cv,'calibration':cal,'projected_time':x,'projected_size_pct':y,'own_share_pct':own,'top1_after_pct':after,'top1_reduction_pp':base-after,'becomes_top1':own>max([100*v for k,v in w.items()if k!='__new__'],default=0)})
    for run,batch in [('38050094529','screen-b'),('38051239279','screen-h'),('38051540412','confirm-j'),('38051548407','confirm-k'),('38052454400','screen-p')]:
        folder=ROOT/f'evidence/round20/{run}/{batch}/gate';state=json.loads((folder/'state.json').read_bytes());e=next(v for v in state['spec']['entries']if v['name']==NAME);assert e['hashes']['parse.rs']==wanted
        role='incidental_control'if e.get('control')else state['spec'].get('r18_role','discovery')
        for block in range(1,state['spec']['screen_blocks']+1):
            c=metrics(folder,f'round{block}-{NAME}.jsonl',NAME);refs={cal:metrics(folder,f'round{block}-{ref}.jsonl',ref)for cal,ref in [('primary','public539'),('shadow','public539-shadow')]};add(run,block,role,NAME,c,refs)
    run='38050952723';folder=ROOT/f'evidence/round20/{run}/noise-g-diagnostic/diagnostics'
    for block in [1,2]:
        refs={cal:metrics(folder,f'r18-noise/official_isolated-block{block}-{ref}.jsonl',ref)for cal,ref in [('primary','public539'),('shadow','public539-shadow')]}
        for cv in [NAME,NAME+'-shadow']:
            c=metrics(folder,f'r18-noise/official_isolated-block{block}-{cv}.jsonl',cv);add(run,block,'original_protocol_diagnostic',cv,c,refs)
    summaries=[]
    for role in ['all_primary_candidate_views','discovery','incidental_control','independent_confirmation','original_protocol_diagnostic']:
        for cal in ['primary','shadow']:
            rs=[r for r in obs if r['candidate_view']==NAME and r['calibration']==cal and(role=='all_primary_candidate_views'or r['role']==role)]
            v={'role':role,'calibration':cal,'blocks':len(rs),'runners':len({r['run_id']for r in rs}),'zero_own_count':sum(r['own_share_pct']==0 for r in rs),'no_top1_reduction_count':sum(r['top1_reduction_pp']<=0 for r in rs),'top1_count':sum(r['becomes_top1']for r in rs)}
            for k in ['own_share_pct','top1_after_pct','top1_reduction_pp']:
                vs=[r[k]for r in rs];v[k]={'median':st.median(vs),'min':min(vs),'max':max(vs)}
            summaries.append(v)
    result={'status':'VERIFIED_ALL_ORIGINAL_PROTOCOL_RAW_REPLAY_CONDITIONAL_GEOMETRY','snapshot':ctx,'policy_validation':check,'rust_sha256':wanted,'current_top1':{'id':str(top['id']),'share_pct':base},'observations':obs,'summaries':summaries,'raw_files':audits,'limits':['Freeze-confirmation cohort is separated from discovery, later controls and original-protocol diagnostic blocks.','Extra same-source candidate copies and two calibration views are not independent blocks.','All views are retained; proportions are not formal success probabilities.','Private-corpus, admission, eligibility and actual payment remain unknown.']}
    a.output.write_text(json.dumps(result,indent=2)+'\n');print(json.dumps([r for r in summaries if r['role']=='all_primary_candidate_views'],indent=2))
if __name__=='__main__':main()
