"""Exact Fraction oracle and independent word-limb execution model, no native run."""
from fractions import Fraction
from pathlib import Path
import hashlib
import json
import random

HERE = Path(__file__).resolve().parent
MASK = (1 << 64) - 1
SEEDS = (24294011, 24294013)


def p2(e):
    return Fraction(1 << e) if e >= 0 else Fraction(1, 1 << -e)


def parts(w):
    e, f = (w >> 23) & 255, w & 0x7fffff
    return f if e == 0 else f | 0x800000, max(e - 1, 0), bool(w >> 31)


def value(w):
    m, k, s = parts(w)
    return (-m if s else m) * p2(k - 149)


def rne(q, negative_zero=False):
    if q == 0:
        return int(negative_zero) << 31
    negative = q < 0
    q = abs(q)
    exponent = q.numerator.bit_length() - q.denominator.bit_length()
    if q < p2(exponent):
        exponent -= 1
    target = max(exponent - 23, -149)
    scaled = q / p2(target)
    mantissa, remainder = divmod(scaled.numerator, scaled.denominator)
    mantissa += 2 * remainder > scaled.denominator or (2 * remainder == scaled.denominator and bool(mantissa & 1))
    if mantissa >= 1 << 24:
        mantissa >>= 1
        target += 1
    encoded = target + 150 if mantissa >= 1 << 23 else 0
    if encoded >= 255:
        return (int(negative) << 31) | 0x7f800000
    return (int(negative) << 31) | (encoded << 23) | (mantissa - (1 << 23) if encoded else mantissa)


def prepare_operand(raw):
    good = [parts(w)[1] for w in raw if (w >> 23) & 255 != 255 and parts(w)[0] != 0]
    normal = all((w >> 23) & 255 != 255 and ((w >> 23) & 255 != 0 or w & 0x7fffff == 0) for w in raw)
    data = [((w & 0x80000000) | 0x7f000000) if parts(w)[0] == 0 else (w - 0x800000) & 0xffffffff for w in raw]
    return {'raw': raw, 'data': data, 'normal': normal,
            'finite': all((w >> 23) & 255 != 255 for w in raw),
            'has': bool(good), 'lo': min(good, default=0), 'hi': max(good, default=0)}


def cache(a, b):
    left, right = prepare_operand(a), prepare_operand(b)
    active = left['has'] and right['has']
    lo = left['lo'] + right['lo'] if active else 0
    hi = left['hi'] + right['hi'] if active else 0
    matched = len(a) == len(b)
    normal = left['normal'] and right['normal']
    finite = left['finite'] and right['finite']
    count = len(a)
    ceil = (count - 1).bit_length() if count > 1 else 0
    eligible = matched and normal and count <= 1 << 20 and 48 + hi - lo + ceil <= 128
    return dict(left=left, right=right, lo=lo, hi=hi, matched=matched, normal=normal, finite=finite, eligible=eligible)


def round_word(negative, lo, hi, base):
    if lo == 0 and hi == 0:
        return int(negative) << 31
    leading = lo.bit_length() - 1 if hi == 0 else 64 + hi.bit_length() - 1
    total = base + leading
    if total > 127:
        return (int(negative) << 31) | 0x7f800000
    target = max(total - 23, -149)
    delta = target - base
    if delta <= 0:
        m = (lo << -delta) & MASK
    elif delta > 128:
        m = 0
    else:
        if delta < 64:
            q = (lo >> delta) | ((hi << (64 - delta)) & MASK)
        elif delta == 64:
            q = hi
        elif delta < 128:
            q = hi >> (delta - 64)
        else:
            q = 0
        if delta <= 64:
            guard = bool((lo >> (delta - 1)) & 1)
            sticky = bool(lo & ((1 << (delta - 1)) - 1))
        else:
            guard = bool((hi >> (delta - 65)) & 1)
            sticky = lo != 0 or bool(hi & ((1 << (delta - 65)) - 1))
        m = q + (guard and (sticky or bool(q & 1)))
    carry = m == 1 << 24
    normalized = m >> 1 if carry else m
    encoded = target + 150 + carry
    if normalized < 1 << 23:
        return (int(negative) << 31) | normalized
    if encoded >= 255:
        return (int(negative) << 31) | 0x7f800000
    return (int(negative) << 31) | (encoded << 23) | (normalized - (1 << 23))


def native_model(c):
    assert c['eligible']
    p_lo = p_hi = n_lo = n_hi = 0
    neg_zero = bool(c['left']['raw'])
    pos_exact = neg_exact = 0
    for wa, wb in zip(c['left']['data'], c['right']['data']):
        ia, ib = (wa >> 23) & 255, (wb >> 23) & 255
        ma = 0 if ia == 254 else (wa & 0x7fffff) | 0x800000
        mb = 0 if ib == 254 else (wb & 0x7fffff) | 0x800000
        product, negative = ma * mb, bool((wa ^ wb) >> 31)
        if product == 0:
            neg_zero &= negative
            continue
        neg_zero = False
        shift = ia + ib - c['lo']
        lo = product << shift & MASK if shift < 64 else 0
        hi = 0 if shift == 0 else product >> (64 - shift) if shift < 64 else product << (shift - 64) & MASK
        if negative:
            new_lo = (n_lo + lo) & MASK
            n_hi = (n_hi + hi + (new_lo < n_lo)) & MASK
            n_lo = new_lo
            neg_exact += product << shift
        else:
            new_lo = (p_lo + lo) & MASK
            p_hi = (p_hi + hi + (new_lo < p_lo)) & MASK
            p_lo = new_lo
            pos_exact += product << shift
        assert (p_hi << 64) | p_lo == pos_exact < 1 << 128
        assert (n_hi << 64) | n_lo == neg_exact < 1 << 128
    if p_hi == n_hi and p_lo == n_lo:
        return int(neg_zero) << 31
    negative = (p_hi, p_lo) < (n_hi, n_lo)
    big_lo, big_hi, small_lo, small_hi = (n_lo, n_hi, p_lo, p_hi) if negative else (p_lo, p_hi, n_lo, n_hi)
    return round_word(negative, (big_lo - small_lo) & MASK,
                      (big_hi - small_hi - (big_lo < small_lo)) & MASK, c['lo'] - 298)


def oracle(a, b):
    c = cache(a, b)
    if not c['matched'] or not c['finite']:
        return 0x7fc00000, c
    q = sum((value(x) * value(y) for x, y in zip(a, b)), Fraction())
    nz = bool(a) and all((parts(x)[0] == 0 or parts(y)[0] == 0) and bool((x ^ y) >> 31) for x, y in zip(a, b))
    expected = rne(q, nz)
    if c['eligible']:
        assert native_model(c) == expected
    return expected, c


def normal_word(rng, low, high):
    return (rng.getrandbits(1) << 31) | (rng.randrange(low, high + 1) << 23) | rng.getrandbits(23)


def main():
    fixtures = []
    def add(name, a, b, seed=None):
        expected, c = oracle(a, b)
        fixtures.append({'id': name, 'seed': seed, 'a': a, 'b': b, 'expected': expected,
                         'expected_fast': c['eligible'], 'expected_finite': c['finite'], 'expected_matched': c['matched'],
                         'min_scale': c['lo'], 'max_scale': c['hi'], 'native_baseline_model_checked': c['eligible']})
    for seed in SEEDS:
        rng = random.Random(seed)
        for kind, low, high in [('normal', 121, 126), ('wide_fit', 90, 120), ('wide_reject', 2, 254)]:
            for n in (1, 7, 32, 127, 256, 513):
                add(f'{seed}-{kind}-{n}', [normal_word(rng, low, high) for _ in range(n)],
                    [normal_word(rng, low, high) for _ in range(n)], seed)
    one, minus_one = 0x3f800000, 0xbf800000
    def power(e):
        assert -126 <= e <= 127
        return (e + 127) << 23
    directed = [
        ('empty', [], []), ('negative_zero', [0x80000000], [one]),
        ('negative_zeros', [0x80000000] * 5, [one] * 5),
        ('mixed_zero', [0x80000000, 0], [one, one]),
        ('zero_sign_product', [0x80000000, 0], [minus_one, one]),
        ('cancel', [one, minus_one], [one, one]),
        ('f64_lost_middle', [one, power(-26), minus_one], [one, power(-27), one]),
        ('wide_cancel', [power(100), one, power(100) | 0x80000000], [one] * 3),
        ('tie_even', [one, power(-24)], [one, one]),
        ('tie_odd', [one + 1, power(-24)], [one, one]),
        ('binade_tie', [0x3fffffff, power(-24)], [one, one]),
        ('min_sub_tie', [power(-126)], [power(-24)]),
        ('min_sub_above', [power(-126)], [power(-24) + 1]),
        ('negative_underflow', [power(-126) | 0x80000000], [power(-25)]),
        ('overflow_tie', [0x7f7fffff, power(103)], [one, one]),
        ('overflow_below', [0x7f7fffff, power(102)], [one, one]),
        ('max_product', [0x7f7fffff], [0x7f7fffff]),
        ('round_shift64', [(90 << 23) | 0x7fffff, (110 << 23) | 0x7fffff], [(90 << 23) | 0x7fffff, (110 << 23) | 0x7fffff]),
        ('round_shift128', [(11 << 23) | 0x7fffff] + [(50 << 23) | 0x7fffff] * 3,
                           [(12 << 23) | 0x7fffff] + [(51 << 23) | 0x7fffff] * 3),
        ('guard128', [(90 << 23) | 0x7fffff] + [(126 << 23) | 0x7fffff] * 255,
                      [(90 << 23) | 0x7fffff] + [(126 << 23) | 0x7fffff] * 255),
        ('guard129_reject', [(90 << 23) | 0x7fffff] + [(126 << 23) | 0x7fffff] * 256,
                             [(90 << 23) | 0x7fffff] + [(126 << 23) | 0x7fffff] * 256),
        ('separable_reject_pair_tight', [power(-77), power(23)] * 16, [power(23), power(-77)] * 16),
        ('subnormal_replay', [1, 0x80000001], [one, one]),
        ('infinity_unsupported', [0x7f800000], [one]),
        ('nan_unsupported', [0x7fa12345], [one]),
        ('mismatch_unsupported', [one], []),
    ]
    for row in directed:
        add(*row)
    rounds = []
    for seed in SEEDS:
        rng = random.Random(seed ^ 0xa5a5a5a5)
        for i in range(512):
            magnitude = rng.getrandbits(rng.randrange(1, 129))
            negative = bool(rng.getrandbits(1))
            base = rng.randrange(-500, 151)
            expected = rne((-1 if negative else 1) * magnitude * p2(base), negative and magnitude == 0)
            actual = round_word(negative, magnitude & MASK, magnitude >> 64, base)
            assert actual == expected
            rounds.append({'id': f'{seed}-round-{i}', 'negative': negative, 'lo': magnitude & MASK,
                           'hi': magnitude >> 64, 'base': base, 'expected': expected})
    for shift in (1, 23, 24, 63, 64, 65, 127, 128, 129):
        for delta in (-1, 0, 1):
            magnitude = (1 << (shift - 1)) + delta
            if 0 <= magnitude < 1 << 128:
                base = -149 - shift
                expected = rne(magnitude * p2(base))
                assert round_word(False, magnitude & MASK, magnitude >> 64, base) == expected
                rounds.append({'id': f'shift{shift}-delta{delta}', 'negative': False, 'lo': magnitude & MASK,
                               'hi': magnitude >> 64, 'base': base, 'expected': expected})
    report = {'scope': 'Research normal-or-zero native128 baseline plus exact finite replay. Nonfinite/mismatch canonicalNaN unsupported policy; no official payload claim.',
              'seeds': SEEDS, 'source_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
              'lean_source_sha256': hashlib.sha256((HERE / 'ExactDotCost.lean.inc').read_bytes()).hexdigest(),
              'dot_cases': fixtures, 'round_cases': rounds,
              'summary': {'dot_cases': len(fixtures), 'native_fast_cases': sum(f['expected_fast'] for f in fixtures),
                          'finite_replay_cases': sum(f['expected_finite'] and f['expected_matched'] and not f['expected_fast'] for f in fixtures),
                          'unsupported_cases': sum(not f['expected_finite'] or not f['expected_matched'] for f in fixtures),
                          'round_cases': len(rounds)}, 'native_lean_validation': 'NOT_RUN'}
    (HERE / 'exact-dot-cost-fixtures.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(report['summary'], indent=2))


if __name__ == '__main__':
    main()
