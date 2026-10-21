"""Finite integer-model diagnostic for the nearest-even threshold transformation."""

import hashlib
import json
import random
from datetime import datetime, timezone
from pathlib import Path

MASK = (1 << 64) - 1


def old_decision(q, r, half):
    if r < half:
        return q
    if r > half:
        return (q + 1) & MASK
    return q if q & 1 == 0 else (q + 1) & MASK


def new_decision(q, r, half):
    return (q + 1) & MASK if r > half - (q & 1) else q


def rse_inputs(value, shift):
    amount = shift % 64
    q = value >> amount
    r = value & ((1 << amount) - 1)
    half = 1 << (((shift - 1) & MASK) % 64)
    return q, r, half


def exact_round(value, shift):
    """Independent unbounded-integer nearest-even oracle for shifts 1..63."""
    q, r = divmod(value, 1 << shift)
    denominator = 1 << shift
    return q + int(2 * r > denominator or (2 * r == denominator and q % 2 == 1))


def main():
    root = Path(__file__).resolve().parent
    counts = {"small_decisions": 0, "tie_and_binade_edges": 0,
              "uniform_word_helper": 0, "independent_rounding_oracle": 0}
    for q in range(8):
        for r in range(256):
            for half in range(1, 256):
                assert old_decision(q, r, half) == new_decision(q, r, half)
                counts["small_decisions"] += 1
    for shift in range(64):
        half = 1 << (((shift - 1) & MASK) % 64)
        for q in (0, 1, 2, 3, (1 << 23) - 1, 1 << 23, MASK - 1, MASK):
            for r in (0, half - 1, half, min(MASK, half + 1), MASK):
                assert old_decision(q, r, half) == new_decision(q, r, half)
                counts["tie_and_binade_edges"] += 1
    rng = random.Random(0xF1032026)
    for _ in range(200_000):
        value, shift = rng.getrandbits(64), rng.getrandbits(64)
        args = rse_inputs(value, shift)
        assert old_decision(*args) == new_decision(*args)
        counts["uniform_word_helper"] += 1
        small_shift = rng.randrange(1, 64)
        args = rse_inputs(value, small_shift)
        expected = exact_round(value, small_shift)
        assert old_decision(*args) == new_decision(*args) == expected
        counts["independent_rounding_oracle"] += 1
    result = {
        "status": "PASS_FINITE_PYTHON_MODEL",
        "executed_at_utc": datetime.now(timezone.utc).isoformat(),
        "kernel_sha256": hashlib.sha256((root / "Kernel.lean").read_bytes()).hexdigest(),
        "probe_sha256": hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        "seed": "0xF1032026", "groups": counts, "mismatches": 0,
        "scope": "Finite translated helper; official Lean/full gate/timing NOT_RUN",
    }
    (root / "probe-result.json").write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(result))


if __name__ == "__main__":
    main()
