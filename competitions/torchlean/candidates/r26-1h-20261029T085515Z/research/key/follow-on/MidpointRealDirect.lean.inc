/- Direct raw64 midpoint values, independent of the earlier widening closure. -/
namespace Submission.R25Checker
open Submission.R25OrderKey

noncomputable def cellLower (e f : Nat) : Real :=
  (8388608 + (f : Real) - (if f = 0 ∧ 1 < e then (1 : Real) / 4 else 1 / 2)) *
    (2 : Real) ^ ((e : Int) - 150)

noncomputable def cellUpper (e f : Nat) : Real :=
  (8388608 + (f : Real) + (1 : Real) / 2) * (2 : Real) ^ ((e : Int) - 150)

private theorem shift29 (n : Nat) (e : Int) :
    (n : Real) * (2 : Real) ^ (e - 29) =
      ((n : Real) / 536870912) * (2 : Real) ^ e := by
  rw [show e - 29 = e + (-29) by omega, zpow_add₀ (by norm_num : (2 : Real) ≠ 0)]
  norm_num <;> ring

private theorem shift30 (n : Nat) (e : Int) :
    (n : Real) * (2 : Real) ^ (e - 30) =
      ((n : Real) / 1073741824) * (2 : Real) ^ e := by
  rw [show e - 30 = e + (-30) by omega, zpow_add₀ (by norm_num : (2 : Real) ≠ 0)]
  norm_num <;> ring

private theorem positive_normal_value (w : UInt64) (hf : finite64 w = true)
    (hs : negative w = false) (he : exponent w ≠ 0) :
    value w = ((4503599627370496 + fraction w : Nat) : Real) *
      (2 : Real) ^ ((exponent w : Int) - 1075) := by
  rw [raw_value w hf]
  simp only [hs, Bool.false_eq_true, ite_false, magnitudeReal,
    magnitude_div, magnitude_mod, he, ite_false]

/-- Exact real values of both unsigned runtime midpoint words. -/
theorem unsigned_midpoint_values (q : UInt32) (he0 : eWord q ≠ 0) (he255 : eWord q ≠ 255) :
    value (below q) = cellLower (eWord q).toNat (fWord q).toNat ∧
    value (above q) = cellUpper (eWord q).toNat (fWord q).toNat := by
  have hb := unsigned_bounds q he0 he255
  have hlo : (below q).toNat < 9223372036854775808 := by omega
  have hhi : (above q).toNat < 9223372036854775808 := by omega
  have hbf : finite64 (below q) = true := by
    apply finite_of_magnitude
    rw [unsigned_magnitude _ hlo]
    exact hb.2.1
  have haf : finite64 (above q) = true := by
    apply finite_of_magnitude
    rw [unsigned_magnitude _ hhi]
    exact hb.2.2.2
  have hbs : negative (below q) = false := by simp [negative]; omega
  have has : negative (above q) = false := by simp [negative]; omega
  have hEn : (eWord q).toNat ≠ 0 := by
    intro hz
    apply he0
    apply UInt32.toNat_inj.mp
    exact hz
  constructor
  · by_cases hf0 : (fWord q).toNat = 0
    · by_cases he1 : (eWord q).toNat = 1
      · have hd := below_decode_fields_minnormal q hf0 he1
        rw [positive_normal_value _ hbf hbs (by rw [hd.1]; decide), hd.1, hd.2]
        norm_num [cellLower, hf0, he1]
      · have hd := below_decode_fields_power q hf0 he1
        have hpower : (fWord q).toNat = 0 ∧ 1 < (eWord q).toNat := ⟨hf0, by omega⟩
        rw [positive_normal_value _ hbf hbs (by rw [hd.1]; omega), hd.1, hd.2]
        change (9007198986305536 : Real) *
          (2 : Real) ^ (((eWord q).toNat : Int) + 895 - 1075) = _
        rw [show (((eWord q).toNat : Int) + 895 - 1075) =
          (((eWord q).toNat : Int) - 150) - 30 by omega]
        rw [shift30 9007198986305536 (((eWord q).toNat : Int) - 150)]
        simp only [cellLower, hpower, ite_true, hf0, Nat.cast_zero, add_zero]
        norm_num
    · have hd := below_decode_fields_inner q (by omega : 0 < (fWord q).toNat)
      have hsub : 268435456 ≤ (fWord q).toNat * 536870912 := by omega
      have hnp : ¬ ((fWord q).toNat = 0 ∧ 1 < (eWord q).toNat) := by omega
      rw [positive_normal_value _ hbf hbs (by rw [hd.1]; omega), hd.1, hd.2]
      rw [show (((eWord q).toNat + 896 : Nat) : Int) - 1075 =
        (((eWord q).toNat : Int) - 150) - 29 by omega, shift29]
      simp only [cellLower, hnp, ite_false, Nat.cast_add, Nat.cast_sub hsub, Nat.cast_mul]
      norm_num <;> ring
  · have hd := above_decode_fields q
    rw [positive_normal_value _ haf has (by rw [hd.1]; omega), hd.1, hd.2]
    rw [show (((eWord q).toNat + 896 : Nat) : Int) - 1075 =
      (((eWord q).toNat : Int) - 150) - 29 by omega, shift29]
    simp only [cellUpper, Nat.cast_add, Nat.cast_mul]
    norm_num <;> ring

end Submission.R25Checker
