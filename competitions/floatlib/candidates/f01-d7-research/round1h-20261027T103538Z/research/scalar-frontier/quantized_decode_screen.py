"""Read-only known-plan screen of a full raw-high16 decoder table; no candidate."""
from pathlib import Path
import ast,json,hashlib,time
D=Path(__file__).resolve().parent
R=next(p for p in D.parents if (p/'AGENTS.md').exists())
G=R/'competitions/floatlib/research/astra-collab-20261023-r7/public-nonfinite-opportunity.py'
T=ast.parse(G.read_bytes());E={};exec(compile(ast.Module(body=[n for n in T.body if isinstance(n,ast.FunctionDef) and n.name in {'word','ctz','element'} or isinstance(n,ast.Assign) and any(isinstance(z,ast.Name) and z.id in {'M32','M64'} for z in n.targets)],type_ignores=[]),str(G),'exec'),E)
def partner(c,i,a):
 w=E['word'](c['seed'],i,31);rel=c['relation']
 if rel==1:return a
 if rel==2:return a^0x80000000
 if rel in (3,7):
  mask=(1<<min(23,c['relParam']))-1;b=(a&(~mask&0xffffffff))|(w&mask)
  return b^0x80000000 if rel==3 else b
 if rel==4:return E['element'](c,0,1,31)
 if rel==5:
  if w%100<c['relParam']:return (w&0x80000000)|(0 if c['kernel']=='add' else 0x3f800000)
  return E['element'](c,i,1,31)
 if rel==6:
  ea=(a>>23)&255
  if ea in (0,255):return E['element'](c,i,1,31)
  return (w&0x807fffff)|(max(1,min(254,ea-c['relParam']))<<23)
 return E['element'](c,i,1,31)
def kind(w):
 mag=w&0x7fffffff;e=(w>>23)&255
 if mag==0:return 'zero_existing_tableProduct'
 if 24<=e<=254:return 'normal_existing_tableProduct'
 return 'fallback_ofBits'
start=time.monotonic();run=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40124283357';idx=json.loads((run/'original-artifact-hashes.json').read_bytes());p=run/idx['directory']/'diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json';b=p.read_bytes();key=p.relative_to(run/idx['directory']).as_posix();assert hashlib.sha256(b).hexdigest()==idx['files'][key]['sha256'];plan=json.loads(b);rows=[];totals={}
for c in plan['cases']:
 if c['kernel'] not in ('add','mul') or not c['timed']:continue
 n=c['work'];pos=sorted({0,n-1,*[i*n//256 for i in range(256)]}) if n else []
 row={'case':c['name'],'kernel':c['kernel'],'sampled_pairs':len(pos),'reaches_decoder_pairs':0,'decoder_operands':0,'table_hits':0,'categories':{},'distinct_table_indices':set()}
 for i in pos:
  u=E['element'](c,i,0,31);v=partner(c,i,u)
  if c['kernel']=='mul' and ((u>>23)&255)+((v>>23)&255)<128:continue
  row['reaches_decoder_pairs']+=1
  for w in (u,v):
   row['decoder_operands']+=1
   if w&0xffff:continue
   assert ((w>>16)<<16)==w
   row['table_hits']+=1;k=kind(w);row['categories'][k]=row['categories'].get(k,0)+1;row['distinct_table_indices'].add(w>>16)
 row['distinct_table_indices']=len(row['distinct_table_indices']);rows.append(row)
for op in ['add','mul']:
 rs=[r for r in rows if r['kernel']==op];t={k:sum(r[k] for r in rs) for k in ['sampled_pairs','reaches_decoder_pairs','decoder_operands','table_hits']};t['categories']={k:sum(r['categories'].get(k,0) for r in rs) for k in ['zero_existing_tableProduct','normal_existing_tableProduct','fallback_ofBits']};totals[op]=t
out={'status':'BOUNDED_SOURCE_TRANSCRIPTION_ONLY','old_plan_sha256':hashlib.sha256(b).hexdigest(),'totals':totals,'cases':rows,'selected_representation':'65536-entryArrayFloat32ofBits(j<<16), usedonlywhenrawlow16zero; otherwiseexistingB2decoder','physical_cost':'65536slots vs512scaletable; boxedFloat32perentry remains, notcontiguousFloat32. Coldinitialization/residency/cache/extraeligibilitybranchunknown.','actual_work_removed':'Onordinaryhits deletesmantissa numericcast+FPscale multiply; onzero B2ALREADYusestableProduct, noexistingofBitscall toclaim; onfallbackhits canreplaceofBits. MULLowScale rows excluded.','limits':'Not Lean-alignedofficial/privatecoverage or timing; nooperationweights inferred; no proposed adoption.','elapsed_seconds':time.monotonic()-start,'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()};(D/'quantized-decode-screen.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8',newline='\n');print(json.dumps(totals,indent=2))
