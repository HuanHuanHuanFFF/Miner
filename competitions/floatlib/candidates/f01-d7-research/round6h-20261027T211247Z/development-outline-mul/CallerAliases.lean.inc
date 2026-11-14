/- Diagnostic aliases to put both complete guards in D's same binary.
   This fragment is NOT_COMPILED, does not change public endpoints, and is not
   a theorem that either diagnostic equals the multiplication contract. -/
open Competition

@[inline] def r22CostOriginalGuardedMul (x y : Binary32) : Binary32 :=
  Submission.R19DirectBias.guardedMul Submission.mul x y

@[inline] def r22CostOutlinedMul (x y : Binary32) : Binary32 :=
  Submission.R22OutlineMul.guardedMul x y

/-- Structural transfer only; does not discharge the normalCore math obligation. -/
theorem r22Outlined_eq_originalGuarded (x y : Binary32) :
    r22CostOutlinedMul x y = r22CostOriginalGuardedMul x y := by
  rfl
