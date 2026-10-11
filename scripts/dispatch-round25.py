"""Dispatch one frozen R25 batch within the currently authorized fixed deadline."""
from pathlib import Path
from datetime import datetime, timezone
import argparse, hashlib, importlib.util, json, os, subprocess, time

ROOT=Path(__file__).resolve().parents[1]
REPO='HuanHuanHuanFFF/Miner'

def verify_committed_inputs(spec, sha):
    """Require the local frozen inputs to exist with exact bytes in that Git tree."""
    checked={}
    def check(path, expected=None):
        local=(ROOT/path).resolve()
        assert local.is_relative_to(ROOT.resolve()) and local.is_file(), f'Missing local input: {path}'
        blob=subprocess.run(['git','show',sha+':'+Path(path).as_posix()],cwd=ROOT,capture_output=True)
        assert blob.returncode==0, f'Required input absent from dispatched commit: {path}'
        digest=hashlib.sha256(blob.stdout).hexdigest()
        assert digest==hashlib.sha256(local.read_bytes()).hexdigest(), f'Local/commit input mismatch: {path}'
        assert expected is None or digest==expected, f'Frozen hash/commit mismatch: {path}'
        checked[Path(path).as_posix()]=digest
    if spec['r25_mode']=='gate':
        for name,digest in spec['files'].items():check(str(Path(spec['path'])/name),digest)
    else:
        for entry in spec['entries']:
            for name,digest in entry['hashes'].items():check(str(Path(entry['path'])/name),digest)
        check(spec['snapshot_pages'])
        if spec.get('r25_dispatch_after_gate_pair_known'):
            for entry in spec['entries']:
                if entry.get('control'):continue
                certpath=str(Path(entry['path'])/'VERIFICATION.json')
                check(certpath)
                cert=json.loads((ROOT/certpath).read_bytes())
                check(cert['receipt'])
    for path,digest in spec.get('r25_required_files',{}).items():
        check(path,digest)
    return checked


def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('batch');ap.add_argument('--ref',default='codex/round25-fast-quality')
    ap.add_argument('--max-minutes',type=int,default=45)
    args=ap.parse_args()
    budget=json.loads((ROOT/'evidence/round25/budget.json').read_bytes())
    left=int((datetime.fromisoformat(budget['deadline_utc'])-datetime.now(timezone.utc)).total_seconds()//60)-10
    minutes=min(args.max_minutes,left,75);assert 10<=minutes<=75
    os.environ['ROUND4_SPEC_DIR']='evidence/round25'
    import importlib
    from round4 import validate
    mode='gate' if args.batch.startswith('gate-') else 'extract' if args.batch.endswith('-extract') else 'native' if args.batch.endswith('-native') else 'diagnostic' if args.batch.endswith('-diagnostic') else 'standard'
    spec=importlib.import_module('verify-round25-exact').validate(args.batch) if mode=='gate' else validate(args.batch)
    assert not spec.get('preflight_only'), 'Preflight fixtures cannot be dispatched as research results'
    assert spec['r25_mode']==mode and bool(spec.get('native_only'))==(mode=='native')
    if mode not in ('gate', 'extract') and spec.get('r18_role') != 'independent_confirmation':
        assert datetime.now(timezone.utc) < datetime.fromisoformat(budget['latest_new_research_dispatch_utc']), 'Final confirmation/collection reserve has begun; do not launch a new research batch'
    if spec.get('r25_dispatch_after_gate_pair_known'):
        for entry in spec['entries']:
            if entry.get('control'):continue
            cert=json.loads((ROOT/entry['path']/'VERIFICATION.json').read_bytes())
            assert cert.get('status')=='VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED' and cert['files']==entry['hashes'], 'Final-pair confirmation requires the exact accepted Rust/Lean pair'
    os.environ.update(ROUND4_SPEC=args.batch,ROUND25_MODE=mode)
    importlib.import_module('round25-preflight').main()
    assert args.ref=='codex/round25-fast-quality'
    helper_spec=importlib.util.spec_from_file_location('r25_gh',ROOT/'scripts/collect-round2.py')
    helper=importlib.util.module_from_spec(helper_spec);helper_spec.loader.exec_module(helper)
    env=helper.gh_env()
    repo=json.loads(helper.run(['api',f'repos/{REPO}'],env));assert repo['private'] is False
    sha=subprocess.check_output(['git','rev-parse',args.ref],text=True).strip()
    assert subprocess.run(['git','merge-base','--is-ancestor',budget['baseline_main_sha'],sha],capture_output=True).returncode==0
    remote=json.loads(helper.run(['api',f'repos/{REPO}/commits/{args.ref}'],env))['sha'];assert remote==sha
    frozen=json.loads(subprocess.check_output(['git','show',sha+f':evidence/round25/{args.batch}.json']));assert frozen==spec
    committed_inputs=verify_committed_inputs(spec,sha)
    listing=['run','list','--repo',REPO,'--branch',args.ref,'--workflow','deflate-round9.yml','--limit','25','--json','databaseId,headSha,status,createdAt,url']
    seen={r['databaseId'] for r in json.loads(helper.run(listing,env))}
    inputs={'experiment_round':'25','specification':args.batch,'allow_private':'false','job_minutes':str(minutes)}
    cmd=['workflow','run','deflate-round9.yml','--repo',REPO,'--ref',args.ref]
    for key,value in inputs.items():cmd+=['-f',f'{key}={value}']
    started=datetime.now(timezone.utc).isoformat();helper.run(cmd,env)
    for _ in range(10):
        matches=[r for r in json.loads(helper.run(listing,env)) if r['headSha']==sha and r['databaseId'] not in seen]
        if matches:
            assert len(matches)==1
            record={'round':25,'batch':args.batch,'mode':mode,'git_sha':sha,'inputs':inputs,'committed_input_sha256':committed_inputs,'dispatch_utc':started,'repository_visibility_verified':'public','authorization':'Current user research budget including explicit extensions, necessary cloud verification and experiment-branch push scope; no submission, registration or wallet actions.','job_timeout_minutes':minutes,'collection_reserve_minutes':10,'fixed_deadline_utc':budget['deadline_utc'],'run':matches[0]}
            p=ROOT/f'evidence/round25/dispatch-{matches[0]["databaseId"]}.json';assert not p.exists();p.write_text(json.dumps(record,indent=2)+'\n')
            print(json.dumps({k:v for k,v in record.items() if k!='committed_input_sha256'} | {'committed_input_count':len(committed_inputs)}));return
        time.sleep(2)
    raise RuntimeError('Dispatch accepted; discovery pending. Inspect existing runs before any retry.')

if __name__=='__main__':
    main()
