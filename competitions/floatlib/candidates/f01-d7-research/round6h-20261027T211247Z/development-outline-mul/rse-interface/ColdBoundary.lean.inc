namespace Submission.R22RseCold
open Competition
@[noinline] def retainedB2 (x y : Binary32) : Binary32 := Submission.mul x y
@[inline] def inlineOld (x y : Binary32) : Binary32 :=
  R14ExponentShift.guardedMul Submission.mul x y
@[inline] def outlined (x y : Binary32) : Binary32 :=
  R14ExponentShift.guardedMul retainedB2 x y
end Submission.R22RseCold
