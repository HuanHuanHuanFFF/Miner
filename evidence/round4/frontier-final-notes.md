# Round 4 final frontier and calibration notes

Checked at the final refresh for this pass. Scope is fast3, H16d64, Hmode1i8, and sampleguard; M/N/O are not included and this is not an overall candidate selection. All coordinates below are conditional public geometry; none is an admission, private-stage2, or reward prediction.

## Frozen official snapshot

The read-only API snapshot is evidence/round4/frontier-24737/, snapshot 24737, computed at 2026-10-06T22:52:55.034003+00:00. The five Pareto pages contain 442 unique points; the five leaderboard pages contain 418 ranking rows. Both page sets use the same context and snapshot; both final cursors are null. The standard array for scripts/round4.py is pareto-pages.json.

SHA-256: pareto-pages.json: 88d205c2382fd0333f0f4b10c3dce07c6c5d21c0774d0f8873ac5aa28bec3da4; leaderboard-pages.json: 7351c9919af7f7255065b4f5d3e2f3edf3229a6eceaa5ad9611d2e9e8c36d787. The pinned scorer is commit a356bbff18b60c4527fbcc85d5a28ef9c20214e0, worktree SHA-256 294e0501c740087a3b328d04134074c5a08c3cfedc06b3affa63e108da12a70f. Replaying local-global-improvement-space-log on all 72 published frontier points sums to 1.0; maximum absolute error against published point weights is 6.94e-18. All 72 current frontier rows have score.payment_eligible=true; that flag does not establish that any reward was paid. API freshness is unknown.

Relative to snapshot 24650, this pass has no new or removed IDs, frontier membership changes, metric changes, or admission changes. The slow frontier coordinates and the fast endpoint are unchanged.

Current formal anchor metrics are:

| ID | Balanced time ratio | Mean file compression (%) | Admission / frontier |
| --- | ---: | ---: | --- |
| 299 | 9.176642755 | 34.102373220 | admitted; not frontier |
| 427 | 0.466143278 | 36.173282125 | dominated; not admitted |
| 432 | 0.441385057 | 36.912735156 | admitted; not frontier |

## J/K evidence and calibration scopes

J gate evidence is evidence/round4/37535056448/gate/gate-summary.json; K refine evidence is evidence/round4/37537479001/refine/refine-summary.json. Both runs used snapshot 24442. I recomputed their matched-anchor projections with the unchanged formal anchor metrics from snapshot 24737. J reports r4-parse-h16d64-core accepted on the public stage1 corpus (15,930,000 raw bytes; 4,870,451 output bytes; accepted=true). K is a refine result for Hmode1i8 and sampleguard, not a new formal competition gate.

The fixed-427 projection uses repository constants TIME_FACTOR=1.014402891250616 and SIZE_FACTOR=1.0070277985275755: multiply the measured public time and size by those factors. A matched anchor instead scales each candidate’s paired public measurements by the current formal anchor metrics. Sampleguard’s public299 anchor is a true same-family reference because it derives from #299. H has no formal H-family anchor: the own_anchor coordinates in J/K are a matched public432 control projection, not an H-family calibration. Treat them as cross-family sensitivity only.

| Candidate / evidence | Public-stage1 time, size (%) | Fixed 427: time, size (%) | Matched anchor: time, size (%) |
| --- | ---: | ---: | ---: |
| fast3, 12-runner equal-runner mean (selection.json) | 0.432746996, 36.602139106 | 0.438979804, 36.859371566 | #432 control hypothesis: 0.437764814, 36.991342624 |
| H16d64 core, J gate | 5.866798207, 33.874353293 | 5.951297063, 34.112415423 | #432 cross-family: 5.940100807, 34.234551297 |
| Hmode1i8, K refine | 5.608305944, 33.874432867 | 5.689081765, 34.112495557 | #432 cross-family: 5.682682670, 34.234631717 |
| sampleguard, K refine | 7.936404382, 33.843555302 | 8.050711552, 34.081400990 | #299 same-family: 7.950523481, 34.103103028 |

The raw public size values are stage1 measurements and are not the official full scoring axis. The coordinates in the last two columns are sensitivity projections against the current published anchors; they do not replace held-out testing.

Candidate hashes checked against the J/K specs: H16d64 parse.rs ba3c16422a5fc9432c41d80c0ad0ab5657605c1e020d14b7e1135e430ce3a7ee, Parse.lean 13f23fc46a6d18283aeb339f949cca102761133d6e1ff9b3a1007cd8b7926a46; Hmode1i8 parse.rs 87550e2af37eb409f6d23f5ee23ca70b6fc55ace6b28bca1b85db38929d99a79, Parse.lean ea44caf8730aa9dab5508cd49f8c3c9cf7277cfbba2c7084fe419670c723edc2; sampleguard parse.rs f7d57e4351b7e36dccdfe0aff9d0087422b960d61cdba4f812fea4591eef17eb, Parse.lean 9b77b3523cbf7044aaffa11b6fd9676b3615ca4bf148b43b3cb92da4073b3e3d.

## Slow-end size thresholds

For each time cap, the threshold is the smallest official frontier size among points at or faster than that cap. It is the size-best envelope under that cap, not a complete frontier-membership test: a faster point with a larger size can still be non-dominated. A point at the boundary’s time would need a strictly smaller size to improve that size-best envelope.

| Time cap | Limiting point | Official size threshold (%) |
| ---: | --- | ---: |
| 5.8 | #316 at 5.780248919 | 34.101907101 |
| 8.0 | #316 at 5.780248919 | 34.101907101 |
| 9.2 | #305 at 8.318555305 | 34.100976621 |

Size gap below means projected candidate size minus the threshold; positive values are a shortfall, negative values are size headroom.

| Projection | Current projected time / size (%) | Gap at the 5.8–8.0 threshold (pp) | Gap at the 9.2 threshold (pp) |
| --- | ---: | ---: | ---: |
| H16d64, fixed 427 | 5.951297 / 34.112415 | +0.010508 | +0.011439 |
| H16d64, cross-family #432 | 5.940101 / 34.234551 | +0.132644 | +0.133575 |
| Hmode1i8, fixed 427 | 5.689082 / 34.112496 | +0.010588 | +0.011519 |
| Hmode1i8, cross-family #432 | 5.682683 / 34.234632 | +0.132725 | +0.133655 |
| sampleguard, same-family #299 | 7.950523 / 34.103103 | +0.001196 | +0.002126 |
| sampleguard, fixed 427 | 8.050712 / 34.081401 | -0.020506 | -0.019576 |

At Hmode1i8’s present fixed time 5.689082, the more exact boundary is #396 at 5.183001 / 34.102497; its size shortfall is 0.009998 pp. If it slows to 5.8, the limiting point becomes #316 and the shortfall grows to 0.010588 pp. Sampleguard’s fixed projection is slightly slower than cap 8, but remains before #305 at 8.318555, so the #316 size threshold still applies. The same-family #299 projection is dominated by #316/#396; the fixed-427 projection is geometrically nondominated. That disagreement is calibration sensitivity, not an observed admission.

## Fast3 speed headroom

The earlier version of evidence/round4/selection.json aggregated 12 runner means across three CPU models, checked at 2026-10-06T22:50:46.846972+00:00 against snapshot 24650. Snapshot 24737 preserves the same frontier coordinates. For the matched #432-control projection, the equal-runner point is (0.437764814, 36.991342624); fixed 427 is (0.438979804, 36.859371566). At either size coordinate, the fastest existing frontier point no larger in size is #433 at 0.440208895 / 36.603956159.

Holding size fixed, nominal geometric time headroom to #433 is 0.5583% for the matched-control mean and 0.2800% for fixed 427. The report places 11 of 12 runner-mean matched points on the frontier; its slowest observed anchor block plus 1% is dominated by #425/#433. The J/K four-block results show the run sensitivity: matched #432 headroom ranges from 0.3095% (J) to 0.8545% (K), and fixed-427 headroom from 0.1208% (J) to 0.7408% (K). These are point-estimate geometry margins, not confidence bounds; a 1% speed regression exceeds all reported margins.

## Payment-field cross-check and remaining unknowns

Submission #215 is not an official frontier point in either snapshots 24650 or 24737. Its Pareto item says gate passed, admission passed, bounds eligible, score.on_frontier=false, score.payment_eligible=false, and score.unpaid_reason="deregistered". Recomputing a metric-only skyline from the 433 metric-bearing API rows also excludes #215. Its leaderboard row is rank 330 with submission ID 215, zero Pareto/improvement/combined/payable weights, and bounty_earned_alpha=4.155172151. The leaderboard row contains no miner_status, payment_eligible, or reason field; those values must not be inferred from that row. The 72/72 payment flags apply only to the current official frontier items, not to all miners and not to proof that any reward was paid.

UNKNOWN: current API freshness is unknown; private stage2 behavior and admission for these local candidates are unknown; H has no formal same-family anchor; the public projections do not establish online frontier membership or payable weight. The 12-runner fast3 margins are conditional geometry, not a promised speed budget.

## Read-only audit of scripts/select-round4.py

The script reads only published frontier points, replays the pinned scorer, and reports conditional geometry separately from accepted public-gate runs. Its matched time projection uses each runner’s candidate/anchor time delta against the official anchor ratio, then gives runners equal weight; its size projection rescales the candidate’s aggregate public size by the formal anchor size and the anchor’s public size. The fixed-427 projection applies the constants above. It marks H candidates as unknown_H_family and r4-hybrid candidates as unknown_hybrid_family; any #432 matched-control projection for them is not labeled a same-family anchor. Geometry is not admission: the script’s shortlist is explicitly research-only, and its own warning requires a separate evidence review.

Hash audit of the older and J/K proof-gate evidence:

- The J H16d64 gate’s saved input parse.rs and Parse.lean hashes match the J spec exactly; its stage1 gate record says accepted=true.
- K was initially audited from the refine receipt. The subsequently collected final gate receipt at `37537479001/gate/` confirms both Hmode1i8 and sampleguard accepted, with generated-input checks; the earlier absence of a gate in refine is not a failed or absent final gate.
- The manually retained fast3 gate run 37493517227 has no source/proof hashes in its small gate JSON. Its CI record pins head SHA bde76168028ad021295e1f41e1bee1c4f46398be; reading those two files from that commit reproduces the selected fast3 hashes exactly. The initial script relied on this external commit-tree check. The final script now also verifies the historical CI head, accepted gate JSON, and both Git-tree file hashes before retaining the old gate binding.
- scripts/summarize-round4.py groups Round 4 receipts by candidate name plus both parse.rs and Parse.lean hashes. When a gate record exists, it also checks the saved gate input files against the spec hashes before recording accepted_public_gate.

The 12-runner selection report was computed against snapshot 24650. The final snapshot 24737 comparison shows no frontier membership or metric changes from 24650, so its stated geometric coordinates remain applicable to this refresh. Its gate and private-corpus limitations still apply.

The central selection.json is regenerated as later receipts arrive. Its current runner count supersedes the historical 12-runner numerical example above; that example remains tied to its stated timestamp.


## Final refresh at 23:35 UTC

Snapshot 24830 (computed_at 2026-10-06T23:35:20.478745+00:00) has 444 Pareto items, 419 leaderboard rows and 72 frontier points. Newly admitted #443 (1.213514, 34.195086) replaces #351 in the middle-speed region; #444 is still running with no metrics. The fast and time>=3 boundaries used above remain unchanged. Fifteen snapshot-file hashes and the official scorer replay were verified. The current central selection report includes M/N/O public measurements: 15 runs and 56 new candidate versions; the historical examples above keep their original scope.
