# R24 dot-cost full paired comparison

**Scope:** exploratory synthetic runtime-cost comparison only. This is not an official score, correctness proof, adoption result, or success probability.

- Run `40804860824`, artifact `12867428299`: all 256/256 file hashes and byte counts matched (33,254,405 bytes).
- Both bodies are complete: 32 runs, 16 paired records, 4,704 raw ns values, 49 cases × 3 samples per run. Both retained all cases; the JSON includes all per-case ratios and every ratio >1 regression.
- Fixture SHA-256 `f49020bba646e73531940af6b7fa32cd8ad76b05177146dcddf2f95e6642e74b` matched in both body preparations. Both ran on AMD EPYC 9V45 96-Core Processor pinned to CPU 0. Raw `/proc/cpuinfo` hashes differ because MHz fields vary; stable model/family/stepping/flags match.
- Control identity checks pass: official source maps and the `MainFull.c` source-fragment hash match; all four pre-build snapshot differences are candidate-derived (`Submission.c`, its export object, and `benchFull` plus trace). Shared owned harness/barrier/fixture files match; both within-body flag and six-caller audits pass.
- Both native finite-check receipts passed 148 dots, 1,049 word rounds, 86 known fast cases / 51 known accepts; both `originals_unchanged` flags are true. Each body also passed six typed two-argument adapter checks with barrier and adapter calls inside the native-loop backedge. Cost-body correctness remains **UNPROVED**. Math35 helper audit: `ABSENT`; expected 31 helpers + 4 old roots are not verified from this artifact.
- The CI receipt is completed/failure; the runtime-cost diagnostics themselves are complete. The broader gate failure is separately attributed to Math7's two remaining `Int` casts, not these measurements.

## Within-body paired sum-time ratios

Each ratio is sum of variant medians / sum of exact-control medians across all 49 cases; lower than 1 is faster in this pilot. Four values are the two matched ABBA repetitions across both groups.

| Body | Boundary | Variant | All 49 ratios (4 pairs) | Range | Narrow long (n≥32) range | Moderate long (n≥32) range |
|---|---|---|---|---:|---:|---:|
| original | full | eager | 1.080286, 1.072650, 1.074616, 1.056370 | 1.056370–1.080286 | 1.186823–1.247918 | 0.358829–0.378634 |
| original | full | lazy | 0.726189, 0.716367, 0.781763, 0.795174 | 0.716367–0.795174 | 0.268813–0.282837 | 0.079645–0.085067 |
| original | prepared | eager | 0.672293, 0.699986, 0.746857, 0.729503 | 0.672293–0.746857 | 1.919582–2.140679 | 0.049968–0.052980 |
| original | prepared | lazy | 1.121926, 1.124846, 1.182160, 1.188037 | 1.121926–1.188037 | 2.003624–2.285340 | 0.051256–0.054348 |
| tail | full | eager | 1.007685, 1.014881, 1.034128, 1.033001 | 1.007685–1.034128 | 1.130761–1.185060 | 0.335575–0.359748 |
| tail | full | lazy | 0.694878, 0.671270, 0.724660, 0.721959 | 0.671270–0.724660 | 0.172830–0.182463 | 0.051826–0.055690 |
| tail | prepared | eager | 0.609095, 0.595228, 0.687456, 0.651795 | 0.595228–0.687456 | 0.323936–0.352367 | 0.008424–0.008943 |
| tail | prepared | lazy | 1.026000, 1.095173, 1.083775, 1.082764 | 1.026000–1.095173 | 0.322561–0.347314 | 0.008142–0.008628 |

## Direct tail / original frontend ratios

These match the same group, boundary, order, and case between bodies; lower than 1 means the tail frontend was faster for that matched run.

| Boundary | Variant | Matched-run ratios | Range |
|---|---|---|---:|
| full | exact | 1.035076, 1.025586, 1.024738, 1.025254, 1.016523, 1.005144, 1.010158, 0.997363 | 0.997363–1.035076 |
| full | eager | 0.965513, 0.970351, 0.978224, 0.982908 | 0.965513–0.982908 |
| full | lazy | 0.980554, 0.960713, 0.936372, 0.905531 | 0.905531–0.980554 |
| prepared | exact | 0.989132, 1.014985, 1.002150, 1.000336, 0.987411, 1.011203, 1.010434, 1.010146 | 0.987411–1.014985 |
| prepared | eager | 0.896150, 0.863085, 0.908878, 0.903488 | 0.863085–0.908878 |
| prepared | lazy | 0.916465, 0.973947, 0.926341, 0.920636 | 0.916465–0.973947 |

## Worst per-case regressions

For each body/boundary/variant, this lists the largest per-case variant/control ratio among the four paired records. Every individual regression remains in `full-408048-comparison.json`.

| Body | Boundary | Variant | Regression count across 4 pairs | Worst case | Ratio |
|---|---|---|---:|---|---:|
| original | full | eager | 164 | s24282403-wide-n1 (wide, n=1) | 1.839083 |
| original | full | lazy | 79 | overflow-product (overflow-product, n=1) | 1.755551 |
| original | prepared | eager | 122 | cancel (cancel, n=2) | 2.888916 |
| original | prepared | lazy | 127 | plus-zero (plus-zero, n=2) | 16.266204 |
| tail | full | eager | 164 | s24282403-wide-n1 (wide, n=1) | 1.698391 |
| tail | full | lazy | 82 | s24282405-wide-n1 (wide, n=1) | 1.676310 |
| tail | prepared | eager | 71 | s24282405-wide-n1 (wide, n=1) | 1.944931 |
| tail | prepared | lazy | 82 | huge-cancel (huge-cancel, n=2) | 13.802263 |

The pair records also contain per-kind sums, all n<32/n≥32 rollups, narrow/moderate/wide long-normal summaries, and all best/worst cases. The workflow receipt is completed/failure; the run summary attributes the failure to Math7's two remaining `Int` casts, separate from these completed cost diagnostics. No official target, proof, adoption, champion-gain, or probability conclusion follows.
