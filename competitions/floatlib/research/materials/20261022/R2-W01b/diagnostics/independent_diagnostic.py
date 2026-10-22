#!/usr/bin/env python3
"""Independent finite diagnostic; pure integer binary32 model, no C benchmark.

The decoder specification comes only from the R2-W01b handoff. All arithmetic
below uses exact Python integers and round-to-nearest/ties-to-even. NaNs model
Lean Float32.toBits' observable canonical value, not physical payload bytes.
"""

from collections import Counter
import hashlib
import json
from pathlib import Path
import random

MASK = 0xFFFFFFFF
SIGN = 0x80000000
FRAC = 0x7FFFFF
INF = 0x7F800000
NAN = 0x7FC00000
LOWER = 0x0C000000


def is_nan(u):
    return (u & INF) == INF and (u & FRAC) != 0


def canonical(u):
    return NAN if is_nan(u) else u


def split_finite(u):
    e, f = (u >> 23) & 255, u & FRAC
    assert e < 255
    return (f, -149) if e == 0 else (0x800000 | f, e - 150)


def round_shift_even(n, shift):
    if shift <= 0:
        return n << -shift
    q, r = divmod(n, 1 << shift)
    half = 1 << (shift - 1)
    return q + (r > half or (r == half and q & 1))


def pack_exact(sign, n, power):
    """Round sign * n * 2**power to binary32, retaining a zero sign."""
    assert sign in (0, SIGN) and n >= 0
    if n == 0:
        return sign
    top = n.bit_length() - 1
    exponent = top + power
    if exponent > 127:
        return sign | INF
    if exponent < -126:
        significand = round_shift_even(n, -149 - power)
        assert significand <= 0x800000
        return sign | significand
    significand = round_shift_even(n, top - 23)
    if significand == 0x1000000:
        significand >>= 1
        exponent += 1
    if exponent > 127:
        return sign | INF
    assert 0x800000 <= significand <= 0xFFFFFF
    return sign | ((exponent + 127) << 23) | (significand & FRAC)


def mul_bits(a, b):
    if is_nan(a) or is_nan(b):
        return NAN
    sa, sb = a & 0x7FFFFFFF, b & 0x7FFFFFFF
    sign = (a ^ b) & SIGN
    if sa == INF or sb == INF:
        return NAN if sa == 0 or sb == 0 else sign | INF
    ma, pa = split_finite(a)
    mb, pb = split_finite(b)
    return pack_exact(sign, ma * mb, pa + pb)


def add_bits(a, b):
    if is_nan(a) or is_nan(b):
        return NAN
    aa, ab = a & 0x7FFFFFFF, b & 0x7FFFFFFF
    if aa == INF and ab == INF:
        return a if a == b else NAN
    if aa == INF:
        return a
    if ab == INF:
        return b
    ma, pa = split_finite(a)
    mb, pb = split_finite(b)
    if ma == 0 and mb == 0:
        return SIGN if (a & SIGN) and (b & SIGN) else 0
    power = min(pa, pb)
    left = ma << (pa - power)
    right = mb << (pb - power)
    value = (-left if a & SIGN else left) + (-right if b & SIGN else right)
    return pack_exact(SIGN if value < 0 else 0, abs(value), power)


def table_bits(j):
    e, sign = j & 255, (j & 256) << 23
    return sign | ((e - 23) << 23) if 24 <= e <= 254 else sign


TABLE = [table_bits(j) for j in range(512)]


def gate(u):
    a = u & 0x7FFFFFFF
    return ((a - 1) & MASK) >= 0x0BFFFFFF and a < INF


def intended_route(u):
    e, f = (u >> 23) & 255, u & FRAC
    return (e == 0 and f == 0) or 24 <= e <= 254


def product(u, table=TABLE):
    m = (u & FRAC) | 0x800000
    m_bits = pack_exact(0, m, 0)
    return mul_bits(m_bits, table[u >> 23])


def merged(u):
    return product(u) if gate(u) else canonical(u)


def old(u):
    a = u & 0x7FFFFFFF
    if u == 0:
        return 0
    return product(u) if LOWER <= a < INF else canonical(u)


def sum_bits(words, decoder):
    acc, additions = 0, 0
    for u in words:
        acc = add_bits(acc, decoder(u))
        additions += 1
    return acc, additions


def kind(u):
    a = u & 0x7FFFFFFF
    if a == 0:
        return "negative_zero" if u & SIGN else "positive_zero"
    if a < 0x800000:
        return "subnormal"
    if a < LOWER:
        return "small_normal"
    if a < INF:
        return "admitted_normal"
    return "infinity" if a == INF else "nan"


def hex32(u):
    return f"0x{u:08x}"


def main():
    # Known independent rounding/sign anchors for the integer arithmetic model.
    assert pack_exact(0, 0x800000, 0) == 0x4B000000
    assert pack_exact(0, 0xFFFFFF, 0) == 0x4B7FFFFF
    assert pack_exact(0, 0x1000001, 0) == 0x4B800000
    assert pack_exact(0, 0x1000003, 0) == 0x4B800002
    assert pack_exact(0, 1, -150) == 0
    assert pack_exact(SIGN, 1, -150) == SIGN
    assert pack_exact(0, 3, -150) == 2
    assert mul_bits(0x4B000000, SIGN) == SIGN
    assert add_bits(0, SIGN) == 0
    assert add_bits(SIGN, SIGN) == SIGN
    assert add_bits(0x7F7FFFFF, 0x7F7FFFFF) == INF

    magnitudes = [
        0, 1, 2, 0x007FFFFE, 0x007FFFFF, 0x00800000, 0x00800001,
        0x0B7FFFFF, 0x0B800000, 0x0B800001, 0x0BFFFFFE, 0x0BFFFFFF,
        0x0C000000, 0x0C000001, 0x0C7FFFFF, 0x0C800000,
        0x7F000000, 0x7F7FFFFE, 0x7F7FFFFF, 0x7F800000,
        0x7F800001, 0x7FBFFFFF, 0x7FC00000, 0x7FC00001,
        0x7FFFFFFE, 0x7FFFFFFF,
    ]
    cases = {a | s for a in magnitudes for s in (0, SIGN)}
    for j in range(512):
        fractions = [0, 1, 2, 3, 0x2AAAAA, 0x3FFFFF, 0x400000,
                     0x555555, 0x7FFFFE, 0x7FFFFF,
                     (j * 1664525 + 1013904223) & FRAC]
        cases.update((j << 23) | f for f in fractions)
    rng = random.Random(0x523257303162)
    cases.update(rng.getrandbits(32) for _ in range(131072))
    cases = sorted(cases)
    seen_j = set()
    counts = Counter()
    for u in cases:
        seen_j.add(u >> 23)
        counts[kind(u)] += 1
        assert gate(u) == intended_route(u), f"route {hex32(u)}"
        assert merged(u) == canonical(u), f"merged {hex32(u)}"
        assert old(u) == canonical(u), f"old {hex32(u)}"
    assert seen_j == set(range(512))

    boundary_rows = []
    for a in magnitudes:
        for s in (0, SIGN):
            u = a | s
            boundary_rows.append({
                "input": hex32(u), "class": kind(u), "j": u >> 23,
                "wrapped_a_minus_one": hex32(((u & 0x7FFFFFFF) - 1) & MASK),
                "admitted": gate(u), "scale_bits": hex32(TABLE[u >> 23]),
                "baseline_toBits": hex32(canonical(u)),
                "merged_toBits": hex32(merged(u)),
            })

    # Routing mutations matter even when fallback hides their output effect.
    route_mutations = []
    for name, u, bad in [
        ("unsigned_wrap_replaced_with_saturating_subtraction", 0,
         lambda x: max((x & 0x7FFFFFFF) - 1, 0) >= 0x0BFFFFFF and (x & 0x7FFFFFFF) < INF),
        ("lower_comparison_strict", LOWER,
         lambda x: (((x & 0x7FFFFFFF) - 1) & MASK) > 0x0BFFFFFF and (x & 0x7FFFFFFF) < INF),
    ]:
        assert bad(u) != gate(u)
        route_mutations.append({"mutation": name, "witness": hex32(u),
                                "expected_route": gate(u), "mutated_route": bad(u)})

    output_mutations = []
    for name, u, bad_gate in [
        ("threshold_one_unit_too_low", 0x0BFFFFFF,
         lambda x: (((x & 0x7FFFFFFF) - 1) & MASK) >= 0x0BFFFFFE and (x & 0x7FFFFFFF) < INF),
        ("finite_upper_guard_removed_infinity", INF,
         lambda x: (((x & 0x7FFFFFFF) - 1) & MASK) >= 0x0BFFFFFF),
        ("finite_upper_guard_removed_nan", 0xFFA12345,
         lambda x: (((x & 0x7FFFFFFF) - 1) & MASK) >= 0x0BFFFFFF),
        ("sign_not_removed_in_lower_test", 0x80000001,
         lambda x: ((x - 1) & MASK) >= 0x0BFFFFFF and (x & 0x7FFFFFFF) < INF),
    ]:
        got = product(u) if bad_gate(u) else canonical(u)
        assert got != canonical(u)
        output_mutations.append({"mutation": name, "witness": hex32(u),
                                 "expected": hex32(canonical(u)), "mutated": hex32(got)})

    bad_zero_table = TABLE.copy()
    bad_zero_table[256] = 0
    bad_zero_decoder = lambda u: product(u, bad_zero_table) if gate(u) else canonical(u)
    assert bad_zero_decoder(SIGN) == 0 and merged(SIGN) == SIGN
    # Strongest zero counterexample: the per-item defect is invisible in full sum.
    assert sum_bits([SIGN], merged) == sum_bits([SIGN], bad_zero_decoder) == (0, 1)
    output_mutations.append({"mutation": "negative_zero_table_entry_cleared",
                             "witness": hex32(SIGN), "expected": hex32(SIGN),
                             "mutated": hex32(0), "same_full_sum": hex32(0)})

    vectors = []
    finite_exponents = [1, 23, 24, 102, 110, 124, 125, 126, 127, 128, 129, 130, 151]
    for i in range(96):
        vector = []
        for k in range(1000):
            word = rng.getrandbits(32)
            exponent = finite_exponents[rng.randrange(len(finite_exponents))]
            value = (word & (SIGN | FRAC)) | (exponent << 23)
            if (k + i) % 5 == 0:
                value = word & SIGN
            vector.append(value)
        vector[i % 1000] = [0, SIGN, 1, SIGN | 1, LOWER, SIGN | LOWER][i % 6]
        vectors.append(vector)
    hashes = {hashlib.sha256(b"".join(u.to_bytes(4, "little") for u in v)).hexdigest()
              for v in vectors}
    assert len(hashes) == 96
    sum_digest = hashlib.sha256()
    distinct_sum_outputs = set()
    for vector in vectors:
        base, count = sum_bits(vector, canonical)
        assert (base & 0x7FFFFFFF) < INF
        assert count == len(vector)
        assert sum_bits(vector, old) == (base, count)
        assert sum_bits(vector, merged) == (base, count)
        sum_digest.update(base.to_bytes(4, "little"))
        distinct_sum_outputs.add(base)

    ordered = [0x4B800000, 0x3F800000, 0xCB800000]
    reordered = [0x4B800000, 0xCB800000, 0x3F800000]
    assert sum_bits(ordered, merged) == (0, 3)
    assert sum_bits(reordered, merged) == (0x3F800000, 3)
    nan_masking = [0x7FA12345, 0x0BFFFFFF]
    bad_lower_decoder = lambda u: product(u) if (((u & 0x7FFFFFFF) - 1) & MASK) >= 0x0BFFFFFE and (u & 0x7FFFFFFF) < INF else canonical(u)
    assert bad_lower_decoder(nan_masking[1]) != merged(nan_masking[1])
    assert sum_bits(nan_masking, merged) == sum_bits(nan_masking, bad_lower_decoder) == (NAN, 2)

    result = {
        "scope": "finite diagnostic, not Lean proof, not native-runtime validation, not a C benchmark",
        "arithmetic": "pure integer binary32 round-to-nearest ties-to-even; Lean-observable canonical NaN",
        "distinct_point_cases": len(cases),
        "covered_table_indices": len(seen_j),
        "class_counts": dict(sorted(counts.items())),
        "signed_table_zeros": sum((x & 0x7FFFFFFF) == 0 for x in TABLE),
        "normal_table_entries": sum((x & 0x7FFFFFFF) != 0 for x in TABLE),
        "pointwise_route_and_bit_mismatches": 0,
        "full_sum_vectors": len(vectors), "full_sum_vector_length": 1000,
        "full_sum_vectors_and_outputs_all_finite": True,
        "full_sum_distinct_outputs": len(distinct_sum_outputs),
        "full_sum_additions_per_arm": len(vectors) * 1000,
        "full_sum_output_sha256": sum_digest.hexdigest(),
        "routing_mutation_witnesses": route_mutations,
        "output_mutation_witnesses": output_mutations,
        "sum_can_hide_negative_zero_error": True,
        "sum_can_hide_later_error_after_nan": True,
        "ordered_sum_witness": {"original": [hex32(u) for u in ordered],
                                "sum": hex32(0), "reordered_sum": hex32(0x3F800000)},
        "boundary_rows": boundary_rows,
    }
    output = Path(__file__).with_name("diagnostic.json")
    output.write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n")
    print(json.dumps({k: v for k, v in result.items() if k != "boundary_rows"},
                     ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
