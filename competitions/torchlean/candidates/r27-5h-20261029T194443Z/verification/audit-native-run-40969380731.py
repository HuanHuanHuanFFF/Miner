#!/usr/bin/env python3
"""Independent read-only audit of B7 adaptive mixer results with the pinned R25 scorer."""
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

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
ROUND = HERE.parent
ROOT = ROUND.parents[3]
STATE = ROUND / "competition-state"
RUN_DIR = ROUND / "evidence/40969380731"
PLAN_PATH = ROUND / "ci-plan-batch7.json"
RESULT_PATH = ROUND / "CI-RESULTS-BATCH7.json"
OUT_PATH = HERE / "audit-native-run-40969380731.json"


def read(path: Path):
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


def normalize(args: list[str]) -> list[str]:
    return [
        re.sub(
            r"(?<=/)(?:benchExact|r27Native)(?=\.|$)",
            "<BIN>",
            re.sub(r"(?<=/)(?:MainExact|R27NativeMain)(?=\.)", "<MAIN>", x),
        )
        for x in args
    ]


def main() -> int:
    failures: list[str] = []
    plan, plan_bytes, plan_sha = read(PLAN_PATH)
    results, _, results_sha = read(RESULT_PATH)
    ci, _, ci_sha = read(RUN_DIR / "ci-run.json")
    root_audit, _, root_audit_sha = read(RUN_DIR / "root-native-audit.json")
    manifest, _, _ = read(RUN_DIR / "original-artifact-hashes.json")
    artifact_dir = RUN_DIR / manifest["directory"]
    summary, _, summary_sha = read(artifact_dir / "summary.json")
    artifact_plan, artifact_plan_bytes, artifact_plan_sha = read(artifact_dir / "plan.json")
    file_manifest, _, inner_manifest_sha = read(artifact_dir / "file-hashes.json")

    r26_path = ROOT / "competitions/torchlean/candidates/r26-1h-20261029T085515Z/verification/analyze-native-only.py"
    r26 = load_module(r26_path, "r27_b7_pinned_r26_auditor")
    mod, modules, pins = r26.r25_tools()
    outer = r26.audit_tree(artifact_dir, manifest.get("files", {}))
    inner = r26.audit_tree(artifact_dir, file_manifest, excluded=("file-hashes.json",))
    if outer.get("status") != "PASS":
        failures.append("outer_hashes")
    if inner.get("status") != "PASS":
        failures.append("inner_hashes")

    dispatch_path, dispatch = r26.find_dispatch(RUN_DIR.parent, "40969380731")
    frozen = dispatch.get("frozen_files", {})
    dispatch_checks = {
        "run_commit_matches": dispatch.get("source_commit") == ci.get("headSha") == results.get("source_commit"),
        "run_id_matches": str((dispatch.get("run") or {}).get("databaseId")) == str(ci.get("databaseId")) == "40969380731",
        "public_allow_private_false": dispatch.get("repository_public") is True and str(dispatch.get("request", {}).get("inputs", {}).get("allow_private", "")).lower() == "false",
        "artifact_plan_matches_batch7_plan": artifact_plan_sha == plan_sha == frozen.get("competitions/torchlean/candidates/r27-5h-20261029T194443Z/ci-plan.json"),
        "patch_hash_matches_dispatch": frozen.get(plan["candidates"][0]["patch_script"]) == plan["candidates"][0]["patch_script_sha256"],
        "official_head_matches_plan": plan.get("official_commit") == artifact_plan.get("official_commit") == "27fb1d19c712ead50ad34b4ad0d4ba597161e616",
    }
    if not all(dispatch_checks.values()):
        failures.extend("dispatch:" + k for k, ok in dispatch_checks.items() if not ok)

    source_path = STATE / "source-private/submission27-Kernel.lean"
    source = source_path.read_bytes()
    source_sha = hashlib.sha256(source).hexdigest()
    receipts, _, receipts_sha = read(STATE / "public-source-and-report-receipts.json")
    source_receipt = next((x for x in receipts if x.get("url") == "https://conjectures.io/v1/competitions/torchlean/submissions/27/source"), None)
    source_receipt_ok = bool(source_receipt and source_receipt.get("status") == 200 and source_receipt.get("sha256") == source_sha == plan["reference"]["sha256"] and source_receipt.get("bytes") == len(source))
    if not source_receipt_ok:
        failures.append("public27_source_receipt")
    entry = plan["candidates"][0]
    patch_path = ROOT / entry["patch_script"]
    patch = load_module(patch_path, "r27_b7_static_patch")
    candidate_bytes = patch.transform(source, 27, entry["variant"])
    candidate_sha = hashlib.sha256(candidate_bytes).hexdigest()
    transform_checks = {
        "patch_matches_plan_and_dispatch": sha(patch_path) == entry.get("patch_script_sha256") == frozen.get(entry["patch_script"]),
        "source_matches_plan": source_sha == entry["fetch"]["sha256"],
        "candidate_hash_matches_plan": candidate_sha == entry["sha256"] == "d6294bba2fc3808fabfbd38ed14452403f9fc574b34beff6565fa1aac57e6415",
        "candidate_bytes_match_plan": len(candidate_bytes) == entry.get("bytes"),
        "native_only_plan_flags": entry.get("full_gate") is False and entry.get("declares_correct") is True,
    }
    if not all(transform_checks.values()):
        failures.extend("transform:" + k for k, ok in transform_checks.items() if not ok)

    main_hash = summary.get("owned_main_equals_original_sha256")
    runner_rel = "competitions/torchlean/candidates/r27-5h-20261029T194443Z/development/ci-bridge/runner.py"
    runner_hash = frozen.get(runner_rel)
    try:
        runner_blob = subprocess.run(["git", "show", f"{ci['headSha']}:{runner_rel}"], cwd=ROOT, capture_output=True, check=True).stdout
        runner_blob_sha = hashlib.sha256(runner_blob).hexdigest()
        main_copy_assertion = b"mainfile.write_bytes(mainbytes)" in runner_blob and b"assert mainfile.read_bytes()==mainbytes" in runner_blob
    except (subprocess.CalledProcessError, FileNotFoundError):
        runner_blob_sha = None
        main_copy_assertion = False
    main_receipt = {
        "sha256": main_hash,
        "root_audit_sha256": root_audit.get("MainExact_sha256"),
        "runner_frozen_sha256": runner_hash,
        "runner_commit_blob_sha256": runner_blob_sha,
        "runner_blob_matches_dispatch": runner_blob_sha == runner_hash,
        "copy_assertion_present": main_copy_assertion,
        "direct_official_bytes_in_artifact": False,
    }
    if main_hash != root_audit.get("MainExact_sha256") or runner_blob_sha != runner_hash or not main_copy_assertion:
        failures.append("MainExact_copy_receipt")

    build_dir = artifact_dir / entry["name"]
    saved_flags = read(build_dir / "flags.json")[0]
    flags = {}
    for kind in ("compile", "link", "response"):
        a, b = build_dir / f"original-{kind}.raw", build_dir / f"owned-{kind}.raw"
        old = shlex.split(a.read_text(encoding="utf-8")) if kind == "response" else r26.trace_args(a)
        new = shlex.split(b.read_text(encoding="utf-8")) if kind == "response" else r26.trace_args(b)
        persisted = saved_flags.get(kind, {})
        passed = normalize(old) == normalize(new) and persisted.get("original_args") == old and persisted.get("owned_args") == new and persisted.get("equal_only_root_mapping") is True
        flags[kind] = {"equal_after_target_mapping": passed, "original_arg_count": len(old), "owned_arg_count": len(new)}
        if not passed:
            failures.append("native_flags:" + kind)

    config = modules["config"].Config.load(artifact_dir / "overall-config.toml")
    board = config.plan("mixer")
    expected_cells = list(board["cells"])
    expected_timing = config.timing | board["timing"] | config.environments["local"]["timing"]
    expected_timing.update(build_seconds=300, cached_build_seconds=180, benchmark_seconds=300, run_seconds=120)
    summary_results = {x.get("name"): x for x in summary.get("results", []) if isinstance(x, dict)}
    seed_rows, pairs, cpus = [], [], []
    for seed in plan["seeds"]:
        seed = int(seed)
        request, _, req_sha = read(artifact_dir / f"{entry['name']}-{seed}-request.json")
        raw, _, raw_sha = read(artifact_dir / f"{entry['name']}-{seed}-measurement.json")
        result = raw.get("result")
        if not isinstance(result, dict):
            failures.append("measurement_missing:" + str(seed))
            continue
        expected = {
            "environment": "local",
            "identity": config.environments["local"]["identity"],
            "seed": seed,
            "candidate_hash": entry["sha256"],
            "reference_hash": plan["reference"]["sha256"],
            "cells": expected_cells,
            "timing": expected_timing,
            "benchmark_identity": board["benchmark_identity"],
            "workloads": modules["multiseed"].workloads(seed),
        }
        req_checks = {k: request.get(k) == v for k, v in expected.items()}
        try:
            modules["config"].MeasurementRequest.parse(request)
            req_checks["parse"] = True
        except Exception:
            req_checks["parse"] = False
        checked = mod.measurement_check(request, raw, board["cells"], modules)
        r26.raw_rounds(artifact_dir, entry["name"], seed, request, result)
        paired = sum(len(r.get("cells", {})) for r in result.get("rounds", []))
        nsv = 2 * paired
        checksums = sum(c.get("reference_checksum") == c.get("candidate_checksum") for r in result.get("rounds", []) for c in r.get("cells", {}).values())
        prov = result.get("provenance", {})
        cand_bin = summary_results.get(entry["name"], {}).get("binary_sha256")
        ref_bin = summary_results.get("calibration", {}).get("binary_sha256")
        prov_checks = {"identity": prov.get("identity") == request.get("identity"), "candidate_binary": prov.get("candidate_binary") == cand_bin, "reference_binary": prov.get("reference_binary") == ref_bin}
        if not all(req_checks.values()):
            failures.extend(f"request:{seed}:{k}" for k, v in req_checks.items() if not v)
        if checked.get("status") != "PASS" or paired != 180 or nsv != 360 or checksums != 180 or checked.get("checksum_mismatches") != 0:
            failures.append("measurement_validation:" + str(seed))
        if not all(prov_checks.values()):
            failures.extend(f"provenance:{seed}:{k}" for k, v in prov_checks.items() if not v)
        cpus.append({k: prov.get(k) for k in ("identity", "machine", "architecture", "cpu_affinity")})
        seed_rows.append({"seed": seed, "request_sha256": req_sha, "measurement_sha256": raw_sha, "paired_rows": paired, "nanosecond_values": nsv, "checksum_pairs": checksums, "checksum_mismatches": checked.get("checksum_mismatches"), "rounds": len(result.get("rounds", [])), "cells_per_round": [len(r.get("cells", {})) for r in result.get("rounds", [])], "reference_first_sequence": [r.get("reference_first") for r in result.get("rounds", [])], "request_checks": req_checks, "pinned_measurement_check": checked, "provenance": {**prov, "checks": prov_checks}})
        pairs.append((request, result))
    same_cpu = len(cpus) == 2 and all(cpus[0].get(k) == cpus[1].get(k) for k in ("identity", "machine", "architecture", "cpu_affinity"))
    if not same_cpu:
        failures.append("same_cpu")
    local_plan = dict(board)
    local_plan["strata"] = [{"environment": q["environment"], "identity": q["identity"], "seed": q["seed"], "weight": 1 / len(pairs), "timing": q["timing"]} for q, _ in pairs]
    scorer = modules["scoring"].assess(local_plan, pairs) if len(pairs) == 2 else None
    root_row = next((x for x in root_audit.get("results", []) if x.get("candidate") == entry["name"]), {})
    score = scorer.get("score") if scorer else None

    report_chain, _, report_chain_sha = read(HERE / "official-report-chain.json")
    mixer_chain = next((x for x in report_chain.get("boards", []) if x.get("board") == "mixer"), {})
    current_champ_time_over_anchor = float(mixer_chain.get("current_ratio_to_reference_reported"))
    boards, _, boards_sha = read(STATE / "boards-2150.raw")
    champion_response, champion_response_bytes, champion_response_sha = read(STATE / "champions-mixer-2130.raw")
    champion_receipt, _, champion_receipt_sha = read(STATE / "champions-mixer-2130-receipt.json")
    current_champion = next((x for x in champion_response.get("champions", []) if x.get("current") is True), {})
    mixer_chain_edge = (mixer_chain.get("chain_edges_current_to_anchor") or [{}])[0]
    mixer_report_path = ROOT / mixer_chain_edge.get("report_path", "")
    mixer_report, mixer_report_bytes, mixer_report_sha = read(mixer_report_path)
    mixer_report_receipt = mixer_chain_edge.get("report_receipt")
    mixer_report_eval = next((x for x in mixer_report.get("evaluations", []) if x.get("board") == "mixer"), {})
    current_mixer_board = next((x for x in boards.get("boards", []) if x.get("id") == "mixer"), {})
    estimate = score / current_champ_time_over_anchor if score else None
    reported_estimate = root_row.get("candidate_time_over_current_champion_estimate")
    score_checks = {
        "pinned_score": score,
        "root_audit_score": root_row.get("score_vs_calibration_internal", {}).get("score"),
        "score_matches": bool(score is not None and math.isclose(float(score), float(root_row.get("score_vs_calibration_internal", {}).get("score", -1)), rel_tol=1e-12, abs_tol=1e-15)),
        "current36_over_public27_old_report": current_champ_time_over_anchor,
        "candidate_over_current36_estimate": estimate,
        "reported_estimate": reported_estimate,
        "estimate_matches": bool(estimate is not None and math.isclose(float(estimate), float(reported_estimate or -1), rel_tol=1e-12, abs_tol=1e-15)),
        "classification": "INFERRED_CROSS_BENCHMARK_VERSION_LOCAL_ENVIRONMENT_AND_SEEDS",
        "strict_converter_status": "UNKNOWN_CURRENT_REPORT_VERSION_AND_LOCAL_COHORT_MISMATCH",
    }
    if not score_checks["score_matches"] or not score_checks["estimate_matches"]:
        failures.append("score_reconstruction")

    mixer_record = read(HERE / "champion-only-record.json")[0]
    current_mixer_record = next((x for x in mixer_record.get("boards", []) if x.get("board") == "mixer"), {})
    mixer_binding_checks = {
        "current_board_and_response_publication_match": boards.get("publication_hash") == champion_response.get("publication_hash") == current_mixer_record.get("latest_board_publication_hash"),
        "current_champion_is36_and_source_private": current_champion.get("submission") == 36 and current_champion.get("source_available") is False,
        "current_champion_source_matches_record": current_champion.get("source_sha256") == current_mixer_record.get("champion_source_sha256"),
        "champion_receipt_matches_bytes": champion_receipt.get("status") == 200 and champion_receipt.get("sha256") == champion_response_sha and champion_receipt.get("bytes") == len(champion_response_bytes),
        "report36_receipt_matches_bytes": bool(mixer_report_receipt and mixer_report_receipt.get("status") == 200 and mixer_report_receipt.get("sha256") == mixer_report_sha and mixer_report_receipt.get("bytes") == len(mixer_report_bytes)),
        "report36_source_matches_current_champion": mixer_report.get("submission", {}).get("id") == 36 and mixer_report.get("submission", {}).get("source_sha256") == current_champion.get("source_sha256"),
        "report36_anchor_hash_is_public27": mixer_report_eval.get("reference_hash") == source_sha and mixer_report_eval.get("reference_promotion_id") == 25,
        "report36_config_differs_from_live_board": mixer_report_eval.get("config_hash") == mixer_chain.get("report_config_hash") and mixer_report_eval.get("config_hash") != current_mixer_board.get("config_hash"),
        "latest_strict_calibration_unknown": current_mixer_record.get("calibration_status") == "UNKNOWN_BENCHMARK_VERSION_CHANGED" and current_mixer_record.get("current_report_policy_matches") is False,
    }
    if not all(mixer_binding_checks.values()):
        failures.extend("current36_binding:" + k for k, ok in mixer_binding_checks.items() if not ok)

    summary_candidate = summary_results.get(entry["name"], {})
    results_candidate = next((x for x in results.get("results", []) if x.get("candidate") == entry["name"]), {})
    terminal_checks = {
        "ci_is_terminal_and_result_is_audited": ci.get("status") == "completed" and results.get("state") == "TERMINAL_ALL_MODEL_DATA_AUDITED",
        "plan_full_gate_absent": entry.get("full_gate") is False and not results.get("full_gates"),
        "proof_stays_declared_not_replayed": summary_candidate.get("proof_state") == "DECLARED_CORRECT_TYPECHECKED_NO_FULL_ORIGINAL_REPLAY" and results_candidate.get("candidate_proof") == "DECLARED_CORRECT_TYPECHECKED_NO_FULL_ORIGINAL_REPLAY",
        "result_has_no_full_gate_claim": "NOT_ESTABLISHED_NO_ORIGINAL_FULL_GATE_REPLAY" in results_candidate.get("eligibility", ""),
    }
    if not all(terminal_checks.values()):
        failures.extend("terminal_boundary:" + k for k, ok in terminal_checks.items() if not ok)

    output = {
        "round": "R27",
        "captured_at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
        "scope": "INDEPENDENT_B7_RAW_ARTIFACT_AUDIT_WITH_PINNED_R25_SCORER; NOT_CORRECT_OR_OFFICIAL_PERFORMANCE",
        "run": {"id": ci.get("databaseId"), "source_commit": ci.get("headSha"), "conclusion": ci.get("conclusion")},
        "plan": {"sha256": plan_sha, "artifact_plan_sha256": artifact_plan_sha, "official_commit": plan.get("official_commit")},
        "dispatch": {"path": dispatch_path.relative_to(ROOT).as_posix(), "checks": dispatch_checks},
        "artifact_integrity": {"outer": outer, "inner": inner, "outer_manifest_sha256": hashlib.sha256((RUN_DIR / "original-artifact-hashes.json").read_bytes()).hexdigest(), "inner_manifest_sha256": inner_manifest_sha},
        "public27_source": {"sha256": source_sha, "bytes": len(source), "receipt": source_receipt, "receipt_matches": source_receipt_ok, "body_included": False},
        "candidate": {"sha256": candidate_sha, "expected_sha256": entry["sha256"], "patch_sha256": sha(patch_path), "expected_patch_sha256": entry["patch_script_sha256"], "proof_state": summary_candidate.get("proof_state"), "full_gate": entry.get("full_gate"), "declares_correct": entry.get("declares_correct"), "transform_checks": transform_checks, "native_flags": flags, "seed_rows": seed_rows, "same_cpu": same_cpu, "pinned_score_and_current36_estimate": score_checks, "current36_binding_checks": mixer_binding_checks, "terminal_checks": terminal_checks},
        "MainExact": main_receipt,
        "results_file_sha256": results_sha,
        "root_audit_sha256": root_audit_sha,
        "official_report_chain_sha256": report_chain_sha,
        "mixer_report_sha256": mixer_report_sha,
        "mixer_response_receipt_sha256": champion_receipt_sha,
        "current_boards_sha256": boards_sha,
        "claim_boundary": "B7 is a five-round, three-inner-repetition, 2ms local screen against retired public #27, not a full Correct result or direct current #36 pair. Its current-champion estimate is inferred across benchmark version, environments and seeds.",
        "failures": failures,
        "status": "PASS_NATIVE_ONLY_EVIDENCE_AUDITED_NOT_CORRECT_OR_CHAMPION" if not failures else "AUDIT_FAILED",
    }
    OUT_PATH.write_text(json.dumps(output, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    print(json.dumps({"status": output["status"], "outer": outer.get("status"), "inner": inner.get("status"), "score": score_checks, "failures": failures}, ensure_ascii=False))
    return 0 if not failures else 1


if __name__ == "__main__":
    raise SystemExit(main())
