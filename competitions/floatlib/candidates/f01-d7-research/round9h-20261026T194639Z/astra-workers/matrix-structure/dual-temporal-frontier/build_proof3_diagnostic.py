"""A single-branch goal/equation diagnostic from actual d765 failure; NOT a repair."""
from pathlib import Path
from datetime import datetime,timezone
from types import SimpleNamespace
import hashlib,json,re,ast,difflib
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
sha=lambda b:hashlib.sha256(b).hexdigest()
run=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40420540388'
idxraw=(run/'original-artifact-hashes.json').read_bytes()
idx=json.loads(idxraw);root=run/idx['directory']
suite=root/'diagnostics/f01-d7-public-suite/public-suite'
diag=suite/'diagnostics/f01-r19-dev-dual-temporal-a4-2'
evidence=H/'ci-40420540388';evidence.mkdir(exist_ok=True)
files=[suite/'inputs/f01-r19-dev-dual-temporal-a4-2/Kernel.lean',
 suite/'f01-r19-dev-dual-temporal-a4-2-verdict.json',diag/'full-build-output.txt',diag/'replay.log',diag/'index.json']
bindings=[]
for p in files:
 raw=p.read_bytes();record=idx['files'][p.relative_to(root).as_posix()]
 assert sha(raw)==record['sha256'] and len(raw)==record['bytes']
 name='input-d765.lean' if p.name=='Kernel.lean' else p.name
 (evidence/name).write_bytes(raw)
 bindings.append({'original':str(p.relative_to(R)),'copy':str((evidence/name).relative_to(H)),'sha256':sha(raw),'bytes':len(raw)})
(evidence/'original-artifact-hashes.json').write_bytes(idxraw)
base=(H/'proof2/Kernel-dual-temporal-a4-proof2.lean').read_bytes()
assert sha(base)=='d765bd41234a26640eaa6df6c7134e0d4d8dca760e50eaef3aa82eff1fac0847'
assert files[0].read_bytes()==base
verdict=json.loads(files[1].read_bytes());assert verdict['stage']=='statement' and verdict['passed'] is False
build=files[2].read_text()
errors=re.findall(r'^error: work/Submission.lean:(\d+):(\d+): (.*)$',build,re.M)
assert errors==[(str(l),str(c),'Failed to rewrite using equation theorems for `loop`') for l,c in [(6751,8),(6761,14),(6766,14),(6771,12),(6776,10)]]
capture=json.loads((diag/'index.json').read_bytes())
assert capture['generated_c']==[] and capture['replay_exit_code']==1
frag=(H/'proof2/DualTemporal-proof2.lean.inc').read_text()
assert base.endswith(frag.encode())
a=frag.index('theorem loop_eq (');b=frag.index('@[inline] def runDot ',a)
old=frag[a:b]
needle='    rw [loop]\n    conv_rhs => unfold R19Temporal.loop\n'
assert old.count(needle)==1
probe='''    -- Diagnostic P3: exact failing target and explicit one-step equations, first branch only.
    trace_state
    have dual_p3_new_eq :=
      @Submission.R19DualTemporal.loop.eq_def n basePacket A B hA t s0 s1
    have dual_p3_old_eq :=
      @Submission.R19Temporal.loop.eq_def n baseA Araw B t s0 s1
    trace_state
    rw [dual_p3_new_eq]
    trace_state
    conv_rhs => unfold R19Temporal.loop
'''
new=old.replace(needle,probe,1)
# Four other branch proof bodies, including their original failing rw, are exact bytes.
tail='  · by_cases h0 : 4*t<n\n'
assert new[new.index(tail):]==old[old.index(tail):]
assert new.count('rw [loop]')==4
fixedfrag=frag[:a]+new+frag[b:]
prefix=base[:-len(frag.encode())];fixed=prefix+fixedfrag.encode()
def mask(s):
 a=s.index('theorem loop_eq (');b=s.index('@[inline] def runDot ',a)
 p=s.index(':= by',a)+len(':= by')
 return s[:p]+'<LOOP_EQ_PROOF_BODY>'+s[b:]
assert mask(frag)==mask(fixedfrag)
assert len(fixed)<256000 and fixed[:len(prefix)]==prefix
out=H/'proof3-diagnostic';out.mkdir(exist_ok=True)
source=out/'Kernel-dual-temporal-a4-proof3-diagnostic.lean'
source.write_bytes(fixed)
(out/'DualTemporal-proof3-diagnostic.lean.inc').write_bytes(fixedfrag.encode())
patch=''.join(difflib.unified_diff(base.decode().splitlines(keepends=True),fixed.decode().splitlines(keepends=True),fromfile='failed-d765.lean',tofile='proof3-diagnostic.lean'))
(out/'proof-only.patch').write_bytes(patch.encode())
# Apply the inverse independently and recover the exact failed d765 source.
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
upstream=out/'compiler-originals';provenance=json.loads((upstream/'provenance.json').read_bytes())
for item in provenance:
 data=(upstream/item['name']).read_bytes()
 # apply_patch preserves source text but may append a final blank line; retain that fact.
 candidates=[data,data[:-1]] if data.endswith(b'\n\n') else [data]
 matched=next((raw for raw in candidates if hashlib.sha1(b'blob '+str(len(raw)).encode()+b'\0'+raw).hexdigest()==item['sha1_git_blob']),None)
 assert matched is not None,(item['name'],item['sha1_git_blob'])
 if matched!=data:(upstream/item['name']).write_bytes(matched)
 item['sha256']=sha(matched);item['bytes']=len(matched)
(upstream/'verified-provenance.json').write_text(json.dumps(provenance,indent=2)+'\n')
roots=json.loads((H/'build-receipt.json').read_bytes())['explicit_helper_roots']
manifest={'at_utc':datetime.now(timezone.utc).isoformat(),'purpose':'DIAGNOSTIC_ONLY; preserve four red branches; obtain exact target/equation evidence, not a passing or performance candidate','failed_run':40420540388,'failed_source_sha256':sha(base),'original_index_sha256':sha(idxraw),'original_bindings':bindings,'actual_errors':errors,'failed_scope':'loop_eq only; group_eq no longer reports error; statement failed, 18-root audit/replay/C/ASM NOT_RUN','new_source':str(source.relative_to(H)),'new_source_sha256':sha(fixed),'new_source_bytes':len(fixed),'fragment_sha256':sha(fixedfrag.encode()),'patch_sha256':sha(patch.encode()),'runtime_domain_all_theorem_statements_and_other_proofs_byte_identical':True,'unchanged_prefix_bytes':len(prefix),'changed_proof_bodies':['Submission.R19DualTemporal.loop_eq FIRST BRANCH ONLY'],'four_tail_branches_byte_identical':True,'inverse_to_failed_d765':True,'text_policy':checks,'explicit_helper_roots':roots,'expected_root_count':len(roots),'root_cause':'UNKNOWN: bare-identifier rewrite hides inner error; supplied pinned compiler explains absent goals, not alias failure','probe':'trace target; instantiate fully qualified new/old eq_def; trace equations; rewrite only first branch with explicit new equality; trace residual target','formal':'NOT_RUN_DIAGNOSTIC_EXPECTS_FOUR_OLD_ERRORS','codegen':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN','local_Lean':False,'Git':False,'CI_dispatch':False}
(out/'diagnostic-receipt.json').write_text(json.dumps(manifest,indent=2)+'\n')
print(json.dumps({k:manifest[k] for k in ('purpose','new_source','new_source_sha256','new_source_bytes','four_tail_branches_byte_identical','runtime_domain_all_theorem_statements_and_other_proofs_byte_identical','inverse_to_failed_d765','text_policy','formal')}))
