"""Build CPU-only ablations from the exact round-3 fast3 source.

No compiler or CI invocation is performed here. --check rebuilds every output
byte in memory, including the manifest, then compares it with the saved files.
"""
from pathlib import Path
import argparse
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r3-432-fast3"
BASE_HASHES = {
    "parse.rs": "bae8014121e4710f4a34ce63452578b4bf69121b4f695e1b1356780a019108ef",
    "Parse.lean": "e2c200cf084eca95eb70d26c0efb04e70d88f015315610d2a54d20b6adb7cf04",
}

# Each row changes one mechanism. The fold row moves both implementations of
# backward folding out of line; they differ only in the configured back limit.
VARIANTS = {
    "r4-cpu-r1off": {
        "constant_changes": {"R1_ON": (1, 0)},
        "attributes": {},
        "mechanism": "Disable the regular run1 read-ahead route; use the existing run chain engine. Small-text run1t, tiny, and stride routes keep their existing selection.",
        "expected_token_equivalence": "INFERRED from the upstream description and one-step routing preconditions; not proven or observed. Full token and DEFLATE hash comparison is required.",
        "diagnostic": "Separate table clearing/window writes, delayed literal flushing, and read-ahead effects. This is an ablation; a speed gain is not assumed.",
    },
    "r4-cpu-run1ni": {
        "constant_changes": {},
        "attributes": {"run1": ("always", "never")},
        "mechanism": "Put the monomorphized run1 body out of line instead of copying it into each class dispatch branch.",
        "expected_token_equivalence": "INFERRED: Rust function bodies and constants are byte-identical after removing inline attributes. Attribute changes do not specify a token algorithm change.",
        "diagnostic": "Measure code-size versus call overhead and loss of constant propagation for skip/lazy/km. Inspect generated symbols before attributing any timing difference.",
    },
    "r4-cpu-run1tai": {
        "constant_changes": {},
        "attributes": {"run1t": ("never", "always")},
        "mechanism": "Inline the small-text run1t engine at its single dispatch call so skip/lazy/skcap/lm are visible constants.",
        "expected_token_equivalence": "INFERRED: Rust function bodies and constants are byte-identical after removing inline attributes. Attribute changes do not specify a token algorithm change.",
        "diagnostic": "Check whether constant propagation removes lazy/skip branches and whether larger parse code offsets any gain. Separate small-text files in paired data.",
    },
    "r4-cpu-commonni": {
        "constant_changes": {},
        "attributes": {"common_from": ("always", "never")},
        "mechanism": "Keep the first 8/16-byte match tests inlined but move the longer-match extension loop out of line.",
        "expected_token_equivalence": "INFERRED: Rust function bodies and constants are byte-identical after removing inline attributes. Attribute changes do not specify a token algorithm change.",
        "diagnostic": "Measure code footprint and extension-heavy file regressions; the extension path frequency and CPU benefit are UNKNOWN without runtime data.",
    },
    "r4-cpu-foldni": {
        "constant_changes": {},
        "attributes": {"fold": ("always", "never"), "fold_bt": ("always", "never")},
        "mechanism": "Keep fold_w's quick reject inline while moving backward token scanning for regular and small-text engines out of line.",
        "expected_token_equivalence": "INFERRED: Rust function bodies and constants are byte-identical after removing inline attributes. Attribute changes do not specify a token algorithm change.",
        "diagnostic": "Measure body duplication and call frequency after the quick word reject. A code-size reduction alone is not evidence of faster total compression.",
    },
    "r4-cpu-stai": {
        "constant_changes": {},
        "attributes": {"run_st": ("never", "always")},
        "mechanism": "Inline the pair-structured binary stride engine into the existing dispatch branch.",
        "expected_token_equivalence": "INFERRED: Rust function bodies and constants are byte-identical after removing inline attributes. Attribute changes do not specify a token algorithm change.",
        "diagnostic": "Separate stride-routed files and check code layout/call overhead. Content routing and stride insertion settings are unchanged.",
    },
    "r4-cpu-x2lazy": {
        "constant_changes": {},
        "attributes": {},
        "source_edits": ["x2lazy"],
        "mechanism": "Read the second pair of eight-byte words in xlen16 only when the first eight bytes agree; retain all extension and tail cases.",
        "expected_token_equivalence": "INFERRED: x2 was used only inside the x==0 branch and the guarded read has no side effects; actual compiled token hashes are UNKNOWN.",
        "diagnostic": "Compare short-match files against long-match files. Removing eager loads can introduce a dependent branch/read latency; generated assembly and paired total time decide.",
    },
    "r4-cpu-flush": {
        "constant_changes": {},
        "attributes": {},
        "source_edits": ["flush"],
        "mechanism": "Use the existing exact-length literal flush in regular run1 instead of the speculative four-write flush4 fast case.",
        "expected_token_equivalence": "INFERRED for the first nt tokens only: flush4's extra writes lie beyond counted tokens and are subsequently overwritten; unused output storage may differ.",
        "diagnostic": "Tests four-store unrolling against exact-length writes and loop cost. Token-count prefix hashes, not the full unused output buffer, define this comparison.",
    },
    "r4-cpu-foldplain": {
        "constant_changes": {},
        "attributes": {},
        "source_edits": ["foldplain"],
        "mechanism": "Use the existing backward fold directly in regular run1, omitting fold_w's speculative word reject.",
        "expected_token_equivalence": "INFERRED from fold_w's upstream shortcut description: it returns unchanged only when fold would stop at its first token. Actual executed hashes are UNKNOWN.",
        "diagnostic": "Tests extra word loads and rejects against the direct token scan. Do not combine with fold outlining before an isolated measurement.",
    },
    "r4-cpu-endreload": {
        "constant_changes": {},
        "attributes": {},
        "source_edits": ["endreload"],
        "mechanism": "Read the regular run1 match-end candidate after recording, removing the early ae read and ahead_fix_m cache validation.",
        "expected_token_equivalence": "INFERRED: ahead_fix_m already reloads unless the early candidate equals the post-recording head; direct post-recording ahead_if_m returns those same current values.",
        "diagnostic": "Tests early load overlap against duplicate reads and cache-validation branches. Keep the one-position main read-ahead unchanged.",
    },
    "r4-cpu-slotonly": {
        "constant_changes": {},
        "attributes": {},
        "source_edits": ["matchslot_helper", "matchslot_call"],
        "proof_edits": ["matchslot_helper"],
        "mechanism": "When regular run1 has a match and lazy=0, prepare only the p+1 slot used for recording; retain the old candidate/word until the match-end reload. Miss and lazy paths retain full next-position loads.",
        "expected_token_equivalence": "INFERRED: the skipped candidate/word is not searched on a lazy=0 match path; the p+1 slot is unchanged and end read-ahead reloads before the next iteration. Actual executed hashes are UNKNOWN.",
        "diagnostic": "Removes candidate-word reads after successful non-lazy probes, but moves probe before next-position preloads. Measure load reduction against branch latency; helper proof and new extraction require validation.",
    },
}

SOURCE_EDITS = {
    "x2lazy": (
        "        let x2 = xor8(s, c + 8, p + 8);\n        let mut y = x;\n        let mut k = 0usize;\n        if x == 0 {\n            y = x2;",
        "        let mut y = x;\n        let mut k = 0usize;\n        if x == 0 {\n            y = xor8(s, c + 8, p + 8);",
    ),
    "flush": (
        "                nt = flush4(input, out, nt, ls, p);",
        "                nt = flush(input, out, nt, ls, p);",
    ),
    "foldplain": (
        "                nt = flush4(input, out, nt, ls, p);\n                let b = fold_w(input, out, nt, p, l, d);",
        "                nt = flush4(input, out, nt, ls, p);\n                let b = fold(input, out, nt, p, l, d);",
    ),
    "endreload": (
        "                let e = p + l;\n                let ae = ahead_if_m::<H>(input, &head, e, lim, pre_slot, pre_c, pre_w, km);",
        "",
    ),
    "endreload_after": (
        "                let a3 = ahead_fix_m::<H>(input, &head, p, lim, e, ae.0, ae.1, ae.2, pre_slot, pre_c, pre_w, km);",
        "                let a3 = ahead_if_m::<H>(input, &head, p, lim, pre_slot, pre_c, pre_w, km);",
    ),
    "matchslot_helper": (
        "/// `ahead_fix` with keys under `km`.",
        "/// Slot-only preparation when a successful non-lazy match will not search i.\n"
        "#[inline(always)]\n"
        "pub fn ahead_slot_m<const H: usize>(s: &[u8], i: usize, lim: usize, a: usize, c: usize, w: u64, km: u32) -> (usize, usize, u64) {\n"
        "    if i < lim {\n"
        "        (slot_of_m::<H>(s, i, km), c, w)\n"
        "    } else {\n"
        "        (a, c, w)\n"
        "    }\n"
        "}\n\n"
        "/// `ahead_fix` with keys under `km`.",
    ),
    "matchslot_call": (
        "            let a1 = ahead_if_m::<H>(input, &head, p + 1, lim, pre_slot, pre_c, pre_w, km);\n"
        "            pre_slot = a1.0;\n            pre_c = a1.1;\n            pre_w = a1.2;\n"
        "            let f = probe_m(input, c, cw, p, km);",
        "            let f = probe_m(input, c, cw, p, km);\n"
        "            let a1 = if lazy == 0 && f.0 >= 3 {\n"
        "                ahead_slot_m::<H>(input, p + 1, lim, pre_slot, pre_c, pre_w, km)\n"
        "            } else {\n"
        "                ahead_if_m::<H>(input, &head, p + 1, lim, pre_slot, pre_c, pre_w, km)\n"
        "            };\n"
        "            pre_slot = a1.0;\n            pre_c = a1.1;\n            pre_w = a1.2;",
    ),
}

PROOF_EDITS = {
    "matchslot_helper": (
        "/-- `ahead_fix_m`: the read-ahead",
        "/-- Slot-only preparation preserves the supplied candidate/word and gives a valid slot. -/\n"
        "@[local step]\n"
        "theorem ahead_slot_m_spec (H : Std.Usize) (s : Slice Std.U8)\n"
        "    (i lim a c : Std.Usize) (w : Std.U64) (km : Std.U32)\n"
        "    (hlim : lim.val + 8 = s.length) (ha : a.val < H.val)\n"
        "    (hc : c.val ≤ i.val) (hw : w.val = word8 s c.val) (hH : 0 < H.val) :\n"
        "    slot.ahead_slot_m H s i lim a c w km ⦃ fun r => r.1.val < H.val ∧\n"
        "      r.2.1.val ≤ i.val ∧ r.2.2.val = word8 s r.2.1.val ⦄ := by\n"
        "  rw [slot.ahead_slot_m]\n"
        "  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s\n"
        "  step*\n\n"
        "/-- `ahead_fix_m`: the read-ahead",
    ),
}


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def edit_attribute(text, function, old, new):
    pattern = rf"#\[inline\({old}\)\](\s*pub fn {function}(?:<|\())"
    text, count = re.subn(pattern, rf"#[inline({new})]\g<1>", text)
    if count != 1:
        raise AssertionError(f"{function}: expected one {old} attribute, got {count}")
    return text


def build(base, name, spec):
    text = base["parse.rs"].decode("utf-8")
    for key, (old, new) in spec["constant_changes"].items():
        text, count = re.subn(
            rf"(pub const {key}: usize = ){old};", rf"\g<1>{new};", text
        )
        if count != 1:
            raise AssertionError(f"{key}: expected one constant, got {count}")
    for function, (old, new) in spec["attributes"].items():
        text = edit_attribute(text, function, old, new)
    source_edits = list(spec.get("source_edits", []))
    if "endreload" in source_edits:
        source_edits.append("endreload_after")
    for edit in source_edits:
        before, after = SOURCE_EDITS[edit]
        if text.count(before) != 1:
            raise AssertionError(f"{edit}: expected one source anchor")
        text = text.replace(before, after, 1)

    # Attribute-only candidates must change no Rust body, signature, or constant.
    if not spec["constant_changes"] and not source_edits:
        strip = lambda x: re.sub(r"#\[inline\((?:always|never)\)\]", "", x)
        assert strip(text) == strip(base["parse.rs"].decode("utf-8"))
    proof_edits = spec.get("proof_edits", [])
    proof = base["Parse.lean"].decode("utf-8")
    for edit in proof_edits:
        before, after = PROOF_EDITS[edit]
        if proof.count(before) != 1:
            raise AssertionError(f"{edit}: expected one proof anchor")
        proof = proof.replace(before, after, 1)
    files = {"parse.rs": text.encode("utf-8"), "Parse.lean": proof.encode("utf-8")}
    manifest = {
        "candidate": name,
        "base_candidate": "r3-432-fast3",
        "base_path": BASE.relative_to(ROOT).as_posix(),
        "base_submission_id": "432",
        "base_hashes": BASE_HASHES,
        "change": {
            "constants": {k: {"old": a, "new": b} for k, (a, b) in spec["constant_changes"].items()},
            "inline_attributes": {k: {"old": a, "new": b} for k, (a, b) in spec["attributes"].items()},
            **({"source_edits": source_edits} if source_edits else {}),
            **({"proof_edits": proof_edits} if proof_edits else {}),
        },
        "mechanism": spec["mechanism"],
        "expected_token_equivalence": spec["expected_token_equivalence"],
        "actual_token_equivalence": "UNKNOWN: no execution or corpus token comparison in this generator",
        "proof": {
            "mode": ("Baseline proof plus a local-step helper lemma; new official extraction, Lean obligation, and axiom audit required"
                     if proof_edits else "Byte-for-byte copied from the baseline; new official extraction, Lean obligation, and axiom audit required"),
            "sha256": sha256(files["Parse.lean"]),
            "fresh_gate": "UNKNOWN",
        },
        "diagnostic": spec["diagnostic"],
        "hashes": {n: sha256(v) for n, v in files.items()},
        "attribution": {
            "source": "Officially published submission 432, then r3-432-fast3 constants",
            "reference": "references/round3-public-432/PROVENANCE.md",
            "public_miner_hotkey": "5EAM7rJK571o7asrBBk6oozUZCRubR1tMiDKBNWmWhw66PRy",
            "named_author": "UNKNOWN: official snapshot/source exposes no name",
            "ownership": "Derivative of external public miner code; not an independent parser algorithm",
        },
        "scope": "Research candidate only; total paired compression, round trip, token hashes, fresh public gate, independent-runner reproduction, private stage2 and official admission are separate checks",
        "cpu_gain": "UNKNOWN",
        "formal_submission_sent": False,
    }
    files["manifest.json"] = (json.dumps(manifest, indent=2, ensure_ascii=False) + "\n").encode("utf-8")
    return files, manifest


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    base = {n: (BASE / n).read_bytes() for n in BASE_HASHES}
    for name, expected in BASE_HASHES.items():
        observed = sha256(base[name])
        if observed != expected:
            raise AssertionError(f"Baseline drift: {name}: {observed} != {expected}")
    for name, spec in VARIANTS.items():
        files, manifest = build(base, name, spec)
        dest = ROOT / "candidates" / name
        if args.check:
            for filename, data in files.items():
                if (dest / filename).read_bytes() != data:
                    raise AssertionError(f"Generated bytes differ: {name}/{filename}")
        else:
            dest.mkdir(exist_ok=True)
            for filename, data in files.items():
                (dest / filename).write_bytes(data)
        print(name, manifest["hashes"]["parse.rs"])


if __name__ == "__main__":
    main()
