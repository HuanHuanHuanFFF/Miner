import BenchFull
import BenchSuite
import Submission

open Competition

/- Keep environment choice outside Suite callback construction. The prior
   resident8 Main emitted captured-Bool scalar MUL callbacks; actual new
   callback arities and selected BMM still require C inspection. -/
@[noinline] def runControl : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.bmm

@[noinline] def runResident16 : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.R22Resident16.guarded

def main : IO UInt32 := do
  let variant ← IO.getEnv "BENCH_VARIANT"
  if variant == some "control" then
    runControl
  else if variant == some "resident16" then
    runResident16
  else
    throw (IO.userError "Unknown BENCH_VARIANT")
