"""Bounded source inverse, shape exposure and exact index/order traces; no Lean."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib, json, time, re
OUT = Path(__file__).resolve().parent
ROOT = next(p for p in OUT.parents if (p / "competitions/floatlib/pins.json").is_file())
start = time.monotonic()
sha = lambda b: hashlib.sha256(b).hexdigest()
meta = json.loads((OUT / "pairs-build-receipt.json").read_bytes())
candidate = (OUT / meta["candidate_file"]).read_bytes()
parent = (ROOT / meta["parent"]).read_bytes()
fragment = (OUT / meta["fragment"]).read_bytes()
assert sha(candidate) == meta["sha256"] and sha(parent) == meta["parent_sha256"]
assert sha(fragment) == meta["fragment_sha256"]
eol = b"\r\n" if b"\r\n" in parent else b"\n"
insert = eol + fragment.replace(b"\n", eol) + eol
assert candidate.count(insert) == 1
recovered = candidate.replace(insert, b"", 1)
recovered = recovered.replace(b"else R15ThinPairs.dispatch batch m n p A B", b"else bmmBeforeUnderflowZero batch m n p A B")
recovered = recovered.replace(b"exact R15ThinPairs.dispatch_spec batch m n p A B", b"exact bmmBeforeUnderflowZero_spec batch m n p A B")
assert recovered == parent
assert candidate.count(b"import ContractTensor") == 1 and len(candidate) <= 256000
assert not re.search(rb"\b(sorry|admit|axiom|unsafe|implemented_by|extern)\b", fragment)

trace_checks = 0
for batch in range(4):
    for m in range(9):
        for n in range(7):
            for p in range(11):
                emitted = []
                for r in range(batch * m):
                    row = []
                    for g in range((p + 1) // 2):
                        count = min(2, p - 2 * g)
                        for lane in range(count):
                            j = 2 * g + lane
                            fused = [(r * n + k, (r // m) * n * p + 2 * g + lane + k * p) for k in range(n)]
                            reference = [(r * n + k, ((r // m) * n + k) * p + j) for k in range(n)]
                            assert fused == reference
                            row.append(j)
                            trace_checks += 1
                    assert row == list(range(p))
                    emitted.extend(r * p + j for j in row)
                assert emitted == list(range(batch * m * p))
                assert time.monotonic() - start < 5

path = "competitions/floatlib/candidates/f01-d7-research/round3h-20261024T112622Z/profile-whole-multi-analysis-40099316795.json"
raw = (ROOT / path).read_bytes()
analysis = json.loads(raw)
groups = []
for seed in analysis["seeds"]:
    cs = [c for c in seed["cases"] if c["timed"]]
    whole = sum(c["whole_process_mean_ns"] for c in cs)
    bmm = sum(c["whole_process_mean_ns"] for c in cs if c["kernel"] == "bmm")
    selected = []
    for c in cs:
        s = c["shape"]
        if c["kernel"] != "bmm" or not (2 <= s["p"] <= 8 and s["n"] > 1 and s["m"] >= 4):
            continue
        if c["route"]["route"] == "UnderflowZero":
            continue
        rows, n, p = s["batch"] * s["m"], s["n"], s["p"]
        selected.append({"name": c["name"], "shape": s, "prior_route": c["route"]["route"],
                         "whole_ns": c["whole_process_mean_ns"], "whole_share": c["whole_process_mean_ns"] / whole,
                         "direct_A_decodes": rows * n * p, "paired_A_decodes": rows * n * ((p + 1) // 2),
                         "direct_B_decodes_p3to8": rows * n * p,
                         "prepared_B_decodes": s["batch"] * n * p,
                         "pair_MACs_including_unobserved_odd_tail": 2 * ((p + 1) // 2) * rows * n,
                         "original_MACs": p * rows * n,
                         "finish_calls_both": rows * p})
    cost = sum(c["whole_ns"] for c in selected)
    groups.append({"seed": seed["seed"], "cases": selected, "whole_share": cost / whole,
                   "bmm_share": cost / bmm, "hypothetical_25pct_local_reduction_whole": .25 * cost / whole,
                   "hypothetical_50pct_local_reduction_whole": .5 * cost / whole})

receipt = {"at_utc": datetime.now(timezone.utc).isoformat(), "status": "STATIC_AND_FINITE_TRACE_PASS",
           "candidate_sha256": sha(candidate), "candidate_bytes": len(candidate),
           "exact_parent_recovered": True, "new_imports": [], "new_unproved_assumptions_in_text": [],
           "trace_lane_checks": trace_checks, "trace_shapes": {"batch": "0..3", "m": "0..8", "n": "0..6", "p": "0..10"},
           "trace_scope": "Every emitted column, its raw input addresses and ascending k order; includes empty outputs, n=0 and odd tails. No Float32 oracle or Lean proof execution.",
           "exposure_source": path, "exposure_source_sha256": sha(raw), "exposure": groups,
           "exposure_scope": "Existing exposed df5c whole-call diagnostics, not official score. Shapes satisfying outer UnderflowZero route excluded. Parent ec82 runtime and new candidate timing remain UNKNOWN.",
           "cost_caveats": "Odd p computes one unobserved extra lane; pair object and emitter cost are charged. p2 already has one B map in parent, so no additional B-decoder saving there. Source counts do not prove allocations or dynamic cost.",
           "elapsed_seconds": time.monotonic() - start}
assert receipt["elapsed_seconds"] < 5
(OUT / "pairs-validation.json").write_text(json.dumps(receipt, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
print(json.dumps({"status": receipt["status"], "sha256": sha(candidate), "bytes": len(candidate),
                  "trace_lane_checks": trace_checks, "elapsed_seconds": receipt["elapsed_seconds"],
                  "exposure": [{"seed":g["seed"],"whole":g["whole_share"],"bmm":g["bmm_share"],"cases":len(g["cases"])} for g in groups]}))
