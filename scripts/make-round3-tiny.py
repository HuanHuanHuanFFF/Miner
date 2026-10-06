"""Two single-factor tiny-planner experiments; generate files only, never submit."""
from __future__ import annotations

import argparse
import hashlib
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASE_SOURCE = "e20ea5a7d2e77821008592faef393855077b9b8ceee244f390a85ac0257e047d"
BASE_PROOF = "3906aeb259d83d315811629a54d796b514fc3953742063081451c47997b824b7"
VARIANTS = {
    "round3-tiny-kind2": ("TF_TKIND", 1, 2,
        "Allow all <=TF_N structured text (tf_class=1), in addition to existing kinds 0/2, through the unchanged plan+emit path."),
    "round3-tiny-rep1": ("TF_REP", 0, 1,
        "Try the previous match distance before the hash chain; equal-length chain matches retain that previous distance."),
}


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    source = (ROOT / "candidates/probe3/parse.rs").read_bytes()
    proof = (ROOT / "candidates/probe3/Parse.lean").read_bytes()
    assert digest(source) == BASE_SOURCE, "probe3 source drift"
    assert digest(proof) == BASE_PROOF, "probe3 proof drift"
    for name, (constant, old, new, description) in VARIANTS.items():
        text, count = re.subn(rf"(pub const {constant}: usize = ){old};",
            lambda m: m[1] + str(new) + ";", source.decode("utf-8"))
        assert count == 1, constant
        data = text.encode("utf-8")
        assert len(data) <= 524288 and len(proof) <= 524288
        metadata = {
            "candidate": name,
            "description": description,
            "single_factor": {"constant": constant, "old": old, "new": new},
            "base": "candidates/probe3",
            "base_source_sha256": BASE_SOURCE,
            "base_proof_sha256": BASE_PROOF,
            "parse_rs_sha256": digest(data),
            "parse_lean_sha256": digest(proof),
            "source_attribution": "Public submission 261 via probe3; see references/submission-261/PROVENANCE.md",
            "proof_change": "none; exact probe3 proof retained, new parser requires fresh gate",
            "upstream_revision": "a356bbff18b60c4527fbcc85d5a28ef9c20214e0",
            "status": "UNVERIFIED; no extraction, gate, performance, admission, or reward claim",
        }
        files = {
            "parse.rs": data,
            "Parse.lean": proof,
            "manifest.json": (json.dumps(metadata, indent=2) + "\n").encode("utf-8"),
        }
        target = ROOT / "candidates" / name
        if args.check:
            for file, expected in files.items():
                assert (target / file).read_bytes() == expected, (name, file)
        else:
            target.mkdir(exist_ok=True)
            for file, expected in files.items():
                (target / file).write_bytes(expected)
        print(json.dumps(metadata))


if __name__ == "__main__":
    main()
