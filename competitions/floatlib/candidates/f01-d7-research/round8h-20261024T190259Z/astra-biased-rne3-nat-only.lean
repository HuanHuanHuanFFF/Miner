
/- Independent exact RNE lemma requested by the integer-normal development route. -/
namespace Submission.R14BiasRNE

open FloatLib.Numerics

theorem nat_bias (p t : Nat) (ht : t = 23 ∨ t = 24) :
    roundShiftRightEven p t =
      (p + 2 ^ (t - 1) - 1 + (p >>> t) % 2) >>> t := by
  rcases ht with rfl | rfl
  all_goals
    rw [roundShiftRightEven_eq_roundQuotientEven]
    unfold roundQuotientEven
    norm_num [Nat.shiftRight_eq_div_pow]
    split_ifs <;> omega

end Submission.R14BiasRNE
