"""Close the elapsed R5 window only after every started CI is collected."""
from pathlib import Path
from statistics import median
import argparse, datetime, hashlib, json, os

ROOT=Path.cwd();OWN=Path(__file__).resolve().parent
ap=argparse.ArgumentParser();ap.add_argument('--candidate',required=True);ap.add_argument('--confirmation-run',required=True,type=int);a=ap.parse_args()
P=ROOT/'competitions/floatlib/coordination/development-status.json'
state=json.loads(P.read_bytes());c=state['collaboration'];summary=json.loads((OWN/'summary.json').read_bytes())
now=datetime.datetime.now(datetime.timezone.utc);end=datetime.datetime.fromisoformat(c['end_utc'].replace('Z','+00:00'))
assert now>=end, 'The user requested the full ninety-minute continuation'
assert len(summary['jobs'])==len(c['active_ci']) and all(j['collected'] for j in summary['jobs'])
assert all(j['status']=='completed' and j.get('artifact_index') for j in c['active_ci'])
kernel=ROOT/'competitions/floatlib/candidates'/a.candidate/'Kernel.lean';raw=kernel.read_bytes();sha=hashlib.sha256(raw).hexdigest()
rows=[r for r in summary['records'] if r['candidate']==a.candidate and r.get('full_gate') and r['kernel_sha256']==sha]
assert len(rows)>=2 and any(r['run']==a.confirmation_run for r in rows)
assert all(r['matches_current_official_fingerprint'] for r in rows)
assert summary.get('git_payload_audit',{}).get('verified')==summary['payload_files_verified']
(OWN/'preclose-state.json').write_bytes(P.read_bytes())
def save(p,d):
    t=p.with_name(p.name+'.update-tmp');t.write_bytes((json.dumps(d,ensure_ascii=False,indent=2)+'\n').encode());os.replace(t,p)
manifest=kernel.with_name('manifest.json');m=json.loads(manifest.read_bytes());m.update(proof_status='PASS_FULL_GATE_FROZEN_INDEPENDENT_CONFIRMATION',full_gate_runs=[r['run'] for r in rows]);save(manifest,m)
c.update(state='COMPLETE_ALL_STARTED_CI_COLLECTED',confirmed_candidate=a.candidate,confirmation_run=a.confirmation_run,closed_at_utc=now.isoformat())
state.update(state='R5_COMPLETE_FROZEN_FULL_PACKAGE_CONFIRMED_CHAMPION_NOT_ACHIEVED',updated_at_utc=now.isoformat(),candidate=kernel.parent.relative_to(ROOT).as_posix(),kernel=kernel.relative_to(ROOT).as_posix(),kernel_sha256=sha,kernel_bytes=len(raw),manifest=manifest.relative_to(ROOT).as_posix(),proof_status='PASS_FULL_OFFICIAL_GATE_WITH_FROZEN_INDEPENDENT_CONFIRMATION',active_jobs=[],history={'previous_round_state':(OWN/'previous-state.json').relative_to(ROOT).as_posix(),'preclose_state':(OWN/'preclose-state.json').relative_to(ROOT).as_posix()},performance={'full_gate_runs':[r['run'] for r in rows],'seeds':[r['seed'] for r in rows],'cpus':[r['cpu'] for r in rows],'ratio_vs_shipped':[r['ratio_vs_shipped'] for r in rows],'kernels_vs_shipped':[r['kernels_vs_shipped'] for r in rows],'paired_gain_p05':[r['paired_gain_p05'] for r in rows]},payload_integrity={'status':'PASS_DISK_AND_COMMITTED_RAW_BYTES','verified_payloads':summary['payload_files_verified'],'evidence':(OWN/'summary.json').relative_to(ROOT).as_posix()})
comp=json.loads((OWN/'operation-comparisons.json').read_bytes())
state['current_champion_comparison']={'submission':comp['champion_submission'],'source_digest':comp['champion_sha256'],'policy_snapshot':comp['policy_snapshot'],'queried_at_utc':comp['queried_at_utc'],'candidate':a.candidate,'candidate_over_champion_time_inferred':median(r['whole_entry_inferred'] for r in comp['records'] if r['candidate']==a.candidate),'direct_paired_ratio':'UNKNOWN','method':comp['method'],'evidence':(OWN/'operation-comparisons.json').relative_to(ROOT).as_posix()}
save(P,state)
elapsed=(now-datetime.datetime.fromisoformat(c['start_utc'].replace('Z','+00:00'))).total_seconds()/60
save(OWN/'completion.json',{'window_start_utc':c['start_utc'],'window_end_utc':c['end_utc'],'closed_at_utc':now.isoformat(),'elapsed_minutes':elapsed,'drain_minutes':max(0,(now-end).total_seconds()/60),'candidate':a.candidate,'kernel_sha256':sha,'full_gate_runs':[r['run'] for r in rows],'confirmation_run':a.confirmation_run,'jobs':len(summary['jobs']),'all_started_jobs_collected':True,'payloads_verified':summary['payload_files_verified'],'champion_achieved':False,'formal_submission':'NOT_SUBMITTED'})
print(json.dumps({'candidate':a.candidate,'full_gate_runs':[r['run'] for r in rows],'jobs':len(summary['jobs']),'elapsed_minutes':elapsed}))
