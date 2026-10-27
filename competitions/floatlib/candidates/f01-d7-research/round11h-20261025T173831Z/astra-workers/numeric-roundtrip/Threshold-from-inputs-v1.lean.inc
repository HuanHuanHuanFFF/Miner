/- R17 input-derived threshold proof attempts. Fixed-environment elaboration is pending. -/
namespace Submission.R17Threshold

open FloatLib.Numerics

abbrev leading (n : Nat) : Nat := n.log2 + R14NatNormal.carry n
abbrev rounded (n : Nat) : Nat := R16UInt32Roundtrip.roundedInteger n

theorem rounded_binade (n : Nat)
    (hlo : 8388608 ≤ n) (hhi : n ≤ 2164260735) :
    2 ^ leading n ≤ rounded n ∧ rounded n < 2 ^ (leading n + 1) := by
  have hl := R16UInt32Roundtrip.rounded_leading n hlo hhi
  have hm := R16UInt32Roundtrip.high_mantissa n hlo hhi
  have he : 23 + R16UInt32Roundtrip.roundedShift n = leading n := by
    unfold R16UInt32Roundtrip.roundedShift leading
    omega
  have he' : 24 + R16UInt32Roundtrip.roundedShift n = leading n + 1 := by omega
  constructor
  · calc
      2 ^ leading n = 8388608 * 2 ^ R16UInt32Roundtrip.roundedShift n := by
        change 2 ^ leading n = 2 ^ 23 * 2 ^ R16UInt32Roundtrip.roundedShift n
        rw [← Nat.pow_add, he]
      _ ≤ rounded n := Nat.mul_le_mul_right _ hm.1
  · calc
      rounded n < 16777216 * 2 ^ R16UInt32Roundtrip.roundedShift n :=
        Nat.mul_lt_mul_of_pos_right hm.2 (Nat.two_pow_pos _)
      _ = 2 ^ (leading n + 1) := by
        change 2 ^ 24 * 2 ^ R16UInt32Roundtrip.roundedShift n = _
        rw [← Nat.pow_add, he']

theorem rounded_log2 (n : Nat)
    (hlo : 8388608 ≤ n) (hhi : n ≤ 2164260735) :
    (rounded n).log2 = leading n := by
  have hb := rounded_binade n hlo hhi
  have hp := Nat.two_pow_pos (leading n)
  have hn : rounded n ≠ 0 := by omega
  exact (Nat.log2_eq_iff hn).2 hb

theorem threshold_leading (r h k : Nat)
    (hk : k ≤ h) (hk' : h ≤ k + 1)
    (hr : 2 ^ h ≤ r) (hr' : r < 2 ^ (h + 1)) :
    h = k + (if 2 ^ (k + 1) ≤ r then 1 else 0) := by
  by_cases ht : 2 ^ (k + 1) ≤ r
  · have hne : h ≠ k := by
      intro he
      rw [he] at hr'
      omega
    simp only [if_pos ht]
    omega
  · have hne : h ≠ k + 1 := by
      intro he
      rw [he] at hr
      omega
    simp only [if_neg ht]
    omega

theorem same_magnitude_bounds (a b d : Nat)
    (ha : 8388608 ≤ a) (ha' : a < 16777216)
    (hb : 8388608 ≤ b) (hb' : b < 16777216) (hd : d ≤ 7) :
    8388608 ≤ a * 2 ^ d + b ∧ a * 2 ^ d + b ≤ 2164260735 ∧
      2 ^ (23 + d) ≤ a * 2 ^ d + b ∧ a * 2 ^ d + b < 2 ^ (25 + d) := by
  interval_cases d <;> norm_num <;> omega

theorem opposite_magnitude_bounds (a b d : Nat)
    (ha : 8388608 ≤ a) (ha' : a < 16777216)
    (hb : 8388608 ≤ b) (hb' : b < 16777216)
    (hd0 : 1 ≤ d) (hd : d ≤ 7)
    (hN : 8388608 ≤ a * 2 ^ d - b) :
    a * 2 ^ d - b ≤ 2164260735 ∧
      2 ^ (22 + d) ≤ a * 2 ^ d - b ∧ a * 2 ^ d - b < 2 ^ (24 + d) := by
  interval_cases d <;> norm_num at hN ⊢ <;> omega

theorem same_top_no_carry (a b d : Nat)
    (ha : 8388608 ≤ a) (ha' : a < 16777216)
    (hb : 8388608 ≤ b) (hb' : b < 16777216) (hd : d ≤ 7)
    (hh : (a * 2 ^ d + b).log2 = 24 + d) :
    R14NatNormal.carry (a * 2 ^ d + b) = 0 := by
  have hs : 24 + d - 23 = d + 1 := by omega
  have hq : R14NatNormal.rounded (a * 2 ^ d + b) < 16777216 := by
    unfold R14NatNormal.rounded
    rw [hh, hs]
    by_cases hz : d = 0
    · subst d
      norm_num only [Nat.pow_zero, Nat.mul_one, Nat.zero_add]
      rw [roundShiftRightEven_one]
      split <;> omega
    · have hr := roundShiftRightEven_le_shiftRight_add1 (a * 2 ^ d + b) (d + 1)
      rw [Nat.shiftRight_eq_div_pow] at hr
      interval_cases d <;> norm_num at hr ⊢ <;> omega
  have hne : R14NatNormal.rounded (a * 2 ^ d + b) ≠ 16777216 := by omega
  simp [R14NatNormal.carry, hne]

theorem opposite_top_no_carry (a b d : Nat)
    (ha : 8388608 ≤ a) (ha' : a < 16777216)
    (hb : 8388608 ≤ b) (hb' : b < 16777216)
    (hd0 : 1 ≤ d) (hd : d ≤ 7)
    (hh : (a * 2 ^ d - b).log2 = 23 + d) :
    R14NatNormal.carry (a * 2 ^ d - b) = 0 := by
  have hs : 23 + d - 23 = d := by omega
  have hr := roundShiftRightEven_le_shiftRight_add1 (a * 2 ^ d - b) d
  rw [Nat.shiftRight_eq_div_pow] at hr
  have hq : R14NatNormal.rounded (a * 2 ^ d - b) < 16777216 := by
    unfold R14NatNormal.rounded
    rw [hh, hs]
    interval_cases d <;> norm_num at hr ⊢ <;> omega
  have hne : R14NatNormal.rounded (a * 2 ^ d - b) ≠ 16777216 := by omega
  simp [R14NatNormal.carry, hne]

theorem same_leading_bounds (a b d : Nat)
    (ha : 8388608 ≤ a) (ha' : a < 16777216)
    (hb : 8388608 ≤ b) (hb' : b < 16777216) (hd : d ≤ 7) :
    23 + d ≤ leading (a * 2 ^ d + b) ∧ leading (a * 2 ^ d + b) ≤ 24 + d := by
  have hN := same_magnitude_bounds a b d ha ha' hb hb' hd
  have hn : a * 2 ^ d + b ≠ 0 := by omega
  have hlo : 23 + d ≤ (a * 2 ^ d + b).log2 := (Nat.le_log2 hn).2 hN.2.2.1
  have hhi : (a * 2 ^ d + b).log2 < 25 + d := (Nat.log2_lt hn).2 hN.2.2.2
  have hc := R14NatNormal.carry_le (a * 2 ^ d + b)
  unfold leading
  by_cases ht : (a * 2 ^ d + b).log2 = 24 + d
  · rw [same_top_no_carry a b d ha ha' hb hb' hd ht]
    omega
  · omega

theorem opposite_leading_bounds (a b d : Nat)
    (ha : 8388608 ≤ a) (ha' : a < 16777216)
    (hb : 8388608 ≤ b) (hb' : b < 16777216)
    (hd0 : 1 ≤ d) (hd : d ≤ 7)
    (hN : 8388608 ≤ a * 2 ^ d - b) :
    22 + d ≤ leading (a * 2 ^ d - b) ∧ leading (a * 2 ^ d - b) ≤ 23 + d := by
  have hM := opposite_magnitude_bounds a b d ha ha' hb hb' hd0 hd hN
  have hn : a * 2 ^ d - b ≠ 0 := by omega
  have hlo : 22 + d ≤ (a * 2 ^ d - b).log2 := (Nat.le_log2 hn).2 hM.2.1
  have hhi : (a * 2 ^ d - b).log2 < 24 + d := (Nat.log2_lt hn).2 hM.2.2
  have hc := R14NatNormal.carry_le (a * 2 ^ d - b)
  unfold leading
  by_cases ht : (a * 2 ^ d - b).log2 = 23 + d
  · rw [opposite_top_no_carry a b d ha ha' hb hb' hd0 hd ht]
    omega
  · omega

theorem same_R_interval (a b d : Nat)
    (ha : 8388608 ≤ a) (ha' : a < 16777216)
    (hb : 8388608 ≤ b) (hb' : b < 16777216) (hd : d ≤ 7) :
    2 ^ (23 + d) ≤ rounded (a * 2 ^ d + b) ∧
      rounded (a * 2 ^ d + b) < 2 ^ (25 + d) := by
  have hN := same_magnitude_bounds a b d ha ha' hb hb' hd
  have hl := same_leading_bounds a b d ha ha' hb hb' hd
  have hr := rounded_binade (a * 2 ^ d + b) hN.1 hN.2.1
  constructor
  · exact le_trans (Nat.pow_le_pow_right (by decide) hl.1) hr.1
  · exact lt_of_lt_of_le hr.2 (Nat.pow_le_pow_right (by decide) (by omega))

theorem opposite_R_interval (a b d : Nat)
    (ha : 8388608 ≤ a) (ha' : a < 16777216)
    (hb : 8388608 ≤ b) (hb' : b < 16777216)
    (hd0 : 1 ≤ d) (hd : d ≤ 7)
    (hN : 8388608 ≤ a * 2 ^ d - b) :
    2 ^ (22 + d) ≤ rounded (a * 2 ^ d - b) ∧
      rounded (a * 2 ^ d - b) < 2 ^ (24 + d) := by
  have hM := opposite_magnitude_bounds a b d ha ha' hb hb' hd0 hd hN
  have hl := opposite_leading_bounds a b d ha ha' hb hb' hd0 hd hN
  have hr := rounded_binade (a * 2 ^ d - b) hN hM.1
  constructor
  · exact le_trans (Nat.pow_le_pow_right (by decide) hl.1) hr.1
  · exact lt_of_lt_of_le hr.2 (Nat.pow_le_pow_right (by decide) (by omega))

theorem same_threshold_from_inputs (a b d : Nat)
    (ha : 8388608 ≤ a) (ha' : a < 16777216)
    (hb : 8388608 ≤ b) (hb' : b < 16777216) (hd : d ≤ 7) :
    (rounded (a * 2 ^ d + b)).log2 =
        23 + d + (if 2 ^ (24 + d) ≤ rounded (a * 2 ^ d + b) then 1 else 0) ∧
      R16UInt32Roundtrip.roundedShift (a * 2 ^ d + b) =
        d + (if 2 ^ (24 + d) ≤ rounded (a * 2 ^ d + b) then 1 else 0) := by
  have hN := same_magnitude_bounds a b d ha ha' hb hb' hd
  have hl := same_leading_bounds a b d ha ha' hb hb' hd
  have hr := rounded_binade (a * 2 ^ d + b) hN.1 hN.2.1
  have hk : leading (a * 2 ^ d + b) ≤ (23 + d) + 1 := by omega
  have ht := threshold_leading _ _ (23 + d) hl.1 hk hr.1 hr.2
  have he : (23 + d) + 1 = 24 + d := by omega
  rw [he] at ht
  constructor
  · rw [rounded_log2 _ hN.1 hN.2.1]
    exact ht
  · unfold R16UInt32Roundtrip.roundedShift
    change leading (a * 2 ^ d + b) - 23 = _
    rw [ht]
    omega

theorem opposite_threshold_from_inputs (a b d : Nat)
    (ha : 8388608 ≤ a) (ha' : a < 16777216)
    (hb : 8388608 ≤ b) (hb' : b < 16777216)
    (hd0 : 1 ≤ d) (hd : d ≤ 7)
    (hN : 8388608 ≤ a * 2 ^ d - b) :
    (rounded (a * 2 ^ d - b)).log2 =
        22 + d + (if 2 ^ (23 + d) ≤ rounded (a * 2 ^ d - b) then 1 else 0) ∧
      R16UInt32Roundtrip.roundedShift (a * 2 ^ d - b) =
        d - 1 + (if 2 ^ (23 + d) ≤ rounded (a * 2 ^ d - b) then 1 else 0) := by
  have hM := opposite_magnitude_bounds a b d ha ha' hb hb' hd0 hd hN
  have hl := opposite_leading_bounds a b d ha ha' hb hb' hd0 hd hN
  have hr := rounded_binade (a * 2 ^ d - b) hN hM.1
  have hk : leading (a * 2 ^ d - b) ≤ (22 + d) + 1 := by omega
  have ht := threshold_leading _ _ (22 + d) hl.1 hk hr.1 hr.2
  have he : (22 + d) + 1 = 23 + d := by omega
  rw [he] at ht
  constructor
  · rw [rounded_log2 _ hN hM.1]
    exact ht
  · unfold R16UInt32Roundtrip.roundedShift
    change leading (a * 2 ^ d - b) - 23 = _
    rw [ht]
    omega

end Submission.R17Threshold
