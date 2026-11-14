import BenchFull
import BenchSuite
import Submission

open Competition

@[inline] def r22CostScaledMul (x y : Binary32) : Binary32 :=
  Submission.R21ScaledU32.guardedMul Submission.mul x y

def main : IO UInt32 := do
  let variant ← IO.getEnv "BENCH_VARIANT"
  if variant == some "control" then
    Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.bmm
  else if variant == some "streamed" then
    Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.R22StreamingCost.guarded
  else if variant == some "scaled" then
    Bench.Suite.run Submission.add r22CostScaledMul Submission.sum Submission.bmm
  else
    throw (IO.userError "BENCH_VARIANT must be control, streamed or scaled")
