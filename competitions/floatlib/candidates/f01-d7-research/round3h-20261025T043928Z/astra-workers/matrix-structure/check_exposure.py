"""Read existing exposed diagnostics; bounded structure/trace model, no float oracle."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib, json, time

OUT = Path(__file__).resolve().parent
ROOT = next(p for p in OUT.parents if (p / "competitions/floatlib/pins.json").is_file())
start = time.monotonic()
source = ROOT / "competitions/floatlib/candidates/f01-d7-research/round3h-20261024T112622Z/profile-whole-multi-analysis-40099316795.json"
raw = source.read_bytes()
analysis = json.loads(raw)
groups = []
for seed in analysis["seeds"]:
    cases = seed["cases"]
    whole = sum(c["whole_process_mean_ns"] for c in cases if c["timed"])
    bmm = sum(c["whole_process_mean_ns"] for c in cases if c["timed"] and c["kernel"] == "bmm")
    selected = []
    for c in cases:
        s = c["shape"]
        if c["kernel"] != "bmm" or not c["timed"] or not (s["p"] == 2 and s["n"] > 1 and s["m"] >= 4):
            continue
        rows, n = s["batch"] * s["m"], s["n"]
        selected.append({"name": c["name"], "shape": s, "prior_route": c["route"],
                         "diagnostic_whole_ns": c["whole_process_mean_ns"],
                         "whole_share": c["whole_process_mean_ns"] / whole,
                         "raw_A_decodes_thinB": 2 * rows * n,
                         "raw_A_decodes_dual": rows * n,
                         "k_loop_steps_thinB": 2 * rows * n,
                         "k_loop_steps_dual": rows * n,
                         "B_map_elements_both": s["batch"] * n * 2,
                         "native_multiply_add_pairs_both": 2 * rows * n,
                         "NaN_finish_calls_both": 2 * rows})
    cost = sum(c["diagnostic_whole_ns"] for c in selected)
    groups.append({"seed": seed["seed"], "selected_cases": selected,
                   "whole_share": cost / whole, "bmm_share": cost / bmm,
                   "hypothetical_25pct_selected_reduction_whole": .25 * cost / whole,
                   "hypothetical_50pct_selected_reduction_whole": .50 * cost / whole})

# Tokens encode every original ordered multiply-then-add input. No arithmetic is
# replaced, and signed-zero/NaN handling remains an obligation of the Lean proof.
checks = 0
for batch in range(4):
    for m in range(9):
        for n in range(6):
            for r in range(batch * m):
                base_a, base_b = r * n, (r // m) * n * 2
                for j in range(2):
                    reference = [(base_a + k, base_b + j + k * 2) for k in range(n)]
                    fused_lane = [(base_a + k, base_b + k * 2 + j) for k in range(n)]
                    assert fused_lane == reference
                    checks += 1
                assert time.monotonic() - start < 5

receipt = {"at_utc": datetime.now(timezone.utc).isoformat(),
           "status": "FINITE_TRACE_AND_EXISTING_DIAGNOSTIC_ONLY",
           "source": str(source.relative_to(ROOT)), "source_sha256": hashlib.sha256(raw).hexdigest(),
           "scope": "Already exposed R12 DF whole-call diagnostics; not official score weights, not fresh holdouts, not dual-kernel timing",
           "groups": groups, "trace_lane_checks": checks,
           "trace_dimensions": {"batch": "0..3", "m": "0..8", "n": "0..5", "p": 2},
           "elapsed_seconds": time.monotonic() - start,
           "limitations": "Saved A reads and loop counts are source-model counts. Actual generated code, full gate, and end-to-end timing UNKNOWN. Float32 exceptional-value correctness is not established by the trace model."}
(OUT / "exposure-and-trace.json").write_text(json.dumps(receipt, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
print(json.dumps({"trace_lane_checks": checks, "elapsed_seconds": receipt["elapsed_seconds"],
                  "shares": [{"seed": g["seed"], "whole": g["whole_share"], "bmm": g["bmm_share"], "cases": len(g["selected_cases"])} for g in groups]}))
