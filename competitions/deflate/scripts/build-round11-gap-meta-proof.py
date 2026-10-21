"""Actual gap-b interfaces: first bounded, UNCOMPILED totality bridge."""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r11-gap-meta"
PARENT = ROOT / "candidates/r10-finder-pipeline-proof"
DEST = ROOT / "candidates/r11-gap-meta-proof"
EXTRACT = ROOT / "evidence/round11/37724534982/gap-b/extraction/r11-gap-meta"
RUST_SHA = "25bd4ee52560288f36c73f813a769345044cab2c4924705e6c4c92a64c017de6"
PARENT_LEAN_SHA = "e0ded4248a894e8c53bc1ce644c7c3f5c6681fe3c06eaab597caf10a5bf472db"
FUNS_SHA = "dd29b3f280b82c2e942deb633b03daca246fe9885734961028d8a28a562cc955"

PRELUDE = r'''
-- R11: actual loaded-table helper totality. No price-origin premise is added.
theorem d11_amut {α β : Type} {n : Usize} {a : Std.Array α n} {i : Usize}
    {k : (α × (α → Std.Array α n)) → Result β} {P : β → Prop}
    (h : i.val < n.val) (hk : ∀ x back, WP.spec (k (x, back)) P) :
    WP.spec (Bind.bind (Array.index_mut_usize a i) k) P :=
  WP.spec_bind (Array.index_mut_usize_spec a i (Nat.lt_of_lt_of_eq h a.property.symm))
    (fun r _ => hk r.1 r.2)

theorem d11_smut {α β : Type} {s : Slice α} {i : Usize}
    {k : (α × (α → Slice α)) → Result β} {P : β → Prop}
    (h : i.val < (Slice.len s).val)
    (hk : ∀ x back, (∀ v, (back v).length = s.length) → WP.spec (k (x, back)) P) :
    WP.spec (Bind.bind (Slice.index_mut_usize s i) k) P := by
  refine WP.spec_bind (Slice.index_mut_usize_spec s i h) ?_
  rintro ⟨x, back⟩ ⟨_, hback⟩
  apply hk x back
  intro v
  rw [hback]
  exact Slice.set_length s i v

@[local step]
theorem d_gap_positive_max_loop_spec (litc i maximum positive) :
    slot.d_gap_positive_max_loop litc i maximum positive ⦃ fun _ => True ⦄ := by
  rw [slot.d_gap_positive_max_loop]
  apply Std.loop.spec_decr_nat (measure := fun x => 256 - x.1.val) (inv := fun _ => True)
  · rintro ⟨i', maximum', positive'⟩ _
    unfold slot.d_gap_positive_max_loop.body
    refine d2_lt (fun hi => ?_) (fun _ => d2_ok trivial)
    refine d2_idx hi fun price => ?_
    refine d2_tot d2_itev fun maximum1 => ?_
    refine d2_tot d2_itev fun positive1 => ?_
    refine d2_inck 256 (Nat.le_of_lt hi) (by decide) fun i1 hi1 => ?_
    exact d2_ok ⟨trivial, d2_msub hi hi1⟩
  · trivial

@[local step]
theorem d_gap_positive_max_spec (litc) :
    slot.d_gap_positive_max litc ⦃ fun _ => True ⦄ := by
  rw [slot.d_gap_positive_max]
  refine d2_tot (d_gap_positive_max_loop_spec _ _ _ _) ?_
  rintro ⟨maximum, positive⟩
  exact d2_itev

@[local step]
theorem d_load_meta_spec (tabs tb litc lc dcc) :
    slot.d_load_meta tabs tb litc lc dcc ⦃ fun _ => True ⦄ := by
  rw [slot.d_load_meta]
  refine d2_tot (d_load_spec _ _ _ _ _) ?_
  rintro ⟨litc1, lc1, dcc1⟩
  refine d2_tot (d_gap_positive_max_spec _) fun bound => ?_
  exact d2_upd (by decide) fun lc2 => d2_ok trivial

'''

NESTED = r'''
@[local step]
theorem d_gap_meta_loop2_loop0_spec (s lc ring out stop «end» chd q nxt length_price high) :
    slot.d_gap_meta_loop2_loop0 s lc ring out stop «end» chd q nxt length_price high
      ⦃ fun r => r.2.1.length = out.length ∧ r.2.2.1.val ≤ q.val ⦄ := by
  rw [slot.d_gap_meta_loop2_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.2.1.val)
    (inv := fun x => x.2.1.length = out.length ∧ x.2.2.1.val ≤ q.val)
  · rintro ⟨ring', out', q', nxt'⟩ hinv
    unfold slot.d_gap_meta_loop2_loop0.body
    refine d2_lt (fun h1 => ?_) (fun _ => d2_ok hinv)
    refine d2_le (fun h2 => ?_) (fun _ => d2_ok hinv)
    refine d2_le (fun h3 => ?_) (fun _ => d2_ok hinv)
    refine d2_le (fun h4 => ?_) (fun _ => d2_ok hinv)
    refine d2_dec h1 fun q1 hq1 => ?_
    refine d2_sub (Nat.le_of_lt (d2_le_pred hq1 h4)) fun rem1 _ => ?_
    refine d2_ite (fun _ => d2_ok hinv) (fun _ => ?_)
    refine d2_rem (by decide) fun i2 hi2 => ?_
    refine d2_idx hi2 fun i3 => ?_
    refine d2_ite (fun _ => d2_ok hinv) (fun _ => ?_)
    refine d2_lift <| d2_lift <| d2_lift <| d2_remR fun i6 hi6 => ?_
    refine d2_upd hi6 fun a => ?_
    refine d2_lift <| d2_supd (d2_le_pred hq1 h3) fun out1 hout1 => ?_
    exact d2_ok ⟨⟨hout1.trans hinv.1, Nat.le_trans (Nat.le_of_lt (d2_pred hq1)) hinv.2⟩, d2_pred hq1⟩
  · exact ⟨rfl, Nat.le_refl _⟩

@[local step]
theorem d_gap_meta_loop2_spec (s litc lc ring out stop «end» chd dlit maximum q nxt kc) :
    slot.d_gap_meta_loop2 s litc lc ring out stop «end» chd dlit maximum q nxt kc
      ⦃ fun r => r.2.2.length = out.length ⦄ := by
  rw [slot.d_gap_meta_loop2]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.2.1.val)
    (inv := fun x => x.2.1.length = out.length)
  · rintro ⟨ring', out', q', nxt'⟩ hinv
    unfold slot.d_gap_meta_loop2.body
    refine d2_lt (fun h1 => ?_) (fun _ => d2_ok hinv)
    refine d2_le (fun h2 => ?_) (fun _ => d2_ok hinv)
    refine d2_le (fun h3 => ?_) (fun _ => d2_ok hinv)
    refine d2_le (fun h4 => ?_) (fun _ => d2_ok hinv)
    refine d2_dec h1 fun q1 hq1 => ?_
    refine d2_sub (Nat.le_of_lt (d2_le_pred hq1 h4)) fun rem _ => ?_
    refine d2_rem (by decide) fun i2 hi2 => ?_
    refine d2_idx hi2 fun length_price => ?_
    refine d2_tot (d2_shr32 _) fun i3 => ?_
    refine d2_sidx (d2_le_pred hq1 h2) fun i4 => ?_
    refine d2_lift <| d2_idx (d2_u8 i4) fun i6 => ?_
    refine d2_lift <| d2_lift <| d2_tot (d2_shl32 _) fun i9 => ?_
    refine d2_lift <| d2_lift <| d2_lift <| d2_tot (d2_shl32 _) fun i12 => ?_
    refine d2_lift <| d2_lift <| d2_lift <| d2_tot d2_itev fun v => ?_
    refine d2_remR fun i15 hi15 => ?_
    refine d11_amut hi15 fun _ back0 => ?_
    refine d11_smut (d2_le_pred hq1 h3) fun _ back1 hback1 => ?_
    refine d2_lift ?_
    have hout1 := (hback1 (UScalar.cast .U32 v)).trans hinv
    refine d2_ite (fun _ => ?_) (fun _ => d2_ok ⟨hout1, d2_pred hq1⟩)
    refine d2_ite (fun _ => ?_) (fun _ => d2_ok ⟨hout1, d2_pred hq1⟩)
    refine d2_ite (fun _ => ?_) (fun _ => d2_ok ⟨hout1, d2_pred hq1⟩)
    refine d2_tot (d2_shr32 _) fun i17 => ?_
    refine d2_lift <| d2_ite (fun _ => ?_) (fun _ => d2_ok ⟨hout1, d2_pred hq1⟩)
    refine d2_lift <| d2_bind (d_gap_meta_loop2_loop0_spec _ _ _ _ _ _ _ _ _ _ _) ?_
    rintro ⟨ring1, out1, q2, nxt1⟩ ⟨hlen, hq2⟩
    exact d2_ok ⟨hlen.trans hout1, Nat.lt_of_le_of_lt hq2 (d2_pred hq1)⟩
  · rfl

@[local step]
theorem d_gap_meta_spec (s litc lc ring out hi stop «end» kcd chd lo nxt0 dlit) :
    slot.d_gap_meta s litc lc ring out hi stop «end» kcd chd lo nxt0 dlit
      ⦃ fun r => r.2.2.length = out.length ⦄ := by
  rw [slot.d_gap_meta]
  refine d2_idx (by decide) fun i => ?_
  refine d2_lift <| d2_ite (fun _ => d_gap_spec _ _ _ _ _ _ _ _ _ _ _ _ _) (fun _ => ?_)
  refine d2_ite (fun _ => d_gap_spec _ _ _ _ _ _ _ _ _ _ _ _ _) (fun _ => ?_)
  refine d2_ite (fun _ => d_gap_spec _ _ _ _ _ _ _ _ _ _ _ _ _) (fun _ => ?_)
  refine d2_lift <| d2_tot (d_clip_spec _ _ _) fun mid => ?_
  refine d2_bind (d_gap_meta_loop0_spec s litc ring out lo dlit hi nxt0 mid) ?_
  rintro ⟨ring1, out1, q, nxt⟩ h0
  refine d2_tot (d_cell_spec _ _) fun i2 => ?_
  refine d2_tot (d2_shr32 _) fun i3 => ?_
  refine d2_lift <| d2_tot (d_clip_spec _ _ _) fun s1 => ?_
  refine d2_bind (d_gap_meta_loop1_spec s litc lc ring1 out1 «end» chd dlit q nxt _ s1) ?_
  rintro ⟨ring2, out2, q1, nxt1⟩ h1
  exact WP.spec_mono (d_gap_meta_loop2_spec s litc lc ring2 out2 stop «end» chd dlit _ q1 nxt1 _)
    (fun r h2 => h2.trans (h1.trans h0))

'''


def sha(raw: bytes) -> str:
    return hashlib.sha256(raw).hexdigest()


def theorem(source: str, name: str) -> str:
    start = source.index("@[local step]\ntheorem " + name + " ")
    end = source.index("\n@[local step]", start + 1)
    return source[start:end] + "\n"


def generate() -> dict[str, bytes]:
    rust = (BASE / "parse.rs").read_bytes(); parent = (PARENT / "Parse.lean").read_bytes()
    funs = (EXTRACT / "Funs.lean").read_bytes()
    assert sha(rust) == RUST_SHA and sha(parent) == PARENT_LEAN_SHA and sha(funs) == FUNS_SHA
    proof = parent.decode()
    clones = "".join(theorem(proof, f"d_gap_loop{i}_spec").replace(f"d_gap_loop{i}", f"d_gap_meta_loop{i}") for i in (0, 1))
    block = theorem(proof, "d_block_spec").replace("d_block_spec", "d_block_meta_spec").replace("slot.d_block", "slot.d_block_meta").replace("d_load_spec", "d_load_meta_spec")
    additions = PRELUDE + block + clones + NESTED
    assert not re.search(r"\b(sorry|axiom|admit)\b", additions)
    anchor = "@[local step]\ntheorem d_top_spec "
    assert proof.count(anchor) == 1
    proof = proof.replace(anchor, additions + anchor, 1)
    start = proof.index("@[local step]\ntheorem d_dp_loop0_loop0_spec ")
    end = proof.index("@[local step]\ntheorem d_extract_loop_spec ", start)
    old = proof[start:end]; changed = old
    counts = {}
    for before, after, count in (("d_load_spec", "d_load_meta_spec", 1), ("d_block_spec", "d_block_meta_spec", 2), ("d_gap_spec", "d_gap_meta_spec", 1)):
        assert changed.count(before) == count
        changed = changed.replace(before, after); counts[before] = count
    proof = proof[:start] + changed + proof[end:]
    restored = proof.replace(additions, "", 1)
    start = restored.index("@[local step]\ntheorem d_dp_loop0_loop0_spec ")
    end = restored.index("@[local step]\ntheorem d_extract_loop_spec ", start)
    back = restored[start:end]
    for before, after in (("d_load_meta_spec", "d_load_spec"), ("d_block_meta_spec", "d_block_spec"), ("d_gap_meta_spec", "d_gap_spec")):
        back = back.replace(before, after)
    restored = restored[:start] + back + restored[end:]
    assert restored.encode() == parent
    files = {"parse.rs": rust, "Parse.lean": proof.encode()}
    manifest = json.loads((BASE / "manifest.json").read_text())
    manifest.update(candidate="r11-gap-meta-proof", parent="candidates/r11-gap-meta",
                    parent_hashes={"parse.rs": RUST_SHA, "Parse.lean": PARENT_LEAN_SHA},
                    hashes={f: sha(data) for f, data in files.items()}, bytes={f: len(data) for f, data in files.items()},
                    proof_status="UNCOMPILED_ACTUAL_GAP_B_FIRST_TOTALITY_BRIDGE; root CI must verify exact pair, original obligation/axioms/roundtrip",
                    equivalence_status="VERIFIED_FINITE_LOADER10_DP1540_BOUNDARY_CHECKS in gap-b, including honest-wrap and false-metadata counterexample. 444/public pair receipt pending; no arbitrary-metadata helper equivalence claim.",
                    performance_status="PENDING_GAP_B_TOTAL_COMPRESSION; operation coverage is not performance",
                    proof_scope="New helpers forall totality and out.length preservation only; no metadata-origin premise added to original LZ77 obligation. Checked emitter/root proof bytes unchanged.")
    audit = {"status": "VERIFIED_ACTUAL_INTERFACE_UNCOMPILED_PROOF", "rust_sha256": RUST_SHA, "funs_sha256": FUNS_SHA,
             "nested_loop": "d_gap_meta_loop2_loop0", "nested_state": ["ring", "out", "q", "nxt"],
             "nested_post": "out.length unchanged and q_out<=q_in", "outer_state": ["ring", "out", "q", "nxt"],
             "outer_return": ["nxt", "ring", "out"], "positive_max_state": ["i", "maximum", "positive"],
             "positive_max_return": ["maximum", "positive"], "dp_inner_components": 9, "dp_outer_components": 9,
             "new_mut_borrows": "outer seed Array.index_mut_usize and Slice.index_mut_usize return back closures; Slice back length derived from existing index_mut spec/set_length", "proof_status": "UNCOMPILED"}
    port = {"status": "VERIFIED_SOURCE_PROOF_REVERSAL_ONLY", "candidate_hashes": manifest["hashes"],
            "parent_lean_sha256": PARENT_LEAN_SHA, "inserted_bytes": len(additions.encode()), "binding_changes": counts,
            "no_new_sorry_axiom": True, "original_checked_emitter_and_root_suffix": "byte-identical",
            "limits": ["No local Lean run, fresh root CI required", "Slice mutable-index API checked against official upstream and local Array reference; exact pinned API must compile in CI", "Totality does not establish semantic optimum or all-input token equivalence"]}
    for f, obj in (("manifest.json", manifest), ("interface-audit.json", audit), ("proof-port-audit.json", port)):
        files[f] = (json.dumps(obj, indent=2, ensure_ascii=False) + "\n").encode()
    assert all(0 < len(files[f]) <= 524288 for f in ("parse.rs", "Parse.lean"))
    return files


def main():
    parser = argparse.ArgumentParser(); parser.add_argument("--check", action="store_true"); args = parser.parse_args()
    files = generate(); DEST.mkdir(parents=True, exist_ok=True)
    for f, data in files.items():
        path = DEST / f
        if args.check: assert path.read_bytes() == data
        elif path.exists(): assert path.read_bytes() == data, f"Refusing to mutate frozen proof {path}"
        else: path.write_bytes(data)
    print(json.dumps({"candidate": "r11-gap-meta-proof", "status": "UNCOMPILED", "hashes": {f: sha(data) for f, data in files.items()}, "builder_sha256": sha(Path(__file__).read_bytes())}))


if __name__ == "__main__":
    main()
