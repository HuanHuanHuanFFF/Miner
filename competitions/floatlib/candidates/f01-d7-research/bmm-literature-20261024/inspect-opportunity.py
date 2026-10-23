"""Read frozen evidence only; report route coverage, never predicted speedup."""

import argparse
import hashlib
import json
from datetime import datetime, timezone
from pathlib import Path


ROOT = Path(__file__).resolve().parents[5]
TRACK = ROOT / "competitions/floatlib"
CI = TRACK / "candidates/f01-mul-log2-proof1/ci-runs"
BASE = CI / "40005234741/download-9f2affecc48e4d2993e5b715cba86bf6/diagnostics/f01-d7-public-suite/retained-stage-profile"
SOURCE = TRACK / "candidates/f01-r8-combined-result-guard/Kernel.lean"
EXPECTED_SOURCE = "41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7"
EXPECTED_C = "fb421a595ceced1cf8994f19ccb32704ac20a02a0430eda6c4134bf042d075db"


def identity(path):
    payload = path.read_bytes()
    return {"path": path.relative_to(ROOT).as_posix(), "bytes": len(payload),
            "sha256": hashlib.sha256(payload).hexdigest()}


def read_json(path):
    return json.loads(path.read_text(encoding="utf-8"))


def bmm_cases(plan):
    return [c for c in plan["cases"] if c["kernel"] == "bmm" and c["timed"]]


def groups(cases):
    predicates = {
        "direct": lambda c: c["n"] <= 4 or c["p"] <= 2,
        "packed": lambda c: c["n"] > 4 and c["p"] > 2,
        "short_n": lambda c: c["n"] <= 4,
        "cross_batch_long_thin": lambda c: c["batch"] >= 4 and c["n"] > 4 and c["p"] <= 2,
        "cross_batch_long_thin_p1": lambda c: c["batch"] >= 4 and c["n"] > 4 and c["p"] == 1,
        "cross_batch_long_thin_p2": lambda c: c["batch"] >= 4 and c["n"] > 4 and c["p"] == 2,
        "packed_p3_to_8": lambda c: c["n"] > 4 and 2 < c["p"] <= 8,
        "packed_m_le_2": lambda c: c["n"] > 4 and c["p"] > 2 and c["m"] <= 2,
    }
    return {name: [c for c in cases if pred(c)] for name, pred in predicates.items()}


def inspect():
    plan_path = BASE / "profile-retained-public-plan.json"
    control_path = BASE / "profile-retained-control-0.json"
    build_path = BASE / "profile-retained-plan.json"
    c_path = BASE / "profile-retained-original.c"
    source_identity = identity(SOURCE)
    c_identity = identity(c_path)
    assert source_identity["sha256"] == EXPECTED_SOURCE, "Retained source drifted"
    assert c_identity["sha256"] == EXPECTED_C, "Captured C drifted"
    build = read_json(build_path)
    assert build["kernel_sha256"] == EXPECTED_SOURCE
    assert build["original_c_sha256"] == EXPECTED_C
    assert "-ffp-contract=off" in build["compile_argv"]
    cases = bmm_cases(read_json(plan_path))
    control = read_json(control_path)
    assert len(cases) == 34
    assert all(control[c["name"]]["timed"] for c in cases)
    total = sum(control[c["name"]]["best_ns"] for c in cases)
    assert total > 0
    coverage = {}
    for name, selected in groups(cases).items():
        ns = sum(control[c["name"]]["best_ns"] for c in selected)
        coverage[name] = {
            "cases": len(selected), "control_best_ns_sum": ns,
            "fraction_of_bmm_control": ns / total,
            "case_names": [c["name"] for c in selected],
            "outputs": sum(c["batch"] * c["m"] * c["p"] for c in selected),
        }
    assert coverage["direct"]["control_best_ns_sum"] + coverage["packed"]["control_best_ns_sum"] == total
    assert coverage["cross_batch_long_thin_p1"]["control_best_ns_sum"] + coverage["cross_batch_long_thin_p2"]["control_best_ns_sum"] == coverage["cross_batch_long_thin"]["control_best_ns_sum"]

    historical_shapes = []
    for run in [39996680317, 40003013355, 40003240475]:
        paths = list((CI / str(run)).rglob("public-drawn-plan.json"))
        assert len(paths) == 1, (run, len(paths))
        selected = bmm_cases(read_json(paths[0]))
        historical_shapes.append({"run": run, "plan": identity(paths[0]),
                                  "timed_bmm_cases": len(selected),
                                  "guard_case_counts": {k: len(v) for k, v in groups(selected).items()},
                                  "scope": "Already-executed plans; guard counts only, no per-case time share inferred."})

    return {
        "generated_at_utc": datetime.now(timezone.utc).isoformat(),
        "status": "VERIFIED_HISTORICAL_EVIDENCE_DERIVATION_ONLY",
        "run": 40005234741, "seed": 852,
        "scope": "One uninstrumented diagnostic control process, per-case best_ns sum. Route exposure is not recoverable time, a predicted speedup, official scoring weight, or a fresh benchmark.",
        "groups_overlap": "direct/packed partition the cases; p1/p2 partition cross_batch_long_thin. Other groups overlap and must not be added.",
        "inputs": [source_identity, c_identity, identity(plan_path), identity(control_path), identity(build_path)],
        "bmm_control_best_ns_sum": total, "coverage": coverage,
        "historical_other_input_coverage": historical_shapes,
        "candidate_size_headroom_bytes": {"retained41": 256000 - SOURCE.stat().st_size,
            "research_a066": 256000 - (TRACK / "candidates/f01-d10-bmm-direct-rows/Kernel.lean").stat().st_size},
        "new_candidate_created": False, "new_lean_or_ci_run": False,
    }


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    result = inspect()
    content = json.dumps(result, ensure_ascii=False, indent=2) + "\n"
    if args.output:
        destination = args.output.resolve()
        assert destination.parent == Path(__file__).resolve().parent, "Output must stay in this research directory"
        destination.write_text(content, encoding="utf-8", newline="\n")
        print(json.dumps({"output": destination.relative_to(ROOT).as_posix(),
                          "timed_bmm_cases": 34, "input_identities_checked": len(result["inputs"]),
                          "new_ci": False}, ensure_ascii=False))
    else:
        print(content)
