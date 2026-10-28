/- Runtime discriminator only. Public operations/specifications remain B2. -/
namespace Submission.R22NativeCold
open FloatLib.Floats Competition
@[noinline] def retainedMul (x y : Binary32) : Binary32 := Submission.mul x y
@[inline] def pairOK (u v : UInt32) : Bool :=
  (((u &&& 0x7fffffff) - 0x20000000) |||
   ((v &&& 0x7fffffff) - 0x20000000)) < (0x40000000 : UInt32)
@[inline] def hotMul (x y : Binary32) : Binary32 :=
  ExecFloat.Binary.ofFloat32 (R2W01b.tableProduct x.raw.1 * R2W01b.tableProduct y.raw.1)
@[inline] def inlineMul (x y : Binary32) : Binary32 :=
  if pairOK x.raw.1 y.raw.1 then hotMul x y else Submission.mul x y
@[inline] def coldMul (x y : Binary32) : Binary32 :=
  if pairOK x.raw.1 y.raw.1 then hotMul x y else retainedMul x y
end Submission.R22NativeCold
