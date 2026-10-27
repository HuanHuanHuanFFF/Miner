"""Propagate CI11's successful explicit equation pattern; proof body only."""
from pathlib import Path
from datetime import datetime,timezone
from types import SimpleNamespace
import hashlib,json,re,ast,difflib
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
sha=lambda b:hashlib.sha256(b).hexdigest()
run=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40428306094'
idxraw=(run/'original-artifact-hashes.json').read_bytes()
idx=json.loads(idxraw);root=run/idx['directory']
suite=root/'diagnostics/f01-d7-public-suite/public-suite'
candidate='f01-r19-dev-dual-equation-diagnostic1';diag=suite/'diagnostics'/candidate
evidence=H/'ci-40428306094';evidence.mkdir(exist_ok=True)
files=[suite/'inputs'/candidate/'Kernel.lean',suite/(candidate+'-verdict.json'),
 diag/'full-build-output.txt',diag/'replay.log',diag/'index.json']
bindings=[]
for p in files:
 raw=p.read_bytes();record=idx['files'][p.relative_to(root).as_posix()]
 assert sha(raw)==record['sha256'] and len(raw)==record['bytes']
 name='input-c598.lean' if p.name=='Kernel.lean' else p.name
 (evidence/name).write_bytes(raw)
 bindings.append({'original':str(p.relative_to(R)),'copy':str((evidence/name).relative_to(H)),'sha256':sha(raw),'bytes':len(raw)})
(evidence/'original-artifact-hashes.json').write_bytes(idxraw)
base=(H/'proof3-diagnostic/Kernel-dual-temporal-a4-proof3-diagnostic.lean').read_bytes()
assert sha(base)=='c5981413680244f3d93d79a372a09b36dcbe22028a942b8a35fd2cd18d5f0cf7'
assert files[0].read_bytes()==base
verdict=json.loads(files[1].read_bytes());assert verdict['stage']=='statement' and verdict['passed'] is False
build=files[2].read_text()
errors=re.findall(r'^error: work/Submission.lean:(\d+):(\d+): (.*)$',build,re.M)
assert errors==[(str(l),str(c),'Failed to rewrite using equation theorems for `loop`') for l,c in [(6769,14),(6774,14),(6779,12),(6784,10)]]
for line in (6752,6757,6759):assert f'info: work/Submission.lean:{line}:4: case pos' in build
assert 'B : Vector R19Temporal.B8 ((n + 3) / 4)' in build
assert 'dual_p3_new_eq :' in build and 'dual_p3_old_eq :' in build
assert '⊢ (let k := 4 * t;' in build
capture=json.loads((diag/'index.json').read_bytes());assert capture['generated_c']==[] and capture['replay_exit_code']==1
start=build.index('info: work/Submission.lean:6752:4: case pos')
end=build.index('warning: work/Submission.lean:6825:50:',start)
(evidence/'trace-targets.txt').write_text(build[start:end])
frag=(H/'proof3-diagnostic/DualTemporal-proof3-diagnostic.lean.inc').read_text()
assert base.endswith(frag.encode())
a=frag.index('theorem loop_eq (');b=frag.index('@[inline] def runDot ',a)
old=frag[a:b]
# Preserve exactly the successful first-branch equation pattern, including old_eq.
assert old.count('trace_state')==3 and old.count('rw [loop]')==4
new=re.sub(r'(?m)^    -- Diagnostic P3:.*\n','',old)
new=re.sub(r'(?m)^    trace_state\n','',new)
bridge='''have dual_p3_new_eq :=
  @Submission.R19DualTemporal.loop.eq_def n basePacket A B hA t s0 s1
have dual_p3_old_eq :=
  @Submission.R19Temporal.loop.eq_def n baseA Araw B t s0 s1
rw [dual_p3_new_eq]'''
first_block='\n'.join('    '+x for x in bridge.splitlines())
assert first_block in new
def extend(m):
 indent,bullet=m[1],m[2] or ''
 cont=indent+('  ' if bullet else '')
 parts=bridge.splitlines()
 return indent+bullet+parts[0]+'\n'+'\n'.join(cont+x for x in parts[1:])
new=re.sub(r'(?m)^([ \t]*)(· )?rw \[loop\]$',extend,new)
assert 'trace_state' not in new and 'rw [loop]' not in new
for text in ('have dual_p3_new_eq :=','have dual_p3_old_eq :=','rw [dual_p3_new_eq]',
             'conv_rhs => unfold R19Temporal.loop'):
 assert new.count(text)==5,text
# Everything after each equation step is unchanged; no new tail arithmetic or domain.
strip=lambda s:re.sub(r'(?m)^\s*(?:· )?(?:have dual_p3_(?:new|old)_eq :=|@Submission\.R19(?:Dual)?Temporal\.loop\.eq_def.*|rw \[(?:loop|dual_p3_new_eq)\]|trace_state|-- Diagnostic P3:.*)\n','',s)
assert strip(old)==strip(new)
fixedfrag=frag[:a]+new+frag[b:]
prefix=base[:-len(frag.encode())];fixed=prefix+fixedfrag.encode()
def mask(s):
 a=s.index('theorem loop_eq (');b=s.index('@[inline] def runDot ',a)
 p=s.index(':= by',a)+len(':= by')
 return s[:p]+'<LOOP_EQ_PROOF_BODY>'+s[b:]
assert mask(frag)==mask(fixedfrag)
proof2=(H/'proof2/Kernel-dual-temporal-a4-proof2.lean').read_text()
assert mask(base.decode())==mask(fixed.decode())==mask(proof2)
assert len(fixed)<256000 and fixed[:len(prefix)]==prefix
out=H/'proof4';out.mkdir(exist_ok=True)
source=out/'Kernel-dual-temporal-a4-proof4.lean';source.write_bytes(fixed)
(out/'DualTemporal-proof4.lean.inc').write_bytes(fixedfrag.encode())
patch=''.join(difflib.unified_diff(base.decode().splitlines(keepends=True),fixed.decode().splitlines(keepends=True),fromfile='actual-ci11-c598.lean',tofile='proof4.lean'))
(out/'proof-only.patch').write_bytes(patch.encode())
# Independent inverse unified-patch application to recover the exact diagnostic input.
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
gate=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
assert sha(gate.read_bytes())=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
tree=ast.parse(gate.read_text());env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
for name in ('OPTIONS','ATTRIBUTES','BANNED'):
 node=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id==name for t in n.targets))
 env[name]=re.compile(ast.literal_eval(node.value.args[0])) if name=='BANNED' else ast.literal_eval(node.value)
fns=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in ('intake','policy','options')]
exec(compile(ast.Module(body=fns,type_ignores=[]),str(gate),'exec'),env)
checks={k:env[k](source,SimpleNamespace(slot='full')) for k in ('intake','policy')};checks['options']=env['options'](fixed.decode())
assert all(v is None for v in checks.values())
roots=json.loads((H/'build-receipt.json').read_bytes())['explicit_helper_roots']
manifest={'at_utc':datetime.now(timezone.utc).isoformat(),'actual_feedback_run':40428306094,
 'source_commit':'a92abea11a0a21e76df44a1a93114801dd3085a8','diagnostic_source_sha256':sha(base),
 'original_index_sha256':sha(idxraw),'original_bindings':bindings,'actual_errors':errors,
 'verified_diagnostic_change':'First branch explicit new/old eq_def instantiate; new equality rewrites LHS; no first-branch error. Four untouched bare-rw tails remain red. Module not accepted.',
 'root_cause_boundary':'Implicit equation selection/instantiation fails while fully instantiated eq_def succeeds on the same normalized dependent target. Exact internal alias/transparency subcause not separately isolated.',
 'new_source':str(source.relative_to(H)),'new_source_sha256':sha(fixed),'new_source_bytes':len(fixed),
 'fragment_sha256':sha(fixedfrag.encode()),'patch_sha256':sha(patch.encode()),
 'runtime_domain_all_theorem_statements_and_other_proofs_byte_identical':True,
 'masked_equal_to_d765_and_c598':True,'changed_proof_bodies':['Submission.R19DualTemporal.loop_eq'],
 'first_branch_pattern_preserved_except_trace_removal':True,'four_tail_branches_use_exact_same_pattern':True,
 'inverse_to_actual_c598':True,'text_policy':checks,'explicit_helper_roots':roots,'expected_root_count':len(roots),
 'formal':'NOT_RUN_NEW_PROOF4','codegen':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN',
 'local_Lean':False,'Git':False,'CI_dispatch':False}
(out/'repair-receipt.json').write_text(json.dumps(manifest,indent=2)+'\n')
print(json.dumps({k:manifest[k] for k in ('new_source','new_source_sha256','new_source_bytes','changed_proof_bodies','masked_equal_to_d765_and_c598','inverse_to_actual_c598','text_policy','formal')}))
