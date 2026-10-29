/- Whole-model runtime research only. This proposed record has no correctness theorem.
Its exact original fallback is retained. No official verification or adoption is claimed. -/
namespace Submission.R25FpModel
open ExactRuntime
local instance : Inhabited R24PortableF64.Prepared :=
  ⟨⟨#[], FloatArray.emptyWithCapacity 0, 0, false⟩⟩

@[noinline] def dot (n : Nat) (fa fb : Nat → Word) : Word :=
  if n < 32 then dotFn n fa fb
  else
    let a := Array.ofFn (n := n) fun i => fa i.val
    let b := Array.ofFn (n := n) fun i => fb i.val
    let guess := R24PortableF64.attemptCold a b
    if guess == 0 then dotFn n fa fb else guess

@[noinline] def linear (rows inW outW : Nat) (relu : Bool) (X W b : Array Word) : Array Word :=
  if inW < 31 then linearWith dotFn rows inW outW relu X W b
  else
    let xs := Array.ofFn (n := rows) fun i =>
      R24PortableF64.prepare (Array.ofFn (n := inW + 1) fun t =>
        if t.val < inW then X[i.val * inW + t.val]! else oneW)
    let ws := Array.ofFn (n := outW) fun j =>
      R24PortableF64.prepare (Array.ofFn (n := inW + 1) fun t =>
        if t.val < inW then W[j.val * inW + t.val]! else b[j.val]!)
    Array.ofFn (n := rows * outW) fun q =>
      let i := q.val / outW
      let j := q.val % outW
      let guess := R24PortableF64.attemptPrepared xs[i]! ws[j]!
      let value := if guess == 0 then
        dotFn (inW + 1) (fun t => if t < inW then X[i * inW + t]! else oneW)
          (fun t => if t < inW then W[j * inW + t]! else b[j]!)
        else guess
      act relu value

@[noinline] def gemm (batch m k n : Nat) (A B : Array Word) : Array Word :=
  if k < 32 then gemmWith dotFn batch m k n A B
  else
    let as_ := Array.ofFn (n := batch * m) fun r =>
      R24PortableF64.prepare (Array.ofFn (n := k) fun t => A[r.val * k + t.val]!)
    let bs := Array.ofFn (n := batch * n) fun c =>
      R24PortableF64.prepare (Array.ofFn (n := k) fun t => B[((c.val / n) * k + t.val) * n + c.val % n]!)
    Array.ofFn (n := batch * (m * n)) fun q =>
      let beta := q.val / (m * n)
      let i := q.val / n % m
      let j := q.val % n
      let guess := R24PortableF64.attemptPrepared as_[beta * m + i]! bs[beta * n + j]!
      if guess == 0 then dotFn k (fun t => A[(beta * m + i) * k + t]!)
        (fun t => B[(beta * k + t) * n + j]!) else guess

def kernels : Kernels := { retainedKernels with
  dense := ⟨linear, gemm⟩
  conv := ⟨conv2dWith dot, depthwiseWith dot⟩ }
end Submission.R25FpModel

namespace Submission
/-- This record is a runtime probe. It has no Submission.correct. -/
def kernels : ExactRuntime.Kernels := R25FpModel.kernels
end Submission
