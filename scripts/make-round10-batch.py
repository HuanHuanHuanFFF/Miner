"""Freeze a named R10 experiment specification without launching anything."""
from pathlib import Path
import argparse
import hashlib
import json
import os
import re

ROOT = Path(__file__).resolve().parents[1]


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('batch')
    ap.add_argument('candidates', nargs='+')
    ap.add_argument('--extract', nargs='*', default=[])
    ap.add_argument('--gate', nargs='*', default=[])
    ap.add_argument('--synthetic', nargs='*', default=[])
    ap.add_argument('--forward-diagnostics', action='store_true')
    ap.add_argument('--finder-diagnostics', action='store_true')
    ap.add_argument('--blocks', type=int, choices=[1, 2, 3, 4], default=2)
    args = ap.parse_args()
    assert re.fullmatch(r'[a-z0-9-]{1,48}', args.batch)
    assert len(args.candidates) == len(set(args.candidates))
    assert len(args.extract) <= 3 and len(args.synthetic) <= 3
    assert all(n.startswith('r10-') and re.fullmatch(r'[a-z0-9-]+', n) for n in args.candidates)
    assert set(args.extract + args.gate + args.synthetic) <= set(args.candidates)
    old = json.loads((ROOT / 'evidence/round9/block-b.json').read_text())
    entries = [e for e in old['entries'] if e.get('control')]
    scalar = next(e for e in old['entries'] if e['name'] == 'r9-block-scalar').copy()
    scalar['control'] = True
    scalar.pop('expected_equivalent_to', None)
    entries.append(scalar)
    for name in args.candidates:
        path = ROOT / 'candidates' / name
        hashes = {f: hashlib.sha256((path / f).read_bytes()).hexdigest() for f in ['parse.rs', 'Parse.lean']}
        entries.append({'name': name, 'path': path.relative_to(ROOT).as_posix(),
                        'control': False, 'anchor': 'public361', 'hashes': hashes})
    spec = {'entries': entries, 'snapshot_pages': 'evidence/round10/official-start/pareto-pages.json',
            'screen_blocks': args.blocks, 'refine_blocks': 0, 'shortlist': len(args.candidates),
            'gate_candidates': args.gate, 'gate_limit': len(args.gate),
            'synthetic_validation': True, 'retain_extracted_lean': True,
            'cpu_diagnostics': False, 'extract_candidates': args.extract, 'cost_differential': False,
            'forward_diagnostics': args.forward_diagnostics, 'finder_diagnostics': args.finder_diagnostics,
            'research_synthetic_candidates': args.synthetic,
            'description': 'R10 bounded structural experiment; exact bytes frozen in this specification.',
            'selection_policy': 'Same-family 361 paired transfer; adverse max observed relative-time+2%, size max(family+0.01pp,public*1.008). Geometry is conditional, not formal admission or reward.'}
    target = ROOT / 'evidence/round10' / (args.batch + '.json')
    assert not target.exists(), 'Preserve old experiment specs; use a fresh batch label'
    target.write_text(json.dumps(spec, indent=2) + '\n')
    os.environ['ROUND4_SPEC_DIR'] = 'evidence/round10'
    from round4 import validate
    validate(args.batch)
    print(json.dumps({'batch': args.batch, 'entries': len(entries), 'candidates': args.candidates,
                      'extract': args.extract, 'gate': args.gate, 'blocks': args.blocks}))


if __name__ == '__main__':
    main()
