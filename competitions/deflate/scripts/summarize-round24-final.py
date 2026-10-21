"""Summarize frozen confirmation by actual main blocks, aliases, runners and anchors."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,csv,hashlib,json,statistics as st
from round3 import load_scorer
from round10_payability import load_flat_rows,validate_policy_for_replay
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24'
def read(p):return json.loads(p.read_bytes())
def dist(values):
    return {'observations':len(values),'minimum_pct':min(values)if values else None,'median_pct':st.median(values)if values else None,'best_pct':max(values)if values else None,'zero_count':sum(v==0 for v in values),'at_least_10_count':sum(v>=10 for v in values),'at_least_15_count':sum(v>=15 for v in values)}
def csvout(path,rows):
    if not rows:return None
    with path.open('w',newline='',encoding='utf-8-sig')as f:
        w=csv.DictWriter(f,fieldnames=list(rows[0]));w.writeheader();w.writerows(rows)
    return {'path':path.relative_to(ROOT).as_posix(),'sha256':hashlib.sha256(path.read_bytes()).hexdigest(),'rows':len(rows)}
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--analysis',required=True,type=Path);ap.add_argument('--anchors',required=True,type=Path);ap.add_argument('--capture',required=True,type=Path);ap.add_argument('--out',required=True,type=Path);a=ap.parse_args();out=a.out.resolve();assert out.is_relative_to(E.resolve())and not out.exists();out.mkdir()
    primary,anchors=read(a.analysis),read(a.anchors);selection=read(E/'final-selection-decision.json');plan=read(E/'confirm-final-plan.json');comp,ctx,rows=load_flat_rows(a.capture);assert primary['snapshot']==anchors['snapshot']==ctx
    sc=load_scorer(E/'official-rules-start/validator--scoring--pareto.py');policy=validate_policy_for_replay(comp['policy'],rows,sc);b=sc.Boundaries(comp['policy']['max_balanced_time_ratio'],comp['policy']['max_mean_file_compression_pct']);front=[sc.Point(str(r['id']),r['metrics']['balanced_time_ratio'],r['metrics']['mean_file_compression_pct'])for r in rows if(r.get('score')or{}).get('on_frontier')]
    def score(name,x,y):
        if not(0<x<=b.time_s and 0<y<=b.ratio_pct)or any(p.time_s<=x and p.ratio_pct<=y for p in front):return 0.0
        f=sc.pareto_front(front+[sc.Point(name,x,y)]);return 100*comp['policy']['pareto_share']*sc.local_global_improvement_space_log_weights(f,b).get(name,0)
    refs={(r['run_id'],r['block'],r['anchor']):r for r in anchors['anchor_measurements']};expected=plan['runners']*plan['blocks_per_runner'];gates=[];candidates=[];main_csv=[];alias_csv=[];perfile=[];all_points={};run_ids=sorted(r['run_id']for r in primary['runs'])
    frozen=datetime.fromisoformat(plan['frozen_utc']);runner_receipt=read(E/'confirmation-runners-final/receipt.json');assert len({r['runner_id']for r in runner_receipt['jobs']})==3
    for j in runner_receipt['jobs']:assert datetime.fromisoformat(j['started_at'].replace('Z','+00:00'))>frozen
    for item in selection['selected']:
        name=item['candidate'];label=item['label'];target=item['target_pool_share_pct'];hs=plan['files'][name];matches=[g for g in primary['candidates']if g['rust_sha256']==hs['parse.rs']];assert len(matches)==1;g=matches[0]
        cert=read(ROOT/'candidates'/name/'VERIFICATION.json');assert cert['status']=='VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED'and cert['files']==hs;assert any(p['files']==hs for p in g['verified_pairs']);gates.append(cert)
        points=[]
        for o in g['observations']:
            anchor='public609'if o['calibration']=='primary'else'public609-shadow';r={'label':label,'candidate':name,'run_id':o['run_id'],'block':o['block'],'entry_name':o['entry_name'],'entry_role':o['entry_role'],'evidence_role':o['role'],'anchor':anchor,'public_time_axis':o['public_time'],'public_size_pct':o['public_size_pct'],'projected_time':o['projected_time'],'projected_size_pct':o['projected_size_pct'],'single_pool_share_pct':o['single_pool_share_pct']};points.append(r)
            if o['calibration']=='primary':
                ref=refs.get((o['run_id'],o['block'],'public607'))
                if ref:
                    x=o['public_time']*ref['time_factor'];y=o['public_size_pct']*ref['size_factor'];points.append({**r,'anchor':'public607','projected_time':x,'projected_size_pct':y,'single_pool_share_pct':score(name,x,y)})
                if o['entry_role']=='candidate'and o['role']=='independent_confirmation':
                    assert o['proof_sha256']==hs['Parse.lean']
                    for f in o['per_file']:perfile.append({'label':label,'candidate':name,'run_id':o['run_id'],'block':o['block'],'file':f['file'],'candidate_median_total_seconds':f['candidate_median_total_seconds'],'incumbent_median_total_seconds':f['incumbent_median_total_seconds'],'public_time_ratio':f['time_ratio'],'size_pct':f['size_pct'],'output_bytes':f['output_bytes'],'input_sha256':f['input_sha256']})
        main=[r for r in points if r['entry_role']=='candidate'and r['evidence_role']=='independent_confirmation'];controls=[r for r in points if r['entry_role']=='control'];key=lambda r:(r['run_id'],r['block'],r['anchor']);main_by={key(r):r for r in main};assert len(main_by)==len(main)
        # Independently derived607 view must agree with the separate audited tool.
        for r in anchors['candidate_observations']:
            if r['candidate']!=name:continue
            m=main_by.get((r['run_id'],r['block'],r['anchor']));assert m and abs(m['single_pool_share_pct']-r['single_share_pct'])<1e-10
        for r in controls:
            m=main_by.get(key(r))
            if not m:continue
            alias_csv.append({'label':label,'candidate':name,'run_id':r['run_id'],'block':r['block'],'anchor':r['anchor'],'main_entry':m['entry_name'],'alias_entry':r['entry_name'],'normalized_time_gap_pct':100*(r['public_time_axis']/m['public_time_axis']-1),'main_single_share_pct':m['single_pool_share_pct'],'alias_single_share_pct':r['single_pool_share_pct'],'zero_verdict_disagrees':(m['single_pool_share_pct']==0)!=(r['single_pool_share_pct']==0),'assigned_target_verdict_disagrees':(m['single_pool_share_pct']>=target)!=(r['single_pool_share_pct']>=target)})
        summaries={anchor:dist([r['single_pool_share_pct']for r in main if r['anchor']==anchor])for anchor in ['public609','public609-shadow','public607']};all_summaries={anchor:dist([r['single_pool_share_pct']for r in points if r['anchor']==anchor])for anchor in summaries};by_runner=[{'run_id':run,'anchor':anchor,**dist([r['single_pool_share_pct']for r in main if r['anchor']==anchor and r['run_id']==run])}for run in run_ids for anchor in summaries]
        complete=all(v['observations']==expected for v in summaries.values())and len(run_ids)==plan['runners'];ad=[r for r in alias_csv if r['candidate']==name]
        candidates.append({'label':label,'candidate':name,'target_pool_share_pct':target,'files':hs,'exact_gate_run_id':cert['run_id'],'expected_independent_main_blocks':expected,'complete_main_confirmation':complete,'main_by_anchor':summaries,'all_same_source_entries_by_anchor_NOT_independent_blocks':all_summaries,'main_by_runner_and_anchor':by_runner,'same_source_zero_verdict_disagreements':sum(r['zero_verdict_disagrees']for r in ad),'same_source_target_verdict_disagreements':sum(r['assigned_target_verdict_disagrees']for r in ad),'observed_main_and_alias_minimum_pct':min(r['single_pool_share_pct']for r in points)if points else None,'assigned_target_met_all_observed_views':complete and all(r['single_pool_share_pct']>=target for r in points),'formal_admission':'UNKNOWN_NOT_SUBMITTED','formal_payable_pool_share_pct':None})
        main_csv.extend(main);all_points[name]=main_by
    names=plan['candidates'];joint_csv=[]
    for r in anchors['pairwise_joint']:
        if set(r['candidates'])!=set(names):continue
        aa,bb=[all_points[n].get((r['run_id'],r['block'],r['anchor']))for n in names];assert aa and bb;shares=r['simultaneous_share_pct'];joint_csv.append({'run_id':r['run_id'],'block':r['block'],'anchor':r['anchor'],'A_individual_pct':aa['single_pool_share_pct'],'B_individual_pct':bb['single_pool_share_pct'],'A_joint_pct':shares[names[0]],'B_joint_pct':shares[names[1]],'joint_sum_pct':sum(shares.values())})
    for row in primary['joint'][0]['matched_observations']:
        anchor='public609'if row['calibration']=='primary'else'public609-shadow';match=next(r for r in joint_csv if r['run_id']==row['run_id']and r['block']==row['block']and r['anchor']==anchor)
        for label,n in zip(['A','B'],names):assert abs(match[label+'_joint_pct']-row['simultaneous_geometric_pct'][n])<1e-10
    joint_summary={anchor:{'A':dist([r['A_joint_pct']for r in joint_csv if r['anchor']==anchor]),'B':dist([r['B_joint_pct']for r in joint_csv if r['anchor']==anchor])}for anchor in ['public609','public609-shadow','public607']}
    exports=[csvout(out/'main-blocks.csv',main_csv),csvout(out/'same-source-aliases.csv',alias_csv),csvout(out/'joint-blocks.csv',joint_csv),csvout(out/'per-file-total-times.csv',perfile)]
    result={'status':'VERIFIED_FROZEN_CONFIRMATION_RECOMPUTATION_CONDITIONAL_SHARES','computed_utc':datetime.now(timezone.utc).isoformat(),'snapshot':ctx,'policy_validation':policy,'frozen_plan':'evidence/round24/confirm-final-plan.json','frozen_utc':plan['frozen_utc'],'runners':primary['runs'],'distinct_runner_id_receipt':'evidence/round24/confirmation-runners-final/receipt.json','expected_main_blocks_per_candidate':expected,'candidates':candidates,'joint_by_anchor':joint_summary,'same_source_reference_controls':primary['same_source_controls'],'public_target_pair_established_over_observed_scope':all(c['assigned_target_met_all_observed_views']for c in candidates),'formal_objective':'UNKNOWN_NOT_SUBMITTED','exports':[v for v in exports if v],'inputs':{str(p.relative_to(ROOT)if p.is_absolute()else p):hashlib.sha256(p.read_bytes()).hexdigest()for p in [a.analysis,a.anchors]},'limits':['Only main declared candidateentries counttoward9 independentblocks; shadows/parentaliases/calibrationviews do notmultiplysample size. Alltheir extrema/counterexamples remainreported.','Publiccorpus wassearched; independenceis newfrozenruns/runners, notheld-outprivateinputs.','Threecalibrationviews areconditionalmigration models, notformalpayable results or successprobabilities.','Jointgeometry assumesadmission anddistincteligiblehotkeys withoutolder survivingentries; no registration/slot/chain guarantee.','Accountusage andrunnerseconds areseparate frommonetarycost.']};(out/'summary.json').write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps({'snapshot':ctx,'candidates':[{k:c[k]for k in ['label','candidate','main_by_anchor','same_source_zero_verdict_disagreements','assigned_target_met_all_observed_views']}for c in candidates],'joint':joint_summary},indent=2))
if __name__=='__main__':main()
