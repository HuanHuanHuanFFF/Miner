/- Draft / NOT_RUN. Paper option, not a new runtime/CI candidate.
   Normal significands separated by >=26 raw exponent steps round back to hi.
   Opposite signs at a power-of-two hi need the distinct lower-binade proof. -/
namespace Submission.R14FarAdd

open FloatLib.Numerics

theorem small_remainder (r d : Nat) (hr : r < 16777216) (hd : 26 ≤ d) :
    2 * r < 2 ^ d ∧ 2 * r < 2 ^ (d - 1) := by
  have h0 : 2 ^ 26 ≤ 2 ^ d := Nat.pow_le_pow_right (by decide) hd
  have h1 : 2 ^ 25 ≤ 2 ^ (d - 1) :=
    Nat.pow_le_pow_right (by decide) (by omega)
  norm_num at h0 h1
  omega

theorem log_add (m r d : Nat) (hm0 : 8388608 ≤ m) (hm1 : m < 16777216)
    (hr : r < 2 ^ d) : (m * 2 ^ d + r).log2 = 23 + d := by
  have hd0 := Nat.two_pow_pos d
  have hpos := Nat.mul_pos (show 0 < m by omega) hd0
  have hn : m * 2 ^ d + r ≠ 0 := by omega
  have hlo := Nat.mul_le_mul_right (2 ^ d) hm0
  have hhi := Nat.mul_le_mul_right (2 ^ d) (show m + 1 ≤ 16777216 by omega)
  rw [Nat.add_mul, Nat.one_mul] at hhi
  apply (Nat.log2_eq_iff hn).2
  have hp0 : 2 ^ (23 + d) = 8388608 * 2 ^ d := by rw [Nat.pow_add]; norm_num
  have hp1 : 2 ^ (23 + d + 1) = 16777216 * 2 ^ d := by
    rw [show 23 + d + 1 = 24 + d by omega, Nat.pow_add]
    norm_num
  rw [hp0, hp1]
  constructor <;> omega

theorem log_sub_large (m r d : Nat) (hm0 : 8388608 < m) (hm1 : m < 16777216)
    (hr : r < 2 ^ d) : (m * 2 ^ d - r).log2 = 23 + d := by
  have hd0 := Nat.two_pow_pos d
  have hmul : m * 2 ^ d = (m - 1) * 2 ^ d + 2 ^ d := by
    calc m * 2 ^ d = (m - 1 + 1) * 2 ^ d := by rw [show m - 1 + 1 = m by omega]
         _ = (m - 1) * 2 ^ d + 2 ^ d := by rw [Nat.add_mul, Nat.one_mul]
  have hlo := Nat.mul_le_mul_right (2 ^ d) (show 8388608 ≤ m - 1 by omega)
  have hhi := Nat.mul_le_mul_right (2 ^ d) (show m ≤ 16777215 by omega)
  have hn : m * 2 ^ d - r ≠ 0 := by omega
  apply (Nat.log2_eq_iff hn).2
  have hp0 : 2 ^ (23 + d) = 8388608 * 2 ^ d := by rw [Nat.pow_add]; norm_num
  have hp1 : 2 ^ (23 + d + 1) = 16777216 * 2 ^ d := by
    rw [show 23 + d + 1 = 24 + d by omega, Nat.pow_add]
    norm_num
  rw [hp0, hp1]
  constructor <;> omega

theorem log_sub_power (r d : Nat) (hr0 : 0 < r) (hr : r < 2 ^ d) :
    (8388608 * 2 ^ d - r).log2 = 22 + d := by
  have hd0 := Nat.two_pow_pos d
  have hn : 8388608 * 2 ^ d - r ≠ 0 := by omega
  apply (Nat.log2_eq_iff hn).2
  have hp0 : 2 ^ (22 + d) = 4194304 * 2 ^ d := by rw [Nat.pow_add]; norm_num
  have hp1 : 2 ^ (22 + d + 1) = 8388608 * 2 ^ d := by
    rw [show 22 + d + 1 = 23 + d by omega, Nat.pow_add]
    norm_num
  rw [hp0, hp1]
  constructor <;> omega

theorem rounded_add (m r d : Nat) (hm0 : 8388608 ≤ m) (hm1 : m < 16777216)
    (hr : r < 16777216) (hd : 26 ≤ d) :
    Submission.R14NatNormal.rounded (m * 2 ^ d + r) = m := by
  have hs := small_remainder r d hr hd
  have hrD : r < 2 ^ d := by omega
  unfold Submission.R14NatNormal.rounded
  rw [log_add m r d hm0 hm1 hrD, show 23 + d - 23 = d by omega]
  exact Submission.R14NearestMultiple.shift_add_small m r d hs.1

theorem rounded_sub_large (m r d : Nat) (hm0 : 8388608 < m) (hm1 : m < 16777216)
    (hr0 : 0 < r) (hr : r < 16777216) (hd : 26 ≤ d) :
    Submission.R14NatNormal.rounded (m * 2 ^ d - r) = m := by
  have hs := small_remainder r d hr hd
  have hrD : r < 2 ^ d := by omega
  unfold Submission.R14NatNormal.rounded
  rw [log_sub_large m r d hm0 hm1 hrD, show 23 + d - 23 = d by omega]
  exact Submission.R14NearestMultiple.shift_sub_small m r d (by omega) hr0 hs.1

theorem rounded_sub_power (r d : Nat) (hr0 : 0 < r)
    (hr : r < 16777216) (hd : 26 ≤ d) :
    Submission.R14NatNormal.rounded (8388608 * 2 ^ d - r) = 16777216 := by
  have hs := small_remainder r d hr hd
  have hrD : r < 2 ^ d := by omega
  have hpow : 2 ^ d = 2 * 2 ^ (d - 1) := by
    have h := Nat.pow_succ 2 (d - 1)
    rw [show d - 1 + 1 = d by omega] at h
    simpa only [Nat.mul_comm] using h
  have hn : 8388608 * 2 ^ d - r = 16777216 * 2 ^ (d - 1) - r := by
    rw [hpow]
    congr 1
    ring
  unfold Submission.R14NatNormal.rounded
  rw [log_sub_power r d hr0 hrD, show 22 + d - 23 = d - 1 by omega, hn]
  exact Submission.R14NearestMultiple.shift_sub_small 16777216 r (d - 1)
    (by decide) hr0 hs.2

end Submission.R14FarAdd
