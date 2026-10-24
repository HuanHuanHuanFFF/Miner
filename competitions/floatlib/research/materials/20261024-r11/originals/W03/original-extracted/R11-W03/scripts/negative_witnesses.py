#!/usr/bin/env python3
"""Small exact rational witnesses; NOT a FloatLib/Lean or candidate validator.

Only finite binary32 operands are supported. All rounding uses integer/Fraction
arithmetic. No host floating arithmetic, foreign candidate code, or timing.
"""
from fractions import Fraction
import json


def pow2(e):
    return Fraction(1 << e, 1) if e >= 0 else Fraction(1, 1 << -e)


def decode(w):
    sign, e, f = w >> 31, (w >> 23) & 255, w & 0x7fffff
    if e == 255:
        raise ValueError("This witness runner deliberately excludes NaN/Inf")
    v = Fraction(f) * pow2(-149) if e == 0 else Fraction((1 << 23) + f) * pow2(e - 150)
    return -v if sign else v


def int_rne(x):
    q, r = divmod(x.numerator, x.denominator)
    return q + int(2 * r > x.denominator or (2 * r == x.denominator and q % 2))


def round32(x, zero_sign=0):
    x = Fraction(x)
    if x == 0:
        return int(zero_sign) << 31
    sign = int(x < 0)
    x = abs(x)
    e = x.numerator.bit_length() - x.denominator.bit_length()
    if x < pow2(e):
        e -= 1
    if e < -126:
        m = int_rne(x / pow2(-149))
        return (sign << 31) | m
    m = int_rne(x / pow2(e - 23))
    if m == 1 << 24:
        m >>= 1
        e += 1
    if e > 127:
        return (sign << 31) | 0x7f800000
    return (sign << 31) | ((e + 127) << 23) | (m - (1 << 23))


def mul32(a, b):
    return round32(decode(a) * decode(b), (a ^ b) >> 31)


def add32(a, b):
    x, y = decode(a), decode(b)
    # Under RN-even, exact cancellation is +0, except (-0)+(-0).
    neg_zero = x == 0 and y == 0 and (a >> 31) and (b >> 31)
    return round32(x + y, neg_zero)


def hx(x):
    return f"0x{x:08x}"


def main():
    negzero, one, zero = 0x80000000, 0x3f800000, 0
    p = mul32(negzero, one)
    a = [0xbf800000, 0x3f800001]
    b = [0x3f800000, 0x3f7ffffe]
    s1 = add32(0, mul32(a[0], b[0]))
    separate = add32(s1, mul32(a[1], b[1]))
    fused = round32(decode(s1) + decode(a[1]) * decode(b[1]))
    double_exact = round32(sum((decode(x) * decode(y) for x, y in zip(a, b)), Fraction()))
    result = {
        "status": "EXACT_FINITE_RATIONAL_WITNESSES_ONLY",
        "candidate_validation": "NOT_RUN",
        "cases": [
            {"name": "n1_leading_zero_required", "a": hx(negzero), "b": hx(one),
             "required": hx(add32(zero, p)), "bare_product": hx(p)},
            {"name": "n2_two_negative_zero_products", "required": hx(add32(add32(zero, p), p)),
             "sum_products_without_leading_zero": hx(add32(p, p))},
            {"name": "n2_second_step_fma_forbidden", "a": list(map(hx, a)), "b": list(map(hx, b)),
             "second_product_exact": str(decode(a[1]) * decode(b[1])),
             "ordered_separate": hx(separate), "fused_second_step": hx(fused)},
            {"name": "widened_exact_accumulation_differs", "ordered_binary32": hx(separate),
             "round_once_exact_dot": hx(double_exact)}
        ],
        "limits": "No NaN payload model; no generated C; no timing; no all-input proof."
    }
    assert add32(zero, p) == 0 and p == 0x80000000
    assert add32(add32(zero, p), p) == 0 and add32(p, p) == 0x80000000
    assert separate == 0 and fused == 0xa8800000 and double_exact == 0xa8800000
    print(json.dumps(result, indent=2))


if __name__ == "__main__":
    main()
