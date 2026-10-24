"""Read three small pinned public sources and keep original bytes and license."""
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
from urllib.request import Request,urlopen
from datetime import datetime,timezone
import hashlib,json
OUT=Path(__file__).resolve().parent;SHA='497c81c1f5016dc6ef5b3219ece2f3c261d4d8f1'
dest=OUT/'development-sources/softfloat';dest.mkdir(parents=True,exist_ok=False)
def fetch(path):
    url=f'https://raw.githubusercontent.com/ucb-bar/berkeley-softfloat-3/{SHA}/{path}'
    with urlopen(Request(url,headers={'User-Agent':'FloatLib-source-research'}),timeout=18) as response:
        assert response.status==200;raw=response.read(1000001)
    assert len(raw)<=1000000;target=dest/(path.rsplit('/',1)[-1]+'.raw');target.write_bytes(raw)
    return {'url':url,'file':target.relative_to(OUT).as_posix(),'bytes':len(raw),'sha256':hashlib.sha256(raw).hexdigest()}
with ThreadPoolExecutor(max_workers=3) as pool:rows=list(pool.map(fetch,['source/f32_mul.c','source/s_roundPackToF32.c','COPYING.txt']))
record={'queried_at_utc':datetime.now(timezone.utc).isoformat(),'repository':'ucb-bar/berkeley-softfloat-3','commit':SHA,'author':'John R. Hauser / The Regents of the University of California','license':'SoftFloat Release3e three-condition BSD-style license, complete COPYING.txt retained','files':rows,'scope':'Legal public implementation/source investigation only. No local compilation, Lean, source import or benchmark. No runtime/performance claim.'}
(OUT/'development-softfloat-source-receipt.json').write_bytes((json.dumps(record,ensure_ascii=False,indent=2)+'\n').encode());print(json.dumps(record))
