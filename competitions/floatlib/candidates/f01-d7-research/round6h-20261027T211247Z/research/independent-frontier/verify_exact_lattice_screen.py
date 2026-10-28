"""Receipt verification; no rescan, new random sample or performance execution."""
from pathlib import Path
from datetime import datetime,timezone
import json,hashlib
D=Path(__file__).resolve().parent;R=next(p for p in D.parents if (p/'AGENTS.md').exists())
records=[]
for run in [40168687803,40169957447,40171180249]:
 receipt_path=D/f'exact-lattice-{run}.json';d=json.loads(receipt_path.read_bytes());u=json.loads((D/f'underflow-summary-{run}.json').read_bytes())
 assert d['source_script_sha256']==hashlib.sha256((D/'screen_exact_lattice.py').read_bytes()).hexdigest()
 assert d['helper_source_sha256']==hashlib.sha256((D/'same_exponent_add.py').read_bytes()).hexdigest()
 assert d['reads']==u['reads'] and len(d['cases'])==d['timed_BMM_cases']==34
 assert d['plan_sha256']==u['plan_sha256'] and d['verdict_sha256']==u['verdict_sha256']
 assert [r['name'] for r in d['cases']]==[r['name'] for r in u['cases']]
 for r,z in zip(d['cases'],u['cases']):
  assert r['A_trace_sha256']==z['A_trace_sha256'] and r['B_trace_sha256']==z['B_trace_sha256']
  c=r['counts'];batch,m,n,p=r['shape'];assert c['outputs']==batch*m*p
  assert 0<=c['max_bound_hits']<=c['L1_bound_hits']<=c['outputs']
  assert c['max_bound_hits']==c['max_hits_nonzero_products']+c['max_hits_zero_products']
  assert c['L1_bound_hits']==c['L1_hits_nonzero_products']+c['L1_hits_zero_products']
  assert c['L1_bound_hits']+c['nonfinite_reject']+c['quantum_reject']+c['coefficient_reject']==c['outputs']
  for w in r['nonzero_hit_examples']:
   assert -149<=w['qProduct']<=103 and w['qProduct']==w['qA']+w['qB']
   mx=n*w['maxA']*w['maxB'];l1=min(mx,w['L1A']*w['maxB'],w['maxA']*w['L1B']);assert l1<=1<<24
   assert (mx<=1<<24)==w['nmax_pass']
 for key,val in d['totals'].items():assert val==sum(r['counts'][key] for r in d['cases'])
 assert not d['new_whole_certificate_cases']
 assert d['new_nonzero_affected_entire_cell_share_ceiling']<0.1
 records.append({'run':run,'sha256':hashlib.sha256(receipt_path.read_bytes()).hexdigest(),'reads':d['reads'],'outputs':d['totals']['outputs'],'nonzero_nmax':d['totals']['max_hits_nonzero_products'],'nonzero_L1':d['totals']['L1_hits_nonzero_products'],'cell_ceiling':d['new_nonzero_affected_entire_cell_share_ceiling']})
w=D/'exact-lattice-witnesses.json';v=json.loads(w.read_bytes());assert v['witness_count']==6 and v['product_and_prefix_steps']==33
assert v['certificate_receipt_sha256']==records[2]['sha256']
assert all(r['final_raw']==r['integer_final_raw'] for r in v['witnesses'])
out={'verified_at_utc':datetime.now(timezone.utc).isoformat(),'state':'RECEIPT_CONSISTENCY_AND_FINITE_WITNESS_PASS','first_tool_utc':'2026-10-27T22:22:52Z','twenty_minute_deadline_utc':'2026-10-27T22:42:52Z','decision':'PARK_NO_TEN_PERCENT_RELEVANT_NONZERO_EXPOSURE_IN_THREE_OLD_PLANS','runs':records,'total_words':sum(r['reads'] for r in records),'total_outputs':sum(r['outputs'] for r in records),'witness_sha256':hashlib.sha256(w.read_bytes()).hexdigest(),'report_sha256':hashlib.sha256((D/'EXACT-LATTICE-DECISION.md').read_bytes()).hexdigest(),'scope':'Paper exactness condition plus complete source-model summaries and six finite word-oracle witnesses. No new Lean, original gate, timing, or candidate. Historical cells only.'}
(D/'exact-lattice-verification.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8',newline='\n');print(json.dumps(out))
