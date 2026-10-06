"""Rebuild the predeclared round3 compression experiments from frozen probe3.

Only writes candidates/round3-size-*/.  No toolchain, CI, network, or submission.
--check compares exact bytes without writing.  The source/proof relationship is
an experiment until official re-extraction and the complete gate accept it.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASE_SOURCE_SHA256 = "e20ea5a7d2e77821008592faef393855077b9b8ceee244f390a85ac0257e047d"
BASE_PROOF_SHA256 = "3906aeb259d83d315811629a54d796b514fc3953742063081451c47997b824b7"
UPSTREAM_REVISION = "a356bbff18b60c4527fbcc85d5a28ef9c20214e0"


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def replace_once(text: str, old: str, new: str) -> str:
    assert text.count(old) == 1, (old, text.count(old))
    return text.replace(old, new, 1)


def variants(source: str) -> dict[str, tuple[str, str]]:
    # The branch is before the engine loops; no extra loop state or helper is
    # introduced. The run proof accepts any minl in [3,8] and any hash mask.
    anchor = "    if n > 16 && cls != 0 {"
    three = replace_once(source, anchor, """    // round3: expose 3-byte repeats in regular text. Binary routes retain
    // their original settings; the tiny planner is unchanged.
    if cls == 1 || cls == 5 || cls == 6 {
        mask = 0xFFFF_FF00;
        minl = 3;
    }
""" + anchor)
    # At HLIT=5 bits/byte and GBASE=10.5 bits, the proxy becomes marginal
    # near distance 128 for length 3. This is a predeclared empirical cutoff,
    # not a claim about the encoder's actual dynamic Huffman costs.
    near = replace_once(three, "            if l >= 3 {", """            // Keep text length-3 tokens only at short distances. Class 3
            // retains the original binary engine's unrestricted minimum.
            if l >= 3 && (l >= 4 || cls == 3 || d <= 128) {""")
    gain = replace_once(source,
                        "let f = find(input, &prev, p, hc, 0, minl, depth, 0);",
                        "let f = find(input, &prev, p, hc, 0, minl, depth, 1);")
    insert, count = re.subn(r"(pub const INS_MAX: usize = )2;", r"\g<1>6;", source)
    assert count == 1
    return {
        "round3-size-hash3": (three, "Regular text classes 1/5/6 use a three-byte hash key and minimum length 3; all other behavior is probe3."),
        "round3-size-hash3-near": (near, "As hash3, but the main engine rejects text length-3 matches farther than 128 bytes; class 3 binaries retain their original behavior."),
        "round3-size-gain": (gain, "The regular main find call uses gm=1, so a longer match must improve the existing gain estimate; lazy find already used gm=1."),
        "round3-size-insert6": (insert, "INS_MAX changes from 2 to 6 with search depth 3 unchanged, isolating denser head insertion from deeper search."),
    }


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    base_source = (ROOT / "candidates/probe3/parse.rs").read_bytes()
    base_proof = (ROOT / "candidates/probe3/Parse.lean").read_bytes()
    assert sha256(base_source) == BASE_SOURCE_SHA256, "probe3 source drift"
    assert sha256(base_proof) == BASE_PROOF_SHA256, "probe3 proof drift"
    source = base_source.decode("utf-8")
    for name, (text, description) in variants(source).items():
        data = text.encode("utf-8")
        assert len(data) <= 524288 and len(base_proof) <= 524288
        metadata = {
            "candidate": name,
            "description": description,
            "base": "candidates/probe3",
            "base_source_sha256": BASE_SOURCE_SHA256,
            "base_proof_sha256": BASE_PROOF_SHA256,
            "parse_rs_sha256": sha256(data),
            "parse_lean_sha256": sha256(base_proof),
            "proof_change": "none; exact original probe3 proof copied, not yet reverified for this parser",
            "upstream_revision": UPSTREAM_REVISION,
            "provenance": "Derived from public submission 261 via probe3; see references/submission-261/PROVENANCE.md",
            "status": "UNVERIFIED candidate; official re-extraction, obligation, axioms, round trip, and performance pending",
        }
        files = {
            "parse.rs": data,
            "Parse.lean": base_proof,
            "manifest.json": (json.dumps(metadata, ensure_ascii=False, indent=2) + "\n").encode("utf-8"),
        }
        target = ROOT / "candidates" / name
        if args.check:
            for file, expected in files.items():
                assert (target / file).read_bytes() == expected, f"candidate drift: {name}/{file}"
        else:
            target.mkdir(exist_ok=True)
            for file, expected in files.items():
                (target / file).write_bytes(expected)
        print(json.dumps(metadata, ensure_ascii=False))


if __name__ == "__main__":
    main()
