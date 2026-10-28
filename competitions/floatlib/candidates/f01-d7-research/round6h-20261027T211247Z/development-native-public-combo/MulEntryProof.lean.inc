namespace Submission.R22NativeCold
open FloatLib.Floats Competition

theorem coldMul_spec (x y : Binary32) : coldMul x y = ExecFloat.Spec.mul x y := by
  unfold coldMul
  split
  · rename_i h
    have hh := R22NativeColdReview.pairOK_normal x.raw.1 y.raw.1 h
    have hx : R2W01b.fastOK x.raw.1 = true :=
      (R2W01b.fastOK_iff x.raw.1).mpr (Or.inr hh.1)
    have hy : R2W01b.fastOK y.raw.1 = true :=
      (R2W01b.fastOK_iff y.raw.1).mpr (Or.inr hh.2)
    simpa only [hotMul] using R22NativeColdReview.native_mul_spec_of_fastOK x y hx hy
  · simpa only [retainedMul] using (Submission.mul_spec x y)

end Submission.R22NativeCold
