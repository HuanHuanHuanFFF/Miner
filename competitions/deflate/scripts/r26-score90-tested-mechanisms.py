"""Map six unique R26 Rust hashes to their first actual original-protocol run."""
from __future__ import annotations

import hashlib
import json
import re
from datetime import datetime, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
EVIDENCE = ROOT / "evidence/round26"
OUTPUT = ROOT / "evidence/round26/extension90m/score-audit/tested-mechanisms.json"

MECHANISMS = [
    {"id": "C2", "label": "fold-tail", "generation": "older Rust; this window adds confirmation/retest",
     "canonical_candidate": "candidates/r26-c-658-fold-tail", "expected_first_run": "38266836712"},
    {"id": "C3", "label": "deferred-extension", "generation": "older Rust; this window adds confirmation/retest",
     "canonical_candidate": "candidates/r26-c-658-deferred-extension", "expected_first_run": "38266836712"},
    {"id": "D1", "label": "selective-depth", "generation": "new Rust in this window",
     "canonical_candidate": "candidates/r26-d-658-selective-depth", "expected_first_run": "38267276245"},
    {"id": "D2", "label": "once-budget", "generation": "new Rust in this window",
     "canonical_candidate": "candidates/r26-d-658-once-budget", "expected_first_run": "38269236685"},
    {"id": "E1", "label": "short-same", "generation": "new Rust in this window",
     "canonical_candidate": "candidates/r26-e-658-short-same-proof2", "expected_first_run": "38268487485"},
    {"id": "E2", "label": "short-tail controlled combination", "generation": "new Rust in this window",
     "canonical_candidate": "candidates/r26-e-658-short-tail-proof1", "expected_first_run": "38271606627"},
]


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def read_json(path: Path):
    return json.loads(path.read_bytes())


def inspect_stream(path: Path) -> dict | None:
    """Return qualifying method headers; full protocol validation follows for first hits."""
    try:
        with path.open("r", encoding="utf-8") as handle:
            meta = json.loads(handle.readline())
    except (OSError, json.JSONDecodeError):
        return None
    if (meta.get("kind") != "meta" or meta.get("corpus") != "corpus-stage1"
            or meta.get("warmup_rounds") != 1 or meta.get("measured_rounds") != 11
            or not meta.get("benchmark_provenance")):
        return None
    return meta


def verify_original_protocol(path: Path, method: str) -> dict:
    objects = [json.loads(line) for line in path.read_text(encoding="utf-8").splitlines() if line.strip()]
    meta, rows = objects[0], [obj for obj in objects[1:] if obj.get("kind") == "file"]
    assert meta["kind"] == "meta" and meta["corpus"] == "corpus-stage1"
    assert meta["warmup_rounds"] == 1 and meta["measured_rounds"] == 11
    assert len(rows) == 28
    assert method in meta["methods"] and "incumbent" in meta["methods"]
    assert not meta["methods"][method].get("external", True)
    x_values, y_values = [], []
    for row in rows:
        cand = row["methods"][method]
        inc = row["methods"]["incumbent"]
        cand_times = [float(rep["total_s"]) for rep in cand["reps"] if rep["phase"] == "measured"]
        inc_times = [float(rep["total_s"]) for rep in inc["reps"] if rep["phase"] == "measured"]
        assert len(cand_times) == len(inc_times) == 11
        x_values.append(sorted(cand_times)[5] / sorted(inc_times)[5])
        y_values.append(100 * float(cand["output_bytes"]) / float(row["raw_bytes"]))
    match = re.search(r"evidence[\\/]round26[\\/](\d+)[\\/]([^\\/]+)[\\/]gate[\\/]", str(path))
    assert match, path
    run_id, batch = match.group(1), match.group(2)
    return {
        "run_id": run_id, "batch": batch, "block": 2 if "round2-" in path.name else 1,
        "method_name": method, "raw_jsonl_path": path.relative_to(ROOT).as_posix(),
        "raw_jsonl_sha256": sha256(path), "started_at_unix": meta["started_at_unix"],
        "started_at_utc": datetime.fromtimestamp(float(meta["started_at_unix"]), timezone.utc).isoformat(),
        "cpu_model": meta["cpu_model"], "rustc_version": meta["rustc_version"],
        "rust_source_sha256": meta["methods"][method]["source_sha256"],
        "executable_sha256": meta["methods"][method]["lib_sha256"],
        "incumbent_source_sha256": meta["methods"]["incumbent"]["source_sha256"],
        "incumbent_executable_sha256": meta["methods"]["incumbent"]["lib_sha256"],
        "file_count": len(rows), "warmup_rounds": 1, "measured_rounds_per_file": 11,
        "raw_x_equal_file_mean": sum(x_values) / len(x_values),
        "raw_y_mean_file_compression_pct": sum(y_values) / len(y_values),
        "protocol_evidence": "stage1 paired incumbent; 28 files; one warmup and eleven measured total_s repetitions; parser plus encoder total time",
    }


def main() -> None:
    # Use the actual parse.rs bytes as the identity key. Aliased candidate
    # directories with the same Rust hash collapse into one mechanism record.
    candidates_by_hash: dict[str, list[str]] = {}
    for path in sorted((ROOT / "candidates").glob("*/parse.rs")):
        candidates_by_hash.setdefault(sha256(path), []).append(path.parent.relative_to(ROOT).as_posix())

    records = []
    for spec in MECHANISMS:
        candidate_dir = ROOT / spec["canonical_candidate"]
        rust_file = candidate_dir / "parse.rs"
        manifest_file = candidate_dir / "manifest.json"
        manifest = read_json(manifest_file)
        rust_sha = sha256(rust_file)
        assert manifest.get("hashes", {}).get("parse.rs") == rust_sha
        alias_paths = candidates_by_hash.get(rust_sha, [])
        assert spec["canonical_candidate"] in alias_paths

        matches = []
        for path in EVIDENCE.rglob("round*.jsonl"):
            meta = inspect_stream(path)
            if not meta:
                continue
            for method, method_info in meta.get("methods", {}).items():
                if method != "incumbent" and method_info.get("source_sha256") == rust_sha:
                    matches.append((float(meta.get("started_at_unix", 0)), path, method))
        assert matches, f"No original-protocol source-hash match for {spec['id']} {rust_sha}"
        _, first_path, first_method = min(matches, key=lambda row: row[0])
        first_run = verify_original_protocol(first_path, first_method)
        assert first_run["rust_source_sha256"] == rust_sha
        assert first_run["run_id"] == spec["expected_first_run"], (spec["id"], first_run["run_id"])
        records.append({
            **spec,
            "rust_sha256": rust_sha,
            "canonical_lean_sha256": manifest.get("hashes", {}).get("Parse.lean"),
            "canonical_proof_status": manifest.get("proof_status"),
            "unique_rust_version_count": 1,
            "alias_candidate_directories_same_rust_hash": alias_paths,
            "first_actual_original_protocol_run": first_run,
            "all_matching_original_protocol_streams_count": len(matches),
            "identity_basis": "SHA-256 of exact parse.rs bytes; aliases with this hash are grouped once.",
        })

    assert len(records) == 6 and len({row["rust_sha256"] for row in records}) == 6

    # Preserve the uncompiled C4 proof draft as excluded context. Its Rust is
    # already the C4 Rust hash; the draft itself creates no seventh mechanism.
    c4_manifest_path = ROOT / "candidates/r26-c-658-greedy-once-proof2/manifest.json"
    c4_manifest = read_json(c4_manifest_path)
    c4_draft = ROOT / "evidence/round26/extension1h/audit/C4-Parse-proof2-UNCOMPILED.lean"
    c4_rust_sha = sha256(ROOT / "candidates/r26-c-658-greedy-once-proof2/parse.rs")
    assert c4_manifest["hashes"]["parse.rs"] == c4_rust_sha
    c4_matches = []
    for path in EVIDENCE.rglob("round*.jsonl"):
        meta = inspect_stream(path)
        if not meta:
            continue
        for method, info in meta.get("methods", {}).items():
            if method != "incumbent" and info.get("source_sha256") == c4_rust_sha:
                c4_matches.append((float(meta.get("started_at_unix", 0)), path, method))
    c4_first = verify_original_protocol(*min(c4_matches, key=lambda row: row[0])[1:]) if c4_matches else None
    c4_excluded = {
        "candidate_path": "candidates/r26-c-658-greedy-once-proof2",
        "proof_draft_path": c4_draft.relative_to(ROOT).as_posix(),
        "rust_sha256": c4_rust_sha,
        "lean_sha256": sha256(c4_draft),
        "proof_status": c4_manifest.get("proof_status"),
        "first_original_protocol_run_for_same_rust_if_any": c4_first,
        "excluded_from_six_mechanism_count": True,
        "reason": "This is an uncompiled proof-only draft on an already observed C4 Rust hash, not a distinct tested Rust mechanism or an exact accepted proof pair.",
    }

    result = {
        "status": "VERIFIED_SIX_UNIQUE_RUST_HASHES_AND_FIRST_ORIGINAL_PROTOCOL_RUNS",
        "checked_utc": datetime.now(timezone.utc).isoformat(),
        "scan_scope": "evidence/round26/**/round*.jsonl; first qualifying stage1 paired original-protocol stream per exact Rust source hash",
        "qualifying_stream_header_count_scanned": sum(
            1 for path in EVIDENCE.rglob("round*.jsonl") if inspect_stream(path)
        ),
        "unique_tested_rust_version_count": len(records),
        "tested_mechanisms": records,
        "excluded_unpromoted_proof_drafts": [c4_excluded],
        "limits": [
            "A run mapping proves an original-protocol paired timing stream exists for that exact Rust hash; it does not prove a full gate, independent confirmation, admission, or reward.",
            "C2/C3 Rust hashes are legacy mechanisms remeasured/confirmed later; D1/D2/E1/E2 are new Rust hashes from this window.",
            "Directories sharing one parse.rs SHA-256 are aliases of one Rust version and are listed once.",
            "C4 proof2 is excluded as a proof-only draft; its associated Rust hash was measured earlier, but that does not accept this proof draft.",
        ],
    }
    OUTPUT.parent.mkdir(parents=True, exist_ok=True)
    OUTPUT.write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"status": result["status"],
                      "unique_rust_versions": len(records),
                      "first_runs": {row["id"]: row["first_actual_original_protocol_run"]["run_id"] for row in records},
                      "E2_aliases": next(row["alias_candidate_directories_same_rust_hash"] for row in records if row["id"] == "E2"),
                      "excluded_C4_rust_run": c4_first["run_id"] if c4_first else None,
                      "output": OUTPUT.relative_to(ROOT).as_posix()}, ensure_ascii=False))


if __name__ == "__main__":
    main()
