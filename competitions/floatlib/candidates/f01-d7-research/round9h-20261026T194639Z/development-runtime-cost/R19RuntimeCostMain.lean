import BenchFull
import BenchSuite
import Submission

open Competition

/- Diagnostic composition only. No theorem equating this MUL to the contract. -/
@[inline] def r19CostGuardedMul (x y : Binary32) : Binary32 :=
  Submission.R19DirectBias.guardedMul Submission.mul x y

def main : IO UInt32 := do
  let variant ← IO.getEnv "BENCH_VARIANT"
  if variant == some "control" then
    Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.bmm
  else if variant == some "guarded" then
    Bench.Suite.run Submission.add r19CostGuardedMul Submission.sum Submission.bmm
  else
    throw (IO.userError "BENCH_VARIANT must be control or guarded")
