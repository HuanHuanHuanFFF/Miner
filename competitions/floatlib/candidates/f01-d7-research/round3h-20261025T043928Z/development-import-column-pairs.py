"""Select the reviewed broad pair-column source, without importing research notes."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
C = ROOT / 'competitions/floatlib/candidates'
WORKER = HERE / 'astra-workers/matrix-structure'
sha = lambda b: hashlib.sha256(b).hexdigest()
review = json.loads((HERE / 'astra-pairs-independent-review.json').read_bytes())
raw = (WORKER / 'Kernel-pairs.lean').read_bytes()
assert sha(raw) == review['candidate_sha256'] == 'b9629b37f47ed8b5c169de213ccec2a67a2b3b2737803c5814e996c1a1cc16b3'
assert len(raw) == review['candidate_bytes'] <= 256000
parent = C / 'f01-r15-dev-matrix-only1/Kernel.lean'
assert sha(parent.read_bytes()) == review['parent_sha256']
fragment_raw = (WORKER / 'ThinPairs.lean').read_bytes()
fragment = fragment_raw.replace(b'\r\n', b'\n')
assert raw.count(fragment) == 1
copy = HERE / 'development-column-pairs-fragment1.lean'
assert not copy.exists()
copy.write_bytes(fragment)
folder = C / 'f01-r15-dev-column-pairs1'
assert not folder.exists()
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(raw)
record = dict(candidate=folder.name, candidate_file='Kernel.lean', candidate_sha256=sha(raw),
    candidate_bytes=len(raw), created_at_utc=datetime.now(timezone.utc).isoformat(),
    parent=parent.parent.name, parent_sha256=sha(parent.read_bytes()),
    research_review_sha256=sha((HERE / 'astra-pairs-independent-review.json').read_bytes()),
    donor_original_fragment_sha256=sha(fragment_raw),
    components=[dict(path=copy.relative_to(ROOT).as_posix(), sha256=sha(fragment), bytes=len(fragment))],
    mechanism='p2..8,n>1,m>=4: pair adjacent independent columns, reuse one A decode per pair/k and one prepared B per call. Original per-lane k order, +0 start and raw NaN finish retained. Odd tail writes only active lane.',
    selection='Broad pairs primary b962 selected once; obsolete p2-only sources not run as alternate discovery trials.',
    review='Independent research review and development full-fragment reading complete; finite trace evidence is not Lean or performance acceptance.',
    proof_status='NOT_COMPILED_THIS_EXACT_SOURCE', performance='NOT_RUN',
    cost_risk='F2 return/writer overhead, B Float32 boxes and extra unused-tail work charged; actual C and performance UNKNOWN.')
(folder / 'manifest.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({k: record[k] for k in ('candidate', 'candidate_sha256', 'candidate_bytes', 'proof_status')}))
