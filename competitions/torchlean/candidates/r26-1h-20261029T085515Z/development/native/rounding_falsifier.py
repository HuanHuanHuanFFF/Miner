"""Directed exact arithmetic falsifier for reused round128; no native claim."""
from pathlib import Path
import hashlib
import importlib.util
import json
import sys
import time
sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
OLD = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z/development-broad'
spec = importlib.util.spec_from_file_location('r26_round_falsifier_oracle', OLD / 'exact_dot_baseline_model.py')
m = importlib.util.module_from_spec(spec)
spec.loader.exec_module(m)

def main():
    started = time.monotonic()
    failures = []
    count = 0
    shifts = set()
    bases = set()
    quotients = (0, 1, 2, 0x7fffff, 0x800000, 0x800001, 0xfffffe, 0xffffff, 0x1000000)
    for target in (-149, -148, -127, -126, -1, 0, 102, 103, 104, 105):
        for shift in range(131):
            for q in quotients:
                for offset in (-1, 0, 1):
                    center = q if shift == 0 else (q << shift) + (1 << (shift - 1))
                    magnitude = center + offset
                    if not 0 <= magnitude < 1 << 128:
                        continue
                    for negative in (False, True):
                        base = target - shift
                        exact = (-magnitude if negative else magnitude) * m.p2(base)
                        expected = m.rne(exact, negative and magnitude == 0)
                        actual = m.round_word(negative, magnitude & m.MASK, magnitude >> 64, base)
                        if expected != actual:
                            failures.append({'target': target, 'shift': shift, 'q': q,
                                             'offset': offset, 'negative': negative,
                                             'base': base, 'magnitude': magnitude,
                                             'expected': expected, 'actual': actual})
                        count += 1
                        shifts.add(shift)
                        bases.add(base)
                    if time.monotonic() - started > 20:
                        raise RuntimeError('Falsifier exceeded fixed 20 second lightweight budget')
    source = (OLD / 'ExactDotCost.lean.inc').read_bytes()
    report = {'scope': 'Directed Python Fraction/RNE versus word-rounding model only; not native or all-input proof',
              'cases': count, 'shifts': sorted(shifts), 'bases': [min(bases), max(bases)],
              'quotients': list(quotients), 'failures': failures,
              'source_helper_sha256': hashlib.sha256(source).hexdigest(),
              'elapsed_seconds': time.monotonic() - started}
    (HERE / 'rounding-falsifier.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({k: v for k, v in report.items() if k != 'shifts'}, indent=2))
    assert not failures

if __name__ == '__main__':
    main()
