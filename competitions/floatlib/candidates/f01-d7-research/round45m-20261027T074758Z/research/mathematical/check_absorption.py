"""Exact integer oracle falsification only; no workload exposure or timing."""
from pathlib import Path
import ast,json,hashlib,random,time
D=Path(__file__).resolve().parent
R=next(p for p in D.parents if (p/'AGENTS.md').exists())
source=R/'competitions/floatlib/research/astra-collab-20261023-r7/nonfinite-oracle.py'
tree=ast.parse(source.read_bytes());names={'exp','frac','nan','snan','inf','zero','choose','unpack','rounded','add','summation'}
env={};exec(compile(ast.Module(body=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in names],type_ignores=[]),str(source),'exec'),env)
add=env['add'];start=time.monotonic();rng=random.Random(202610270808)
def small(a,x):
 e=(a>>23)&255
 return 26<=e<=254 and (x&0x7fffffff)<((e-25)<<23)
def fold(a,xs):
 for x in xs:a=add(a,x)
 return a
pairs=[]
for e in [26,27,28,100,126,127,128,129,252,253,254]:
 lim=(e-25)<<23
 for f in [0,1,2,0x3fffff,0x7ffffe,0x7fffff]:
  for sa in [0,1]:
   for t in [0,1,0x7fffff,lim-1,lim,lim+1]:
    for sx in [0,1]:pairs.append(((sa<<31)|(e<<23)|f,(sx<<31)|t))
for _ in range(30000):
 e=rng.randrange(26,255);a=(rng.randrange(2)<<31)|(e<<23)|rng.randrange(1<<23)
 x=(rng.randrange(2)<<31)|rng.randrange((e-25)<<23);pairs.append((a,x))
checked=0;bad=[]
for a,x in pairs:
 if small(a,x):
  checked+=1;y=add(a,x)
  if y!=a:bad.append([hex(a),hex(x),hex(y)])
assert not bad,bad[:2]
a,x=0x3f800000,0xb3400000
naive={'a':hex(a),'x':hex(x),'exact_result':hex(add(a,x)),'a_preserved':add(a,x)==a,'safe_guard':small(a,x),
 'dyadic':'a=1, x=-3*2^-26; abs(x)<2^-24, but the lower binade midpoint is2^-25'}
assert add(a,x)==0x3f7fffff and not small(a,x)
xs=[0x32800000]*16  # 16 copies of2^-26; each individually absorbed at1.
assert all(small(a,t) for t in xs) and fold(a,xs)==a
sum_v=sum(env['unpack'](t)[0] << (env['unpack'](t)[1]+149) for t in xs)
once=add(a,env['rounded'](sum_v,-149))
assert once!=a
nonfinite=[0x7f800000,0xff800000,0x7fc00001,0xff800001]
assert all(not small(a,t) for t in nonfinite)
blocks=0
for _ in range(1000):
 e=rng.randrange(26,255);a=(rng.randrange(2)<<31)|(e<<23)|rng.randrange(1<<23)
 xs=[(rng.randrange(2)<<31)|rng.randrange((e-25)<<23) for _ in range(4)]
 assert fold(a,xs)==a;blocks+=1
out={'state':'PASS_FINITE_EXACT_INTEGER_ORACLE_ONLY','accepted_pair_checks':checked,'pairs_considered':len(pairs),'mismatch_count':len(bad),'four_term_blocks':blocks,
 'binade_counterexample':naive,'cannot_aggregate_block':{'start':'0x3f800000','term':'0x32800000','copies':16,'ordered_result':'0x3f800000','aggregate_then_add':hex(once)},
 'source_oracle_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
 'elapsed_seconds':time.monotonic()-start,'limitations':'No Lean/publicSUM proof, no hardware, no performance/workloadcoverage, no future confirmation inputs. Source-derived exact integer oracle, not an official measured implementation.'}
(D/'absorption-oracle.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8',newline='\n')
print(json.dumps(out,indent=2))
