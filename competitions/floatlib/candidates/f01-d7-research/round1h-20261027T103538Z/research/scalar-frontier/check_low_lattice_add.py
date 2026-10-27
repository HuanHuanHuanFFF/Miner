"""Small isolated next-round math discriminator; no Lean runtime/candidate."""
from pathlib import Path
import ast,json,hashlib,random
D=Path(__file__).resolve().parent
R=next(p for p in D.parents if (p/'AGENTS.md').exists())
O=R/'competitions/floatlib/research/astra-collab-20261023-r7/nonfinite-oracle.py'
t=ast.parse(O.read_bytes());E={};names={'exp','frac','nan','snan','inf','zero','choose','unpack','rounded','add'}
exec(compile(ast.Module(body=[n for n in t.body if isinstance(n,ast.FunctionDef) and n.name in names],type_ignores=[]),str(O),'exec'),E)
def core(u,v):
 a,b=u&0x7fffffff,v&0x7fffffff
 assert a<0x01000000 and b<0x01000000
 if ((u^v)&0x80000000)==0:
  n=a+b
  if n<0x01000000:return (u&0x80000000)|n
  q=(n>>1)+int((n&3)==3)
  return (u&0x80000000)|(q+0x800000)
 if a==b:return 0
 return ((u&0x80000000)|(a-b)) if a>b else ((v&0x80000000)|(b-a))
edge=[0,1,2,3,4,(1<<23)-2,(1<<23)-1,1<<23,(1<<23)+1,(1<<23)+2,(1<<24)-3,(1<<24)-2,(1<<24)-1]
pairs=[((s<<31)|a,(t<<31)|b) for s in range(2) for t in range(2) for a in edge for b in edge]
rng=random.Random(202610271124);pairs += [((rng.randrange(2)<<31)|rng.randrange(1<<24),(rng.randrange(2)<<31)|rng.randrange(1<<24)) for _ in range(20000)]
for u,v in pairs:assert core(u,v)==E['add'](u,v),(hex(u),hex(v),hex(core(u,v)),hex(E['add'](u,v)))
out={'state':'FINITE_MATH_ONLY_NO_RUNTIME_OR_CI','pairs':len(pairs),'mismatch_count':0,
 'domain':'Both raw magnitudes<2^24: zero/subnormal/raw exponent1. This entire maximal first affine segment denotesmag*2^-149.',
 'formula':'Same sign: exactmagnitudeN=a+b<2^25; below2^24 raw=N; otherwiseq=(N>>1)+[N&3==3],raw=q+2^23. Opposite signs: signedabsolute difference, equalmagnitudesreturn+0.',
 'difference_vs_GRS':'Noalign/log2/Float32cast/toBits/softwaregeneralRNE. R18normal-onlyADDrejects genuine subnormal operands butmayoverlapE1/E1; retainitsnegative evidence. R19d3c preguard25..253excludes thissegment. Scopedhistoryonly, notglobalnovelty.',
 'missing':'ActualFloatLibModel.add bridge, legalfullfallback, selectedC/ASM, old/public/privatedomaincoverage andmissguardcost allUNKNOWN; no highwholegainclaim.',
 'oracle_sha256':hashlib.sha256(O.read_bytes()).hexdigest(),'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
(D/'low-lattice-model.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8',newline='\n');print(json.dumps(out,indent=2))
