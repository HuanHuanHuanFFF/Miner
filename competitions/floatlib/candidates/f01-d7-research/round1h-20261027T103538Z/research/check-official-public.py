"""Read public official resources only, stage raw receipts on E: then verify copy."""
from pathlib import Path
import datetime, hashlib, json, urllib.request, urllib.error
HERE=Path(__file__).resolve().parent
stamp=datetime.datetime.now(datetime.timezone.utc).strftime('%Y%m%dT%H%M%SZ')
stage=Path('E:/Download/FloatLib/20261027-R21/official')/stamp
dest=HERE/'official-public'/stamp
stage.mkdir(parents=True,exist_ok=False); dest.mkdir(parents=True,exist_ok=False)
base='https://conjectures.io/v1/competitions/floatlib'
paths={'champion-source.raw':base+'/submissions/323/source','b2-status.raw':base+'/submissions/336','b2-report.raw':base+'/submissions/336/report'}
rows=[]
for name,url in paths.items():
    row={'url':url,'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat()}
    try:
        with urllib.request.urlopen(url,timeout=10) as response:
            raw=response.read(1_000_001); code=response.status
    except urllib.error.HTTPError as error:
        code=error.code; raw=error.read(1_000_001)
    except Exception as error:
        row.update(status='UNKNOWN',error_type=type(error).__name__); rows.append(row); continue
    if len(raw)>1_000_000: raise ValueError('unexpected resource size')
    (stage/name).write_bytes(raw); (dest/name).write_bytes((stage/name).read_bytes())
    assert (stage/name).read_bytes()==(dest/name).read_bytes()
    row.update(status=code,bytes=len(raw),sha256=hashlib.sha256(raw).hexdigest(),file=name)
    rows.append(row)
out={'checked_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'stage':str(stage),'destination':str(dest),'rows':rows,'scope':'Fresh public read only. No new registration, submission, private runner or paid action. Web open failed, so direct official HTTPS read used.'}
(dest/'receipts.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(out,ensure_ascii=False))
