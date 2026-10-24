# R13 short-packed route review

Reviewed at 2026-10-24 12:44 UTC. Read-only review; no Lean, CI, Git, candidate, or shared-state action was taken. Root's D5 full comparison run 40094337126 is not used as evidence in this report.

## `f01-d13-short-packed`

Candidate SHA `252b4539…04af80`, 248,130 bytes, 7,870 bytes under the package cap. The manifest and builder agree on exactly two replacements within `bmmBeforeR11Cross`: the `n ≤ 4 ∧ 2 < p` runtime branch changes `DirectContinuous.core` to existing `RowStream.core`, and its proof changes to `RowStream.core_eq_reference`. I independently reversed the two substitutions: the original section and whole parent Kernel SHA `df5c61a0…fb172` both match exactly.

No other source text changes. The outer `UnderflowZero` guard still precedes this dispatcher, the `p = 2` R11CrossRows branch remains earlier, and the existing `bmmBeforeDirectRows` fallback remains the else branch. The proof reuses an existing unconditional RowStream equivalence; full integration and full gate are still NOT_RUN in the manifest.

## Historical route evidence

I found **no prior full-gate negative for this exact df5c change**. There is relevant historical coverage:

- The old `f01-d5-stream-pack` Kernel (`8eb63a2f…61e045`) sends every nonempty BMM shape to `RowStream.core`. Its seven saved R7 public-v2 full gates exposed the `n ≤ 4, p > 2` subdomain in 19 timed case executions across seeds 801, 802, 804–808 (21 cases including two untimed checks). Those were full-gate passes of a different source and overall package, not a paired incremental comparison against df5c; they do not establish a negative for this route.
- The historical `f01-d11-bmm-direct-continuous` source (`2aaa5d9e…a5f56`) used this exact shape guard but ran DirectContinuous. It passed full gates on runs 40032766690 and 40039965234. The discovery comparison at run 40032766690 was 0.963488 whole and 0.815550 BMM normalized versus D10 DirectRows, with p05 0.030509; the run had codegen capture. This is positive evidence for DirectContinuous against DirectRows, not a test of switching that branch to RowStream.
- The exact-df5c seed-1224016 diagnostic groups eight timed cases as DirectContinuous (14.246874 ms original-whole sum) and fifteen as RowStream (6.231684 ms). The groups contain different cases, so those sums do not compare the alternatives. The profile itself marks route classification as source-model and stage probes as perturbed diagnostic data.

Thus this is a valid new route experiment. Only D5's clean candidate↔df5c full comparison can decide whether RowStream wins on the current source and input set.

## Optional `f01-r13-cross-fused-output` static check

I independently reversed its three ledger entries. Each new block/replacement occurs once; the reconstructed Kernel SHA is df5c. The candidate is 255,114 bytes, leaving only 886 bytes, and the manifest reports no Lean/full-gate/codegen/performance run.

Statically, the added writer reuses `R11CrossRows.blockRows` and emits its W8 fields as two row-major values. `word_point` bridges each emitted field to the original `RowStream.point`; row guards discard the padded tail, `emitBlock_prefix` advances by four rows, and `output_prefix` closes over the existing ceil-divided `groups` fold. Only the already-guarded p=2 Cross dispatch arm and its proof bridge change. UnderflowZero/Cross priority, pack, ordered recurrence, `finish8`, NaN behavior, and all other routes remain unchanged.

Its key runtime falsifier remains code generation and complete cost: the source removes the all-groups W8 vector and second traversal, but still computes one W8 per block and appends rows to the final Array. Reuse/copy behavior, actual route reachability, and whether allocation or `Array.push` offsets the saved vector/scan cost are NOT_RUN.

## Bound evidence

Hashes and route-case counts are recorded in `review-short-packed-route.json`. No official score or champion-performance claim is made.
