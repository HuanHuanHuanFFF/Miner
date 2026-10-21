"""Finite helper diagnostic. This does not compile Lean or replace the full gate."""

import hashlib
import json
import random
from datetime import datetime, timezone
from pathlib import Path


def fallback_log2(x):
    r = 0
    for k in (32, 16, 8, 4, 2, 1):
        if x >> k:
            x >>= k
            r += k
    return r


def candidate_log2(x):
    if x >> 47 == 1:
        return 47
    if x >> 46 == 1:
        return 46
    return fallback_log2(x)


def main():
    root = Path(__file__).resolve().parent
    rng = random.Random(0xF1022026)
    boundaries = {0, 1, (1 << 64) - 1}
    for k in range(65):
        for delta in (-2, -1, 0, 1, 2):
            x = (1 << k) + delta
            if 0 <= x < 1 << 64:
                boundaries.add(x)
    groups = {
        "all_binade_boundaries": sorted(boundaries),
        "uniform_uint64": [rng.getrandbits(64) for _ in range(200_000)],
        "normal_mantissa_products": [
            rng.randrange(1 << 23, 1 << 24) * rng.randrange(1 << 23, 1 << 24)
            for _ in range(200_000)
        ],
        "subnormal_or_mixed_mantissa_products": [
            rng.randrange(1 << 23) * rng.randrange(1 << 24)
            for _ in range(200_000)
        ],
    }
    results = {}
    for name, values in groups.items():
        hits = {"47": 0, "46": 0, "fallback": 0}
        for x in values:
            expected = max(0, x.bit_length() - 1)
            actual = candidate_log2(x)
            original = fallback_log2(x)
            if expected != actual or expected != original:
                raise AssertionError((name, x, expected, original, actual))
            branch = "47" if x >> 47 == 1 else "46" if x >> 46 == 1 else "fallback"
            hits[branch] += 1
        results[name] = {"samples": len(values), "mismatches": 0, "branch_hits": hits}
    report = {
        "status": "PASS_FINITE_PYTHON_MODEL",
        "executed_at_utc": datetime.now(timezone.utc).isoformat(),
        "kernel_sha256": hashlib.sha256((root / "Kernel.lean").read_bytes()).hexdigest(),
        "probe_sha256": hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        "seed": "0xF1022026",
        "oracle": "Python integer bit_length, with log2(0)=0",
        "groups": results,
        "scope": "Finite translated helper diagnostic only; Lean/full gate/timing NOT_RUN",
    }
    (root / "probe-result.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(report))


if __name__ == "__main__":
    main()
