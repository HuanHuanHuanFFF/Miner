"""Read-only actual public-CI entry and source identity preflight."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,subprocess
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[4]
spec=importlib.util.spec_from_file_location('r18_public_ci_entry',HERE/'development-ci.py');m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
env=m.env();out=HERE/'development-entry-evidence';out.mkdir()
records={};values={}
for name,url in [('repository','repos/'+m.REPO),('workflow','repos/'+m.REPO+'/actions/workflows/floatlib-validate.yml'),('remote-head','repos/'+m.REPO+'/commits/huan/codex-gpt'),('runs','repos/'+m.REPO+'/actions/runs?branch=huan%2Fcodex-gpt&per_page=30')]:
    raw=m.gh(['api',url],env).encode();path=out/(name+'.json');path.write_bytes(raw);values[name]=json.loads(raw);records[name]=dict(file=path.relative_to(ROOT).as_posix(),bytes=len(raw),sha256=hashlib.sha256(raw).hexdigest())
head=subprocess.check_output(['git','rev-parse','HEAD'],cwd=ROOT).decode().strip()
active=[dict(run=r['id'],status=r['status'],url=r['html_url']) for r in values['runs']['workflow_runs'] if r['status']!='completed']
assert not values['repository']['private'] and values['workflow']['state']=='active' and values['remote-head']['sha']==head
assert not active,active
report=dict(checked_utc=datetime.now(timezone.utc).isoformat(),public_repository=True,workflow_active=True,source_commit=head,active_own_jobs=active,public_standard_slots=1,allow_private=False,responses=records)
(HERE/'development-entry-preflight.json').write_bytes((json.dumps(report,ensure_ascii=False,indent=2)+'\n').encode());print(json.dumps({k:v for k,v in report.items() if k!='responses'}))
