import BenchFull
import BenchSuite
import Submission

open Competition

def main : IO UInt32 := do
  let variant ← IO.getEnv "BENCH_VARIANT"
  if variant == some "control" then
    Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.bmm
  else if variant == some "quad" then
    Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.R22StreamingQuad.guarded
  else if variant == some "prepared" then
    Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.R22PreparedQuad.guarded
  else if variant == some "pair8" then
    Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.R22Pair8.guarded
  else
    throw (IO.userError "Unknown BENCH_VARIANT")
