"""CI12 exact tail record goals: add definitional reflexivity after the three final simps."""
from pathlib import Path
from datetime import datetime,timezone
from types import SimpleNamespace
import hashlib,json,re,ast,difflib
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
sha=lambda b:hashlib.sha256(b).hexdigest()
run=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40430974047'
idxraw=(run/'original-artifact-hashes.json').read_bytes();idx=json.loads(idxraw);root=run/idx['directory']
suite=root/'diagnostics/f01-d7-public-suite/public-suite';candidate='f01-r19-dev-dual-temporal-a4-4';diag=suite/'diagnostics'/candidate
evidence=H/'ci-40430974047';evidence.mkdir(exist_ok=True)
files=[suite/'inputs'/candidate/'Kernel.lean',suite/(candidate+'-verdict.json'),diag/'full-build-output.txt',diag/'replay.log',diag/'index.json']
bindings=[]
for p in files:
 raw=p.read_bytes();rec=idx['files'][p.relative_to(root).as_posix()]
 assert sha(raw)==rec['sha256'] and len(raw)==rec['bytes']
 name='input-b92d.lean' if p.name=='Kernel.lean' else p.name
 (evidence/name).write_bytes(raw)
 bindings.append({'original':str(p.relative_to(R)),'copy':str((evidence/name).relative_to(H)),'sha256':sha(raw),'bytes':len(raw)})
(evidence/'original-artifact-hashes.json').write_bytes(idxraw)
base=(H/'proof4/Kernel-dual-temporal-a4-proof4.lean').read_bytes()
assert sha(base)=='b92dac573897e6dc5c72eef9d5eebac778eeefde1f9ca262657dfacaa368c4ca'
assert files[0].read_bytes()==base
verdict=json.loads(files[1].read_bytes());assert verdict['stage']=='statement' and verdict['passed'] is False
build=files[2].read_text();errors=re.findall(r'^error: work/Submission.lean:(\d+):(\d+): (.*)$',build,re.M)
assert errors==[(str(l),str(c),'unsolved goals') for l,c in [(6765,8),(6774,8),(6783,6)]]
assert 'Failed to rewrite' not in build
capture=json.loads((diag/'index.json').read_bytes());assert capture['generated_c']==[] and capture['replay_exit_code']==1
goals=[]
for n,part in enumerate(build.split('error: work/Submission.lean:')[1:]):
 context=part[:part.find('\nwarning:')] if '\nwarning:' in part else part
 goal=context[context.index('⊢ '):].rstrip()
 # Pretty-printed fields and arithmetic on both sides are exactly equal, modulo indentation.
 left,right=goal[2:].split(' } =\n',1) if ' } =\n' in goal else ('','')
 assert left and right
 normalized_left=re.sub(r'\s+','',left+' }')
 normalized_right=re.sub(r'\s+','',right)
 assert normalized_left==normalized_right,(n,normalized_left,normalized_right)
 goals.append({'tail_count':3-n,'pretty_goal':goal,'printed_sides_equal_ignoring_whitespace':True,'hidden_detail':'Fin membership proof ellipses; kernel definitional reflexivity still needs actual compilation'})
(evidence/'tail-goals.json').write_text(json.dumps(goals,ensure_ascii=False,indent=2)+'\n')
frag=(H/'proof4/DualTemporal-proof4.lean.inc').read_text();assert base.endswith(frag.encode())
new=frag
for args in ('packetA, h0, h1, h2, ite_true','packetA, h0, h1, ite_true','packetA, h0, ite_true'):
 line='simp only ['+args+']';assert new.count(line+'\n')==1
 new=new.replace(line+'\n',line+' <;> rfl\n',1)
assert new.count('<;> rfl')==frag.count('<;> rfl')+3
def mask(s):
 a=s.index('theorem loop_eq (');b=s.index('@[inline] def runDot ',a);p=s.index(':= by',a)+len(':= by')
 return s[:p]+'<LOOP_EQ_PROOF_BODY>'+s[b:]
assert mask(frag)==mask(new)
prefix=base[:-len(frag.encode())];fixed=prefix+new.encode();assert len(fixed)<256000
assert fixed[:len(prefix)]==prefix and fixed.decode().replace('] <;> rfl\n',']\n')!=base.decode()
out=H/'proof5';out.mkdir(exist_ok=True)
source=out/'Kernel-dual-temporal-a4-proof5.lean';source.write_bytes(fixed)
(out/'DualTemporal-proof5.lean.inc').write_bytes(new.encode())
patch=''.join(difflib.unified_diff(base.decode().splitlines(keepends=True),fixed.decode().splitlines(keepends=True),fromfile='actual-ci12-b92d.lean',tofile='proof5.lean'))
(out/'proof-only.patch').write_bytes(patch.encode())
# Independent inverse unified diff application restores the exact failed CI12 input.
lines=fixed.decode().splitlines(keepends=True);pl=patch.splitlines(keepends=True);i=2;cursor=0;back=[]
while i<len(pl):
 m=re.match(r'@@ -(\d+)(?:,(\d+))? \+(\d+)(?:,(\d+))? @@',pl[i]);assert m
 pos=int(m[3])-(0 if int(m[4] or 1)==0 else 1);back.extend(lines[cursor:pos]);cursor=pos;i+=1
 while i<len(pl) and not pl[i].startswith('@@ '):
  line=pl[i];i+=1
  if line.startswith(' '):assert lines[cursor]==line[1:];back.append(line[1:]);cursor+=1
  elif line.startswith('+'):assert lines[cursor]==line[1:];cursor+=1
  elif line.startswith('-'):back.append(line[1:])
  else:raise ValueError(line)
back.extend(lines[cursor:]);assert ''.join(back).encode()==base
gate=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py';assert sha(gate.read_bytes())=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
tree=ast.parse(gate.read_text());env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
for name in ('OPTIONS','ATTRIBUTES','BANNED'):
 node=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id==name for t in n.targets))
 env[name]=re.compile(ast.literal_eval(node.value.args[0])) if name=='BANNED' else ast.literal_eval(node.value)
fns=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in ('intake','policy','options')]
exec(compile(ast.Module(body=fns,type_ignores=[]),str(gate),'exec'),env)
checks={k:env[k](source,SimpleNamespace(slot='full')) for k in ('intake','policy')};checks['options']=env['options'](fixed.decode());assert all(v is None for v in checks.values())
roots=json.loads((H/'build-receipt.json').read_bytes())['explicit_helper_roots'];assert len(roots)==18
(out/'HelperAudit.lean.inc').write_text('\n'.join('#print axioms '+r for r in roots)+'\n')
manifest={'at_utc':datetime.now(timezone.utc).isoformat(),'feedback_run':40430974047,'source_commit_prefix':'f4211856','failed_source_sha256':sha(base),'original_index_sha256':sha(idxraw),'original_bindings':bindings,'actual_errors':errors,'actual_goal_evidence':'ci-40430974047/tail-goals.json; three tail3/2/1 records have identical printed fields, differing hidden Fin proof detail remains subject to kernel checking','new_source':str(source.relative_to(H)),'new_source_sha256':sha(fixed),'new_source_bytes':len(fixed),'fragment_sha256':sha(new.encode()),'patch_sha256':sha(patch.encode()),'only_change':'Add <;> rfl after the three terminal packetA simplifications; no full-block or zero-tail edits','runtime_domain_all_theorem_statements_and_other_proofs_byte_identical':True,'changed_proof_bodies':['Submission.R19DualTemporal.loop_eq'],'inverse_to_actual_b92d':True,'text_policy':checks,'explicit_helper_roots':roots,'expected_root_count':len(roots),'formal':'NOT_RUN_NEW_PROOF5','codegen':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN','local_Lean':False,'Git':False,'CI_dispatch':False}
(out/'repair-receipt.json').write_text(json.dumps(manifest,indent=2)+'\n')
print(json.dumps({k:manifest[k] for k in ('new_source','new_source_sha256','new_source_bytes','only_change','inverse_to_actual_b92d','text_policy','formal')}))
