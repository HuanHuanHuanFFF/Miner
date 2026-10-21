"""Audit Round 10 completed-run receipts, source copies, and optional Git bytes."""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path, PurePosixPath
import re
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_SUMMARY = ROOT / "evidence/round10/pre-final-summary.json"
DEFAULT_OUTPUT = ROOT / "evidence/round10/archive-check-draft.json"


def sha256_file(path: Path) -> tuple[int, str]:
    h = hashlib.sha256()
    size = 0
    with path.open("rb") as f:
        while chunk := f.read(1024 * 1024):
            h.update(chunk)
            size += len(chunk)
    return size, h.hexdigest()


def safe_repo_path(value: str | Path) -> Path:
    p = Path(value)
    resolved = (ROOT / p).resolve() if not p.is_absolute() else p.resolve()
    try:
        resolved.relative_to(ROOT.resolve())
    except ValueError as exc:
        raise ValueError(f"path escapes repository: {value}") from exc
    return resolved


def rel_repo(path: Path) -> str:
    return path.resolve().relative_to(ROOT.resolve()).as_posix()


def add_check(checks: list, counts: dict, kind: str, path: Path, expected_sha: str,
              expected_bytes: int | None = None, expected_label: str | None = None):
    record = {"kind": kind, "path": rel_repo(path), "expected_sha256": expected_sha}
    if expected_label:
        record["expected_from"] = expected_label
    if expected_bytes is not None:
        record["expected_bytes"] = expected_bytes
    if not path.is_file():
        record.update(status="MISSING_IN_WORKSPACE", actual_sha256=None, actual_bytes=None)
        counts["missing_files"] += 1
    else:
        size, actual = sha256_file(path)
        record.update(actual_sha256=actual, actual_bytes=size,
                      status="MATCH" if actual == expected_sha and (expected_bytes is None or size == expected_bytes)
                      else "MISMATCH")
        if actual != expected_sha:
            counts["sha_mismatches"] += 1
        if expected_bytes is not None and size != expected_bytes:
            counts["size_mismatches"] += 1
    counts["checks"] += 1
    checks.append(record)
    return record


def resolve_gate_receipts(summary: dict):
    result = []
    runs = summary.get("completed_ci_runs", [])
    for entry in runs:
        run_id = str(entry["run_id"])
        batch = str(entry["batch"])
        if not run_id.isdigit() or not re.fullmatch(r"[A-Za-z0-9-]+", batch):
            raise ValueError(f"invalid run/batch in summary: {run_id}/{batch}")
        folder = safe_repo_path(Path("evidence/round10") / run_id / batch / "gate")
        result.append((entry, folder))
    return result


def audit_run(summary_run: dict, folder: Path, aggregate: dict, git_targets: dict):
    run_id = str(summary_run["run_id"])
    batch = summary_run["batch"]
    run_result = {"run_id": run_id, "batch": batch, "receipt_path": rel_repo(folder),
                  "summary_conclusion": summary_run.get("conclusion"),
                  "summary_source_commit": summary_run.get("source_commit"),
                  "public_paired_processes_summary": summary_run.get("public_paired_processes"),
                  "receipt_exists": folder.is_dir(), "ci": {}, "raw_artifacts": {},
                  "spec_files": [], "gate_attempts": []}
    if not folder.is_dir():
        aggregate["missing_receipt_dirs"] += 1
        run_result["receipt_exists"] = False
        return run_result

    state_path = folder / "state.json"
    ci_path = folder / "ci-run.json"
    manifest_path = folder / "raw-artifact-files.json"
    for key, path in (("state.json", state_path), ("ci-run.json", ci_path),
                      ("raw-artifact-files.json", manifest_path)):
        if path.is_file():
            size, digest = sha256_file(path)
            git_targets[rel_repo(path)] = {"path": path, "sha256": digest, "bytes": size,
                                            "kind": "receipt_metadata"}
    if not state_path.is_file() or not ci_path.is_file() or not manifest_path.is_file():
        run_result["ci"] = {"status": "MISSING_REQUIRED_RECEIPT_FILE"}
        aggregate["ci_identity_failures"] += 1
        return run_result

    state = json.loads(state_path.read_text(encoding="utf-8"))
    ci = json.loads(ci_path.read_text(encoding="utf-8"))
    check_ci = {
        "database_id_matches_run_id": str(ci.get("databaseId")) == run_id,
        "head_sha_matches_state_git_sha": ci.get("headSha") == state.get("git_sha"),
        "head_sha_matches_summary_source_commit": ci.get("headSha") == summary_run.get("source_commit"),
        "status_completed": ci.get("status") == "completed",
        "conclusion_matches_summary": ci.get("conclusion") == summary_run.get("conclusion"),
    }
    run_result["ci"] = {"database_id": ci.get("databaseId"), "head_sha": ci.get("headSha"),
                        "state_git_sha": state.get("git_sha"), "status": ci.get("status"),
                        "conclusion": ci.get("conclusion"), "checks": check_ci,
                        "identity_and_completion_ok": all(check_ci.values())}
    if not all(check_ci.values()):
        aggregate["ci_identity_failures"] += 1
    aggregate["ci_completed_runs"] += ci.get("status") == "completed"
    aggregate["ci_success_runs"] += ci.get("status") == "completed" and ci.get("conclusion") == "success"
    aggregate["ci_failed_runs"] += ci.get("status") == "completed" and ci.get("conclusion") == "failure"

    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    artifact_results = []
    for relative, expected in sorted(manifest.get("files", {}).items()):
        rel = PurePosixPath(relative)
        if rel.is_absolute() or ".." in rel.parts:
            artifact_results.append({"path": relative, "status": "INVALID_MANIFEST_PATH"})
            aggregate["invalid_manifest_paths"] += 1
            continue
        path = safe_repo_path(folder.joinpath(*rel.parts))
        check = add_check(artifact_results, aggregate, "raw_artifact", path,
                          expected.get("sha256", ""), expected.get("bytes"),
                          f"{rel_repo(manifest_path)}::{relative}")
        git_targets[rel_repo(path)] = {"path": path, "sha256": expected.get("sha256", ""),
                                        "bytes": expected.get("bytes"), "kind": "raw_artifact"}
    run_result["raw_artifacts"] = {
        "manifest_sha256": sha256_file(manifest_path)[1],
        "listed_files": len(manifest.get("files", {})),
        "verified_files": sum(x.get("status") == "MATCH" for x in artifact_results),
        "missing_files": sum(x.get("status") == "MISSING_IN_WORKSPACE" for x in artifact_results),
        "sha_mismatches": sum(x.get("status") == "MISMATCH" and x.get("actual_sha256") != x.get("expected_sha256") for x in artifact_results),
        "size_mismatches": sum(x.get("status") == "MISMATCH" and x.get("actual_bytes") != x.get("expected_bytes") for x in artifact_results),
        "files": artifact_results,
    }
    aggregate["raw_artifact_files_listed"] += len(manifest.get("files", {}))
    aggregate["raw_artifact_files_verified"] += run_result["raw_artifacts"]["verified_files"]

    entries = {e["name"]: e for e in state.get("spec", {}).get("entries", [])}
    for name, entry in sorted(entries.items()):
        candidate_path = safe_repo_path(entry["path"])
        for filename, expected_sha in sorted(entry.get("hashes", {}).items()):
            source_path = safe_repo_path(candidate_path / filename)
            detail = add_check(run_result["spec_files"], aggregate, "spec_source_or_proof",
                               source_path, expected_sha, expected_label=f"state.spec.entries[{name}].hashes[{filename}]")
            detail.update(candidate=name, filename=filename)
            if source_path.is_file():
                size, digest = sha256_file(source_path)
                git_targets[rel_repo(source_path)] = {"path": source_path, "sha256": digest,
                                                       "bytes": size, "kind": "workspace_source_or_proof",
                                                       "expected_sha256": expected_sha}

    gates = state.get("gates", {})
    for name, gate in sorted(gates.items()):
        accepted = bool(gate.get("accepted", False))
        attempt = {"candidate": name, "attempted": True, "accepted": accepted,
                   "gate_exit": gate.get("gate_exit"), "origin": gate.get("origin"), "input_files": []}
        aggregate["gate_attempts"] += 1
        aggregate["gate_accepted"] += accepted
        aggregate["gate_rejected"] += not accepted
        entry = entries.get(name)
        if entry is None:
            attempt["status"] = "GATE_CANDIDATE_NOT_IN_SPEC"
            aggregate["gate_input_failures"] += 1
            run_result["gate_attempts"].append(attempt)
            continue
        input_dir = folder / ("input-" + name)
        for filename, expected_sha in sorted(entry.get("hashes", {}).items()):
            input_path = safe_repo_path(input_dir / filename)
            detail = add_check(attempt["input_files"], aggregate, "gate_input_copy",
                               input_path, expected_sha,
                               expected_label=f"state.spec.entries[{name}].hashes[{filename}]")
            detail.update(filename=filename)
            if input_path.is_file():
                size, digest = sha256_file(input_path)
                git_targets[rel_repo(input_path)] = {"path": input_path, "sha256": digest,
                                                      "bytes": size, "kind": "gate_input_copy",
                                                      "expected_sha256": expected_sha}
        attempt["status"] = "VERIFIED" if all(x["status"] == "MATCH" for x in attempt["input_files"]) else "INPUT_COPY_MISMATCH"
        if attempt["status"] != "VERIFIED":
            aggregate["gate_input_failures"] += 1
        run_result["gate_attempts"].append(attempt)
    aggregate["spec_file_checks"] += len(run_result["spec_files"])
    aggregate["gate_input_file_checks"] += sum(len(g["input_files"]) for g in run_result["gate_attempts"])
    aggregate["summary_paired_processes_seen"] += len(state.get("metrics", []))
    run_result["state_phase"] = state.get("phase")
    run_result["state_metric_rows"] = len(state.get("metrics", []))
    run_result["spec_entry_count"] = len(entries)
    run_result["gate_attempt_count"] = len(gates)
    return run_result


def git_blob_audit(ref: str, targets: dict[str, dict]):
    resolved = subprocess.run(["git", "rev-parse", "--verify", f"{ref}^{{commit}}"],
                              cwd=ROOT, check=True, capture_output=True, text=True).stdout.strip()
    paths = sorted(targets)
    proc = subprocess.Popen(["git", "cat-file", "--batch"], cwd=ROOT,
                            stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
    assert proc.stdin is not None and proc.stdout is not None
    results = []
    for relative in paths:
        proc.stdin.write(f"{resolved}:{relative}\n".encode("utf-8"))
        proc.stdin.flush()
        header = proc.stdout.readline().decode("utf-8", "replace").rstrip("\n")
        fields = header.split()
        target = targets[relative]
        item = {"path": relative, "kind": target["kind"], "expected_fs_sha256": target["sha256"],
                "expected_fs_bytes": target.get("bytes")}
        if len(fields) == 2 and fields[1] == "missing":
            item.update(status="MISSING_IN_GIT_REF", git_sha256=None, git_bytes=None)
        elif len(fields) == 3 and fields[1] == "blob":
            size = int(fields[2])
            h = hashlib.sha256()
            remaining = size
            while remaining:
                chunk = proc.stdout.read(min(1024 * 1024, remaining))
                if not chunk:
                    raise RuntimeError(f"truncated git cat-file output for {relative}")
                h.update(chunk)
                remaining -= len(chunk)
            delimiter = proc.stdout.read(1)
            if delimiter != b"\n":
                raise RuntimeError(f"bad git cat-file delimiter for {relative}")
            digest = h.hexdigest()
            item.update(git_bytes=size, git_sha256=digest,
                        status="MATCH" if digest == target["sha256"] and size == target.get("bytes") else "MISMATCH")
        else:
            item.update(status="GIT_CAT_FILE_ERROR", header=header, git_sha256=None, git_bytes=None)
        results.append(item)
    proc.stdin.close()
    exit_code = proc.wait()
    if exit_code != 0:
        raise RuntimeError(f"git cat-file --batch exited {exit_code}")
    counts = {"paths_checked": len(results),
              "matched": sum(x["status"] == "MATCH" for x in results),
              "missing_in_ref": sum(x["status"] == "MISSING_IN_GIT_REF" for x in results),
              "mismatched": sum(x["status"] == "MISMATCH" for x in results),
              "git_errors": sum(x["status"] == "GIT_CAT_FILE_ERROR" for x in results)}
    return {"ref_requested": ref, "resolved_commit": resolved, "counts": counts, "files": results}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--summary", type=Path, default=DEFAULT_SUMMARY)
    ap.add_argument("--output", type=Path, default=DEFAULT_OUTPUT)
    ap.add_argument("--git-ref", help="optional commit/ref; verify Git archive blobs against workspace and manifests")
    args = ap.parse_args()
    summary_path = safe_repo_path(args.summary)
    output_path = safe_repo_path(args.output)
    summary_raw = summary_path.read_bytes()
    summary = json.loads(summary_raw)
    receipts = resolve_gate_receipts(summary)
    aggregate = {"missing_receipt_dirs": 0, "ci_identity_failures": 0, "ci_completed_runs": 0,
                 "ci_success_runs": 0, "ci_failed_runs": 0, "checks": 0, "missing_files": 0,
                 "sha_mismatches": 0, "size_mismatches": 0, "invalid_manifest_paths": 0,
                 "raw_artifact_files_listed": 0, "raw_artifact_files_verified": 0,
                 "spec_file_checks": 0, "gate_attempts": 0, "gate_accepted": 0,
                 "gate_rejected": 0, "gate_input_file_checks": 0, "gate_input_failures": 0,
                 "summary_paired_processes_seen": 0}
    git_targets: dict[str, dict] = {}
    summary_size, summary_sha = len(summary_raw), hashlib.sha256(summary_raw).hexdigest()
    git_targets[rel_repo(summary_path)] = {"path": summary_path, "sha256": summary_sha,
                                           "bytes": summary_size, "kind": "summary"}
    runs = [audit_run(item, folder, aggregate, git_targets) for item, folder in receipts]
    summary_processes = sum(int(r.get("public_paired_processes", 0)) for r, _ in receipts)
    summary_checks = {
        "declared_run_count_matches": len(receipts) == len(summary.get("completed_ci_runs", [])),
        "declared_run_count": len(summary.get("completed_ci_runs", [])),
        "summary_public_paired_processes_sum": summary_processes,
        "summary_paired_process_count_matches_root_value": summary_processes == summary.get("public_paired_processes"),
        "summary_rust_candidate_count": summary.get("candidate_count"),
        "summary_candidate_rows": len(summary.get("candidates", [])),
        "summary_unique_rust_source_hashes": len({c.get("source_sha256") for c in summary.get("candidates", [])}),
        "candidate_count_matches_rows_and_unique_rust_sources": (
            summary.get("candidate_count") == len(summary.get("candidates", [])) ==
            len({c.get("source_sha256") for c in summary.get("candidates", [])})),
        "state_metric_rows_sum": aggregate["summary_paired_processes_seen"],
        "state_metric_rows_match_summary_processes": aggregate["summary_paired_processes_seen"] == summary_processes,
        "summary_status_is_completed_recompute": summary.get("status") == "COMPLETED_CI_RECEIPTS_RECOMPUTED",
        "summary_status": summary.get("status"),
    }
    failed_summary_checks = sum(value is False for key, value in summary_checks.items() if key not in ("summary_status",))
    fs_failures = (failed_summary_checks + aggregate["missing_receipt_dirs"] + aggregate["ci_identity_failures"] +
                   aggregate["missing_files"] + aggregate["sha_mismatches"] + aggregate["size_mismatches"] +
                   aggregate["invalid_manifest_paths"] + aggregate["gate_input_failures"])
    git_result = git_blob_audit(args.git_ref, git_targets) if args.git_ref else None
    result = {
        "status": "VERIFIED_FILESYSTEM" if fs_failures == 0 else "FILESYSTEM_AUDIT_HAS_FAILURES",
        "mode": "filesystem_only" if not args.git_ref else "filesystem_and_git_archive",
        "summary": {"path": rel_repo(summary_path), "sha256": summary_sha,
                    "declared_counts": summary_checks},
        "counts": {**aggregate, "run_receipts": len(runs), "source_proof_and_input_checks": aggregate["spec_file_checks"] + aggregate["gate_input_file_checks"],
                   "summary_check_failures": failed_summary_checks, "filesystem_failures": fs_failures,
                   "gate_attempt_status_scope": "accepted values are copied from state.gates; CI conclusion is checked separately"},
        "runs": runs,
        "non_success_ci_runs": [{"run_id": r["run_id"], "batch": r["batch"], "status": r["ci"].get("status"),
                                 "conclusion": r["ci"].get("conclusion")}
                                for r in runs if r["ci"].get("conclusion") != "success"],
        "gate_rejections": [{"run_id": r["run_id"], "candidate": g["candidate"], "accepted": g["accepted"],
                             "gate_exit": g.get("gate_exit")}
                            for r in runs for g in r["gate_attempts"] if not g["accepted"]],
        "verification_failures": [{"run_id": r["run_id"], "category": category, "path": check.get("path"),
                                   "status": check.get("status"), "candidate": check.get("candidate"),
                                   "filename": check.get("filename")}
                                  for r in runs
                                  for category, checks in (("raw_artifact", r["raw_artifacts"].get("files", [])),
                                                           ("source_or_proof", r["spec_files"]),
                                                           ("gate_input_copy", [x for g in r["gate_attempts"] for x in g["input_files"]]))
                                  for check in checks if check.get("status") != "MATCH"],
        "git_archive": git_result if git_result else {"status": "NOT_REQUESTED", "scope": "filesystem hashes only; no archived-byte claim"},
        "limits": ["Gate acceptance is read from the candidate-specific state.gates entry; completed CI alone is not a gate pass.",
                   "Raw-artifact verification checks each listed extracted file against its receipt SHA-256 and byte size.",
                   "Git-ref mode compares archived blob bytes to the verified workspace/manifest SHA and size; missing Git objects are reported, not treated as pass."],
    }
    if git_result:
        result["counts"]["git_archive_paths"] = git_result["counts"]["paths_checked"]
        result["counts"]["git_archive_missing"] = git_result["counts"]["missing_in_ref"]
        result["counts"]["git_archive_mismatched"] = git_result["counts"]["mismatched"] + git_result["counts"]["git_errors"]
        if result["counts"]["git_archive_missing"] or result["counts"]["git_archive_mismatched"]:
            result["status"] = "GIT_ARCHIVE_HAS_MISSING_OR_MISMATCHED_FILES"
        elif fs_failures == 0:
            result["status"] = "VERIFIED_FILESYSTEM_AND_GIT"
    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"status": result["status"], "mode": result["mode"], "output": rel_repo(output_path),
                      "counts": result["counts"],
                      "gate_accepted": [(r["run_id"], g["candidate"], g["accepted"])
                                        for r in runs for g in r["gate_attempts"]]}, indent=2))
    if fs_failures or (git_result and (result["counts"]["git_archive_missing"] or
                                      result["counts"]["git_archive_mismatched"])):
        raise SystemExit(1)


if __name__ == "__main__":
    main()
