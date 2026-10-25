"""Remove the cached-B loop's foreign A bitcast via the existing exact decoder."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
C = ROOT / 'competitions/floatlib/candidates'
parent = C / 'f01-r15-dev-shortn-bcache1/Kernel.lean'
raw = parent.read_bytes()
sha = lambda b: hashlib.sha256(b).hexdigest()
assert sha(raw) == 'cb1bc62b2be91b52b45090af1f53ef8270b510b1f24264c667ec1308f094d152'
text = raw.decode()
start = text.index('namespace Submission.R14ThinBCache')
end = text.index('end Submission.R14ThinBCache', start)
fragment = text[start:end]
needle = 'let fa := ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero)'
assert fragment.count(needle) == 1
fragment = fragment.replace(needle, 'let fa := R2W01b.convert (A.getD (baseA + k) posZero).raw.1')
proof_needle = '    simp only [dif_pos hk]\n    rw [Packed10.nativeA_getD]'
assert fragment.count(proof_needle) == 1
fragment = fragment.replace(proof_needle,
    '    simp only [dif_pos hk]\n    rw [R2W01c.convert_eq]\n    rw [Packed10.nativeA_getD]')
result = (text[:start] + fragment + text[end:]).encode()
folder = C / 'f01-r15-dev-shortn-inline-decode1'
assert not folder.exists()
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(result)
record = dict(candidate=folder.name, candidate_file='Kernel.lean', candidate_sha256=sha(result),
    candidate_bytes=len(result), created_at_utc=datetime.now(timezone.utc).isoformat(),
    parent=parent.parent.name, parent_sha256=sha(raw),
    mechanism='In the once-B cached dot loop only, use the already all-input-proved R2W01b.convert instead of direct toFloat32/ofBits for A. It can avoid a foreign bitcast call in the hot loop for eligible inputs. Preparation, branches and all conversion costs remain inside full timing.',
    proof_route='Existing R2W01c.convert_eq in loop_eq followed by unchanged prepared-B identity; exact same dot arithmetic and raw finish.',
    known_tradeoff='The inline converter has guards/table operations and may lose. Prior scalar adoption is evidence for trying the mechanism, not evidence for this matrix result. No local C or cycle claim.',
    proof_status='NOT_COMPILED_THIS_EXACT_SOURCE', performance='NOT_RUN',
    invariant='Other candidate bytes unchanged, including all public scalars/sum and outer dispatch.')
(folder / 'manifest.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({k: record[k] for k in ('candidate', 'candidate_sha256', 'candidate_bytes', 'proof_status')}))
