/- NOT_COMPILED. Requires acceptedMathSupport plusColdBoundary on exactB2.
   This delegates the existing all-input theorem; no newIEEE derivation. -/
namespace Submission.R22RseCold
open Competition

theorem outlined_spec (x y : Binary32) :
    outlined x y = ExecFloat.Spec.mul x y :=
  R14ExponentShift.guardedMul_spec retainedB2
    (by intro a b; exact Submission.mul_spec a b) x y

end Submission.R22RseCold
