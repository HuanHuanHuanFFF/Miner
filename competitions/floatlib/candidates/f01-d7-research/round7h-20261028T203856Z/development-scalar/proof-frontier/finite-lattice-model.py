"""Untimed finite falsifier for a proposed normal-or-zero FP64 proof domain.
No compiler/native benchmark, performance comparison, or universal proof.
"""
from fractions import Fraction
from pathlib import Path
import hashlib,json,random,struct
OUT=Path(__file__).resolve().parent

def f32(w):return struct.unpack('<f',struct.pack('<I',w))[0]
def bits64(x):return struct.unpack('<Q',struct.pack('<d',x))[0]
def exact(w):
 e=(w>>23)&255;f=w&0x7fffff
 assert e<255
 n=f if e==0 else (1<<23)+f;k=-149 if e==0 else e-150
 if w>>31:n=-n
 return Fraction(n<<k,1) if k>=0 else Fraction(n,1<<(-k))
def idx(w):return max(0,((w>>23)&255)-1)
def pow2(k):return Fraction(1<<k,1) if k>=0 else Fraction(1,1<<(-k))

counts=dict(dots=0,products=0,prefixes=0,nonzero_prefixes=0,zeros=0)
worst=Fraction(0);worst_case=None
witness=[]
# Values exercise signed zero, minimum/maximum subnormal and normal, and extrema.
pool=[0,0x80000000,1,0x80000001,0x7fffff,0x807fffff,0x800000,0x80800000,0x3f800000,0xbf800000,0x7f7fffff,0xff7fffff]
for seed in [24282811,24282813]:
 rng=random.Random(seed)
 for case in range(36):
  n=[1,2,3,7,16,31,64,127,256,1024,2048,4096][case%12]
  if case<12:
   aa=[pool[(case+i)%len(pool)] for i in range(n)]
   bb=[pool[(case*3+i*5)%len(pool)] for i in range(n)]
  elif case<24:
   aa=[rng.choice(pool) for _ in range(n)];bb=[rng.choice(pool) for _ in range(n)]
  else:
   aa=[(rng.getrandbits(1)<<31)|(rng.randrange(255)<<23)|rng.getrandbits(23) for _ in range(n)]
   bb=[(rng.getrandbits(1)<<31)|(rng.randrange(255)<<23)|rng.getrandbits(23) for _ in range(n)]
  H=max(map(idx,aa))+max(map(idx,bb));L=(n-1).bit_length();B=pow2(H+2*L-303)
  M=pow2(H-250);acc=0.0;total=Fraction(0)
  for a,b in zip(aa,bb):
   a0=exact(a);b0=exact(b);prod=f32(a)*f32(b)
   assert Fraction.from_float(prod)==a0*b0
   assert abs(a0*b0)<M
   acc=acc+prod;total+=a0*b0
   w=bits64(acc);e=(w>>52)&2047
   assert e<2047
   if acc:
    assert e>0
    assert Fraction.from_float(acc).denominator <= 1<<298
    counts['nonzero_prefixes']+=1
   else:counts['zeros']+=1
   counts['products']+=1;counts['prefixes']+=1
  ratio=abs(Fraction.from_float(acc)-total)/B
  assert ratio<=1
  if ratio>worst:worst=ratio;worst_case={'seed':seed,'case':case,'n':n,'H':H,'L':L}
  witness.append({'seed':seed,'case':case,'n':n,'H':H,'L':L,'sum_bits':hex(bits64(acc)),'error_div_B_num':str(ratio.numerator),'error_div_B_den':str(ratio.denominator)})
  counts['dots']+=1
# Exact rational scalar inequalities used by the proposed induction; boundaries only.
abstract=[]
u=Fraction(1,1<<53)
for n in [2,3,4,7,16,1<<20,(1<<30)-1,1<<30]:
 assert n*u<=Fraction(1,1<<23)
 assert Fraction(n*(n+1),2)/(1-n*u)<=n*n
 abstract.append({'n':n,'n_u_num':str((n*u).numerator),'n_u_den':str((n*u).denominator)})
result={'status':'FINITE_MODEL_PASS_NOT_PROOF','seeds':[24282811,24282813],'counts':counts,'worst_error_div_B':{'num':str(worst.numerator),'den':str(worst.denominator),'case':worst_case},'abstract_boundary_checks':abstract,'cases':witness,'unknown':['Lean native primitive/model bridge','Universal subnormal widening','Universal normal-or-zero invariant','Universal error enclosure and actual certificate soundness']}
(OUT/'finite-lattice-model.json').write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps({k:v for k,v in result.items() if k!='cases'}))
