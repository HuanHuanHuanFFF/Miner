"""Record our actual run identity and terminal receipt without overwriting peers."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,json,os
OUT=Path(__file__).resolve().parent;ROOT=OUT.parents[4]
ap=argparse.ArgumentParser();ap.add_argument('--dispatch',type=Path);ap.add_argument('--complete',type=int);a=ap.parse_args()
state_path=ROOT/'competitions/floatlib/coordination/development-status.json';old=state_path.read_bytes();state=json.loads(old);rr=state['research_round'];assert rr['id']=='R19-20261026T194639Z'
now=datetime.now(timezone.utc).isoformat()
if a.dispatch:
    d=json.loads(a.dispatch.read_bytes());run=d['run']['databaseId'];assert len(rr['active_ci'])==0 and run not in rr['started_ci']
    job={'run':run,'url':d['run']['url'],'source_commit':d['source_commit'],'workflow':d['workflow'],'inputs':d['inputs'],'dispatch_receipt':a.dispatch.resolve().relative_to(ROOT).as_posix(),'state':'RUNNING','updated_utc':now}
    rr['started_ci'].append(run);rr['active_ci'].append(run);state['active_jobs']=[job]
else:
    run=a.complete;assert run in rr['active_ci']
    base=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'/str(run)
    meta=json.loads((base/'ci-run.json').read_bytes());assert meta['status']=='completed' and (base/'original-artifact-hashes.json').is_file()
    job=json.loads((OUT/f'development-ci-job-{run}.json').read_bytes());assert job['source_commit']==meta['headSha']
    job.update(state='TERMINAL_COLLECTED',conclusion=meta['conclusion'],updated_utc=now,evidence=base.relative_to(ROOT).as_posix())
    rr['active_ci'].remove(run);rr['completed_ci'].append(run);state['active_jobs']=[]
job_path=OUT/f'development-ci-job-{run}.json';job_path.write_bytes((json.dumps(job,ensure_ascii=False,indent=2)+'\n').encode())
state['updated_at_utc']=now;tmp=state_path.with_name('development-status-job.tmp');assert not tmp.exists();tmp.write_bytes((json.dumps(state,ensure_ascii=False,indent=2)+'\n').encode());assert state_path.read_bytes()==old;os.replace(tmp,state_path)
print(json.dumps(job,ensure_ascii=False))
