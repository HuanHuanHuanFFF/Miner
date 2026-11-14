# Minimum verification handoff for Droot

All current official bytes were read from Droot's saved R27 state. No API request was repeated. The official interfaces evidenced by the saved receipts are:
- Current champion rows: /v1/competitions/torchlean/champions?board=<board>
- Hash-bound submission evaluation reports: /v1/competitions/torchlean/submissions/<submission>/report
- Available historical source bytes: /v1/competitions/torchlean/submissions/<submission>/source

## Latest official snapshot (2026-10-29 21:51–21:54 UTC)

The latest saved `boards-2150.raw` publication is `a8167e48…f312f21`. The matching normalized-MLP champion response makes #43/promotion28 the current champion; its source remains unavailable. The #43 official report binds the source hash and directly references public #23 (hash `1010c074…df0665fe`), whose source bytes are saved locally under the LOCAL_ONLY receipt. The report uses the new official head `27fb1d19c712ead50ad34b4ad0d4ba597161e616` and config hash `647ef0dc…bbd95a`.

Droot also saved a mixer champion response (#36) for the same publication. No matching current champion responses were saved for overall, MLP, ResNet or MobileNet, so their latest current identities are UNKNOWN; older bound rows remain in `champion-only-record.json` as history. The 21:29 mixer response that was previously unbound became usable after `boards-2150.raw` arrived.

The benchmark version changed between head `accb82b6e2adeda1b41a57a260d68fb3879c427e` and head `27fb1d19c712ead50ad34b4ad0d4ba597161e616`. The official comparison lists only `validator/benchmark.py` and its budget tests, so the exact R27 full-gate proof for guard26-v2 remains valid; its performance comparison crosses benchmark identities. Public #23 is the usable current-head calibration carrier. A replay now reconstructs the new report policy from the current official head, B4 helper-run identities, and all six live board hashes; the report still omits its identity, so conversion is INFERRED and requires a candidate row matching every current input and both production runs. See [review-current43-version-and-chain.md](review-current43-version-and-chain.md).

The historical guard26-v2 screen maps to `1.136801409x current #43 time`, INFERRED across benchmark versions, environments and seeds; it is not a current-champion win. The B3 candidate measurement remains the original local quick sample. Show current-champion multipliers in any human performance summary; keep the underlying scorer ratios in the audit record.

## Initial R27 snapshot at 19:49 UTC (historical)

At this capture all six champion rows said `source_available=false`: overall #18/submission 8, MLP #26/submission 33, mixer #27/submission 36, ResNet #20/submission 11, MobileNet #16/submission 7, and normalized MLP #24/submission 23. Those rows and factors below were bound to the initial `boards.raw` publication only. They must not override a newer board response or be presented as the latest normalized-MLP champion.

## Historical report-chain conversion (initial snapshot only)

The factors below belong only to the 19:49 initial publication snapshot. Do not use them as latest current-board state after the #43 promotion. For that historical snapshot, let A be the exact source hash chosen as the candidate run's reference. The conversion was:

candidate_time / current_champion_time
= (candidate_time / A_time) * (A_time / current_champion_time)

The recorded A_time/current_champion_time factors are:

| Board | Current champion | Reference source | A time / champion time | Report config hash |
|---|---:|---:|---:|---|
| overall | #18 / sub 8 | sub 5, bc580a4c… | 1.082958767462 | 04df6f67… |
| mlp | #26 / sub 33 | sub 13, b3104321… | 1.591448604762 | 6fe1d4ff… |
| mixer | #27 / sub 36 | sub 27, f92ee2c9… | 1.039265349893 | ab0fdb55… |
| resnet | #20 / sub 11 | sub 5, bc580a4c… | 1.205126061278 | 8339be07… |
| mobilenet | #16 / sub 7 | sub 5, bc580a4c… | 1.255779062372 | 7d260156… |
| normalized_mlp | #24 / sub 23 | sub 12, e2c1f1f1… | 1.044308182792 | 2597459e… |

ResNet uses two verified report edges: current sub 11 to retired sub 7 at 0.9414568929566234, then sub 7 to source-available sub 5 at 0.8813878961371248. Their product is current champion time / sub 5 time = 0.8297887101868325.

These are INFERRED cross-environment multipliers, not same-run candidate/current-champion pairs. The six current boards.raw config hashes differ from the current champion report config hashes. Use the conversion only when the candidate/reference result has the exact report config hash listed above. If the R27 run uses the live boards.raw config hash instead, set the current-champion comparison to UNKNOWN; no current source bytes are available to create a direct pair.

Reference source bytes and receipts are stored under the ignored source-private folder, with local-only publication policy pending review. Do not copy or publish those full sources as part of verification. The record stores their hashes and receipt metadata.

## Fixed scorer interface

Use R26 verification/analyze-native-only.py and the original pinned R25 scoring.py after source-byte verification. The companion champion-multiplier.py only converts a fixed scorer's per-board candidate/reference ratio into candidate_time_over_current_champion_time. It does not score raw timings or prove correctness.

Its input row must bind the current promotion ID, current champion source hash, champion-response hash, current champion report hash, board ID, report config hash, candidate/reference source hashes, and pinned-scorer ratio. Missing or mismatched state becomes UNKNOWN. The display multiplier below 1 means candidate time is below current champion time; above 1 means slower. NativeOnly remains diagnostic and never proves candidate correctness or official promotion.

## Historical winner-report measurement inputs (initial snapshot)

These inputs come from the initial publication's successful official evaluation rows. The official report uses 11 rounds, inner 3, and 50 ms per cell. Use the exact report config hash, seed, and rows when deriving an inferred multiplier. R26 and B3 5-round/2-ms quick cohorts are not comparable to these reports.

| Board | Current report seed | Cells | per-environment entries | benchmark seconds |
|---|---:|---:|---:|---:|
| overall | 2327529241 | 30 | 180 | 1200 |
| mlp | 2777525764 | 6 | 36 | 360 |
| mixer | 1593160531 | 6 | 36 | 360 |
| resnet | 1198852529 | 6 | 36 | 360 |
| mobilenet | 1208908567 | 6 | 36 | 360 |
| normalized_mlp | 3542272469 | 6 | 36 | 360 |

Each report has production amd64 and arm64 entries with the same board seed. The three workload names are wide, normal and sparse. A candidate run on one runner cannot become a same-run mixed-production result; the report-chain conversion stays INFERRED. Keep full paired input rows, all timing/checksum values, CPU identity, and alternating order.

## Current #43 report input

| Board | Current champion | Calibration source | Seed | Cells | Per-environment entries | Benchmark seconds | Report config hash |
|---|---|---|---:|---:|---:|---:|---|
| normalized_mlp | #28 / sub 43 | sub 23, `1010c074…` | 1300210886 | 6 | 36 | 360 | `647ef0dc…` |

The current report records both production identities, 11 rounds, inner 3, 50 ms/cell, six workloads, and a six-cell model. Its config hash matches the latest boards response. The official report omits `benchmark_identity` and `proof_identity`; the pinned plan replay and B4 helper audit reconstruct them as INFERRED (`6df065ba…f3faa5cd` and `3a69968c…77bee6`). Source #43 remains unavailable; source #23 is saved under its LOCAL_ONLY receipt.

Before claiming any multiplier, verify the runner's candidate and anchor rows use the same report config hash and exact board seed/workloads/time limits above. Recheck current champion IDs against the latest official response at the measurement checkpoint; the timestamped response hashes in champion-only-record.json bind this initial comparison. If a current ID/hash/report changes, regenerate the record from Droot's saved original bytes before converting.

The only extracted predecessor source bytes are in the ignored local-only directory and are not part of these verification outputs. Their official source endpoint and hash receipts support identity only; source use or publication still follows the separate license-policy gate.

Each board uses its own report-chain anchor hash, so a multi-board input must place reference_sha256 on each board_results row (with candidate_time_over_reference_time and report config hash). Do not use one top-level reference hash for all boards. Candidate hash may also be row-specific.

The converter input must include pinned_scorer with config.py, multiseed.py and scoring.py Git blob IDs plus SHA-256 values from champion-only-record.json. Each board_results row must carry its candidate/reference SHA-256, board config hash, fixed-scorer candidate/reference ratio, current_promotion_id, current_champion_source_sha256, champion_response_sha256 and current_champion_report_sha256. The converter returns UNKNOWN when any scorer source or snapshot identity is absent or mismatched.

## Configuration identity reconciliation

For the initial snapshot, pinned `Config.plan()` hashes include `initial_reference`; the saved policy replay reconstructed all six initial report hashes and environment-resolved timing. The latest #43 report uses the new official benchmark head and a config hash equal to the latest board hash. The report summary omits `benchmark_identity` and `proof_identity`, but the pinned plan replay plus B4 helper audit reproduce the live policy hash; the conversion is INFERRED, not verified.

For a future current #43 comparison, use public #23 as the candidate/reference source and measure under official head `27fb1d19c712ead50ad34b4ad0d4ba597161e616`, with the exact inputs and run contracts in `current43-report-chain.json`. The fixed converter returns an INFERRED multiplier only if the candidate row matches benchmark/proof identity, report config, report seed, cells, workloads, timing, both production identities, weights, and complete runs. A shorter or local-only NativeOnly cohort remains UNKNOWN. A plan pinned to the older `accb82b6e2adeda1b41a57a260d68fb3879c427e` or the #12 anchor cannot use the current #43 edge.

## Current mixer #36 status

The latest saved mixer champion is #36, source unavailable. Its official report edge to public #27 has score `0.9622181669992014` under historical config `ab0fdb552d44b82ee286607a8ad0d914b6426615853ea3fe255878208a744f0e`, while the current mixer board config is `4a9278fefa8f3799173bf1dfec50c7ea02819d3e312c819e267ecfeb89b5dbf9`. The benchmark identity changed. Keep mixer calibration UNKNOWN until a current-identity #36/#27 report is saved or the current #36 source permits a direct pair. B5's public #27 carrier is not the current champion.
