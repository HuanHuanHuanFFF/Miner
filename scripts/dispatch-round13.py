"""Dispatch authorized R13 experiments inside the user-provided seven-hour window."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,importlib.util,json,os,subprocess,time

ROOT=Path(__file__).resolve().parents[1];REPO='HuanHuanHuanFFF/Miner';ROUND=13

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('batch');ap.add_argument('--ref',default='codex/round13-chat-integration');ap.add_argument('--max-minutes',type=int,default=60);args=ap.parse_args()
    budget=json.loads((ROOT/f'evidence/round{ROUND}/budget.json').read_bytes());left=int((datetime.fromisoformat(budget['deadline_utc'])-datetime.now(timezone.utc)).total_seconds()//60)-8
    minutes=min(args.max_minutes,left,90);assert 10<=minutes<=90
    os.environ['ROUND4_SPEC_DIR']=f'evidence/round{ROUND}';from round4 import validate;spec=validate(args.batch);assert args.ref.startswith('codex/')
    s=importlib.util.spec_from_file_location('r13_gh',ROOT/'scripts/collect-round2.py');m=importlib.util.module_from_spec(s);s.loader.exec_module(m);env=m.gh_env()
    sha=subprocess.check_output(['git','rev-parse',args.ref],text=True).strip();repo=json.loads(m.run(['api',f'repos/{REPO}'],env));private=bool(repo['private']);remote=json.loads(m.run(['api',f'repos/{REPO}/commits/{args.ref}'],env))['sha'];assert remote==sha
    frozen=json.loads(subprocess.check_output(['git','show',sha+f':evidence/round{ROUND}/{args.batch}.json']));assert frozen==spec
    listing=['run','list','--repo',REPO,'--branch',args.ref,'--workflow','deflate-round9.yml','--limit','20','--json','databaseId,headSha,status,createdAt,url'];seen={r['databaseId']for r in json.loads(m.run(listing,env))}
    inputs={'experiment_round':str(ROUND),'specification':args.batch,'allow_private':str(private).lower(),'job_minutes':str(minutes)}
    cmd=['workflow','run','deflate-round9.yml','--repo',REPO,'--ref',args.ref]
    for key,value in inputs.items():cmd+=['-f',f'{key}={value}']
    m.run(cmd,env)
    for _ in range(10):
        matches=[r for r in json.loads(m.run(listing,env))if r['headSha']==sha and r['databaseId']not in seen]
        if matches:
            record={'round':ROUND,'batch':args.batch,'git_sha':sha,'inputs':inputs,'allow_private':private,'repository_visibility_verified':'private'if private else'public','authorization':'User requested absorb research ZIP and continue optimization7h; existing explicit experiment-branch push/cloud verification authorization persists. No artificial job-count cap is added.','job_timeout_minutes':minutes,'runtime_scope':'Job cap; queue separately observed. Reserve8minutes outside cap for collection.','run':matches[0]}
            p=ROOT/f'evidence/round{ROUND}/dispatch-{matches[0]["databaseId"]}.json';assert not p.exists();p.write_bytes((json.dumps(record,indent=2)+'\n').encode());print(json.dumps(record));return
        time.sleep(2)
    raise RuntimeError('Dispatch accepted; discovery pending. Inspect existing runs before any retry.')

if __name__=='__main__':main()
