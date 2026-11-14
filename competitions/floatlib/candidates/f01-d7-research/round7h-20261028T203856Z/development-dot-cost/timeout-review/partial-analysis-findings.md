# R24 dot-cost first-group partial analysis

**Scope:** exploratory synthetic runtime-cost evidence only. No official score, correctness proof, adoption, or probability claim.

- Parent artifact #12866686423: all **119/119** files matched original SHA-256 and byte-count records; no missing or extra files.
- Frozen fixture SHA-256 `f49020bba646e73531940af6b7fa32cd8ad76b05177146dcddf2f95e6642e74b` matches the candidate manifest component. It defines **49 timed cases** for this seed plus directed cases.
- First group `24282403`: **16 complete runs** (8 full, 8 prepared), each with 49 cases × 3 raw ns samples. All `2,352` first-group sample values were included; no slow-case filter. All 18 stored row files (including two unpaired second-group files) matched `result.json`.
- Second group `24282405` has only full orders 0/1 (exact/eager); it is incomplete and excluded from paired ratios.
- Source index cross-check: `development-jobs.json` and `development-dot-cost-first-result.json` agree on `FAILURE_COLLECTED_OUTER120_TIMEOUT_PARTIAL18PROCESSES`, 18 completed processes, 119 files, and 15,208,417 uncompressed bytes. The CI receipt is completed/failure at the indexed commit.
- Pairing follows the frozen parser: exact 0→eager 1, exact 3→eager 2, exact 4→lazy 5, exact 7→lazy 6, separately for full and prepared.

## All 49 cases: paired sum-time ratios

Ratio is sum of variant case medians / sum of exact control case medians; below 1 is faster for this pilot. Each cell shows pair 1 / pair 2.

| Boundary | Variant | All-49 ratio of sums | Sum of per-case ratios |
|---|---|---:|---:|
| full | eager | 0.781862 / 1.045448 | 51.4474 / 56.6957 |
| full | lazy | 0.996616 / 0.845727 | 43.9457 / 39.7464 |
| prepared | eager | 0.983964 / 0.684615 | 67.0170 / 60.1232 |
| prepared | lazy | 1.460794 / 0.929373 | 146.0611 / 133.9892 |

## Long normal cases (`n ≥ 32`)

Each cell gives narrow / moderate / wide ratio-of-summed medians; pair 1 / pair 2.

| Boundary | Variant | Narrow | Moderate | Wide |
|---|---|---:|---:|---:|
| full | eager | 1.268825 / 1.230556 | 0.239608 / 0.376714 | 0.690851 / 1.087089 |
| full | lazy | 0.272417 / 0.311582 | 0.083476 / 0.096851 | 1.621855 / 1.075648 |
| prepared | eager | 2.132876 / 2.127627 | 0.050376 / 0.050387 | 1.672118 / 1.054511 |
| prepared | lazy | 2.149993 / 2.065642 | 0.050636 / 0.028984 | 2.035727 / 1.239585 |

## Per-case extremes across all 49 cases

Ratios are variant/control per-case medians; best is the smallest ratio and worst the largest. Pair 1 / pair 2.

| Boundary | Variant | Best case | Worst case |
|---|---|---|---|
| full | eager | s24282403-moderate-n512 (0.199014) / s24282403-moderate-n1024 (0.318926) | s24282403-wide-n1 (1.642882) / s24282403-wide-n1 (1.741308) |
| full | lazy | s24282403-moderate-n1024 (0.068657) / s24282403-moderate-n1024 (0.069774) | half-ulp-even-tie (2.344321) / s24282403-wide-n1 (2.508439) |
| prepared | eager | s24282403-moderate-n1024 (0.040124) / s24282403-moderate-n512 (0.040810) | huge-cancel (2.448877) / plus-zero (2.485304) |
| prepared | lazy | s24282403-moderate-n1024 (0.041281) / s24282403-moderate-n1024 (0.023452) | cancel (14.600201) / huge-cancel (14.598148) |

## Completion and gate boundary

- Build exit 0; compile/link records show no removed files, response shows only `R24DotBarrier.c.o.export` removed, and arguments match after root mapping in all three records. Actual caller audit: 6/6 records passed.
- Finite native check exit 0: 148 dot cases and 1049 word-round cases; all recorded acceptance/miss checks matched. This remains finite checking, not an all-input proof.
- The runtime result is `complete: False`; stage receipt is `RUNNING`, candidate verdict is `diagnostic-timeout`, and formal adoption/full gate are false. Final provenance checks are not recorded.
- The source index marks outer120 timeout/partial18 and `full_final_provenance: NOT_EXECUTED_AFTER_EXTERNALKILL`. The exact nested candidate index records `diagnostic-only replay process group timed out at 120s` at 120.004 seconds. Its missing R24-specific timeout metadata is expected from the pre-fix source; the outer suite wrapper separately reports 191.459 seconds / exit 1.
- Correction retained: an earlier lookup read only the outer suite wrapper and left stop attribution UNKNOWN. The nested candidate receipt resolves the 120-second cutoff; no upstream raw evidence was changed.
- The 590-second-monitor rerun remains planning only.

Detailed per-pair, per-kind, n-range, best/worst and hash-audit data are in `partial-analysis-results.json` and `partial-analysis-hash-audit.json`.
