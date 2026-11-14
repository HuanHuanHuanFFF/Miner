"""Fixed-word midpoint falsifier. No Lean/native execution or timing claim."""
from pathlib import Path
from fractions import Fraction
import hashlib
import importlib.util
import json
import random

HERE = Path(__file__).resolve().parent


def round_even(num, den):
    quotient, remainder = divmod(num, den)
    return quotient + (2 * remainder > den or
                       (2 * remainder == den and quotient % 2 == 1))


def check(num, den, mant, width=64, *, high=True, ordered=True, full_product=True):
    radix = 1 << width
    product = mant * den if full_product else (mant * den) % radix
    residue = abs(num - product)
    lo, hi = residue % radix, residue // radix
    return (den > 0 and mant > 0 and (not high or hi == 0) and
            (not ordered or lo < den) and lo < (den - lo) % radix)


def main():
    exhaustive = accepted = rejected = ties = 0
    for den in range(1, 16):
        for mant in range(1, 16):
            for num in range(256):
                got = check(num, den, mant, 4)
                expected = 2 * abs(num - mant * den) < den
                assert got == expected
                if got:
                    assert round_even(num, den) == mant
                    accepted += 1
                else:
                    rejected += 1
                ties += 2 * abs(num - mant * den) == den
                exhaustive += 1
    rng = random.Random(24293119)
    random_cases = random_accept = 0
    for _ in range(20000):
        den = rng.randrange(1, 1 << 64)
        mant = rng.randrange(1, 1 << 64)
        product = den * mant
        num = product + rng.randrange(-den, den + 1)
        if not 0 <= num < 1 << 128:
            continue
        got = check(num, den, mant)
        assert got == (2 * abs(num - product) < den)
        if got:
            assert round_even(num, den) == mant
            random_accept += 1
        random_cases += 1
    mutants = [
        ('drop_high_limb', (1 << 64) + 3, 3, 1, {'high': False}),
        ('drop_ordered_subtraction', (1 << 63) + 1, 1, 1, {'ordered': False}),
        ('truncate_product_to_low_limb', 0, 1 << 63, 2, {'full_product': False}),
    ]
    witnesses = []
    for name, num, den, mant, mutation in mutants:
        assert check(num, den, mant, **mutation)
        assert not check(num, den, mant)
        actual = round_even(num, den)
        assert actual != mant
        witnesses.append({'mutation': name, 'num': num, 'den': den,
                          'mant': mant, 'actual_round_even': actual})
    assert not check(0, 0, 1)
    assert not check(0, 1, 0)
    spec = importlib.util.spec_from_file_location('r24_word_gap_math', HERE / 'certificates.py')
    math_model = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(math_model)
    normal_cases = 0
    for _ in range(2000):
        den = rng.randrange(1, 1 << 64)
        mant = rng.randrange(8388609, 16777216)
        exponent = rng.randrange(-149, 105)
        num = mant * den + rng.randrange(-(den // 2), den // 2 + 1)
        if not check(num, den, mant):
            continue
        for sign in (False, True):
            value = Fraction(num, den) * math_model.pow2(exponent) * (-1 if sign else 1)
            expected = (int(sign) << 31) | ((exponent + 150) << 23) | (mant - 8388608)
            assert math_model.rn_rational(value) == expected
            normal_cases += 1
    report = {
        'scope': 'Exact integer model only; Lean typing, replay, axiom audit, native cost NOT_RUN.',
        'exhaustive_width4_cases': exhaustive,
        'exhaustive_accept': accepted, 'exhaustive_reject': rejected,
        'midpoint_ties_rejected': ties,
        'width64_cases': random_cases, 'width64_accept': random_accept,
        'normal_word_signed_cases_with_width64_denominator': normal_cases,
        'mutant_witnesses': witnesses,
        'source_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        'lean_fragment_sha256': hashlib.sha256((HERE / 'WordGap128.lean.inc').read_bytes()).hexdigest(),
    }
    (HERE / 'word-gap128-model.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
