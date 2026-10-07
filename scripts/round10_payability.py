"""Project a point's Pareto share and apply the official same-hotkey payability rule.

The pure helper accepts flat official Pareto rows and the public scorer module. It
does not infer admission, registration, bounty, or on-chain acceptance for a future
submission; all candidate payout fields are conditional on those gates.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import sys
from pathlib import Path
from typing import Any

ROOT = Path(__file__).resolve().parents[1]
PRIMARY = ROOT / "evidence/round10/official-mid-payability"
HISTORICAL = ROOT / "evidence/round10/official-start"
SCORER_PATH = ROOT / "sources/conjectures-optimisation-deflate/validator/scoring/pareto.py"
COMBINE_PATH = ROOT / "sources/conjectures-optimisation-deflate/validator/scoring/combine.py"
SCORING_DOC = ROOT / "sources/conjectures-optimisation-deflate/docs/SCORING.md"
DEFAULT_OUTPUT = ROOT / "evidence/round10/payability-start.json"


def load_json(path: Path) -> Any:
    return json.loads(path.read_bytes())


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def load_official_scorer():
    """Load the repository's pure official Pareto source, avoiding package services."""
    sys.path.insert(0, str(ROOT / "scripts"))
    from round3 import load_scorer

    return load_scorer(SCORER_PATH)


def _id_key(row: dict[str, Any]) -> tuple[str, int | str]:
    submission_id = str(row.get("id", ""))
    numeric_id: int | str = int(submission_id) if submission_id.isdigit() else submission_id
    return str(row.get("submitted_at", "")), numeric_id


def analyze_payability(
    rows: list[dict[str, Any]],
    time_ratio: float,
    compressed_pct: float,
    reference_submission_id: str | int,
    scorer: Any,
    *,
    candidate_name: str = "__round10_hypothetical_future__",
    pareto_share: float = 1.0,
    improvement_share: float = 0.0,
) -> dict[str, Any]:
    """Return official geometry and conditional payout ownership for a future point.

    `rows` are flat submissions from one official Pareto snapshot. The hypothetical
    submission is assumed newer than every existing row. Its hotkey is modeled twice:
    the reference submission's hotkey, and a fresh independent eligible hotkey.
    """
    if not rows:
        raise ValueError("rows must contain the reference submission")
    if improvement_share != 0:
        raise ValueError("This helper models frontier-only payment; nonzero improvement share needs separate replay")
    ids = [str(row["id"]) for row in rows]
    if len(ids) != len(set(ids)):
        raise ValueError("duplicate submission ids")
    if candidate_name in ids:
        raise ValueError("candidate_name collides with an existing submission id")
    reference = next((row for row in rows if str(row["id"]) == str(reference_submission_id)), None)
    if reference is None:
        raise ValueError(f"reference submission {reference_submission_id} is missing")
    ref_metrics = reference["metrics"]
    ref_bounds = reference.get("bounds") or {}
    max_time = float(ref_bounds.get("max_balanced_time_ratio", 10.0))
    max_size = float(ref_bounds.get("max_mean_file_compression_pct", 40.0))
    bounds = scorer.Boundaries(max_time, max_size)
    in_bounds = 0 < time_ratio <= max_time and 0 < compressed_pct <= max_size

    # Current API rows identify the official accepted geometric frontier. Points
    # already dominated can never re-enter it when one more point is added.
    frontier_rows = [
        row for row in rows if (row.get("score") or {}).get("on_frontier") is True
    ]
    frontier_points = [
        scorer.Point(
            name=str(row["id"]),
            time_s=float(row["metrics"]["balanced_time_ratio"]),
            ratio_pct=float(row["metrics"]["mean_file_compression_pct"]),
        )
        for row in frontier_rows
    ]
    base_front = scorer.pareto_front(frontier_points)
    base_weights = scorer.local_global_improvement_space_log_weights(base_front, bounds)
    replay_error = max((
        abs(base_weights.get(str(row["id"]), 0.0) * pareto_share
            - float((row.get("score") or {}).get("pareto_weight", 0.0)))
        for row in frontier_rows
    ), default=0.0)

    weak_dominators = [p for p in frontier_points if p.time_s <= time_ratio and p.ratio_pct <= compressed_pct]
    candidate_point = scorer.Point(candidate_name, float(time_ratio), float(compressed_pct))
    updated_front = scorer.pareto_front(
        frontier_points + ([candidate_point] if in_bounds and not weak_dominators else [])
    )
    updated_ids = {point.name for point in updated_front}
    updated_weights = scorer.local_global_improvement_space_log_weights(updated_front, bounds)
    candidate_on_frontier = in_bounds and candidate_name in updated_ids
    geometry_fraction = (
        float(updated_weights.get(candidate_name, 0.0)) * pareto_share
        if candidate_on_frontier else 0.0
    )

    reference_hotkey = reference.get("hotkey")
    current_same_hotkey_frontier = [
        row for row in frontier_rows if reference_hotkey is not None and row.get("hotkey") == reference_hotkey
    ]
    surviving_same_hotkey = [
        row for row in current_same_hotkey_frontier if str(row["id"]) in updated_ids
    ]
    surviving_same_hotkey.sort(key=_id_key)
    older_surviving_ids = [str(row["id"]) for row in surviving_same_hotkey]
    oldest_survivor = surviving_same_hotkey[0] if surviving_same_hotkey else None
    old_hotkey_share = (
        float(updated_weights.get(str(oldest_survivor["id"]), 0.0)) * pareto_share
        if oldest_survivor else 0.0
    )

    dominators = [
        row for row in frontier_rows
        if float(row["metrics"]["balanced_time_ratio"]) <= time_ratio
        and float(row["metrics"]["mean_file_compression_pct"]) <= compressed_pct
        and (
            float(row["metrics"]["balanced_time_ratio"]) < time_ratio
            or float(row["metrics"]["mean_file_compression_pct"]) < compressed_pct
        )
    ]
    candidate_dominated_existing = [
        str(row["id"]) for row in frontier_rows
        if time_ratio <= float(row["metrics"]["balanced_time_ratio"])
        and compressed_pct <= float(row["metrics"]["mean_file_compression_pct"])
        and (
            time_ratio < float(row["metrics"]["balanced_time_ratio"])
            or compressed_pct < float(row["metrics"]["mean_file_compression_pct"])
        )
    ] if in_bounds else []

    # combine.score chooses the oldest point for a hotkey after assigning geometric
    # weights. With improvement_share=0, a duplicate frontier point adds no weight.
    same_hotkey_increment = geometry_fraction if not older_surviving_ids else 0.0
    return {
        "reference_submission_id": str(reference["id"]),
        "reference_on_current_frontier": bool((reference.get("score") or {}).get("on_frontier")),
        "reference_metrics": {
            "time_ratio": float(ref_metrics["balanced_time_ratio"]),
            "compressed_pct": float(ref_metrics["mean_file_compression_pct"]),
        },
        "reference_snapshot_score": {
            key: (reference.get("score") or {}).get(key)
            for key in ("pareto_weight", "payable_weight", "payment_eligible", "unpaid_reason", "bounty_capped")
        },
        "candidate": {
            "name": candidate_name,
            "time_ratio": float(time_ratio),
            "compressed_pct": float(compressed_pct),
            "within_published_scoring_bounds": in_bounds,
            "on_updated_geometric_frontier": candidate_on_frontier,
            "dominating_existing_frontier_ids": [str(row["id"]) for row in dominators],
            "existing_frontier_ids_dominated_by_candidate": candidate_dominated_existing,
            "geometric_share_fraction_of_competition_pareto_pool": geometry_fraction,
            "geometric_share_pct_of_competition_pareto_pool": 100 * geometry_fraction,
        },
        "same_hotkey_payability_if_admission_registration_and_bounty_remain_eligible": {
            "older_same_hotkey_frontier_ids_surviving": older_surviving_ids,
            "oldest_surviving_same_hotkey_id": str(oldest_survivor["id"]) if oldest_survivor else None,
            "oldest_survivor_updated_geometric_share_fraction": old_hotkey_share,
            "candidate_additional_share_fraction": same_hotkey_increment,
            "candidate_additional_share_pct": 100 * same_hotkey_increment,
            "reason": (
                "candidate is outside the current geometric frontier or published bounds"
                if not candidate_on_frontier else
                "older_same_hotkey_frontier_point_survives; duplicate-hotkey Pareto allocation is unpaid"
                if older_surviving_ids else
                "no older same-hotkey frontier point survives; candidate would be the hotkey's oldest frontier point"
            ),
        },
        "independent_eligible_hotkey_conditional_share": {
            "assumption": "fresh distinct hotkey with no older frontier submission, admitted, registered, and below bounty cap",
            "share_fraction_of_competition_pareto_pool": geometry_fraction,
            "share_pct_of_competition_pareto_pool": 100 * geometry_fraction,
        },
        "assumptions": {
            "hypothetical_submission_is_newer_than_all_snapshot_rows": True,
            "improvement_share": 0.0,
            "actual_admission_registration_bounty_and_chain_payment": "UNKNOWN; not inferred by this helper",
        },
        "scorer_replay": {
            "current_frontier_points": len(frontier_rows),
            "max_abs_current_weight_replay_error": replay_error,
        },
    }


def load_flat_rows(root: Path) -> tuple[dict[str, Any], dict[str, Any], list[dict[str, Any]]]:
    competition = load_json(root / "competition.json")
    pages = load_json(root / "pareto-pages.json")
    snapshot_id = str(competition["current_snapshot_id"])
    if not pages or any(str(page.get("context", {}).get("snapshot_id")) != snapshot_id for page in pages):
        raise ValueError("Pareto pages do not share the competition current_snapshot_id")
    if pages[-1].get("next_cursor"):
        raise ValueError("Pareto pagination is incomplete")
    rows = [row for page in pages for row in page["items"]]
    if len({str(row["id"]) for row in rows}) != len(rows):
        raise ValueError("duplicate submission ids across Pareto pages")
    return competition, pages[0]["context"], rows


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--capture", type=Path, default=PRIMARY)
    parser.add_argument("--historical-capture", type=Path, default=HISTORICAL)
    parser.add_argument("--reference", default="453")
    parser.add_argument("--output", type=Path, default=DEFAULT_OUTPUT)
    args = parser.parse_args()
    args.capture = args.capture.resolve()
    args.historical_capture = args.historical_capture.resolve()
    args.output = args.output.resolve()

    scorer = load_official_scorer()
    competition, context, rows = load_flat_rows(args.capture)
    policy = competition["policy"]
    historical_competition, historical_context, historical_rows = load_flat_rows(args.historical_capture)
    ref = next(row for row in rows if str(row["id"]) == str(args.reference))
    ref_time = float(ref["metrics"]["balanced_time_ratio"])
    ref_size = float(ref["metrics"]["mean_file_compression_pct"])

    candidate_case = analyze_payability(rows, 1.25, 34.18, args.reference, scorer,
                                        pareto_share=float(policy["pareto_share"]))
    synthetic_margin = 0.001
    synthetic_case = analyze_payability(
        rows, ref_time - synthetic_margin, ref_size - synthetic_margin,
        args.reference, scorer, pareto_share=float(policy["pareto_share"]),
        candidate_name="__synthetic_strictly_dominates_453__",
    )
    historical_ref = next(row for row in historical_rows if str(row["id"]) == str(args.reference))
    primary_receipt = load_json(args.capture / "receipt.json")
    historical_receipt = load_json(args.historical_capture / "receipt.json")
    weights = load_json(args.capture / "weights-current.json")
    results = {
        "status": "OFFICIAL_PAYABILITY_RULE_REPLAYED_CONDITIONALLY",
        "primary_snapshot": {
            "snapshot_id": context["snapshot_id"],
            "computed_at": context.get("computed_at"),
            "freshness": context.get("freshness"),
            "freshness_reason": context.get("freshness_reason"),
            "pareto_rows": len(rows),
            "receipt_path": args.capture.relative_to(ROOT).as_posix(),
            "pareto_pages_sha256": sha256(args.capture / "pareto-pages.json"),
            "receipt_sha256": sha256(args.capture / "receipt.json"),
        },
        "historical_start_snapshot": {
            "snapshot_id": historical_context["snapshot_id"],
            "computed_at": historical_context.get("computed_at"),
            "freshness": historical_context.get("freshness"),
            "pareto_rows": len(historical_rows),
            "receipt_path": args.historical_capture.relative_to(ROOT).as_posix(),
            "receipt_sha256": sha256(args.historical_capture / "receipt.json"),
            "reference_453": {
                "on_frontier": (historical_ref.get("score") or {}).get("on_frontier"),
                "pareto_weight": (historical_ref.get("score") or {}).get("pareto_weight"),
                "payable_weight": (historical_ref.get("score") or {}).get("payable_weight"),
                "time_ratio": historical_ref["metrics"]["balanced_time_ratio"],
                "compressed_pct": historical_ref["metrics"]["mean_file_compression_pct"],
            },
        },
        "official_policy": policy,
        "official_sources": {
            "scoring_docs": "sources/conjectures-optimisation-deflate/docs/SCORING.md",
            "combine_score": "sources/conjectures-optimisation-deflate/validator/scoring/combine.py:score",
            "pareto_score": "sources/conjectures-optimisation-deflate/validator/scoring/frontier.py:score_frontier",
            "pareto_scorer_sha256": sha256(SCORER_PATH),
            "combine_source_sha256": sha256(COMBINE_PATH),
            "scoring_docs_sha256": sha256(SCORING_DOC),
            "combine_rule": "Score geometry first; choose oldest frontier submission per hotkey by (submitted_at, submission_id); later same-hotkey frontier submissions get zero Pareto payable weight when improvement_share=0.",
        },
        "primary_capture": {
            "retrieval_start_utc": primary_receipt.get("retrieval_start_utc"),
            "retrieval_end_utc": primary_receipt.get("retrieval_end_utc"),
            "weights_same_snapshot": primary_receipt.get("weights_same_snapshot"),
            "weights_context_snapshot_id": primary_receipt.get("weights_context", {}).get("snapshot_id"),
        },
        "historical_start_capture": {
            "retrieval_start_utc": historical_receipt.get("retrieval_start_utc"),
            "retrieval_end_utc": historical_receipt.get("retrieval_end_utc"),
            "weights_same_snapshot": historical_receipt.get("weights_same_snapshot"),
            "weights_context_snapshot_id": historical_receipt.get("weights_context", {}).get("snapshot_id"),
        },
        "weights_current_scope": {
            "weights_snapshot_id": (weights.get("context") or {}).get("snapshot_id"),
            "score_snapshot_id": context["snapshot_id"],
            "same_snapshot": primary_receipt.get("weights_same_snapshot"),
            "chain_accepted": weights.get("chain_accepted"),
            "interpretation": "Not joined to the Pareto score snapshot; actual on-chain acceptance for the primary score snapshot remains UNKNOWN.",
        },
        "reference_453": {
            "time_ratio": ref_time,
            "compressed_pct": ref_size,
            "same_hotkey_projection_reference_id": str(ref["id"]),
            "current_score": candidate_case["reference_snapshot_score"],
            "current_frontier_peer_ids_for_same_hotkey": [
                str(row["id"]) for row in rows
                if row.get("hotkey") == ref.get("hotkey") and (row.get("score") or {}).get("on_frontier")
            ],
        },
        "scenarios": {
            "equilibrium_candidate_1_25_34_18": candidate_case,
            "synthetic_point_that_strictly_dominates_453": {
                "coordinates": {"time_ratio": ref_time - synthetic_margin, "compressed_pct": ref_size - synthetic_margin},
                "is_synthetic_not_a_real_submission": True,
                "result": synthetic_case,
            },
        },
        "eligibility_boundary": {
            "admission": "UNKNOWN for a future point; both conditional shares assume it passes.",
            "registration": "UNKNOWN for a future point; do not infer an authorized hotkey or identity from public #453 metadata.",
            "bounty": "UNKNOWN for a future (hotkey, submission) pair; both conditional shares assume it is uncapped.",
            "wallet_chain_or_submission_actions": "Not accessed or performed.",
        },
        "limits": [
            "Pareto weights are competition-local geometric allocations; conditional share is not a formal admission result or realized reward.",
            "Freshness is API-reported unknown; the public policy snapshot does not prove live validator deployment identity.",
            "weights/current is from a different snapshot than the primary Pareto pages and is not used to infer current-chain acceptance.",
            "Exact same-hotkey payability after admission is applied by combine.score; missing registration, bounty cap, or other eligibility still burns the allocation without renormalizing.",
        ],
    }
    args.output.write_bytes((json.dumps(results, ensure_ascii=False, indent=2) + "\n").encode("utf-8"))
    print(json.dumps({
        "status": results["status"],
        "snapshot_id": context["snapshot_id"],
        "reference_453": {"time_ratio": ref_time, "compressed_pct": ref_size,
                          "pareto_weight": (ref.get("score") or {}).get("pareto_weight"),
                          "payable_weight": (ref.get("score") or {}).get("payable_weight")},
        "candidate_1_25_34_18": {
            "on_frontier": candidate_case["candidate"]["on_updated_geometric_frontier"],
            "geometry_share_pct": candidate_case["candidate"]["geometric_share_pct_of_competition_pareto_pool"],
            "same_hotkey_old_front_ids": candidate_case["same_hotkey_payability_if_admission_registration_and_bounty_remain_eligible"]["older_same_hotkey_frontier_ids_surviving"],
            "same_hotkey_increment_pct": candidate_case["same_hotkey_payability_if_admission_registration_and_bounty_remain_eligible"]["candidate_additional_share_pct"],
            "independent_hotkey_conditional_pct": candidate_case["independent_eligible_hotkey_conditional_share"]["share_pct_of_competition_pareto_pool"],
        },
        "synthetic_dominates_453": {
            "coordinates": results["scenarios"]["synthetic_point_that_strictly_dominates_453"]["coordinates"],
            "on_frontier": synthetic_case["candidate"]["on_updated_geometric_frontier"],
            "old_same_hotkey_front_ids": synthetic_case["same_hotkey_payability_if_admission_registration_and_bounty_remain_eligible"]["older_same_hotkey_frontier_ids_surviving"],
            "same_hotkey_increment_pct": synthetic_case["same_hotkey_payability_if_admission_registration_and_bounty_remain_eligible"]["candidate_additional_share_pct"],
            "independent_hotkey_conditional_pct": synthetic_case["independent_eligible_hotkey_conditional_share"]["share_pct_of_competition_pareto_pool"],
        },
        "weights_same_snapshot": primary_receipt.get("weights_same_snapshot"),
        "output": args.output.relative_to(ROOT).as_posix(),
    }, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
