namespace Submission.R17NumericMulInteger
open FloatLib.Floats Competition

def diagnosticEntry (x y : Binary32) : Binary32 :=
  guardedMul Submission.mulBeforeR16NativeRepack x y

end Submission.R17NumericMulInteger
