"""Bounded exhaustive check of the 256x256 exponent-only guard model.

This is neither Lean execution nor a benchmark/Float32 equivalence proof.
The guard depends on raw exponent fields only; fractions/signs are not sampled.
"""
import hashlib
import json
import time
from pathlib import Path

started = time.perf_counter()
limit_seconds = 2.0
limit_cases = 65536
mask = (1 << 32) - 1
trace = hashlib.sha256()
counts = {"accepted": 0, "non_normal": 0, "normal_sum_low": 0, "normal_sum_high": 0}
by_sum = {}
cases = 0
for ex in range(256):
    if time.perf_counter() - started > limit_seconds:
        raise RuntimeError("Time bound exceeded")
    for ey in range(256):
        cases += 1
        if cases > limit_cases:
            raise RuntimeError("Case bound exceeded")
        actual_model = ((ex - 1) & mask) <= 253 and ((ey - 1) & mask) <= 253 and ((ex + ey - 128) & mask) <= 252
        intended = 1 <= ex <= 254 and 1 <= ey <= 254 and 128 <= ex + ey <= 380
        if actual_model != intended:
            raise AssertionError((ex, ey, actual_model, intended))
        trace.update(bytes((ex, ey, int(actual_model))))
        if actual_model:
            counts["accepted"] += 1
            by_sum[ex + ey] = by_sum.get(ex + ey, 0) + 1
        elif not (1 <= ex <= 254 and 1 <= ey <= 254):
            counts["non_normal"] += 1
        elif ex + ey < 128:
            counts["normal_sum_low"] += 1
        else:
            counts["normal_sum_high"] += 1
assert cases == 65536
assert counts == {"accepted": 48259, "non_normal": 1020, "normal_sum_low": 8001, "normal_sum_high": 8256}
assert by_sum[128] == 127 and by_sum[380] == 129
result = {
    "purpose": "Check wrapped UInt32 exponent-only guard model against its exact intended normal domain; quantify exponent-pair domain, not workload frequency or speed.",
    "scope": "All 65536 pairs of raw exponent fields 0..255; no Float32 runtime arithmetic executed.",
    "limits": {"seconds": limit_seconds, "cases": limit_cases},
    "elapsed_seconds": time.perf_counter() - started,
    "cases": cases,
    "counts": counts,
    "accepted_edge_sum_counts": {"128": by_sum[128], "380": by_sum[380]},
    "uniform_raw_exponent_pair_fraction": counts["accepted"] / 65536,
    "uniform_normal_exponent_pair_fraction": counts["accepted"] / (254 * 254),
    "trace_sha256": trace.hexdigest(),
    "script_sha256": hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
    "proof_status": "FINITE_GUARD_MODEL_ONLY; pinned Lean eligible_conditions and actual generated caller still require compilation/inspection.",
    "performance_status": "UNKNOWN; uniform exponent-pair counts do not describe public workload or saved time."
}
out = Path(__file__).with_suffix(".json")
out.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
print(json.dumps(result))
