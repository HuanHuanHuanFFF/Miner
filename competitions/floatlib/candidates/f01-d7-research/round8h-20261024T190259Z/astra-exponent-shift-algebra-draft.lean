
/- Raw-word algebra for the one-native-product route. No floating-point reassociation. -/
namespace Submission.R14ExponentAlgebra

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

theorem mkBits_nat (sign : Bool) (e f : Nat) (he : e < 256) (hf : f < 8388608) :
    (Model.NativeBinary32.mkBits sign e f).toNat =
      (if sign then 2147483648 else 0) + e * 8388608 + f := by
  have heMask : (UInt32.ofNat e &&& 255).toNat = e := by
    rw [UInt32.toNat_and]
    change (e % 4294967296) &&& (2 ^ 8 - 1) = e
    rw [Nat.mod_eq_of_lt (by omega), Nat.and_two_pow_sub_one_eq_mod,
      Nat.mod_eq_of_lt he]
  have heField : ((UInt32.ofNat e &&& 255) <<< 23).toNat = e * 8388608 := by
    rw [UInt32.toNat_shiftLeft, heMask]
    change (e <<< 23) % 4294967296 = e * 8388608
    rw [Nat.shiftLeft_eq]
    change (e * 8388608) % 4294967296 = _
    exact Nat.mod_eq_of_lt (by omega)
  have hfField : (UInt32.ofNat f &&& 8388607).toNat = f := by
    rw [UInt32.toNat_and]
    change (f % 4294967296) &&& (2 ^ 23 - 1) = f
    rw [Nat.mod_eq_of_lt (by omega), Nat.and_two_pow_sub_one_eq_mod,
      Nat.mod_eq_of_lt hf]
  have horEF : e * 8388608 ||| f = e * 8388608 + f := by
    have h := (Nat.two_pow_add_eq_or_of_lt (show f < 2 ^ 23 by exact hf) e).symm
    simpa [Nat.mul_comm] using h
  have hlow : e * 8388608 + f < 2 ^ 31 := by norm_num; omega
  have horSign : 2147483648 ||| (e * 8388608 + f) =
      2147483648 + (e * 8388608 + f) := by
    simpa using (Nat.two_pow_add_eq_or_of_lt hlow 1).symm
  cases sign <;>
    simp [Model.NativeBinary32.mkBits, UInt32.toNat_or, heField, hfField,
      Nat.or_assoc, horEF, horSign, Nat.add_assoc]

theorem translated_nat (em f s : Nat)
    (he0 : 173 ≤ em) (he : em ≤ 174) (hf : f < 8388608)
    (hs : 128 ≤ s) (hs' : s ≤ 380) :
    (em * 8388608 + f +
      ((((4294966996 + s) % 4294967296) <<< 23) % 4294967296)) % 4294967296 =
      (em + s - 300) * 8388608 + f := by
  have hout : (em + s - 300) * 8388608 + f < 4294967296 := by omega
  rw [Nat.shiftLeft_eq]
  change (em * 8388608 + f +
      (((4294966996 + s) % 4294967296 * 8388608) % 4294967296)) % 4294967296 = _
  by_cases hsmall : s < 300
  · have hsub : (4294966996 + s) % 4294967296 = 4294966996 + s :=
      Nat.mod_eq_of_lt (by omega)
    rw [hsub]
    have hdEq : (4294966996 + s) * 8388608 =
        4294967296 * 8388607 + (s + 212) * 8388608 := by omega
    have hdLt : (s + 212) * 8388608 < 4294967296 := by omega
    have hd : ((4294966996 + s) * 8388608) % 4294967296 = (s + 212) * 8388608 := by
      rw [hdEq]
      simp [Nat.add_mod, Nat.mod_eq_of_lt hdLt]
    rw [hd]
    have hnum : em * 8388608 + f + (s + 212) * 8388608 =
        4294967296 + ((em + s - 300) * 8388608 + f) := by omega
    rw [hnum]
    simp [Nat.add_mod, Nat.mod_eq_of_lt hout]
  · have hsubEq : 4294966996 + s = 4294967296 + (s - 300) := by omega
    have hsub : (4294966996 + s) % 4294967296 = s - 300 := by
      rw [hsubEq]
      simp [Nat.add_mod, Nat.mod_eq_of_lt (show s - 300 < 4294967296 by omega)]
    rw [hsub, Nat.mod_eq_of_lt (show (s - 300) * 8388608 < 4294967296 by omega)]
    have hnum : em * 8388608 + f + (s - 300) * 8388608 =
        (em + s - 300) * 8388608 + f := by omega
    rw [hnum]
    exact Nat.mod_eq_of_lt hout

theorem shift_magnitude (em f : Nat) (s : UInt32)
    (he0 : 173 ≤ em) (he : em ≤ 174) (hf : f < 8388608)
    (hs : 128 ≤ s.toNat) (hs' : s.toNat ≤ 380) :
    (Model.NativeBinary32.mkBits false em f + ((s - 300) <<< 23)).toNat =
      (em + s.toNat - 300) * 8388608 + f := by
  rw [UInt32.toNat_add, mkBits_nat false em f (by omega) hf,
    UInt32.toNat_shiftLeft, UInt32.toNat_sub]
  simp only [Bool.false_eq_true, ↓reduceIte, Nat.zero_add]
  change (em * 8388608 + f +
      ((((4294966996 + s.toNat) % 4294967296) <<< 23) % 4294967296)) % 4294967296 = _
  exact translated_nat em f s.toNat he0 he hf hs hs'

theorem shifted_word (sign : Bool) (em f : Nat) (s : UInt32)
    (he0 : 173 ≤ em) (he : em ≤ 174) (hf : f < 8388608)
    (hs : 128 ≤ s.toNat) (hs' : s.toNat ≤ 380) :
    (if sign then (2147483648 : UInt32) else 0) |||
        (Model.NativeBinary32.mkBits false em f + ((s - 300) <<< 23)) =
      Model.NativeBinary32.mkBits sign (em + s.toNat - 300) f := by
  apply UInt32.toNat_inj.mp
  rw [UInt32.toNat_or, shift_magnitude em f s he0 he hf hs hs',
    mkBits_nat sign (em + s.toNat - 300) f (by omega) hf]
  have hlow : (em + s.toNat - 300) * 8388608 + f < 2 ^ 31 := by norm_num; omega
  have hor : 2147483648 ||| ((em + s.toNat - 300) * 8388608 + f) =
      2147483648 + ((em + s.toNat - 300) * 8388608 + f) := by
    simpa using (Nat.two_pow_add_eq_or_of_lt hlow 1).symm
  cases sign <;> simp [hor, Nat.add_assoc]

end Submission.R14ExponentAlgebra
