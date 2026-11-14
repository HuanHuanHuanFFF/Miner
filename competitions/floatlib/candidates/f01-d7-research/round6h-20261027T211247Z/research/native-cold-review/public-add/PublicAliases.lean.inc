namespace Submission
open FloatLib.Floats Competition

@[inline] def add (x y : Binary32) : Binary32 :=
  R22NativeAddBase.Submission.R22NativeColdAdd.diagnosticEntry x y
theorem add_spec (x y : Binary32) : add x y = ExecFloat.Spec.add x y :=
  R22NativeAddBase.Submission.R22NativeColdAdd.diagnosticEntry_spec x y

@[inline] def mul := R22NativeAddBase.Submission.mul
theorem mul_spec : ∀ x y : Binary32, mul x y = ExecFloat.Spec.mul x y :=
  R22NativeAddBase.Submission.mul_spec

@[inline] def sum {n : Nat} (x : Vector Binary32 n) : Binary32 :=
  R22NativeAddBase.Submission.sum x
theorem sum_spec : ∀ (n : Nat) (x : Vector Binary32 n), sum x = sumSpec x.get :=
  R22NativeAddBase.Submission.sum_spec

@[inline] def bmm := R22NativeAddBase.Submission.bmm
theorem bmm_spec : ∀ (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get :=
  R22NativeAddBase.Submission.bmm_spec

end Submission
