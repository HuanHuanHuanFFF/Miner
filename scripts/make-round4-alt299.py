"""Controlled planner-budget experiments from official public submission 299.

The content classifier and checked emitter are unchanged. This only creates
research inputs; copied Lean is not fresh proof acceptance.
"""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'references/round4-public-299'
HASHES = {'parse.rs': '71314c4da7ccd29331a360bce9be8697857109c66adc87d3480eeaa22930625d',
          'Parse.lean': '9b77b3523cbf7044aaffa11b6fd9676b3615ca4bf148b43b3cb92da4073b3e3d'}
MODES = ['halfpass', 'samplemore', 'livehuff', 'tinydepth32', 'tinypass8']
ROW0 = [0, 16, 260, 7, 4, 4, 2, 0, 0]


def sha(data):
    return hashlib.sha256(data).hexdigest()


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--check', action='store_true')
    ap.add_argument('--only', nargs='+', choices=MODES)
    args = ap.parse_args()
    files = {n: (BASE / n).read_bytes() for n in HASHES}
    assert {n: sha(b) for n, b in files.items()} == HASHES
    source = files['parse.rs'].decode().replace('\r\n', '\n')
    match = re.search(r'pub const CFG: \[\[usize; 9\]; 16\] = \[(.*?)\n\];', source, re.S)
    assert match is not None
    rows = [[int(x.strip()) for x in s.split(',')] for s in re.findall(r'\[([\d, ]+)\]', match[1])]
    assert len(rows) == 16 and all(len(r) == 9 for r in rows)
    for mode in args.only or MODES:
        name = 'r4-alt299-' + mode
        edited = [r.copy() for r in rows]
        changes = []
        for i, (old, row) in enumerate(zip(rows, edited, strict=True)):
            if mode == 'tinydepth32':
                if i == 0:
                    assert old == ROW0
                    row[1] = 32
            elif mode == 'tinypass8':
                if i == 0:
                    assert old == ROW0 and old[3:5] == [7, 4]
                    row[3] = 8
                    assert row[4] == 4
            elif row[0] == 0:
                first, fsample, later, encoded = row[3:7]
                rotation, sample = encoded // 16, encoded % 16
                if mode == 'halfpass':
                    row[3] = max(1, (first + 1) // 2)
                    row[4] = min((fsample + 1) // 2, row[3] - 1)
                    row[5] = max(1, (later + 1) // 2)
                    row[6] = 16 * rotation + min((sample + 1) // 2, row[5] - 1)
                elif mode == 'samplemore':
                    row[4] = max(fsample, max(0, first - 2))
                    row[6] = 16 * rotation + max(sample, max(0, later - 2))
                assert row[1:3] == old[1:3] and row[6] // 16 == rotation
            assert all(0 <= x <= 65536 for x in row)
            if row != old:
                changes.append({'row': i, 'before': old, 'after': row})
        if mode in ('tinydepth32', 'tinypass8'):
            assert changes == [{'row': 0, 'before': ROW0,
                                'after': edited[0]}]
            assert all(edited[i] == rows[i] for i in range(1, len(rows)))
            old_line = '    [0, 16, 260, 7, 4, 4, 2, 0, 0],       // 0  A (depth 16 skip 260 first 7/4 passes 4/2)'
            new_line = ('    [0, 32, 260, 7, 4, 4, 2, 0, 0],       // 0  A (depth 32 skip 260 first 7/4 passes 4/2)'
                        if mode == 'tinydepth32' else
                        '    [0, 16, 260, 8, 4, 4, 2, 0, 0],       // 0  A (depth 16 skip 260 first 8/4 passes 4/2)')
            assert source.count(old_line) == 1
            text = source.replace(old_line, new_line, 1)
        else:
            body = '\n' + '\n'.join('    [' + ', '.join(map(str, r)) + '],' for r in edited)
            text = source[:match.start(1)] + body + source[match.end(1):]
        source_changes = []
        if mode == 'livehuff':
            text = source
            for old, new in [('lf[z] = lf0[z].wrapping_add(1);', 'lf[z] = lf0[z];'),
                             ('dd[i] = df[i].wrapping_add(1);', 'dd[i] = df[i];')]:
                assert text.count(old) == 1
                text = text.replace(old, new, 1)
                source_changes.append({'before': old, 'after': new})
        output = {'parse.rs': text.encode(), 'Parse.lean': files['Parse.lean']}
        mechanism = ('Halve only engine A first/later refinement budgets; halve sampled counts and retain rotation, finder depths, classifier and emitter.' if mode == 'halfpass' else
                     'Keep pass counts, search and routing; where the original A configuration used more than two final full passes, replace earlier ones with sampled passes and retain two final full passes.' if mode == 'samplemore' else
                     'In engine A Huffman refinement only, use actual live frequencies instead of adding one to every symbol; retain the existing unseen-symbol cost fallback, effort, classifier and checked emitter. This still is not the official package-merge/header/block-choice cost model.' if mode == 'livehuff' else
                     'Change only CFG row 0 engine-A depth from 16 to 32. The existing general classifier routes every input shorter than 32768 bytes to class 0 and configuration row 0; no exact-size, file-name or sample-specific route is added.' if mode == 'tinydepth32' else
                     'Change only CFG row 0 engine-A first full-pass budget from 7 to 8; keep first sampled-pass count at 4. The existing general classifier routes every input shorter than 32768 bytes to class 0 and configuration row 0; no exact-size, file-name or sample-specific route is added.')
        proof_status = ('Copied inherited Parse.lean bytes; row 0 stays within its generic CFG upper/skip bounds, but fresh extraction, Lean, axiom-whitelist and round-trip checks are UNKNOWN.' if mode in ('tinydepth32', 'tinypass8') else
                        'Exact inherited proof; CFG bounds use decide, but new extraction, Lean, axiom whitelist and round trip are UNKNOWN.' if mode != 'livehuff' else
                        'Exact inherited proof; modified cost helper needs new extraction, Lean, axiom whitelist and round trip, all UNKNOWN.')
        performance = ('UNKNOWN. Hypothesis only: saving a few bytes on a small input may have geometric objective value; no measurement has been made, and private migration is UNKNOWN.' if mode in ('tinydepth32', 'tinypass8') else
                       'UNKNOWN. Different costs can change both plans and block boundaries; no compression or speed gain is assumed.' if mode == 'livehuff' else
                       'UNKNOWN. Sample passes fall back to full passes on short spans; savings cannot be inferred from configured counts.')
        manifest = {'candidate': name, 'base': BASE.relative_to(ROOT).as_posix(), 'base_hashes': HASHES,
                    'attribution': 'Derivative of officially published submission 299, hotkey 5En8AugiKmLmnoaWzrGMz9oWMbQYvekaMvZSjViLTLhrrq4E; provenance retained.',
                    'mechanism': mechanism,
                    'changes': changes, 'hashes': {n: sha(b) for n, b in output.items()},
                    **({'source_changes': source_changes} if source_changes else {}),
                    'proof_status': proof_status,
                    'performance': performance,
                    **({'gain_hypothesis': 'A few bytes saved on one or more small-input files could matter under the geometric objective; this remains unmeasured.',
                        'private_migration': 'UNKNOWN'} if mode in ('tinydepth32', 'tinypass8') else {}),
                    'formal_submission_sent': False}
        output['manifest.json'] = (json.dumps(manifest, indent=2) + '\n').encode()
        dest = ROOT / 'candidates' / name
        if args.check:
            assert all((dest / n).read_bytes() == b for n, b in output.items()), name
        else:
            dest.mkdir(exist_ok=True)
            for n, b in output.items():
                (dest / n).write_bytes(b)
        print(name, manifest['hashes'], 'changed_rows', [c['row'] for c in changes])


if __name__ == '__main__':
    main()
