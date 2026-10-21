"""Rebuild three one-constant speed hypotheses from official public submission 407.

This only writes lightweight candidates. Source attribution and exact reference
hashes travel with each candidate; copied proofs still need new official gates.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "references" / "round3-public-407"
EXPECTED = {
    "parse.rs": "64945bab5fa675ed724748b3097bf02477ba3677afc9fa4478a394ccc0996a40",
    "Parse.lean": "ed37de55387d9a984afa841b83aac1edd4ea4517cfb5831967884b6783fa98a8",
}
VARIANTS = {
    "round3-speed-407-dt900": {"FL_SM_DT": 900},
    "round3-speed-407-dt1200": {"FL_SM_DT": 1200},
    "round3-speed-407-acc3": {"G_ACC": 3},
}


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def generate(check: bool = False) -> dict:
    frozen = {filename: (BASE / filename).read_bytes() for filename in EXPECTED}
    for filename, expected in EXPECTED.items():
        assert sha(frozen[filename]) == expected, f"public reference drift: {filename}"
    provenance = json.loads((BASE / "source.json").read_text(encoding="utf-8"))
    assert str(provenance["submission_id"]) == "407"
    # The initial receipt was normalized while this worker was reconstructing.
    # Both observed schemas bind exactly the same two preserved source files.
    if "files" in provenance:
        assert provenance["files"]["parse_rs_sha256"] == EXPECTED["parse.rs"]
        assert provenance["files"]["proof_lean_sha256"] == EXPECTED["Parse.lean"]
        original_author = provenance["entry"]["hotkey"]
    else:
        assert provenance["file_sha256"]["parse_rs"] == EXPECTED["parse.rs"]
        assert provenance["file_sha256"]["proof_lean"] == EXPECTED["Parse.lean"]
        original_author = provenance["author_hotkey"]
    source = frozen["parse.rs"].decode("utf-8")
    proof = frozen["Parse.lean"]
    result = {}
    for name, constants in VARIANTS.items():
        text = source
        for key, value in constants.items():
            text, count = re.subn(rf"(pub const {key}: (?:usize|u64) = )\d+;",
                                 rf"\g<1>{value};", text)
            assert count == 1, (name, key, count)
        source_lines, output_lines = source.splitlines(), text.splitlines()
        assert len(source_lines) == len(output_lines)
        assert sum(a != b for a, b in zip(source_lines, output_lines)) == len(constants)
        # Ensure parse and every helper body are exactly the returned reference.
        strip_constants = lambda x: re.sub(r"pub const \w+: (?:usize|u64) = \d+;", "CONST", x)
        assert strip_constants(source) == strip_constants(text)
        files = {"parse.rs": text.encode("utf-8"), "Parse.lean": proof}
        manifest = {
            "candidate": name,
            "base_submission_id": "407",
            "base_path": "references/round3-public-407",
            "source_endpoint": provenance["source_endpoint"],
            "reference_fetched_at_utc": provenance["fetched_at_utc"],
            "original_author_hotkey": original_author,
            "original_sha256": EXPECTED,
            "sha256": {filename: sha(data) for filename, data in files.items()},
            "changed_constants": constants,
            "proof_bytes_unchanged": True,
            "changed_source_lines": len(constants),
            "status": {"generation": "VERIFIED", "official_gate": "UNKNOWN", "performance": "UNKNOWN"},
        }
        files["manifest.json"] = (json.dumps(manifest, ensure_ascii=False, indent=2) + "\n").encode("utf-8")
        attribution = (
            f"# {name}\n\n"
            "Derived from official public submission **407**, retrieved at "
            f"{provenance['fetched_at_utc']}.\n\n"
            f"Original public author attribution (miner hotkey): `{original_author}`. "
            "The original parser and proof are third-party work; this candidate changes only "
            + ", ".join(f"`{key}={value}`" for key, value in constants.items()) + ".\n\n"
            f"[Official source endpoint]({provenance['source_endpoint']}); preserved reference and receipt: "
            "`references/round3-public-407/`. Original source/proof and candidate hashes are in "
            "`manifest.json`. The proof bytes remain unchanged.\n\n"
            "**UNKNOWN**: fresh official extraction, Lean obligation, axiom audit, round trip, paired "
            "performance, private stage2, admission/rank, and rewards. The original submission's "
            "recorded gate status does not certify this modified candidate.\n"
        )
        files["PROVENANCE.md"] = attribution.encode("utf-8")
        target = ROOT / "candidates" / name
        if check:
            for filename, data in files.items():
                assert (target / filename).read_bytes() == data, f"generated-file drift: {name}/{filename}"
        else:
            target.mkdir(exist_ok=True)
            for filename, data in files.items():
                (target / filename).write_bytes(data)
        result[name] = manifest
    return result


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true", help="verify exact reconstruction without writing")
    args = parser.parse_args()
    print(json.dumps(generate(args.check), ensure_ascii=False, indent=2))
