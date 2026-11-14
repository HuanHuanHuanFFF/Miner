#!/usr/bin/env python3
"""Audit the saved B4 helper-only artifact and its printed axiom sets; no network/build."""
from __future__ import annotations

import hashlib
import json
import re
from pathlib import Path
from typing import Any

HERE = Path(__file__).resolve().parent
ROUND = HERE.parent
ROOT = ROUND.parents[3]
RUN = 40964374666
EVIDENCE = ROUND / "evidence" / str(RUN)
DISPATCH = ROUND / "evidence" / "dispatch-20261029T221452Z" / "dispatch.json"
DOWNLOAD = EVIDENCE / "download-5146e875eb624117a7e03ecb485b3f60"
ALLOWED = {"Classical.choice", "Quot.sound", "propext"}


def read(path: Path) -> Any:
    return json.loads(path.read_text(encoding="utf-8-sig"))


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def verify_manifest(root: Path, expected: dict[str, Any], ignored: set[str] | None = None) -> dict[str, Any]:
    missing = []
    mismatches = []
    for rel, meta in expected.items():
        path = root / rel
        if not path.is_file():
            missing.append(rel)
            continue
        data = path.read_bytes()
        if len(data) != meta.get("bytes") or hashlib.sha256(data).hexdigest() != meta.get("sha256"):
            mismatches.append(rel)
    actual = {x.relative_to(root).as_posix() for x in root.rglob("*") if x.is_file()}
    actual -= ignored or set()
    unexpected = sorted(actual - set(expected))
    return {
        "expected_count": len(expected),
        "matched_count": len(expected) - len(missing) - len(mismatches),
        "missing": missing,
        "mismatches": mismatches,
        "unexpected": unexpected,
        "pass": not missing and not mismatches and not unexpected,
    }


def parse_axioms(log_text: str) -> list[set[str]]:
    normalized = re.sub(r"\s+", " ", log_text)
    result = []
    for match in re.finditer(r"depends on axioms: \[([^\]]*)\]", normalized):
        values = {item.strip() for item in match.group(1).split(",") if item.strip()}
        result.append(values)
    return result


def main() -> int:
    dispatch = read(DISPATCH)
    ci = read(EVIDENCE / "ci-run.json")
    artifact = read(EVIDENCE / "artifacts.json")
    outer_record = read(EVIDENCE / "original-artifact-hashes.json")
    summary = read(DOWNLOAD / "summary.json")
    plan = read(DOWNLOAD / "plan.json")
    result = read(ROUND / "CI-RESULTS-BATCH4.json")

    dispatch_hashes = dispatch.get("frozen_files", {})
    dispatch_checks = {}
    current_checkout_checks = {}
    for rel, expected in dispatch_hashes.items():
        path = ROOT / rel
        current_matches = path.is_file() and sha(path) == expected
        current_checkout_checks[rel] = current_matches
        saved_matches = False
        if not current_matches and rel.endswith("/ci-plan.json"):
            saved_copy = ROUND / "ci-plan-batch4-helpers.json"
            saved_matches = saved_copy.is_file() and sha(saved_copy) == expected
        dispatch_checks[rel] = current_matches or saved_matches

    outer = verify_manifest(DOWNLOAD, outer_record.get("files", {}))
    inner = verify_manifest(DOWNLOAD, read(DOWNLOAD / "file-hashes.json"), ignored={"file-hashes.json"})

    summary_helpers = {x.get("name"): x for x in summary.get("helper_diagnostics", [])}
    result_helpers = {x.get("name"): x for x in result.get("helper_results", [])}
    helper_rows = []
    for name, receipt in result_helpers.items():
        summary_row = summary_helpers.get(name, {})
        log_path = DOWNLOAD / f"{name}-helper.log"
        log = log_path.read_text(encoding="utf-8", errors="replace") if log_path.is_file() else ""
        parsed = parse_axioms(log)
        recorded = [{str(x) for x in row} for row in receipt.get("printed_axiom_sets", [])]
        parsed_equals_recorded = len(parsed) == len(recorded) and all(a == b for a, b in zip(parsed, recorded))
        extras = sorted({axiom for group in parsed for axiom in group - ALLOWED})
        helper_rows.append({
            "name": name,
            "source_sha256": receipt.get("source_sha256"),
            "exit_code": summary_row.get("exit_code"),
            "source_hash_matches_plan": summary_row.get("source_sha256") == next(
                (h.get("sha256") for h in plan.get("helpers", []) if h.get("name") == name), None
            ),
            "raw_log_sha256": sha(log_path) if log_path.is_file() else None,
            "printed_axiom_sets_from_raw": [sorted(x) for x in parsed],
            "printed_axiom_sets_match_result_record": parsed_equals_recorded,
            "extra_axioms": extras,
            "helper_scope_only": summary_row.get("scope"),
            "accepted_standalone_diagnostic": summary_row.get("exit_code") == 0 and parsed_equals_recorded and not extras,
        })

    source_files = sorted(
        x.relative_to(DOWNLOAD).as_posix()
        for x in DOWNLOAD.rglob("*")
        if x.is_file() and x.suffix.lower() in {".lean", ".c", ".cc", ".cpp", ".h", ".hpp", ".s", ".asm", ".ll", ".bc", ".wasm"}
    )
    output = {
        "run": RUN,
        "workflow_conclusion": ci.get("conclusion"),
        "source_commit": ci.get("headSha"),
        "official_commit": summary.get("official_commit"),
        "plan_sha256": sha(DOWNLOAD / "plan.json"),
        "runner_complete": summary.get("complete"),
        "runner_scope": summary.get("scope"),
        "candidate_measurement": "NONE_BY_PLAN" if not plan.get("candidates") else "PRESENT",
        "full_gates": summary.get("full_gates", []),
        "elapsed_seconds": summary.get("elapsed_seconds"),
        "benchmark_identity": result.get("benchmark_identity"),
        "proof_identity": result.get("proof_identity"),
        "dispatch_hash_checks": dispatch_checks,
        "current_checkout_hash_checks": current_checkout_checks,
        "dispatch_source_commit_matches_run": dispatch.get("source_commit") == ci.get("headSha") == dispatch.get("run", {}).get("headSha"),
        "artifact_plan_matches_frozen_dispatch": sha(DOWNLOAD / "plan.json") == dispatch_hashes.get("competitions/torchlean/candidates/r27-5h-20261029T194443Z/ci-plan.json"),
        "outer_artifact_manifest": outer,
        "inner_file_hash_manifest": inner,
        "helper_results": helper_rows,
        "source_shaped_artifact_files": source_files,
        "conclusion": "HELPER_DIAGNOSTICS_ONLY; successful workflow does not mean every lemma passed or any candidate is Correct",
    }
    OUT = HERE / "audit-helper-run-40964374666.json"
    OUT.write_text(json.dumps(output, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    print(json.dumps({
        "run": RUN,
        "workflow": ci.get("conclusion"),
        "outer_manifest_pass": outer["pass"],
        "inner_manifest_pass": inner["pass"],
        "helpers": [{"name": x["name"], "exit_code": x["exit_code"], "accepted": x["accepted_standalone_diagnostic"], "extra_axioms": x["extra_axioms"]} for x in helper_rows],
        "candidate_measurement": output["candidate_measurement"],
        "source_artifact_count": len(source_files),
    }, ensure_ascii=False))
    return 0 if outer["pass"] and inner["pass"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
