#!/usr/bin/env python3
"""Independent read-only audit of B6 native-cost and failed full-gate artifacts."""
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
RUN_DIR = ROUND / "evidence/40967910604"
PLAN_PATH = ROUND / "ci-plan-batch6.json"
OUT_PATH = HERE / "audit-native-run-40967910604.json"


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
            r"(?<=/)(?:benchExact|r27Native)(?=\.|$)", "<BIN>",
            re.sub(r"(?<=/)(?:MainExact|R27NativeMain)(?=\.)", "<MAIN>", arg),
        )
        for arg in args
    ]


def main() -> int:
    failures: list[str] = []
    plan, plan_bytes, plan_sha = read(PLAN_PATH)
    ci, _, ci_sha = read(RUN_DIR / "ci-run.json")
    root_audit, root_audit_bytes, root_audit_sha = read(RUN_DIR / "root-native-audit.json")
    results_path = ROUND / "CI-RESULTS-BATCH6.json"
    results_file_present = results_path.is_file()
    results_doc = read(results_path)[0] if results_file_present else {}
    results_sha = sha(results_path) if results_file_present else None
    original_manifest, _, original_manifest_sha = read(RUN_DIR / "original-artifact-hashes.json")
    artifact_dir = RUN_DIR / original_manifest["directory"]
    summary, summary_bytes, summary_sha = read(artifact_dir / "summary.json")
    artifact_plan, artifact_plan_bytes, artifact_plan_sha = read(artifact_dir / "plan.json")
    file_manifest, _, file_manifest_sha = read(artifact_dir / "file-hashes.json")

    r26_path = ROOT / "competitions/torchlean/candidates/r26-1h-20261029T085515Z/verification/analyze-native-only.py"
    r26 = load_module(r26_path, "r27_b6_pinned_r26_auditor")
    mod, modules, pins = r26.r25_tools()

    outer = r26.audit_tree(artifact_dir, original_manifest.get("files", {}))
    inner = r26.audit_tree(artifact_dir, file_manifest, excluded=("file-hashes.json",))
    if outer.get("status") != "PASS":
        failures.append("outer_artifact_hashes")
    if inner.get("status") != "PASS":
        failures.append("inner_runner_hashes")

    dispatch_path, dispatch = r26.find_dispatch(RUN_DIR.parent, "40967910604")
    frozen = dispatch.get("frozen_files", {})
    owned_source_rows = []
    for rel in plan.get("owned_sources", []):
        path = ROOT / rel
        got = sha(path) if path.is_file() else None
        expected = frozen.get(rel)
        passed = path.is_file() and got == expected
        owned_source_rows.append({"path": rel, "sha256": got, "dispatch_sha256": expected, "pass": passed})
        if not passed:
            failures.append("dispatch_owned_source_hash:" + rel)
    dispatch_helper_rows = []
    for entry in plan.get("helpers", []):
        path = ROOT / entry["path"]
        got = sha(path) if path.is_file() else None
        expected = entry.get("sha256")
        frozen_hash = frozen.get(entry["path"])
        passed = path.is_file() and got == expected == frozen_hash
        dispatch_helper_rows.append({"name": entry.get("name"), "path": entry.get("path"), "actual_sha256": got, "plan_sha256": expected, "dispatch_sha256": frozen_hash, "pass": passed})
        if not passed:
            failures.append("dispatch_helper_hash:" + str(entry.get("name")))

    dispatch_checks = {
        "source_commit_matches_ci": dispatch.get("source_commit") == ci.get("headSha") == "3c6b481f242c208fc1b4f00f1f523650deb8f32b",
        "run_id_matches": str((dispatch.get("run") or {}).get("databaseId")) == str(ci.get("databaseId")) == "40967910604",
        "dispatch_state_identified": dispatch.get("state") == "RUN_IDENTIFIED",
        "repository_public": dispatch.get("repository_public") is True,
        "allow_private_false": str(dispatch.get("request", {}).get("inputs", {}).get("allow_private", "")).lower() == "false",
        "official_commit_matches_plan": plan.get("official_commit") == "27fb1d19c712ead50ad34b4ad0d4ba597161e616",
        "dispatch_plan_matches_artifact_and_frozen_map": (
            artifact_plan_sha == plan_sha == frozen.get("competitions/torchlean/candidates/r27-5h-20261029T194443Z/ci-plan.json")
        ),
        "runner_hash_present": bool(frozen.get("competitions/torchlean/candidates/r27-5h-20261029T194443Z/development/ci-bridge/runner.py")),
    }
    if not all(dispatch_checks.values()):
        failures.extend("dispatch:" + k for k, ok in dispatch_checks.items() if not ok)

    listed_artifacts = read(RUN_DIR / "artifacts.json")[0].get("artifacts", [])
    artifact_meta = original_manifest.get("artifact", {})
    artifact_matches = [x for x in listed_artifacts if x.get("id") == artifact_meta.get("id")]
    artifact_meta_ok = (
        len(artifact_matches) == 1
        and artifact_matches[0].get("name") == "torchlean-40967910604-receipts"
        and artifact_matches[0].get("expired") is False
        and artifact_matches[0].get("digest") == artifact_meta.get("digest")
    )
    if not artifact_meta_ok:
        failures.append("artifact_metadata")

    terminal_checks = {
        "ci_terminal_failure": ci.get("status") == "completed" and ci.get("conclusion") == "failure",
        "torchlean_job_terminal": any(x.get("name") == "torchlean_r27" and x.get("status") == "completed" for x in ci.get("jobs", [])),
        "artifact_plan_sha_matches_frozen": artifact_plan_sha == plan_sha,
        "root_audit_outer_hashes_pass": root_audit.get("outer_hashes", {}).get("status") == "PASS",
        "root_audit_inner_hashes_pass": root_audit.get("inner_hashes", {}).get("status") == "PASS",
        "root_audit_counts_match": root_audit.get("outer_hashes", {}).get("files") == len(original_manifest.get("files", {})) and root_audit.get("inner_hashes", {}).get("files") == len(file_manifest),
    }
    if not all(terminal_checks.values()):
        failures.extend("terminal:" + k for k, ok in terminal_checks.items() if not ok)

    # Verify official public23 bytes and reconstruct both frozen candidates in memory.
    source_path = STATE / "source-private/submission23-Kernel.lean"
    source = source_path.read_bytes()
    source_sha = hashlib.sha256(source).hexdigest()
    receipts, _, receipts_sha = read(STATE / "normalized-champion-update-2150-receipts.json")
    source_receipt = next((x for x in receipts if x.get("url") == "https://conjectures.io/v1/competitions/torchlean/submissions/23/source"), None)
    source_receipt_ok = bool(source_receipt and source_receipt.get("status") == 200 and source_receipt.get("sha256") == source_sha == plan["reference"]["sha256"] and source_receipt.get("bytes") == len(source))
    if not source_receipt_ok:
        failures.append("public23_source_receipt")
    transform_rows = []
    patch_modules = {}
    for entry in plan.get("candidates", []):
        patch_path = ROOT / entry["patch_script"]
        module = load_module(patch_path, "r27_b6_terminal_" + entry["name"])
        patch_modules[entry["name"]] = module
        candidate_bytes = module.transform(source, 23, entry["variant"])
        candidate_sha = hashlib.sha256(candidate_bytes).hexdigest()
        checks = {
            "patch_hash_matches_plan_and_dispatch": sha(patch_path) == entry.get("patch_script_sha256") == frozen.get(entry["patch_script"]),
            "candidate_hash_matches_plan": candidate_sha == entry.get("sha256"),
            "candidate_length_matches_plan": len(candidate_bytes) == entry.get("bytes"),
        }
        if not all(checks.values()):
            failures.extend(f"candidate_transform:{entry.get('name')}:{k}" for k, ok in checks.items() if not ok)
        transform_rows.append({"name": entry.get("name"), "candidate_sha256": candidate_sha, "expected_sha256": entry.get("sha256"), "bytes": len(candidate_bytes), "expected_bytes": entry.get("bytes"), "full_gate": entry.get("full_gate"), "declares_correct": entry.get("declares_correct"), "proof_state": entry.get("proof_state"), "checks": checks})

    # Bind the current #43 champion and its saved #43/#23 edge before estimating.
    boards, _, boards_sha = read(STATE / "boards-2150.raw")
    champions, champions_bytes, champions_sha = read(STATE / "champions-normalized_mlp-2150.raw")
    champion_receipts, _, champion_receipts_sha = read(STATE / "normalized-champion-update-2150-receipts.json")
    report43, report43_bytes, report43_sha = read(STATE / "submission43-report.raw")
    current43_chain, _, current43_chain_sha = read(HERE / "current43-report-chain.json")
    board_norm = next((x for x in boards.get("boards", []) if x.get("id") == "normalized_mlp"), {})
    current43 = next((x for x in champions.get("champions", []) if x.get("current") is True), {})
    report43_eval = next((x for x in report43.get("evaluations", []) if x.get("board") == "normalized_mlp"), {})
    report43_receipt = next((x for x in champion_receipts if x.get("url") == "https://conjectures.io/v1/competitions/torchlean/submissions/43/report"), None)
    current43_checks = {
        "current_champion_response_matches_latest_publication": champions.get("publication_hash") == boards.get("publication_hash"),
        "current_champion_is43_source_private": current43.get("submission") == 43 and current43.get("source_available") is False,
        "current_report_receipt_matches_bytes": bool(report43_receipt and report43_receipt.get("status") == 200 and report43_receipt.get("sha256") == report43_sha and report43_receipt.get("bytes") == len(report43_bytes)),
        "report_config_matches_live_board": report43_eval.get("config_hash") == board_norm.get("config_hash"),
        "report_edge_is_public23": report43_eval.get("reference_hash") == source_sha and report43_eval.get("reference_promotion_id") == 24,
        "current43_chain_audit_passed": current43_chain.get("status", "").startswith("CURRENT43_REPORT_EDGE_BOUND") and not current43_chain.get("audit_failures"),
    }
    if not all(current43_checks.values()):
        failures.extend("current43:" + k for k, ok in current43_checks.items() if not ok)

    summary = json.loads((artifact_dir / "summary.json").read_text(encoding="utf-8-sig"))
    config = modules["config"].Config.load(artifact_dir / "overall-config.toml")
    board = config.plan("normalized_mlp")
    expected_cells = list(board["cells"])
    expected_timing = config.timing | board["timing"] | config.environments["local"]["timing"]
    expected_timing.update(build_seconds=300, cached_build_seconds=180, benchmark_seconds=300, run_seconds=120)
    cost_candidate = plan["candidates"][0]
    candidate_name = cost_candidate["name"]
    candidate_summary = {x.get("name"): x for x in summary.get("results", []) if isinstance(x, dict)}
    rows: list[dict[str, Any]] = []
    pairs: list[tuple[dict, dict]] = []
    cpus: list[dict] = []
    cost_candidate_dir = artifact_dir / candidate_name
    flags = read(cost_candidate_dir / "flags.json")[0]
    flag_checks = {}
    for kind in ("compile", "link", "response"):
        a = cost_candidate_dir / f"original-{kind}.raw"
        b = cost_candidate_dir / f"owned-{kind}.raw"
        old = shlex.split(a.read_text(encoding="utf-8")) if kind == "response" else r26.trace_args(a)
        new = shlex.split(b.read_text(encoding="utf-8")) if kind == "response" else r26.trace_args(b)
        saved = flags.get(kind, {})
        passed = normalized_args(old) == normalized_args(new) and saved.get("original_args") == old and saved.get("owned_args") == new and saved.get("equal_only_root_mapping") is True
        flag_checks[kind] = {"same_after_target_name_mapping": passed, "original_arg_count": len(old), "owned_arg_count": len(new)}
        if not passed:
            failures.append("b6_native_flags:" + kind)

    for seed in plan.get("seeds", []):
        seed = int(seed)
        request, _, request_sha = read(artifact_dir / f"{candidate_name}-{seed}-request.json")
        raw_result, _, measurement_sha = read(artifact_dir / f"{candidate_name}-{seed}-measurement.json")
        result = raw_result.get("result")
        if not isinstance(result, dict):
            failures.append("native_cost_measurement_missing:" + str(seed))
            continue
        expected = {
            "environment": "local",
            "identity": config.environments["local"]["identity"],
            "seed": seed,
            "candidate_hash": cost_candidate["sha256"],
            "reference_hash": plan["reference"]["sha256"],
            "cells": expected_cells,
            "timing": expected_timing,
            "benchmark_identity": board["benchmark_identity"],
            "workloads": modules["multiseed"].workloads(seed),
        }
        request_checks = {k: request.get(k) == v for k, v in expected.items()}
        try:
            modules["config"].MeasurementRequest.parse(request)
            request_checks["request_parses"] = True
        except Exception:
            request_checks["request_parses"] = False
        measurement_check = mod.measurement_check(request, raw_result, board["cells"], modules)
        r26.raw_rounds(artifact_dir, candidate_name, seed, request, result)
        paired = sum(len(r.get("cells", {})) for r in result.get("rounds", []))
        ns_values = 2 * paired
        checksums = sum(cell.get("reference_checksum") == cell.get("candidate_checksum") for r in result.get("rounds", []) for cell in r.get("cells", {}).values())
        provenance = result.get("provenance", {})
        built = candidate_summary.get(candidate_name, {}).get("binary_sha256")
        refbin = candidate_summary.get("calibration", {}).get("binary_sha256")
        provenance_checks = {"identity": provenance.get("identity") == request.get("identity"), "candidate_binary": provenance.get("candidate_binary") == built, "reference_binary": provenance.get("reference_binary") == refbin}
        if not all(request_checks.values()):
            failures.extend(f"b6_request:{seed}:{k}" for k, ok in request_checks.items() if not ok)
        if measurement_check.get("status") != "PASS" or paired != 180 or ns_values != 360 or checksums != 180 or measurement_check.get("checksum_mismatches") != 0:
            failures.append("b6_measurement_validation:" + str(seed))
        if not all(provenance_checks.values()):
            failures.extend(f"b6_provenance:{seed}:{k}" for k, ok in provenance_checks.items() if not ok)
        cpus.append({k: provenance.get(k) for k in ("identity", "machine", "architecture", "cpu_affinity")})
        pairs.append((request, result))
        rows.append({"seed": seed, "request_sha256": request_sha, "measurement_sha256": measurement_sha, "paired_rows": paired, "nanosecond_values": ns_values, "checksum_pairs": checksums, "checksum_mismatches": measurement_check.get("checksum_mismatches"), "rounds": len(result.get("rounds", [])), "cells_per_round": [len(x.get("cells", {})) for x in result.get("rounds", [])], "reference_first_sequence": [x.get("reference_first") for x in result.get("rounds", [])], "request_checks": request_checks, "pinned_measurement_check": measurement_check, "provenance": {**provenance, "checks": provenance_checks}})

    same_cpu = len(cpus) == 2 and all(cpus[0].get(k) == cpus[1].get(k) for k in ("identity", "machine", "architecture", "cpu_affinity"))
    if not same_cpu:
        failures.append("b6_same_cpu_across_seeds")
    local_plan = dict(board)
    local_plan["strata"] = [{"environment": req["environment"], "identity": req["identity"], "seed": req["seed"], "weight": 1 / len(pairs), "timing": req["timing"]} for req, _ in pairs]
    scorer = modules["scoring"].assess(local_plan, pairs) if len(pairs) == 2 else None
    root_cost = next((x for x in root_audit.get("results", []) if x.get("candidate") == candidate_name), {})
    score = scorer.get("score") if scorer else None
    report_score = float(report43_eval.get("decision", {}).get("score")) if report43_eval.get("decision", {}).get("score") is not None else None
    current43_estimate = score / report_score if score and report_score else None
    score_checks = {
        "pinned_score": score,
        "root_audit_score": root_cost.get("score_vs_calibration_internal", {}).get("score"),
        "score_matches_root_audit": bool(score is not None and math.isclose(float(score), float(root_cost.get("score_vs_calibration_internal", {}).get("score", -1)), rel_tol=1e-12, abs_tol=1e-15)),
        "current_report_current43_over_public23": report_score,
        "candidate_over_current43_estimate": current43_estimate,
        "reported_current43_estimate": root_cost.get("candidate_time_over_current_champion_estimate"),
        "estimate_matches": bool(current43_estimate is not None and math.isclose(float(current43_estimate), float(root_cost.get("candidate_time_over_current_champion_estimate", -1)), rel_tol=1e-12, abs_tol=1e-15)),
        "classification": "INFERRED_SCREEN_LOCAL_ENVIRONMENT_AND_SEEDS",
        "strict_fixed_converter_status": "UNKNOWN_LOCAL_RUN_CONTRACT_DOES_NOT_MATCH_BOTH_CURRENT_PRODUCTION_RUNS",
    }
    if not score_checks["score_matches_root_audit"] or not score_checks["estimate_matches"]:
        failures.append("b6_score_reconstruction")

    results_candidate = next((x for x in results_doc.get("results", []) if x.get("candidate") == cost_candidate["name"]), {})
    results_gate = next((x for x in results_doc.get("full_gates", []) if x.get("name") == "public23-row-reciprocal23-v3"), {})
    results_file_checks = {
        "result_file_present": results_file_present,
        "run_id_matches": results_doc.get("run") == 40967910604,
        "outer_manifest_matches_raw_audit": results_doc.get("outer_hashes", {}).get("status") == outer.get("status") == "PASS" and results_doc.get("outer_hashes", {}).get("files") == outer.get("files"),
        "inner_manifest_matches_raw_audit": results_doc.get("inner_hashes", {}).get("status") == inner.get("status") == "PASS" and results_doc.get("inner_hashes", {}).get("files") == inner.get("files"),
        "current43_estimate_matches_raw_reconstruction": bool(current43_estimate is not None and math.isclose(float(results_candidate.get("candidate_time_over_current_champion_estimate", -1)), float(current43_estimate), rel_tol=1e-12, abs_tol=1e-15)),
        "formal_gate_rejected_at_statement": results_gate.get("exit_code") != 0 and results_gate.get("verdict", {}).get("stage") == "statement" and results_gate.get("verdict", {}).get("passed") is False,
    }
    if not all(results_file_checks.values()):
        failures.extend("b6_results_file:" + k for k, ok in results_file_checks.items() if not ok)

    gate_rows = summary.get("full_gates", [])
    gate = next((x for x in gate_rows if x.get("name") == "public23-row-reciprocal23-v3"), {})
    gate_verdict = gate.get("verdict", {})
    gate_raw_path = artifact_dir / "public23-row-reciprocal23-v3/full-gate-raw-statement.log"
    gate_raw_text = gate_raw_path.read_text(encoding="utf-8", errors="replace") if gate_raw_path.is_file() else ""
    gate_error_lines = [line.strip() for line in gate_raw_text.splitlines() if line.lstrip().startswith("error:") or "unsolved goals" in line or "Unknown identifier" in line or "unexpected token" in line]
    gate_checks = {
        "exact_planned_candidate_gate_attempted": gate.get("source_sha256") == plan["candidates"][1]["sha256"],
        "gate_failed_at_statement": gate.get("exit_code") != 0 and gate_verdict.get("stage") == "statement" and gate_verdict.get("passed") is False,
        "start_and_end_fingerprints_match": gate_verdict.get("verifier_fingerprint") == gate_verdict.get("verifier_fingerprint_end"),
        "not_exhausted": gate_verdict.get("exhausted") is False,
        "full_candidate_native_measurement_absent": not any(p.name.startswith("public23-row-reciprocal23-v3-") and p.name.endswith("-measurement.json") for p in artifact_dir.iterdir()),
    }
    if not all(gate_checks.values()):
        failures.extend("b6_full_gate:" + k for k, ok in gate_checks.items() if not ok)

    helper_diag_rows = []
    helper_summary = {x.get("name"): x for x in summary.get("helper_diagnostics", [])}
    for entry in plan.get("helpers", []):
        result = helper_summary.get(entry.get("name"), {})
        log = artifact_dir / f"{entry.get('name')}-helper.log"
        log_text = log.read_text(encoding="utf-8", errors="replace") if log.is_file() else ""
        axiom_rows = []
        for match in re.finditer(r"'([^']+)' depends on axioms: \[(.*?)\]", log_text, flags=re.S):
            axiom_rows.append({"root": match.group(1), "axioms": sorted(set(re.findall(r"[A-Za-z][A-Za-z0-9_.]*", match.group(2))))})
        expected_roots = entry.get("helper_roots", [])
        got_roots = [x["root"] for x in axiom_rows]
        helper_checks = {
            "standalone_exit_zero": result.get("exit_code") == 0,
            "source_hash_matches_plan_and_dispatch": result.get("source_sha256") == entry.get("sha256") == frozen.get(entry.get("path")),
            "all_planned_roots_printed": sorted(got_roots) == sorted(expected_roots),
            "no_sorry_ax": "sorryAx" not in log_text,
            "standalone_diagnostic_only": result.get("scope") == "Standalone helper elaboration only; not original all12 gate or replay",
        }
        helper_diag_rows.append({"name": entry.get("name"), "exit_code": result.get("exit_code"), "source_sha256": result.get("source_sha256"), "log_sha256": sha(log) if log.is_file() else None, "scope": result.get("scope"), "axiom_sets": axiom_rows, "checks": helper_checks, "standalone_diagnostic_only": True})
        if not all(helper_checks.values()):
            failures.extend(f"helper_diagnostic:{entry.get('name')}:{k}" for k, ok in helper_checks.items() if not ok)

    profile = summary.get("cost_profile", {})
    profile_log = artifact_dir / "cost-profile/profile-compile.log"
    profile_diagnostic = {
        "state": profile.get("state"),
        "error_type": profile.get("error_type"),
        "error": profile.get("error"),
        "compile_log_sha256": sha(profile_log) if profile_log.is_file() else None,
        "actual_operator_cost_data": False,
    }

    main_hash = summary.get("owned_main_equals_original_sha256")
    runner_path = "competitions/torchlean/candidates/r27-5h-20261029T194443Z/development/ci-bridge/runner.py"
    main_receipt = {"sha256": main_hash, "root_audit_sha256": root_audit.get("MainExact_sha256"), "frozen_runner_sha256": frozen.get(runner_path), "hash_matches_audit": main_hash == root_audit.get("MainExact_sha256"), "direct_official_bytes_in_artifact": False}
    try:
        runner_blob = subprocess.run(["git", "show", f"{ci['headSha']}:{runner_path}"], cwd=ROOT, capture_output=True, check=True).stdout
        main_receipt["runner_blob_sha256"] = hashlib.sha256(runner_blob).hexdigest()
        main_receipt["runner_hash_matches_dispatch"] = main_receipt["runner_blob_sha256"] == main_receipt["frozen_runner_sha256"]
        main_receipt["copy_assertion_present"] = b"mainfile.write_bytes(mainbytes)" in runner_blob and b"assert mainfile.read_bytes()==mainbytes" in runner_blob
    except (subprocess.CalledProcessError, FileNotFoundError):
        main_receipt["runner_hash_matches_dispatch"] = None
        main_receipt["copy_assertion_present"] = None
    if not main_receipt["hash_matches_audit"] or main_receipt.get("runner_hash_matches_dispatch") is False or main_receipt.get("copy_assertion_present") is False:
        failures.append("b6_main_exact_copy_receipt")

    proof_errors = [x.get("error") for x in summary.get("candidate_errors", []) if x.get("candidate") == plan["candidates"][1]["name"]]
    output = {
        "round": "R27",
        "captured_at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
        "scope": "INDEPENDENT_B6_RAW_ARTIFACT_AUDIT_WITH_PINNED_R25_SCORER; FAILED_FULL_GATE_AND_NATIVE_ONLY_COST",
        "run": {"id": ci.get("databaseId"), "commit": ci.get("headSha"), "conclusion": ci.get("conclusion"), "official_commit": plan.get("official_commit")},
        "plan": {"path": PLAN_PATH.relative_to(ROOT).as_posix(), "sha256": plan_sha, "artifact_plan_sha256": artifact_plan_sha, "scope": plan.get("scope")},
        "dispatch": {"path": dispatch_path.relative_to(ROOT).as_posix(), "checks": dispatch_checks, "owned_source_hashes": owned_source_rows, "helper_hashes": dispatch_helper_rows},
        "artifact_integrity": {"outer": outer, "inner": inner, "original_manifest_sha256": hashlib.sha256((RUN_DIR / "original-artifact-hashes.json").read_bytes()).hexdigest(), "file_manifest_sha256": file_manifest_sha},
        "public23_source": {"path": source_path.relative_to(ROOT).as_posix(), "sha256": source_sha, "bytes": len(source), "receipt": source_receipt, "receipt_matches": source_receipt_ok, "body_included_in_output": False},
        "candidate_transforms": transform_rows,
        "MainExact": main_receipt,
        "cost_only_candidate": {"candidate": cost_candidate, "native_flags": flag_checks, "seeds": rows, "same_cpu": same_cpu, "pinned_score_and_current43_estimate": score_checks, "proof_state": "NOT_PROVED_NATIVE_ONLY", "correctness_gate": "NOT_CLAIMED"},
        "formal_candidate": {"candidate": plan["candidates"][1], "full_gate": gate, "full_gate_checks": gate_checks, "raw_statement_log_sha256": sha(gate_raw_path) if gate_raw_path.is_file() else None, "raw_error_lines": gate_error_lines, "native_measurement": "NOT_RUN_AFTER_GATE_REJECTED", "runner_error": proof_errors},
        "helper_diagnostics": helper_diag_rows,
        "cost_profile_diagnostic": profile_diagnostic,
        "CI_RESULTS_batch6": {"path": results_path.relative_to(ROOT).as_posix(), "sha256": results_sha, "checks": results_file_checks},
        "current43": {"boards_sha256": boards_sha, "champions_sha256": champions_sha, "champion_response_sha256": hashlib.sha256(champions_bytes).hexdigest(), "report_sha256": report43_sha, "report_receipt": report43_receipt, "report_checks": current43_checks, "report_score_current43_over_public23": report_score, "calibration_status": "INFERRED"},
        "root_audit_sha256": root_audit_sha,
        "results_file_present": (ROUND / "CI-RESULTS-BATCH6.json").is_file(),
        "failures": failures,
        "status": "PASS_B6_EVIDENCE_AUDITED_NOT_CORRECT_OR_CHAMPION" if not failures else "AUDIT_FAILED",
    }
    OUT_PATH.write_text(json.dumps(output, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    print(json.dumps({"status": output["status"], "outer": outer.get("status"), "inner": inner.get("status"), "score": score_checks, "gate": gate_checks, "failures": failures}, ensure_ascii=False))
    return 0 if not failures else 1


if __name__ == "__main__":
    raise SystemExit(main())
