# Skip-aware read-ahead: source checkpoint

Status: **SOURCE_INTERFACE_DRAFT_UNCOMPILED**. No native Rust, fresh extraction, Lean gate or performance result is supplied by this checkpoint. Parent public #432 attribution and fast3 constants are retained. The source is independent of the closed pendingfold/continuation/gaprepeat probes and the separate sniff experiment.

Frozen pair prepared for the parent runner:

- Rust `3e68ad368a56115111fc0f61038dcaa3658e2b31dee40db24916445b49add08e`.
- Lean draft `672a5c17aabdc647e13ee0c73a4535f73dc3c242785bf7fb5d07e44cefda687f`.

The original non-lazy loop preloads `p+1` before probing `p`. If that probe misses and the unchanged skip formula advances farther, it discards this cache and loads the actual destination again. This candidate predicts that exact miss destination before the probe and preloads it once. It keeps early loading rather than moving it after the outcome branch. Successful matches may pay for recomputing the first insertion key instead; extra arithmetic, live registers and scheduling changes could outweigh the eliminated reads.

R4 `slotonly` removed candidate-word loads on successful non-lazy matches after moving the probe before lookahead. R4 `endreload` changed the match-end reload. Neither changed the skipped-miss destination. The original compiled fast3 receipt `evidence/round4/37515419910/gate/cpu/r3-432-fast3-assembly.txt` shows a miss shift/cap followed by new hash/head/candidate loading at `0x11000..0x1106b`. That is historical generated-code evidence of the second load path, not a current CPU profile or evidence that this candidate's compiler eliminates the intended work.

Equivalence obligations are explicit:

1. Current `head_set(p)` stays before prediction/lookahead. A future slot colliding with the current slot sees `p`, exactly as the original later miss reload would.
2. The discarded old `p+1` lookahead never writes the head. There are no head mutations between it and the old miss reload, so the forecast cache at a live destination is identical.
3. If the probe succeeds and forecast differs from `ins`, `r11_record_slot` computes the original key at `ins`; it does not use the forecast key. The insertion cursor is the search/lazy cursor, not the backward-folded match start. Fold preserves the end, and every old insertion stays in order.
4. With `lazy>0`, forecast is exactly `p+1`, the old lazy loop and miss reload remain. Cache and insertion behavior are unchanged.
5. If forecast reaches `lim`, the leftover tuple can differ, but the loop exits before consuming it. Counted output still must match.

The 4000-case Python model covers cache identity for valid states, 192 forced same-slot forecasts, 14 forecasts reaching the limit and first-slot repairs. It is not an opportunity count or whole-parser test. Native 444 cases and all28 public token/output identity are mandatory. Any difference rejects the current implementation before performance interpretation.

The proof draft only adds bounds rules for the two helpers. `r11_next_spec` keeps the next position strictly after p and at most lim; `r11_record_slot_spec` keeps the slot inside H. Original `MainInv1` only requires past candidate position and the matching cached word, not that the slot represents `p+1`. Nevertheless the actual Aeneas signatures, loop state and old `step*` proof must be checked after real extraction. The draft is not an accepted pair, and the original obligation/axioms have not been weakened.

No actual skip-event counters are claimed. Desired follow-up counts, if the paired result merits them, are loop calls, non-lazy forecast beyond p+1, true skipped-miss reuses and successful-match insertion-slot repairs. Existing component fractions imply a limited total-time opportunity; fewer source reads or a smaller instruction sequence alone cannot establish the required frontier gain.

Generation and reverse-region audits: `python scripts/build-round11-fast-skipahead.py --check`. No source, proof or parameter variant should be silently changed after this pair is frozen for CI.
