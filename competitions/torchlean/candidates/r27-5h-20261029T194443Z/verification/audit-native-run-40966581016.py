#!/usr/bin/env python3
"""Independent read-only audit of B5 native-only artifacts with the R25 scorer."""
from __future__ import annotations

import datetime
import hashlib
import importlib.util
import json
import math
from pathlib import Path
import re
import shlex
import subprocess
import sys
from typing import Any

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
ROUND = HERE.parent
ROOT = ROUND.parents[3]
STATE = ROUND / "competition-state"
RUN_DIR = ROUND / "evidence/40966581016"
CI_RESULTS_PATH = ROUND / "CI-RESULTS-BATCH5.json"
PLAN_PATH = ROUND / "ci-plan-batch5.json"
OUT_PATH = HERE / "audit-native-run-40966581016.json"


def read(path: Path) -> tuple[Any, bytes, str]:
    raw = path.read_bytes()
    return json.loads(raw.decode("utf-8-sig")), raw, hashlib.sha256(raw).hexdigest()


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def load_module(path: Path, name: str):
    spec = importlib.util.spec_from_file_location(name, path)
    if spec is None or spec.loader is None:
        raise ValueError(f"cannot load {path}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def normalized_args(args: list[str]) -> list[str]:
    return [
        re.sub(
            r"(?<=/)(?:benchExact|r27Native)(?=\.|$)",
            "<BIN>",
            re.sub(r"(?<=/)(?:MainExact|R27NativeMain)(?=\.)", "<MAIN>", arg),
        )
        for arg in args
    ]


def main() -> int:
    failures: list[str] = []
    plan, plan_bytes, plan_sha = read(PLAN_PATH)
    results, results_bytes, results_sha = read(CI_RESULTS_PATH)
    ci, _, ci_sha = read(RUN_DIR / "ci-run.json")
    original_manifest, _, original_manifest_sha = read(RUN_DIR / "original-artifact-hashes.json")
    artifact_dir = RUN_DIR / original_manifest["directory"]
    summary, summary_bytes, summary_sha = read(artifact_dir / "summary.json")
    artifact_plan, artifact_plan_bytes, artifact_plan_sha = read(artifact_dir / "plan.json")
    manifest, _, manifest_sha = read(artifact_dir / "file-hashes.json")

    r26_path = ROOT / "competitions/torchlean/candidates/r26-1h-20261029T085515Z/verification/analyze-native-only.py"
    r26 = load_module(r26_path, "r27_b5_pinned_r26_auditor")
    mod, modules, pins = r26.r25_tools()

    outer = r26.audit_tree(artifact_dir, original_manifest.get("files", {}))
    inner = r26.audit_tree(artifact_dir, manifest, excluded=("file-hashes.json",))
    if outer.get("status") != "PASS":
        failures.append("outer_artifact_hashes")
    if inner.get("status") != "PASS":
        failures.append("inner_runner_hashes")

    dispatch_path, dispatch = r26.find_dispatch(RUN_DIR.parent, "40966581016")
    frozen = dispatch.get("frozen_files", {})
    dispatch_checks = {
        "dispatch_terminal_identity": dispatch.get("state") == "RUN_IDENTIFIED"
        and dispatch.get("source_commit") == ci.get("headSha") == results.get("source_commit"),
        "public_dispatch": dispatch.get("repository_public") is True
        and str(dispatch.get("request", {}).get("inputs", {}).get("allow_private", "")).lower() == "false",
        "run_id_matches": str((dispatch.get("run") or {}).get("databaseId")) == str(ci.get("databaseId")) == "40966581016",
        "official_head_matches_plan": plan.get("official_commit") == results.get("official_commit") == "27fb1d19c712ead50ad34b4ad0d4ba597161e616",
        "artifact_plan_matches_frozen_plan": artifact_plan_sha == plan_sha == frozen.get("competitions/torchlean/candidates/r27-5h-20261029T194443Z/ci-plan.json"),
        "patch_hash_matches_dispatch": frozen.get(plan["candidates"][0]["patch_script"]) == plan["candidates"][0]["patch_script_sha256"],
        "workflow_run_matches_dispatch": ci.get("headSha") == (dispatch.get("run") or {}).get("headSha"),
    }
    if not all(dispatch_checks.values()):
        failures.extend(f"dispatch:{k}" for k, ok in dispatch_checks.items() if not ok)

    listed_artifacts = read(RUN_DIR / "artifacts.json")[0].get("artifacts", [])
    artifact = original_manifest.get("artifact", {})
    artifact_matches = [x for x in listed_artifacts if x.get("id") == artifact.get("id")]
    artifact_meta_ok = (
        len(artifact_matches) == 1
        and artifact_matches[0].get("name") == "torchlean-40966581016-receipts"
        and artifact_matches[0].get("expired") is False
        and artifact_matches[0].get("digest") == artifact.get("digest")
    )
    if not artifact_meta_ok:
        failures.append("artifact_metadata")

    terminal_checks = {
        "ci_terminal": ci.get("status") == "completed" and ci.get("conclusion") == "failure",
        "job_terminal": any(x.get("name") == "torchlean_r27" and x.get("status") == "completed" for x in ci.get("jobs", [])),
        "result_is_terminal_partial": results.get("state") == "TERMINAL_PARTIAL_CANDIDATE_RESULTS_ALL_ARTIFACTS_COLLECTED",
        "no_full_gates": not results.get("full_gates") and not summary.get("full_gates"),
        "candidate_plan_full_gate_false": all(x.get("full_gate") is False for x in plan.get("candidates", [])),
        "summary_incomplete": summary.get("complete") is False,
    }
    if not all(terminal_checks.values()):
        failures.extend(f"terminal:{k}" for k, ok in terminal_checks.items() if not ok)

    # Confirm the exact #27 input and the plan's candidate bytes without writing generated source.
    source_path = STATE / "source-private/submission27-Kernel.lean"
    source = source_path.read_bytes()
    source_sha = hashlib.sha256(source).hexdigest()
    source_receipts, _, _ = read(STATE / "public-source-and-report-receipts.json")
    source27_receipt = next((x for x in source_receipts if x.get("url") == "https://conjectures.io/v1/competitions/torchlean/submissions/27/source"), None)
    source_receipt_ok = (
        source_sha == plan["reference"]["sha256"]
        and source27_receipt is not None
        and source27_receipt.get("sha256") == source_sha
        and source27_receipt.get("status") == 200
        and source27_receipt.get("bytes") == len(source)
    )
    candidate_transform_rows = []
    for entry in plan["candidates"]:
        patch_path = ROOT / entry["patch_script"]
        patch = load_module(patch_path, "r27_b5_static_" + entry["name"])
        generated = patch.transform(source, 27, entry["variant"])
        got_sha = hashlib.sha256(generated).hexdigest()
        checks = {
            "source_hash_matches_plan": source_sha == entry["fetch"]["sha256"] == plan["reference"]["sha256"],
            "patch_hash_matches_plan": sha(patch_path) == entry["patch_script_sha256"],
            "candidate_hash_matches_plan": got_sha == entry["sha256"],
            "candidate_length_matches_plan": len(generated) == entry["bytes"],
        }
        if not all(checks.values()):
            failures.extend(f"transform:{entry['name']}:{k}" for k, ok in checks.items() if not ok)
        candidate_transform_rows.append({
            "name": entry["name"],
            "source_sha256": source_sha,
            "candidate_sha256": got_sha,
            "expected_candidate_sha256": entry["sha256"],
            "candidate_bytes": len(generated),
            "expected_candidate_bytes": entry["bytes"],
            "full_gate": entry.get("full_gate"),
            "declares_correct": entry.get("declares_correct"),
            "proof_state": entry.get("proof_state"),
            "checks": checks,
        })
    if not source_receipt_ok:
        failures.append("public27_source_receipt")

    # Check frozen MainExact copy receipt and compiler/linker/response arguments.
    main_hash = summary.get("owned_main_equals_original_sha256")
    main_exact_receipt = {
        "sha256": main_hash,
        "CI_results_sha256": results.get("MainExact_sha256"),
        "hashes_match": bool(main_hash and main_hash == results.get("MainExact_sha256")),
        "runner_copy_assertion_present_in_frozen_runner": False,
        "frozen_runner_sha256": frozen.get("competitions/torchlean/candidates/r27-5h-20261029T194443Z/development/ci-bridge/runner.py"),
        "direct_official_bytes_available_in_artifact": False,
    }
    runner_path_in_commit = "competitions/torchlean/candidates/r27-5h-20261029T194443Z/development/ci-bridge/runner.py"
    try:
        blob = subprocess.run(
            ["git", "show", f"{ci['headSha']}:{runner_path_in_commit}"],
            cwd=ROOT,
            capture_output=True,
            check=True,
        ).stdout
        main_exact_receipt["runner_blob_sha256"] = hashlib.sha256(blob).hexdigest()
        main_exact_receipt["runner_hash_matches_dispatch"] = main_exact_receipt["runner_blob_sha256"] == main_exact_receipt["frozen_runner_sha256"]
        main_exact_receipt["runner_copy_assertion_present_in_frozen_runner"] = (
            b"mainfile.write_bytes(mainbytes)" in blob and b"assert mainfile.read_bytes()==mainbytes" in blob
        )
    except (subprocess.CalledProcessError, FileNotFoundError):
        main_exact_receipt["runner_hash_matches_dispatch"] = None
    if main_exact_receipt["hashes_match"] is not True or main_exact_receipt.get("runner_hash_matches_dispatch") is False or main_exact_receipt["runner_copy_assertion_present_in_frozen_runner"] is not True:
        failures.append("main_exact_copy_receipt")

    folder_summary = artifact_dir
    candidate_summary = {x.get("name"): x for x in summary.get("results", []) if isinstance(x, dict)}
    plan_ref = plan["reference"]
    config = modules["config"].Config.load(artifact_dir / "overall-config.toml")
    board = config.plan("mixer")
    expected_cells = list(board["cells"])
    expected_timing = config.timing | board["timing"] | config.environments["local"]["timing"]
    expected_timing.update(build_seconds=300, cached_build_seconds=180, benchmark_seconds=300, run_seconds=120)
    seed_rows = []
    pairs: list[tuple[dict, dict]] = []
    cpus: list[dict] = []
    flags_by_candidate: dict[str, Any] = {}
    candidate = plan["candidates"][0]
    candidate_name = candidate["name"]
    candidate_dir = artifact_dir / candidate_name
    raw_flags = read(candidate_dir / "flags.json")[0]
    for kind in ("compile", "link", "response"):
        orig_path = candidate_dir / f"original-{kind}.raw"
        owned_path = candidate_dir / f"owned-{kind}.raw"
        old = shlex.split(orig_path.read_text(encoding="utf-8")) if kind == "response" else r26.trace_args(orig_path)
        new = shlex.split(owned_path.read_text(encoding="utf-8")) if kind == "response" else r26.trace_args(owned_path)
        persisted = raw_flags.get(kind, {})
        ok = normalized_args(old) == normalized_args(new) and persisted.get("original_args") == old and persisted.get("owned_args") == new and persisted.get("equal_only_root_mapping") is True
        flags_by_candidate[kind] = {"equal_only_target_mapping": ok, "original_count": len(old), "owned_count": len(new)}
        if not ok:
            failures.append(f"native_flags:{kind}")

    for seed in plan["seeds"]:
        seed = int(seed)
        request, _, request_sha = read(artifact_dir / f"{candidate_name}-{seed}-request.json")
        raw, _, raw_sha = read(artifact_dir / f"{candidate_name}-{seed}-measurement.json")
        result = raw.get("result")
        if not isinstance(result, dict):
            failures.append(f"measurement_missing:{seed}")
            continue
        expected_request = {
            "environment": "local",
            "identity": config.environments["local"]["identity"],
            "seed": seed,
            "candidate_hash": candidate["sha256"],
            "reference_hash": plan_ref["sha256"],
            "cells": expected_cells,
            "timing": expected_timing,
            "benchmark_identity": board["benchmark_identity"],
            "workloads": modules["multiseed"].workloads(seed),
        }
        request_checks = {k: request.get(k) == v for k, v in expected_request.items()}
        try:
            modules["config"].MeasurementRequest.parse(request)
            request_checks["request_parses"] = True
        except Exception:
            request_checks["request_parses"] = False
        request_result = mod.measurement_check(request, raw, board["cells"], modules)
        r26.raw_rounds(artifact_dir, candidate_name, seed, request, result)
        rounds = result.get("rounds", [])
        paired = sum(len(x.get("cells", {})) for x in rounds)
        ns_values = 2 * paired
        checksum_pairs = sum(
            x.get("reference_checksum") == x.get("candidate_checksum")
            for r in rounds for x in r.get("cells", {}).values()
        )
        provenance = result.get("provenance", {})
        candidate_binary_sha = candidate_summary.get(candidate_name, {}).get("binary_sha256")
        reference_binary_sha = candidate_summary.get("calibration", {}).get("binary_sha256")
        provenance_checks = {
            "identity_matches_request": provenance.get("identity") == request.get("identity"),
            "candidate_binary_matches_build_receipt": provenance.get("candidate_binary") == candidate_binary_sha,
            "reference_binary_matches_build_receipt": provenance.get("reference_binary") == reference_binary_sha,
        }
        if not all(request_checks.values()):
            failures.extend(f"request:{seed}:{k}" for k, ok in request_checks.items() if not ok)
        if request_result.get("status") != "PASS":
            failures.append(f"pinned_measurement_check:{seed}")
        if paired != 180 or ns_values != 360 or checksum_pairs != 180 or request_result.get("checksum_mismatches") != 0:
            failures.append(f"row_count_or_checksum:{seed}")
        if not all(provenance_checks.values()):
            failures.extend(f"provenance:{seed}:{k}" for k, ok in provenance_checks.items() if not ok)
        cpus.append({k: provenance.get(k) for k in ("identity", "machine", "architecture", "cpu_affinity")})
        seed_rows.append({
            "seed": seed,
            "request_sha256": request_sha,
            "measurement_sha256": raw_sha,
            "paired_rows": paired,
            "nanosecond_values": ns_values,
            "checksum_pairs": checksum_pairs,
            "checksum_mismatches": request_result.get("checksum_mismatches"),
            "rounds": len(rounds),
            "cells_per_round": [len(x.get("cells", {})) for x in rounds],
            "reference_first_sequence": [x.get("reference_first") for x in rounds],
            "request_checks": request_checks,
            "pinned_measurement_check": request_result,
            "provenance": {**provenance, "checks": provenance_checks},
        })
        pairs.append((request, result))

    same_cpu = len(cpus) == 2 and all(cpus[0].get(k) == cpus[1].get(k) for k in ("identity", "machine", "architecture", "cpu_affinity"))
    if not same_cpu:
        failures.append("same_cpu_across_seeds")

    local_plan = dict(board)
    local_plan["strata"] = [
        {"environment": req["environment"], "identity": req["identity"], "seed": req["seed"], "weight": 1 / len(pairs), "timing": req["timing"]}
        for req, _ in pairs
    ]
    scorer_result = modules["scoring"].assess(local_plan, pairs) if len(pairs) == 2 else None
    reported = next((x for x in results.get("results", []) if x.get("candidate") == candidate_name), {})
    root_audit, _, root_audit_sha = read(RUN_DIR / "root-native-audit.json")
    root_row = next((x for x in root_audit.get("results", []) if x.get("candidate") == candidate_name), {})

    boards, _, boards_sha = read(STATE / "boards-2150.raw")
    mixer_champions, mixer_bytes, mixer_sha = read(STATE / "champions-mixer-2130.raw")
    mixer_response_receipt, _, mixer_receipt_sha = read(STATE / "champions-mixer-2130-receipt.json")
    champion_record, _, champion_record_sha = read(HERE / "champion-only-record.json")
    official_chain, _, official_chain_sha = read(HERE / "official-report-chain.json")
    mixer_chain = next((x for x in official_chain.get("boards", []) if x.get("board") == "mixer"), {})
    edge = (mixer_chain.get("chain_edges_current_to_anchor") or [{}])[0]
    report_path = ROOT / edge.get("report_path", "")
    report36, report36_bytes, report36_sha = read(report_path)
    report_receipt = edge.get("report_receipt")
    mixer_board = next((x for x in boards.get("boards", []) if x.get("id") == "mixer"), {})
    current_champion = next((x for x in mixer_champions.get("champions", []) if x.get("current") is True), {})
    ledger_mixer = next((x for x in champion_record.get("boards", []) if x.get("board") == "mixer"), {})
    report_eval = next((x for x in report36.get("evaluations", []) if x.get("board") == "mixer"), {})
    report_source_hash = hashlib.sha256((STATE / "source-private/submission27-Kernel.lean").read_bytes()).hexdigest()
    report_edge_checks = {
        "latest_board_and_champion_publication_match": boards.get("publication_hash") == mixer_champions.get("publication_hash") == ledger_mixer.get("latest_board_publication_hash"),
        "saved_champion_receipt_matches_bytes": mixer_response_receipt.get("status") == 200 and mixer_response_receipt.get("sha256") == mixer_sha and mixer_response_receipt.get("bytes") == len(mixer_bytes),
        "current_submission_is36": current_champion.get("submission") == 36 and mixer_chain.get("current_submission") == 36,
        "current_source_is_unavailable": current_champion.get("source_available") is False,
        "current_source_sha_matches_saved_response": current_champion.get("source_sha256") == mixer_chain.get("current_source_sha256"),
        "current_champion_report_source_matches": report36.get("submission", {}).get("id") == 36 and report36.get("submission", {}).get("source_sha256") == current_champion.get("source_sha256"),
        "report_receipt_matches_saved_bytes": bool(report_receipt and report_receipt.get("status") == 200 and report_receipt.get("sha256") == report36_sha and report_receipt.get("bytes") == len(report36_bytes)),
        "report_reference_is_public27": report_eval.get("reference_promotion_id") == 25 and report_eval.get("reference_hash") == plan["reference"]["sha256"] == report_source_hash,
        "report_ratio_matches_record": math.isclose(float(report_eval.get("decision", {}).get("score", -1)), float(mixer_chain.get("current_ratio_to_reference_reported", -2)), rel_tol=1e-12, abs_tol=1e-15),
        "report_config_is_old_not_live": report_eval.get("config_hash") == mixer_chain.get("report_config_hash") and report_eval.get("config_hash") != mixer_board.get("config_hash"),
        "latest_ledger_keeps_strict_calibration_unknown": ledger_mixer.get("calibration_status") == "UNKNOWN_BENCHMARK_VERSION_CHANGED" and ledger_mixer.get("current_report_policy_matches") is False,
    }
    if not all(report_edge_checks.values()):
        failures.extend(f"report_edge:{k}" for k, ok in report_edge_checks.items() if not ok)

    fixed_score = scorer_result.get("score") if scorer_result else None
    old_champion_over_public27 = float(report_eval.get("decision", {}).get("score")) if report_eval.get("decision", {}).get("score") is not None else None
    current_champion_estimate = fixed_score / old_champion_over_public27 if fixed_score and old_champion_over_public27 else None
    audit_vs_result = {
        "pinned_scorer_candidate_over_public27": fixed_score,
        "CI_results_candidate_over_public27": reported.get("score_vs_calibration_internal", {}).get("score"),
        "root_audit_candidate_over_public27": root_row.get("score_vs_calibration_internal", {}).get("score"),
        "fixed_scorer_values_match": bool(fixed_score is not None and math.isclose(float(fixed_score), float(reported.get("score_vs_calibration_internal", {}).get("score", -1)), rel_tol=1e-12, abs_tol=1e-15)),
        "official_old_report_current36_over_public27": old_champion_over_public27,
        "candidate_over_current36_time_estimate": current_champion_estimate,
        "reported_candidate_over_current36_estimate": reported.get("candidate_time_over_current_champion_estimate"),
        "inferred_estimate_matches": bool(current_champion_estimate is not None and math.isclose(float(current_champion_estimate), float(reported.get("candidate_time_over_current_champion_estimate", -1)), rel_tol=1e-12, abs_tol=1e-15)),
        "classification": "INFERRED_CROSS_BENCHMARK_VERSION_LOCAL_ENVIRONMENT_AND_SEEDS",
        "strict_fixed_converter_status": "UNKNOWN_CURRENT_REPORT_VERSION_AND_LOCAL_RUN_CONTRACT_MISMATCH",
    }
    if audit_vs_result["fixed_scorer_values_match"] is not True or audit_vs_result["inferred_estimate_matches"] is not True:
        failures.append("score_reconstruction")

    adaptive = plan["candidates"][1]
    adaptive_log = artifact_dir / "public27-adaptive" / "build.log"
    adaptive_text = adaptive_log.read_text(encoding="utf-8", errors="replace") if adaptive_log.is_file() else ""
    adaptive_diagnostic = {
        "candidate_sha256": adaptive.get("sha256"),
        "measurement_available": False,
        "candidate_error": next((x for x in summary.get("candidate_errors", []) if x.get("candidate") == adaptive["name"]), None),
        "HAnd_type_error_lines": [line.strip() for line in adaptive_text.splitlines() if "HAnd" in line or "work/Submission.lean:813" in line],
        "proof_state": "NO_FULL_GATE_BY_PLAN",
    }

    results_summary = {
        "run": ci.get("databaseId"),
        "source_commit": ci.get("headSha"),
        "workflow_conclusion": ci.get("conclusion"),
        "outer_manifest_files": outer.get("files"),
        "inner_manifest_files": inner.get("files"),
        "columns_all_status": reported.get("status"),
        "columns_all_proof_state": reported.get("candidate_proof"),
        "columns_all_native_flags": reported.get("native_flags"),
        "columns_all_measurements": seed_rows,
        "adaptive": adaptive_diagnostic,
        "candidate_transforms": candidate_transform_rows,
        "candidate_over_champion": audit_vs_result,
        "report_edge_checks": report_edge_checks,
    }
    output = {
        "round": "R27",
        "captured_at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
        "scope": "INDEPENDENT_B5_RAW_ARTIFACT_AUDIT_WITH_PINNED_R25_SCORER; NOT_CORRECT_OR_OFFICIAL_PERFORMANCE",
        "plan": {"sha256": plan_sha, "artifact_plan_sha256": artifact_plan_sha, "source_commit": ci.get("headSha"), "official_commit": plan.get("official_commit")},
        "dispatch_receipt": {"path": dispatch_path.relative_to(ROOT).as_posix(), "checks": dispatch_checks, "frozen_files": frozen},
        "ci_run": {"path": (RUN_DIR / "ci-run.json").relative_to(ROOT).as_posix(), "sha256": ci_sha, "status": ci.get("status"), "conclusion": ci.get("conclusion")},
        "artifact_integrity": {"outer": outer, "inner": inner, "original_manifest_sha256": original_manifest_sha, "file_manifest_sha256": manifest_sha, "artifact_metadata_ok": artifact_meta_ok},
        "pinned_scorer_sources": pins,
        "official_source27": {"path": source_path.relative_to(ROOT).as_posix(), "sha256": source_sha, "bytes": len(source), "receipt": source27_receipt, "receipt_matches": source_receipt_ok, "body_included_in_output": False},
        "current_mixer_report_chain": {
            "current_board_publication_hash": boards.get("publication_hash"),
            "current_champion_response_sha256": mixer_sha,
            "current_promotion_id": current_champion.get("promotion_id"),
            "current_submission": current_champion.get("submission"),
            "current_source_sha256": current_champion.get("source_sha256"),
            "source_available": current_champion.get("source_available"),
            "report_path": edge.get("report_path"),
            "report_sha256": report36_sha,
            "report_receipt": report_receipt,
            "report_config_hash": report_eval.get("config_hash"),
            "live_board_config_hash": mixer_board.get("config_hash"),
            "report_score_current36_over_public27": old_champion_over_public27,
            "public27_source_sha256": report_source_hash,
            "strict_current_calibration_status": ledger_mixer.get("calibration_status"),
            "strict_converter_status": audit_vs_result["strict_fixed_converter_status"],
        },
        "MainExact": main_exact_receipt,
        "summary_sha256": summary_sha,
        "results_sha256": results_sha,
        "root_audit_sha256": root_audit_sha,
        "champion_record_sha256": champion_record_sha,
        "official_report_chain_sha256": official_chain_sha,
        "mixer_champion_receipt_sha256": mixer_receipt_sha,
        "result": results_summary,
        "claim_boundary": "B5 is a five-round, three-inner-repetition, 2ms local runner screen. The only measured candidate is slower than current #36 by an inferred cross-version multiplier; full original proof gate was not in the plan. Adaptive did not build or measure.",
        "failures": failures,
        "status": "PASS_NATIVE_ONLY_EVIDENCE_AUDITED_NOT_CORRECT_OR_CHAMPION" if not failures else "AUDIT_FAILED",
    }
    OUT_PATH.write_text(json.dumps(output, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    print(json.dumps({"status": output["status"], "outer": outer.get("status"), "inner": inner.get("status"), "measured": len(seed_rows), "score_checks": audit_vs_result, "failures": failures}, ensure_ascii=False))
    return 0 if not failures else 1


if __name__ == "__main__":
    raise SystemExit(main())
