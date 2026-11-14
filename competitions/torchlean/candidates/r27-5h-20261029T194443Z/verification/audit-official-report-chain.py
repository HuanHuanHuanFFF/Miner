#!/usr/bin/env python3
"""Audit saved R27 official champion and report-chain bytes; never fetches sources."""
from __future__ import annotations

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
POLICY_CONFIG_BLOB = "6743c5c0060b7babab5155ffe1e0dc94dbf8a742"
POLICY_CONFIG_SHA256 = "42150b6f1e13b51d18116bb0d9b4b017904793470ae8fdcb364de614499182b5"


def raw_json(path: Path) -> tuple[dict[str, Any], str, int]:
    data = path.read_bytes()
    value = json.loads(data.decode("utf-8-sig"))
    if not isinstance(value, dict):
        raise ValueError(f"expected JSON object: {path}")
    return value, hashlib.sha256(data).hexdigest(), len(data)


def receipt_items() -> list[dict[str, Any]]:
    found: list[dict[str, Any]] = []
    for name in (
        "receipts.json",
        "board-report-receipts.json",
        "public-source-and-report-receipts.json",
        "retired5-source-receipt.json",
        "champions-mixer-2130-receipt.json",
    ):
        path = STATE / name
        if not path.exists():
            continue
        value = json.loads(path.read_text(encoding="utf-8-sig"))
        if isinstance(value, list):
            found.extend(x for x in value if isinstance(x, dict))
        elif isinstance(value, dict):
            if name == "champions-mixer-2130-receipt.json":
                value = dict(value)
                value["_resolved_path"] = (STATE / "champions-mixer-2130.raw").relative_to(ROUND.parents[3]).as_posix()
            if isinstance(value.get("records"), list):
                found.extend(x for x in value["records"] if isinstance(x, dict))
            else:
                found.append(value)
    return found


def report_receipt_map(items: list[dict[str, Any]]) -> dict[int, dict[str, Any]]:
    result: dict[int, dict[str, Any]] = {}
    for item in items:
        url = item.get("url", "")
        if isinstance(url, str) and url.endswith("/report"):
            try:
                sid = int(url.rsplit("/", 2)[-2])
            except (ValueError, IndexError):
                sid = None
        else:
            sid = item.get("submission")
        if isinstance(sid, int) and item.get("sha256"):
            result[sid] = item
    return result


def source_receipt_map(items: list[dict[str, Any]]) -> dict[int, dict[str, Any]]:
    result: dict[int, dict[str, Any]] = {}
    for item in items:
        url = item.get("url", "")
        if not isinstance(url, str) or not url.endswith("/source"):
            continue
        try:
            sid = int(url.rsplit("/", 2)[-2])
        except (ValueError, IndexError):
            continue
        result[sid] = item
    return result


def champion_receipt_map(
    items: list[dict[str, Any]],
    expected_publication_hash: str,
) -> tuple[dict[str, dict[str, Any]], list[dict[str, Any]]]:
    result: dict[str, dict[str, Any]] = {}
    unbound: list[dict[str, Any]] = []
    for item in items:
        url = item.get("url", "")
        if not isinstance(url, str) or "/champions" not in url:
            continue
        board = "overall"
        if "?board=" in url:
            board = url.rsplit("?board=", 1)[-1]
        path_value = item.get("path") or item.get("_resolved_path")
        if not isinstance(path_value, str):
            unbound.append({
                "board": board,
                "at_utc": item.get("at_utc"),
                "status": item.get("status"),
                "response_sha256": item.get("sha256"),
                "classification": "UNKNOWN_RESPONSE_BODY_PATH_MISSING",
            })
            continue
        response_path = ROUND.parents[3] / path_value
        try:
            response_path.resolve().relative_to(STATE.resolve())
        except ValueError:
            unbound.append({
                "board": board,
                "at_utc": item.get("at_utc"),
                "status": item.get("status"),
                "response_sha256": item.get("sha256"),
                "classification": "UNKNOWN_RESPONSE_PATH_OUTSIDE_COMPETITION_STATE",
            })
            continue
        if not response_path.is_file():
            unbound.append({
                "board": board,
                "at_utc": item.get("at_utc"),
                "status": item.get("status"),
                "response_sha256": item.get("sha256"),
                "classification": "UNKNOWN_RESPONSE_BODY_MISSING",
            })
            continue
        response_doc, response_sha, response_bytes = raw_json(response_path)
        if (
            item.get("status") != 200
            or item.get("sha256", "").lower() != response_sha.lower()
            or item.get("bytes") != response_bytes
            or response_doc.get("board") != board
        ):
            unbound.append({
                "board": board,
                "path": path_value,
                "at_utc": item.get("at_utc"),
                "status": item.get("status"),
                "response_sha256": response_sha,
                "classification": "UNKNOWN_RESPONSE_RECEIPT_BODY_MISMATCH",
            })
            continue
        if response_doc.get("publication_hash") != expected_publication_hash:
            current_rows = [x for x in response_doc.get("champions", []) if x.get("current") is True]
            current = current_rows[0] if len(current_rows) == 1 else {}
            unbound.append({
                "board": board,
                "path": path_value,
                "at_utc": item.get("at_utc"),
                "status": item.get("status"),
                "response_sha256": response_sha,
                "response_bytes": response_bytes,
                "response_publication_hash": response_doc.get("publication_hash"),
                "boards_snapshot_publication_hash": expected_publication_hash,
                "current_promotion_id": current.get("promotion_id"),
                "current_submission": current.get("submission"),
                "current_source_sha256": current.get("source_sha256"),
                "current_source_available": current.get("source_available"),
                "classification": "UNKNOWN_NEWER_RESPONSE_PUBLICATION_MISMATCH",
            })
            continue
        previous = result.get(board)
        if previous is None or str(item.get("at_utc", "")) >= str(previous.get("at_utc", "")):
            selected = dict(item)
            selected["_resolved_path"] = path_value
            result[board] = selected
    return result, unbound


def board_receipt(items: list[dict[str, Any]]) -> dict[str, Any] | None:
    for item in items:
        url = item.get("url", "")
        if isinstance(url, str) and url.endswith("/boards"):
            return item
    return None


def brief_receipt(item: dict[str, Any] | None, *, source: bool = False) -> dict[str, Any] | None:
    if item is None:
        return None
    keys = ("url", "at_utc", "status", "path", "sha256", "bytes")
    result = {key: item.get(key) for key in keys if key in item}
    if source:
        result["publication"] = item.get("publication", item.get("full_source_publication", "UNKNOWN"))
    return result


def same_num(a: Any, b: Any) -> bool:
    return (
        isinstance(a, (int, float))
        and not isinstance(a, bool)
        and isinstance(b, (int, float))
        and not isinstance(b, bool)
        and math.isfinite(float(a))
        and math.isfinite(float(b))
        and math.isclose(float(a), float(b), rel_tol=1e-12, abs_tol=1e-15)
    )


def valid_sha256(value: Any) -> bool:
    return isinstance(value, str) and len(value) == 64 and all(ch in "0123456789abcdef" for ch in value)


def load_pinned_multiseed():
    path = ROUND.parents[3] / "competitions/torchlean/candidates/r25-90m-20261029T064916Z/verification/pinned-source/multiseed.py"
    data = path.read_bytes()
    if hashlib.sha256(data).hexdigest() != "f171929b08cce37d848e736bb1d3c0bb422daeda1bbbd0da2ba3707d43d19341":
        raise ValueError("pinned multiseed.py SHA-256 mismatch")
    blob = b"blob " + str(len(data)).encode() + b"\0" + data
    if hashlib.sha1(blob).hexdigest() != "299b2e77db596a2720db3d54c2df46b3e5d2c3b3":
        raise ValueError("pinned multiseed.py Git blob mismatch")
    sys.dont_write_bytecode = True
    spec = importlib.util.spec_from_file_location("r27_pinned_multiseed", path)
    if spec is None or spec.loader is None:
        raise ValueError("pinned multiseed.py could not be loaded")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def bind_report_policy(
    board: dict[str, Any],
    current_submission: int | None,
    current_edge: dict[str, Any],
    replay_row: dict[str, Any] | None,
    replay_sha256: str | None,
    replay_path: Path,
    replay_root_valid: bool,
) -> tuple[dict[str, Any], list[dict[str, Any]]]:
    name = board.get("id")
    plan = replay_row.get("report_plan", {}) if isinstance(replay_row, dict) else {}
    report_runs = current_edge.get("benchmark_runs", [])
    report_runs_by_env = {
        run.get("environment"): run
        for run in report_runs
        if isinstance(run, dict) and isinstance(run.get("environment"), str)
    }
    board_envs = {
        env.get("id"): env
        for env in board.get("environments", [])
        if isinstance(env, dict) and isinstance(env.get("id"), str)
    }
    strata = plan.get("strata", []) if isinstance(plan, dict) else []
    exact_runs: list[dict[str, Any]] = []
    strata_ok = isinstance(strata, list) and bool(strata)
    if strata_ok:
        for stratum in strata:
            if not isinstance(stratum, dict):
                strata_ok = False
                continue
            environment = stratum.get("environment")
            board_env = board_envs.get(environment)
            measured = report_runs_by_env.get(environment)
            timing = stratum.get("timing", plan.get("timing"))
            if not isinstance(board_env, dict) or not isinstance(measured, dict) or not isinstance(timing, dict):
                strata_ok = False
                continue
            if (
                stratum.get("identity") != board_env.get("identity")
                or measured.get("identity") != stratum.get("identity")
                or not same_num(stratum.get("weight"), board_env.get("weight"))
            ):
                strata_ok = False
            exact_runs.append({
                "environment": environment,
                "identity": stratum.get("identity"),
                "seed": measured.get("seed"),
                "state": measured.get("state"),
                "attempts": measured.get("attempts"),
                "repetition_count": measured.get("repetition_count"),
                "round_count": measured.get("round_count"),
                "weight": stratum.get("weight"),
                "timing": timing,
            })
    strata_ok = (
        strata_ok
        and len(strata) == len(board_envs) == len(report_runs_by_env)
        and set(report_runs_by_env) == {x.get("environment") for x in exact_runs}
    )
    checks = {
        "global_replay_status_and_pinned_identity": replay_root_valid,
        "replay_row_matches_report_hash": (
            isinstance(replay_row, dict)
            and replay_row.get("matches") is True
            and replay_row.get("reconstructed_report_config_hash") == replay_row.get("expected_report_config_hash")
            and replay_row.get("expected_report_config_hash") == current_edge.get("report_config_hash")
        ),
        "replay_negative_control_rejected": (
            isinstance(replay_row, dict)
            and replay_row.get("negative_control_one_build_limit_change") == "REJECTED"
        ),
        "replay_submission_matches_current": (
            isinstance(replay_row, dict)
            and replay_row.get("current_submission") == current_submission
        ),
        "plan_matches_report_cells_timing_and_admission": (
            isinstance(plan, dict)
            and plan.get("board") == name
            and plan.get("seed_mode") == "fresh"
            and plan.get("cells") == current_edge.get("cells")
            and plan.get("timing") == current_edge.get("timing")
            and plan.get("admission") == current_edge.get("admission_policy")
        ),
        "plan_identity_hashes_present": (
            isinstance(plan, dict)
            and valid_sha256(plan.get("initial_reference"))
            and valid_sha256(plan.get("proof_identity"))
            and valid_sha256(plan.get("benchmark_identity"))
        ),
        "all_environment_identities_weights_and_run_timings_bound": strata_ok,
    }
    record = {
        "replay_path": replay_path.relative_to(ROUND.parents[3]).as_posix(),
        "replay_sha256": replay_sha256,
        "pinned_config_git_blob_sha": POLICY_CONFIG_BLOB,
        "pinned_config_sha256": POLICY_CONFIG_SHA256,
        "report_config_hash": (
            replay_row.get("reconstructed_report_config_hash") if isinstance(replay_row, dict) else None
        ),
        "reconstructed_report_config_hash": (
            replay_row.get("reconstructed_report_config_hash") if isinstance(replay_row, dict) else None
        ),
        "expected_report_config_hash": (
            replay_row.get("expected_report_config_hash") if isinstance(replay_row, dict) else None
        ),
        "initial_reference": plan.get("initial_reference") if isinstance(plan, dict) else None,
        "seed_mode": plan.get("seed_mode") if isinstance(plan, dict) else None,
        "proof_identity": plan.get("proof_identity") if isinstance(plan, dict) else None,
        "benchmark_identity": plan.get("benchmark_identity") if isinstance(plan, dict) else None,
        "cells": plan.get("cells") if isinstance(plan, dict) else None,
        "timing": plan.get("timing") if isinstance(plan, dict) else None,
        "admission": plan.get("admission") if isinstance(plan, dict) else None,
        "checks": checks,
    }
    return record, exact_runs


def main() -> int:
    boards_doc, boards_sha, boards_bytes = raw_json(STATE / "boards.raw")
    failures: list[str] = []
    policy_path = STATE / "exact-report-policy-replay.json"
    policy_doc: dict[str, Any] = {}
    policy_sha: str | None = None
    policy_rows: dict[str, dict[str, Any]] = {}
    policy_root_valid = False
    if policy_path.exists():
        policy_doc, policy_sha, _ = raw_json(policy_path)
        policy_pin = policy_doc.get("pinned_config", {})
        if (
            policy_doc.get("status") != "ALL_SIX_EXACT_REPORT_POLICY_HASHES_RECONSTRUCTED"
            or policy_pin.get("git_blob_sha") != POLICY_CONFIG_BLOB
            or policy_pin.get("sha256") != POLICY_CONFIG_SHA256
        ):
            failures.append("exact-report-policy-replay.json: status or pinned config identity mismatch")
        policy_rows = {
            row.get("board"): row
            for row in policy_doc.get("rows", [])
            if isinstance(row, dict) and isinstance(row.get("board"), str)
        }
        if len(policy_rows) != 6:
            failures.append(f"exact-report-policy-replay.json: expected six distinct board rows, got {len(policy_rows)}")
        policy_root_valid = (
            policy_doc.get("status") == "ALL_SIX_EXACT_REPORT_POLICY_HASHES_RECONSTRUCTED"
            and policy_pin.get("git_blob_sha") == POLICY_CONFIG_BLOB
            and policy_pin.get("sha256") == POLICY_CONFIG_SHA256
            and len(policy_rows) == 6
        )
    else:
        failures.append("exact-report-policy-replay.json: report policy reconstruction receipt missing")
    all_receipts = receipt_items()
    rreports = report_receipt_map(all_receipts)
    rsources = source_receipt_map(all_receipts)
    rchampions, unbound_champion_responses = champion_receipt_map(
        all_receipts,
        boards_doc.get("publication_hash"),
    )
    rboards = board_receipt(all_receipts)
    multiseed = load_pinned_multiseed()
    if (
        rboards is None
        or rboards.get("status") != 200
        or rboards.get("sha256", "").lower() != boards_sha.lower()
    ):
        failures.append("boards.raw: missing/mismatched original boards response receipt")
    result_boards: list[dict[str, Any]] = []

    for board in boards_doc.get("boards", []):
        name = board.get("id")
        if not isinstance(name, str):
            failures.append("board without id")
            continue
        champ_path = STATE / f"champions-{name}.raw"
        champ_receipt = rchampions.get(name)
        response_path_value = (
            champ_receipt.get("path") or champ_receipt.get("_resolved_path")
            if champ_receipt else None
        )
        if isinstance(response_path_value, str):
            receipt_path = ROUND.parents[3] / response_path_value
            try:
                receipt_path.resolve().relative_to(STATE.resolve())
                if receipt_path.is_file():
                    champ_path = receipt_path
            except ValueError:
                pass
        if not champ_path.exists():
            champ_path = STATE / "champions.raw"
        champ_doc, champ_sha, champ_bytes = raw_json(champ_path)
        expected_champion_path = champ_path.relative_to(ROUND.parents[3]).as_posix()
        if (
            champ_receipt is None
            or champ_receipt.get("status") != 200
            or champ_receipt.get("sha256", "").lower() != champ_sha.lower()
            or response_path_value != expected_champion_path
        ):
            failures.append(f"{name}: missing/mismatched original champions response receipt")
        history = champ_doc.get("champions", [])
        current_rows = [p for p in history if p.get("current") is True]
        if (
            champ_doc.get("board") != name
            or champ_doc.get("publication_hash") != boards_doc.get("publication_hash")
            or len(current_rows) != 1
        ):
            failures.append(f"{name}: champion response scope/current row mismatch")
            continue
        current = current_rows[0]
        promo = current.get("promotion_id")
        if promo != board.get("current_promotion_id"):
            failures.append(f"{name}: champions and boards current promotion differ")
            continue

        chain: list[dict[str, Any]] = []
        cursor = current
        seen: set[int] = set()
        common_config: str | None = None
        anchor: dict[str, Any] | None = None
        chain_ratio = 1.0
        chain_status = "INFERRED"
        for depth in range(10):
            sid = cursor.get("submission")
            if not isinstance(sid, int) or not isinstance(cursor.get("promotion_id"), int):
                failures.append(f"{name}: malformed promotion/source row")
                chain_status = "UNKNOWN"
                break
            if cursor["promotion_id"] in seen:
                failures.append(f"{name}: promotion cycle")
                chain_status = "UNKNOWN"
                break
            seen.add(cursor["promotion_id"])

            report_path = STATE / f"submission{sid}-report.raw"
            if not report_path.exists():
                failures.append(f"{name}: missing report for submission {sid}")
                chain_status = "UNKNOWN"
                break
            report, report_sha, report_bytes = raw_json(report_path)
            if report.get("submission", {}).get("id") != sid:
                failures.append(f"{name}: report submission identity mismatch for {sid}")
                chain_status = "UNKNOWN"
                break
            source_sha = report.get("submission", {}).get("source_sha256")
            if source_sha != cursor.get("source_sha256"):
                failures.append(f"{name}: report/source hash mismatch for submission {sid}")
                chain_status = "UNKNOWN"
                break
            rr = rreports.get(sid)
            expected_report_path = report_path.relative_to(ROUND.parents[3]).as_posix()
            if (
                rr is None
                or rr.get("status") != 200
                or rr.get("sha256", "").lower() != report_sha.lower()
                or rr.get("path") != expected_report_path
            ):
                failures.append(f"{name}: missing/mismatched original report receipt for submission {sid}")
                chain_status = "UNKNOWN"
                break

            evals = [
                e for e in report.get("evaluations", [])
                if e.get("board") == name
                and e.get("state") == "completed"
                and e.get("decision", {}).get("outcome") == "qualifies"
                and isinstance(e.get("decision", {}).get("score"), (int, float))
                and not isinstance(e.get("decision", {}).get("score"), bool)
            ]
            expected_score = cursor.get("ratio")
            if depth == 0:
                evals = [e for e in evals if same_num(e.get("decision", {}).get("score"), expected_score)]
            elif common_config is not None:
                evals = [e for e in evals if e.get("config_hash") == common_config]
            if len(evals) != 1:
                failures.append(f"{name}: report evaluation not unique for submission {sid}")
                chain_status = "UNKNOWN"
                break
            ev = evals[0]
            cfg = ev.get("config_hash")
            if not isinstance(cfg, str):
                failures.append(f"{name}: evaluation config hash missing for {sid}")
                chain_status = "UNKNOWN"
                break
            if common_config is None:
                common_config = cfg
            elif cfg != common_config:
                failures.append(f"{name}: report-chain config changes at {sid}")
                chain_status = "UNKNOWN"
                break

            ref_promo = ev.get("reference_promotion_id")
            ref_sha = ev.get("reference_hash")
            score = float(ev["decision"]["score"])
            if not math.isfinite(score) or score <= 0:
                failures.append(f"{name}: invalid score edge at submission {sid}")
                chain_status = "UNKNOWN"
                break
            expected_envs = {
                item.get("id"): item.get("identity")
                for item in board.get("environments", [])
                if isinstance(item, dict)
            }
            env_weights = {
                item.get("id"): item.get("weight")
                for item in board.get("environments", [])
                if isinstance(item, dict)
            }
            report_runs = ev.get("measurements", [])
            report_cells = ev.get("cells", {})
            cell_count = len(report_cells)
            expected_cells = {}
            for model, weight in board.get("models", {}).items():
                batches = (1, 8) if model in ("mlp", "normalized_mlp") else (1, 4)
                for batch in batches:
                    for kind in ("normal", "wide", "sparse"):
                        expected_cells[f"{model}:b{batch}:{kind}"] = float(weight) / 6
            cell_weights_match = (
                set(report_cells) == set(expected_cells)
                and all(
                    isinstance(report_cells.get(key), (int, float))
                    and math.isclose(float(report_cells[key]), value, rel_tol=1e-12, abs_tol=1e-15)
                    for key, value in expected_cells.items()
                )
            )
            workload_names = sorted({
                key.rsplit(":", 1)[-1]
                for item in report_runs
                for key in item.get("repetitions", {})
                if "|" in key
            })
            report_workloads = report_runs[0].get("workloads", []) if report_runs else []
            expected_profiles = ["typical", "typical", "scale", "scale", "boundary", "boundary"]
            expected_workload_weights = [0.25, 0.25, 0.15, 0.15, 0.1, 0.1]
            workload_shape_ok = (
                len(report_workloads) == 6
                and [item.get("id") for item in report_workloads] == [f"s{i}" for i in range(6)]
                and [item.get("profile") for item in report_workloads] == expected_profiles
                and all(
                    math.isclose(float(item.get("weight", -1)), weight, rel_tol=1e-12, abs_tol=1e-15)
                    for item, weight in zip(report_workloads, expected_workload_weights)
                )
                and all(isinstance(item.get("seed"), int) and 0 <= item["seed"] < 2**32 for item in report_workloads)
            )
            same_workloads_across_envs = len(report_runs) == 2 and all(
                item.get("workloads") == report_workloads for item in report_runs
            )
            generated_workloads_match = bool(report_runs) and multiseed.workloads(report_runs[0].get("seed")) == report_workloads
            aggregate_matches = False
            if (
                len(report_runs) == 2
                and all(isinstance(item.get("score"), (int, float)) and item.get("score", 0) > 0 for item in report_runs)
                and all(isinstance(env_weights.get(item.get("environment")), (int, float)) for item in report_runs)
                and math.isclose(sum(float(v) for v in env_weights.values()), 1.0, rel_tol=1e-12, abs_tol=1e-12)
            ):
                mixed = math.exp(
                    sum(math.log(float(item["score"])) * float(env_weights[item["environment"]]) for item in report_runs)
                )
                aggregate_matches = math.isclose(mixed, score, rel_tol=1e-12, abs_tol=1e-15)
            run_ok = (
                len(report_runs) == len(expected_envs) == 2
                and all(item.get("state") == "completed" for item in report_runs)
                and all(
                    item.get("environment") in expected_envs
                    and item.get("identity") == expected_envs.get(item.get("environment"))
                    for item in report_runs
                )
                and len({item.get("seed") for item in report_runs}) == 1
                and all(len(item.get("repetitions", {})) == cell_count * 6 for item in report_runs)
            )
            expected_cell_count = 30 if name == "overall" else 6
            timing = ev.get("timing", {})
            admission = ev.get("admission_policy", {})
            input_checks = {
                "production_envs_match_boards": run_ok,
                "environment_weights_and_aggregate_score": aggregate_matches,
                "cells": cell_count == expected_cell_count,
                "cell_weights_match_board_models": cell_weights_match,
                "six_workloads_per_cell": workload_names == ["normal", "sparse", "wide"],
                "six_profiled_workloads_and_exact_subseeds": workload_shape_ok and same_workloads_across_envs,
                "pinned_multiseed_generator_matches_report": generated_workloads_match,
                "timing_11x3x50ms": timing.get("rounds") == 11 and timing.get("inner") == 3 and timing.get("cell_ms") == 50,
                "eleven_rounds_per_environment": all(len(item.get("rounds", [])) == timing.get("rounds") for item in report_runs),
                "admission_bar_guard": admission.get("bar") == board.get("promotion_bar") and admission.get("guard") == board.get("guard_limit"),
            }
            if not all(input_checks.values()):
                failures.append(f"{name}: official report input audit failed: {input_checks}")
                chain_status = "UNKNOWN"
            edge = {
                "promotion_id": cursor["promotion_id"],
                "submission": sid,
                "source_sha256": source_sha,
                "source_available": cursor.get("source_available"),
                "report_path": report_path.relative_to(ROUND.parents[3]).as_posix(),
                "report_sha256": report_sha,
                "report_bytes": report_bytes,
                "report_receipt": brief_receipt(rr),
                "evaluation_id": ev.get("id"),
                "reference_promotion_id": ref_promo,
                "reference_sha256": ref_sha,
                "report_config_hash": cfg,
                "score_candidate_over_reference": score,
                "outcome": ev.get("decision", {}).get("outcome"),
                "guard_passed": ev.get("decision", {}).get("guard_passed"),
                "timing": ev.get("timing"),
                "admission_policy": ev.get("admission_policy"),
                "cell_count": cell_count,
                "cells": report_cells,
                "input_checks": input_checks,
                "cell_weight_values": sorted(set(ev.get("cells", {}).values())),
                "workload_names": sorted({key.rsplit(":", 1)[-1] for item in ev.get("measurements", []) for key in item.get("repetitions", {}) if "|" in key}),
                "workloads": report_workloads,
                "strata_names": sorted({key.split("|", 1)[0] for item in ev.get("measurements", []) for key in item.get("repetitions", {}) if "|" in key}),
                "benchmark_runs": [
                    {
                        "environment": item.get("environment"),
                        "seed": item.get("seed"),
                        "identity": item.get("identity"),
                        "state": item.get("state"),
                        "attempts": item.get("attempts"),
                        "repetition_count": len(item.get("repetitions", {})),
                        "round_count": len(item.get("rounds", [])),
                    }
                    for item in ev.get("measurements", [])
                ],
            }
            if not isinstance(ref_promo, int):
                failures.append(f"{name}: no champion promotion anchor; do not use the shipped source as a champion")
                chain_status = "UNKNOWN"
                break

            parent = next((p for p in history if p.get("promotion_id") == ref_promo), None)
            if parent is None or parent.get("source_sha256") != ref_sha:
                failures.append(f"{name}: reference promotion/hash not present in champion history")
                chain_status = "UNKNOWN"
                break
            chain.append(edge)
            chain_ratio *= score
            if parent.get("source_available") is True:
                sr = rsources.get(parent.get("submission"))
                expected_source_path = (STATE / "source-private" / f"submission{parent.get('submission')}-Kernel.lean").relative_to(ROUND.parents[3]).as_posix()
                if (
                    sr is None
                    or sr.get("status") != 200
                    or sr.get("sha256", "").lower() != ref_sha.lower()
                    or sr.get("path") != expected_source_path
                ):
                    failures.append(f"{name}: available report-chain anchor lacks matching official source receipt for {parent.get('submission')}")
                    chain_status = "UNKNOWN"
                    break
                anchor = {
                    "promotion_id": ref_promo,
                    "submission": parent.get("submission"),
                    "source_sha256": ref_sha,
                    "source_receipt": brief_receipt(sr, source=True),
                }
                break
            cursor = parent
        else:
            failures.append(f"{name}: report chain exceeded depth limit")
            chain_status = "UNKNOWN"

        current_edge = chain[0] if chain else {}
        report_cfg = current_edge.get("report_config_hash")
        board_cfg = board.get("config_hash")
        config_matches = report_cfg == board_cfg
        current_policy, current_report_runs = bind_report_policy(
            board,
            current.get("submission"),
            current_edge,
            policy_rows.get(name),
            policy_sha,
            policy_path,
            policy_root_valid,
        )
        policy_matches = all(current_policy.get("checks", {}).values())
        if not policy_matches:
            failures.append(f"{name}: pinned report-policy reconstruction does not bind the current report")
            chain_status = "UNKNOWN"
        if anchor is None or chain_status == "UNKNOWN":
            chain_status = "UNKNOWN"
            ref_over_champ = None
        else:
            ref_over_champ = 1.0 / chain_ratio if chain_ratio > 0 else None
            if not config_matches:
                chain_status = "INFERRED_REPORT_CONFIG_DIFFERS_FROM_LIVE_BOARD_CONFIG"

        result_boards.append({
            "board": name,
            "current_promotion_id": promo,
            "current_submission": current.get("submission"),
            "current_source_sha256": current.get("source_sha256"),
            "current_source_available": current.get("source_available"),
            "current_champion_response_path": champ_path.relative_to(ROUND.parents[3]).as_posix(),
            "current_champion_response_sha256": champ_sha,
            "current_champion_response_bytes": champ_bytes,
            "current_champion_response_receipt": brief_receipt(champ_receipt),
            "current_ratio_to_reference_reported": current.get("ratio"),
            "live_board_config_hash": board_cfg,
            "report_config_hash": report_cfg,
            "live_board_config_matches_current_report": config_matches,
            "reference_anchor": anchor,
            "chain_edges_current_to_anchor": chain,
            "current_champion_time_over_anchor_time": chain_ratio if anchor else None,
            "anchor_time_over_current_champion_time": ref_over_champ,
            "calibration_status": chain_status,
            "calibration_scope": "Official current-champion report chain, converted across environments; inferred when not a same-run candidate/champion pair.",
            "current_report_policy": current_policy,
            "current_report_benchmark_runs": current_report_runs,
            "current_report_policy_matches": policy_matches,
        })

    output = {
        "round": "R27",
        "captured_at_utc": "2026-10-29T19:49:49Z",
        "boards_snapshot": {
            "path": "competitions/torchlean/candidates/r27-5h-20261029T194443Z/competition-state/boards.raw",
            "sha256": boards_sha,
            "bytes": boards_bytes,
            "configuration_hash": boards_doc.get("configuration_hash"),
            "publication_hash": boards_doc.get("publication_hash"),
            "receipt": brief_receipt(rboards),
        },
        "current_champion_source_status": "All current champion rows in the saved per-board responses say source_available=false.",
        "current_champion_response_selection": "Latest saved response matching the boards snapshot per board; unbound newer responses are listed separately.",
        "unbound_current_champion_responses": unbound_champion_responses,
        "human_metric": "candidate_time_over_current_champion_time; below 1 is faster, above 1 is slower.",
        "report_policy_replay": {
            "path": policy_path.relative_to(ROUND.parents[3]).as_posix(),
            "sha256": policy_sha,
            "status": policy_doc.get("status"),
            "pinned_config_git_blob_sha": policy_doc.get("pinned_config", {}).get("git_blob_sha"),
            "pinned_config_sha256": policy_doc.get("pinned_config", {}).get("sha256"),
        },
        "report_config_caveat": "The live board config hashes differ from current report hashes. The saved pinned Config.plan replay now reconstructs all six exact current report hashes, including proof and benchmark identities and environment-resolved build/cache limits; candidate/reference ratios must bind that reconstructed report plan. A local quick screen remains inferred and cannot be promoted to a direct current-champion result.",
        "boards": result_boards,
        "audit_failures": failures,
    }
    alerts_by_board: dict[str, dict[str, Any]] = {}
    for alert in unbound_champion_responses:
        board_name = alert.get("board")
        if isinstance(board_name, str):
            previous = alerts_by_board.get(board_name)
            if previous is None or str(alert.get("at_utc", "")) >= str(previous.get("at_utc", "")):
                alerts_by_board[board_name] = alert
    for board_result in result_boards:
        alert = alerts_by_board.get(board_result.get("board"))
        board_result["latest_champion_response_status"] = (
            "UNKNOWN_NEWER_RESPONSE_PUBLICATION_MISMATCH" if alert else "VERIFIED_AGAINST_BOARDS_SNAPSHOT"
        )
        if alert:
            board_result["latest_unbound_champion_response"] = alert
    out = HERE / "official-report-chain.json"
    out.write_text(json.dumps(output, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    chain_sha = hashlib.sha256(out.read_bytes()).hexdigest()
    record_path = HERE / "champion-only-record.json"
    record_doc, _, _ = raw_json(record_path)
    chain_ref_before_refresh = record_doc.get("current_official_report_chain")
    out_relative = out.relative_to(ROUND.parents[3]).as_posix()
    if isinstance(chain_ref_before_refresh, dict) and chain_ref_before_refresh.get("path") != out_relative:
        print(json.dumps({
            "output": str(out),
            "boards": len(result_boards),
            "failures": failures,
            "champion_record_refreshed": False,
            "reason": "A newer current snapshot report pointer is active; this audit remains historical.",
            "champion_record_sha256": hashlib.sha256(record_path.read_bytes()).hexdigest(),
        }, ensure_ascii=False))
        return 0 if len(result_boards) == 6 and not failures else 1
    record_boards = record_doc.get("boards", [])
    record_by_board = {
        item.get("board"): item
        for item in record_boards
        if isinstance(item, dict) and isinstance(item.get("board"), str)
    }
    for board_result in result_boards:
        target = record_by_board.get(board_result.get("board"))
        edge = (board_result.get("chain_edges_current_to_anchor") or [{}])[0]
        if target is None or not edge:
            failures.append(f"champion-only-record.json: cannot refresh {board_result.get('board')} report binding")
            continue
        policy = board_result.get("current_report_policy", {})
        alert = alerts_by_board.get(board_result.get("board"))
        target.update({
            "current_champion_identity": (
                "UNKNOWN_LATEST_RESPONSE_PUBLICATION_MISMATCH" if alert else "VERIFIED_BY_CURRENT_CHAMPIONS_RESPONSE"
            ),
            "current_promotion_id": board_result.get("current_promotion_id"),
            "champion_promotion_id": board_result.get("current_promotion_id"),
            "champion_submission": board_result.get("current_submission"),
            "champion_source_sha256": board_result.get("current_source_sha256"),
            "champion_source_available": board_result.get("current_source_available"),
            "champion_response_sha256": board_result.get("current_champion_response_sha256"),
            "champion_response_receipt": board_result.get("current_champion_response_receipt"),
            "raw_champion_ratio": board_result.get("current_ratio_to_reference_reported"),
            "calibration_status": board_result.get("calibration_status"),
            "calibration_status_detail": board_result.get("calibration_status"),
            "calibration_board_config_hash": board_result.get("report_config_hash"),
            "candidate_reference_time_over_champion_time": board_result.get("anchor_time_over_current_champion_time"),
            "current_champion_time_over_anchor_time": board_result.get("current_champion_time_over_anchor_time"),
            "current_champion_report_path": edge.get("report_path"),
            "current_champion_report_sha256": edge.get("report_sha256"),
            "current_champion_report_receipt": edge.get("report_receipt"),
            "current_report_timing": policy.get("timing"),
            "current_report_cell_count": len(policy.get("cells", {})),
            "current_report_workloads": edge.get("workloads"),
            "current_report_benchmark_runs": board_result.get("current_report_benchmark_runs"),
            "current_report_input_checks": edge.get("input_checks"),
            "current_report_policy": policy,
            "current_report_policy_matches": board_result.get("current_report_policy_matches"),
            "latest_champion_response_status": board_result.get("latest_champion_response_status"),
        })
        if alert:
            if "last_bound_current_champion" not in target:
                target["last_bound_current_champion"] = {
                    "current_champion_identity": "VERIFIED_BY_CURRENT_CHAMPIONS_RESPONSE",
                    "current_promotion_id": board_result.get("current_promotion_id"),
                    "submission": board_result.get("current_submission"),
                    "source_sha256": board_result.get("current_source_sha256"),
                    "source_available": board_result.get("current_source_available"),
                    "response_sha256": board_result.get("current_champion_response_sha256"),
                    "response_receipt": board_result.get("current_champion_response_receipt"),
                    "boards_snapshot_publication_hash": boards_doc.get("publication_hash"),
                }
            target["latest_unbound_champion_response"] = alert
        else:
            target.pop("latest_unbound_champion_response", None)
    snapshot = record_doc.get("current_official_snapshot")
    if isinstance(snapshot, dict):
        old_responses = snapshot.get("champions_responses", [])
        if "initial_champions_responses" not in snapshot and isinstance(old_responses, list):
            snapshot["initial_champions_responses"] = old_responses
        latest_responses = []
        for board_result in result_boards:
            receipt = board_result.get("current_champion_response_receipt") or {}
            latest_responses.append({
                "board": board_result.get("board"),
                "path": board_result.get("current_champion_response_path"),
                "at_utc": receipt.get("at_utc"),
                "status": receipt.get("status"),
                "sha256": board_result.get("current_champion_response_sha256"),
                "bytes": board_result.get("current_champion_response_bytes"),
            })
        snapshot["champions_responses"] = latest_responses
        snapshot["champions_response_scope"] = "latest saved response receipt matching boards snapshot per board; capture timestamps may differ"
        timestamps = [x.get("at_utc") for x in latest_responses if isinstance(x.get("at_utc"), str)]
        snapshot["latest_board_response_at_utc"] = max(timestamps) if timestamps else None
        snapshot["unbound_newer_champion_responses"] = unbound_champion_responses
        unbound_times = [x.get("at_utc") for x in unbound_champion_responses if isinstance(x.get("at_utc"), str)]
        snapshot["latest_unbound_champion_response_at_utc"] = max(unbound_times) if unbound_times else None
    record_doc["review_status"] = (
        "STATIC_REPORT_CHAIN_AUDITED_WITH_UNBOUND_NEWER_MIXER_RESPONSE; CURRENT_MIXER_STATE_UNKNOWN"
        if unbound_champion_responses else "STATIC_CHAMPION_AND_REPORT_POLICY_AUDIT_COMPLETE; CANDIDATE_TERMINAL_PENDING"
    )
    chain_ref = record_doc.get("current_official_report_chain")
    if isinstance(chain_ref, dict):
        chain_ref.update({
            "path": out.relative_to(ROUND.parents[3]).as_posix(),
            "sha256": chain_sha,
            "policy_replay_sha256": policy_sha,
            "config_mismatch": "Live board hashes differ; all current report hashes were reconstructed from pinned Config.plan. Conversion still requires the exact report policy and remains inferred across environments.",
            "input_audit": "PASS_6_BOARDS_WITH_PINNED_REPORT_POLICY_ENVIRONMENT_TIMINGS_AND_MULTISEED",
        })
    else:
        failures.append("champion-only-record.json: current_official_report_chain pointer missing")
    if failures:
        output["audit_failures"] = failures
        out.write_text(json.dumps(output, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
        chain_sha = hashlib.sha256(out.read_bytes()).hexdigest()
        if isinstance(chain_ref, dict):
            chain_ref["sha256"] = chain_sha
    record_path.write_text(json.dumps(record_doc, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    print(json.dumps({
        "output": str(out),
        "boards": len(result_boards),
        "failures": failures,
        "champion_record_sha256": hashlib.sha256(record_path.read_bytes()).hexdigest(),
        "calibration_statuses": {r["board"]: r["calibration_status"] for r in result_boards},
        "anchor_sources": {r["board"]: r["reference_anchor"] for r in result_boards},
        "ratios": {r["board"]: r["current_champion_time_over_anchor_time"] for r in result_boards},
    }, ensure_ascii=False))
    return 0 if len(result_boards) == 6 and not failures else 1


if __name__ == "__main__":
    raise SystemExit(main())


