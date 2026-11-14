import BenchFull
import BenchSuite
import Submission
open Competition
@[noinline] def runControl : IO UInt32 :=
  Bench.Suite.run R19BiasBase.add R19BiasBase.mul R19BiasBase.sum R19BiasBase.bmm
@[noinline] def runNative : IO UInt32 :=
  Bench.Suite.run R19BiasBase.add Submission.R24Scalar.nativeMul R19BiasBase.sum R19BiasBase.bmm
@[noinline] def runInteger : IO UInt32 :=
  Bench.Suite.run R19BiasBase.add Submission.mul R19BiasBase.sum R19BiasBase.bmm
@[noinline] def runNativeFirst : IO UInt32 :=
  Bench.Suite.run R19BiasBase.add Submission.R24Scalar.nativeFirst R19BiasBase.sum R19BiasBase.bmm
@[noinline] def runIntegerFirst : IO UInt32 :=
  Bench.Suite.run R19BiasBase.add Submission.R24Scalar.integerFirst R19BiasBase.sum R19BiasBase.bmm
def main : IO UInt32 := do
  let variant ← IO.getEnv "BENCH_VARIANT"
  if variant == some "control" then runControl
  else if variant == some "native" then runNative
  else if variant == some "integer" then runInteger
  else if variant == some "nativefirst" then runNativeFirst
  else if variant == some "integerfirst" then runIntegerFirst
  else throw (IO.userError "BENCH_VARIANT invalid for R24 scalar diagnostic")
