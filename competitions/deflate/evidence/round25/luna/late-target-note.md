# R25 late target checkpoint

This is an investment checkpoint, not a candidate result or final recommendation. It separates official snapshot facts, a scorer-generated geometry grid, and measured source observations.

## Correction to the prior note

The previous version directly compared raw `public_time` / `public_size_pct` observations with the official frontier geometry. Those are not the same coordinate system. I withdraw the prior raw-based absolute gap figures and quality deficits. Raw measurements remain below only as runner-specific diagnostics. All absolute target comparisons below use `projected_time` / `projected_size_pct` from `analysis-late-29690.json`, replayed against snapshot 29690, with public595 primary and shadow calibration reported separately.

## Verified: official snapshot

The existing read-only capture script saved the full snapshot to `evidence/round25/official-target-late/`. Snapshot **29690** was computed at 2026-10-11 11:16:01Z and retrieved 11:18:25–11:18:41Z. API freshness is **unknown**. Its policy version, `compression-policy-c255effb7d5afeef`, matches snapshot 29687. `round25-frontier-map.py` replay validation reports `CAPTURE_POLICY_MATCHES_LOCAL_SCORER_INPUTS` (617 rows with bounds checked; 11 unscored rows without bounds); this does not establish deployed-validator identity.

Between snapshots 29687 and 29690, the Pareto list stayed at 628 IDs, while the leaderboard grew from 586 to 587 rows. Submission #628 changed from `running` / `awaiting-current-scoring-evidence` to `passed` and scored at frontier order 93: time ratio 5.8521312, mean compression 34.0914226%, payable weight 2.6827606%. #627 remains order 2 at (0.4305253341, 36.5215702164); its payable weight moved from 0.0902773% to 0.0905731% as weights were recomputed. #612 remains first at (0.4304598592, 36.5273012167); its payable share moved from 16.3285475% to 16.3820404% (+0.0534929 percentage points).

The capture receipt retains all original response bodies, per-page SHA-256 values, HTTP status, response date and request times. Representative current hashes are `competition.response.json` `28e0460e…bdf5fd7`, Pareto page 1 `b3484209…3267a350`, leaderboard page 1 `4a5869b8…a6b5ec`, and `receipt.json` `161ade2d…a78ac12`.

## Inferred: strict-first geometry from the saved map

The existing `scripts/round25-frontier-map.py` generated `evidence/round25/luna/target-map-late.json` against snapshot 29690; the script and candidate files were not modified. It labels its result `INFERRED_SCORING_GEOMETRY_NOT_IMPLEMENTED_PERFORMANCE`. The time grid advances in 0.00005 steps. It recomputes geometric allocations with existing frontier points, including unpaid points, and assumes a separate eligible candidate; it does not predict admission or payout.

| Mean-compression target | Sampled strict-geometric-first time-ratio interval | Relative interval width | Recomputed candidate-share range |
|---:|---:|---:|---:|
| 35.5% | 0.42860–0.43750 | 2.0765% | 15.74–46.97% |
| 36.0% | 0.42860–0.43045 | 0.4316% | 36.33–37.42% |
| 36.5% | 0.42860–0.43045 | 0.4316% | 21.18–27.99% |
| 36.55% | Not sampled exactly; the 36.54% and 36.60% rows happen to show 0.42860–0.43045 | 0.4316% at both sampled rows | 15.80–27.22% at 36.54%; 14.63–25.90% at 36.60% |

These are grid intervals, not continuous boundaries. The equal-looking 36.54% and 36.60% rows do not prove the exact interval at 36.55%. At 36.0% and 36.5%, the sampled upper edge 0.43045 is just below #612's 0.4304599. The wider 35.5% interval allows a slower time ratio, but requires substantially better compression.

## Observed: measured-source comparison

`analysis-all-29687.json` (SHA-256 `f2daffe5…bc9d3cf6`) reports six successful measured runs, 114 paired processes, nine candidate sources and 24 same-source control rows. I deduplicated observations by run, block and source/role; shadow aliases are not extra source samples. The time ratios below are raw `public_time` values. I keep runner models separate.

| Source and evidence role | Runner / unique blocks | Raw public coordinates (diagnostic only) | Evidence status |
|---|---|---|---|
| `r25-astra-end4`, Rust SHA `03ec0aa4…681ed8e6` | AMD EPYC 9V45, 2 candidate blocks in run 38124524718 | public size 36.1270506%; public time 0.4356844–0.4357202 | One exact Rust/Lean pair has a passed full gate. |
| `r25-astra-tiny-pc-sparse`, Rust SHA `84ccbcbe…9c294e5` | Intel Xeon 8370C, 2 candidate blocks in run 38132849624 | public size 36.1462188%; public time 0.4375501–0.4379986 | No exact pair is gate-verified in this analysis; its new gate is paused per the task brief. |

The root TinyPC Rust hash `5c20b99c…b891f00` appears in two different CI runs with the same reported Intel CPU model: two candidate blocks from screen-hi (0.4384319–0.4395803, proof `4ff09d16…a76c70a6`) and two control/alias blocks in the separately started screen-M run (0.442981–0.444130, proof `3bd53694…05ccdb8`). This is a same-Rust timing comparison, not an exact Rust/Lean-pair repeat; the roles and proofs differ. The 0.438432–0.444130 span is descriptive and must not be treated as a noise ceiling or four independent source confirmations.

For scale, the identical-binary `public595` / `public595-shadow` differences are kept by actual CI run, not pooled by CPU model. Each row below has two run-local block pairs. These are measured control gaps, not future noise bounds or extra independent candidates.

| CI run | Reported CPU model | Control gap, blocks 1 / 2 |
|---|---|---:|
| 38124524718 | AMD EPYC 9V45 96-Core Processor | -0.059844% / +0.057532% |
| 38126014186 | AMD EPYC 9V74 80-Core Processor | +0.404042% / -0.131117% |
| 38126675905 | AMD EPYC 7763 64-Core Processor | -0.067650% / +0.890772% |
| 38130275592 | Intel(R) Xeon(R) Platinum 8370C CPU @ 2.80GHz | +0.112350% / -0.278748% |
| 38130458692 | Intel(R) Xeon(R) Platinum 8370C CPU @ 2.80GHz | +0.340229% / -0.267059% |
| 38132849624 | Intel(R) Xeon(R) Platinum 8370C CPU @ 2.80GHz | -0.032360% / +0.217354% |

## Absolute target gap in projected coordinates

I re-ran the existing `scripts/analyze-round25.py` on the original six receipt folders with capture 29690. `analysis-late-29690.json` has snapshot 29690, policy `compression-policy-c255effb7d5afeef`, and status `VERIFIED_RAW_RECOMPUTATION_CONDITIONAL_PROJECTIONS`. The table below keeps all two measured blocks and both calibrations; it does not select the faster calibration or block. The nearby sampled strict-first edge is 0.43045 at 36.50%, 36.54%, and 36.60%. The exact projected quality values are off-grid, so these are gaps to the nearest sampled edge, not exact continuous boundaries.

| Candidate | Calibration | Projected quality | Projected time, block 1 / 2 | Gap to sampled edge 0.43045, block 1 / 2 |
|---|---|---:|---:|---:|
| End4 | Public595 primary | 36.5187975% | 0.434288906 / 0.435219179 | +0.892% / +1.108% |
| End4 | Public595 shadow | 36.5187975% | 0.434548957 / 0.434968933 | +0.952% / +1.050% |
| TinyPC sparse (M) | Public595 primary | 36.5381736% | 0.432961999 / 0.433892186 | +0.584% / +0.800% |
| TinyPC sparse (M) | Public595 shadow | 36.5381736% | 0.433102151 / 0.432951151 | +0.616% / +0.581% |

These projected quality values are the ones to compare with the quality axis. End4 is 0.01880 pp above the 36.5% target, 0.51880 pp above 36.0%, and 1.01880 pp above 35.5%. M is 0.03817 pp above 36.5%, 0.53817 pp above 36.0%, and 1.03817 pp above 35.5%. Both projected qualities are below 36.55%, but the exact 36.55% geometry was not directly sampled. If their projected times stayed unchanged after reaching 35.5%, they would be below that row's 0.4375 upper edge; the remaining quality improvement is about 1.02–1.04 pp, and no evidence shows that such a change would preserve these times.

The task brief reports that M is faster than I but remains 0.47–0.72% slower than `combo`; this note does not recompute that pairwise comparison. The raw public times and projected times above have distinct bases: the former remain runner-local diagnostics, while the latter use the current 595 primary/shadow calibration for target comparison. The absolute gap in the table is therefore not the same as M's task-brief lag to `combo`.

## Investment boundary

M's projected quality is near the 36.54% sampled row, but its projected time remains about 0.58–0.80% above that row's upper edge, depending on block and calibration. That is the current first-place gap in a common coordinate system. Reaching the 35.5% geometry instead needs about 1.02–1.04 pp further projected mean-compression improvement; the existing projected times fit under 0.4375, but no source observation establishes that additional quality can be gained without changing speed. End4 has a completed exact gate, while its projected time remains about 0.89–1.11% above the nearby sampled upper edge. This identifies the gap to test or stop against; it is not a claim about success probability.

**Unknown:** future same-source timing; how further quality changes affect speed; cross-runner transfer; any exact M gate result after the pause; private or held-out results; and actual payable share for an unsubmitted candidate. Neither the scorer grid nor the observed worst range is a probability estimate or a future noise bound.

Evidence hashes: capture receipt SHA-256 `161ade2d2830bac4dd495e05beb5c60257a9751a9bdcad55c231ec179a78ac12`; target map SHA-256 `07148b875d7ebecb22da31164011f3958384af7536c2001eb75c70f1c1eb7704`; reprojected analysis SHA-256 `1aac42ed349c5fb75938654cb92433a54ad946f0c8e8f92bf1110d2a8f5831fb`; scorer SHA-256 `486f9b425ef6fc0bfae2fdc9eb2f342de9c40efcae3b41bf14ced18128b571dd`.
