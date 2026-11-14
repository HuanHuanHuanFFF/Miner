/- Proof-only compatibility of two standard sign-extension expressions.
   Covers every UInt64, not only the signed62 encoder domain. -/
namespace Submission.R24TwoChain128HighCompat
open FloatLib.Numerics.FixedWord
open Submission.R24TwoChain128 (high)

theorem high_eq_neg_top_bit (q : UInt64) : high q = 0 - (q >>> 63) := by
  have hs : (q >>> 63).toNat = q.toNat / 2 ^ 63 := by
    simpa only [Nat.shiftRight_eq_div_pow] using
      shiftRight_toNat q 63 (by decide)
  by_cases h : q.toNat < 2 ^ 63
  · have hw : q < 0x8000000000000000 := UInt64.lt_iff_toNat_lt.mpr h
    have hz : q >>> 63 = 0 := UInt64.toNat_inj.mp (hs.trans (Nat.div_eq_of_lt h))
    rw [high, if_pos hw, hz]
    decide
  · have hw : ¬q < 0x8000000000000000 := by
      simpa only [UInt64.lt_iff_toNat_lt] using h
    have hd : q.toNat / 2 ^ 63 = 1 := by
      apply (Nat.div_eq_iff (Nat.two_pow_pos 63)).2
      constructor
      · simpa only [Nat.one_mul] using Nat.le_of_not_gt h
      · have hu := q.toNat_lt
        omega
    have ho : q >>> 63 = 1 := UInt64.toNat_inj.mp (hs.trans hd)
    rw [high, if_neg hw, ho]
    decide

end Submission.R24TwoChain128HighCompat
