/- Optional composition interface only; NOT included in public ADD Kernel.lean.
   Requires exact e3b NativeCold, 5681 PairDomain and 5607 native bridges. NOT_RUN. -/
namespace Submission.R22NativeCold
open FloatLib.Floats Competition

theorem hotMul_spec_of_pairOK (x y : Binary32) (h : pairOK x.raw.1 y.raw.1 = true) :
    hotMul x y = ExecFloat.Spec.mul x y := by
  have hn := R22NativeColdReview.pairOK_normal x.raw.1 y.raw.1 h
  have hx := (R2W01b.fastOK_iff x.raw.1).mpr (Or.inr hn.1)
  have hy := (R2W01b.fastOK_iff y.raw.1).mpr (Or.inr hn.2)
  exact R22NativeColdReview.native_mul_spec_of_fastOK x y hx hy

theorem coldMul_spec (x y : Binary32) : coldMul x y = ExecFloat.Spec.mul x y := by
  unfold coldMul
  split
  · rename_i h
    exact hotMul_spec_of_pairOK x y h
  · simpa only [retainedMul] using (Submission.mul_spec x y)

theorem coldMul_eq_inlineMul (x y : Binary32) : coldMul x y = inlineMul x y := rfl

end Submission.R22NativeCold
