# R24 representation: frozen FloatLib and read-only TorchLean decision

Owner R24 A, first observed tool UTC 2026-10-28 20:43:06; shared cutoff 2026-10-29 03:38:56. After the parent reported the official target change, no further FloatLib implementation/proof/CI request and no TorchLean implementation or compilation is authorized here. This note is a source-level assessment, not a migration decision. Tokens/cache/model-compute time UNKNOWN; no observed capacity gap; no local Lean or native build.

Current decision supplements: [actual former-champion paths and residual candidates](FORMER-CHAMPION-RESIDUAL.md); [new score weights and wide-route guards](SCORE-AND-WIDE-GUARDS.md). Their later source checks supersede the initial shipped-baseline opportunity selection below.

Resumed read-only subtask at 21:49:46 UTC: [clean baseline and proof-interface map](CLEAN-BASELINE-INTERFACE.md), requested checkpoint 22:15. It resolves the public import/record/rounder prerequisite without copying former #2 or writing a new-track implementation.

Narrow authority update at22:12: parent separately authorized a **portable old ContractTensor/B2 normal-or-zero widening helper**, with all four public B2 endpoints unchanged. Current component handoff is [../widen1-HANDOFF.md](../widen1-HANDOFF.md), source75a1/238814B, NOT_RUN. This does not authorize a TorchLean implementation or benchmark; the earlier FloatLib performance candidates remain frozen.

## Frozen work, not a correctness or performance result

- `f01-r24-research-representation-warmsum1/Kernel.lean`: SHA-256 `1590792fbe13ff25ee6dc9f4e27db0909658ae6f2744f722a4db395d3dd3f8ca`, 229532 bytes. An actual public SUM replacement draft, single normal prefix followed by a one-way transfer to the original loop before the first cold input. No scan/record, no cold-to-hot edge, and unchanged operation order. Three helper proofs NOT_RUN. Existing normal decoding already inline; only changed frame/spill behavior was hypothesized, and old exact SUM machine spill is UNKNOWN.
- `f01-r24-research-representation-densescale1/Kernel.lean`: SHA-256 `28542912254e009ab7c3e047e2fc3b7145a9205eb4b862401abea5fe28230fbf`, 228600 bytes. Only the common scale reader changes: a constant checked FloatArray table, a retained original-table fallback, and narrowing before original Float32 arithmetic. Four helper proofs NOT_RUN. The intended deletion is a boxed table pointer chase; added global validity branch and narrowing are charged. No benefit is claimed.
- `../frontier.json` rechecks the old raw discovery rows against their archive: SUM 6.85–7.76% of whole time; conservative all-warm-header SUM cases 4.83–5.50%; BMM 15.59–20.81%; ADD+MUL 72.34–76.84%. These are historical whole-case exposure ceilings, not saved time or current TorchLean evidence. SUM was downgraded to a cheap mechanism probe before the target-change message.

## Semantic break: old reductions cannot be carried over

The official source at commit `accb82b6e2adeda1b41a57a260d68fb3879c427e` defines exact sums of exact products, rounded once. This is different from old FloatLib's original-order binary32 multiplication and addition.

Three exact counterexamples, derivable without simulation:

1. Sum `[2^24, 1, -2^24]`: old left fold starting at +0 returns +0, because the first addition of 1 is a ties-to-even round back to 2^24. Exact total is 1, so new sum returns 1.
2. Dot `[(1+2^-23), 1] · [(1-2^-23), -1]`: old rounded products give `1 + (-1) = +0`; the exact result is `-2^-46`, representable as raw `0xa8800000`. Input raw words are `[0x3f800001,0x3f800000]` and `[0x3f7ffffe,0xbf800000]`.
3. A nonempty dot of `[-0]` with `[1]` returns -0 under the new all-negative-zero rule. The old +0-prefixed fold returns +0. Empty new dot is +0, and exact cancellation of nonzero terms is +0. An exact rational total alone therefore does not determine all required zero bits.

Linear and convolution include bias before final rounding. `scaleShift` is fused multiply-add, so old MUL followed by ADD is not interchangeable. Average pooling first rounds its exact sum, then performs the specified division; it is not a single rounding of an exact average. Max pooling remains an ordered IEEE maximum with special-value/zero semantics. NaN/Inf input processing must retain the raw specification; finite-term associativity does not license reordering NaN payload selection.

## Reuse boundaries

Reusable ideas: raw sign/exponent/fraction extraction; bounded word arithmetic lemmas; array addressing and output-prefix methods; exact integer accumulation invariants; source/hash/gate discipline. Their concrete statements must be rebound to the new imported contract and allowed axioms.

Not directly reusable: the old B2 `sum_spec`/`bmm_spec`, native repeated Float32 chains, old speed ratios, old four-function package, old case weights, old 25-round protocol, or old reward allocation. New submission is a `Kernels` record with twelve fields/five proof families and universal `Obligation K := K = specKernels`; raw malformed inputs remain in scope even if checked model execution rejects them. Model boards measure complete inference, not standalone kernel totals.

Critical scope detail: `ContractExact.lean` lines 217–227 sends the stable normalization domain directly to `rmsnormStable`/`layernormStable`. The supplied `dot` argument is used only by the fallback branch there. A faster shared `dotFn` reaches linear/GEMM/convolution/depthwise/average pooling, but cannot be credited with accelerating the stable normalization statistics.

## Two substantial representation routes, still only hypotheses

**20:56 UTC correction after reading coordination:** the parent reports that former champion #2 / `cea442` already has the integer-moment route, `n*S2-S1²`, integer sqrt and quotient finalization connected to its real normalization entry. Route A below records the opportunity relative to the shipped implementation only. It is NOT a new optimization against that available stronger source and is no longer selected as this worker's main route. The exact former source/receipt is being independently inspected before further selection. No historical text or frozen source is erased.

**A. Exact statistics as two integer moments.** Stable normalization currently repeatedly builds rationals for each decoded value, centered value, square and accumulated total. Let `u_i = k_i * 2^-149`, with signed integer `k_i = ±mantOf(u_i) * 2^idxOf(u_i)`, `M = Σ k_i`, `Q = Σ k_i²`, and `n > 0`. Then

```
mean     = M / (n * 2^149)
RMS var  = Q / (n * 2^298)
layer var= (n*Q - M²) / (n² * 2^298)
```

This moves per-element rational normalization/GCD work into exact integer accumulation, with rational formation once per row. It does not use floating-point reassociation: the contract's statistics are already exact rationals. A first implementation would retain the original sqrt and final-output expressions to isolate the statistics change. `TensorProofs.variance_second_moment` supplies the relevant algebraic statement, but TensorProofs is not directly imported by ContractExact; availability in a legal single-import submission must be checked before relying on that name. `Values.decodeD_toRat` supplies the exact word-to-dyadic bridge. All stable-domain checks and the legacy fallback must remain.

First falsifier after authorization: obtain actual model layer costs, then compare complete stable normalization including finite-domain scan, integer moments, conversion to rationals, original square root, and final expressions. Reject a large-optimization claim if repeated statistics are not material or if integer/big-number work costs at least as much. Normalized-model time share, achievable speed and compiler behavior are UNKNOWN.

**B. Exact-dot accumulator and finalizer costs.** The shipped source has eighteen positive and eighteen negative `Array Nat` limbs, two indexed modifications per nonzero finite product, and a final limb comparison/subtraction/rounding path. One improved `dotFn = dotOf` proof can be transported through several layers. Unlike old sequential Float32 arithmetic, finite exact products may be grouped before the one final rounding, provided exact total and special/negative-zero state are retained.

A bounded UInt64 dirty-limb idea requires care. Each actual mantissa product is `<2^48`; its split low contribution is `<2^32`, high contribution `<2^47`, and each product contributes to at most one of those at any fixed limb. Thus each nonnegative limb remains `<2^64` for at most `2^17` terms. Arbitrarily long input requires chunk normalization or original fallback. But `Array UInt64` can box each full-width element, whereas small `Nat` is immediate: changing the type is not an allocation improvement by itself. Conversely, thirty-six scalar accumulator arguments can spill heavily. The first useful evidence is real codegen/layer cost, not an expensive proof of an unmeasured representation. A narrower exponent window or reused decoded panels could amortize the representation, but their guards/prepasses/preparation and all finalization must be charged.

The shipped source already uses UInt64 shifts for splitting (`addLimbs64`) and a digit/sticky final rounder (`finishFast`). Replacing an imagined arbitrary-precision shift or full-big-integer finalizer would duplicate work already removed. The source comment claiming no per-term allocation is not machine-code evidence.

## Primary evidence and limitations

Read-only saved official copies are under this round's `development-broad/torchlean-source/`. I independently fetched ContractExact and TensorProofs at the exact commit through the GitHub connector and matched the local Git blob hashes:

| Source | SHA-256 of local bytes | Git blob |
|---|---|---|
| ContractExact.lean | `bddd6bd9caa19f9419e0e38cd553b109a7675fc710fdf82a6d6f7d0f2a4c8b1b` | `fba2ff6e77cf75922c6819f9193491cb8224459d` |
| ExactToolkit/TensorProofs.lean | `6f5cb15103542b5043ea529947cf8a7c51157d6de975854dddec37f2234fc447` | `d29c7c254268adefa2842070199755482c40b929` |
| incumbent Kernel.lean | `9b2d940338dfcc42a38443324d63041a27cc9b5df1b18675103c7d67934d1df8` | local calculation `0ef0e7c8a1802bd6129b230e7be49f9e4d92d725` |
| ExactToolkit/Values.lean | `34e5482fa27a4a2cd33e86ffdbcac02916e59306f12a441cb659273dc633da0f` | local calculation `9662350c91092ee5b18ed93fb10e71858d3f7dd2` |
| ExactToolkit/Limbs.lean | `50c78dd60755137d7fdf48615e72ac25561c7b7a578264bcdf22b166c67da008` | local calculation `02587cedb27bc0e08a4842cdf7221fa016854f85` |

`ExactToolkit/StableNorm.lean` was independently fetched at that commit: Git blob `dbab06ffdd3c372de2b33e5b53a8af07f818dd06`. It defines the repeated rational operations and `sqrtShift = denominator.log2 + 150`. The latter suggests a later square-root scaling investigation, not an adopted new algorithm.

Canonical sources: [contract](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/accb82b6e2adeda1b41a57a260d68fb3879c427e/lean/contract/ContractExact.lean), [stable normalization](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/accb82b6e2adeda1b41a57a260d68fb3879c427e/lean/contract/ExactToolkit/StableNorm.lean), [tensor proofs](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/accb82b6e2adeda1b41a57a260d68fb3879c427e/lean/contract/ExactToolkit/TensorProofs.lean).

Root `LICENSE` lookup returned 404; repository-specific copying/license terms remain UNKNOWN in this audit. No new target implementation or copied proof has been written. The official API state is sourced from D's round `competition-state-check/receipts.json` at 20:47:37–39 UTC; this worker has not made a formal submission, wallet call, or registration action.

## Imported proof APIs and the source-size prerequisite

The new official API and `docs/PROOFS.md` still cap the single file at 256000 bytes. Former #2 is 254884 bytes, leaving only 1116 bytes. Appending a substantial new algorithm and proof is therefore not an implementable plan by itself. Any future authorized adoption must first budget replacement/removal or an independent source basis; this note does not alter or copy that source.

An independently inspected import chain may reduce proof duplication: `ContractExact → Values → Decode → Congr → ExactToolkit.Round`, whose first line imports `FloatLib`; that root publicly imports `Floats`, then `Kernels`, then `FixedWord`. The fixed sources expose `FloatLib.Numerics.FixedWord.UInt128.toNat_lt`, `toNat_ofNat`, `toNat_injective`, word and multiword shift/rounding proofs, and other fixed-word modules through the permitted single import. This is source-level accessibility evidence; no new Lean `#check` or build was run.

Relevant fixed Git blobs: ExactToolkit.Round `b135b1c53167600a53638e9f474e3ef4e7390ab6`; FloatLib root `a33c3245f268792a9e9924226e6889b144f64d0f`; Floats `ce2a7d1e9830bff0ab40eefad51faa0546b0d42a`; Kernels `a210ce58c81cd8b41eac27de55a0890b305a174f`; FixedWord `8abbfb25308fcb3521cf9aa2d398963ab925af43`; Core/Proof/UInt128 `d9935670e5d70c31578b908af0134320ad87d8b2`; LimbRound/Proof/UInt128 `624b3895a3bf39da82b04e7d67d04fe1b1b1692d`. Official contract files use the recorded accb82 revision; FloatLib files use 0d918.

Access does not mean a matching interface. B inspected `CertifiedDivision.certificate_sound` and found precision 65..126/256-bit-product assumptions, unsuitable as a direct 24-bit RMS checker. Its general quotient-rounding theorem may support a mathematical bridge, but does not establish cheap UInt64 runtime behavior. Likewise, a library UInt128 record is not proof that a hot loop keeps two scalar words without allocation; actual ordinary codegen remains required.
