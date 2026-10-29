"""Audit the saved R25 CI artifact without contacting GitHub or starting another run."""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
import math
import re
import sys
import zipfile
import tempfile
from pathlib import Path, PurePosixPath

HERE = Path(__file__).resolve().parent
ROUND = HERE.parent
REPO = ROUND.parents[3]
DEFAULT_EVIDENCE = ROUND / "evidence" / "dispatch-20261029T071936Z"
PINNED = HERE / "pinned-source"
OFFICIAL_COMMIT = "accb82b6e2adeda1b41a57a260d68fb3879c427e"
PINNED_BLOBS = {
    "config.py": "6743c5c0060b7babab5155ffe1e0dc94dbf8a742",
    "timing.py": "5b52a105a53089369977a7148541885904496d1c",
    "multiseed.py": "299b2e77db596a2720db3d54c2df46b3e5d2c3b3",
    "scoring.py": "f5e1b500bc3976764eea0451c500907e08e17dda",
}


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def git_blob_sha(data: bytes) -> str:
    return hashlib.sha1(b"blob " + str(len(data)).encode("ascii") + b"\0" + data).hexdigest()


def load_pinned_modules():
    sources = {}
    for name, expected in PINNED_BLOBS.items():
        data = (PINNED / name).read_bytes()
        actual = git_blob_sha(data)
        if actual != expected:
            raise ValueError(f"pinned source mismatch: {name} blob {actual}, expected {expected}")
        sources[name] = {"git_blob_sha": actual, "bytes": len(data), "sha256": sha256(data)}

    modules = {}
    for name in ("multiseed", "timing", "config", "scoring"):
        spec = importlib.util.spec_from_file_location(name, PINNED / f"{name}.py")
        if spec is None or spec.loader is None:
            raise ImportError(f"cannot load pinned {name}.py")
        module = importlib.util.module_from_spec(spec)
        sys.modules[name] = module
        spec.loader.exec_module(module)
        modules[name] = module
    return modules, sources


def read_json(data: bytes, label: str):
    try:
        return json.loads(data.decode("utf-8")), None
    except Exception as exc:
        return None, f"{label}: {type(exc).__name__}: {exc}"


def add_payload(payloads: dict[str, bytes], inventory: list[dict], name: str, data: bytes, kind: str):
    payloads[name] = data
    inventory.append({"path": name, "kind": kind, "bytes": len(data), "sha256": sha256(data)})


def collect_inputs(paths: list[Path]):
    payloads: dict[str, bytes] = {}
    inventory: list[dict] = []
    containers: list[dict] = []
    for root in paths:
        if not root.exists():
            continue
        if root.is_dir():
            files = sorted(p for p in root.rglob("*") if p.is_file())
            for path in files:
                rel = path.relative_to(root).as_posix()
                key = f"{root.name}/{rel}"
                data = path.read_bytes()
                if path.suffix.lower() == ".zip":
                    add_payload(payloads, inventory, key, data, "artifact_container")
                    containers.append({"path": key, "sha256": sha256(data), "bytes": len(data)})
                    try:
                        with zipfile.ZipFile(path) as archive:
                            for member in archive.infolist():
                                if member.is_dir():
                                    continue
                                raw = archive.read(member)
                                member_key = f"{key}!{PurePosixPath(member.filename).as_posix()}"
                                add_payload(payloads, inventory, member_key, raw, "artifact_member")
                    except Exception as exc:
                        inventory.append({"path": key, "kind": "zip_error", "error": f"{type(exc).__name__}: {exc}"})
                else:
                    add_payload(payloads, inventory, key, data, "file")
        elif root.is_file():
            data = root.read_bytes()
            if root.suffix.lower() == ".zip":
                add_payload(payloads, inventory, root.name, data, "artifact_container")
                containers.append({"path": root.name, "sha256": sha256(data), "bytes": len(data)})
                try:
                    with zipfile.ZipFile(root) as archive:
                        for member in archive.infolist():
                            if member.is_dir():
                                continue
                            raw = archive.read(member)
                            member_key = f"{root.name}!{PurePosixPath(member.filename).as_posix()}"
                            add_payload(payloads, inventory, member_key, raw, "artifact_member")
                except Exception as exc:
                    inventory.append({"path": root.name, "kind": "zip_error", "error": f"{type(exc).__name__}: {exc}"})
            else:
                add_payload(payloads, inventory, root.name, data, "file")
    return payloads, inventory, containers


def find_payload(payloads: dict[str, bytes], name: str) -> tuple[str | None, bytes | None, str | None]:
    normalized = PurePosixPath(name.replace("\\", "/")).as_posix().lstrip("./")
    matches = [
        (key, value)
        for key, value in payloads.items()
        if key == normalized or key.endswith("/" + normalized) or key.endswith("!" + normalized)
    ]
    if not matches and "/" not in normalized:
        matches = [(key, value) for key, value in payloads.items() if PurePosixPath(key.split("!")[-1]).name == normalized]
    unique = {sha256(value): (key, value) for key, value in matches}
    if len(unique) == 1:
        key, value = next(iter(unique.values()))
        return key, value, None
    if not unique:
        return None, None, "missing"
    return None, None, "ambiguous"


def verify_file_hash_manifest(payloads: dict[str, bytes]) -> dict:
    path, data, error = find_payload(payloads, "file-hashes.json")
    if error:
        return {"status": "UNKNOWN", "reason": error, "entries": []}
    manifest, parse_error = read_json(data, path or "file-hashes.json")
    if parse_error or not isinstance(manifest, dict):
        return {"status": "FAIL", "reason": parse_error or "file-hashes.json is not an object", "entries": []}
    rows = []
    for rel, expected in sorted(manifest.items()):
        if not isinstance(expected, dict):
            rows.append({"path": rel, "status": "FAIL", "reason": "invalid manifest row"})
            continue
        actual_path, actual, lookup_error = find_payload(payloads, rel)
        if lookup_error:
            rows.append({"path": rel, "status": "UNKNOWN", "reason": lookup_error})
            continue
        got = {"bytes": len(actual), "sha256": sha256(actual)}
        ok = got["bytes"] == expected.get("bytes") and got["sha256"] == expected.get("sha256")
        rows.append({"path": rel, "artifact_path": actual_path, "expected": expected, "actual": got, "status": "MATCH" if ok else "MISMATCH"})
    statuses = {row["status"] for row in rows}
    return {
        "status": "FAIL" if "MISMATCH" in statuses or "FAIL" in statuses else "UNKNOWN" if "UNKNOWN" in statuses else "PASS",
        "manifest_path": path,
        "entries_count": len(rows),
        "entries": rows,
    }


def verify_original_artifact_hashes(payloads: dict[str, bytes]) -> dict:
    path, data, error = find_payload(payloads, "original-artifact-hashes.json")
    if error:
        return {"status": "UNKNOWN", "reason": error, "entries": []}
    receipt, parse_error = read_json(data, path or "original-artifact-hashes.json")
    if parse_error or not isinstance(receipt, dict):
        return {"status": "FAIL", "reason": parse_error or "receipt is not an object", "entries": []}
    expected_files = receipt.get("files", {})
    rows = []
    for rel, expected in sorted(expected_files.items()):
        actual_path, actual, lookup_error = find_payload(payloads, rel)
        if lookup_error:
            rows.append({"path": rel, "status": "UNKNOWN", "reason": lookup_error})
            continue
        got = {"bytes": len(actual), "sha256": sha256(actual)}
        ok = got["bytes"] == expected.get("bytes") and got["sha256"] == expected.get("sha256")
        rows.append({"path": rel, "artifact_path": actual_path, "expected": expected, "actual": got, "status": "MATCH" if ok else "MISMATCH"})
    statuses = {row["status"] for row in rows}
    return {
        "status": "FAIL" if "MISMATCH" in statuses else "UNKNOWN" if "UNKNOWN" in statuses else "PASS",
        "receipt_path": path,
        "artifact": receipt.get("artifact", {}),
        "entries_count": len(rows),
        "entries": rows,
    }


def verify_artifact_metadata(payloads: dict[str, bytes], original_receipt: dict, run_id) -> dict:
    path, data, error = find_payload(payloads, "artifacts.json")
    if error:
        return {"status": "UNKNOWN", "reason": error}
    listing, parse_error = read_json(data, path or "artifacts.json")
    if parse_error or not isinstance(listing, dict):
        return {"status": "FAIL", "reason": parse_error or "artifacts.json is not an object", "path": path}
    artifact = original_receipt.get("artifact") or original_receipt
    rows = [item for item in listing.get("artifacts", []) if item.get("id") == artifact.get("id")]
    if len(rows) != 1:
        return {"status": "FAIL", "path": path, "matching_artifacts": len(rows), "expected_id": artifact.get("id")}
    listed = rows[0]
    fields = ("id", "name", "size_in_bytes", "digest")
    matches = {field: listed.get(field) == artifact.get(field) for field in fields}
    run_match = (listed.get("workflow_run") or {}).get("id") == run_id
    matches["workflow_run_id"] = run_match
    return {
        "status": "PASS" if all(matches.values()) else "FAIL",
        "path": path,
        "metadata_matches_original_receipt": matches,
        "artifact_id": listed.get("id"),
        "name": listed.get("name"),
        "size_in_bytes": listed.get("size_in_bytes"),
        "digest": listed.get("digest"),
        "workflow_run_id": (listed.get("workflow_run") or {}).get("id"),
    }


def validate_dispatch_and_summary(dispatch: dict | None, ci_run: dict | None, summary: dict | None, plan: dict) -> dict:
    frozen_files = (dispatch or {}).get("frozen_files", {})
    candidate_freezes = []
    for candidate in plan.get("candidates", []):
        frozen_sha = frozen_files.get(candidate.get("path"))
        candidate_freezes.append({
            "candidate": candidate.get("name"),
            "plan_sha256": candidate.get("sha256"),
            "dispatch_frozen_sha256": frozen_sha,
            "status": "PASS" if frozen_sha == candidate.get("sha256") else "MISMATCH" if frozen_sha else "UNKNOWN",
        })
    run = ci_run or {}
    dispatch_run = (dispatch or {}).get("run", {})
    run_identity_match = (
        run.get("databaseId") == dispatch_run.get("databaseId")
        and run.get("headSha") == (dispatch or {}).get("source_commit")
    ) if ci_run and dispatch else None
    if summary is None:
        return {
            "status": "PENDING_ARTIFACT",
            "dispatch_history": None if dispatch is None else {
                "saved_run_status": dispatch_run.get("status", "UNKNOWN"),
                "run_id": dispatch_run.get("databaseId"),
                "source_commit": dispatch.get("source_commit"),
            },
            "ci_run_terminal_state": {k: run.get(k) for k in ("status", "conclusion", "databaseId", "headSha", "updatedAt", "url") if run.get(k) is not None},
            "dispatch_ci_run_identity_match": "PASS" if run_identity_match else "FAIL" if run_identity_match is False else "UNKNOWN",
            "summary": "MISSING",
            "source_commit_match": "UNKNOWN",
            "official_commit_match": "UNKNOWN",
            "originals_unchanged": "UNKNOWN",
            "candidate_frozen_hashes": candidate_freezes,
            "proofs": [],
        }
    source_match = summary.get("source_commit") == (dispatch or {}).get("source_commit") if dispatch else None
    source_run_match = summary.get("source_commit") == run.get("headSha") if ci_run else None
    official_match = summary.get("official_commit") == plan.get("official_commit")
    before, after = summary.get("protected_before"), summary.get("protected_after")
    protected = (
        "UNKNOWN" if not isinstance(before, dict) or not isinstance(after, dict)
        else "PASS" if before == after and summary.get("originals_unchanged") is True
        else "FAIL"
    )
    proofs = []
    results = {row.get("name"): row for row in summary.get("results", []) if isinstance(row, dict)}
    for candidate in plan.get("candidates", []):
        row = results.get(candidate.get("name"))
        if row is None:
            proofs.append({"candidate": candidate.get("name"), "status": "UNKNOWN", "candidate_sha256_match": "UNKNOWN", "reason": "missing result row"})
            continue
        verdict = row.get("verdict") or {}
        candidate_sha_match = row.get("sha256") == candidate.get("sha256")
        proofs.append({
            "candidate": candidate.get("name"),
            "candidate_sha256": row.get("sha256"),
            "candidate_sha256_match": "PASS" if candidate_sha_match else "FAIL",
            "proof_state": row.get("proof_state", "UNKNOWN"),
            "proof_exit_code": row.get("proof_exit_code"),
            "verdict_stage": verdict.get("stage"),
            "verdict_passed": verdict.get("passed"),
            "verdict_reason": verdict.get("reason"),
            "helper_audit": row.get("helper_audit"),
            "measurement_state": row.get("measurement_state", "UNKNOWN"),
            "measurements": row.get("measurements", []),
        })
    proof_passes = [
        row.get("candidate_sha256_match") == "PASS"
        and row.get("proof_state") == "FULL_ORIGINAL_PROOF_GATE_PASS"
        and row.get("proof_exit_code") == 0
        and (row.get("helper_audit") is None or row["helper_audit"].get("pass") is True)
        for row in proofs
    ]
    retained = results.get("baseline")
    shipped = plan.get("shipped_sha256")
    baseline = None
    if retained is not None:
        baseline = {
            "candidate_sha256": retained.get("sha256"),
            "matches_shipped_reference": retained.get("sha256") == shipped,
            "proof_state": retained.get("proof_state", "UNKNOWN"),
            "proof_exit_code": retained.get("proof_exit_code"),
            "verdict_stage": (retained.get("verdict") or {}).get("stage"),
            "verdict_passed": (retained.get("verdict") or {}).get("passed"),
            "verifier_fingerprint": (retained.get("verdict") or {}).get("verifier_fingerprint"),
            "verifier_fingerprint_end": (retained.get("verdict") or {}).get("verifier_fingerprint_end"),
            "measurement_state": retained.get("measurement_state", "UNKNOWN"),
        }
    return {
        "status": "PRESENT",
        "ci_run_id": run.get("databaseId", dispatch_run.get("databaseId")),
        "ci_run_status": run.get("status", "UNKNOWN"),
        "ci_run_conclusion": run.get("conclusion", "UNKNOWN"),
        "ci_run_updated_at": run.get("updatedAt"),
        "ci_run_url": run.get("url"),
        "dispatch_historical_status": dispatch_run.get("status", "UNKNOWN"),
        "dispatch_ci_run_identity_match": "PASS" if run_identity_match else "FAIL" if run_identity_match is False else "UNKNOWN",
        "summary_source_commit": summary.get("source_commit"),
        "dispatch_source_commit": (dispatch or {}).get("source_commit"),
        "source_commit_match": "PASS" if source_match else "FAIL" if source_match is False else "UNKNOWN",
        "ci_run_source_commit_match": "PASS" if source_run_match else "FAIL" if source_run_match is False else "UNKNOWN",
        "official_commit": summary.get("official_commit"),
        "official_commit_match": "PASS" if official_match else "FAIL",
        "complete_flag": summary.get("complete", "UNKNOWN"),
        "all_requested_proofs_pass": summary.get("all_requested_proofs_pass", "UNKNOWN"),
        "all_requested_measurements_complete": summary.get("all_requested_measurements_complete", "UNKNOWN"),
        "independently_verified_all_proofs_pass": all(proof_passes) if proofs else "UNKNOWN",
        "candidate_frozen_hashes": candidate_freezes,
        "originals_unchanged": protected,
        "retained_baseline_original_obligation": baseline,
        "error": {k: summary.get(k) for k in ("error_type", "error") if summary.get(k) is not None},
        "proofs": proofs,
    }


def request_check(request: dict, candidate: dict, seed: int, modules: dict, reference_sha: str, config_obj=None) -> dict:
    config = modules["config"]
    parsed = config.MeasurementRequest.parse(request)
    expected_names = {
        "environment": "local",
        "seed": seed,
        "candidate_hash": candidate["sha256"],
        "reference_hash": reference_sha,
    }
    checks = {key: request.get(key) == value for key, value in expected_names.items() if value is not None}
    checks["environment"] = request.get("environment") == "local"
    checks["unique_cells"] = len(parsed.cells) == len(set(parsed.cells))
    checks["30_model_batch_cells"] = len(parsed.cells) == 30
    checks["six_seeded_workloads"] = len(parsed.workloads) == 6
    checks["180_expanded_workload_cells"] = len(parsed.cells) * len(parsed.workloads) == 180
    timing = request.get("timing", {})
    checks["five_rounds"] = timing.get("rounds") == 5
    checks["three_inner_repetitions"] = timing.get("inner") == 3
    checks["two_ms_cell_target"] = timing.get("cell_ms") == 2
    checks["driver_time_limits"] = all(timing.get(k) == v for k, v in {
        "build_seconds": 600,
        "cached_build_seconds": 180,
        "benchmark_seconds": 300,
        "run_seconds": 120,
    }.items())
    if config_obj is not None:
        board = config_obj.plan("overall")
        checks["reference_hash"] = request.get("reference_hash") == board["initial_reference"]
        checks["benchmark_identity"] = request.get("benchmark_identity") == board["benchmark_identity"]
        checks["runner_identity"] = request.get("identity") == config_obj.environments["local"]["identity"]
        expected_timing = config_obj.timing | board["timing"] | config_obj.environments["local"]["timing"]
        expected_timing.update(build_seconds=600, cached_build_seconds=180, benchmark_seconds=300, run_seconds=120)
        checks["timing_matches_driver"] = request.get("timing") == expected_timing
    else:
        checks["benchmark_identity"] = None
        checks["runner_identity"] = None
        checks["timing_matches_official_config"] = None
    status = "FAIL" if any(value is False for value in checks.values()) else "UNKNOWN" if any(value is None for value in checks.values()) else "PASS"
    return {
        "status": status,
        "candidate": candidate["name"],
        "seed": seed,
        "candidate_hash": request.get("candidate_hash"),
        "request_hash": parsed.identity_hash(),
        "cell_count": len(parsed.cells),
        "workload_count": len(parsed.workloads),
        "expanded_workload_cells": len(parsed.cells) * len(parsed.workloads),
        "rounds": request.get("timing", {}).get("rounds"),
        "inner": request.get("timing", {}).get("inner"),
        "cell_ms": request.get("timing", {}).get("cell_ms"),
        "checks": checks,
    }


def measurement_check(request: dict, raw_result: dict, cell_weights: dict | None, modules: dict) -> dict:
    if not isinstance(raw_result, dict) or not isinstance(raw_result.get("result"), dict):
        return {"status": "FAIL", "error": (raw_result or {}).get("error", {"reason": "missing result object"})}
    result = raw_result["result"]
    rounds = result.get("rounds", [])
    expected_rounds = request.get("timing", {}).get("rounds")
    expected_expanded = len(request.get("cells", [])) * len(request.get("workloads", []))
    row_cells = [len(row.get("cells", {})) for row in rounds if isinstance(row, dict)]
    ns_values = []
    checksum_pairs = 0
    checksum_mismatches = 0
    for round_row in rounds:
        for cell in round_row.get("cells", {}).values():
            for key in ("reference_ns", "candidate_ns"):
                if key in cell:
                    ns_values.append(cell[key])
            if "reference_checksum" in cell and "candidate_checksum" in cell:
                checksum_pairs += 1
                checksum_mismatches += cell["reference_checksum"] != cell["candidate_checksum"]
    try:
        round_scores = modules["scoring"].validate_result(request, result, cell_weights)
        scorer_status = "PASS"
        scorer_error = None
    except Exception as exc:
        round_scores = None
        scorer_status = "FAIL"
        scorer_error = f"{type(exc).__name__}: {exc}"
    finite_positive_ns = all(
        not isinstance(x, bool) and isinstance(x, (int, float)) and math.isfinite(x) and x > 0
        for x in ns_values
    )
    complete = (
        len(rounds) == expected_rounds
        and all(count == expected_expanded for count in row_cells)
        and len(ns_values) == 2 * expected_rounds * expected_expanded
        and finite_positive_ns
        and checksum_pairs == expected_rounds * expected_expanded
        and checksum_mismatches == 0
        and scorer_status == "PASS"
    )
    return {
        "status": "PASS" if complete else "FAIL",
        "request_hash_match": result.get("request_hash") == modules["config"].measurement_hash(request),
        "workloads_match": result.get("workloads") == request.get("workloads"),
        "expected_rounds": expected_rounds,
        "actual_rounds": len(rounds),
        "expected_workload_cells_per_round": expected_expanded,
        "actual_cells_per_round": row_cells,
        "expected_nanosecond_values": 2 * expected_rounds * expected_expanded,
        "actual_nanosecond_values": len(ns_values),
        "finite_positive_nanoseconds": finite_positive_ns,
        "checksum_pairs": checksum_pairs,
        "checksum_mismatches": checksum_mismatches,
        "pinned_scoring_validate_result": scorer_status,
        "pinned_scoring_error": scorer_error,
        "per_round_weighted_ratio": round_scores,
        "provenance_identity": (result.get("provenance") or {}).get("identity"),
        "request_identity": request.get("identity"),
    }


def audit_verdict_receipts(plan: dict, summary: dict | None, payloads: dict[str, bytes]) -> list[dict]:
    summary_rows = {row.get("name"): row for row in (summary or {}).get("results", []) if isinstance(row, dict)}
    rows = []
    for candidate in plan.get("candidates", []):
        name = candidate.get("name")
        path, data, lookup_error = find_payload(payloads, f"{name}-verdict.json")
        if lookup_error:
            rows.append({"candidate": name, "status": "UNKNOWN", "reason": lookup_error})
            continue
        verdict, error = read_json(data, path or f"{name}-verdict.json")
        if error or not isinstance(verdict, dict):
            rows.append({"candidate": name, "status": "FAIL", "path": path, "error": error or "verdict is not an object"})
            continue
        summary_verdict = (summary_rows.get(name) or {}).get("verdict")
        compared = ["submission", "stage", "passed", "reason", "verifier_fingerprint", "verifier_fingerprint_end", "seconds", "exhausted"]
        agrees = isinstance(summary_verdict, dict) and all(verdict.get(k) == summary_verdict.get(k) for k in compared)
        rows.append({
            "candidate": name,
            "path": path,
            "sha256": sha256(data),
            "status": "PASS" if agrees else "MISMATCH" if summary_verdict is not None else "UNKNOWN",
            "matches_summary_verdict": agrees if summary_verdict is not None else "UNKNOWN",
            "proof_exit_code_from_summary": (summary_rows.get(name) or {}).get("proof_exit_code"),
            "stage": verdict.get("stage"),
            "passed": verdict.get("passed"),
            "reason": verdict.get("reason"),
            "verifier_fingerprint": verdict.get("verifier_fingerprint"),
            "verifier_fingerprint_end": verdict.get("verifier_fingerprint_end"),
        })
    return rows


def audit_helper_axioms(plan: dict, summary: dict | None, payloads: dict[str, bytes]) -> dict:
    allowed = {"propext", "Classical.choice", "Quot.sound"}
    summary_rows = {row.get("name"): row for row in (summary or {}).get("results", []) if isinstance(row, dict)}
    candidates = []
    for candidate in plan.get("candidates", []):
        roots = candidate.get("explicit_helper_roots", candidate.get("helper_roots", []))
        if roots:
            candidates.append((candidate, roots))
    if not candidates:
        return {"status": "NOT_REQUESTED", "expected_count": 0, "printed_count": 0, "roots": [], "per_candidate": []}

    all_roots = []
    per_candidate = []
    for candidate, expected in candidates:
        name = candidate.get("name")
        result_row = summary_rows.get(name, {})
        summary_audit = result_row.get("helper_audit") or {}
        if result_row.get("proof_state") != "FULL_ORIGINAL_PROOF_GATE_PASS" or result_row.get("proof_exit_code") != 0:
            per_candidate.append({"candidate": name, "status": "NOT_RUN", "expected_count": len(expected), "printed_count": 0, "reason": "candidate did not pass the original proof gate"})
            continue
        path, data, lookup_error = find_payload(payloads, f"helper-{name}.log")
        if lookup_error:
            per_candidate.append({"candidate": name, "status": "UNKNOWN", "expected_count": len(expected), "printed_count": 0, "reason": lookup_error})
            continue
        reports = re.findall(r"'([^']+)' depends on axioms: \[([^\]]*)\]", data.decode("utf-8", "replace").replace("\n", " "))
        rows = []
        for root_name, axiom_text in reports:
            found = {x.strip() for x in axiom_text.split(",") if x.strip()}
            rows.append({"root": root_name, "candidate": name, "axioms": sorted(found), "allowed_only": found <= allowed})
        names = [row["root"] for row in rows]
        exact_roots = len(rows) == len(expected) and set(names) == set(expected)
        all_allowed = len(rows) == len(expected) and all(row["allowed_only"] for row in rows)
        summary_agrees = (
            summary_audit.get("expected") == len(expected)
            and summary_audit.get("printed") == len(rows)
            and summary_audit.get("allowed_only") is all_allowed
            and summary_audit.get("pass") is True
        )
        status = "PASS" if exact_roots and all_allowed and summary_agrees else "FAIL"
        per_candidate.append({
            "candidate": name,
            "status": status,
            "path": path,
            "sha256": sha256(data),
            "expected_count": len(expected),
            "printed_count": len(rows),
            "root_names_match_plan": exact_roots,
            "all_allowed_only": all_allowed,
            "summary_agrees": summary_agrees,
        })
        all_roots.extend(rows)
    executed = [row for row in per_candidate if row["status"] in ("PASS", "FAIL")]
    return {
        "status": "FAIL" if any(row["status"] == "FAIL" for row in per_candidate) else "PASS" if executed and all(row["status"] == "PASS" for row in executed) else "NOT_RUN",
        "expected_count": sum(row["expected_count"] for row in per_candidate if row["status"] != "NOT_RUN"),
        "printed_count": len(all_roots),
        "allowed_axioms": sorted(allowed),
        "all_allowed_only": bool(all_roots) and all(row["allowed_only"] for row in all_roots),
        "roots": all_roots,
        "per_candidate": per_candidate,
    }


def batch1_metadata_self_check(
    run_id,
    plan: dict,
    plan_source: dict,
    dispatch: dict | None,
    ci_run: dict | None,
    summary: dict | None,
    dispatch_summary: dict,
    original_hashes: dict,
    runner_hashes: dict,
    artifact_listing: dict,
    verdict_receipts: list[dict],
    helper_audit: dict,
    measurement_rows: list[dict],
    score_rows: list[dict],
) -> dict:
    if run_id != 40834710293:
        return {"status": "NOT_APPLICABLE", "scope": "CI batch 1 only"}
    results = {row.get("name"): row for row in (summary or {}).get("results", []) if isinstance(row, dict)}
    proof_receipts = {row.get("candidate"): row for row in verdict_receipts}
    required = {"baseline", "adaptive", "patch-norm", "widen7", "order-key-v2"}
    plan_candidates = {row.get("name"): row for row in plan.get("candidates", [])}
    allowed = {"propext", "Classical.choice", "Quot.sound"}
    baseline = results.get("baseline", {})
    widen = results.get("widen7", {})
    rejected = {name: results.get(name, {}) for name in ("adaptive", "patch-norm", "order-key-v2")}
    checks = {
        "artifact_plan_used": plan_source.get("kind") == "artifact" and str(plan_source.get("path", "")).endswith("plan.json"),
        "five_frozen_candidates": set(plan_candidates) == required,
        "ci_run_terminal_and_identity_consistent": (ci_run or {}).get("status") == "completed" and (ci_run or {}).get("conclusion") == "failure" and (ci_run or {}).get("databaseId") == (dispatch or {}).get("run", {}).get("databaseId") and (ci_run or {}).get("headSha") == (dispatch or {}).get("source_commit"),
        "pinned_official_commit_consistent": plan.get("official_commit") == OFFICIAL_COMMIT and (summary or {}).get("official_commit") == OFFICIAL_COMMIT,
        "summary_source_matches_run": (summary or {}).get("source_commit") == (ci_run or {}).get("headSha"),
        "original_artifact_20_of_20": original_hashes.get("status") == "PASS" and original_hashes.get("entries_count") == 20,
        "runner_manifest_19_of_19": runner_hashes.get("status") == "PASS" and runner_hashes.get("entries_count") == 19,
        "artifact_listing_matches_receipt": artifact_listing.get("status") == "PASS",
        "all_candidate_hashes_match_frozen_plan": all(row.get("status") == "PASS" for row in dispatch_summary.get("candidate_frozen_hashes", [])) and len(dispatch_summary.get("candidate_frozen_hashes", [])) == 5 and all(results.get(name, {}).get("sha256") == plan_candidates[name].get("sha256") for name in required),
        "original_sources_unchanged": dispatch_summary.get("originals_unchanged") == "PASS" and (summary or {}).get("originals_unchanged") is True,
        "retained_baseline_same_as_shipped_and_full_gate_pass": baseline.get("sha256") == plan.get("shipped_sha256") and baseline.get("proof_state") == "FULL_ORIGINAL_PROOF_GATE_PASS" and baseline.get("proof_exit_code") == 0 and (baseline.get("verdict") or {}).get("passed") is True and (baseline.get("verdict") or {}).get("verifier_fingerprint") == (baseline.get("verdict") or {}).get("verifier_fingerprint_end") and proof_receipts.get("baseline", {}).get("status") == "PASS",
        "widen7_full_gate_pass": widen.get("proof_state") == "FULL_ORIGINAL_PROOF_GATE_PASS" and widen.get("proof_exit_code") == 0 and (widen.get("verdict") or {}).get("passed") is True and proof_receipts.get("widen7", {}).get("status") == "PASS",
        "all_six_helper_axiom_roots_match_and_are_allowed": helper_audit.get("status") == "PASS" and helper_audit.get("expected_count") == 6 and helper_audit.get("printed_count") == 6 and all(set(row.get("axioms", [])) <= allowed for row in helper_audit.get("roots", [])),
        "three_other_candidates_rejected_at_policy": all(rejected[name].get("proof_state") == "REJECTED_OR_INFRASTRUCTURE" and rejected[name].get("proof_exit_code") == 1 and (rejected[name].get("verdict") or {}).get("stage") == "policy" and proof_receipts.get(name, {}).get("status") == "PASS" for name in rejected),
        "performance_all_not_run": all(row.get("measurement_state") == "NOT_RUN" for row in results.values()) and bool(results) and bool(measurement_rows) and all(row.get("status") == "NOT_RUN" for row in measurement_rows),
        "no_synthetic_score_or_nanoseconds": all(not any(key in row for key in ("score_ratio", "gain_lower", "reference_ns", "candidate_ns")) for row in score_rows) and all(not any(key in row for key in ("reference_ns", "candidate_ns", "ratio", "score")) for row in measurement_rows),
    }
    return {
        "status": "PASS" if all(checks.values()) else "FAIL",
        "scope": "Batch 1 metadata/raw-JSON checks only; no model rerun",
        "checks": checks,
        "performance_state": "NOT_RUN",
        "official_score": "NOT_COMPUTED",
        "current_champion_comparison": "NOT_COMPUTED",
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--input", action="append", type=Path, help="evidence directory, artifact directory, or downloaded artifact ZIP; repeatable")
    parser.add_argument("--plan", type=Path, help="explicit frozen plan fallback, used only if the artifact does not contain plan.json")
    parser.add_argument("--output", type=Path, default=HERE / "analysis.json")
    args = parser.parse_args()
    inputs = args.input or [DEFAULT_EVIDENCE]
    payloads, inventory, containers = collect_inputs(inputs)
    modules, pinned_hashes = load_pinned_modules()

    dispatch_path, dispatch_bytes, dispatch_lookup = find_payload(payloads, "dispatch.json")
    dispatch = None
    dispatch_error = None
    if dispatch_bytes is not None:
        dispatch, dispatch_error = read_json(dispatch_bytes, dispatch_path or "dispatch.json")
    ci_run_path, ci_run_bytes, _ = find_payload(payloads, "ci-run.json")
    ci_run = None
    ci_run_error = None
    if ci_run_bytes is not None:
        ci_run, ci_run_error = read_json(ci_run_bytes, ci_run_path or "ci-run.json")

    artifact_plan_path, artifact_plan_bytes, _ = find_payload(payloads, "plan.json")
    plan = None
    plan_error = None
    plan_source = None
    if artifact_plan_bytes is not None:
        plan, plan_error = read_json(artifact_plan_bytes, artifact_plan_path or "plan.json")
        plan_source = {"kind": "artifact", "path": artifact_plan_path}
    elif args.plan is not None:
        plan, plan_error = read_json(args.plan.read_bytes(), str(args.plan))
        plan_source = {"kind": "explicit_fallback", "path": str(args.plan)}
    else:
        plan = {}
        plan_error = "artifact plan.json missing; no live ci-plan.json fallback is used"
        plan_source = {"kind": "missing", "path": None}

    summary_path, summary_bytes, summary_lookup_error = find_payload(payloads, "summary.json")
    summary = None
    summary_error = None
    if summary_bytes is not None:
        summary, summary_error = read_json(summary_bytes, summary_path or "summary.json")
    if not isinstance(summary, dict):
        summary_for_report = None
        if summary is not None:
            summary_error_list = [f"summary.json must be an object, got {type(summary).__name__}"]
        else:
            summary_error_list = []
    else:
        summary_for_report = summary
        summary_error_list = [x for x in (summary_lookup_error, summary_error) if x]
    if not isinstance(plan, dict):
        plan = {}
    artifact_hash_check = verify_file_hash_manifest(payloads)
    original_artifact_hash_check = verify_original_artifact_hashes(payloads)
    artifact_listing_check = verify_artifact_metadata(
        payloads,
        original_artifact_hash_check.get("artifact", {}),
        (ci_run or {}).get("databaseId"),
    )

    config_path, config_bytes, _ = find_payload(payloads, "overall-config.toml")
    config_obj = None
    config_error = None
    if config_bytes is not None:
        try:
            with tempfile.TemporaryDirectory(prefix="torchlean-r25-analysis-") as tmp:
                config_file = Path(tmp) / "overall-config.toml"
                config_file.write_bytes(config_bytes)
                config_obj = modules["config"].Config.load(config_file)
        except Exception as exc:
            config_error = f"{type(exc).__name__}: {exc}"

    request_rows = []
    request_map: dict[tuple[str, int], dict] = {}
    summary_result_map = {row.get("name"): row for row in (summary_for_report or {}).get("results", []) if isinstance(row, dict)}
    measured_candidates = [c for c in plan.get("candidates", []) if c.get("measure")]
    expected_requests = [(c, int(seed)) for c in measured_candidates for seed in plan.get("seeds", [])]
    for candidate, seed in expected_requests:
        filename = f"{candidate['name']}-{seed}-request.json"
        request_file, request_bytes, lookup_error = find_payload(payloads, filename)
        if lookup_error:
            result_row = summary_result_map.get(candidate["name"], {})
            proof_failed = result_row.get("proof_exit_code") not in (None, 0) or result_row.get("proof_state") == "REJECTED_OR_INFRASTRUCTURE"
            not_run = result_row.get("measurement_state") == "NOT_RUN" or proof_failed
            request_rows.append({"candidate": candidate["name"], "seed": seed, "status": "NOT_RUN" if not_run else "UNKNOWN", "reason": "proof did not pass; request builder was not reached" if not_run else lookup_error})
            continue
        request, error = read_json(request_bytes, request_file or filename)
        if error:
            request_rows.append({"candidate": candidate["name"], "seed": seed, "status": "FAIL", "reason": error})
            continue
        try:
            row = request_check(request, candidate, seed, modules, plan.get("shipped_sha256"), config_obj)
            row["path"] = request_file
            request_rows.append(row)
            request_map[(candidate["name"], seed)] = request
        except Exception as exc:
            request_rows.append({"candidate": candidate["name"], "seed": seed, "path": request_file, "status": "FAIL", "error": f"{type(exc).__name__}: {exc}"})

    measurements = []
    measurement_groups: dict[str, list[tuple[dict, dict]]] = {}
    for candidate, seed in expected_requests:
        key = (candidate["name"], seed)
        request = request_map.get(key)
        if request is None:
            result_row = summary_result_map.get(candidate["name"], {})
            proof_failed = result_row.get("proof_exit_code") not in (None, 0) or result_row.get("proof_state") == "REJECTED_OR_INFRASTRUCTURE"
            not_run = result_row.get("measurement_state") == "NOT_RUN" or proof_failed
            measurements.append({"candidate": candidate["name"], "seed": seed, "status": "NOT_RUN" if not_run else "UNKNOWN", "reason": "proof did not pass; measurement was not reached" if not_run else "validated request missing"})
            continue
        filename = f"{candidate['name']}-{seed}-measurement.json"
        result_file, result_bytes, lookup_error = find_payload(payloads, filename)
        if lookup_error:
            result_row = summary_result_map.get(candidate["name"], {})
            proof_failed = result_row.get("proof_exit_code") not in (None, 0) or result_row.get("proof_state") == "REJECTED_OR_INFRASTRUCTURE"
            not_run = result_row.get("measurement_state") == "NOT_RUN" or proof_failed
            measurements.append({"candidate": candidate["name"], "seed": seed, "status": "NOT_RUN" if not_run else "UNKNOWN", "reason": "proof did not pass; measurement was not reached" if not_run else lookup_error})
            continue
        raw_result, error = read_json(result_bytes, result_file or filename)
        if error:
            measurements.append({"candidate": candidate["name"], "seed": seed, "path": result_file, "status": "FAIL", "error": error})
            continue
        weights = None
        if config_obj is not None:
            weights = config_obj.plan("overall")["cells"]
        checked = measurement_check(request, raw_result, weights, modules)
        checked.update(candidate=candidate["name"], seed=seed, path=result_file)
        measurements.append(checked)
        if checked.get("status") == "PASS":
            measurement_groups.setdefault(candidate["name"], []).append((request, raw_result["result"]))

    exploratory_scores = []
    for candidate in measured_candidates:
        pairs = measurement_groups.get(candidate["name"], [])
        if config_obj is None or len(pairs) != len(plan.get("seeds", [])) or not pairs:
            result_row = summary_result_map.get(candidate["name"], {})
            proof_failed = result_row.get("proof_exit_code") not in (None, 0) or result_row.get("proof_state") == "REJECTED_OR_INFRASTRUCTURE"
            not_run = result_row.get("measurement_state") == "NOT_RUN" or proof_failed
            exploratory_scores.append({"candidate": candidate["name"], "status": "NOT_RUN" if not_run else "UNKNOWN", "reason": "proof did not pass; no measurements or score were run" if not_run else "complete request/result cohort or official config missing"})
            continue
        official_plan = config_obj.plan("overall")
        official_plan["strata"] = [
            {
                "environment": request["environment"],
                "identity": request["identity"],
                "seed": request["seed"],
                "weight": 1 / len(pairs),
                "timing": request["timing"],
            }
            for request, _ in pairs
        ]
        try:
            score = modules["scoring"].assess(official_plan, pairs)
            exploratory_scores.append({
                "candidate": candidate["name"],
                "status": "COMPUTED_EXPLORATORY",
                "reference": "pinned shipped baseline",
                "sample_role": plan.get("sample_role", "UNKNOWN"),
                "score_ratio": score["score"],
                "gain_lower": score["gain_lower"],
                "guard_passed": score["guard_passed"],
                "scorer_outcome_under_quick_config": score["outcome"],
                "strata": score["strata"],
                "official_promotion_or_champion_claim": False,
            })
        except Exception as exc:
            exploratory_scores.append({"candidate": candidate["name"], "status": "FAIL", "error": f"{type(exc).__name__}: {exc}"})

    dispatch_summary = validate_dispatch_and_summary(dispatch, ci_run, summary_for_report, plan)
    verdict_receipts = audit_verdict_receipts(plan, summary_for_report, payloads)
    helper_axiom_audit = audit_helper_axioms(plan, summary_for_report, payloads)
    request_complete = bool(expected_requests) and len(request_rows) == len(expected_requests) and all(row.get("status") == "PASS" for row in request_rows)
    measurement_complete = bool(expected_requests) and len(measurements) == len(expected_requests) and all(row.get("status") == "PASS" for row in measurements)
    verified_input_and_measurement_state = (
        "PASS" if request_complete and measurement_complete
        else "FAIL" if any(row.get("status") == "FAIL" for row in request_rows + measurements)
        else "UNKNOWN"
    )
    metadata_self_check = batch1_metadata_self_check(
        (ci_run or {}).get("databaseId"), plan, plan_source, dispatch, ci_run, summary_for_report,
        dispatch_summary, original_artifact_hash_check, artifact_hash_check, artifact_listing_check,
        verdict_receipts, helper_axiom_audit, measurements, exploratory_scores,
    )
    artifact_metadata = (dispatch or {}).get("artifact") or original_artifact_hash_check.get("artifact") or {}
    artifact_digest = artifact_metadata.get("digest")
    if artifact_digest and containers:
        expected_artifact_sha = str(artifact_digest).removeprefix("sha256:").lower()
        matches = [row for row in containers if row.get("sha256") == expected_artifact_sha]
        artifact_digest_check = {"status": "PASS" if matches else "FAIL", "expected_sha256": expected_artifact_sha, "matching_containers": [row["path"] for row in matches]}
    else:
        artifact_digest_check = {
            "status": "METADATA_MATCH_CONTAINER_NOT_DOWNLOADED" if artifact_listing_check.get("status") == "PASS" else "UNKNOWN",
            "reason": "artifact listing and original receipt agree; no ZIP container was included to recompute its digest" if artifact_listing_check.get("status") == "PASS" else "artifact digest metadata or downloaded container not present",
        }
    output = {
        "round": "R25",
        "analyzed_at_local": __import__("datetime").datetime.now().astimezone().isoformat(),
        "ci_run_id": (ci_run or {}).get("databaseId", (dispatch or {}).get("run", {}).get("databaseId")),
        "ci_run_status": (ci_run or {}).get("status", "UNKNOWN"),
        "ci_run_conclusion": (ci_run or {}).get("conclusion", "UNKNOWN"),
        "dispatch_status_history": (dispatch or {}).get("run", {}).get("status", "UNKNOWN"),
        "source_commit": (dispatch or {}).get("source_commit", "UNKNOWN"),
        "official_commit": plan.get("official_commit", "UNKNOWN"),
        "plan_source": plan_source,
        "plan_error": plan_error,
        "dispatch_error": dispatch_error,
        "ci_run_error": ci_run_error,
        "pinned_analysis_modules": pinned_hashes,
        "artifact_metadata": artifact_metadata,
        "artifact_listing_check": artifact_listing_check,
        "artifact_digest_check": artifact_digest_check,
        "artifact_containers": containers,
        "raw_files": sorted(inventory, key=lambda row: row["path"]),
        "runner_file_hash_manifest": artifact_hash_check,
        "original_artifact_hash_manifest": original_artifact_hash_check,
        "summary_errors": summary_error_list,
        "config_path": config_path,
        "config_load_error": config_error,
        "dispatch_and_gate": dispatch_summary,
        "verdict_receipts": verdict_receipts,
        "helper_axiom_audit": helper_axiom_audit,
        "metadata_self_check": metadata_self_check,
        "requests": {
            "expected_count": len(expected_requests),
            "observed_count": sum(row.get("status") == "PASS" for row in request_rows),
            "independently_verified_all_requested_present_and_valid": "PASS" if request_complete else "FAIL" if any(row.get("status") == "FAIL" for row in request_rows) else "UNKNOWN",
            "rows": request_rows,
        },
        "measurements": {
            "expected_request_results": len(expected_requests),
            "complete_result_count": sum(row.get("status") == "PASS" for row in measurements),
            "independently_verified_all_requested_complete": "PASS" if measurement_complete else "FAIL" if any(row.get("status") == "FAIL" for row in measurements) else "UNKNOWN",
            "rows": measurements,
        },
        "performance_status": "NOT_RUN" if measurements and all(row.get("status") == "NOT_RUN" for row in measurements) else "ANALYZED" if measurements and all(row.get("status") == "PASS" for row in measurements) else "PARTIAL_OR_UNKNOWN",
        "verified_request_and_measurement_cohort": verified_input_and_measurement_state,
        "exploratory_scores_vs_shipped_reference": exploratory_scores,
        "score_boundary": "Pinned scorer on the two seeded exploratory cohort and quick config only; not live champion, official score, or promotion evidence.",
        "status": "PENDING_CI_ARTIFACT" if summary_for_report is None else "ANALYZED",
        "no_ci_or_lean_started_by_analyzer": True,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(output, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    print(json.dumps({"status": output["status"], "run_id": output["ci_run_id"], "ci_run_status": output["ci_run_status"], "ci_run_conclusion": output["ci_run_conclusion"], "plan_source": plan_source, "artifact_files": len(inventory), "summary_present": summary_for_report is not None, "requests_complete": output["requests"]["observed_count"], "measurements_complete": output["measurements"]["complete_result_count"], "analysis": str(args.output)}, ensure_ascii=False))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
