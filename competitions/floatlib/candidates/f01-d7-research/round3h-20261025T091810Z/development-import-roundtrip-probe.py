"""Import a closed mathematical probe; compiler feedback is not helper replay."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
WORKER = HERE / 'astra-workers/matrix-architecture/future-u32-roundtrip'
sha = lambda raw: hashlib.sha256(raw).hexdigest()
record = json.loads((WORKER / 'packaged-probe-manifest.json').read_bytes())
basepath = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
base = basepath.read_bytes()
assert sha(base) == record['parent']['sha256'] == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert all(value is None for value in record['original_text_checks']['result'].values())
original = base + b'\n' + b'\n'.join((WORKER / part['path']).read_bytes() for part in record['pieces'])
assert original == (WORKER / record['probe']['path']).read_bytes()
assert sha(original) == record['probe']['sha256'] == '4c65f15da51c7ccf5a0ebb259aa7dd6ba7ef0e5d21520a3272aaf2ab64189a2e'
pieces = []
parts = []
for part in record['pieces']:
    raw = (WORKER / part['path']).read_bytes()
    assert sha(raw) == part['sha256'] and len(raw) == part['bytes']
    if part['path'] == 'HighRoundtrip-probe-fragment.lean':
        assert raw.count(b': Dyadic)') == 1
        raw = raw.replace(b': Dyadic)', b': FloatLib.Numerics.Dyadic)')
    target = HERE / ('development-roundtrip-' + part['path'])
    assert not target.exists()
    target.write_bytes(raw)
    parts.append(raw)
    pieces.append(dict(path=target.relative_to(ROOT).as_posix(), sha256=sha(raw), bytes=len(raw),
                       producer_original_sha256=part['sha256']))
source = base + b'\n' + b'\n'.join(parts)
assert len(source) == 238074 < 256000
name = 'f01-r16-dev-u32-roundtrip-probe1'
folder = ROOT / 'competitions/floatlib/candidates' / name
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(source)
manifest = dict(candidate=name, candidate_file='Kernel.lean', candidate_sha256=sha(source),
                candidate_bytes=len(source), created_at_utc=datetime.now(timezone.utc).isoformat(),
                parent=basepath.parent.name, parent_sha256=sha(base), components=pieces,
                producer_probe_sha256=record['probe']['sha256'],
                modification='Qualify one known-ambiguous Dyadic annotation from prior compiler evidence; all runtime and proof reasoning unchanged.',
                mechanism='Append-only high-N native UInt32 numerical round-trip proof attempt; no runtime candidate.',
                validation_mode='statement-only', proof_status='NOT_COMPILED', performance='NOT_RUN',
                explicit_helper_audit=record['explicit_helper_audit'],
                helper_replay_and_standard_axiom_audit='NOT_RUN; original public specs do not reach appended helpers',
                scope='Pure candidate/proof source only; original B2 remains exact prefix. Statement pass must not be reported as helper replay or complete acceptance.')
(folder / 'manifest.json').write_bytes((json.dumps(manifest, ensure_ascii=False, indent=2)+'\n').encode())
print(json.dumps(dict(candidate=name, sha256=sha(source), bytes=len(source))))
