"""Finite word-path comparison for existing guarded rrsG reused at the RMS terminal."""
from __future__ import annotations
from collections import Counter
from datetime import datetime,timezone
from pathlib import Path
import hashlib,json,random
import norm_frontier as nf
from norm_path_check import finish_normal

def probe(w,g,d):
 sw,mw,iw=nf.fields(w);sg,mg,ig=nf.fields(g);sd,md,idd=nf.fields(d)
 if sd*md<=0:return None,'denominator_fallback'
 N=mw*mg;D=md
 if N==0:
  assert nf.round_ratio(sw*sg*N,D,iw+ig-idd-149)==0
  return 0,'native_exact_zero'
 if D>N:return None,'small_or_zero_product_fallback'
 result=finish_normal(sw!=sg,N,D,iw+ig,idd+22)
 if result is None:return None,'normal_range_fallback'
 exact=nf.round_ratio(sw*sg*N,D,iw+ig-idd-149)
 assert result==exact,(w,g,d,result,exact)
 return result,'native_output'

def main():
 start=datetime.now(timezone.utc).isoformat();counts=Counter();rng=random.Random(20261029)
 special=[0,0x80000000,1,0x80000001,0x007fffff,0x807fffff,0x00800000,0x80800000,0x3f800000,0xbf800000,0x7f7fffff,0xff7fffff]
 for w in special:
  for g in special:
   for d in special:counts[probe(w,g,d)[1]]+=1
 for _ in range(30000):
  words=[]
  for j in range(3):
   bits=rng.randrange(1<<32)
   if (bits>>23)&255==255:bits^=1<<23
   words.append(bits)
  counts[probe(*words)[1]]+=1
 cells=[]
 for seed in [27051001,27151004,27251007]:
  for profile in ['typical','scale','boundary']:
   i,h,h2=nf.dimensions(seed,profile)
   for kind in ['normal','wide','sparse']:
    for rows in [1,8]:
     x=nf.gen(kind,rows*i,seed+999)
     x=nf.linear(x,rows,i,h,nf.weights(kind,seed,1,i,h*i),nf.bias(seed,2,h),True)
     g=nf.scale(seed+3,h);c=Counter()
     for r in range(rows):
      a=x[r*h:(r+1)*h];Q=sum(nf.key(w)**2 for w in a)
      d=nf.sqrt_ratio(Q+h*nf.key(nf.EPS)*(1<<149),h<<298)
      for j,w in enumerate(a):c[probe(w,g[j],d)[1]]+=1
     cells.append({'seed':seed,'profile':profile,'kind':kind,'rows':rows,'shape':[i,h,h2,10],'counts':dict(c)})
 total=sum((Counter(c['counts'])for c in cells),Counter())
 out={'at_utc':datetime.now(timezone.utc).isoformat(),'start_utc':start,'status':'FINITE_WORD_MODEL_NO_LEAN_NO_NATIVE_TIME','script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'adversarial_counts':dict(counts),'benchmark_census_cells':len(cells),'benchmark_census':dict(total),'cells':cells,'proof_interface':'Reuse original rrsGe under D>0,D<=N,D<2^40,U,V<2^20,E+127=U-V; all final out-of-range cases call original Ya7','limits':['Finite sampled words only','Not formal correctness','Not native speed','Formula inputs are pre-freeze exploration samples only']}
 Path(__file__).with_name('rms-native-finish-check.json').write_text(json.dumps(out,indent=2),encoding='utf8');print(json.dumps({k:v for k,v in out.items()if k!='cells'}))
if __name__=='__main__':main()
