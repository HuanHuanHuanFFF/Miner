"""Read-only bounded official state snapshot; preserves bytes, time and digest."""
from pathlib import Path
from urllib.request import Request,urlopen
from urllib.error import HTTPError
from concurrent.futures import ThreadPoolExecutor
import datetime,hashlib,json
HERE=Path(__file__).resolve().parent
BASE='https://conjectures.io/v1/competitions/'
REQUESTS={'floatlib':'floatlib','torchlean':'torchlean','leaderboard':'floatlib/leaderboard','status336':'floatlib/submissions/336','report336':'floatlib/submissions/336/report','torchlean-board':'torchlean/leaderboard'}
def main():
 stamp=datetime.datetime.now(datetime.timezone.utc).strftime('%Y%m%dT%H%M%SZ')
 out=HERE/('official-final-'+stamp);out.mkdir(exist_ok=False)
 def get(pair):
  name,path=pair;url=BASE+path
  try:
   try:
    with urlopen(Request(url,headers={'Accept':'application/json'}),timeout=25) as response:raw=response.read(8*1024*1024+1);status=response.status
   except HTTPError as error:raw=error.read(8*1024*1024+1);status=error.code
   assert len(raw)<=8*1024*1024
   (out/(name+'.raw')).write_bytes(raw)
   return name,{'url':url,'http_status':status,'checked_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'bytes':len(raw),'sha256':hashlib.sha256(raw).hexdigest(),'latest':'VERIFIED_RESPONSE' if status==200 else 'UNKNOWN'}
  except Exception as error:return name,{'url':url,'checked_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'latest':'UNKNOWN','error':str(error)}
 with ThreadPoolExecutor(max_workers=3) as pool:receipts=dict(pool.map(get,REQUESTS.items()))
 (out/'receipts.json').write_bytes((json.dumps(receipts,ensure_ascii=False,indent=2)+'\n').encode())
 result={'checked_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'source':'Officialread-onlyGET','submissions_open':'UNKNOWN','champion':'UNKNOWN','submission336':'UNKNOWN','torchlean_submissions_open':'UNKNOWN','scope':'Snapshotonly, no formal upload, wallet, signature, new candidate or benchmark.'}
 def load(name):return json.loads((out/(name+'.raw')).read_bytes()) if receipts[name].get('http_status')==200 else None
 for name,target in [('floatlib','submissions_open'),('torchlean','torchlean_submissions_open')]:
  obj=load(name)
  if obj is not None:result[target]=obj.get('submissions_open','UNKNOWN')
 board=load('leaderboard');status=load('status336')
 if board is not None:
  result['champion']=board.get('leader','UNKNOWN');result['champion_sha256']=board.get('champion_sha256','UNKNOWN')
 if status is not None:
  result['submission336']={k:status.get(k,'UNKNOWN') for k in ['id','state','stage','ratio','verification_current','digest','champion_sha256']}
  result['submission336']['rank']=next((x.get('rank','UNKNOWN') for x in board.get('ranking',[]) if x.get('submission')==336),'UNKNOWN') if board else 'UNKNOWN'
  result['submission336']['same_current_champion']=status.get('champion_sha256')==board.get('champion_sha256') if board else 'UNKNOWN'
 (out/'comparison.json').write_bytes((json.dumps(result,ensure_ascii=False,indent=2)+'\n').encode())
 print(json.dumps({'directory':str(out),'comparison':result},ensure_ascii=False))
if __name__=='__main__':main()
