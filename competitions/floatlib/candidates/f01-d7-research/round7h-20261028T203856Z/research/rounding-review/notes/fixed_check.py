"""Bounded exact mathematical falsifier. Not a race kernel or a Lean proof.

Frozen scope: integer/Fraction boundary cases plus seed 20261028, with no timing
interpretation and no new benchmark/confirmation input. Run from this directory.
"""
from fractions import Fraction as F
from functools import lru_cache
from pathlib import Path
from random import Random
import hashlib
import json
import platform
import time

SIGN = 1 << 31
MAX = 0x7f7fffff
INF = 0x7f800000
MASK64 = (1 << 64) - 1


def pow2(k):
    return F(1 << k) if k >= 0 else F(1, 1 << -k)


@lru_cache(maxsize=16384)
def positive_value(w):
    assert 0 <= w <= MAX
    z, f = w >> 23, w & ((1 << 23) - 1)
    return F(f) * pow2(-149) if z == 0 else F((1 << 23) + f) * pow2(z - 150)


def value(w):
    v = positive_value(w & ~SIGN)
    return -v if w & SIGN else v


OVERFLOW = positive_value(MAX) + pow2(103)


def rne(x, negative_zero=False):
    """Independent oracle: search adjacent finite words and compare distances."""
    if x == 0:
        return SIGN if negative_zero else 0
    s = SIGN if x < 0 else 0
    x = abs(x)
    if x >= OVERFLOW:
        return s | INF
    if x > positive_value(MAX):
        return s | MAX
    lo, hi = 0, MAX
    while lo < hi:
        mid = (lo + hi + 1) // 2
        if positive_value(mid) <= x:
            lo = mid
        else:
            hi = mid - 1
    if x == positive_value(lo) or lo == MAX:
        return s | lo
    up = lo + 1
    dl, du = x - positive_value(lo), positive_value(up) - x
    chosen = lo if dl < du else up if du < dl else lo if lo % 2 == 0 else up
    return s | chosen


def cell_ab(A, B, Z, M, wrong_power_lower=False, ignore_parity=False):
    assert A > 0 and B > 0 and 2 <= Z <= 254 and (1 << 23) <= M < (1 << 24)
    T = 2 * B * M
    even = M % 2 == 0 or ignore_parity
    upper = A < T + B or (A == T + B and even)
    if M == 1 << 23 and not wrong_power_lower:
        lower = 2 * A > 2 * T - B or (2 * A == 2 * T - B and even)
    else:
        lower = A > T - B or (A == T - B and even)
    return lower and upper


def cell_exact(x, w):
    Z, frac = w >> 23, w & ((1 << 23) - 1)
    if not (x > 0 and 2 <= Z <= 254):
        return False
    y = x * pow2(151 - Z)
    return cell_ab(y.numerator, y.denominator, Z, (1 << 23) + frac)


def rms_checked(P, D, w, wrap=False, wrong_power_lower=False, ignore_parity=False):
    Z, frac = w >> 23, w & ((1 << 23) - 1)
    if not (0 < P < 1 << 48 and 1 << 23 <= D < 1 << 24 and 103 <= Z <= 152):
        return False
    M, k = (1 << 23) + frac, 151 - Z
    if k >= 0:
        A, B = P << k, D
        if A > MASK64 and not wrap:
            return False
        A &= MASK64
    else:
        A, B = P, D << -k
    T = 2 * B * M
    assert T + B < 1 << 50
    even = M % 2 == 0 or ignore_parity
    upper = A < T + B or (A == T + B and even)
    if not upper:
        return False
    assert 2 * A < 1 << 51
    return cell_ab(A, B, Z, M, wrong_power_lower, ignore_parity)


def relu(w):
    is_nan = (w & INF) == INF and (w & 0x7fffff) != 0
    return 0 if w & SIGN and not is_nan else w


def run():
    started = time.time()
    counts = {"rms_arbitrary_proposals": 0, "exact_cell_boundary_checks": 0,
              "interval_dots": 0, "interval_accepts": 0, "relu_cases": 0,
              "normal_scaling_checks": 0}
    witness = {}

    P, D, w = 131073, 8388608, 0x34000000
    assert rms_checked(P, D, w, wrap=True)
    assert not rms_checked(P, D, w)
    assert rne(F(P, D)) == 0x3c800040
    witness["unchecked_shift"] = {"P": P, "D": D, "proposed": hex(w),
        "correct": hex(rne(F(P, D))), "k": 47, "unbounded_A": str(P << 47)}

    P, D, w = 33554430, 8388608, 0x40800000
    assert rms_checked(P, D, w, wrong_power_lower=True)
    assert not rms_checked(P, D, w)
    assert rne(F(P, D)) == 0x407fffff
    witness["power_two_lower"] = {"P": P, "D": D, "proposed": hex(w),
                                      "correct": hex(rne(F(P, D)))}

    P, D, w = 25165822, 16777215, 0x3fc00000
    x = F(P, D)
    assert rne(x) == w and rms_checked(P, D, w)
    assert rne(x * pow2(-149)) == 1
    assert rne(value(w) * pow2(-149)) == 2
    witness["subnormal_double_round"] = {"P": P, "D": D, "source": hex(w),
        "exponent": -149, "correct": "0x1", "scaled_rounded_proposal": "0x2"}

    for P, expected in [(16777217, 0x40000000), (16777219, 0x40000002)]:
        assert not rms_checked(P, 8388608, 0x40000001)
        assert rms_checked(P, 8388608, 0x40000001, ignore_parity=True)
        assert rne(F(P, 8388608)) == expected
    witness["odd_ties"] = {"D": 8388608, "candidate": "0x40000001",
        "lower_P": 16777217, "lower_correct": "0x40000000",
        "upper_P": 16777219, "upper_correct": "0x40000002"}

    assert value(0) == value(SIGN) == 0 and SIGN != 0
    for x, expected in [(pow2(-150), 0), (-pow2(-150), SIGN),
                        (OVERFLOW, INF), (-OVERFLOW, SIGN | INF)]:
        assert rne(x) == expected
    witness["signed_zero_real_collision"] = ["0x0", "0x80000000"]
    witness["overflow_threshold"] = str(OVERFLOW)

    # Exact cell boundaries, including exponent carry and finite/Inf threshold.
    words = [(z << 23) + f for z in (2, 52, 103, 126, 127, 128, 152, 253, 254)
             for f in (0, 1, 2, (1 << 23) - 2, (1 << 23) - 1)]
    for w in words:
        v = value(w)
        lower = (value(w - 1) + v) / 2
        upper = OVERFLOW if w == MAX else (value(w + 1) + v) / 2
        eps = min(v - lower, upper - v) / 8
        for x in (lower - eps, lower, lower + eps, v, upper - eps, upper, upper + eps):
            assert cell_exact(x, w) == (rne(x) == w)
            assert rne(-x) == (rne(x) | SIGN)
            counts["exact_cell_boundary_checks"] += 1

    rng = Random(20261028)
    for _ in range(600):
        P = rng.randrange(1, 1 << rng.randrange(1, 49))
        D = rng.randrange(1 << 23, 1 << 24)
        exact = rne(F(P, D))
        proposals = [exact, exact - 1, exact + 1,
                     (rng.randrange(103, 153) << 23) | rng.randrange(1 << 23)]
        assert rms_checked(P, D, exact)
        for w in proposals:
            if rms_checked(P, D, w):
                assert w == exact
            counts["rms_arbitrary_proposals"] += 1

    for _ in range(320):
        n = rng.randrange(1, 66)
        L = (n - 1).bit_length()
        H = rng.randrange(0, 507)
        B = H + 48 + L - 62
        T, S = 0, F(0)
        for _ in range(n):
            m, I, sign = rng.randrange(1 << 48), H - rng.randrange(0, 600), rng.choice((-1, 1))
            mag = F(m) * pow2(I - B)
            q = sign * (mag.numerator // mag.denominator)
            assert abs(q) < pow2(62 - L)
            assert abs(F(sign * m) * pow2(I) - F(q) * pow2(B)) < pow2(B)
            T += q
            assert abs(T) < 1 << 62
            S += F(sign * m) * pow2(I - 298)
        lo, hi = F(T - n) * pow2(B - 298), F(T + n) * pow2(B - 298)
        assert -(1 << 63) < T - n <= T + n < 1 << 63
        assert lo < S < hi
        wl, ws, wh = rne(lo), rne(S), rne(hi)
        if H + L <= 377:
            assert max(abs(lo), abs(hi), abs(S)) < 3 * pow2(126) < positive_value(MAX)
            assert (wl & INF) != INF and (ws & INF) != INF and (wh & INF) != INF
        if wl == wh and (wl & ~SIGN) != 0:
            assert ws == wl
            counts["interval_accepts"] += 1
        if T + n <= 0:
            assert relu(ws) == 0
            counts["relu_cases"] += 1
        counts["interval_dots"] += 1

    # Canonical zero, negative zero, underflow, negative finite and negative overflow.
    for x in (F(0), -pow2(-1000), -pow2(-150), -pow2(-149), F(-1), -OVERFLOW, -pow2(300)):
        for zero_sign in (False, True):
            assert relu(rne(x, negative_zero=zero_sign)) == 0
            counts["relu_cases"] += 1
    assert relu(0xffc00001) == 0xffc00001
    assert relu(rne(F(-1) + 2)) != relu(rne(F(-1))) + 0  # later bias is not omitted

    # Cell scaling into every sampled normal target, including min-normal power of two.
    for sourceZ in (103, 127, 152):
        for frac in (0, 1, (1 << 23) - 1):
            source = (sourceZ << 23) | frac
            low = (value(source - 1) + value(source)) / 2
            high = (value(source + 1) + value(source)) / 2
            for x in (low, (low + value(source)) / 2, value(source),
                      (high + value(source)) / 2, high):
                if rne(x) != source:
                    continue
                for targetZ in (1, 2, 52, 127, 253, 254):
                    target = (targetZ << 23) | frac
                    assert rne(x * pow2(targetZ - sourceZ)) == target
                    counts["normal_scaling_checks"] += 1

    return {"status": "PASS_BOUNDED_EXACT_MODEL_NOT_LEAN", "seed": 20261028,
            "scope": "fixed boundary corpus and 600 rational/320 dyadic random cases; exploration only",
            "counts": counts, "counterexamples_to_weakened_variants": witness,
            "runtime_seconds": time.time() - started, "python": platform.python_version(),
            "source_sha256": hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}


if __name__ == "__main__":
    result = run()
    path = Path(__file__).with_name("fixed-check-result.json")
    path.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(result, indent=2))
