"""Integrate the frozen batch-local writer draft into the statement-passed base."""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
parent = ROOT/'competitions/floatlib/candidates/f01-d11-bmm-fused-output-proof3'
raw = (parent/'Kernel.lean').read_bytes()
expected = '5b7d926cf628c2d87042386834f7c1581b9a6aa7441af196453984b395534ba2'
assert hashlib.sha256(raw).hexdigest() == expected
draft_path = HERE/'review-output-batch-local.lean'
draft_raw = draft_path.read_bytes()
assert hashlib.sha256(draft_raw).hexdigest() == '7314cb0d6501ea896b7ba508af5054252a3ab5f8154a79703f733258d3f222ba'
source = raw.decode('utf-8')
anchor = '\nnamespace Submission\nopen FloatLib.Floats Competition\n\ndef bmm (batch m n p : Nat)'
assert source.count(anchor) == 1
prefix, tail = source.rsplit(anchor, 1)
tail = anchor+tail
original_tail = tail
tail = tail.replace('def bmm (', 'def bmmBeforeBatchLocal (', 1)
tail = tail.replace('theorem bmm_spec :', 'theorem bmmBeforeBatchLocal_spec :', 1)
tail = tail.replace('(bmm batch m n p A B).get', '(bmmBeforeBatchLocal batch m n p A B).get', 1)
tail = tail.replace('  unfold bmm\n', '  unfold bmmBeforeBatchLocal\n', 1)
draft = draft_raw.decode('utf-8')
draft = draft[draft.index('namespace Submission.BatchLocalPacked'):]
wrapper = '''

namespace Submission
open FloatLib.Floats Competition

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if 4 < n ∧ 2 < p ∧ 0 < batch * m then BatchLocalPacked.core batch m n p A B
  else bmmBeforeBatchLocal batch m n p A B

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold bmm
  split
  · rw [BatchLocalPacked.core_eq_reference]
    exact referenceBmm_spec batch m n p A B
  · exact bmmBeforeBatchLocal_spec batch m n p A B

end Submission
'''
payload = (prefix+tail+'\n\n'+draft+wrapper).encode('utf-8')
assert len(payload) <= 256000
assert (prefix+original_tail).encode('utf-8') == raw
out = ROOT/'competitions/floatlib/candidates/f01-d11-bmm-batch-local-output'
out.mkdir(exist_ok=False)
(out/'Kernel.lean').write_bytes(payload)
metadata = {'candidate': out.name, 'candidate_file': 'Kernel.lean',
            'candidate_sha256': hashlib.sha256(payload).hexdigest(), 'candidate_bytes': len(payload),
            'created_at_utc': datetime.now(timezone.utc).isoformat(),
            'parent': parent.name, 'parent_sha256': expected,
            'draft_sha256': hashlib.sha256(draft_raw).hexdigest(),
            'mechanism': 'For nonempty n>4,p>2 packed matrices only, retain global nativeA but construct only one batch of B packets, compute that batch into the same continuous output Array, then release the local packet scope. No global packedB Vector in the new runtime path. Original ordered MAC and raw NaN finish unchanged.',
            'proof': 'Concrete packBatch equals original packB.get b; batch/row/group prefix invariants connect the actual local preparation and output to referenceBmm. Full-source statement NOT_RUN.',
            'guard': '4<n AND2<p AND0<batch*m; all other shapes use exact5b7d parent.',
            'validation_mode': 'statement-only first, then full-gate', 'proof_status': 'NOT_RUN',
            'performance': 'UNKNOWN', 'lifetime_codegen': 'UNKNOWN_UNTIL_ACTUAL_C_AND_ASM',
            'formal_submission': 'NOT_SUBMITTED'}
(out/'manifest.json').write_text(json.dumps(metadata, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')
(out/'lineage.json').write_text(json.dumps({'parent_sha256': expected,
    'unchanged_parent_except_final_entry_rename': True, 'source_pruning': False,
    'original_tail_sha256': hashlib.sha256(original_tail.encode()).hexdigest(),
    'renamed_tail_sha256': hashlib.sha256(tail.encode()).hexdigest(),
    'increment_sha256': hashlib.sha256((draft+wrapper).encode()).hexdigest()}, indent=2)+'\n', encoding='utf-8')
print(json.dumps(metadata, ensure_ascii=False))
