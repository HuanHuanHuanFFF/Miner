"""Audit raw paired reps, replay individual and jointly inserted R18 candidates."""
from pathlib import Path
import argparse, hashlib, itertools, json, statistics as st
from round10_payability import load_official_scorer, load_flat_rows, validate_policy_for_replay

ROOT=Path(__file__).resolve().parents[1]

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def read(p):return json.loads(p.read_bytes())

def distribution(values):
    assert values
    return {'n':len(values),'best_pct':max(values),'median_pct':st.median(values),'range_pct':[min(values),max(values)],'zero_count':sum(v==0 for v in values),'at_least_5_count':sum(v>=5 for v in values),'at_least_15_count':sum(v>=15 for v in values)}

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('receipts',type=Path,nargs='+')
    ap.add_argument('--capture',type=Path,default=ROOT/'evidence/round18/official-start-live')
    ap.add_argument('--output',type=Path,required=True);args=ap.parse_args()
    args.receipts=[p.resolve() for p in args.receipts]
    comp,context,rows=load_flat_rows(args.capture);sc=load_official_scorer();policy=comp['policy']
    policy_check=validate_policy_for_replay(policy,rows,sc);assert policy['improvement_share']==0
    formal={r['id']:r for r in rows};front=[sc.Point(r['id'],r['metrics']['balanced_time_ratio'],r['metrics']['mean_file_compression_pct']) for r in rows if (r.get('score')or{}).get('on_frontier')]
    bounds=sc.Boundaries(policy['max_balanced_time_ratio'],policy['max_mean_file_compression_pct'])
    def scores(points):
        eligible=[]
        for name,x,y in points:
            if 0<x<=bounds.time_s and 0<y<=bounds.ratio_pct and not any(p.time_s<=x and p.ratio_pct<=y for p in front):
                eligible.append(sc.Point(name,x,y))
        f=sc.pareto_front(front+eligible);w=sc.local_global_improvement_space_log_weights(f,bounds)
        return {name:100*policy['pareto_share']*w.get(name,0) for name,_,_ in points},[p.name for p in f]
    declarations={};states=[]
    for folder in args.receipts:
        state=read(folder/'state.json');ci=read(folder/'ci-run.json');inv=read(folder/'raw-artifact-files.json')
        assert ci['status']=='completed' and str(ci['databaseId'])==state['run_id'] and ci['headSha']==state['git_sha']
        namespace=folder.resolve().relative_to((ROOT/'evidence').resolve()).parts[0]
        assert inv['artifact_name']==f"{namespace.replace('round','r')}-{state['run_id']}-{state['batch']}-gate"
        for name,v in inv['files'].items():
            p=(folder/name).resolve();assert p.is_relative_to(folder.resolve()) and p.stat().st_size==v['bytes'] and sha(p)==v['sha256']
        entries={e['name']:e for e in state['spec']['entries']}
        for n,e in entries.items():
            if not e.get('control'):
                decl={'candidate':n,'rust_sha256':e['hashes']['parse.rs'],'anchor_formal_id':entries[e['anchor']]['formal_id'],'parent':e.get('comparison_baseline',e['anchor'])}
                prior=declarations.setdefault(e['hashes']['parse.rs'],decl)
                assert (prior['anchor_formal_id'],prior['parent'])==(decl['anchor_formal_id'],decl['parent'])
        states.append((folder,state,ci,entries))
    assert len(states)==len({s[1]['run_id']for s in states})
    groups={};runs=[];input_hashes={};output_hashes={};raw_audit={};shadows=[];timing_owners={}
    for folder,state,ci,entries in states:
        by={};envs=[]
        for m in state['metrics']:
            n,b=m['candidate'],m['round'];e=entries[n];p=folder/f'round{b}-{n}.jsonl'
            data=[json.loads(s)for s in p.read_text().splitlines()];meta=data[0];fs=[r for r in data if r['kind']=='file']
            assert meta['corpus']=='corpus-stage1' and meta['measured_rounds']==11 and meta['warmup_rounds']==1
            assert len(fs)==28 and sum(f['raw_bytes']for f in fs)==15930000
            assert meta['methods'][n]['source_sha256']==e['hashes']['parse.rs']==m['source_sha256']
            ratios=[];sizes=[];total=0;perfile=[];timing=[]
            for f in fs:
                assert input_hashes.setdefault(f['file'],f['sha256'])==f['sha256']
                med={}
                for method in (n,'incumbent'):
                    x=f['methods'][method];assert x['deterministic'] and not x['errors']
                    reps=[v['total_s']for v in x['reps']if v['phase']=='measured'];assert len(reps)==11 and min(reps)>0
                    med[method]=st.median(reps)
                    if method==n:
                        key=(e['hashes']['parse.rs'],f['file']);ident=(x['tokens_sha256'],x['output_sha256'],x['output_bytes'])
                        assert output_hashes.setdefault(key,ident)==ident;timing.extend(reps)
                ratio=med[n]/med['incumbent'];size=100*f['methods'][n]['output_bytes']/f['raw_bytes']
                ratios.append(ratio);sizes.append(size);total+=med[n]
                perfile.append({'file':f['file'],'input_sha256':f['sha256'],'candidate_median_total_seconds':med[n],'incumbent_median_total_seconds':med['incumbent'],'time_ratio':ratio,'size_pct':size,'output_bytes':f['methods'][n]['output_bytes']})
            signature=hashlib.sha256(json.dumps(timing).encode()).hexdigest();owner=timing_owners.setdefault((e['hashes']['parse.rs'],signature),state['run_id']);assert owner==state['run_id'],'Repeated exact timing vector from another run'
            x,y=st.mean(ratios),st.mean(sizes);assert abs(x-m['time'])<1e-12 and abs(y-m['size_pct'])<1e-12
            by[n,b]={'time':x,'size_pct':y,'total_seconds_telemetry':total,'per_file':perfile,'library_sha256':meta['methods'][n]['lib_sha256']}
            raw_audit[str(p.relative_to(ROOT))]={'sha256':sha(p),'source_hashes':e['hashes'],'timing_vector_sha256':signature}
            envs.append({k:meta.get(k)for k in ('os','arch','rustc_version','cpu_model','cpu_governor','benchmark_provenance')})
        assert all(x==envs[0]for x in envs)
        runs.append({'run_id':state['run_id'],'git_sha':state['git_sha'],'batch':state['batch'],'ci_conclusion':ci['conclusion'],'phase':state['phase'],'failures':state['failures'],'paired_processes':len(by),'environment':envs[0],'role':state['spec'].get('r18_role','discovery')})
        for n,e in entries.items():
            if n.endswith('-shadow') and n[:-7]in entries:
                parent=n[:-7];assert e['hashes']==entries[parent]['hashes']
                for name,b in by:
                    if name==n:
                        assert by[n,b]['library_sha256']==by[parent,b]['library_sha256']
                        shadows.append({'run_id':state['run_id'],'block':b,'shadow':n,'parent':parent,'relative_time_gap_pct':100*(by[n,b]['time']/by[parent,b]['time']-1),'same_binary_sha256':by[n,b]['library_sha256']})
            if e['hashes']['parse.rs'] not in declarations:continue
            decl=declarations[e['hashes']['parse.rs']];g=groups.setdefault(e['hashes']['parse.rs'],{**decl,'observations':[],'verified_pairs':[]})
            anchor=next(k for k,v in entries.items()if v.get('formal_id')==decl['anchor_formal_id']);fm=formal[decl['anchor_formal_id']]['metrics']
            for name,b in by:
                if name!=n:continue
                for label,ref in [('primary',anchor),('shadow',anchor+'-shadow')]:
                    if (ref,b)not in by:continue
                    x=fm['balanced_time_ratio']*by[n,b]['time']/by[ref,b]['time'];y=fm['mean_file_compression_pct']*by[n,b]['size_pct']/by[ref,b]['size_pct']
                    shares,ids=scores([(n,x,y)])
                    g['observations'].append({'run_id':state['run_id'],'block':b,'role':state['spec'].get('r18_role','discovery'),'calibration':label,'anchor_name':ref,'projected_time':x,'projected_size_pct':y,'single_pool_share_pct':shares[n],'new_frontier_ids':ids,'public_time':by[n,b]['time'],'public_size_pct':by[n,b]['size_pct'],'time_change_pct_vs_parent':100*(by[n,b]['time']/by[decl['parent'],b]['time']-1),'size_change_pp_vs_parent':by[n,b]['size_pct']-by[decl['parent'],b]['size_pct'],'proof_sha256':e['hashes']['Parse.lean'],'per_file':by[n,b]['per_file']})
            gate=state.get('gates',{}).get(n)
            if gate and gate.get('accepted'):
                assert gate==read(folder/(n+'-gate.json')) and gate['corpora']==['corpus-stage1']
                assert all(sha(folder/('input-'+n)/f)==h for f,h in e['hashes'].items())
                g['verified_pairs'].append({'run_id':state['run_id'],'files':e['hashes']})
    for g in groups.values():
        g['summary']={}
        for cal in ('primary','shadow'):
            obs=[o for o in g['observations']if o['calibration']==cal]
            if not obs:continue
            rid=sorted({o['run_id']for o in obs});mx=st.mean(st.mean(o['projected_time']for o in obs if o['run_id']==r)for r in rid);my=obs[0]['projected_size_pct']
            assert all(abs(o['projected_size_pct']-my)<1e-12 for o in obs)
            ss,_=scores([(g['candidate'],mx,my)])
            g['summary'][cal]={**distribution([o['single_pool_share_pct']for o in obs]),'runner_count':len(rid),'runner_equal_center_time':mx,'projected_size_pct':my,'score_at_center_NOT_expected_reward_pct':ss[g['candidate']]}
    joint=[]
    for a,b in itertools.combinations(groups.values(),2):
        oa={(o['run_id'],o['block'],o['calibration']):o for o in a['observations']};ob={(o['run_id'],o['block'],o['calibration']):o for o in b['observations']}
        matched=[]
        for key in sorted(oa.keys()&ob.keys()):
            x,y=oa[key],ob[key];ss,ids=scores([(a['candidate'],x['projected_time'],x['projected_size_pct']),(b['candidate'],y['projected_time'],y['projected_size_pct'])])
            matched.append({'run_id':key[0],'block':key[1],'calibration':key[2],'separate_pct':{a['candidate']:x['single_pool_share_pct'],b['candidate']:y['single_pool_share_pct']},'simultaneous_geometric_pct':ss,'simultaneous_frontier_ids':ids})
        joint.append({'candidates':[a['candidate'],b['candidate']],'matched_observations':matched,'scope':'Joint geometry on matching run/block/control. Conditional on admission and distinct eligible hotkeys without older surviving submissions. Same-hotkey rule pays only oldest surviving frontier submission; registration/slots are UNKNOWN and no new registration is authorized.'})
    result={'status':'VERIFIED_RAW_RECOMPUTATION_CONDITIONAL_PROJECTIONS','snapshot':context,'policy_validation':policy_check,'runs':runs,'paired_processes':sum(r['paired_processes']for r in runs),'candidates':list(groups.values()),'same_source_controls':shadows,'joint':joint,'raw_input_audit':raw_audit,'limits':['Original total-time public protocol only. Diagnostic timing is excluded.','Observed block/runner distributions are not formal success probabilities. Center-coordinate scores are not expected rewards.','No private-corpus, admission, registration, slot, signing, or realized reward claim.','Discovery and fresh confirmation roles remain distinct; all same-source later control measurements remain evidence.']}
    args.output.write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'runs':len(runs),'paired_processes':result['paired_processes'],'candidates':[{'candidate':g['candidate'],'summary':g['summary'],'verified_pairs':g['verified_pairs']}for g in groups.values()],'same_source_controls':shadows,'joint_rows':sum(len(j['matched_observations'])for j in joint)},indent=2))

if __name__=='__main__':main()
