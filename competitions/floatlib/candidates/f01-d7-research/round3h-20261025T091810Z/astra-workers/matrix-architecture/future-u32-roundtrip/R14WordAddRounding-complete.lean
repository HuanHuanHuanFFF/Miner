namespace Submission.R14WordAddRounding

open FloatLib.Numerics

theorem rounded_bounds (n : Nat) (hn : n ≠ 0) (hh : 23 ≤ n.log2) :
    8388608 ≤ Submission.R14NatNormal.rounded n ∧
    Submission.R14NatNormal.rounded n ≤ 16777216 := by
  let k := n.log2 - 23
  have hpow : 2 ^ k ≤ n :=
    le_trans (Nat.pow_le_pow_right (by decide) (show k ≤ n.log2 by dsimp [k]; omega))
      (Nat.log2_self_le hn)
  have hq : n >>> k ≠ 0 := by
    intro hz
    rw [Nat.shiftRight_eq_div_pow, Nat.div_eq_zero_iff] at hz
    rcases hz with hz | hz
    · exact (Nat.two_pow_pos k).ne' hz
    · omega
  have hlog := Submission.FastMul.log2_shift n k hq
  have hqlog : (n >>> k).log2 = 23 := by
    dsimp [k] at hlog ⊢
    omega
  have hqlo := Nat.log2_self_le hq
  have hqhi := Nat.lt_log2_self (n := n >>> k)
  rw [hqlog] at hqlo hqhi
  norm_num at hqlo hqhi
  have hrlo := shiftRight_le_roundShiftRightEven n k
  have hrhi := roundShiftRightEven_le_shiftRight_add1 n k
  change n >>> k ≤ roundShiftRightEven n k at hrlo
  change roundShiftRightEven n k ≤ (n >>> k) + 1 at hrhi
  rw [Nat.shiftRight_eq_div_pow] at hrlo hrhi
  change 8388608 ≤ roundShiftRightEven n k ∧ roundShiftRightEven n k ≤ 16777216
  omega

theorem shift_carry (n : Nat) (hn : n ≠ 0) (hh : 23 ≤ n.log2) :
    Submission.R14NatNormal.rounded n >>> 24 = Submission.R14NatNormal.carry n := by
  have hb := rounded_bounds n hn hh
  rw [Nat.shiftRight_eq_div_pow]
  unfold Submission.R14NatNormal.carry
  split <;> norm_num at * <;> omega

theorem masked_fraction (n : Nat) (hn : n ≠ 0) (hh : 23 ≤ n.log2) :
    Submission.R14NatNormal.rounded n % 8388608 =
      Submission.R14NatNormal.mantissa n - 8388608 := by
  have hb := rounded_bounds n hn hh
  unfold Submission.R14NatNormal.mantissa
  split <;> norm_num at * <;> omega

end Submission.R14WordAddRounding
