"""Dispatch two explicitly requested DNA retests and unconditional Lean validation."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,importlib.util,json,os,subprocess,time

ROOT=Path(__file__).resolve().parents[1];REPO='HuanHuanHuanFFF/Miner';ROUND=17

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('batch');ap.add_argument('--ref',default='codex/round17-dna-confirm');ap.add_argument('--max-minutes',type=int,default=60);args=ap.parse_args()
    assert args.batch in ('retest-a','retest-b')
    cap=60 if args.batch=='retest-a' else 40
    minutes=min(args.max_minutes,cap);assert 10<=minutes<=cap
    prior=[json.loads(p.read_bytes()) for p in (ROOT/'evidence/round17').glob('dispatch-*.json')]
    assert not any(p['batch']==args.batch for p in prior),'Already dispatched; inspect existing run rather than duplicate'
    os.environ['ROUND4_SPEC_DIR']=f'evidence/round{ROUND}';from round4 import validate;spec=validate(args.batch);assert args.ref.startswith('codex/')
    native_route=args.batch in ('ef32-d','price-f') or args.batch.endswith('-native')
    assert bool(spec.get('native_only'))==native_route,'Native/full workflow route must match the frozen specification'
    s=importlib.util.spec_from_file_location('r17_gh',ROOT/'scripts/collect-round2.py');m=importlib.util.module_from_spec(s);s.loader.exec_module(m);env=m.gh_env()
    sha=subprocess.check_output(['git','rev-parse',args.ref],text=True).strip();repo=json.loads(m.run(['api',f'repos/{REPO}'],env));private=bool(repo['private']);assert not private,'R17 renewed public-runner scope does not automatically authorize additional private Actions billing';remote=json.loads(m.run(['api',f'repos/{REPO}/commits/{args.ref}'],env))['sha'];assert remote==sha
    frozen=json.loads(subprocess.check_output(['git','show',sha+f':evidence/round{ROUND}/{args.batch}.json']));assert frozen==spec
    listing=['run','list','--repo',REPO,'--branch',args.ref,'--workflow','deflate-round9.yml','--limit','20','--json','databaseId,headSha,status,createdAt,url'];seen={r['databaseId']for r in json.loads(m.run(listing,env))}
    inputs={'experiment_round':str(ROUND),'specification':args.batch,'allow_private':str(private).lower(),'job_minutes':str(minutes)}
    cmd=['workflow','run','deflate-round9.yml','--repo',REPO,'--ref',args.ref]
    for key,value in inputs.items():cmd+=['-f',f'{key}={value}']
    m.run(cmd,env)
    for _ in range(10):
        matches=[r for r in json.loads(m.run(listing,env))if r['headSha']==sha and r['databaseId']not in seen]
        if matches:
            record={'round':ROUND,'batch':args.batch,'git_sha':sha,'inputs':inputs,'allow_private':private,'repository_visibility_verified':'private'if private else'public','authorization':'User explicitly requests two additional independent performance tests and full Lean verification for r14-514-dna-nofold. Public runner and experiment-branch push authorized; no competition upload or wallet operation.','job_timeout_minutes':minutes,'runtime_scope':'Job cap enforced; queue separately observed. This followup is not the closed R16 timed research window.','run':matches[0]}
            p=ROOT/f'evidence/round{ROUND}/dispatch-{matches[0]["databaseId"]}.json';assert not p.exists();p.write_bytes((json.dumps(record,indent=2)+'\n').encode());print(json.dumps(record));return
        time.sleep(2)
    raise RuntimeError('Dispatch accepted; discovery pending. Inspect existing runs before any retry.')

if __name__=='__main__':main()
