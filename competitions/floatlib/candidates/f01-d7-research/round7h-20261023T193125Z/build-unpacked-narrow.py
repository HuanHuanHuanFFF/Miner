"""A complete no-prepacking comparison for low-reuse narrow matrices."""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[5]
PARENT = ROOT / 'competitions/floatlib/candidates/f01-d10-bmm-direct-rows/Kernel.lean'
EXPECTED = 'a06608bdc419d4647af301bfdd617d52e4796c404661a28672a022eef4a10b78'
raw = PARENT.read_bytes()
assert hashlib.sha256(raw).hexdigest() == EXPECTED
source = raw.decode('utf-8')
anchor = '\nnamespace Submission\nopen FloatLib.Floats Competition\n\ndef bmm (batch m n p : Nat)'
assert source.count(anchor) == 1
prefix, last = source.rsplit(anchor, 1)
last = anchor + last
last = last.replace('def bmm (', 'def bmmBeforeNoPack (', 1)
last = last.replace('theorem bmm_spec :', 'theorem bmmBeforeNoPack_spec :', 1)
last = last.replace('(bmm batch m n p A B).get', '(bmmBeforeNoPack batch m n p A B).get', 1)
last = last.replace('  unfold bmm\n', '  unfold bmmBeforeNoPack\n', 1)
new = '''

namespace Submission
open FloatLib.Floats Competition

/-- Low row reuse: pay no nativeA map or global F10 B preparation. -/
def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if 4 < n ∧ 2 < p ∧ p ≤ 8 ∧ m ≤ 2 then DirectRows.core batch m n p A B
  else bmmBeforeNoPack batch m n p A B

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold bmm
  split
  · rw [DirectRows.core_eq, DirectSmall.core_eq_reference]
    exact referenceBmm_spec batch m n p A B
  · exact bmmBeforeNoPack_spec batch m n p A B

end Submission
'''
result = (prefix + last + new).encode('utf-8')
out = ROOT / 'competitions/floatlib/candidates/f01-d11-bmm-unpacked-narrow'
out.mkdir(exist_ok=False)
assert len(result) <= 256000
(out / 'Kernel.lean').write_bytes(result)
manifest = {
 'candidate': out.name, 'candidate_file': 'Kernel.lean',
 'candidate_sha256': hashlib.sha256(result).hexdigest(), 'candidate_bytes': len(result),
 'created_at_utc': datetime.now(timezone.utc).isoformat(),
 'parent': PARENT.parent.name, 'parent_sha256': EXPECTED,
 'mechanism': 'For n>4,3<=p<=8,m<=2 only, use proven ordered DirectRows instead of nativeA map/F10 prepack. This is the full no-packing algorithm control, including repeated raw conversions and output allocation. Other shapes keep exact a066 behavior.',
 'proof': 'Reuse all-dimension DirectRows.core_eq and DirectSmall.core_eq_reference; new dispatcher still needs its own original full gate.',
 'validation_mode': 'full-gate', 'proof_status': 'NOT_RUN', 'performance': 'UNKNOWN',
 'formal_submission': 'NOT_SUBMITTED',
}
(out / 'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(manifest,ensure_ascii=False))
