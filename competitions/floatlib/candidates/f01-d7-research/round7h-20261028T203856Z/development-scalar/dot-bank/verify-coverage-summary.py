"""Read-only fixed replay of the frozen bank coverage receipt."""
from pathlib import Path
from collections import Counter
import hashlib,importlib.util,json
P=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('model',P.parent/'portable-f64-dot-model.py');fp=importlib.util.module_from_spec(spec);spec.loader.exec_module(fp)
raw=(P/'fixtures.json').read_bytes();craw=(P/'coverage-summary.json').read_bytes();coverage=json.loads(craw);fixtures=json.loads(raw)
assert hashlib.sha256(raw).hexdigest()==coverage['fixture_sha256']=='986eaf0dd77ec19d6f64bed9a1f653da6004f28c3d4968fd31358c98e421d7f1'
assert hashlib.sha256((P.parent/'portable-f64-dot-model.py').read_bytes()).hexdigest()==coverage['model_sha256']
ref=fp.load_ref();words=0;outputs=0;accepts=0;miss=0;ua=set();ub=set()
for c,s in zip(fixtures['cases'],coverage['cases'],strict=True):
 assert c['name']==s['name']
 A=c['rowsA'];B=c['rowsB'];n=c['inner'];a=list(map(fp.prepare,A));b=list(map(fp.prepare,B));reasons=Counter();got=0;zeros=0;cancel=0;zero_product=0;wide=0
 for i,x in enumerate(A):
  for j,y in enumerate(B):
   q,obs=fp.attempt(a[i],b[j]);want,value=fp.exact_dot(x,y,ref);z=i*len(B)+j
   assert want==c['expected'][z] and q==c['fast_results_model'][z]
   assert (q!=0)==(z in s['model_fp']['accepted_flat_indices'])
   assert q==0 or q==want
   reasons[obs['reason']]+=1;got+=q!=0;zeros+=value==0
   scales=[fp.decode32(xx)[2]+fp.decode32(yy)[2]for xx,yy in zip(x,y)if xx&0x7fffffff and yy&0x7fffffff]
   cancel+=value==0 and bool(scales);zero_product+=not scales;wide+=bool(scales)and max(scales)-min(scales)>=64
 assert got==s['model_fp']['accepted'] and dict(reasons)==s['model_fp']['reasons']
 assert zeros==s['categories']['exact_zero'] and cancel==s['categories']['exact_nonzero_product_cancellation']
 assert zero_product==s['categories']['all_products_zero'] and wide==s['categories'].get('active_product_scale_span_ge64',0)
 assert s['cache_amortization_model']['primary_rows']==len(A)+len(B)
 assert s['cache_amortization_model']['lazy_exact_fallback_row_builds']==2*(len(A)*len(B)-got)
 ua.update(map(tuple,A));ub.update(map(tuple,B));words+=sum(map(len,A+B));outputs+=len(A)*len(B);accepts+=got;miss+=len(A)*len(B)-got
assert (outputs,accepts,miss,words,len(ua),len(ub),len(ua|ub))==(464,346,118,9216,30,63,90)
report={'status':'PASS_FROZEN_COVERAGE_REPLAY','fixture_sha256':hashlib.sha256(raw).hexdigest(),'coverage_sha256':hashlib.sha256(craw).hexdigest(),'plan_sha256':hashlib.sha256((P/'NEXT-CONFIRM.md').read_bytes()).hexdigest(),'cases':len(fixtures['cases']),'outputs':outputs,'model_accepted':accepts,'model_rejected':miss,'native_or_cost_rerun':False,'input_generation':False}
(P/'coverage-summary-verified.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps(report))
