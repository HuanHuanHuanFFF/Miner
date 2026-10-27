"""Finite boundary refutation and dependency binding, not a Lean proof."""
from pathlib import Path
import json,hashlib,struct,time,re
from datetime import datetime,timezone
H=Path(__file__).resolve().parent;ROOT=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
start=time.monotonic();LO=2**23;HI=2164260735
def rn(n):
 h=n.bit_length()-1;s=max(0,h-23);q,r=divmod(n,2**s)
 if s and (r>2**(s-1) or (r==2**(s-1) and q%2)):q+=1
 c=int(q==2**24);m=2**23 if c else q
 return q*2**s,h,c,m,h+c-23
points={LO,HI,HI-1,HI-127,HI-128,HI-129}
for h in range(23,32):
 for base in (2**h,2**(h+1),2**h+2**23,HI):
  points.update(base+delta for delta in range(-512,513))
points={x for x in points if LO<=x<=HI}
maxR=0
for n in sorted(points):
 R,h,c,m,e=rn(n)
 native=int(struct.unpack('<f',struct.pack('<f',float(n)))[0])
 assert R==native==m*2**e and 2**23<=m<2**24 and 0<=e<=8 and R<2**32
 assert h!=31 or c==0
 maxR=max(maxR,R)
 assert time.monotonic()-start<4.5
offsets=(0,1,2,3,63,64,65,126,127,128,129,254,255,256,257,511,512,513,1023)
mantissas=sorted({LO+i for i in offsets}|{2**24-1-i for i in offsets})
threshold_checks=0;cases=[]
for d in range(8):
 for a in mantissas:
  for b in mantissas:
   for same in (True,False):
    n=(a<<d)+(b if same else -b)
    if not(LO<=n<=HI):continue
    R,h,c,m,e=rn(n);L=23+d
    actual=R.bit_length()-1
    if same:predicted=L+int(R>=2**(L+1))
    else:
     assert d>=1
     predicted=L-1+int(R>=2**L)
    assert actual==predicted
    if same and d==0:assert actual==24
    threshold_checks+=1
    assert time.monotonic()-start<4.5
files=['HighRoundtrip-bridge.lean','fixed-Native-ToInt.lean','fixed-Native-Model.lean','fixed-Operations-Runtime.lean','fixed-ExactValue.lean','ToNat.lean']
bindings=[]
sourcepaths={'fixed-Native-ToInt.lean':'FloatLib/Floats/Formats/IEEE754/Native/Integer/ToInt.lean',
 'fixed-Native-Model.lean':'FloatLib/Floats/Formats/IEEE754/Native/Model.lean',
 'fixed-Operations-Runtime.lean':'FloatLib/Floats/Formats/BinaryInterchange/Operations/Runtime.lean',
 'fixed-ExactValue.lean':'FloatLib/Floats/Formats/BinaryInterchange/Model/ExactValue.lean'}
for name in files:
 p=H/name;raw=p.read_bytes();bindings.append(dict(path=name,bytes=len(raw),sha256=hashlib.sha256(raw).hexdigest(),git_blob_sha1=hashlib.sha1(b'blob '+str(len(raw)).encode()+b'\0'+raw).hexdigest(),
  source_url='https://raw.githubusercontent.com/lean-dojo/FloatLib/0d91825727839f597fd06b22fdd038ea21480f0c/'+sourcepaths[name] if name in sourcepaths else None))
support=ROOT/'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/scalar-representation/next-add-u32/Add-native-high-support.lean'
base=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
for p in (support,base):bindings.append(dict(path=str(p.relative_to(ROOT)),bytes=p.stat().st_size,sha256=hashlib.sha256(p.read_bytes()).hexdigest()))
draft=(H/'HighRoundtrip-bridge.lean').read_text()
assert not re.search(r'\b(sorry|axiom|unsafe|implemented_by|extern)\b',draft)
final=draft[draft.index('theorem high_roundtrip ('):]
assert '(hd :'not in final and '(hfit :'not in final
record=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='COMPLETE_SMALL_NUMERIC_BRIDGE_ATTEMPT_NOT_COMPILED',
 target='For UInt32 n with2^23<=n.toNat<=2164260735, native numeric roundtrip toNat equals RNE integer; all helper premises discharged in target theorem.',
 lean='NOT_RUN',kernel='NOT_CREATED',CI='NOT_RUN',new_axioms=False,
 finite_checks=dict(direct_N_count=len(points),threshold_pair_checks=threshold_checks,max_observed_R=maxR,
  threshold_domain='38 chosen mantissas per operand, d0..7, same/opposite signs, exact high-N filter',
  limit='Finite arithmetic/host binary32 checks only; no proof or timing claim'),
 source_bindings=bindings,missing_mathematical_interface='NONE_IDENTIFIED_IN_INSPECTED_FIXED_DEFINITIONS',
 remaining='Pinned Lean elaboration/kernel replay of the fragment; integer-to-word repack and runtime performance are separate and not implemented.',
 elapsed_seconds=time.monotonic()-start)
(H/'bridge-check.json').write_text(json.dumps(record,indent=2)+'\n')
print(json.dumps({k:record[k] for k in ('state','finite_checks','elapsed_seconds')}))
