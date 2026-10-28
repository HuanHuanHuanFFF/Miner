"""Pinned-source and exact-interface audit only; never invokes Lean or a compiler."""
from pathlib import Path
from hashlib import sha256, sha1
import json, re
from datetime import datetime, timezone

root = Path(__file__).resolve().parent
index = json.loads((root / 'borrowed-interface-source/source-index.json').read_text())
records = []
for row in index['files']:
    raw = (root / row['file']).read_bytes()
    blob = sha1(b'blob ' + str(len(raw)).encode() + b'\0' + raw).hexdigest()
    assert blob == row['git_blob_sha'], (row['file'], blob)
    records.append({**row, 'bytes': len(raw), 'sha256': sha256(raw).hexdigest(), 'git_blob_match': True})
raw = (root / 'Borrowed-tail-ABI.lean.inc').read_bytes()
assert len(raw) == 1400
assert sha256(raw).hexdigest() == '680ca1b3676bf0e3e71d92b94a858ad87c1481b41e878bab5b0fae0aeedf1495'
s = raw.decode()
sig = r'\(n a0 a1 a2 a3 s : USize\) \(A B : @& Array UInt32\) \(k c : USize\)\s+\(q0 q1 q2 q3 q4 q5 q6 q7 : Float32\) : R15ThinPairs.F2'
assert len(re.findall(sig, s)) == 2
assert not re.search(r'\b(?:unsafe|extern|implemented_by|axiom|sorry|partial)\b', s)
assert not re.search(r'@\[export\b|set_option\s+compiler\.ignoreBorrowAnnotation', s)
assert s.count('termination_by 2*(n.toNat-k.toNat)') == 2
assert s.count('Packed10Index.next_decreases') == 2
out = {
    'at_utc': datetime.now(timezone.utc).isoformat(),
    'scope': 'Text/source audit; no type checking, numerical model or code generation',
    'pinned_ref': index['ref'], 'sources': records,
    'probe': {'file': 'Borrowed-tail-ABI.lean.inc', 'bytes': len(raw), 'sha256': sha256(raw).hexdigest(),
              'identical_signature_text': True, 'parameter_counts': {'USize': 8, 'borrowed_array': 2, 'Float32': 8},
              'runtime_fuel_or_phase_parameter': False, 'added_forbidden_declarations': False},
    'typing': 'NOT_RUN', 'emitted_C': 'NOT_RUN', 'actual_tail_jumps_or_fused_loop': 'UNKNOWN',
    'post_call_RC': 'UNKNOWN', 'timing': 'NOT_RUN', 'new_runtime_version': False,
    'interpretation': 'BORROWED-INTERFACE-AUDIT.md'
}
(root / 'borrowed-interface-audit.json').write_text(json.dumps(out, indent=2) + '\n', encoding='utf-8')
print(json.dumps({'sources': len(records), 'source_bytes': sum(x['bytes'] for x in records),
                  'probe_bytes': len(raw), 'source_hashes_match': True, 'Lean': 'NOT_RUN'}))
