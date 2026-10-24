
/- R14 proof probe. Runtime definitions above remain the retained df5c source. -/
namespace Submission.R14ScaleShape

open FloatLib.Floats.Formats.BinaryInterchange
open Model.NativeBinary32

theorem mantissa_product_bounds (a b : Nat)
    (ha : 8388608 ≤ a) (ha' : a < 16777216)
    (hb : 8388608 ≤ b) (hb' : b < 16777216) :
    70368744177664 ≤ a * b ∧ a * b ≤ 281474943156225 := by
  have hlo := Nat.mul_le_mul ha hb
  have hhi := Nat.mul_le_mul (show a ≤ 16777215 by omega)
    (show b ≤ 16777215 by omega)
  norm_num at hlo hhi
  exact ⟨hlo, hhi⟩

theorem leading_bounds (p : UInt64)
    (hlo : 70368744177664 ≤ p.toNat)
    (hhi : p.toNat < 281474976710656) :
    46 ≤ p.log2.toNat ∧ p.log2.toNat ≤ 47 := by
  have hn : p.toNat ≠ 0 := by omega
  have hl : 46 ≤ p.toNat.log2 := (Nat.le_log2 hn).2 (by norm_num; exact hlo)
  have hh : p.toNat.log2 < 48 := (Nat.log2_lt hn).2 (by norm_num; exact hhi)
  simp only [FloatLib.Numerics.FixedWord.log2_toNat]
  omega

def rounded (p : UInt64) : UInt64 :=
  FloatLib.Numerics.FixedWord.roundShiftRightEven p (p.log2 - 23).toNat

def carryNat (p : UInt64) : Nat := if rounded p = 16777216 then 1 else 0

def fraction (p : UInt64) : Nat :=
  (if rounded p = 16777216 then (8388608 : UInt64) else rounded p).toNat - 8388608

theorem carryNat_le (p : UInt64) : carryNat p ≤ 1 := by
  unfold carryNat
  split <;> omega

/-- The original word rounder uses one identical mantissa rounding throughout this scale band.
The upper bound 379 avoids needing the stronger real-mantissa upper bound at scale 380. -/
theorem normal_form (sign : Bool) (p : UInt64) (s : Nat)
    (hp : p ≠ 0)
    (hl : 46 ≤ p.log2.toNat) (hh : p.log2.toNat ≤ 47)
    (hs : 174 ≤ s) (hs' : s ≤ 379) :
    roundProduct sign p (UInt64.ofNat (s - 2)) =
      mkBits sign (p.log2.toNat + s + carryNat p - 173) (fraction p) := by
  let scale : UInt64 := UInt64.ofNat (s - 2)
  have hscale : scale.toNat = s - 2 := by
    change (s - 2) % 18446744073709551616 = s - 2
    omega
  have hpos : (p.log2 + scale).toNat = p.log2.toNat + s - 2 := by
    rw [UInt64.toNat_add, hscale]
    change (p.log2.toNat + (s - 2)) % 18446744073709551616 = _
    omega
  have hpos1 : (p.log2 + scale + 1).toNat = p.log2.toNat + s - 1 := by
    rw [UInt64.toNat_add, hpos]
    change (p.log2.toNat + s - 2 + 1) % 18446744073709551616 = _
    omega
  have hlead : ¬p.log2 < 23 := by
    rw [UInt64.lt_iff_toNat_lt]
    change ¬p.log2.toNat < 23
    omega
  have hnormal : ¬p.log2 + scale < 172 := by
    rw [UInt64.lt_iff_toNat_lt, hpos]
    change ¬p.log2.toNat + s - 2 < 172
    omega
  have hfinite : ¬(425 : UInt64) < p.log2 + scale := by
    rw [UInt64.lt_iff_toNat_lt, hpos]
    change ¬425 < p.log2.toNat + s - 2
    omega
  have hfinite1 : ¬(425 : UInt64) < p.log2 + scale + 1 := by
    rw [UInt64.lt_iff_toNat_lt, hpos1]
    change ¬425 < p.log2.toNat + s - 1
    omega
  have hsub : (171 : UInt64) ≤ p.log2 + scale := by
    rw [UInt64.le_iff_toNat_le, hpos]
    change 171 ≤ p.log2.toNat + s - 2
    omega
  have hsub1 : (171 : UInt64) ≤ p.log2 + scale + 1 := by
    rw [UInt64.le_iff_toNat_le, hpos1]
    change 171 ≤ p.log2.toNat + s - 1
    omega
  have he : (p.log2 + scale - 171).toNat = p.log2.toNat + s - 173 := by
    rw [UInt64.toNat_sub_of_le _ _ hsub, hpos]
    change p.log2.toNat + s - 2 - 171 = _
    omega
  have he1 : (p.log2 + scale + 1 - 171).toNat =
      p.log2.toNat + s + 1 - 173 := by
    rw [UInt64.toNat_sub_of_le _ _ hsub1, hpos1]
    change p.log2.toNat + s - 1 - 171 = _
    omega
  change roundProduct sign p scale = _
  by_cases hc : FloatLib.Numerics.FixedWord.roundShiftRightEven
      p (p.log2 - 23).toNat = 16777216
  · simp only [roundProduct, rounded, carryNat, fraction, beq_iff_eq, hp,
      hlead, hnormal, hc, hfinite1, he1, ↓reduceIte]
  · simp only [roundProduct, rounded, carryNat, fraction, beq_iff_eq, hp,
      hlead, hnormal, hc, hfinite, he, ↓reduceIte, Nat.add_zero]

theorem first_product_form (p : UInt64)
    (hp : p ≠ 0) (hl : 46 ≤ p.log2.toNat) (hh : p.log2.toNat ≤ 47) :
    roundProduct false p 298 =
      mkBits false (p.log2.toNat + carryNat p + 127) (fraction p) := by
  have h := normal_form false p 300 hp hl hh (by decide) (by decide)
  have he : p.log2.toNat + 300 + carryNat p - 173 =
      p.log2.toNat + carryNat p + 127 := by omega
  simpa only [he] using h

end Submission.R14ScaleShape
