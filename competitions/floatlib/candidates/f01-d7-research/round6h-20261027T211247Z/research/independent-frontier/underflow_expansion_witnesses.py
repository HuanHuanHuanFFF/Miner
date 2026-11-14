"""Locate the seven new summary certificates; check exact product-vs-half-minsub."""
import importlib.util,json,hashlib,time
from pathlib import Path
from datetime import datetime,timezone
D=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('gen',D/'same_exponent_add.py');M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)
base=M.R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40171180249';idx=json.loads((base/'original-artifact-hashes.json').read_bytes());plan,ph=M.load_checked(base,idx,'diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json');c=next(c for c in plan['cases'] if c['name']=='bmm:dense:1')
m,n,p=(c[k] for k in ['m','n','p']);st=time.monotonic();witnesses=[]
for b in range(c['batch']):
 A=[[M.E['element'](c,(b*m+r)*n+k,0,n) for k in range(n)] for r in range(m)]
 B=[[M.E['element'](c,b*n*p+k*p+j,1,p) for k in range(n)] for j in range(p)]
 for r,a in enumerate(A):
  for j,bb in enumerate(B):
   ea=max((w>>23)&255 for w in a);eb=max((w>>23)&255 for w in bb)
   if ea<=43 and eb<=43:continue
   if max(ea,1)+max(eb,1)>102:continue
   pairs=[]
   for u,v in zip(a,bb):
    eu,ev=(u>>23)&255,(v>>23)&255;mu=(u&0x7fffff)|(0x800000 if eu else 0);mv=(v&0x7fffff)|(0x800000 if ev else 0);scale=max(eu-1,0)+max(ev-1,0);prod=mu*mv
    assert scale<=100 and prod<1<<48
    threshold=1<<(148-scale)
    assert prod<threshold
    pairs.append({'u':f'{u:08x}','v':f'{v:08x}','raw_exp_sum':eu+ev,'finiteScale_sum':scale,'integer_product':prod,'half_min_subnormal_product_threshold':threshold,'strictly_below_half':True,'signed_product_zero':f'{(u^v)&0x80000000:08x}'})
   witnesses.append({'batch':b,'row':r,'column':j,'A_max_raw_exp':ea,'B_max_raw_exp':eb,'symmetric51':ea<=51 and eb<=51,'pairs':pairs,'original_order_dot_bits':'00000000','dot_basis':'Every independently rounded product is signed zero; exact +0 seed plus either signed zero returns +0, stepwise.'})
assert len(witnesses)==7
out={'at_utc':datetime.now(timezone.utc).isoformat(),'plan_sha256':ph,'run':40171180249,'case':c['name'],'shape':[c['batch'],m,n,p],'witnesses':witnesses,'count':len(witnesses),'pairs_checked':sum(len(x['pairs']) for x in witnesses),'elapsed_seconds':time.monotonic()-st,'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'scope':'Finite exact-integer threshold checks on new summary witnesses only; not full Lean, machine execution or timing. No random correctness enumeration.'}
(D/'underflow-expansion-witnesses.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8',newline='\n');print(json.dumps({'count':out['count'],'pairs_checked':out['pairs_checked'],'elapsed_seconds':out['elapsed_seconds']}))
