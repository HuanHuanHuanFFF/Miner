"""Replay the current official DEFLATE frontier and calibrate candidate thresholds.

Examples:
  python scripts/analyze-round10.py
  python scripts/analyze-round10.py --candidate next-run 1.31 34.18

Candidate coordinates are already on the official balanced-time / mean-file-size axes.
For a public-stage1 projection, first apply the #361 calibration described in the output.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import math
import statistics
import sys
from pathlib import Path
from typing import Any

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_SNAPSHOT = ROOT / "evidence/round10/official-start/pareto-pages.json"
DEFAULT_COMPETITION = ROOT / "evidence/round10/official-start/competition.json"
DEFAULT_LEADERBOARD = ROOT / "evidence/round10/official-start/leaderboard-pages.json"
DEFAULT_WEIGHTS = ROOT / "evidence/round10/official-start/weights-current.json"
DEFAULT_RECEIPT = ROOT / "evidence/round10/official-start/receipt.json"
DEFAULT_SOURCES = ROOT / "evidence/round10/official-start/source-availability.json"
DEFAULT_ROUND9 = ROOT / "evidence/round9/final-summary.json"
DEFAULT_OUTPUT = ROOT / "evidence/round10/frontier-start.json"
SCORER_PATH = ROOT / "sources/conjectures-optimisation-deflate/validator/scoring/pareto.py"


def load_json(path: Path) -> Any:
    return json.loads(path.read_bytes())


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def load_scorer(path: Path):
    sys.path.insert(0, str(ROOT / "scripts"))
    from round3 import load_scorer as load_round3_scorer

    return load_round3_scorer(path)


def page_rows(pages: list[dict[str, Any]], key: str, identity: str, snapshot_id: str):
    if not pages:
        raise ValueError("snapshot has no pages")
    for page in pages:
        if str(page.get("context", {}).get("snapshot_id")) != snapshot_id:
            raise ValueError("page context does not match the captured snapshot")
    if pages[-1].get("next_cursor"):
        raise ValueError("the final page still has a next_cursor")
    rows = [row for page in pages for row in page.get(key, [])]
    ids = [row[identity] for row in rows]
    if len(ids) != len(set(ids)):
        raise ValueError(f"duplicate {identity} across pages")
    return rows


def geometry(name: str, time_ratio: float, compressed_pct: float, rows: list[dict[str, Any]],
             points: list[Any], scorer: Any, bounds: Any) -> dict[str, Any]:
    dominators = [
        row["id"] for row in rows
        if row["metrics"]["balanced_time_ratio"] <= time_ratio
        and row["metrics"]["mean_file_compression_pct"] <= compressed_pct
    ]
    eligible = (
        math.isfinite(time_ratio) and math.isfinite(compressed_pct)
        and 0 < time_ratio <= bounds.time_s
        and 0 < compressed_pct <= bounds.ratio_pct
        and not dominators
    )
    trial_weights = scorer.local_global_improvement_space_log_weights(
        scorer.pareto_front(points + [scorer.Point(name, time_ratio, compressed_pct)]), bounds
    )
    better_or_equal_size = [
        row for row in rows
        if row["metrics"]["mean_file_compression_pct"] <= compressed_pct
    ]
    limiter = min(
        better_or_equal_size,
        key=lambda row: row["metrics"]["balanced_time_ratio"],
        default=None,
    )
    threshold_time = (
        limiter["metrics"]["balanced_time_ratio"] if limiter is not None else None
    )
    return {
        "name": name,
        "time_ratio": time_ratio,
        "compressed_pct": compressed_pct,
        "on_geometric_frontier": eligible,
        "dominating_ids": dominators,
        "conditional_pareto_share_pct": (
            100 * trial_weights.get(name, 0.0) if eligible else 0.0
        ),
        "strict_time_threshold_at_this_size": threshold_time,
        "limiting_submission_id": limiter["id"] if limiter else None,
        "limiting_submission_coordinates": (
            {
                "time_ratio": limiter["metrics"]["balanced_time_ratio"],
                "compressed_pct": limiter["metrics"]["mean_file_compression_pct"],
            } if limiter else None
        ),
        "required_relative_time_vs_361_strictly_below": None,
        "speed_gain_vs_this_projection_pct_strictly_greater_than": (
            100 * (1 - threshold_time / time_ratio)
            if threshold_time is not None and time_ratio > threshold_time else 0.0
        ),
        "share_if_1e-6_faster_than_threshold_pct": (
            100 * scorer.local_global_improvement_space_log_weights(
                scorer.pareto_front(
                    points + [scorer.Point(name + "-epsilon", threshold_time - 1e-6, compressed_pct)]
                ), bounds
            ).get(name + "-epsilon", 0.0)
            if threshold_time is not None and threshold_time > 1e-6 else None
        ),
    }


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--snapshot", type=Path, default=DEFAULT_SNAPSHOT)
    parser.add_argument("--competition", type=Path, default=DEFAULT_COMPETITION)
    parser.add_argument("--leaderboard", type=Path, default=DEFAULT_LEADERBOARD)
    parser.add_argument("--weights", type=Path, default=DEFAULT_WEIGHTS)
    parser.add_argument("--receipt", type=Path, default=DEFAULT_RECEIPT)
    parser.add_argument("--source-status", type=Path, default=DEFAULT_SOURCES)
    parser.add_argument("--round9-summary", type=Path, default=DEFAULT_ROUND9)
    parser.add_argument("--output", type=Path, default=DEFAULT_OUTPUT)
    parser.add_argument(
        "--candidate", nargs=3, action="append", metavar=("NAME", "TIME_RATIO", "COMPRESSED_PCT"),
        help="Replay an additional candidate already expressed on the official scoring axes; repeatable.",
    )
    args = parser.parse_args()

    pages = load_json(args.snapshot)
    competition = load_json(args.competition)
    snapshot_id = str(competition["current_snapshot_id"])
    rows = page_rows(pages, "items", "id", snapshot_id)
    if str(pages[0]["context"].get("snapshot_id")) != snapshot_id:
        raise ValueError("competition current_snapshot_id does not match Pareto pages")
    leaderboard_pages = load_json(args.leaderboard)
    leaderboard_rows = page_rows(leaderboard_pages, "ranking", "hotkey", snapshot_id)
    weights_current = load_json(args.weights)
    weights_same_snapshot = str(weights_current.get("context", {}).get("snapshot_id")) == snapshot_id

    policy = competition["policy"]
    bounds = type("PublishedBounds", (), {
        "time_s": float(policy["max_balanced_time_ratio"]),
        "ratio_pct": float(policy["max_mean_file_compression_pct"]),
    })()
    scorer = load_scorer(SCORER_PATH)
    frontier = [row for row in rows if (row.get("score") or {}).get("on_frontier")]
    points = [
        scorer.Point(row["id"], row["metrics"]["balanced_time_ratio"],
                     row["metrics"]["mean_file_compression_pct"])
        for row in frontier
    ]
    replayed_weights = scorer.local_global_improvement_space_log_weights(
        scorer.pareto_front(points), bounds
    )
    replay_error = max(
        abs(replayed_weights[row["id"]] - row["score"]["pareto_weight"])
        for row in frontier
    ) if frontier else 0.0

    round9 = load_json(args.round9_summary)
    scalar = next(row for row in round9["candidates"] if row["candidate"] == "r9-block-scalar")
    runs = scalar["runs"]
    relative_mean = statistics.mean(
        statistics.mean(run["relative_times"]) for run in runs
    )
    relative_worst = max(value for run in runs for value in run["relative_times"])
    public_361_pct = scalar["public_size_pct"] - scalar["public_size_change_pp"]
    anchor = next(row for row in rows if str(row["id"]) == "361")
    anchor_time = float(anchor["metrics"]["balanced_time_ratio"])
    anchor_size = float(anchor["metrics"]["mean_file_compression_pct"])
    family_time = anchor_time * relative_mean
    family_size = anchor_size * scalar["public_size_pct"] / public_361_pct
    conservative_time = anchor_time * relative_worst * 1.02
    conservative_size = max(family_size + 0.01, scalar["public_size_pct"] * 1.008)

    candidate_results = [
        geometry("round9-scalar-361-calibrated", family_time, family_size, frontier,
                 points, scorer, bounds),
        geometry("round9-scalar-conservative", conservative_time, conservative_size, frontier,
                 points, scorer, bounds),
    ]
    for result in candidate_results:
        threshold = result["strict_time_threshold_at_this_size"]
        result["required_relative_time_vs_361_strictly_below"] = (
            threshold / anchor_time if threshold is not None else None
        )
        result["calibration_anchor_submission_id"] = "361"
    for name, x_text, y_text in args.candidate or []:
        x, y = float(x_text), float(y_text)
        candidate_results.append(geometry(name, x, y, frontier, points, scorer, bounds))
        threshold = candidate_results[-1]["strict_time_threshold_at_this_size"]
        candidate_results[-1]["required_relative_time_vs_361_strictly_below"] = (
            threshold / anchor_time if threshold is not None else None
        )
        candidate_results[-1]["calibration_anchor_submission_id"] = "361"

    near = [
        row for row in frontier
        if 0.95 <= row["metrics"]["balanced_time_ratio"] <= 1.55
        and 34.14 <= row["metrics"]["mean_file_compression_pct"] <= 34.24
    ]
    near.sort(key=lambda row: row["metrics"]["balanced_time_ratio"])
    near = [{
        "id": row["id"],
        "time_ratio": row["metrics"]["balanced_time_ratio"],
        "compressed_pct": row["metrics"]["mean_file_compression_pct"],
        "frontier_order": row["frontier_order"],
        "official_pareto_share_pct": 100 * row["score"]["pareto_weight"],
        "kind": row["kind"],
        "baseline_name": row["baseline_name"],
    } for row in near]
    leaderboard_top = [{
        "rank": row["rank"],
        "hotkey": row["hotkey"],
        "submission_ids": row["submission_ids"],
        "pareto_weight_pct": 100 * row["pareto_weight"],
        "improvement_weight_pct": 100 * row["improvement_weight"],
        "combined_weight_pct": 100 * row["combined_weight"],
        "payable_weight_pct": 100 * row["payable_weight"],
    } for row in sorted(leaderboard_rows, key=lambda row: row["rank"])[:10]]

    source_status = load_json(args.source_status) if args.source_status.exists() else None
    receipt = load_json(args.receipt)
    source_hashes = {
        "official_response_manifest": args.receipt.relative_to(ROOT).as_posix(),
        "pareto_pages_sha256": sha256(args.snapshot),
        "competition_json_sha256": sha256(args.competition),
        "leaderboard_pages_sha256": sha256(args.leaderboard),
        "weights_snapshot_sha256": sha256(args.weights),
        "official_scorer_file_sha256": sha256(SCORER_PATH),
    }
    if args.source_status.exists():
        source_hashes["source_availability_sha256"] = sha256(args.source_status)
    result = {
        "status": "OFFICIAL_SNAPSHOT_REPLAYED_WITH_LOCAL_SCORER",
        "snapshot": {
            "snapshot_id": snapshot_id,
            "computed_at": pages[0]["context"].get("computed_at"),
            "policy_version": pages[0]["context"].get("policy_version"),
            "freshness": pages[0]["context"].get("freshness"),
            "freshness_reason": pages[0]["context"].get("freshness_reason"),
            "retrieval_start_utc": receipt.get("retrieval_start_utc"),
            "retrieval_end_utc": receipt.get("retrieval_end_utc"),
            "time_note": receipt.get("time_evidence"),
            "capture_receipt": args.receipt.relative_to(ROOT).as_posix(),
        },
        "official_policy": policy,
        "score_replay": {
            "pareto_rows": len(rows),
            "leaderboard_hotkeys": len(leaderboard_rows),
            "official_frontier_points": len(frontier),
            "local_scorer_replay_max_abs_weight_error": replay_error,
            "formula_source": SCORER_PATH.relative_to(ROOT).as_posix(),
            "formula_source_sha256": source_hashes["official_scorer_file_sha256"],
            "deployment_code_match": "UNKNOWN",
        },
        "current_weights_snapshot": {
            key: weights_current.get(key)
            for key in ("payable_competition_weight", "unpaid_competition_weight", "competition_share",
                        "weight_set_id", "dry_run", "chain_accepted")
        },
        "current_weights_context": weights_current.get("context"),
        "weights_same_snapshot": weights_same_snapshot,
        "leaderboard_top_10": leaderboard_top,
        "anchor_361": {
            "metrics": anchor["metrics"],
            "score": anchor["score"],
            "admission": anchor.get("admission"),
        },
        "round9_scalar_block1_calibration": {
            "candidate": scalar["candidate"],
            "rust_source_sha256": scalar["source_sha256"],
            "public_compressed_pct": scalar["public_size_pct"],
            "paired_public_361_compressed_pct": public_361_pct,
            "public_compression_ratio_to_361": scalar["public_size_pct"] / public_361_pct,
            "relative_time_by_run": [
                {"run_id": run["run_id"], "relative_times": run["relative_times"]}
                for run in runs
            ],
            "relative_time_mean": relative_mean,
            "relative_time_worst_observed": relative_worst,
            "same_family_projection": candidate_results[0],
            "conservative_projection": candidate_results[1],
            "conservative_scenario_definition": {
                "time": "current #361 time ratio x worst of the four observed scalar/public361 block ratios x 1.02",
                "size": "max(same-family size + 0.01 percentage point, public scalar size x 1.008)",
                "interpretation": "stress scenario, not a confidence interval or held-out-set guarantee",
            },
            "verified_source_proof_pairs": scalar.get("verified_source_proof_pairs", []),
        },
        "near_balanced_frontier": near,
        "candidate_replays": candidate_results,
        "source_availability_probes": source_status,
        "evidence_hashes": source_hashes,
        "limits": [
            "API freshness is unknown; snapshot records a scoring pass and does not prove the current live validator deployment is byte-identical.",
            "Candidate projections and conditional Pareto shares are inferred from public stage-1 measurements; private stage-2 results, admission and actual rewards remain unknown.",
            "weights/current is separately timed and may use a newer snapshot; its chain_accepted field is reported without inferring realized emissions.",
            "The official leaderboard and weights are snapshot scoring outputs, not a promise of future payment to a candidate.",
        ],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({
        "snapshot_id": snapshot_id,
        "pareto_rows": len(rows),
        "leaderboard_hotkeys": len(leaderboard_rows),
        "frontier_points": len(frontier),
        "scorer_replay_max_abs_weight_error": replay_error,
        "candidate_replays": [{key: row.get(key) for key in (
            "name", "time_ratio", "compressed_pct", "on_geometric_frontier", "dominating_ids",
            "strict_time_threshold_at_this_size", "limiting_submission_id",
            "required_relative_time_vs_361_strictly_below",
            "speed_gain_vs_this_projection_pct_strictly_greater_than",
            "conditional_pareto_share_pct", "share_if_1e-6_faster_than_threshold_pct",
        )} for row in candidate_results],
        "output": args.output.relative_to(ROOT).as_posix() if args.output.is_relative_to(ROOT) else str(args.output),
    }, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
