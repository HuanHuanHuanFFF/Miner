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
    "r4-cpu-flushzero": {
        "constant_changes": {},
        "attributes": {},
        "source_edits": ["flushzero"],
        "proof_edits": ["flushzero"],
        "proof_mode": "Baseline proof plus a zero-literal return case in flush4_spec; new official extraction, Lean obligation, and axiom audit required",
        "mechanism": "Return immediately when flush4 has zero pending literals, preserving its existing four-literal SIMD-friendly path for nonempty short runs.",
        "expected_token_equivalence": "INFERRED for the counted prefix: the removed four speculative writes occur beyond nt when from==to; counted tokens and subsequent parse state are unchanged.",
        "diagnostic": "Base screen assembly at fc9a/fcb6/fcbb/fcbf/fcc8 performs a four-byte load, two unpacks and a 16-byte store for pending<=4 without a zero test. This deletes that work only for empty literal runs; paired benefit remains UNKNOWN.",
    },
    "r4-cpu-classoutline": {
        "constant_changes": {},
        "attributes": {},
        "source_edits": ["classoutline_helpers", "classoutline_text_hn", "classoutline_text_hs", "classoutline_prose_hn", "classoutline_prose_hs"],
        "proof_edits": ["classoutline_helpers", "classoutline_parse"],
        "proof_mode": "Baseline proof plus two wrapper lemmas and parse dispatch alternatives; new official extraction, Lean obligation, and axiom audit required",
        "mechanism": "Outline only the text and prose run1 class calls behind separate noinline wrappers, with the always-inline run1 body and all settings constant inside each wrapper.",
        "expected_token_equivalence": "INFERRED: wrappers call the same run1 instantiations with byte-identical constants. Other dispatch routes and all parser bodies remain unchanged.",
        "diagnostic": "Actual run1ni assembly loses per-class constant specialization: HN loads km/lazy from stack and uses runtime skip shifts, while common public text parser times rise 25-43%. This candidate keeps class constants visible while testing outline code footprint; new emitted assembly must confirm specialization.",
    },
    "r4-cpu-directemit": {
        "constant_changes": {},
        "attributes": {},
        "source_edits": ["directemit"],
        "proof_edits": ["directemit_helpers", "directemit_bounds", "directemit_comment"],
        "proof_mode": "Baseline MatchAt call-site proofs plus wrapping-u32 packing specs; new extraction/Lean must validate every input path, not just the public corpus",
        "expected_equivalent": True,
        "mechanism": "Directly emit the canonical packed match token under the existing proven MatchAt precondition, deleting put_match's repeated runtime range/fallback tests. Safe out indexing and position/count advances remain.",
        "expected_token_equivalence": "INFERRED for parse inputs satisfying the obligation: every put_match call is specified with a real in-range MatchAt. The invalid-argument behavior of this internal helper changes; no all-input theorem is claimed before fresh Lean acceptance.",
        "diagnostic": "Base assembly at 11705-1172d repeats output-position, length and distance bounds before packing at 11738-1174a. Check that these branches disappear; then require exact public/synthetic tokens and round trip, paired total time, and all-call-site fresh gate.",
    },
    "r4-cpu-hash32": {
        "constant_changes": {},
        "attributes": {},
        "source_edits": ["hash32"],
        "expected_equivalent": False,
        "mechanism": "Use a 32-bit immediate multiplicative hash in regular run1's slot_of_m instead of its 64-bit multiplicative high-bit hash; table cardinality, content dispatch and search policy are fixed.",
        "expected_token_equivalence": "NOT_EXPECTED: bucket collisions and retained candidates change. Actual token/output changes and paired compression cost must be measured independently.",
        "diagnostic": "Base assembly keeps a 64-bit golden-ratio constant in a register and uses imul plus a 49-bit shift per slot. A 32-bit imul immediate can reduce instruction/register cost; collision quality and total speed are UNKNOWN. Original slot_of for run1t and insert for the chain engine are retained controls.",
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
    "flushzero": (
        "pub fn flush4(input: &[u8], out: &mut [u32], nt0: usize, from: usize, to: usize) -> usize {\n    if from <= to",
        "pub fn flush4(input: &[u8], out: &mut [u32], nt0: usize, from: usize, to: usize) -> usize {\n    if from == to {\n        nt0\n    } else if from <= to",
    ),
    "classoutline_helpers": (
        "/// The class itself when `parse` gives class `cls` to `run1` (R1_ON, no stride recording, and one",
        "/// Separate class kernels retain constant settings while keeping the main dispatch smaller.\n"
        "#[inline(never)]\n"
        "pub fn run1_text<const H: usize>(input: &[u8], out: &mut [u32]) -> usize {\n"
        "    run1::<H>(input, out, T_SKIP, T_LAZY, SKCAP, 4294967295)\n"
        "}\n\n"
        "#[inline(never)]\n"
        "pub fn run1_prose<const H: usize>(input: &[u8], out: &mut [u32]) -> usize {\n"
        "    run1::<H>(input, out, P_SKIP, P_LAZY, SKCAP, P_KM)\n"
        "}\n\n"
        "/// The class itself when `parse` gives class `cls` to `run1` (R1_ON, no stride recording, and one",
    ),
    "classoutline_text_hn": ("run1::<HN>(input, out, T_SKIP, T_LAZY, SKCAP, 4294967295)", "run1_text::<HN>(input, out)"),
    "classoutline_text_hs": ("run1::<HS>(input, out, T_SKIP, T_LAZY, SKCAP, 4294967295)", "run1_text::<HS>(input, out)"),
    "classoutline_prose_hn": ("run1::<HN>(input, out, P_SKIP, P_LAZY, SKCAP, P_KM)", "run1_prose::<HN>(input, out)"),
    "classoutline_prose_hs": ("run1::<HS>(input, out, P_SKIP, P_LAZY, SKCAP, P_KM)", "run1_prose::<HS>(input, out)"),
    "directemit": (
        "/// Emit a match (re-checked when VERIFY = 1), else a literal. Returns (tokens, next position).\n"
        "#[inline(always)]\n"
        "pub fn put_match(s: &[u8], out: &mut [u32], nt: usize, p: usize, d: usize, l: usize) -> (usize, usize) {\n"
        "    let n = s.len();\n"
        "    if d >= 1 && d <= 32768 && d <= p && l >= 3 && l <= 258 && p < n && l <= n - p && (VERIFY == 0 || same(s, p - d, p, l) == 1) {\n"
        "        out[nt] = 16777216u32 + ((d - 1) as u32) * 256 + ((l - 3) as u32);\n"
        "        (nt + 1, p + l)\n"
        "    } else {\n"
        "        out[nt] = s[p] as u32;\n"
        "        (nt + 1, p + 1)\n"
        "    }\n"
        "}",
        "/// Canonical match packing; its caller proves 1<=d<=32768 and 3<=l<=258.\n"
        "#[inline(always)]\n"
        "pub fn pack_match(d: usize, l: usize) -> u32 {\n"
        "    (d as u32).wrapping_mul(256).wrapping_add(l as u32).wrapping_add(16776957)\n"
        "}\n\n"
        "/// Emit under the proven MatchAt precondition; no repeated fallback range tests.\n"
        "#[inline(always)]\n"
        "pub fn put_match(s: &[u8], out: &mut [u32], nt: usize, p: usize, d: usize, l: usize) -> (usize, usize) {\n"
        "    out[nt] = pack_match(d, l);\n"
        "    (nt + 1, p + l)\n"
        "}",
    ),
    "hash32": (
        "pub fn slot_of_m<const H: usize>(s: &[u8], i: usize, km: u32) -> usize {\n"
        "    let k = (be4(s, i) & km) as u64;\n"
        "    (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (64 - HB)) as usize % H\n"
        "}",
        "pub fn slot_of_m<const H: usize>(s: &[u8], i: usize, km: u32) -> usize {\n"
        "    let k = be4(s, i) & km;\n"
        "    (k.wrapping_mul(0x9E37_79B9) >> (32 - HB)) as usize % H\n"
        "}",
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
    "flushzero": (
        "  rw [slot.flush4]\n  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input\n  step*\n  all_goals first\n",
        "  rw [slot.flush4]\n  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input\n  step*\n  all_goals first\n"
        "    | (refine ⟨?_, rfl⟩\n       convert hdec using 1 <;> scalar_tac)\n",
    ),
    "classoutline_helpers": (
        "/-! ## 15g. The E paths:",
        "@[local step]\n"
        "theorem run1_text_spec (H : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32)\n"
        "    (hlen : input.length ≤ out.length) (hH : 0 < H.val) :\n"
        "    slot.run1_text H input out ⦃ fun r => r.1.val ≤ input.length ∧\n"
        "      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by\n"
        "  rw [slot.run1_text]\n"
        "  exact run1_spec _ input out _ _ _ _ hlen hH (by simp)\n\n"
        "@[local step]\n"
        "theorem run1_prose_spec (H : Std.Usize) (input : Slice Std.U8) (out : Slice Std.U32)\n"
        "    (hlen : input.length ≤ out.length) (hH : 0 < H.val) :\n"
        "    slot.run1_prose H input out ⦃ fun r => r.1.val ≤ input.length ∧\n"
        "      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by\n"
        "  rw [slot.run1_prose]\n"
        "  exact run1_spec _ input out _ _ _ _ hlen hH (by simp)\n\n"
        "/-! ## 15g. The E paths:",
    ),
    "classoutline_parse": (
        "      | exact run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)",
        "      | exact run1_text_spec _ input out hlen (by simp)\n"
        "      | exact run1_prose_spec _ input out hlen (by simp)\n"
        "      | exact run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)",
    ),
    "directemit_helpers": (
        "/-- With `VERIFY = 0` and a real match, `put_match` writes the match token. -/",
        "/-- Wrapping u32 addition is ordinary addition when its inputs fit. -/\n"
        "@[local step]\n"
        "theorem cpu_wadd_u32_spec (x y : Std.U32) :\n"
        "    lift (core.num.U32.wrapping_add x y) ⦃ fun z => z = core.num.U32.wrapping_add x y ∧\n"
        "      (x.val + y.val ≤ U32.max → z.val = x.val + y.val) ⦄ := by\n"
        "  simp only [lift, Std.WP.spec_ok, true_and]\n"
        "  intro h\n"
        "  rw [core.num.U32.wrapping_add_val_eq]\n"
        "  apply Nat.mod_eq_of_lt\n"
        "  scalar_tac\n\n"
        "/-- Wrapping u32 multiplication is ordinary multiplication when its inputs fit. -/\n"
        "@[local step]\n"
        "theorem cpu_wmul_u32_spec (x y : Std.U32) :\n"
        "    lift (core.num.U32.wrapping_mul x y) ⦃ fun z => z = core.num.U32.wrapping_mul x y ∧\n"
        "      (x.val * y.val ≤ U32.max → z.val = x.val * y.val) ⦄ := by\n"
        "  simp only [lift, Std.WP.spec_ok, true_and]\n"
        "  intro h\n"
        "  rw [core.num.U32.wrapping_mul_val_eq]\n"
        "  apply Nat.mod_eq_of_lt\n"
        "  scalar_tac\n\n"
        "/-- Direct packing equals the contract's match token on every legal match. -/\n"
        "@[local step]\n"
        "theorem pack_match_spec (d l : Std.Usize) (hd1 : 1 ≤ d.val) (hd32 : d.val ≤ 32768)\n"
        "    (hl3 : 3 ≤ l.val) (hl258 : l.val ≤ 258) :\n"
        "    slot.pack_match d l ⦃ fun r => r.val = LZ77.mkMatch d.val l.val ⦄ := by\n"
        "  rw [slot.pack_match]\n"
        "  step*\n"
        "  simp only [LZ77.mkMatch, LZ77.MATCH_BASE]\n"
        "  scalar_tac\n\n"
        "/-- With a real MatchAt, direct put_match writes the canonical match token. -/",
    ),
    "directemit_comment": (
        "  -- only the `VERIFY = 0`, all-checks-pass branch is left: the others contradict `MatchAt`",
        "  -- MatchAt supplies all bounds; pack_match_spec supplies the canonical token value.",
    ),
    "directemit_bounds": (
        "  rw [slot.put_match]\n  have hm' := hm",
        "  rw [slot.put_match]\n"
        "  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s\n"
        "  have hdec' := hdec\n"
        "  obtain ⟨hp_bound, hnt_bound, hout_bound, _⟩ := hdec'\n"
        "  have hm' := hm",
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
        **({"expected_equivalent": spec["expected_equivalent"]} if "expected_equivalent" in spec else {}),
        "actual_token_equivalence": "UNKNOWN: no execution or corpus token comparison in this generator",
        "proof": {
            "mode": spec.get("proof_mode", "Baseline proof plus a local-step helper lemma; new official extraction, Lean obligation, and axiom audit required"
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
    ap.add_argument("--only", nargs="+", choices=list(VARIANTS), help="Generate/check named candidates without rewriting frozen files")
    args = ap.parse_args()
    base = {n: (BASE / n).read_bytes() for n in BASE_HASHES}
    for name, expected in BASE_HASHES.items():
        observed = sha256(base[name])
        if observed != expected:
            raise AssertionError(f"Baseline drift: {name}: {observed} != {expected}")
    for name in args.only or VARIANTS:
        spec = VARIANTS[name]
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
