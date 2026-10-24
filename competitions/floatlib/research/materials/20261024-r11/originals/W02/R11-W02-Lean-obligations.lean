/- R11-W02 proposed fragment. It intentionally contains no axioms or placeholder
   theorems pretending to prove the missing facts. NOT compiled. -/
namespace Submission.R11W02

inductive ZeroProductSummary
  | allFinite
  | firstNaN (k : Nat) (quietWord : UInt32)
  | firstInfinity (k : Nat)

/-- The classifier must return the least k with exponent field 255, distinguishing
    fraction=0 (infinity) from fraction!=0 (NaN). Prove this over raw UInt32 words. -/
def classifyZeroColumn (n : Nat) (A : Array UInt32) : ZeroProductSummary :=
  -- Implementation intentionally omitted pending a concrete, bound-carrying scan.
  .allFinite

/- Concrete existing declarations to reuse from the supplied exact Kernel text:

#check R7W01.mul32_not_snan
#check R7W01.add_mul_absorb
#check R7W01.modelDotFold_absorb
#check R7NaNReplay.replayFold_absorb
#check NativeFinal.dot_eq

New theorem statements to add once raw-index proofs are supplied:

zero_mul_finite_bits:
  finite(a) -> b ∈ {+0,-0} -> Spec.mul a b = signedZero(sign(a) xor sign(b))

zero_prefix_sum_pos:
  allFinite(A[0..k)) -> orderedDot(A[0..k), BsignedZero, +0) = +0

classifyZeroColumn_sound:
  classifyZeroColumn n A = firstNaN k w ->
    k < n ∧ isNaN(A[k]) ∧ (∀ i<k, isFinite(A[i])) ∧ w = quietNaNWord(A[k])

zero_column_summary_eq_dot:
  summary(A) = s -> exactOriginalDot(A, BsignedZero) = summaryWord(s)

single_nonzero_suffix_preserves:
  centerResultIsNonNaN -> allFinite(A[r+1..n)) ->
    exactOriginalSuffixFold(centerResult, A, signedZeroB) = centerResult

These are obligations, not proved declarations. In particular, the classifier above
is only a type/shape sketch and must not be integrated as a working implementation.
-/
end Submission.R11W02
