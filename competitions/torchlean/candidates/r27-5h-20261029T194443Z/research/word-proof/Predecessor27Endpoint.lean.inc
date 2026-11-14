-- Original extension; append inside predecessor27's Submission namespace.
-- Exact base SHA256: f92ee2c9a29de78dc434ad158b7141c0e4b5a67a5a198a353d59a4703481aa67.
-- This source does not copy the predecessor's implementation or proof.
namespace R27WordEndpoint

@[inline] def top128 (hi : UInt64) : UInt64 :=
  if hi < 0x8000000000000000 then 0 else 0xffffffffffffffff

def signedPair (lo hi : UInt64) : Int :=
  (lo.toNat : Int) +
    ((hi.toNat : Int) - if hi.toNat < 9223372036854775808 then 0 else 18446744073709551616) *
      18446744073709551616

theorem top128_value (lo hi : UInt64) :
    YC (top128 hi) hi lo = signedPair lo hi := by
  unfold top128
  rw [UInt64.lt_iff_toNat_lt]
  change YC (if hi.toNat < 9223372036854775808 then 0 else 0xffffffffffffffff) hi lo = _
  by_cases h : hi.toNat < 9223372036854775808
  · rw [if_pos h]
    simp only [YC, signedPair, h, if_true]
    norm_num
    ring
  · rw [if_neg h]
    simp only [YC, signedPair, h, if_false]
    norm_num
    ring

@[inline] def finish128 (lo hi : UInt64) (exponent : Int) (negativeZero : Bool) : UInt32 :=
  Ybo (top128 hi) hi lo exponent negativeZero

theorem finish128_exact (lo hi : UInt64) (exponent : Int) (negativeZero : Bool) :
    finish128 lo hi exponent negativeZero =
      ExactRuntime.finishWord (signedPair lo hi) exponent negativeZero := by
  unfold finish128
  rw [X7, top128_value]

end R27WordEndpoint
