from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
import json

HERE = Path(__file__).resolve().parent
PARENT = HERE.parent / 'f01-d11-bmm-underflow-zero' / 'Kernel.lean'
PARENT_SHA = 'd37743d3ad6fbc0ee81007a70dc8b1795d3b1aeda4fc58ed379cbab7544feddb'
old = b'    have hh := Bool.and_eq_true.mp h\n'
new = '''    have hh : A.toArray.all UnderflowZero.small = true ∧
        B.toArray.all UnderflowZero.small = true := by
      simpa only [Bool.and_eq_true] using h
'''.encode('utf-8')
source = PARENT.read_bytes()
assert sha256(source).hexdigest() == PARENT_SHA
assert source.count(old) == 1
candidate = source.replace(old, new, 1)
assert candidate.count(new) == 1
assert candidate.replace(new, old, 1) == source
assert len(candidate) <= 256000
assert candidate.startswith(b'import ContractTensor\n')
assert candidate.count(b'\nimport ') == 0
for forbidden in (b'sorry', b'axiom ', b'unsafe ', b'extern ', b'implemented_by', b'set_option'):
    assert forbidden not in candidate
(HERE / 'Kernel.lean').write_bytes(candidate)
manifest = json.loads((PARENT.parent / 'manifest.json').read_text(encoding='utf-8'))
manifest.update({
    'candidate': HERE.name,
    'candidate_sha256': sha256(candidate).hexdigest(),
    'candidate_bytes': len(candidate),
    'created_at_utc': datetime.now(timezone.utc).isoformat(),
    'parent': PARENT.parent.name,
    'parent_sha256': PARENT_SHA,
    'change': 'Proof only: replace invalid Bool.and_eq_true.mp field notation with explicitly typed conjunction and simpa only [Bool.and_eq_true] using branch hypothesis. Original accepted-parent proof text already uses this rewrite lemma form. No runtime, arithmetic theorem, environment or proof resource change.',
    'previous_failure': {
        'run': 40025423585,
        'seed': 910,
        'stage': 'statement',
        'source_sha256': PARENT_SHA,
        'verdict': 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40025423585/download-50f43747e99846ebac96a513ea4ebeb0/diagnostics/f01-d7-public-suite/public-suite/f01-d11-bmm-underflow-zero-verdict.json',
        'verdict_sha256': '91394417d19073a82402061873bd9f242413be62eab936977e061d96e2dd64ac',
        'reason': '6590:15 Unknown constant Bool.and_eq_true.mp',
        'scope': 'No other error reported in earlier small/scale/roundP/actual ExecFloat.mul/signed-zero/fold/reference bridge; full package and all original gates still require actual new acceptance.',
    },
    'source_status': 'FROZEN_FOR_SECOND_UNDERFLOW_STATEMENT',
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
    'old_text': old.decode(),
    'new_text': new.decode(),
    'old_text_sha256': sha256(old).hexdigest(),
    'new_text_sha256': sha256(new).hexdigest(),
    'inverse_edit_recovers_parent_bytes': True,
    'edits_confined_to': 'Submission.bmm_spec proof final Bool scan conjunction',
    'all_runtime_definition_bytes_preserved': True,
    'all_arithmetic_proof_bytes_preserved': True,
    'all_author_source_comments_preserved': True,
    'compiler_environment_options_changed': False,
    'proof_resource_limits_changed': False,
    'Lean_and_full_gate_validation': 'NOT_RUN',
}
(HERE / 'repair-evidence.json').write_text(json.dumps(evidence, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')
print(json.dumps({key: manifest[key] for key in ('candidate', 'candidate_sha256', 'candidate_bytes', 'proof_status')}))
