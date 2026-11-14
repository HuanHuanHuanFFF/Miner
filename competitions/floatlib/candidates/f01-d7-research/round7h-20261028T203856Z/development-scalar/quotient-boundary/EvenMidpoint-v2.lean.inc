namespace Submission.R24CellPrimitive
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange
theorem quotient_even_closed_midpoint (num den mant : Nat)
    (hd : 0 < den) (hm : 0 < mant) (heven : mant % 2 = 0)
    (hl : den * (2 * mant - 1) ≤ 2 * num)
    (hu : 2 * num ≤ den * (2 * mant + 1)) :
    FloatLib.Numerics.roundQuotientEven num den = mant := by
  cases mant with
  | zero => omega
  | succ k =>
    have hleft : 2 * (k + 1) - 1 = 2 * k + 1 := by omega
    have hright : 2 * (k + 1) + 1 = 2 * k + 3 := by omega
    rw [hleft] at hl
    rw [hright] at hu
    have hlo : k * den ≤ num := by nlinarith
    have hhi : num < (k + 2) * den := by nlinarith
    have hql : k ≤ num / den := (Nat.le_div_iff_mul_le hd).2 hlo
    have hqu : num / den < k + 2 := (Nat.div_lt_iff_lt_mul hd).2 hhi
    have hdiv := Nat.mod_add_div num den
    have hcases : num / den = k ∨ num / den = k + 1 := by omega
    rcases hcases with hq | hq
    · have hr : den ≤ 2 * (num % den) := by rw [hq] at hdiv; nlinarith
      have hn : ¬ 2 * (num % den) < den := by omega
      by_cases hs : den < 2 * (num % den)
      · simp [FloatLib.Numerics.roundQuotientEven, hq, hn, hs]
      · have he : 2 * (num % den) = den := by omega
        have hk : k % 2 = 1 := by omega
        simp [FloatLib.Numerics.roundQuotientEven, hq, he, hk]
    · have hr : 2 * (num % den) ≤ den := by rw [hq] at hdiv; nlinarith
      by_cases hs : 2 * (num % den) < den
      · simp [FloatLib.Numerics.roundQuotientEven, hq, hs]
      · have he : 2 * (num % den) = den := by omega
        simp [FloatLib.Numerics.roundQuotientEven, hq, he, heven]

end Submission.R24CellPrimitive
