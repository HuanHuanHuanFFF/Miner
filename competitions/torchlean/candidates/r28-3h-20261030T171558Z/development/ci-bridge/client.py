"""Manual public-runner operations; existing Git credential only in process memory."""
from pathlib import Path
import argparse,datetime,hashlib,importlib.util,json,subprocess,time,uuid
ROOT=next(p for p in Path(__file__).resolve().parents if (p/'AGENTS.md').is_file());REPO='HuanHuanHuanFFF/Miner';ROUND=ROOT/'competitions/torchlean/candidates/r28-3h-20261030T171558Z';EVIDENCE=ROUND/'evidence'
spec=importlib.util.spec_from_file_location('retained_authenticated_ci_helper',ROOT/'scripts/github-ci.py');base=importlib.util.module_from_spec(spec);spec.loader.exec_module(base)
terminal_spec=importlib.util.spec_from_file_location('r28_terminal_evidence',Path(__file__).with_name('terminal-evidence.py'));terminal=importlib.util.module_from_spec(terminal_spec);terminal_spec.loader.exec_module(terminal)
def main():
 ap=argparse.ArgumentParser();ap.add_argument('mode',choices=['dispatch','status','collect']);ap.add_argument('--run');ap.add_argument('--expect-commit');a=ap.parse_args();env=base.env()
 def gh(args):return base.gh(args,env)
 if a.mode=='dispatch':
  assert a.expect_commit
  sha=subprocess.check_output(['git','rev-parse','HEAD'],cwd=ROOT,text=True).strip();branch=subprocess.check_output(['git','branch','--show-current'],cwd=ROOT,text=True).strip();assert sha==a.expect_commit and branch=='huan/codex-gpt'
  assert json.loads(gh(['api','repos/'+REPO]))['private'] is False
  remote_ref=subprocess.check_output(['git','ls-remote','origin','refs/heads/'+branch],cwd=ROOT,text=True).split();assert len(remote_ref)==2 and remote_ref[0]==sha,'ExactGitremoterefnotpushed'
  plan=json.loads((ROUND/'ci-plan.json').read_bytes());assert datetime.datetime.now(datetime.timezone.utc)<datetime.datetime.fromisoformat(plan['dispatch_not_after_utc'])
  paths=[Path(__file__).relative_to(ROOT).as_posix(),Path(__file__).with_name('terminal-evidence.py').relative_to(ROOT).as_posix(),'.github/workflows/deflate-baseline.yml','competitions/torchlean/candidates/r28-3h-20261030T171558Z/development/ci-bridge/runner.py',plan.get('prepare_script','competitions/torchlean/scripts/ci-prepare.sh'),(ROUND/'ci-plan.json').relative_to(ROOT).as_posix()]+[x['path'] for x in plan.get('helpers',[]) if not x.get('fetch')]+plan.get('owned_sources',[]);hashes={}
  for p in paths:
   blob=subprocess.check_output(['git','show',sha+':'+p],cwd=ROOT);assert blob==(ROOT/p).read_bytes(),p;hashes[p]=hashlib.sha256(blob).hexdigest()
  listing=['run','list','--repo',REPO,'--workflow','deflate-baseline.yml','--branch',branch,'--limit','25','--json','databaseId,headSha,status,createdAt,url'];prior=json.loads(gh(listing));assert not any(x['status']!='completed' and not terminal.verified(EVIDENCE/str(x['databaseId']),x['headSha']) for x in prior),'ExistingDbranchCIstillactive_without_verified_finalevidence';seen={x['databaseId'] for x in prior}
  stamp=datetime.datetime.now(datetime.timezone.utc).strftime('%Y%m%dT%H%M%SZ');out=EVIDENCE/('dispatch-'+stamp);out.mkdir(parents=True);req={'ref':branch,'inputs':{'competition':'floatlib','candidates':'__torchlean_r28__','seed':str(plan['dispatch_seed']),'allow_private':'false'}};base.save(out/'request.json',req);receipt={'state':'REQUEST_PREPARED','source_commit':sha,'frozen_files':hashes,'repository_public':True,'request':req};base.save(out/'dispatch.json',receipt)
  gh(['api','--method','POST','repos/'+REPO+'/actions/workflows/deflate-baseline.yml/dispatches','--input',str(out/'request.json')]);receipt['state']='SENT_NO_AUTO_RETRY';base.save(out/'dispatch.json',receipt)
  identify_listing=listing+['--commit',sha]
  for _ in range(12):
   rows=[x for x in json.loads(gh(identify_listing)) if x['databaseId'] not in seen and x['headSha']==sha]
   if rows:
    assert len(rows)==1;receipt.update(state='RUN_IDENTIFIED',run=rows[0]);base.save(out/'dispatch.json',receipt);print(json.dumps(receipt));return
   time.sleep(2)
  raise RuntimeError('Sent_butnotidentified_inspectbeforeanyretry')
 assert a.run and a.run.isdecimal();sid=a.run;meta=json.loads(gh(['run','view',sid,'--repo',REPO,'--json','databaseId,headSha,status,conclusion,url,jobs,createdAt,updatedAt']));print(json.dumps({'run':sid,'status':meta['status'],'conclusion':meta['conclusion'],'jobs':[{'name':x['name'],'status':x['status'],'active':[s['name'] for s in x['steps'] if s['status']=='in_progress']} for x in meta['jobs']]}))
 if a.mode=='collect':
  assert meta['status']=='completed' or terminal.verified(EVIDENCE/sid,meta['headSha']);out=EVIDENCE/sid;out.mkdir(exist_ok=True);base.save(out/'ci-run.json',meta);arts=json.loads(gh(['api','repos/'+REPO+'/actions/runs/'+sid+'/artifacts']));base.save(out/'artifacts.json',arts);art=next(x for x in arts['artifacts'] if x['name']=='torchlean-'+sid+'-receipts' and not x['expired']);dest=out/('download-'+uuid.uuid4().hex);dest.mkdir();gh(['run','download',sid,'--repo',REPO,'--name',art['name'],'--dir',str(dest)]);files={p.relative_to(dest).as_posix():{'bytes':p.stat().st_size,'sha256':hashlib.sha256(p.read_bytes()).hexdigest()} for p in dest.rglob('*') if p.is_file()};base.save(out/'original-artifact-hashes.json',{'artifact':art,'directory':dest.name,'files':files});(out/'ci.log').write_text(gh(['run','view',sid,'--repo',REPO,'--log']),encoding='utf-8');summary=json.loads((dest/'summary.json').read_bytes());assert summary['source_commit']==meta['headSha'];print(json.dumps({'directory':str(dest),'files':len(files),'source_commit':meta['headSha'],'complete':summary['complete'],'error':summary.get('error'),'results':[(x['name'],x['proof_state'],x['measurement_state']) for x in summary['results']]}))
if __name__=='__main__':main()
