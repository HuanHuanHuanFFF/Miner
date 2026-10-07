"""Isolate the second backward-extension endpoint in newly enabled D routes."""
from pathlib import Path
import argparse
import hashlib
import importlib.util
import json

ROOT = Path(__file__).resolve().parents[1]


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--check', action='store_true')
    args = ap.parse_args()
    spec = importlib.util.spec_from_file_location('r7tables', ROOT / 'scripts/make-round7-middle.py')
    module = importlib.util.module_from_spec(spec); spec.loader.exec_module(module)
    parent = ROOT / 'candidates/r7-mid361-block1'
    old = json.loads((parent / 'manifest.json').read_text())
    raw = {n: (parent / n).read_bytes() for n in ('parse.rs', 'Parse.lean')}
    assert all(hashlib.sha256(raw[n]).hexdigest() == old['hashes'][n] for n in raw)
    def transform(row, values):
        if 5 <= row <= 10:
            assert values[7] == 1
            values[7] = 0
        return values
    source, edit, rows = module.table(raw['parse.rs'].decode(), 'D_KNOBS', 17, transform)
    assert source.replace(edit[1], edit[0], 1).encode() == raw['parse.rs']
    assert len(rows) == 6
    name = 'r9-push-single'
    files = {'parse.rs': source.encode(), 'Parse.lean': raw['Parse.lean']}
    manifest = {'candidate': name, 'parent': 'candidates/r7-mid361-block1', 'parent_hashes': old['hashes'],
                'base_submission_id': '361', 'attribution': old['attribution'], 'parameter_rows': rows,
                'hashes': {n: hashlib.sha256(b).hexdigest() for n, b in files.items()}, 'bytes': {n: len(b) for n, b in files.items()},
                'mechanism': 'Disable only the cheapest-shorter-end extra backward pushes in the six newly enabled D rows. Full-end backward pushes and original D routes remain.',
                'audit': 'Reverse one declared table edit restores parent Rust exactly; proof bytes unchanged.',
                'proof_status': 'UNKNOWN pending fresh original gate; arbitrary parameter totality is a source observation, not a verdict.',
                'performance_status': 'UNKNOWN; deliberate quality/time tradeoff, not a token-equivalence candidate.'}
    files['manifest.json'] = (json.dumps(manifest, indent=2) + '\n').encode()
    dest = ROOT / 'candidates' / name
    if args.check:
        assert all((dest / n).read_bytes() == b for n, b in files.items())
    else:
        dest.mkdir(exist_ok=True)
        for n, b in files.items():
            assert not (dest / n).exists() or (dest / n).read_bytes() == b
            (dest / n).write_bytes(b)
    print(json.dumps({'candidate': name, 'hashes': manifest['hashes']}))


if __name__ == '__main__':
    main()
