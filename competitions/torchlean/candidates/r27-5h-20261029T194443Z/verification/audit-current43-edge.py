#!/usr/bin/env python3
"""Audit the saved R27 current #43 -> public #23 report edge and refresh the champion ledger.

Reads only previously saved official responses, reports, receipts and evidence. It makes no
network requests and never reads the body of the unavailable current #43 source.
"""
from __future__ import annotations

import copy
import hashlib
import importlib.util
import json
import math
from pathlib import Path
import sys
from typing import Any

HERE = Path(__file__).resolve().parent
ROUND = HERE.parent
STATE = ROUND / "competition-state"
ROOT = ROUND.parents[3]
CURRENT_BOARDS = STATE / "boards-2150.raw"
CURRENT_CHAMPIONS = STATE / "champions-normalized_mlp-2150.raw"
CURRENT_REPORT = STATE / "submission43-report.raw"
REF_SOURCE = STATE / "source-private/submission23-Kernel.lean"
VERSION_CHECK = STATE / "official-current-version-check.json"
OLD_REPORT = STATE / "submission23-report.raw"
NATIVE_AUDIT = HERE / "audit-native-40952423982.json"
HELPER_AUDIT = HERE / "audit-helper-run-40964374666.json"
CURRENT_POLICY_REPLAY = HERE / "current-board-policy-replay.json"
RECORD_PATH = HERE / "champion-only-record.json"
OUT_PATH = HERE / "current43-report-chain.json"


def read_json(path: Path) -> tuple[dict[str, Any], bytes, str]:
    data = path.read_bytes()
    value = json.loads(data.decode("utf-8-sig"))
    if not isinstance(value, dict):
        raise ValueError(f"expected JSON object: {path}")
    return value, data, hashlib.sha256(data).hexdigest()


def find_receipt(rows: list[dict[str, Any]], url: str) -> dict[str, Any] | None:
    return next((row for row in rows if row.get("url") == url), None)


def receipt_matches(receipt: dict[str, Any] | None, path: Path, url: str) -> bool:
    if receipt is None:
        return False
    data = path.read_bytes()
    return (
        receipt.get("url") == url
        and receipt.get("status") == 200
        and receipt.get("sha256", "").lower() == hashlib.sha256(data).hexdigest()
        and receipt.get("bytes") == len(data)
    )


def load_pinned_multiseed():
    path = ROOT / "competitions/torchlean/candidates/r25-90m-20261029T064916Z/verification/pinned-source/multiseed.py"
    data = path.read_bytes()
    if hashlib.sha256(data).hexdigest() != "f171929b08cce37d848e736bb1d3c0bb422daeda1bbbd0da2ba3707d43d19341":
        raise ValueError("pinned multiseed.py SHA-256 mismatch")
    blob = b"blob " + str(len(data)).encode() + b"\0" + data
    if hashlib.sha1(blob).hexdigest() != "299b2e77db596a2720db3d54c2df46b3e5d2c3b3":
        raise ValueError("pinned multiseed.py Git blob mismatch")
    sys.dont_write_bytecode = True
    spec = importlib.util.spec_from_file_location("r27_current43_multiseed", path)
    if spec is None or spec.loader is None:
        raise ValueError("pinned multiseed.py could not be loaded")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def main() -> int:
    boards, boards_bytes, boards_sha = read_json(CURRENT_BOARDS)
    champions, champions_bytes, champions_sha = read_json(CURRENT_CHAMPIONS)
    report, report_bytes, report_sha = read_json(CURRENT_REPORT)
    version, version_bytes, version_sha = read_json(VERSION_CHECK)
    current_policy_replay, _, current_policy_replay_sha = read_json(CURRENT_POLICY_REPLAY)
    current_results, _, current_results_sha = read_json(HELPER_AUDIT)
    old_report, _, old_report_sha = read_json(OLD_REPORT)
    version_raw_path = ROOT / version["raw_path"]
    version_raw = version_raw_path.read_bytes()
    batch4_plan = json.loads((ROUND / "ci-plan-batch4.json").read_text(encoding="utf-8-sig"))
    update_receipts = json.loads((STATE / "normalized-champion-update-2150-receipts.json").read_text(encoding="utf-8-sig"))
    old_receipts = json.loads((STATE / "public-source-and-report-receipts.json").read_text(encoding="utf-8-sig"))
    boards_receipt = json.loads((STATE / "boards-2150-receipt.json").read_text(encoding="utf-8-sig"))
    mixer_receipt = json.loads((STATE / "champions-mixer-2130-receipt.json").read_text(encoding="utf-8-sig"))
    source23_receipt = find_receipt(update_receipts, "https://conjectures.io/v1/competitions/torchlean/submissions/23/source")
    report43_receipt = find_receipt(update_receipts, "https://conjectures.io/v1/competitions/torchlean/submissions/43/report")
    champions43_receipt = find_receipt(update_receipts, "https://conjectures.io/v1/competitions/torchlean/champions?board=normalized_mlp")
    old_report23_receipt = find_receipt(old_receipts, "https://conjectures.io/v1/competitions/torchlean/submissions/23/report")

    board_row = next((x for x in boards.get("boards", []) if x.get("id") == "normalized_mlp"), None)
    current_rows = [x for x in champions.get("champions", []) if x.get("current") is True]
    current = current_rows[0] if len(current_rows) == 1 else None
    report_source = report.get("submission", {})
    evaluation = next((x for x in report.get("evaluations", []) if x.get("board") == "normalized_mlp"), None)
    report23_source = old_report.get("submission", {})
    evaluation23 = next((x for x in old_report.get("evaluations", []) if x.get("board") == "normalized_mlp"), None)
    reference_rows = [x for x in champions.get("champions", []) if x.get("promotion_id") == 24 and x.get("current") is False]
    reference = reference_rows[0] if len(reference_rows) == 1 else None
    policy_rows = {x.get("board"): x for x in current_policy_replay.get("rows", []) if isinstance(x, dict)}
    normalized_policy_replay = current_policy_replay.get("current43_report", {})
    normalized_policy_row = policy_rows.get("normalized_mlp", {})

    proof_file_changes = [x.get("filename") for x in version.get("files", [])]
    proof_side_unchanged = not any(
        any(token in name.lower() for token in ("contract", "verify", "lean", "gate", "proof", "pins"))
        for name in proof_file_changes
    )
    checks: dict[str, bool] = {
        "boards_receipt_matches_bytes": receipt_matches(boards_receipt, CURRENT_BOARDS, "https://conjectures.io/v1/competitions/torchlean/boards"),
        "champion_receipt_matches_bytes": receipt_matches(champions43_receipt, CURRENT_CHAMPIONS, "https://conjectures.io/v1/competitions/torchlean/champions?board=normalized_mlp"),
        "boards_champion_publication_matches": boards.get("publication_hash") == champions.get("publication_hash"),
        "exactly_one_current_normalized_champion": len(current_rows) == 1 and bool(current),
        "current_champion_report_receipt_matches": receipt_matches(report43_receipt, CURRENT_REPORT, "https://conjectures.io/v1/competitions/torchlean/submissions/43/report"),
        "previous23_report_receipt_matches": receipt_matches(old_report23_receipt, OLD_REPORT, "https://conjectures.io/v1/competitions/torchlean/submissions/23/report"),
        "previous23_report_source_identity_matches": bool(report23_source.get("id") == 23 and report23_source.get("source_sha256") == "1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe"),
        "report_source_identity_matches_champion": bool(current and report_source.get("id") == 43 and report_source.get("source_sha256") == current.get("source_sha256")),
        "report_edge_matches_public23": bool(evaluation and reference and evaluation.get("reference_promotion_id") == reference.get("promotion_id") == 24 and evaluation.get("reference_hash") == reference.get("source_sha256")),
        "report_score_matches_current_champion_row": bool(evaluation and current and math.isclose(float(evaluation.get("decision", {}).get("score", -1)), float(current.get("ratio", -2)), rel_tol=1e-12, abs_tol=1e-15)),
        "previous23_report_edge_is_public12": bool(evaluation23 and evaluation23.get("reference_promotion_id") == 21 and evaluation23.get("reference_hash") == "e2c1f1f1ba52e32563fb193ceea7e2a271b989fd3ba2eb16cff747987879b521" and receipt_matches(old_report23_receipt, OLD_REPORT, "https://conjectures.io/v1/competitions/torchlean/submissions/23/report")),
        "report_config_matches_current_board": bool(evaluation and board_row and evaluation.get("config_hash") == board_row.get("config_hash")),
        "public23_source_receipt_matches_bytes": receipt_matches(source23_receipt, REF_SOURCE, "https://conjectures.io/v1/competitions/torchlean/submissions/23/source"),
        "public23_source_matches_report_reference": bool(evaluation and hashlib.sha256(REF_SOURCE.read_bytes()).hexdigest() == evaluation.get("reference_hash")),
        "official_version_raw_matches_summary": hashlib.sha256(version_raw).hexdigest() == version.get("raw_sha256"),
        "version_compare_is_expected": version.get("old_commit") == "accb82b6e2adeda1b41a57a260d68fb3879c427e" and version.get("new_commit") == "27fb1d19c712ead50ad34b4ad0d4ba597161e616",
        "no_proof_contract_lean_gate_files_changed": proof_side_unchanged,
        "new_benchmark_identity_replayed_to_live_board_hash": normalized_policy_row.get("matches_live_board_hash") is True,
        "current43_report_config_hash_matches_replayed_plan": (
            normalized_policy_replay.get("live_board_hash_matches_report_plan") is True
            and normalized_policy_replay.get("config_hash") == evaluation.get("config_hash") if evaluation else False
        ),
        "six_live_board_hashes_replayed_with_negative_controls": (
            len(current_policy_replay.get("rows", [])) == 6
            and not current_policy_replay.get("failures")
            and all(x.get("matches_live_board_hash") is True and x.get("negative_control_build_limit_rejected") is True for x in current_policy_replay.get("rows", []))
        ),
        "current_policy_proof_identity_matches_runtime": (
            normalized_policy_replay.get("proof_identity") == current_results.get("proof_identity")
        ),
        "replayed_current_policy_negative_controls_reject": bool(normalized_policy_replay.get("live_board_hash_matches_report_plan") is True and all(x.get("negative_control_build_limit_rejected") is True for x in current_policy_replay.get("rows", []))),
        "report_plan_identity_inferred_from_current_head": (
            normalized_policy_replay.get("benchmark_identity_inferred_from_current_official_head") == current_results.get("benchmark_identity")
            and normalized_policy_replay.get("proof_identity") == current_results.get("proof_identity")
            and version.get("new_commit") == current_results.get("official_commit")
        ),
        "helper_run_hash_audit_passes": (
            current_results.get("outer_artifact_manifest", {}).get("pass") is True
            and current_results.get("inner_file_hash_manifest", {}).get("pass") is True
            and current_results.get("dispatch_source_commit_matches_run") is True
            and current_results.get("artifact_plan_matches_frozen_dispatch") is True
            and current_results.get("official_commit") == version.get("new_commit")
            and current_results.get("runner_scope") == "CURRENT_OFFICIAL_HELPER_DIAGNOSTICS_ONLY_NO_CANDIDATE_OR_PERFORMANCE_ACCEPTANCE"
        ),
    }

    input_checks: dict[str, bool] = {}
    if evaluation and board_row:
        multiseed = load_pinned_multiseed()
        measured = evaluation.get("measurements", [])
        workloads = measured[0].get("workloads", []) if measured else []
        expected_cells = {
            f"normalized_mlp:b{batch}:{kind}": 1 / 6
            for batch in (1, 8)
            for kind in ("normal", "wide", "sparse")
        }
        envs = {x.get("id"): x for x in board_row.get("environments", []) if isinstance(x, dict)}
        one_seed = len({x.get("seed") for x in measured}) == 1 and bool(measured)
        seed = measured[0].get("seed") if measured else None
        weights = {name: value.get("weight") for name, value in envs.items()}
        aggregate = None
        if len(measured) == len(envs) == 2 and all(m.get("environment") in weights and m.get("score", 0) > 0 for m in measured):
            aggregate = math.exp(sum(math.log(float(m["score"])) * float(weights[m["environment"]]) for m in measured))
        input_checks = {
            "six_cells_and_weights": evaluation.get("cells") == expected_cells,
            "six_workloads_and_pinned_subseeds": len(workloads) == 6 and multiseed.workloads(seed) == workloads,
            "same_seed_workloads_both_environments": one_seed and len(measured) == 2 and all(m.get("workloads") == workloads for m in measured),
            "both_production_identities_and_weights": len(measured) == len(envs) == 2 and all(m.get("identity") == envs.get(m.get("environment"), {}).get("identity") for m in measured),
            "two_complete_runs_11_rounds_36_repetitions": all(m.get("state") == "completed" and m.get("attempts") == 1 and len(m.get("rounds", [])) == 11 and len(m.get("repetitions", {})) == 36 for m in measured),
            "timing_11x3x50ms": evaluation.get("timing", {}).get("rounds") == 11 and evaluation.get("timing", {}).get("inner") == 3 and evaluation.get("timing", {}).get("cell_ms") == 50,
            "admission_bar_and_guard": evaluation.get("admission_policy", {}).get("bar") == 0.97 and evaluation.get("admission_policy", {}).get("guard") == 1.1,
            "aggregate_matches_decision": aggregate is not None and math.isclose(aggregate, float(evaluation.get("decision", {}).get("score", -1)), rel_tol=1e-12, abs_tol=1e-15),
        }
        checks["current43_report_inputs_match_replayed_plan"] = (
            all(input_checks.values())
            and normalized_policy_replay.get("report_seed") == seed
            and normalized_policy_replay.get("report_workloads") == workloads
            and normalized_policy_replay.get("timing") == evaluation.get("timing")
            and normalized_policy_replay.get("cells") == evaluation.get("cells")
        )

    old_score = evaluation23.get("decision", {}).get("score") if evaluation23 else None
    current_score = evaluation.get("decision", {}).get("score") if evaluation else None
    current43_over_public12 = float(current_score) * float(old_score) if current_score and old_score else None
    run_details = [
        {
            "environment": m.get("environment"),
            "identity": m.get("identity"),
            "seed": m.get("seed"),
            "state": m.get("state"),
            "attempts": m.get("attempts"),
            "score": m.get("score"),
            "repetition_count": len(m.get("repetitions", {})),
            "round_count": len(m.get("rounds", [])),
        }
        for m in (evaluation.get("measurements", []) if evaluation else [])
    ]
    if normalized_policy_replay.get("resolved_run_contract"):
        run_details = normalized_policy_replay["resolved_run_contract"]
    guard_audit, _, _ = read_json(NATIVE_AUDIT)
    guard = next((x for x in guard_audit.get("results", []) if x.get("candidate") == "public12-guard26-v2"), None)
    guard_public12 = guard.get("score_vs_calibration_internal", {}).get("score") if guard else None
    guard_over_43 = float(guard_public12) / current43_over_public12 if guard_public12 and current43_over_public12 else None

    version_files = [x.get("filename") for x in version.get("files", [])]
    output = {
        "round": "R27",
        "captured_at_utc": "2026-10-29T21:54:05Z",
        "board": "normalized_mlp",
        "latest_board_snapshot": {
            "path": CURRENT_BOARDS.relative_to(ROOT).as_posix(),
            "sha256": boards_sha,
            "publication_hash": boards.get("publication_hash"),
            "receipt": boards_receipt,
            "normalized_mlp_config_hash": board_row.get("config_hash") if board_row else None,
            "champion_response_scope": "normalized_mlp and mixer have matching current-publication responses; other four boards have no response saved for this publication",
        },
        "current_champion": {
            "promotion_id": current.get("promotion_id") if current else None,
            "submission": current.get("submission") if current else None,
            "source_sha256": current.get("source_sha256") if current else None,
            "source_available": current.get("source_available") if current else None,
            "response_path": CURRENT_CHAMPIONS.relative_to(ROOT).as_posix(),
            "response_sha256": champions_sha,
            "receipt": champions43_receipt,
        },
        "current_report_edge": {
            "report_path": CURRENT_REPORT.relative_to(ROOT).as_posix(),
            "report_sha256": report_sha,
            "report_receipt": report43_receipt,
            "evaluation_id": evaluation.get("id") if evaluation else None,
            "reference_promotion_id": evaluation.get("reference_promotion_id") if evaluation else None,
            "reference_source_sha256": evaluation.get("reference_hash") if evaluation else None,
            "reference_source_receipt": source23_receipt,
            "reference_source_bytes_sha256": hashlib.sha256(REF_SOURCE.read_bytes()).hexdigest(),
            "report_config_hash": evaluation.get("config_hash") if evaluation else None,
            "live_board_config_hash": board_row.get("config_hash") if board_row else None,
            "score_current43_over_public23": current_score,
            "outcome": evaluation.get("decision", {}).get("outcome") if evaluation else None,
            "guard_passed": evaluation.get("decision", {}).get("guard_passed") if evaluation else None,
            "timing": evaluation.get("timing") if evaluation else None,
            "cell_count": len(evaluation.get("cells", {})) if evaluation else None,
            "workloads": evaluation.get("measurements", [{}])[0].get("workloads") if evaluation else None,
            "benchmark_runs": run_details,
            "input_checks": input_checks,
        },
        "replayed_current_report_policy": {
            "path": "competitions/torchlean/candidates/r27-5h-20261029T194443Z/verification/current-board-policy-replay.json",
            "sha256": hashlib.sha256(CURRENT_POLICY_REPLAY.read_bytes()).hexdigest(),
            "helper_run_audit_path": "competitions/torchlean/candidates/r27-5h-20261029T194443Z/verification/audit-helper-run-40964374666.json",
            "helper_run_audit_sha256": current_results_sha,
            "plan_hash": normalized_policy_replay.get("replayed_plan_hash"),
            "live_board_hash_match": normalized_policy_replay.get("live_board_hash_matches_report_plan"),
            "benchmark_identity": normalized_policy_replay.get("benchmark_identity_inferred_from_current_official_head"),
            "benchmark_identity_basis": "INFERRED_FROM_CURRENT_OFFICIAL_HEAD_AND_LIVE_BOARD_HASH; report endpoint omits identity",
            "proof_identity": normalized_policy_replay.get("proof_identity"),
            "initial_reference": normalized_policy_replay.get("initial_reference"),
            "seed_mode": normalized_policy_replay.get("seed_mode"),
            "cells": normalized_policy_replay.get("cells"),
            "timing": normalized_policy_replay.get("timing"),
            "admission": normalized_policy_replay.get("admission"),
            "run_contract": normalized_policy_replay.get("resolved_run_contract"),
            "report_inputs_match_replayed_plan": checks.get("current43_report_inputs_match_replayed_plan"),
            "checks": checks,
            "status": "INFERRED_CURRENT_OFFICIAL_HEAD_AND_LIVE_BOARD_HASH" if all(checks.values()) and all(input_checks.values()) else "UNKNOWN",
        },
        "benchmark_version": {
            "old_commit": version.get("old_commit"),
            "current_commit": version.get("new_commit"),
            "old_report23_config_hash": evaluation23.get("config_hash") if evaluation23 else None,
            "new_report43_config_hash": evaluation.get("config_hash") if evaluation else None,
            "changed_files": version_files,
            "benchmark_identity_changed": any(x == "validator/benchmark.py" for x in version_files),
            "proof_contract_lean_gate_changed": not proof_side_unchanged,
            "new_benchmark_identity_from_api": "Not present; inferred from current official head and report hash replay",
            "new_benchmark_identity_from_helper_run": current_results.get("benchmark_identity"),
            "new_proof_identity_from_helper_run": current_results.get("proof_identity"),
            "current_board_policy_replay_sha256": current_policy_replay_sha,
            "batch4_plan_official_commit": batch4_plan.get("official_commit"),
            "batch4_plan_uses_current_head": batch4_plan.get("official_commit") == version.get("new_commit"),
        },
        "cross_version_calibration": {
            "public23_over_public12_old_report_score": old_score,
            "current43_over_public12_product": current43_over_public12,
            "classification": "INFERRED_CROSS_BENCHMARK_VERSION",
            "reason": "#43/#23 was evaluated under current benchmark head 27fb, while #23/#12 and the guard26 quick run are from prior head accb; benchmark identity changed.",
            "exact_current43_comparison_allowed": False,
        },
        "other_current_response": {
            "mixer": {
                "path": (STATE / "champions-mixer-2130.raw").relative_to(ROOT).as_posix(),
                "receipt": mixer_receipt,
                "publication_matches_latest_boards": json.loads((STATE / "champions-mixer-2130.raw").read_text(encoding="utf-8-sig")).get("publication_hash") == boards.get("publication_hash"),
                "current_promotion_id": 27,
                "current_submission": 36,
                "source_available": False,
                "report_policy_status": "UNKNOWN_BENCHMARK_VERSION_CHANGED",
            },
            "unanswered_latest_board_ids": [x.get("id") for x in boards.get("boards", []) if x.get("id") not in {"normalized_mlp", "mixer"}],
        },
        "historical_guard26_screen": {
            "candidate_sha256": "dced7848655a50a136750c1837b46f084a25ec26d13df72fe907d4a162bf1cb9",
            "full_original_gate_pass": bool(guard_audit.get("full_gates", [{}])[0].get("verdict", {}).get("passed")) if guard_audit.get("full_gates") else False,
            "candidate_over_public12_old_quick_score": guard_public12,
            "candidate_over_current43_estimate": guard_over_43,
            "human_multiplier": f"{guard_over_43:.10g}x current champion time" if guard_over_43 else None,
            "classification": "INFERRED_SCREEN_CROSS_VERSION_SEEDS_ENVIRONMENTS",
            "current_champion_win": bool(guard_over_43 is not None and guard_over_43 < 1),
        },
        "future_exact_route": {
            "calibration_source_submission": 23,
            "calibration_source_sha256": "1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe",
            "calibration_source_status": "PUBLIC_SOURCE_BYTES_SAVED_LOCAL_ONLY",
            "required_official_head": version.get("new_commit"),
            "batch4_plan_official_head": batch4_plan.get("official_commit"),
            "batch4_plan_uses_current_benchmark_head": batch4_plan.get("official_commit") == version.get("new_commit"),
            "required_report_inputs": "Use current #43/#23 report input seed, cells, workloads, timing and environments; bind exact new benchmark identity before strict conversion.",
            "strict_current43_multiplier_status": "INFERRED_IF_CANDIDATE_ROW_MATCHES_REPLAYED_CURRENT43_PLAN_AND_ALL_ENVIRONMENT_RUNS",
            "current_batch4_plan_status": "STALE_OFFICIAL_COMMIT_AND_PUBLIC12_REFERENCE; current plan uses accb/#12 while current report is 27fb/#23",
        },
        "integrity_checks": checks,
        "audit_failures": [k for k, v in {**checks, **input_checks}.items() if not v],
    }
    if output["audit_failures"]:
        output["status"] = "SAVED_BYTES_MISMATCH"
    else:
        output["status"] = "CURRENT43_REPORT_EDGE_BOUND; FUTURE_MATCHING_ROW_CONVERTIBLE_AS_INFERRED; NO_CURRENT_CANDIDATE_ROW"
    OUT_PATH.write_text(json.dumps(output, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")

    record, _, _ = read_json(RECORD_PATH)
    if "pre_current43_state" not in record:
        record["pre_current43_state"] = {
            "current_official_snapshot": copy.deepcopy(record.get("current_official_snapshot")),
            "boards": copy.deepcopy(record.get("boards", [])),
            "current_official_report_chain": copy.deepcopy(record.get("current_official_report_chain")),
        }
    previous = {x.get("board"): x for x in record["pre_current43_state"].get("boards", []) if isinstance(x, dict)}
    boards_rows = []
    new_champion_docs = {"mixer": json.loads((STATE / "champions-mixer-2130.raw").read_text(encoding="utf-8-sig")), "normalized_mlp": champions}
    response_meta = {
        "normalized_mlp": {"path": CURRENT_CHAMPIONS.relative_to(ROOT).as_posix(), "at_utc": champions43_receipt.get("at_utc"), "sha256": champions_sha, "bytes": len(champions_bytes), "receipt": champions43_receipt},
        "mixer": {"path": (STATE / "champions-mixer-2130.raw").relative_to(ROOT).as_posix(), "at_utc": mixer_receipt.get("at_utc"), "sha256": mixer_receipt.get("sha256"), "bytes": mixer_receipt.get("bytes"), "receipt": mixer_receipt},
    }
    for board in boards.get("boards", []):
        name = board.get("id")
        prior = copy.deepcopy(previous.get(name, {}))
        response_doc = new_champion_docs.get(name)
        current_rows = [x for x in (response_doc or {}).get("champions", []) if x.get("current") is True]
        if response_doc and response_doc.get("publication_hash") == boards.get("publication_hash") and len(current_rows) == 1:
            current_row = current_rows[0]
            prior["last_bound_current_champion"] = prior.get("last_bound_current_champion") or {
                k: prior.get(k) for k in ("current_champion_identity", "current_promotion_id", "champion_submission", "champion_source_sha256", "champion_source_available", "champion_response_sha256", "champion_response_receipt", "current_champion_report_sha256")
            }
            prior.update({
                "board": name,
                "board_config_hash": board.get("config_hash"),
                "current_champion_identity": "VERIFIED_BY_CURRENT_CHAMPIONS_RESPONSE",
                "current_promotion_id": current_row.get("promotion_id"),
                "champion_promotion_id": current_row.get("promotion_id"),
                "champion_submission": current_row.get("submission"),
                "champion_source_sha256": current_row.get("source_sha256"),
                "champion_source_available": current_row.get("source_available"),
                "champion_response_sha256": response_meta[name]["sha256"],
                "champion_response_receipt": response_meta[name]["receipt"],
                "champion_response_config_hash": current_row.get("config_hash"),
                "raw_champion_ratio": current_row.get("ratio"),
                "latest_board_publication_hash": boards.get("publication_hash"),
                "latest_champion_response_at_utc": response_meta[name]["at_utc"],
            })
            if name == "normalized_mlp":
                replay_checks = {
                    "saved_current43_report_receipt_matches": checks["current_champion_report_receipt_matches"],
                    "current43_reference_is_saved_public23": checks["report_edge_matches_public23"] and checks["public23_source_receipt_matches_bytes"],
                    "current_report_config_matches_board": checks["report_config_matches_current_board"],
                    "current_report_inputs_match_replayed_plan": checks.get("current43_report_inputs_match_replayed_plan") is True,
                    "six_live_board_hashes_replayed_with_negative_controls": checks["six_live_board_hashes_replayed_with_negative_controls"],
                    "helper_run_hash_audit_passes": checks["helper_run_hash_audit_passes"],
                    "benchmark_identity_inferred_from_current_head": checks["report_plan_identity_inferred_from_current_head"],
                    "proof_identity_matches_current_helper_run": checks["current_policy_proof_identity_matches_runtime"],
                }
                current_report_policy_matches = all(replay_checks.values())
                replayed_contract = normalized_policy_replay.get("resolved_run_contract", [])
                policy = {
                    "report_path": CURRENT_REPORT.relative_to(ROOT).as_posix(),
                    "report_sha256": report_sha,
                    "report_config_hash": evaluation.get("config_hash"),
                    "calibration_reference_source_sha256": evaluation.get("reference_hash"),
                    "calibration_reference_source_receipt": source23_receipt,
                    "initial_reference": normalized_policy_replay.get("initial_reference"),
                    "seed_mode": normalized_policy_replay.get("seed_mode"),
                    "proof_identity": normalized_policy_replay.get("proof_identity"),
                    "benchmark_identity": normalized_policy_replay.get("benchmark_identity_inferred_from_current_official_head"),
                    "benchmark_identity_basis": "INFERRED_FROM_CURRENT_OFFICIAL_HEAD_AND_LIVE_BOARD_HASH; REPORT_ENDPOINT_OMITS_IDENTITY",
                    "cells": normalized_policy_replay.get("cells"),
                    "timing": normalized_policy_replay.get("timing"),
                    "admission": normalized_policy_replay.get("admission"),
                    "run_contract": replayed_contract,
                    "report_seed": normalized_policy_replay.get("report_seed"),
                    "report_workloads": normalized_policy_replay.get("report_workloads"),
                    "benchmark_version_commit": version.get("new_commit"),
                    "checks": replay_checks,
                }
                prior.update({
                    "calibration_reference_sha256": evaluation.get("reference_hash"),
                    "candidate_reference_source_receipt": source23_receipt,
                    "candidate_reference_time_over_champion_time": 1.0 / float(current_score),
                    "calibration_board_config_hash": evaluation.get("config_hash"),
                    "current_champion_time_over_anchor_time": current_score,
                    "current_champion_report_path": CURRENT_REPORT.relative_to(ROOT).as_posix(),
                    "current_champion_report_sha256": report_sha,
                    "current_champion_report_receipt": report43_receipt,
                    "current_report_timing": evaluation.get("timing"),
                    "current_report_cell_count": len(evaluation.get("cells", {})),
                    "current_report_workloads": output["current_report_edge"]["workloads"],
                    "current_report_benchmark_runs": replayed_contract,
                    "current_report_input_checks": input_checks,
                    "current_report_policy": policy,
                    "current_report_policy_matches": current_report_policy_matches,
                    "calibration_status": "INFERRED" if current_report_policy_matches else "UNKNOWN_BENCHMARK_IDENTITY_CHANGED",
                    "calibration_status_detail": "#43/#23 report identity is inferred from the current official head and a replayed plan hash matching the live board; strict candidate conversion still requires every input and both production runs to match.",
                    "calibration_eligible_for_current_board": current_report_policy_matches,
                    "calibration_eligible_for_report_config": current_report_policy_matches,
                    "champion_report_chain_to_current_config": "INFERRED_CURRENT_HEAD_IDENTITY_RECONSTRUCTED_BY_LIVE_HASH_AND_NEGATIVE_CONTROLS" if current_report_policy_matches else "UNKNOWN_BENCHMARK_VERSION_RECONSTRUCTION_REQUIRED",
                    "report_chain_edges": [{
                        "promotion_id": current_row.get("promotion_id"),
                        "submission": current_row.get("submission"),
                        "source_sha256": current_row.get("source_sha256"),
                        "report_path": CURRENT_REPORT.relative_to(ROOT).as_posix(),
                        "report_sha256": report_sha,
                        "reference_promotion_id": evaluation.get("reference_promotion_id"),
                        "reference_sha256": evaluation.get("reference_hash"),
                        "report_config_hash": evaluation.get("config_hash"),
                        "score_candidate_over_reference": current_score,
                        "outcome": evaluation.get("decision", {}).get("outcome"),
                    }],
                    "benchmark_version_status": "CURRENT_HEAD_27FB; BENCHMARK_IDENTITY_CHANGED_FROM_OLD_REPORT23_CHAIN",
                })
            else:
                if name == "mixer":
                    if "last_bound_current_report" not in prior:
                        prior["last_bound_current_report"] = {
                            "report_path": prior.get("current_champion_report_path"),
                            "report_sha256": prior.get("current_champion_report_sha256"),
                            "report_config_hash": prior.get("current_champion_report_config_hash"),
                            "reference_sha256": prior.get("calibration_reference_sha256"),
                            "score": prior.get("current_champion_time_over_anchor_time"),
                            "response_at_utc": (prior.get("champion_response_receipt") or {}).get("at_utc"),
                        }
                    prior["current_champion_report_path"] = None
                    prior["current_champion_report_sha256"] = None
                    prior["current_champion_report_receipt"] = None
                    prior["current_champion_time_over_anchor_time"] = None
                    prior["candidate_reference_time_over_champion_time"] = None
                    prior["current_report_benchmark_runs"] = []
                    prior["current_report_policy"] = {
                        "status": "UNKNOWN_CURRENT_REPORT_VERSION_CHANGED",
                        "current_boards_config_hash": board.get("config_hash"),
                        "last_report_config_hash": prior["last_bound_current_report"].get("report_config_hash"),
                        "benchmark_version_commit": version.get("new_commit"),
                        "checks": {"current_report_matches_new_benchmark_version": False},
                    }
                prior["calibration_status"] = "UNKNOWN_BENCHMARK_VERSION_CHANGED"
                prior["calibration_eligible_for_current_board"] = False
                prior["calibration_eligible_for_report_config"] = False
                prior["current_report_policy_matches"] = False
                prior["champion_report_chain_to_current_config"] = "UNKNOWN_REPORT_VERSION_RECONSTRUCTION_REQUIRED"
        else:
            prior["last_bound_current_champion"] = prior.get("last_bound_current_champion") or {
                k: prior.get(k) for k in ("current_champion_identity", "current_promotion_id", "champion_submission", "champion_source_sha256", "champion_source_available", "champion_response_sha256", "champion_response_receipt", "current_champion_report_sha256")
            }
            prior.update({
                "board": name,
                "board_config_hash": board.get("config_hash"),
                "current_champion_identity": "UNKNOWN_LATEST_BOARD_RESPONSE_MISSING",
                "current_promotion_id": None,
                "champion_promotion_id": None,
                "champion_submission": None,
                "champion_source_sha256": None,
                "champion_source_available": None,
                "champion_response_sha256": None,
                "champion_response_receipt": None,
                "calibration_status": "UNKNOWN_LATEST_BOARD_RESPONSE_MISSING",
                "calibration_eligible_for_current_board": False,
                "calibration_eligible_for_report_config": False,
                "current_report_policy_matches": False,
            })
        boards_rows.append(prior)

    old_snapshot = record.get("current_official_snapshot", {})
    if "pre_current43_snapshot" not in record:
        record["pre_current43_snapshot"] = copy.deepcopy(old_snapshot)
    latest_responses = [response_meta[k] for k in ("mixer", "normalized_mlp")]
    record["current_official_snapshot"] = {
        "boards_path": CURRENT_BOARDS.relative_to(ROOT).as_posix(),
        "boards_at_utc": boards_receipt.get("at_utc"),
        "boards_sha256": boards_sha,
        "boards_bytes": len(boards_bytes),
        "publication_hash": boards.get("publication_hash"),
        "boards_receipt": boards_receipt,
        "champions_response_scope": "normalized_mlp and mixer have matching current-publication responses; other four boards UNKNOWN",
        "champions_responses": latest_responses,
        "latest_board_response_at_utc": max(x["at_utc"] for x in latest_responses),
    }
    record["boards"] = boards_rows
    previous_chain = record.get("current_official_report_chain")
    if previous_chain and record.get("previous_official_report_chain") is None:
        record["previous_official_report_chain"] = copy.deepcopy(previous_chain)
    chain_sha = hashlib.sha256(OUT_PATH.read_bytes()).hexdigest()
    record["current_official_report_chain"] = {
        "path": OUT_PATH.relative_to(ROOT).as_posix(),
        "sha256": chain_sha,
        "status": output["status"],
        "benchmark_version": version.get("new_commit"),
        "current_edge": "submission43-report.raw references public submission23 source hash",
        "strict_multiplier_status": "INFERRED_ONLY_FOR_FUTURE_ROWS_MATCHING_CURRENT43_PLAN_AND_BOTH_ENVIRONMENT_RUNS; NO_CURRENT_CANDIDATE_ROW",
    }
    record["current_guard26_estimate"] = output["historical_guard26_screen"]
    record["review_status"] = "CURRENT43_EDGE_AUDITED; CURRENT_REPORT_POLICY_INFERRED_FROM_LIVE_HASH_REPLAY; CROSS_VERSION_MULTIPLIER_INFERRED"
    RECORD_PATH.write_text(json.dumps(record, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    print(json.dumps({"status": output["status"], "current43_over_public23": current_score, "current43_over_public12": current43_over_public12, "guard26_over_current43_estimate": guard_over_43, "integrity_failures": output["audit_failures"]}, ensure_ascii=False))
    return 0 if not output["audit_failures"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
