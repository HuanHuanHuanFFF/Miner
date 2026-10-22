"""Collect published completed-job evidence despite the Actions results incident."""
from pathlib import Path
import argparse, hashlib, importlib.util, json, uuid

ROOT=Path.cwd();spec=importlib.util.spec_from_file_location('authorized_ci',ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci.py')
ci=importlib.util.module_from_spec(spec);spec.loader.exec_module(ci)
ap=argparse.ArgumentParser();ap.add_argument('--run',required=True);a=ap.parse_args();assert a.run.isdecimal()
env=ci.env();target=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'/a.run;target.mkdir(exist_ok=True)
meta=json.loads(ci.gh(['run','view',a.run,'--repo',ci.REPO,'--json','databaseId,headSha,headBranch,event,status,conclusion,createdAt,updatedAt,url,jobs'],env))
jobs=json.loads(ci.gh(['api',f'repos/{ci.REPO}/actions/runs/{a.run}/jobs'],env))
body_complete=bool(jobs['jobs']) and all(any(s['name']=='Complete job' and s['status']=='completed' for s in j['steps']) for j in jobs['jobs'])
if meta['status']!='completed' and not body_complete:
    print(json.dumps({'run':a.run,'status':meta['status'],'job_bodies_complete':False,'collected':False}));raise SystemExit(0)
if (target/'ci-run.json').exists() and not (target/'ci-run-before-terminal.json').exists():
    (target/'ci-run-before-terminal.json').write_bytes((target/'ci-run.json').read_bytes())
ci.save(target/'ci-run.json',meta);ci.save(target/'jobs-at-collection.json',jobs)
artifacts=json.loads(ci.gh(['api',f'repos/{ci.REPO}/actions/runs/{a.run}/artifacts'],env));ci.save(target/'artifacts.json',artifacts)
artifact=next(x for x in artifacts['artifacts'] if x['name']==f'floatlib-{a.run}-receipts' and not x['expired'])
index=target/'original-artifact-hashes.json'
if index.exists():
    receipt=json.loads(index.read_bytes());stage=target/receipt['directory']
    for name,row in receipt['files'].items():
        b=(stage/name).read_bytes();assert len(b)==row['bytes'] and hashlib.sha256(b).hexdigest()==row['sha256']
else:
    stage=target/('download-'+uuid.uuid4().hex);stage.mkdir()
    ci.gh(['run','download',a.run,'--repo',ci.REPO,'--name',artifact['name'],'--dir',str(stage)],env)
    rows={p.relative_to(stage).as_posix():{'sha256':hashlib.sha256(p.read_bytes()).hexdigest(),'bytes':p.stat().st_size} for p in stage.rglob('*') if p.is_file()}
    ci.save(index,{'artifact':artifact,'directory':stage.name,'files':rows})
summary=json.loads((stage/'summary.json').read_bytes());assert summary['source_commit']==meta['headSha']
for job in jobs['jobs']:
    log=target/('job-'+str(job['id'])+'.log')
    if not log.exists():log.write_bytes(ci.gh(['api',f'repos/{ci.REPO}/actions/jobs/{job["id"]}/logs'],env).encode())
ci.save(target/'collection-status.json',{'run':a.run,'workflow_status':meta['status'],'workflow_conclusion':meta['conclusion'],'job_bodies_complete':body_complete,'artifact_collected':True,'scope':'Original gate evidence and control-plane terminal status are distinct. Never infer a completed workflow from Complete job alone.'})
print(json.dumps({'run':a.run,'status':meta['status'],'conclusion':meta['conclusion'],'job_bodies_complete':body_complete,'results':[(x['candidate'],x['full_gate'],x['compile_pass'],x.get('ratio')) for x in summary['results']]},ensure_ascii=False))
