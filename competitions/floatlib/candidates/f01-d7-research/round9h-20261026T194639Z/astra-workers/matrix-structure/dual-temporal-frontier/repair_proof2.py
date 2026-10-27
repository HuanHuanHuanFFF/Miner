"""Exact first compiler feedback: proof-only repair copy, never overwrites9a5/D artifacts."""
from pathlib import Path
from datetime import datetime,timezone
from types import SimpleNamespace
import hashlib,json,re,ast,difflib
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
sha=lambda b:hashlib.sha256(b).hexdigest()
run=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40410895344'
idx=json.loads((run/'original-artifact-hashes.json').read_bytes());root=run/idx['directory']
suite=root/'diagnostics/f01-d7-public-suite/public-suite'
diag=suite/'diagnostics/f01-r19-dev-dual-temporal-a4-1'
evidence=H/'ci-40410895344';evidence.mkdir(exist_ok=True)
bindings=[]
files=[suite/'inputs/f01-r19-dev-dual-temporal-a4-1/Kernel.lean',
 suite/'f01-r19-dev-dual-temporal-a4-1-verdict.json',diag/'full-build-output.txt',diag/'replay.log',diag/'index.json']
for p in files:
 raw=p.read_bytes();record=idx['files'][p.relative_to(root).as_posix()]
 assert sha(raw)==record['sha256'] and len(raw)==record['bytes']
 name='input-9a5.lean' if p.name=='Kernel.lean' else p.name
 (evidence/name).write_bytes(raw)
 bindings.append({'original':str(p.relative_to(R)),'copy':str((evidence/name).relative_to(H)),'sha256':sha(raw),'bytes':len(raw)})
base=(H/'Kernel-dual-temporal-a4.lean').read_bytes()
assert sha(base)=='9a5f19bea40d607de2e491aa45ab2deaac8fb68ea34a939817380eb7b362f4de'
assert files[0].read_bytes()==base
verdict=json.loads(files[1].read_bytes());assert verdict['stage']=='statement' and verdict['passed'] is False
build=files[2].read_text();assert build.count('Failed to rewrite using equation theorems for `R19Temporal.loop`')==5
assert 'work/Submission.lean:6810:59: unsolved goals' in build
capture=json.loads((diag/'index.json').read_bytes());assert capture['generated_c']==[] and capture['replay_exit_code']==1
original_frag=(H/'DualTemporal.lean.inc').read_text()
assert base.endswith(original_frag.encode())
def bounds(s,start,end):
 a=s.index(start);b=s.index(end,a);return a,b
la,lb=bounds(original_frag,'theorem loop_eq (','@[inline] def runDot ')
ga,gb=bounds(original_frag,'theorem group_eq (','@[inline] def row ')
old_loop=original_frag[la:lb];old_group=original_frag[ga:gb]
new_loop=old_loop.replace(':= by\n  by_cases h3',':= by\n  unfold blocks at *\n  by_cases h3',1)
assert new_loop!=old_loop and new_loop.count('rw [loop, R19Temporal.loop]')==5
# Direct the old recursive definition's unfolding at its actual RHS, after normalizing its length alias.
def directional(m):
 indent,bullet=m[1],m[2] or ''
 return indent+bullet+'rw [loop]\n'+indent+('  ' if bullet else '')+'conv_rhs => unfold R19Temporal.loop'
new_loop=re.sub(r'(?m)^([ \t]*)(· )?rw \[loop, R19Temporal\.loop\]$',directional,new_loop)
assert 'rw [loop, R19Temporal.loop]' not in new_loop
assert new_loop.count('conv_rhs => unfold R19Temporal.loop')==5
new_group=old_group.replace('  simp only [group, R19Temporal.group, runDot_eq]\n',
 '  simp only [group, R19Temporal.group, runDot_eq] <;> rfl\n',1)
assert new_group!=old_group
fixed_frag=original_frag[:la]+new_loop+original_frag[lb:ga]+new_group+original_frag[gb:]
def masked(s):
 for first,last in [('theorem group_eq (','@[inline] def row '),('theorem loop_eq (','@[inline] def runDot ')]:
  a,b=bounds(s,first,last);proof=s.index(':= by',a)+len(':= by')
  assert proof<b
  s=s[:proof]+'<PROOF_BODY>'+s[b:]
 return s
assert masked(original_frag)==masked(fixed_frag)
prefix=base[:-len(original_frag.encode())]
fixed=prefix+fixed_frag.encode()
assert len(fixed)<256000 and fixed[:len(prefix)]==prefix
out=H/'proof2';out.mkdir(exist_ok=True)
source=out/'Kernel-dual-temporal-a4-proof2.lean';source.write_bytes(fixed)
(out/'DualTemporal-proof2.lean.inc').write_bytes(fixed_frag.encode())
patch=''.join(difflib.unified_diff(base.decode().splitlines(keepends=True),fixed.decode().splitlines(keepends=True),fromfile='original-9a5.lean',tofile='proof2.lean'))
(out/'proof-only.patch').write_bytes(patch.encode())
# Independently reverse the unified diff and recover the exact failed source.
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
manifest={'at_utc':datetime.now(timezone.utc).isoformat(),'failed_run':40410895344,'failed_source_sha256':sha(base),'original_bindings':bindings,'failed_scope':'Only two proof declarations: five R19Temporal.loop equation-unfolding failures plus one group_eq definitional closure; statement failed, 18-root audit/replay/C/ASM NOT_RUN','new_source':str(source.relative_to(H)),'new_source_sha256':sha(fixed),'new_source_bytes':len(fixed),'fragment_sha256':sha(fixed_frag.encode()),'patch_sha256':sha(patch.encode()),'runtime_and_domain_and_all_theorem_statements_byte_identical':True,'unchanged_prefix_bytes':len(prefix),'changed_proof_bodies':['Submission.R19DualTemporal.loop_eq','Submission.R19DualTemporal.group_eq'],'inverse_to_failed_9a5':True,'text_policy':checks,'explicit_helper_roots':roots,'expected_root_count':len(roots),'hypothesis':'Normalize blocks length alias in proof context; directionally unfold old recursive RHS; use kernel definitional reflexivity for remaining identical group expression. Real compiler result required.','formal':'NOT_RUN','codegen':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN','local_Lean':False,'Git':False,'CI_dispatch':False}
(out/'repair-receipt.json').write_text(json.dumps(manifest,indent=2)+'\n')
print(json.dumps({k:manifest[k] for k in ('failed_scope','new_source','new_source_sha256','new_source_bytes','changed_proof_bodies','runtime_and_domain_and_all_theorem_statements_byte_identical','inverse_to_failed_9a5','text_policy','formal')}))
