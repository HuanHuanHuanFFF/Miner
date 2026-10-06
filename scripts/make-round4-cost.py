"""Rebuild prose short/far-match rejection candidates from frozen fast3.

Only writes candidates/r4-parse-cost*/. --check performs exact byte checks.
The gate, extraction and all Rust/Lean execution belong to temporary CI runners.
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


def variants(source: str) -> dict[str, tuple[str, str]]:
    begin = source.index("pub fn run1<const H:")
    end = source.index("pub fn r1_kind(", begin)
    body = source[begin:end]
    old = "            if f.0 >= 3 {"
    assert body.count(old) == 1
    # Only the prose run1 call passes P_SKIP=5 in this SHA-locked base.
    # Other classes pass T_SKIP=3, H_SKIP=3, Z_SKIP=4 or B_SKIP=4.
    constants = {"P_SKIP": 5, "T_SKIP": 3, "H_SKIP": 3, "Z_SKIP": 4, "B_SKIP": 4}
    for name, value in constants.items():
        assert f"pub const {name}: usize = {value};" in source
    policies = {
        "r4-parse-cost2048": (
            "skip != P_SKIP || f.0 >= 5 || f.1 <= 2048",
            "Only prose run1 rejects length-4 matches beyond distance 2048; under the existing 5-bit-literal/10.5-bit-base proxy these matches have negative savings. Existing literal/miss handling performs rejection.",
        ),
        "r4-parse-cost8192": (
            "skip != P_SKIP || f.0 >= 5 || f.1 <= 8192",
            "Only prose run1 rejects length-4 matches beyond distance 8192, a weaker predeclared cutoff to test whether retaining mildly negative proxy matches helps backward merging and encoder token count.",
        ),
        "r4-parse-cost2048-back": (
            "skip != P_SKIP || f.0 >= 5 || f.1 <= 2048 || (f.1 < p && input[p - 1] == input[p - 1 - f.1])",
            "As cost2048, but retain a candidate when its immediately preceding byte also agrees at its distance, preserving a possible backward fold. The added guarded two-byte read occurs only for short/far prose matches.",
        ),
    }
    return {
        name: (source[:begin] + body.replace(old, f"            if f.0 >= 3 && ({condition}) {{", 1) + source[end:], description)
        for name, (condition, description) in policies.items()
    }


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    base = {name: (BASE / name).read_bytes() for name in BASE_HASHES}
    for name, sha in BASE_HASHES.items():
        assert hashlib.sha256(base[name]).hexdigest() == sha, f"base drift: {name}"
    newline = "\r\n" if b"\r\n" in base["parse.rs"] else "\n"
    source = base["parse.rs"].decode("utf-8").replace("\r\n", "\n")
    for name, (text, mechanism) in variants(source).items():
        files = {"parse.rs": text.replace("\n", newline).encode(), "Parse.lean": base["Parse.lean"]}
        assert all(len(content) <= 524288 for content in files.values())
        manifest = {
            "candidate": name,
            "base_submission_id": "432",
            "base_path": BASE.relative_to(ROOT).as_posix(),
            "base_hashes": BASE_HASHES,
            "mechanism": mechanism,
            "route_scope": "At this frozen base, only cls=5 passes skip=P_SKIP=5 to run1; other classes pass 3 or 4. Small text run1t is unchanged.",
            "hashes": {file: hashlib.sha256(content).hexdigest() for file, content in files.items()},
            "proof_change": "Exact fast3 proof copied, not yet reverified. Stronger match guard, same loop state and fuel, same literal/miss branch; no extra loop.",
            "attribution": "Derivative of public submission 432 through fast3; see references/round3-public-432/PROVENANCE.md.",
            "anticipated_tradeoff": "INFERRED: reject negative-proxy short matches without extra searches; more literals and lost fold opportunities may worsen both axes.",
            "verification": "UNKNOWN: Rust build, official extraction, Lean obligation, axiom whitelist, public round trip/performance, private stage2 and admission.",
        }
        files["manifest.json"] = (json.dumps(manifest, indent=2) + "\n").encode()
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
