/- NOT_RUN -/
namespace D7SingletonNative

open FloatLib.Floats Competition

/- NOT_RUN -/
@[inline] def nativeProduct (x y : Binary32) : Binary32 :=
  let r := ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y
  if hr : r.isNaN = false then ExecFloat.Binary.ofFloat32 r
  else Submission.mul x y

/- NOT_RUN -/
theorem nativeProduct_eq (x y : Binary32) :
    nativeProduct x y = Submission.mul x y := by
  unfold nativeProduct
  dsimp only
  split
  · rename_i hr
    have hi := Submission.NotNaNProbe.mul_inputs
      (ExecFloat.Binary.toFloat32 x) (ExecFloat.Binary.toFloat32 y) hr
    have hm := Submission.R7Native.ofFloat32Mul
      (ExecFloat.Binary.toFloat32 x) (ExecFloat.Binary.toFloat32 y) hi.1 hi.2
    rw [Submission.NotNaNProbe.roundtrip x hi.1,
      Submission.NotNaNProbe.roundtrip y hi.2] at hm
    simpa only [Submission.mul_eq] using hm
  · rfl

end D7SingletonNative
