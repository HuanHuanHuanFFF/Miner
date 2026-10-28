/- Conditional proof-only replacement after NatPostBeforeNormalized.
   NOT_RUN. Same arithmetic statement; no new runtime, gate or resource option.
   Helpers separate division goals from p/shift/parity/RNE contexts. -/
namespace R19PostBias

private theorem r22_small_divisions (b : Nat) (hb : b < 140737496743936) :
    b / 140737488355328 = (if b / 8388608 = 16777216 then 1 else 0) ∧
      b / 2 ^ (23 + b / 140737488355328) =
        (if b / 8388608 = 16777216 then 8388608 else b / 8388608) := by
  by_cases hc : b < 140737488355328
  · have hq : b / 8388608 < 16777216 :=
      (Nat.div_lt_iff_lt_mul (by decide)).2 (by omega)
    have hh : b / 140737488355328 = 0 := Nat.div_eq_of_lt hc
    have hn : b / 8388608 ≠ 16777216 := Nat.ne_of_lt hq
    norm_num [hh, hn]
  · have qlo : 16777216 * 8388608 ≤ b := by omega
    have qhi : b < (16777216 + 1) * 8388608 := by omega
    have rlo : 8388608 * 16777216 ≤ b := by omega
    have rhi : b < (8388608 + 1) * 16777216 := by omega
    have hlo : 1 * 140737488355328 ≤ b := by omega
    have hhi : b < (1 + 1) * 140737488355328 := by omega
    have hq : b / 8388608 = 16777216 := Nat.div_eq_of_lt_le qlo qhi
    have hr : b / 16777216 = 8388608 := Nat.div_eq_of_lt_le rlo rhi
    have hh : b / 140737488355328 = 1 := Nat.div_eq_of_lt_le hlo hhi
    norm_num [hh, hq, hr]

private theorem r22_large_divisions (b : Nat)
    (hlo : 140737488355328 ≤ b) (hhi : b < 281474976710656) :
    b / 140737488355328 = 1 + (if b / 16777216 = 16777216 then 1 else 0) ∧
      b / 2 ^ (23 + b / 140737488355328) =
        (if b / 16777216 = 16777216 then 8388608 else b / 16777216) := by
  have hhlo : 1 * 140737488355328 ≤ b := by omega
  have hhhi : b < (1 + 1) * 140737488355328 := by omega
  have hq : b / 16777216 < 16777216 :=
    (Nat.div_lt_iff_lt_mul (by decide)).2 (by omega)
  have hh : b / 140737488355328 = 1 := Nat.div_eq_of_lt_le hhlo hhhi
  have hn : b / 16777216 ≠ 16777216 := Nat.ne_of_lt hq
  norm_num [hh, hn]

theorem normalized_quotient (p : Nat)
    (hlo : 70368744177664 ≤ p) (hhi : p ≤ 281474943156225) :
    let q := FloatLib.Numerics.roundShiftRightEven p (shift p)
    let h := biased p >>> 47
    h = (if p < 140737488355328 then 0 else 1) + (if q = 16777216 then 1 else 0) ∧
      biased p >>> (23 + h) = (if q = 16777216 then 8388608 else q) := by
  have hb := biased_bounds p hlo hhi
  dsimp only
  by_cases hp : p < 140737488355328
  · have hk : shift p = 23 := by simp [shift, hp]
    have hpar : (p >>> 23) % 2 < 2 := Nat.mod_lt _ (by decide)
    have hsmall : biased p < 140737496743936 := by
      calc
        biased p = p + 4194303 + (p >>> 23) % 2 := by
          simp only [biased, hk, Nat.reduceSub, Nat.reducePow]
        _ ≤ p + 4194303 + 1 := Nat.add_le_add_left (Nat.le_of_lt_succ hpar) _
        _ = p + 4194304 := Nat.add_assoc _ _ _
        _ < 140737492549632 := by
          simpa only [Nat.reduceAdd] using Nat.add_lt_add_right hp 4194304
        _ < 140737496743936 := by decide
    have hx := r22_small_divisions (biased p) hsmall
    have hq := biased_quotient p
    rw [hk] at hq ⊢
    rw [← hq]
    simpa only [hp, ↓reduceIte, Nat.zero_add, Nat.shiftRight_eq_div_pow, Nat.reducePow] using hx
  · have hk : shift p = 24 := by simp [shift, hp]
    have hlarge : 140737488355328 ≤ biased p := by
      calc
        140737488355328 ≤ p := Nat.le_of_not_gt hp
        _ ≤ p + (2 ^ (shift p - 1) - 1) := Nat.le_add_right _ _
        _ ≤ biased p := Nat.le_add_right _ _
    have hupper : biased p < 281474976710656 :=
      Nat.lt_of_le_of_lt hb.2 (by decide)
    have hx := r22_large_divisions (biased p) hlarge hupper
    have hq := biased_quotient p
    rw [hk] at hq ⊢
    rw [← hq]
    simpa only [hp, ↓reduceIte, Nat.shiftRight_eq_div_pow, Nat.reducePow] using hx

end R19PostBias
