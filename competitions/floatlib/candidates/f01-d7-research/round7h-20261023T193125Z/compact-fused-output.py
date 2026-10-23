"""Create one byte-checked compact 5b7d package for subsequent composition.

Only obsolete P1-P5 declarations and their proof consumer are removed. This
creates source headroom, not a claimed performance optimization. Exact new Lean
closure and full gate are required independently.
"""
from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
import argparse
import json

HERE = Path(__file__).resolve().parent
CS = HERE.parent.parent
SOURCE = CS / 'f01-d11-bmm-fused-output-proof3/Kernel.lean'
SOURCE_SHA = '5b7d926cf628c2d87042386834f7c1581b9a6aa7441af196453984b395534ba2'
DEST = CS / 'f01-d11-bmm-fused-output-compact'


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--write', action='store_true')
    args = ap.parse_args()
    source = SOURCE.read_bytes()
    assert sha256(source).hexdigest() == SOURCE_SHA
    inventory_path = HERE / 'review-source-headroom.json'
    inventory = json.loads(inventory_path.read_bytes())
    origin = (CS / 'f01-d11-bmm-fused-output/Kernel.lean').read_bytes()
    assert sha256(origin).hexdigest() == inventory['base']['sha256']
    edits = []
    for block in inventory['blocks']:
        if block['id'] not in {'P1', 'P2', 'P3', 'P4', 'P5'}:
            continue
        a, b = block['base_byte_offsets_half_open']
        old = origin[a:b]
        assert sha256(old).hexdigest() == block['sha256']
        assert source.count(old) == 1
        at = source.index(old)
        edits.append((at, at + len(old), old, b''))
    assert len(edits) == 5
    rewire = inventory['rewire']
    first, last = rewire['original_lines']
    old = b''.join(origin.splitlines(keepends=True)[first - 1:last])
    assert sha256(old).hexdigest() == rewire['original_sha256']
    new = old
    for change in rewire['four_exact_substitutions']:
        before, after = change['old'].encode(), change['new'].encode()
        assert new.count(before) == 1
        new = new.replace(before, after, 1)
    assert sha256(new).hexdigest() == rewire['proposed_proof_sha256']
    assert source.count(old) == 1
    at = source.index(old)
    edits.append((at, at + len(old), old, new))
    edits.sort()
    assert all(a[1] <= b[0] for a, b in zip(edits, edits[1:]))
    chunks, inverse = [], []
    cursor = new_cursor = 0
    for start, stop, old, new in edits:
        kept = source[cursor:start]
        chunks.extend([kept, new])
        new_cursor += len(kept)
        inverse.append((new_cursor, new_cursor + len(new), new, old))
        new_cursor += len(new)
        cursor = stop
    chunks.append(source[cursor:])
    data = b''.join(chunks)
    restored = data
    for start, stop, new, old in reversed(inverse):
        assert restored[start:stop] == new
        restored = restored[:start] + old + restored[stop:]
    assert restored == source
    assert len(data) == 236400 and len(source) - len(data) == 9441
    for name in (b'RowOutput.', b'tileResults', b'outputFromTiles',
                 b'inlineDecodeC', b'Packed10.core', b'bmmRows',
                 b'bmmR4_spec', b'RowStream.core_eq '):
        assert name not in data
    for forbidden in (b'sorry', b'axiom ', b'unsafe ', b'extern ',
                      b'implemented_by', b'set_option'):
        assert forbidden not in data
    manifest = json.loads((SOURCE.parent / 'manifest.json').read_bytes())
    manifest.update(candidate=DEST.name, candidate_sha256=sha256(data).hexdigest(),
                    candidate_bytes=len(data), created_at_utc=datetime.now(timezone.utc).isoformat(),
                    parent=SOURCE.parent.name, parent_sha256=SOURCE_SHA,
                    mechanism='Exact obsolete P1-P5 removal and proof rewire; retained runtime definition bodies unchanged. Source headroom only.',
                    change='Compact exact accepted5b7d source for later composition; no compiler or proof resource change.',
                    proof='New rewire and dependency closure require exact statement/full gate; no prior acceptance inheritance.',
                    proof_status='NOT_RUN', performance='UNKNOWN')
    report = {'parent_sha256': SOURCE_SHA, 'candidate_sha256': manifest['candidate_sha256'],
              'bytes': len(data), 'net_saved_bytes': 9441,
              'inventory_sha256': sha256(inventory_path.read_bytes()).hexdigest(),
              'inverse_restores_parent': True, 'retained_runtime_bodies_unchanged': True,
              'all_5b7d_proof_repairs_preserved': True,
              'edits': [{'old_start': a, 'old_end': b, 'old_sha256': sha256(old).hexdigest(),
                         'new_sha256': sha256(new).hexdigest()} for a, b, old, new in edits],
              'Lean_full_gate_performance': 'NOT_RUN', 'Kernel_written': args.write}
    if args.write:
        assert not DEST.exists(), 'Never overwrite saved candidate'
        DEST.mkdir()
        (DEST / 'Kernel.lean').write_bytes(data)
        for name, value in [('manifest.json', manifest), ('compact-evidence.json', report)]:
            (DEST / name).write_text(json.dumps(value, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(report, ensure_ascii=False))


if __name__ == '__main__':
    main()
