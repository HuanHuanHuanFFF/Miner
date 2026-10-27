"""Decide whether a distinct public low-normal decoder proof route has exposure."""
from pathlib import Path
from datetime import datetime,timezone
import json,hashlib,importlib.util,time
H=Path(__file__).resolve().parent;R=H.parents[3]
sp=importlib.util.spec_from_file_location('p',H/'public-nonfinite-opportunity.py');P=importlib.util.module_from_spec(sp);sp.loader.exec_module(P)
pp=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/39840672791/download-81e3479e9e2b47249bf76c8d44eb2e62/diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json';plan=json.loads(pp.read_text());rows=[];start=time.monotonic()
keys=['all_words','active_prefix_words','subnormal_full','low_normal_full','subnormal_prefix','low_normal_prefix','zero_full','zero_prefix']
for c in plan['cases']:
 if c['kernel']!='sum':continue
 n=c['length'];row={k:0 for k in keys};row.update(name=c['name'],timed=c['timed'],low_normal_exponents_prefix={str(e):0 for e in range(1,24)})
 for b in range(c['batch']):
  active=True
  for k in range(n):
   u=P.element(c,b*n+k,0,n);e=(u>>23)&255;f=u&0x7fffff;row['all_words']+=1;row['active_prefix_words']+=int(active)
   if e==0:
    kind='subnormal' if f else 'zero';row[kind+'_full']+=1;row[kind+'_prefix']+=int(active)
   elif 1<=e<24:
    row['low_normal_full']+=1;row['low_normal_prefix']+=int(active)
    if active:row['low_normal_exponents_prefix'][str(e)]+=1
   if e==255 and f:active=False
 rows.append(row)
totals={str(t):{k:sum(x[k] for x in rows if x['timed']==t) for k in keys} for t in [True,False]}
out={'completed_at_utc':datetime.now(timezone.utc).isoformat(),'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'plan_sha256':hashlib.sha256(pp.read_bytes()).hexdigest(),'analysis_seconds':time.monotonic()-start,'totals':totals,'cases':rows,'question':'Could exact two-normal-power scaling of UInt32 mantissa target low-normal exponent1..23 without subnormal multiplier operand? A new proof/decoder route only if exposure merits it. Actual FP costs/hardware output handling UNKNOWN. Subnormal range is a different route, not silently included.','scope':'Public exposed807 sourcegenerator counted inputs only; no runtime speed, probability, orprivate distribution claim. Nativeprefix truncates atfirstoriginalNaN, notfirstnativeinvalid.'}
(H/'sum-decoder-low-screen.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(totals,indent=2))
