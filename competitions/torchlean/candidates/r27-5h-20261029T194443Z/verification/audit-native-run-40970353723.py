#!/usr/bin/env python3
"""Independent read-only B8 artifact audit with the pinned R25 scorer."""
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
RUN_DIR = ROUND / "evidence/40970353723"
PLAN_PATH = ROUND / "ci-plan-batch8.json"
RESULTS_PATH = ROUND / "CI-RESULTS-BATCH8.json"
OUT_PATH = HERE / "audit-native-run-40970353723.json"


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
    return [re.sub(r"(?<=/)(?:benchExact|r27Native)(?=\.|$)", "<BIN>", re.sub(r"(?<=/)(?:MainExact|R27NativeMain)(?=\.)", "<MAIN>", x)) for x in args]


def main() -> int:
    failures: list[str] = []
    plan, plan_bytes, plan_sha = read(PLAN_PATH)
    ci, _, ci_sha = read(RUN_DIR / "ci-run.json")
    root_audit, _, root_audit_sha = read(RUN_DIR / "root-native-audit.json")
    results_present = RESULTS_PATH.is_file()
    results_doc, _, results_sha = read(RESULTS_PATH) if results_present else ({}, b"", None)
    original_manifest, _, original_manifest_sha = read(RUN_DIR / "original-artifact-hashes.json")
    artifact_dir = RUN_DIR / original_manifest["directory"]
    summary, _, summary_sha = read(artifact_dir / "summary.json")
    artifact_plan, artifact_plan_bytes, artifact_plan_sha = read(artifact_dir / "plan.json")
    file_manifest, _, inner_manifest_sha = read(artifact_dir / "file-hashes.json")

    r26_path = ROOT / "competitions/torchlean/candidates/r26-1h-20261029T085515Z/verification/analyze-native-only.py"
    r26 = load_module(r26_path, "r27_b8_pinned_r26_auditor")
    mod, modules, pins = r26.r25_tools()
    outer = r26.audit_tree(artifact_dir, original_manifest.get("files", {}))
    inner = r26.audit_tree(artifact_dir, file_manifest, excluded=("file-hashes.json",))
    if outer.get("status") != "PASS":
        failures.append("outer_hashes")
    if inner.get("status") != "PASS":
        failures.append("inner_hashes")

    dispatch_path, dispatch = r26.find_dispatch(RUN_DIR.parent, "40970353723")
    frozen = dispatch.get("frozen_files", {})
    owned_rows = []
    for rel in plan.get("owned_sources", []):
        p = ROOT / rel
        got = sha(p) if p.is_file() else None
        passed = got == frozen.get(rel)
        owned_rows.append({"path": rel, "sha256": got, "dispatch_sha256": frozen.get(rel), "pass": passed})
        if not passed:
            failures.append("owned_dispatch_hash:" + rel)
    candidate_patches_frozen = all(x.get("patch_script") in frozen and frozen.get(x.get("patch_script")) == x.get("patch_script_sha256") for x in plan.get("candidates", []))
    dispatch_checks = {
        "run_id_and_commit_match": str((dispatch.get("run") or {}).get("databaseId")) == str(ci.get("databaseId")) == "40970353723" and dispatch.get("source_commit") == ci.get("headSha"),
        "public_repository_allow_private_false": dispatch.get("repository_public") is True and str(dispatch.get("request", {}).get("inputs", {}).get("allow_private", "")).lower() == "false",
        "plan_hash_matches_frozen_ci_plan": plan_sha == artifact_plan_sha == frozen.get("competitions/torchlean/candidates/r27-5h-20261029T194443Z/ci-plan.json"),
        "all_owned_sources_frozen": all(x.get("pass") for x in owned_rows),
        "all_candidate_patches_frozen": candidate_patches_frozen,
        "official_head_matches_plan": plan.get("official_commit") == artifact_plan.get("official_commit") == "27fb1d19c712ead50ad34b4ad0d4ba597161e616",
    }
    if not all(dispatch_checks.values()):
        failures.extend("dispatch:" + k for k, ok in dispatch_checks.items() if not ok)

    # Verify exact public23 base and reconstruct all three candidate outputs in memory.
    source_path = STATE / "source-private/submission23-Kernel.lean"
    source = source_path.read_bytes()
    source_sha = hashlib.sha256(source).hexdigest()
    source_receipts, _, source_receipts_sha = read(STATE / "normalized-champion-update-2150-receipts.json")
    source_receipt = next((x for x in source_receipts if x.get("url") == "https://conjectures.io/v1/competitions/torchlean/submissions/23/source"), None)
    source_ok = bool(source_receipt and source_receipt.get("status") == 200 and source_receipt.get("sha256") == source_sha == plan["reference"]["sha256"] and source_receipt.get("bytes") == len(source))
    if not source_ok:
        failures.append("public23_source_receipt")
    transforms = []
    for entry in plan.get("candidates", []):
        patch_path = ROOT / entry["patch_script"]
        module = load_module(patch_path, "r27_b8_terminal_" + entry["name"])
        result_bytes = module.transform(source, 23, entry["variant"])
        digest = hashlib.sha256(result_bytes).hexdigest()
        code = result_bytes.decode("utf-8")
        checks = {
            "patch_matches_plan_and_dispatch": sha(patch_path) == entry.get("patch_script_sha256") == frozen.get(entry["patch_script"]),
            "candidate_hash_matches_plan": digest == entry.get("sha256"),
            "candidate_bytes_match_plan": len(result_bytes) == entry.get("bytes"),
            "full_gate_false": entry.get("full_gate") is False,
            "declares_correct_false": entry.get("declares_correct") is False,
            "proof_not_inherited": "theorem retainedCorrect:" in code and "theorem correct:" not in code,
        }
        if not all(checks.values()):
            failures.extend(f"candidate:{entry.get('name')}:{k}" for k, ok in checks.items() if not ok)
        transforms.append({"name": entry.get("name"), "candidate_sha256": digest, "expected_sha256": entry.get("sha256"), "bytes": len(result_bytes), "expected_bytes": entry.get("bytes"), "proof_state": entry.get("proof_state"), "checks": checks})

    # Validate the terminal runner, gate boundary, and MainExact preservation.
    runner_rel = "competitions/torchlean/candidates/r27-5h-20261029T194443Z/development/ci-bridge/runner.py"
    runner_hash = frozen.get(runner_rel)
    try:
        runner_blob = subprocess.run(["git", "show", f"{ci['headSha']}:{runner_rel}"], cwd=ROOT, capture_output=True, check=True).stdout
        runner_blob_sha = hashlib.sha256(runner_blob).hexdigest()
        runner_text = runner_blob.decode("utf-8")
    except (subprocess.CalledProcessError, FileNotFoundError):
        runner_blob_sha, runner_text = None, ""
    main_hash = summary.get("owned_main_equals_original_sha256")
    main_receipt = {
        "sha256": main_hash,
        "root_audit_sha256": root_audit.get("MainExact_sha256"),
        "runner_dispatch_sha256": runner_hash,
        "runner_commit_blob_sha256": runner_blob_sha,
        "runner_blob_matches_dispatch": runner_blob_sha == runner_hash,
        "copy_assertion_present": "mainfile.write_bytes(mainbytes)" in runner_text and "assert mainfile.read_bytes()==mainbytes" in runner_text,
        "direct_official_bytes_in_artifact": False,
    }
    if main_hash != root_audit.get("MainExact_sha256") or runner_blob_sha != runner_hash or not main_receipt["copy_assertion_present"]:
        failures.append("MainExact_copy_receipt")
    gate_boundary_checks = {
        "all_plan_candidates_are_cost_only": all(x.get("full_gate") is False and x.get("declares_correct") is False for x in plan.get("candidates", [])),
        "runner_fullgate_branch_precedes_native_build": bool(runner_text and runner_text.index("if entry.get('full_gate')") < runner_text.index("g._budget.reset(300")),
        "runner_profiles_reference_only": "if plan.get('profile_control') and entry.get('reference')" in runner_text,
    }
    if not all(gate_boundary_checks.values()):
        failures.extend("gate_boundary:" + k for k, ok in gate_boundary_checks.items() if not ok)

    # Bind the current #43 report edge to the fixed reference, then rescore all candidates.
    boards, _, boards_sha = read(STATE / "boards-2150.raw")
    champions, champion_bytes, champions_sha = read(STATE / "champions-normalized_mlp-2150.raw")
    champion_receipts, _, champion_receipts_sha = read(STATE / "normalized-champion-update-2150-receipts.json")
    report43, report43_bytes, report43_sha = read(STATE / "submission43-report.raw")
    chain, _, chain_sha = read(HERE / "current43-report-chain.json")
    board = modules["config"].Config.load(artifact_dir / "overall-config.toml").plan("normalized_mlp")
    current_board = next((x for x in boards.get("boards", []) if x.get("id") == "normalized_mlp"), {})
    current_champion = next((x for x in champions.get("champions", []) if x.get("current") is True), {})
    report_eval = next((x for x in report43.get("evaluations", []) if x.get("board") == "normalized_mlp"), {})
    report_receipt = next((x for x in champion_receipts if x.get("url") == "https://conjectures.io/v1/competitions/torchlean/submissions/43/report"), None)
    current43_ratio = float(report_eval.get("decision", {}).get("score"))
    current43_checks = {
        "current_response_matches_latest_board": champions.get("publication_hash") == boards.get("publication_hash"),
        "current_champion_is43_source_unavailable": current_champion.get("submission") == 43 and current_champion.get("source_available") is False,
        "current_report_receipt_matches_bytes": bool(report_receipt and report_receipt.get("status") == 200 and report_receipt.get("sha256") == report43_sha and report_receipt.get("bytes") == len(report43_bytes)),
        "current_report_config_matches_live_board": report_eval.get("config_hash") == current_board.get("config_hash"),
        "current_report_anchor_is_public23": report_eval.get("reference_hash") == source_sha and report_eval.get("reference_promotion_id") == 24,
        "current43_chain_audit_passed": chain.get("status", "").startswith("CURRENT43_REPORT_EDGE_BOUND") and not chain.get("audit_failures"),
    }
    if not all(current43_checks.values()):
        failures.extend("current43:" + k for k, ok in current43_checks.items() if not ok)

    # Rebuild every paired row from raw JSON and call the pinned R25 scorer.
    config = modules["config"].Config.load(artifact_dir / "overall-config.toml")
    model = config.plan("normalized_mlp")
    expected_cells = list(model["cells"])
    expected_timing = config.timing | model["timing"] | config.environments["local"]["timing"]
    expected_timing.update(build_seconds=300, cached_build_seconds=180, benchmark_seconds=300, run_seconds=120)
    summary_by_name = {x.get("name"): x for x in summary.get("results", []) if isinstance(x, dict)}
    root_rows = {x.get("candidate"): x for x in root_audit.get("results", []) if isinstance(x, dict)}
    candidate_rows = []
    all_cpus: list[dict] = []
    for entry in plan.get("candidates", []):
        pairs: list[tuple[dict, dict]] = []
        seed_rows = []
        name = entry["name"]
        for seed in plan.get("seeds", []):
            seed = int(seed)
            request, _, request_sha = read(artifact_dir / f"{name}-{seed}-request.json")
            raw, _, raw_sha = read(artifact_dir / f"{name}-{seed}-measurement.json")
            result = raw.get("result")
            if not isinstance(result, dict):
                failures.append("measurement_missing:" + name + ":" + str(seed))
                continue
            expected = {"environment":"local","identity":config.environments["local"]["identity"],"seed":seed,"candidate_hash":entry["sha256"],"reference_hash":plan["reference"]["sha256"],"cells":expected_cells,"timing":expected_timing,"benchmark_identity":model["benchmark_identity"],"workloads":modules["multiseed"].workloads(seed)}
            request_checks = {k: request.get(k) == v for k,v in expected.items()}
            try:
                modules["config"].MeasurementRequest.parse(request)
                request_checks["parse"] = True
            except Exception:
                request_checks["parse"] = False
            checked = mod.measurement_check(request, raw, model["cells"], modules)
            r26.raw_rounds(artifact_dir, name, seed, request, result)
            paired = sum(len(r.get("cells",{})) for r in result.get("rounds",[]))
            ns_values = 2*paired
            checksum_pairs = sum(c.get("reference_checksum")==c.get("candidate_checksum") for r in result.get("rounds",[]) for c in r.get("cells",{}).values())
            provenance = result.get("provenance",{})
            built = summary_by_name.get(name,{}).get("binary_sha256")
            refbin = summary_by_name.get("calibration",{}).get("binary_sha256")
            provenance_checks = {"identity":provenance.get("identity")==request.get("identity"),"candidate_binary":provenance.get("candidate_binary")==built,"reference_binary":provenance.get("reference_binary")==refbin}
            if not all(request_checks.values()):
                failures.extend(f"request:{name}:{seed}:{k}" for k,v in request_checks.items() if not v)
            if checked.get("status")!="PASS" or paired!=180 or ns_values!=360 or checksum_pairs!=180 or checked.get("checksum_mismatches")!=0:
                failures.append("measurement_check:"+name+":"+str(seed))
            if not all(provenance_checks.values()):
                failures.extend(f"provenance:{name}:{seed}:{k}" for k,v in provenance_checks.items() if not v)
            all_cpus.append({k:provenance.get(k) for k in ("identity","machine","architecture","cpu_affinity")})
            seed_rows.append({"seed":seed,"request_sha256":request_sha,"measurement_sha256":raw_sha,"paired_rows":paired,"ns_values":ns_values,"checksum_pairs":checksum_pairs,"checksum_mismatches":checked.get("checksum_mismatches"),"rounds":len(result.get("rounds",[])),"cells_per_round":[len(r.get("cells",{})) for r in result.get("rounds",[])],"reference_first_sequence":[r.get("reference_first") for r in result.get("rounds",[])],"request_checks":request_checks,"pinned_measurement_check":checked,"provenance":{**provenance,"checks":provenance_checks}})
            pairs.append((request,result))
        local_plan = dict(model)
        local_plan["strata"] = [{"environment":q["environment"],"identity":q["identity"],"seed":q["seed"],"weight":1/len(pairs),"timing":q["timing"]} for q,_ in pairs]
        fixed = modules["scoring"].assess(local_plan,pairs) if len(pairs)==2 else None
        fixed_score = fixed.get("score") if fixed else None
        root_row = root_rows.get(name,{})
        estimate = fixed_score/current43_ratio if fixed_score else None
        root_score = root_row.get("score_vs_calibration_internal",{}).get("score")
        root_estimate = root_row.get("candidate_time_over_current_champion_estimate")
        root_score_block = root_row.get("score_vs_calibration_internal", {})
        result_checks = {"pinned_score":fixed_score,"root_score":root_score,"score_matches":bool(fixed_score is not None and math.isclose(float(fixed_score),float(root_score or -1),rel_tol=1e-12,abs_tol=1e-15)),"fixed_scorer_guard_passed":fixed.get("guard_passed") if fixed else None,"root_guard_passed":root_score_block.get("guard_passed"),"guard_status_matches":bool(fixed is not None and fixed.get("guard_passed")==root_score_block.get("guard_passed")),"fixed_scorer_outcome":fixed.get("outcome") if fixed else None,"root_outcome":root_score_block.get("outcome"),"outcome_matches":bool(fixed is not None and fixed.get("outcome")==root_score_block.get("outcome")),"candidate_over_current43_estimate":estimate,"root_estimate":root_estimate,"estimate_matches":bool(estimate is not None and math.isclose(float(estimate),float(root_estimate or -1),rel_tol=1e-12,abs_tol=1e-15)),"classification":"INFERRED_SCREEN_LOCAL_ENVIRONMENT_AND_SEEDS","strict_converter_status":"UNKNOWN_CURRENT_REPORT_PRODUCTION_INPUTS_MISMATCH"}
        if not result_checks["score_matches"] or not result_checks["estimate_matches"] or not result_checks["guard_status_matches"] or not result_checks["outcome_matches"]:
            failures.append("score_reconstruction:"+name)
        candidate_info = summary_by_name.get(name,{})
        candidate_rows.append({"name":name,"sha256":entry["sha256"],"proof_state":candidate_info.get("proof_state"),"full_gate":entry.get("full_gate"),"declares_correct":entry.get("declares_correct"),"seeds":seed_rows,"score_and_current43_estimate":result_checks,"status":root_row.get("status")})

    ci_result_rows = {x.get("candidate"): x for x in results_doc.get("results", []) if isinstance(x, dict)}
    ci_results_checks = {
        "file_present": results_present,
        "run_id_matches": results_doc.get("run") == 40970353723,
        "terminal_state_is_all_candidates_audited": results_doc.get("state") == "ALL_THREE_CANDIDATES_NATIVE_COMPLETE_ALL_RAW_BYTES_AUDITED",
        "outer_hash_manifest_matches": results_doc.get("outer_hashes", {}).get("status") == "PASS" and results_doc.get("outer_hashes", {}).get("files") == outer.get("files"),
        "inner_hash_manifest_matches": results_doc.get("inner_hashes", {}).get("status") == "PASS" and results_doc.get("inner_hashes", {}).get("files") == inner.get("files"),
        "no_full_gates_by_plan": all(x.get("full_gate") is False for x in plan.get("candidates", [])) and not results_doc.get("full_gates"),
        "all_three_candidate_rows_present": len(ci_result_rows) == len(plan.get("candidates", [])),
    }
    for row in candidate_rows:
        ci_row = ci_result_rows.get(row["name"], {})
        result_checks = row["score_and_current43_estimate"]
        root_factor = ci_row.get("candidate_time_over_current_champion_estimate")
        ci_score = (ci_row.get("score_vs_calibration_internal") or {}).get("score")
        if ci_score is None or root_factor is None or not math.isclose(float(ci_score), float(result_checks["pinned_score"]), rel_tol=1e-12, abs_tol=1e-15) or not math.isclose(float(root_factor), float(result_checks["candidate_over_current43_estimate"]), rel_tol=1e-12, abs_tol=1e-15):
            ci_results_checks[f"row_matches:{row['name']}"] = False
        else:
            ci_results_checks[f"row_matches:{row['name']}"] = True
    if not all(ci_results_checks.values()):
        failures.extend("ci_results:" + k for k, ok in ci_results_checks.items() if not ok)

    same_cpu = bool(all_cpus) and all(tuple(all_cpus[0].get(k) for k in ("identity","machine","architecture","cpu_affinity")) == tuple(x.get(k) for k in ("identity","machine","architecture","cpu_affinity")) for x in all_cpus[1:])
    if not same_cpu:
        failures.append("same_cpu_across_candidates")

    cost_profile = summary.get("cost_profile",{})
    profile_path = artifact_dir / "cost-profile/profile.json"
    profile_doc = read(profile_path)[0] if profile_path.is_file() else {}
    profile_totals = {}
    for row in profile_doc.get("rows", []):
        for kernel, values in row.get("instrumented_kernel_entry_times", {}).items():
            accum = profile_totals.setdefault(kernel, {"calls": 0, "inclusive_ns": 0, "exclusive_ns": 0})
            for field in accum:
                accum[field] += values.get(field, 0)
    total_exclusive_ns = sum(x["exclusive_ns"] for x in profile_totals.values())
    profile_summary = {
        kernel: {**values, "share_of_instrumented_exclusive_ns": values["exclusive_ns"] / total_exclusive_ns if total_exclusive_ns else None}
        for kernel, values in profile_totals.items()
    }
    profile_checks = {
        "profile_completed": cost_profile.get("state") == "COMPLETE_INSTRUMENTED_COST_DISCRIMINATOR" and profile_doc.get("scope") == "INSTRUMENTED_COST_DISCRIMINATOR_ONLY_NOT_OFFICIAL_TIMING_OR_GATE",
        "six_cells": len(profile_doc.get("rows",[])) == 6,
        "checksums_36": sum(x.get("checksum_pairs",0) for x in profile_doc.get("rows",[])) == 36,
        "reference_only_diagnostic": profile_doc.get("control_binary_sha256") == summary_by_name.get("calibration",{}).get("binary_sha256"),
        "three_named_kernel_entry_groups": set(profile_totals) == {"linear", "layernorm", "rmsnorm"},
        "profile_time_is_positive": total_exclusive_ns > 0,
    }
    if not all(profile_checks.values()):
        failures.extend("profile:" + k for k, ok in profile_checks.items() if not ok)

    output = {
        "round":"R27",
        "captured_at_utc":datetime.datetime.now(datetime.timezone.utc).isoformat(),
        "scope":"INDEPENDENT_B8_RAW_ARTIFACT_AUDIT_WITH_PINNED_R25_SCORER; ALL_CANDIDATES_UNPROVED",
        "run":{"id":ci.get("databaseId"),"source_commit":ci.get("headSha"),"conclusion":ci.get("conclusion")},
        "plan":{"sha256":plan_sha,"artifact_plan_sha256":artifact_plan_sha,"official_commit":plan.get("official_commit")},
        "dispatch":{"path":dispatch_path.relative_to(ROOT).as_posix(),"checks":dispatch_checks,"owned_source_count":len(owned_rows)},
        "artifact_integrity":{"outer":outer,"inner":inner},
        "source23":{"sha256":source_sha,"receipt":source_receipt,"receipt_matches":source_ok,"body_included":False},
        "candidate_transforms":transforms,
        "MainExact":{"sha256":summary.get("owned_main_equals_original_sha256"),"root_audit_sha256":root_audit.get("MainExact_sha256")},
        "candidate_results":candidate_rows,
        "CI_RESULTS_batch8":{"sha256":results_sha,"checks":ci_results_checks},
        "same_cpu_across_candidates":same_cpu,
        "profile":{"state":cost_profile.get("state"),"checks":profile_checks,"scope":profile_doc.get("scope"),"profile_sha256":sha(profile_path) if profile_path.is_file() else None,"exclusive_ns_total":total_exclusive_ns,"kernel_entry_summary":profile_summary,"attribution_boundary":profile_doc.get("boundary")},
        "current43":{"boards_sha256":boards_sha,"champions_sha256":champions_sha,"report_sha256":report43_sha,"report_config_hash":report_eval.get("config_hash"),"report_score_current43_over_public23":current43_ratio,"report_checks":current43_checks,"calibration_status":"INFERRED"},
        "root_audit_sha256":root_audit_sha,
        "results_file_present":results_present,
        "claim_boundary":"B8 completed a successful NativeOnly local-cost run. All three candidates lack new correctness proofs and failed no formal gate only because none was planned; current-#43 estimates are inferred local screens, not official promotion.",
        "failures":failures,
        "status":"PASS_NATIVE_ONLY_EVIDENCE_AUDITED_NOT_CORRECT_OR_CHAMPION" if not failures else "AUDIT_FAILED",
    }
    OUT_PATH.write_text(json.dumps(output,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({"status":output["status"],"outer":outer.get("status"),"inner":inner.get("status"),"candidate_results":[{"name":x["name"],"multiplier":x["score_and_current43_estimate"]["candidate_over_current43_estimate"],"score_ok":x["score_and_current43_estimate"]["score_matches"]} for x in candidate_rows],"profile":profile_checks,"failures":failures},ensure_ascii=False))
    return 0 if not failures else 1


if __name__ == "__main__":
    raise SystemExit(main())
