from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
import json

HERE = Path(__file__).resolve().parent
PARENT = HERE.parent / 'f01-d10-bmm-direct-rows' / 'Kernel.lean'
PARENT_SHA = 'a06608bdc419d4647af301bfdd617d52e4796c404661a28672a022eef4a10b78'
source = PARENT.read_bytes()
assert sha256(source).hexdigest() == PARENT_SHA
anchor = b'namespace Submission\nopen FloatLib.Floats Competition\n\ndef bmm (batch m n p : Nat)'
assert source.count(anchor) == 1
at = source.index(anchor)
old_dispatch = source[at:]
new_dispatch = old_dispatch
for old, new in [
    (b'def bmm (', b'def bmmBeforeUnderflowZero ('),
    (b'theorem bmm_spec :', b'theorem bmmBeforeUnderflowZero_spec :'),
    (b'(bmm batch m n p A B).get', b'(bmmBeforeUnderflowZero batch m n p A B).get'),
    (b'  unfold bmm\n', b'  unfold bmmBeforeUnderflowZero\n'),
]:
    assert new_dispatch.count(old) == 1
    new_dispatch = new_dispatch.replace(old, new, 1)
block = (HERE / 'underflow-zero-block.lean').read_bytes().strip() + b'\n'
candidate = source[:at] + new_dispatch.rstrip() + b'\n\n\n' + block
assert candidate[:at] == source[:at]
assert len(candidate) <= 256000
for forbidden in (b'sorry', b'axiom ', b'unsafe ', b'extern ', b'implemented_by', b'set_option'):
    assert forbidden not in candidate
assert candidate.startswith(b'import ContractTensor\n')
assert candidate.count(b'\nimport ') == 0
(HERE / 'Kernel.lean').write_bytes(candidate)
manifest = {
    'candidate': HERE.name,
    'candidate_file': 'Kernel.lean',
    'candidate_sha256': sha256(candidate).hexdigest(),
    'candidate_bytes': len(candidate),
    'created_at_utc': datetime.now(timezone.utc).isoformat(),
    'parent': PARENT.parent.name,
    'parent_sha256': PARENT_SHA,
    'baseline': 'f01-r8-combined-result-guard',
    'baseline_sha256': '41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7',
    'mechanism': 'Two short-circuit Array.all scans on original A/B words. If every magnitude<0x16000000, return full +0 Vector.replicate; else exact original a066 dispatcher. All scan and fill costs remain in entry.',
    'threshold': {'raw_magnitude_strict_lt': '0x16000000', 'max_raw_exponent': 43, 'max_finiteScale_each': 42, 'max_sum_scale': 84},
    'proof': 'small_exp and scale_small derive scale sum<=84; generic 64-bit log2 bound gives roundP subnormal branch and shift149-scale>=65, so rseAny=0 even without a mantissa bound. FastMul.mul_spec/ExecFloat.Proof.mul_eq_spec connect signed zero to actual ExecFloat.mul. +0 plus either signed zero is +0. Fin.foldl fixed-zero induction and Array.all/getD default-zero connect to original referenceBmm and all four formal specs. New text is NOT_RUN.',
    'history_difference': 'R10 astra-subnormal-next proposed a broader exponent-sum<=102 whole-matrix condition without a Lean theorem or new Kernel; exposed831 had zero matching whole-matrix cases. This is the first implemented whole-array fixed-threshold path in the searched records, using a stronger domain for a simpler full proof. It differs from previously negative per-MAC low-exponent and zero-input guards.',
    'history_evidence': ['competitions/floatlib/candidates/f01-d7-research/round1h-20261023T125752Z/astra-subnormal-next.md', 'competitions/floatlib/candidates/f01-d7-research/round1h-20261023T125752Z/direct-low-input-scope-831.json'],
    'edge_cases': 'All Nat dimensions; empty arrays all=true, n=0 fold fixed-zero, zero output length; out-of-bounds getD uses certified small +0. Guard rejects any infinity/NaN magnitude. Original a066 unchanged on guard miss.',
    'source_status': 'FROZEN_FOR_STATEMENT',
    'validation_mode': 'statement-only first; original complete gate if accepted',
    'proof_status': 'NOT_RUN',
    'kernel_replay': 'NOT_RUN',
    'axiom_audit': 'NOT_RUN',
    'checksum': 'NOT_RUN',
    'performance': 'UNKNOWN',
    'formal_submission': 'NOT_SUBMITTED',
    'attribution': 'All parent provenance retained. finiteScale_toNat proof ported from FloatLib Team MIT FiniteProof.lean captured in existing R6-W01 public-source evidence; attribution comment in Kernel. Remaining new proof/runtime session-authored.',
}
(HERE / 'manifest.json').write_text(json.dumps(manifest, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')
report = {
    'state': 'PASS_STATIC_EXACT_PARENT_AND_SIZE_ONLY',
    'parent_sha256': PARENT_SHA,
    'candidate_sha256': manifest['candidate_sha256'],
    'candidate_bytes': len(candidate),
    'new_block_bytes': len(block),
    'headroom_bytes': 256000 - len(candidate),
    'parent_prefix_before_final_dispatch_byte_identical': True,
    'original_final_dispatch_runtime_changes': 'Names only: bmm -> bmmBeforeUnderflowZero',
    'new_runtime': ['UnderflowZero.small', 'UnderflowZero.zeros', 'Submission.bmm whole-array guard'],
    'compiler_environment_options_changed': False,
    'proof_resource_limits_changed': False,
    'Lean_float_gate_timing': 'NOT_RUN',
}
(HERE / 'static-precheck.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
print(json.dumps({key: manifest[key] for key in ('candidate', 'candidate_sha256', 'candidate_bytes', 'proof_status')}))
