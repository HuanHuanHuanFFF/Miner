/- B2 proof-only interface. No builder, no public candidate. NOT_RUN. -/
namespace Submission.R22FloatArrayBridgeReview
open FloatLib.Floats Competition

@[inline] def checkNative (source : Float32) (stored : Float) : Bool :=
  (ExecFloat.Binary.ofFloat32 stored.toFloat32).raw.1 ==
    (ExecFloat.Binary.ofFloat32 source).raw.1

theorem checked_import (source : Float32) (stored : Float)
    (h : checkNative source stored = true) :
    ExecFloat.Binary.ofFloat32 stored.toFloat32 = ExecFloat.Binary.ofFloat32 source := by
  apply ExecFloat.ext
  apply Subtype.ext
  simpa only [checkNative, beq_iff_eq] using h

theorem checked_native (source : Float32) (stored : Float)
    (h : checkNative source stored = true) : stored.toFloat32 = source := by
  have he := congrArg ExecFloat.Binary.toFloat32 (checked_import source stored h)
  simpa only [ExecFloat.Binary.toFloat32_ofFloat32] using he

theorem checked_convert (raw : Binary32) (stored : Float)
    (h : checkNative (R2W01b.convert raw.raw.1) stored = true) :
    stored.toFloat32 = ExecFloat.Binary.toFloat32 raw := by
  have he := checked_native (R2W01b.convert raw.raw.1) stored h
  rw [R2W01c.convert_eq] at he
  exact he

end Submission.R22FloatArrayBridgeReview
