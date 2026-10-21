"""Generate three active symbol/token-cost experiments from frozen fast3.

Only writes candidates/r4-parse-symbol*/. No local Rust/Lean execution or CI.
The policies are hypotheses until public measurement and a fresh full gate.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r3-432-fast3"
HASHES = {
    "parse.rs": "bae8014121e4710f4a34ce63452578b4bf69121b4f695e1b1356780a019108ef",
    "Parse.lean": "e2c200cf084eca95eb70d26c0efb04e70d88f015315610d2a54d20b6adb7cf04",
}


def replace_once(text: str, old: str, new: str) -> str:
    assert text.count(old) == 1, (old, text.count(old))
    return text.replace(old, new, 1)


def policies(source: str) -> dict[str, tuple[str, dict]]:
    assert "pub const TM_ON: usize = 1;" in source
    assert "pub const TF_TEXT: usize = 0;" in source
    assert "run1t::<HS>(input, out, T_SKIP, TM_LAZY, SKCAP, TM_LM)" in source
    plus6 = replace_once(source, "pub const TM_LM: u32 = 302_256_128;",
                        "pub const TM_LM: u32 = 302_256_136;")
    plus6 = replace_once(plus6,
        "/// Allowed length codes (bit c = length code 257 + c): 12, 18, 25, 28 = lengths 19-22, 51-58, 163-194, 258.",
        "/// Allowed length codes (bit c = length code 257 + c): 3, 12, 18, 25, 28 = lengths 6, 19-22, 51-58, 163-194, 258.")
    back64 = replace_once(source, "pub const TM_BACK: usize = 16;",
                         "pub const TM_BACK: usize = 64;")
    block512 = replace_once(source, """        let x = e_piece(lens, end - q);
        if x >= 3 {""", """        let mut x = e_piece(lens, end - q);
        // Round4: after 512 tokens in this actual encoder block, let text
        // matches use their full length. run_z's distance-1 pieces stay frugal.
        if d > 1 && nt % 16384 >= 512 {
            x = end - q;
            if x > 258 {
                x = 258;
            }
        }
        if x >= 3 {""")
    return {
        "r4-parse-symbol-len6": (plus6, {
            "mechanism": "Add only length code 260 (length 6) to the active run1t length palette; a fifth length symbol may replace many short-repeat literals and reduce token count.",
            "changes": {"TM_LM": {"old": 302256128, "new": 302256136}},
            "changed_functions": [],
            "risk": "More short matches may introduce distance symbols; one added length code need not reduce total live symbols or encoder work.",
        }),
        "r4-parse-symbol-back64": (back64, {
            "mechanism": "Keep the four-code palette but allow backward merging over up to 64 prior tokens instead of 16 in run1t; longer merged spans may need fewer pieces and tail literals.",
            "changes": {"TM_BACK": {"old": 16, "new": 64}},
            "changed_functions": [],
            "risk": "Additional backward comparison work may cost more than the token/encoder savings, or the deeper budget may not be exercised.",
        }),
        "r4-parse-symbol-block512": (block512, {
            "mechanism": "Use the existing narrow palette for the first 512 tokens of each actual 16384-token encoder block; afterwards allow the full match length for distances >1. This tests amortizing symbol setup cost while reducing literal tails and split tokens.",
            "changes": {"warm_tokens_per_encoder_block": 512, "encoder_block_tokens": 16384},
            "changed_functions": ["e_pieces"],
            "risk": "The candidate does not predict final block size or measure live symbols; opening the alphabet can make a small block slower. Fold retractions can cross a boundary, so the condition uses current emitted-token count, without cached block state.",
        }),
    }


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    base = {name: (BASE / name).read_bytes() for name in HASHES}
    for name, sha in HASHES.items():
        assert hashlib.sha256(base[name]).hexdigest() == sha, f"base drift: {name}"
    newline = "\r\n" if b"\r\n" in base["parse.rs"] else "\n"
    source = base["parse.rs"].decode().replace("\r\n", "\n")
    for name, (text, policy) in policies(source).items():
        files = {"parse.rs": text.replace("\n", newline).encode(), "Parse.lean": base["Parse.lean"]}
        assert all(len(data) <= 524288 for data in files.values())
        manifest = {
            "candidate": name,
            "base_submission_id": "432",
            "base_path": BASE.relative_to(ROOT).as_posix(),
            "base_hashes": HASHES,
            "hashes": {file: hashlib.sha256(data).hexdigest() for file, data in files.items()},
            **policy,
            "active_route": "parse -> e_kind -> run1t for text classes 1/5/6 with n <= TM_MAX=65536. TF_TEXT=0 and TF planner settings unchanged. run_z calls e_pieces only with distance 1, so the block512 policy leaves that path's behavior unchanged.",
            "proof_change": "Exact fast3 proof copied, not reverified. Constants already parameterized by the proof; block512 keeps e_pieces loop state and measure and bounds the selected piece by remaining bytes and 258, matching existing MatchAt.piece obligations.",
            "attribution": "Public submission 432 derivative through fast3; original provenance in references/round3-public-432/PROVENANCE.md.",
            "evidence": "Pinned encoder uses 16384 tokens/block and constructs dynamic Huffman tables before choosing a representation. Public receipts show encoder-heavy small files, but no per-block live-symbol profile is available.",
            "status": "INFERRED mechanism. UNKNOWN build, official extraction, Lean obligation, axioms, round trip, performance, stage2, admission and payment.",
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
        print(json.dumps({"candidate": name, "hashes": manifest["hashes"]}))


if __name__ == "__main__":
    main()
