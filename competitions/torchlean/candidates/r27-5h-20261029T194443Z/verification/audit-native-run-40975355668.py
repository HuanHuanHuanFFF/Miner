#!/usr/bin/env python3
"""Independent raw-evidence audit for the B11 NativeOnly build failure."""
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
RUN_DIR = ROUND / "evidence/40975355668"
PLAN_PATH = ROUND / "ci-plan-batch11.json"
RESULTS_PATH = ROUND / "CI-RESULTS-BATCH11.json"
OUT_PATH = HERE / "audit-native-run-40975355668.json"


def read_json(path: Path):
    raw = path.read_bytes()
    return json.loads(raw.decode("utf-8-sig")), hashlib.sha256(raw).hexdigest()


def sha_bytes(raw: bytes) -> str:
    return hashlib.sha256(raw).hexdigest()


def load_module(path: Path, name: str):
    spec = importlib.util.spec_from_file_location(name, path)
    if spec is None or spec.loader is None:
        raise ValueError(f"cannot load {path}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def main() -> int:
    failures: list[str] = []
    plan, plan_sha = read_json(PLAN_PATH)
    ci, ci_sha = read_json(RUN_DIR / "ci-run.json")
    dispatch_path = RUN_DIR.parent / "dispatch-20261029T234609Z/dispatch.json"
    dispatch, dispatch_sha = read_json(dispatch_path)
    outer_manifest, outer_manifest_sha = read_json(RUN_DIR / "original-artifact-hashes.json")
    artifact_dir = RUN_DIR / outer_manifest["directory"]
    summary, summary_sha = read_json(artifact_dir / "summary.json")
    artifact_plan, artifact_plan_sha = read_json(artifact_dir / "plan.json")
    inner_manifest, inner_manifest_sha = read_json(artifact_dir / "file-hashes.json")
    artifact_index, artifact_index_sha = read_json(RUN_DIR / "artifacts.json")

    r26_path = ROOT / "competitions/torchlean/candidates/r26-1h-20261029T085515Z/verification/analyze-native-only.py"
    r26 = load_module(r26_path, "r27_b11_pinned_r25_auditor")
    r26.r25_tools()  # Confirms the pinned scorer tool set is available; no score exists in this run.
    outer = r26.audit_tree(artifact_dir, outer_manifest.get("files", {}))
    inner = r26.audit_tree(artifact_dir, inner_manifest, excluded=("file-hashes.json",))
    if outer.get("status") != "PASS":
        failures.append("outer_artifact_hashes")
    if inner.get("status") != "PASS":
        failures.append("inner_runner_hashes")

    frozen = dispatch.get("frozen_files", {})
    candidate = plan["candidates"][0]
    owned = []
    for rel in plan.get("owned_sources", []):
        p = ROOT / rel
        current_digest = hashlib.sha256(p.read_bytes()).hexdigest() if p.is_file() else None
        try:
            commit_blob = subprocess.run(["git", "show", f"{ci['headSha']}:{rel}"], cwd=ROOT, capture_output=True, check=True).stdout
            commit_digest = sha_bytes(commit_blob)
        except (subprocess.CalledProcessError, FileNotFoundError):
            commit_digest = None
        passed = commit_digest is not None and commit_digest == frozen.get(rel)
        owned.append({"path": rel, "current_sha256": current_digest, "run_commit_sha256": commit_digest, "dispatch_sha256": frozen.get(rel), "pass": passed})
        if not passed:
            failures.append("owned_dispatch_hash:" + rel)
    try:
        immutable_plan_blob = subprocess.run(["git", "show", f"{ci['headSha']}:competitions/torchlean/candidates/r27-5h-20261029T194443Z/ci-plan.json"], cwd=ROOT, capture_output=True, check=True).stdout
        immutable_plan_sha = sha_bytes(immutable_plan_blob)
    except (subprocess.CalledProcessError, FileNotFoundError):
        immutable_plan_sha = None
    workspace_canonical_plan_sha = hashlib.sha256((ROUND / "ci-plan.json").read_bytes()).hexdigest()
    plan_checks = {
        "run_id_matches": str(ci.get("databaseId")) == "40975355668" == str(dispatch.get("run", {}).get("databaseId")),
        "source_commit_matches": ci.get("headSha") == dispatch.get("source_commit") == "6435029b784069762d61e333ccf51405c61b844f",
        "workflow_failure_terminal": ci.get("status") == "completed" and ci.get("conclusion") == "failure",
        "repository_public_allow_private_false": dispatch.get("repository_public") is True and str(dispatch.get("request", {}).get("inputs", {}).get("allow_private", "")).lower() == "false",
        "run_commit_canonical_plan_matches_batch_plan": immutable_plan_sha == plan_sha,
        "artifact_plan_matches_frozen_plan": artifact_plan_sha == plan_sha == frozen.get("competitions/torchlean/candidates/r27-5h-20261029T194443Z/ci-plan.json"),
        "official_head_matches": plan.get("official_commit") == artifact_plan.get("official_commit") == "27fb1d19c712ead50ad34b4ad0d4ba597161e616",
        "candidate_frozen": frozen.get(candidate["patch_script"]) == candidate.get("patch_script_sha256"),
        "all_owned_sources_frozen": all(x["pass"] for x in owned),
    }
    for k, ok in plan_checks.items():
        if not ok:
            failures.append("dispatch:" + k)

    source_path = ROUND / "competition-state/source-private/submission23-Kernel.lean"
    source = source_path.read_bytes()
    source_sha = sha_bytes(source)
    builder = load_module(ROOT / candidate["patch_script"], "r27_b11_failure_audit_builder")
    transformed = builder.transform(source, 23, candidate["variant"])
    transformed_sha = sha_bytes(transformed)
    source_checks = {
        "source_matches_plan_fetch": source_sha == candidate["fetch"]["sha256"],
        "transform_matches_candidate_hash": transformed_sha == candidate["sha256"],
        "transform_matches_candidate_bytes": len(transformed) == candidate["bytes"],
    }
    for k, ok in source_checks.items():
        if not ok:
            failures.append("source:" + k)

    result_names = [x.get("name") for x in summary.get("results", []) if isinstance(x, dict)]
    candidate_result = next((x for x in summary.get("results", []) if x.get("name") == candidate["name"]), None)
    candidate_errors = summary.get("candidate_errors", [])
    candidate_error = next((x for x in candidate_errors if x.get("candidate") == candidate["name"]), None)
    build_rel = f"{candidate['name']}/build.log"
    build_path = artifact_dir / build_rel
    build_text = build_path.read_text(encoding="utf-8", errors="replace") if build_path.is_file() else ""
    compile_errors = re.findall(r"^error: work/Submission\.lean:\d+:\d+:.*$", build_text, flags=re.MULTILINE)
    proof_boundary = {
        "plan_full_gate": candidate.get("full_gate"),
        "plan_declares_correct": candidate.get("declares_correct"),
        "candidate_result_recorded": candidate_result is not None,
        "candidate_in_summary_results": candidate["name"] in result_names,
        "candidate_measurements": (candidate_result or {}).get("measurements", []),
        "candidate_measurement_state": (candidate_result or {}).get("measurement_state", "NOT_RECORDED"),
        "summary_complete": summary.get("complete"),
        "candidate_error": candidate_error,
        "candidate_build_log_sha256": hashlib.sha256(build_path.read_bytes()).hexdigest() if build_path.is_file() else None,
        "compile_errors": compile_errors,
        "candidate_performance_multiplier": "UNKNOWN_NO_CANDIDATE_MEASUREMENTS",
        "correctness": "NOT_ESTABLISHED_NATIVE_ONLY_NO_FULL_GATE",
    }
    if candidate_error is None or candidate_result is not None or bool((candidate_result or {}).get("measurements")):
        failures.append("candidate_failure_state_unexpected")
    if summary.get("complete") is not False:
        failures.append("summary_not_incomplete")

    rows = {
        "outer": outer,
        "inner": inner,
    }
    output = {
        "round": "R27",
        "batch": 11,
        "captured_at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
        "scope": "INDEPENDENT_B11_RAW_ARTIFACT_AND_NATIVE_BUILD_FAILURE_AUDIT; NO_SCORE_OR_CORRECTNESS_CLAIM",
        "run": {
            "id": ci.get("databaseId"),
            "source_commit": ci.get("headSha"),
            "status": ci.get("status"),
            "conclusion": ci.get("conclusion"),
            "started_at_utc": summary.get("started_at_utc"),
            "finished_at_utc": summary.get("finished_at_utc"),
            "runner_elapsed_seconds": summary.get("elapsed_seconds"),
        },
        "plan": {
            "sha256": plan_sha,
            "artifact_plan_sha256": artifact_plan_sha,
            "run_commit_canonical_plan_sha256": immutable_plan_sha,
            "workspace_current_canonical_plan_sha256": workspace_canonical_plan_sha,
            "candidate_sha256": candidate.get("sha256"),
            "official_commit": plan.get("official_commit"),
        },
        "dispatch": {
            "path": dispatch_path.relative_to(ROOT).as_posix(),
            "sha256": dispatch_sha,
            "checks": plan_checks,
            "owned_sources": owned,
        },
        "artifact": {
            "id": artifact_index.get("artifacts", [{}])[0].get("id"),
            "archive_sha256": artifact_index.get("artifacts", [{}])[0].get("digest"),
            "archive_bytes": artifact_index.get("artifacts", [{}])[0].get("size_in_bytes"),
            "directory": outer_manifest.get("directory"),
            "outer_manifest_sha256": outer_manifest_sha,
            "inner_manifest_sha256": inner_manifest_sha,
            "summary_sha256": summary_sha,
            "files": rows,
        },
        "source_reconstruction": {
            "source23_sha256": source_sha,
            "candidate_transform_sha256": transformed_sha,
            "candidate_bytes": len(transformed),
            "checks": source_checks,
        },
        "calibration": {
            "source_sha256": summary.get("results", [{}])[0].get("source_sha256"),
            "flags_pass": summary.get("results", [{}])[0].get("flags_pass"),
            "measurements": summary.get("results", [{}])[0].get("measurements"),
        },
        "candidate": proof_boundary,
        "protected_sources_unchanged": summary.get("originals_unchanged"),
        "ci_results_file_present": RESULTS_PATH.is_file(),
        "failures": failures,
        "status": "PASS_ARTIFACTS_AND_CANDIDATE_BUILD_FAILURE_AUDITED_NO_TIMING" if not failures else "AUDIT_FAILED",
    }
    OUT_PATH.write_text(json.dumps(output, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    print(json.dumps({"status": output["status"], "outer": outer.get("status"), "outer_files": outer.get("files"), "inner": inner.get("status"), "inner_files": inner.get("files"), "candidate_error": candidate_error, "compile_errors": compile_errors, "candidate_performance_multiplier": proof_boundary["candidate_performance_multiplier"], "failures": failures}, ensure_ascii=False))
    return 0 if not failures else 1


if __name__ == "__main__":
    raise SystemExit(main())
