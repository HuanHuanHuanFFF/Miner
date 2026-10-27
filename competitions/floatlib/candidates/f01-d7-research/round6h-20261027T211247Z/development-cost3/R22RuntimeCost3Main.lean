import BenchFull
import BenchSuite
import Submission

open Competition

@[inline] def r22CostFloatProductMul (x y : Binary32) : Binary32 :=
  Submission.R22FloatProduct.guardedMul Submission.mul x y

@[inline] def r22CostSameExponentAdd (x y : Binary32) : Binary32 :=
  if Submission.R22SameExponent.eligible x.raw.1 y.raw.1 then
    Submission.FastMul.ofBits (Submission.R22SameExponent.core x.raw.1 y.raw.1)
  else Submission.add x y

def main : IO UInt32 := do
  let variant ← IO.getEnv "BENCH_VARIANT"
  if variant == some "control" then
    Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.bmm
  else if variant == some "streamed" then
    Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.R22StreamingCost.guarded
  else if variant == some "quad" then
    Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.R22StreamingQuad.guarded
  else if variant == some "prepared" then
    Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.R22PreparedQuad.guarded
  else if variant == some "fpmul" then
    Bench.Suite.run Submission.add r22CostFloatProductMul Submission.sum Submission.bmm
  else if variant == some "sameexp" then
    Bench.Suite.run r22CostSameExponentAdd Submission.mul Submission.sum Submission.bmm
  else
    throw (IO.userError "Unknown BENCH_VARIANT")
