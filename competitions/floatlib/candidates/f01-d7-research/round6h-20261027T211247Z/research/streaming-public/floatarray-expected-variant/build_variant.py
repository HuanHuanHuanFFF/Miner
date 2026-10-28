"""Independent expected-word variant; frozen f5a/303a are only read."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,difflib,re,ast
from types import SimpleNamespace
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
RESEARCH=HERE.parents[1]
sha=lambda b:hashlib.sha256(b).hexdigest()
old_path=HERE.parent/'floatarray-storage/Runtime.lean.inc'
old_bytes=old_path.read_bytes();assert sha(old_bytes)=='f5a6cbc6a89ccccd1e08cb861ce483d447d9b8dc30feed21ef24a2f30e5cacf8'
old=old_bytes.decode();new=old
changes=[('Submission.R22FloatArrayB2','Submission.R22FloatArrayB2Expected'),
('    let f0 := ExecFloat.Binary.toFloat32 (B.getD (base + k * p) posZero)',
 '    let raw0 := B.getD (base + k * p) posZero\n    let f0 := ExecFloat.Binary.toFloat32 raw0'),
('      let f1 := ExecFloat.Binary.toFloat32 (B.getD (base + 1 + k * p) posZero)',
 '      let raw1 := B.getD (base + 1 + k * p) posZero\n      let f1 := ExecFloat.Binary.toFloat32 raw1'),
('R22FloatArrayBridgeReview.checkNative f0 d0','R22ExpectedB2Check.check raw0 d0'),
('R22FloatArrayBridgeReview.checkNative f1 d1','R22ExpectedB2Check.check raw1 d1')]
for i,(a,b) in enumerate(changes):
 assert new.count(a)==(2 if i==0 else 1),(i,new.count(a))
 new=new.replace(a,b)
inverse=new
for a,b in reversed(changes):inverse=inverse.replace(b,a)
assert inverse.encode()==old_bytes
new_bytes=new.encode();(HERE/'Runtime.lean.inc').write_bytes(new_bytes)
for name,a,b,fa,fb in [('forward-runtime.patch',old,new,'Runtime-f5a6.lean.inc','Runtime-expected.lean.inc'),
 ('inverse-runtime.patch',new,old,'Runtime-expected.lean.inc','Runtime-f5a6.lean.inc')]:
 (HERE/name).write_text(''.join(difflib.unified_diff(a.splitlines(True),b.splitlines(True),fromfile=fa,tofile=fb)),encoding='utf-8')
base=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
expected_original=HERE.parent/'expected-native-word/ExpectedNativeWord.lean.inc'
eb=expected_original.read_bytes()
assert sha(eb)=='37cd4435b62e306d08923ecca2fc8f9dabb0e39c84a2f8f583e65bbe49ef097f'
# Fixed lexical policy scans this comment as an import declaration. Keep37cd intact.
ea=b'expected native import word';ez=b'expected native readback word'
assert eb.count(ea)==1
ep=eb.replace(ea,ez)
assert ep.replace(ez,ea)==eb
(HERE/'ExpectedNativeWord-policy.lean.inc').write_bytes(ep)
paths=[base,HERE.parent/'PairEmitSizeOnly.lean.inc',RESEARCH/'floatarray-bridge-review/NativeTarget.lean.inc',
 HERE/'ExpectedNativeWord-policy.lean.inc',HERE/'ExpectedCheck.lean.inc',HERE/'Runtime.lean.inc']
blocks=[p.read_bytes() for p in paths]
assert sha(blocks[0])=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert sha(blocks[2])=='fb7d71540db5b0fee7ae9a9b73440b10224713ebd646c4cd812d145c4dfbc1b1'
assert blocks[3]==ep
kernel=b'\n'.join(blocks);assert len(kernel)<256000 and kernel.startswith(blocks[0]);(HERE/'Kernel-probe.lean').write_bytes(kernel)
inverse_kernel=b'\n'.join([*blocks[:3],old_bytes])
assert sha(inverse_kernel)=='303a239716b2521a72093453f7d363553055bc2702f481a09837a6ed53724da1'
# Exact static intake/policy functions; never run the gate or a compiler here.
g=ROOT/'competitions/floatlib/candidates/f01-d7-research/official-policy/gate-4b7e838.raw';gb=g.read_bytes()
assert sha(gb)=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
t=ast.parse(gb);nodes=[n for n in t.body if (isinstance(n,ast.FunctionDef) and n.name in ('intake','options','policy')) or (isinstance(n,ast.Assign) and any(isinstance(v,ast.Name) and v.id in ('OPTIONS','ATTRIBUTES','BANNED') for v in n.targets))]
env={'Path':Path,'re':re,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
module=ast.Module(body=[ast.ImportFrom(module='__future__',names=[ast.alias(name='annotations')],level=0),*nodes],type_ignores=[])
exec(compile(ast.fix_missing_locations(module),'pinned-static-functions','exec'),env)
policy={n:env[n](HERE/'Kernel-probe.lean',SimpleNamespace(slot='full')) for n in ['intake','policy']};assert all(v is None for v in policy.values()),policy
roots=['Submission.add_spec','Submission.mul_spec','Submission.sum_spec','Submission.bmm_spec','Submission.R21StreamingPair.emit_size']
roots+=['Submission.R22FloatArrayBridgeReview.'+n for n in ['checked_import','checked_native','checked_convert']]
roots+=['Submission.R22ExpectedNativeWord.'+n for n in ['canonical_nan_raw','import_raw_eq_expected','checkNative_eq_expected']]
roots+=['Submission.R22ExpectedB2Check.check_eq_native']
roots+=['Submission.R22FloatArrayB2Expected.'+n for n in ['push_size','group_size','row_size','output_size']]
(HERE/'HelperAudit.lean.inc').write_text(''.join('#print axioms '+n+'\n' for n in roots),encoding='utf-8')
def record(p):
 b=p.read_bytes();return dict(path=str(p.relative_to(ROOT)),bytes=len(b),sha256=sha(b))
out=dict(created_at_utc=datetime.now(timezone.utc).isoformat(),phase_start_utc='2026-10-28T02:11:13Z',
 phase_limit_utc='2026-10-28T02:21:13Z',shared_deadline_utc='2026-10-28T03:12:47Z',
 source=record(HERE/'Kernel-probe.lean'),runtime=record(HERE/'Runtime.lean.inc'),check=record(HERE/'ExpectedCheck.lean.inc'),
 dependencies=[record(p) for p in paths[:-2]],expected_original=record(expected_original),
 expected_comment_only_policy_projection=dict(old_text=ea.decode(),new_text=ez.decode(),exact_inverse_sha256=sha(ep.replace(ez,ea))),
 callback='Submission.R22FloatArrayB2Expected.guarded',
 helper_audit_roots=roots,root_count=len(roots),public_bmm_still='Original622d Submission.bmm; new callback has no public bmm_spec',
 raw_binding_counts=dict(old_field_getD_sites=2,new_field_getD_sites=2,old_field_decode_sites=2,new_field_decode_sites=2),
 exact_inverse_runtime_sha256=sha(inverse.encode()),exact_inverse_kernel_sha256=sha(inverse_kernel),
 only_runtime_changes='Namespace plus naming existing raw read before one decode; check uses raw expected-word target. All remaining producer, layout, loop, size/writer/guard/odd/fallback bytes inverse-identical.',
 check_equivalence='check_eq_native uses37cd full Bool equality for any stored value; NOT_RUN',
 policy_preflight=policy,formal='NOT_RUN',native_cost='UNKNOWN',actual_codegen='UNKNOWN',CI=False,
 frozen_parent_modified=False,confirmation_inputs_read=False,
 cost_scope='One source-side toBits expression removed per stored field; actual CSE/FFI/calls/spills/time UNKNOWN. No inherited measurement fromf5a/303a.')
(HERE/'manifest.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:out[k] for k in ['created_at_utc','source','runtime','check','root_count','formal','policy_preflight']},ensure_ascii=False))
