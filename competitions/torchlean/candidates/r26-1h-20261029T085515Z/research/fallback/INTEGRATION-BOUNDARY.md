# Block fallback integration boundary — 2026-10-29 09:34 UTC

Source evidence: D's `development/native/fp-word-conv6-local/Kernel.lean`
ad9bde3e… has `R24ExactDotCost.nativeLoop` (four scalar UInt64 accumulators,
per-product mantissa/index extraction and variable shift), then
`R26WordFallback.dotPrepared` chooses the floating certificate or this exact
fallback. This role's `body128Each` is an **aligned-factor control**, not that
same baseline. Its block-vs-each cost probe isolates block grouping only and
cannot establish a speedup versus D's complete candidate.

The new mechanism moves alignment into cached Array UInt32 factors. It removes
per-MAC exponent extraction/shift and accumulates16 products in one UInt64,
then sign-extends once. The source carries lo/hi as scalar recursive arguments;
no generated C or allocation evidence yet establishes the physical hot loop.
All UInt32 array slots remain pointer-sized on64-bit Lean; no4-byte-per-entry
claim is made. n608 factor weights need48640 slots before array metadata.

Bias must remain separate when preparing these factors. D's current `linear`
and shared convolution cache `k+1` terms, inserting oneW and bias into the same
operand range. Those ranges are not interchangeable with the new body-only
range. Integrating this route means preparing body factors separately and
adding `sv bias * 2^(idxBias+149-baseA-baseB)` once before rounding. The actual
`finish_prepared_bias_dot` draft relates this body+terminal form to original
`dotOf (n+1)`; it is NOT_COMPILED.

Guard premises needed once per prepared vector/pair: finite raw inputs, each
nonzero index≥its base, aligned magnitude<2^31, n≤2^20, finite bias, and
baseA+baseB≤idxBias+149. The actual canBlock16 guard is proved in the draft
against maxima; false takes per-item128, not a signed64 whole-sum assumption.
The original encoded getters, base and successful metadata scan still need one
verified connection. Failed outer guards go to existing shipped function.

Parent09:41 review processed09:46: actual signed32 magnitudes ma,mb are each
≤2^31, so the UInt64 guard product≤2^62 cannot wrap before comparison. However,
the literal `preparedBody` rescans maxMagnitude for both getters on every dot.
The diagnostic `CostDriver.output` instead uses each Prepared.maximum cached
at prepare time and calls body128/body128Each directly. Its prepared boundary
therefore is a **cached-metadata prospective caller**, not a timing of literal
preparedBody. Full mode includes its own scans and factor preparation. This
distinction must survive any future comparison or promotion.

Signed zero can avoid a per-MAC flag: `zeroSafeFinish` computes body+bias and
calls shipped on exact0; nonzero calls original finishWord with flagfalse.
`guard-counterexamples.json` retains -0 and positive cancellation cases plus
the new negative-bias-shift failure: (1*1)+(-1*1)+minSubnormal should word1;
saturating shift-103 to0 produces679477248. Guarding only the body is unsound.

Priorities after D's main CI: compile the3287B runtime or inspect emittedC;
compile the18821B modular carrier only once full stdout is retained; run the
8999B fixed cost driver if capacity remains. The41194B assembled proof chain is
follow-on material. Current all12/fullmodel/official acceptance remain UNKNOWN.
