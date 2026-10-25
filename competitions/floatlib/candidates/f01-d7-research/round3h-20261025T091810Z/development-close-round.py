"""Close only after the full window and collection of every started job."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,json
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[4];D7=HERE.parent
ap=argparse.ArgumentParser();ap.add_argument('--close',action='store_true');a=ap.parse_args()
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
read=lambda p:json.loads(p.read_bytes())
save=lambda p,v:p.write_bytes((json.dumps(v,ensure_ascii=False,indent=2)+'\n').encode())
state_path=ROOT/'competitions/floatlib/coordination/development-status.json';state=read(state_path);rr=state['research_round']
assert rr['id']=='R16-20261025T091810Z' and not rr['active_ci'] and not state['active_jobs']
assert len(rr['started_ci'])==len(rr['completed_ci'])==10 and set(rr['started_ci'])==set(rr['completed_ci'])
assert sha(ROOT/state['kernel'])==state['kernel_sha256']=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert sha(D7/'champion-time-estimate.json')=='9222bdf6edec6efe75c009203405357155045f75028727a2e1fc237b9a343e53'
jobs=[];artifact_files=0
for rid in rr['completed_ci']:
    folder=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'/str(rid)
    meta=read(folder/'ci-run.json');idx=read(folder/'original-artifact-hashes.json');assert meta['status']=='completed'
    artifact_files+=len(idx['files'])
    jobs.append(dict(run=rid,conclusion=meta['conclusion'],source_commit=meta['headSha'],artifact_index_sha256=sha(folder/'original-artifact-hashes.json'),artifact_files=len(idx['files'])))
outcomes=[]
for seed,candidate in ((1626003,'f01-r16-dev-native-repack1'),(1626003,'f01-r16-dev-a4b2-entry3'),(1626008,'f01-r16-dev-native-add-high3')):
    row=read(HERE/f'result-{seed}-{candidate}-vs-f01-r15-dev-packed-b2-1.json')
    assert row['full_gate_both'] and not row['local_discovery_screen_passed']
    outcomes.append({k:row[k] for k in ('candidate','sha256','run','seed','relative_normalized_ratio','gain_p05','per_operation_normalized')})
proof=read(HERE/'development-proof-f01-r16-dev-u32-roundtrip-probe1-40192000569.json')
assert not proof['statement_pass'] and proof['kernel_replay_and_helper_axiom_audit']=='NOT_RUN'
now=datetime.now(timezone.utc);deadline=datetime.fromisoformat(rr['deadline_utc'].replace('Z','+00:00'))
report=dict(round=rr['id'],start_utc=rr['start_utc'],deadline_utc=rr['deadline_utc'],checked_at_utc=now.isoformat(),
    budget_status='COMPLETED_180_MINUTES' if a.close else 'FINAL_REVIEW_ACTIVE_UNTIL_DEADLINE',
    ci=jobs,all_started_ci_terminal_and_collected=True,original_artifact_files=artifact_files,
    retained_candidate=state['candidate'],retained_sha256=state['kernel_sha256'],adoption_performed=False,
    timed_outcomes=outcomes,confirmation_groups_generated=False,
    champion=309,champion_goal='UNACHIEVED',formal_submission='NOT_SUBMITTED',
    numeric_model_sha256_unchanged=sha(D7/'champion-time-estimate.json'),
    official_receipt='competitions/floatlib/candidates/f01-d7-research/official-20261025T121232Z/receipts.json',
    roundtrip_math_probe=dict(source_sha256=proof['kernel_sha256'],run=40192000569,statement='FAILED_ONE_REWRITE',helper_replay_and_axioms='NOT_RUN',next='Resolve exact toUInt32_of_nonnegative_integral_decode rewrite target in original mapped compiler report; no further CI this round'),
    control_anomaly='Same source/input repeat returned ADD/41 from2.9066 to0.9076; both samples retained, root cause UNKNOWN; no model refit',
    source_policy_and_format_receipts=['development-probe-canonicalization.json','development-add-policy-feedback.md'])
if a.close:
    assert now>=deadline,'Do not end the authorized window early'
    report.update(ended_at_utc=now.isoformat(),elapsed_minutes=(now-datetime.fromisoformat(rr['start_utc'].replace('Z','+00:00'))).total_seconds()/60)
    rr.update(state='COMPLETED_WINDOW',window_status='COMPLETED_180_MINUTES',ended_at_utc=now.isoformat(),current_phase='All10 CI collected; three timed mechanisms negative; no adoption; final numeric bridge has one compiler rewrite gap')
    state.update(state='R16_WINDOW_COMPLETED_RETAIN_B2_ALL_CI_COLLECTED',updated_at_utc=now.isoformat())
    state['collaboration']['state']='COMPLETED_WINDOW'
    save(state_path,state)
save(HERE/'development-round-results.json',report)
print(json.dumps(dict(budget_status=report['budget_status'],ci=len(jobs),original_artifact_files=artifact_files,adoption=False,champion=309)))
