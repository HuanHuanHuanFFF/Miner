"""Synthetic exact-word counterexamples and tie cases; no workload sampling."""
from pathlib import Path
import ast,json,hashlib
D=Path(__file__).resolve().parent
R=next(p for p in D.parents if (p/'AGENTS.md').exists())
src=R/'competitions/floatlib/research/astra-collab-20261023-r7/nonfinite-oracle.py'
tree=ast.parse(src.read_bytes());names={'exp','frac','nan','snan','inf','zero','choose','unpack','rounded','add','mul','dot'}
e={};exec(compile(ast.Module(body=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in names],type_ignores=[]),str(src),'exec'),e)
add,mul,dot=e['add'],e['mul'],e['dot']
def safe(a,x):
 z=(a>>23)&255
 return 26<=z<=254 and (x&0x7fffffff)<((z-25)<<23)
ties=[]
for a in [0x3f800000,0x3f800001,0x3f800002,0x7f7fffff]:
 z=(a>>23)&255
 for sa in [0,0x80000000]:
  for offset in [25,24]:
   midpoint=(z-offset)<<23
   for sx in [0,0x80000000]:
    for delta in [-1,0,1]:
     x=sx|(midpoint+delta);u=sa|a;y=add(u,x)
     if safe(u,x):assert y==u
     ties.append({'a':hex(u),'x':hex(x),'half_kind':'quarter_binade' if offset==25 else 'ordinary_half',
       'neighbor_delta':delta,'safe_guard':safe(u,x),'result':hex(y),'unchanged':y==u})
# Factoring a common finite normal multiplier changes product rounding.
a=0x3f800001;b0=0x3f800000;b1=0xbf7ffffe
ordered=add(mul(a,b0),mul(a,b1));factored=mul(a,add(b0,b1))
assert ordered==0x34000000 and factored==0x34000001
# Every input and both dot endpoints are normal; a product still underflows.
A=[0x00800000,0x00800000];B=[0x33800000,0x3f800001];two=0x40000000
scaledA=[mul(two,x) for x in A]
base=dot(A,B);rescaled=mul(two,base);actual=dot(scaledA,B)
assert base==0x00800001 and rescaled==0x01000001 and actual==0x01000002
assert all(1<=e['exp'](x)<=254 for x in A+B+scaledA+[base,rescaled,actual])
out={'state':'EXACT_INTEGER_ORACLE_COUNTEREXAMPLES_ONLY','tie_neighbor_rows':ties,
 'distribution_failure':{'a':hex(a),'b':[hex(b0),hex(b1)],'ordered_products':[hex(mul(a,b0)),hex(mul(a,b1))],
 'ordered_sum':hex(ordered),'factored':hex(factored),'all_inputs_normal':True},
 'power2_scaling_endpoint_guard_failure':{'A':[hex(x) for x in A],'B':[hex(x) for x in B],
 'scaled_A':[hex(x) for x in scaledA],'base_products':[hex(mul(x,y)) for x,y in zip(A,B)],
 'scaled_products':[hex(mul(x,y)) for x,y in zip(scaledA,B)],'base_dot':hex(base),'scale_after_dot':hex(rescaled),
 'dot_after_scaling_A':hex(actual),'all_inputs_and_endpoints_normal':True},
 'limits':'Synthetic source-derived integer word model, not Lean/hardware or official coverage/performance. Frozen strictSUMguard unchanged.',
 'oracle_sha256':hashlib.sha256(src.read_bytes()).hexdigest(),'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
(D/'semantic-reuse-counterexamples.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8',newline='\n')
print(json.dumps({k:v for k,v in out.items() if k!='tie_neighbor_rows'},indent=2))
print('tie/neighbor rows',len(ties))
