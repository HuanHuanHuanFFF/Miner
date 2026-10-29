# R24 broad route: read-only TorchLean migration assessment

Snapshot read at UTC2026-10-28 20:50–20:54. Scope selection remains with the user/root; this is no new-track implementation or CI request. Original seven-hour cutoff is unchanged. Source: official commit `accb82b6e2adeda1b41a57a260d68fb3879c427e`, nine independently fetched files under `torchlean-source/` with Git blob/SHA-256 checks in its receipt; root additionally has the production API, boards and former-champion2 source snapshots. Token/cache usage UNKNOWN.

**The frozen broad native-pair kernel cannot be ported as the new exact dot.** It keeps two Float32 multiply/add chains and rounds every step. The new `ContractExact.dotOf` requires the exact sum of exact products, rounded once, and linear/conv include the bias before that rounding. `rounding-boundary-falsifier.json` gives two executable finite rational counterexamples: `[1,2^-24,-1]·[1,1,1]` gives old0 versus exact2^-24; `[(1+2^-23),-1]·[(1-2^-23),1]` gives old0 versus exact−2^-46. Both exact results are representable binary32. This only discriminates the semantics; it is no new Lean proof.

## What transfers and what does not

| Old evidence/artifact | New use | Boundary |
|---|---|---|
| B2 operation/shape/category costs | Historical FloatLib evidence only | New scoring is model-family workloads, weighted geometric ratios, multiple CPU environments; old ADD/MUL/BMM percentages cannot rank new routes. |
| Full-lifecycle source/flag/callback checks | Reusable verification method | BenchExact/MainExact and twelve-field obligation need a new bound harness. Existing BenchSuite callback driver cannot become the new gate by changing names. |
| Pair/group writer and address proofs | Possible layout lemmas | Raw malformed arrays and outside-domain behavior remain universally specified. Exact accumulator state, special fallback and signed-zero flags must be transported independently. |
| Native F32 codec and cold fallback | Potential residual `addRelu` side route | Core/dense/conv exact dot and fused `scaleShift` do not use per-step F32 semantics; stable norms do exact rational statistics. No broad core reuse claim. |
| FloatArray native caches | No immediate exact-dot value | Exact dot needs significand/exponent/sign words, not F32 multiply/add. A decoded-word producer would need a different cost premise and cannot inherit these arrays' performance. |
| x86 C/ASM findings | Compiler hypothesis | Root's new board snapshot requires AMD and ARM; removed x86 spill alone does not establish a cross-environment win. |

## Actual starting work and public prior art

The shipped38506B kernel uses eighteen positive and eighteen negative Nat limbs; every finite product splits into two limb updates. `dotLoop` already threads accumulator fields as plain arguments, so a generic statement that “one Acc record allocation per MAC can be deleted” is unsupported by the source. Finalization scans nonzero range, normalizes/subtracts digits and uses a top-two-digit plus sticky-bit rounding proof. Special inputs fall back to FloatLib's exact dot. Scalar inputs are raw UInt32, with bit-field decode rather than the old numeric F32 codec.

Its dot is reused by linear/gemm/conv/depthwise/average pooling. Stable normalization chooses `rmsnormStable`/`layernormStable` on its valid finite domain and bypasses the dot parameter; changing dot alone therefore does not automatically accelerate normalized-model rational statistics. Maxpool's shipped finite comparator builds shifted integer keys. These are source facts, not measured time shares.

Root's public former-champion2 source (SHA `cea442…`,254884B; read-only, licenseUNKNOWN) already goes substantially beyond that starter. Its final kernels record selects separate dense, convolution, element and norm implementations. Static inspection shows guarded64/128/192-bit arithmetic, exponent summaries for activations/weights, prepared signed activation tables, optional sparse indexes, padded convolution input and precomputed offsets, and dedicated rational normalization/rounding code. Current champion5's implementation is UNKNOWN; former2's code is not a candidate dependency and no body was copied here. A proposal to merely add a multiword accumulator, predecode inputs, cache sparse indexes or precompute convolution offsets would repeat known work unless a concrete new mechanism and reachable coverage are identified.

## Minimum next discriminators if migration is authorized

1. Acquire or run one unchanged new-target reference through the complete proof/build/audit path and one original model profile. Check current public-source availability and licensing separately. Actual layer/prepare/finalize/limb-update times are UNKNOWN now; count estimates must not masquerade as them.
2. Bind the actual selected model→kernel→dot caller in C/ASM for both required CPU environments. The starter's `@[specialize]` and simple source expressions are not evidence that all higher-order callbacks, divisions, allocations or range checks disappeared.
3. Compare any proposed work deletion against public former2's already guarded integer/summary/offset mechanisms, and against current5 only where exact public evidence exists. Retain malformed inputs, NaN/Inf, empty/negative-zero/cancellation and bias-before-round cases.
4. Only after one broad measured cost opportunity exists, build the smallest full kernel or model callback with complete cache/preparation/failure/finish/release costs. Fixed-input diagnostic first, then the actual new gate and board-specific independent confirmation. Rewriting or measuring the frozen old native-pair kernel has no new-target value.

No new-target performance, correctness acceptance, ranking, reward or net-profit claim was established. FloatLib cost package remains frozenNOT_RUN because its submission target closed; the route was not algorithmically rejected.
