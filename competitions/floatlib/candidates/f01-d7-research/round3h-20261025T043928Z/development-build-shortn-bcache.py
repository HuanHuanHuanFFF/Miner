"""Reuse B in short inner dimensions already routed through scalar direct dots."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
C = ROOT / 'competitions/floatlib/candidates'
parent = C / 'f01-r15-dev-matrix-only1/Kernel.lean'
raw = parent.read_bytes()
sha = lambda b: hashlib.sha256(b).hexdigest()
assert sha(raw) == 'ec82ac20cf5b2a9621dce7e409a68a4af9700b1845d23385497c896439e372a1'
needle = b'if 4 \xe2\x89\xa4 m \xe2\x88\xa7 1 < n \xe2\x88\xa7 0 < p \xe2\x88\xa7 p \xe2\x89\xa4 2 then core batch m n p A B'
replacement = 'if 4 ≤ m ∧ 1 < n ∧ 0 < p ∧ (p ≤ 2 ∨ n ≤ 4) then core batch m n p A B'.encode()
assert raw.count(needle) == 1
result = raw.replace(needle, replacement)
folder = C / 'f01-r15-dev-shortn-bcache1'
assert not folder.exists()
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(result)
record = dict(candidate=folder.name, candidate_file='Kernel.lean', candidate_sha256=sha(result),
    candidate_bytes=len(result), created_at_utc=datetime.now(timezone.utc).isoformat(),
    parent=parent.parent.name, parent_sha256=sha(raw), parent_bytes=len(raw),
    mechanism='Extend the already-proved once-B cache from thin outputs to m>=4,1<n<=4,all positive p. Those shapes already use scalar DirectContinuous dots in the parent, so cached-B replaces repeated B conversion across rows without replacing a shared-A vector kernel.',
    invariant='Same dot loop k order, Float32 multiply then add, raw per-output NaN fallback, all add/mul/sum bytes and outer underflow-zero shortcut unchanged.',
    selection='One mechanism-driven broader reuse domain; not a numeric threshold grid. m>=4 keeps at least four uses per B element in the target domain. Actual allocation/conversion cost is charged and may still lose.',
    proof_route='Existing R14ThinBCache.core_eq_reference for all shapes; dispatch_spec already proves either branch independently of the shape predicate.',
    proof_status='NOT_COMPILED_THIS_EXACT_SOURCE', performance='NOT_RUN',
    first_discovery='Required on this exact distinct source; parent outcome cannot be inherited, failed D will be retained.')
(folder / 'manifest.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({k: record[k] for k in ('candidate', 'candidate_sha256', 'candidate_bytes', 'proof_status')}))
