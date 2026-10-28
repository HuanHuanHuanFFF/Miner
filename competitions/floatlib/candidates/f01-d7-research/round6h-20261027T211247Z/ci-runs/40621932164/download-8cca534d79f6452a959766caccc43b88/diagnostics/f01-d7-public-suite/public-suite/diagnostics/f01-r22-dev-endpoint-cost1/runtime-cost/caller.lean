import BenchFull
import BenchSuite
import Submission
open Competition
@[noinline] def runControl : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.bmm
@[noinline] def runOldNative : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.R22NativeCold.coldMul Submission.sum Submission.bmm
@[noinline] def runEndpoint : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.R22ExtremeNativeCold.diagnosticEntry Submission.sum Submission.bmm

def main : IO UInt32 := do
  let variant ← IO.getEnv "BENCH_VARIANT"
  if variant == some "control" then runControl
  else if variant == some "oldnative" then runOldNative
  else if variant == some "endpoint" then runEndpoint
  else throw (IO.userError "BENCH_VARIANT invalid for endpointcost")
