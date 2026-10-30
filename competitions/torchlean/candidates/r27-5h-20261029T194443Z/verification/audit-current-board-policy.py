#!/usr/bin/env python3
"""Replay saved current board policy plans using the new official benchmark identity.

Only reads pinned Config.plan source and saved official receipts. Writes a compact receipt in
this verification folder; it does not fetch APIs, compile code, or mutate the competition state.
"""
from __future__ import annotations

import copy
import hashlib
import importlib.util
import json
from pathlib import Path
import sys
from typing import Any

HERE = Path(__file__).resolve().parent
ROUND = HERE.parent
ROOT = ROUND.parents[3]
STATE = ROUND / "competition-state"
sys.dont_write_bytecode = True


def read(path: Path) -> tuple[dict[str, Any], bytes, str]:
    data = path.read_bytes()
    value = json.loads(data.decode("utf-8-sig"))
    if not isinstance(value, dict):
        raise ValueError(f"expected JSON object: {path}")
    return value, data, hashlib.sha256(data).hexdigest()


def main() -> int:
    r26 = ROOT / "competitions/torchlean/candidates/r26-1h-20261029T085515Z/verification/analyze-native-only.py"
    spec = importlib.util.spec_from_file_location("r27_current_policy_pinned", r26)
    if spec is None or spec.loader is None:
        raise ValueError("pinned analyzer could not be loaded")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    _, modules, pins = module.r25_tools()
    config = modules["config"]

    old_replay, _, old_replay_sha = read(STATE / "exact-report-policy-replay.json")
    boards_doc, boards_bytes, boards_sha = read(STATE / "boards-2150.raw")
    current_results, _, _ = read(ROUND / "CI-RESULTS-BATCH4.json")
    current_report, _, current_report_sha = read(STATE / "submission43-report.raw")
    version, _, version_sha = read(STATE / "official-current-version-check.json")
    new_benchmark_identity = current_results.get("benchmark_identity")
    current_proof_identity = current_results.get("proof_identity")
    current_submission = current_report.get("submission", {}).get("id")
    board_by_id = {x.get("id"): x for x in boards_doc.get("boards", []) if isinstance(x, dict)}
    current_eval = next((x for x in current_report.get("evaluations", []) if x.get("board") == "normalized_mlp"), {})
    current_measurements = current_eval.get("measurements", [])
    actual_workloads = current_measurements[0].get("workloads", []) if current_measurements else []
    report_seed = current_measurements[0].get("seed") if current_measurements else None
    run_contract = []
    normalized_plan = None

    rows = []
    for old in old_replay.get("rows", []):
        board = old.get("board")
        plan = copy.deepcopy(old.get("report_plan", {}))
        plan["benchmark_identity"] = new_benchmark_identity
        if board == "normalized_mlp":
            normalized_plan = copy.deepcopy(plan)
        actual_hash = config.digest(plan)
        current_board = board_by_id.get(board, {})
        negative = copy.deepcopy(plan)
        negative["strata"][0]["timing"]["build_seconds"] += 1
        negative_hash = config.digest(negative)
        rows.append({
            "board": board,
            "initial_current_submission": old.get("current_submission"),
            "replayed_plan_hash": actual_hash,
            "current_live_board_hash": current_board.get("config_hash"),
            "matches_live_board_hash": actual_hash == current_board.get("config_hash"),
            "negative_control_build_limit_rejected": negative_hash != actual_hash,
            "proof_identity": plan.get("proof_identity"),
            "benchmark_identity": plan.get("benchmark_identity"),
            "benchmark_identity_matches_current_runtime": plan.get("benchmark_identity") == new_benchmark_identity,
            "seed_mode": plan.get("seed_mode"),
            "cells": len(plan.get("cells", {})),
            "environments": [x.get("environment") for x in plan.get("strata", [])],
            "current_report_config_hash": current_eval.get("config_hash") if board == "normalized_mlp" else None,
            "current43_report_matches_replayed_live_board_hash": (
                board == "normalized_mlp" and current_eval.get("config_hash") == actual_hash == current_board.get("config_hash")
            ) if board == "normalized_mlp" else None,
        })

    if normalized_plan is not None:
        measurements_by_env = {m.get("environment"): m for m in current_measurements}
        env_weight_by_id = {x.get("id"): x.get("weight") for x in board_by_id["normalized_mlp"].get("environments", [])}
        for stratum in normalized_plan.get("strata", []):
            environment = stratum.get("environment")
            measured = measurements_by_env.get(environment, {})
            timing = stratum.get("timing", normalized_plan.get("timing"))
            run_contract.append({
                "environment": environment,
                "identity": stratum.get("identity"),
                "seed": measured.get("seed"),
                "state": measured.get("state"),
                "attempts": measured.get("attempts"),
                "repetition_count": len(measured.get("repetitions", {})),
                "round_count": len(measured.get("rounds", [])),
                "weight": env_weight_by_id.get(environment),
                "timing": timing,
            })
        normalized_plan["resolved_report_run_contract"] = run_contract

    result = {
        "round": "R27",
        "boards_path": "competitions/torchlean/candidates/r27-5h-20261029T194443Z/competition-state/boards-2150.raw",
        "boards_sha256": boards_sha,
        "boards_bytes": len(boards_bytes),
        "initial_policy_replay_path": "competitions/torchlean/candidates/r27-5h-20261029T194443Z/competition-state/exact-report-policy-replay.json",
        "initial_policy_replay_sha256": old_replay_sha,
        "helper_run": current_results.get("run"),
        "helper_run_plan_sha256": "0413b9499f208dd217629ed78cb5513542b6f196454d020d7b091e6d96ff9932",
        "official_old_head": version.get("old_commit"),
        "official_current_head": version.get("new_commit"),
        "version_check_sha256": version_sha,
        "current_benchmark_identity": new_benchmark_identity,
        "current_proof_identity": current_proof_identity,
        "pinned_config": pins["config.py"],
        "rows": rows,
        "current43_report": {
            "submission": current_submission,
            "report_sha256": current_report_sha,
            "config_hash": current_eval.get("config_hash"),
            "benchmark_identity_exposed_by_report": any("benchmark_identity" in x for x in current_report.get("evaluations", [])),
            "initial_reference": normalized_plan.get("initial_reference") if normalized_plan else None,
            "seed_mode": normalized_plan.get("seed_mode") if normalized_plan else None,
            "proof_identity": normalized_plan.get("proof_identity") if normalized_plan else None,
            "benchmark_identity_inferred_from_current_official_head": new_benchmark_identity,
            "cells": normalized_plan.get("cells") if normalized_plan else None,
            "timing": normalized_plan.get("timing") if normalized_plan else None,
            "admission": normalized_plan.get("admission") if normalized_plan else None,
            "report_seed": report_seed,
            "report_workloads": actual_workloads,
            "resolved_run_contract": run_contract,
            "replayed_plan_hash": next((x.get("replayed_plan_hash") for x in rows if x.get("board") == "normalized_mlp"), None),
            "live_board_hash_matches_report_plan": next((x.get("current43_report_matches_replayed_live_board_hash") for x in rows if x.get("board") == "normalized_mlp"), False),
        },
        "classification": "RECONSTRUCTED_LIVE_BOARD_POLICY_WITH_NEW_BENCHMARK_IDENTITY; REPORT_BENCHMARK_IDENTITY_INFERRED_FROM_CURRENT_OFFICIAL_HEAD",
        "limitations": "Old #23/#12 score used the previous benchmark identity; this replay does not retroactively make cross-version performance products exact. New candidate/current conversion must use current head and exact current report inputs.",
        "failures": [
            f"{x['board']}: live board config hash mismatch" for x in rows if not x["matches_live_board_hash"]
        ] + [
            f"{x['board']}: negative control was not rejected" for x in rows if not x["negative_control_build_limit_rejected"]
        ],
    }
    out = HERE / "current-board-policy-replay.json"
    out.write_text(json.dumps(result, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    print(json.dumps({"rows": len(rows), "live_board_matches": sum(x["matches_live_board_hash"] for x in rows), "current43_report_matches": result["current43_report"]["config_hash"] == next((x["replayed_plan_hash"] for x in rows if x["board"] == "normalized_mlp"), None), "failures": result["failures"]}, ensure_ascii=False))
    return 0 if len(rows) == 6 and not result["failures"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
