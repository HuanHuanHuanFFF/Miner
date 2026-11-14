"""Two documented public GETs; E-first archival, then byte-identical local notes."""
from pathlib import Path
from urllib.request import Request,urlopen
from urllib.error import HTTPError
from concurrent.futures import ThreadPoolExecutor
import hashlib,json,datetime
HERE=Path(__file__).resolve().parent
stamp=datetime.datetime.now(datetime.timezone.utc).strftime('%Y%m%dT%H%M%SZ')
E=Path('E:/Download/FloatLib/20261029-R24/protocol-comparison')/stamp
out=HERE/'public-reports'/stamp
E.mkdir(parents=True,exist_ok=False);out.mkdir(parents=True,exist_ok=False)
def get(sid):
 url=f'https://conjectures.io/v1/competitions/torchlean/submissions/{sid}/report'
 try:
  with urlopen(Request(url,headers={'Accept':'application/json'}),timeout=30) as response:
   raw=response.read(8*1024*1024+1);status=response.status
 except HTTPError as error:raw=error.read(8*1024*1024+1);status=error.code
 except OSError as error:return dict(submission=sid,url=url,status='FETCH_FAILED',error=str(error),latest='UNKNOWN')
 assert len(raw)<=8*1024*1024
 name=f'submission-{sid}-report.raw';(E/name).write_bytes(raw);(out/name).write_bytes((E/name).read_bytes())
 assert (out/name).read_bytes()==raw
 return dict(submission=sid,url=url,http_status=status,at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),bytes=len(raw),sha256=hashlib.sha256(raw).hexdigest(),e_path=str(E/name),copy_path=str(out/name),first_persisted_to_E=True)
with ThreadPoolExecutor(max_workers=2) as pool:rows=list(pool.map(get,[2,5]))
receipt=dict(retrieved_at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),requests=rows,scope='Public report evidence only; no new-track code/CI, no credentials, no raw third-party implementation copied',archives='NONE')
b=(json.dumps(receipt,ensure_ascii=False,indent=2)+'\n').encode();(E/'receipts.json').write_bytes(b);(out/'receipts.json').write_bytes(b)
print(json.dumps(receipt,ensure_ascii=False))
