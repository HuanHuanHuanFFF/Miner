from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
import json

HERE = Path(__file__).resolve().parent
PARENT = HERE.parent / 'f01-d11-bmm-fused-output' / 'Kernel.lean'
PARENT_SHA = '1b71f67ee1cb154399e60a0657618c4b968d8e4b4d642cfc0621fdf416811792'
old = b'''  intro q hq
  change (output batch m n p A B)[q] = _
  rw [(output_prefix batch m n p A B).2 q (by
    rw [(output_prefix batch m n p A B).1]
    exact hq)]
'''
new = b'''  intro q hq
  have hqo : q < (output batch m n p A B).size := by
    rw [(output_prefix batch m n p A B).1]
    exact hq
  change (output batch m n p A B)[q]'hqo = _
  rw [(output_prefix batch m n p A B).2 q hqo]
'''
parent = PARENT.read_bytes()
assert sha256(parent).hexdigest() == PARENT_SHA
assert parent.count(old) == 1
candidate = parent.replace(old, new, 1)
assert candidate.count(new) == 1
assert candidate.replace(new, old, 1) == parent
assert len(candidate) <= 256000
for forbidden in (b'sorry', b'axiom ', b'unsafe ', b'extern ', b'implemented_by'):
    assert forbidden not in candidate
assert candidate.count(b'import ContractTensor') == 1
assert candidate.count(b'\nimport ') == 0
assert sha256(PARENT.read_bytes()).hexdigest() == PARENT_SHA
(HERE / 'Kernel.lean').write_bytes(candidate)
manifest = json.loads((PARENT.parent / 'manifest.json').read_text(encoding='utf-8'))
manifest.update({
    'candidate': HERE.name,
    'candidate_sha256': sha256(candidate).hexdigest(),
    'candidate_bytes': len(candidate),
    'created_at_utc': datetime.now(timezone.utc).isoformat(),
    'parent': PARENT.parent.name,
    'parent_sha256': PARENT_SHA,
    'change': 'Proof only: establish hqo:q<output.size by output_prefix before change, supply the explicit index proof to GetElem, and use the same hqo in the prefix rewrite. No runtime definition or environment/compiler option changed.',
    'proof': 'All fused-output prefix/row/lane proofs and reference connection retained. Only core_eq_reference array-index elaboration is repaired; source remains NOT_RUN until exact new statement check.',
    'previous_failure': {
        'run': 40017211049,
        'seed': 903,
        'source_sha256': PARENT_SHA,
        'stage': 'statement',
        'verdict': 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40017211049/download-2cc430a78bfb46d29fb8ac9ee87f2ec4/diagnostics/f01-d7-public-suite/public-suite/f01-d11-bmm-fused-output-verdict.json',
        'verdict_sha256': '1ac42368e06cd97a8f49db541bd27d04fbf6b0738b978f74fac9461cf2f0924a',
        'errors': ['6191:9 failed to prove index is valid', '6185:0 whnf heartbeat 200000 timeout', '6203:8 unknown constant core_eq_reference'],
        'interpretation': 'First error is explicit index proof omission; subsequent timeout and missing constant may be cascading. This repair must be checked rather than assumed to remove them.'
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
    'delta_bytes': len(candidate) - len(parent),
    'old_text': old.decode(),
    'new_text': new.decode(),
    'old_text_sha256': sha256(old).hexdigest(),
    'new_text_sha256': sha256(new).hexdigest(),
    'inverse_edit_recovers_parent_bytes': True,
    'edits_confined_to': 'Submission.RowStream.core_eq_reference proof',
    'all_runtime_definition_bytes_preserved': True,
    'all_author_source_comments_preserved': True,
    'compiler_environment_options_changed': False,
    'Lean_and_float_validation': 'NOT_RUN',
}
(HERE / 'repair-evidence.json').write_text(json.dumps(evidence, indent=2) + '\n', encoding='utf-8')
print(json.dumps({k: manifest[k] for k in ['candidate', 'candidate_sha256', 'candidate_bytes', 'proof_status']}))
