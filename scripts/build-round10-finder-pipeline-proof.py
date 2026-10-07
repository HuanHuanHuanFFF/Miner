"""Bounded31-state totality bridge for the frozen D insertion pipeline.

Reuse existing DP cache-bound contracts; no universal token equivalence theorem,
axiom, sorry, weakened obligation, Rust change or CI dispatch is introduced.
Native Lean compilation remains pending after this interface-bound assembly.
"""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r10-finder-pipeline"
RECORD = ROOT / "candidates/r10-record-nonempty"
NAME = "r10-finder-pipeline-proof"
RUST_SHA = "b74ae5fd9575101b6b34b9f2718d8835adca770c6765c30b33bb895878ba1adf"
PROOF_SHA = "86cfc36adb009970bccbb5a9c543c5f559148d729e8c0f041934aab44e95592d"
FUNS = ROOT / "evidence/round10/37695964878/restore-h/extraction/r10-finder-pipeline/Funs.lean"
FUNS_SHA = "5b6803aa4a3a092dc3f0cdfc8770b2717e66d0ac7e766ecf1a6fcf707cd4e1e9"


def sha(raw: bytes) -> str:
    return hashlib.sha256(raw).hexdigest()


def once(s: str, before: str, after: str) -> str:
    if s.count(before) != 1:
        raise ValueError(f"Expected one proof anchor ({s.count(before)}): {before[:100]}")
    return s.replace(before, after, 1)


def append_tuple(s: str, prefix: str, values: list[str]) -> str:
    a = s.index(prefix) + len(prefix); b = s.index(")", a)
    return s[:b] + ", " + ", ".join(values) + s[b:]


def port(proof: str) -> tuple[str, dict]:
    a = proof.index("@[local step]\ntheorem d_parse_loop_spec")
    b = proof.index("@[local step]\ntheorem d_parse_spec", a)
    c = proof.index("@[local step]\ntheorem d_plan_k_loop_spec", b)
    old_loop = proof[a:b]; old_wrapper = proof[b:c]; loop = old_loop; wrapper = old_wrapper
    loop = once(loop,
        "(s next_upd : Std.Usize) (cands pc) (pn ppos cl cd : Std.Usize) (cdc : Std.U32) (i anchor alen : Std.Usize)",
        """(s next_upd : Std.Usize) (cands pc) (pn ppos cl cd : Std.Usize) (cdc : Std.U32) (i anchor alen : Std.Usize)
    (b8 : Std.U64) (x3 x4 x7 : Std.Usize) (pre : Std.Usize × Std.Usize × Std.Usize)""")
    loop = once(loop,
        "(h3 : LeAll head3.val i.val) (h4 : LeAll head4.val i.val) (h7 : LeAll head7.val i.val) :",
        """(h3 : LeAll head3.val i.val) (h4 : LeAll head4.val i.val) (h7 : LeAll head7.val i.val)
    (hc3 : pre.1.val ≤ i.val) (hc4 : pre.2.1.val ≤ i.val) (hc7 : pre.2.2.val ≤ i.val) :""")
    loop = once(loop, "cl cd cdc i anchor alen ⦃ fun _ => True ⦄", "cl cd cdc i anchor alen b8 x3 x4 x7 pre ⦃ fun _ => True ⦄")
    loop = append_tuple(loop, "(measure := fun (", ["_"] * 5)
    loop = append_tuple(loop, "(inv := fun (", ["_", "_", "_", "_", "pre'"])
    loop = once(loop, "       LeAll h7'.val i'.val)",
        "       LeAll h7'.val i'.val ∧ pre'.1.val ≤ i'.val ∧ pre'.2.1.val ≤ i'.val ∧ pre'.2.2.val ≤ i'.val)")
    loop = once(loop, "ppos', cl', cd', cdc', i', anc', alen'⟩ ⟨hs', hi', hcl', hh3, hh4, hh7⟩",
        """ppos', cl', cd', cdc', i', anc', alen', b8', x3', x4', x7', c3, c4, c7⟩
      ⟨hs', hi', hcl', hh3, hh4, hh7, hq1, hq2, hq3⟩
    have hq1 : c3.val ≤ i'.val := hq1
    have hq2 : c4.val ≤ i'.val := hq2
    have hq3 : c7.val ≤ i'.val := hq3""")
    loop = once(loop, "clear hsi hin hcl h3 h4 h7", "clear hsi hin hcl h3 h4 h7 hc3 hc4 hc7")
    loop = once(loop, "      anchor alen\n", "      anchor alen b8 x3 x4 x7 pre\n")
    old_start = loop.index("    refine d3_bind (be8_spec _ _ (by clear * - hiM; omega))")
    old_end = loop.index("    refine d3_rem (b := 8192)", old_start)
    original_setup = loop[old_start:old_end]
    new_setup = """    refine d3_bind (dp_store_spec _ _ _ _ _ _ _ _ _ _ _ i'.val hh3 hh4 hh7 (le_refl _)) ?_
    rintro ⟨head31, head41, prev41, head71, prev71⟩ ⟨hL3, hL4, hL7⟩
    have hL3 : LeAll head31.val i'.val := hL3
    have hL4 : LeAll head41.val i'.val := hL4
    have hL7 : LeAll head71.val i'.val := hL7
    iterate 4 refine d3_unc ?_
    have hw1 : (core.num.Usize.wrapping_add i' 1#usize).val = i'.val + 1 :=
      lc_wadd1 i' (by clear * - hiM; omega)
    refine d3_bind (be8_spec _ _ (by rw [hw1]; clear * - hiM; omega)) ?_; intro b8n _
    refine d3_bind (hashes_spec _ _) ?_; rintro ⟨nx3, nx4, nx7⟩ _
    iterate 2 refine d3_unc ?_
    refine d3_bind (dp_heads_spec _ _ _ _ _ _ i'.val hL3 hL4 hL7) ?_; intro next_pre hpn
    have hn1 : next_pre.1.val ≤ i'.val := hpn.1
    have hn2 : next_pre.2.1.val ≤ i'.val := hpn.2.1
    have hn3 : next_pre.2.2.val ≤ i'.val := hpn.2.2
    clear hpn
"""
    loop = loop[:old_start] + new_setup + loop[old_end:]
    # Add only the actual branch-local jumped result; no assertion about its value.
    loop = once(loop, "Std.U32 × Std.Usize × Std.Usize × Std.Usize) =>", "Std.U32 × Std.Usize × Std.Usize × Std.Usize × Bool) =>")
    loop = once(loop, "cl1, _, _, i12, _, _) =>", "cl1, _, _, i12, _, _, _) =>")
    loop = once(loop, "Array Std.U32 320#usize × Array Std.U32 32#usize × Std.Usize × Std.Usize × Std.Usize) =>",
        "Array Std.U32 320#usize × Array Std.U32 32#usize × Std.Usize × Std.Usize × Std.Usize × Bool) =>")
    loop = once(loop, "| (_, g3, g4, _, g7, _, _, _, _, _, s1, cl1, i12) =>", "| (_, g3, g4, _, g7, _, _, _, _, _, s1, cl1, i12, _) =>")
    loop = once(loop, "rintro ⟨v, a, a1, a2, a3, a4, a5, a6, a7, a8, i21, i22, i23⟩", "rintro ⟨v, a, a1, a2, a3, a4, a5, a6, a7, a8, i21, i22, i23, b2⟩")
    loop = once(loop, "iterate 12 refine d3_unc ?_", "iterate 13 refine d3_unc ?_")
    loop = once(loop, "cl1, cd1, cdc1, i12, anchor1, alen1⟩", "cl1, cd1, cdc1, i12, anchor1, alen1, jumped⟩")
    loop = once(loop, "iterate 21 refine d3_unc ?_", "iterate 22 refine d3_unc ?_")
    refresh_anchor = "    refine d3_sub rfl rfl hs1 ?_; intro i13 _\n"
    refresh = """    refine d3_bind (Q := fun (x : Std.U64 × Std.Usize × Std.Usize × Std.Usize × (Std.Usize × Std.Usize × Std.Usize)) =>
        x.2.2.2.2.1.val ≤ i12.val ∧ x.2.2.2.2.2.1.val ≤ i12.val ∧ x.2.2.2.2.2.2.val ≤ i12.val) ?_ ?_
    · apply dp_ite_spec <;> intro _
      · refine d3_bind (be8_spec _ _ (by clear * - h12M; omega)) ?_; intro b82 _
        refine d3_bind (hashes_spec _ _) ?_; rintro ⟨rx3, rx4, rx7⟩ _
        iterate 2 refine d3_unc ?_
        refine d3_bind (dp_heads_spec _ _ _ _ _ _ i12.val hk3 hk4 hk7) ?_; intro fresh_pre hpre2
        exact d3_ok hpre2
      · exact d3_ok ⟨Nat.le_trans hn1 (Nat.le_of_lt hii), Nat.le_trans hn2 (Nat.le_of_lt hii),
          Nat.le_trans hn3 (Nat.le_of_lt hii)⟩
    rintro ⟨b81, px3, px4, px7, pre1⟩ ⟨hp1, hp2, hp3⟩
    iterate 4 refine d3_unc ?_
"""
    loop = once(loop, refresh_anchor, refresh + refresh_anchor)
    loop = loop.replace("⟨⟨hs2, hin1, hcl1, hk3, hk4, hk7⟩, hms⟩", "⟨⟨hs2, hin1, hcl1, hk3, hk4, hk7, hp1, hp2, hp3⟩, hms⟩")
    loop = once(loop, "exact ⟨hsi, hin, hcl, h3, h4, h7⟩", "exact ⟨hsi, hin, hcl, h3, h4, h7, hc3, hc4, hc7⟩")
    init_anchor = "  refine d3_bind (d_parse_loop_spec (hn := hl)"
    init = """  refine d3_bind (be8_spec _ _ (by show 0 + 8 ≤ Std.Usize.max; clear * - hM; omega)) ?_; intro b8 _
  refine d3_bind (hashes_spec _ _) ?_; rintro ⟨x3, x4, x7⟩ _
  iterate 2 refine d3_unc ?_
  refine d3_bind (dp_heads_spec _ _ _ _ _ _ 0
    (dp_LeAll_repeat _ _ _ (Nat.le_refl _))
    (dp_LeAll_repeat _ _ _ (Nat.le_refl _))
    (dp_LeAll_repeat _ _ _ (Nat.le_refl _))) ?_; intro pre hpre
"""
    wrapper = once(wrapper, init_anchor, init + init_anchor)
    wrapper = once(wrapper, "(h7 := dp_LeAll_repeat _ _ _ (Nat.le_refl _)) ..)",
        "(h7 := dp_LeAll_repeat _ _ _ (Nat.le_refl _))\n    (hc3 := hpre.1) (hc4 := hpre.2.1) (hc7 := hpre.2.2) ..)")
    changed = proof[:a] + loop + wrapper + proof[c:]
    audit = {"original_loop_sha256":sha(old_loop.encode()),"ported_loop_sha256":sha(loop.encode()),
        "original_wrapper_sha256":sha(old_wrapper.encode()),"ported_wrapper_sha256":sha(wrapper.encode()),
        "reused_proven_pattern":"dp_parse_loop_spec current store/prefetch and jump refresh; dp_parse_spec initialization",
        "changes_only":"d_parse_loop_spec and d_parse_spec; no new helper theorem, axiom, sorry or contract statement",
        "prefix_and_final_proof_suffix_identical":changed[:a]==proof[:a] and changed[changed.index("@[local step]\ntheorem d_plan_k_loop_spec"):]==proof[c:],
        "loop_function_components":31,"invariant_additions":["cached pre.1<=i","cached pre.2.1<=i","cached pre.2.2<=i"],
        "semantic_scope":"Planner totality and capped-probe bounds; no universal token equivalence theorem",
        "original_setup_replaced_sha256":sha(original_setup.encode())}
    return changed,audit


def generate() -> dict[str,bytes]:
    rust=(BASE/"parse.rs").read_bytes();proof=(RECORD/"Parse.lean").read_bytes();funs=FUNS.read_bytes()
    if sha(rust)!=RUST_SHA or sha(proof)!=PROOF_SHA or sha(funs)!=FUNS_SHA:raise ValueError("Frozen source/proof/extraction changed")
    interface=json.loads((BASE/"interface-audit.json").read_text(encoding="utf-8"))
    if interface["loop_state_component_count"]!=31 or interface["extraction"]["files"]["Funs.lean"]["sha256"]!=FUNS_SHA:raise ValueError("Actual pipeline interface audit differs")
    lean,audit=port(proof.decode("utf-8"));files={"parse.rs":rust,"Parse.lean":lean.encode("utf-8")}
    if not all(0<len(v)<=524288 for v in files.values()):raise ValueError("Per-file size boundary exceeded")
    manifest=json.loads((BASE/"manifest.json").read_text(encoding="utf-8"));manifest.update(candidate=NAME,parent="candidates/r10-finder-pipeline",parent_hashes={"parse.rs":RUST_SHA,"Parse.lean":PROOF_SHA},hashes={n:sha(v) for n,v in files.items()},bytes={n:len(v) for n,v in files.items()},
        proof_status="UNCOMPILED_ACTUAL_31STATE_TOTALITY_BRIDGE: reuse existing DP cache-bound proof; original obligation/axioms/full public round trip NOT_RUN for this exact package",
        equivalence_status="VERIFIED_FINITE_RESTORE_H for exact unchanged Rust: run37695964878 passed444 native token/decode cases versus record-nonempty and all28 public token/output identities. Not universal token equivalence; this new Lean draft remains uncompiled.",
        performance_status="MEASURED_PUBLIC_SMALL_UNCONFIRMED_SIGNAL: restore-h paired total time versus record is-0.222957519%/-0.412390392%, mean-0.317673956%, with identical public size. No independent confirmation or new-frontier claim; confirm run pending.",
        performance_evidence={"run_id":"37695964878","receipt":"evidence/round10/37695964878/restore-h/gate","time_change_pct_vs_record":[-0.22295751931866725,-0.4123903922774619],"mean_pct":-0.31767395579806457,"public_size_delta_pp":0.0,"native_cases":444,"different_or_failed":0,"independent_confirmation":"PENDING"},
        allocation_decision="One bounded20-minute confirmation preparation after the same-byte small signal; not frontier promotion or an unlimited proof repair cycle",
        proof_scope="D planner totality only; retained checked-emitter theorem unchanged. This is not an all-input token-equivalence proof.",
        extraction_interface={"run_id":"37695964878","Funs.lean_sha256":FUNS_SHA,"loop_components":31})
    files["manifest.json"]=(json.dumps(manifest,indent=2,ensure_ascii=False)+"\n").encode()
    audit.update(status="VERIFIED_LOCAL_SOURCE_INTERFACE_PORT_ONLY_UNCOMPILED",Rust_sha256=RUST_SHA,Lean_sha256=sha(files["Parse.lean"]),actual_Funs_sha256=FUNS_SHA,native_Lean="NOT_RUN",original_obligation="UNCHANGED_NOT_RUN",allowed_axioms="UNCHANGED_NOT_RUN")
    files["proof-port-audit.json"]=(json.dumps(audit,indent=2,ensure_ascii=False)+"\n").encode()
    files["interface-audit.json"]=(BASE/"interface-audit.json").read_bytes()
    return files


def main() -> None:
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument("--check",action="store_true");args=parser.parse_args();files=generate();target=ROOT/"candidates"/NAME
    if args.check:
        if not all((target/n).read_bytes()==v for n,v in files.items()):raise ValueError("Proof bridge reconstruction differs")
    else:
        target.mkdir(exist_ok=True)
        for n,v in files.items():
            path=target/n
            if path.exists() and path.read_bytes()!=v:raise ValueError(f"Preserve existing independent proof {path}")
            path.write_bytes(v)
    print(json.dumps({"candidate":NAME,"hashes":json.loads(files["manifest.json"])["hashes"],"proof_status":"UNCOMPILED_ACTUAL31STATE_TOTALITY_BRIDGE"}))


if __name__=="__main__":main()
