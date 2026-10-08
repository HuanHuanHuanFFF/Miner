"""One dependency-order experiment: read D's existing next link before probe.

No added read, changed search budget or layout. Preserve verified nonempty-record
parent; the small loop-proof bind reorder remains uncompiled until fresh gate.
"""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r10-record-nonempty"
NAME = "r10-finder-linkearly"
PINNED = {
    "parse.rs": "7f1c661fd1ce29d12c69671f034ff5a713e284ed1fcba66ba404ff25479b55b7",
    "Parse.lean": "86cfc36adb009970bccbb5a9c543c5f559148d729e8c0f041934aab44e95592d",
}
READ = "            let nx = prev[c % WN] as usize;\n"
PROBE = "            let l = probe(s, c, i, b8, cap, best);\n"
PROOF_READ = """              refine d3_rem (b := 32768) dp_WN_val (by decide) ?_; intro i2 hi2
              refine d3_idx (c := 32768) rfl hi2 ?_; intro i3
"""
PROOF_PROBE = "              refine d3_bind (probe_spec _ _ _ _ _ _ h1 hcap hic hs8) ?_; intro l hl\n"


def sha(raw: bytes) -> str:
    return hashlib.sha256(raw).hexdigest()


def region(text: str, start_marker: str, end_marker: str) -> tuple[int, int, str]:
    if text.count(start_marker) != 1:
        raise ValueError("Start region marker not unique")
    start = text.index(start_marker); end = text.index(end_marker, start)
    return start, end, text[start:end]


def reorder(text: str, read: str, probe: str) -> str:
    if text.count(read) != 1 or text.count(probe) != 1 or text.index(read) < text.index(probe):
        raise ValueError("Expected one original read following probe")
    changed = text.replace(read, "", 1).replace(probe, read + probe, 1)
    restored = changed.replace(read + probe, probe, 1)
    # Put the read back at its original offset in the original source region.
    original_position = text.index(read)
    restored = restored[:original_position] + read + restored[original_position:]
    if restored != text:
        raise ValueError("Exact read-order reversal failed")
    return changed


def generate() -> dict[str, bytes]:
    raw = {file: (BASE / file).read_bytes() for file in PINNED}
    if {file: sha(value) for file, value in raw.items()} != PINNED:
        raise ValueError("Frozen accepted record parent changed")
    verified = json.loads((BASE / "VERIFICATION.json").read_text(encoding="utf-8"))
    if verified["files"] != PINNED or verified["official_accepted"] is not True:
        raise ValueError("Parent full-gate hash binding differs")
    source = raw["parse.rs"].decode("utf-8")
    proof = raw["Parse.lean"].decode("utf-8")
    a, b, old_rust = region(source, "/// `walk` with a stop once a match of at least `nice` bytes is known.", "/// `back_best` with a limit")
    new_rust = reorder(old_rust, READ, PROBE)
    rust = (source[:a] + new_rust + source[b:]).encode("utf-8")
    c, d, old_lean = region(proof, "@[local step]\ntheorem d_walk_loop_spec", "@[local step]\ntheorem d_walk_spec")
    new_lean = reorder(old_lean, PROOF_READ, PROOF_PROBE)
    lean = (proof[:c] + new_lean + proof[d:]).encode("utf-8")
    if len(rust) != len(raw["parse.rs"]) or len(lean) != len(raw["Parse.lean"]):
        raise ValueError("Moving existing source/proof lines changed bytes length")
    files = {"parse.rs": rust, "Parse.lean": lean}
    parent = json.loads((BASE / "manifest.json").read_text(encoding="utf-8"))
    old_assembly = ROOT / "evidence/round7/37636990183/middle-cpu/gate/cpu/r7-mid361-walk-outline-assembly.txt"
    manifest = {
        "candidate": NAME, "parent": "candidates/r10-record-nonempty", "base_submission_id": "361",
        "parent_hashes": PINNED, "hashes": {file: sha(value) for file, value in files.items()},
        "bytes": {file: len(value) for file, value in files.items()}, "attribution": parent["attribution"],
        "mechanism": "Move the existing immutable D-chain next-link load before the current probe, attempting memory-latency overlap without adding or removing any read/probe/candidate",
        "source_audit": "Only one existing read line moves within d_walk; reverse exactly that move restores accepted record-nonempty Rust. No table, key, depth, cap/nice, insertion, records, costs, routing or output change.",
        "proof_audit": "Only d_walk_loop_spec's existing modulo/index bind pair moves before probe_spec; public helper signature, five-state loop, depth measure, invariant and all final proof statements remain unchanged. Reverse bind move restores accepted parent Lean.",
        "equivalence_status": "INFERRED same-output for all defined executions: prev is immutable and its modulo-bounded read is independent of probe/candidate writes. Fresh444 native tokens/decode and public tokens/output equality still required.",
        "expected_equivalent_to": "r10-record-nonempty",
        "proof_status": "UNCOMPILED_REORDERED_LOOP_DRAFT: no new lemma/axiom/sorry; actual extraction binding order and original obligation/axiom/public round trip NOT_RUN for this source",
        "performance_status": "UNKNOWN: LLVM may already schedule the read early, or the longer live range may add spills and cost. Require same-runner paired official total compression; historical late read does not prove current code opportunity.",
        "historical_machine_evidence": {"path": str(old_assembly.relative_to(ROOT)).replace("\\", "/"),
            "sha256": sha(old_assembly.read_bytes()), "source": "r7 walk-outline (older ordinary walk, not current inlined D)",
            "first_probe_word_load_address": "0x1f670", "next_link_load_address": "0x1f8e1",
            "boundary": "VERIFIED late-load example only; current accepted record D release code needs same-runner comparison"},
        "cost_scope": "Same number of chain reads and byte probes; only dependency scheduling/lifetime changes. No assumed6% improvement or d_walk phase fraction.",
        "stop": "Stop if compiler normalizes the intended dependency order away, native output differs, or paired total time lacks a material positive signal. Register/address-only differences do not establish successful load scheduling; no ordering micro-variant sweep.",
    }
    audit = {"status": "VERIFIED_LOCAL_REVERSIBLE_SOURCE_PROOF_REORDER_ONLY", "parent_hashes": PINNED,
        "candidate_hashes": manifest["hashes"], "source_region": {"function": "d_walk", "old_sha256": sha(old_rust.encode()), "new_sha256": sha(new_rust.encode()), "moved_line": READ.rstrip(),
            "old_relative_offset": old_rust.index(READ), "new_relative_offset": new_rust.index(READ), "read_count_before": 1, "read_count_after": 1},
        "proof_region": {"theorem": "d_walk_loop_spec", "old_sha256": sha(old_lean.encode()), "new_sha256": sha(new_lean.encode()), "moved_bind_pair": PROOF_READ.rstrip(),
            "loop_state": ["cands", "nc", "best", "c", "k"], "signature_and_invariant_changed": False},
        "unchanged": ["Complete source outside d_walk", "Complete proof outside d_walk_loop_spec", "Byte lengths", "Original obligation and final correctness theorem", "Parent accepted files"],
        "not_verified": ["Native Rust equality", "Actual extraction", "Lean compilation/full gate", "Current release instruction schedule", "Performance"]}
    if not all(0 < len(value) <= 524288 for value in files.values()):
        raise ValueError("Per-file size boundary exceeded")
    files["manifest.json"] = (json.dumps(manifest, indent=2, ensure_ascii=False) + "\n").encode("utf-8")
    files["source-proof-audit.json"] = (json.dumps(audit, indent=2, ensure_ascii=False) + "\n").encode("utf-8")
    return files


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true"); args = parser.parse_args()
    files = generate(); target = ROOT / "candidates" / NAME
    if args.check:
        if not all((target / file).read_bytes() == value for file, value in files.items()):
            raise ValueError("Rebuilt linkearly candidate differs")
    else:
        target.mkdir(exist_ok=True)
        for file, value in files.items():
            path = target / file
            if path.exists() and path.read_bytes() != value:
                raise ValueError(f"Preserve differing candidate {path}")
            path.write_bytes(value)
    print(json.dumps({"candidate": NAME, "hashes": json.loads(files["manifest.json"])["hashes"],
        "expected_equivalent_to": "r10-record-nonempty", "proof_status": "UNCOMPILED_REORDERED_LOOP_DRAFT"}))


if __name__ == "__main__":
    main()
