"""Bind an already identified R7 dispatch to the current state; no network or dispatch."""
from pathlib import Path
import argparse,datetime,json,os,subprocess

ap=argparse.ArgumentParser();ap.add_argument('--seed',required=True,type=int);a=ap.parse_args()
root=Path.cwd();runs=root/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'
state_path=root/'competitions/floatlib/coordination/development-status.json'
state=json.loads(state_path.read_bytes());assert state['collaboration']['round']=='R7'
matches=[]
for p in runs.glob('dispatch-*/dispatch.json'):
    row=json.loads(p.read_bytes())
    if row.get('state')=='RUN_IDENTIFIED' and int(row['inputs']['seed'])==a.seed:
        matches.append((p,row))
assert matches,'No identified exact dispatch; do not invent a job'
path,dispatch=max(matches,key=lambda x:x[0].parent.name)
run=dispatch['run'];commit=dispatch['source_commit'];assert run['headSha']==commit
names=dispatch['inputs']['candidates'].split(',')
if names==['f01-d7-public-suite']:
    frozen=subprocess.check_output(['git','show',commit+':competitions/floatlib/candidates/f01-d7-public-suite/suite-plan.json'])
    plan=json.loads(frozen);assert plan['seed']==a.seed
    names=[x['candidate'] for x in plan['candidates']]
row={'run':run['databaseId'],'seed':a.seed,'wrapper':dispatch['inputs']['candidates'],'candidates':names,'source_commit':commit,'status':run['status'],'collected':False,'dispatch_receipt':path.relative_to(root).as_posix()}
ledger=state['collaboration']['active_ci']
existing=next((x for x in ledger if x['run']==row['run']),None)
if existing:
    assert existing['source_commit']==commit and existing['seed']==a.seed
else:ledger.append(row)
for item in ledger:
    rp=runs/str(item['run']);meta=rp/'ci-run.json'
    if meta.exists():
        actual=json.loads(meta.read_bytes());assert actual['headSha']==item['source_commit']
        item.update(status=actual['status'],conclusion=actual['conclusion'],collected=(rp/'original-artifact-hashes.json').exists())
state['active_jobs']=[x for x in ledger if x['status']!='completed']
state['updated_at_utc']=datetime.datetime.now(datetime.timezone.utc).isoformat()
tmp=state_path.with_suffix('.r7-update-tmp');tmp.write_bytes((json.dumps(state,ensure_ascii=False,indent=2)+'\n').encode());os.replace(tmp,state_path)
print(json.dumps({'recorded_run':row['run'],'exact_source_commit':commit,'active_runs':[x['run'] for x in state['active_jobs']]}))
