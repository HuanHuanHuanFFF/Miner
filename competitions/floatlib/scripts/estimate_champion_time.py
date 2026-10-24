"""Frozen champion estimate; absolute nanoseconds never recalibrate an existing anchor."""
import argparse
from copy import deepcopy
from datetime import datetime, timezone
import hashlib
import json
import math
from pathlib import Path
import statistics
import sys

ROOT = Path(__file__).resolve().parents[3]
DATA = ROOT / "competitions/floatlib/candidates/f01-d7-research"
OPS = ("add", "mul", "sum", "bmm")
DEFAULT_ANCHOR = DATA / "round8h-20261024T190259Z/freeze-anchor.json"
AGGREGATION = "median_per_cell_normalized_delta_then_frozen_work_projection"

class EstimateRejected(ValueError):
    """Unsupported evidence. Callers must not save an estimate after this failure."""

def require(condition, message):
    if not condition:
        raise EstimateRejected(message)

def load(path):
    return json.loads(Path(path).read_bytes())

def save(path, value):
    Path(path).write_text(json.dumps(value, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")

def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()

def canonical_sha(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(",", ":"), ensure_ascii=False, allow_nan=False).encode()).hexdigest()

def positive(value):
    return isinstance(value, (int, float)) and not isinstance(value, bool) and math.isfinite(value) and value > 0

def aggregate(values):
    return {"ratio_median": statistics.median(values), "ratio_range": [min(values), max(values)]}

def checked_record(row, root=ROOT):
    """Bind source, raw gate and execution plan before allowing a paired update."""
    require(row.get("full_gate") is True, "Not a complete passing gate")
    path = root / row["verdict"]
    require(sha(path) == row["verdict_sha256"], "Verdict bytes changed")
    verdict = load(path)
    directory = path.parent
    provenance = load(directory / "provenance.json")
    summary = load(directory / "summary.json")
    plan = load(directory / "requested-plan.json")
    require(verdict.get("passed") is True and verdict.get("mode") == "gate" and verdict.get("slot") == "full" and verdict.get("stage") == "score", "Incomplete raw gate")
    require(verdict.get("reference_complete") is True and not verdict.get("incumbent_failed") and not verdict.get("exhausted"), "Incomplete reference or exhausted gate")
    require(len(verdict.get("rounds", [])) == provenance["rounds"] == 25, "Expected original 25 rounds")
    require(verdict["seed"] == row["seed"] == provenance["seed"] == plan["seed"], "Seed mismatch")
    require(verdict["suite"]["sha256"] == row["suite_sha256"] == provenance["suite_sha256"] == sha(directory / "public-v2.json"), "Suite mismatch")
    require(row["official_commit"] == provenance["official_commit"] == summary["official_commit"] == plan["official_commit"], "Official version mismatch")
    require(sha(directory / "requested-plan.json") == provenance["requested_plan_sha256"], "Plan changed")
    require(verdict["verifier_fingerprint"] == verdict["verifier_fingerprint_end"] == row["verifier_fingerprint"], "Verifier changed")
    require(verdict["classes"] == row["classes"], "Classes differ from raw gate")
    require(load(directory / "public-cell-work.json") == row["cell_work"], "Work differs from raw plan")
    source_path = directory / "inputs" / row["candidate"] / "Kernel.lean"
    require(sha(source_path) == row["kernel_sha256"], "Wrong candidate source bytes")
    matches = [r for r in summary["results"] if r["candidate"] == row["candidate"]]
    require(len(matches) == 1, "Ambiguous summary candidate")
    result = matches[0]
    require(result["kernel_sha256"] == row["kernel_sha256"] and result.get("full_gate") is True and result.get("exit_code") == 0 and result["verdict_sha256"] == row["verdict_sha256"], "Source/full gate summary mismatch")
    require(any(c["candidate"] == row["candidate"] and c["sha256"] == row["kernel_sha256"] for c in plan["candidates"]), "Source absent from execution plan")
    normalized = deepcopy(row)
    # A shared artifact directory identifies one runner execution, not just CPU model.
    normalized.update(runner_execution=directory.relative_to(root).as_posix(), drawn_plan_sha256=sha(directory / "public-drawn-plan.json"), provenance_sha256=sha(directory / "provenance.json"), incumbent_sha256=verdict["incumbent_sha256"], reference_champion_sha256=verdict["champion_sha256"], rounds=25)
    normalized["raw_evidence"] = [{"path": p.relative_to(root).as_posix(), "sha256": sha(p)} for p in (path, source_path, directory / "summary.json", directory / "provenance.json", directory / "requested-plan.json", directory / "public-drawn-plan.json", directory / "public-cell-work.json", directory / "public-v2.json")]
    return normalized

def build_frozen_anchor(model, rows, provenance, champion_classes):
    """Pure constructor from an explicitly reviewed projection; never called by refresh."""
    require(len(model["samples"]) >= 2, "Anchor needs multiple retained samples")
    selected = []
    for sample in model["samples"]:
        matches = [r for r in rows if r["run"] == sample["run"] and r["kernel_sha256"] == model["kernel_sha256"]]
        require(len(matches) == 1, "Anchor sample absent or ambiguous")
        row = matches[0]
        require(row["full_gate"] and row["verdict_sha256"] == sample["candidate_verdict_sha256"] and row["cell_work"] == sample["cell_work"] and row["seed"] == sample["seed"] and row["suite_sha256"] == sample["candidate_suite_sha256"], "Anchor source/sample mismatch")
        require(set(row["classes"]) == set(row["cell_work"]) == set(champion_classes), "Anchor/champion cell mismatch")
        require(all(positive(c["submission_ns"]) and positive(c["incumbent_ns"]) and
                    positive(row["cell_work"][key]) and positive(champion_classes[key]["submission_ns"])
                    for key, c in row["classes"].items()), "Invalid anchor costs")
        for op in OPS:
            total = sum(c["submission_ns"] * row["cell_work"][key] for key, c in row["classes"].items() if key.startswith(op + ":"))
            projected = sum(c["submission_ns"] * row["cell_work"][key] for key, c in champion_classes.items() if key.startswith(op + ":"))
            require(math.isclose(total, sample["candidate_total_ns"][op], rel_tol=1e-12), "Anchor original costs do not reproduce")
            require(math.isclose(projected, sample["champion_projected_total_ns"][op], rel_tol=1e-12), "Anchor champion raw projection mismatch")
            require(math.isclose(total / sample["champion_projected_total_ns"][op], sample["operation_ratios"][op], rel_tol=1e-12), "Anchor ratio mismatch")
        require(math.isclose(sum(sample["candidate_total_ns"].values()) / sum(sample["champion_projected_total_ns"].values()),
                             sample["whole_ratio"], rel_tol=1e-12), "Anchor whole ratio mismatch")
        selected.append(deepcopy(row))
    require(len({r["run"] for r in selected}) == len(selected), "Duplicate frozen sample")
    require(len({r["suite_sha256"] for r in selected}) == 1, "Mixed anchor suites")
    for op in OPS:
        require(aggregate([s["operation_ratios"][op] for s in model["samples"]]) == model["operations"][op], "Anchor aggregate mismatch")
    require(aggregate([s["whole_ratio"] for s in model["samples"]]) == model["whole"], "Whole aggregate mismatch")
    anchor = {"schema_version": 1, "aggregation": AGGREGATION, "provenance": deepcopy(provenance), "original_model": deepcopy(model), "frozen_records": selected, "champion_classes": deepcopy(champion_classes), "public_suite_sha256": selected[0]["suite_sha256"], "candidate_kernel_sha256": model["kernel_sha256"], "champion_digest": model["champion_digest"], "champion_suite": deepcopy(model["champion_suite"])}
    anchor["payload_sha256"] = canonical_sha(anchor)
    return anchor

def validate_anchor(anchor):
    require(anchor.get("payload_sha256") == canonical_sha({k: v for k, v in anchor.items() if k != "payload_sha256"}), "Frozen anchor payload changed")
    require(anchor.get("schema_version") == 1 and anchor.get("aggregation") == AGGREGATION, "Unsupported anchor schema/aggregation")
    model = anchor["original_model"]
    require(model["kernel_sha256"] == anchor["candidate_kernel_sha256"] and model["champion_digest"] == anchor["champion_digest"] and model["champion_suite"] == anchor["champion_suite"], "Anchor identities disagree")
    require(anchor == build_frozen_anchor(model, anchor["frozen_records"], anchor["provenance"], anchor["champion_classes"]),
            "Frozen inputs do not reconstruct original projection")
    return model

def normalized_pair_delta(candidate, baseline, anchor, candidate_sha256):
    """Pure per-cell (candidate/incumbent)/(anchor/incumbent) within one execution."""
    require(candidate["kernel_sha256"] == candidate_sha256, "Wrong candidate source")
    require(baseline["kernel_sha256"] == anchor["candidate_kernel_sha256"], "Wrong baseline source")
    for row in (candidate, baseline):
        require(row.get("full_gate") is True and row.get("rounds") == 25, "Pair lacks full gate")
        require(row.get("suite_sha256") == anchor["public_suite_sha256"], "Wrong pair suite")
        for field in ("official_commit", "incumbent_sha256", "reference_champion_sha256", "verifier_fingerprint"):
            require(row.get(field) == anchor["frozen_records"][0][field], "Changed anchor gate/reference: " + field)
    for field in ("run", "seed", "suite_sha256", "official_commit", "runner_execution", "drawn_plan_sha256", "provenance_sha256", "incumbent_sha256", "reference_champion_sha256", "verifier_fingerprint", "cell_work"):
        require(candidate.get(field) is not None and candidate[field] == baseline.get(field), "Unmatched pair: " + field)
    cells = set(anchor["frozen_records"][0]["classes"])
    require(set(candidate["classes"]) == set(baseline["classes"]) == set(candidate["cell_work"]) == cells, "Incomplete pair cells")
    delta = {}
    for cell in sorted(cells):
        c, b = candidate["classes"][cell], baseline["classes"][cell]
        require(all(positive(x) for x in (c["submission_ns"], c["incumbent_ns"], b["submission_ns"], b["incumbent_ns"], candidate["cell_work"][cell])), "Invalid per-cell timing/work")
        delta[cell] = (c["submission_ns"] / c["incumbent_ns"]) / (b["submission_ns"] / b["incumbent_ns"])
    return delta

def estimate_from_anchor(anchor, candidate_sha256, champion_digest, champion_suite, pairs=()):
    """Pure estimate. Same source is an identity, not another noisy control sample."""
    original = validate_anchor(anchor)
    require(champion_digest == anchor["champion_digest"] and champion_suite == anchor["champion_suite"], "Champion digest/suite changed: reviewed re-anchor required; no verified same-suite digest chain supplied")
    model = deepcopy(original)
    model.update(method="FROZEN_ANCHOR_NORMALIZED_PAIRED_DELTAS", kernel_sha256=candidate_sha256, aggregation=AGGREGATION, anchor_payload_sha256=anchor["payload_sha256"], direct_same_suite_champion_comparison="UNKNOWN", official_admission="UNKNOWN")
    if candidate_sha256 == anchor["candidate_kernel_sha256"]:
        model.update(update_kind="EXACT_FROZEN_SOURCE_IDENTITY", paired_updates=[])
        return model
    require(len(pairs) >= 1, "New source needs raw same-runner paired full gates; absolute ns is insufficient")
    keys = [(c["runner_execution"], c["run"], c["seed"]) for c, _ in pairs]
    require(len(set(keys)) == len(keys), "Duplicate paired execution")
    deltas = [normalized_pair_delta(c, b, anchor, candidate_sha256) for c, b in pairs]
    cells = sorted(deltas[0])
    median_delta = {cell: statistics.median(d[cell] for d in deltas) for cell in cells}
    samples = []
    for frozen, sample in zip(anchor["frozen_records"], original["samples"]):
        projected = sample["champion_projected_total_ns"]
        totals = {op: sum(frozen["classes"][cell]["submission_ns"] * sample["cell_work"][cell] * median_delta[cell] for cell in cells if cell.startswith(op + ":")) for op in OPS}
        updated = deepcopy(sample)
        updated.update(candidate_total_ns=totals, operation_ratios={op: totals[op] / projected[op] for op in OPS}, whole_ratio=sum(totals.values()) / sum(projected.values()), source_role="FROZEN_ANCHOR_WORK_PROJECTION")
        samples.append(updated)
    model.update(update_kind="PAIRED_SOURCE_DELTA", samples=samples, cell_relative_delta_median=median_delta, operations={op: aggregate([s["operation_ratios"][op] for s in samples]) for op in OPS}, whole=aggregate([s["whole_ratio"] for s in samples]), paired_updates=[{"run": c["run"], "seed": c["seed"], "runner_execution": c["runner_execution"], "candidate_verdict": c["verdict"], "candidate_verdict_sha256": c["verdict_sha256"], "baseline_verdict": b["verdict"], "baseline_verdict_sha256": b["verdict_sha256"], "cell_relative_delta": d, "raw_evidence": c.get("raw_evidence", []) + b.get("raw_evidence", [])} for (c, b), d in zip(pairs, deltas)])
    return model

def select_pairs(records, runs, candidate_sha256, anchor, root=ROOT):
    """Every declared complete source gate must have a matching anchor baseline."""
    require(len(set(runs)) == len(runs), "Duplicate declared gate")
    target = [r for r in records if r["kernel_sha256"] == candidate_sha256 and r.get("full_gate")]
    require({r["run"] for r in target} == set(runs), "Declared gates omit eligible source records")
    pairs = []
    for run in runs:
        matches = [r for r in target if r["run"] == run]
        require(len(matches) == 1, "Candidate gate absent/ambiguous")
        candidate = checked_record(matches[0], root)
        matches = [r for r in records if r.get("full_gate") and r["run"] == run and r["kernel_sha256"] == anchor["candidate_kernel_sha256"] and (root / r["verdict"]).parent == (root / candidate["verdict"]).parent]
        require(len(matches) == 1, "No unique same-runner anchor baseline for source gate")
        baseline = checked_record(matches[0], root)
        normalized_pair_delta(candidate, baseline, anchor, candidate_sha256)
        pairs.append((candidate, baseline))
    return pairs

def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--anchor", type=Path, default=DEFAULT_ANCHOR)
    parser.add_argument("--dry-run", action="store_true", help="Verify and print without writing model/view/state")
    args = parser.parse_args(argv)
    view_path = DATA / "multiplier-comparison.json"
    state_path = ROOT / "competitions/floatlib/coordination/development-status.json"
    view, state, anchor = load(view_path), load(state_path), load(args.anchor)
    validate_anchor(anchor)
    for item in anchor["provenance"].get("frozen_files", []):
        require(sha(ROOT / item["path"]) == item["sha256"], "Frozen input bytes changed: " + item["path"])
    for row in anchor["frozen_records"]:
        for item in row.get("raw_evidence", []):
            require(sha(ROOT / item["path"]) == item["sha256"], "Historical raw evidence changed")
    require(sha(ROOT / state["kernel"]) == view["kernel_sha256"] == state["kernel_sha256"], "Current source mismatch")
    snapshot = load(DATA / "current-official-snapshot.json")
    official = DATA / snapshot["directory"]
    receipt = load(official / "receipts.json")
    for name in ("champions", "competition", "champion-detail", "champion-report"):
        item = receipt["responses"][name]
        path = official / item["file"]
        require(item["status"] == 200 and len(path.read_bytes()) == item["bytes"] and sha(path) == item["sha256"], "Official receipt mismatch")
    detail = load(official / "champion-detail.raw")
    report = load(official / "champion-report.raw")["report"]
    report = json.loads(report) if isinstance(report, str) else report
    champion = next(x for x in load(official / "champions.raw") if x["current"])
    competition = load(official / "competition.raw")
    require(detail["id"] == snapshot["champion"] == champion["submission"] == int(report["submission"]), "Official champion ID mismatch")
    require(detail["verification_current"] and detail["state"] == "accepted" and report["passed"] and detail["classes"] == report["classes"], "Official champion not verified")
    require(detail["digest"] == anchor["champion_digest"] and report["suite"] == anchor["champion_suite"], "Champion digest/suite changed: explicit reviewed re-anchor required; previous estimate preserved")
    records = load(ROOT / view["public_results"])["records"]
    pairs = () if view["kernel_sha256"] == anchor["candidate_kernel_sha256"] else select_pairs(records, view["full_gate_runs"], view["kernel_sha256"], anchor)
    model = estimate_from_anchor(anchor, view["kernel_sha256"], detail["digest"], report["suite"], pairs)
    model.update(as_of_utc=datetime.now(timezone.utc).isoformat(), candidate=view["candidate"], estimator_sha256=sha(Path(__file__)), anchor=args.anchor.resolve().relative_to(ROOT).as_posix(), anchor_sha256=sha(args.anchor), current_public_results_sha256=sha(ROOT / view["public_results"]), champion_submission=detail["id"], current_champion_report=(official / "champion-report.raw").relative_to(ROOT).as_posix(), current_champion_report_sha256=sha(official / "champion-report.raw"), formula="Frozen original group costs/work, updated only by each cell median (candidate_submission/candidate_incumbent)/(anchor_submission/anchor_incumbent) across ALL declared matched full gates; re-sum four operations and whole for each frozen workload, then median across frozen workloads.", scope="INFERRED rough development estimate; original cross-suite/cross-hardware calibration uncertainty is frozen, not resolved. Direct same-suite champion comparison and official admission remain UNKNOWN.", range_scope="Range across frozen anchor workloads after common paired delta; not a confidence interval.")
    output = {"champion": detail["id"], "operations": model["operations"], "whole": model["whole"], "update_kind": model["update_kind"], "anchor_sha256": model["anchor_sha256"], "dry_run": args.dry_run}
    if args.dry_run:
        print(json.dumps(output))
        return model
    model_path = DATA / "champion-time-estimate.json"
    save(model_path, model)
    summary = {k: model[k] for k in ("status", "method", "candidate", "kernel_sha256", "champion_submission", "champion_digest", "operations", "whole")}
    summary.update(evidence=model_path.relative_to(ROOT).as_posix(), evidence_sha256=sha(model_path))
    if view["champion"]["submission"] != detail["id"]:
        view["champion"]["candidate_over_champion_time"] = "UNKNOWN"
        view["champion"]["candidate_over_champion_time_by_operation"] = {op: "UNKNOWN" for op in OPS}
    view["champion"].update(submission=detail["id"], digest=detail["digest"], snapshot=competition["current_snapshot_id"], official_cumulative_speedup_vs_shipped=champion["speedup_vs_shipped"], official_speedup_basis=champion["speedup_basis"], receipts=(official / "receipts.json").relative_to(ROOT).as_posix())
    view["champion_time_estimate"] = summary
    policy = view["dashboard_policy"]
    policy.update(use_estimates_when_direct_unknown=True, allow_cross_suite_conversion=True, cross_suite_scope="INFERRED_FROZEN_ANCHOR_WITH_MATCHED_SOURCE_DELTAS", estimator="competitions/floatlib/scripts/estimate_champion_time.py", updated_at_utc=model["as_of_utc"])
    view["as_of_utc"] = model["as_of_utc"]
    save(view_path, view)
    state["current_multiplier_view"].update(official_champion=detail["id"], snapshot=competition["current_snapshot_id"], champion_time_estimate=summary, dashboard_policy=policy, champion_official_historical_speedup_vs_shipped=champion["speedup_vs_shipped"], champion_official_speedup_basis=champion["speedup_basis"])
    state["current_champion_comparison"].update(submission=detail["id"], source_digest=detail["digest"], policy_snapshot=competition["current_snapshot_id"], queried_at_utc=snapshot["queried_at_utc"])
    save(state_path, state)
    print(json.dumps(output))
    return model

if __name__ == "__main__":
    try:
        main()
    except (EstimateRejected, KeyError, OSError, ValueError) as exc:
        print("Champion estimate REJECTED: " + str(exc), file=sys.stderr)
        sys.exit(2)
