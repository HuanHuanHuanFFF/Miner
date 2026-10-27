"""Bounded source-model screening of whole-dot/whole-batch zero certificates."""
from pathlib import Path
from datetime import datetime,timezone
import ast,hashlib,json,time
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
start=time.monotonic();sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
generator=R/'competitions/floatlib/candidates/f01-d7-research/round3h-20261024T112622Z/profile-analyze.py'
tree=ast.parse(generator.read_text());fn=[x for x in tree.body if isinstance(x,ast.FunctionDef) and x.name in ('word','element')]
assert len(fn)==2
env={'MASK64':(1<<64)-1};exec(compile(ast.Module(body=fn,type_ignores=[]),str(generator),'exec'),env)
element=env['element']
bench=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/BenchSuite.lean'
assert sha(bench)=='2f1672738e07851fdb24ed968c248fc2e6d8a3e677c27763ebd489ada9425a9f'
home=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40398675395/download-42cfe8ce05b24bf6bd145777f10a1729/diagnostics/f01-d7-public-suite/public-suite'
plan_path=home/'public-drawn-plan.json';plan=json.loads(plan_path.read_bytes())
work=json.loads((home/'public-cell-work.json').read_bytes())
v=json.loads((home/'f01-r15-dev-packed-b2-1-verdict.json').read_bytes())
cost={cell:weight*v['classes'][cell]['submission_ns'] for cell,weight in work.items()};whole=sum(cost.values())
cases=[];read_words=0
zero=lambda w:(w&0x7fffffff)==0
finite=lambda w:(w&0x7f800000)!=0x7f800000
for c in plan['cases']:
 if c['kernel']!='bmm' or not c['timed']:continue
 batch,m,n,p=(c[k] for k in ('batch','m','n','p'))
 possible=c['mag']==2 or (c['zeroPct']>0 and c['zeroKind']!=3) or (c['specRate']>0 and (c['specMask']&16))
 if not possible:
  cases.append({'name':c['name'],'shape':[batch,m,n,p],'certificate_outputs':0,'certificate_mac_terms':0,'whole_batches':0,'screen':'GENERATOR_NO_ZERO_BRANCH; normal exponents >=1, subnormal fraction |1; zeroKind3 is tiny nonzero normal'})
  continue
 A=[element(c,i,0,n) for i in range(batch*m*n)]
 B=[element(c,i,1,p) for i in range(batch*n*p)];read_words+=len(A)+len(B)
 old_underflow=all((w&0x7fffffff)<0x16000000 for w in A) and all((w&0x7fffffff)<0x16000000 for w in B)
 counts={'zero_A_rows':0,'finite_A_rows':0,'zero_B_columns':0,'finite_B_columns':0,'certificate_outputs':0,'whole_batches':0}
 for b in range(batch):
  rows=[A[(b*m+r)*n:(b*m+r+1)*n] for r in range(m)]
  cols=[[B[(b*n+k)*p+j] for k in range(n)] for j in range(p)]
  rz=sum(all(map(zero,row)) for row in rows);rf=sum(all(map(finite,row)) for row in rows)
  cz=sum(all(map(zero,col)) for col in cols);cf=sum(all(map(finite,col)) for col in cols)
  counts['zero_A_rows']+=rz;counts['finite_A_rows']+=rf;counts['zero_B_columns']+=cz;counts['finite_B_columns']+=cf
  counts['certificate_outputs']+=rz*cf+rf*cz-rz*cz
  counts['whole_batches']+=int((rz==m and cf==p) or (rf==m and cz==p))
  assert time.monotonic()-start<18
 if old_underflow:counts['certificate_outputs']=counts['whole_batches']=0
 cases.append({'name':c['name'],'shape':[batch,m,n,p],'zeroPct':c['zeroPct'],'zeroKind':c['zeroKind'],'zeroCluster':c['zeroCluster'],'original_underflow_case':old_underflow,'total_outputs':batch*m*p,'certificate_mac_terms':counts['certificate_outputs']*n,'scan_words':len(A)+len(B),**counts,'screen':'LITERAL_INTEGER_WORD_GENERATOR; not machine branch or float execution'})
affected={':'.join(c['name'].split(':')[:2]) for c in cases if c['certificate_outputs']}
report={'at_utc':datetime.now(timezone.utc).isoformat(),'seed':1927003,'source_model_only':True,'plan_sha256':sha(plan_path),'generator_translation_sha256':sha(generator),'official_BenchSuite_sha256':sha(bench),'input_words_generated':read_words,'cases':cases,'certificate_outputs':sum(x['certificate_outputs'] for x in cases),'certificate_mac_terms':sum(x['certificate_mac_terms'] for x in cases),'whole_batches':sum(x['whole_batches'] for x in cases),'touched_cells':sorted(affected),'touched_cell_whole_time_upper':sum(cost[x] for x in affected)/whole,'target_time':'UNKNOWN','scope':'Exact exposed plan + previously checked literal generator translation. Counts are not physical execution or speed; cell upper includes all unaffected work in that cell, and is only for this sample. New row/column guards, flags, output and fallback costs are not free. Original whole-tensor underflow hits excluded.','elapsed_seconds':time.monotonic()-start}
(H/'zero-certificate-screen.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps({k:report[k] for k in ('input_words_generated','certificate_outputs','certificate_mac_terms','whole_batches','touched_cells','touched_cell_whole_time_upper','elapsed_seconds')}))
print(json.dumps([x for x in cases if x['certificate_outputs']],indent=2))
