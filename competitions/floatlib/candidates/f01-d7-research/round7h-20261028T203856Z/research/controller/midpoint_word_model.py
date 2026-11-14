"""Exact integer/dyadic model of a cheap proposed RNE32 cell checker.

Only a mathematical component diagnostic. This neither executes native Lean
nor estimates production hit rate, instruction cost or end-to-end speed.
"""
from fractions import Fraction
from pathlib import Path
import hashlib
import json


def dyadic(m: int, e: int) -> Fraction:
    return Fraction(m << e) if e >= 0 else Fraction(m, 1 << -e)


def value32(u: int) -> Fraction:
    e, f = (u >> 23) & 255, u & 0x7fffff
    assert e < 255
    v = dyadic((1 << 23) + f, e - 150) if e else dyadic(f, -149)
    return -v if u >> 31 else v


def value64(u: int) -> Fraction:
    e, f = (u >> 52) & 2047, u & ((1 << 52) - 1)
    assert e < 2047
    v = dyadic((1 << 52) + f, e - 1075) if e else dyadic(f, -1074)
    return -v if u >> 63 else v


def abs_widen_bits(a: int) -> int:
    e, f = (a >> 23) & 255, a & 0x7fffff
    assert 1 <= e <= 254
    return ((e + 896) << 52) | (f << 29)


def cell_words(q: int) -> tuple[int, int]:
    """Exact strict-cell boundaries, in increasing real order.

    At the binary32 minimum normal, lower spacing does not halve; its
    binary64 encoding therefore needs twice the ordinary decrement.
    The maximum finite upper midpoint is the finite overflow threshold.
    """
    a, s = q & 0x7fffffff, (q >> 31) << 63
    w = abs_widen_bits(a)
    lower_delta = 1 << (29 if a == 0x00800000 else 28)
    lower, upper = w - lower_delta, w + (1 << 28)
    return (s | upper, s | lower) if s else (lower, upper)


def mathematical_cell(q: int) -> tuple[Fraction, Fraction]:
    a = q & 0x7fffffff
    x, prev = value32(a), value32(a - 1)
    nxt = value32(a + 1) if a < 0x7f7fffff else dyadic(1, 128)
    lo, hi = (prev + x) / 2, (x + nxt) / 2
    return (-hi, -lo) if q >> 31 else (lo, hi)


def ordered_key(u: int) -> int:
    return ((~u) & ((1 << 64) - 1)) if u >> 63 else u ^ (1 << 63)


def main() -> None:
    cases, bad, naive_min_normal = 0, [], []
    fractions = [0, 1, 2, (1 << 22) - 1, 1 << 22, (1 << 23) - 2, (1 << 23) - 1]
    for e in range(1, 255):
        for f in fractions:
            for s in (0, 1):
                q = (s << 31) | (e << 23) | f
                lo, hi = cell_words(q)
                expected = mathematical_cell(q)
                if (value64(lo), value64(hi)) != expected:
                    bad.append(hex(q))
                assert ordered_key(lo) < ordered_key(hi)
                assert expected[0] < value32(q) < expected[1]
                cases += 1
    # A real falsifier for the tempting uniform decrement. Its boundary is
    # too close to minimum normal, which is conservative but loses coverage.
    a = 0x00800000
    wrong = value64(abs_widen_bits(a) - (1 << 28))
    correct = mathematical_cell(a)[0]
    assert wrong != correct
    naive_min_normal.append({"word": hex(a), "naive_lower": str(wrong),
                             "actual_lower": str(correct),
                             "naive_minus_actual": str(wrong - correct)})
    result = {
        "scope": "Exact rational boundary model; no native execution or Lean acceptance",
        "normal_words_sampled": cases,
        "exponent_fields_exhausted": [1, 254],
        "fraction_samples_per_exponent": fractions,
        "both_signs": True,
        "boundary_mismatches": bad,
        "uniform_delta_counterexample": naive_min_normal,
        "proof": "NOT_RUN",
        "production_hit_rate": "UNKNOWN",
        "runtime_cost": "UNKNOWN",
        "whole_model_gain": "UNKNOWN",
        "script_sha256": hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
    }
    out = Path(__file__).with_name("midpoint-word-model-results.json")
    out.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k: result[k] for k in ["normal_words_sampled", "boundary_mismatches", "proof", "runtime_cost"]}))


if __name__ == "__main__":
    main()
