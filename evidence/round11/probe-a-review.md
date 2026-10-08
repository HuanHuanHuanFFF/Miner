# R11 probe-a independent review

This review covers run `37722786008` (`probe-a`) and official snapshot 28214. CI completed successfully, but `state.gates` is empty and no candidate full gate was accepted.

I recomputed both fast variants from the 28 paired files in each block. For each file, I used the median of 11 measured `total_s` values and averaged candidate/incumbent ratios. Input SHA-256s match across methods and blocks; candidate output streams are deterministic and identical between blocks.

| Variant vs fast3 | Block 1 time | Block 2 time | Mean block time | Size delta | Changed output streams |
|---|---:|---:|---:|---:|---:|
| pendingfold | +0.742774% | +0.695779% | +0.719277% | 0.000000 pp / 0 bytes | 0/28 |
| continuation | +0.609618% | +0.483303% | +0.546461% | −0.006407 pp / −1,201 bytes | 12/28 |

Fast-shadow drifted +0.517556% in block 1 and −0.174696% in block 2, with output and token streams identical to fast3. This is a same-run noise diagnostic, not a confidence interval. Both candidates were slower than fast3 in both blocks.

Continuation's 12 changed streams comprise 8 smaller files (gross −1,250 bytes), 2 larger files (+49 bytes), and 2 same-size but different streams, netting −1,201 bytes. `catalog.xml.txt` and `multibyte.txt` account for 1,073 bytes, 85.84% of gross reductions. The size gain is small and concentrated.

The finite native checker covers 444 cases per variant: 28 public and 416 synthetic. Pendingfold matched fast3's tokens and decoded in all 444. Continuation differs in 32 token streams (12 public, 20 synthetic); all candidate and reference outputs decoded, and frozen/instrumented results agreed. Continuation is not declared equivalent to fast3, so these token differences are expected variant behavior, not a correctness failure. This finite check is not an all-input proof or full gate.

Snapshot 28214 contains 507 Pareto rows and 82 frontier rows. The projections are `(time=0.441022980, size=36.999728557)` for pendingfold and `(time=0.440266265, size=36.993252266)` for continuation. Both are strictly dominated by current frontier IDs 481, 506, and 507, so each has zero geometric share and zero conditional same-hotkey additional share. #453 is off frontier with payable weight zero. Snapshot freshness is unknown; future admission, registration, bounty, validator identity, and actual chain payment remain unknown.

No omitted positive result changes the stop decision for these exact revisions: pendingfold has no size gain, while continuation's small saving does not offset slower time or current domination. This is a snapshot-bound screen, not a rejection of future variants. Raw-file hashes and exact per-file differences are in [`probe-a-review.json`](probe-a-review.json).
