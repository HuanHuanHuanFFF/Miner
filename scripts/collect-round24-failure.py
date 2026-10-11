"""Preserve an ended R24 job's raw CLI log separately from immutable artifacts."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib,json
ROOT=Path(__file__).resolve().parents[1]
def main():
    ap=argparse.ArgumentParser();ap.add_argument('run_id');a=ap.parse_args();assert a.run_id.isdecimal()
    h=importlib.import_module('collect-round2');env=h.gh_env();repo='HuanHuanHuanFFF/Miner'
    meta=json.loads(h.run(['run','view',a.run_id,'--repo',repo,'--json','databaseId,headSha,headBranch,event,status,conclusion,createdAt,updatedAt,url,jobs'],env))
    assert meta['status']=='completed' and meta['headBranch']=='codex/round24-stable-dual'
    raw=h.run(['run','view',a.run_id,'--repo',repo,'--log'],env).encode()
    p=ROOT/f'evidence/round24/{a.run_id}/execution-log';p.mkdir(exist_ok=False)
    (p/'ci.log').write_bytes(raw);(p/'ci-run.json').write_bytes((json.dumps(meta,indent=2)+'\n').encode())
    receipt={'status':'VERIFIED_ENDED_JOB_LOG_CAPTURE','run_id':a.run_id,'retrieved_utc':datetime.now(timezone.utc).isoformat(),'conclusion':meta['conclusion'],'raw_cli_log_sha256':hashlib.sha256(raw).hexdigest(),'scope':'Log evidence only; inspect phase outputs separately. Existing artifact bytes remain unchanged.'}
    (p/'receipt.json').write_bytes((json.dumps(receipt,indent=2)+'\n').encode());print(json.dumps(receipt))
if __name__=='__main__':main()
