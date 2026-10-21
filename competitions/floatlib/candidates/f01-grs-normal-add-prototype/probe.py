"""Independent integer-rounding reference vs guarded normal GRS addition."""
from pathlib import Path
import random,json
def shift_round(x,k):
 if k<=0:return x<<(-k)
 q,r=divmod(x,1<<k);h=1<<(k-1)
 return q+int(r>h or (r==h and q&1))
def reference(a,b):
 def unpack(w):
  e=(w>>23)&255;f=w&0x7fffff
  return (-1 if w>>31 else 1)*((1<<23)|f if e else f),(e-150 if e else -149)
 x,ex=unpack(a);y,ey=unpack(b);e=min(ex,ey);v=(x<<(ex-e))+(y<<(ey-e))
 if not v:return (a&b)&0x80000000 if not x and not y else 0
 sign=int(v<0)<<31;v=abs(v);top=v.bit_length()-1;out_e=top+e
 if out_e < -126:return sign|shift_round(v,-149-e)
 m=shift_round(v,top-23)
 if m==1<<24:m>>=1;out_e+=1
 if out_e>127:return sign|0x7f800000
 return sign|((out_e+127)<<23)|(m&0x7fffff)
def fast(a,b):
 ea=(a>>23)&255;eb=(b>>23)&255
 if ea in [0,255] or eb in [0,255] or a>>31!=b>>31:return None
 hi,lo=(b,a) if ea<eb or (ea==eb and (a&0x7fffff)<(b&0x7fffff)) else (a,b)
 eh=(hi>>23)&255;el=(lo>>23)&255;d=eh-el
 if d>27:return hi
 mh=((hi&0x7fffff)|0x800000)<<3;ml0=((lo&0x7fffff)|0x800000)<<3
 ml=(ml0>>d)|int((ml0&((1<<d)-1))!=0);m=mh+ml;e=eh
 if m>=0x8000000:m=(m>>1)|(m&1);e+=1
 q=m>>3;r=m&7;q+=int(r>4 or (r==4 and q&1))
 if q==1<<24:q>>=1;e+=1
 if e>=255:return None
 return (hi&0x80000000)|(e<<23)|(q&0x7fffff)
rng=random.Random(20261021);cases=0;hits=0
values=[]
for e in [1,2,3,100,126,127,128,200,252,253,254]:
 for f in [0,1,2,3,0x3fffff,0x400000,0x7ffffd,0x7ffffe,0x7fffff]:values.append((e<<23)|f)
pairs=[(a,b) for a in values for b in values]
pairs += [(rng.randrange(1,255)<<23|rng.getrandbits(23),rng.randrange(1,255)<<23|rng.getrandbits(23)) for _ in range(80000)]
for a,b in pairs:
 for sign in [0,0x80000000]:
  a1=a|sign;b1=b|sign;got=fast(a1,b1);cases+=1
  if got is not None:
   assert got==reference(a1,b1),(hex(a1),hex(b1),hex(got),hex(reference(a1,b1)));hits+=1
result={'cases':cases,'protected_path_cases':hits,'mismatches':0,'scope':'Finite integer-reference check; GRS proof not supplied, no formal correctness claim'}
(Path(__file__).resolve().parent/'probe-result.json').write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps(result))
