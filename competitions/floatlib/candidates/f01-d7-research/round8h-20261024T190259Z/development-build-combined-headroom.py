"""Create proof-source headroom in a new package; keep every runtime definition."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[4]
C = ROOT / 'competitions/floatlib/candidates'
inventory = json.loads((OUT / 'development-unused-proof-inventory.json').read_bytes())
source = ROOT / inventory['source']
raw = source.read_bytes()
assert hashlib.sha256(raw).hexdigest() == inventory['source_sha256'] == 'd94060b28aa4d374c16cdd0b8ee26ee7ba570155476bbf743877e4e3212ff277'
assert inventory['global_search_tactics_present'] is False
text = raw.decode()
selected = inventory['rows']
assert len(selected) == 32 and sum(row['bytes'] for row in selected) == 8473
previous_end = 0
for row in selected:
    start, end = row['character_start'], row['character_end']
    assert start >= previous_end and start < end
    block = text[start:end].encode()
    assert hashlib.sha256(block).hexdigest() == row['sha256'] and len(block) == row['bytes']
    assert re.match(r'^(?:theorem|lemma) ' + re.escape(row['name']) + r'\b', block.decode())
    assert '@[' not in block.decode() and '\nattribute ' not in block.decode()
    previous_end = end
parts, position = [], 0
for row in selected:
    parts.append(text[position:row['character_start']])
    position = row['character_end']
parts.append(text[position:])
result = ''.join(parts).encode()
assert len(raw) - len(result) == 8473
assert len(result) <= 256000
# Every deleted byte belongs to one explicitly inventoried proof declaration;
# all other source text, including definitions/options/imports/attribution, stays exact.
folder = C / 'f01-r14-dev-combined-headroom1'
assert not folder.exists()
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(result)
record = dict(candidate=folder.name, candidate_file='Kernel.lean', candidate_sha256=hashlib.sha256(result).hexdigest(),
              candidate_bytes=len(result), created_at_utc=datetime.now(timezone.utc).isoformat(), validation_mode='full-gate',
              proof_status='UNUSED_PROOF_PRUNING_NOT_COMPILED', performance='NOT_RUN',
              parent=source.parent.name, parent_sha256=hashlib.sha256(raw).hexdigest(),
              removed_proof_declarations=selected, removed_bytes=8473, bytes_remaining=256000 - len(result),
              runtime_definition_source_changed=False,
              mechanism='Same declared runtime as combined-slim1; remove32 explicit unreferenced, unattributed proof declarations to make room for actual add/mul reconstruction. This is source preparation, not a new optimization trial or statistical reset.',
              verification='Exact SHA-bound removal slices; no global-search tactics found in parent, immediate attributes/docstrings/scoped options excluded by conservative inventory. All remaining source bytes retained in order. Original full parent persists for lookup/restoration.',
              limits='Static identifier absence cannot replace Lean elaboration and original full gate. New exact source still needs compilation, four obligations, replay, axiom audit and full performance evidence. Any newly needed proof can be restored from original parent and its recorded slice.')
(folder / 'manifest.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
(OUT / 'development-combined-headroom-build.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({key: record[key] for key in ('candidate', 'candidate_sha256', 'candidate_bytes', 'bytes_remaining', 'runtime_definition_source_changed', 'proof_status')}))
