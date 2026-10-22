"""Observe this round's existing CI jobs; collect each terminal artifact once."""
from pathlib import Path
import concurrent.futures,datetime,json,os,subprocess,sys
ROOT=Path.cwd();STATE=ROOT/'competitions/floatlib/coordination/development-status.json'
CI=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci.py'
state=json.loads(STATE.read_bytes());ledger=state['collaboration']['active_ci']

def save_state():
    state['updated_at_utc']=datetime.datetime.now(datetime.timezone.utc).isoformat()
    state['active_jobs']=[{k:r.get(k) for k in ['run','status','candidates','source_commit']} for r in ledger if r.get('status')!='completed']
    tmp=STATE.with_name(STATE.name+'.update-tmp');tmp.write_bytes((json.dumps(state,ensure_ascii=False,indent=2)+'\n').encode());os.replace(tmp,STATE)

if len(sys.argv)==3 and sys.argv[1]=='--register-seed':
    seed=sys.argv[2];assert seed.isdecimal()
    found=[]
    for p in (CI.parent/'ci-runs').glob('dispatch-*/dispatch.json'):
        d=json.loads(p.read_bytes())
        if d.get('inputs',{}).get('seed')==seed and d.get('state')=='RUN_IDENTIFIED':found.append((p,d))
    assert len(found)==1,(seed,len(found))
    p,d=found[0];rid=d['run']['databaseId']
    if not any(r['run']==rid for r in ledger):
        ledger.append(dict(run=rid,seed=int(seed),candidates=d['inputs']['candidates'].split(','),source_commit=d['source_commit'],status=d['run']['status'],receipt=p.relative_to(ROOT).as_posix(),created_at_utc=d['run']['createdAt']))
    save_state();print(json.dumps({'registered':rid,'seed':seed,'active_jobs':state['active_jobs']}));raise SystemExit(0)

def status(row):
    result=subprocess.run([sys.executable,str(CI),'status','--run',str(row['run'])],capture_output=True,text=True,encoding='utf-8')
    assert result.returncode==0,result.stderr
    return json.loads(result.stdout)

pending=[row for row in ledger if not row.get('artifact_index')]
with concurrent.futures.ThreadPoolExecutor(max_workers=2) as pool:
    observations=list(pool.map(status,pending))
for row,value in zip(pending,observations):
    row.update(status=value['status'],conclusion=value['conclusion'],url=value['url'])
    if value['status']=='completed':
        directory=CI.parent/'ci-runs'/str(row['run']);index=directory/'original-artifact-hashes.json'
        if not index.exists():
            result=subprocess.run([sys.executable,str(CI),'collect','--run',str(row['run'])],capture_output=True,text=True,encoding='utf-8')
            assert result.returncode==0,result.stderr
        assert index.exists(),f"Missing artifact for terminal job {row['run']}"
        row['artifact_index']=index.relative_to(ROOT).as_posix()
        artifact=directory/json.loads(index.read_bytes())['directory']
        summary=json.loads((artifact/'summary.json').read_bytes())
        print(json.dumps({'run':row['run'],'results':[{k:r.get(k) for k in ['candidate','full_gate','compile_pass','reason']} for r in summary['results']]}))
    else:
        print(json.dumps(value))
save_state()
