"""Generally routed speed derivatives of public submission 432."""
from pathlib import Path
import argparse
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'references/round3-public-432'
HASHES = {'parse.rs': '160d1b3f9edb307a0f97bde13cd972b5f6f0a426dd669515f639e4bfa24ef054',
          'Parse.lean': 'e2c200cf084eca95eb70d26c0efb04e70d88f015315610d2a54d20b6adb7cf04'}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--check', action='store_true')
    args = ap.parse_args()
    base = {n: (BASE / n).read_bytes() for n in HASHES}
    assert all(hashlib.sha256(base[n]).hexdigest() == h for n, h in HASHES.items())
    variants = {
        'r3-432-tshift3': ({'T_SKIP': (4, 3)}, 'Larger miss >> skip steps in the existing read-ahead text and structured-text paths; fewer probes, routing unchanged.'),
        'r3-432-dmin257': ({'ST_DMIN': (129, 257)}, 'Exclude two more short-distance code groups in the existing parity-selected binary path; all routing unchanged.'),
        'r3-432-fast3': ({'T_SKIP': (4, 3), 'P_DEPTH': (4, 1)}, 'Fewer text probes plus the existing one-probe read-ahead prose path, selected by general content class.'),
        'r3-432-fast2': ({'T_SKIP': (4, 2), 'P_DEPTH': (4, 1)}, 'More aggressive miss acceleration than fast3, with the same one-probe read-ahead prose path.'),
    }
    for name, (changes, explanation) in variants.items():
        text = base['parse.rs'].decode()
        for key, (old, new) in changes.items():
            text, count = re.subn(rf'(pub const {key}: usize = ){old};', rf'\g<1>{new};', text)
            assert count == 1
        files = {'parse.rs': text.encode(), 'Parse.lean': base['Parse.lean']}
        manifest = {'candidate': name, 'base_submission_id': '432', 'base_path': BASE.relative_to(ROOT).as_posix(),
                    'base_hashes': HASHES, 'change': {key: {'old': old, 'new': new} for key, (old, new) in changes.items()}, 'mechanism': explanation,
                    'hashes': {n: hashlib.sha256(v).hexdigest() for n, v in files.items()},
                    'attribution': 'Original public miner source, not an independent algorithm; see reference PROVENANCE.md',
                    'scope': 'Unverified derivative; new official gate and paired performance required'}
        files['manifest.json'] = (json.dumps(manifest, indent=2) + '\n').encode()
        dest = ROOT / 'candidates' / name
        if args.check:
            assert all((dest / n).read_bytes() == b for n, b in files.items())
        else:
            dest.mkdir(exist_ok=True)
            for n, b in files.items():
                (dest / n).write_bytes(b)
        print(name, manifest['hashes']['parse.rs'])


if __name__ == '__main__':
    main()
