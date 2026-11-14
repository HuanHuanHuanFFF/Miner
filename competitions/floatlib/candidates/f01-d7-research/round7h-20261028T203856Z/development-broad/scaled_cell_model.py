"""Independent exact model for raw128/word38 scaled cells, no native execution."""
from fractions import Fraction
from pathlib import Path
import hashlib
import importlib.util
import json
import random

HERE = Path(__file__).resolve().parent
spec = importlib.util.spec_from_file_location('r24_scaled_cell_math', HERE / 'certificates.py')
c = importlib.util.module_from_spec(spec)
spec.loader.exec_module(c)
MASK = (1 << 64) - 1


def fast_allowed(num, source, word, target):
    if num >> 64:
        return True
    significand, shift = (word, target - source) if source <= target else (num, source - target)
    return shift < 64 and (significand == 0 or significand.bit_length() + shift <= 64)


def checked(num, den, mant, source, target, *, require_dcap=True):
    if not (0 < den and (not require_dcap or den < 1 << 38) and
            8388608 < mant < 16777216 and 1 <= target + 150 <= 254):
        return False
    twice = den * ((mant + mant) & MASK) & MASK
    lower, upper = (twice - den) & MASK, (twice + den) & MASK
    if not (fast_allowed(num, source + 1, lower, target) and
            fast_allowed(num, source + 1, upper, target)):
        return False
    return lower * c.pow2(target) < num * c.pow2(source + 1) < upper * c.pow2(target)


def ratio_log(num, den):
    exponent = num.bit_length() - den.bit_length()
    if Fraction(num, den) < c.pow2(exponent):
        exponent -= 1
    return exponent


def main():
    groups = []
    for seed in (24293429, 24293431):
        rng = random.Random(seed)
        cases = accepted = raw_accept = not_interior = wide_den = wrong_reject = 0
        for i in range(2500):
            if i < 1000:
                num = rng.randrange(1 << 94, 1 << 95)
                den = rng.randrange(1 << 29, 1 << 30)
            else:
                nb, db = rng.randrange(1, 129), rng.randrange(1, 39)
                num, den = rng.randrange(1 << (nb - 1), 1 << nb), rng.randrange(1 << (db - 1), 1 << db)
            alpha = ratio_log(num, den)
            source = rng.randrange(-149, 104) - alpha + 23
            truth = c.rn_rational(Fraction(num, den) * c.pow2(source))
            ef = (truth >> 23) & 255
            if not 1 <= ef <= 254:
                continue
            mant, target = (truth & 0x7fffff) + (1 << 23), ef - 150
            cases += 1
            if mant == 8388608:
                not_interior += 1
                assert not checked(num, den, mant, source, target)
                continue
            strict = den * (2 * mant - 1) * c.pow2(target) < 2 * num * c.pow2(source) < den * (2 * mant + 1) * c.pow2(target)
            got = checked(num, den, mant, source, target)
            assert got == strict
            if got:
                for sign in (False, True):
                    expected = (int(sign) << 31) | ((target + 150) << 23) | (mant - 8388608)
                    assert c.rn_rational(Fraction(num, den) * c.pow2(source) * (-1 if sign else 1)) == expected
                accepted += 1
            raw_accept += den * (2 * mant - 1) < 2 * num < den * (2 * mant + 1)
            normalize = source - target
            wide_den += normalize < 0 and (den << -normalize).bit_length() > 64
            wrong = mant + 1 if mant + 1 < 16777216 else mant - 1
            if not checked(num, den, wrong, source, target):
                wrong_reject += 1
        groups.append({'seed': seed, 'normal_cases': cases, 'scaled_accepted': accepted,
                       'power_boundaries_rejected': not_interior, 'raw_normalized_helper_accept': raw_accept,
                       'logical_normalized_denominator_exceeds64': wide_den, 'adjacent_wrong_mantissa_rejected': wrong_reject})
    num, den, source = 3 * (1 << 93), (1 << 30) + 1, -64
    mant, target = 12582912, -23
    assert checked(num, den, mant, source, target)
    witness = {'num': num, 'den': den, 'source': source, 'target': target, 'mant': mant,
               'num_bits': num.bit_length(), 'den_bits': den.bit_length(),
               'normalized_denominator_bits': (den << (target - source)).bit_length(),
               'midpoint_coefficient_bits': (den * (2 * mant + 1)).bit_length(),
               'word': f'{c.rn_rational(Fraction(num, den) * c.pow2(source)):08x}'}
    bad_den, bad_mant = (1 << 63) + 1, 8388609
    bad_num = (1 << 62) + bad_mant
    assert checked(bad_num, bad_den, bad_mant, 0, 0, require_dcap=False)
    assert not checked(bad_num, bad_den, bad_mant, 0, 0)
    assert c.rn_rational(Fraction(bad_num, bad_den)) != (150 << 23) | 1
    assert 2 * 8388609 - 1 < 2 * 8388609 < 2 * 8388609 + 1
    assert not checked(8388609, 1, 8388609, 0, 1)
    assert not fast_allowed(1, -10000, 100000000, 10000)
    report = {'scope': 'Exact rational/word model only. No Lean, native cost, workload probability or adoption.',
              'groups': groups, 'capacity_counterexample': witness,
              'mutants_caught': ['drop_denominator_cap_causes_wrapped_midpoint_false_accept',
                                 'ignore_source_vs_target_scale_doubles_output'],
              'large_wrong_exponent_rejects_before_public_small_word_Nat_fallback': True,
              'source_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
              'lean_sources': {name: hashlib.sha256((HERE / name).read_bytes()).hexdigest()
                               for name in ('ScaledCell.lean.inc', 'ScaledWord128.lean.inc')}}
    (HERE / 'scaled-cell-model-results.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
