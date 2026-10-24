"""Derive measured operation shares; hypothetical savings are not measurements."""
from datetime import datetime,timezone
import hashlib,json,statistics
from pathlib import Path
HERE=Path(__file__).resolve().parent
source='6c2d394dd34e8854d0d44d5d6605c194ecb27c152a1768d236481fc03fa4277d'
path=HERE/'public-index-at-adoption.json';raw=path.read_bytes()
model=json.loads((HERE.parent/'champion-time-estimate.json').read_bytes())
assert hashlib.sha256(raw).hexdigest()==model['current_public_results_sha256']
rows=[r for r in json.loads(raw)['records'] if r.get('full_gate') and r['kernel_sha256']==source]
assert len(rows)==6 and len({r['run'] for r in rows})==6
ops=('add','mul','sum','bmm')
for r in rows:
 assert abs(sum(r['time_share_percent'].values())-100)<1e-9
 actual={o:sum(v['submission_ns']*r['cell_work'][k] for k,v in r['classes'].items() if k.startswith(o+':')) for o in ops}
 for o in ops:assert abs(actual[o]/sum(actual.values())*100-r['time_share_percent'][o])<1e-9
summary={'recorded_at_utc':datetime.now(timezone.utc).isoformat(),'source_sha256':source,
         'input_snapshot_sha256':hashlib.sha256(raw).hexdigest(),
         'scope':'Six actual complete public-suite same-source entry costs weighted by original cell_work; not official scoring weights, private-suite shares, stage costs, or recoverable cost.',
         'groups':[{'run':r['run'],'seed':r['seed'],'role':r.get('sample_role'),'observer':r.get('execution_has_observer'),'time_share_percent':r['time_share_percent']} for r in rows],
         'median_time_share_percent':{o:statistics.median(r['time_share_percent'][o] for r in rows) for o in ops},
         'combined_add_mul_median_percent':statistics.median(r['time_share_percent']['add']+r['time_share_percent']['mul'] for r in rows),
         'hypothetical_whole_savings_percent':{
             'bmm_cost_halved':statistics.median(r['time_share_percent']['bmm']*.5 for r in rows),
             'add_and_mul_cost_reduced20percent':statistics.median((r['time_share_percent']['add']+r['time_share_percent']['mul'])*.2 for r in rows)},
         'opportunity_boundary':'Hypothetical fractional reductions remain unimplemented. Actual achievable reductions and engineering/proof/verification costs are UNKNOWN; capture MainFull scalar hot paths before expanding variants.'}
with (HERE/'current-cost-shares.json').open('x',encoding='utf-8',newline='\n') as out:out.write(json.dumps(summary,ensure_ascii=False,indent=2)+'\n')
print(json.dumps({k:summary[k] for k in ('median_time_share_percent','combined_add_mul_median_percent','hypothetical_whole_savings_percent')}))
