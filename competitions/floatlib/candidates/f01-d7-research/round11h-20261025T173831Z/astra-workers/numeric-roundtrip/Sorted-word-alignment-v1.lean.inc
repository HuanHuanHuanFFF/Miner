/- R18 single-sort word alignment. Fixed-environment elaboration is pending. -/
namespace Submission.R18SortedWord
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

theorem sign_eq (u : UInt32) :
    decide ((0x80000000 : UInt32) ≤ u) = R2W01c.wordSign u := by
  change decide (2147483648 ≤ u.toNat) = decide (2147483648 ≤ u.toNat)
  rfl

theorem left_word_nat (hi d : UInt32) (hd : d.toNat ≤ 7) :
    (R2W01b.mantissa hi <<< d).toNat = (R2W01b.mantissa hi).toNat <<< d.toNat := by
  have hm := R2W01c.mantissa_bounds hi
  have hp : 2 ^ d.toNat ≤ 128 := by
    have h := Nat.pow_le_pow_right (by decide : 1 ≤ (2 : Nat)) hd
    norm_num at h
    exact h
  have hx := Nat.mul_le_mul_left (R2W01b.mantissa hi).toNat hp
  rw [UInt32.toNat_shiftLeft, Nat.mod_eq_of_lt (show d.toNat < 32 by omega)]
  rw [Nat.shiftLeft_eq]
  exact Nat.mod_eq_of_lt (by omega)

theorem magnitude_word_nat (hi lo d : UInt32) (hd : d.toNat ≤ 7)
    (hdom : R2W01c.wordSign hi = R2W01c.wordSign lo ∨ 1 ≤ d.toNat) :
    (if R2W01c.wordSign hi == R2W01c.wordSign lo
      then (R2W01b.mantissa hi <<< d) + R2W01b.mantissa lo
      else (R2W01b.mantissa hi <<< d) - R2W01b.mantissa lo).toNat =
    A16L.magnitude (R2W01c.wordSign hi) (R2W01c.wordSign lo)
      (R2W01b.mantissa hi).toNat (R2W01b.mantissa lo).toNat d.toNat := by
  have hh := R2W01c.mantissa_bounds hi
  have hl := R2W01c.mantissa_bounds lo
  have hb := A16L.magnitude_bounds _ _ _ _ _ hh.1 hh.2 hl.1 hl.2 hd hdom
  by_cases hs : R2W01c.wordSign hi = R2W01c.wordSign lo
  · have hbtrue : (R2W01c.wordSign hi == R2W01c.wordSign lo) = true := beq_iff_eq.mpr hs
    rw [if_pos hbtrue, UInt32.toNat_add, left_word_nat hi d hd]
    simp only [A16L.magnitude, if_pos hs] at hb ⊢
    exact Nat.mod_eq_of_lt (by omega)
  · have hbfalse : ¬ (R2W01c.wordSign hi == R2W01c.wordSign lo) = true := by
      simpa only [beq_iff_eq] using hs
    have hg : 1 ≤ d.toNat := hdom.resolve_left hs
    have hlarge := A16L.large_left _ _ _ hh.1 hl.2 hg
    have hle : R2W01b.mantissa lo ≤ R2W01b.mantissa hi <<< d := by
      rw [UInt32.le_iff_toNat_le, left_word_nat hi d hd]
      omega
    rw [if_neg hbfalse, UInt32.toNat_sub_of_le _ _ hle, left_word_nat hi d hd]
    simp only [A16L.magnitude, if_neg hs]

theorem high_low_model (hi lo d : UInt32)
    (hhi : 0 < R2W01c.wordExp hi ∧ R2W01c.wordExp hi < 255)
    (hlo : 0 < R2W01c.wordExp lo ∧ R2W01c.wordExp lo < 255)
    (ho : R2W01c.wordExp lo ≤ R2W01c.wordExp hi)
    (hg : d.toNat = R2W01c.wordExp hi - R2W01c.wordExp lo) (hd : d.toNat ≤ 7)
    (hdom : R2W01c.wordSign hi = R2W01c.wordSign lo ∨ 1 ≤ d.toNat) :
    Model.add (R2W01c.rawModel hi) (R2W01c.rawModel lo) =
    Model.roundDyadic FloatFormat.binary32
      (⟨R2W01c.wordSign hi,
        (if R2W01c.wordSign hi == R2W01c.wordSign lo
          then (R2W01b.mantissa hi <<< d) + R2W01b.mantissa lo
          else (R2W01b.mantissa hi <<< d) - R2W01b.mantissa lo).toNat,
        (R2W01c.wordExp lo : Int) - 150⟩ : FloatLib.Numerics.Dyadic) := by
  have hh := R2W01c.mantissa_bounds hi
  have hl := R2W01c.mantissa_bounds lo
  have hdom' : R2W01c.wordSign hi = R2W01c.wordSign lo ∨
      1 ≤ R2W01c.wordExp hi - R2W01c.wordExp lo := by rwa [← hg]
  rw [magnitude_word_nat hi lo d hd hdom, hg, Model.Proof.add_eq_spec]
  rw [A16L.spec_add_of_decodes _ _ _ _
    (R14NatNormal.raw_normal_decode hi hhi.1 hhi.2)
    (R14NatNormal.raw_normal_decode lo hlo.1 hlo.2)]
  rw [A16L.exact_high_low _ _ _ _ _ _ hh.1 (by omega) hl.2 ho hdom']

theorem low_high_model (hi lo d : UInt32)
    (hhi : 0 < R2W01c.wordExp hi ∧ R2W01c.wordExp hi < 255)
    (hlo : 0 < R2W01c.wordExp lo ∧ R2W01c.wordExp lo < 255)
    (ho : R2W01c.wordExp lo ≤ R2W01c.wordExp hi)
    (hg : d.toNat = R2W01c.wordExp hi - R2W01c.wordExp lo) (hd : d.toNat ≤ 7)
    (hdom : R2W01c.wordSign hi = R2W01c.wordSign lo ∨ 1 ≤ d.toNat) :
    Model.add (R2W01c.rawModel lo) (R2W01c.rawModel hi) =
    Model.roundDyadic FloatFormat.binary32
      (⟨R2W01c.wordSign hi,
        (if R2W01c.wordSign hi == R2W01c.wordSign lo
          then (R2W01b.mantissa hi <<< d) + R2W01b.mantissa lo
          else (R2W01b.mantissa hi <<< d) - R2W01b.mantissa lo).toNat,
        (R2W01c.wordExp lo : Int) - 150⟩ : FloatLib.Numerics.Dyadic) := by
  have hh := R2W01c.mantissa_bounds hi
  have hl := R2W01c.mantissa_bounds lo
  have hdom' : R2W01c.wordSign hi = R2W01c.wordSign lo ∨
      1 ≤ R2W01c.wordExp hi - R2W01c.wordExp lo := by rwa [← hg]
  rw [magnitude_word_nat hi lo d hd hdom, hg, Model.Proof.add_eq_spec]
  rw [A16L.spec_add_of_decodes _ _ _ _
    (R14NatNormal.raw_normal_decode lo hlo.1 hlo.2)
    (R14NatNormal.raw_normal_decode hi hhi.1 hhi.2)]
  rw [A16L.exact_low_high _ _ _ _ _ _ hh.1 (by omega) hl.2 ho hdom']

end Submission.R18SortedWord
