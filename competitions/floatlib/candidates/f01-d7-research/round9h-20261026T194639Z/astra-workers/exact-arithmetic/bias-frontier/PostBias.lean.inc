namespace R19PostBias
open FloatLib.Numerics

def shift (p : Nat) : Nat := if p < 140737488355328 then 23 else 24
def biased (p : Nat) : Nat := p + (2 ^ (shift p - 1) - 1) + (p >>> shift p) % 2

/-- Uses the retained uncompiled bias proof, not an independent new proof. -/
theorem biased_quotient (p : Nat) :
    biased p >>> shift p = roundShiftRightEven p (shift p) := by
  have hk : shift p = 23 ∨ shift p = 24 := by
    unfold shift
    split <;> simp_all
  exact (BranchlessRNESeed.nat_grouped_bias p (shift p) hk).symm

theorem biased_bounds (p : Nat)
    (hlo : 70368744177664 ≤ p) (hhi : p ≤ 281474943156225) :
    70368744177664 ≤ biased p ∧ biased p ≤ 281474951544833 := by
  have hpar : (p >>> shift p) % 2 < 2 := Nat.mod_lt _ (by decide)
  unfold biased
  by_cases hp : p < 140737488355328
  · simp only [shift,if_pos hp]
    norm_num only [Nat.reduceSub,Nat.reducePow]
    simp only [shift,if_pos hp] at hpar
    omega
  · simp only [shift,if_neg hp]
    norm_num only [Nat.reduceSub,Nat.reducePow]
    simp only [shift,if_neg hp] at hpar
    omega

/-- The actual product cap prevents a second carry beyond bit47. -/
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
  · have hk : shift p = 23 := by simp [shift,hp]
    have hsmall : biased p < 140737496743936 := by
      have hpar : (p >>> 23) % 2 < 2 := Nat.mod_lt _ (by decide)
      unfold biased
      rw [hk]
      norm_num only [Nat.reduceSub,Nat.reducePow]
      omega
    rw [hk] at hq ⊢
    rw [← hq]
    simp only [hp,↓reduceIte,Nat.shiftRight_eq_div_pow]
    have hh : biased p / 140737488355328 = 0 ∨ biased p / 140737488355328 = 1 := by omega
    rcases hh with hh | hh
    · rw [hh]
      norm_num only [Nat.reduceAdd,Nat.reducePow]
      have hn : biased p / 8388608 ≠ 16777216 := by omega
      simp [hn]
    · rw [hh]
      norm_num only [Nat.reduceAdd,Nat.reducePow]
      have he : biased p / 8388608 = 16777216 := by omega
      simp only [he,↓reduceIte]
      constructor <;> omega
  · have hk : shift p = 24 := by simp [shift,hp]
    have hlarge : 140737488355328 ≤ biased p := by
      unfold biased
      omega
    rw [hk] at hq ⊢
    rw [← hq]
    simp only [hp,↓reduceIte,Nat.shiftRight_eq_div_pow]
    have hh : biased p / 140737488355328 = 1 := by omega
    rw [hh]
    norm_num only [Nat.reduceAdd,Nat.reducePow]
    have hn : biased p / 16777216 ≠ 16777216 := by omega
    simp [hn]

end R19PostBias
