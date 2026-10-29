"""Deterministic exact rational checks for the separate F64 enclosure obligation.

No host float arithmetic, kernel implementation, benchmark, or Lean execution.
All cases are exposed mathematical diagnostics, not confirmation inputs.
"""
from fractions import Fraction as F
from pathlib import Path
import hashlib
import json
import time


def p2(e):
    return F(1 << e) if e >= 0 else F(1, 1 << -e)


def decode32(w):
    sign, e, f = (-1 if w >> 31 else 1), (w >> 23) & 255, w & 0x7fffff
    assert e != 255
    m, index = (f, 0) if e == 0 else ((1 << 23) + f, e - 1)
    return sign * m, index


def v32(w):
    m, i = decode32(w)
    return m * p2(i - 149)


def widen(w):
    sign, e, f = (w >> 31) << 63, (w >> 23) & 255, w & 0x7fffff
    assert e != 255
    if e:
        return sign | ((e + 896) << 52) | (f << 29)
    if not f:
        return sign
    l = f.bit_length() - 1
    return sign | ((l + 874) << 52) | ((f - (1 << l)) << (52 - l))


def v64(w):
    sign, e, f = (-1 if w >> 63 else 1), (w >> 52) & 2047, w & ((1 << 52) - 1)
    assert e != 2047
    return sign * F(f) * p2(-1074) if e == 0 else sign * F((1 << 52) + f) * p2(e - 1075)


def rn64(x):
    """Exact binary64 RNE evaluated as integer quotient and remainder."""
    if x == 0:
        return F(0)
    sign, a = (-1 if x < 0 else 1), abs(x)
    assert a.denominator & (a.denominator - 1) == 0
    top = a.numerator.bit_length() - a.denominator.bit_length()
    target = max(top - 52, -1074)
    scaled = a / p2(target)
    q, r = divmod(scaled.numerator, scaled.denominator)
    q += 2 * r > scaled.denominator or (2 * r == scaled.denominator and q % 2 == 1)
    result = sign * q * p2(target)
    assert abs(result) < p2(1024), "Outside this finite checker domain"
    return result


def fold(pairs):
    terms = [v32(a) * v32(b) for a, b in pairs]
    n = len(terms)
    assert n > 0
    L = (n - 1).bit_length()
    H = max(decode32(a)[1] + decode32(b)[1] for a, b in pairs)
    M, local = p2(H - 250), p2(H + L - 304)
    total, s = F(0), F(0)
    for j, t in enumerate(terms, 1):
        assert abs(t) < M and rn64(t) == t
        r = s + t
        assert abs(r) < j * M
        next_s = rn64(r)
        assert abs(next_s) <= j * M
        assert abs(next_s - r) <= local
        assert (r / p2(-298)).denominator == 1
        assert (next_s / p2(-298)).denominator == 1
        if next_s:
            assert abs(next_s) >= p2(-298) > p2(-1022)
        s, total = next_s, total + t
    error = abs(s - total)
    assert error <= (n - 1) * local < p2(H + 2 * L - 304)
    assert error < p2(H + 2 * L - 303)
    return {"n": n, "H": H, "L": L, "error": str(error),
            "proposed_radius_exponent": H + 2 * L - 303,
            "sharper_radius_exponent": H + 2 * L - 304}, s, total


def run():
    started = time.time()
    magnitudes = [0, 1, 2, 0x003fffff, 0x007fffff, 0x00800000, 0x00800001,
                  0x3f000000, 0x3f800000, 0x3f800001, 0x3fffffff, 0x7f7fffff]
    words = magnitudes + [w | 0x80000000 for w in magnitudes]
    for w in words:
        expanded = widen(w)
        assert v64(expanded) == v32(w)
        if w & 0x7fffffff:
            assert 1 <= (expanded >> 52) & 2047 <= 2046
        else:
            assert expanded == ((w >> 31) << 63)
    for a in words:
        for b in words:
            product = v64(widen(a)) * v64(widen(b))
            assert product == v32(a) * v32(b)
            assert rn64(product) == product

    cases = []
    for n in [1, 2, 3, 4, 7, 8, 31, 32, 33, 63, 64]:
        cases.append([(0x7f7fffff, 0x7f7fffff)] * n)
        cases.append([(1, 1)] * n)
        cases.append([((0xff7fffff if i % 2 else 0x7f7fffff), 0x7f7fffff)
                      for i in range(n)])
    cases += [
        [(0x3f800000, 0x3f800000), (0x32800000, 0x32000000), (0xbf800000, 0x3f800000)],
        [(0x7f7fffff, 0x7f7fffff), (0x72000000, 0x72000000)],
        [(0x80000000, 0x3f800000)],
        [(0x3fffffff, 0x3ffffffd)] * 33,
        [(0x3f800000, 0x3f800000), (0x32000000, 0x32000000)],
    ]
    checked = [fold(c)[0] for c in cases]

    # Boundary counts are checked as exact integers, not by executing gigantic folds.
    exact_boundary_count_checks = 0
    for H in [0, 198, 252, 506]:
        for j in [0, 1, (1 << 30) - 1, 1 << 30, (1 << 51) - 1, 1 << 51]:
            x = j * p2(H - 250)
            assert rn64(x) == x
            exact_boundary_count_checks += 1

    # The jM monotone induction must not be generalized to a non-power-of-two M.
    pair = (0x3fffffff, 0x3ffffffd)
    Msep = v32(pair[0]) * v32(pair[1])
    _, s, total = fold([pair] * 33)
    assert total == 33 * Msep and s - total == p2(-46)

    # Ignoring an exact initial bias in H/count invalidates the dot error radius.
    bias, t = F(1), p2(-54)
    error_ignored_bias = abs(rn64(bias + t) - (bias + t))
    bad_radius = p2(198 - 303)
    assert error_ignored_bias == p2(-54) > bad_radius
    corrected, _, _ = fold([(0x3f800000, 0x3f800000), (0x32000000, 0x32000000)])

    # Native-rounded endpoints need not enclose the exact mathematical endpoints.
    center, radius = 1 - 3 * p2(-53), p2(-50)
    exact_upper, rounded_upper = center + radius, rn64(center + radius)
    assert rounded_upper < exact_upper and exact_upper - rounded_upper == p2(-53)

    return {"status": "PASS_DETERMINISTIC_EXACT_MODEL_NOT_NATIVE_OR_LEAN",
            "raw_expansion_cases": len(words), "exact_product_cases": len(words) ** 2,
            "fold_cases": len(cases), "maximum_executed_fold_length": 64,
            "symbolic_boundary_count_checks": exact_boundary_count_checks,
            "fold_results": checked,
            "non_power_two_prefix_counterexample": {
                "input_pair": [hex(x) for x in pair], "n": 33,
                "s_minus_nM": str(s - total),
                "scope": "Refutes |s_j|<=j*M for arbitrary representable non-power M; not the recurrence enclosure"},
            "ignored_bias_counterexample": {
                "bias_word": "0x3f800000", "product_pair": ["0x32000000", "0x32000000"],
                "bad_H": 198, "bad_n": 1, "error": str(error_ignored_bias),
                "bad_radius": str(bad_radius), "corrected_H": corrected["H"], "corrected_n": corrected["n"]},
            "inward_rounded_endpoint": {"center": str(center), "B": str(radius),
                "exact_upper": str(exact_upper), "rounded_upper": str(rounded_upper)},
            "scope": "Fixed exposed mathematics cases only; no performance or acceptance-rate inference",
            "runtime_seconds": time.time() - started,
            "source_sha256": hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}


if __name__ == "__main__":
    result = run()
    Path(__file__).with_name("f64-exact-check-result.json").write_text(
        json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k: v for k, v in result.items() if k != "fold_results"}, indent=2))
