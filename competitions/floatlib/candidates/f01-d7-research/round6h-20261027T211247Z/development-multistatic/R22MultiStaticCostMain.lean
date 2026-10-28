import BenchFull
import BenchSuite
import Submission

open Competition

/- Diagnostic composition only. Both guarded variants have the exact old
   normalCore and guard. Neither has a proved new public mul_spec. -/
@[inline] def r22CostInlineOldMul (x y : Binary32) : Binary32 :=
  Submission.R19DirectBias.guardedMul Submission.mul x y

@[inline] def r22CostOutlinedMul (x y : Binary32) : Binary32 :=
  Submission.R22OutlineMul.diagnosticEntry x y

/- Keep variant selection outside these separate Suite caller definitions.
   Actual emitted closed callbacks and tail jumps still require inspection. -/
@[noinline] def runControl : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.bmm

@[noinline] def runInlineOld : IO UInt32 :=
  Bench.Suite.run Submission.add r22CostInlineOldMul Submission.sum Submission.bmm

@[noinline] def runOutline : IO UInt32 :=
  Bench.Suite.run Submission.add r22CostOutlinedMul Submission.sum Submission.bmm

@[inline] def r22CostNativeProductMul (x y : Binary32) : Binary32 :=
  Submission.R22NativeProductScale.guardedMul Submission.mul x y

@[noinline] def runNativeProduct : IO UInt32 :=
  Bench.Suite.run Submission.add r22CostNativeProductMul Submission.sum Submission.bmm

@[noinline] def runResident16 : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.R22Resident16.guarded

def main : IO UInt32 := do
  let variant ← IO.getEnv "BENCH_VARIANT"
  if variant == some "control" then
    runControl
  else if variant == some "inlineOld" then
    runInlineOld
  else if variant == some "outline" then
    runOutline
  else if variant == some "nativeprod" then
    runNativeProduct
  else if variant == some "resident16" then
    runResident16
  else
    throw (IO.userError "BENCH_VARIANT must be control, inlineOld, outline, nativeprod, or resident16")
