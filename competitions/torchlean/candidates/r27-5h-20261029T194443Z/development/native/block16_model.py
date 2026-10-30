"""Finite signed-word audit of grouped prepared products, never a gate."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,random
HERE=Path(__file__).resolve().parent
B=1<<64;MASK=B-1;M128=(1<<128)-1
def signed(q):return q if q<(1<<63) else q-B
def merge(hi,lo,q):return (hi+(-1 if q>>63 else 0)+(1 if ((lo+q)&MASK)<lo else 0))&MASK
def run(terms):
 hi=lo=0;n=len(terms);full=n//16*16
 for j in range(0,full,16):
  q=sum(terms[j:j+16])&MASK
  assert signed(q)==sum(terms[j:j+16])
  hi,lo=merge(hi,lo,q),(lo+q)&MASK
 for q0 in terms[full:]:
  q=q0&MASK;hi,lo=merge(hi,lo,q),(lo+q)&MASK
 z=lo+(hi<<64)
 return z if z<(1<<127) else z-(1<<128)
rng=random.Random(0x27B16)
cases=0;terms_count=0
for n in [0,1,15,16,17,31,32,33,63,64,65,127,128,129,255,256,257,1024,4096]:
 for mode in range(12):
  if mode==0:ts=[(1<<59)-1]*n
  elif mode==1:ts=[-((1<<59)-1)]*n
  elif mode==2:ts=[(1 if i%2 else -1)*((1<<59)-1) for i in range(n)]
  elif mode==3:ts=[0]*n
  else:
   sx=rng.randrange(12);sw=11-sx
   ts=[rng.randrange(-(1<<(24+sx))+1,1<<(24+sx))*rng.randrange(-(1<<(24+sw))+1,1<<(24+sw)) for _ in range(n)]
  assert run(ts)==sum(ts)
  cases+=1;terms_count+=n
# A legal span12 term gives the discriminating negative control.
wide=(1<<24)-1
bad=(wide<<6)*(wide<<6)
assert bad<(1<<60) and 16*bad>=(1<<63)
bad_block=(16*bad)&MASK
assert signed(bad_block)!=16*bad
receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'seed':0x27B16,'cases':cases,'terms':terms_count,'mismatches':0,
 'bound':'Signed prepared coefficients, combined exponent span<=11, each absolute term<2^59; no per-dot max scan',
 'negative_control':{'span':12,'term':bad,'block_exact_sum':16*bad,'signed_low64':signed(bad_block),'detected':True},
 'scope':'Finite generic prepared-integer word/carry model only; no actual Float32 metadata bounds, bias finish, Lean/native or all12 acceptance',
 'runtime_risk':'Recursive Nat fuel per MAC may erase carry savings; use fixed16 unroll before native screen if implemented; no measured regression claim'}
(HERE/'block16-model.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
print(json.dumps(receipt,indent=2))
