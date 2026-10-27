namespace Submission
open FloatLib.Floats Competition
@[inline] def mul (x y : Binary32) : Binary32 :=
  R17NumericMulInteger.guardedMul mul0 x y
theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y :=
  R18NumericMulSpec.guardedMul_spec mul0 mul0_spec x y
