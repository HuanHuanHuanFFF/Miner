import BenchFull
import BenchSuite
import Submission

open Competition

def main : IO UInt32 := do
  let variant ← IO.getEnv "BENCH_VARIANT"
  if variant == some "control" then
    Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.bmm
  else if variant == some "flatadd" then
    Bench.Suite.run Submission.R22FlatScale.add Submission.mul Submission.sum Submission.bmm
  else if variant == some "flatmul" then
    Bench.Suite.run Submission.add Submission.R22FlatScale.mul Submission.sum Submission.bmm
  else
    throw (IO.userError "Unknown BENCH_VARIANT")
