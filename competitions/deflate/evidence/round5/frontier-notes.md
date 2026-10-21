# Round 5 frontier refresh and old-candidate shortlist

## Official snapshot

At `2026-10-07T14:10:41.852363+08:00`, the official competition endpoint reported snapshot `25678`, policy `compression-policy-c255effb7d5afeef`, status `ready`, and freshness `unknown`. The freshness reason is preserved exactly as returned: `Recorded scoring pass; live policy changes require a new pass.` All retrievals used this explicit snapshot ID. Every Pareto and leaderboard page, plus the details for submissions 453, 432, and 299, has the same snapshot ID, `computed_at`, policy version, status, freshness, and freshness reason.

The complete Pareto response is in [pareto-pages.json](frontier-25678/pareto-pages.json): 5 pages, 454 unique items, and no next cursor. The complete per-hotkey leaderboard is in [leaderboard-pages.json](frontier-25678/leaderboard-pages.json): 5 pages, 430 unique ranks, and no next cursor. The original competition response and refreshed submission details are in the same [frontier-25678 directory](frontier-25678/).

Submission #453 is confirmed as the requested fast3 source: SHA256 `bae8014121e4710f4a34ce63452578b4bf69121b4f695e1b1356780a019108ef`. Its current official record is gate `passed`, admission `recorded/passed`, metrics `(0.43787345819892, 36.999728556810254%)`, `on_frontier=true`, `payment_eligible=true`, and `payable_weight=0.005035502557086433`. This is a current record for #453; it says nothing about admission or reward for an unsubmitted candidate.

## Scorer replay

I loaded `sources/conjectures-optimisation-deflate/validator/scoring/pareto.py` through `scripts/round4.load_scorer` and applied `local_global_improvement_space_log_weights` to the 75 published frontier points. The maximum absolute difference from the published `pareto_weight` values is `6.938893903907228e-18`, and the replayed weights sum to `1.0`. #453 replays to its published weight exactly at displayed precision.

The shortlist's candidate coordinates and conditional weights are **INFERRED** transfers of prior public-run measurements onto an official same-family anchor, followed by insertion into this snapshot's Pareto frontier and rescoring with the official pure scorer. They are geometry diagnostics only; they are not private stage2 measurements, official admission tests, online ranks, or reward predictions. Full source and proof hashes, gate links, calculations, and sample notes are in [old-candidate-shortlist.json](old-candidate-shortlist.json).

## Shortlist

| Priority | Candidate | Anchor | Transferred point `(time, size%)` | Conditional weight | Evidence and main limit |
| --- | --- | --- | ---: | ---: | --- |
| 1 | `r4-cpu-run1tai` | #453 fast3 | `(0.43743567, 36.99972856)` | 0.00587 | Two successful gates, but runner deltas span -0.277% to +0.077%; same-runner CPU comparison is useful. |
| 2 | `r4-cpu-flushzero` | #453 fast3 | `(0.43697584, 36.99972856)` | 0.00677 | One successful gate and one cancelled run with measurements; deltas span -0.621% to +0.211%. |
| 3 | `r4-parse-lazy4far` | #453 fast3 | `(0.43865845, 36.97454845)` | 0.00190 | One successful runner; about 0.179% slower with a small public-size improvement. |
| 4 | `r3-432-dmin257` | #432 | `(0.43974952, 36.91438746)` | 0.00330 | One successful four-block runner; previous +1% slower stress test left the frontier. |
| 5 | `r3-432-tshift3` | #432 | `(0.44019494, 36.92742969)` | 0.00125 | One successful four-block runner; public-file bootstrap lower 5% speed gain was -0.012%. |

The fast3-derived CPU candidates are calibrated from #453. Their public outputs matched fast3 on the finite public corpus; that does not prove all-input equivalence. `lazy4far` changes outputs on a narrow public input subset and has only one runner. The round3 candidates derive from #432, so their transfer uses #432's current official metrics and the earlier #432-relative measurements, not #453. Both have only one four-block runner. `dmin257` looks more promising than `tshift3` in the old same-run analysis; `tshift3` remains in the five only as the lower-cost same-stage comparison selected by the parent thread.

Timing estimates below one percent remain noise-sensitive. `run1tai` and `flushzero` both reverse sign across runs; `lazy4far` has no independent rerun; the round3 bootstrap intervals resample public files only and do not include runner, private-corpus, or selection uncertainty. The CPU candidates therefore need a fresh paired runner with fast3-shadow and same-process control before their small speed differences are treated as repeatable.

## Anchor boundaries and correction

The refreshed details for #432 and #299 are saved beside #453. #432's current point is `(0.4413850574969763, 36.91273515631194%)`; #299's is `(9.176642754907775, 34.10237321953839%)`. Neither is on this snapshot's frontier.

I excluded `r4-alt299-tinydepth32` after correcting its size transfer. Its public size equals the `public299` control, so its same-family transfer must preserve #299's official size `34.10237321953839%`; the earlier `33.84283105%` estimate incorrectly used an absolute public percentage as the formal coordinate. At corrected one-run inferred coordinates `(9.08055080, 34.10237322%)`, the official scorer says it is not on snapshot 25678's frontier. Its source SHA is `ca41b676a56eb31607199e941893a03466dc5c5e74823d1630449ed2f3384863`, proof SHA `9b77b3523cbf7044aaffa11b6fd9676b3615ca4bf148b43b3cb92da4073b3e3d`, and prior successful gate is [37535056448](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/37535056448). It is not prioritized for an independent runner.

No #453 transfer is used for H candidates. Their review must retain a true #299-family reference and report #427 and #299 only as separate sensitivity cases. Fresh private stage2 behavior, candidate admission, and future snapshot position remain **UNKNOWN**. This task did not start a CI run or perform a competition submission.