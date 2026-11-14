"""Validate the completed source-summary receipts without rerunning full scans."""
from pathlib import Path
import json,hashlib,datetime
D=Path(__file__).resolve().parent
R=next(p for p in D.parents if (p/'AGENTS.md').exists())
script=D/'screen_underflow_summary.py';rows=[]
for run in [40168687803,40169957447,40171180249]:
 p=D/f'underflow-summary-{run}.json';d=json.loads(p.read_bytes());assert d['script_sha256']==hashlib.sha256(script.read_bytes()).hexdigest()
 base=R/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}';idx=json.loads((base/'original-artifact-hashes.json').read_bytes());q=base/idx['directory']/'diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json';plan=json.loads(q.read_bytes());assert d['plan_sha256']==hashlib.sha256(q.read_bytes()).hexdigest()
 expected=[c for c in plan['cases'] if c['timed'] and c['kernel']=='bmm'];assert [c['name'] for c in expected]==[c['name'] for c in d['cases']]
 assert d['reads']==sum(c['batch']*(c['m']*c['n']+c['n']*c['p']) for c in expected)
 delta={'symmetric51_rowcol':0,'effective102_rowcol':0,'raw102_rowcol':0}
 affected=set()
 for c,r in zip(expected,d['cases']):
  o=r['output_certificates'];assert o['all']==c['batch']*c['m']*c['p']
  assert 0<=o['old43_rowcol']<=o['symmetric51_rowcol']<=o['effective102_rowcol']<=o['raw102_rowcol']<=o['raw102_or_zero_rowcol']<=o['all']
  assert all(v<=o['all'] for v in o.values())
  if r['whole_certificates']['old43']:assert o['old43_rowcol']==o['all']
  for k in delta:delta[k]+=o[k]-o['old43_rowcol']
  if o['raw102_rowcol']>o['old43_rowcol']:affected.add(r['cell'])
 assert all(d['totals'][k]['new_whole_cases']==[] for k in ['symmetric51','effective102','raw102','raw102_or_finite_zero'])
 rows.append({'run':run,'receipt_sha256':hashlib.sha256(p.read_bytes()).hexdigest(),'timed_BMM_cases':len(expected),'reads':d['reads'],'expanded_domain_increment_outputs':delta,'increment_cells':sorted(affected),'scan_totals':d['scan_totals']})
w=D/'underflow-expansion-witnesses.json';dw=json.loads(w.read_bytes());assert dw['count']==7 and dw['pairs_checked']==14
assert all(p['integer_product']<p['half_min_subnormal_product_threshold'] for r in dw['witnesses'] for p in r['pairs'])
srcs=['same_exponent_add.py','screen_underflow_summary.py','underflow_expansion_witnesses.py']
upstream=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/BenchSuite.lean'
assert hashlib.sha256(upstream.read_bytes()).hexdigest()=='2f1672738e07851fdb24ed968c248fc2e6d8a3e677c27763ebd489ada9425a9f'
out={'verified_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'state':'RECEIPT_CONSISTENCY_PASS_SOURCE_MODEL_ONLY','runs':rows,'total_words':sum(r['reads'] for r in rows),'source_bindings':{n:hashlib.sha256((D/n).read_bytes()).hexdigest() for n in srcs},'generator_translation_sha256':hashlib.sha256((R/'competitions/floatlib/research/astra-collab-20261023-r7/public-nonfinite-opportunity.py').read_bytes()).hexdigest(),'official_generator_sha256':hashlib.sha256(upstream.read_bytes()).hexdigest(),'witness_receipt_sha256':hashlib.sha256(w.read_bytes()).hexdigest(),'metadata_correction':'Raw summary limits text says35 timed cases; actual selected/verified cases length is34 in each run (35 includes untimed check). Counts/arrays are complete for all34 timed BMM cases. Original result bytes retained.','no_new_Lean_or_candidate':True,'scope':'Receipt identities, count conservation, monotonicity and finite witness threshold checks; not independent Lean operand generation or performance.'}
(D/'underflow-screen-verification.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8',newline='\n');print(json.dumps({'state':out['state'],'total_words':out['total_words'],'runs':[{'run':r['run'],'cases':r['timed_BMM_cases'],'delta':r['expanded_domain_increment_outputs']} for r in rows]}))
