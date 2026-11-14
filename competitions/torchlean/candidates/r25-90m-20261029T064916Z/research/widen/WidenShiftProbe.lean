import ContractExact

namespace Submission.R25WidenShiftProbe

theorem shift29_toReal (s : Bool) (m : Nat) (e : Int) :
    (FloatLib.Numerics.Dyadic.mk s (m * 536870912) (e - 29)).toReal =
      (FloatLib.Numerics.Dyadic.mk s m e).toReal := by
  have hp : (536870912 : ℝ) * (2 : ℝ) ^ (e - 29) = (2 : ℝ) ^ e := by
    have hc : (536870912 : ℝ) = (2 : ℝ) ^ (29 : Int) := by norm_num
    rw [hc, ← zpow_add₀ (by norm_num : (2 : ℝ) ≠ 0)]
    congr 1
    omega
  have hcast (n : Nat) : ((Int.ofNat n : Int) : ℝ) = (n : ℝ) := by
    rw [Int.ofNat_eq_natCast, Int.cast_natCast]
  have hcNum : ((536870912 : Nat) : ℝ) = (536870912 : ℝ) := by norm_num
  cases s with
  | false =>
    simpa only [FloatLib.Numerics.Dyadic.toReal, FloatLib.Numerics.Dyadic.signedSignificand,
      Bool.false_eq_true, ite_false, ite_true, hcast, Nat.cast_mul, hcNum, mul_assoc] using
      congrArg (fun x : ℝ => (m : ℝ) * x) hp
  | true =>
    simpa only [FloatLib.Numerics.Dyadic.toReal, FloatLib.Numerics.Dyadic.signedSignificand,
      Bool.false_eq_true, ite_false, ite_true, Int.cast_neg, hcast,
      Nat.cast_mul, hcNum, neg_mul, mul_assoc] using
      congrArg (fun x : ℝ => -(m : ℝ) * x) hp

end Submission.R25WidenShiftProbe
