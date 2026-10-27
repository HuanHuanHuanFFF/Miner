import BenchFull
import BenchSuite
import Submission

open Competition

/- Diagnostic only. Distinct noinline entry identities prevent scalar variant capture;
   the existing guardedAdd and public ADD implementation inline inside these bodies.
   No theorem equating guarded ADD to the contract is claimed. -/
@[noinline] def r19CostControlAdd (x y : Binary32) : Binary32 :=
  Submission.add x y

@[noinline] def r19CostGuardedAdd (x y : Binary32) : Binary32 :=
  Submission.R19GRS32Add.guardedAdd Submission.add x y

def main : IO UInt32 := do
  let variant ← IO.getEnv "BENCH_VARIANT"
  let add : Binary32 → Binary32 → Binary32 ←
    if variant == some "control" then pure r19CostControlAdd
    else if variant == some "guarded" then pure r19CostGuardedAdd
    else throw (IO.userError "BENCH_VARIANT must be control or guarded")
  Bench.Suite.run add Submission.mul Submission.sum Submission.bmm
