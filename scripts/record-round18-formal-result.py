"""Bind the completed official #603 result to its frozen files and raw receipts."""
from pathlib import Path
import hashlib,json

ROOT=Path(__file__).resolve().parents[1]
E=ROOT/'evidence/round18/formal-a'
read=lambda p:json.loads(p.read_bytes())
status=read(E/'latest-status.json');upload=read(E/'submission-receipt.json')
assert status['terminal_result_observed'] and status['gate_status'] in ('passed','accepted')
assert status['admission']['admitted'] is True and status['score']['payment_eligible'] is True
assert status['bundle_digest']==upload['bundle_digest']
audited={}
for p in E.glob('*.receipt.json'):
 r=read(p);raw=E/r['raw_file'];assert hashlib.sha256(raw.read_bytes()).hexdigest()==r['sha256']
 audited[p.name]=hashlib.sha256(p.read_bytes()).hexdigest()
assert hashlib.sha256((E/'submission-accepted.response.json').read_bytes()).hexdigest()==upload['raw_response']['sha256']
leaderpath=sorted(E.glob('leaderboard-*.response.json'))[-1];leader=read(leaderpath)
row=next(r for r in leader['ranking'] if r['submission_ids']==['603'])
assert leader['context']['snapshot_id']==status['snapshot']['snapshot_id']==row.get('snapshot_id',status['snapshot']['snapshot_id'])
assert row['payable_weight']==status['score']['payable_weight']
admissionpath=sorted(E.glob('admission-*.response.json'))[-1];admission=read(admissionpath)
assert admission['context']['snapshot_id']==status['snapshot']['snapshot_id']
weights_path=sorted(E.glob('weights-*.response.json'))[-1];weights=read(weights_path)
assert weights['context']['snapshot_id']==status['snapshot']['snapshot_id']
report_path=sorted(E.glob('report-final-*.response.json'))[-1];report=read(report_path)['report']
assert 'LZ77.Obligation slot.parse' in report and 'corpus-stage1' in report and 'corpus-stage2' in report
assert '4864300' in report and '4955619' in report
pair=upload['files'];source=ROOT/'candidates/r18-rf-sf-content-proof1'
for name,digest in pair.items():assert hashlib.sha256((source/name).read_bytes()).hexdigest()==digest
result={**status,'status':'VERIFIED_FORMAL_GATE_ADMISSION_FRONTIER_AND_PAYABLE_SHARE','files':pair,'competition_pool_share_pct':100*row['payable_weight'],'leaderboard_rank':row['rank'],'bounty_earned_alpha_at_snapshot':row['bounty_earned_alpha'],'actual_wallet_payment':'UNKNOWN_NOT_QUERIED','weights_context':weights['context'],'chain_accepted_for_this_weight_pass':weights.get('chain_accepted'),'weight_pass_dry_run':weights.get('dry_run'),'admission_speed_test':admission['decision']['speed_test'],'report':str(report_path.relative_to(ROOT)),'leaderboard':str(leaderpath.relative_to(ROOT)),'admission_receipt':str(admissionpath.relative_to(ROOT)),'audited_receipt_hashes':audited,'research_goal_status':'UNMET_A_BELOW_15_AND_B_NOT_FORMALLY_SUBMITTED','scope':'One official submission only. Snapshot eligibility/share is not an actual payment receipt or a guarantee of future share. Original 11-hour observations are retained.'}
(E/'result-summary.json').write_bytes((json.dumps(result,indent=2)+'\n').encode())
vp=source/'VERIFICATION.json';v=read(vp);assert v['files']==pair
v['formal_admission']='VERIFIED_PASSED';v['formal_reward_pool_share_pct']=result['competition_pool_share_pct']
v['formal_submission'].update({'gate_status':'passed','admitted':True,'on_frontier':True,'payment_eligible':True,'snapshot_id':status['snapshot']['snapshot_id'],'result':'evidence/round18/formal-a/result-summary.json','actual_wallet_payment':'UNKNOWN_NOT_QUERIED'})
vp.write_bytes((json.dumps(v,indent=2)+'\n').encode())
print(json.dumps({k:result[k] for k in ('competition_pool_share_pct','leaderboard_rank','bounty_earned_alpha_at_snapshot','actual_wallet_payment','chain_accepted_for_this_weight_pass','weight_pass_dry_run')}))
