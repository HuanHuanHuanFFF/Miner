private theorem shift_value (s : Bool) (m k : Nat) (e : Int) :
    (FloatLib.Numerics.Dyadic.mk s (m * 2 ^ k) (e - (k : Int))).toReal =
      (FloatLib.Numerics.Dyadic.mk s m e).toReal := by
  have hp : (2 : Real) ^ k * (2 : Real) ^ (e - (k : Int)) = (2 : Real) ^ e := by
    rw [← zpow_natCast, ← zpow_add₀ (by norm_num : (2 : Real) ≠ 0)]
    congr 1
    omega
  have hcast (n : Nat) : ((Int.ofNat n : Int) : Real) = (n : Real) := by
    rw [Int.ofNat_eq_natCast, Int.cast_natCast]
  cases s with
  | false =>
    simpa only [FloatLib.Numerics.Dyadic.toReal, FloatLib.Numerics.Dyadic.signedSignificand,
      Bool.false_eq_true, ite_false, ite_true, hcast, Nat.cast_mul, Nat.cast_pow,
      Nat.cast_ofNat, mul_assoc] using congrArg (fun x : Real => (m : Real) * x) hp
  | true =>
    simpa only [FloatLib.Numerics.Dyadic.toReal, FloatLib.Numerics.Dyadic.signedSignificand,
      Bool.false_eq_true, ite_false, ite_true, Int.cast_neg, hcast, Nat.cast_mul,
      Nat.cast_pow, Nat.cast_ofNat, neg_mul, mul_assoc] using
      congrArg (fun x : Real => -(m : Real) * x) hp
