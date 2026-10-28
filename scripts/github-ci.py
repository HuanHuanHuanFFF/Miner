"""Operate authorized manual CI with existing credentials kept only in process memory."""
from pathlib import Path
import argparse,datetime,hashlib,importlib.util,json,os,re,subprocess,sys,time,uuid

ROOT=Path(__file__).resolve().parents[1];REPO='HuanHuanHuanFFF/Miner'

def env():
    e=os.environ.copy()
    if not (e.get('GH_TOKEN') or e.get('GITHUB_TOKEN')):
        p=subprocess.run(['git','credential','fill'],input='protocol=https\nhost=github.com\n\n',text=True,capture_output=True,check=True,cwd=ROOT)
        fields=dict(x.split('=',1) for x in p.stdout.splitlines() if '=' in x)
        if not fields.get('password'):raise RuntimeError('Existing credential unavailable')
        e['GH_TOKEN']=fields['password']
    return e

def gh(args,e):
    p=subprocess.run(['gh',*args],cwd=ROOT,env=e,capture_output=True,text=True,encoding='utf-8')
    if p.returncode:raise RuntimeError(f'GitHub request failed ({p.returncode}): '+p.stderr[:500])
    return p.stdout

def save(p,value):p.write_text(json.dumps(value,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')

def main():
    ap=argparse.ArgumentParser();ap.add_argument('mode',choices=['dispatch','status','collect']);ap.add_argument('--run');ap.add_argument('--workflow',default='floatlib-validate.yml');ap.add_argument('--candidates',default='baseline');ap.add_argument('--seed',default='42');ap.add_argument('--branch',default='codex/multi-track-floatlib',help='Explicit authorized experimental branch; must match checked-out branch');ap.add_argument('--expect-commit',help='Abort before dispatch unless HEAD equals this reviewed exact commit');args=ap.parse_args()
    e=env();evidence=ROOT/'competitions/floatlib/evidence';evidence.mkdir(exist_ok=True)
    if args.mode=='dispatch':
        assert re.fullmatch(r'(?:baseline|f01-[a-z0-9-]+)(?:,(?:baseline|f01-[a-z0-9-]+))*',args.candidates)
        assert args.seed.isdecimal();assert args.workflow in ['floatlib-validate.yml','deflate-baseline.yml']
        branch=subprocess.check_output(['git','branch','--show-current'],cwd=ROOT,text=True).strip();sha=subprocess.check_output(['git','rev-parse','HEAD'],cwd=ROOT,text=True).strip();assert branch==args.branch and branch.startswith(('codex/','huan/')),'Explicit experimental branch must match checkout'
        if args.expect_commit:assert sha==args.expect_commit,'Reviewed dispatch commit differs from HEAD'
        subprocess.run(['git','check-ref-format','--branch',branch],cwd=ROOT,check=True,stdout=subprocess.DEVNULL)
        raw=gh(['api',f'repos/{REPO}'],e);repository=json.loads(raw);assert repository['private'] is False
        remote=json.loads(gh(['api',f'repos/{REPO}/commits/{branch}'],e));assert remote['sha']==sha,'Push precise commit before dispatch'
        stamp=datetime.datetime.now(datetime.timezone.utc).strftime('%Y%m%dT%H%M%SZ');receipt=evidence/('dispatch-'+stamp);receipt.mkdir()
        (receipt/'repository.response.json').write_text(raw,encoding='utf-8')
        checked={}
        paths=['competitions/floatlib/pins.json','.github/workflows/'+args.workflow,'competitions/floatlib/scripts/ci-prepare.sh','competitions/floatlib/scripts/ci-setup.sh','competitions/floatlib/scripts/ci-validate.sh','competitions/floatlib/scripts/run-gates.py']
        paths += ['scripts/github-ci.py','competitions/floatlib/candidates/f01-word-tensors/ci-diagnostics.py']
        candidates=[n for n in args.candidates.split(',') if n!='baseline']
        if 'f01-d7-public-suite' in candidates:
            plan_path='competitions/floatlib/candidates/f01-d7-public-suite/suite-plan.json'
            plan=json.loads((ROOT/plan_path).read_bytes());assert plan.get('dispatch_state','READY')=='READY'
            assert plan['seed']==int(args.seed),'Nested public plan seed differs before dispatch'
            paths += [plan_path,'competitions/floatlib/candidates/f01-d7-research/public-suite.py']
            if plan.get('r22_cost_diagnostic'):paths += ['competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z/development-cost-suite.py','competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z/development-cost-audit.py']
            candidates += [e['candidate'] for e in plan['candidates'] if e['candidate']!='baseline']
        for name in dict.fromkeys(candidates):
            paths.append('competitions/floatlib/candidates/'+name+'/Kernel.lean')
            manifest='competitions/floatlib/candidates/'+name+'/manifest.json'
            if (ROOT/manifest).is_file():
                paths.append(manifest)
                data=json.loads((ROOT/manifest).read_bytes())
                helper=data.get('helper_audit_module')
                if name.startswith('f01-r22-') and helper in ('development-cost-audit.py','development-cost2-audit.py','development-cost3-audit.py','development-flat-cost-audit.py','development-flat-cost2-audit.py','development-pair8-cost-audit.py','development-resident8-cost-audit.py','development-broadword-cost-audit.py','development-multistatic-cost-audit.py','development-farstatic-cost-audit.py','development-nativecold-cost-audit.py','development-indexed8-cost-audit.py','development-outline-isolation-audit.py','development-wordcarry-cost-audit.py','development-nat-prefix-audit.py','development-nat-bias-repair-audit.py','development-endpoint-cost-audit.py','development-nat-light-repair-audit.py'):
                    paths.append('competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z/'+helper)
                for component in data.get('components',[]):
                    component_path=component['path'];resolved=(ROOT/component_path).resolve()
                    assert resolved.is_relative_to(ROOT/'competitions/floatlib/candidates')
                    assert hashlib.sha256(resolved.read_bytes()).hexdigest()==component['sha256']
                    paths.append(component_path)
        for path in dict.fromkeys(paths):
            blob=subprocess.check_output(['git','show',sha+':'+path],cwd=ROOT);assert blob==(ROOT/path).read_bytes();checked[path]=hashlib.sha256(blob).hexdigest()
        listing=['run','list','--repo',REPO,'--branch',branch,'--workflow',args.workflow,'--limit','25','--json','databaseId,headSha,status,createdAt,url']
        seen={x['databaseId'] for x in json.loads(gh(listing,e))}
        inputs={'candidates':args.candidates,'seed':args.seed,'allow_private':'false'}
        if args.workflow=='deflate-baseline.yml':inputs['competition']='floatlib'
        body={'ref':branch,'inputs':inputs};request=receipt/'request.json';save(request,body)
        base={'checked_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'source_commit':sha,'branch':branch,'inputs':inputs,'frozen_file_sha256':checked,'repository_visibility':'public','repository_response_sha256':hashlib.sha256(raw.encode()).hexdigest(),'workflow':args.workflow}
        save(receipt/'dispatch.json',{**base,'state':'REQUEST_PREPARED'})
        gh(['api','--method','POST',f'repos/{REPO}/actions/workflows/{args.workflow}/dispatches','--input',str(request)],e)
        save(receipt/'dispatch.json',{**base,'state':'DISPATCH_SENT_NO_AUTOMATIC_RETRY'})
        for _ in range(12):
            rows=[x for x in json.loads(gh(listing,e)) if x['databaseId'] not in seen and x['headSha']==sha]
            if rows:
                assert len(rows)==1;save(receipt/'dispatch.json',{**base,'state':'RUN_IDENTIFIED','run':rows[0]});print(json.dumps({'receipt':str(receipt),'run':rows[0]}));return
            time.sleep(2)
        raise RuntimeError('Dispatch sent but run not identified; inspect before retry')
    assert args.run and args.run.isdecimal()
    raw=gh(['run','view',args.run,'--repo',REPO,'--json','databaseId,headSha,headBranch,event,status,conclusion,createdAt,updatedAt,url,jobs'],e);meta=json.loads(raw)
    print(json.dumps({'run':args.run,'status':meta['status'],'conclusion':meta['conclusion'],'url':meta['url'],'jobs':[{'name':j['name'],'status':j['status'],'conclusion':j['conclusion'],'active_steps':[s['name'] for s in j['steps'] if s['status']=='in_progress']} for j in meta['jobs']]}))
    if args.mode=='collect':
        assert meta['status']=='completed';target=evidence/args.run;target.mkdir(exist_ok=True);save(target/'ci-run.json',meta)
        artifacts=json.loads(gh(['api',f'repos/{REPO}/actions/runs/{args.run}/artifacts'],e));save(target/'artifacts.json',artifacts)
        artifact=next((a for a in artifacts['artifacts'] if a['name']==f'floatlib-{args.run}-receipts' and not a['expired']),None)
        if artifact:
            stage=target/('download-'+uuid.uuid4().hex);stage.mkdir()
            gh(['run','download',args.run,'--repo',REPO,'--name',artifact['name'],'--dir',str(stage)],e)
            hashes={p.relative_to(stage).as_posix():{'sha256':hashlib.sha256(p.read_bytes()).hexdigest(),'bytes':p.stat().st_size} for p in stage.rglob('*') if p.is_file()}
            save(target/'original-artifact-hashes.json',{'artifact':artifact,'directory':stage.name,'files':hashes})
            for s in stage.rglob('summary.json'):
                summary=json.loads(s.read_text());assert summary['source_commit']==meta['headSha'];print(json.dumps(summary,ensure_ascii=False)[:12000])
        (target/'ci.log').write_text(gh(['run','view',args.run,'--repo',REPO,'--log'],e),encoding='utf-8')

if __name__=='__main__':main()
