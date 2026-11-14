"""Dispatch only immutable-reference observation, with exact Git provenance."""
from pathlib import Path
import argparse, datetime, hashlib, importlib.util, json, subprocess, time

ROOT=next(p for p in Path(__file__).resolve().parents if (p/'AGENTS.md').is_file())
HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('standing_ci_access',ROOT/'scripts/github-ci.py')
ci=importlib.util.module_from_spec(spec);spec.loader.exec_module(ci)
ap=argparse.ArgumentParser();ap.add_argument('--expect-commit',required=True);args=ap.parse_args()
branch=subprocess.check_output(['git','branch','--show-current'],cwd=ROOT,text=True).strip()
head=subprocess.check_output(['git','rev-parse','HEAD'],cwd=ROOT,text=True).strip()
assert branch=='huan/codex-gpt' and head==args.expect_commit
e=ci.env();repo=json.loads(ci.gh(['api','repos/'+ci.REPO],e));assert repo['private'] is False
remote=json.loads(ci.gh(['api','repos/'+ci.REPO+'/commits/'+branch],e));assert remote['sha']==head
listing=['run','list','--repo',ci.REPO,'--branch',branch,'--limit','20','--json','databaseId,headSha,status,createdAt,url']
known=json.loads(ci.gh(listing,e));assert all(x['status']=='completed' for x in known),'D slot occupied; wait and collect first'
files=['.github/workflows/deflate-baseline.yml','scripts/github-ci.py',
       HERE.relative_to(ROOT).as_posix()+'/readonly-reference-profile.py',
       HERE.relative_to(ROOT).as_posix()+'/dispatch-readonly-reference.py']
frozen={}
for path in files:
    raw=subprocess.check_output(['git','show',head+':'+path],cwd=ROOT)
    assert raw==(ROOT/path).read_bytes(),path
    frozen[path]=hashlib.sha256(raw).hexdigest()
stamp=datetime.datetime.now(datetime.timezone.utc).strftime('%Y%m%dT%H%M%SZ')
out=HERE/'ci-runs'/('reference-dispatch-'+stamp);out.mkdir(parents=True)
body={'ref':branch,'inputs':{'competition':'floatlib','candidates':'__torchlean_readonly_profile__','seed':'42','allow_private':'false'}}
ci.save(out/'request.json',body)
record={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'source_commit':head,'branch':branch,
        'request':body,'frozen_sha256':frozen,'scope':'Read-only immutable upstream reference analysis; no new entry or official score',
        'new_target_candidate_implementation':False,'state':'PREPARED'}
ci.save(out/'dispatch.json',record)
ci.gh(['api','--method','POST','repos/'+ci.REPO+'/actions/workflows/deflate-baseline.yml/dispatches','--input',str(out/'request.json')],e)
record['state']='SENT_NO_AUTOMATIC_RETRY';ci.save(out/'dispatch.json',record)
seen={x['databaseId'] for x in known}
for _ in range(12):
    rows=[x for x in json.loads(ci.gh(listing,e)) if x['databaseId'] not in seen and x['headSha']==head]
    if rows:
        assert len(rows)==1;record.update(state='RUN_IDENTIFIED',run=rows[0]);ci.save(out/'dispatch.json',record)
        print(json.dumps({'receipt':str(out),'run':rows[0]}));break
    time.sleep(2)
else:raise RuntimeError('Dispatch sent but not identified; inspect, never blind retry')
