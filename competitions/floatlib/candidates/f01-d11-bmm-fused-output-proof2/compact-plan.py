"""Exact byte-checked headroom transform. Default is a report-only dry run.

No Lean build is performed. A caller must explicitly pass --emit-dir to create
one new candidate, after the input's statement feedback has been considered.
"""
from argparse import ArgumentParser
from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
import json

HERE = Path(__file__).resolve().parent
CANDIDATES = HERE.parent
ROUND = CANDIDATES / 'f01-d7-research' / 'round7h-20261023T193125Z'
DEFAULT_SHA = '2c73622e91fa0edef0e37a22bac1724190451479b0dceeee04ef5d181cc811ed'

parser = ArgumentParser(description=__doc__)
parser.add_argument('--source', type=Path, default=HERE / 'Kernel.lean')
parser.add_argument('--source-sha256', default=DEFAULT_SHA)
parser.add_argument('--emit-dir', type=Path)
args = parser.parse_args()

inventory_path = ROUND / 'review-source-headroom.json'
inventory = json.loads(inventory_path.read_text(encoding='utf-8'))
origin = (CANDIDATES / 'f01-d11-bmm-fused-output' / 'Kernel.lean').read_bytes()
assert sha256(origin).hexdigest() == inventory['base']['sha256']
source = args.source.resolve().read_bytes()
assert sha256(source).hexdigest() == args.source_sha256, 'Source SHA mismatch'

edits = []
removed = []
for block in inventory['blocks']:
    if block['id'] not in {'P1', 'P2', 'P3', 'P4', 'P5'}:
        continue
    begin, end = block['base_byte_offsets_half_open']
    old = origin[begin:end]
    assert len(old) == block['bytes_including_each_line_LF']
    assert sha256(old).hexdigest() == block['sha256']
    assert source.count(old) == 1, f"Changed/missing/nonunique block {block['id']}"
    at = source.index(old)
    edits.append((at, at + len(old), old, b''))
    removed.append({k: block[k] for k in ('id', 'name', 'sha256', 'bytes_including_each_line_LF')})

rewire = inventory['rewire']
first, last = rewire['original_lines']
old_proof = b''.join(origin.splitlines(keepends=True)[first - 1:last])
assert len(old_proof) == rewire['original_bytes']
assert sha256(old_proof).hexdigest() == rewire['original_sha256']
assert source.count(old_proof) == 1
new_proof = old_proof
for replacement in rewire['four_exact_substitutions']:
    old = replacement['old'].encode()
    new = replacement['new'].encode()
    assert new_proof.count(old) == 1
    new_proof = new_proof.replace(old, new, 1)
assert len(new_proof) == rewire['proposed_proof_bytes']
assert sha256(new_proof).hexdigest() == rewire['proposed_proof_sha256']
at = source.index(old_proof)
edits.append((at, at + len(old_proof), old_proof, new_proof))

edits.sort()
assert all(a[1] <= b[0] for a, b in zip(edits, edits[1:])), 'Overlapping byte edits'
chunks = []
cursor = 0
inverse_edits = []
new_cursor = 0
for start, stop, old, new in edits:
    retained = source[cursor:start]
    chunks.extend([retained, new])
    new_cursor += len(retained)
    inverse_edits.append((new_cursor, new_cursor + len(new), new, old))
    new_cursor += len(new)
    cursor = stop
chunks.append(source[cursor:])
proposed = b''.join(chunks)

# Reconstruct the exact input, including deleted helper definitions and proofs.
restored = proposed
for start, stop, new, old in reversed(inverse_edits):
    assert restored[start:stop] == new
    restored = restored[:start] + old + restored[stop:]
assert restored == source
assert len(proposed) <= 256000
assert len(source) - len(proposed) == 9441
for forbidden in (b'sorry', b'axiom ', b'unsafe ', b'extern ', b'implemented_by'):
    assert forbidden not in proposed
assert proposed.startswith(b'import ContractTensor\n')
assert proposed.count(b'\nimport ') == 0

# Removed names must not survive in executable/proof text. Historical comments
# mentioning bmmR4 are intentionally retained and checked against the inventory.
for name in (b'RowOutput.', b'tileResults', b'outputFromTiles', b'inlineDecodeC',
             b'Packed10.core', b'bmmRows', b'bmmR4_spec', b'RowStream.core_eq '):
    assert name not in proposed, f'Remaining consumer of removed name {name!r}'
bmm_r4_lines = [line.decode() for line in proposed.splitlines() if b'bmmR4' in line]
expected_comments = [x['text'] for x in inventory['remaining_references_after_B_deletions_before_rewire']['bmmR4']
                     if x['classification'] == 'PRESERVED_HISTORICAL_COMMENT']
assert bmm_r4_lines == expected_comments

report = {
    'state': 'PASS_MECHANICAL_DRY_RUN_NOT_LEAN_VERIFIED',
    'updated_at_utc': datetime.now(timezone.utc).isoformat(),
    'source': str(args.source.resolve()),
    'source_sha256': sha256(source).hexdigest(),
    'source_bytes': len(source),
    'inventory_sha256': sha256(inventory_path.read_bytes()).hexdigest(),
    'removed_blocks': removed,
    'rewire': 'bmmPackedBase_spec to existing RowStream.core_eq_reference and referenceBmm_spec',
    'rewire_delta_bytes': len(new_proof) - len(old_proof),
    'projected_sha256': sha256(proposed).hexdigest(),
    'projected_bytes': len(proposed),
    'projected_headroom': 256000 - len(proposed),
    'net_saved_bytes': len(source) - len(proposed),
    'inverse_transform_recovers_source_bytes': True,
    'retained_runtime_definition_bytes_changed': False,
    'author_provenance_comments_changed': False,
    'historical_bmmR4_comments_retained': bmm_r4_lines,
    'Lean_dependency_closure': 'INFERRED_NOT_RUN',
    'full_gate_and_timing': 'NOT_RUN',
    'new_Kernel_written': False,
}

if args.emit_dir:
    destination = args.emit_dir.resolve()
    assert destination.parent == CANDIDATES.resolve()
    assert destination.name.startswith('f01-d11-bmm-fused-output')
    assert not destination.exists(), 'Never overwrite a candidate'
    destination.mkdir()
    (destination / 'Kernel.lean').write_bytes(proposed)
    manifest = json.loads((HERE / 'manifest.json').read_text(encoding='utf-8'))
    manifest.update({
        'candidate': destination.name,
        'candidate_sha256': report['projected_sha256'],
        'candidate_bytes': len(proposed),
        'created_at_utc': report['updated_at_utc'],
        'parent': args.source.parent.name,
        'parent_sha256': report['source_sha256'],
        'change': 'Remove exact obsolete materialized-output helper chain P1-P5, preserving runtime entry definitions; rewire bmmPackedBase_spec directly to existing reference equality. No runtime speedup claim.',
        'proof_status': 'NOT_RUN',
    })
    (destination / 'manifest.json').write_text(json.dumps(manifest, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')
    report['new_Kernel_written'] = True
    report['destination'] = str(destination)
    (destination / 'compact-evidence.json').write_text(json.dumps(report, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')

(ROUND / 'review-output-compact-dry-run.json').write_text(json.dumps(report, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')
print(json.dumps({key: report[key] for key in ('state', 'source_sha256', 'projected_sha256', 'projected_bytes', 'projected_headroom', 'new_Kernel_written')}))
