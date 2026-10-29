/- Full twelve runtime probe; the retained proof is for retainedKernels only. -/
namespace Submission.R26WordModel
open ExactRuntime
open R26WordFallback

@[noinline] def dot (n : Nat) (fa fb : Nat → Word) : Word :=
  let a := Array.ofFn (n := n) fun i => fa i.val
  let b := Array.ofFn (n := n) fun i => fb i.val
  dotPrepared (prepare a) (prepare b)

@[noinline] def linear (rows inW outW : Nat) (relu : Bool) (X W b : Array Word) : Array Word :=
  if rows * outW == 0 then #[]
  else
    let xs := Array.ofFn (n := rows) fun i =>
      prepare (Array.ofFn (n := inW + 1) fun t =>
        if t.val < inW then X[i.val * inW + t.val]! else oneW)
    let ws := Array.ofFn (n := outW) fun j =>
      prepare (Array.ofFn (n := inW + 1) fun t =>
        if t.val < inW then W[j.val * inW + t.val]! else b[j.val]!)
    Array.ofFn (n := rows * outW) fun q =>
      act relu (dotPrepared xs[q.val / outW]! ws[q.val % outW]!)

@[noinline] def gemm (batch m k n : Nat) (A B : Array Word) : Array Word :=
  if batch * (m * n) == 0 then #[]
  else
    let as_ := Array.ofFn (n := batch * m) fun r =>
      prepare (Array.ofFn (n := k) fun t => A[r.val * k + t.val]!)
    let bs := Array.ofFn (n := batch * n) fun c =>
      prepare (Array.ofFn (n := k) fun t => B[((c.val / n) * k + t.val) * n + c.val % n]!)
    Array.ofFn (n := batch * (m * n)) fun q =>
      let beta := q.val / (m * n)
      let i := q.val / n % m
      let j := q.val % n
      dotPrepared as_[beta * m + i]! bs[beta * n + j]!

def dotArrays (a b : Array Word) : Word :=
  if a.size == b.size then dotPrepared (prepare a) (prepare b) else dotSpec a b

def sumArray (x : Array Word) : Word := dot x.size (fun i => x[i]!) (fun _ => oneW)

def kernels : Kernels := { retainedKernels with
  core := ⟨sumArray, dotArrays⟩
  dense := ⟨linear, gemm⟩
  conv := ⟨conv2dWith dot, depthwiseWith dot⟩
  elem := ⟨avgpoolWith dot, maxpoolW, addReluSpec, scaleShiftSpec⟩ }
end Submission.R26WordModel

namespace Submission
/-- UNPROVED runtime probe. retainedCorrect applies only to retainedKernels. -/
def kernels : ExactRuntime.Kernels := R26WordModel.kernels
end Submission
