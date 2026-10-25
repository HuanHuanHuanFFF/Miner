"""Repair exactly the three original proof errors; retain failed source unchanged."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
C = ROOT / 'competitions/floatlib/candidates'
sha = lambda b: hashlib.sha256(b).hexdigest()
parent = C / 'f01-r15-dev-column-pairs1/Kernel.lean'
raw = parent.read_bytes()
assert sha(raw) == 'b9629b37f47ed8b5c169de213ccec2a67a2b3b2737803c5814e996c1a1cc16b3'
diagnostic = HERE / 'development-compiler-error-map-40164630534.json'
observed = json.loads(diagnostic.read_bytes())['candidates'][0]
assert observed['kernel_sha256'] == sha(raw) and len(observed['errors']) == 3
start = raw.index(b'namespace Submission.R15ThinPairs')
end = raw.index(b'end Submission.R15ThinPairs', start) + len(b'end Submission.R15ThinPairs')
fragment = raw[start:end]
old = b'    simp only [dif_pos hk]\n    dsimp only\n    simp only [Packed10.nativeA_getD]'
new = b'    simp only [dif_pos hk]\n    simp only [Packed10.nativeA_getD]'
assert fragment.count(old) == 2
fixed = fragment.replace(old, new)
old_zero = b'simpa only [select, Nat.add_zero, if_pos rfl] using'
new_zero = 'simpa only [select, Nat.add_zero, ↓reduceIte] using'.encode()
assert fixed.count(old_zero) == 1
fixed = fixed.replace(old_zero, new_zero)
assert fixed.replace(new_zero, old_zero).replace(new, old) == fragment
result = raw[:start] + fixed + raw[end:]
folder = C / 'f01-r15-dev-column-pairs2'
assert not folder.exists()
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(result)
component = HERE / 'development-column-pairs-fragment2.lean'
assert not component.exists()
component.write_bytes(fixed)
manifest = dict(candidate=folder.name, candidate_file='Kernel.lean', candidate_sha256=sha(result),
    candidate_bytes=len(result), created_at_utc=datetime.now(timezone.utc).isoformat(),
    parent=parent.parent.name, parent_sha256=sha(raw), original_failure_run=40164630534,
    original_diagnostic_sha256=sha(diagnostic.read_bytes()),
    components=[dict(path=component.relative_to(ROOT).as_posix(), sha256=sha(fixed), bytes=len(fixed))],
    repairs=['Remove redundant dsimp in loop_s0', 'Remove redundant dsimp in loop_s1',
             'Use reduceIte to eliminate the actual remaining if True in finish_select zero lane'],
    runtime_change=False, inverse_proof_patch_exact=True,
    proof_status='REPAIRED_NOT_COMPILED', full_gate='NOT_RUN', performance='NOT_RUN',
    mechanism='Same broad p2..8 paired-column B cache as b962; proof scripts only changed in response to actual immutable CI diagnostics.')
(folder / 'manifest.json').write_bytes((json.dumps(manifest, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({k: manifest[k] for k in ('candidate', 'candidate_sha256', 'candidate_bytes', 'runtime_change')}))
