"""Select one reviewed B2 layout prototype; import pure source, not research notes."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
C = ROOT / 'competitions/floatlib/candidates'
WORKER = HERE / 'astra-workers/matrix-structure'
sha = lambda b: hashlib.sha256(b).hexdigest()
review_path = HERE / 'astra-b2-independent-review.json'
review = json.loads(review_path.read_bytes())
raw = (WORKER / 'Kernel-b2.lean').read_bytes()
assert sha(raw) == review['candidate_sha256'] == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert len(raw) == review['candidate_bytes'] <= 256000
parent = C / 'f01-r15-dev-column-pairs2/Kernel.lean'
assert sha(parent.read_bytes()) == review['parent_sha256']
fragment_raw = (WORKER / 'PackedB2.lean').read_bytes()
fragment = fragment_raw.replace(b'\r\n', b'\n')
assert raw.count(fragment) == 1
component = HERE / 'development-packed-b2-fragment1.lean'
assert not component.exists()
component.write_bytes(fragment)
folder = C / 'f01-r15-dev-packed-b2-1'
assert not folder.exists()
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(raw)
record = dict(candidate=folder.name, candidate_file='Kernel.lean', candidate_sha256=sha(raw),
    candidate_bytes=len(raw), created_at_utc=datetime.now(timezone.utc).isoformat(),
    parent=parent.parent.name, parent_sha256=sha(parent.read_bytes()),
    independent_review_sha256=sha(review_path.read_bytes()),
    components=[dict(path=component.relative_to(ROOT).as_posix(), sha256=sha(fragment), bytes=len(fragment))],
    donor_original_fragment_sha256=sha(fragment_raw),
    mechanism='In the same p2..8,n>1,m>=4 path, prepare per-batch/per-column-pair inner vectors of F2 native scalar records; each loop reads one record and its two fields. Pair arithmetic, A conversion, raw finish and fallback unchanged.',
    correctness_route='Both raw addresses, including the unobserved odd tail, project to the parent loop; output_eq and original prefix/reference close full shape specs.',
    cost_risks='Nested containers, closures, strided preparation, odd extra conversion, return F2 and destruction are timed. No claim of halved total allocation or measured speed.',
    source_review='Development read all new definitions/proofs; R independent inverse and pinned APIs checked. Finite index checks are not Lean acceptance.',
    proof_status='NOT_COMPILED_THIS_EXACT_SOURCE', full_gate='NOT_RUN', performance='NOT_RUN')
(folder / 'manifest.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({k: record[k] for k in ('candidate', 'candidate_sha256', 'candidate_bytes', 'proof_status')}))
