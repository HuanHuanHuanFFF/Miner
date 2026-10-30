#!/usr/bin/env python3
"""R28 original, stdlib-only finite arithmetic experiments; NOT a benchmark.

Independent oracles use Fraction and unbounded integers. The proposed checker
uses a separate two-limb UInt64 model, with explicit masked arithmetic.
No downloaded Kernel, frozen model inputs, Lean execution, or timing is used.
"""
from __future__ import annotations

import argparse
from collections import Counter
from dataclasses import dataclass
from fractions import Fraction as F
import hashlib
import json
import math
from pathlib import Path
import random
import struct

MASK = (1 << 64) - 1
SIGN = 1 << 31
MAX_FINITE = 0x7F7FFFFF
Pair = tuple[int, int]  # high, low


def pow2(e: int) -> F:
    return F(1 << e) if e >= 0 else F(1, 1 << -e)


def fields(w: int) -> tuple[bool, int, int, int]:
    e, f = (w >> 23) & 255, w & 0x7FFFFF
    return bool(w & SIGN), (f if e == 0 else (1 << 23) + f), max(e - 1, 0), e


def finite_value(w: int) -> F:
    sign, m, idx, e = fields(w)
    if e == 255:
        raise ValueError("nonfinite is not an IEEE rational")
    return (-1 if sign else 1) * m * pow2(idx - 149)


def rne_quotient(n: int, d: int) -> int:
    q, r = divmod(n, d)
    return q + int(2 * r > d or (2 * r == d and q & 1))


def log2_ratio(n: int, d: int) -> int:
    e = n.bit_length() - d.bit_length()
    if (n < (d << e)) if e >= 0 else ((n << -e) < d):
        e -= 1
    return e


def round32(v: F) -> int:
    """Independent RNE rational oracle, including subnormal/overflow/signed 0.
    Mathematical exact zero is canonical +0, as in stable roundRational.
    """
    if v == 0:
        return 0
    sign = SIGN if v < 0 else 0
    n, d = abs(v.numerator), v.denominator
    e = log2_ratio(n, d)
    if e < -126:
        m = rne_quotient(n << 149, d)
        return sign | m  # carry into minimum normal is correct here
    if e > 127:
        return sign | 0x7F800000
    shift = 23 - e
    m = rne_quotient(n << shift, d) if shift >= 0 else rne_quotient(n, d << -shift)
    if m == 1 << 24:
        m >>= 1
        e += 1
    if e > 127:
        return sign | 0x7F800000
    return sign | ((e + 127) << 23) | (m - (1 << 23))


def sqrt32(v: F) -> int:
    """Independent exact sqrt oracle: binary-search finite words, compare
    rational squares of the actual neighbours' midpoint. Never host sqrt.
    """
    if v <= 0:
        return 0
    lo, hi = 0, MAX_FINITE
    while lo < hi:
        mid = (lo + hi + 1) // 2
        if finite_value(mid) ** 2 <= v:
            lo = mid
        else:
            hi = mid - 1
    left = finite_value(lo)
    right = finite_value(lo + 1) if lo < MAX_FINITE else pow2(128)
    midpoint_squared = ((left + right) / 2) ** 2
    return lo + int(v > midpoint_squared or (v == midpoint_squared and lo & 1))


def host_word(v: float) -> int:
    try:
        return struct.unpack(">I", struct.pack(">f", v))[0]
    except OverflowError:
        return (SIGN if v < 0 else 0) | 0x7F800000


def join(p: Pair) -> int:
    return (p[0] << 64) + p[1]


def split(n: int) -> Pair:
    assert 0 <= n < 1 << 128
    return n >> 64, n & MASK


def mul64x24(a: int, b: int) -> Pair:
    """Two 32x24 products; deliberately not unbounded a*b in implementation."""
    assert 0 <= a <= MASK and 0 <= b < 1 << 24
    low_part = (a & 0xFFFFFFFF) * b
    high_part = (a >> 32) * b
    lo = (low_part + ((high_part << 32) & MASK)) & MASK
    hi = (high_part >> 32) + int(lo < low_part)
    return hi, lo


def uadd(a: Pair, b: Pair) -> Pair:
    lo = (a[1] + b[1]) & MASK
    hi = (a[0] + b[0] + int(lo < a[1])) & MASK
    return hi, lo


def usub(a: Pair, b: Pair) -> Pair:
    assert a >= b
    return ((a[0] - b[0] - int(a[1] < b[1])) & MASK, (a[1] - b[1]) & MASK)


def fits_shift(a: Pair, s: int) -> bool:
    if s < 0 or s >= 128:
        return False
    if s == 0:
        return True
    if s < 64:
        return a[0] >> (64 - s) == 0
    if s == 64:
        return a[0] == 0
    return a[0] == 0 and a[1] >> (128 - s) == 0


def ushift(a: Pair, s: int) -> Pair:
    assert fits_shift(a, s)
    if s == 0:
        return a
    if s < 64:
        return (((a[0] << s) | (a[1] >> (64 - s))) & MASK, (a[1] << s) & MASK)
    return (a[1] << (s - 64)) & MASK, 0


def sadd(sa: bool, a: Pair, sb: bool, b: Pair) -> tuple[bool, Pair]:
    if sa == sb:
        assert join(a) + join(b) < 1 << 128
        return sa, uadd(a, b)
    return (sa, usub(a, b)) if a >= b else (sb, usub(b, a))


def cell_coeff(q: int) -> tuple[int, int, int]:
    mag = q & 0x7FFFFFFF
    e, f = mag >> 23, mag & 0x7FFFFF
    assert 1 <= e <= 254
    m = (1 << 23) + f
    return 4 * m - (1 if f == 0 and e > 1 else 2), 4 * m + 2, e - 152


def strict_cell_reference(p: int, d: int, exponent: int, q: int) -> bool:
    """Reference checker uses actual predecessor/successor values, not Klo/Khi."""
    mag = q & 0x7FFFFFFF
    if not ((1 << 23) <= mag <= MAX_FINITE) or p == 0 or d <= 0:
        return False
    if bool(q & SIGN) != (p < 0):
        return False
    v = F(abs(p), d) * pow2(exponent)
    center = finite_value(mag)
    predecessor = finite_value(mag - 1)
    successor = finite_value(mag + 1) if mag < MAX_FINITE else pow2(128)
    return (predecessor + center) / 2 < v < (center + successor) / 2


def limb_cell(negative: bool, p: Pair, d: int, exponent: int, q: int) -> bool:
    """Division-free certificate, strict boundaries: every midpoint misses."""
    e = (q >> 23) & 255
    if e == 0 or e == 255 or p == (0, 0) or not (0 < d < 1 << 36):
        return False
    if bool(q & SIGN) != negative:
        return False
    low, high, h = cell_coeff(q)
    a, b = (0, d * low), (0, d * high)
    assert b[1] < 1 << 62
    shift = exponent - h
    if shift >= 0:
        if not fits_shift(p, shift):
            return False
        v = ushift(p, shift)
        return a < v < b
    shift = -shift
    if not fits_shift(b, shift):
        return False
    return ushift(a, shift) < p < ushift(b, shift)


@dataclass(frozen=True)
class Row:
    n: int
    b0: int
    total: int
    denominator_word: int
    mean: F
    variance: F


def prepare_row(words: list[int], epsilon: int) -> Row:
    assert words and all(fields(w)[3] != 255 for w in words)
    eps = finite_value(epsilon)
    assert eps > 0
    n = len(words)
    b0 = min((fields(w)[2] for w in words if fields(w)[1]), default=255)
    total = sum((-1 if fields(w)[0] else 1) * fields(w)[1] *
                (1 << (fields(w)[2] - b0)) for w in words if fields(w)[1])
    values = [finite_value(w) for w in words]
    mean = sum(values, F(0)) / n
    variance = sum(((v - mean) ** 2 for v in values), F(0)) / n
    assert F(total, n) * pow2(b0 - 149) == mean
    return Row(n, b0, total, sqrt32(variance + eps), mean, variance)


def construct(row: Row, w: int, g: int, b: int, *, zero_aware: bool = True):
    """Model of the guarded C and full biased numerator; no exact division."""
    n, b0, total, dw = row.n, row.b0, row.total, row.denominator_word
    sw, mw, iw, ew = fields(w)
    sg, mg, ig, eg = fields(g)
    sb, mb, ib, eb = fields(b)
    sd, md, idd, ed = fields(dw)
    if ew == 255 or eg == 255 or eb == 255:
        return None, "nonfinite_input"
    if sd or not 1 <= ed <= 254:
        return None, "denominator_not_positive_normal"
    if not 0 < n < 4096 or not 0 <= b0 <= 255 or abs(total) >= 1 << 60:
        return None, "row_guard"
    if mw and not (b0 <= iw and iw - b0 <= 24):
        return None, "input_shift_guard"
    xmag = 0 if mw == 0 else n * (mw << (iw - b0))
    # Sign/magnitude construction mirrors the bounded-word draft.
    sn, sm = total < 0, abs(total)
    if sw == sn:
        sc, cv = ((sw, xmag - sm) if xmag >= sm else (not sw, sm - xmag))
    else:
        sc, cv = sw, xmag + sm
    assert (-cv if sc else cv) == n * ((-1 if sw else 1) * (mw << (iw - b0)) if mw else 0) - total
    assert cv < 1 << 61
    d = n * md
    az, bz = cv == 0 or mg == 0, mb == 0
    if az and bz:
        return None, "exact_zero"
    alpha, beta = b0 + ig, ib + idd
    if zero_aware:
        c = beta if az else alpha if bz else min(alpha, beta)
        ks, bs = (0 if az else alpha - c), (0 if bz else beta - c)
    else:
        c = min(alpha, beta)
        ks, bs = alpha - c, beta - c
    abase, bbase = mul64x24(cv, mg), (0, d * mb)
    if not fits_shift(abase, ks) or not fits_shift(bbase, bs):
        return None, "alignment_guard"
    a = ushift(abase, ks)
    bpair = ushift(bbase, bs)
    # Each term < 2^127 is a cheap sufficient guard for their signed sum.
    if a[0] >> 63 or bpair[0] >> 63:
        return None, "addition_guard"
    negative, p = sadd(sc != sg, a, sb, bpair)
    if p == (0, 0):
        return None, "exact_zero"
    assert join(p) < 1 << 128
    if ks <= 8 and bs <= 37:
        assert join(p) < 1 << 98
    exponent = c - 149 - idd
    signed_p = -join(p) if negative else join(p)
    # Independent semantic oracle includes bias and exact rational mean.
    expected = (finite_value(w) - row.mean) * finite_value(g) / finite_value(dw) + finite_value(b)
    assert F(signed_p, d) * pow2(exponent) == expected
    return (negative, p, d, exponent), "constructed"


def numerator_proposal(negative: bool, p: Pair, d: int, exponent: int) -> int:
    # Mirrors the native draft. It is only a suggestion, never the oracle.
    approx = (float(p[0]) * (2.0 ** 64) + float(p[1])) / float(d)
    approx = math.ldexp(approx, exponent)
    return host_word(-approx if negative else approx)


def attempt(row: Row, w: int, g: int, b: int, *, zero_aware: bool = True):
    data, reason = construct(row, w, g, b, zero_aware=zero_aware)
    if data is None:
        return None, reason
    q = numerator_proposal(*data)
    if limb_cell(*data, q):
        return q, "accepted"
    return None, "cell_miss"


def test_word_arithmetic(rng: random.Random) -> dict:
    multiplication = shifts = additions = 0
    for _ in range(3000):
        a, b = rng.getrandbits(64), rng.getrandbits(24)
        assert join(mul64x24(a, b)) == a * b
        multiplication += 1
        x, y = rng.getrandbits(127), rng.getrandbits(127)
        assert join(uadd(split(x), split(y))) == x + y
        assert join(usub(split(max(x, y)), split(min(x, y)))) == abs(x - y)
        additions += 2
        for s in (0, 1, 31, 32, 63, 64, 65, 96, 127, 128, 129):
            expected = 0 <= s < 128 and (x << s) < 1 << 128
            assert fits_shift(split(x), s) == expected
            if expected:
                assert join(ushift(split(x), s)) == x << s
            shifts += 1
    for x in (0, 1, (1 << 64) - 1, 1 << 64, (1 << 128) - 1):
        for s in range(130):
            expected = s < 128 and (x << s) < 1 << 128
            assert fits_shift(split(x), s) == expected
            if expected:
                assert join(ushift(split(x), s)) == x << s
            shifts += 1
    return {"mul64x24_cases": multiplication, "add_sub_cases": additions, "shift_cases": shifts}


def test_full32_boundaries() -> dict:
    count = accepted = ties = 0
    for e in range(1, 255):
        for frac in (0, 1, 2, 0x3FFFFF, 0x7FFFFE, 0x7FFFFF):
            qmag = (e << 23) | frac
            low, high, h = cell_coeff(qmag)
            for sign in (0, SIGN):
                q = qmag | sign
                probes = [(4 * c + off, h - 2) for c in (low, high) for off in (-2, -1, 0, 1, 2)]
                probes.append((4 * ((1 << 23) + frac), h))
                for p, exponent in probes:
                    signed = -p if sign else p
                    hit = limb_cell(bool(sign), split(p), 1, exponent, q)
                    ref = strict_cell_reference(signed, 1, exponent, q)
                    assert hit == ref
                    truth = round32(F(signed) * pow2(exponent))
                    if hit:
                        assert truth == q
                        accepted += 1
                    if p in (4 * low, 4 * high) and exponent == h - 2:
                        assert not hit
                        ties += 1
                    count += 1
    return {"cases": count, "accepted": accepted, "exact_midpoints_rejected": ties}


def test_small_format() -> dict:
    """Exhaustive finite local-midpoint grid in four toy formats.
    Not exhaustive over all integers/rationals or binary32 words.
    """
    count = accepted = 0
    for precision in range(2, 6):
        first = 1 << (precision - 1)
        for e in range(1, 7):
            for frac in range(first):
                m = first + frac
                # Common scaling removes e; independently derive neighbours.
                center = F(4 * m)
                prev = F(4 * m - (2 if frac == 0 and e > 1 else 4))
                nxt = F(4 * m + 4)
                lo, hi = (prev + center) / 2, (center + nxt) / 2
                lcoef = 4 * m - (1 if frac == 0 and e > 1 else 2)
                hcoef = 4 * m + 2
                for d in range(1, 8):
                    for n in range((lcoef - 2) * d, (hcoef + 2) * d + 1):
                        hit = lcoef * d < n < hcoef * d
                        v = F(n, d)
                        assert hit == (lo < v < hi)
                        if hit:
                            assert (v - center) ** 2 < (v - prev) ** 2
                            assert (v - center) ** 2 < (v - nxt) ** 2
                            accepted += 1
                        count += 1
    return {"precisions": [2, 3, 4, 5], "exponent_fields": [1, 6],
            "denominators": [1, 7], "local_grid_cases": count, "accepted": accepted}


def test_random_cells(rng: random.Random) -> dict:
    count = accepted = correct_rejected = 0
    for _ in range(6000):
        p = rng.getrandbits(rng.randrange(1, 129)) or 1
        neg, d, exponent = bool(rng.getrandbits(1)), rng.randrange(1, 1 << 36), rng.randrange(-350, 200)
        exact = F(-p if neg else p, d) * pow2(exponent)
        truth = round32(exact)
        choices = [truth, truth ^ 1, truth ^ SIGN, rng.getrandbits(32)]
        for q in choices:
            hit = limb_cell(neg, split(p), d, exponent, q)
            if hit:
                assert q == truth
                assert strict_cell_reference(-p if neg else p, d, exponent, q)
                accepted += 1
            elif q == truth:
                correct_rejected += 1
            count += 1
    return {"cases": count, "accepted": accepted, "correct_proposals_rejected": correct_rejected}


def test_synthetic_rows(rng: random.Random) -> dict:
    counts = Counter()
    conservative = Counter()
    groups = {}
    eps = host_word(1e-5)
    for group in ("compact_full_bias", "zero_bias", "mixed_subnormal", "wide_exponents"):
        gc = Counter()
        for n in (8, 32, 64, 128, 255, 256):
            for _ in range(4):
                if group == "wide_exponents":
                    words = [(rng.randrange(1, 254) << 23) | rng.getrandbits(23) | (SIGN if rng.getrandbits(1) else 0) for _ in range(n)]
                elif group == "mixed_subnormal":
                    words = [(rng.randrange(0, 4) << 23) | rng.getrandbits(23) | (SIGN if rng.getrandbits(1) else 0) for _ in range(n)]
                else:
                    words = [(rng.randrange(121, 129) << 23) | rng.getrandbits(23) | (SIGN if rng.getrandbits(1) else 0) for _ in range(n)]
                row = prepare_row(words, eps)
                for w in words:
                    g = (rng.randrange(125, 130) << 23) | rng.getrandbits(23) | (SIGN if rng.getrandbits(1) else 0)
                    b = ((SIGN if rng.getrandbits(1) else 0) if group == "zero_bias" else
                         (rng.randrange(122, 129) << 23) | rng.getrandbits(23) | (SIGN if rng.getrandbits(1) else 0))
                    q, reason = attempt(row, w, g, b)
                    qc, rc = attempt(row, w, g, b, zero_aware=False)
                    counts[reason] += 1
                    conservative[rc] += 1
                    gc[reason] += 1
                    if fields(row.denominator_word)[3] != 255:
                        truth = round32((finite_value(w) - row.mean) * finite_value(g) /
                                        finite_value(row.denominator_word) + finite_value(b))
                        if q is not None:
                            assert q == truth
                        if qc is not None:
                            assert qc == truth
                    else:
                        assert q is None and qc is None
        groups[group] = dict(gc)
    return {"description": "Synthetic inputs only; not frozen board inputs and not representative performance evidence.",
            "total_elements": sum(counts.values()), "zero_aware": dict(counts),
            "minimum_of_both_raw_exponents": dict(conservative), "groups": groups}


def test_counterexamples() -> list[dict]:
    examples = []
    p, d, e, q = (1 << 26) - 3, 1, -26, 0x3F800000
    truth = round32(F(p, d) * pow2(e))
    assert truth == 0x3F7FFFFF and not limb_cell(False, split(p), d, e, q)
    assert 1 - pow2(-24) < F(p) * pow2(e) < 1 + pow2(-24)
    examples.append({"name": "symmetric_power_of_two_lower_is_unsound", "proposal": hex(q), "correct": hex(truth)})
    p, e, q = (1 << 24) + 3, -24, 0x3F800001
    truth = round32(F(p) * pow2(e))
    assert truth == 0x3F800002 and not limb_cell(False, split(p), 1, e, q)
    examples.append({"name": "closed_cell_accepts_odd_midpoint", "proposal": hex(q), "correct": hex(truth)})
    v = pow2(-126) - 3 * pow2(-152)
    q = 0x00800000
    assert round32(v) == q
    p = (1 << 26) - 3
    assert limb_cell(False, split(p), 1, -152, q)
    examples.append({"name": "minimum_normal_needs_full_lower_gap", "correct": hex(q)})
    r = prepare_row([0x3F800000, 0x3F800000], 0x3F800000)
    native_negative_zero = host_word((1.0 - 1.0) * -1.0 / 1.0 + -0.0)
    result, reason = attempt(r, 0x3F800000, 0xBF800000, SIGN)
    assert native_negative_zero == SIGN and result is None and reason == "exact_zero"
    examples.append({"name": "exact_rational_zero_is_not_native_negative_zero", "native": hex(SIGN), "correct": hex(0)})
    correct_p = (1 << 82) + (1 << 46)
    wrong_p = 1 << 46
    assert round32(F(correct_p, 1 << 23) * pow2(-23)) != 0x3F800000
    assert limb_cell(False, split(wrong_p), 1 << 23, -23, 0x3F800000)
    examples.append({"name": "truncated_numerator_can_certify_its_own_error", "note": "machine-arithmetic counterexample, not claimed as a full row"})
    r = prepare_row([0x3F800000, 0x3F800000, 0x3F800001], 0x3F800000)
    w, g, b = 0x3F800000, 0x40400000, 0x34000001
    truth = round32((finite_value(w) - r.mean) * finite_value(g) / finite_value(r.denominator_word) + finite_value(b))
    native = host_word((float(finite_value(w)) - float(r.mean)) * float(finite_value(g)) /
                       float(finite_value(r.denominator_word)) + float(finite_value(b)))
    new, reason = attempt(r, w, g, b)
    assert native != truth and new == truth
    examples.append({"name": "full_row_bias_cancellation", "row": [hex(z) for z in [0x3F800000, 0x3F800000, 0x3F800001]],
                     "g": hex(g), "b": hex(b), "dw": hex(r.denominator_word),
                     "native_affine_proposal": hex(native), "numerator_first_accepted": hex(new), "correct": hex(truth)})
    # Shift wrap at width is not integer multiplication by 2^64.
    assert ((1 << (64 % 64)) & MASK) == 1 and (1 << 64) != 1
    examples.append({"name": "word_shift_64_is_not_integer_shift_64"})
    # Overflow boundary: exact threshold goes to infinity, never max finite.
    threshold = (finite_value(MAX_FINITE) + pow2(128)) / 2
    assert round32(threshold) == 0x7F800000
    assert not limb_cell(False, split(threshold.numerator), 1, 0, MAX_FINITE)
    examples.append({"name": "maximum_finite_upper_tie_overflows", "correct": hex(0x7F800000)})
    # Directed output/denominator/input and row guard cases.
    base = prepare_row([0x3F800000, 0x40000000], 0x3F800000)
    for altered in [Row(0, base.b0, base.total, base.denominator_word, base.mean, base.variance),
                    Row(4096, base.b0, base.total, base.denominator_word, base.mean, base.variance),
                    Row(base.n, base.b0, 1 << 60, base.denominator_word, base.mean, base.variance),
                    Row(base.n, base.b0, base.total, 0x7F800000, base.mean, base.variance),
                    Row(base.n, base.b0, base.total, 1, base.mean, base.variance)]:
        assert attempt(altered, 0x3F800000, 0x3F800000, 0)[0] is None
    for special in [0x7F800000, 0xFF800000, 0x7FC00001]:
        assert attempt(base, special, 0x3F800000, 0)[0] is None
        assert attempt(base, 0x3F800000, special, 0)[0] is None
        assert attempt(base, 0x3F800000, 0x3F800000, special)[0] is None
    examples.append({"name": "guard_cases_rejected", "cases": 14,
                     "note": "forged metadata exercises guards only; no claim that these are valid stable rows"})
    return examples


def run(seed: int) -> dict:
    rng = random.Random(seed)
    result = {
        "status": "FINITE_MODEL_PASS",
        "lean_status": "NOT_COMPILED",
        "native_timing_status": "NOT_RUN",
        "seed": seed,
        "word_arithmetic": test_word_arithmetic(rng),
        "toy_formats": test_small_format(),
        "binary32_boundary_grid": test_full32_boundaries(),
        "random_adversarial_proposals": test_random_cells(rng),
        "synthetic_rows": test_synthetic_rows(rng),
        "counterexamples_and_guards": test_counterexamples(),
        "false_accepts": 0,
        "scope": "Finite, independently checked arithmetic models only. No all-input formal proof, no whole-model performance result.",
    }
    return result


if __name__ == "__main__":
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--seed", type=int, default=20261030)
    ap.add_argument("--json", type=Path)
    args = ap.parse_args()
    result = run(args.seed)
    encoded = json.dumps(result, indent=2, ensure_ascii=False) + "\n"
    if args.json:
        args.json.write_text(encoded, encoding="utf-8")
    print(encoded)
