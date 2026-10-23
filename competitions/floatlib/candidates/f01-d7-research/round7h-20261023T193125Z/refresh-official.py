"""Read-only official snapshot; never silently recalibrate frozen champion estimates."""
from concurrent.futures import ThreadPoolExecutor
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
from urllib.error import HTTPError, URLError
from urllib.request import Request, urlopen

D7=Path(__file__).resolve().parent.parent
stamp=datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%SZ')
out=D7/f'official-{stamp}';out.mkdir(exist_ok=False)
records={}

def fetch(item):
    name,url=item
    at=datetime.now(timezone.utc).isoformat()
    try:
        with urlopen(Request(url,headers={'User-Agent':'FloatLib-research-readonly'}),timeout=18) as response:
            status=response.status;payload=response.read()
        error=None
    except HTTPError as exc:
        status=exc.code;payload=exc.read();error=None
    except (URLError,TimeoutError,OSError) as exc:
        status=None;payload=str(exc).encode();error=type(exc).__name__
    file=name+('.raw' if status is not None else '.error.txt')
    (out/file).write_bytes(payload)
    record={'url':url,'queried_at_utc':at,'status':status,'bytes':len(payload),'sha256':hashlib.sha256(payload).hexdigest(),'file':file}
    if error:record['error']=error
    return name,record

def batch(items):
    with ThreadPoolExecutor(max_workers=4) as pool:
        for name,record in pool.map(fetch,items):records[name]=record

base='https://conjectures.io/v1/competitions/floatlib'
batch([('competition',base),('champions',base+'/champions'),('leaderboard',base+'/leaderboard'),
       ('upstream-head','https://api.github.com/repos/conjectures-io/conjectures-optimisation-float-kernels/commits/main')])
leader=None;commit=None
if records['leaderboard']['status']==200:
    leader=json.loads((out/records['leaderboard']['file']).read_bytes())['leader']
if records['upstream-head']['status']==200:
    commit=json.loads((out/records['upstream-head']['file']).read_bytes())['sha']
items=[]
if leader is not None:
    items += [(name,base+f'/submissions/{leader}'+suffix) for name,suffix in [('champion-detail',''),('champion-source','/source'),('champion-report','/report')]]
if commit:
    source=f'https://raw.githubusercontent.com/conjectures-io/conjectures-optimisation-float-kernels/{commit}/'
    items += [(name,source+path) for name,path in [('manual','MANUAL.md'),('benchmarking','docs/BENCHMARKING.md'),('shipped-kernel','kernels/full/incumbent/Kernel.lean'),('public-suite','suites/public-v2.json')]]
batch(items)
at=datetime.now(timezone.utc).isoformat()
complete=all(records[k]['status']==200 for k in ['competition','champions','leaderboard','upstream-head']) and all(records.get(k,{}).get('status')==200 for k in ['champion-detail','champion-report','manual','benchmarking','shipped-kernel','public-suite'])
result={'queried_at_utc':at,'champion':leader,'official_commit':commit,'responses':records,
        'status':'VERIFIED_SNAPSHOT' if complete else 'UNKNOWN_INCOMPLETE_REFRESH',
        'compatible_frozen_protocol':bool(commit=='4b7e83841cc0c32c6529f533923c73d33b5ecf97' and records.get('public-suite',{}).get('sha256')=='a16494e97c6a073bfd8accf72480c34534c87808092c56074fdcfa42cd34868a'),
        'scope':'Raw official reads only. Existing current snapshot pointer, champion anchor, estimates and dashboard are not changed by this collector.'}
(out/'receipts.json').write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'directory':out.name,'status':result['status'],'champion':leader,'official_commit':commit,'compatible_frozen_protocol':result['compatible_frozen_protocol'],'source_status':records.get('champion-source',{}).get('status')},ensure_ascii=False))
