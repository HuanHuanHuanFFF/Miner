"""Finite rounding-domain cross-check, not a Lean proof or performance test."""
import random,json,hashlib
from pathlib import Path
MASK=(1<<64)-1
def rse(v,s):
 if s==0:return v
 if s<64:
  q=v>>s;r=v&((1<<s)-1);h=1<<(s-1)
  return q+int(r>h or (r==h and q&1))
 if s==64:return int(v>(1<<63))
 return 0
def finish(sign,p,scale,k):
 q=rse(p,k-23);carry=q==(1<<24);position=(k+scale+int(carry))&MASK
 if position>425:return (int(sign)<<31)|0x7f800000
 m=(1<<23) if carry else q
 return (int(sign)<<31)|(((position-171)&255)<<23)|((max(0,m-(1<<23)))&0x7fffff)
def ref(sign,p,scale):
 if p==0:return int(sign)<<31
 k=p.bit_length()-1;pos=(k+scale)&MASK
 if pos<172:
  q=rse(p,149-scale) if scale<149 else (p<<((scale-149)&63))&MASK
  if q==0:return int(sign)<<31
  if q==0x800000:return (int(sign)<<31)|0x800000
  return (int(sign)<<31)|(q&0x7fffff)
 q=((p<<((23-k)&63))&MASK) if k<23 else rse(p,k-23)
 carry=q==0x1000000;pos=(pos+int(carry))&MASK
 if pos>425:return (int(sign)<<31)|0x7f800000
 m=0x800000 if carry else q
 return (int(sign)<<31)|(((pos-171)&255)<<23)|(max(0,m-0x800000)&0x7fffff)
def new(sign,p,scale):
 for k in [47,46]:
  if p>>k==1 and ((k+scale)&MASK)>=172:return finish(sign,p,scale,k)
 return ref(sign,p,scale)
rng=random.Random(101);count=0;hits=0
values=[0,1,(1<<46)-1,1<<46,(1<<46)+1,(1<<47)-1,1<<47,(1<<47)+1,(1<<48)-1,(1<<64)-1]
values += [rng.getrandbits(64) for _ in range(1000)]
values += [rng.randrange(1<<23,1<<24)*rng.randrange(1<<23,1<<24) for _ in range(6000)]
scales=[0,1,123,124,125,126,127,128,129,148,149,150,170,171,172,377,378,379,380,381,424,425,426,MASK-47,MASK-46,MASK]
for p in values:
 for scale in scales:
  for sign in [False,True]:
   assert new(sign,p,scale)==ref(sign,p,scale),(sign,p,scale)
   count+=1;hits+=int(any(p>>k==1 and ((k+scale)&MASK)>=172 for k in [47,46]))
root=Path(__file__).resolve().parent
result={'cases':count,'protected_path_cases':hits,'mismatches':0,'kernel_sha256':hashlib.sha256((root/'Kernel.lean').read_bytes()).hexdigest(),'scope':'Finite Python model comparison only; Lean and performance pending'}
(root/'probe-result.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps(result))
