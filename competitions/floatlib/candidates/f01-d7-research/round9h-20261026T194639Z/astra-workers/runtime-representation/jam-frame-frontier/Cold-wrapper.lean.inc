/- R19: isolate the exact old fallback; Jam arithmetic and guards are unchanged. -/
@[noinline] def jamColdFallback (x y : Binary32) : Binary32 := R19Base.mul x y
theorem jamColdFallback_spec (x y : Binary32) :
    jamColdFallback x y = ExecFloat.Spec.mul x y := R19Base.mul_spec x y
@[inline] def mul (x y : Binary32) : Binary32 := R19Base.R19Jam17.guardedMul jamColdFallback x y
theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y :=
  R19Base.R19Jam17.guardedMul_spec jamColdFallback jamColdFallback_spec x y
