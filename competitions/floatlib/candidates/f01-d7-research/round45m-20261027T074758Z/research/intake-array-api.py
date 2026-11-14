"""Preserve the fixed safe Array API source, staged on E: before branch intake."""
from pathlib import Path
import datetime, hashlib, json, urllib.request
HERE=Path(__file__).resolve().parent
commit='293d5d0c0c3f3dded4688b3ccd6a33939ac5102b'
url=f'https://raw.githubusercontent.com/leanprover/lean4/{commit}/src/Init/Data/Array/Basic.lean'
raw=urllib.request.urlopen(url,timeout=25).read()
assert len(raw)<500_000 and b'def modify' in raw
stage=Path('E:/Download/FloatLib/20261027-R20/lean-runtime-293d5d0c/Array.Basic.lean')
dest=HERE/'source-intake/lean-runtime-293d5d0c/Array.Basic.lean'
for p in (stage,dest):
    if p.exists() and p.read_bytes()!=raw: raise ValueError(f'existing source differs: {p}')
stage.write_bytes(raw); dest.write_bytes(stage.read_bytes())
assert stage.read_bytes()==dest.read_bytes()
out={'retrieved_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'url':url,'fixed_commit':commit,'stage':str(stage),'destination':str(dest),'bytes':len(raw),'sha256':hashlib.sha256(raw).hexdigest(),'equal':True,'license_file':'LICENSE','candidate_unsafe_added':False,'purpose':'Read the implementation behind public safe Array.modify; actual constructor reuse and native costs remain UNKNOWN.'}
(dest.parent/'array-api-intake.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(out,ensure_ascii=False))
