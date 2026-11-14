import BenchFull
import BenchSuite
import Submission

open Competition

@[inline] def r22CostBroadWordAdd (x y : Binary32) : Binary32 :=
  Submission.R22BroadWordAdd.diagnosticEntry x y

def main : IO UInt32 := do
  let variant ← IO.getEnv "BENCH_VARIANT"
  if variant == some "control" then
    Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.bmm
  else if variant == some "broadword" then
    Bench.Suite.run r22CostBroadWordAdd Submission.mul Submission.sum Submission.bmm
  else
    throw (IO.userError "Unknown BENCH_VARIANT")
