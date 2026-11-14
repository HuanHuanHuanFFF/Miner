"""Finite shape/layout/negativezero check for the exact Ya3Q -> linearSpec bridge."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,random
import norm_frontier as nf
ONE=0x3f800000;NEGZERO=0x80000000

def get(a,i):return a[i]if i<len(a)else 0
def dot(a,b):
 assert len(a)==len(b)
 assert all(((w>>23)&255)!=255 for w in a+b)
 value=sum(nf.key(x)*nf.key(y)for x,y in zip(a,b))
 if value==0:
  nz=bool(a)and all((nf.fields(x)[1]*nf.fields(y)[1]==0)and bool((x^y)>>31)for x,y in zip(a,b))
  return NEGZERO if nz else 0
 return nf.round_ratio(value,1,-298)

def reference(A,B,batch,m,k,n):
 return[dot([get(A,(bb*m+i)*k+t)for t in range(k)],[get(B,(bb*k+t)*n+j)for t in range(k)])for bb in range(batch)for i in range(m)for j in range(n)]
def scheduled(A,B,batch,m,k,n):
 if k<1:return reference(A,B,batch,m,k,n),'small_k_fallback'
 if any(((x>>23)&255)==255 for x in A+B):return None,'nonfinite_fallback'
 R=[]
 for bb in range(batch):
  AA=A[bb*m*k:(bb+1)*m*k];WW=[get(B,(bb*k+q%k)*n+q//k)for q in range(n*k)]
  R.append([dot([get(AA,i*k+t)for t in range(k)]+[ONE],[WW[j*k+t]for t in range(k)]+[NEGZERO])for i in range(m)for j in range(n)])
 return[R[q//(m*n)][q%(m*n)]for q in range(batch*m*n)],'linear_schedule'

def main():
 rng=random.Random(27102927);words=[0,NEGZERO,ONE,0xbf800000,1,0x80000001,0x007fffff,0x00800000,0x7f7fffff,0xff7fffff,0x3f800001,0x3effffff];counts={};outputs=0
 shapes=[(b,m,k,n)for b in [0,1,2]for m in [0,1,3]for k in [0,1,19,20,21,32]for n in [0,1,4]]
 for batch,m,k,n in shapes:
  for trunc in [0,1,2]:
   A=[rng.choice(words)for _ in range(max(0,batch*m*k-trunc))];B=[rng.choice(words)for _ in range(max(0,batch*k*n-trunc))]
   want=reference(A,B,batch,m,k,n);got,state=scheduled(A,B,batch,m,k,n);assert got==want,(batch,m,k,n,trunc,got,want);counts[state]=counts.get(state,0)+1;outputs+=len(got)
 a=[ONE]*20;b=[NEGZERO]*20;good=dot(a+[ONE],b+[NEGZERO]);bad=dot(a+[ONE],b+[0]);orig=dot(a,b);assert orig==good==NEGZERO and bad==0
 nonfinite=scheduled([0x7fc00001]*20,[ONE]*20,1,1,20,1);assert nonfinite==(None,'nonfinite_fallback')
 out={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'FINITE_LAYOUT_AND_SIGNEDZERO_MODEL_ONLY','candidate_sha256':'6fe5feb6cf0b919a9700f5f05264b1e98e24d7ee74b9d2853c1e55be866d4ada','script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'cases':sum(counts.values()),'outputs':outputs,'counts':counts,'negativezero_mutant':{'k':20,'A':'all3f800000','B':'all80000000','originaldot':'80000000','linear_bias80000000':'80000000','wrong_bias00000000':'00000000'},'nonfinite_fallback_branch_checked':True,'limits':['NoLean/native execution','Scalarfiniteexactmodel not allFloatLibsemantics','No speedclaim; allcompleteMixer allocations/residual costs still measuredbyD']};Path(__file__).with_name('gemm-graft-positive-check.json').write_text(json.dumps(out,indent=2),encoding='utf8');print(json.dumps(out))
if __name__=='__main__':main()
