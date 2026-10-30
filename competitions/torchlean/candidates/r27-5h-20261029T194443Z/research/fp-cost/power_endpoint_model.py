"""Exact-integer model of the proposed fixed power-envelope FP proof.

This is a finite model, not execution or verification of Lean Float.add.
Coefficients use the exact common product unit 2^-298.
"""
from pathlib import Path
from fractions import Fraction
import datetime
import hashlib
import json
import random


def round64(z):
    sign = -1 if z < 0 else 1
    z = abs(z)
    shift = max(0, z.bit_length() - 53)
    if not shift:
        return sign * z
    q, rem = divmod(z, 1 << shift)
    half = 1 << (shift - 1)
    q += rem > half or (rem == half and q & 1)
    return sign * (q << shift)


def decode32(word):
    e, f = (word >> 23) & 255, word & 0x7fffff
    assert e != 255
    z = f if e == 0 else ((1 << 23) | f) << (e - 1)
    return -z if word >> 31 else z


def index32(word):
    return max(0, ((word >> 23) & 255) - 1)


def power(k):
    return Fraction(1 << k) if k >= 0 else Fraction(1, 1 << -k)


def check(xs, ys):
    n = len(xs)
    assert 1 <= n == len(ys) <= 2**30
    h = max(map(index32, xs)) + max(map(index32, ys))
    ell = (n - 1).bit_length()
    product_cap = 1 << (h + 48)  # 2^(H-250) / 2^-298
    delta = power(h + ell - 5)
    radius = power(h + 2 * ell - 5)
    acc = exact = 0
    for i, (x, y) in enumerate(zip(xs, ys), 1):
        p = decode32(x) * decode32(y)
        assert abs(p) < product_cap
        assert round64(p) == p
        z = acc + p
        rounded = round64(z)
        assert abs(z) <= i * product_cap
        assert abs(rounded) <= i * product_cap
        assert abs(rounded - z) <= delta
        acc, exact = rounded, exact + p
        assert abs(acc - exact) <= i * delta
    assert abs(acc - exact) <= radius
    assert 720 <= h + 2 * ell + 720 <= 1286
    return n


def main():
    rng = random.Random(2026102923)
    edge = [0, 0x80000000, 1, 0x807fffff, 0x00800000, 0x3f800000,
            0xbf800000, 0x7f7fffff, 0xff7fffff, 0x3f7fffff, 0x00800001]
    cases = []
    for x in edge:
        for y in edge:
            cases.append(([x], [y]))
            cases.append(([x, x, x, x], [y, y ^ 0x80000000, y, y]))
    for n in [2, 3, 4, 7, 8, 16, 31, 64, 127]:
        for _ in range(120):
            def word():
                if rng.randrange(4) == 0:
                    return rng.choice(edge)
                return rng.getrandbits(1) << 31 | rng.randrange(255) << 23 | rng.getrandbits(23)
            cases.append(([word() for _ in range(n)], [word() for _ in range(n)]))
    products = 0
    for xs, ys in cases:
        try:
            products += check(xs, ys)
        except AssertionError:
            Path(__file__).with_name("power-endpoint-counterexample.json").write_text(
                json.dumps({"xs": xs, "ys": ys}, indent=2) + "\n", encoding="utf-8")
            raise
    # Endpoints for all H and critical counts are representable in binary64.
    endpoint_checks = 0
    for h in range(507):
        for i in [0, 1, 2, 3, 2**29-1, 2**29, 2**30-1, 2**30]:
            z = i << (h + 48)
            assert round64(z) == z
            assert not z or z.bit_length() - 1 - 298 <= 286
            endpoint_checks += 1
    result = {"at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
              "source_sha256": hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
              "state": "PASS_FINITE_EXACT_INTEGER_MODEL_ONLY",
              "cases": len(cases), "modeled_products": products,
              "endpoint_checks": endpoint_checks,
              "checked": ["exact binary32 products fit RN64", "representable integer-power endpoint",
                          "prefix enclosure", "uniform absolute per-add budget", "final code radius"],
              "unclosed": ["Actual native Float.add to FloatLib RN64 connection", "Universal bounded-rounding lemma",
                           "prepareFn/getter all-input correctness", "full12 candidate proof", "native performance"],
              "limits": "Own finite fixtures only; no frozen confirmation inputs, no timing/probability claims"}
    Path(__file__).with_name("power-endpoint-model-result.json").write_text(
        json.dumps(result, indent=2) + "\n", encoding="utf-8", newline="\n")
    print(json.dumps(result))


if __name__ == "__main__":
    main()
