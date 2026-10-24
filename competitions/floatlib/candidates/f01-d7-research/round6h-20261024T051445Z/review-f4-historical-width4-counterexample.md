# Historical global-width4 counterexample supplement

This supplements [review-f4-public-plan-opportunity.md](review-f4-public-plan-opportunity.md); that report is preserved unchanged. The relevant historical result is a real negative current-public-v2 measurement, but its run ID needs care: **the full-gate result is run 39847080316, seed 809.** Run 39839349846 is seed 806; its width4/width8 rows were statement-only and contain no score. Some older D7 indexes cross-link the run-398393 artifact for this candidate, so that artifact must not be cited as the full-gate timing.

## Exact full-gate evidence

Run 39847080316 used the official public-v2 suite (`a16494e9…cd34868`) and public-drawn plan seed 809. The exact width4 source is `f01-d7-width4-proof2/Kernel.lean`, SHA-256 `96131686…3e7674f7e`, 137,146 bytes. Its raw verdict is `mode=gate`, `stage=score`, `passed=true`, `exit_code=0`, with 25 rounds and matching start/end verifier fingerprints. The same run includes `f01-d7-direct-small` as baseline, SHA-256 `d9a80847…51411fb3`; both use the same drawn plan and official suite.

The saved same-plan comparison reports width4 versus D9 as 1.15596 for whole-entry time and 1.45707 for BMM after reference normalization; raw ratios are 1.15606 and 1.45823. Ratios above 1 mean width4 was slower. Width8 was also slower: whole 1.17617 and BMM 1.50598. Per BMM cell, normalized width4/D9 ratios were 1.989 dense, 2.046 ml, 1.304 sparse, 2.332 specials, 1.367 subnormal and 1.604 extremes.

This rejects the **global width4 implementation** on that run. It does not measure a p=3/4-only branch. The seed-809 plan has 34 timed BMM cases, nine with p=3 or 4 and six with p=3/4 and n>4. Those shapes account for 30.38% and 18.92% of planned BMM MAC work, respectively. The verdict stores only six BMM cell aggregates and round totals; it has no per-case timings. Therefore p=3/4 and p=3/4,n>4 runtime results are **UNKNOWN** in this artifact.

## What the old implementation actually did

The old source is not already restricted to narrow p. `Packed4.groups=(p+3)/4`; `packB` and `outputFromTiles` use four-column blocks; the exported BMM calls the Packed4 stream path for every nonempty output and nonzero reduction. There is no `p<=4` or `n>4` dispatcher guard. The seed-809 drawn plan exercised p values from 1 through 59, so the negative aggregate includes all sampled widths.

Its `Packed4.finish` tests `result.isFinite`. A finite result converts directly; any infinity or NaN reruns the entire n-step original Binary32 multiply/add fold from +0. It does not use the later NaN-only guard or quiet-NaN replay. The old row writer constructs vectors with `Vector.ofFn` and `flatMap`; it is not the current D11 Array-backed continuous row writer.

The current parent `f01-d11-bmm-combined-classifier` (6c2d…a4277d) already has materially different surrounding machinery: p=2 CrossRows dispatch, ten-lane Packed10 for the generic route, `R7W04.nonNaN` finalization, and `R7NaNReplay.replayEarly`. That replay starts at k=0 with the exact raw fold and can stop after an absorbing quiet result. The proposed F4 branch further narrows dispatch to p=3/4,n>4 and retains the current writer. Those are real implementation differences from the old global-width4 experiment. The F4 packet, four ordered accumulators, and column-block mapping themselves are old and were already full-gated.

## Interpretation for the proposed branch

Treat the run as a strong stop signal against copying the old generic width4 route. Do not treat its 1.457 BMM ratio as a measured p=3/4 penalty: this batch never saved per-case time, and its width4 code handled every sampled p with an isFinite/full-replay fallback. The narrower route plus current NaN-only/quiet replay and Array writer is a different hypothesis, but it has no performance evidence yet. The first useful test must retain the n>4,p=3/4 guard and report target-shape timing separately; otherwise a broad full-suite result cannot answer whether this slice helps.

See [review-f4-historical-width4-counterexample.json](review-f4-historical-width4-counterexample.json) for exact hashes, draw-shape counts, verdict details, source comparison and the run-398393 correction.
