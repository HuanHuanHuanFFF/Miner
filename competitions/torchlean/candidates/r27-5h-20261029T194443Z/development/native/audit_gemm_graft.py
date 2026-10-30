"""Read-only declaration/alias audit for the exact Mixer graft."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,re
HERE=Path(__file__).resolve().parent;BASE=HERE.parents[1]
def sha(x):return hashlib.sha256(x).hexdigest()
def load(path,name):
 s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
c=load(HERE/'frozen_compact_public23.py','r27_gemm_audit_cp')
raw23=(BASE/'competition-state/source-private/submission23-Kernel.lean').read_bytes()
raw27=(BASE/'competition-state/source-private/submission27-Kernel.lean').read_bytes()
builder=load(HERE/'graft_gemm27_public23.py','r27_gemm_audit_builder')
result,metadata=builder.build(raw23,raw27)
def decls(source):return {m.group(1):source[m.start():end].rstrip() for m,end in c.ranges(source,c.DECL)}
s23=raw23.decode();s27=raw27.decode();a=decls(s23);b=decls(s27)
rows=[]
for name in ['Yo','Yq','Zy','Z5','Zi','ZcC','ZbZ','finiteWord','kernels0']:
 aa=a.get(name);bb=b.get(name)
 rows.append({'name':name,'present23':aa is not None,'present27':bb is not None,
  'exact_declaration_equal':aa==bb if aa is not None and bb is not None else None,
  'statement_equal':aa.split(':=',1)[0]==bb.split(':=',1)[0] if aa is not None and bb is not None else None,
  'source23_sha256':sha(aa.encode()) if aa else None,'source27_sha256':sha(bb.encode()) if bb else None})
aa=c.aliases(s23[:s23.index('structure Acc')]);bb=c.aliases(s27[:s27.index('structure Acc')])
alias_evidence={alias:{'qualified':q,'source23_alias':aa.get(q),'source27_alias':bb.get(q)} for q,alias in bb.items() if alias in ['Cw','CQ']}
out={'at_utc':datetime.now(timezone.utc).isoformat(),'candidate_sha256':sha(result),'candidate_bytes':len(result),
 'dependency_declarations':rows,'alias_evidence':alias_evidence,'metadata':metadata,
 'actual_binding':{'dense_field':'YaV,Ya3Q','full_correct':'Original all12 entry with Zc0Q simplification','runtime_fallback':'kernels0.dense.2, never gemmSpec'},
 'scope':'Bounded lexical/declaration evidence, not Lean name-resolution proof. All old common proofs typechecked before new reciprocal failures inbatch6, but this new exact source still needs full original gate',
 'small_k_option':{'recipe':'graft_gemm27_threshold0.py','sha256':'345ffefe39ad4c1b2f3a9dbc3bdb14c3e086ace4c2a450fb2ea621065214619b','bytes':252763,
 'change':'Only finite nonempty small k uses YaV too, avoiding legacyfallback; original proof requires onlyk>0. Notcompiled/notqueued; D chooses, no extra queue by default'},
 'publication':'Hashes/own recipe only, no upstream source text emitted'}
(HERE/'gemm27-graft-static-audit.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
req_path=HERE/'CI-REQUEST-16-MIXER-GEMM-GRAFT.json';req=json.loads(req_path.read_text());req['static_audit']='gemm27-graft-static-audit.json';req['optional_small_k0']=out['small_k_option'];req_path.write_text(json.dumps(req,indent=2)+'\n',encoding='utf-8')
print(json.dumps(out,indent=2))
