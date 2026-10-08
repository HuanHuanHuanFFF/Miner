# R11 frontier route review

Snapshot **28214** was computed at `2026-10-08 03:16:43.509389 UTC` (11:16:43 +08). The receipt covers the 11:16:52–11:17:01 +08 retrieval. All 13 raw response hashes/sizes and all four derived-file hashes match; six Pareto pages contain 507 unique rows, five leaderboard pages contain 481 rows, and request cursors, page contexts, and weights/current all align to snapshot 28214. Freshness is API-reported `unknown`. The [receipt](official-start/receipt.json) and [complete Pareto pages](official-start/pareto-pages.json) are the exact inputs.

The captured scorer policy is local-global improvement-space log, bounds 10.0/40.0, Pareto/improvement shares 1.0/0.0. The local scorer replay checked 496 scored rows and reproduced weights within `3.47e-18`. This checks the saved policy against the public scorer source; deployed validator identity remains UNKNOWN. Weights/current reports `chain_accepted=false`, but the actual finalized-chain result remains UNKNOWN.

## Entry thresholds

The original speed endpoint #453 is now off the frontier. Its coordinates remain `(0.437873458, 36.999728557)`, but its current Pareto and payable weights are zero. It is payment-eligible in the API row, and no same-hotkey submission survives on the current frontier. #506 `(0.436622858, 36.664602629)` and #507 `(0.434267784, 36.685609096)` dominate #453.

At #453's fixed size, a new point needs time **strictly below 0.434267784**—at least **0.82345% faster** than #453 at the boundary, with a strict margin beyond it. At #453's fixed time, size must be **strictly below 36.664602629%**, an improvement of **0.335126 pp** (0.90575% relative).

The R10 pipeline same-family projection is `(1.403780310, 34.185517190)`, still dominated by #360/#418/#422. At fixed size, time must be **strictly below 1.333373452** (#418), about **5.01552% faster**. At fixed time, size must be **strictly below 34.177242463%** (#422), an improvement of **0.008275 pp**. The underlying [R10 final summary](../round10/final-summary.json) records the projected point; this remains a public-to-formal transfer hypothesis.

For a nearby fast3 objective, `(0.4350, 36.68%)` sits between #507 and #506 and is non-dominated when inserted into the current geometry. Its conditional geometric share is **0.08210%**. This is a geometry witness, not a measured target or stage2 forecast; admission, registration, bounty and actual payment remain UNKNOWN.

## Historical alternatives

R3 selected the gate-verified fast3 derivative. Its other fast2/tshift3/dmin257 variants do not supply a new robust R11 route: the early screen found no fixed-#427 frontier candidate, while later same-family variants either lost to fast3 or retained only narrow, historical projections. See [R3 selection](../round3/selection.json) and [R3 report](../../docs/rounds/round03.md).

The most relevant unverified fast-side mechanism is [r4-cpu-directemit-wrap](../../candidates/r4-cpu-directemit-wrap/manifest.json). It changes match packing/emission arithmetic rather than the R10 finder pipeline. Its one-run, four-block public comparison preserved output on 28 files, but block time changes versus fast3 were `+0.3282%, −0.5092%, −0.0671%, +0.6425%` (mean **0.0986% slower**). The R4 H run was cancelled; its directemit-wrap gate was not accepted, and the saved decision says the proof still failed. Under the historical same-family #432 transfer it projects to `(0.429749494, 36.991342624)`, which is non-dominated in snapshot 28214 with 0.09637% conditional geometry; the fixed-#427 projection is instead dominated by #507. That calibration-sensitive projection does not override the lack of a repeatable speed gain or a completed proof. Evidence: [R4 selection](../round4/selection.json), [paired refine analysis](../round4/37529887857/refine/analysis.json), and [stop decision](../round4/decision-stop-h.json). I would not promote it as an R11 candidate on this evidence alone.

The R4 H16/#299 small-input hybrid is a distinct, unverified compression-side mechanism with one runner. Its fixed-#427 projection is currently non-dominated, but that hybrid has no reliable family anchor; both the #432 matched projection and the #299 size-factor sensitivity are dominated in snapshot 28214. R4 itself warns that applying #427 across families falsely promotes #299. See [candidate manifest](../../candidates/r4-hybrid-h16-smallc299/manifest.json) and [R4 calibration notes](../../docs/rounds/round04.md). This is not a robust measured alternative. The separately gated H3R/#299 hybrid remains a historical public-gate result, not a stage2 or admission result.

The R4 `lazy9-prefilter` variant is another different mechanism, but its same-family projected point is now dominated by #481/#506/#507; its run was one runner and no accepted gate is recorded. Other #299 sampling variants only appear non-dominated under the rejected cross-family #427 transfer, while their #299 sensitivity/matched coordinates are dominated. The evidence is in [R4 selection.json](../round4/selection.json).

**Decision:** no robust unverified R3/R4 alternative is established for immediate R11 use. Directemit-wrap is the narrow fast-end lead for a proof-first review, but its same-run measurements do not show a gain over fast3. The apparently larger H16 hybrid share is calibration-sensitive. No candidate was changed or run in this review.

The machine-readable thresholds, projections, and evidence links are in [frontier-route-review.json](frontier-route-review.json). No historical public-to-formal transfer is treated as stage2 evidence, and no actual reward or chain acceptance is inferred.
