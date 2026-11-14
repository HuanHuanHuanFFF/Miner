# Former #2: actual paths and remaining representation hypotheses

Read-only decision note, UTC 2026-10-28 21:06. Exact source is the shared `source-snapshot/former-champion-2.Kernel.lean`, 254884 bytes, independently rehashed SHA-256 `cea4422fb6d3bd613b306127e7017331560875ddb840a7f2e174f6c03bdb480f`. D's receipt binds public source URL and retrieval at 20:51:22 UTC. This is FORMER champion #2, not the unavailable current champion or a new candidate. Source is not copied into this worker's output or a submission. Licensing/adaptation permission remains separately unresolved. No compilation, timing, or new-target implementation has occurred.

## Actual entry map prevents duplicate proposals

The final `kernels` record is at lines 3736 onward. Reading the earlier baseline alone substantially overstates the remaining cost.

| Actual field | Main route and source lines | Retained other route |
|---|---|---|
| core sum/dot | `kernels0.core` → `Yn`/`Yw`, 258/252: 18 positive and 18 negative Nat limbs | source specification for special or unequal inputs |
| linear | `YaV` 1373 → `QPa` 1352 → `QY6G` 1321: two UInt64 words; sign-dependent prepacked input, sparse index path | `YaU` 1267 → `YS6`/`YS` 1239/1154: three UInt64 words; then `Yai` → `Yn` |
| GEMM | `Ya3` 2215 → `Ya2` 2177 → `YE` 1779: three UInt64 words | `Yan` → `Yn` |
| conv/depthwise | `Ybp`/`dwQ` 3413/3415 → `cdQ` 3349 → `Ybj` 3237 → `Y5` 2930: split at 25 bits, two independent signed UInt64 dirty components, final merge | `Ya0`/`dwF` → `YaC`/`YE`; then exact Nat-limb fallback |
| average pooling | `Ybk` 3447 can reuse the split convolution path | single-window/global pooling falls back to `YaZ`/`Yn`, followed by the exact specified division |
| stable normalization | `Ybb`/`Ybc` 2802/2807 already use integer moments, integer square root and integer quotient finalization | legacy contract behavior outside stable domain |

Consequences: Nat Array.modify is not established as the hot normal dense/convolution path. Integer moments are already implemented in #2. The convolution loop already defers cross-word carry, so “remove carry per term” is not a new convolution mechanism. Source comments are not machine-code measurements.

## Two-term carry batching for the real linear path

`QY6G` updates the two-word sum for each signed 64-bit product. Its high word receives sign extension plus the low-word overflow carry. The actual product proof near `A9` has the strict bound `-2^62 < q < 2^62`: 24-bit significands and total aligned exponent span at most 14.

Therefore two adjacent signed terms have a sum strictly inside `(-2^63, 2^63)`. Their UInt64 addition can be interpreted exactly as signed64; one two-word accumulator update then equals two original updates. This removes one high-word sign/carry update per pair and reduces the loop-carried dependency frequency. An odd last term is processed once, bias is added once after the term loop, and the existing zero sentinel/fallback/final rounder remain.

The existing `A8` interface only states non-strict `±2^62` bounds. That interface is NOT sufficient: two terms equal to positive `2^62` sum to `2^63`, whose signed64 interpretation is negative. The discrepancy is exactly `2^64`. A correct proof must preserve the stronger actual-product bound, not reuse `A8` unchanged and silently assume the endpoints unreachable.

Useful local proof target: with `sgn(q)` the signed64 interpretation and `U(acc,q)` the original two-word update, prove `U(U(acc,q0),q1) = U(acc,q0+q1)` under the strict signed64 sum bound. Prove equality modulo `2^128`, then pair-word injectivity; no assumption about the initial two-word accumulator is needed for this local bit-pattern equality. The wrapper proof then groups the original sequence into pairs and retains the odd suffix. This is a mathematical interface, NOT a Lean-checked theorem.

First falsifier after authorization: inspect real specialized machine bodies and complete model cost. Reject if the old compiler already removes the relevant dependency, new indexing/closures/boxing outweigh it, or the packed path is a small fraction of actual model time. No whole-model gain is inferred from instruction counts. New opportunity fraction and speed are UNKNOWN.

At 21:26 UTC this worker read only the relevant strict-bound/finalizer passages of the parent's independent Pro report (`research/pro-results/20261028T212553Z/torchlean_readonly_adversarial_review.md`, 41235 bytes, SHA-256 `30a03fd603926e42e4ec363083a041cdddd27ae9caddeb4a2be652fdb0df8848`, rehashed here). It confirms the strict pair premise and that the actual count bound keeps arbitrary disjoint-chain subsets below 2^82 in magnitude. It also makes the cheapest integration boundary explicit: prove the unrounded raw128 state identical, then execute the original shared bias/finalizer once. P/I length guards alone are not the semantic bridge; `YaV`'s actual prepack/sparse-index construction must supply the product relation. This is one independent paper review, not measured speed or compiled proof. Neither semantic operation counts nor multiple reviewers establish CPU cycles.

## Rejected larger-looking extension: long convolution fan-in

`Ybg` 3155 and `cdQ` 3349 restrict the split path to `k < 256`; the actual theorem `S3` already supports `K ≤ 256`. Each dirty component is strictly less than `2^55` in magnitude per term. Up to 256 terms fit signed64; a blockwise exact merge could in principle extend this fast representation to longer dots.

The first source-domain check rejects it as a main route for the currently published generator. In both legacy and `profileModel`, CNN input channels are 3 and later 3×3 layers use `c1`; `c1` is 4–8 typical/legacy, 4–6 scale, and 5 or 7 boundary. Thus CNN fan-in is at most 72. MobileNet depthwise fan-in is 9; pointwise fan-in is at most 16. The `k ≥ 256` extension cannot activate on those generated convolution shapes. This is a static statement about these source builders, not a claim about all future/hidden inputs. The proposal is parked before code or expensive proof. Merely changing `<256` to `≤256` is also not a large route.

## Broader, independent exactness certificate for wide finite dots

Potential target: finite wide-exponent cases that currently miss prepacked exact routes and use three-word shifting/carry per product. Use one signed64 truncated accumulator and a rigorous interval; return only when the entire interval rounds to one identical binary32 word with nonzero magnitude bits (`w & 0x7fffffff != 0`), otherwise run the original exact path. A mere raw `w != 0` would also admit negative zero and is insufficient for the selected injectivity theorem. This is exact conditional execution, not tolerance acceptance.

For actual finite terms `s_i * m_i * 2^I_i`, with `m_i < 2^48`, choose a bound `H ≥ I_i`, `L` with `n ≤ 2^L`, and integer `B = H + 48 + L - 62`. Truncate each signed term toward zero in units of `2^B`, producing integer `q_i`. Then `|q_i| < 2^(62-L)` and `|Σq_i| < 2^62` (for positive n), while the true scaled total lies in `[T-n,T+n] * 2^B`, `T=Σq_i`. The FloatLib value has the additional common factor `2^-298`.

The machine kernel would keep the 48-bit product and shift in UInt64, with an explicit large-right-shift case because UInt64 shifts reduce their count modulo 64. Sign is applied after truncation. Count/exponent guards must establish every stated bound; bias is one of the exact terms, not added after certification. Two exact integer endpoint roundings plus a raw-word comparison form the certificate. Only matching nonzero results return, avoiding unsupported signed-zero conclusions; specials, empty input, cancellation/underflow-to-zero uncertainty and ambiguous rounding use the original full semantics. Existing exact prepacked fast paths should stay ahead of this more expensive fallback candidate.

At 21:17 UTC, independent reviewer C's first pass found no counterexample to the guarded paper interval and supplied the finite-endpoint and nonzero-word proof interfaces. Its bounded exact checks are only finite diagnostics; the accepted-check count is not a future hit-rate estimate. C clarified the magnitude-bit guard above. See `research/rounding-review/notes/REVIEW.md`; its actual library identities and any Lean composition remain separately checked. This worker did not rerun or enlarge those examples.

Needed proof interfaces: exact per-term dyadic truncation interval; finite fold interval and no machine overflow; convexity of a single nonzero RNE output cell, including tie endpoints/overflow; transport to actual `dotOf` with original NaN and negative-zero behavior on fallback. The current inspected source's `Y0` is an exact integer-exponent representation condition, not this discarded-tail interval certificate. B's independent normalization work may share a rounding-cell lemma, but targets a different final operation.

First falsifier after authorization: whole caller cost including exponent metadata, product truncation, two final roundings, failures and exact replay, plus actual frequency of misses from the old exact paths. Wide input labels alone are not a measured exposure fraction. No candidate, finite empirical pass ratio, or speed result exists for this route.

## Lower-risk exact 128-bit comparison route

The general `YE`/`YS` path reserves three words for a worst-case shifted product window up to 122 bits plus the 48-bit significand product and the term-count growth. Many actual ranges fit two words. With a shared finite window `lo ≤ I_i ≤ hi`, `span=hi-lo`, positive count `n ≤ 2^L`, and `span+L ≤ 78`, every prefix has absolute exact scaled sum less than `2^(48+span+L) ≤ 2^126`. The two-word signed result is therefore sufficient; bias must be included in this count/window or added with a separately proved bound.

A two-word worker can use the same exact product, variable shift, sign-complement convention and deferred negative-count correction as the existing three-word source. It removes the third word's per-term update/high-overflow work while retaining exact accumulation and deterministic success on its guard. No discarded-tail or rounding-cell theorem is needed for this comparison. It is different from #2's packed linear 128-bit path, which requires the much narrower prepacked range. A complete modulo-2^128 invariant and sign-extension bridge remain uncompiled.

**22:57 UTC source-fact correction from Pro-A second review.** The stored two-word ones-complement state is `S-c (mod 2^128)`, not S. The selected integration now explicitly sign-extends **S-c** to 192 bits and keeps c unchanged; the original bias→YD terminal adds the correction once. Since c≤K<2^20 and |S|<2^126, also |S-c|<2^127, so that extension has the intended integer meaning. An alternative may add c first only if it resets the terminal's incoming c to zero and proves that transport. Adding c first and then passing the original c would double-correct. The earlier wording was ambiguous about that required reset and must not be used as an implementation instruction.

The base must be the original actual `Yp` value ℓ, which may include a tiny nonzero bias. Do not replace `H_products-ℓ` with a products-only max-minus-min. For product 1 and bias 2^-149, product index252 and padded bias index126 give original ℓ=126; the conservative 128-bit guard correctly rejects. Taking ℓ=252 would make the unchanged bias shift negative. Original finite, count, addressing and bias guards remain. The wider product-plus-bias bound still belongs to the original terminal, with bias added once and sentinel examined only afterwards. At shift zero, `m >> 64` would be wrong under UInt64 shift semantics; the existing split expression using `(m >> 1) >> (63-shift)` avoids that trap. The initial width condition is conservative, not a maximal-domain claim. Pro source: `research/pro-results/20261028T224335954875Z/torchlean_wide_dot_two_page_review.md`, SHA-256 `3e4207ba5676d7bedc1f68fb56135afec23a39e829a2ce880428a91b28ab63c9`; only these two new source facts were rechecked.

This route is a possible cheap exact control for the larger single-word certificate idea. Dynamic coverage, old/new machine instructions and model score are UNKNOWN; it does not justify replacing the better existing packed routes or launching work before target authorization.

## Representation caution confirmed from pinned runtime source

On the pinned 64-bit Lean runtime, UInt32 boxes into an immediate (`lean_box(v)`), just as a small Nat; UInt64 and USize boxing allocate constructors. Thus replacing `Array UInt32` with `Array Nat` is not a threefold payload win, and replacing immediate Nat limbs with `Array UInt64` may add allocations. The existing exact runtime uses the same Lean v4.34.0 toolchain. A scalar-argument UInt64 calculation and an Array UInt64 storage representation have different costs and must not be conflated.
