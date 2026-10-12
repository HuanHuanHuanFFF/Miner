"""Freeze a small R25 fast-family screen using the established public protocol."""
from pathlib import Path
import argparse, hashlib, json

ROOT = Path(__file__).resolve().parents[1]


def entry(name, path, control=True, formal=None, anchor='public595'):
    folder = ROOT / path
    row = {'name': name, 'path': path, 'control': control, 'anchor': anchor,
           'hashes': {f: hashlib.sha256((folder/f).read_bytes()).hexdigest()
                      for f in ('parse.rs', 'Parse.lean')}}
    if formal:
        row['formal_id'] = formal
    if not control:
        row.update(comparison_baseline='combo', native_decode_reference='combo')
    return row


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('label')
    ap.add_argument('candidates', nargs='+')
    ap.add_argument('--mode', choices=['native', 'standard', 'extract'], required=True)
    ap.add_argument('--blocks', type=int, default=2)
    ap.add_argument('--capture', default='evidence/round25/official-frontier-current/pareto-pages.json')
    ap.add_argument('--description', required=True)
    a = ap.parse_args()
    assert 1 <= len(a.candidates) <= 3 and 1 <= a.blocks <= 4
    assert all(x.startswith('r25-') for x in a.candidates)
    assert a.label.endswith('-native') == (a.mode == 'native')
    assert a.label.endswith('-extract') == (a.mode == 'extract')
    entries = [entry('probe3', 'candidates/probe3', formal='427', anchor='probe3'),
               entry('r3-432-fast3', 'candidates/r3-432-fast3', formal='453', anchor='r3-432-fast3'),
               entry('public432', 'references/round3-public-432', formal='432', anchor='public432')]
    if a.mode == 'native':
        entries.append(entry('public514', 'references/round13-public-514', formal='514', anchor='public514'))
    entries += [entry('public595', 'references/round21-public-595', formal='595'),
                entry('public595-shadow', 'references/round21-public-595'),
                entry('combo', 'candidates/r22-595-chain-halfhead')]
    entries += [entry(n, 'candidates/'+n, control=False) for n in a.candidates]
    names = [e['name'] for e in entries]
    spec = {'entries': entries, 'snapshot_pages': a.capture,
            'screen_blocks': a.blocks, 'refine_blocks': 0, 'shortlist': 0,
            'gate_candidates': [], 'gate_limit': 0,
            'extract_candidates': a.candidates if a.mode == 'extract' else [],
            'retain_extracted_lean': True, 'synthetic_validation': False,
            'synthetic_reference_candidates': [], 'research_synthetic_candidates': [],
            'cpu_diagnostics': False, 'native_only': a.mode == 'native',
            'native_encoder': a.mode == 'native',
            'native_encoder_references': ['public595', 'combo'] if a.mode == 'native' else [],
            'r18_role': 'discovery', 'description': a.description,
            'screen_orders': [names if i % 2 == 0 else list(reversed(names)) for i in range(a.blocks)],
            'r25_mode': a.mode, 'r25_expected_candidates': len(a.candidates)}
    out = ROOT / 'evidence/round25' / (a.label+'.json')
    assert not out.exists(), 'Frozen batches are immutable; use a new label for changes'
    out.write_bytes((json.dumps(spec, indent=2)+'\n').encode())
    print(json.dumps({'file': out.relative_to(ROOT).as_posix(), 'mode': a.mode,
                      'candidate_count': len(a.candidates), 'entries': len(entries)}))


if __name__ == '__main__':
    main()
