import json,random,struct,time,hashlib
from pathlib import Path
D=Path(__file__).resolve().parent
start=time.perf_counter()
def rne(p,t):
 q,r=divmod(p,1<<t)
 return q+int(r>(1<<(t-1)) or (r==(1<<(t-1)) and q&1)) if t else p
def rn24(p):
 t=max(0,p.bit_length()-24)
 return rne(p,t)<<t

def jam(p): return (p>>17)|int((p&131071)!=0)
def u32fp(n): return int(struct.unpack('<f',struct.pack('<f',n))[0])
def old_core(a,b,s):
 p=a*b;r=rn24(p);hi=int(r>=1<<47);q=r>>(23+hi)
 return ((s-127+hi)<<23)|(q-(1<<23))
def new_core(a,b,s):
 p=a*b;j=jam(p);r=u32fp(j);hi=r>>30;q=r>>(6+hi)
 return ((s-127+hi)<<23)|(q-(1<<23))
# Directed product and all remainder classes around ties at quotient parity0/1.
ps=[]
for h in (46,47):
 t=h-23
 for q in ((1<<23),(1<<23)+1,(1<<24)-2,(1<<24)-1):
  for rem in (0,1,(1<<(t-1))-131073,(1<<(t-1))-131072,(1<<(t-1))-1,1<<(t-1),(1<<(t-1))+1,(1<<(t-1))+131071,(1<<t)-1):
   p=(q<<t)+rem
   if 1<<46<=p<1<<48:ps.append(p)
rng=random.Random(190102)
ps += [rng.randrange(1<<46,(1<<24)-1<<24) for _ in range(50000)]
mismatch=[];nosticky=[]
for p in ps:
 lhs=rn24(p);rhs=u32fp(jam(p))<<17
 if lhs!=rhs:mismatch.append([p,lhs,rhs])
 if lhs != (u32fp(p>>17)<<17) and len(nosticky)<5:nosticky.append([p,lhs,u32fp(p>>17)<<17])
# Valid24x24 inputs, independent full normal-core comparison with u32 native conversion.
pairs=[(1<<23,1<<23),(8388609,16777214),((1<<24)-1,(1<<24)-1),(8390656,8390656),(8390656,8394752)]
pairs += [(rng.randrange(1<<23,1<<24),rng.randrange(1<<23,1<<24)) for _ in range(50000)]
core_mismatch=[]
for a,b in pairs:
 for s in (128,254,380):
  if old_core(a,b,s)!=new_core(a,b,s):core_mismatch.append([a,b,s])
out={'state':'FINITE_MODEL_PASS' if not mismatch and not core_mismatch else 'COUNTEREXAMPLE','shift':17,'general_product_samples':len(ps),'valid_mantissa_pairs':len(pairs),'normal_core_comparisons':len(pairs)*3,'mismatch_count':len(mismatch),'core_mismatch_count':len(core_mismatch),'first_mismatches':mismatch[:3]+core_mismatch[:3],'without_sticky_counterexamples':nosticky,'max_valid':{'P':((1<<24)-1)**2,'J':jam(((1<<24)-1)**2),'R':u32fp(jam(((1<<24)-1)**2))},'elapsed_seconds':time.perf_counter()-start,'limits':'Finite Python exact integer and IEEE binary32 struct conversion only. Not Lean, original runtime, full gate, benchmark or unseen confirmation.'}
out['script_sha256']=hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
(D/'jam-model.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8')
print(json.dumps(out,indent=2))
