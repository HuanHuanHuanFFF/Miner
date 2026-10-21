"""Bind Round 8 helper proofs to the already-screened Rust candidates."""
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
    spec = importlib.util.spec_from_file_location('r8proof', ROOT / 'scripts/make-round8-proof.py')
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    for label in ('top', 'suffix'):
        parent_name = 'r8-mid361-cost-' + label
        parent = ROOT / 'candidates' / parent_name
        old = json.loads((parent / 'manifest.json').read_text())
        raw = {n: (parent / n).read_bytes() for n in ('parse.rs', 'Parse.lean')}
        assert all(hashlib.sha256(raw[n]).hexdigest() == old['hashes'][n] for n in raw)
        files = {'parse.rs': raw['parse.rs'], 'Parse.lean': module.adapt(raw['Parse.lean'].decode(), label).encode()}
        name = parent_name + '-proof'
        manifest = dict(old, candidate=name, parent='candidates/' + parent_name,
                        parent_hashes=old['hashes'],
                        hashes={n: hashlib.sha256(b).hexdigest() for n, b in files.items()},
                        bytes={n: len(b) for n, b in files.items()},
                        proof_status='DRAFT_HELPER_TOTALITY; actual extraction and original complete gate required.',
                        proof_change='Insert bounded helper totality lemmas; original rc_seq theorem and verified emitter retained.')
        files['manifest.json'] = (json.dumps(manifest, indent=2) + '\n').encode()
        target = ROOT / 'candidates' / name
        if args.check:
            assert all((target / n).read_bytes() == b for n, b in files.items()), name
        else:
            target.mkdir(exist_ok=True)
            for n, b in files.items():
                assert not (target / n).exists() or (target / n).read_bytes() == b
                (target / n).write_bytes(b)
        print(json.dumps({'candidate': name, 'hashes': manifest['hashes']}))


if __name__ == '__main__':
    main()
