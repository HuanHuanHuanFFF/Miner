#!/usr/bin/env python3
"""Independent finite binary32 checks for fixed-ULP transition summaries.

No repository or historical data is read.  Random probes draw a fresh seed on
each invocation.  This script is a proof aid, not a production kernel or timing
benchmark; all reference additions use exact Python integer arithmetic.
"""

from __future__ import annotations

import json
import random
import secrets
import struct
from dataclasses import dataclass
from fractions import Fraction
from pathlib import Path


HERE = Path(__file__).resolve().parent
L = 1 << 23
U = 1 << 24


def units(word: int) -> int:
    """Finite binary32 as an integer times 2**-149."""
    e = (word >> 23) & 255
    f = word & 0x7FFFFF
    if e == 255:
        raise ValueError("finite inputs only")
    v = f if e == 0 else ((1 << 23) | f) << (e - 1)
    return -v if word >> 31 else v


def rn_word(value: int) -> int:
    """RN-even of an integer times 2**-149, including gradual subnormals."""
    if not value:
        return 0
    sign = 0x80000000 if value < 0 else 0
    n = abs(value)
    if n < 1 << 23:
        return sign | n
    shift = max(0, n.bit_length() - 24)
    m = n >> shift
    if shift:
        rem = n - (m << shift)
        half = 1 << (shift - 1)
        if rem > half or (rem == half and (m & 1)):
            m += 1
    if m == 1 << 24:
        m >>= 1
        shift += 1
    e = shift + 1
    if e >= 255:
        return sign | 0x7F800000
    return sign | (e << 23) | (m - (1 << 23))


def add_words(a: int, b: int) -> int:
    z = units(a) + units(b)
    if z == 0 and a == b == 0x80000000:
        return 0x80000000
    return rn_word(z)


def f32(w: int) -> float:
    return struct.unpack(">f", struct.pack(">I", w))[0]


def hexword(w: int) -> str:
    return f"0x{w:08x}"


def rn_integer(x: Fraction) -> int:
    n, rem = divmod(x.numerator, x.denominator)
    twice = rem * 2
    if twice > x.denominator or (twice == x.denominator and (n & 1)):
        n += 1
    return n


def floor_frac(x: Fraction) -> int:
    return x.numerator // x.denominator


def ceil_frac(x: Fraction) -> int:
    return -((-x.numerator) // x.denominator)


@dataclass(frozen=True)
class Summary:
    # Offsets for starting k of parity 0 and 1; extremal prefix offsets.
    d: tuple[int, int]
    lo: tuple[int, int]
    hi: tuple[int, int]
    # Raw-value certificate, quantized as floor(r+1/4), ceil(r-1/2).
    rawlo: tuple[int, int]
    rawhi: tuple[int, int]


def one(r: Fraction) -> Summary:
    d = tuple(rn_integer(Fraction(p) + r) - p for p in (0, 1))
    low = floor_frac(r + Fraction(1, 4))
    high = ceil_frac(r - Fraction(1, 2))
    return Summary(d, d, d, (low, low), (high, high))


def compose(a: Summary, b: Summary) -> Summary:
    # b AFTER a, preserving original input order.
    d, lo, hi, rawlo, rawhi = [], [], [], [], []
    for p in (0, 1):
        t = (p + a.d[p]) & 1
        d.append(a.d[p] + b.d[t])
        lo.append(min(a.lo[p], a.d[p] + b.lo[t]))
        hi.append(max(a.hi[p], a.d[p] + b.hi[t]))
        rawlo.append(min(a.rawlo[p], a.d[p] + b.rawlo[t]))
        rawhi.append(max(a.rawhi[p], a.d[p] + b.rawhi[t]))
    return Summary(tuple(d), tuple(lo), tuple(hi), tuple(rawlo), tuple(rawhi))


def summarize(rs: list[Fraction]) -> Summary:
    assert rs
    result = one(rs[0])
    for r in rs[1:]:
        result = compose(result, one(r))
    return result


def q_units(qexp: int) -> int:
    assert qexp >= -149
    return 1 << (qexp + 149)


def model(start: int, words: list[int], qexp: int) -> dict:
    qu = q_units(qexp)
    assert units(start) % qu == 0
    k = units(start) // qu
    rs = [Fraction(units(w), qu) for w in words]
    summary = summarize(rs)
    p = k & 1
    predicted = k + summary.d[p]
    actual = start
    actual_prefix = []
    for w in words:
        actual = add_words(actual, w)
        actual_prefix.append(hexword(actual))
    return {
        "start": hexword(start),
        "inputs": [hexword(w) for w in words],
        "q_exponent": qexp,
        "start_k": k,
        "summary_d": summary.d,
        "predicted_k": predicted,
        "predicted_word_if_rounded_again": hexword(rn_word(predicted * qu)),
        "actual": hexword(actual),
        "actual_prefixes": actual_prefix,
        "grid_exactly_matches_actual": units(actual) == predicted * qu,
        "safe_rounded_prefix_certificate": k + summary.lo[p] >= L + 1 and k + summary.hi[p] <= U,
        "safe_raw_prefix_certificate": k + summary.rawlo[p] >= L and k + summary.rawhi[p] <= U,
        "rounded_prefix_k_range": [k + summary.lo[p], k + summary.hi[p]],
    }


def dense_word(w: int) -> int:
    return (w & 0x807FFFFF) | ((124 + (w >> 23) % 7) << 23)


def relu_word(w: int) -> int:
    return 0 if not (w & 1) else dense_word(w) & 0x7FFFFFFF


def naive_sum(words: list[int]) -> int:
    acc = 0
    for w in words:
        acc = add_words(acc, w)
    return acc


def main() -> None:
    seed = secrets.randbits(128)
    rng = random.Random(seed)
    result: dict = {
        "fresh_random_seed_hex": f"{seed:032x}",
        "reference": "finite addition uses exact integer multiples of 2^-149; no native float in reference",
        "counterexamples": {},
    }
    cases = {
        "lower_boundary_dense": (0x3F900000, [0xBE000004], -23),
        "lower_boundary_exact_safe_equality_dense": (0x3F900000, [0xBE000002], -23),
        "endpoint_only_misses_upper_excursion_dense": (0x3FC00000, [0x3F000002, 0xBF000000], -23),
        "endpoint_only_misses_lower_excursion_dense": (0x3FC00000, [0xBF000001, 0x3E800004], -23),
        "parity_matters_dense": (0x40000001, [0x3E000008], -22),
        "no_tie_does_not_mean_round_exact_block_sum": (0x40000000, [0x3E000004] * 3, -22),
    }
    for name, args in cases.items():
        result["counterexamples"][name] = model(*args)
    c = result["counterexamples"]["no_tie_does_not_mean_round_exact_block_sum"]
    exact_total = units(0x40000000) + 3 * units(0x3E000004)
    c["one_round_of_exact_total"] = hexword(rn_word(exact_total))
    result["counterexamples"]["same_exact_sum_different_order"] = {
        "a": [hexword(w) for w in [0x3F800000, 0x3E000004, 0xBF800000]],
        "b": [hexword(w) for w in [0x3F800000, 0xBF800000, 0x3E000004]],
        "a_sequential": hexword(naive_sum([0x3F800000, 0x3E000004, 0xBF800000])),
        "b_sequential": hexword(naive_sum([0x3F800000, 0xBF800000, 0x3E000004])),
        "both_exact_sum": "0x3e000004",
    }
    result["counterexamples"]["crossing_breaks_period_two"] = {
        "a": "0x3f800003", "b": "0x3f800005", "x": "0x3f800000",
        "T_a": hexword(add_words(0x3F800003, 0x3F800000)),
        "T_b": hexword(add_words(0x3F800005, 0x3F800000)),
        "input_difference_in_q": 2, "output_difference_in_q": 0,
    }
    # Multiplication is a separate RN stage. Exact product is an integer in
    # units 2^-298; this particular product equals 1 - 2^-46.
    result["counterexamples"]["fma_changes_bmm"] = {
        "first_product": ["0xbf800000", "0x3f800000"],
        "second_product": ["0x3f800001", "0x3f7ffffe"],
        "second_product_rounded": "0x3f800000",
        "mul_then_add": "0x00000000",
        "fused_second_update": "0xa8800000",
        "derivation": "(1+2^-23)*(1-2^-23)=1-2^-46; separate RN product is 1, fused add with -1 is -2^-46",
    }

    # All named dense counterexamples embed in n=1000 without answer caching.
    neutral2 = [0x3E000000, 0xBE000000]
    neutral3 = [0x3E800000, 0xBE000000, 0xBE000000]
    seq2 = neutral2 * 499 + [0x3F900000, 0xBE000004]
    seq3 = neutral2 * 497 + neutral3 + [0x3FC00000, 0x3F000002, 0xBF000000]
    assert len(seq2) == len(seq3) == 1000
    assert all(124 <= ((w >> 23) & 255) <= 130 for w in seq2 + seq3)
    result["n1000_dense_embeddings"] = {
        "lower_boundary_final": hexword(naive_sum(seq2)),
        "upper_excursion_final": hexword(naive_sum(seq3)),
        "padding": "exact cancellation pairs (+0.125,-0.125), plus (+0.25,-0.125,-0.125) for odd padding length",
    }

    counts = {"associativity_blocks": 0, "parity_evaluations": 0,
              "boundary_cases": 0, "accepted_simple": 0, "accepted_raw": 0,
              "signed_dense_blocks": 0, "signed_dense_accepted": 0,
              "relu_monotone_blocks": 0, "relu_accepted": 0,
              "finite_reference_native_checks": 0}
    for _ in range(5000):
        rs = [Fraction(rng.randrange(-50000, 50001), 1 << rng.randrange(0, 10))
              for _ in range(rng.randrange(3, 33))]
        cut1 = rng.randrange(1, len(rs) - 1)
        cut2 = rng.randrange(cut1 + 1, len(rs))
        a, b, c = summarize(rs[:cut1]), summarize(rs[cut1:cut2]), summarize(rs[cut2:])
        lhs = compose(compose(a, b), c)
        rhs = compose(a, compose(b, c))
        assert lhs == rhs == summarize(rs)
        assert abs(lhs.d[0] - lhs.d[1]) <= 1
        for k in (-3, -2, -1, 0, 1, 2, L, L + 1):
            direct = k
            for r in rs:
                direct = rn_integer(Fraction(direct) + r)
            assert direct == k + lhs.d[k & 1]
            counts["parity_evaluations"] += 1
        counts["associativity_blocks"] += 1

    # Exhaustive small neighborhood in units q/8 at many binade boundaries.
    # e>=-122 ensures q/8 is representable. Avoid the overflow binade e=127.
    for e in (-122, -50, -3, 0, 3, 5, 20, 80, 126):
        qe = e - 23
        qu = q_units(qe)
        for k in (L, L + 1, L + 2, U - 2, U - 1, U):
            for num in range(-32, 33):
                x = rn_word(num * (qu // 8))
                start = rn_word(k * qu)
                s = summarize([Fraction(units(x), qu)])
                p = k & 1
                expected_units = (k + s.d[p]) * qu
                actual = units(add_words(start, x))
                simple = k + s.lo[p] >= L + 1 and k + s.hi[p] <= U
                raw = k + s.rawlo[p] >= L and k + s.rawhi[p] <= U
                if simple:
                    assert actual == expected_units
                    counts["accepted_simple"] += 1
                if raw:
                    assert actual == expected_units
                    counts["accepted_raw"] += 1
                counts["boundary_cases"] += 1

    for _ in range(3000):
        e = rng.randrange(-3, 15)
        qe = e - 23
        qu = q_units(qe)
        sign = rng.choice((-1, 1))
        k = rng.randrange(L, U)
        start = rn_word(sign * k * qu)
        words = [dense_word(rng.getrandbits(32)) for _ in range(rng.randrange(1, 33))]
        s = summarize([Fraction(sign * units(w), qu) for w in words])
        p = k & 1
        accepted = k + s.rawlo[p] >= L and k + s.rawhi[p] <= U
        if accepted:
            actual = start
            for word in words:
                actual = add_words(actual, word)
            assert units(actual) == sign * (k + s.d[p]) * qu
            counts["signed_dense_accepted"] += 1
        counts["signed_dense_blocks"] += 1

    for _ in range(3000):
        e = rng.randrange(5, 13)
        qe = e - 23
        qu = q_units(qe)
        k = rng.randrange(L, U)
        start = rn_word(k * qu)
        words = [relu_word(rng.getrandbits(32)) for _ in range(rng.randrange(1, 65))]
        rs = [Fraction(units(w), qu) for w in words]
        # For e>=5 and input E<=130, every nonzero odd significand has
        # exponent gap >=2; therefore it cannot land exactly at a half-ULP.
        assert all(r.denominator != 2 for r in rs)
        s = summarize(rs)
        assert s.d[0] == s.d[1]
        accepted = k + s.d[k & 1] <= U
        if accepted:
            actual = start
            for w in words:
                actual = add_words(actual, w)
            assert units(actual) == (k + s.d[k & 1]) * qu
            counts["relu_accepted"] += 1
        counts["relu_monotone_blocks"] += 1

    # A secondary independent sanity check of the exact integer RN reference.
    # Python double addition followed by binary32 conversion is used only here.
    for _ in range(10000):
        a = (rng.getrandbits(1) << 31) | rng.randrange(0, 0x7F800000)
        b = (rng.getrandbits(1) << 31) | rng.randrange(0, 0x7F800000)
        native = f32(a) + f32(b)
        try:
            word = struct.unpack(">I", struct.pack(">f", native))[0]
        except OverflowError:
            word = 0xFF800000 if native < 0 else 0x7F800000
        assert add_words(a, b) == word
        counts["finite_reference_native_checks"] += 1

    result["test_counts"] = counts
    result["all_assertions_passed"] = True
    output = HERE / "verification_results.json"
    output.write_text(json.dumps(result, indent=2) + "\n")
    print(json.dumps({"output": str(output), "test_counts": counts, "all_assertions_passed": True}, indent=2))


if __name__ == "__main__":
    main()
