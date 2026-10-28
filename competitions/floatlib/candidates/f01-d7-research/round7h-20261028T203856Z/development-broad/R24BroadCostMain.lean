import BenchFull
import BenchSuite
import Submission

open Competition

@[noinline] def runControl : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.bmm

@[noinline] def runNativeArray : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.R24BroadArray.guarded

@[noinline] def runCheckedFlat : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.R24BroadFlat.guarded

def main : IO UInt32 := do
  let variant ← IO.getEnv "BENCH_VARIANT"
  if variant == some "control" then runControl
  else if variant == some "nativearray" then runNativeArray
  else if variant == some "checkedflat" then runCheckedFlat
  else throw (IO.userError "BENCH_VARIANT must be control, nativearray, or checkedflat")
