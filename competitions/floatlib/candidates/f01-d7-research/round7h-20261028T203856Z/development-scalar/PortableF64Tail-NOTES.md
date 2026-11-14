# Conditional structural-remaining frontend

The original FP source dd775683…, Main254a106f…, Barrier3d374250… and the
frozen input bytes stay unchanged. The alternative only supplies
`Submission.R24PortableF64Tail.sumRemaining/attemptPrepared/attemptCold` and
directly reuses original preparation, cache type, count bound, proposal,
radius and certificate. It has no benchmark dispatch or new CI request.

For original loop state `(i,s)`, define `s₀=+0` and
`sᵢ₊₁=Float.add sᵢ (Float.mul a[i] b[i])`. The original while advances from
`(0,s₀)` to `(n,sₙ)` one indexed reading at a time. At recursive entry,
`remaining=n−i`; the recursive step computes the identical next product and
addition, then calls with `(i+1,sᵢ₊₁,remaining−1)`. The zero case returns the
same accumulator. This is a control/order argument and uses no associativity
of floating addition. The short Lean `sumRemaining_eq_foldl` refines to the
same recursively defined list of readings; it is still NOT_COMPILED and does
not claim the full Id/while translation or native rounding agreement proved.

The finite Python comparison checks the same structural recursion separately:
all86 frozen fixtures agree in attempt/rejection; all82 evaluated sums and
endpoint words agree bitwise. Another128 untimed model examples also agree
(116 reach the fold). Accepted outputs remain equal to the independent exact
oracle. These counts are neither native execution nor a performance result.

Before any activation, inspect the selected original FP MAC loop, not its
outer benchmark pass or cache preparation. Evidence would be Float boxing,
generic loop-state allocation or dispatch repeated per MAC. The proposed
worker's intended ABI is Float accumulator argument and result, with
structural `remaining`, not a well-founded `n−i` recursion. Actual generated
C/ASM must decide whether that happens.

If the original is already unboxed with no repeated state allocation, PARK
this source and do not buy a second timing run. It may even add a second
counter operation where the original while needs only an index. No variant
grid, threshold/shape route or compiler-flag change is proposed.
