namespace Submission.R25Checker
open Submission.R25OrderKey
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

private theorem positive_word_negate_value (w : UInt64)
    (hw : w.toNat < 9223372036854775808) (hf : finite64 w = true) :
    value (w ||| 0x8000000000000000) = -value w := by
  have hm : magnitude (w ||| 0x8000000000000000) = magnitude w := by
    rw [signed_magnitude w hw, unsigned_magnitude w hw]
  have he : exponent (w ||| 0x8000000000000000) = exponent w := by
    rw [← magnitude_div, ← magnitude_div, hm]
  have hnf : finite64 (w ||| 0x8000000000000000) = true := by
    apply (finite64_iff_exp _).mpr
    rw [he]
    exact (finite64_iff_exp w).mp hf
  have hp : w.toNat < 2 ^ 63 := hw
  have hnNat : (w ||| 0x8000000000000000).toNat = w.toNat + 9223372036854775808 := by
    rw [UInt64.toNat_or]
    exact Nat.or_two_pow_eq_add_of_lt hp
  have hn : negative (w ||| 0x8000000000000000) = true := by
    simp only [negative, hnNat, decide_eq_true_eq]
    omega
  have hs : negative w = false := by simp [negative]; omega
  rw [raw_value _ hnf, raw_value _ hf, hm]
  simp only [hn, hs, Bool.false_eq_true, ite_false, ite_true]

theorem signed_midpoint_values (q : UInt32) (he0 : eWord q ≠ 0) (he255 : eWord q ≠ 255) :
    value (lowerWord q) = (if negative32 q then
      -cellUpper (eWord q).toNat (fWord q).toNat
      else cellLower (eWord q).toNat (fWord q).toNat) ∧
    value (upperWord q) = (if negative32 q then
      -cellLower (eWord q).toNat (fWord q).toNat
      else cellUpper (eWord q).toNat (fWord q).toNat) := by
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
  have hv := unsigned_midpoint_values q he0 he255
  cases hs : negative32 q <;>
    simp only [lowerWord, upperWord, hs, Bool.false_eq_true, ite_false, ite_true,
      positive_word_negate_value _ hlo hbf, positive_word_negate_value _ hhi haf, hv.1, hv.2, and_self]

theorem eWord_eq_native (q : UInt32) : eWord q = Model.NativeBinary32.expField q := by
  apply UInt32.toNat_inj.mp
  rw [e32_nat, mag32_nat]
  rw [show (2147483648 : Nat) = 8388608 * 256 by decide, Nat.mod_mul_right_div_self]
  rw [Model.NativeBinary32.expField, UInt32.toNat_and, UInt32.toNat_shiftRight]
  change q.toNat / 8388608 % 256 = (q.toNat >>> 23) &&& (2 ^ 8 - 1)
  rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]

theorem fWord_eq_native (q : UInt32) : fWord q = Model.NativeBinary32.fracField q := by
  apply UInt32.toNat_inj.mp
  rw [f32_nat, mag32_nat]
  rw [show (2147483648 : Nat) = 8388608 * 256 by decide, Nat.mod_mul_right_mod]
  rw [Model.NativeBinary32.fracField, UInt32.toNat_and]
  exact (Nat.and_two_pow_sub_one_eq_mod q.toNat 23).symm

theorem negative32_eq_native (q : UInt32) : negative32 q = Model.NativeBinary32.signBit q := rfl

end Submission.R25Checker
