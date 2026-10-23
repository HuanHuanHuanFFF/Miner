from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
import json

HERE = Path(__file__).resolve().parent
PARENT = HERE.parent / 'f01-d11-bmm-fused-output-proof2' / 'Kernel.lean'
PARENT_SHA = '2c73622e91fa0edef0e37a22bac1724190451479b0dceeee04ef5d181cc811ed'
source = PARENT.read_bytes()
assert sha256(source).hexdigest() == PARENT_SHA
scope = source.index(b'namespace Submission.RowStream\n')
start = source.index(b'theorem core_eq_reference (batch m n p : Nat)\n', scope)
stop = source.index(b'theorem core_eq (batch m n p : Nat)\n', start)
old = source[start:stop]
new = (HERE / 'reference-bridge.lean').read_bytes()
if not new.endswith(b'\n\n'):
    new = new.rstrip(b'\n') + b'\n\n'
candidate = source[:start] + new + source[stop:]
assert candidate[:start] + old + candidate[start + len(new):] == source
assert len(candidate) <= 256000
for forbidden in (b'sorry', b'axiom ', b'unsafe ', b'extern ', b'implemented_by', b'set_option'):
    assert forbidden not in candidate
assert candidate.startswith(b'import ContractTensor\n')
assert candidate.count(b'\nimport ') == 0
(HERE / 'Kernel.lean').write_bytes(candidate)
manifest = json.loads((PARENT.parent / 'manifest.json').read_text(encoding='utf-8'))
manifest.update({
    'candidate': HERE.name,
    'candidate_sha256': sha256(candidate).hexdigest(),
    'candidate_bytes': len(candidate),
    'created_at_utc': datetime.now(timezone.utc).isoformat(),
    'parent': PARENT.parent.name,
    'parent_sha256': PARENT_SHA,
    'change': 'Proof only: factor the writer-to-Vector equality through a generic abstract Array Prefix lemma; prove scalar point-vector equivalence separately; core_eq_reference now composes the two opaque theorems. Remove concrete output GetElem/change/simp interaction from the combined theorem. No source trimming, runtime, compiler or environment changes.',
    'proof': 'New prefix_vector_eq_ofFn quantifies abstract out:Array, so Vector.ext/GetElem elaboration cannot unfold concrete output. points_eq_reference reuses the already accepted DirectSmall-style Vector.ofFn congruence proof and original NativeFinal.dot_eq/address bridge. core_eq_reference composes them. Exact new statement remains NOT_RUN.',
    'previous_failure': {
        'run': 40019256733,
        'seed': 905,
        'source_sha256': PARENT_SHA,
        'stage': 'statement',
        'verdict': 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40019256733/download-7bf307c0b7d641309f3afc28df73f547/diagnostics/f01-d7-public-suite/public-suite/f01-d11-bmm-fused-output-proof2-verdict.json',
        'verdict_sha256': 'b40b26767f286b4456428fb84a3de70025da5c2503fa99c6c34e89b824a5b191',
        'errors': ['6185:0 whnf heartbeat 200000 timeout', '6204:8 unknown constant core_eq_reference'],
        'observed': 'Explicit GetElem validity error disappeared; core_eq_reference still timed out. All earlier fused writer invariant theorems were accepted in the statement traversal.',
        'root_cause_hypothesis': 'INFERRED: concrete output-dependent Vector.ext/change/rewrites permit expensive definitional normalization of nested Fin.foldl while checking transported index types. No gate trace isolates the exact tactic. Proof3 separates an abstract container bridge from the scalar semantic bridge to prevent this concrete unfolding and localize any remaining failure.',
    },
    'validation_mode': 'statement-only first; full original gate if accepted',
    'proof_status': 'NOT_RUN',
    'kernel_replay': 'NOT_RUN',
    'axiom_audit': 'NOT_RUN',
    'checksum': 'NOT_RUN',
    'performance': 'UNKNOWN',
    'formal_submission': 'NOT_SUBMITTED',
})
(HERE / 'manifest.json').write_text(json.dumps(manifest, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')
evidence = {
    'state': 'PASS_EXACT_PROOF_ONLY_BYTE_TRANSFORM',
    'parent_sha256': PARENT_SHA,
    'candidate_sha256': manifest['candidate_sha256'],
    'candidate_bytes': len(candidate),
    'delta_bytes': len(candidate) - len(source),
    'old_span_sha256': sha256(old).hexdigest(),
    'new_span_sha256': sha256(new).hexdigest(),
    'old_span_bytes': len(old),
    'new_span_bytes': len(new),
    'inverse_edit_recovers_parent_bytes': True,
    'edits_confined_to': 'Replace RowStream.core_eq_reference theorem with two helper theorems and its composition proof',
    'all_runtime_definition_bytes_preserved': True,
    'all_author_source_comments_preserved': True,
    'compiler_environment_options_changed': False,
    'proof_resource_limits_changed': False,
    'Lean_and_float_validation': 'NOT_RUN',
}
(HERE / 'repair-evidence.json').write_text(json.dumps(evidence, indent=2) + '\n', encoding='utf-8')
print(json.dumps({key: manifest[key] for key in ('candidate', 'candidate_sha256', 'candidate_bytes', 'proof_status')}))
