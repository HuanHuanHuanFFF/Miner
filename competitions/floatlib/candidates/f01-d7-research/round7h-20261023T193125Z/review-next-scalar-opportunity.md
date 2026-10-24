# Next scalar opportunity: exact6c six-run review

Conclusion: **first inspect actual MainFull hot code; keep numeric-band retries parked.** A conditional second lead is reuse of existing raw-NaN cold helpers, not a new NaN classifier mechanism. No gain is established. Only this report pair is written.

## Recomputed cost exposure

The exact adoption index SHA is `f55fc7442cd978df09c8e0d38becb46af832bd6d69fcda419d0ad0865501f9ba`; exact source is `6c2d394dd34e8854d0d44d5d6605c194ecb27c152a1768d236481fc03fa4277d` (254654B). For each run, class cost = raw gate class submission_ns times independently summed timed plan work. Raw-verdict SHA/pass/25 rounds/seed, summary seed, all input Kernel hashes, plan work, public-cell-work and all four operation totals were checked. Untimed raw cases are excluded. These are headline class cost reconstructions, not25-round walltime sums or stage profiles.

Each row below is the median [min,max] of percentages computed separately in each run. Do not sum independently computed medians or mistake a class share for removable conversion/fallback time.

|Class|% of complete source cost|% of same operation cost|
|---|---:|---:|
|add:dense|4.494 [4.183, 4.662]|13.166 [12.919, 13.504]|
|add:ml|5.977 [5.576, 6.218]|17.400 [17.236, 18.012]|
|add:sparse|4.980 [4.664, 6.185]|15.062 [13.511, 17.339]|
|add:specials|5.893 [5.047, 6.191]|17.179 [15.243, 18.108]|
|add:subnormal|3.385 [3.231, 3.681]|10.071 [9.436, 11.118]|
|add:paired|5.977 [5.577, 6.218]|17.405 [17.218, 18.013]|
|add:extremes|3.249 [2.896, 3.360]|9.484 [9.044, 9.725]|
|mul:dense|5.212 [4.991, 5.443]|14.540 [14.091, 14.856]|
|mul:ml|6.836 [6.381, 7.113]|18.897 [18.734, 19.319]|
|mul:sparse|5.737 [4.723, 5.974]|15.504 [14.054, 16.480]|
|mul:specials|4.493 [3.880, 5.023]|12.526 [11.224, 13.433]|
|mul:subnormal|3.433 [3.133, 3.881]|9.328 [9.256, 10.556]|
|mul:paired|6.835 [6.380, 7.118]|18.911 [18.719, 19.320]|
|mul:extremes|3.608 [3.485, 3.766]|9.977 [9.755, 10.370]|

Overall add is34.067% [32.024,35.668] and mul36.442% [33.608,37.518] of source cost. Special cells together are10.327% [9.518,10.922]; this is not a NaN-only or eliminable-stage budget. JSON retains every run, class cost in ns and both shares.

|Seed|Run|Role|Observer|
|---|---|---|---|
|922|40039965234|DISCOVERY|True|
|929|40044330511|DISCOVERY|True|
|930|40044727137|DISCOVERY|False|
|933|40047321773|DISCOVERY|False|
|103391|40048911739|FROZEN_INDEPENDENT_CONFIRMATION|False|
|103392|40048972520|FROZEN_INDEPENDENT_CONFIRMATION|False|

922/929 remain observer discovery;930 is selected discoveryD,933 unselected discovery;103391/103392 are clean frozen independent A/B. No source/role samples were dropped.

## Current source and actual codegen boundary

Kernel3263-3266 computes two numeric conversions, native add, then the result self-BEq; nonNaN results including Inf are accepted, otherwise TunedAdd. Kernel3284-3287 nativeMul uses two toFloat32 conversions, native multiply, result self-BEq and FastMul fallback. Kernel3301-3304 retains expSum<128 LowScale; it must not be accidentally replaced by a normal-path proposal. TunedAdd2042-2054 and FastMul2408-2420 repeat their special checks before generic ExecFloat fallback. Whether LLVM folds those checks at the actual caller is UNKNOWN.

825 exact41 diagnostic C already cloned scalar bodies into MainFull public lambdas; W11 actual60f machine code also showed caller specialization and foreign conversions. Neither binds current6c actual public MainFull machine code. Submission wrappers and old-object observations do not establish current inlining, foreign-call cost or removable cycles. No MainFull/final-link claim is inherited.

## Negative results and existing NaN assets

919 e279 normal-band exact full gate passed but whole normalized ratio1.01759515, p05=-0.01601289; add1.04349682 and mul1.01006218. Some cells improve (e.g. mul:ml0.858057), while dense/sparse/extremes regress. Do not restart a numeric-band threshold grid from the favorable cells. The same-run official-add-fallback candidate fully passed but whole1.00328806/p05=-0.00797838; add0.99647369. It is a source-capacity asset, not a selected speed gain.

Raw NaN operand priority/quieting is already prepared in4a30 (Option rawChoose and selected_add/mul) and939 (no-Option complete exceptional word dispatcher). Their original manifests remain unrun, and the adoption index contains no eligible full-gate measurement for either; absence here is not proof they were never examined elsewhere. Old808 special-model285ed4 was rejected for concrete proof rfl goals, not timed. Existing808 tensor raw quiet-accumulator replay7acff and generic fullpath9a2a both actually passed; word/fullpath headline ratio is1.01649605 (one discovery pair, about1.65% slower). This is a different tensor replay mechanism; it neither disproves scalar selection nor supports calling raw classification automatically faster.

Current6c already includes full-pass rawSNaN/quietRaw bridges (483-565), quiet-left-NaN rule643-653, and raw suffix step694/5014. They preserve later signaling-NaN override; generic quiet-NaN absorption cannot discard later sNaN in sum. Reuse these established assets rather than re-proving or advertising them as a new direction.

## Two falsifiable next steps

1. **GO, codegen diagnostic only: exact current MainFull hot path first.** Capture the actual BENCH_PLAN add/mul closures/lambdas, boxed adapters, BenchSuite.runScalar call chain and the same statement objects, with C, nm, SHA, relocations and available link provenance. Check whether candidate-controllable duplicate conversions, tests or spills remain. Immutable benchmark dispatch cannot be optimized by editing the candidate. If the actual path is already minimal native arithmetic plus fixed ABI, PARK common finite-path work. Call counts and C size do not supply cycle or gain estimates.

2. **Conditional existing-asset revisit: raw selection only after the current NaN-result guard.** Preserve the fast result guard and LowScale. Reuse4a30 selected_add/mul plus existing quieting for rawChoose=some; retain certified generic fallback for None/invalid. This avoids claiming the old939 exp255 premise follows directly from the new result guard. If choosing full no-Option939 instead, that domain bridge remains a real missing obligation. Do not add a NaN preclassifier ahead of all finite calls without new cost evidence. Inspect actual MainFull cold code for Option construction/repeated decoding, then use one complete exact-source gate and cost comparison. PARK if extra branching/materialization cancels savings.

The6c source has1346B headroom; the existing DWordNaN block alone is7400B, so it cannot just append. The exact old TunedAdd block is15524B and has the known two-reference official-fallback removal route;919 supplies negative timing evidence for that capacity edit. Deduplication/removal plus the new proof context must be independently checked. No new source, proof, full gate or performance result is claimed. Class shares are exposure only; projected gain remains **UNKNOWN**. This recommendation does not extend the current round or change next-investment40/35/25 allocation.

All source/manifest/raw verdict/plan hashes and per-run values are retained in the companion JSON.
