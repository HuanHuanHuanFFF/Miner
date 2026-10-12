"""One extra predecessor only after an observed duplicate short-head prefix."""
from pathlib import Path
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r22-595-chain-halfhead"
EVIDENCE = ROOT / "evidence/round25/sol"
NAME = "r25-sol-duplicate-hop"
EXPECTED = {"parse.rs": "57a8fb4feffa52d6b966899c4a56bc4754f6fc967a05cf52d5b02a574d037275",
            "Parse.lean": "4ff09d168269ae8d9c93e602496b01078d2d0ec80f27d6cd16041d91a76c70a6"}
HELPER = """/// Preserve original deepening; one extra hop only when a short primary's old source repeats its8-byte prefix.
#[inline(always)]
pub fn r25_duplicate_deepen(s: &[u8], prev: &[u32; 32768], c: usize, c2: usize,
    cw: u64, p: usize, l: usize, d: usize, km: u32, dp: usize, minl: usize) -> (usize, usize) {
    let g = pc_f_deepen(s, prev, c, c2, p, l, d, dp, minl);
    if km == 4294967295 && dp == 1 && l < 8 && c2 < c
        && p.wrapping_sub(c2).wrapping_sub(1) < 32768 && p + 8 <= s.len()
        && pc_be8(s, c2) == cw {
        let c3 = prev[c2 % 32768] as usize;
        pc_f_try(s, c2, c3, p, g.0, g.1, minl)
    } else {
        g
    }
}

"""


def sha(data):
    return hashlib.sha256(data).hexdigest()


def generate():
    raw = {name: (BASE / name).read_bytes() for name in EXPECTED}
    assert {name: sha(data) for name, data in raw.items()} == EXPECTED
    plan = json.loads((EVIDENCE / "duplicate-hop-predeclared.json").read_bytes())
    assert plan["parent_rust_sha256"] == EXPECTED["parse.rs"]
    receipt = ROOT / plan["evidence"]
    receipt_raw = receipt.read_bytes()
    assert sha(receipt_raw) == plan["evidence_sha256"]
    assert json.loads(receipt_raw)["status"] == "VERIFIED_UNTIMED_PARENT_OBSERVER_TOKEN_AND_DECODE_EQUAL"
    source = raw["parse.rs"].decode()
    marker = "/// `pc_run1` with chain links and `pc_f_deepen` at every match of at least `minl` bytes."
    assert source.count(marker) == 1
    old = "pc_f_deepen(input, &prev, c, cl, p, f.0, f.1, dp, minl)"
    new = "r25_duplicate_deepen(input, &prev, c, cl, cw, p, f.0, f.1, km, dp, minl)"
    assert source.count(old) == 1
    source = source.replace(marker, HELPER + marker, 1).replace(old, new, 1)
    assert source.replace(HELPER, "", 1).replace(new, old, 1).encode() == raw["parse.rs"]
    files = {"parse.rs": source.encode(), "Parse.lean": raw["Parse.lean"]}
    assert all(0 < len(data) <= 524288 for data in files.values())
    manifest = {"candidate": NAME, "parent": BASE.name, "parent_hashes": EXPECTED,
        "hashes": {name: sha(data) for name, data in files.items()},
        "mechanism": plan["change"], "difference_from_old_work": plan["difference_from_old_work"],
        "attribution": {"original_source": "references/round21-public-595/source-receipt.json",
            "parent": "candidates/r22-595-chain-halfhead/manifest.json",
            "ownership": "Public source and author headers retained. Existing PC match/deepening/emission and all insertion code inherited; this is a bounded derivative query change."},
        "evidence": plan["evidence"], "evidence_sha256": plan["evidence_sha256"],
        "proof_status": "DRAFT_PARENT_LEAN_COPIED_UNADAPTED_FOR_NEW_WRAPPER",
        "proof_migration": plan["proof"], "performance_status": "UNKNOWN",
        "comparison_baseline": "combo", "native_decode_reference": "combo",
        "formal_submission_sent": False, "risks": plan["risks"],
        "source_reversal": "Remove one wrapper and reverse the one original main-loop callee replacement to recover exact combo Rust. Lean is the exact parent copy.",
        "stop_condition": plan["stop_condition"]}
    files["manifest.json"] = (json.dumps(manifest, indent=2, ensure_ascii=False) + "\n").encode()
    return files, manifest


def main():
    parser = argparse.ArgumentParser(); parser.add_argument("--check", action="store_true")
    args = parser.parse_args(); files, manifest = generate()
    destination = ROOT / "candidates" / NAME
    if args.check:
        assert all((destination / name).read_bytes() == files[name] for name in ("parse.rs", "Parse.lean"))
        assert json.loads((destination / "manifest.json").read_bytes())["hashes"] == manifest["hashes"]
    else:
        assert not destination.exists(), destination
        destination.mkdir()
        for name, data in files.items(): (destination / name).write_bytes(data)
        entry = {"name": NAME, "path": destination.relative_to(ROOT).as_posix(), "control": False,
            "hashes": manifest["hashes"], "anchor": "public595", "comparison_baseline": "combo",
            "native_decode_reference": "combo"}
        records = {"duplicate-hop-entry.json": entry,
            "duplicate-hop-build-preflight.json": {"status": "VERIFIED_SOURCE_SCOPE_AND_RECEIPT_BINDING_ONLY",
                "hashes": manifest["hashes"], "parent_hashes": EXPECTED,
                "source_reversal_exact": True, "lean_is_parent_copy": True,
                "original_insertions_arrays_parameters_unchanged": True,
                "extra_hops_maximum": 1, "current_head_word_reused": True,
                "long_primary_and_three_byte_dp2_behavior": "Original g returned without extra predecessor/word read",
                "native_rust": "NOT_RUN", "paired_total_time": "NOT_RUN", "full_gate": "NOT_RUN"}}
        for name, record in records.items():
            path = EVIDENCE / name; assert not path.exists(), path
            path.write_bytes((json.dumps(record, indent=2, ensure_ascii=False) + "\n").encode())
    print(json.dumps({"candidate": NAME, "hashes": manifest["hashes"], "check": args.check,
        "proof_status": manifest["proof_status"]}))


if __name__ == "__main__": main()
