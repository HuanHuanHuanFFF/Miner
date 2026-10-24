# R13 p=1 CrossRows opportunity review

Reviewed at 2026-10-24 12:44 UTC. Read-only review; no candidate, CI, Git or shared-state action and no Lean/test run.

## Proof domain and unused lane

The existing `R11CrossRows.core_eq_rows`/`rowWord_eq` proofs accept `p ≤ 2`, so p=1 is statically inside the proved domain. `packGeneral` and `packShared` are parameterized by arbitrary p: the valid B lane is `base + k*p`, which becomes `base+k`; the other lane is `base+1+k*p`, which can read the next input value or `getD`'s zero fallback at the array end. `rowWord` with `Fin p` returns only j=0 for p=1.

There is a concrete source-level cost risk. CrossRows builds a W8 with four rows by two columns, `dot8` updates eight accumulators, and `finish8` constructs eight finished words. With p=1 only the first word for each row is returned, so the second column is unused in the final vector. Whether the compiler eliminates any of that work is UNKNOWN; no p=1 Cross codegen was found. Reusing the p≤2 correctness proof would be plausible, but it would not prove the proposed route is faster.

Any p=1 dispatch should be a separate arm and retain the p=2 arm. Keep the existing positive-n, USize, array/output-size guards and handle empty batches/outputs explicitly; m≥4 alone is not a replacement for every old guard.

## Historical evidence and first falsifier

No historical full-gate negative was found for dispatching p=1 to CrossRows. The old `f01-d5-stream-pack` source (`8eb63a2f…61e045`) routed all nonempty BMM shapes through RowStream. Its seven public-v2 full gates exposed the n≤4,p>2 family in 19 timed cases, but they benchmarked a different whole package and do not isolate a p=1 CrossRows route.

The historical `f01-d11-bmm-direct-continuous` source used the same n≤4,p>2 guard but DirectContinuous, not CrossRows. It passed full gates on runs 40032766690 and 40039965234. Its run-916 discovery ratio was 0.963488 whole, p05 0.030509 versus D10 DirectRows, with an observer. This is not a p=1 Cross test or a negative.

In the exact df5c seed-1224016 profile, p1 `bmm:ml:7` (m=9,n=3) had an uninstrumented whole-case anchor of 3.396324 ms and is eligible for m≥4; p1 `bmm:ml:1` (m=1,n=67, 1.083267 ms) is excluded. The one eligible case is about 1.95% of that plan's 174.631942 ms whole anchor. Even eliminating the complete case would not reach 3% on that one plan; the D5 plan can contain other eligible cases, so this is not a bound for the full experiment. The source-level extra second lane and this case are the clearest early falsifiers/risk. Do not infer time from MAC or lane counts.

The already-started D5 run 40094337126 is the relevant current-source full comparison; its result is not used here. Do not treat the profile's p=1 case timing as a score or permission to proceed to confirmation.

## Optional cross-fused-output static review

The `f01-r13-cross-fused-output` ledger's three replacements each occur once; reversing them reconstructs the df5c parent SHA. It is 255,114 bytes with 886 bytes remaining. The static Prefix chain maps each W8 pair to two row-major `RowStream.point` entries, guards every row, and folds `ceil(rows/4)` groups to the full output length. Only the existing guarded p=2 Cross arm and its proof bridge change. UnderflowZero/p2 priority, P12 packing, ordered recurrence, finish8, NaN behavior and other routes stay unchanged.

Its intended saving is removal of the all-groups W8 vector and second traversal. It still computes one W8 per block and appends to the final Array. Actual codegen, Array reuse/copy behavior, Lean integration and whole cost remain NOT_RUN.

## Bound evidence

Source, manifest, historical full-gate, and exact-df5c profile hashes are recorded in `review-column1-p1-cross.json`.
