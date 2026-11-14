namespace Submission.R24WordGap128
open FloatLib.Numerics.FixedWord
@[inline] def gap (num : UInt128) (den mant : UInt64) : UInt128 :=
  let product := mul64 mant den
  if UInt128.less num product then UInt128.sub product num
  else UInt128.sub num product


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

end Submission.R24WordGap128
