
namespace Submission.R24Scalar
open FloatLib.Floats Competition
@[inline] def pairOK (u v : UInt32) : Bool :=
  (((u &&& 0x7fffffff)-0x20000000) |||
   ((v &&& 0x7fffffff)-0x20000000)) < (0x40000000 : UInt32)
@[inline] def hotMul (x y : Binary32) : Binary32 :=
  ExecFloat.Binary.ofFloat32 (R2W01b.tableProduct x.raw.1 * R2W01b.tableProduct y.raw.1)
@[inline] def nativeMul (x y : Binary32) : Binary32 :=
  if pairOK x.raw.1 y.raw.1 then hotMul x y
  else R19BiasBase.R19DirectBias.retainedMul x y
@[inline] def nativeFirst (x y : Binary32) : Binary32 :=
  if pairOK x.raw.1 y.raw.1 then hotMul x y else Submission.mul x y
@[inline] def integerFirst (x y : Binary32) : Binary32 :=
  R19BiasBase.R19DirectBias.guardedMul nativeMul x y
end Submission.R24Scalar
