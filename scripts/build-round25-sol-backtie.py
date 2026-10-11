"""One-byte backward support makes a forward-length tie worth examining.

This builder writes only the delegated Sol candidate/evidence paths. It does
not compile Rust/Lean, dispatch CI, or make any external submission.
"""
from pathlib import Path
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r22-595-chain-halfhead"
NAME = "r25-sol-backtie"
EVIDENCE = ROOT / "evidence/round25/sol"
EXPECTED = {
    "parse.rs": "57a8fb4feffa52d6b966899c4a56bc4754f6fc967a05cf52d5b02a574d037275",
    "Parse.lean": "4ff09d168269ae8d9c93e602496b01078d2d0ec80f27d6cd16041d91a76c70a6",
}

TRY_OLD = """pub fn pc_f_try(s: &[u8], c: usize, c2: usize, p: usize, l: usize, d: usize, minl: usize) -> (usize, usize) {
    let n = s.len();
    let d2 = p.wrapping_sub(c2);
    if c2 < c && d2.wrapping_sub(1) < 32768 && p + l < n && s[c2 + l] == s[p + l] {
        let mut cap = n - p;
        if cap > 258 {
            cap = 258;
        }
        let m = pc_common_from(s, c2, p, cap, 0);
        if m > l && m >= minl {
            (m, d2)
        } else {
            (l, d)
        }
    } else {
        (l, d)
    }
}"""

TRY_NEW = """pub fn pc_f_try(s: &[u8], c: usize, c2: usize, p: usize, l: usize, d: usize, minl: usize, ls: usize) -> (usize, usize) {
    let n = s.len();
    let d2 = p.wrapping_sub(c2);
    if c2 < c && d2.wrapping_sub(1) < 32768 && p + l < n {
        // An equal forward match may cover one more pending literal backwards.
        // The original source must fail that byte; full forward validation follows.
        let forward = s[c2 + l] == s[p + l];
        let backtie = !forward && ls < p && l < 258 && c2 > 0 && d < p
            && s[c2 - 1] == s[p - 1] && s[p - 1 - d] != s[p - 1];
        if forward
            || (backtie && l >= 3 && s[c2 + l - 1] == s[p + l - 1]) {
            let mut cap = n - p;
            if cap > 258 {
                cap = 258;
            }
            let m = pc_common_from(s, c2, p, cap, 0);
            if (m > l || (m == l && backtie)) && m >= minl {
                (m, d2)
            } else {
                (l, d)
            }
        } else {
            (l, d)
        }
    } else {
        (l, d)
    }
}"""


def sha(data):
    return hashlib.sha256(data).hexdigest()


def replace_once(text, old, new):
    assert text.count(old) == 1, (old, text.count(old))
    return text.replace(old, new, 1)


def build():
    raw = {name: (BASE / name).read_bytes() for name in EXPECTED}
    assert {name: sha(data) for name, data in raw.items()} == EXPECTED
    source = raw["parse.rs"].decode()
    changes = [
        (TRY_OLD, TRY_NEW),
        ("pub fn pc_f_deepen(s: &[u8], prev: &[u32; 32768], c: usize, c2: usize, p: usize, l: usize, d: usize, dp: usize, minl: usize)",
         "pub fn pc_f_deepen(s: &[u8], prev: &[u32; 32768], c: usize, c2: usize, p: usize, l: usize, d: usize, dp: usize, minl: usize, ls: usize)"),
        ("pc_f_try(s, c, c2, p, l, d, minl)", "pc_f_try(s, c, c2, p, l, d, minl, ls)"),
        ("pc_f_try(s, c2, c3, p, g.0, g.1, minl)", "pc_f_try(s, c2, c3, p, g.0, g.1, minl, ls)"),
        ("pc_f_deepen(input, &prev, c, cl, p, f.0, f.1, dp, minl)",
         "pc_f_deepen(input, &prev, c, cl, p, f.0, f.1, dp, minl, ls)"),
    ]
    for old, new in changes:
        source = replace_once(source, old, new)
    restored = source
    for old, new in changes[::-1]:
        restored = replace_once(restored, new, old)
    assert restored.encode() == raw["parse.rs"]

    # Interface-only adaptation. The inherited proof body is still a draft for
    # the changed extracted branches; real extraction and original gate decide it.
    proof = raw["Parse.lean"].decode()
    proof_changes = [
        ("theorem f_try_spec (s : Slice Std.U8) (c c2 p l d minl : Std.Usize)",
         "theorem f_try_spec (s : Slice Std.U8) (c c2 p l d minl ls : Std.Usize)"),
        ("slot.pc_f_try s c c2 p l d minl ⦃", "slot.pc_f_try s c c2 p l d minl ls ⦃"),
        ("(c c2 p l d dp minl : Std.Usize) (hc : c.val ≤ p.val)",
         "(c c2 p l d dp minl ls : Std.Usize) (hc : c.val ≤ p.val)"),
        ("slot.pc_f_deepen s prev c c2 p l d dp minl ⦃",
         "slot.pc_f_deepen s prev c c2 p l d dp minl ls ⦃"),
    ]
    for old, new in proof_changes:
        proof = replace_once(proof, old, new)
    restored_proof = proof
    for old, new in proof_changes[::-1]:
        restored_proof = replace_once(restored_proof, new, old)
    assert restored_proof.encode() == raw["Parse.lean"]

    files = {"parse.rs": source.encode(), "Parse.lean": proof.encode()}
    hashes = {name: sha(data) for name, data in files.items()}
    assert all(0 < len(data) <= 524288 for data in files.values())
    assert source[:source.index("pub fn pc_f_try(")] == raw["parse.rs"].decode()[:raw["parse.rs"].decode().index("pub fn pc_f_try(")]
    manifest = {
        "candidate": NAME,
        "parent": "r22-595-chain-halfhead",
        "parent_hashes": EXPECTED,
        "hashes": hashes,
        "mechanism": "Permit a fully validated equal-forward-length predecessor only when it matches the immediately preceding pending literal and the current source does not. Preserve every original strictly-longer match acceptance, shallow search depth, tables, routes, insertion, skip/lazy, fold and encoder.",
        "difference_from_old_work": "R22/R23 widened matched-position chain capacity; R24 gain acceptance could only filter strictly longer offers. This exposes equal-length sources that the old byte[l] quick rejection excludes, and ranks them by an actual one-byte backward extension opportunity. It is neither failed-primary rescue (R13) nor repeat-distance literal-gap rescue (R11) nor end-of-match insertion.",
        "attribution": {
            "original_source": "references/round21-public-595/source-receipt.json",
            "author_hotkey": "5CciqiMAb9d1qu9CsZLtr2svoxCU4ywUtDX6pLHMZWmRB8D1",
            "parent_manifest": "candidates/r22-595-chain-halfhead/manifest.json",
            "ownership": "Existing public595 and inherited PC matching/proof machinery retained with original headers. This is a bounded derivative acceptance experiment.",
        },
        "proof_status": "DRAFT_INTERFACE_ADAPTED_UNCOMPILED_FOR_NEW_EXACT_PAIR",
        "proof_migration": "pc_f_try and pc_f_deepen gain an unchecked hint ls; four Lean interface locations are adapted. Existing MatchAt postconditions cover equal matches because l>=3. New backward branch and real extracted interfaces remain unverified; original Obligation, axiom whitelist and roundtrip/fullgate are required.",
        "semantic_status": "Intentional token/output differences allowed. Each adopted source passes strict predecessor/window guards and original full forward byte comparison. Correctness of the actual Rust/Lean pair is UNKNOWN before cloud verification.",
        "performance_status": "UNKNOWN; no native Rust run or timing in this builder",
        "comparison_baseline": "combo",
        "native_decode_reference": "combo",
        "stop_condition": "Decode/panic failure stops. If original-encoder changes are negligible or the distance/token cost offsets the extra backward coverage without a useful frontier tradeoff, stop this exact implementation. Any worthwhile signal needs original paired total-time screening and a frozen independent confirmation.",
        "formal_submission_sent": False,
        "source_reversal": "Reverse isolated pc_f_try body, extra ls argument on pc_f_deepen and its three calls; exact parent bytes are restored. Reverse four Lean signature/call changes to restore exact inherited proof bytes.",
    }
    files["manifest.json"] = (json.dumps(manifest, indent=2, ensure_ascii=False) + "\n").encode()
    return files, manifest


def finite_opportunity_model():
    """Concrete branch opportunity and guards, not a Rust/Lean certificate."""
    cases = []
    for length in (3, 4, 16, 128, 257, 258):
        data = bytearray(b"!" * 1100)
        older, current, position = 16, 320, 640
        prefix = bytes((65 + i % 23 for i in range(length)))
        for start in (older, current, position):
            data[start:start + length] = prefix
        data[older - 1] = data[position - 1] = ord("z")
        data[current - 1] = ord("y")
        data[older + length] = data[current + length] = ord("Q")
        data[position + length] = ord("R")
        distance = position - current
        old_quick_passes = data[older + length] == data[position + length]
        backtie = length < 258 and data[older - 1] == data[position - 1] and data[position - 1 - distance] != data[position - 1]
        actual = 0
        while actual < 258 and data[older + actual] == data[position + actual]:
            actual += 1
        assert actual == length
        assert not old_quick_passes
        accepted = backtie and actual >= 4
        if accepted:
            assert data[position - 1] == data[position - 1 - (position - older)]
            assert data[position - 1] != data[position - 1 - distance]
        cases.append({"forward_length": length, "chain_minimum": 4,
                      "old_byte_at_length_quick_reject": not old_quick_passes,
                      "candidate_tie_guard": backtie, "accepted_with_pending_literal": accepted,
                      "extra_verified_backwards_literal": 1 if accepted else 0})
    return {
        "status": "VERIFIED_FINITE_PYTHON_OPPORTUNITY_MODEL_ONLY",
        "cases": cases,
        "scope": "Six constructed disjoint sources establish that an equal forward match with distinct backward support is reachable and that length258/minimum4 prevent this specific tie. They are not real Rust executions, corpus coverage, encoded savings, Lean proof or performance evidence.",
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    files, manifest = build()
    destination = ROOT / "candidates" / NAME
    if args.check:
        assert all((destination / name).read_bytes() == data for name, data in files.items())
    else:
        assert not destination.exists(), destination
        destination.mkdir()
        for name, data in files.items():
            (destination / name).write_bytes(data)
        EVIDENCE.mkdir(parents=True, exist_ok=True)
        records = {
            "design.json": {
                "gap": "Existing matched-position chain search ignores equal forward matches whose source can absorb a pending literal backwards.",
                "change": manifest["mechanism"],
                "prior_work": manifest["difference_from_old_work"],
                "minimum_action": "Original28-file encoder/token/decode against exact public595 and actual combo; inspect per-file byte and token differences before time/gate spend.",
                "decision": manifest["stop_condition"],
                "cost_cap_runner_minutes_for_native_screen": 15,
                "local_work": "Lightweight builder, byte reversal and concrete branch model only. No Rust/Lean tools, CI or external actions.",
                "proof_status": manifest["proof_status"],
                "risks": ["Farther distance can cost more than one saved literal", "Qualifying ties require another full forward comparison", "Tie source can permit further token folding, so real encoded result need not improve monotonically"],
            },
            "build-preflight.json": {
                "candidate": NAME, "parent_hashes": EXPECTED,
                "hashes": manifest["hashes"],
                "source_reversal_exact": True, "proof_reversal_exact": True,
                "source_bytes": {name: len(data) for name, data in files.items() if name != "manifest.json"},
                "finite_opportunity": finite_opportunity_model(),
                "native_rust": "NOT_RUN", "lean_compile": "NOT_RUN", "full_gate": "NOT_RUN", "total_time": "NOT_RUN",
            },
            "entries.json": [{
                "name": NAME, "path": "candidates/" + NAME, "control": False,
                "hashes": manifest["hashes"], "anchor": "public595",
                "comparison_baseline": "combo", "native_decode_reference": "combo",
            }],
        }
        for name, record in records.items():
            path = EVIDENCE / name
            assert not path.exists(), path
            path.write_bytes((json.dumps(record, indent=2, ensure_ascii=False) + "\n").encode())
    print(json.dumps({"candidate": NAME, "hashes": manifest["hashes"], "status": manifest["proof_status"], "check": args.check}))


if __name__ == "__main__":
    main()
