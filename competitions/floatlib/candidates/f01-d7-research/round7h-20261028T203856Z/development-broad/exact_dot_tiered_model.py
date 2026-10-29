"""One-chain signed62 model against the frozen Fraction oracle and all fixtures."""
from pathlib import Path
import hashlib
import importlib.util
import json

HERE = Path(__file__).resolve().parent
spec = importlib.util.spec_from_file_location('r24_exact_baseline', HERE / 'exact_dot_baseline_model.py')
m = importlib.util.module_from_spec(spec)
spec.loader.exec_module(m)


def eligible64(c):
    n = len(c['left']['raw'])
    ceil = (n - 1).bit_length() if n > 1 else 0
    return c['matched'] and c['normal'] and n <= 1 << 20 and 48 + c['hi'] - c['lo'] + ceil <= 62


def model64(c):
    assert eligible64(c)
    acc = exact = 0
    neg_zero = bool(c['left']['raw'])
    for a, b in zip(c['left']['data'], c['right']['data']):
        ia, ib = (a >> 23) & 255, (b >> 23) & 255
        ma, mb = (0 if ia == 254 else (a & 0x7fffff) | 0x800000), (0 if ib == 254 else (b & 0x7fffff) | 0x800000)
        product = ma * mb
        negative = bool((a ^ b) >> 31)
        bit = int(negative)
        sign_mask = -bit & m.MASK
        shift = ia + ib - c['lo']
        term = (((product << (shift % 64)) & m.MASK) ^ sign_mask) + bit
        acc = (acc + term) & m.MASK
        neg_zero = neg_zero and product == 0 and negative
        exact += (-product if negative else product) << shift
        interpreted = acc - (1 << 64) if acc >> 63 else acc
        assert interpreted == exact and abs(exact) < 1 << 62
    if acc == 0:
        return int(neg_zero) << 31
    negative = bool(acc >> 63)
    magnitude = (-acc & m.MASK) if negative else acc
    return m.round_word(negative, magnitude, 0, c['lo'] - 298)


def main():
    own = json.loads((HERE / 'exact-dot-cost-fixtures.json').read_text(encoding='utf-8'))
    peer_path = HERE.parent / 'development-scalar/portable-f64-dot-fixtures.json'
    peer = json.loads(peer_path.read_text(encoding='utf-8'))
    groups = [('own', [(f['id'], f['a'], f['b'], f['expected']) for f in own['dot_cases']]),
              ('scalar', [(f['name'], f['x'], f['y'], f['expected']) for f in peer['cases']])]
    results = []
    for group, rows in groups:
        for name, aa, bb, expected in rows:
            a = [int(x, 0) if isinstance(x, str) else x for x in aa]
            b = [int(x, 0) if isinstance(x, str) else x for x in bb]
            expected = int(expected, 0) if isinstance(expected, str) else expected
            truth, c = m.oracle(a, b)
            assert truth == expected
            fast64 = eligible64(c)
            actual = model64(c) if fast64 else m.native_model(c) if c['eligible'] else truth
            assert actual == expected
            results.append({'group': group, 'name': name, 'expected': expected,
                            'tier': 'word64' if fast64 else 'word128' if c['eligible'] else 'finite_replay' if c['finite'] and c['matched'] else 'unsupported'})
    report = {'scope': 'Exact word/Fraction model; no native Lean run or speed claim.',
              'source_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
              'tiered_lean_sha256': hashlib.sha256((HERE / 'ExactDotTiered.lean.inc').read_bytes()).hexdigest(),
              'frozen_baseline_lean_sha256': hashlib.sha256((HERE / 'ExactDotCost.lean.inc').read_bytes()).hexdigest(),
              'own_fixture_sha256': hashlib.sha256((HERE / 'exact-dot-cost-fixtures.json').read_bytes()).hexdigest(),
              'peer_fixture_sha256': hashlib.sha256(peer_path.read_bytes()).hexdigest(),
              'cases': results,
              'summary': {group: {tier: sum(r['group'] == group and r['tier'] == tier for r in results)
                                  for tier in ('word64', 'word128', 'finite_replay', 'unsupported')}
                          for group, _ in groups}}
    (HERE / 'exact-dot-tiered-model-results.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(report['summary'], indent=2))


if __name__ == '__main__':
    main()
