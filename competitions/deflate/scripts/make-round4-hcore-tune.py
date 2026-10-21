"""Three fixed-budget experiments on the frozen H-only core.

Only writes candidates/r4-parse-h16*/. No compilation, CI or submission.
Every non-constant source byte and the 95KB proof remain identical to the
declared direct parent. Fresh official extraction and gate remain mandatory.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASE_NAME = "r4-parse-h8d32-core"
BASE_SHA = "916f3a0b5f64b17919c7e4871f878ef2827530a9e3bf577020d8865e61b26953"
PROOF_SHA = "13f23fc46a6d18283aeb339f949cca102761133d6e1ff9b3a1007cd8b7926a46"


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def change_constants(source: str, changes: dict) -> str:
    text = source
    for name, (typ, old, new) in changes.items():
        before, after = f"pub const {name}: {typ} = {old};", f"pub const {name}: {typ} = {new};"
        assert text.count(before) == 1, name
        text = text.replace(before, after, 1)
    restored = text
    for name, (typ, old, new) in changes.items():
        before, after = f"pub const {name}: {typ} = {old};", f"pub const {name}: {typ} = {new};"
        assert restored.count(after) == 1, name
        restored = restored.replace(after, before, 1)
    assert restored == source, "non-constant source drift"
    return text


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--only", action="append", default=[])
    args = ap.parse_args()
    base = ROOT / "candidates" / BASE_NAME
    source_bytes = (base / "parse.rs").read_bytes()
    proof = (base / "Parse.lean").read_bytes()
    audit = (base / "dependency-audit.json").read_bytes()
    assert sha(source_bytes) == BASE_SHA and sha(proof) == PROOF_SHA, "frozen H-core drift"
    recipes = [
        ("r4-parse-h16d32-core", BASE_NAME, {"H_ITERS": ("usize", 8, 16)},
         "Permit up to sixteen learned-cost DP iterations, retaining the existing early-stop rule, depth 32/16, length windows and query margin. Tests remaining cost-refit headroom; actual pass count may remain below the cap."),
        ("r4-parse-h16d64-core", "r4-parse-h16d32-core", {
            "H_BTD": ("usize", 32, 64), "H_BTDS": ("usize", 16, 32),
            "H_BTDMC": ("usize", 32, 64), "H_BTDX": ("usize", 32, 64)},
         "Relative to h16d32, double all active tree-search depth budgets to 64/32; keep iteration cap, cost model, length windows, query margin and routing unchanged. Tests additional match-cache alternatives."),
        ("r4-parse-h16d32-pm256-core", "r4-parse-h16d32-core", {"H_PM": ("u32", 128, 256)},
         "Relative to h16d32, retain first-pass relaxation queries within sixteen rather than eight modeled bits of the running best. Subsequent iterations replay this larger retained-query set; search depth and iteration cap are unchanged."),
    ]
    names = {name for name, _, _, _ in recipes}
    assert set(args.only) <= names, "unknown --only candidate"
    sources = {BASE_NAME: source_bytes.decode()}
    for name, parent, changes, mechanism in recipes:
        text = change_constants(sources[parent], changes)
        sources[name] = text
        if args.only and name not in args.only:
            continue
        files = {"parse.rs": text.encode(), "Parse.lean": proof}
        assert all(len(data) <= 524288 for data in files.values())
        manifest = {
            "candidate": name,
            "base_submission_id": "402",
            "parent": {"candidate": parent, "path": "candidates/" + parent,
                "source_sha256": sha(sources[parent].encode()), "proof_sha256": PROOF_SHA},
            "core_ancestor": {"candidate": BASE_NAME, "source_sha256": BASE_SHA,
                "proof_sha256": PROOF_SHA, "dependency_audit_sha256": sha(audit)},
            "hashes": {file: sha(data) for file, data in files.items()},
            "bytes": {file: len(data) for file, data in files.items()},
            "delta_from_parent": {key: {"type": typ, "old": old, "new": new}
                for key, (typ, old, new) in changes.items()},
            "mechanism": mechanism,
            "source_audit": "VERIFIED reverse constant substitution restores the direct parent byte-for-byte; function bodies, uniform entry, constants outside the listed delta and 148-function closure are unchanged.",
            "proof_change": "None; exact H-core proof retained. Tree-walk totality is parameterized by maxd, iteration measure uses H_ITERS, and H_PM is read in guarded/wrapping query-selection arithmetic. This is a source review, not a new Lean result.",
            "performance_target": {"public_time_axis_less_than": 10, "status": "UNKNOWN until measured; not a proven time bound"},
            "attribution": "Public submission 402 derivative; original metadata in references/round4-public-402/PROVENANCE.json, through the frozen uniform-H and H-core parents.",
            "verification": "VERIFIED local hashes and generation only. Fresh Rust build, official extraction, Lean obligation, axiom whitelist, round trip, time/size, stage2, admission and rewards UNKNOWN.",
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
        print(json.dumps({"candidate": name, "parent": manifest["parent"], "hashes": manifest["hashes"], "bytes": manifest["bytes"]}))


if __name__ == "__main__":
    main()
