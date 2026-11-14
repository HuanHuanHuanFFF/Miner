# Actual runtime proof frontier

The preserved `Submission.retainedCorrect` certifies only `retainedKernels`.
No R26 `Submission.correct` is provided. Python models and native finite
checksums cannot instantiate any missing all-input proof below.

The R24 prepared-word helper is already structural in saved C. The intended
R26 gain is replacing the shipped eighteen-limb MAC in real model calls. The
minimum full-model proof should start from an actual dot equality and then
reuse the official kernel definitions, or prove the prepared cache getters.

For `fp-raw5`, `RawFactorProofContractOnly.lean` is a small NOT_COMPILED bridge:
raw exponent/fraction to official fields, raw mantissa to `mantOf`, raw index to
`idxOf`, exact UInt64 product, and official exact rational value. It does not
claim native sign-predicate equality or full loop/rounding correctness.

Remaining dependencies, in useful order:

1. Actual fused `prepare` has raw getter agreement and valid finite/size guards;
   nonzero indices lie between its actual min/max. Zeros must remain outside
   the min bound, since their underflowing UInt32 shift is harmless only after
   showing the product is zero.
2. Nonzero UInt64 mantissa products are exact and <2^48. Pair metadata bounds
   every active term shift; the 128 guard gives span≤80 and bounds each positive
   and negative prefix below 2^128. The signed64 guard gives each absolute
   signed prefix <2^62. These are bounds on actual ordered getters, not an
   abstract list unrelated to runtime preparation.
3. The exact structural word64/128 recurrence refines the ordered integer sum,
   including the original nonempty/all-negative-zero flag. The ordinary zero
   cancellation result must be +0; a nonzero exact negative result rounded to
   zero must be -0.
4. `round128` equals the official final RNE (`finishWord`/roundDyadic) at shifts
   0/64/128/>128, normal/subnormal transition, midpoint parity and overflow.
   An alternate terminal using one official `finishWord` call could remove
   this proof dependency at a once-per-dot runtime cost; it must be measured
   as its own source rather than assumed equivalent in cost.
5. The actual FP attempt needs exact widening for all admitted finite words,
   the actual native tail accumulation enclosure, and the actual checker
   strict-cell theorem. Research finite/key tasks own those dependencies.
6. `dotPrepared` follows original `dotFn` whenever finite/range/certificate
   guards fail. Nonfinite and mismatched inputs retain the official semantics;
   no canonical-NaN policy is imported from R24's diagnostic replay.
7. Dense and conv caches need exact row/column/window getter identities and
   the final bias term. Empty output extents return before preparation. The
   shared conv cache uses the original `windowAt` unchanged, so no new padding
   arithmetic or different rounding order is introduced.

This is a dependency/cost boundary, not a proof-completion estimate. CI and
token costs are UNKNOWN until saved actual evidence exists.
