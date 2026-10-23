"""Project champion group costs onto our measured work mix; estimates only."""
from datetime import datetime, timezone
import hashlib
import json
import math
from pathlib import Path
import statistics

ROOT = Path(__file__).resolve().parents[3]
DATA = ROOT / "competitions/floatlib/candidates/f01-d7-research"
OPS = ("add", "mul", "sum", "bmm")


def load(path):
    return json.loads(path.read_bytes())


def save(path, value):
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    view_path = DATA / "multiplier-comparison.json"
    state_path = ROOT / "competitions/floatlib/coordination/development-status.json"
    view, state = load(view_path), load(state_path)
    assert sha(ROOT / state["kernel"]) == view["kernel_sha256"] == state["kernel_sha256"]
    snapshot = load(DATA / "current-official-snapshot.json")
    official = DATA / snapshot["directory"]
    receipt = load(official / "receipts.json")
    for name in ("champions", "competition", "champion-detail", "champion-report"):
        item = receipt["responses"][name]
        path = official / item["file"]
        assert item["status"] == 200 and len(path.read_bytes()) == item["bytes"] and sha(path) == item["sha256"]
    detail = load(official / "champion-detail.raw")
    report = load(official / "champion-report.raw")["report"]
    report = json.loads(report) if isinstance(report, str) else report
    champion = next(x for x in load(official / "champions.raw") if x["current"])
    competition = load(official / "competition.raw")
    assert detail["id"] == snapshot["champion"] == champion["submission"] == int(report["submission"])
    assert detail["verification_current"] and detail["state"] == "accepted" and report["passed"]
    assert detail["classes"] == report["classes"]
    records = load(ROOT / view["public_results"])["records"]
    samples = []
    for run in view["full_gate_runs"]:
        rows = [r for r in records if r["run"] == run and r["kernel_sha256"] == view["kernel_sha256"] and r["full_gate"]]
        assert len(rows) == 1
        row = rows[0]
        verdict_path = ROOT / row["verdict"]
        assert sha(verdict_path) == row["verdict_sha256"]
        verdict = load(verdict_path)
        assert verdict["passed"] and verdict["classes"] == row["classes"]
        assert set(row["classes"]) == set(detail["classes"]) == set(row["cell_work"])
        projected, candidate = {}, {}
        for op in OPS:
            keys = [key for key in row["classes"] if key.startswith(op + ":")]
            assert keys
            for key in keys:
                assert row["cell_work"][key] > 0
                for ns in (row["classes"][key]["submission_ns"], detail["classes"][key]["submission_ns"]):
                    assert math.isfinite(ns) and ns > 0
            candidate[op] = sum(row["classes"][key]["submission_ns"] * row["cell_work"][key] for key in keys)
            assert math.isclose(candidate[op], row["operation_total_ns"][op], rel_tol=1e-12)
            projected[op] = sum(detail["classes"][key]["submission_ns"] * row["cell_work"][key] for key in keys)
        samples.append({"run": run, "seed": row["seed"], "candidate_verdict": row["verdict"],
                        "candidate_verdict_sha256": row["verdict_sha256"], "candidate_suite_sha256": row["suite_sha256"],
                        "candidate_total_ns": candidate, "champion_projected_total_ns": projected,
                        "cell_work": row["cell_work"],
                        "operation_ratios": {op: candidate[op] / projected[op] for op in OPS},
                        "whole_ratio": sum(candidate.values()) / sum(projected.values())})
    assert len(samples) >= 2 and len({x["run"] for x in samples}) == len(samples)

    def aggregate(values):
        return {"ratio_median": statistics.median(values), "ratio_range": [min(values), max(values)]}

    model = {
        "as_of_utc": datetime.now(timezone.utc).isoformat(), "status": "INFERRED",
        "method": "CROSS_RUN_GROUP_COST_PROJECTION", "candidate": view["candidate"],
        "estimator_sha256": sha(Path(__file__)), "public_results_sha256": sha(ROOT / view["public_results"]),
        "kernel_sha256": view["kernel_sha256"], "champion_submission": detail["id"], "champion_digest": detail["digest"],
        "champion_suite": report["suite"], "champion_report": (official / "champion-report.raw").relative_to(ROOT).as_posix(),
        "champion_report_sha256": sha(official / "champion-report.raw"),
        "official_receipts": (official / "receipts.json").relative_to(ROOT).as_posix(),
        "official_receipts_sha256": sha(official / "receipts.json"),
        "formula": "For each run and operation: sum(candidate_group_ns_per_work * public_group_work) / sum(champion_group_ns_per_work * the_same_public_group_work); median over all retained exact-source full-gate runs. Whole uses summed ns before division.",
        "assumptions": ["Champion private-suite group mean costs approximate the same named public-suite groups.",
                        "Cross-run hardware cost scale is assumed 1.0; no matched CPU calibration is available.",
                        "Both sources use the original gate ns-per-work units; length, shape and value distributions can differ."],
        "scope": "User-requested development gap estimate. Direct same-suite champion comparison and official admission remain UNKNOWN. No use of the overall champion speedup as a per-operation factor.",
        "range_scope": "Min/max across the projected public runs, not a confidence interval.",
        "operations": {op: aggregate([s["operation_ratios"][op] for s in samples]) for op in OPS},
        "whole": aggregate([s["whole_ratio"] for s in samples]), "samples": samples,
    }
    model_path = DATA / "champion-time-estimate.json"
    save(model_path, model)
    summary = {k: model[k] for k in ("status", "method", "candidate", "kernel_sha256", "champion_submission", "champion_digest", "operations", "whole")}
    summary.update(evidence=model_path.relative_to(ROOT).as_posix(), evidence_sha256=sha(model_path))
    old_champion = view["champion"]["submission"]
    if old_champion != detail["id"]:
        view["champion"]["candidate_over_champion_time"] = "UNKNOWN"
        view["champion"]["candidate_over_champion_time_by_operation"] = {op: "UNKNOWN" for op in OPS}
    view["champion"].update(submission=detail["id"], digest=detail["digest"], snapshot=competition["current_snapshot_id"],
                            official_cumulative_speedup_vs_shipped=champion["speedup_vs_shipped"], official_speedup_basis=champion["speedup_basis"],
                            receipts=(official / "receipts.json").relative_to(ROOT).as_posix())
    view["champion_time_estimate"] = summary
    policy = view["dashboard_policy"]
    policy.update(use_estimates_when_direct_unknown=True, allow_cross_suite_conversion=True,
                  cross_suite_scope="INFERRED_GROUP_COST_PROJECTION_ONLY", estimator="competitions/floatlib/scripts/estimate_champion_time.py",
                  updated_at_utc=model["as_of_utc"])
    view["as_of_utc"] = model["as_of_utc"]
    save(view_path, view)
    state["current_multiplier_view"].update(official_champion=detail["id"], snapshot=competition["current_snapshot_id"],
                                            champion_time_estimate=summary, dashboard_policy=policy,
                                            champion_official_historical_speedup_vs_shipped=champion["speedup_vs_shipped"],
                                            champion_official_speedup_basis=champion["speedup_basis"])
    state["current_champion_comparison"].update(submission=detail["id"], source_digest=detail["digest"],
                                               policy_snapshot=competition["current_snapshot_id"], queried_at_utc=snapshot["queried_at_utc"])
    save(state_path, state)
    print(json.dumps({"champion": detail["id"], "operations": model["operations"], "whole": model["whole"]}))


if __name__ == "__main__":
    main()
