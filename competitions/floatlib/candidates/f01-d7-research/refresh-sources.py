"""Read public competition/upstream data only; retain response bytes and failures."""
from pathlib import Path
import datetime, hashlib, json, urllib.request, urllib.error

ROOT=Path(__file__).resolve().parent
stamp=datetime.datetime.now(datetime.timezone.utc).strftime('%Y%m%dT%H%M%SZ')
out=ROOT/('official-'+stamp);out.mkdir()
rows={}
def get(name,url):
    now=datetime.datetime.now(datetime.timezone.utc).isoformat()
    request=urllib.request.Request(url,headers={'User-Agent':'FloatLib-public-research/1.0'})
    try:
        with urllib.request.urlopen(request,timeout=30) as response:
            raw=response.read();status=response.status
    except urllib.error.HTTPError as error:
        raw=error.read();status=error.code
    except Exception as error:
        rows[name]={'url':url,'queried_at_utc':now,'error':str(error)}
        return None
    (out/(name+'.raw')).write_bytes(raw)
    rows[name]={'url':url,'queried_at_utc':now,'status':status,'bytes':len(raw),'sha256':hashlib.sha256(raw).hexdigest(),'file':name+'.raw'}
    if status!=200:return None
    return raw

base='https://conjectures.io/v1/competitions/floatlib'
competition=get('competition',base)
champions=get('champions',base+'/champions')
get('leaderboard',base+'/leaderboard')
champion=None
if champions:
    champion=next(r for r in json.loads(champions) if r['current'])['submission']
    get('champion-detail',base+'/submissions/'+str(champion))
    get('champion-source',base+'/submissions/'+str(champion)+'/source')
    get('champion-report',base+'/submissions/'+str(champion)+'/report')
repo='conjectures-io/conjectures-optimisation-float-kernels'
head=get('upstream-head','https://api.github.com/repos/'+repo+'/commits/main')
if head:
    commit=json.loads(head)['sha']
    for name,path in [('manual','MANUAL.md'),('benchmarking','docs/BENCHMARKING.md'),('shipped-kernel','kernels/full/incumbent/Kernel.lean'),('public-suite','suites/public-v2.json')]:
        get(name,'https://raw.githubusercontent.com/'+repo+'/'+commit+'/'+path)
(out/'receipts.json').write_text(json.dumps({'responses':rows},indent=2)+'\n','utf-8')
pointer={'directory':out.name,'queried_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'champion':champion,'official_commit':json.loads(head)['sha'] if head else 'UNKNOWN'}
(ROOT/'current-official-snapshot.json').write_text(json.dumps(pointer,indent=2)+'\n','utf-8')
print(json.dumps({'snapshot':pointer,'responses':{k:v.get('status',v.get('error')) for k,v in rows.items()}}))
