"""One EOB-frequency experiment on frozen public submission 299.

Only writes candidates/r4-parse-299-eob1/. Preserve all original routing,
effort settings, other frequencies and emitter/proof text. No toolchain or CI.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "references/round4-public-299"
HASHES = {
    "parse.rs": "71314c4da7ccd29331a360bce9be8697857109c66adc87d3480eeaa22930625d",
    "Parse.lean": "9b77b3523cbf7044aaffa11b6fd9676b3615ca4bf148b43b3cb92da4073b3e3d",
}
NAME = "r4-parse-299-eob1"
ANCHOR = "            a_add_counts(&mut sl, &bl, &lf, &mut sd, &bd, &df);"


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    base = {name: (BASE / name).read_bytes() for name in HASHES}
    for name, expected in HASHES.items():
        assert sha(base[name]) == expected, f"public299 drift: {name}"
    source = base["parse.rs"].decode()
    newline = "\r\n" if "\r\n" in source else "\n"
    assert source.count(ANCHOR) == 1
    assert source.index("pub fn a_engine(") < source.index(ANCHOR) < source.index("pub const B_WR:")
    insertion = ANCHOR + newline + "            sl[256] = 1;"
    text = source.replace(ANCHOR, insertion, 1)
    assert text.replace(insertion, ANCHOR, 1) == source, "unexpected additional source edit"
    files = {"parse.rs": text.encode(), "Parse.lean": base["Parse.lean"]}
    assert all(len(data) <= 524288 for data in files.values())
    provenance = json.loads((BASE / "PROVENANCE.json").read_text())
    manifest = {
        "candidate": NAME,
        "base_submission_id": "299",
        "parent": {"path": BASE.relative_to(ROOT).as_posix(), "hashes": HASHES},
        "hashes": {name: sha(data) for name, data in files.items()},
        "bytes": {name: len(data) for name, data in files.items()},
        "change": "In a_engine only, immediately after a_add_counts(sl,bl,lf,sd,bd,df), set sl[256]=1.",
        "mechanism": "Normalize observed EOB frequency after sampled segment scaling and partial-block count merging; a_walk emits one EOB into each segment's model, while the encoder has one EOB per 16384-token block.",
        "preserved": "All classifier, CFG, search depths, pass counts, other frequencies, cost-model add-one priors, verified emitter and complete proof bytes remain unchanged.",
        "model_limit": "a_set_costs_huff still adds one pseudocount to every litlen symbol, including EOB. This candidate corrects the observed count only; accumulated EOB may have acted as useful regularization. Improvement is not assumed.",
        "proof_review": "a_engine_loop1_loop0_spec tracks window/path/token bounds, not sl frequency values. The added write is at fixed in-range index 256 of a 512-element array, with no new branch, loop, state field or changed measure. Copied proof still requires fresh extraction and gate.",
        "attribution": {"source_url": provenance["source_url"], "miner_hotkey": provenance["official_item"]["hotkey"],
            "note": "External public299 source; metadata and original files retained unchanged in the reference directory."},
        "verification": "VERIFIED local SHA locks, exact one-line change and --check only. Rust, official extraction, Lean obligation, axioms, round trip, performance, stage2, admission and reward UNKNOWN.",
    }
    files["manifest.json"] = (json.dumps(manifest, indent=2) + "\n").encode()
    dest = ROOT / "candidates" / NAME
    if args.check:
        for name, data in files.items():
            assert (dest / name).read_bytes() == data, f"candidate drift: {name}"
    else:
        dest.mkdir(parents=True, exist_ok=True)
        for name, data in files.items():
            (dest / name).write_bytes(data)
    print(json.dumps({"candidate": NAME, "hashes": manifest["hashes"], "bytes": manifest["bytes"]}))


if __name__ == "__main__":
    main()
