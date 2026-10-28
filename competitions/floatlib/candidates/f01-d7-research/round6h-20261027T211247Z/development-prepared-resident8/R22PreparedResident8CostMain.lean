import BenchFull
import BenchSuite
import Submission

open Competition

def main : IO UInt32 := do
  let variant ← IO.getEnv "BENCH_VARIANT"
  if variant == some "control" then
    Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.bmm
  else if variant == some "resident8" then
    Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.R22Resident8.guarded
  else if variant == some "prepared8" then
    Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.R22PreparedResident8.guarded
  else
    throw (IO.userError "Unknown BENCH_VARIANT")
