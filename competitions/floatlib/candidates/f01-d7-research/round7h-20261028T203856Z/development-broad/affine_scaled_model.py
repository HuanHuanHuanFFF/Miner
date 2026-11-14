"""Exact word construction + scaled certificate/fallback model; no native time."""
from fractions import Fraction
from pathlib import Path
import hashlib
import importlib.util
import json
import random

HERE = Path(__file__).resolve().parent
spec = importlib.util.spec_from_file_location('r24_affine_scaled_math', HERE / 'scaled_cell_model.py')
sc = importlib.util.module_from_spec(spec)
spec.loader.exec_module(sc)
B64, B128 = 1 << 64, 1 << 128
MASK = B64 - 1


def multiply(a, factor, *, high_guard=True, factor_guard=True):
    if (high_guard and a >> 64 >= 1 << 40) or (factor_guard and factor >= 1 << 24):
        return 0, False
    lower = (a & MASK) * factor
    upper = ((a >> 64) * factor) & MASK
    middle = (lower >> 64) + upper
    return ((middle & MASK) << 64) | (lower & MASK), middle < B64


def combine(sa, sb, a, b, *, carry_guard=True):
    if sa == sb:
        return sa, (a + b) % B128, not carry_guard or a + b < B128
    return (sb, b - a, True) if a < b else (sa, a - b, True)


def coefficient(sa, sb, a, factor, b):
    return (-a if sa else a) * factor + (-b if sb else b)


def attempt(sa, sb, a, factor, b, den, mant, source, target, **mutation):
    product, pv = multiply(a, factor, **{k: v for k, v in mutation.items() if k != 'carry_guard'})
    sign, magnitude, sv = combine(sa, sb, product, b, **{k: v for k, v in mutation.items() if k == 'carry_guard'})
    if pv and sv and sc.checked(magnitude, den, mant, source, target):
        return (int(sign) << 31) | ((target + 150) << 23) | (mant - (1 << 23))
    return 0


def run_case(sa, sb, a, factor, b, den, target_hint):
    exact = coefficient(sa, sb, a, factor, b)
    if exact == 0:
        source, truth = 0, 0
    else:
        source = target_hint - sc.ratio_log(abs(exact), den) + 23
        truth = sc.c.rn_rational(Fraction(exact, den) * sc.c.pow2(source))
    exponent_field = (truth >> 23) & 255
    mant, target = (truth & 0x7fffff) + (1 << 23), exponent_field - 150
    candidate = attempt(sa, sb, a, factor, b, den, mant, source, target)
    result = candidate if candidate != 0 else truth
    assert result == truth
    p, pv = multiply(a, factor)
    sign, magnitude, sv = combine(sa, sb, p, b)
    if pv:
        assert p == a * factor
    if pv and sv:
        assert (-magnitude if sign else magnitude) == exact
    wrong = mant + 1 if mant + 1 < 16777216 else mant - 1
    bad = attempt(sa, sb, a, factor, b, den, wrong, source, target)
    assert bad == 0 or bad == truth
    return candidate != 0, pv and sv


def main():
    groups = []
    for seed in (24293607, 24293609):
        rng = random.Random(seed)
        for kind in ('bounded70_gain24_bias86', 'full128_gain64_mixed_guards'):
            hits = valid = 0
            for _ in range(2500):
                if kind.startswith('bounded'):
                    a, factor, b = rng.randrange(1 << 69, 1 << 70), rng.randrange(1 << 23, 1 << 24), rng.randrange(1 << 85, 1 << 86)
                else:
                    aa, ff, bb = rng.randrange(1, 129), rng.randrange(1, 65), rng.randrange(1, 129)
                    a, factor, b = rng.randrange(1 << (aa - 1), 1 << aa), rng.randrange(1 << (ff - 1), 1 << ff), rng.randrange(1 << (bb - 1), 1 << bb)
                hit, ok = run_case(bool(rng.getrandbits(1)), bool(rng.getrandbits(1)), a, factor, b,
                                   rng.randrange(1 << 29, 1 << 30), rng.randrange(-149, 104))
                hits += hit
                valid += ok
            groups.append({'seed': seed, 'constructed_kind': kind, 'cases': 2500,
                           'word_construction_valid': valid, 'perfect_proposal_accept': hits})
    zeros = [(False, True, 1234567, 987, 1234567 * 987), (True, False, 1234567, 987, 1234567 * 987),
             (True, True, 0, 0, 0)]
    for sa, sb, a, factor, b in zeros:
        assert run_case(sa, sb, a, factor, b, 1, -23) == (False, True)
    # Missing either product width guard wraps 2^128 to0; a small bias then
    # passes the cell even though the actual reference overflows binary32.
    mant = 8388609
    mutants = []
    for label, a, factor, mutation in [
        ('drop_high_guard', 1 << 127, 2, {'high_guard': False}),
        ('drop_factor_guard', 1 << 103, 1 << 25, {'factor_guard': False}),
    ]:
        wrong = attempt(False, False, a, factor, mant, 1, mant, 0, 0, **mutation)
        truth = sc.c.rn_rational(Fraction(a * factor + mant))
        assert wrong != 0 and wrong != truth
        assert attempt(False, False, a, factor, mant, 1, mant, 0, 0) == 0
        mutants.append({'mutation': label, 'left': a, 'factor': factor, 'bias': mant,
                        'wrong_word': f'{wrong:08x}', 'truth_word': f'{truth:08x}'})
    a, factor, b = (1 << 103), (1 << 23), B128 - (1 << 126) + mant
    wrong = attempt(False, False, a, factor, b, 1, mant, 0, 0, carry_guard=False)
    truth = sc.c.rn_rational(Fraction(a * factor + b))
    assert wrong != 0 and wrong != truth
    assert attempt(False, False, a, factor, b, 1, mant, 0, 0) == 0
    mutants.append({'mutation': 'drop_signed_add_carry_guard', 'left': a, 'factor': factor,
                    'bias': b, 'wrong_word': f'{wrong:08x}', 'truth_word': f'{truth:08x}'})
    report = {'scope': 'Exact complete generic operation model with perfect reference proposals only; no native guessing/cost/workload probability.',
              'groups': groups, 'zero_cancellation_cases': len(zeros), 'guard_mutants': mutants,
              'source_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
              'lean_source_sha256': hashlib.sha256((HERE / 'AffineScaledWord128.lean.inc').read_bytes()).hexdigest(),
              'scaled_helper_source_sha256': hashlib.sha256((HERE / 'scaled_cell_model.py').read_bytes()).hexdigest()}
    (HERE / 'affine-scaled-model-results.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
