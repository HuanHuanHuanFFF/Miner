"""Prepare source-sized word-add fields; never claim uncompiled source accepted."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[4]
C = ROOT / 'competitions/floatlib/candidates'
sha = lambda raw: hashlib.sha256(raw).hexdigest()
parent = C / 'f01-r14-dev-combined-headroom3/Kernel.lean'
raw = parent.read_bytes()
assert sha(raw) == 'd2b8a436c051c035d1e206f1b8bdec03c2840c0324e459436bb886e5fae32274'
text = raw.decode()
fallback = text.index('@[inline] def mulBeforeExponent ')
start = text.index('\nend Submission\n', fallback)
finish = text.index('theorem add_eq :', start)
removed = text[start:finish].encode()
assert removed.count(b'namespace Submission.R14DIntegerNormal') == 1
assert removed.count(b'R14ExponentShift.guardedMul mulBeforeExponent x y') == 1
text = text[:start] + '\n\n' + text[finish:]
assert text.count('mulBeforeExponent') == 4
text = text.replace('mulBeforeExponent', 'mul')
assert 'R14' not in text[:text.index('def referenceBmm ')]
base_path = OUT / 'development-word-add-slim-parent1.lean'
assert not base_path.exists()
base_path.write_bytes(text.encode())
support = json.loads((C / 'f01-r14-dev-word-add-support1/manifest.json').read_bytes())
pieces = []
rows = []
for component in support['components']:
    path = ROOT / component['path']
    data = path.read_bytes()
    assert sha(data) == component['sha256'] and len(data) == component['bytes']
    pieces.append(data)
    rows.append(component)
fields = OUT / 'development-word-add-fields1.lean'
pieces.append(fields.read_bytes())
rows.append(dict(path=fields.relative_to(ROOT).as_posix(), bytes=fields.stat().st_size,
                 sha256=sha(fields.read_bytes())))
result = text.encode() + b'\n' + b'\n'.join(pieces)
record = dict(created_at_utc=datetime.now(timezone.utc).isoformat(),
              parent=parent.parent.name, parent_sha256=sha(raw),
              slim_parent=dict(path=base_path.relative_to(ROOT).as_posix(),
                               sha256=sha(text.encode()), bytes=len(text.encode())),
              removed_mul_component=dict(bytes=len(removed), sha256=sha(removed)),
              restored_original_mul=True,
              components=rows, candidate_bytes=len(result), bytes_remaining=256000 - len(result),
              candidate_sha256=sha(result), candidate_file='Kernel.lean',
              validation_mode='statement-only', proof_status='WORD_ADD_FIELDS_NOT_COMPILED',
              performance='NOT_RUN', public_add_changed=False,
              scope='Full narrow add word-field source attempt with retained public scalar add/mul; the pre-existing new thin-cache/p8 BMM route remains. Not an optimized-add candidate yet.',
              remaining='Original-order raw Model.add bridge, core_spec, guardedAdd_spec, placement before public add, exact-source gate and whole-cost measurements.')
budget = OUT / 'development-word-add-fields-budget1.json'
assert not budget.exists()
budget.write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
assert len(result) <= 256000, record
folder = C / 'f01-r14-dev-word-add-fields1'
assert not folder.exists()
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(result)
record['candidate'] = folder.name
(folder / 'manifest.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({k: record[k] for k in ('candidate', 'candidate_sha256', 'candidate_bytes', 'bytes_remaining', 'proof_status')}))
