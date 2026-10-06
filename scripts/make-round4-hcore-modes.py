"""Uniform mode experiments on the frozen H8/depth32 core.

Only writes candidates/r4-parse-hmode-*/. Updates the Rust entry and the final
Lean theorem argument together; all engine bodies and emitter proofs remain
unchanged. No local toolchain execution, CI dispatch or submission.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r4-parse-h8d32-core"
BASE_SOURCE = "916f3a0b5f64b17919c7e4871f878ef2827530a9e3bf577020d8865e61b26953"
BASE_PROOF = "13f23fc46a6d18283aeb339f949cca102761133d6e1ff9b3a1007cd8b7926a46"
OLD_ENTRY = """pub fn parse(input: &[u8], out: &mut [u32]) -> usize {
    h_parse_mode(input, out, 0)
}"""
OLD_PROOF_CALL = "  exact EH.parse_mode_spec input out 0#usize hlen"


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def replace_once(text: str, old: str, new: str) -> str:
    assert text.count(old) == 1, (old, text.count(old))
    return text.replace(old, new, 1)


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--only", action="append", default=[], help="Generate/check only named candidates; repeatable")
    args = ap.parse_args()
    source_bytes, proof_bytes = (BASE / "parse.rs").read_bytes(), (BASE / "Parse.lean").read_bytes()
    assert sha(source_bytes) == BASE_SOURCE and sha(proof_bytes) == BASE_PROOF, "H-core base drift"
    source, proof = source_bytes.decode(), proof_bytes.decode()
    recipes = [
        ("r4-parse-hmode-1-i8", 1, 8,
         "Uniform mode 1 with the original eight-pass cap: halve the existing per-content stopping constant, potentially continuing cost fitting longer. No restart and no new initial-model family."),
        ("r4-parse-hmode-2-i4", 2, 4,
         "Uniform mode 2 with a four-pass normal cap: halve the stopping constant and allow one content-qualified restart, consisting of deterministic cost jitter and exactly three additional DP/refit steps over the existing cache. Reduce the normal cap to budget for restart work."),
        ("r4-parse-hmode-2-i8", 2, 8,
         "Uniform mode 2 with the eight-pass normal cap and at most one content-qualified three-step restart. Keep the H8/depth32 cache, query margin and length windows unchanged, testing restart after the stronger normal fit."),
        ("r4-parse-hmode-3-i8", 3, 8,
         "Uniform mode 3 with the eight-pass normal cap and at most two content-qualified restarts (three DP/refit steps each, distinct deterministic seeds). Search depth, query margin and length windows remain H8/depth32; no additional tree search."),
    ]
    assert set(args.only) <= {r[0] for r in recipes}, "unknown --only candidate"
    for name, mode, iterations, mechanism in recipes:
        if args.only and name not in args.only:
            continue
        new_entry = OLD_ENTRY.replace("out, 0)", f"out, {mode})")
        new_proof_call = OLD_PROOF_CALL.replace("0#usize", f"{mode}#usize")
        text = replace_once(source, OLD_ENTRY, new_entry)
        if iterations != 8:
            text = replace_once(text, "pub const H_ITERS: usize = 8;", f"pub const H_ITERS: usize = {iterations};")
        lean = replace_once(proof, OLD_PROOF_CALL, new_proof_call)
        # Reverse only the declared changes to establish that every engine
        # function, route predicate, emitter and other proof byte is unchanged.
        restored_source = replace_once(text, new_entry, OLD_ENTRY)
        if iterations != 8:
            restored_source = replace_once(restored_source, f"pub const H_ITERS: usize = {iterations};", "pub const H_ITERS: usize = 8;")
        assert restored_source == source
        assert replace_once(lean, new_proof_call, OLD_PROOF_CALL) == proof
        assert re.search(r"h_parse_mode\(input, out, " + str(mode) + r"\)", new_entry)
        assert f"EH.parse_mode_spec input out {mode}#usize hlen" in lean
        assert not re.search(r"\b(?:sorry|admit|axiom)\b", lean)
        files = {"parse.rs": text.encode(), "Parse.lean": lean.encode()}
        assert all(len(data) <= 524288 for data in files.values())
        manifest = {
            "candidate": name,
            "base_submission_id": "402",
            "parent": {"candidate": BASE.name, "path": BASE.relative_to(ROOT).as_posix(),
                "source_sha256": BASE_SOURCE, "proof_sha256": BASE_PROOF},
            "hashes": {file: sha(data) for file, data in files.items()},
            "bytes": {file: len(data) for file, data in files.items()},
            "delta_from_parent": {"entry_mode": {"old": 0, "new": mode}, "H_ITERS": {"old": 8, "new": iterations}},
            "mechanism": mechanism,
            "entrypoint": f"parse -> h_parse_mode(input, out, {mode}) for every input",
            "proof_entry": f"exact EH.parse_mode_spec input out {mode}#usize hlen",
            "initial_model": "Existing literal/lazy comparison and content-selected high-entropy seed retained. The ew argument computed by h_optimize is unused by h_eval_mode in this source.",
            "restart_scope": "Mode 3's at most two restarts run only when the existing general h_classify(input) % 4 == 0; no file identity or exact-length router is present." if mode == 3 else "Mode 1 never restarts. Mode 2's single restart runs only when the existing general h_classify(input) % 4 == 0; no file identity or exact-length router is present.",
            "restart_budget": {"maximum_restarts": 0 if mode == 1 else 2 if mode == 3 else 1, "DP_steps_per_restart": 3,
                "normal_iteration_cap": iterations, "actual_work": "UNKNOWN; normal early stopping and content qualification remain active"},
            "dependency_audit": "Same 148-function H-only closure as the parent. Reverse substitutions restore source/proof byte-for-byte; only entry mode and declared iteration constant change.",
            "attribution": "Public submission 402 derivative; original provenance retained at references/round4-public-402/PROVENANCE.json.",
            "performance_target": "Public time axis <10 and incremental size benefit are unmeasured hypotheses, not guarantees.",
            "verification": "VERIFIED local generation/hash/paired-entry checks only. Fresh official extraction, Lean obligation, axioms, round trip, time/size, stage2, admission and payment UNKNOWN.",
        }
        files["manifest.json"] = (json.dumps(manifest, indent=2) + "\n").encode()
        dest = ROOT / "candidates" / name
        if args.check:
            for file, data in files.items():
                assert (dest / file).read_bytes() == data, f"candidate drift: {name}/{file}"
        else:
            dest.mkdir(parents=True, exist_ok=True)
            for file, data in files.items():
                (dest / file).write_bytes(data)
        print(json.dumps({"candidate": name, "hashes": manifest["hashes"], "bytes": manifest["bytes"]}))


if __name__ == "__main__":
    main()
