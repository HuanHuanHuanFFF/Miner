#!/usr/bin/env python3
"""Static audit of B9 public23/public27 GEMM-graft recipe and proof binding."""
from __future__ import annotations

import datetime
import hashlib
import importlib.util
import json
from pathlib import Path
import re
import subprocess
import sys

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
ROUND = HERE.parent
ROOT = ROUND.parents[3]
STATE = ROUND / "competition-state"
PLAN_PATH = ROUND / "ci-plan-batch9.json"
OUT_PATH = HERE / "audit-batch9-gemm27-static.json"


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


def main() -> int:
    failures: list[str] = []
    plan, plan_bytes, plan_sha = read(PLAN_PATH)
    source23_path = STATE / "source-private/submission23-Kernel.lean"
    source27_path = STATE / "source-private/submission27-Kernel.lean"
    source23 = source23_path.read_bytes()
    source27 = source27_path.read_bytes()
    source23_sha = hashlib.sha256(source23).hexdigest()
    source27_sha = hashlib.sha256(source27).hexdigest()
    receipts, _, receipts_sha = read(STATE / "public-source-and-report-receipts.json")
    receipt23 = next((x for x in receipts if x.get("url") == "https://conjectures.io/v1/competitions/torchlean/submissions/23/source"), None)
    receipt27 = next((x for x in receipts if x.get("url") == "https://conjectures.io/v1/competitions/torchlean/submissions/27/source"), None)
    latest_receipts, _, latest_receipts_sha = read(STATE / "normalized-champion-update-2150-receipts.json")
    if receipt23 is None:
        receipt23 = next((x for x in latest_receipts if x.get("url") == "https://conjectures.io/v1/competitions/torchlean/submissions/23/source"), None)
    source_checks = {
        "public23_receipt_matches_plan": bool(receipt23 and receipt23.get("status") == 200 and receipt23.get("sha256") == source23_sha == plan["candidates"][0]["fetch"]["sha256"] and receipt23.get("bytes") == len(source23)),
        "public27_receipt_matches_reference_and_extra_fetch": bool(receipt27 and receipt27.get("status") == 200 and receipt27.get("sha256") == source27_sha == plan["reference"]["sha256"] == plan["candidates"][0]["extra_fetches"][0]["sha256"] and receipt27.get("bytes") == len(source27)),
    }
    if not all(source_checks.values()):
        failures.extend("source:" + k for k, ok in source_checks.items() if not ok)

    candidate = plan["candidates"][0]
    patch_path = ROOT / candidate["patch_script"]
    patch = load_module(patch_path, "r27_b9_gemm_v2_static")
    result = patch.transform(source23, 23, candidate["variant"], donor_raw=source27)
    result_sha = hashlib.sha256(result).hexdigest()
    text = result.decode("utf-8")
    base_patch_path = ROUND / "development/ci-bridge/batch9/build_gemm27_on_public23.py"
    compactor_path = ROUND / "development/ci-bridge/batch9/compact_public23.py"
    base_patch = base_patch_path.read_text(encoding="utf-8")
    patch_text = patch_path.read_text(encoding="utf-8")
    source_files = []
    for rel in plan.get("owned_sources", []):
        path = ROOT / rel
        exists = path.is_file()
        digest = sha(path) if exists else None
        source_files.append({"path": rel, "exists": exists, "bytes": path.stat().st_size if exists else None, "sha256": digest})
        if not exists:
            failures.append("owned_source_missing:" + rel)

    transform_checks = {
        "patch_sha_matches_plan": sha(patch_path) == candidate.get("patch_script_sha256"),
        "base_recipe_sha_matches_v2_pin": sha(base_patch_path) == "a920b7ab2545ad4e7eb4f009b29c5a78da2ae0fa9f41415c9546e0f679049736" and "BASE_RECIPE_SHA=" in patch_text,
        "compactor_sha_matches_base_pin": sha(compactor_path) == "4c3dd79284f6701d3b128687f9f973f47d9236f8d9db502d398e2eb4d131e129",
        "candidate_sha_matches_plan": result_sha == candidate["sha256"] == "6fe5feb6cf0b919a9700f5f05264b1e98e24d7ee74b9d2853c1e55be866d4ada",
        "candidate_size_matches_plan_and_cap": len(result) == candidate["bytes"] == 252719 and len(result) <= 256000,
        "extra_fetch27_is_declared": candidate.get("extra_fetches", [{}])[0].get("sha256") == source27_sha and candidate.get("extra_fetches", [{}])[0].get("submission") == 27,
        "preserves_original_all12_correct_entry": text.count("theorem correct:Obligation kernels:=") == 1 and "retainedCorrect" not in text,
        "binds_new_gemm_kernel": "dense:=⟨YaV,Ya3Q⟩" in text,
        "connects_linear_and_gemm_proofs": "ZcC,Zc0Q" in text and "Zc0Q" in text,
        "uses_proved_linear_fallback": "gemmWith Yn" in text and "gemmWith Yn batch m k n A B" in text,
        "allpositive_threshold_and_nonfinite_fallback": "if k<1||!(A.all finiteWord&&B.all finiteWord)" in text,
        "donor_small_k_engine_not_copied": "then Ya3 batch m k n A B else" not in text,
        "no_explicit_sorry_token": "sorry" not in text,
        "correctness_gate_is_required_by_plan": candidate.get("full_gate") is True and candidate.get("declares_correct") is True,
    }
    if not all(transform_checks.values()):
        failures.extend("transform:" + k for k, ok in transform_checks.items() if not ok)

    base_script_checks = {
        "shared_declaration_bytes_checked": all(x in base_patch for x in ("Yo","Yq","Zy","Yn","Zi","Z5","ZcC")),
        "alias_difference_is_explicitly_closed": "differences=={'CQ':['Nat.pos_of_mul_pos_right',None]}" in base_patch,
        "graft_import_replaces_only_missing_declarations": "NAMES=['Yos','Yqs','Yoc','Gsn','Gcg','Ya3Q','Xg','Fw','Zg2','Zc0Q']" in base_patch,
        "public23_compactor_recipe_is_proof_only": sha(compactor_path) == "4c3dd79284f6701d3b128687f9f973f47d9236f8d9db502d398e2eb4d131e129",
    }
    if not all(base_script_checks.values()):
        failures.extend("proof_recipe:" + k for k, ok in base_script_checks.items() if not ok)

    runner_path = ROUND / "development/ci-bridge/runner.py"
    runner_text = runner_path.read_text(encoding="utf-8")
    runner_checks = {
        "runner_supports_extra_fetches": "for extra in entry.get('extra_fetches',[]):public_source(extra)" in runner_text,
        "source_materializes_under_private_cache": "UP/'r27-source-private'" in runner_text,
        "full_gate_flag_branches_before_native_build": runner_text.index("if entry.get('full_gate')") < runner_text.index("g._budget.reset(300"),
        "full_gate_is_original_verifier": "[py,'-m','verification'" in runner_text and "verdict.get('passed')" in runner_text,
        "native_measurement_waits_after_build": runner_text.index("binary,info=build(entry)") < runner_text.index("for seed in plan['seeds']"),
        "standard_mode_omits_quick_config_flag": "measurement_mode=='quick'" in runner_text and "['--quick'] if measurement_mode=='quick' else []" in runner_text,
        "standard_mode_asserts_11x3x50": "else:assert (timing['rounds'],timing['inner'],timing['cell_ms'])==(11,3,50)" in runner_text,
    }
    if not all(runner_checks.values()):
        failures.extend("runner:" + k for k, ok in runner_checks.items() if not ok)

    report_chain, _, report_chain_sha = read(HERE / "official-report-chain.json")
    mixer_chain = next((x for x in report_chain.get("boards", []) if x.get("board") == "mixer"), {})
    mixer_report_config = mixer_chain.get("report_config_hash")
    current_mixer_record = read(HERE / "champion-only-record.json")[0]
    current_mixer = next((x for x in current_mixer_record.get("boards", []) if x.get("board") == "mixer"), {})
    board_snapshot, _, board_sha = read(STATE / "boards-2150.raw")
    mixer_board = next((x for x in board_snapshot.get("boards", []) if x.get("id") == "mixer"), {})
    freeze9, _, freeze9_sha = read(ROUND / "requests/FREEZE9-STANDARD-READING-BARRIER.json")
    champion_checks = {
        "current_target_is_mixer36": plan.get("champion", {}).get("submission") == 36 and plan.get("champion", {}).get("source_sha256") == current_mixer.get("champion_source_sha256"),
        "current36_source_unavailable": current_mixer.get("champion_source_available") is False,
        "retired27_not_mislabeled_current": plan.get("reference", {}).get("comparison_role", "").find("NOT current champion") >= 0,
        "current36_report_ratio_is_saved": mixer_chain.get("current_ratio_to_reference_reported") == plan.get("champion", {}).get("current_champion_over_calibration"),
        "old_report_config_differs_from_live_board": mixer_report_config != mixer_board.get("config_hash"),
        "strict_current36_calibration_unknown": current_mixer.get("calibration_status") == "UNKNOWN_BENCHMARK_VERSION_CHANGED" and current_mixer.get("current_report_policy_matches") is False,
        "human_target_current36_only": plan.get("human_performance_target") == "Only currentMixer36, public27calibrationcarrier",
    }
    if not all(champion_checks.values()):
        failures.extend("champion:" + k for k, ok in champion_checks.items() if not ok)

    plan_checks = {
        "public_run_no_private": plan.get("allow_private") is False,
        "mixer36_only_target": plan.get("human_performance_target") == "Only currentMixer36, public27calibrationcarrier",
        "standard_measurement_mode": plan.get("measurement_mode") == "standard",
        "two_distinct_roots": len(plan.get("seeds", [])) == 2 and plan.get("seeds", [None, None])[0] != plan.get("seeds", [None, None])[1],
        "full_original_gate_required": candidate.get("full_gate") is True and candidate.get("declares_correct") is True,
        "freeze_request_binds_same_candidate": "6fe5feb6" in freeze9.get("candidate", ""),
        "freeze_request_requires_standard_contract": "standard 11/3/50" in freeze9.get("plan9", ""),
        "plan_official_head_current": plan.get("official_commit") == "27fb1d19c712ead50ad34b4ad0d4ba597161e616",
    }
    if not all(plan_checks.values()):
        failures.extend("plan:" + k for k, ok in plan_checks.items() if not ok)

    dispatch_path = ROUND / "evidence/dispatch-20261029T232441Z/dispatch.json"
    dispatch, _, dispatch_sha = read(dispatch_path)
    frozen = dispatch.get("frozen_files", {})
    runner_rel = "competitions/torchlean/candidates/r27-5h-20261029T194443Z/development/ci-bridge/runner.py"
    prepare_rel = "competitions/torchlean/candidates/r27-5h-20261029T194443Z/development/ci-bridge/prepare-current.sh"
    dispatch_plan_rel = "competitions/torchlean/candidates/r27-5h-20261029T194443Z/ci-plan.json"
    frozen_owned_checks = {rel: ROOT.joinpath(*Path(rel).parts).is_file() and sha(ROOT.joinpath(*Path(rel).parts)) == frozen.get(rel) for rel in plan.get("owned_sources", [])}
    try:
        runner_blob = subprocess.run(["git", "show", f"{dispatch.get('source_commit')}:{runner_rel}"], cwd=ROOT, capture_output=True, check=True).stdout
        runner_blob_text = runner_blob.decode("utf-8")
    except (subprocess.CalledProcessError, FileNotFoundError):
        runner_blob = b""
        runner_blob_text = ""
    dispatch_checks = {
        "dispatch_identified": dispatch.get("state") == "RUN_IDENTIFIED",
        "plan_hash_matches_dispatch": plan_sha == frozen.get(dispatch_plan_rel),
        "source_commit_matches_run": dispatch.get("source_commit") == (dispatch.get("run") or {}).get("headSha"),
        "public_and_allow_private_false": dispatch.get("repository_public") is True and str(dispatch.get("request", {}).get("inputs", {}).get("allow_private", "")).lower() == "false",
        "dispatch_seed_matches_plan": str(dispatch.get("request", {}).get("inputs", {}).get("seed")) == str(plan.get("dispatch_seed")),
        "candidate_patch_hash_frozen": frozen.get(candidate["patch_script"]) == candidate.get("patch_script_sha256"),
        "owned_sources_match_frozen_hashes": all(frozen_owned_checks.values()),
        "prepare_hash_frozen": bool(frozen.get(prepare_rel)),
        "runner_blob_hash_matches_dispatch": hashlib.sha256(runner_blob).hexdigest() == frozen.get(runner_rel),
        "runner_materializes_extra_fetches": "for extra in entry.get('extra_fetches',[]):public_source(extra)" in runner_blob_text,
        "runner_full_gate_before_native_build": bool(runner_blob_text) and runner_blob_text.index("if entry.get('full_gate')") < runner_blob_text.index("g._budget.reset(300"),
        "runner_standard_measurement_contract": "else:assert (timing['rounds'],timing['inner'],timing['cell_ms'])==(11,3,50)" in runner_blob_text,
    }
    if not all(dispatch_checks.values()):
        failures.extend("dispatch:" + key for key, ok in dispatch_checks.items() if not ok)
    b9_dispatch_exists = True
    output = {
        "round": "R27",
        "captured_at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
        "scope": "READ_ONLY_STATIC_RECIPE_AND_PROOF_BINDING_AUDIT; NO_COMPILE_OR_CI",
        "plan": {"path": PLAN_PATH.relative_to(ROOT).as_posix(), "sha256": plan_sha, "batch": plan.get("batch"), "scope": plan.get("scope"), "official_commit": plan.get("official_commit"), "board": plan.get("board")},
        "freeze_request_sha256": freeze9_sha,
        "plan_checks": plan_checks,
        "sources": {"public23_sha256": source23_sha, "public27_sha256": source27_sha, "public23_receipt": receipt23, "public27_receipt": receipt27, "receipts_manifest_sha256": receipts_sha, "latest_receipts_manifest_sha256": latest_receipts_sha, "receipt_checks": source_checks, "source_bodies_in_output": False},
        "candidate": {"name": candidate.get("name"), "patch_path": candidate.get("patch_script"), "patch_sha256": sha(patch_path), "expected_patch_sha256": candidate.get("patch_script_sha256"), "candidate_sha256": result_sha, "expected_candidate_sha256": candidate.get("sha256"), "bytes": len(result), "bytes_under_cap": 256000-len(result), "full_gate": candidate.get("full_gate"), "declares_correct": candidate.get("declares_correct"), "proof_state": candidate.get("proof_state"), "checks": transform_checks},
        "recipe_files": source_files,
        "proof_recipe_checks": base_script_checks,
        "runner_checks": runner_checks,
        "current_mixer_champion": {"source_sha256": current_mixer.get("champion_source_sha256"), "source_available": current_mixer.get("champion_source_available"), "current_ratio_over_public27_old_report": mixer_chain.get("current_ratio_to_reference_reported"), "old_report_config_hash": mixer_report_config, "live_board_config_hash": mixer_board.get("config_hash"), "checks": champion_checks},
        "official_report_chain_sha256": report_chain_sha,
        "boards_sha256": board_sha,
        "b9_dispatch_receipt_available": b9_dispatch_exists,
        "dispatch": {"path": dispatch_path.relative_to(ROOT).as_posix(), "sha256": dispatch_sha, "run_id": (dispatch.get("run") or {}).get("databaseId"), "run_status": (dispatch.get("run") or {}).get("status"), "checks": dispatch_checks, "frozen_owned_sources": frozen_owned_checks},
        "acceptance_barrier": "B9 is active/acceptance-only after dispatch; this audit read plan/dispatch/source hashes only, not run outputs.",
        "graft_ci_full_gate_result": "NOT_RUN",
        "compile_executed_by_this_audit": False,
        "candidate_output_written_by_this_audit": False,
        "failures": failures,
        "status": "PASS_STATIC_ONLY_FULL_GATE_STILL_REQUIRED" if not failures else "AUDIT_FAILED",
    }
    OUT_PATH.write_text(json.dumps(output, indent=2, ensure_ascii=False)+"\n", encoding="utf-8")
    print(json.dumps({"status": output["status"], "plan_sha256": plan_sha, "candidate_sha256": result_sha, "candidate_bytes": len(result), "b9_dispatch_receipt_available": b9_dispatch_exists, "runner_checks": runner_checks, "champion_checks": champion_checks, "failures": failures}, ensure_ascii=False))
    return 0 if not failures else 1


if __name__ == "__main__":
    raise SystemExit(main())
