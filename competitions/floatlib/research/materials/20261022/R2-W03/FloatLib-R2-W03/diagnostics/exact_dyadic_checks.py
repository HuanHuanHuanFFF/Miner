#!/usr/bin/env python3
"""Finite diagnostic, not a Lean proof, benchmark, or exhaustive 2^32 test.

No random seed or measured-case-specific answer table is used.  IEEE binary32
RN-even is modeled by integer shifts and tie tests.  The test domain enumerates
every exponent and both signs at structured mantissa boundaries.
"""
import json
from pathlib import Path

FRAC = (1 << 23) - 1
SIGN = 1 << 31


def round_shift_even(n, shift):
    if shift <= 0:
        return n << -shift
    q, r = divmod(n, 1 << shift)
    half = 1 << (shift - 1)
    return q + (r > half or (r == half and (q & 1)))


def encode(sign, n, q):
    """Round the nonnegative exact dyadic n*2^q, then apply explicit sign."""
    if n == 0:
        return sign << 31
    e = n.bit_length() - 1 + q
    if e < -126:
        m = round_shift_even(n, -149 - q)
        # Rounding at the subnormal boundary may produce the minimum normal.
        return (sign << 31) | m
    m = round_shift_even(n, n.bit_length() - 24)
    if m == 1 << 24:
        m >>= 1
        e += 1
    if e > 127:
        return (sign << 31) | 0x7F800000
    return (sign << 31) | ((e + 127) << 23) | (m - (1 << 23))


def decode(u):
    e, f = (u >> 23) & 255, u & FRAC
    assert e < 255
    return u >> 31, (f if e == 0 else (1 << 23) | f), max(e, 1) - 150


def mul(a, b):
    sa, ma, ea = decode(a)
    sb, mb, eb = decode(b)
    return encode(sa ^ sb, ma * mb, ea + eb)


def power_bits(q):
    assert -149 <= q <= 127
    return (1 << (q + 149)) if q < -126 else ((q + 127) << 23)


def factor_bits(e):
    assert 1 <= e <= 254
    return (1 << (e - 1)) if e <= 23 else ((e - 23) << 23)


def reconstruct_normal(u):
    e, f = (u >> 23) & 255, u & FRAC
    assert 1 <= e <= 254
    m = f | (1 << 23)
    return mul(encode(0, m, 0), factor_bits(e)) ^ (u & SIGN)


def reconstruct_finite(u):
    s, m, q = decode(u)
    return mul(encode(0, m, 0), power_bits(q)) ^ (s << 31)


def reconstruct_two_stage_normal(u):
    e, f = (u >> 23) & 255, u & FRAC
    assert 1 <= e <= 254
    m = f | (1 << 23)
    normalized = mul(encode(0, m, 0), power_bits(-23))
    return mul(normalized, power_bits(e - 127)) ^ (u & SIGN)


def reconstruct_dense_shift32(u):
    e, f = (u >> 23) & 255, u & FRAC
    assert 124 <= e <= 130
    n = ((1 << 23) | f) << (e - 124)
    assert n < (1 << 30)
    return mul(encode(0, n, 0), power_bits(-26)) ^ (u & SIGN)


def reconstruct_block_shift32(u):
    e, f = (u >> 23) & 255, u & FRAC
    assert 24 <= e <= 254
    q, r = e >> 3, e & 7
    n = ((1 << 23) | f) << r
    assert n < (1 << 31)
    return mul(encode(0, n, 0), power_bits(8 * q - 150)) ^ (u & SIGN)


def reconstruct_block_shift64(u):
    e, f = (u >> 23) & 255, u & FRAC
    assert 24 <= e <= 254
    q, r = (e - 24) >> 5, (e - 24) & 31
    n = ((1 << 23) | f) << r
    assert n < (1 << 55)
    return mul(encode(0, n, 0), power_bits(32 * q - 126)) ^ (u & SIGN)


def fractions():
    fs = set(range(32)) | set(range((1 << 23) - 32, 1 << 23))
    for k in range(23):
        for delta in range(-3, 4):
            f = (1 << k) + delta
            if 0 <= f <= FRAC:
                fs.add(f)
    return sorted(fs)


def run():
    normal_count = finite_count = 0
    dense_shift32_count = block_shift32_count = block_shift64_count = 0
    fs = fractions()
    for e in range(1, 255):
        assert factor_bits(e) == power_bits(e - 150)
        for s in range(2):
            for f in fs:
                u = (s << 31) | (e << 23) | f
                assert reconstruct_normal(u) == u
                assert reconstruct_two_stage_normal(u) == u
                normal_count += 1
                if 124 <= e <= 130:
                    assert reconstruct_dense_shift32(u) == u
                    dense_shift32_count += 1
                if 24 <= e <= 254:
                    assert reconstruct_block_shift32(u) == u
                    block_shift32_count += 1
                    assert reconstruct_block_shift64(u) == u
                    block_shift64_count += 1
    for e in range(255):
        for s in range(2):
            for f in fs:
                u = (s << 31) | (e << 23) | f
                assert reconstruct_finite(u) == u
                finite_count += 1

    # A no-table, one-conversion special case: representable unsigned integers.
    shifted_count = 0
    for e in range(150, 159):
        for s in range(2):
            for f in fs:
                m = f | (1 << 23)
                n = m << (e - 150)
                assert n < 1 << 32
                assert encode(s, n, 0) == ((s << 31) | (e << 23) | f)
                shifted_count += 1

    failures = []
    # An implicit one must not be added to the subnormal significand.
    bad_subnormal = mul(encode(0, (1 << 23) | 1, 0), power_bits(-149))
    assert bad_subnormal == 0x00800001
    failures.append(dict(name="hidden_bit_on_subnormal", input="00000001",
                         expected="00000001", got=f"{bad_subnormal:08x}"))
    # The unadjusted normal exponent formula asks for unrepresentable 2^-150.
    rounded_scale = encode(0, 1, -150)
    assert rounded_scale == 0
    bad_scale = mul(encode(0, (1 << 23) | 1, 0), rounded_scale)
    failures.append(dict(name="normal_formula_on_E0", input="00000001",
                         expected="00000001", got=f"{bad_scale:08x}"))
    # Blind normal-only scale encoding wraps for small E.
    wrapped = (((1 - 23) & 0xFFFFFFFF) << 23) & 0xFFFFFFFF
    bad_wrapped = mul(encode(0, 1 << 23, 0), wrapped)
    assert wrapped == 0xF5000000 and bad_wrapped == 0xFF800000
    failures.append(dict(name="wrapped_factor_encoding", input="00800000",
                         expected="00800000", scale=f"{wrapped:08x}",
                         got=f"{bad_wrapped:08x}"))
    # Scaling before normalizing the mantissa overflows although output is finite.
    bad_first_step = mul(encode(0, 1 << 23, 0), power_bits(127))
    assert bad_first_step == 0x7F800000
    failures.append(dict(name="wrong_two_stage_order", input="7f000000",
                         expected="7f000000", intermediate="7f800000",
                         got="7f800000"))
    failures.append(dict(name="DAZ_on_scale", input="00800000",
                         expected="00800000", scale="00000001",
                         got="00000000", note="Outside the gradual-subnormal contract"))
    failures.append(dict(name="zero_minus_magnitude", input="80000000",
                         expected="80000000", got="00000000",
                         note="RN-even: +0 - +0 = +0; use native negation for -0"))
    # Extending the dense UInt32 shift formula without an overflow guard fails.
    wrapped_n = ((1 << 23) << (133 - 124)) & 0xFFFFFFFF
    assert wrapped_n == 0
    bad_shift = mul(encode(0, wrapped_n, 0), power_bits(-26))
    failures.append(dict(name="dense_shift32_overflow_at_E133", input="42800000",
                         expected="42800000", got=f"{bad_shift:08x}"))

    return dict(status="PASS", proof_status="NOT_A_LEAN_PROOF",
                fractions_per_exponent=len(fs), normal_cases=normal_count,
                all_finite_cases=finite_count, shifted_integer_cases=shifted_count,
                dense_shift32_cases=dense_shift32_count,
                block_shift32_cases=block_shift32_count,
                block_shift64_cases=block_shift64_count,
                checked_normal_exponents=[1, 254], checked_finite_exponents=[0, 254],
                counterexamples=failures,
                limitations=["Structured finite diagnostics, not exhaustive over all 2^32 bit patterns",
                             "No NaN payload model is used; nonfinite values require exact original fallback",
                             "No performance measurements are made by this script"])


if __name__ == "__main__":
    result = run()
    p = Path(__file__).with_name("exact_dyadic_results.json")
    p.write_text(json.dumps(result, indent=2, ensure_ascii=False) + "\n")
    print(json.dumps(result, ensure_ascii=False))
