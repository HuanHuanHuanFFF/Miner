/- Native-only experiment binding. It has no correctness theorem and is not
an official submission. Token GEMM and rows<8 remain the exact predecessor. -/
namespace R27PackedExperiment
open ExactRuntime
def linear (rows k outW : Nat) (relu : Bool) (X W b : Array Word) : Array Word :=
  if 8 ≤ rows then R27PackedLinear.linear 16 rows k outW relu X W b
  else Submission.kernels.dense.linear rows k outW relu X W b
def kernels : Kernels :=
  { Submission.kernels with dense := { Submission.kernels.dense with linear := linear } }
end R27PackedExperiment
