/- Minimal dependency bridge for exact FlatScale82ebf77c. NOT_RUN.
   The four block-wide pick equations remain explicit premises; no512-case
   proof or public candidate is generated before the selector-cost result. -/
namespace Submission.R22FlatScale
open FloatLib.Floats Competition

theorem slot_nat (j : UInt32) : (j &&& (127 : UInt32)).toNat = j.toNat % 128 := by
  rw [UInt32.toNat_and]
  exact Nat.and_two_pow_sub_one_eq_mod j.toNat 7

theorem group_nat (j : UInt32) : (j >>> (7 : UInt32)).toNat = j.toNat / 128 := by
  rw [UInt32.toNat_shiftRight]
  change j.toNat >>> 7 = j.toNat / 128
  simp only [Nat.shiftRight_eq_div_pow]

theorem lookup_index_bounds (u : UInt32) :
    ((R2W01b.tableIndex u) >>> (7 : UInt32)).toNat < 4 ∧
      ((R2W01b.tableIndex u) &&& (127 : UInt32)).toNat < 128 := by
  have hj := R2W01b.tableIndex_toNat_lt u
  rw [group_nat,slot_nat]
  constructor
  · omega
  · exact Nat.mod_lt _ (by decide)

theorem group_slot_recompose (j : UInt32) :
    128*(j >>> (7 : UInt32)).toNat+(j &&& (127 : UInt32)).toNat = j.toNat := by
  rw [group_nat,slot_nat]
  exact Nat.div_add_mod j.toNat 128

theorem lookup_eq_scaleAt_of_blocks
    (h0 : ∀ s : Nat, s<128 → pick block0 s = seed (UInt32.ofNat s))
    (h1 : ∀ s : Nat, s<128 → pick block1 s = seed (UInt32.ofNat (128+s)))
    (h2 : ∀ s : Nat, s<128 → pick block2 s = seed (UInt32.ofNat (256+s)))
    (h3 : ∀ s : Nat, s<128 → pick block3 s = seed (UInt32.ofNat (384+s)))
    (u : UInt32) : lookup u = R2W01b.scaleAt u := by
  let j := R2W01b.tableIndex u
  let g := j >>> (7 : UInt32)
  let s := (j &&& (127 : UInt32)).toNat
  have hg : g.toNat < 4 := (lookup_index_bounds u).1
  have hs : s < 128 := (lookup_index_bounds u).2
  have hj : 128*g.toNat+s = j.toNat := group_slot_recompose j
  have hc : g.toNat=0 ∨ g.toNat=1 ∨ g.toNat=2 ∨ g.toNat=3 := by omega
  have target : seed j = R2W01b.scaleAt u := by
    simpa only [seed] using (R2W01b.scaleAt_eq u).symm
  refine Eq.trans ?_ target
  change pick (if g == (0 : UInt32) then block0 else if g == (1 : UInt32) then block1
    else if g == (2 : UInt32) then block2 else block3) s = seed j
  rcases hc with h | h | h | h
  · have hw : g = (0 : UInt32) := UInt32.toNat_inj.mp h
    have hs' : s = j.toNat := by omega
    simpa [hw,hs',UInt32.ofNat_toNat] using h0 s hs
  · have hw : g = (1 : UInt32) := UInt32.toNat_inj.mp h
    have hs' : 128+s = j.toNat := by omega
    have he : seed (UInt32.ofNat (128+s)) = seed j := by rw [hs',UInt32.ofNat_toNat]
    simpa [hw] using (h1 s hs).trans he
  · have hw : g = (2 : UInt32) := UInt32.toNat_inj.mp h
    have hs' : 256+s = j.toNat := by omega
    have he : seed (UInt32.ofNat (256+s)) = seed j := by rw [hs',UInt32.ofNat_toNat]
    simpa [hw] using (h2 s hs).trans he
  · have hw : g = (3 : UInt32) := UInt32.toNat_inj.mp h
    have hs' : 384+s = j.toNat := by omega
    have he : seed (UInt32.ofNat (384+s)) = seed j := by rw [hs',UInt32.ofNat_toNat]
    simpa [hw] using (h3 s hs).trans he

theorem convert_eq_old (hlookup : ∀ u, lookup u = R2W01b.scaleAt u) (u : UInt32) :
    convert u = R2W01b.convert u := by
  simp only [convert,R2W01b.convert,R2W01b.tableProduct,hlookup]

theorem add_eq_old (hconvert : ∀ u, convert u = R2W01b.convert u) (x y : Binary32) :
    add x y = Submission.add x y := by
  simp only [add,Submission.add,hconvert]

theorem nativeMul_eq_old (hconvert : ∀ u, convert u = R2W01b.convert u) (x y : Binary32) :
    nativeMul x y = Submission.nativeMul x y := by
  simp only [nativeMul,Submission.nativeMul,hconvert]

theorem mul_eq_old (hconvert : ∀ u, convert u = R2W01b.convert u) (x y : Binary32) :
    mul x y = Submission.mul x y := by
  simp only [mul,Submission.mul,nativeMul_eq_old hconvert]

theorem add_spec_of_lookup (hlookup : ∀ u, lookup u = R2W01b.scaleAt u) (x y : Binary32) :
    add x y = ExecFloat.Spec.add x y := by
  rw [add_eq_old (convert_eq_old hlookup)]
  exact Submission.add_spec x y

theorem nativeMul_spec_of_lookup (hlookup : ∀ u, lookup u = R2W01b.scaleAt u) (x y : Binary32) :
    nativeMul x y = ExecFloat.Spec.mul x y := by
  rw [nativeMul_eq_old (convert_eq_old hlookup)]
  exact Submission.nativeMul_spec x y

theorem mul_spec_of_lookup (hlookup : ∀ u, lookup u = R2W01b.scaleAt u) (x y : Binary32) :
    mul x y = ExecFloat.Spec.mul x y := by
  rw [mul_eq_old (convert_eq_old hlookup)]
  exact Submission.mul_spec x y

end Submission.R22FlatScale
