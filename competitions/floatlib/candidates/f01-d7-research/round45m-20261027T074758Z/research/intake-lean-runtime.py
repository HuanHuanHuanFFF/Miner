"""Stage two fixed-version primary sources on E:, then byte-verify branch intake."""
from pathlib import Path
import datetime, hashlib, json, urllib.request

HERE = Path(__file__).resolve().parent
STAGE = Path('E:/Download/FloatLib/20261027-R20/lean-runtime-293d5d0c')
DEST = HERE / 'source-intake/lean-runtime-293d5d0c'
COMMIT = '293d5d0c0c3f3dded4688b3ccd6a33939ac5102b'
FILES = {'lean.h':'src/include/lean/lean.h','LICENSE':'LICENSE'}
STAGE.mkdir(parents=True, exist_ok=True)
DEST.mkdir(parents=True, exist_ok=True)
rows=[]
for name, relative in FILES.items():
    url=f'https://raw.githubusercontent.com/leanprover/lean4/{COMMIT}/{relative}'
    raw=urllib.request.urlopen(url, timeout=25).read()
    if len(raw)>500_000: raise ValueError('unexpectedly large primary source')
    stage=STAGE/name
    if stage.exists() and stage.read_bytes()!=raw: raise ValueError(f'existing stage differs: {stage}')
    stage.write_bytes(raw)
    target=DEST/name
    if target.exists() and target.read_bytes()!=raw: raise ValueError(f'existing destination differs: {target}')
    target.write_bytes(stage.read_bytes())
    if stage.read_bytes()!=target.read_bytes(): raise ValueError('byte copy differs')
    rows.append({'file':name,'url':url,'stage':str(stage),'destination':str(target),'bytes':len(raw),'sha256':hashlib.sha256(raw).hexdigest(),'verified_equal':True})
receipt={'retrieved_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'fixed_commit':COMMIT,'purpose':'Verify actual UInt32/Float32 boxing and output lifecycle prerequisites; do not modify toolchain or candidate runtime.','files':rows,'archive_downloaded':False,'archive_deleted':False}
(DEST/'intake.json').write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(receipt,ensure_ascii=False))
