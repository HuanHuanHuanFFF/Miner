# Round 5 frontier refresh — snapshot 25803

## Snapshot and source

The official `GET /v1/competitions/deflate` response selected snapshot `25803`, computed at `2026-10-07T15:09:58.649118+08:00`, policy `compression-policy-c255effb7d5afeef`. Its scoring context reports `status=ready`, `freshness=unknown`, and `freshness_reason=Recorded scoring pass; live policy changes require a new pass.` I fetched every page with explicit `snapshot_id=25803` and retained the context unchanged.

The full Pareto response is in [pareto-pages.json](frontier-refresh/pareto-pages.json): 5 pages, 455 unique points, terminal cursor null. The full leaderboard is in [leaderboard-pages.json](frontier-refresh/leaderboard-pages.json): 5 pages, 431 unique ranks, terminal cursor null. Every page and the official details for #453, #432, #299, and #427 has the same snapshot ID, computed time, policy, status, freshness, and freshness reason. The competition index and details are saved in [frontier-refresh](frontier-refresh/).

Sources: [competition](https://conjectures.io/v1/competitions/deflate), [Pareto pages](https://conjectures.io/v1/competitions/deflate/pareto?limit=100&snapshot_id=25803), [leaderboard pages](https://conjectures.io/v1/competitions/deflate/leaderboard?limit=100&snapshot_id=25803), [#453 detail](https://conjectures.io/v1/competitions/deflate/submissions/453?snapshot_id=25803), and [current weights](https://conjectures.io/v1/competitions/deflate/weights/current?snapshot_id=25803).

## #453: published score versus accepted chain weights

**VERIFIED from the official scoring snapshot:** #453 still has a positive payable score. Its source SHA is `bae8014121e4710f4a34ce63452578b4bf69121b4f695e1b1356780a019108ef`; gate is `passed`; admission is `recorded/passed` with `speed-advantage-established` against #433. Its official point is `(0.43787345819892, 36.999728556810254%)`, `on_frontier=true`, `payment_eligible=true`, and `payable_weight=0.0050170871052243535` (about 0.5017%). Its hotkey is rank 52 with the same payable weight. Rank is unchanged from snapshot 25678; payable weight decreased slightly from `0.005035502557086433`.

I replayed `local_global_improvement_space_log_weights` from `sources/conjectures-optimisation-deflate/validator/scoring/pareto.py`, loaded through `scripts/round4.load_scorer`. The replay covers 76 published frontier points; maximum absolute weight error is `6.938893903907228e-18`.

The separate `weights/current` response is saved as [weights-current.json](frontier-refresh/weights-current.json). It has the same snapshot ID, computed time, and policy, but its own freshness is `stale`, with reason `Submission membership or selected evidence changed after this pass.` The map includes #453's hotkey at `0.0050170871052243535`, while `chain_accepted=false`. Therefore the official leaderboard shows a positive payable score, while this response does not confirm that the vector was accepted on chain. Neither response confirms a reward payment.

A control-row `summary.on_frontier=false` must not be read as #453 losing eligibility. The exact fast3 control maps to #453's existing point; when I add that point under a new control label, the pure scorer drops the duplicate label and retains official #453 in the frontier. The API itself also explicitly reports #453 `on_frontier=true` with positive weight.

## Old candidates remapped with the new four-block run

The new paired run is [37582344420](37582344420/old-speed-replication-a/gate/analysis.json). I used its four per-block time deltas against the fast3 control and size ratio to map each point onto the current official #453 coordinates, then inserted the hypothetical point into snapshot 25803's official frontier and reran the pure scorer. These are **INFERRED public-stage1 transfers**, not new submissions, admission results, or payment predictions.

| Candidate | Mean paired time change vs fast3 | Mapped point `(time, size%)` | Result on snapshot 25803 | Main dominator |
| --- | ---: | ---: | --- | --- |
| `r4-cpu-run1tai` | +0.2816% | `(0.43910632, 36.99972856)` | Off frontier; conditional weight 0 | #453 |
| `r4-cpu-flushzero` | +0.3430% | `(0.43937516, 36.99972856)` | Off frontier; conditional weight 0 | #453 |
| `r4-parse-lazy4far` | +0.5510% | `(0.44028600, 36.97454845)` | Off frontier; conditional weight 0 | #433 |
| `r3-432-dmin257` | +0.8986% | `(0.44180805, 36.92275595)` | Off frontier; conditional weight 0 | #433 |
| `r3-432-tshift3` | +0.9944% | `(0.44222783, 36.93580113)` | Off frontier; conditional weight 0 | #433 |

The two CPU candidates retained fast3's public size. `run1tai` averaged 0.2816% slower with mixed per-block signs; `flushzero` averaged 0.3430% slower and was slower in all four blocks. The other three improved public size but their slower mapped times leave them dominated by #433. Thus the five old-candidate mapping conclusion is unchanged: none enters the current frontier.

## Two new mechanisms

The fresh two-block measurement is [37582348267](37582348267/new-mechanisms-a/gate/analysis.json). I recomputed both saved gate states with `scripts/round4.summarize` and the complete snapshot 25803 pages. Coordinates use its matched-block mean formula: `formal_time × mean_b(candidate_time_b / paired_anchor_time_b)`; size uses `formal_size × (candidate_public_size / paired_anchor_public_size)`. This is not the ratio of aggregate means, which explains the small coordinate correction. These coordinates are **INFERRED** transfers; two public blocks do not establish runner stability or online admission.

- `r5-opt-a-best299` had a matched-block mean time ratio 3.38448% slower and public size `0.010447` points larger than the same-run `public299` control. `round4.summarize` maps it through the true #299 anchor to `(9.487224244880458, 34.11290028294168%)`; it remains off frontier, dominated by the current frontier (including #305 and #316). The no-gain conclusion is unchanged.
- `r5-opt-small-select` had a matched-block mean time ratio 11.15905% faster than `public299`, with size worse by `0.012721` points. It is nevertheless 8.23568% slower than the same-run `r4-hybrid-h3r-smallc299` control at identical public size. `round4.summarize` maps it through #299 to `(8.152616229136308, 34.11519168590491%)`, still off frontier. The separate #427 sensitivity maps to `(8.243824709912985, 34.093481955464476%)`, with conditional geometric weight `0.000812978366` if that transfer held. This is only a sensitivity: current #427 is itself off frontier and has `payment_eligible=false` / `unpaid_reason=admission-dominated`. It does not show an improvement over the H3r control or establish admission.

The refreshed #299 point is `(9.176642754907775, 34.10237321953839%)` and is off frontier. The refreshed #427 point is `(0.46614327772931885, 36.173282125166494%)` and is also off frontier. H candidates therefore remain separate #299-family and #427-sensitivity cases; I did not transfer them from #453.

## Evidence boundary

**VERIFIED:** current API page counts and context; #453's current score, admission, leaderboard rank, and weight-map response; pure-scorer replay; paired public measurements in the two saved gate analyses.

**INFERRED:** all candidate coordinates and hypothetical frontier weights, because they transfer public measurements to official points. The #427 comparison is explicitly a sensitivity case.

**UNKNOWN:** future scoring snapshots, candidate private-stage2 results, future candidate admission, and actual reward payment. This refresh did not start CI or modify candidate, script, prior-snapshot, or Git files.