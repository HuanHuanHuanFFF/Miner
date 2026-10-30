# Exact runtime integration boundary

Inspected R26 fp-word-conv6 source ad9bde3e9e8490df15f3d8d15c08805f85d4451e0a5f2d20977632c0b4b22540, lines1111-1360. This is a historical runtime audit, not a correctness or current-champion result.

The prepared numerical theorem must instantiate `R24PortableF64.prepare raw`. A user-constructed `Prepared` with `valid=true` could contain unrelated cached Float values, so `valid` alone is never a sufficient invariant for arbitrary Prepared records. The original R26 linear/gemm/conv/depthwise construction does use `R26WordFallback.prepare`, whose fp field is definitionally the actual prepare. Array lookup proofs must retain this constructor origin and show index validity; the local Inhabited empty record is a fallback value, not a semantic prepared cache.

For an accepted attempt, derive all shape and validity conditions from actual `attemptPrepared != 0` via AttemptGuards, then rewrite prepare.raw=raw. Do not assume the guessed word was a correctly rounded native conversion: `proposal` is deliberately midpoint-up, and strict checker acceptance must prove the result independently of proposal accuracy.

The final scalar composition has two branches. Accepted FP returns the official dotSpec by the completed producer/checker/rounder chain. Miss returns a separately proved fallback on the same original arrays. The R26 `exact` fallback has unproved 64/128-bit paths and cannot inherit retainedCorrect. A known-correct current-base dot or ExactRuntime.dotSpec can be instantiated if the word proof is unfinished; performance must then be measured for that exact alternative.

Full12 still needs actual cached tensor getters, bias as one extra exact product, zero output sizes, and equality of new kernels to specKernels. The existing retainedCorrect root is about retainedKernels only. Helper compilation, a conditional strict-cell root, or finite checksum agreement cannot discharge this record equality.

The FP module can be attached to a stronger public predecessor only after source budget review: #27 is255647B and #12 is218232B before an owned patch. Appending the current full FP proof closure exceeds the former cap. Dependency removal or source compression must preserve exact replay and axiom checking on the final256000B-limited Kernel.

Additional exact negative control (`follow-on/PROPOSAL-ZERO-NEGATIVE-CONTROL.json`): the bit proposal maps native +0 to raw32 0x40000000 (+2), and -0 to0xc0000000 (-2). This intentionally arbitrary proposal is rejected by the actual strict cell with radius2^-303. A future caller proof must never assume it is an RN32 conversion, even on finite or zero inputs; the accepted checker consumer correctly avoids that assumption.
