#!/usr/bin/env python3
"""Small exact experiment for a PREDETERMINED sequence of dyadic grids.

This is not an implementation of adaptive binary32 binade discovery.
"""
import json
import random
import secrets
from fractions import Fraction
from pathlib import Path

from verify_transition import rn_integer


def evaluate(k, schedule):
    value = Fraction(k)
    for q, x in schedule:
        value = q * rn_integer((value + x) / q)
    return value


def main():
    seed = secrets.randbits(128)
    rng = random.Random(seed)
    evaluations = 0
    for _ in range(2000):
        schedule = [(1 << rng.randrange(6), Fraction(rng.randrange(-100, 101), 4))
                    for _ in range(rng.randrange(1, 17))]
        Q = max(q for q, _ in schedule)
        H = 2 * Q
        values = [evaluate(k, schedule) for k in range(H + 1)]
        base = values[0]
        assert values[-1] == base + H
        assert all(v >= u for u, v in zip(values, values[1:]))
        assert all((v - base) % Q == 0 for v in values)
        assert len(set(values[:-1])) <= 3
        t1 = next(k for k, v in enumerate(values) if v >= base + Q)
        t2 = next(k for k, v in enumerate(values) if v >= base + 2 * Q)
        for k in range(-H, 2 * H + 1):
            quotient, residue = divmod(k, H)
            compact = base + H * quotient + Q * ((residue >= t1) + (residue >= t2))
            assert compact == evaluate(k, schedule)
            evaluations += 1
    result = {"fresh_random_seed_hex": f"{seed:032x}",
              "fixed_grid_schedules": 2000,
              "exact_summary_evaluations": evaluations,
              "all_assertions_passed": True,
              "limitation": "q_j is specified in advance; no adaptive binary32 boundary discovery is implemented"}
    path = Path(__file__).resolve().parent / "fixed_schedule_results.json"
    path.write_text(json.dumps(result, indent=2) + "\n")
    print(json.dumps(result, indent=2))


if __name__ == "__main__":
    main()
