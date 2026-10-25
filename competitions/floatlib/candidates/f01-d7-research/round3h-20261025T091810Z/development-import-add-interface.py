"""Import exact pure proof fragments for one statement-only interface probe."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
WORKER = HERE / 'astra-workers/scalar-representation/next-add-u32'
sha = lambda raw: hashlib.sha256(raw).hexdigest()
record = json.loads((WORKER / 'probe-manifest.json').read_bytes())
parent = ROOT / 'competitions/floatlib/candidates/f01-r16-dev-native-repack1/Kernel.lean'
assert sha(parent.read_bytes()) == record['parent']['sha256']
pieces = []
source = parent.read_bytes()
for row in record['pieces']:
    raw = (WORKER / row['path']).read_bytes()
    assert sha(raw) == row['sha256'] and len(raw) == row['bytes']
    target = HERE / ('development-add-interface-' + row['path'])
    assert not target.exists()
    target.write_bytes(raw)
    pieces.append(dict(path=target.relative_to(ROOT).as_posix(), sha256=sha(raw), bytes=len(raw)))
    source += b'\n' + raw
assert source == (WORKER / record['probe']['path']).read_bytes()
assert sha(source) == record['probe']['sha256'] == '41241a3353203ea581a365dfd4f2f6b39e35badd08030a1d4ea5b6dd32881625'
assert len(source) == 253667 < 256000
name = 'f01-r16-dev-add-interface1'
folder = ROOT / 'competitions/floatlib/candidates' / name
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(source)
manifest = dict(candidate=name, candidate_file='Kernel.lean', candidate_sha256=sha(source),
                candidate_bytes=len(source), created_at_utc=datetime.now(timezone.utc).isoformat(),
                parent=parent.parent.name, parent_sha256=sha(parent.read_bytes()), components=pieces,
                mechanism='Append-only UInt32 native-rounding and low-normalization proof interface; no ADD runtime change.',
                validation_mode='statement-only', proof_status='NOT_COMPILED',
                unused_helper_kernel_replay_and_axioms='NOT_RUN; original four specs do not reach appended helpers',
                performance='NOT_RUN; this is not a new timed ADD entry',
                scope='Only pure proof source is imported; no research conversation or held R14 export.')
(folder / 'manifest.json').write_bytes((json.dumps(manifest, ensure_ascii=False, indent=2)+'\n').encode())
print(json.dumps(dict(candidate=name, sha256=sha(source), bytes=len(source))))
