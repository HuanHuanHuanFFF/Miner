/- NOT_COMPILED structural interface. Append to the diagnostic carrier only
   if a helper statement/replay is wanted. It proves no new arithmetic fact. -/
namespace Submission.R22OutlineMul
open Competition

theorem retainedMul_eq_old (x y : Binary32) :
    retainedMul x y = Submission.mul x y := by
  rfl

theorem guardedMul_eq_old (x y : Binary32) :
    guardedMul x y = R19DirectBias.guardedMul Submission.mul x y := by
  rfl

theorem diagnosticEntry_eq_old (x y : Binary32) :
    diagnosticEntry x y = R19DirectBias.guardedMul Submission.mul x y := by
  rfl

theorem diagnosticEntry_spec_of_old
    (h : ∀ x y : Binary32,
      R19DirectBias.guardedMul Submission.mul x y = ExecFloat.Spec.mul x y)
    (x y : Binary32) : diagnosticEntry x y = ExecFloat.Spec.mul x y := by
  exact (diagnosticEntry_eq_old x y).trans (h x y)

end Submission.R22OutlineMul
