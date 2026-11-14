from pathlib import Path
from fractions import Fraction
import json,hashlib
from datetime import datetime,timezone
H=Path('competitions/torchlean/candidates/r26-1h-20261029T085515Z/research/key')
def p2(e):return Fraction(1<<e) if e>=0 else Fraction(1,1<<(-e))
def decode32mag(w):
 e=w>>23; f=w&0x7fffff
 assert e<255
 return Fraction(f)*p2(-149) if e==0 else Fraction((1<<23)+f)*p2(e-150)
def decode64(w):
 sg=-1 if w>>63 else 1; e=(w>>52)&2047;f=w&((1<<52)-1)
 assert e<2047
 return sg*(Fraction(f)*p2(-1074) if e==0 else Fraction((1<<52)+f)*p2(e-1075))
def runtime(q):
 m=q&0x7fffffff;e=(m>>23)&255;f=m&0x7fffff;b=((e+896)<<52)|(f<<29)
 below=b-(0x20000000 if m==0x00800000 else 0x10000000);above=b+0x10000000
 return ((above|(1<<63)),(below|(1<<63))) if q>>31 else (below,above)
fractions=[0,1,2,(1<<22),(1<<23)-2,(1<<23)-1];cases=[];bad=[]
for e in range(1,255):
 for f in fractions:
  m=(e<<23)|f;v=decode32mag(m);prev=decode32mag(m-1)
  nxt=p2(128) if m==0x7f7fffff else decode32mag(m+1)
  lo=(prev+v)/2;hi=(v+nxt)/2
  for sign in [0,1]:
   q=m|(sign<<31);low,high=runtime(q);expected=(-hi,-lo) if sign else (lo,hi)
   actual=(decode64(low),decode64(high))
   assert expected[0]<expected[1]
   assert not expected[0]<=0<=expected[1]
   if actual!=expected:bad.append(hex(q))
   cases.append(dict(q=f'{q:08x}',lower=f'{low:016x}',upper=f'{high:016x}',match=actual==expected))
assert not bad
payload=json.dumps(cases,separators=(',',':')).encode();(H/'follow-on/direct-cell-cases.json').write_bytes(payload+b'\n')
res=dict(at_utc=datetime.now(timezone.utc).isoformat(),scope='Exact rational diagnostic for newly drafted direct midpoint field/real/sign branches; no Float native operation and no Lean proof',normal_exponents='all 1..254',fractions=fractions,signs=[False,True],cases=len(cases),endpoint_equalities=2*len(cases),zero_containment_failures=0,mismatches=bad,cases_sha256=hashlib.sha256(payload+b'\n').hexdigest(),candidate_sha256=hashlib.sha256((H/'follow-on/MidpointDirectContractOnly.lean').read_bytes()).hexdigest(),source='IEEE exact neighbor average model; maximum finite upper neighbor modeled as exact 2^128 before overflow',complete_input_domain=False,Lean='NOT_RUN',native='NOT_RUN',public_gate='NOT_RUN',performance='NOT_RUN',selection_effect='New branch constants checked; not an independent formal confirmation')
(H/'follow-on/direct-cell-model.json').write_text(json.dumps(res,indent=2)+'\n',encoding='utf-8');print(json.dumps(res,indent=2))
