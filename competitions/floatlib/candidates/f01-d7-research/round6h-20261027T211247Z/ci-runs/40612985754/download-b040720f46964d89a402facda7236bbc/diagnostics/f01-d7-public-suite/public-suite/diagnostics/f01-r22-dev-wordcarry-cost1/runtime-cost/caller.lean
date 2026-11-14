import BenchFull
import BenchSuite
import Submission
open Competition
@[noinline] def runControl : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.bmm
@[noinline] def runOldWord : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.R22OutlineMul.diagnosticEntry Submission.sum Submission.bmm
@[noinline] def runWordCarry : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.R22WordCarry.guardedMul Submission.sum Submission.bmm

def main : IO UInt32 := do
  let variant ← IO.getEnv "BENCH_VARIANT"
  if variant == some "control" then runControl
  else if variant == some "oldword" then runOldWord
  else if variant == some "wordcarry" then runWordCarry
  else throw (IO.userError "BENCH_VARIANT invalid for wordcarry")
