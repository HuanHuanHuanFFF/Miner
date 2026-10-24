"""Freeze one source-level integer-to-Float32 bridge diagnostic."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[4]
C = ROOT / 'competitions/floatlib/candidates'
parent = C / 'f01-r14-dev-compact-base/Kernel.lean'
raw = parent.read_bytes()
assert hashlib.sha256(raw).hexdigest() == '3c6af73f9d679e9831ac8c4abb9f0e6d41b61718301dd045bedd2402e980632a'
fragment = OUT / 'development-int64-rounding-bridge.lean'
part = fragment.read_bytes()
result = raw + b'\n' + part
assert len(result) <= 256000
folder = C / 'f01-r14-dev-integer-round-bridge1'
assert not folder.exists()
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(result)
record = dict(candidate=folder.name, candidate_file='Kernel.lean', candidate_sha256=hashlib.sha256(result).hexdigest(),
              candidate_bytes=len(result), created_at_utc=datetime.now(timezone.utc).isoformat(),
              parent='f01-r14-dev-compact-base', parent_sha256=hashlib.sha256(raw).hexdigest(),
              fragment=fragment.relative_to(ROOT).as_posix(), fragment_sha256=hashlib.sha256(part).hexdigest(),
              validation_mode='statement-only', proof_status='NOT_COMPILED', public_runtime_changed=False,
              purpose='Check arbitrary UInt64 and Int64 native-cast RNE models, exact signed bitcast below2^63, and agreement of low signed/unsigned casts. Existing four public kernels are the compact retained baseline.',
              performance='NOT_RUN; this helper package is not a runtime optimization.')
(folder / 'manifest.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
(OUT / 'development-integer-round-bridge-build.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({key: record[key] for key in ('candidate', 'candidate_sha256', 'candidate_bytes', 'proof_status')}))
