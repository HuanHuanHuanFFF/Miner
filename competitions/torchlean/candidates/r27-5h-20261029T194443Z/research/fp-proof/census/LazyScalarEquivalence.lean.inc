/- Relative scalar equivalence only. This does not prove the historical FP or
   integer fallback kernels correct. Append to the lazy-preparation runtime. -/
namespace Submission.R27LazyWordProof
open Submission.R24ExactDotCost
open Submission.R26WordFallback

private theorem fp_prepare_raw (raw : Array UInt32) :
    (Submission.R24PortableF64.prepare raw).raw = raw := by
  by_cases h : 1073741824 < raw.size
  · simp only [Submission.R24PortableF64.prepare, h, ite_true] <;> rfl
  · simp only [Submission.R24PortableF64.prepare, h, ite_false] <;> rfl

def eagerPrepare (raw : Array UInt32) : Prepared :=
  ⟨Submission.R24PortableF64.prepare raw, prepareOperand raw⟩

def eagerDot (left right : Prepared) : UInt32 :=
  let guess := Submission.R24PortableF64.attemptPrepared left.fp right.fp
  if guess == 0 then Submission.R26WordFallback.exact (pair left.word right.word)
  else guess

/-- Lazy preparation preserves the old scalar computation on every pair of
    raw arrays, including exceptional values, shape mismatch and signed zero. -/
theorem cold_equivalent (a b : Array UInt32) :
    dotPrepared (prepare a) (prepare b) = eagerDot (eagerPrepare a) (eagerPrepare b) := by
  simp only [dotPrepared, prepare, eagerDot, eagerPrepare, fp_prepare_raw]

end Submission.R27LazyWordProof
