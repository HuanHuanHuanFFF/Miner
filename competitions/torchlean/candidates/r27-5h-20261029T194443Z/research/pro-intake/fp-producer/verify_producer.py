#!/usr/bin/env python3
"""Exact-integer finite checks for the LazyFPOnly producer research.

No host floating-point arithmetic is used. Binary32 inputs are integers in
units 2^-149; products and binary64 accumulator values use units 2^-298.
This is a finite executable model, not a Lean proof or native benchmark.
Run: python3 verify_producer.py --output verification.json
"""

import argparse
from fractions import Fraction
import hashlib
import json
from pathlib import Path
import random


def pow2(e):
    return Fraction(1 << e) if e >= 0 else Fraction(1, 1 << -e)


def fields32(w):
    return (w >> 31), ((w >> 23) & 255), (w & 0x7FFFFF)


def index32(w):
    _, e, _ = fields32(w)
    assert e != 255
    return max(0, e - 1)


def units32(w):
    sign, e, f = fields32(w)
    assert e != 255, "nonfinite input must fail the runtime guard"
    m = f if e == 0 else (1 << 23) + f
    return (-1 if sign else 1) * (m << max(0, e - 1))


def widen_bits(w):
    sign, e, f = fields32(w)
    assert e != 255
    sign64 = sign << 63
    if e == 0:
        if f == 0:
            return sign64
        leading = f.bit_length() - 1
        return (sign64 | ((leading + 874) << 52)
                | ((f - (1 << leading)) << (52 - leading)))
    return sign64 | ((e + 896) << 52) | (f << 29)


def value64(w):
    sign = w >> 63
    e = (w >> 52) & 2047
    f = w & ((1 << 52) - 1)
    assert e != 2047
    m = f if e == 0 else (1 << 52) + f
    v = m * pow2(-1074 if e == 0 else e - 1075)
    return -v if sign else v


def significant_bits(z):
    z = abs(z)
    return 0 if not z else z.bit_length() - ((z & -z).bit_length() - 1)


def rn64_units(z):
    """RN-even to precision 53 on the safe 2^-298 integer lattice.

    The precondition checks rule out exponent-range exceptions. In this range
    integer rounding is exactly binary64 nearest-even value rounding.
    Signed zero is intentionally not modeled by this value-only function.
    """
    if z == 0:
        return 0
    s = -1 if z < 0 else 1
    a = abs(z)
    exponent = a.bit_length() - 1 - 298
    assert -1022 <= exponent <= 1022
    shift = max(0, a.bit_length() - 53)
    if shift == 0:
        return z
    q, r = divmod(a, 1 << shift)
    half = 1 << (shift - 1)
    if r > half or (r == half and q & 1):
        q += 1
    ans = s * (q << shift)
    assert significant_bits(ans) <= 53
    assert abs(ans).bit_length() - 1 - 298 <= 1023
    return ans


def bits64_from_units(z):
    if z == 0:
        return 0
    sign = (1 << 63) if z < 0 else 0
    a = abs(z)
    leading = a.bit_length() - 1
    exp = leading - 298
    assert -1022 <= exp <= 1023
    assert significant_bits(z) <= 53
    mant = a << (52 - leading) if leading <= 52 else a >> (leading - 52)
    word = sign | ((exp + 1023) << 52) | (mant - (1 << 52))
    assert value64(word) == z * pow2(-298)
    return word


def ceil_log2(n):
    return 0 if n <= 1 else (n - 1).bit_length()


def finite32(w):
    return ((w >> 23) & 255) != 255


def normal_or_zero32(w):
    _, e, f = fields32(w)
    return e != 255 and (e != 0 or f == 0)


def narrow_proposal32(w):
    _, e, f = fields32(w)
    return 2 <= e <= 253 and f != 0


def checked_dot(a, b, label):
    assert len(a) == len(b) and 1 <= len(a) <= (1 << 30)
    assert all(finite32(w) for w in a + b)
    n = len(a)
    H = max(map(index32, a)) + max(map(index32, b))
    L = ceil_log2(n)
    N = 1 << L
    M = 1 << (H + 48)  # M=2^(H-250), in 2^-298 units
    uM = Fraction(M, 1 << 53)
    C = Fraction(N * M, 1 << 54)
    products = [units32(x) * units32(y) for x, y in zip(a, b)]
    assert all(abs(t) < M and significant_bits(t) <= 48 for t in products)
    assert all(rn64_units(t) == t for t in products)
    acc = exact = 0
    total_local_error = 0
    for k, t in enumerate(products, 1):
        z = acc + t
        assert abs(z) < k * M <= N * M
        rounded = rn64_units(z)
        err = abs(rounded - z)
        assert abs(rounded) <= k * M
        assert err <= C
        if k == 1:
            assert err == 0
        else:
            assert err <= (k - 1) * uM
        if z:
            assert abs(z) >= 1  # no nonzero value below 2^-298
        if rounded:
            assert abs(rounded) >= 1
        total_local_error += err
        acc = rounded
        exact += t
    error = abs(acc - exact)
    r720 = pow2(H + 2 * L - 5)  # also in 2^-298 units
    r719 = r720 / 2
    assert error <= total_local_error
    assert error <= uM * n * (n - 1) / 2 < r719 < r720
    assert error <= (n - 1) * C < r719
    for const, radius in [(720, r720), (719, r719)]:
        E = H + 2 * L + const
        assert 1 <= E <= 2046
        assert value64(E << 52) == radius * pow2(-298)
    return {
        "label": label, "n": n, "H": H, "L": L,
        "a_raw32": [f"0x{w:08x}" for w in a],
        "b_raw32": [f"0x{w:08x}" for w in b],
        "all_inputs_normal_or_zero": all(map(normal_or_zero32, a + b)),
        "sum64_bits_value_model": f"0x{bits64_from_units(acc):016x}",
        "signed_zero_note": "value model canonicalizes zero; widen sign tested separately",
        "exact_sum_units_2pow_minus298": str(exact),
        "rounded_sum_units_2pow_minus298": str(acc),
        "absolute_error_units_2pow_minus298": str(error),
        "absolute_error": str(error * pow2(-298)),
        "radius720": str(r720 * pow2(-298)),
        "radius719": str(r719 * pow2(-298)),
        "error_over_radius719": str(Fraction(error, 1) / r719),
    }


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--output", default="verification.json")
    args = ap.parse_args()
    rng = random.Random(0x4C465032)
    count = {"widen_words": 0, "product_pairs": 0, "dot_vectors": 0,
             "dot_terms": 0, "radius_H_L_pairs": 0}
    # Both signs, every finite exponent, and boundary/interior significands.
    for e in range(255):
        for f in [0, 1, 2, 3, 0x3FFFFF, 0x400000, 0x7FFFFE, 0x7FFFFF]:
            for sign in [0, 1]:
                w = (sign << 31) | (e << 23) | f
                assert value64(widen_bits(w)) == units32(w) * pow2(-149)
                count["widen_words"] += 1
    assert widen_bits(0x00000000) == 0x0000000000000000
    assert widen_bits(0x80000000) == 0x8000000000000000
    for w in [0x7F800000, 0xFF800000, 0x7FC00000, 0x7F800001]:
        assert not finite32(w) and not normal_or_zero32(w)
    assert not normal_or_zero32(0x00000001)
    assert not normal_or_zero32(0x807FFFFF)
    assert normal_or_zero32(0x00000000) and normal_or_zero32(0x80000000)
    assert narrow_proposal32(0x3F800001)
    for w in [0, 0x80000000, 0x00800001, 0x3F800000, 0x7F000001, 0x7F800000]:
        assert not narrow_proposal32(w)

    edge = [0, 0x80000000, 1, 0x80000001, 0x007FFFFF, 0x807FFFFF,
            0x00800000, 0x80800000, 0x00800001, 0x3F800000, 0x3F800001,
            0xBF800000, 0x32000000, 0x7F7FFFFF, 0xFF7FFFFF]

    def random_finite():
        if rng.randrange(3) == 0:
            return rng.choice(edge)
        return (rng.randrange(2) << 31) | (rng.randrange(255) << 23) | rng.randrange(1 << 23)

    pairs = [(x, y) for x in edge for y in edge]
    pairs += [(random_finite(), random_finite()) for _ in range(4096)]
    for x, y in pairs:
        t = units32(x) * units32(y)
        assert significant_bits(t) <= 48 and rn64_units(t) == t
        if t:
            exp = abs(t).bit_length() - 1 - 298
            assert -298 <= exp <= 255
        count["product_pairs"] += 1

    cases = [
        ("min_subnormal_squared_n1", [1], [1]),
        ("max_finite_squared_n1", [0x7F7FFFFF], [0x7F7FFFFF]),
        ("max_times_min_subnormal", [0x7F7FFFFF], [1]),
        ("min_normal_squared", [0x00800000], [0x00800000]),
        ("negative_zero_input", [0x80000000], [0x7F7FFFFF]),
        ("all_signed_zeros", [0, 0x80000000, 0x80000000], [0x80000000, 0, 0x80000000]),
        ("exact_cancellation", [0x7F7FFFFF, 0xFF7FFFFF], [0x7F7FFFFF, 0x7F7FFFFF]),
        ("cancellation_loses_min_product", [0x7F7FFFFF, 1, 0xFF7FFFFF],
         [0x7F7FFFFF, 1, 0x7F7FFFFF]),
        ("two_normal_products_not_exact", [0x3F800001, 0x32000000],
         [0x3F800000, 0x32000000]),
        ("normal_cancellation_not_exact", [0x3F800000, 0x32000000, 0xBF800000],
         [0x3F800000, 0x32000000, 0x3F800000]),
        ("normal_inputs_reach_smallest_product_lattice", [0x00800001, 0x00800000],
         [0x00800001, 0x80800002]),
        ("bias_must_contribute_to_H", [0x00800000, 0x3F800000],
         [0x00800000, 0x3F800000]),
    ]
    detailed = []
    for label, a, b in cases:
        rec = checked_dot(a, b, label)
        detailed.append(rec)
        count["dot_vectors"] += 1
        count["dot_terms"] += len(a)
    lengths = [1, 2, 3, 4, 7, 8, 16, 31, 32, 33, 63, 64, 65, 127, 128, 129, 255, 256, 257]
    max_ratio = Fraction(0)
    worst = None
    for i in range(512):
        n = lengths[i % len(lengths)]
        a = [random_finite() for _ in range(n)]
        b = [random_finite() for _ in range(n)]
        rec = checked_dot(a, b, f"seeded_{i}")
        ratio = Fraction(rec["error_over_radius719"])
        if ratio > max_ratio:
            max_ratio, worst = ratio, rec
        count["dot_vectors"] += 1
        count["dot_terms"] += n
    # Exhaust the finite exponent-encoding parameter rectangle, not inputs.
    for H in range(507):
        for L in range(31):
            for const in [719, 720]:
                E = H + 2 * L + const
                assert 1 <= E <= 2046
                assert value64(E << 52) == pow2(H + 2 * L + const - 1023)
            count["radius_H_L_pairs"] += 1
    # Exact arithmetic checks at the length limit. No billion-term loop.
    N = 1 << 30
    u = Fraction(1, 1 << 53)
    m = N - 2
    growth_majorant = 1 / (1 - m * u)
    standard_coefficient = Fraction((N - 1) * (N + 2), 2)
    assert standard_coefficient * growth_majorant < N * N
    uniform_growth_majorant = 1 / (1 - Fraction(1, 1 << 23))
    assert Fraction(9, 16) * uniform_growth_majorant < 1
    assert Fraction(N * (N - 1), 2) < Fraction(N * N, 2)
    # Genuine counterexample to ignoring the bias when forming H.
    bias_rec = detailed[-1]
    missed_bias_error = Fraction(bias_rec["absolute_error"])
    wrong_H_radius = pow2(0 + 2 * ceil_log2(2) - 303)
    assert missed_bias_error == pow2(-252) > wrong_H_radius
    # Genuine counterexample to exact accumulation on unrestricted normal inputs.
    by_label = {rec["label"]: rec for rec in detailed}
    cancellation = by_label["normal_cancellation_not_exact"]
    assert Fraction(cancellation["absolute_error"]) == pow2(-54)
    assert cancellation["rounded_sum_units_2pow_minus298"] == "0"
    tiny_normal = by_label["normal_inputs_reach_smallest_product_lattice"]
    assert tiny_normal["all_inputs_normal_or_zero"]
    assert tiny_normal["exact_sum_units_2pow_minus298"] == "1"
    assert tiny_normal["rounded_sum_units_2pow_minus298"] == "1"
    # Independent scaling check of the compact 718 counterexample.
    a718 = [0x3FFFFFFF] * 512
    b718 = [0x3FFFFFFF] * 128 + [0x3FFFFFFB] * 128 + [0x3FFFFFF7] * 256
    rec718 = checked_dot(a718, b718, "718_counterexample_crosscheck")
    count["dot_vectors"] += 1
    count["dot_terms"] += 512
    assert int(rec718["exact_sum_units_2pow_minus298"]) == 144115127946316800 << 252
    assert int(rec718["rounded_sum_units_2pow_minus298"]) == 144115127946318880 << 252
    assert Fraction(rec718["absolute_error"]) == 2080 * pow2(-46) > pow2(-35)
    assert rec718["sum64_bits_value_model"] == "0x409fffff20000142"
    result = {
        "status": "PASS_FINITE_INTEGER_MODEL",
        "seed": "0x4c465032",
        "script_sha256": hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        "counts": count,
        "uses_host_float": False,
        "lean_status": "NOT_COMPILED",
        "native_benchmark_status": "NOT_RUN",
        "scope": "Finite tests plus integer checks; universal proof is in the report, not inferred from these tests.",
        "max_length_checked_by_loop": 512,
        "length_2pow30_check": "symbolic integer/rational bound only; no full dot execution",
        "radius_counterexample_found": False,
        "radius_counterexample_scope": "No 719/720 counterexample; 718 has an exact counterexample.",
        "radius718_counterexample_crosscheck": {
            k: rec718[k] for k in ["n", "H", "L", "sum64_bits_value_model",
                                    "absolute_error", "error_over_radius719"]
        },
        "uniform_growth_majorant": str(uniform_growth_majorant),
        "standard_bound_ratio_at_n_2pow30": str(standard_coefficient * growth_majorant / (N * N)),
        "detailed_boundary_vectors": detailed,
        "worst_seeded_vector": worst,
        "max_seeded_error_over_radius719": str(max_ratio),
        "unsafe_bias_omission": {
            "wrong_H": 0, "actual_H": bias_rec["H"],
            "error": str(missed_bias_error), "wrong_radius720": str(wrong_H_radius),
            "error_over_wrong_radius": str(missed_bias_error / wrong_H_radius),
        },
    }
    out = Path(args.output)
    out.write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"status": result["status"], "counts": count,
                      "output": str(out), "max_seeded_error_over_radius719": str(max_ratio)},
                     ensure_ascii=False))


if __name__ == "__main__":
    main()
