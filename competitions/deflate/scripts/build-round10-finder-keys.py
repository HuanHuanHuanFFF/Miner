"""Build five/six-byte D chain keys with no supplemental maintenance table.

Only KB7 changes. The symbolic parent proof is retained as a compatible draft,
not evidence that either new exact source has passed a complete gate.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r9-block-scalar"
PINNED = {
    "parse.rs": "faf1d7281678d12c3243002121feecdd0ea139633dea197dbc77d86fb6319257",
    "Parse.lean": "aa21da6f74e81314297df07beecbfc98b15c848354437674bdb9347d8632f0af",
}
OLD = b"pub const KB7: u32 = 7;"
PROOF_BOUND = b"theorem dp_KB7_bound : slot.KB7.val \xe2\x89\xa4 8 := by simp [slot.KB7]"


def sha(raw: bytes) -> str:
    return hashlib.sha256(raw).hexdigest()


def generate(key_bytes: int) -> dict[str, bytes]:
    if key_bytes not in (5, 6):
        raise ValueError("This experiment has only the declared five/six-byte keys")
    raw = {file: (BASE / file).read_bytes() for file in PINNED}
    if {file: sha(value) for file, value in raw.items()} != PINNED:
        raise ValueError("Pinned scalar parent changed")
    source, proof = raw["parse.rs"], raw["Parse.lean"]
    if source.count(OLD) != 1 or proof.count(PROOF_BOUND) != 1:
        raise ValueError("Exact source/constant lemma anchors changed")
    # All occurrences were reviewed: only the symbolic bound and the two
    # arithmetic uses in d_parse_spec occur in the parent proof.
    if proof.count(b"slot.KB7") != 4:
        raise ValueError("Unexpected additional proof dependency on KB7")
    replacement = f"pub const KB7: u32 = {key_bytes};".encode("ascii")
    rust = source.replace(OLD, replacement, 1)
    if rust.replace(replacement, OLD, 1) != source:
        raise ValueError("Reverse one-constant audit failed")
    if len(rust) != len(source) or sum(a != b for a, b in zip(rust, source)) != 1:
        raise ValueError("Expected precisely one changed source byte")
    if not (5 <= key_bytes <= 8 and 0 <= 64 - 8 * key_bytes < 64):
        raise ValueError("Existing KB7/sh7 totality preconditions are not met")
    name = f"r10-finder-key{key_bytes}"
    files = {"parse.rs": rust, "Parse.lean": proof}
    parent = json.loads((BASE / "manifest.json").read_text(encoding="utf-8"))
    manifest = {
        "candidate": name, "parent": "candidates/r9-block-scalar",
        "base_submission_id": "361", "parent_hashes": PINNED,
        "hashes": {file: sha(value) for file, value in files.items()},
        "bytes": {file: len(value) for file, value in files.items()},
        "attribution": parent["attribution"],
        "mechanism": f"Replace engine D's seven-byte long-chain hash key with {key_bytes} bytes, retaining original chain table, insertion/search code and all depth budgets",
        "key_bytes": key_bytes, "old_key_bytes": 7,
        "extra_state_bytes": 0, "extra_insertion_operations": 0,
        "extra_search_operations": 0,
        "motivation": "R10 hash5 supplement added 97744 public longer records, 92650 of them after an existing 4..7-byte best, but its +4.5% time cost outweighed -0.005377pp size. Reuse the existing long chain to explore the shorter key without a side-cache update.",
        "old_trial_review": "No other candidate source with global pub const KB7=5 or6 was found in the current repository; relevant historical manifests/generator scripts/reports did not record this D-global-key trial. DP_KNOBS per-row key lengths are a distinct interface already used by the DP engine.",
        "coverage_limit": "This replaces, rather than supplements, long-chain grouping: depth-limited seven-byte-key matches can be displaced by nearer shorter-key occurrences and collisions. Original table/depth/search branch schedule code is unchanged, but match results can change future continuation/skipping/cost statistics.",
        "audit": "Reverse exactly one source-byte constant edit restores verified scalar Rust. No new table, helper, loop, condition, route or budget; complete parent Lean bytes retained.",
        "proof_review": {
            "constant_lemma": "dp_KB7_bound: slot.KB7.val<=8, proved by simp [slot.KB7]",
            "uses": "Only d_parse_spec's U32 8*KB7 and 64-8*KB7 arithmetic; values40/48 satisfy the same symbolic safety bound. No exact KB7=7 statement or new state/interface.",
            "required": "New exact source extraction, native Lean compilation, original obligation, allowed axioms and full public round trip",
        },
        "proof_status": "COMPATIBLE_SYMBOLIC_PARENT_DRAFT / NOT_RUN: constant lemma remains true at five/six bytes; exact new Rust has not passed a fresh full gate",
        "correctness_status": "UNKNOWN pending fresh native build/finite decode and complete gate",
        "performance_status": "UNKNOWN until fixed-corpus paired parser+official encoder measurements; side-cache opportunity counts do not establish this replacement's encoded gain",
        "falsification": "Stop a key if public size does not improve or loss of depth-limited original long-key coverage outweighs short-match gains; no gate expenditure for a dominated time/size tradeoff",
    }
    if not all(0 < len(value) <= 524288 for value in files.values()):
        raise ValueError("Official per-file size boundary exceeded")
    files["manifest.json"] = (json.dumps(manifest, indent=2, ensure_ascii=False) + "\n").encode("utf-8")
    return files


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    for key_bytes in (5, 6):
        files = generate(key_bytes)
        destination = ROOT / "candidates" / f"r10-finder-key{key_bytes}"
        if args.check:
            if not all((destination / file).read_bytes() == value for file, value in files.items()):
                raise ValueError("Existing key candidate differs")
        else:
            destination.mkdir(exist_ok=True)
            for file, value in files.items():
                target = destination / file
                if target.exists() and target.read_bytes() != value:
                    raise ValueError(f"Preserve differing existing candidate: {target}")
                target.write_bytes(value)
        manifest = json.loads(files["manifest.json"])
        print(json.dumps({"candidate": destination.name, "hashes": manifest["hashes"],
            "changed_source_bytes": 1, "extra_state_bytes": 0, "proof_status": "COMPATIBLE_PARENT_DRAFT_NOT_GATE_TESTED"}))


if __name__ == "__main__":
    main()
