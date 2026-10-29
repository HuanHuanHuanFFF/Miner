# Source-grounded cost decision, 07:10 UTC

Official source is pinned to `accb82b6e2adeda1b41a57a260d68fb3879c427e`; full model runtime and current champion comparison remain UNKNOWN. Toolchain file says `leanprover/lean4:v4.34.0`. No local Lean/native compilation was run.

| Route | Original repeated work | Actual candidate change | First discriminator |
|---|---|---|---|
| Decode cache | `dotStep` extracts mantissa, index, sign, exponent from both words per product | Cache exact components per tensor; preserve `Acc.add`, `finishFast`, flags and original special fallback | Complete candidate compilation, then model profiles including cache preparation |
| Adaptive linear | Input row reused `outW` times; each weight reused `rows` times; for `rows=1` no weight reuse | Cache only X when `rows≤1`; both X/W otherwise | MLP normal/wide/sparse, both batch sizes |
| Convolution patch cache | Each spatial window's channel/filter division, modulo, padding checks repeat for each of `cout` output channels | Build each spatial decoded window once; share decoded input objects and window references over output channels | CNN/MobileNet profiles; charge patch allocation and output lifetime |
| Exact normalization cache | Layernorm converts x to Rat in mean, variance, output; RMS in variance/output. Row denominator Word is converted to Rat `n` times | Cache exact Rat x/g/b and once-per-row denominator conversion; preserve all rational algebra, `sqrtRational`, `roundRational`, stable-domain branch and legacy fallback | normalized MLP/Mixer profiles, complete round-once checksums |
| Exact integer row moments, added 07:19 | Original stable mean/variance reduce rational fractions per element even though all binary32 values share the `2^-149` lattice | Sum signed `keyOf` integers and their squares, convert only row totals to Rat; use the exact centered-variance identity at the actual mean | Separate full proof and normalized-model timing; exact integer allocation/shift cost is UNKNOWN |

The first source path `dotFn` already reads through fa/fb without operand arrays on its finite path. Removing a hypothetical per-dot input-array allocation is therefore not an opportunity in this baseline.

The kernel source gives reuse factors, not runtime shares. Decoded structs and patch references add allocation and memory traffic. One-row weight cache was removed in the adaptive variant because it has no reuse. The cache routes can lose; no synthetic R24 integer ratio transfers to this package.

Arithmetic opportunity reserved for actual C/assembly review: `addLimbs64` computes `m % (1 << s)` with dynamic s. A proved mask replacement is useful only if the compiler has not already emitted a bit mask. No division-cost claim is made without that evidence.

Proof acceptance closes the producer-to-contract equality, not model performance or promotion. Every candidate retains the complete `Submission.correct`; ordinary `rfl`/rewrites prove the cache-to-original producer relation. New proofs, kernel replay and native timing are all NOT_RUN as of this note.

The 07:19 integer-moment source is a distinct mechanism and remains outside the first frozen CI group. The first group is unchanged. It proves `rationalWord w = keyOf(w) * 2^-149`, transports actual integer folds into the original rational folds, and proves the centered-variance identity for `n≠0`; `n=0` retains the original function. It uses arbitrary-precision exact Int arithmetic, not native floating point or an assumed correct fallback.

07:24 prior-source check: public former-champion2 already contains common-binade limb row statistics and accelerated normalization output/square-root functions (read-only hotspot scan around lines2490–2823). This limits the independent integer-moment route's expectation versus a strong former champion; it does not measure current champion performance. No body from that source is copied and its license remains UNKNOWN. The first experimental reference remains the shipped baseline, explicitly named.

07:46 actual resource evidence from run40834710293: original setup took470.30s and the driver phase630.23s; original baseline gate verdict43.742s (outer command54.29s), Widen7 verdict55.314s (outer64.16s). Frozen cache sources were policy-rejected before Lean, so these are environment/gate costs rather than cache proof estimates or performance. The workflow only saves the new TorchLean dependency cache on whole-job success; this failed group does not establish a saved new cache. A later runner may repeat setup unless another matching cache exists. Its model measurement/build cost is still UNKNOWN.
