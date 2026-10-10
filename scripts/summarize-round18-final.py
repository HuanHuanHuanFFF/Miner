"""Summarize only the two predeclared final runners, with exact pair and joint checks."""
from pathlib import Path
import argparse,hashlib,json,statistics as st

ROOT=Path(__file__).resolve().parents[1]

def dist(v):
    assert v
    return {'n':len(v),'best_pct':max(v),'median_pct':st.median(v),'range_pct':[min(v),max(v)],'zero_count':sum(x==0 for x in v),'at_least_5_count':sum(x>=5 for x in v),'at_least_15_count':sum(x>=15 for x in v)}

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('analysis',type=Path);ap.add_argument('--plan',type=Path,default=ROOT/'evidence/round18/final-confirmation-plan.json');ap.add_argument('--output',type=Path,required=True);args=ap.parse_args()
    data=json.loads(args.analysis.read_bytes());plan=json.loads(args.plan.read_bytes());ids={plan['first_run_id'],plan['second_run_id']};assert None not in ids and len(ids)==2
    runs=[r for r in data['runs']if r['run_id']in ids]
    assert len(runs)==2 and all(r['ci_conclusion']=='success' and isinstance(r['failures'],list) and not r['failures'] and r['role']=='independent_confirmation' for r in runs)
    targets=plan['candidates'];assert len(targets)==2 and len({t['hashes']['parse.rs']for t in targets})==2
    candidates=[];aliases={};groups={}
    for target in targets:
        matching=[g for g in data['candidates']if g['rust_sha256']==target['hashes']['parse.rs']];assert len(matching)==1;g=matching[0];groups[g['candidate']]=g
        assert any(p['files']==target['hashes']and p.get('source_path')==target['path']for p in g['verified_pairs'])
        role = target.get('role', 'A' if target['name'].startswith('r18-dna-base6') else 'B')
        assert role in ('A', 'B')
        threshold = 15 if role == 'A' else 5
        aliases[g['candidate']] = role
        obs=[o for o in g['observations']if o['run_id']in ids and o['entry_role']=='candidate'and o['role']=='independent_confirmation'];assert all(o['proof_sha256']==target['hashes']['Parse.lean']for o in obs)
        c={'role':role,'goal_pool_share_pct':threshold,'name':target['name'],'path':target['path'],'files':target['hashes'],'verified_pairs':g['verified_pairs'],'single':{},'by_runner':[]}
        for cal in('primary','shadow'):
            chosen=[o for o in obs if o['calibration']==cal];assert len(chosen)==plan['planned_total_final_blocks']and len({(o['run_id'],o['block'])for o in chosen})==len(chosen)
            c['single'][cal]=dist([o['single_pool_share_pct']for o in chosen])
            for rid in sorted(ids):
                rr=[o for o in chosen if o['run_id']==rid];assert len(rr)==plan['blocks_per_runner'];c['by_runner'].append({'run_id':rid,'calibration':cal,**dist([o['single_pool_share_pct']for o in rr])})
        by={(o['run_id'],o['block'],o['calibration']):o for o in obs};gaps=[]
        for rid,block in sorted({(o['run_id'],o['block'])for o in obs}):
            p=by[rid,block,'primary']['single_pool_share_pct'];s=by[rid,block,'shadow']['single_pool_share_pct'];gaps.append({'run_id':rid,'block':block,'primary_pct':p,'shadow_pct':s,'absolute_share_gap_pct':abs(p-s),'zero_disagreement':(p==0)!=(s==0),'target_disagreement':(p>=threshold)!=(s>=threshold)})
        c['control_disagreement']={'blocks':gaps,'zero_disagreement_count':sum(x['zero_disagreement']for x in gaps),'target_disagreement_count':sum(x['target_disagreement']for x in gaps),'max_absolute_share_gap_pct':max(x['absolute_share_gap_pct']for x in gaps),'median_absolute_share_gap_pct':st.median(x['absolute_share_gap_pct']for x in gaps)};candidates.append(c)
    assert {c['role']for c in candidates}=={'A','B'}
    joint=[j for j in data['joint']if set(j['candidates'])==set(aliases)];assert len(joint)==1;rows=[]
    for r in joint[0]['matched_observations']:
        if r['run_id']not in ids:continue
        alone={aliases[k]:v for k,v in r['separate_pct'].items()};together={aliases[k]:v for k,v in r['simultaneous_geometric_pct'].items()};rows.append({'run_id':r['run_id'],'block':r['block'],'calibration':r['calibration'],'single_pct':alone,'joint_geometric_pct':together,'joint_minus_single_pct':{k:together[k]-alone[k]for k in alone},'both_geometric_thresholds_met':together['A']>=15 and together['B']>=5})
    assert len(rows)==2*plan['planned_total_final_blocks'];joint_summary={}
    for cal in('primary','shadow'):
        rr=[r for r in rows if r['calibration']==cal];assert len(rr)==plan['planned_total_final_blocks'];joint_summary[cal]={'A':dist([r['joint_geometric_pct']['A']for r in rr]),'B':dist([r['joint_geometric_pct']['B']for r in rr]),'both_geometric_thresholds_met_count':sum(r['both_geometric_thresholds_met']for r in rr)}
    result={'status':'VERIFIED_FINAL_FROZEN_PAIR_CONFIRMATION_CONDITIONAL_SCORES','snapshot':data['snapshot'],'plan_sha256':hashlib.sha256(args.plan.read_bytes()).hexdigest(),'analysis_sha256':hashlib.sha256(args.analysis.read_bytes()).hexdigest(),'run_ids':sorted(ids),'runner_count':2,'blocks_per_runner':plan['blocks_per_runner'],'total_final_blocks_per_candidate':plan['planned_total_final_blocks'],'candidates':sorted(candidates,key=lambda c:c['role']),'joint_summary':joint_summary,'joint_by_block':rows,'same_source_time_controls':[s for s in data['same_source_controls']if s['run_id']in ids],'environments':runs,'formal_admission':'UNKNOWN_NOT_SUBMITTED','formal_payable_goal_status':'NOT_ESTABLISHED','limits':['Only the two predeclared final runner contexts are summarized here; discovery and early Y data are separate.','Eight blocks are not eight runners. Observed target counts are not formal success probabilities.','Scores are fixed-snapshot conditional pool geometry, not validator total weight, expected reward or formal payability.','Joint scores are recomputed with both points, conditional on distinct eligible hotkeys without older surviving submissions. They are not the sum of independently normalized forecasts.']};args.output.write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps({'snapshot':result['snapshot'],'candidates':[{'role':c['role'],'name':c['name'],'single':c['single'],'zero_control_disagreements':c['control_disagreement']['zero_disagreement_count'],'target_control_disagreements':c['control_disagreement']['target_disagreement_count']}for c in result['candidates']],'joint':joint_summary},indent=2))

if __name__=='__main__':main()
