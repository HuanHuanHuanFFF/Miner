namespace Submission.R22NativeColdAdd
open FloatLib.Floats Competition

theorem diagnosticEntry_spec (x y : Binary32) :
    diagnosticEntry x y = ExecFloat.Spec.add x y := by
  unfold diagnosticEntry
  split
  · rename_i h
    simp only [Bool.and_eq_true] at h
    exact R22NativeColdReview.native_add_spec_of_fastOK x y h.1 h.2
  · simpa only [coldAdd] using (Submission.add_spec x y)

theorem diagnosticEntry_eq_B2_add (x y : Binary32) :
    diagnosticEntry x y = Submission.add x y :=
  (diagnosticEntry_spec x y).trans (Submission.add_spec x y).symm

end Submission.R22NativeColdAdd
