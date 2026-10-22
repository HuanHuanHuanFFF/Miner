"""Count scalar cold paths actually reachable during exposed tensor fallbacks.

Finite source model, checksum anchored to prior Lean outputs; no new timing/proof.
Never reads a future confirmation plan or invokes the original runner.
"""
from collections import Counter
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
from pathlib import Path
import time

HERE = Path(__file__).resolve().parent
spec = importlib.util.spec_from_file_location("scalar_discovery", HERE / "scalar-opportunity.py")
S = importlib.util.module_from_spec(spec)
spec.loader.exec_module(S)
BASE = S.BASE
MAX_SECONDS = 600


def counters():
    return Counter({name: 0 for name in ("ordered_steps", "scalar_add_calls", "scalar_mul_calls",
        "add_nonfinite_cold_calls", "mul_nonfinite_cold_calls", "add_raw_nan_selected",
        "mul_raw_nan_selected", "add_no_nan_exceptional_misses", "mul_no_nan_exceptional_misses")})


def main():
    started = time.monotonic()
    dependencies = [S.R / "public-nonfinite-opportunity.py", S.R / "nonfinite-oracle.py",
                    S.R / "upstream/BenchSuite.lean"]
    cached = {p: p.read_bytes() for p in dependencies}
    generator = S.load_functions(cached[dependencies[0]], dependencies[0], ("word", "ctz", "element"), ("M64", "M32"))
    oracle = S.load_functions(cached[dependencies[1]], dependencies[1],
        ("exp", "frac", "nan", "snan", "inf", "zero", "choose", "unpack", "rounded", "add", "mul"))
    plan_path = BASE / "public-drawn-plan.json"
    plan_bytes = plan_path.read_bytes()
    assert S.sha(plan_bytes) == "9cc5d7368749c369172b019d66bc4cd8455ae4323d0b9a175bd031f936e78622"
    plan = json.loads(plan_bytes)
    logs = {"control": json.loads((S.PROFILE / "profile-current-control-0.json").read_bytes())}
    logs.update({f"instrumented_{i}": json.loads((S.PROFILE / f"profile-current-instrumented-{i}.json").read_bytes())["benchmark_rows"] for i in range(3)})
    verdict_path = BASE / "f01-d7-direct-nonnan-verdict.json"
    verdict = json.loads(verdict_path.read_bytes())
    assert verdict["seed"] == 807 and verdict["passed"] and verdict["stage"] == "score"
    assert S.sha((BASE / "inputs/f01-d7-direct-nonnan/Kernel.lean").read_bytes()) == S.FULL60F
    element = generator["element"]
    rows = []
    for case in plan["cases"]:
        if case["kernel"] not in ("sum", "bmm"):
            continue
        c = case
        checksum = 0
        trace = hashlib.sha256()
        totals = counters()
        nan_outputs = 0
        outputs = 0
        nonfinite_nonnan_outputs = 0
        n = c["length"] if c["kernel"] == "sum" else c["n"]
        if c["kernel"] == "bmm":
            batch, m, p = c["batch"], c["m"], c["p"]
            A = [element(c, i, 0, n) for i in range(batch * m * n)]
            B = [element(c, i, 1, p) for i in range(batch * n * p)]
            count = batch * m * p
        else:
            count = c["batch"]
        for q in range(count):
            assert time.monotonic() - started < MAX_SECONDS, "Bounded local discovery analysis expired"
            local = counters()
            acc = 0
            any_nonfinite = False
            if c["kernel"] == "bmm":
                j = q % p
                i = (q // p) % m
                b = q // (m * p)
                aa, bb = (b * m + i) * n, b * n * p + j
            for k in range(n):
                if c["kernel"] == "sum":
                    value = element(c, q * n + k, 0, n)
                else:
                    x, y = A[aa + k], B[bb + k * p]
                    local["scalar_mul_calls"] += 1
                    if oracle["exp"](x) == 255 or oracle["exp"](y) == 255:
                        any_nonfinite = True
                        local["mul_nonfinite_cold_calls"] += 1
                        selected = oracle["choose"](x, y) is not None
                        local["mul_raw_nan_selected"] += selected
                        local["mul_no_nan_exceptional_misses"] += not selected
                    value = oracle["mul"](x, y)
                local["scalar_add_calls"] += 1
                local["ordered_steps"] += 1
                if oracle["exp"](acc) == 255 or oracle["exp"](value) == 255:
                    any_nonfinite = True
                    local["add_nonfinite_cold_calls"] += 1
                    selected = oracle["choose"](acc, value) is not None
                    local["add_raw_nan_selected"] += selected
                    local["add_no_nan_exceptional_misses"] += not selected
                acc = oracle["add"](acc, value)
            if oracle["nan"](acc):
                nan_outputs += 1
                # Only these outputs reach the retained60f complete raw replay.
                totals.update(local)
            elif any_nonfinite:
                nonfinite_nonnan_outputs += 1
            outputs += 1
            trace.update(acc.to_bytes(4, "little"))
            checksum = ((checksum ^ acc) * 16777619) & S.M32
        matches = {name: log[c["name"]]["checksum"] == checksum for name, log in logs.items()}
        assert all(matches.values()), f"Actual Lean checksum mismatch in {c['name']}"
        row = {"name": c["name"], "kernel": c["kernel"], "timed": c["timed"],
               "outputs": outputs, "native_nan_endpoint_raw_replay_outputs": nan_outputs,
               "nonfinite_inputs_nonnan_outputs_without_raw_replay": nonfinite_nonnan_outputs,
               "current60f_raw_replay_counts": dict(totals), "checksum32": checksum,
               "actual_lean_checksum_matches": matches, "output_words_le_sha256": trace.hexdigest()}
        rows.append(row)
        print(json.dumps({"case": c["name"], "nan_outputs": nan_outputs,
                          "selected_add": totals["add_raw_nan_selected"],
                          "selected_mul": totals["mul_raw_nan_selected"], "checksums": "MATCH_ALL4"}), flush=True)
    assert len(rows) == 70
    groups = {}
    for kernel in ("sum", "bmm"):
        total = counters()
        subset = [r for r in rows if r["kernel"] == kernel and r["timed"]]
        for row in subset:
            total.update(row["current60f_raw_replay_counts"])
        groups[kernel] = {"timed_cases": len(subset), "raw_replay_outputs": sum(r["native_nan_endpoint_raw_replay_outputs"] for r in subset),
                          "counts": dict(total)}
    work = {cell: sum(c["work"] for c in plan["cases"] if c["timed"] and c["name"].rsplit(":", 1)[0] == cell) for cell in verdict["classes"]}
    times = {cell: work[cell] * v["submission_ns"] for cell, v in verdict["classes"].items()}
    affected = sorted({r["name"].rsplit(":", 1)[0] for r in rows if r["timed"] and
        (r["current60f_raw_replay_counts"]["add_raw_nan_selected"] or r["current60f_raw_replay_counts"]["mul_raw_nan_selected"])})
    assert all(p.read_bytes() == data for p, data in cached.items())
    assert plan_path.read_bytes() == plan_bytes
    result = {"status": "PASS_FINITE_MODEL_WITH_ACTUAL_CHECKSUM_ANCHORS", "discovery_seed": 807,
        "completed_at_utc": datetime.now(timezone.utc).isoformat(), "analysis_seconds": time.monotonic() - started,
        "analysis_sha256": S.sha(Path(__file__).read_bytes()), "plan_sha256": S.sha(plan_bytes),
        "current60f_sha256": S.FULL60F, "dependencies_sha256": {S.label(p): S.sha(data) for p, data in cached.items()},
        "checksum_comparisons": len(rows) * 4, "cases": rows, "timed_tensor_totals": groups,
        "affected_whole_cell_time_exposure_ceiling": {"cells": affected, "ns": sum(times[c] for c in affected),
            "whole_timed_share": sum(times[c] for c in affected) / sum(times.values())},
        "scope": "Counts only scalar operations in complete raw sum/dot replay reached by retained60f NaN endpoints. Original first native passes, allocation/preparation and replay normal calls remain costs; no exposure-to-cycle attribution. Checksums compare finite source model to actual earlier Lean outputs, not execution of the new candidate. Quiet-suffix/prefix optimizations overlap these counts. No future confirmation inputs.",
        "gain": "UNKNOWN", "new_candidate_lean_and_full_gate": "NOT_RUN_BY_THIS_ANALYSIS"}
    (HERE / "scalar-nan-fallback-807.json").write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"status": result["status"], "seconds": result["analysis_seconds"], "totals": groups,
                      "exposure": result["affected_whole_cell_time_exposure_ceiling"]}))


if __name__ == "__main__":
    main()
