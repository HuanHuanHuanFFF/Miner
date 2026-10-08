"""Assemble an unverified R10 forward totality bridge without altering screen files.

Fresh extraction is the authority for loop signatures. This initial draft uses
the original d_parse search proof between the retained search-call boundaries.
"""
from pathlib import Path
import argparse
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r10-forward-seed"
DEST = ROOT / "candidates/r10-forward-seed-proof"
EXTRACT = ROOT / "evidence/round10/37679261323/explore-a/extraction"

COLLECT_HEADER = r'''
@[local step]
theorem d_collect_loop_spec (input : Slice Std.U8) (rs)
    (ct lazyn d4 d7 skip h3d tbmax lz2max dupmode d7l d7e nice n : Std.Usize)
    (head3 : Array Std.U32 16384#usize) (head4 : Array Std.U32 65536#usize) (prev4)
    (head7 : Array Std.U32 65536#usize) (prev7) (lim : Std.Usize) (sh7 : Std.U32)
    (cands pc) (pn ppos cl cd i anchor alen : Std.Usize)
    (hn : n.val = input.length) (hlim : lim.val + 8 = n.val)
    (hN : input.length + input.length ≤ Std.Usize.max)
    (hin : i.val ≤ n.val) (hcl : cl.val < 512)
    (h3 : LeAll head3.val i.val) (h4 : LeAll head4.val i.val) (h7 : LeAll head7.val i.val) :
    slot.d_collect_loop input rs ct lazyn d4 d7 skip h3d tbmax lz2max dupmode d7l d7e nice n
      head3 head4 prev4 head7 prev7 lim sh7 cands pc pn ppos cl cd i anchor alen ⦃ fun _ => True ⦄ := by
  have hS := dp_size hN
  rw [slot.d_collect_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, _, _, _, _, i', _, _) => lim.val - i'.val)
    (inv := fun (_, h3', h4', _, h7', _, _, _, _, _, cl', _, i', _, _) =>
      i'.val ≤ n.val ∧ cl'.val < 512 ∧ LeAll h3'.val i'.val ∧ LeAll h4'.val i'.val ∧ LeAll h7'.val i'.val)
  · rintro ⟨rs', h3', h4', p4', h7', p7', cands', pc', pn', ppos', cl', cd', i', anc', alen'⟩
      ⟨hi', hcl', hh3, hh4, hh7⟩
    clear hin hcl h3 h4 h7 rs head3 head4 prev4 head7 prev7 cands pc pn ppos cl cd i anchor alen
    simp only [slot.d_collect_loop.body, lift, bind_tc_ok]
    apply dp_ite_spec <;> intro hlt
    swap
    · exact d3_ok trivial
    have hlt' : i'.val < lim.val := (UScalar.lt_equiv _ _).mp hlt
    have hiM : i'.val + 2147483648 ≤ Std.Usize.max := by clear * - hi' hn hS; omega
    refine d3_bind (be8_spec _ _ (by clear * - hiM; omega)) ?_; intro b8 _
    refine d3_bind (insert_pos_spec _ _ _ _ _ _ _ _ i'.val hh3 hh4 hh7 (le_refl _)) ?_
    rintro ⟨⟨c3, c4, c7⟩, head31, head41, prev41, head71, prev71⟩ ⟨hq1, hq2, hq3, hL3, hL4, hL7⟩
    have hq1 : c3.val ≤ i'.val := hq1
    have hq2 : c4.val ≤ i'.val := hq2
    have hq3 : c7.val ≤ i'.val := hq3
    have hL3 : LeAll head31.val i'.val := hL3
    have hL4 : LeAll head41.val i'.val := hL4
    have hL7 : LeAll head71.val i'.val := hL7
    iterate 5 refine d3_unc ?_
    refine d3_bind (Q := fun _ => True) ?_ ?_
    · apply dp_ite_spec <;> intro _ <;> exact d3_ok trivial
    intro lzn _
    refine d3_bind (Q := fun _ => True) ?_ ?_
    · apply dp_ite_spec <;> intro _
      · exact d3_ok trivial
      · refine d3_bind (Q := fun _ => True) ?_ ?_
        · apply dp_ite_spec <;> intro _ <;> exact d3_ok trivial
        intro _ _; exact d3_ok trivial
    rintro ⟨lazy_here, dep7⟩ _
    refine d3_unc ?_
    clear hh3 hh4 hh7 hlt
    apply dp_ite3_spec
    · intro _ hc3 _
      have hc3' : 3 ≤ cl'.val := (UScalar.le_equiv _ _).mp hc3
      refine d3_sub (b := 1) rfl rfl (by omega) ?_; intro cl2 hcl2
      refine d3_add (b := 1) rfl rfl (by clear * - hiM; omega) ?_; intro i4 hi4
      have hn4 : i4.val ≤ n.val := by clear * - hi4 hlt' hlim; omega
      have h14 : i'.val < i4.val := by clear * - hi4; omega
      exact d3_ok ⟨⟨hn4, (by clear * - hcl2 hcl'; omega : cl2.val < 512),
        LeAll_mono hL3 (Nat.le_of_lt h14), LeAll_mono hL4 (Nat.le_of_lt h14),
        LeAll_mono hL7 (Nat.le_of_lt h14)⟩, (by clear * - h14 hlt'; omega)⟩
    ·
'''

COLLECT_FOOTER = r'''
      refine d3_bind (d_record_spec _ _ _ _ _ _ _ _ _ _ _ _) ?_; intro rs2 _
      refine d3_bind (next_anchor_spec _ _ _ _) ?_; intro alen2 _
      refine d3_bind (next_anchor_spec _ _ _ _) ?_; intro anchor2 _
      refine d3_bind (Q := fun (x : Std.Usize × Std.Usize) => x.1.val < 512) ?_ ?_
      · apply dp_ite_spec <;> intro hnc
        · have hnc' : 0 < nc3.val := (UScalar.lt_equiv _ _).mp hnc
          refine d3_sub (b := 1) rfl rfl hnc' ?_; intro i21 _
          refine d3_rem (b := 16) rfl (by decide) ?_; intro i22 hi22
          refine d3_idx (c := 16) rfl hi22 ?_; intro top
          refine d3_rem (b := 512) rfl (by decide) ?_; intro i23 hi23
          refine d3_shr (n := 9) (by decide) rfl ?_; intro i25 _
          have hsat := dp_sat_sub_val (UScalar.cast .Usize i23) 1#usize
          have hcst := d3_cast_le .Usize i23
          exact d3_ok (by
            show (core.num.Usize.saturating_sub (UScalar.cast .Usize i23) 1#usize).val < 512
            clear * - hsat hcst hi23; omega)
        · exact d3_ok (by decide : 0 < 512)
      rintro ⟨cl2, cd2⟩ hcl2
      have hcl2 : cl2.val < 512 := hcl2
      refine d3_unc ?_
      apply dp_ite2_spec
      · intro _ hnc
        refine d3_add rfl rfl (by clear * - hb4 hic hS; omega) ?_; intro «end» hend
        refine d3_bind (Q := fun (x : Std.Usize) => x.val ≤ «end».val ∧ x.val ≤ lim.val) ?_ ?_
        · apply dp_ite_spec <;> intro h
          · have h' : lim.val < «end».val := (UScalar.lt_equiv _ _).mp h
            exact d3_ok ⟨Nat.le_of_lt h', Nat.le_refl _⟩
          · have h' : ¬ (lim.val < «end».val) := (UScalar.lt_equiv _ _).not.mp h
            exact d3_ok ⟨Nat.le_refl _, (by omega : «end».val ≤ lim.val)⟩
        rintro end1 ⟨he1, he2⟩
        have hE : i'.val ≤ «end».val := by clear * - hend; omega
        refine d3_add (b := 1) rfl rfl (by clear * - hiM; omega) ?_; intro i1 hi1
        refine d3_bind (insert_range_spec _ _ _ _ _ _ _ _ _ «end».val
          (LeAll_mono hL3 hE) (LeAll_mono hL4 hE) (LeAll_mono hL7 hE)
          (by clear * - he1; omega) (by clear * - he2 hlim hn hS; omega)) ?_
        rintro ⟨head33, head43, prev43, head73, prev73⟩ ⟨hr3, hr4, hr7⟩
        iterate 4 refine d3_unc ?_
        exact d3_ok ⟨⟨(by clear * - hend hb4 hcap2; omega : «end».val ≤ n.val),
          (by decide : 0 < 512), hr3, hr4, hr7⟩,
          (by clear * - hend hb3 hlt'; omega)⟩
      · refine d3_add (b := 1) rfl rfl (by clear * - hiM; omega) ?_; intro i4 hi4
        have hn4 : i4.val ≤ n.val := by clear * - hi4 hlt' hlim; omega
        have h14 : i'.val < i4.val := by clear * - hi4; omega
        exact d3_ok ⟨⟨hn4, hcl2, LeAll_mono hL3 (Nat.le_of_lt h14),
          LeAll_mono hL4 (Nat.le_of_lt h14), LeAll_mono hL7 (Nat.le_of_lt h14)⟩,
          (by clear * - h14 hlt'; omega)⟩
  · exact ⟨hin, hcl, h3, h4, h7⟩

@[local step]
theorem d_collect_spec (input : Slice Std.U8) (plan rs)
    (ct lazyn d4 d7 skip h3d flen tbmax lz2max dupmode fback d7l d7e nice : Std.Usize)
    (h16 : 16 ≤ input.length) (hN : input.length + input.length ≤ Std.Usize.max) :
    slot.d_collect input plan rs ct lazyn d4 d7 skip h3d flen tbmax lz2max dupmode fback d7l d7e nice
      ⦃ fun _ => True ⦄ := by
  have hl := Slice.len_val input
  have hk := dp_KB7_bound
  rw [slot.d_collect]
  refine d3_sub (b := 8) rfl rfl (by clear * - hl h16; omega) ?_; intro lim hlim
  refine d3_bind (U32.mul_spec (by
    have := U32.max_eq
    show 8 * slot.KB7.val ≤ U32.max
    clear * - hk this; omega)) ?_
  intro i hi
  have hi : i.val = 8 * slot.KB7.val := hi
  refine d3_bind (U32.sub_spec (by show i.val ≤ 64; clear * - hi hk; omega)) ?_; intro sh7 _
  refine d3_bind (d_collect_loop_spec (hn := hl) (hlim := hlim) (hN := hN)
    (hin := Nat.zero_le _) (hcl := by decide)
    (h3 := dp_LeAll_repeat _ _ _ (Nat.le_refl _)) (h4 := dp_LeAll_repeat _ _ _ (Nat.le_refl _))
    (h7 := dp_LeAll_repeat _ _ _ (Nat.le_refl _)) ..) ?_
  intro rs1 _
  exact d3_ok trivial

'''


def generate():
    source = (BASE / "parse.rs").read_bytes()
    extraction = json.loads((EXTRACT / "research.json").read_text())["extractions"][BASE.name]
    assert extraction["extraction_accepted"]
    assert extraction["source_sha256"] == hashlib.sha256(source).hexdigest()
    for filename, record in extraction["files"].items():
        assert hashlib.sha256((EXTRACT / BASE.name / filename).read_bytes()).hexdigest() == record["sha256"]
    funs = (EXTRACT / BASE.name / "Funs.lean").read_text(encoding="utf-8")
    expected_args = {
        "d_seed_put": "out p len dist",
        "d_seed_map_loop0": "out n q",
        "d_seed_map_loop1_loop0": "rs out e p j",
        "d_seed_map_loop1": "rs out e",
        "d_seed_map": "rs out n",
        "d_seed_loop": "out plan n q «end» dist next",
        "d_seed": "input rs out plan",
        "d_collect_loop": "input rs ct lazyn d4 d7 skip h3d tbmax lz2max dupmode d7l d7e nice n head3 head4 prev4 head7 prev7 lim sh7 cands pc pn ppos cl cd i anchor alen",
        "d_collect": "input plan rs ct lazyn d4 d7 skip h3d flen tbmax lz2max dupmode fback d7l d7e nice",
        "d_plan_k": "input out k",
    }
    interfaces = {}
    for name, expected in expected_args.items():
        match = re.search(r"^def " + re.escape(name) + r"\n(.*?)\n  := do", funs, re.M | re.S)
        assert match, name
        declaration = match.group(1)
        args = " ".join(re.findall(r"\(([^():]+) : ", declaration))
        assert args == expected, (name, args, expected)
        interfaces[name] = args
    proof = (BASE / "Parse.lean").read_text(encoding="utf-8")
    start = proof.index("        refine d3_sub rfl rfl hi' ?_; intro cap hcap", proof.index("theorem d_parse_loop_spec"))
    end = proof.index("        refine d3_bind (d_record_spec", start)
    search = "\n".join(line[2:] if line.startswith("  ") else line for line in proof[start:end].splitlines()) + "\n"
    # The new collector only keeps the search/control state; the retained block
    # itself is lifted byte-for-byte modulo two spaces of indentation.
    collector = COLLECT_HEADER + search + COLLECT_FOOTER
    helpers = (DEST / "forward-totality.lean").read_text(encoding="utf-8")
    marker = "@[local step]\ntheorem d_plan_k_loop_spec"
    assert proof.count(marker) == 1
    proof = proof.replace(marker, collector + helpers + "\n" + marker, 1)
    data = {"parse.rs": source, "Parse.lean": proof.encode()}
    parent = json.loads((BASE / "manifest.json").read_text())
    meta = dict(parent)
    meta.update(candidate=DEST.name, parent="candidates/r10-forward-seed",
                parent_hashes=parent["hashes"],
                hashes={n: hashlib.sha256(b).hexdigest() for n, b in data.items()},
                bytes={n: len(b) for n, b in data.items()},
                proof_status="INTERFACE_RECONCILED_UNCOMPILED: helper/collector signatures reconciled with run 37679261323 extraction; original obligation/axiom gate still untested",
                extracted_funs_sha256=extraction["files"]["Funs.lean"]["sha256"])
    assert len(data["Parse.lean"]) <= 524288
    data["manifest.json"] = (json.dumps(meta, indent=2) + "\n").encode()
    audit = {
        "status": "VERIFIED_INTERFACE_AND_SOURCE_ONLY",
        "extraction_run": "37679261323",
        "source_sha256": hashlib.sha256(source).hexdigest(),
        "proof_sha256": meta["hashes"]["Parse.lean"],
        "extracted_files": extraction["files"],
        "interfaces": interfaces,
        "collector_loop_state": "rs head3 head4 prev4 head7 prev7 cands pc pn ppos cl cd i anchor alen",
        "collector_loop_measure": "lim - i",
        "seed_loop_state": "plan q end dist next",
        "seed_loop_measure": "n - q",
        "corrections": ["d_seed_map inner argument order e,p,j", "collector skips reuse computed end; no second checked add", "d_seed return out,plan; d_plan_k then returns plan,out", "factor seed interval and emission conditionals to avoid duplicated proof search"],
        "proof_elaboration": "UNKNOWN: no local Lean toolchain; original gate required",
    }
    data["interface-audit.json"] = (json.dumps(audit, indent=2) + "\n").encode()
    return data


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    files = generate()
    if args.check:
        assert all((DEST / n).read_bytes() == data for n, data in files.items())
    else:
        DEST.mkdir(parents=True, exist_ok=True)
        for n, data in files.items():
            (DEST / n).write_bytes(data)
    print(json.dumps({"candidate": DEST.name, "hashes": json.loads(files["manifest.json"])["hashes"], "status": "INTERFACE_RECONCILED_UNCOMPILED"}))


if __name__ == "__main__":
    main()
