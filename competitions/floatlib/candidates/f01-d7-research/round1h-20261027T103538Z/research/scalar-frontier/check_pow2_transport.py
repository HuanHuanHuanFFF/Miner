"""Bounded known-public-plan discriminator plus exact integer oracle only."""
from pathlib import Path
import ast,json,hashlib,random,time
D=Path(__file__).resolve().parent
R=next(p for p in D.parents if (p/'AGENTS.md').exists())
G=R/'competitions/floatlib/research/astra-collab-20261023-r7/public-nonfinite-opportunity.py'
O=G.parent/'nonfinite-oracle.py'
def functions(p,names,constants=()):
 t=ast.parse(p.read_bytes());e={};nodes=[n for n in t.body if isinstance(n,ast.FunctionDef) and n.name in names or isinstance(n,ast.Assign) and any(isinstance(z,ast.Name) and z.id in constants for z in n.targets)];exec(compile(ast.Module(body=nodes,type_ignores=[]),str(p),'exec'),e);return e
g=functions(G,{'word','ctz','element'},{'M32','M64'})
o=functions(O,{'exp','frac','nan','snan','inf','zero','choose','unpack','rounded','mul'})
def partner(c,i,a):
 w=g['word'](c['seed'],i,31);rel=c['relation']
 if rel==1:return a
 if rel==2:return a^0x80000000
 if rel in (3,7):
  mask=(1<<min(23,c['relParam']))-1;b=(a&(~mask&0xffffffff))|(w&mask)
  return b^0x80000000 if rel==3 else b
 if rel==4:return g['element'](c,0,1,31)
 if rel==5:
  if w%100<c['relParam']:return (w&0x80000000)|0x3f800000
  return g['element'](c,i,1,31)
 if rel==6:
  ea=(a>>23)&255
  if ea in (0,255):return g['element'](c,i,1,31)
  return (w&0x807fffff)|(max(1,min(254,ea-c['relParam']))<<23)
 return g['element'](c,i,1,31)
def eligible(u,v):
 eu,ev=(u>>23)&255,(v>>23)&255
 return 1<=eu<=254 and 1<=ev<=254 and 128<=eu+ev<=381 and ((u&0x7fffff)==0 or (v&0x7fffff)==0)
def result(u,v):
 return ((u^v)&0x80000000)|((((u>>23)&255)+((v>>23)&255)-127)<<23)|((u|v)&0x7fffff)
start=time.monotonic();rng=random.Random(202610271039);checked=0
for _ in range(20000):
 eu=rng.randrange(1,255);ev=rng.randrange(1,255)
 u=(rng.randrange(2)<<31)|(eu<<23);v=(rng.randrange(2)<<31)|(ev<<23)|rng.randrange(1<<23)
 if rng.randrange(2):u,v=v,u
 if eligible(u,v):assert result(u,v)==o['mul'](u,v);checked+=1
edges=[]
for eu,ev in [(1,127),(127,1),(127,254),(254,127),(128,254),(1,126),(254,254)]:
 for fu,fv in [(0,0),(0,0x7fffff),(0x7fffff,0)]:
  u=(eu<<23)|fu;v=(ev<<23)|fv;hit=eligible(u,v);want=o['mul'](u,v)
  if hit:assert result(u,v)==want
  edges.append({'u':f'{u:08x}','v':f'{v:08x}','accepted':hit,'model':f'{want:08x}'})
run=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40124283357';idx=json.loads((run/'original-artifact-hashes.json').read_bytes());pp=run/idx['directory']/'diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json';pb=pp.read_bytes();rel=pp.relative_to(run/idx['directory']).as_posix();assert hashlib.sha256(pb).hexdigest()==idx['files'][rel]['sha256'];plan=json.loads(pb)
rows=[]
for c in plan['cases']:
 if c['kernel']!='mul' or not c['timed']:continue
 n=c['work'];positions=sorted({0,n-1,*[i*n//256 for i in range(256)]}) if n else []
 hits=0;pows=0
 for i in positions:
  u=g['element'](c,i,0,31);v=partner(c,i,u)
  pows+=int((u&0x7fffff)==0 or (v&0x7fffff)==0)
  if eligible(u,v):hits+=1;assert result(u,v)==o['mul'](u,v)
 rows.append({'case':c['name'],'work':n,'relation':c['relation'],'mantBits':c['mantBits'],'sampled':len(positions),'pow_condition':pows,'guard_hits':hits,'hit_fraction':hits/len(positions) if positions else None})
assert time.monotonic()-start<10
out={'status':'FINITE_MODEL_AND_BOUNDED_OLD_PLAN_ONLY','exact_random_guard_hits':checked,'mismatches':0,'boundary_rows':edges,'old_run':40124283357,'plan_sha256':hashlib.sha256(pb).hexdigest(),'samples':sum(r['sampled'] for r in rows),'guard_hits':sum(r['guard_hits'] for r in rows),'cases':rows,
 'scope':'Own source-transcribed element+scalar partner, bounded deterministic positions. Not Lean-aligned official coverage, not private-suite prevalence/timing/benefit. No future confirmation data. Miss guard cost must be measured; no operation weights inferred.',
 'generator_source_sha256':hashlib.sha256(G.read_bytes()).hexdigest(),'oracle_source_sha256':hashlib.sha256(O.read_bytes()).hexdigest(),'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'elapsed_seconds':time.monotonic()-start}
(D/'pow2-preflight.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8',newline='\n')
print(json.dumps({k:v for k,v in out.items() if k not in ['cases','boundary_rows']},indent=2))
print(json.dumps([r for r in rows if r['guard_hits']],indent=2))
