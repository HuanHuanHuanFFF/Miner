import BenchFull
import BenchSuite
import Submission
open Competition
@[noinline] def runControl : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.bmm
@[noinline] def runTh0 : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.nativeMul Submission.sum Submission.bmm
@[noinline] def runNativeInline : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.R22NativeCold.inlineMul Submission.sum Submission.bmm
@[noinline] def runNativeCold : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.R22NativeCold.coldMul Submission.sum Submission.bmm
@[noinline] def runNativeAdd : IO UInt32 :=
  Bench.Suite.run Submission.R22NativeColdAdd.diagnosticEntry Submission.mul Submission.sum Submission.bmm

def main : IO UInt32 := do
  let variant ← IO.getEnv "BENCH_VARIANT"
  if variant == some "control" then runControl
  else if variant == some "th0" then runTh0
  else if variant == some "nativeinline" then runNativeInline
  else if variant == some "nativecold" then runNativeCold
  else if variant == some "nativeadd" then runNativeAdd
  else throw (IO.userError "BENCH_VARIANT invalid for NativeCold diagnostic")
