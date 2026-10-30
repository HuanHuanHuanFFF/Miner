"""Faithful finite replay of the new two-pass/Yc-metadata consumer, not Lean."""
from pathlib import Path
from collections import Counter
from datetime import datetime,timezone
import hashlib,importlib.util,json,struct,sys,time
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;BASE=HERE.parents[2]
C=BASE/'research/board-frontier';B=BASE/'research/word-proof'
def load(path,name):
 s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
f=load(C/'norm_frontier.py','r27_band_source_formula')
raw=(B/'band_full_model_census_v3.py').read_bytes()
assert hashlib.sha256(raw).hexdigest()=='079147825ee2820b80099e1893b03e9ad92d12f91eb329850235d484e515cb15'
b=load(B/'band_full_model_census_v3.py','r27_band_word_primitives')
MASK=(1<<64)-1
def metadata(ws):
 lo=(1<<32)-1;hi=0
 for w in ws:
  v=w&0x7fffffff;lo=min(lo,(v-1)&0xffffffff);hi=max(hi,v)
 low=max(0,(lo>>23)-1);high=max(0,(hi>>23)-1)
 return low,high,(high-low)&MASK,hi>>23
def factor(w,base):
 s,m,e=f.fields(w);delta=(e-base)&MASK
 mag=(m<<(delta%64))&0xffffffff
 return (s*mag)&0xffffffff
def rowprep(ws,base):
 counts=[0]*16;valid=True
 for w in ws:
  _,m,e=f.fields(w)
  if m:
   band=((e-base)&MASK)//4
   if band<16:counts[band]+=1
   else:valid=False
 starts=[];total=0
 for n in counts:starts.append(total);total+=n
 cur=list(starts);aa=[0]*total;ids=[0]*total
 for i,w in enumerate(ws):
  _,m,e=f.fields(w)
  if m:
   band=((e-base)&MASK)//4
   if band<16:
    dst=cur[band];aa[dst]=factor(w,base+4*band);ids[dst]=i;cur[band]+=1
 assert sorted(ids)==[i for i,w in enumerate(ws) if f.fields(w)[1]]
 return valid,aa,ids,starts,counts
def signed32(x):return x if x<(1<<31) else x-(1<<32)
began=time.perf_counter();original=f.linear;records=[];ctx={}
def observe(x,rows,k,out,w,bias,relu):
 assert time.perf_counter()-began<20,'20second finite discriminator limit'
 baseline=original(x,rows,k,out,w,bias,relu);result=list(baseline);stats=Counter(dots=rows*out)
 xx=[metadata(x[r*k:(r+1)*k]) for r in range(rows)]
 ww=[metadata(w[j*k:(j+1)*k]) for j in range(out)]
 eligible=rows>=4 and k>=16 and k<=1<<20 and all(q[2]<=52 and q[3]!=255 for q in xx) and all(q[2]<=6 and q[3]!=255 and q[0]>=1 for q in ww)
 if not eligible:stats['whole_call_fallback']=1
 else:
  rr=[rowprep(x[r*k:(r+1)*k],xx[r][0]) for r in range(rows)]
  weights=[[factor(w[j*k+i],ww[j][0]) for i in range(k)] for j in range(out)]
  stats['input_partition_words']=rows*k*2;stats['prepared_weight_words']=k*out
  for r,(valid,aa,ids,starts,counts) in enumerate(rr):
   for j,wf in enumerate(weights):
    sb,mb,ib=f.fields(bias[j]);body=xx[r][0]+ww[j][0]
    base=min(body,ib+126) if mb else body;high=max(xx[r][1]+ww[j][1],ib+126) if mb else xx[r][1]+ww[j][1]
    if not valid or ((bias[j]>>23)&255)==255 or high<base or high-base>58:
     stats['dot_fallback']+=1;continue
    lo=hi=0
    for band in range(16):
     gl=gh=0;start=starts[band];n=counts[band]
     for offset in range(0,n,64):
      terms=[signed32(aa[t])*signed32(wf[ids[t]]) for t in range(start+offset,start+min(n,offset+64))]
      assert sum(abs(v) for v in terms)<1<<63
      q=sum(terms)&MASK;gl,gh=b.merge64(gl,gh,q);stats['block_merges']+=1
     sl,sh=b.shift128(gl,gh,body-base+4*band)
     lo,hi=b.add128(lo,hi,sl,sh)
    total=b.signed128(lo,hi)+sb*(mb<<max(0,ib+149-base))
    raw_total=sum(f.key(x[r*k+i])*f.key(w[j*k+i]) for i in range(k))+(f.key(bias[j])<<149)
    assert (total<<base)==raw_total
    assert -(1<<127)<=total<1<<127
    if total==0:stats['exact_zero_fallback']+=1
    else:
     stats['native_word_dots']+=1
     result[r*out+j]=0 if relu and total<0 else f.round_ratio(total,1,base-298)
     assert result[r*out+j]==baseline[r*out+j]
 assert result==baseline
 records.append(dict(**ctx,rows=rows,k=k,out=out,stats=dict(stats)))
 return result
f.linear=observe;seed=27051001;cells=[]
expected=json.loads((C/'norm-frontier-result.json').read_text())['cells']
for kind in ['normal','wide','sparse']:
 for rows in [1,8]:
  ctx.clear();ctx.update(kind=kind)
  i,h,h2=f.dimensions(seed,'typical');x=f.gen(kind,rows*i,seed+999)
  x=f.linear(x,rows,i,h,f.weights(kind,seed,1,i,h*i),f.bias(seed,2,h),True)
  x=f.norm(x,rows,h,f.scale(seed+3,h))
  x=f.linear(x,rows,h,h2,f.weights(kind,seed,4,h,h2*h),f.bias(seed,5,h2),True)
  x=f.norm(x,rows,h2,f.scale(seed+6,h2),f.bias(seed,7,h2))
  x=f.linear(x,rows,h2,10,f.weights(kind,seed,8,h2,10*h2),f.bias(seed,9,10),False)
  digest=hashlib.sha256(b''.join(struct.pack('<I',v) for v in x)).hexdigest()
  old=next(v for v in expected if v['seed']==seed and v['profile']=='typical' and v['kind']==kind and v['rows']==rows)
  assert digest==old['output_sha256'];cells.append({'kind':kind,'rows':rows,'sha256':digest})
out={'at_utc':datetime.now(timezone.utc).isoformat(),'wall_seconds':time.perf_counter()-began,'state':'FINITE_ACTUAL_YC_METADATA_TWO_PASS_PREP_WORDCARRY_SHIFT_AND_TERMINAL_MODEL_ONLY',
 'seed':seed,'cells':cells,'layers':records,'mismatches':0,'scope':'Six alreadyseen model cells, no Lean/native/full12 or current champion measurement',
 'source_sha256':hashlib.sha256((HERE/'BandRuntime.lean.inc').read_bytes()).hexdigest(),
 'boundaries':['Rows1 wholecall fallback retained','Both input counting passes and percall weight factors accounted','Model exactzero uses baseline callback','Preparation and native timing remain unmeasured','Oldseen material cannot become unseen confirmation']}
(HERE/'band-source-model.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'wall_seconds':out['wall_seconds'],'cells':len(cells),'layers':records,'mismatches':0},indent=2))
