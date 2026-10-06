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
MODES = ['halfpass', 'samplemore', 'livehuff', 'tinydepth32', 'tinypass8', 'sampleguard']
ROW0 = [0, 16, 260, 7, 4, 4, 2, 0, 0]
ROW4 = [0, 48, 260, 9, 2, 9, 23, 0, 0]
SAMPLEMORE_PARENT = 'r4-alt299-samplemore'
SAMPLEMORE_PARENT_HASHES = {
    'parse.rs': 'c84a2c379d145277cd0f6e3f9d6906772f91ea7f9bb39b7241dd4b5f8582b3de',
    'Parse.lean': '9b77b3523cbf7044aaffa11b6fd9676b3615ca4bf148b43b3cb92da4073b3e3d',
    'manifest.json': 'c640c8a1d61208b7f10c2065a156781ed0f9a1634e565c85c8fbd8f10478fd12',
}


def sha(data):
    return hashlib.sha256(data).hexdigest()


def samplemore_row(row):
    result = row.copy()
    if result[0] == 0:
        first, fsample, later, encoded = result[3:7]
        rotation, sample = encoded // 16, encoded % 16
        result[4] = max(fsample, max(0, first - 2))
        result[6] = 16 * rotation + max(sample, max(0, later - 2))
        assert result[1:3] == row[1:3] and result[6] // 16 == rotation
    return result


def replace_cfg_rows(source, match, before_rows, after_rows, comment_overrides):
    cfg = match.group(1)
    row_matches = list(re.finditer(r'(?m)^([ \t]*)\[(?P<values>[\d, ]+)\](?P<tail>[^\r\n]*)$', cfg))
    assert len(row_matches) == len(before_rows) == len(after_rows) == 16
    parts = []
    cursor = 0
    for i, row_match in enumerate(row_matches):
        parts.append(cfg[cursor:row_match.start()])
        if after_rows[i] == before_rows[i]:
            parts.append(row_match.group(0))
        else:
            tail = comment_overrides.get(i, row_match.group('tail'))
            values = ', '.join(map(str, after_rows[i]))
            parts.append(f"{row_match.group(1)}[{values}]{tail}")
        cursor = row_match.end()
    parts.append(cfg[cursor:])
    return source[:match.start(1)] + ''.join(parts) + source[match.end(1):]


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
            elif mode in ('samplemore', 'sampleguard') and row[0] == 0:
                if mode == 'sampleguard' and i in (0, 4):
                    pass
                else:
                    row[:] = samplemore_row(row)
            elif row[0] == 0:
                first, fsample, later, encoded = row[3:7]
                rotation, sample = encoded // 16, encoded % 16
                if mode == 'halfpass':
                    row[3] = max(1, (first + 1) // 2)
                    row[4] = min((fsample + 1) // 2, row[3] - 1)
                    row[5] = max(1, (later + 1) // 2)
                    row[6] = 16 * rotation + min((sample + 1) // 2, row[5] - 1)
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
        elif mode == 'sampleguard':
            assert rows[0] == ROW0 and rows[4] == ROW4
            parent_rows = [samplemore_row(row) for row in rows]
            assert parent_rows[0] != ROW0 and parent_rows[4] != ROW4
            assert edited[0] == ROW0 and edited[4] == ROW4
            assert edited == [rows[i] if i in (0, 4) else parent_rows[i]
                              for i in range(len(rows))]
            assert [c['row'] for c in changes] == [7, 9, 10, 12]
            parent_row_diffs = [
                {'row': i, 'from': parent_rows[i], 'to': edited[i]}
                for i in range(len(rows)) if parent_rows[i] != edited[i]
            ]
            assert [c['row'] for c in parent_row_diffs] == [0, 4]
            parent_dir = ROOT / 'candidates' / SAMPLEMORE_PARENT
            assert {n: sha((parent_dir / n).read_bytes()) for n in SAMPLEMORE_PARENT_HASHES} == SAMPLEMORE_PARENT_HASHES
            comments = {
                7: ',      // 7  A (depth 36 skip 260 first 9/9 passes 6/4, rotated samples)',
                9: ',     // 9  A (depth 64 skip 260 first 12/10 passes 12/10)',
                10: ',    // 10 A (depth 64 skip 260 first 12/10 passes 12/10)',
                12: ',     // 12 A (depth 32 skip 260 first 8/6 passes 16/14, rotated samples)',
            }
            text = replace_cfg_rows(source, match, rows, edited, comments)
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
                     'Change only CFG row 0 engine-A first full-pass budget from 7 to 8; keep first sampled-pass count at 4. The existing general classifier routes every input shorter than 32768 bytes to class 0 and configuration row 0; no exact-size, file-name or sample-specific route is added.' if mode == 'tinypass8' else
                     'Starting from samplemore, restore original CFG rows 0 and 4; retain samplemore settings on every other row. Row 0 preserves the original short-span sampled-pass fallback cadence; row 4 preserves the original sampling setting for structured binary. Row 0 is reached by the general <32768-byte classifier route (VERIFIED); associating row 4 with the measured structured-binary losses is INFERRED and needs a fresh per-file route/profile check. No file-name or exact-size routing is added.')
        proof_status = ('Copied original Parse.lean bytes; all CFG values remain within the visible generic upper/engine-A skip bounds, but fresh extraction, Lean, axiom-whitelist and round-trip checks are UNKNOWN.' if mode == 'sampleguard' else
                        'Copied inherited Parse.lean bytes; row 0 stays within its generic CFG upper/skip bounds, but fresh extraction, Lean, axiom-whitelist and round-trip checks are UNKNOWN.' if mode in ('tinydepth32', 'tinypass8') else
                        'Exact inherited proof; CFG bounds use decide, but new extraction, Lean, axiom whitelist and round trip are UNKNOWN.' if mode != 'livehuff' else
                        'Exact inherited proof; modified cost helper needs new extraction, Lean, axiom whitelist and round trip, all UNKNOWN.')
        performance = ('UNKNOWN for this variant. It has not been screened. The prior samplemore attribution is recorded separately and does not predict sampleguard.' if mode == 'sampleguard' else
                       'UNKNOWN. Hypothesis only: saving a few bytes on a small input may have geometric objective value; no measurement has been made, and private migration is UNKNOWN.' if mode in ('tinydepth32', 'tinypass8') else
                       'UNKNOWN. Different costs can change both plans and block boundaries; no compression or speed gain is assumed.' if mode == 'livehuff' else
                       'UNKNOWN. Sample passes fall back to full passes on short spans; savings cannot be inferred from configured counts.')
        parent_info = ({
            'candidate': SAMPLEMORE_PARENT,
            'parent_sha256': SAMPLEMORE_PARENT_HASHES['parse.rs'],
            'parent_manifest_sha256': SAMPLEMORE_PARENT_HASHES['manifest.json'],
            'row_diffs_from_samplemore': parent_row_diffs,
        } if mode == 'sampleguard' else {})
        measured_attribution = ({
            'status': 'VERIFIED from paired public screen raw file records; applies to samplemore, not sampleguard.',
            'run_id': 37524045017,
            'corpus_files': 28,
            'screen_blocks': [1, 2],
            'source_files': [
                'evidence/round4/37524045017/screen/round1-public299.jsonl',
                'evidence/round4/37524045017/screen/round1-r4-alt299-samplemore.jsonl',
                'evidence/round4/37524045017/screen/round2-public299.jsonl',
                'evidence/round4/37524045017/screen/round2-r4-alt299-samplemore.jsonl',
            ],
            'samplemore_mean_file_size_loss_pp_vs_public299': 0.003942280933,
            'major_positive_file_deltas': [
                {'file': 'machine-code.bin', 'extra_bytes': 387, 'mean_file_size_loss_pp': 0.002764285714},
                {'file': 'binary.db.bin', 'extra_bytes': 4, 'mean_file_size_loss_pp': 0.000028571429},
                {'file': 'tiny-app.log', 'extra_bytes': 1, 'mean_file_size_loss_pp': 0.000127551020},
                {'file': 'tiny-config.json.txt', 'extra_bytes': 1, 'mean_file_size_loss_pp': 0.000297619048},
            ],
            'row0_route': 'VERIFIED: classify returns class 0 for input length < 32768 and CLASS_CFG[0] is row 0; both tiny files are below the threshold.',
            'row4_route': 'INFERRED: row 4 is the structured-binary configuration; per-file class/row attribution for machine-code.bin and binary.db.bin needs a fresh profile.',
        } if mode == 'sampleguard' else {})
        manifest = {'candidate': name, 'base': BASE.relative_to(ROOT).as_posix(), 'base_hashes': HASHES,
                    'attribution': 'Derivative of officially published submission 299, hotkey 5En8AugiKmLmnoaWzrGMz9oWMbQYvekaMvZSjViLTLhrrq4E; provenance retained.',
                    'mechanism': mechanism,
                    'changes': changes, 'hashes': {n: sha(b) for n, b in output.items()},
                    **({'parent': parent_info, 'measured_parent_attribution': measured_attribution} if mode == 'sampleguard' else {}),
                    **({'source_changes': source_changes} if source_changes else {}),
                    'proof_status': proof_status,
                    'performance': performance,
                    **({'gain_hypothesis': ('Restore samplemore losses on the small-input and structured-binary routes while retaining its settings elsewhere; the route-to-file link is only partly verified and the variant outcome is unmeasured.'
                                           if mode == 'sampleguard' else
                                           'A few bytes saved on one or more small-input files could matter under the geometric objective; this remains unmeasured.'),
                        'private_migration': 'UNKNOWN'} if mode in ('tinydepth32', 'tinypass8', 'sampleguard') else {}),
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
