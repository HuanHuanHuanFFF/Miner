
/- R14: bounds of the actual nearest-even word mantissa, including the scale380 carry gap. -/
namespace Submission.R14RoundedBounds

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

def rounded (p : UInt64) : UInt64 :=
  FixedWord.roundShiftRightEven p (p.log2 - 23).toNat

def normalized (p : UInt64) : UInt64 :=
  if rounded p = 16777216 then 8388608 else rounded p

theorem rounded_bounds (p : UInt64)
    (hlo : 70368744177664 ≤ p.toNat) (hhi : p.toNat < 281474976710656) :
    8388608 ≤ (rounded p).toNat ∧ (rounded p).toNat ≤ 16777216 := by
  have hn : p.toNat ≠ 0 := by omega
  have hl : 46 ≤ p.toNat.log2 := (Nat.le_log2 hn).2 (by norm_num; exact hlo)
  have hh : p.toNat.log2 < 48 := (Nat.log2_lt hn).2 (by norm_num; exact hhi)
  have hle : (23 : UInt64) ≤ p.log2 := by
    rw [UInt64.le_iff_toNat_le, FixedWord.log2_toNat]
    change 23 ≤ p.toNat.log2
    omega
  have hshift : (p.log2 - 23).toNat = p.toNat.log2 - 23 := by
    rw [UInt64.toNat_sub_of_le _ _ hle, FixedWord.log2_toNat]
    rfl
  have hr : (rounded p).toNat =
      roundShiftRightEven p.toNat (p.toNat.log2 - 23) := by
    unfold rounded
    rw [FixedWord.roundShiftRightEven_toNat, hshift]
  have hlow := Nat.log2_self_le hn
  have hupp := Nat.lt_log2_self (n := p.toNat)
  have hquotient :
      8388608 ≤ Nat.shiftRight p.toNat (p.toNat.log2 - 23) ∧
      Nat.shiftRight p.toNat (p.toNat.log2 - 23) < 16777216 := by
    have hc : p.toNat.log2 = 46 ∨ p.toNat.log2 = 47 := by omega
    rcases hc with hc | hc <;>
      simp only [hc] at hlow hupp ⊢ <;>
      norm_num [Nat.shiftRight_eq_div_pow] at hlow hupp ⊢ <;> omega
  have hroundLo := shiftRight_le_roundShiftRightEven p.toNat (p.toNat.log2 - 23)
  have hroundHi := roundShiftRightEven_le_shiftRight_add1 p.toNat (p.toNat.log2 - 23)
  rw [hr]
  omega

theorem normalized_bounds (p : UInt64)
    (hlo : 70368744177664 ≤ p.toNat) (hhi : p.toNat < 281474976710656) :
    8388608 ≤ (normalized p).toNat ∧ (normalized p).toNat < 16777216 := by
  have hb := rounded_bounds p hlo hhi
  by_cases hc : rounded p = 16777216
  · simp [normalized, hc]
  · have hcNat : (rounded p).toNat ≠ 16777216 := by
      intro he
      apply hc
      apply UInt64.toNat_inj.mp
      exact he
    simp only [normalized, hc, ↓reduceIte]
    omega

/-- Actual 24x24 products have an extra gap below 2^48. This rules out a carry from h47;
it is the missing finite-result fact for extending the exponent-sum bound from379 to380. -/
theorem no_carry_at_47 (p : UInt64)
    (hmax : p.toNat ≤ 281474943156225) (hlog : p.log2.toNat = 47) :
    rounded p ≠ 16777216 := by
  have hle : (23 : UInt64) ≤ p.log2 := by
    rw [UInt64.le_iff_toNat_le, hlog]
    decide
  have hshift : (p.log2 - 23).toNat = 24 := by
    rw [UInt64.toNat_sub_of_le _ _ hle, hlog]
    rfl
  have hr : (rounded p).toNat = roundShiftRightEven p.toNat 24 := by
    unfold rounded
    rw [FixedWord.roundShiftRightEven_toNat, hshift]
  have hquotient : p.toNat / 16777216 ≤ 16777214 := by omega
  have hroundHi := roundShiftRightEven_le_shiftRight_add1 p.toNat 24
  norm_num [Nat.shiftRight_eq_div_pow] at hroundHi
  have hresult : (rounded p).toNat ≤ 16777215 := by
    rw [hr]
    omega
  intro hc
  have he := congrArg UInt64.toNat hc
  change (rounded p).toNat = 16777216 at he
  omega

end Submission.R14RoundedBounds
