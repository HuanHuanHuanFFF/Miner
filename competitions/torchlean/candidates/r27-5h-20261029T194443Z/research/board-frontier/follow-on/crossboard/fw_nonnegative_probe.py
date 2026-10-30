"""Isolated finite probe of exact scaledsqrt for the public23 FW nonnegative-scale gap."""
from pathlib import Path
from datetime import datetime,timezone
from math import isqrt
from collections import Counter
import json,hashlib,random
import norm_fallback_census as nc
nf=nc.nf

def nonnegative(S,m,c):
 assert S>0 and 0<m<1<<32 and 0<=c<=510 and c%2==0
 lS=S.bit_length()-1;lm=m.bit_length()-1;t=(48-lS+lm)//2
 if t<0:return None,'negative_t_original_path',None
 A=S<<(2*t)
 assert 0<=t<=39 and A<1<<80
 if m<1<<16:assert A<1<<64
 q,r=divmod(A,m);assert 1<<46<=q<1<<49
 root=isqrt(q);assert 1<<23<=root<1<<25
 if q==root*root and r==0:sa=0
 elif q<root*root+root or(q==root*root+root and 4*r<m):sa=1
 elif q==root*root+root and 4*r==m:sa=2
 else:sa=3
 sh=int(root>=1<<24);e=(c-298)//2-t;x=e+sh+150
 info={'t':t,'A_bits':A.bit_length(),'q_bits':q.bit_length(),'root':root,'remainder':r,'roundcase':sa,'x':x}
 if not 1<=x<=253:return None,'final_range_fallback',info
 rr=nf.quotient_even(4*root+sa,8 if sh else 4)
 got=((x+1)<<23)if rr==1<<24 else(x<<23)|(rr-(1<<23))
 exact=nf.sqrt_ratio(S<<c,m<<298);assert got==exact,(S,m,c,got,exact,info)
 return got,'native_nonnegative',info

def main():
 rng=random.Random(2710292300);count=Counter();maxbits=0;normalsmall=0
 for _ in range(20000):
  m=rng.randrange(1,1<<(16 if _%2 else 32));lm=m.bit_length()-1;lS=rng.randrange(0,49+lm);S=(1<<lS)|rng.randrange(1<<lS);c=2*rng.randrange(256)
  got,state,info=nonnegative(S,m,c);count[state]+=1
  if info:maxbits=max(maxbits,info['A_bits'])
  if m<1<<16 and got is not None:normalsmall+=1
 # Reconstruct the previouslyseen actualLN row that public23 rejects at t=0.
 fixture=json.loads((nc.HERE/'fallback-first-falsifier.json').read_text());row=fixture['misses'][0];words=[int(x,16)for x in row['words']];n=len(words);fs=list(map(nf.fields,words));b0=row['b0'];S=sum(s*(ma<<max(0,ix-b0))for s,ma,ix in fs);Q=sum((ma<<max(0,ix-b0))**2 for s,ma,ix in fs);_,me,ie=nf.fields(nf.EPS);c=min(2*b0,ie+149)//2*2;value=((n*Q-S*S)<<(2*b0-c))+(n*n*me<<(ie+149-c));got,state,info=nonnegative(value,n*n,c);assert got==int(row['denominator_word'],16)
 out={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'FINITE_MODEL_PLUS_MATHEMATICAL_BOUND_NO_LEAN_NO_NATIVE_TIME','script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'random_cases':20000,'counts':dict(count),'max_scaled_bits_seen':maxbits,'accepted_m_lt_2pow16':normalsmall,'actual_previous_fallback':{'cell':fixture['cell'],'row':row['row'],'new_state':state,'word':f'{got:08x}','details':info},'universal_bound':'ForS>0,0<m<2^32,t=floor((48-floorlog2S+floorlog2m)/2)>=0: t<=39,A=S*2^(2t)<2^80,2^46<=floor(A/m)<2^49. Ifm<2^16 thenA<2^64. c even carries exactpower2sqrtfactor.','scope':'Nextroundproof-space research only, frozenGEMM/RMS sourceunchanged','limits':['Not a runtimecandidate','ExistingFY caller/proofconnection not supplied','Rarepathcoverage not wholemodel speed','No confirmation inputs read']};(nc.HERE/'fw-nonnegative-probe.json').write_text(json.dumps(out,indent=2),encoding='utf8');print(json.dumps(out))
if __name__=='__main__':main()
