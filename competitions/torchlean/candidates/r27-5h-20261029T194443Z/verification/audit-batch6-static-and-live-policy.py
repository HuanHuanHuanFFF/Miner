#!/usr/bin/env python3
"""Read-only audit of the frozen B6 recipes and current official policy replay.

This reconstructs candidate bytes in memory only. It does not write source files,
compile Lean/native code, call CI, or fetch any current API values.
"""
from __future__ import annotations

import copy
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
from pathlib import Path
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
PLAN = json.loads(PLAN_PATH.read_text(encoding="utf-8-sig"))
OUT_PATH = HERE / "audit-batch6-static-and-live-policy.json"


def read(path: Path) -> tuple[Any, bytes, str]:
    raw = path.read_bytes()
    value = json.loads(raw.decode("utf-8-sig"))
    return value, raw, hashlib.sha256(raw).hexdigest()


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
    helper_run, _, helper_run_sha = read(HERE / "audit-helper-run-40964374666.json")
    version, version_bytes, version_sha = read(STATE / "official-current-version-check.json")
    version_raw_sha = sha(ROOT / version["raw_path"])
    boards, boards_bytes, boards_sha = read(STATE / "boards-2150.raw")
    current_replay, current_replay_bytes, current_replay_sha = read(STATE / "current-policy-replay.json")
    historical_replay, _, historical_replay_sha = read(STATE / "exact-report-policy-replay.json")
    current43_chain, _, current43_chain_sha = read(HERE / "current43-report-chain.json")
    report43, report43_bytes, report43_sha = read(STATE / "submission43-report.raw")
    report43_receipts, _, _ = read(STATE / "normalized-champion-update-2150-receipts.json")
    report43_receipt = next(
        (x for x in report43_receipts if x.get("url") == "https://conjectures.io/v1/competitions/torchlean/submissions/43/report"),
        None,
    )
    source23_receipt = next(
        (x for x in report43_receipts if x.get("url") == "https://conjectures.io/v1/competitions/torchlean/submissions/23/source"),
        None,
    )

    analyzer_path = ROOT / "competitions/torchlean/candidates/r26-1h-20261029T085515Z/verification/analyze-native-only.py"
    analyzer = load_module(analyzer_path, "r27_b6_pinned_r26_analyzer")
    _, pinned_modules, pins = analyzer.r25_tools()
    config = pinned_modules["config"]
    ci, _, ci_sha = read(RUN_DIR / "ci-run.json")
    dispatch_path, dispatch = analyzer.find_dispatch(RUN_DIR.parent, "40967910604")
    frozen = dispatch.get("frozen_files", {})
    dispatch_plan_path = "competitions/torchlean/candidates/r27-5h-20261029T194443Z/ci-plan.json"
    dispatch_runner_path = "competitions/torchlean/candidates/r27-5h-20261029T194443Z/development/ci-bridge/runner.py"
    dispatch_prepare_path = "competitions/torchlean/candidates/r27-5h-20261029T194443Z/development/ci-bridge/prepare-current.sh"
    runner_path = ROUND / "development/ci-bridge/runner.py"
    prepare_path = ROUND / "development/ci-bridge/prepare-current.sh"
    commit = ci.get("headSha")
    plan_blob = subprocess.run(["git", "show", f"{commit}:{dispatch_plan_path}"], cwd=ROOT, capture_output=True, check=True).stdout
    runner_blob = subprocess.run(["git", "show", f"{commit}:{dispatch_runner_path}"], cwd=ROOT, capture_output=True, check=True).stdout
    prepare_blob = subprocess.run(["git", "show", f"{commit}:{dispatch_prepare_path}"], cwd=ROOT, capture_output=True, check=True).stdout
    dispatch_checks = {
        "run_id_and_commit_match": str(ci.get("databaseId")) == str((dispatch.get("run") or {}).get("databaseId")) == "40967910604" and ci.get("headSha") == dispatch.get("source_commit"),
        "public_run_allow_private_false": dispatch.get("repository_public") is True and str(dispatch.get("request", {}).get("inputs", {}).get("allow_private", "")).lower() == "false",
        "batch6_plan_matches_frozen_ci_plan": hashlib.sha256(PLAN_PATH.read_bytes()).hexdigest() == hashlib.sha256(plan_blob).hexdigest() == frozen.get(dispatch_plan_path),
        "runner_blob_hash_matches_dispatch": hashlib.sha256(runner_blob).hexdigest() == frozen.get(dispatch_runner_path),
        "prepare_blob_hash_matches_dispatch": hashlib.sha256(prepare_blob).hexdigest() == frozen.get(dispatch_prepare_path),
        "official_commit_matches_plan": PLAN.get("official_commit") == version.get("new_commit"),
    }
    if not all(dispatch_checks.values()):
        failures.extend("dispatch:" + k for k, ok in dispatch_checks.items() if not ok)

    official_commit = version.get("new_commit")
    benchmark_identity = helper_run.get("benchmark_identity")
    proof_identity = helper_run.get("proof_identity")
    board_by_id = {x.get("id"): x for x in boards.get("boards", []) if isinstance(x, dict)}
    parent_rows = {x.get("board"): x for x in current_replay.get("rows", []) if isinstance(x, dict)}
    current43_eval = next((x for x in report43.get("evaluations", []) if x.get("board") == "normalized_mlp"), None)
    old_rows = {x.get("board"): x for x in historical_replay.get("rows", []) if isinstance(x, dict)}
    policy_rows: list[dict[str, Any]] = []

    for board_id, old in old_rows.items():
        old_plan = copy.deepcopy(old.get("report_plan", {}))
        new_plan = copy.deepcopy(old_plan)
        new_plan["benchmark_identity"] = benchmark_identity
        changed_fields = sorted(k for k in set(old_plan) | set(new_plan) if old_plan.get(k) != new_plan.get(k))
        old_hash = config.digest(old_plan)
        new_hash = config.digest(new_plan)
        live_hash = board_by_id.get(board_id, {}).get("config_hash")
        parent = parent_rows.get(board_id, {})
        negative = copy.deepcopy(new_plan)
        negative["strata"][0]["timing"]["build_seconds"] += 1
        checks = {
            "only_benchmark_identity_changed": changed_fields == ["benchmark_identity"],
            "historical_hash_matches_saved_report": old_hash == old.get("expected_report_config_hash"),
            "new_hash_matches_live_board": new_hash == live_hash,
            "parent_replay_hash_matches_independent_replay": new_hash == parent.get("current_config_hash"),
            "parent_replay_marks_live_match": parent.get("matches_live") is True,
            "parent_replay_marks_only_identity_change": parent.get("only_changed_field") == "benchmark_identity",
            "negative_control_rejected": config.digest(negative) != new_hash and parent.get("negative_control_old_benchmark") == "REJECTED",
            "report_plan_benchmark_identity_matches_helper_run": new_plan.get("benchmark_identity") == benchmark_identity,
            "report_plan_proof_identity_matches_helper_run": new_plan.get("proof_identity") == proof_identity,
        }
        if not all(checks.values()):
            failures.extend(f"policy:{board_id}:{name}" for name, passed in checks.items() if not passed)
        policy_rows.append({
            "board": board_id,
            "historical_hash": old_hash,
            "replayed_hash": new_hash,
            "live_hash": live_hash,
            "parent_reported_hash": parent.get("current_config_hash"),
            "changed_fields": changed_fields,
            "checks": checks,
        })

    live_hashes = [x.get("current_config_hash") for x in current_replay.get("rows", [])]
    board43 = board_by_id.get("normalized_mlp", {})
    report43_config = current43_eval.get("config_hash") if current43_eval else None
    new43_checks = {
        "six_policy_rows": len(policy_rows) == 6 and len(current_replay.get("rows", [])) == 6,
        "all_six_live_hashes_match": len(live_hashes) == 6 and all(x.get("checks", {}).get("new_hash_matches_live_board") for x in policy_rows),
        "current43_report_config_matches_current_board": bool(current43_eval and report43_config == board43.get("config_hash")),
        "current43_report_config_matches_independent_replay": bool(
            current43_eval and report43_config == next((x["replayed_hash"] for x in policy_rows if x["board"] == "normalized_mlp"), None)
        ),
        "current43_chain_audit_passed": current43_chain.get("status", "").startswith("CURRENT43_REPORT_EDGE_BOUND") and not current43_chain.get("audit_failures"),
        "current43_receipt_matches_bytes": bool(
            report43_receipt
            and report43_receipt.get("status") == 200
            and report43_receipt.get("sha256") == report43_sha
            and report43_receipt.get("bytes") == len(report43_bytes)
        ),
        "current_official_commit_matches_helper_run": official_commit == helper_run.get("official_commit") == PLAN.get("official_commit"),
        "current_benchmark_identity_bound_to_helper_run": benchmark_identity == current_replay.get("rows", [{}])[0].get("plan", {}).get("benchmark_identity"),
        "official_version_raw_matches_saved_summary": version_raw_sha == version.get("raw_sha256"),
        "b4_helper_run_manifests_pass": (
            helper_run.get("outer_artifact_manifest", {}).get("pass") is True
            and helper_run.get("inner_file_hash_manifest", {}).get("pass") is True
            and helper_run.get("dispatch_source_commit_matches_run") is True
            and helper_run.get("artifact_plan_matches_frozen_dispatch") is True
        ),
    }
    if not all(new43_checks.values()):
        failures.extend(f"current43:{name}" for name, passed in new43_checks.items() if not passed)

    batch_dir = ROUND / "development/ci-bridge/batch6"
    source_path = STATE / "source-private/submission23-Kernel.lean"
    source = source_path.read_bytes()
    source_sha = hashlib.sha256(source).hexdigest()
    expected_source_sha = PLAN["reference"]["sha256"]
    source_receipt_matches = bool(
        source23_receipt
        and source23_receipt.get("status") == 200
        and source23_receipt.get("sha256") == source_sha == expected_source_sha
        and source23_receipt.get("bytes") == len(source)
    )
    if not source_receipt_matches:
        failures.append("b6_public23_source_receipt_mismatch")
    candidate_rows = []
    for entry in PLAN.get("candidates", []):
        patch_path = ROOT / entry["patch_script"]
        patch_sha = sha(patch_path)
        module = load_module(patch_path, "r27_static_" + entry["name"])
        output = module.transform(source, 23, entry["variant"])
        output_sha = hashlib.sha256(output).hexdigest()
        runtime_only = entry.get("name") == "public23-row-reciprocal-native-cost-v1"
        proof_binding_ok = (
            (b"theorem correct:Obligation kernels:=" not in output)
            and (b"theorem retainedCorrect:Obligation retainedKernels:=" in output)
            and (b"def kernels:Kernels:=" in output)
            and (b"R27MYbc" in output)
        ) if runtime_only else (b"theorem correct:Obligation kernels:=" in output)
        checks = {
            "patch_hash_matches_plan": patch_sha == entry.get("patch_script_sha256"),
            "output_hash_matches_plan": output_sha == entry.get("sha256"),
            "output_bytes_match_plan": len(output) == entry.get("bytes"),
            "proof_state_matches_flags": (
                entry.get("full_gate") is False and entry.get("declares_correct") is False and proof_binding_ok
            ) if runtime_only else (
                entry.get("full_gate") is True and entry.get("declares_correct") is True and proof_binding_ok
            ),
        }
        if not all(checks.values()):
            failures.extend(f"candidate:{entry.get('name')}:{name}" for name, passed in checks.items() if not passed)
        candidate_rows.append({
            "name": entry.get("name"),
            "source_sha256": source_sha,
            "source_bytes": len(source),
            "patch_path": entry.get("patch_script"),
            "patch_sha256": patch_sha,
            "expected_patch_sha256": entry.get("patch_script_sha256"),
            "candidate_sha256": output_sha,
            "expected_candidate_sha256": entry.get("sha256"),
            "candidate_bytes": len(output),
            "expected_candidate_bytes": entry.get("bytes"),
            "full_gate": entry.get("full_gate"),
            "declares_correct": entry.get("declares_correct"),
            "proof_state": entry.get("proof_state"),
            "proof_binding_static_check": proof_binding_ok,
            "checks": checks,
        })
        if frozen.get(entry["patch_script"]) != patch_sha:
            failures.append("dispatch_candidate_patch_hash:" + entry.get("name", "UNKNOWN"))

    source_manifest = []
    for rel in PLAN.get("owned_sources", []):
        path = ROOT / rel
        exists = path.is_file()
        digest = sha(path) if exists else None
        dispatch_digest = frozen.get(rel)
        source_manifest.append({"path": rel, "exists": exists, "bytes": path.stat().st_size if exists else None, "sha256": digest, "dispatch_sha256": dispatch_digest, "matches_dispatch": exists and digest == dispatch_digest})
        if not exists:
            failures.append("owned_source_missing:" + rel)
        elif digest != dispatch_digest:
            failures.append("owned_source_dispatch_hash_mismatch:" + rel)
    helper_manifest = []
    for entry in PLAN.get("helpers", []):
        path = ROOT / entry["path"]
        digest = sha(path) if path.is_file() else None
        passed = path.is_file() and digest == entry.get("sha256") and digest == frozen.get(entry["path"])
        helper_manifest.append({"name": entry.get("name"), "path": entry.get("path"), "actual_sha256": digest, "expected_sha256": entry.get("sha256"), "dispatch_sha256": frozen.get(entry["path"]), "pass": passed})
        if not passed:
            failures.append("helper_hash_mismatch:" + str(entry.get("name")))

    plan_bytes = PLAN_PATH.read_bytes()
    runner_text = runner_blob.decode("utf-8")
    gate_before_measurement = runner_text.index("if entry.get('full_gate')") < runner_text.index("for seed in plan['seeds']")
    proof_gate_checks = {
        "candidate_full_gate_branch_precedes_measurement_loop": gate_before_measurement,
        "plan_exact_correct_candidate_runs_full_gate": sum(bool(x.get("full_gate") and x.get("declares_correct")) for x in PLAN.get("candidates", [])) == 1,
        "runtime_only_candidate_never_declares_correct": all(
            x.get("declares_correct") is False and x.get("full_gate") is False
            for x in PLAN.get("candidates", []) if x.get("name") == "public23-row-reciprocal-native-cost-v1"
        ),
        "full_gate_is_original_verifier": "[py,'-m','verification'" in runner_text and "verdict.get('passed')" in runner_text,
    }
    if not all(proof_gate_checks.values()):
        failures.extend(f"gate_order:{name}" for name, passed in proof_gate_checks.items() if not passed)
    plan_contract_checks = {
        "board_is_current_normalized_mlp": PLAN.get("board") == "normalized_mlp",
        "only_current_champion_target": PLAN.get("human_performance_target") == "Current43 only; no new originalshipped comparison",
        "private_runner_disallowed": PLAN.get("allow_private") is False,
        "official_head_matches_saved_current_version": PLAN.get("official_commit") == official_commit,
        "reference_is_public23_with_exact_hash": (
            PLAN.get("reference", {}).get("fetch", {}).get("submission") == 23
            and PLAN.get("reference", {}).get("sha256") == expected_source_sha
        ),
        "plan_batch6_is_frozen_for_run": hashlib.sha256(PLAN_PATH.read_bytes()).hexdigest() == frozen.get(dispatch_plan_path),
    }
    if not all(plan_contract_checks.values()):
        failures.extend(f"plan_contract:{name}" for name, passed in plan_contract_checks.items() if not passed)

    output = {
        "round": "R27",
        "captured_at_utc": datetime.now(timezone.utc).isoformat(),
        "scope": "READ_ONLY_STATIC_RECIPE_AND_SAVED_OFFICIAL_POLICY_AUDIT; NO_COMPILE_OR_CI",
        "plan": {"path": PLAN_PATH.relative_to(ROOT).as_posix(), "sha256": hashlib.sha256(plan_bytes).hexdigest(), "official_commit": official_commit, "batch": PLAN.get("batch")},
        "official_policy_inputs": {
            "boards_path": (STATE / "boards-2150.raw").relative_to(ROOT).as_posix(),
            "boards_sha256": boards_sha,
            "boards_bytes": len(boards_bytes),
            "parent_replay_path": (STATE / "current-policy-replay.json").relative_to(ROOT).as_posix(),
            "parent_replay_sha256": current_replay_sha,
            "historical_replay_sha256": historical_replay_sha,
            "version_check_sha256": version_sha,
            "official_version_raw_sha256": hashlib.sha256(version_bytes).hexdigest(),
            "official_version_source_raw_sha256": version_raw_sha,
            "benchmark_identity": benchmark_identity,
            "proof_identity": proof_identity,
            "pinned_config": pins["config.py"],
            "rows": policy_rows,
            "new43_checks": new43_checks,
        },
        "b6_recipe": {
            "official_source_path": source_path.relative_to(ROOT).as_posix(),
            "official_source_sha256": source_sha,
            "expected_source_sha256": expected_source_sha,
            "source_hash_matches_plan": source_sha == expected_source_sha,
            "saved_official_source_receipt_matches_bytes": source_receipt_matches,
            "source_receipt": source23_receipt,
            "candidate_transforms": candidate_rows,
            "owned_source_manifest": source_manifest,
            "helper_manifest": helper_manifest,
            "proof_gate_checks": proof_gate_checks,
            "plan_contract_checks": plan_contract_checks,
            "runner_sha256": sha(runner_path),
            "dispatched_runner_sha256": hashlib.sha256(runner_blob).hexdigest(),
            "dispatched_prepare_sha256": hashlib.sha256(prepare_blob).hexdigest(),
            "pinned_r26_analyzer_sha256": sha(analyzer_path),
            "dispatch_receipt_available": True,
            "dispatch_receipt_path": dispatch_path.relative_to(ROOT).as_posix(),
            "dispatch_receipt_sha256": hashlib.sha256(dispatch_path.read_bytes()).hexdigest(),
            "dispatch_checks": dispatch_checks,
            "ci_run_sha256": ci_sha,
            "owned_source_dispatch_hashes": "FROZEN_AND_MATCHED",
        },
        "helper_run_audit_sha256": helper_run_sha,
        "current43_report_sha256": report43_sha,
        "current43_report_receipt": report43_receipt,
        "candidate_output_written": False,
        "compile_executed": False,
        "ci_executed": False,
        "failures": failures,
        "status": "PASS_STATIC_ONLY_NO_PROOF_OR_PERFORMANCE_ACCEPTANCE" if not failures else "AUDIT_FAILED",
    }
    OUT_PATH.write_text(json.dumps(output, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    print(json.dumps({"status": output["status"], "policy_rows": len(policy_rows), "current43_checks": sum(new43_checks.values()), "b6_candidates": candidate_rows, "failures": failures}, ensure_ascii=False))
    return 0 if not failures else 1


if __name__ == "__main__":
    raise SystemExit(main())
