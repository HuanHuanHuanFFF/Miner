# Next proof interface after runtime freeze

Paper/interface research only; no new runtime source, Lean build or CI request.
The native pilot establishes finite outputs and selected code structure, not
universal correctness or target admission. This plan keeps the measured
FloatArray program intact.

Pinned Lean v4.34 FloatArray source is preserved at
`source-cache/Lean434-FloatArray-Basic.lean.raw`, exact Git blob
29eb263dfd77c1be05e3cd3d45b94023b4188ed9, SHA256
80f3eff556a5316357ceff025f8b094f9c47915abdb61d4bbb843b92bc8075de.

- FloatArray is logically `structure { data : Array Float }` (line17).
  size (47), push (43) and get! (63) are definitions over that data field,
  with native extern implementations for the optimized representation.
  Thus logical getter/size/push identities can be obtained by cases/rfl.
- Use `values.data` or a recursively defined reading list only in erased
  proofs. Calling the extern `FloatArray.data` from runtime constructs the
  generic boxed Array view and changes the measured program. Do not replace
  the actual native FloatArray getter with a generic Array Float runtime fold.
- `FloatArray.toList` is partial (93). Avoid treating its executable body as
  a total reducible reference in a kernel proof; use the total Array data
  model or the explicit finite readings list instead.

The first useful invariant is about canonically prepared operands, not all
manually constructed Prepared records:

`prepare(raw).values.data = raw.map (Float.ofBits ∘ widenBits)` on finite raw
words, equal lengths, valid flag and the cached max index bound. Nonfinite
words require a separate invalid-cache invariant because their stored value
is a placeholder. The nonzero-subnormal widening extension still needs its
own exact bit/value/finite proof; native oracle cases do not fill that gap.

Next connect the actual structural worker to its reading list. Its recurrence
and Float accumulator already preserve the exact operation order; no
associativity of Float addition is available or needed. The runtime products
must be linked to exact raw32 products, then the existing finite native fold
enclosure theorem instantiated with count L and the SAME separable H that
the measured program uses, including zero entries. Do not silently replace
it by a free paired maximum after observing misses.

The fast result theorem should quantify an arbitrary raw proposal, prove the
actual finite endpoint arithmetic and raw64 order keys, exact midpoint words
(including minnormal lower spacing), and conclude the actual32 output from
the strict enclosure. Proposal accuracy is deliberately absent. Exact zero,
ties and rejected domains stay in the fallback.

Prove the optimized64/128 reference tiers against finite exact Int/dyadic
replay separately. A fastpath theorem can first conclude `attempt≠0 -> word
= referenceSpec`; full eager/lazy correctness then composes that result with
the reference equivalence. Their current equivalenceStatement definitions
are propositions, not accepted proofs.

The bank layer needs only a pointwise row-pair refinement once the backend
is proved, plus row-cache/flatten order and lifetime boundaries. Its new six
banks/464 golden outputs remain finite model evidence until actual native
execution. No official matrix/BMM equivalence is implied. Only after the
user chooses a target should a record/layout/whole-model proof and official
performance gate be planned.
