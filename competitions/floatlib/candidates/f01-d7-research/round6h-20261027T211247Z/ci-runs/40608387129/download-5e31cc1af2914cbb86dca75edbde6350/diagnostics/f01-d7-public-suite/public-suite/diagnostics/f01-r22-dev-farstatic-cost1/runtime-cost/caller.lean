import BenchFull
import BenchSuite
import Submission
open Competition

@[noinline] def runControl : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.bmm

@[noinline] def runFar : IO UInt32 :=
  Bench.Suite.run Submission.R22FarOnlyAdd.diagnosticEntry Submission.mul Submission.sum Submission.bmm

def main : IO UInt32 := do
  let variant ← IO.getEnv "BENCH_VARIANT"
  if variant == some "control" then runControl
  else if variant == some "far" then runFar
  else throw (IO.userError "BENCH_VARIANT must be control or far")
