private theorem low_bias_upper (p r : Nat) (hp : p < 140737488355328) (hr : r < 2) :
    p + 4194303 + r < 140737496743936 := by
  have hb : p + 4194303 + r ≤ 140737488355328 + 4194303 + 1 :=
    Nat.add_le_add (Nat.add_le_add (Nat.le_of_lt hp) (Nat.le_refl _))
      (Nat.le_of_lt_succ hr)
  exact lt_of_le_of_lt hb (by decide)

private theorem below_boundary (b : Nat) (hb : b < 140737488355328) :
    b / 140737488355328 = 0 ∧ b / 8388608 ≠ 16777216 := by
  have hq : b / 8388608 < 16777216 :=
    (Nat.div_lt_iff_lt_mul (by decide)).2 (by
      simpa only [Nat.reduceMul] using hb)
  exact ⟨Nat.div_eq_of_lt hb, Nat.ne_of_lt hq⟩

private theorem at_boundary (b : Nat)
    (hlo : 140737488355328 ≤ b) (hhi : b < 140737496743936) :
    b / 140737488355328 = 1 ∧
      b / 8388608 = 16777216 ∧ b / 16777216 = 8388608 := by
  refine ⟨?_, ?_, ?_⟩
  · apply Nat.div_eq_of_lt_le
    · simpa only [Nat.one_mul] using hlo
    · exact lt_trans hhi (by decide)
  · apply Nat.div_eq_of_lt_le
    · simpa only [Nat.reduceMul] using hlo
    · simpa only [Nat.reduceAdd, Nat.reduceMul] using hhi
  · apply Nat.div_eq_of_lt_le
    · simpa only [Nat.reduceMul] using hlo
    · exact lt_trans hhi (by decide)

private theorem upper_half (b : Nat)
    (hlo : 140737488355328 ≤ b) (hhi : b ≤ 281474951544833) :
    b / 140737488355328 = 1 ∧ b / 16777216 ≠ 16777216 := by
  have hq : b / 16777216 < 16777216 :=
    (Nat.div_lt_iff_lt_mul (by decide)).2 (lt_of_le_of_lt hhi (by decide))
  refine ⟨?_, Nat.ne_of_lt hq⟩
  apply Nat.div_eq_of_lt_le
  · simpa only [Nat.one_mul] using hlo
  · exact lt_of_le_of_lt hhi (by decide)

private theorem normalized_low (b : Nat) (hb : b < 140737496743936) :
    b >>> 47 = (if b >>> 23 = 16777216 then 1 else 0) ∧
      b >>> (23 + (b >>> 47)) =
        (if b >>> 23 = 16777216 then 8388608 else b >>> 23) := by
  simp only [Nat.shiftRight_eq_div_pow]
  by_cases h : b < 140737488355328
  · have h0 := (below_boundary b h).1
    have hn := (below_boundary b h).2
    constructor
    · simpa only [h0, if_neg hn] using (rfl : (0 : Nat) = 0)
    · simpa only [h0, if_neg hn, Nat.add_zero] using (rfl : b / 8388608 = b / 8388608)
  · have hs := at_boundary b (Nat.le_of_not_gt h) hb
    constructor
    · simpa only [hs.1, hs.2.1, ↓reduceIte] using (rfl : (1 : Nat) = 1)
    · simpa only [hs.1, hs.2.1, ↓reduceIte] using hs.2.2

private theorem normalized_high (b : Nat)
    (hlo : 140737488355328 ≤ b) (hhi : b ≤ 281474951544833) :
    b >>> 47 = 1 + (if b >>> 24 = 16777216 then 1 else 0) ∧
      b >>> (23 + (b >>> 47)) =
        (if b >>> 24 = 16777216 then 8388608 else b >>> 24) := by
  simp only [Nat.shiftRight_eq_div_pow]
  have hs := upper_half b hlo hhi
  constructor
  · simpa only [hs.1, if_neg hs.2, Nat.add_zero] using (rfl : (1 : Nat) = 1)
  · simpa only [hs.1, if_neg hs.2] using (rfl : b / 16777216 = b / 16777216)

theorem normalized_quotient (p : Nat)
    (hlo : 70368744177664 ≤ p) (hhi : p ≤ 281474943156225) :
    let q := roundShiftRightEven p (shift p)
    let h := biased p >>> 47
    h = (if p < 140737488355328 then 0 else 1) + (if q = 16777216 then 1 else 0) ∧
      biased p >>> (23 + h) = (if q = 16777216 then 8388608 else q) := by
  have hb := biased_bounds p hlo hhi
  have hq := biased_quotient p
  dsimp only
  by_cases hp : p < 140737488355328
  · have hk : shift p = 23 := by simp only [shift, if_pos hp]
    have hsmall : biased p < 140737496743936 := by
      unfold biased
      rw [hk]
      change p + 4194303 + (p >>> 23) % 2 < 140737496743936
      exact low_bias_upper p _ hp (Nat.mod_lt _ (by decide))
    rw [hk] at hq ⊢
    rw [← hq]
    simpa only [if_pos hp, Nat.zero_add] using normalized_low (biased p) hsmall
  · have hk : shift p = 24 := by simp only [shift, if_neg hp]
    have hge : p ≤ biased p := by
      unfold biased
      exact Nat.le_trans (Nat.le_add_right _ _) (Nat.le_add_right _ _)
    have hlarge : 140737488355328 ≤ biased p :=
      Nat.le_trans (Nat.le_of_not_gt hp) hge
    rw [hk] at hq ⊢
    rw [← hq]
    simpa only [if_neg hp] using normalized_high (biased p) hlarge hb.2
