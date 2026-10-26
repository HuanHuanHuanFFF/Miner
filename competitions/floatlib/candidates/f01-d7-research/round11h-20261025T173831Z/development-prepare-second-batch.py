"""Freeze two scoped proof repairs and a separate unsigned-lowering diagnostic."""
from pathlib import Path
from datetime import datetime,timezone
import ast,hashlib,json
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[4];C=ROOT/'competitions/floatlib/candidates'
sha=lambda b:hashlib.sha256(b).hexdigest();save=lambda p,x:p.write_bytes((json.dumps(x,ensure_ascii=False,indent=2)+'\n').encode())
base=(C/'f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes();module_sha=sha((HERE/'development-helper-audit.py').read_bytes())

def emit(name,raw,old_meta,component,description,endpoints):
    assert raw.startswith(base) and b'\r' not in raw and len(raw)<=256000
    folder=C/name;folder.mkdir();(folder/'Kernel.lean').write_bytes(raw)
    part=HERE/component;assert not part.exists();part.write_bytes(raw[len(base):])
    meta=dict(old_meta);meta.update(candidate=name,candidate_sha256=sha(raw),candidate_bytes=len(raw),created_at_utc=datetime.now(timezone.utc).isoformat(),
        parent='f01-r15-dev-packed-b2-1',parent_sha256=sha(base),
        components=[dict(path=part.relative_to(ROOT).as_posix(),sha256=sha(part.read_bytes()),bytes=part.stat().st_size)],
        mechanism=description,proof_status='NOT_COMPILED',performance='NOT_RUN',helper_audit_source_sha256=sha(raw),helper_audit_module_sha256=module_sha,helper_audit_required_endpoints=endpoints)
    save(folder/'manifest.json',meta);return dict(candidate=name,sha256=sha(raw),bytes=len(raw),helper_roots=meta['helper_audit_expected_count'])

worker=HERE/'astra-workers/numeric-roundtrip';r=json.loads((worker/'repair2-manifest.json').read_bytes());raw=(ROOT/r['primary_probe']['path']).read_bytes()
assert sha(raw)==r['primary_probe']['sha256']=='0873268d474eb79301a929e744271c2c48ea547161ed52eda18b5e4aa4bd8fd9'
old=(C/'f01-r17-dev-u32-roundtrip-repair1/Kernel.lean').read_bytes()
assert raw==old.replace(b'simpa using (UInt32.toNat_ofNatClamp_of_lt hfit)',b'simpa only [Int.toNat_natCast] using (UInt32.toNat_ofNatClamp_of_lt hfit)')
meta=json.loads((C/'f01-r17-dev-u32-roundtrip-repair1/manifest.json').read_bytes());meta['previous_source_sha256']=sha(old)
outputs=[emit('f01-r17-dev-u32-roundtrip-repair2',raw,meta,'development-u32-roundtrip-repair2-fragment.lean','Only scoped Int.toNat_natCast normalization for real40293041239 error; runtime unchanged.',meta['helper_audit_required_endpoints'])]

folder=C/'f01-r17-dev-u64-roundtrip-probe1';old=(folder/'Kernel.lean').read_bytes();meta=json.loads((folder/'manifest.json').read_bytes())
needle=b'simpa using (UInt64.toNat_ofNatClamp_of_lt hfit)';assert old.count(needle)==1
raw=old.replace(needle,b'simpa only [Int.toNat_natCast] using (UInt64.toNat_ofNatClamp_of_lt hfit)')
meta.update(previous_source_sha256=sha(old),known_shared_issue='Shared terminal normalization repaired before first dispatch; original9f9 immutable and NOT_RUN')
outputs.append(emit('f01-r17-dev-u64-roundtrip-repair1',raw,meta,'development-u64-roundtrip-repair1-fragment.lean','UInt64 interface with the same actual scoped Nat/Int normalization repair; audit13 direct and15 support roots.',meta['helper_audit_required_endpoints']))

runtime=HERE/'astra-workers/structural-frontier/inline-u64-mul/Runtime-u64-mul-integer-v3-lf.lean.inc';body=runtime.read_bytes()
assert sha(body)=='cd301ba43a18ba2b9db2a8b2f1109406d00242acdd543b26364d9925ffde6c67'
diagnostic=b'\nnamespace Submission.R17NumericMulInteger\nopen FloatLib.Floats Competition\ndef diagnosticEntry (x y : Binary32) : Binary32 :=\n  guardedMul Submission.mul x y\nend Submission.R17NumericMulInteger\n'
raw=base+b'\n'+body+diagnostic
names=['Submission.R17NumericMulInteger.'+n for n in ('normalCore','guardedMul','diagnosticEntry')]
meta=dict(candidate_file='Kernel.lean',validation_mode='statement-only',explicit_helper_audit=names,helper_audit_expected_count=3,
    helper_kernel_and_axioms='Data-definition type/dependency audit only. Desired MUL equivalence remains UNPROVED; old public MUL stays B2.',
    scope='Actual exported diagnostic caller and original pinned object, not the official timed MainFull MUL or performance acceptance.',
    producer_runtime_sha256=sha(body),fallback='B2 Submission.mul, replacing the old c972-specific fallback name in producer Diagnostic-entry-v2')
outputs.append(emit('f01-r17-dev-u64-lowering1',raw,meta,'development-u64-lowering1-fragment.lean','Unsigned64 integer multiply then numeric forward/back cast; source-level C/ASM discriminator only, no new timed implementation.',[names[-1]]))

diag=ROOT/'competitions/floatlib/candidates/f01-word-tensors/ci-diagnostics.py';text=diag.read_text()
old="names=[name for name in names if name.startswith('lp_competition_Submission_') and 'loop' in name.lower() and 'boxed' not in name and ('Packed' in name or 'NativeDecodeSum' in name or 'Tile' in name)]"
new="names=[name for name in names if name.startswith('lp_competition_Submission_') and 'boxed' not in name and (('loop' in name.lower() and ('Packed' in name or 'NativeDecodeSum' in name or 'Tile' in name)) or name in ('lp_competition_Submission_R17NumericMulInteger_normalCore','lp_competition_Submission_R17NumericMulInteger_diagnosticEntry'))]"
assert text.count(old)==1;diag.write_bytes(text.replace(old,new).encode())
blocks=[n.value for n in ast.walk(ast.parse(diag.read_text())) if isinstance(n,ast.Constant) and isinstance(n.value,str) and 'g.STAGES=' in n.value];assert len(blocks)==1;compile(blocks[0],str(diag)+':embedded','exec')
save(HERE/'development-second-batch-sources.json',dict(at_utc=datetime.now(timezone.utc).isoformat(),candidates=outputs,diagnostic_support_change='Add two exact prototype symbols to read-only post-build nm/objdump selection; no original gate or benchmark change.',embedded_syntax='PASS'))
print(json.dumps(outputs))
