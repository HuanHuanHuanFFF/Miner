/- Diagnostic module only. Not a submission and not a gate modification.
   Build beside one exact candidate copied as Kernel.lean in an isolated copy
   of the pinned official environment. Compilation NOT_RUN.
   Lean [noinline] does not imply a C noinline attribute in the pinned emitter. -/
import Kernel

namespace R11W03Probe
open FloatLib.Floats Competition

@[noinline] def fullN1Shared (A : Vector Binary32 4) (B : Vector Binary32 2) :
    Vector Binary32 8 :=
  Submission.bmm 1 4 1 2 A B

@[noinline] def fullN2Shared (A : Vector Binary32 8) (B : Vector Binary32 4) :
    Vector Binary32 8 :=
  Submission.bmm 1 4 2 2 A B

@[noinline] def fullN2Mixed (A : Vector Binary32 8) (B : Vector Binary32 16) :
    Vector Binary32 8 :=
  Submission.bmm 4 1 2 2 A B

@[noinline] def fullN2Tail (A : Vector Binary32 10) (B : Vector Binary32 4) :
    Vector Binary32 10 :=
  Submission.bmm 1 5 2 2 A B

end R11W03Probe
