#!/usr/bin/env python3
"""Convert fixed-scorer board ratios into current-champion time multipliers.

This is a small postprocessor, not a benchmark scorer. Its input ratios must
come from the unchanged pinned scorer and its calibration must bind the live
current promotion and compatible board config. Missing or mismatched evidence
stays UNKNOWN.
"""
from __future__ import annotations

import argparse
import json
import math
from pathlib import Path
from typing import Any

HERE = Path(__file__).resolve().parent
PINNED_SCORER_SOURCES = {
    "config.py": {
        "git_blob_sha1": "6743c5c0060b7babab5155ffe1e0dc94dbf8a742",
        "sha256": "42150b6f1e13b51d18116bb0d9b4b017904793470ae8fdcb364de614499182b5",
    },
    "multiseed.py": {
        "git_blob_sha1": "299b2e77db596a2720db3d54c2df46b3e5d2c3b3",
        "sha256": "f171929b08cce37d848e736bb1d3c0bb422daeda1bbbd0da2ba3707d43d19341",
    },
    "scoring.py": {
        "git_blob_sha1": "f5e1b500bc3976764eea0451c500907e08e17dda",
        "sha256": "8950678e5f093c9c14d82abe5b42275c122b068e81c95c106a7760a596e1baef",
    },
}


def read_json(path: Path) -> dict[str, Any]:
    value = json.loads(path.read_text(encoding="utf-8-sig"))
    if not isinstance(value, dict):
        raise ValueError(f"expected JSON object: {path}")
    return value


def finite_positive(value: Any) -> float | None:
    if isinstance(value, bool) or not isinstance(value, (int, float)):
        return None
    result = float(value)
    return result if math.isfinite(result) and result > 0 else None


def valid_sha256(value: Any) -> bool:
    return isinstance(value, str) and len(value) == 64 and all(ch in "0123456789abcdef" for ch in value)


def scorer_is_pinned(value: Any) -> bool:
    if not isinstance(value, dict):
        return False
    for name, expected in PINNED_SCORER_SOURCES.items():
        source = value.get(name)
        if not isinstance(source, dict):
            return False
        if source.get("git_blob_sha1") != expected["git_blob_sha1"] or source.get("sha256") != expected["sha256"]:
            return False
    return True


def report_runs_match(row_runs: Any, report_runs: Any) -> bool:
    """Require every official report environment with its exact identity."""
    if not isinstance(row_runs, list) or not isinstance(report_runs, list) or not report_runs:
        return False

    def signature(item: Any) -> tuple[Any, ...] | None:
        if not isinstance(item, dict):
            return None
        fields = (
            "environment",
            "identity",
            "seed",
            "state",
            "attempts",
            "repetition_count",
            "round_count",
            "weight",
        )
        values = tuple(item.get(name) for name in fields)
        if not all(value is not None for value in values):
            return None
        timing = item.get("timing")
        if not isinstance(timing, dict) or not timing:
            return None
        return values + (timing,)

    observed = [signature(item) for item in row_runs]
    expected = [signature(item) for item in report_runs]
    if any(item is None for item in observed + expected):
        return False
    observed_by_env = {item[0]: item for item in observed}
    expected_by_env = {item[0]: item for item in expected}
    return len(observed_by_env) == len(observed) and len(expected_by_env) == len(expected) and observed_by_env == expected_by_env


def analyze(candidate_doc: dict[str, Any], record: dict[str, Any]) -> dict[str, Any]:
    candidate = candidate_doc.get("candidate")
    reference = candidate_doc.get("reference")
    rows = candidate_doc.get("board_results")
    boards = record.get("boards")
    if not isinstance(candidate, dict):
        candidate = {}
    if not isinstance(reference, dict):
        reference = {}
    if not isinstance(rows, list) or not isinstance(boards, list):
        raise ValueError("board_results and champion record boards arrays are required")

    by_board = {b.get("board"): b for b in boards if isinstance(b, dict)}
    output_rows: list[dict[str, Any]] = []
    default_candidate_sha = candidate.get("sha256")
    default_reference_sha = reference.get("sha256")
    default_proof_status = candidate.get("proof_status", "UNKNOWN")
    default_guard_passed = candidate.get("guard_passed")
    pinned_scorer_ok = scorer_is_pinned(candidate_doc.get("pinned_scorer"))

    for row in rows:
        if not isinstance(row, dict):
            continue
        board = row.get("board")
        candidate_sha = row.get("candidate_sha256", default_candidate_sha)
        reference_sha = row.get("reference_sha256", default_reference_sha)
        proof_status = row.get("proof_status", default_proof_status)
        guard_passed = row.get("guard_passed", default_guard_passed)
        base = {
            "board": board,
            "candidate_sha256": candidate_sha,
            "reference_sha256": reference_sha,
            "current_board_config_hash": None,
            "scoring_config_hash": None,
            "current_promotion_id": None,
            "current_champion_source_sha256": None,
            "champion_response_sha256": None,
            "current_champion_report_sha256": None,
            "proof_status": proof_status,
            "guard_passed": guard_passed,
            "candidate_time_over_current_champion_time": None,
            "comparison_status": "UNKNOWN",
            "eligibility": "NOT_ESTABLISHED",
        }
        live = by_board.get(board)
        if live is not None:
            base["current_board_config_hash"] = live.get("board_config_hash")
        if live is None:
            output_rows.append({**base, "comparison_status": "UNKNOWN_BOARD_STATE"})
            continue

        ratio = finite_positive(row.get("candidate_time_over_reference_time"))
        if ratio is None or not valid_sha256(candidate_sha) or not valid_sha256(reference_sha):
            output_rows.append({**base, "comparison_status": "UNKNOWN_SCORER_RATIO"})
            continue
        if not pinned_scorer_ok:
            output_rows.append({**base, "comparison_status": "UNKNOWN_FIXED_SCORER_IDENTITY"})
            continue

        champion_sha = live.get("champion_source_sha256")
        current_ok = (
            live.get("current_champion_identity") == "VERIFIED_BY_CURRENT_CHAMPIONS_RESPONSE"
            and isinstance(live.get("current_promotion_id"), int)
            and not isinstance(live.get("current_promotion_id"), bool)
            and live.get("champion_promotion_id") == live.get("current_promotion_id")
            and valid_sha256(champion_sha)
            and valid_sha256(live.get("champion_response_sha256"))
            and valid_sha256(live.get("current_champion_report_sha256"))
            and valid_sha256(live.get("board_config_hash"))
        )
        if not current_ok:
            output_rows.append({**base, "comparison_status": "UNKNOWN_CURRENT_CHAMPION"})
            continue
        base.update(
            current_promotion_id=live.get("current_promotion_id"),
            current_champion_source_sha256=champion_sha,
            champion_response_sha256=live.get("champion_response_sha256"),
            current_champion_report_sha256=live.get("current_champion_report_sha256"),
        )
        snapshot_bound = (
            row.get("current_promotion_id") == live.get("current_promotion_id")
            and row.get("current_champion_source_sha256") == champion_sha
            and row.get("champion_response_sha256") == live.get("champion_response_sha256")
            and row.get("current_champion_report_sha256") == live.get("current_champion_report_sha256")
        )
        if not snapshot_bound:
            output_rows.append({**base, "comparison_status": "UNKNOWN_CURRENT_CHAMPION_SNAPSHOT_NOT_BOUND"})
            continue
        expected_seed = (live.get("current_report_benchmark_runs") or [{}])[0].get("seed")
        report_policy = live.get("current_report_policy")
        if (
            not isinstance(report_policy, dict)
            or live.get("current_report_policy_matches") is not True
            or not all(report_policy.get("checks", {}).values())
        ):
            output_rows.append({**base, "comparison_status": "UNKNOWN_CURRENT_REPORT_POLICY"})
            continue
        input_contract_matches = (
            row.get("seed") == expected_seed
            and row.get("workloads") == live.get("current_report_workloads")
            and row.get("timing") == live.get("current_report_timing")
            and row.get("cell_count") == live.get("current_report_cell_count")
            and row.get("cells") == report_policy.get("cells")
            and row.get("initial_reference") == report_policy.get("initial_reference")
            and row.get("seed_mode") == report_policy.get("seed_mode")
            and row.get("proof_identity") == report_policy.get("proof_identity")
            and row.get("benchmark_identity") == report_policy.get("benchmark_identity")
            and report_policy.get("report_config_hash") == live.get("calibration_board_config_hash")
        )
        if not input_contract_matches:
            output_rows.append({**base, "comparison_status": "UNKNOWN_CURRENT_REPORT_INPUT_MISMATCH"})
            continue
        if not report_runs_match(row.get("benchmark_runs"), live.get("current_report_benchmark_runs")):
            output_rows.append({**base, "comparison_status": "UNKNOWN_CURRENT_REPORT_ENVIRONMENT_MISMATCH"})
            continue

        if reference_sha == champion_sha:
            if live.get("champion_source_available") is not True:
                output_rows.append({**base, "comparison_status": "UNKNOWN_CURRENT_CHAMPION_SOURCE_UNAVAILABLE"})
                continue
            base["scoring_config_hash"] = live.get("board_config_hash")
            if row.get("board_config_hash") != live.get("board_config_hash"):
                output_rows.append({**base, "comparison_status": "UNKNOWN_DIRECT_PAIR_CONFIG_MISMATCH"})
                continue
            multiplier = ratio
            comparison_status = "VERIFIED_DIRECT_CURRENT_CHAMPION_PAIR"
        elif reference_sha == live.get("calibration_reference_sha256"):
            scoring_config_hash = live.get("calibration_board_config_hash")
            base["scoring_config_hash"] = scoring_config_hash
            if row.get("board_config_hash") != scoring_config_hash:
                output_rows.append({**base, "comparison_status": "UNKNOWN_CALIBRATION_CONFIG_MISMATCH"})
                continue
            calibration = live.get("candidate_reference_time_over_champion_time")
            calibration_value = finite_positive(calibration)
            if live.get("calibration_status") not in {"VERIFIED", "INFERRED"} or calibration_value is None:
                output_rows.append({**base, "comparison_status": "UNKNOWN_CALIBRATION"})
                continue
            multiplier = ratio * calibration_value
            if live.get("calibration_status") == "INFERRED":
                comparison_status = (
                    "INFERRED_REPORT_CHAIN_CONFIG_DIFFERS_FROM_LIVE_BOARD"
                    if scoring_config_hash != live.get("board_config_hash")
                    else "INFERRED_CURRENT_CHAMPION_MULTIPLIER"
                )
            else:
                comparison_status = "VERIFIED_FIXED_REFERENCE_CHAIN_MULTIPLIER"
        else:
            output_rows.append({**base, "comparison_status": "UNKNOWN_REFERENCE_IDENTITY"})
            continue

        if proof_status != "FULL_ORIGINAL_PROOF_GATE_PASS":
            eligibility = "NATIVE_ONLY_OR_PROOF_NOT_ESTABLISHED"
        elif guard_passed is not True:
            eligibility = "GUARD_NOT_PASSED_OR_UNKNOWN"
        else:
            eligibility = "PERFORMANCE_MEASURED; OFFICIAL_PROMOTION_NOT_ESTABLISHED"
        output_rows.append({
            **base,
            "candidate_time_over_current_champion_time": multiplier,
            "comparison_status": comparison_status,
            "eligibility": eligibility,
            "human_display": f"{multiplier:.6g}x current champion time",
        })

    return {
        "round": record.get("round", "UNKNOWN"),
        "metric": "candidate_time_over_current_champion_time",
        "proof_status": candidate.get("proof_status", "UNKNOWN"),
        "claim_boundary": "Performance ratio only; official current rank/promotion and candidate correctness remain separate.",
        "results": output_rows,
    }


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--candidate-ratios", type=Path, required=True)
    parser.add_argument("--champion-record", type=Path, default=HERE / "champion-only-record.json")
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    result = analyze(read_json(args.candidate_ratios), read_json(args.champion_record))
    args.output.write_text(json.dumps(result, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    print(json.dumps({"output": str(args.output), "results": len(result["results"])}))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

