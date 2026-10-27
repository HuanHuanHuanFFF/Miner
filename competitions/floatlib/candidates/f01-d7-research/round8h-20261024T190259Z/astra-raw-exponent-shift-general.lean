/- Draft reusable word-algebra extension. Depends only on the earlier
Submission.R14ExponentAlgebra.mkBits_nat packing theorem, not any Float32 operation.
No runtime candidate or floating equivalence follows merely from this identity. -/
namespace Submission.R14ExponentAlgebra

open FloatLib.Floats.Formats.BinaryInterchange

theorem translated_nat_general (em f s k : Nat)
    (he : em < 256) (hf : f < 8388608)
    (hs : s < 512) (hk : k ≤ 512)
    (hE0 : 0 < em + s - k) (hE : em + s - k < 255) :
    (em * 8388608 + f +
      (((((4294967296 - k + s) % 4294967296) <<< 23) % 4294967296))) % 4294967296 =
      (em + s - k) * 8388608 + f := by
  have hks : k < em + s := by omega
  have hout : (em + s - k) * 8388608 + f < 4294967296 := by omega
  rw [Nat.shiftLeft_eq]
  change (em * 8388608 + f +
      (((4294967296 - k + s) % 4294967296 * 8388608) % 4294967296)) % 4294967296 = _
  by_cases hsmall : s < k
  · have hsub : (4294967296 - k + s) % 4294967296 = 4294967296 - k + s :=
      Nat.mod_eq_of_lt (by omega)
    rw [hsub]
    have hdEq : (4294967296 - k + s) * 8388608 =
        4294967296 * 8388607 + (s + 512 - k) * 8388608 := by omega
    have hdLt : (s + 512 - k) * 8388608 < 4294967296 := by omega
    have hd : ((4294967296 - k + s) * 8388608) % 4294967296 =
        (s + 512 - k) * 8388608 := by
      rw [hdEq]
      simp [Nat.add_mod, Nat.mod_eq_of_lt hdLt]
    rw [hd]
    have hnum : em * 8388608 + f + (s + 512 - k) * 8388608 =
        4294967296 + ((em + s - k) * 8388608 + f) := by omega
    rw [hnum]
    simp [Nat.add_mod, Nat.mod_eq_of_lt hout]
  · have hsubEq : 4294967296 - k + s = 4294967296 + (s - k) := by omega
    have hsub : (4294967296 - k + s) % 4294967296 = s - k := by
      rw [hsubEq]
      simp [Nat.add_mod, Nat.mod_eq_of_lt (show s - k < 4294967296 by omega)]
    rw [hsub, Nat.mod_eq_of_lt (show (s - k) * 8388608 < 4294967296 by omega)]
    have hnum : em * 8388608 + f + (s - k) * 8388608 =
        (em + s - k) * 8388608 + f := by omega
    rw [hnum]
    exact Nat.mod_eq_of_lt hout

theorem shifted_word_general (sign : Bool) (em f : Nat) (s k : UInt32)
    (he : em < 256) (hf : f < 8388608)
    (hs : s.toNat < 512) (hk : k.toNat ≤ 512)
    (hE0 : 0 < em + s.toNat - k.toNat)
    (hE : em + s.toNat - k.toNat < 255) :
    (if sign then (2147483648 : UInt32) else 0) |||
        (Model.NativeBinary32.mkBits false em f + ((s - k) <<< 23)) =
      Model.NativeBinary32.mkBits sign (em + s.toNat - k.toNat) f := by
  have hmag :
      (Model.NativeBinary32.mkBits false em f + ((s - k) <<< 23)).toNat =
        (em + s.toNat - k.toNat) * 8388608 + f := by
    rw [UInt32.toNat_add, mkBits_nat false em f he hf,
      UInt32.toNat_shiftLeft, UInt32.toNat_sub]
    simp only [Bool.false_eq_true, ↓reduceIte, Nat.zero_add]
    change (em * 8388608 + f +
      (((((4294967296 - k.toNat + s.toNat) % 4294967296) <<< 23) % 4294967296))) % 4294967296 = _
    exact translated_nat_general em f s.toNat k.toNat he hf hs hk hE0 hE
  apply UInt32.toNat_inj.mp
  rw [UInt32.toNat_or, hmag, mkBits_nat sign (em + s.toNat - k.toNat) f (by omega) hf]
  have hlow : (em + s.toNat - k.toNat) * 8388608 + f < 2 ^ 31 := by norm_num; omega
  have hor : 2147483648 ||| ((em + s.toNat - k.toNat) * 8388608 + f) =
      2147483648 + ((em + s.toNat - k.toNat) * 8388608 + f) := by
    simpa using (Nat.two_pow_add_eq_or_of_lt hlow 1).symm
  cases sign <;> simp [hor, Nat.add_assoc]

/-- The signed64 conversion already carries the sign in its raw word.
This version preserves that stored sign while adding the exponent delta. -/
theorem shifted_signed_word_general (sign : Bool) (em f : Nat) (s k : UInt32)
    (he : em < 256) (hf : f < 8388608)
    (hs : s.toNat < 512) (hk : k.toNat ≤ 512)
    (hE0 : 0 < em + s.toNat - k.toNat)
    (hE : em + s.toNat - k.toNat < 255) :
    Model.NativeBinary32.mkBits sign em f + ((s - k) <<< 23) =
      Model.NativeBinary32.mkBits sign (em + s.toNat - k.toNat) f := by
  let delta := ((((4294967296 - k.toNat + s.toNat) % 4294967296) <<< 23) % 4294967296)
  have hmag : (em * 8388608 + f + delta) % 4294967296 =
      (em + s.toNat - k.toNat) * 8388608 + f :=
    translated_nat_general em f s.toNat k.toNat he hf hs hk hE0 hE
  apply UInt32.toNat_inj.mp
  rw [UInt32.toNat_add, mkBits_nat sign em f he hf,
    UInt32.toNat_shiftLeft, UInt32.toNat_sub,
    mkBits_nat sign (em + s.toNat - k.toNat) f (by omega) hf]
  cases sign
  · change (0 + em * 8388608 + f + delta) % 4294967296 =
      0 + (em + s.toNat - k.toNat) * 8388608 + f
    simpa only [Nat.zero_add] using hmag
  · change (2147483648 + em * 8388608 + f + delta) % 4294967296 =
      2147483648 + (em + s.toNat - k.toNat) * 8388608 + f
    have hsign : 2147483648 % 4294967296 = 2147483648 := by decide
    have hcalc :
        (2147483648 + (em * 8388608 + f + delta)) % 4294967296 =
          2147483648 + ((em + s.toNat - k.toNat) * 8388608 + f) := by
      calc
        _ = (2147483648 % 4294967296 +
              (em * 8388608 + f + delta) % 4294967296) % 4294967296 :=
          Nat.add_mod _ _ _
        _ = (2147483648 + ((em + s.toNat - k.toNat) * 8388608 + f)) % 4294967296 := by
          rw [hsign, hmag]
        _ = _ := Nat.mod_eq_of_lt (by omega)
    simpa only [Nat.add_assoc] using hcalc

end Submission.R14ExponentAlgebra
