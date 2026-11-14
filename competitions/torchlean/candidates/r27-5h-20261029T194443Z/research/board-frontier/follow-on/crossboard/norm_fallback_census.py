"""Pre-freeze formula census of public23 native statistics/sqrt fallback reachability."""
from pathlib import Path
from datetime import datetime,timezone
from collections import Counter
from math import isqrt
import json,hashlib,sys
HERE=Path(__file__).resolve().parent;OWN=HERE.parents[1];sys.path.insert(0,str(OWN))
import norm_frontier as nf

def native_sqrt(S,m,c):
 lg=max(0,S.bit_length()-1);t=(47-lg+(m.bit_length()-1)+1)//2
 if t>=0 or -t>=64:return None,'FW_shift_guard'
 k=-t;A=S>>(2*k);q,r=divmod(A,m)
 if q>=1<<62:return None,'FX_quotient_guard'
 b2=(S>>(2*k-2))&3;z=(S&((1<<(2*k-2))-1))==0;root=isqrt(q)
 if q==root*root and r==0 and b2==0 and z:sa=0
 elif q<root*root+root or(q==root*root+root and 4*r+b2<m):sa=1
 elif q==root*root+root and 4*r+b2==m and z:sa=2
 else:sa=3
 sh=int(root>=1<<24);e=(c-298)//2-t;x=e+sh+150
 if not(1<<23<=root<1<<25 and 1<=x<=253):return None,'sqV_range_guard'
 rounded=nf.quotient_even(4*root+sa,8 if sh else 4)
 result=((x+1)<<23)if rounded==1<<24 else(x<<23)|(rounded-(1<<23))
 return result,'native_sqrt'

def stats(words,layer):
 n=len(words);fs=list(map(nf.fields,words));b0=min((i for s,m,i in fs if m),default=255)
 if any(m and i-b0>36 for s,m,i in fs)or n>=256:return None,'rsV_span_or_count_guard'
 S=sum(s*(m<<max(0,i-b0))for s,m,i in fs);Q=sum((m<<max(0,i-b0))**2 for s,m,i in fs)
 assert Q<1<<128
 if layer:
  if abs(S)>=1<<64 or n*Q>=1<<128:return None,'FT_centering_guard'
  T=n*Q-S*S;m=n*n
 else:T=Q;m=n
 _,me,ie=nf.fields(nf.EPS);c=min(2*b0,ie+149)//2*2;d1=2*b0-c;d2=ie+149-c;E=m*me
 if T.bit_length()+d1>=128 or E.bit_length()+d2>=128:return None,'FN_alignment_guard'
 merged=(T<<d1)+(E<<d2);assert merged<1<<128
 result,state=native_sqrt(merged,m,c)
 return result,state

def main():
 cells=[];counts={'rms':Counter(),'layer':Counter()}
 for seed in [27051001,27151004,27251007]:
  for profile in ['typical','scale','boundary']:
   i,h,h2=nf.dimensions(seed,profile)
   for kind in ['normal','wide','sparse']:
    for rows in [1,8]:
     x=nf.gen(kind,rows*i,seed+999);x=nf.linear(x,rows,i,h,nf.weights(kind,seed,1,i,h*i),nf.bias(seed,2,h),True)
     rc=Counter();lc=Counter()
     for r in range(rows):
      words=x[r*h:(r+1)*h];Q=sum(nf.key(w)**2 for w in words);exact=nf.sqrt_ratio(Q+h*nf.key(nf.EPS)*(1<<149),h<<298);got,state=stats(words,False);rc[state]+=1
      if got is not None:assert got==exact,(words,got,exact)
     x=nf.norm(x,rows,h,nf.scale(seed+3,h));x=nf.linear(x,rows,h,h2,nf.weights(kind,seed,4,h,h2*h),nf.bias(seed,5,h2),True)
     for r in range(rows):
      words=x[r*h2:(r+1)*h2];ks=list(map(nf.key,words));Q=sum(k*k for k in ks);S=sum(ks);exact=nf.sqrt_ratio(h2*Q-S*S+h2*h2*nf.key(nf.EPS)*(1<<149),h2*h2<<298);got,state=stats(words,True);lc[state]+=1
      if got is not None:assert got==exact,(words,got,exact)
     counts['rms'].update(rc);counts['layer'].update(lc);cells.append({'seed':seed,'profile':profile,'kind':kind,'rows':rows,'shape':[i,h,h2,10],'rms':dict(rc),'layer':dict(lc)})
 out={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'FINITE_FORMULA_CENSUS_NO_LEAN_OR_NATIVE_TIME','source23_sha256':'1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe','script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'counts':{k:dict(v)for k,v in counts.items()},'cells':cells,'scope':'Same previouslyseen explorationformula seeds; doesnotread frozenconfirmation inputs/results','next_question':'Ifrare fallback onactualwholemodel data, canreplace customgenericfallback with pinnedofficialspec tofreeproof/source bytes forcrossboardgraft? Must measuretailcost andproveactualcaller; censusalone cannotselect.'};(HERE/'norm-fallback-census.json').write_text(json.dumps(out,indent=2),encoding='utf8');print(json.dumps({k:v for k,v in out.items()if k!='cells'}))
if __name__=='__main__':main()
