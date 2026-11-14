# R24 scalar first decision — scope suspended for competition change

Actual first tool: **2026-10-28 20:43:26 UTC**. Shared cutoff remains **2026-10-29 03:38:56 UTC**; no extension. D owns Git/CI/adoption. Token, cache and accumulated active execution are UNKNOWN. These notes are read-only research; new-track implementation/CI is not authorized at this checkpoint.

## FloatLib work preserved before the scope notice

- B2/622d already uses six-stage `fastLog2`; replacing generic UInt64.log2 would not remove that work. R16/R18 unsigned aligned-integer ADD is an actual negative: R18 public source uses `UInt32 → Float32 → UInt32`, d≤7, same/opposite adjustment, n≥2^23 and late exponent rejection. R22 sameExp/broadword/far bodies remain parked. Low-scale bias RNE/direct packing was already R6 active-bias, with a failed proof receipt and no matched timing; it is not a new algorithm.
- `../domain-screen.json` rechecks three exposed R15 draws. Whole ADD share is 36.4–36.9%, MUL 37.4–38.2%; E0-pair equal-cost proxies are only 0.37–2.43% whole. These proxies assume equal within-class costs, are not removable-time bounds or probabilities, and say nothing about unseen inputs. Low lattice is not the primary ≥10% route.
- The remaining untested representation was the R14 **signed64 ADD paper reserve**, now bound to `../Runtime-signed-add.lean.inc` (SHA256 `ff3accda4f4defa8f838853d97771ac94405f1411b8392422aa197a1fe7b9416`, written before suspension). Two's-complement mantissas align and add without magnitude/sign branches; one signed integer cast supplies normalization/RNE, then raw exponent translation. Guards E∈24..252 and gap≤38 imply every nonzero result is normal with field≤253, removing all late fallback. Exact cancellation returns +0. Zero/nonfinite/subnormal inputs fall back unchanged. This is a representation/cost-premise change from R18, not a new mathematical addition rule.
- `../signed-add-model.json`: 46,368 fixed/random exact-integer cases, zero mismatches, 192 fixed cancellations, 1,998 fixed small-integer cases. No native execution, Lean or full proof. Broad nearby E24..254/gap≤39 opportunity proxy was 24.9–27.7% whole; exact runtime guard exposure is still UNKNOWN. A 10% whole gain would require about 37–40% reduction of that proxy's work, before misses. The smallest falsifier would have been one complete B2/variant callback cost comparison including misses/boxing and actual selected assembly. **No Kernel/candidate directory/CI was created.**

The preserved model receipt's array name `rejected_boundary_examples` is overbroad: its `0x1f7fffff,0x0c7fffff` row is an accepted gap38 boundary control (`guard:true`), not a rejected example. The per-row guard value is authoritative. Frozen script/receipt bytes are not rewritten to conceal this labeling issue.

## Official boundary discovered by D

`../../../competition-state-check/receipts.json` binds FloatLib closed/queue0 and TorchLean open/queue14 at 20:47:37 UTC. TorchLean is a separate 12-kernel `ContractExact` obligation. Dot is exact sum of exact products with one final rounding; bias is an exact term. Normalization uses exact rational statistics and fixed later rounding. Old ordered-native sum/BMM and scalar rounded-MUL proofs do not establish these semantics.

The only authorized next activity after the parent notice is read-only TorchLean source/cost/license inspection, with notes here. Do not treat the official transition as user authorization to change target, create a new candidate, run CI, submit, or spend funds.

## TorchLean selection evidence

Fixed upstream `accb82b6e2adeda1b41a57a260d68fb3879c427e`; D's `../../../source-snapshot/source-file-hashes.json` binds contract, shipped entry, manuals and runtime. Six boards score complete inference models by weighted geometric ratios; model prep/hash are outside timing. Family and overall weights are not per-kernel time shares. Actual layer costs and current champion source are UNKNOWN.

**Do not optimize only the shipped entry.** At D's 20:49:45 snapshot, overall current #5 has source unavailable; public former #2 SHA256 `cea4422fb6d3bd613b306127e7017331560875ddb840a7f2e174f6c03bdb480f` is available. Its historical 0.0622488 ratio is against its then reference; #5's 0.9397708 is against its own reference, not an additive gain. Former-source publication is evidenced; reuse license and human author attribution are UNKNOWN. Repository `LICENSE` at the fixed commit returned 404, which is not proof that no license exists.

**Stable normalization does not use dotFn.** `ContractExact.rmsnormWith`/`layernormWith` select `rmsnormStable`/`layernormStable` on the normal checked domain and use dotFn only in legacy fallback. Therefore a faster exact dot does not automatically improve the normal normalization statistics.

The first obvious rational-statistics optimization is already in former #2: source lines 2372–2413 define minimum-exponent scan `Y2`, square sum `Y6`, signed sum `Y7`, and `Y8` forming T=n*S2−S1²; lines 2553–2564 prove variance equality. `YaD` uses a 24–25-bit square-root enclosure, and `Yba` handles integer quotient/remainder final rounding. `Ybb/Ybc` really route the stable kernels through these helpers. Re-proposing integer moments or a smaller sqrt alone is not a new route.

One **unmeasured residual** is that `Y8` scans a row for b0, separately scans for signed S1, then separately scans for S2; common mantissa/exponent decoding and array addressing repeat. A fused signed-moment accumulator could reduce those passes; changing fixed 18-Nat-limb arrays to bounded machine-word partial sums with exact fallback may remove more work, but current #5 may already do it. The minimum next evidence is a profile against public #2 plus actual call/loop inspection; no ≥10% whole claim follows from source duplication alone. A stronger line is to eliminate arbitrary-precision rational work from final normalization division, but #2 already has quotient/remainder specialization and must be inspected before proposing one.

## Primary algorithm sources consulted

- John R. Hauser / UC Berkeley, SoftFloat Release3e `s_addMagsF32.c` and `s_subMagsF32.c`, official ucb-bar repository, BSD3-style header. Their same-exponent specialization and jam/normalize approach substantially overlap old FloatLib experiments; no code was copied.
- LLVM compiler-rt `fp_add_impl.inc`, Apache2 with LLVM exception: magnitude ordering, jammed alignment, cancellation normalization, final RNE. This also does not create a new broadword route merely by translation.
- Lean FRO / Markus Himmel signed integer conversion source, Apache2: `Int64.toFloat32` has a public Float32 model. Old `R14DIntegerRound.int64_model_eq_roundDyadic` is a reusable draft interface, not a current accepted proof.
- Fixed TorchLean `ExactToolkit/StableNorm.lean`, Git blob `dbab06ffdd3c372de2b33e5b53a8af07f818dd06`, fetched read-only through GitHub. Algorithm and author/license beyond its exposed source are not assumed.

At this checkpoint there is no new performance result, no adopted candidate, and no formal submission. The FloatLib prototype remains frozen; choose next work only after the parent's target decision.

## Later read-only refinements

`CERTIFIED-RATIONAL-ROUNDING.md`, `STABLE-DENOMINATOR-BOUND.md` and `SCORE-AND-COVERAGE.md` hold the selected conditional route. The smaller first arithmetic interface is `RMS-QUOTIENT-CERTIFICATE.md`: native operations propose a normalized integer quotient, exact word inequalities validate it, then ordinary remainder/parity rounding packs the result. C's single independent review and fixed falsifiers are in `../../rounding-review/notes/REVIEW.md` / `fixed-check-result.json`; the earlier source excerpts and finite models are not Lean acceptance. Parent's public report attempts returned403 Cloudflare1010; raw failure receipts live at `../../public-reports/20261028T210359Z/receipts.json`. No retry or user-agent change is requested. Layer costs remain UNKNOWN.
