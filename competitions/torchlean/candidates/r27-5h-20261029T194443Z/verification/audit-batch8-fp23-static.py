#!/usr/bin/env python3
"""Static proof-binding and recipe-hash audit for the frozen B8 FP23 recipes."""
from __future__ import annotations

import datetime
import hashlib
import importlib.util
import json
from pathlib import Path
import sys

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
ROUND = HERE.parent
ROOT = ROUND.parents[3]
STATE = ROUND / "competition-state"
PLAN_PATH = ROUND / "ci-plan-batch8.json"
OUT_PATH = HERE / "audit-batch8-fp23-static.json"


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
    source_path = STATE / "source-private/submission23-Kernel.lean"
    source = source_path.read_bytes()
    source_sha = hashlib.sha256(source).hexdigest()
    receipts, _, receipts_sha = read(STATE / "normalized-champion-update-2150-receipts.json")
    source_receipt = next((x for x in receipts if x.get("url") == "https://conjectures.io/v1/competitions/torchlean/submissions/23/source"), None)
    source_receipt_ok = bool(source_receipt and source_receipt.get("status") == 200 and source_receipt.get("sha256") == source_sha == plan["reference"]["sha256"] and source_receipt.get("bytes") == len(source))
    if not source_receipt_ok:
        failures.append("public23_source_receipt")

    failures_plan: list[str] = []
    plan_checks = {
        "scope_is_native_cost_only": plan.get("scope") == "TWO_DISTINCT_DENSE_RECONSTRUCTIONS_FP_LAZY_AND_PREPARED_WORD_BLOCK16_NATIVE_COST",
        "target_is_current43_only": plan.get("human_performance_target") == "Current43 only; no new originalshipped comparison",
        "allow_private_false": plan.get("allow_private") is False,
        "official_head_is_current": plan.get("official_commit") == "27fb1d19c712ead50ad34b4ad0d4ba597161e616",
        "reference_is_public23_hash": plan.get("reference", {}).get("fetch", {}).get("submission") == 23 and plan.get("reference", {}).get("sha256") == source_sha,
        "current_champion_record_is43": plan.get("champion", {}).get("submission") == 43 and plan.get("champion", {}).get("source_sha256") == "4fef6fd4dbb39fe6fbf8fa85407228d6ebce9fb98dfbecf0d378e6f3b0df7c8b",
        "all_frozen_candidates_unproved": len(plan.get("candidates", [])) >= 2 and all(x.get("full_gate") is False and x.get("declares_correct") is False for x in plan.get("candidates", [])),
        "two_mechanism_families_present": any(x.get("name") == "public23-fp-only-lazy" for x in plan.get("candidates", [])) and any("block16" in x.get("name", "") for x in plan.get("candidates", [])),
        "profile_control_is_diagnostic": plan.get("profile_control") is True and plan.get("profile_adapter") is not None,
    }
    if not all(plan_checks.values()):
        failures_plan = [k for k, ok in plan_checks.items() if not ok]
        failures.extend("plan:" + k for k in failures_plan)

    candidate_rows = []
    dependency_rows = []
    for rel in plan.get("owned_sources", []):
        path = ROOT / rel
        exists = path.is_file()
        dependency_rows.append({"path": rel, "exists": exists, "bytes": path.stat().st_size if exists else None, "sha256": sha(path) if exists else None})
        if not exists:
            failures.append("owned_source_missing:" + rel)

    for entry in plan.get("candidates", []):
        patch_path = ROOT / entry["patch_script"]
        patch = load_module(patch_path, "r27_b8_static_" + entry["name"])
        result = patch.transform(source, 23, entry["variant"])
        digest = hashlib.sha256(result).hexdigest()
        text = result.decode("utf-8")
        if entry["name"] == "public23-fp-only-lazy":
            binding = {
                "retainedCorrect_present": "theorem retainedCorrect:" in text,
                "new_correct_theorem_absent": "theorem correct:" not in text,
                "new_fp_kernel_bound": "R27FPOnly.linear" in text,
                "original_fallback_word_provider_present": "YaU" in text and "Yc" in text,
            }
        else:
            binding = {
                "retainedCorrect_present": "theorem retainedCorrect:" in text,
                "new_correct_theorem_absent": "theorem correct:" not in text,
                "new_block16_kernel_bound": "R27BlockDense" in text and "R27BlockQPa" in text,
                "original_fallback_provider_present": "retainedKernels" in text and "QY6G" in text,
            }
        checks = {
            "source_hash_matches_plan": source_sha == entry.get("fetch", {}).get("sha256"),
            "patch_hash_matches_plan": sha(patch_path) == entry.get("patch_script_sha256"),
            "candidate_hash_matches_plan": digest == entry.get("sha256"),
            "candidate_bytes_match_plan": len(result) == entry.get("bytes"),
            "full_gate_absent": entry.get("full_gate") is False,
            "declares_correct_false": entry.get("declares_correct") is False,
            "proof_binding_is_native_only": all(binding.values()),
        }
        if not all(checks.values()):
            failures.extend(f"candidate:{entry.get('name')}:{k}" for k, ok in checks.items() if not ok)
        candidate_rows.append({
            "name": entry.get("name"),
            "source_sha256": source_sha,
            "patch_path": entry.get("patch_script"),
            "patch_sha256": sha(patch_path),
            "expected_patch_sha256": entry.get("patch_script_sha256"),
            "candidate_sha256": digest,
            "expected_candidate_sha256": entry.get("sha256"),
            "candidate_bytes": len(result),
            "bytes_under_cap": 256000 - len(result),
            "full_gate": entry.get("full_gate"),
            "declares_correct": entry.get("declares_correct"),
            "proof_state": entry.get("proof_state"),
            "proof_binding_checks": binding,
            "checks": checks,
        })

    batch = ROUND / "development/ci-bridge/batch8"
    fp_script = batch / "patch_fp23.py"
    fp_text = fp_script.read_text(encoding="utf-8")
    fp_dependency_checks = {
        "compact_recipe_hash_matches_embedded_pin": sha(batch / "frozen_compact_public23.py") == "4c3dd79284f6701d3b128687f9f973f47d9236f8d9db502d398e2eb4d131e129",
        "fp_adapter_hash_matches_embedded_pin": sha(batch / "patch_fp_only.py") == "d61bf830be1b197c451b50e555abb2af7b7cd001dc0c80cfb4ddacf6234dfc75",
        "fp_helper_hash_matches_embedded_pin": sha(batch / "LazyFPOnly.lean") == "1762a473178d3a45b431c94b995a2616fd4b939dd5b98d65f40ada71dfc2c892",
        "fp_integrator_checks_all_three_dependencies": all(x in fp_text for x in ("COMPACT=", "PATCH=", "HELPER=")),
    }
    block_script = batch / "public23_block16_cost_v2.py"
    block_text = block_script.read_text(encoding="utf-8")
    block_recipe = batch / "public23_block16_cost.py"
    block_helper = batch / "Block16PreparedUnrolled.lean.inc"
    block_dependency_checks = {
        "v2_hash_matches_plan": sha(block_script) == next(x["patch_sha256"] for x in candidate_rows if x["name"] == "public23-prepared-block16-unrolled-native-cost-v2"),
        "prior_recipe_hash_matches_embedded_pin": sha(block_recipe) == "e63fa1eab138db7bdea0f71cf520fe246287e2ee1798dc2c4f6debc5f33f196a",
        "unrolled_helper_present_and_nonempty": block_helper.is_file() and block_helper.stat().st_size > 0,
        "wrapper_replaces_only_helper_include": "Block16Prepared.lean.inc" in block_text and "Block16PreparedUnrolled.lean.inc" in block_text,
    }
    if not all(fp_dependency_checks.values()):
        failures.extend("fp_dependency:" + k for k, ok in fp_dependency_checks.items() if not ok)
    if not all(block_dependency_checks.values()):
        failures.extend("block16_dependency:" + k for k, ok in block_dependency_checks.items() if not ok)

    profile_path = ROOT / plan["profile_adapter"]
    profile_text = profile_path.read_text(encoding="utf-8")
    runner_path = ROUND / "development/ci-bridge/runner.py"
    runner_text = runner_path.read_text(encoding="utf-8")
    profile_checks = {
        "profile_adapter_hash_matches_plan": sha(profile_path) == plan.get("profile_adapter_sha256"),
        "host_include_paths_are_added_only_to_profile_compile": "-isystem" in profile_text and "host_headers" in profile_text,
        "instrumented_binary_separate_from_scored_binary": "profiled_binary" in profile_text and "control_binary" in profile_text,
        "profile_called_for_reference_only": "if plan.get('profile_control') and entry.get('reference')" in runner_text,
        "profile_scope_says_diagnostic_only": "INSTRUMENTED_COST_DISCRIMINATOR_ONLY_NOT_OFFICIAL_TIMING_OR_GATE" in profile_text,
    }
    if not all(profile_checks.values()):
        failures.extend("profile:" + k for k, ok in profile_checks.items() if not ok)

    fp_request, _, fp_request_sha = read(ROUND / "requests/FP23-INTEGRATED-4950AC8F.json")
    scope_request, _, scope_request_sha = read(ROUND / "requests/BATCH6-NEGATIVE-TO-DENSE8.json")
    third_request, _, third_request_sha = read(ROUND / "requests/BATCH8-INTENDED-THIRD-VARIANT.json")
    plan_mtime = datetime.datetime.fromtimestamp(PLAN_PATH.stat().st_mtime, datetime.timezone.utc).isoformat()
    has_allrows = any(x.get("name") == "public23-prepared-block16-allrows" for x in plan.get("candidates", []))
    allrows_mentioned_earlier = "public23-prepared-block16-allrows" in json.dumps(fp_request, ensure_ascii=False) or "public23-prepared-block16-allrows" in json.dumps(scope_request, ensure_ascii=False)
    allrows_hash = next((x.get("sha256") for x in plan.get("candidates", []) if x.get("name") == "public23-prepared-block16-allrows"), None)
    allrows_mentioned_now = has_allrows and allrows_hash in third_request.get("candidate_sha256", [])
    scope_note = {
        "candidate_count": len(plan.get("candidates", [])),
        "block16_allrows_variant_present": has_allrows,
        "allrows_named_in_initial_requests": allrows_mentioned_earlier,
        "allrows_explicitly_confirmed_in_followup": allrows_mentioned_now,
        "plan_last_modified_utc": plan_mtime,
        "fp_request_at_utc": fp_request.get("at_utc"),
        "batch6_transition_request_at_utc": scope_request.get("at_utc"),
        "followup_request_at_utc": third_request.get("at_utc"),
        "plan_changed_after_initial_request": has_allrows and not allrows_mentioned_earlier and plan_mtime > max(fp_request.get("at_utc", ""), scope_request.get("at_utc", "")),
        "followup_confirms_current_allrows_hash": allrows_mentioned_now,
        "interpretation": "The original FP23 and B6 transition requests named one block16 variant. A later BATCH8-INTENDED-THIRD-VARIANT request explicitly confirms the allrows candidate hash before dispatch.",
    }

    dispatch_path = ROUND / "evidence/dispatch-20261029T230248Z/dispatch.json"
    dispatch, _, dispatch_sha = read(dispatch_path)
    frozen = dispatch.get("frozen_files", {})
    dispatch_plan_path = "competitions/torchlean/candidates/r27-5h-20261029T194443Z/ci-plan.json"
    dispatch_checks = {
        "b8_dispatch_identified": dispatch.get("state") == "RUN_IDENTIFIED" and str((dispatch.get("run") or {}).get("databaseId")) == "40970353723",
        "public_and_private_false": dispatch.get("repository_public") is True and str(dispatch.get("request", {}).get("inputs", {}).get("allow_private", "")).lower() == "false",
        "dispatch_source_hash_is_plan_hash": hashlib.sha256(PLAN_PATH.read_bytes()).hexdigest() == frozen.get(dispatch_plan_path),
        "third_variant_frozen": all(x.get("patch_script") in frozen and frozen.get(x.get("patch_script")) == x.get("patch_script_sha256") for x in plan.get("candidates", [])),
        "all_owned_source_hashes_frozen": all(row.get("path") in frozen and frozen.get(row.get("path")) == row.get("sha256") for row in dependency_rows),
        "helper_and_profile_files_frozen": plan.get("profile_adapter") in frozen and frozen.get(plan.get("profile_adapter")) == plan.get("profile_adapter_sha256"),
        "request_confirms_third_hash": allrows_mentioned_now,
    }
    if not all(dispatch_checks.values()):
        failures.extend("dispatch:" + k for k, ok in dispatch_checks.items() if not ok)

    output = {
        "round": "R27",
        "captured_at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
        "scope": "READ_ONLY_STATIC_RECIPE_AND_PROOF_BINDING_AUDIT; NO_COMPILE_OR_CI",
        "plan": {"path": PLAN_PATH.relative_to(ROOT).as_posix(), "sha256": plan_sha, "source_sha256": source_sha, "official_commit": plan.get("official_commit"), "human_target": plan.get("human_performance_target")},
        "source_receipt": source_receipt,
        "source_receipts_manifest_sha256": receipts_sha,
        "plan_checks": plan_checks,
        "request_scope_note": {"fp_request_sha256": fp_request_sha, "transition_request_sha256": scope_request_sha, **scope_note},
        "dispatch": {"path": dispatch_path.relative_to(ROOT).as_posix(), "sha256": dispatch_sha, "checks": dispatch_checks, "frozen_file_count": len(frozen)},
        "candidate_transforms": candidate_rows,
        "owned_source_manifest": dependency_rows,
        "fp_recipe_dependency_checks": fp_dependency_checks,
        "block16_recipe_dependency_checks": block_dependency_checks,
        "profile_adapter": {"path": plan.get("profile_adapter"), "sha256": sha(profile_path), "checks": profile_checks, "profile_base": "reference-only; diagnostic binary; not candidate or official score"},
        "dispatch_receipt_available": True,
        "compile_executed": False,
        "full_gate_executed": False,
        "candidate_output_written": False,
        "failures": failures,
        "status": "PASS_STATIC_ONLY_NO_PROOF_OR_PERFORMANCE_ACCEPTANCE" if not failures else "AUDIT_FAILED",
    }
    OUT_PATH.write_text(json.dumps(output, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    print(json.dumps({"status": output["status"], "plan_sha256": plan_sha, "candidates": candidate_rows, "fp_dependencies": fp_dependency_checks, "block16_dependencies": block_dependency_checks, "profile": profile_checks, "failures": failures}, ensure_ascii=False))
    return 0 if not failures else 1


if __name__ == "__main__":
    raise SystemExit(main())
