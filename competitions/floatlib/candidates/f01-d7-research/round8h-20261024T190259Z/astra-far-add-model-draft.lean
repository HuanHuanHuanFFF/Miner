/- Draft / NOT_RUN. Requires far-add-nat, nearest-multiple, and word-add-model
   bridge drafts. This is mathematical support only, not a public add change. -/
namespace Submission.R14FarAdd

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

def magnitude (same : Bool) (m r d : Nat) : Nat :=
  if same then m * 2 ^ d + r else m * 2 ^ d - r

theorem normalization (same : Bool) (m r d : Nat)
    (hm0 : 8388608 ≤ m) (hm1 : m < 16777216)
    (hr0 : 0 < r) (hr1 : r < 16777216) (hd : 26 ≤ d) :
    24 ≤ (magnitude same m r d).log2 ∧
    (magnitude same m r d).log2 + R14NatNormal.carry (magnitude same m r d) = 23 + d ∧
    R14NatNormal.mantissa (magnitude same m r d) = m := by
  have hs := small_remainder r d hr1 hd
  have hrD : r < 2 ^ d := by omega
  cases same with
  | false =>
    change 24 ≤ (m * 2 ^ d - r).log2 ∧
      (m * 2 ^ d - r).log2 + R14NatNormal.carry (m * 2 ^ d - r) = 23 + d ∧
      R14NatNormal.mantissa (m * 2 ^ d - r) = m
    by_cases hm : m = 8388608
    · subst m
      have hl := log_sub_power r d hr0 hrD
      have hq := rounded_sub_power r d hr0 hr1 hd
      have hc : R14NatNormal.carry (8388608 * 2 ^ d - r) = 1 := by
        simp only [R14NatNormal.carry, hq, if_pos rfl]
      have hm : R14NatNormal.mantissa (8388608 * 2 ^ d - r) = 8388608 := by
        simp only [R14NatNormal.mantissa, hq, if_pos rfl]
      rw [hl, hc, hm]
      omega
    · have hl := log_sub_large m r d (by omega) hm1 hrD
      have hq := rounded_sub_large m r d (by omega) hm1 hr0 hr1 hd
      have hne : m ≠ 16777216 := by omega
      have hc : R14NatNormal.carry (m * 2 ^ d - r) = 0 := by
        simp only [R14NatNormal.carry, hq, if_neg hne]
      have hm : R14NatNormal.mantissa (m * 2 ^ d - r) = m := by
        simp only [R14NatNormal.mantissa, hq, if_neg hne]
      rw [hl, hc, hm]
      omega
  | true =>
    change 24 ≤ (m * 2 ^ d + r).log2 ∧
      (m * 2 ^ d + r).log2 + R14NatNormal.carry (m * 2 ^ d + r) = 23 + d ∧
      R14NatNormal.mantissa (m * 2 ^ d + r) = m
    have hl := log_add m r d hm0 hm1 hrD
    have hq := rounded_add m r d hm0 hm1 hr1 hd
    have hne : m ≠ 16777216 := by omega
    have hc : R14NatNormal.carry (m * 2 ^ d + r) = 0 := by
      simp only [R14NatNormal.carry, hq, if_neg hne]
    have hm : R14NatNormal.mantissa (m * 2 ^ d + r) = m := by
      simp only [R14NatNormal.mantissa, hq, if_neg hne]
    rw [hl, hc, hm]
    omega

theorem spec_add_absorbs (x y : Model FloatFormat.binary32)
    (dx dy : FloatLib.Numerics.Dyadic) (sign same : Bool) (m r d elo : Nat)
    (hx : Model.toDyadic? x = some dx) (hy : Model.toDyadic? y = some dy)
    (hsum : Model.addDyadic dx dy =
      { negative := sign, significand := magnitude same m r d,
        exponent := (elo : Int) - 150 })
    (hm0 : 8388608 ≤ m) (hm1 : m < 16777216)
    (hr0 : 0 < r) (hr1 : r < 16777216) (hd : 26 ≤ d)
    (helo : 1 ≤ elo) (hehi : elo + d ≤ 254) :
    Model.Spec.add x y = Model.ofFields FloatFormat.binary32 sign
      (elo + d) (m - 8388608) := by
  have hb := normalization same m r d hm0 hm1 hr0 hr1 hd
  have hn : magnitude same m r d ≠ 0 := by
    intro hz
    rw [hz, Nat.log2_zero] at hb
    omega
  have he : (magnitude same m r d).log2 + elo - 23 +
      R14NatNormal.carry (magnitude same m r d) = elo + d := by omega
  have hu : (magnitude same m r d).log2 + elo - 23 +
      R14NatNormal.carry (magnitude same m r d) ≤ 254 := by omega
  rw [Submission.R14WordAddAlignment.spec_add_normal x y dx dy sign
    (magnitude same m r d) elo hx hy hsum hn hb.1 helo hu, he, hb.2.2]

end Submission.R14FarAdd
