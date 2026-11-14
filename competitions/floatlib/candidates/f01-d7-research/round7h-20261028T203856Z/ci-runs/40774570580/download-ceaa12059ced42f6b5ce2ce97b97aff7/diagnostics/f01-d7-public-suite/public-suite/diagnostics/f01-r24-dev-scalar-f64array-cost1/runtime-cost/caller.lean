import BenchFull
import BenchSuite
import Submission
open Competition
@[noinline] def runControl : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.bmm
@[noinline] def runF64Native : IO UInt32 :=
  Bench.Suite.run Submission.R24F64Add.nativeArrayAdd Submission.mul Submission.sum Submission.bmm
@[noinline] def runF64Boxed : IO UInt32 :=
  Bench.Suite.run Submission.R24F64Add.boxedArrayAdd Submission.mul Submission.sum Submission.bmm
@[noinline] def runF64Cast : IO UInt32 :=
  Bench.Suite.run Submission.R24F64Add.nativeCastAdd Submission.mul Submission.sum Submission.bmm
def main : IO UInt32 := do
  let variant ← IO.getEnv "BENCH_VARIANT"
  if variant == some "control" then runControl
  else if variant == some "f64native" then runF64Native
  else if variant == some "f64boxed" then runF64Boxed
  else if variant == some "f64cast" then runF64Cast
  else throw (IO.userError "BENCH_VARIANT invalid for R24 F64 ADD cost")
