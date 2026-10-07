"""Generate one explicit copyfast inlining diagnostic; no compiler or CI action.

Only writes candidates/r6-h16-cpu-copyfast-outline. Adds inline(never) to the
frozen copyfast h_copy32 declaration, preserves every other Rust/proof byte,
and carries NOT_ADAPTED status. --check compares generated artifacts read-only.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PARENT = ROOT / "candidates/r6-h16-cpu-copyfast"
DEST = ROOT / "candidates/r6-h16-cpu-copyfast-outline"
LOCKS = {
    "parse.rs": "d414c981b22a23cae40561173e6812e4846f3fb8ba500ad6dd5d4ef5582efb19",
    "Parse.lean": "d55744de52bb0469768f0bbfd73ffecbabf9899b63e0167469fd7bb79c6293c7",
}
PARENT_METADATA_LOCKS = {
    "manifest.json": "c544a73623dba8df6b09a3736be4fd6f3a548f46562f77a8482ce8d082a57cbb",
    "copy-audit.json": "fef0cda0f7301323670054964d87f4abb2f224746da20bf587475adf7277465c",
}
TARGET = "pub fn h_copy32(src: &[u32], soff: usize, dst: &mut [u32], doff: usize, m: usize) {"
ATTRIBUTE = "#[inline(never)]\n"


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def generate() -> tuple[dict[str, bytes], dict]:
    parent = {file: (PARENT / file).read_bytes() for file in LOCKS}
    for file, expected in LOCKS.items():
        assert sha(parent[file]) == expected, (file, "frozen copyfast drift")
    for file, expected in PARENT_METADATA_LOCKS.items():
        assert sha((PARENT / file).read_bytes()) == expected, (file, "frozen parent metadata drift")
    source = parent["parse.rs"].decode()
    assert "\r\n" not in source and source.count(TARGET) == 1
    assert not re.search(r"#\[inline[^\n]*\]\s*\n\s*pub fn h_copy32\b", source)
    modified = source.replace(TARGET, ATTRIBUTE + TARGET, 1)
    assert modified.count(ATTRIBUTE + TARGET) == 1
    assert modified.replace(ATTRIBUTE + TARGET, TARGET, 1) == source
    files = {"parse.rs": modified.encode(), "Parse.lean": parent["Parse.lean"]}
    assert all(len(data) < 524288 for data in files.values())
    audit = {
        "parent": {"path": PARENT.relative_to(ROOT).as_posix(), "hashes": LOCKS, "metadata_hashes": PARENT_METADATA_LOCKS},
        "function": "h_copy32",
        "parent_function_line": source[:source.index(TARGET)].count("\n") + 1,
        "old_attribute": None,
        "new_attribute": "inline(never)",
        "added_attribute_sha256": sha(ATTRIBUTE.encode()),
        "whole_source_reverse_equal": True,
        "all_other_source_and_function_body_bytes": "VERIFIED exact copyfast parent; fast/fallback loops, guards, operations, call sites, routing, model, budget and existing attributes unchanged",
        "proof_equal": True,
        "proof_status": "NOT_ADAPTED",
        "diagnostic_evidence": {
            "copy_screen_run": "37598783885",
            "copy_screen_commit": "a25dee2e56ba8d7f6d50ce9d132cae3e1af59d10",
            "parent_screen_total_time_change_pct": [0.5057813440609848, 0.8209222796345728],
            "h_block_bits_function_bytes": {"H16_baseline": 7380, "copyfast": 14117},
            "local_vector_copy_observed": "Two XMM loads/two stores per eight u32 in parse at 0x1c640-0x1c65f and 0x1e170-0x1e18d",
            "causality_status": "UNKNOWN whether duplication/code layout caused the screen regression; this single annotation is an explicit mechanism diagnostic, not proof of that cause",
        },
        "expected_machine_effect": "INFERRED: compiler outlines one shared h_copy32 body, shrinks caller duplication, adds real call overhead and may lose constant specialization. Actual symbol sizes/call sites/vector loops must be inspected",
        "extraction_expectation": "INFERRED unchanged copyfast semantic body; the attribute is a compiler hint. New official extraction must still establish the actual definitions; parent copy proof is NOT_ADAPTED",
        "not_established": ["Rust build", "outlined symbol", "retained vectorization", "token/output identity", "paired total benefit", "adapted proof", "complete gate"],
    }
    manifest = {
        "candidate": DEST.name,
        "parent": audit["parent"],
        "hashes": {file: sha(data) for file, data in files.items()},
        "bytes": {file: len(data) for file, data in files.items()},
        "mechanism": "Single inline(never) hint on frozen copyfast h_copy32; test whether removing caller body duplication changes the vector-copy/time tradeoff",
        "attribute_audit": "attribute-audit.json",
        "expected_equivalent": True,
        "equivalence_reference": PARENT.name,
        "expected_equivalence_scope": "INFERRED unchanged complete Rust bodies/control flow relative to copyfast; no new formal or runtime identity claim",
        "proof_status": "NOT_ADAPTED",
        "proof_scope": "Exact inherited copyfast Lean is retained for provenance; no new h_copy32 loop specs, obligation acceptance or gate are claimed",
        "measurement_comparators": ["r5-h16-small-proofopt", "r6-h16-cpu-copyfast", DEST.name],
        "attribution": "Copyfast CPU diagnostic on frozen H16 combination of external public submissions 299 and 402; original provenance retained under references/round4-public-299 and references/round4-public-402",
        "verification": "VERIFIED generation, parent locks, single attribute reverse equality and inherited proof equality only. Realized outlining/vectorization, paired time, adapted Lean/axioms and gate UNKNOWN",
        "scope": "One newly authorized correction based on copyfast machine code; no further algorithm or parameter sweep, no source edits to prior candidates, no official/gate/pin/encoder changes, no admission/reward inference",
    }
    files["attribute-audit.json"] = (json.dumps(audit, indent=2) + "\n").encode()
    files["manifest.json"] = (json.dumps(manifest, indent=2) + "\n").encode()
    return files, manifest


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true", help="compare only; no writes")
    args = parser.parse_args()
    files, manifest = generate()
    if args.check:
        for file, data in files.items():
            assert (DEST / file).read_bytes() == data, (file, "candidate drift")
    else:
        DEST.mkdir(parents=True, exist_ok=True)
        for file, data in files.items():
            path = DEST / file
            if not path.exists() or path.read_bytes() != data:
                path.write_bytes(data)
    print(json.dumps({"candidate": DEST.name, "hashes": manifest["hashes"], "bytes": manifest["bytes"], "proof_status": "NOT_ADAPTED", "check_only": args.check}))


if __name__ == "__main__":
    main()
