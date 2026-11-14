/- Generic old-ContractTensor mathematical helper. No candidate-generation or
   floating-point accuracy premise: the rounded candidate is arbitrary.
   Core gap/check runtime uses fixed words; the normal wrapper also checks Int
   exponent bounds. Typing/replay/dependency audit NOT_RUN. -/
namespace Submission.R24WordGap128

open FloatLib.Numerics.FixedWord

/-- Absolute difference from the exact 64 by 64 product, without wrapping. -/
@[inline] def gap (num : UInt128) (den mant : UInt64) : UInt128 :=
  let product := mul64 mant den
  if UInt128.less num product then UInt128.sub product num
  else UInt128.sub num product

/-- Strict midpoint check; each subtraction is ordered before its value is used. -/
@[inline] def check (num : UInt128) (den mant : UInt64) : Bool :=
  let residue := gap num den mant
  decide ((0 : UInt64) < den) &&
    (decide ((0 : UInt64) < mant) &&
      ((residue.hi == 0) &&
        (decide (residue.lo < den) && decide (residue.lo < den - residue.lo))))

theorem gap_toNat_cases (num : UInt128) (den mant : UInt64) :
    (num.toNat < mant.toNat * den.toNat ∧
      (gap num den mant).toNat = mant.toNat * den.toNat - num.toNat) ∨
    (mant.toNat * den.toNat ≤ num.toNat ∧
      (gap num den mant).toNat = num.toNat - mant.toNat * den.toNat) := by
  by_cases h : UInt128.less num (mul64 mant den) = true
  · left
    have hlt := UInt128.less_eq_true_iff.mp h
    have hsub := UInt128.sub_toNat (mul64 mant den) num hlt.le
    constructor
    · simpa only [mul64_toNat] using hlt
    · simpa only [gap, if_pos h, mul64_toNat] using hsub
  · right
    have hle : (mul64 mant den).toNat ≤ num.toNat := by
      by_contra hn
      have hlt : num.toNat < (mul64 mant den).toNat := by omega
      exact h (UInt128.less_eq_true_iff.mpr hlt)
    have hsub := UInt128.sub_toNat num (mul64 mant den) hle
    constructor
    · simpa only [mul64_toNat] using hle
    · simpa only [gap, if_neg h, mul64_toNat] using hsub

theorem check_midpoint_bounds (num : UInt128) (den mant : UInt64)
    (h : check num den mant = true) :
    0 < den.toNat ∧ 0 < mant.toNat ∧
      den.toNat * (2 * mant.toNat - 1) < 2 * num.toNat ∧
      2 * num.toNat < den.toNat * (2 * mant.toNat + 1) := by
  let residue := gap num den mant
  have hh : (0 : UInt64) < den ∧ ((0 : UInt64) < mant ∧
      (residue.hi = 0 ∧ (residue.lo < den ∧ residue.lo < den - residue.lo))) := by
    simpa only [check, Bool.and_eq_true, decide_eq_true_eq, beq_iff_eq] using h
  have hd : 0 < den.toNat := by
    simpa only [UInt64.toNat_zero] using UInt64.lt_iff_toNat_lt.mp hh.1
  have hm : 0 < mant.toNat := by
    simpa only [UInt64.toNat_zero] using UInt64.lt_iff_toNat_lt.mp hh.2.1
  have hlo := UInt64.lt_iff_toNat_lt.mp hh.2.2.2.1
  have hhalf := UInt64.lt_iff_toNat_lt.mp hh.2.2.2.2
  have hsub : (den - residue.lo).toNat = den.toNat - residue.lo.toNat :=
    UInt64.toNat_sub_of_le den residue.lo (UInt64.le_iff_toNat_le.mpr hlo.le)
  rw [hsub] at hhalf
  have htwice : 2 * residue.lo.toNat < den.toNat := by omega
  have hresidue : residue.toNat = residue.lo.toNat := by
    simp only [UInt128.toNat, hh.2.2.1, UInt64.toNat_zero, zero_mul, add_zero]
  have hgap := gap_toNat_cases num den mant
  change (num.toNat < mant.toNat * den.toNat ∧
      residue.toNat = mant.toNat * den.toNat - num.toNat) ∨
    (mant.toNat * den.toNat ≤ num.toNat ∧
      residue.toNat = num.toNat - mant.toNat * den.toNat) at hgap
  rw [hresidue] at hgap
  have hcut : 2 * mant.toNat - 1 + 1 = 2 * mant.toNat := by omega
  have hexpand : den.toNat * (2 * mant.toNat - 1) + den.toNat =
      2 * (mant.toNat * den.toNat) := by
    calc
      den.toNat * (2 * mant.toNat - 1) + den.toNat =
          den.toNat * ((2 * mant.toNat - 1) + 1) := by ring
      _ = den.toNat * (2 * mant.toNat) := by rw [hcut]
      _ = 2 * (mant.toNat * den.toNat) := by ring
  have hmid : den.toNat * (2 * mant.toNat - 1) < 2 * num.toNat ∧
      2 * num.toNat < den.toNat * (2 * mant.toNat + 1) := by
    rcases hgap with ⟨hlt, hres⟩ | ⟨hle, hres⟩
    · have hsum := Nat.sub_add_cancel hlt.le
      constructor <;> nlinarith
    · have hsum := Nat.sub_add_cancel hle
      constructor <;> nlinarith
  exact ⟨hd, hm, hmid.1, hmid.2⟩

theorem check_sound (num : UInt128) (den mant : UInt64)
    (h : check num den mant = true) :
    FloatLib.Numerics.roundQuotientEven num.toNat den.toNat = mant.toNat := by
  obtain ⟨hd, hm, hl, hu⟩ := check_midpoint_bounds num den mant h
  exact Submission.R24CellPrimitive.quotient_strict_midpoint
    num.toNat den.toNat mant.toNat hd hm hl hu

@[inline] def normalCheck (num : UInt128) (den mant : UInt64) (exponent : Int) : Bool :=
  check num den mant &&
    (decide ((8388608 : UInt64) < mant) &&
      (decide (mant < (16777216 : UInt64)) &&
        (decide (1 ≤ exponent + 150) && decide (exponent + 150 ≤ 254))))

theorem normalCheck_sound (sign : Bool) (num : UInt128) (den mant : UInt64)
    (exponent : Int) (h : normalCheck num den mant exponent = true) :
    FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.roundRatScaled
        sign num.toNat den.toNat exponent =
      FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.mkBits
        sign (exponent + 150).toNat (mant.toNat - 8388608) := by
  have hh : check num den mant = true ∧ ((8388608 : UInt64) < mant ∧
      (mant < (16777216 : UInt64) ∧
        (1 ≤ exponent + 150 ∧ exponent + 150 ≤ 254))) := by
    simpa only [normalCheck, Bool.and_eq_true, decide_eq_true_eq] using h
  have hmlo : 8388608 < mant.toNat := UInt64.lt_iff_toNat_lt.mp hh.2.1
  have hmhi : mant.toNat < 16777216 := UInt64.lt_iff_toNat_lt.mp hh.2.2.1
  obtain ⟨hd, _, hl, hu⟩ := check_midpoint_bounds num den mant hh.1
  exact Submission.R24CellPrimitive.native32_strict_cell
    sign num.toNat den.toNat mant.toNat exponent hd hmlo hmhi
    hh.2.2.2.1 hh.2.2.2.2 hl hu

end Submission.R24WordGap128
