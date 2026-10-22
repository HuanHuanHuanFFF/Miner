"""Own finite-binary32 examples; stdlib only, no project imports.

Every finite value is represented exactly as an integer times 2**-149.
This is a finite arithmetic oracle, not a complete FloatLib NaN oracle and
not a Lean proof or performance benchmark.
"""
from __future__ import annotations

import json
import random
import struct


def bits(x: float) -> int:
    return struct.unpack(">I", struct.pack(">f", x))[0]


def units(w: int) -> int:
    e = (w >> 23) & 255
    f = w & 0x7FFFFF
    assert e < 255
    v = f if e == 0 else ((1 << 23) | f) << (e - 1)
    return -v if w >> 31 else v


def round_integer(n: int, denominator: int) -> int:
    q, r = divmod(n, denominator)
    return q + (2 * r > denominator or (2 * r == denominator and q & 1))


def pack_units(z: int) -> int:
    if z == 0:
        return 0
    sign = 0x80000000 if z < 0 else 0
    z = abs(z)
    if z < 1 << 23:
        return sign | z
    shift = max(0, z.bit_length() - 24)
    q = round_integer(z, 1 << shift)
    if q == 1 << 24:
        q >>= 1
        shift += 1
    e = shift + 1
    if e >= 255:
        return sign | 0x7F800000
    return sign | (e << 23) | (q - (1 << 23))


def add(a: int, b: int) -> int:
    assert (b & 0x7F800000) != 0x7F800000
    if (a & 0x7FFFFFFF) == 0x7F800000:
        return a
    z = units(a) + units(b)
    if z == 0 and a == b == 0x80000000:
        return 0x80000000
    return pack_units(z)


def fold(xs: list[int], start: int = 0) -> int:
    s = start
    for x in xs:
        s = add(s, x)
    return s


def uniform_grid(start: int, xs: list[int]) -> tuple[int, list[int]]:
    e = (start >> 23) & 255
    assert 1 <= e <= 253 and start >> 31 == 0
    h = 1 << (e - 1)
    k = units(start) // h
    trace = [k]
    for x in xs:
        k = round_integer(k * h + units(x), h)
        trace.append(k)
    return pack_units(k * h), trace


def independent_increment(start: int, xs: list[int]) -> int:
    e = (start >> 23) & 255
    h = 1 << (e - 1)
    k = units(start) // h
    return pack_units((k + sum(round_integer(units(x), h) for x in xs)) * h)


def hx(x: int) -> str:
    return f"0x{x:08x}"


def main() -> None:
    a = bits(1 + 3 * 2**-23)
    s = bits(8 + 2**-20)
    xs = [s, a, a]
    rows = {
        "same_multiset_different_order": {
            "input": list(map(hx, xs)),
            "ordered": hx(fold(xs)),
            "permuted_input": list(map(hx, [a, a, s])),
            "permuted_ordered": hx(fold([a, a, s])),
            "round_exact_total": hx(pack_units(sum(map(units, xs)))),
        }
    }
    tie_x = bits(1 + 2**-21)
    even_start, odd_start = bits(8), bits(8 + 2**-20)
    rows["tie_parity"] = {
        "x": hx(tie_x),
        "even_start": hx(even_start),
        "even_result": hx(fold([tie_x], even_start)),
        "odd_start": hx(odd_start),
        "odd_result": hx(fold([tie_x], odd_start)),
        "odd_wrong_independent_increment": hx(independent_increment(odd_start, [tie_x])),
    }
    boundary_cases = [
        ("lower_boundary_single", bits(1), [bits(-3 * 2**-26)]),
        ("lower_exit_then_reenter", bits(1 + 2**-23), [bits(-11 * 2**-26), bits(3 * 2**-23)]),
        ("upper_exit_then_reenter", bits(2 - 2**-23), [bits(2**-22), bits(-2**-21)]),
    ]
    for name, start, tail in boundary_cases:
        candidate, trace = uniform_grid(start, tail)
        rows[name] = {
            "start": hx(start),
            "tail": list(map(hx, tail)),
            "ordered": hx(fold(tail, start)),
            "uniform_candidate": hx(candidate),
            "uniform_k_trace": trace,
        }
    rows["gradual_subnormal"] = {
        "input": ["0x00800000", "0x807fffff"],
        "result": hx(fold([0x00800000, 0x807FFFFF])),
    }
    rows["overflow_then_cancellation"] = {
        "input": ["0x7f7fffff", "0x7f7fffff", "0xff7fffff"],
        "ordered": hx(fold([0x7F7FFFFF, 0x7F7FFFFF, 0xFF7FFFFF])),
        "round_exact_total": hx(pack_units(units(0x7F7FFFFF))),
    }
    rows["starting_positive_zero"] = {
        "input": ["0x80000000", "0x80000000"],
        "ordered": hx(fold([0x80000000, 0x80000000])),
    }

    # An independent randomized check of the proposed monotone no-tie
    # certificate; acceptance requires runtime-checkable input properties.
    rng = random.Random(20261021)
    accepted = 0
    rejected = 0
    midpoint_count = 0
    for _ in range(5000):
        ea = rng.randrange(132, 141)
        start = (ea << 23) | rng.getrandbits(23)
        h = 1 << (ea - 1)
        k = (1 << 23) | (start & 0x7FFFFF)
        tail = []
        increments = []
        for _ in range(32):
            if rng.randrange(2) == 0:
                x = 0
                delta = 0
            else:
                ex = rng.randrange(124, 131)
                m = (1 << 23) | rng.getrandbits(23) | 1
                x = (ex << 23) | (m & 0x7FFFFF)
                d = ea - ex
                assert d >= 2
                midpoint_count += (m % (1 << d)) == (1 << (d - 1))
                delta = (m + (1 << (d - 1))) >> d
                assert delta == round_integer(units(x), h)
            tail.append(x)
            increments.append(delta)
        candidate_k = k + sum(increments)
        if candidate_k <= 1 << 24:
            accepted += 1
            expected = fold(tail, start)
            candidate = pack_units(candidate_k * h)
            assert candidate == expected, (hx(start), list(map(hx, tail)))
        else:
            rejected += 1
    rows["monotone_odd_certificate_self_check"] = {
        "blocks": 5000,
        "length": 32,
        "accepted": accepted,
        "rejected_binade_bound": rejected,
        "midpoints": midpoint_count,
        "mismatches": 0,
        "note": "synthetic starts, not the official generator, no performance claim",
    }
    print(json.dumps(rows, indent=2))


if __name__ == "__main__":
    main()
