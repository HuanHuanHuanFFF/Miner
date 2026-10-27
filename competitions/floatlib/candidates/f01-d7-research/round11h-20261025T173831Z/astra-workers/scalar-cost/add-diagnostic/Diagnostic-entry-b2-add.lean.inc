namespace Submission.R17NumericAdd
open FloatLib.Floats Competition

def diagnosticEntry (x y : Binary32) : Binary32 :=
  guardedAdd Submission.add x y

end Submission.R17NumericAdd
