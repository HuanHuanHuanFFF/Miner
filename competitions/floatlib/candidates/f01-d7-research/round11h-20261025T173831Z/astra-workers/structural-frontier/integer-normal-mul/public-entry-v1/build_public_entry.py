"""Wire the existing numeric core to the actual public MUL without touching frozen inputs."""
from pathlib import Path
from types import SimpleNamespace
from datetime import datetime,timezone
import ast,hashlib,json,re
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
sha=lambda b:hashlib.sha256(b).hexdigest()
parent=H.parent/'Probe-numeric-mul-public-bridge-v2.lean'
old=parent.read_bytes();assert sha(old)=='365f49b1180bae24f217e83089e7a70e71bea6e22696f0b2197a11dac6e7871e'
assert re.search(rb'\bR18\b',old) is None
occurrences=[m.start() for m in re.finditer(rb'\bSubmission\b',old)]
body=re.sub(rb'\bSubmission\b',b'R18',old)
assert len(occurrences)==98 and re.sub(rb'\bR18\b',b'Submission',body)==old
wrapper='''
namespace Submission
open FloatLib.Floats Competition

@[inline] def add := R18.add
theorem add_spec : ∀ x y : Binary32, add x y = ExecFloat.Spec.add x y := R18.add_spec

@[inline] def mul (x y : Binary32) : Binary32 :=
  R18.R17NumericMulInteger.guardedMul R18.mul x y
theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y :=
  R18.R18NumericMulSpec.guardedMul_spec R18.mul R18.mul_spec x y

@[inline] def sum {n : Nat} (x : Vector Binary32 n) : Binary32 := R18.sum x
theorem sum_spec : ∀ (n : Nat) (x : Vector Binary32 n), sum x = sumSpec x.get := R18.sum_spec

@[inline] def bmm := R18.bmm
theorem bmm_spec : ∀ (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := R18.bmm_spec

end Submission
'''.encode()
data=body+wrapper
assert len(data)<=256000,(len(data),len(wrapper))
out=H/'Kernel.lean';out.write_bytes(data)
assert b'\r' not in data and out.read_text().encode()==data
assert re.findall(rb'^import\s+([^\r\n]+)',data,re.M)==[b'ContractTensor']
assert re.findall(rb'^namespace Submission\s*$',data,re.M)==[b'namespace Submission']
# Runtime fallback graph cannot refer back to the new public namespace.
assert b'Submission' not in body
assert b'guardedMul R18.mul x y' in wrapper
assert b'guardedMul_spec R18.mul R18.mul_spec x y' in wrapper
for name in ('add','sum','bmm'):
 assert ('R18.'+name).encode() in wrapper
gate=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
assert sha(gate.read_bytes())=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
t=ast.parse(gate.read_text());env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
for name in ('OPTIONS','ATTRIBUTES','BANNED'):
 n=next(n for n in t.body if isinstance(n,ast.Assign) and any(isinstance(x,ast.Name) and x.id==name for x in n.targets))
 env[name]=re.compile(ast.literal_eval(n.value.args[0])) if name=='BANNED' else ast.literal_eval(n.value)
fs=[n for n in t.body if isinstance(n,ast.FunctionDef) and n.name in ('intake','policy','options')]
exec(compile(ast.Module(body=fs,type_ignores=[]),str(gate),'exec'),env)
checks={k:env[k](out,SimpleNamespace(slot='full')) for k in ('intake','policy')};checks['options']=env['options'](out.read_text())
assert all(x is None for x in checks.values()),checks
pm=json.loads((H.parent/'public-probe-v2-manifest.json').read_text())
roots=[re.sub(r'^Submission\.', 'R18.', x) for x in pm['public_roots']]
assert len(roots)==63 and len(set(roots))==63
audit=H/'HelperAudit.lean.inc';audit.write_bytes((''.join('#print axioms '+x+'\n' for x in roots)).encode())
manifest=dict(created_utc=datetime.now(timezone.utc).isoformat(),state='TRUE_PUBLIC_MUL_ENTRY_WIRED_NOT_COMPILED',
 parent=dict(path=str(parent.relative_to(R)),sha256=sha(old),bytes=len(old)),
 candidate=dict(path='Kernel.lean',sha256=sha(data),bytes=len(data),margin=256000-len(data)),
 edits=[dict(kind='whole-identifier namespace mapping',old='Submission',new='R18',occurrences=len(occurrences),
  original_byte_offsets=occurrences,saved_bytes=len(old)-len(body),exact_inverse=True),
  dict(kind='append explicit public aliases and new MUL/spec',bytes=len(wrapper),sha256=sha(wrapper))],
 new_proof_deletions=[],inherited_proof_leaf_plan='../byte-budget-preview.json',
 public_mapping={'add':'R18.add','mul':'R18.R17NumericMulInteger.guardedMul R18.mul',
  'mul_spec':'R18.R18NumericMulSpec.guardedMul_spec R18.mul R18.mul_spec',
  'sum':'R18.sum with original implicit n','bmm':'R18.bmm'},
 fallback='Exact former B2 MUL under R18.mul; old body cannot reference new Submission namespace',
 unchanged_computation='All previous bodies differ only by the injective namespace mapping; add/sum/bmm public wrappers inline the original implementations',
 actual_callback_and_performance='NOT_RUN; wrapper/renaming codegen still needs original full gate and selected MainFull confirmation',
 helper_roots=roots,audit=dict(path=audit.name,sha256=sha(audit.read_bytes()),bytes=audit.stat().st_size),
 static_checks=checks,canonical_LF=True,source_byte_check=True,old_source_preserved=sha(parent.read_bytes())==sha(old),
 not_run=['Lean elaboration','New63-helper replay/dependency audit','Full gate','C/ASM for this source','Performance'],
 CI=False,Git=False,local_Lean=False)
(H/'manifest.json').write_bytes((json.dumps(manifest,indent=2)+'\n').encode())
print(json.dumps(dict(candidate=manifest['candidate'],namespace_saved=len(old)-len(body),wrapper_bytes=len(wrapper),checks=checks,helper_roots=len(roots))))
