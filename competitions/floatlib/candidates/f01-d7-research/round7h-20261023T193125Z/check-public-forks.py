"""Read public repository metadata only. Never execute or adopt external code."""
from concurrent.futures import ThreadPoolExecutor
from datetime import datetime,timezone
import hashlib,json
from pathlib import Path
from urllib.request import Request,urlopen
from urllib.error import HTTPError,URLError

HERE=Path(__file__).resolve().parent
out=HERE/('public-source-search-'+datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%SZ'))
out.mkdir(exist_ok=False)
urls={'official-forks':'https://api.github.com/repos/conjectures-io/conjectures-optimisation-float-kernels/forks?per_page=100&sort=newest',
      'repository-network-search':'https://api.github.com/search/repositories?q=conjectures-optimisation-float-kernels+fork:true&per_page=100'}
def fetch(item):
 name,url=item;at=datetime.now(timezone.utc).isoformat()
 try:
  with urlopen(Request(url,headers={'User-Agent':'FloatLib-readonly-source-research'}),timeout=18) as r:status=r.status;raw=r.read()
 except HTTPError as e:status=e.code;raw=e.read()
 except (URLError,TimeoutError,OSError) as e:status=None;raw=str(e).encode()
 (out/(name+'.raw')).write_bytes(raw)
 return name,{'url':url,'queried_at_utc':at,'status':status,'bytes':len(raw),'sha256':hashlib.sha256(raw).hexdigest(),'file':name+'.raw'}
with ThreadPoolExecutor(max_workers=2) as pool:responses=dict(pool.map(fetch,urls.items()))
repositories={}
for name,rec in responses.items():
 if rec['status']!=200:continue
 data=json.loads((out/rec['file']).read_bytes())
 for row in (data if isinstance(data,list) else data['items']):
  repositories[row['full_name']]={k:row.get(k) for k in ('full_name','html_url','fork','default_branch','pushed_at','size','description','license')}
receipt={'recorded_at_utc':datetime.now(timezone.utc).isoformat(),'responses':responses,
         'repositories':list(repositories.values()),
         'source_available_or_stronger':'UNKNOWN_UNTIL_ACTUAL_SOURCE_LICENSE_PROOF_AND_COMPLETE_COST_REVIEW',
         'scope':'Public metadata discovery only; page1 at most100 items, no exhaustive-global-source claim, no code executed or inherited performance.'}
(out/'receipts.json').write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'directory':out.name,'responses':{k:v['status'] for k,v in responses.items()},'repositories':list(repositories)}))
