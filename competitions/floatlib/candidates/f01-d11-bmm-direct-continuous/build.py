from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
import json

HERE = Path(__file__).resolve().parent
PARENT = HERE.parent / 'f01-d11-bmm-fused-output-proof3' / 'Kernel.lean'
PARENT_SHA = '5b7d926cf628c2d87042386834f7c1581b9a6aa7441af196453984b395534ba2'
source = PARENT.read_bytes()
assert sha256(source).hexdigest() == PARENT_SHA
anchor = b'namespace Submission\nopen FloatLib.Floats Competition\n\ndef bmm (batch m n p : Nat)'
assert source.count(anchor) == 1
at = source.index(anchor)
old_dispatch = source[at:]
new_dispatch = old_dispatch
changes = [
    (b'if n \xe2\x89\xa4 4 \xe2\x88\xa7 2 < p then DirectRows.core batch m n p A B',
     b'if n \xe2\x89\xa4 4 \xe2\x88\xa7 2 < p then DirectContinuous.core batch m n p A B'),
    (b'  \xc2\xb7 rw [DirectRows.core_eq, DirectSmall.core_eq_reference]\n',
     b'  \xc2\xb7 rw [DirectContinuous.core_eq_reference]\n'),
]
for old, new in changes:
    assert new_dispatch.count(old) == 1
    new_dispatch = new_dispatch.replace(old, new, 1)
block = (HERE / 'direct-continuous-block.lean').read_bytes().strip() + b'\n\n'
candidate = source[:at] + block + new_dispatch
assert len(candidate) <= 256000
assert len(candidate) - len(source) < 8000
assert candidate.startswith(b'import ContractTensor\n')
assert candidate.count(b'\nimport ') == 0
for forbidden in (b'sorry', b'axiom ', b'unsafe ', b'extern ', b'implemented_by', b'set_option'):
    assert forbidden not in candidate
restored_dispatch = new_dispatch
for old, new in reversed(changes):
    assert restored_dispatch.count(new) == 1
    restored_dispatch = restored_dispatch.replace(new, old, 1)
assert candidate[:at] + restored_dispatch == source
assert b'nativeA' not in block and b'packB' not in block
assert b'Vector.ofFn' not in block and b'flatMap' not in block
verdict_path = HERE.parent / 'f01-mul-log2-proof1/ci-runs/40027315361/download-4a79e554697544c9b3d9f99c75284e70/diagnostics/f01-d7-public-suite/public-suite/f01-d11-bmm-fused-output-proof3-verdict.json'
verdict = json.loads(verdict_path.read_text(encoding='utf-8'))
assert verdict['seed'] == 911 and verdict['passed'] and verdict['stage'] == 'score'
assert verdict['mode'] == 'gate' and len(verdict['rounds']) == 25
assert verdict['verifier_fingerprint'] == verdict['verifier_fingerprint_end']
(HERE / 'Kernel.lean').write_bytes(candidate)
manifest = {
    'candidate': HERE.name,
    'candidate_file': 'Kernel.lean',
    'candidate_sha256': sha256(candidate).hexdigest(),
    'candidate_bytes': len(candidate),
    'created_at_utc': datetime.now(timezone.utc).isoformat(),
    'parent': PARENT.parent.name,
    'parent_sha256': PARENT_SHA,
    'parent_validation': {'run': 40027315361, 'seed': 911, 'full_gate': True,
                          'verdict': str(verdict_path.relative_to(HERE.parents[3])),
                          'verdict_sha256': sha256(verdict_path.read_bytes()).hexdigest()},
    'mechanism': 'Only n<=4 and p>2 branch: replace row-number Vector.flatMap / per-row Vector with Fin.foldl over flat rows and emit p original NativeFinal.dot results into one preallocated Array. Share flat baseA=r*n and baseB=(r/m)*n*p per row. This runtime branch never maps nativeA or prepares packedB. All other shapes keep full-gate5b parent routes, including new packed RowStream.',
    'proof': 'row_prefix uses existing emit_prefix and point_row; output_prefix uses foldl_inv; Vector wrapper/reference equality composes already accepted generic prefix_vector_eq_ofFn and points_eq_reference, avoiding concrete output normalization. Final branch connects to original referenceBmm_spec. All new text NOT_RUN.',
    'scope': 'One guard family only. p<=2 unchanged for Astra route ownership. No numeric decoder replacement, unrolling, floating arithmetic change, unsafe or external code. Parent exact source retained; no compact unvalidated parent used.',
    'edge_cases': 'New core proof all Nat dimensions including empty batch/m/p and n=0, though runtime dispatcher selects only n<=4,p>2. Original NativeFinal.dot preserves exact raw NaN replay and fixed MAC sequence; arbitrary Nat output count and addresses remain Nat.',
    'cost_boundary': 'Output allocation, scalar dot conversions, NaN replay, writing and destruction remain inside original timed call. Source contains no row array; actual C exclusivity/closure/control cost remains UNKNOWN. Flat A row reconstruction/modulo removal is part of mechanism and not separately attributed.',
    'validation_mode': 'statement-only first; original complete gate if accepted',
    'proof_status': 'NOT_RUN',
    'kernel_replay': 'NOT_RUN',
    'axiom_audit': 'NOT_RUN',
    'checksum': 'NOT_RUN',
    'performance': 'UNKNOWN',
    'formal_submission': 'NOT_SUBMITTED',
    'attribution': 'All parent author/provenance and obsolete helper declarations retained byte-for-byte. New continuous direct output writer/proof session-authored using existing in-file interfaces.',
}
(HERE / 'manifest.json').write_text(json.dumps(manifest, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')
evidence = {
    'state': 'PASS_STATIC_PARENT_SIZE_AND_EXACT_INVERSE_ONLY',
    'parent_sha256': PARENT_SHA,
    'candidate_sha256': manifest['candidate_sha256'],
    'candidate_bytes': len(candidate),
    'new_block_bytes': len(block),
    'delta_bytes': len(candidate) - len(source),
    'headroom_bytes': 256000 - len(candidate),
    'inverse_transform_recovers_parent_bytes': True,
    'parent_bytes_before_final_dispatch_unchanged': True,
    'new_runtime_has_nativeA_map_or_packedB': False,
    'new_runtime_has_row_vector_or_flatMap': False,
    'old_DirectRows_namespace_preserved': True,
    'final_guard_unchanged': True,
    'compiler_environment_or_proof_resource_changed': False,
    'Lean_full_gate_codegen_performance': 'NOT_RUN',
}
(HERE / 'static-precheck.json').write_text(json.dumps(evidence, indent=2) + '\n', encoding='utf-8')
print(json.dumps({key: manifest[key] for key in ('candidate', 'candidate_sha256', 'candidate_bytes', 'proof_status')}))
