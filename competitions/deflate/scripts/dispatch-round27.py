"""Dispatch a byte-frozen R27 batch before the fixed deadline, public runners only."""
from pathlib import Path
from datetime import datetime, timezone
import argparse, hashlib, importlib, importlib.util, json, os, subprocess, time
ROOT=Path(__file__).resolve().parents[1]
REPO='HuanHuanHuanFFF/Miner'
def main():
    ap=argparse.ArgumentParser();ap.add_argument('batch');ap.add_argument('--max-minutes',type=int,default=20);args=ap.parse_args()
    ref='codex/round27-public-frontier'
    budget=json.loads((ROOT/'evidence/round27/budget.json').read_bytes())
    mode='gate' if args.batch.startswith('gate-') else 'extract' if args.batch.endswith('-extract') else 'standard'
    os.environ.update(ROUND4_SPEC_DIR='evidence/round27',ROUND4_SPEC=args.batch,ROUND27_MODE=mode)
    importlib.import_module('round27-preflight').main()
    spec=importlib.import_module('verify-round27-exact').validate(args.batch) if mode=='gate' else importlib.import_module('round4').validate(args.batch)
    now=datetime.now(timezone.utc);deadline=datetime.fromisoformat(budget['deadline_utc'])
    assert now>=datetime.fromisoformat(budget['start_utc'])
    cutoff='latest_confirmation_dispatch_utc' if mode=='gate' or spec.get('r18_role')=='independent_confirmation' else 'latest_new_research_dispatch_utc'
    assert now<datetime.fromisoformat(budget[cutoff])
    assert 10<=args.max_minutes<=30 and (deadline-now).total_seconds()>=60*(args.max_minutes+10)
    assert subprocess.check_output(['git','branch','--show-current'],text=True).strip()==ref
    sha=subprocess.check_output(['git','rev-parse','HEAD'],text=True).strip()
    helper_spec=importlib.util.spec_from_file_location('r27_gh',ROOT/'scripts/collect-round2.py');helper=importlib.util.module_from_spec(helper_spec);helper_spec.loader.exec_module(helper);env=helper.gh_env()
    repo=json.loads(helper.run(['api',f'repos/{REPO}'],env));assert repo['private'] is False
    assert json.loads(helper.run(['api',f'repos/{REPO}/commits/{ref}'],env))['sha']==sha
    paths={'evidence/round27/budget.json','evidence/round27/'+args.batch+'.json'}
    entries=[{'path':spec['path'],'hashes':spec['files']}] if mode=='gate' else spec['entries']
    for entry in entries:
        for name,h in entry['hashes'].items():
            path=entry['path']+'/'+name;paths.add(path)
            assert hashlib.sha256((ROOT/path).read_bytes()).hexdigest()==h
    if spec.get('snapshot_pages'):paths.add(spec['snapshot_pages'])
    if spec.get('r27_dispatch_after_gate_pair_known'):
        assert spec.get('r18_role')=='independent_confirmation'
        for entry in spec['entries']:
            if entry.get('control'):continue
            cert_path=entry['path']+'/VERIFICATION.json'
            cert=json.loads((ROOT/cert_path).read_bytes())
            assert cert['status']=='VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED' and cert['files']==entry['hashes']
            paths.update([cert_path,cert['receipt']])
    checked={}
    for path in paths:
        blob=subprocess.check_output(['git','show',sha+':'+path]);assert blob==(ROOT/path).read_bytes();checked[path]=hashlib.sha256(blob).hexdigest()
    listing=['run','list','--repo',REPO,'--branch',ref,'--workflow','deflate-round9.yml','--limit','30','--json','databaseId,headSha,status,createdAt,url']
    seen={r['databaseId'] for r in json.loads(helper.run(listing,env))}
    inputs={'experiment_round':'27','specification':args.batch,'allow_private':'false','job_minutes':str(args.max_minutes)}
    cmd=['workflow','run','deflate-round9.yml','--repo',REPO,'--ref',ref]
    for k,v in inputs.items():cmd+=['-f',k+'='+v]
    start=datetime.now(timezone.utc).isoformat();helper.run(cmd,env)
    for _ in range(12):
        runs=[r for r in json.loads(helper.run(listing,env)) if r['databaseId'] not in seen and r['headSha']==sha]
        if runs:
            assert len(runs)==1
            record={'round':27,'batch':args.batch,'mode':mode,'git_sha':sha,'inputs':inputs,'committed_input_sha256':checked,'dispatch_utc':start,'job_timeout_minutes':args.max_minutes,'fixed_deadline_utc':budget['deadline_utc'],'budget_sha256':hashlib.sha256((ROOT/'evidence/round27/budget.json').read_bytes()).hexdigest(),'repository_visibility_verified':'public','run':runs[0]}
            p=ROOT/f'evidence/round27/dispatch-{runs[0]["databaseId"]}.json';assert not p.exists();p.write_bytes((json.dumps(record,indent=2)+'\n').encode())
            print(json.dumps({k:v for k,v in record.items() if k!='committed_input_sha256'}));return
        time.sleep(2)
    raise RuntimeError('Dispatch sent; inspect existing runs before any retry')
if __name__=='__main__':main()
