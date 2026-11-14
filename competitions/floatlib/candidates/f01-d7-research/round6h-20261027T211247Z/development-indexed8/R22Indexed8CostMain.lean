import BenchFull
import BenchSuite
import Submission

open Competition

@[noinline] def runControl : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.bmm

@[noinline] def runRaw8 : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.R22Resident8.guarded

@[noinline] def runIndexed8 : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.R22IndexedResident8.guarded

def main : IO UInt32 := do
  let variant ← IO.getEnv "BENCH_VARIANT"
  if variant == some "control" then runControl
  else if variant == some "raw8" then runRaw8
  else if variant == some "indexed8" then runIndexed8
  else throw (IO.userError "BENCH_VARIANT must be control, raw8, or indexed8")
