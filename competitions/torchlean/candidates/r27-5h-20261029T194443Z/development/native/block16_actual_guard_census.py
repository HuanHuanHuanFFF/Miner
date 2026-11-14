"""Finite pre-freeze guard census for the frozen block16 runtime, no tuning."""
from pathlib import Path
from datetime import datetime,timezone
from collections import Counter
import hashlib,importlib.util,json,struct,sys,time
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;BASE=HERE.parents[1];C=BASE/'research/board-frontier'
sp=importlib.util.spec_from_file_location('r27_block16_guard_formula',C/'norm_frontier.py')
f=importlib.util.module_from_spec(sp);sp.loader.exec_module(f)
def metadata(ws):
 lo=0xffffffff;hi=0
 for w in ws:
  v=w&0x7fffffff;lo=min(lo,(v-1)&0xffffffff);hi=max(hi,v)
 low=max(0,(lo>>23)-1);high=max(0,(hi>>23)-1)
 return low,high,(high-low)&((1<<64)-1),hi>>23
original=f.linear;records=[];context={};start=time.perf_counter()
def observe(x,rows,k,out,w,b,relu):
 assert time.perf_counter()-start<20
 xx=[metadata(x[i*k:(i+1)*k]) for i in range(rows)]
 ww=[metadata(w[j*k:(j+1)*k]) for j in range(out)]
 nz=[sum(f.fields(v)[1]!=0 for v in x[i*k:(i+1)*k]) for i in range(rows)]
 qp_global=k>=16 and all(q[3]!=255 for q in xx+ww) and min([99]+[q[2] for q in xx])+max([0]+[q[2] for q in ww])<=15
 counts=Counter(dots=rows*out,logical_MACs=rows*k*out)
 for i in range(rows):
  p_present=qp_global and xx[i][2]+max([0]+[q[2] for q in ww])<=15
  width=nz[i] if p_present and 0<nz[i] and 4*nz[i]<=3*k else k
  for j in range(out):
   _,mb,ib=f.fields(b[j]);body=xx[i][0]+ww[j][0]
   finite_bias=((b[j]>>23)&255)!=255
   eligible=p_present and xx[i][2]+ww[j][2]<=11 and xx[i][0]<=xx[i][1] and ww[j][0]<=ww[j][1] and ww[j][0]>=1 and finite_bias and (mb==0 or body<=126+ib and 126+ib-body<80)
   if eligible:
    counts['allrows_eligible_dots']+=1;counts['allrows_eligible_logical_MACs']+=k
    counts['allrows_full16_merges']+=width//16
    counts['allrows_grouped_terms']+=width//16*16
    counts['allrows_remainder_terms']+=width%16
    if rows==1:
     counts['frozen_b1_eligible_dots']+=1;counts['frozen_b1_grouped_terms']+=width//16*16
   elif not p_present:counts['P_absent_dots']+=1
   else:counts['P_present_guard_miss_dots']+=1
 records.append(dict(**context,rows=rows,k=k,out=out,counts=dict(counts)))
 return original(x,rows,k,out,w,b,relu)
f.linear=observe;seed=27051001;cells=[]
expected=json.loads((C/'norm-frontier-result.json').read_text())['cells']
for kind in ['normal','wide','sparse']:
 for rows in [1,8]:
  context.clear();context.update(kind=kind)
  i,h,h2=f.dimensions(seed,'typical');x=f.gen(kind,rows*i,seed+999)
  x=f.linear(x,rows,i,h,f.weights(kind,seed,1,i,h*i),f.bias(seed,2,h),True)
  x=f.norm(x,rows,h,f.scale(seed+3,h))
  x=f.linear(x,rows,h,h2,f.weights(kind,seed,4,h,h2*h),f.bias(seed,5,h2),True)
  x=f.norm(x,rows,h2,f.scale(seed+6,h2),f.bias(seed,7,h2))
  x=f.linear(x,rows,h2,10,f.weights(kind,seed,8,h2,10*h2),f.bias(seed,9,10),False)
  digest=hashlib.sha256(b''.join(struct.pack('<I',v) for v in x)).hexdigest()
  old=next(v for v in expected if v['seed']==seed and v['profile']=='typical' and v['kind']==kind and v['rows']==rows)
  assert digest==old['output_sha256']
  cc=Counter()
  for rr in records:
   if rr['kind']==kind and rr['rows']==rows:cc.update(rr['counts'])
  cells.append({'kind':kind,'rows':rows,'counts':dict(cc),'sha256':digest})
receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'wall_seconds':time.perf_counter()-start,'seed':seed,
 'state':'FINITE_OLDSEEN_ACTUAL_YC_QPS_P_I_BIAS_GUARD_COUNTS_NO_SOURCE_CHANGE',
 'candidate':'14ab9f4f frozenb1, parent659c694a intendedallrows branch','cells':cells,'layers':records,
 'scope':'Preparation/eligibility logical counts only. Baselineformula outputs match6oldseen fixturehashes. No candidate native performance, all12 proof or probability claim',
 'freeze_barrier':'Only pre-freeze27051001 data. No batch9 inputs/outputs read/generated; no candidate change or hyperparameter choice follows this census'}
(HERE/'block16-actual-guard-census.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'wall_seconds':receipt['wall_seconds'],'cells':cells},indent=2))
