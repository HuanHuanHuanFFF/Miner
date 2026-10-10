"""Read-only monitor for the single authorized frozen A submission #603."""
from pathlib import Path
from datetime import datetime, timezone
import argparse, hashlib, json, time
import requests

ROOT=Path(__file__).resolve().parents[1]
URL='https://conjectures.io/v1/competitions/deflate/submissions/603'
DIGEST='38c4ccfd8dc9979cb05ea09b64f93dd09ba5f528d260c787b47b3edec8cfca53'
SOURCE='16390a77d6b500f96b37441027512b89ba2d62b5091435e0527d9aa07b9834ef'

def main():
 p=argparse.ArgumentParser(description=__doc__)
 p.add_argument('--max-seconds',type=int,default=3600)
 p.add_argument('--interval',type=int,default=45)
 a=p.parse_args();assert a.max_seconds>=0 and a.interval>=30
 dest=ROOT/'evidence/round18/formal-a';dest.mkdir(exist_ok=True)
 started=time.monotonic();terminal=False
 with requests.Session() as session:
  while True:
   stamp=datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S%fZ')
   response=session.get(URL,timeout=40);raw=response.content
   name=f'status-{stamp}.response.json'
   (dest/name).write_bytes(raw)
   receipt={'url':URL,'read_at_utc':datetime.now(timezone.utc).isoformat(),'http_status':response.status_code,'date_header':response.headers.get('Date'),'bytes':len(raw),'sha256':hashlib.sha256(raw).hexdigest(),'raw_file':name}
   (dest/f'status-{stamp}.receipt.json').write_bytes((json.dumps(receipt,indent=2)+'\n').encode())
   if response.status_code==429:
    delay=max(a.interval,int(response.headers.get('Retry-After','60')))
    print(json.dumps({'state':'RATE_LIMITED_READ_ONLY','retry_after_seconds':delay}),flush=True)
   else:
    response.raise_for_status();body=response.json();s=body['submission']
    assert s['id']=='603' and body['digest']==DIGEST and body['source_sha256']==SOURCE
    gate=s['gate_status'];admission=s.get('admission') or {};score=s.get('score') or {}
    terminal=gate in ('rejected','failed','error') or (gate in ('passed','accepted') and admission.get('admitted') is not None and bool(s.get('score')))
    summary={'checked_at_utc':receipt['read_at_utc'],'submission_id':'603','candidate':'r18-rf-sf-content-proof1','gate_status':gate,'admission':admission,'metrics':s.get('metrics'),'score':s.get('score'),'pipeline':body.get('pipeline'),'snapshot':body.get('context'),'bundle_digest':DIGEST,'source_sha256':SOURCE,'proof_sha256':'0a0171ac0dda3f6c06e574145e6b89b6b90fed45bd2d1d22be0ad199d18bacc7','raw_receipt':f'status-{stamp}.receipt.json','terminal_result_observed':terminal,'chain_transaction_sent':False}
    (dest/'latest-status.json').write_bytes((json.dumps(summary,indent=2)+'\n').encode())
    print(json.dumps({'checked_at_utc':summary['checked_at_utc'],'gate':gate,'admission':admission.get('status'),'outcome':admission.get('outcome'),'snapshot':body.get('context',{}).get('snapshot_id'),'metrics':s.get('metrics'),'score':s.get('score'),'terminal':terminal}),flush=True)
    delay=a.interval
   if terminal or time.monotonic()-started>=a.max_seconds:break
   time.sleep(delay)
 if not terminal:print('Observation window ended; server job not cancelled or assumed terminal.',flush=True)

if __name__=='__main__':main()
