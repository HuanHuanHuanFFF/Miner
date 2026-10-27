"""Actual peer heartbeat failure: factor midpoint proofs, preserve original interfaces/options."""
from pathlib import Path
from datetime import datetime,timezone
from types import SimpleNamespace
import hashlib,json,re,difflib,ast
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
sha=lambda b:hashlib.sha256(b).hexdigest()
run=Path('D:/CodingProject/Bitget-DeepSeek/competitions/floatlib/research/deepseek-20261025/ci-runs/40429425157')
idxraw=(run/'original-artifact-hashes.json').read_bytes();idx=json.loads(idxraw);root=run/idx['directory']
candidate='f01-deepseek-peercheck-jam-probe';diag=root/'diagnostics'/candidate
out=H/'low-state-repair1';evidence=out/'ci-40429425157';evidence.mkdir(exist_ok=True)
files=[root/'inputs'/candidate/'Kernel.lean',root/(candidate+'-verdict.json'),root/(candidate+'-manifest.json'),diag/'full-build-output.txt',diag/'replay.log',diag/'index.json']
bindings=[]
for p in files:
 raw=p.read_bytes();rec=idx['files'][p.relative_to(root).as_posix()]
 assert sha(raw)==rec['sha256'] and len(raw)==rec['bytes']
 name='input-5d0f.lean' if p.name=='Kernel.lean' else p.name
 (evidence/name).write_bytes(raw)
 bindings.append({'original':str(p),'copy':str((evidence/name).relative_to(out)),'sha256':sha(raw),'bytes':len(raw)})
(evidence/'original-artifact-hashes.json').write_bytes(idxraw)
base=files[0].read_bytes();assert sha(base)=='5d0f2e8b1cef4927b0145e3579903d0795679ae722cb1b1ac645c29f6d3ca5bc'
oldfrag=(H/'JamVariable.lean').read_bytes();assert sha(oldfrag)=='a78a153405a2b4a5fd29ac704d77114a8f650ac6120591700f4d2ad05afe5595'
assert sha((H/'JamTranslate.lean.inc').read_bytes())=='c9e0cfb3b59f7eb45f8c5cdc281eb54b4598b080c2c43aae100e04df12237542'
build=files[3].read_text();assert '6618:0: (deterministic) timeout at `whnf`' in build and 'heartbeats (200000)' in build
assert "6629:8: (kernel) unknown constant 'R19JamVariableProbe.low_states'" in build
verdict=json.loads(files[1].read_bytes());assert verdict['stage']=='statement' and verdict['passed'] is False
newblock=(out/'LowStates-replacement.lean.inc').read_text()
start='/-- Exactly 4+8+16 low states.';end='/-- The variable divisor is handled'
def replace(s):
 a=s.index(start);b=s.index(end,a);old=s[a:b]
 oldstmt=old[old.index('theorem low_states'):old.index(':= by')]
 ns=newblock[newblock.index('theorem low_states'):];newstmt=ns[:ns.index(':= by')]
 assert oldstmt==newstmt
 return s[:a]+newblock+'\n'+s[b:],old
newfrag,oldblock=replace(oldfrag.decode());full,oldfullblock=replace(base.decode());assert oldblock==oldfullblock
fullbytes=full.encode();fragbytes=newfrag.encode()
b2=(R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes()
assert sha(b2)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert base[:len(b2)]==fullbytes[:len(b2)]==b2
assert full.replace(newblock+'\n',oldblock,1).encode()==base
assert newfrag.replace(newblock+'\n',oldblock,1).encode()==oldfrag
assert len(fullbytes)<256000
assert not re.search(r'\b(sorry|admit|axiom|unsafe|set_option)\b',newblock)
assert 'interval_cases' not in newblock and 'split_ifs' not in newblock
source=out/'Probe-jam-variable-repair1.lean';source.write_bytes(fullbytes)
(out/'JamVariable-repair1.lean').write_bytes(fragbytes)
patch=''.join(difflib.unified_diff(base.decode().splitlines(keepends=True),full.splitlines(keepends=True),fromfile='actual-peer-5d0f.lean',tofile='jam-variable-repair1.lean'))
(out/'proof-resource-only.patch').write_bytes(patch.encode())
# Inverse unified diff, independent of the replacement construction.
lines=full.splitlines(keepends=True);pl=patch.splitlines(keepends=True);i=2;cursor=0;back=[]
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
checks={k:env[k](source,SimpleNamespace(slot='full')) for k in ('intake','policy')};checks['options']=env['options'](full)
assert all(v is None for v in checks.values())
roots=['Submission.'+n+'_spec' for n in ('add','mul','sum','bmm')]+['R19JamVariableProbe.'+n for n in re.findall(r'^theorem (\w+)',newfrag,re.M)]
assert len(roots)==15
(out/'HelperAudit.lean.inc').write_text('\n'.join('#print axioms '+r for r in roots)+'\n')
manifest={'at_utc':datetime.now(timezone.utc).isoformat(),'failed_run':40429425157,'failed_commit':'38df646a','failed_source_sha256':sha(base),'failed_source_bytes':len(base),'original_bindings':bindings,'original_index_sha256':sha(idxraw),'failure':'low_states whnf heartbeat200000; later unknown constant is downstream','mechanism':'Replace 28 conjunction/if case proof with six small helpers and below/equal/above even-midpoint decisions. Three literal H=2/4/8 instantiations preserve the original low_states statement.','source':source.name,'source_sha256':sha(fullbytes),'source_bytes':len(fullbytes),'fragment':'JamVariable-repair1.lean','fragment_sha256':sha(fragbytes),'fragment_bytes':len(fragbytes),'B2_prefix_bytes':len(b2),'B2_prefix_sha256':sha(b2),'original_main_theorem_statements_unchanged':True,'all_runtime_definitions_and_public_algorithms_unchanged':True,'options_unchanged':True,'old_a78_and_c9_frozen':True,'inverse_patch_to_original_5d0f':True,'patch_sha256':sha(patch.encode()),'roots':roots,'root_count':len(roots),'text_checks':checks,'formal':'NOT_RUN_NEW_REPAIR','full_gate':'NOT_RUN_MATH_PROBE_ONLY','performance':'NOT_APPLICABLE_PUBLIC_RUNTIME_B2','local_Lean':False,'CI_dispatch':False,'Git':False,'next':'One exact proof-resource retry on peer if window allows; no option increase and no added runtime branch.'}
(out/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
print(json.dumps({k:manifest[k] for k in ('source','source_sha256','source_bytes','fragment_sha256','fragment_bytes','root_count','text_checks','formal')}))
