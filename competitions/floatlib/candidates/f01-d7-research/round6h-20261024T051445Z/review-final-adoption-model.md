# Final adopted estimate review

**Read-only review.** I independently recomputed the saved estimate from frozen anchor `d7bcc98f…ed1cfbc` and the six exact-source `df5c61a0…b27fb172` full-gate pairs in the public index. I did not call the saved estimate function. All 26 per-cell deltas and the projected operation/whole medians match the saved model to floating-point roundoff.

| Projection | Independent | Saved model |
|---|---:|---:|
| add | 1.0161062121 | 1.0161062121 |
| mul | 1.1262391292 | 1.1262391292 |
| sum | 1.1405374842 | 1.1405374842 |
| bmm | 1.8440017089 | 1.8440017089 |
| whole package | 1.1773893592 | 1.1773893592 |

For each cell I took the median of `(df5c submission_ns / same-run incumbent_ns) / (41 control submission_ns / same-run incumbent_ns)` across runs 11, 12, 14, 16, A and B. I then applied those deltas to each frozen anchor record’s original `cell_work`, summed the four operation costs and whole-package costs against the frozen champion class costs, and took the median across the six original anchor workloads.

## Three-group retention evidence

The adoption receipt is accepted, says `THREE_GROUP_ADOPTED`, records adoption performed, and has no failure or rollback. Its D/A/B ratios and p05 gains all pass the frozen `.97` and `>0` thresholds:

| Group | Run / seed / job | Relative ratio | Gain p05 | Observer | Shape / order |
|---|---|---:|---:|---|---|
| D | 40074431355 / 1224011 / 120814653529 | 0.887877 | +0.113671 | no | 156-case plan; control, D11, candidate |
| A | 40083425886 / 1224091 / 120841443871 | 0.870513 | +0.137200 | no | distinct 156-case plan; candidate, D11, control |
| B | 40083571000 / 1224092 / 120841858649 | 0.897198 | +0.084925 | no | distinct 156-case plan; D11, candidate, control |

All three plans set `capture_codegen=false`, have distinct run/job IDs and distinct shape-vector hashes. The six full-gate model inputs use the exact `df5c` source and public-v2 suite. Runs 14 and 16 are observer-executed for both `df5c` and the paired 41 estimator control; D, 12, A and B are observer-free. The frozen estimator intentionally retains all six exact-source full samples. A clean-only four-pair sensitivity projects to whole 1.191439 and bmm 1.956400; it is not the adopted model.

The R12 public index lists 17 distinct run IDs, all terminal with downloaded artifacts. I checked 46 result rows: each raw verdict hash and downloaded Kernel hash matches its index record. Thirty-nine rows are full-gate results and seven are statement diagnostics; run 40069713432 is a failed diagnostic workflow whose artifacts are present. The six model rows are full-gate score verdicts with 25 rounds and the expected `df5c` source hash.

The earlier retained-control metadata is separate: it lists 18 D11 full-gate runs for the original estimator identity check and records that the old model hash `da02d437…e3b1d1` and R11 freeze stayed unchanged. The successful adoption receipt’s before-hash is that old model; the current model is the new `5d946420…8a031f` estimate.

## Dashboard and official reference

The live dashboard has exactly four operation rows, all linking to the same `df5c` Kernel. Its estimates round correctly to add 1.02×, mul 1.13×, sum 1.14×, bmm 1.84× and whole 1.18×. The operation labels match the source mechanisms. The official refresh confirms champion #285 and digest `a1e99008…7103082`; the champion source endpoint returned 404. The estimate is marked `INFERRED`; direct same-suite champion timing and official admission remain UNKNOWN.

## Post-adoption display update and traceability

The original adoption receipt was followed by an explicit display/state update. Its separate [post-adoption receipt](post-adoption-display-update.json), SHA-256 `08797f64…1a38b8bc`, reconstructs the original receipt’s after-hashes exactly and binds the current view, state, dashboard and unchanged model hashes. It records the four operation labels, an R12 end-state update and Windows CRLF dashboard rendering; it also states that the numeric model, source, anchor, thresholds and tools were not changed. I independently verified that all four current hashes match this follow-up receipt and that the original adoption receipt remains byte-identical.

Full hashes, independent cell deltas, projected anchor samples, 17-run inventory and receipt comparisons are in [review-final-adoption-model.json](review-final-adoption-model.json). The model is an inferred cross-suite projection, not a direct champion timing result.
