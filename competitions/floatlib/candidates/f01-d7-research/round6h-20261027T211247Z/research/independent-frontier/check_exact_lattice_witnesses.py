"""Six deterministic nonzero witnesses from completed summary output; no random search."""
from pathlib import Path
from datetime import datetime,timezone
import ast,importlib.util,json,hashlib
D=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('gen',D/'same_exponent_add.py');M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)
P=M.R/'competitions/floatlib/research/astra-collab-20261023-r7/nonfinite-oracle.py';tree=ast.parse(P.read_bytes());O={}
names={'exp','frac','nan','snan','inf','zero','canon','choose','unpack','rounded','add','mul','summation','dot'}
exec(compile(ast.Module(body=[x for x in tree.body if isinstance(x,ast.FunctionDef) and x.name in names],type_ignores=[]),str(P),'exec'),O)
base=M.R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40171180249';idx=json.loads((base/'original-artifact-hashes.json').read_bytes());plan,ph=M.load_checked(base,idx,'diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json');cases={c['name']:c for c in plan['cases']}
report=json.loads((D/'exact-lattice-40171180249.json').read_bytes());out=[];steps=0
def equal(x,ex,y,ey):
 e=min(ex,ey);return (x<<(ex-e))==(y<<(ey-e))
for r in report['cases']:
 for w in r['nonzero_hit_examples']:
  c=cases[r['name']];b=w['batch'];i=w['row'];j=w['column'];n=c['n'];q=w['qProduct'];coeffsum=0;acc=0;trace=[]
  for k in range(n):
   u=M.E['element'](c,(b*c['m']+i)*n+k,0,n);v=M.E['element'](c,(b*n+k)*c['p']+j,1,c['p'])
   a,ea=O['unpack'](u);bb,eb=O['unpack'](v);prod=O['mul'](u,v);pr,ep=O['unpack'](prod)
   assert equal(a*bb,ea+eb,pr,ep),'Product was not exact'
   sh=ea+eb-q
   term=(a*bb)<<sh if sh>=0 else (a*bb)//(1<<(-sh))
   assert equal(a*bb,ea+eb,term,q)
   coeffsum+=term;assert abs(coeffsum)<=1<<24
   acc=O['add'](acc,prod);ar,ae=O['unpack'](acc);assert equal(ar,ae,coeffsum,q),'Prefix was not exact'
   if coeffsum==0:assert acc==0,'Zero prefix did not preserve +0 seed semantics'
   trace.append({'k':k,'u':f'{u:08x}','v':f'{v:08x}','product':f'{prod:08x}','coefficient':term,'prefix_coefficient':coeffsum,'prefix':f'{acc:08x}'})
   steps+=1
  expected=O['rounded'](coeffsum,q);assert expected==acc
  out.append({'case':r['name'],**w,'final_raw':f'{acc:08x}','integer_final_raw':f'{expected:08x}','steps':trace})
assert len(out)==6 and steps==33
result={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'PASS_SIX_FINITE_NONZERO_PRODUCT_WITNESSES','plan_sha256':ph,'oracle_sha256':hashlib.sha256(P.read_bytes()).hexdigest(),'certificate_receipt_sha256':hashlib.sha256((D/'exact-lattice-40171180249.json').read_bytes()).hexdigest(),'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'witness_count':6,'product_and_prefix_steps':steps,'witnesses':out,'scope':'Exact integer oracle checks each original product and every prefix, then final word equality. Not Lean/host floating execution, all-input proof, performance, or random correctness expansion.'}
(D/'exact-lattice-witnesses.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8',newline='\n');print(json.dumps({k:result[k] for k in ['state','witness_count','product_and_prefix_steps']}))
