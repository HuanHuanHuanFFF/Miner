# R25 end4 under the existing insertion budget: independent static review

Review of root's proposed rule only; no candidate or shared script was changed. M sparse's full gate is paused after its original-protocol screen had no share in the root's29687 calculation. Its actual-extraction proof draft is retained as uncompiled evidence. This review makes no fresh leaderboard claim.

## Judgment

**INFERRED:** retaining the first head insertion and existing end-1 while trading only the second head position for end-4 is a useful single diagnostic. It tests the unresolved value of the second head key. It is substantively different from both adding end-4 and removing end-1. It may retain enough of the demonstrated suffix opportunity without an extra hash/table write, but there is no quality or speed guarantee.

The highest-risk implementation detail is short matches: unconditionally lowering the head insertion count from2 to1 also discards the second key when no new legal end-4 key exists. That would mix a second mechanism into the experiment. A precise swap should preserve the old sequence outside its eligible domain, or explicitly predeclare that additional removal as part of the test.

## Evidence and limits

**VERIFIED:** `feedback-a-native.json` records end4 addition at5325224B,7397B below combo, with all15 changed files smaller. Its independent original screen was slower, and the exact original gate38125243582 accepted Rust `03ec0aa4e617d622755e85324a9d4fbc77ef74e6572485b3170e2790681ed8e6` paired with the unchanged combo Lean `4ff09d168269ae8d9c93e602496b01078d2d0ec80f27d6cd16041d91a76c70a6`.

**VERIFIED:** `feedback-b-native.json` records tail4 replacement at5339154B,6533B worse than combo;12 of15 changed files grew and3 shrank. That experiment retained both head positions and exchanged end-1 for end-4. It is strong evidence that the crossing end-1 key has useful coverage on this corpus. It does not measure the marginal value of the second head key or prove end-4 itself is bad.

The earlier R3 insertion-density experiments reduced size while adding time (`docs/rounds/round03.md`, lines36/55). Those changed density, not this position allocation. R22 halfhead changed table capacity, not insertion count. R22/R23 deeper chains changed search depth, not retained positions. Neither should be cited as having already tested this exact swap. Old bucket2 had identical tokens and no speed benefit, but concerns table layout rather than this placement question.

## Exact position-domain checks

Let `i=ins0`, `j=end-4`, and keep the inherited `lim=n-8`. In ordinary non-lazy cases the first head insertion is `p+1`; the caller can also supply `p+2` after lazy probing, so the rule must use `ins0` rather than hard-code offsets from `p`.

The original intended first two positions are `i,i+1`, clipped by `end` and `lim`. A budget-neutral replacement for the second is eligible only when the original second exists and `j>=i+1`, `j<lim`. If `j=i+1`, the replacement is identical. A genuinely new position needs `j>i+1`. For `i=p+1`, length6 is the identical-position case and length>=7 can change placement; for `i=p+2`, the corresponding lengths are7 and>=8. Shorter matches should retain the old second insertion if the goal is a clean swap.

Maintain chronological, distinct insertion order: first `i`, replacement `j`, inherited tail when legal. Do not insert end-4 after end-1: that makes an older position replace the current bucket head and changes the predecessor-chain order. Do not accidentally hash/link `j` twice through a modified `ins` variable and the remaining loop/tail. A repeated position can make a self-link and consume bounded search depth even though independent match validation can still prevent invalid output.

The tail is not always a fresh end-1 write: on short spans it can coincide with a head position already emitted, and near `lim` it can be excluded. Preserve the original clipped/de-duplicated behavior, not merely a final unconditional end-1 call. Conversely, end-4 can still be below `lim` when end-1 is excluded; this is a valid domain if it consumes the existing second-head budget.

The inherited first insertion uses `a0` from lookahead and avoids recomputing its hash. Retaining it matters for both cost and prefetched-bucket coherence. Its source helper also guards `a0<H`; caller proofs normally ensure a valid slot, but a replacement should preserve the safe fallback rather than silently strengthening the public helper's precondition.

## Omitted-opportunity and cost risks

- The second head position can seed a later short/shifted match absent from the complete suffix key. There is no receipt counting its accepted future uses, so its marginal quality is **UNKNOWN**.
- In repeated substrings, end-4 can share a4-byte bucket with a retained key. Its marginal information may then be small while it displaces another head/predecessor. Changed key availability alters subsequent parse positions, fold behavior and emitted symbols; byte differences cannot be added/subtracted from the two earlier experiments.
- The complete suffix key rationale is strongest before a true mismatch; matches capped at258 or terminated by input bounds are different domains. The existing evidence does not identify which domain produced7397B.
- Equal numbers of hash calls/head/prev writes do not imply equal time. New guards, changed cache access, altered probes and the downstream encoder all contribute. Total original-protocol timing remains necessary even if an operation-count model is exact.

## Lean reuse

**VERIFIED:** the end4 addition already passed with the original parent Lean, so the existing record proof's `step*`/case splitting can absorb some bounded extra operations. `PC.f_record3_spec` only promises `HeadBound`; it does not promise insertion density or particular matching coverage. `f_link_spec` plus `slot_of_m_spec` can cover a replacement `j<end` and `j<lim`, with the existing independent validators handling any retained candidate. No new correctness invariant about beneficial compression is needed.

**INFERRED:** if root's implementation preserves function and loop interfaces, the parent proof may again compile unchanged. If end/j is referenced inside the first insertion loop, real extraction can add a captured argument to `pc_f_record3_loop0` and its body; its current lemma only carries `s/head/prev/km/ins/stop`. That requires a small loop-lemma migration. If a loop is removed entirely, old Lean references to its extracted definitions must also be removed or adapted. The already-passed end4 gate does not certify this new source.

The practical minimum remains exact-source28-file original-encoder/decode comparison against combo and end4, followed by actual extraction and original paired time only if the quality/cost tradeoff warrants it. A lightweight insertion-sequence model can reject duplicate/order/budget mistakes before native execution, but is not correctness acceptance or a prediction of compressed bytes. Do not expand to a density/position sweep without new feedback.
