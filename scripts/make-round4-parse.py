"""Rebuild bounded-lookahead derivatives of the frozen public-432 fast3 parser.

Only writes candidates/r4-parse-*/. --check compares bytes without writing.
Rust/Lean compilation and measurements belong to temporary GitHub runners.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r3-432-fast3"
BASE_HASHES = {
    "parse.rs": "bae8014121e4710f4a34ce63452578b4bf69121b4f695e1b1356780a019108ef",
    "Parse.lean": "e2c200cf084eca95eb70d26c0efb04e70d88f015315610d2a54d20b6adb7cf04",
}


def replace_once(text: str, old: str, new: str) -> str:
    assert text.count(old) == 1, (old, text.count(old))
    return text.replace(old, new, 1)


def variants(source: str) -> dict[str, tuple[str, str]]:
    lazy6 = replace_once(source, "pub const P_LAZY: usize = 0;", "pub const P_LAZY: usize = 6;")
    lazy9 = replace_once(source, "pub const P_LAZY: usize = 0;", "pub const P_LAZY: usize = 9;")
    begin = lazy9.index("pub fn run1<const H:")
    end = lazy9.index("pub fn r1_kind(", begin)
    body = lazy9[begin:end]
    single = replace_once(body, """                        d = g.1;
                    } else {""", """                        d = g.1;
                        // Prose: at most one accepted lazy step per match.
                        if lazy == 9 {
                            go = 0;
                        }
                    } else {""")
    marginal = replace_once(body, """while go == 1 && l < lazy && p + 1 < lim {""", """while go == 1 && l < lazy && p + 1 < lim && (lazy != 9 || l < 6 || d > 1024) {""")
    return {
        "r4-parse-lazy6": (lazy6, "Prose P_LAZY 0 -> 6: the existing read-ahead loop only searches p+1 after lengths 4 or 5, and accepts by existing gain proxy."),
        "r4-parse-lazy9": (lazy9, "Prose P_LAZY 0 -> 9: existing read-ahead lazy search after lengths 4..8, providing the attribution control for the two restricted variants."),
        "r4-parse-lazy9-one": (lazy9[:begin] + single + lazy9[end:], "Prose P_LAZY 9 with at most one accepted lazy step for each main-loop match; structured-text and other lazy policies unchanged."),
        "r4-parse-lazy9-cost": (lazy9[:begin] + marginal + lazy9[end:], "Prose P_LAZY 9, but spend the extra lookup only for l < 6 or d > 1024; this is a declared proxy for marginal current matches, not an encoder cost claim."),
    }


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    base = {name: (BASE / name).read_bytes() for name in BASE_HASHES}
    for name, sha in BASE_HASHES.items():
        assert hashlib.sha256(base[name]).hexdigest() == sha, f"base drift: {name}"
    # Normalize only for exact edit anchors, then restore the source's line endings.
    newline = "\r\n" if b"\r\n" in base["parse.rs"] else "\n"
    source = base["parse.rs"].decode("utf-8").replace("\r\n", "\n")
    for name, (text, mechanism) in variants(source).items():
        data = text.replace("\n", newline).encode("utf-8")
        files = {"parse.rs": data, "Parse.lean": base["Parse.lean"]}
        assert all(len(content) <= 524288 for content in files.values())
        manifest = {
            "candidate": name,
            "base_submission_id": "432",
            "base_path": BASE.relative_to(ROOT).as_posix(),
            "base_hashes": BASE_HASHES,
            "mechanism": mechanism,
            "hashes": {file: hashlib.sha256(content).hexdigest() for file, content in files.items()},
            "proof_change": "Exact fast3 proof copied. Fresh extraction, Lean obligation and axiom checks pending; copying is not verification.",
            "attribution": "Derivative of public submission 432 through fast3; original author metadata in references/round3-public-432/PROVENANCE.md.",
            "verification": "UNKNOWN: new official gate, round trip, paired performance, private stage2 and online admission.",
            "anticipated_tradeoff": "INFERRED: a next-position match may recover prose compression at less work than a global deeper chain; extra probes may erase the speed benefit.",
        }
        files["manifest.json"] = (json.dumps(manifest, indent=2) + "\n").encode("utf-8")
        dest = ROOT / "candidates" / name
        if args.check:
            for file, content in files.items():
                assert (dest / file).read_bytes() == content, f"candidate drift: {name}/{file}"
        else:
            dest.mkdir(parents=True, exist_ok=True)
            for file, content in files.items():
                (dest / file).write_bytes(content)
        print(json.dumps({"candidate": name, "hashes": manifest["hashes"]}))


if __name__ == "__main__":
    main()
