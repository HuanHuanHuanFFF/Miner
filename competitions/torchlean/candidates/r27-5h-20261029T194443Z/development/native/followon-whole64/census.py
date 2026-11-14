"""Pre-freeze whole64 scaling premise, finite oldseen formula data only."""
from pathlib import Path
from datetime import datetime,timezone
from collections import Counter
import importlib.util,json,time,hashlib,struct,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;BASE=HERE.parents[2];C=BASE/'research/board-frontier'
sp=importlib.util.spec_from_file_location('r27_whole64_old_formula',C/'norm_frontier.py')
f=importlib.util.module_from_spec(sp);sp.loader.exec_module(f)
def meta(ws):
 lo=0xffffffff;hi=0;bits=0
 for w in ws:
  v=w&0x7fffffff;lo=min(lo,(v-1)&0xffffffff);hi=max(hi,v);bits|=w
 low=max(0,(lo>>23)-1);high=max(0,(hi>>23)-1)
 t=min(23,(bits&-bits).bit_length()-1) if bits else 23
 return low,high,(high-low)&((1<<64)-1),hi>>23,t
began=time.perf_counter();original=f.linear;records=[];ctx={}
def observe(x,rows,n,out,w,b,relu):
 assert time.perf_counter()-began<20
 xx=[meta(x[i*n:(i+1)*n]) for i in range(rows)]
 ww=[meta(w[j*n:(j+1)*n]) for j in range(out)]
 counts=Counter(dots=rows*out,logical_MACs=rows*n*out);hist=Counter(q[4] for q in ww)
 oldP=n>=16 and all(q[3]!=255 for q in xx+ww) and min([99]+[q[2] for q in xx])+max([0]+[q[2] for q in ww])<=15
 c=(n-1).bit_length() if n else 0
 for i,(xl,xh,sx,_,_) in enumerate(xx):
  X=[f.fields(v) for v in x[i*n:(i+1)*n]]
  p_present=oldP and sx+max([0]+[q[2] for q in ww])<=15
  for j,(wl,wh,sw,_,t) in enumerate(ww):
   sb,mb,ib=f.fields(b[j]);body=xl+wl
   eligible=p_present and wl>=1 and xl<=xh and wl<=wh and ((b[j]>>23)&255)!=255 and (mb==0 or body<=126+ib and 126+ib-body<80)
   if not eligible:counts['original_guard_fallback_dots']+=1;continue
   counts['original_prepared_dots']+=1
   if 48+sx+sw+c<=63:counts['unscaled_word64_bound_dots']+=1
   if 48+sx+sw+c>63+t:counts['new_mass_guard_miss_dots']+=1;continue
   counts['scaled_word64_bound_dots']+=1;counts['scaled_logical_MACs']+=n
   W=[f.fields(v) for v in w[j*n:(j+1)*n]]
   terms=[];unscaled=[]
   for (sa,ma,ia),(sd,md,id_) in zip(X,W):
    aa=sa*(ma<<max(0,ia-xl))
    bb=sd*(md<<max(0,id_-wl))
    assert bb%(1<<t)==0
    terms.append(aa*(bb//(1<<t)));unscaled.append(aa*bb)
   assert sum(abs(v) for v in terms)<1<<63
   total=sum(terms);assert -(1<<63)<=total<(1<<63)
   assert (total<<t)==sum(unscaled)
   counts['scaled_checked_terms']+=n
 records.append(dict(**ctx,rows=rows,n=n,out=out,counts=dict(counts),weight_common_tz=dict(sorted(hist.items()))))
 return original(x,rows,n,out,w,b,relu)
f.linear=observe;seed=27051001;expected=json.loads((C/'norm-frontier-result.json').read_text())['cells'];cells=[]
for kind in ['normal','wide','sparse']:
 for rows in [1,8]:
  ctx.clear();ctx.update(kind=kind)
  n,h,h2=f.dimensions(seed,'typical');x=f.gen(kind,rows*n,seed+999)
  x=f.linear(x,rows,n,h,f.weights(kind,seed,1,n,h*n),f.bias(seed,2,h),True)
  x=f.norm(x,rows,h,f.scale(seed+3,h))
  x=f.linear(x,rows,h,h2,f.weights(kind,seed,4,h,h2*h),f.bias(seed,5,h2),True)
  x=f.norm(x,rows,h2,f.scale(seed+6,h2),f.bias(seed,7,h2))
  x=f.linear(x,rows,h2,10,f.weights(kind,seed,8,h2,10*h2),f.bias(seed,9,10),False)
  digest=hashlib.sha256(b''.join(struct.pack('<I',v) for v in x)).hexdigest()
  old=next(v for v in expected if v['seed']==seed and v['profile']=='typical' and v['kind']==kind and v['rows']==rows)
  assert digest==old['output_sha256']
  cc=Counter()
  for r in records:
   if r['kind']==kind and r['rows']==rows:cc.update(r['counts'])
  cells.append({'kind':kind,'rows':rows,'counts':dict(cc),'unchanged_formula_sha256':digest})
receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'wall_seconds':time.perf_counter()-began,'seed':seed,'cells':cells,'layers':records,
 'state':'FINITE_EXACT_COMMON_WEIGHT_SCALING_AND_WHOLE63_MASS_PREMISE_ONLY','source':'Source23metadata/rawbits relation, oldseen27051001fixture. No8or9newinput/output used',
 'scope':'Scaled integer carrier checked only; actual new native consumer/preparation/oracle fields/Lean all12 theorem are absent',
 'negative_control':'t cannot exceed23 based only on rawbits: hidden normal bit23 may then be removed. Every used weight divisibility asserted explicitly',
 'next':'Fuse one rawwordOR into weightmetadata and preserve4rowsharing before any complete native cost experiment; no extraCI request or proof inheritance',
 'performance':'UNKNOWN; words/counts are not cycles or success probability'}
(HERE/'whole64-scaling-census.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'wall_seconds':receipt['wall_seconds'],'cells':cells,'performance':'UNKNOWN'},indent=2))
