"""E1: bounded 1..8-byte U118 equality before the generic loop.

No local Rust/Lean build is performed. The measurement pair carries the exact
parent Lean scaffold; a separate proof1 directory carries an UNCOMPILED draft.
"""
from pathlib import Path
import datetime
import hashlib
import importlib
import json

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "references/round26-public-658"
OUT = ROOT / "evidence/round26/extension90m/route-e"
EDIT = importlib.import_module("r26-a-rep-shadow")
NAME = "r26-e-658-short-same"


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def dump(path, obj):
    path.write_bytes((json.dumps(obj, ensure_ascii=False, indent=2) + "\n").encode())


def main():
    raw = (BASE / "parse.rs").read_bytes()
    lean = (BASE / "Parse.lean").read_bytes()
    assert sha(raw) == "1185749453a5abe100106f2e15082eca84521292b7233784a9c2f4562367f3ad"
    assert sha(lean) == "354d56aa9f58536efdb410f3d5ecdf1945bded607965fe8a48161f96b035c494"
    patch = """    let n = s.len();
    // E1: short equality uses the same masked word semantics as the old tail.
    // Guard full loads without overflowing a+8 or b+8. Zero and near-tail cases
    // keep the original loop/tail fallback below.
    if len >= 1 && len <= 8 && n >= 8 && a <= n - 8 && b <= n - 8 {
        let x = u118_be8(s, a) ^ u118_be8(s, b);
        let sh = 64 - 8 * (len as u32);
        if (x >> sh) == 0 { return 1; }
        return 0;
    }
"""
    text = EDIT.edit_fn(raw.decode(), "u118_same(",
                        lambda fn: EDIT.once(fn, "    let n = s.len();\n", patch))
    candidate = ROOT / "candidates" / NAME
    assert not candidate.exists(), candidate
    candidate.mkdir()
    candidate_rust = text.encode()
    (candidate / "parse.rs").write_bytes(candidate_rust)
    (candidate / "Parse.lean").write_bytes(lean)
    hashes = {"parse.rs": sha(candidate_rust), "Parse.lean": sha(lean)}
    dump(candidate / "manifest.json", {
        "candidate": NAME, "parent": "references/round26-public-658", "hashes": hashes,
        "attribution": {"source_receipt": "references/round26-public-658/source-receipt.json",
            "author_hotkey": "5G3YLL7PuDhRBoVoDBYKhAfTxFM4EouSDiYuFXeeWciNRzyK",
            "ownership": "Derivative of public658; all parent source and proof comments retained."},
        "mechanism": "Before original U118 same loop, len1..8 with both full8 loads in bounds returns prefix equality from the same big-endian xor/shift rule as the original tail; len8 uses shift0. Generic loop/tail remains unchanged for len0, len>8 and insufficient load bounds.",
        "difference": "Existing U118/PC masked tail already handles len<8 after generic loop state; this is a dispatch/control-flow change, not a new matching primitive. No equivalent measured historical front-dispatch found in the checked reports/manifests/Rust search.",
        "equivalence": "INFERRED exact return semantics for valid U118 calls: len1..7 original masked tail at k0, len8 original first word equality. No all-input machine execution proof or finite native check yet.",
        "guard_safety": "len>=1 excludes shift64; len<=8 bounds shift to0..56. n>=8 and a,b<=n-8 make full loads safe and a+8/b+8 nonoverflowing. Old fallback retained byte for byte.",
        "proof_status": "DRAFT_PARENT_SCAFFOLD_ONLY_UNCOMPILED",
        "performance": "UNKNOWN. Compiler may already lower the original short case equivalently; added dispatch may cost more. Must receive one original-protocol paired measurement, with all negative results retained.",
        "formal_submission_sent": False,
        "prepared_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
    })
    OUT.mkdir(parents=True, exist_ok=True)
    entry = {"name": NAME, "path": candidate.relative_to(ROOT).as_posix(), "hashes": hashes,
             "anchor": "public658", "comparison_baseline": "public658", "control": False,
             "native_decode_reference": "public658", "expected_equivalent_to": "public658"}
    dump(OUT / "e1-entry.json", entry)
    dump(OUT / "e1-local-preparation.json", {"status": "STATIC_SOURCE_PATCH_NOT_COMPILED",
        "hashes": hashes, "rust_bytes": len(candidate_rust), "lean_bytes": len(lean),
        "full_gate": "NOT_RUN", "native": "NOT_RUN", "original_protocol": "NOT_RUN",
        "patched_function": "u118_same", "patch_count": 1,
        "parent_rust_sha256": sha(raw), "parent_lean_sha256": sha(lean)})
    print(json.dumps(entry, indent=2))


if __name__ == "__main__":
    main()
