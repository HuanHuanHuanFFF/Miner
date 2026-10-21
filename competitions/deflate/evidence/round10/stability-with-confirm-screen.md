# Round 10 stability and route-contribution audit

Status: **VERIFIED_PUBLIC_RECEIPTS_RECOMPUTED**. D routes: 18 input SHAs from `evidence/round10/37679261323/explore-a/gate/forward-diagnostics/forward.json` (SHA-256 `3fd658edbf840173c0f756d3bb926df7201d91d704a40d6c1ea68f7ad35c7f78`); all receipt rows were classified by input SHA.

Per-file axis is each method's measured-total median divided by that file's paired-incumbent measured-total median. Each block averages the 28 axes. Contributions use `100 × (challenger file axis − reference file axis) / (28 × block reference axis)`; D and non-D contributions sum to the overall relative change. Blocks are equal within a runner, and runners are equal in the final mean.

## Record versus scalar

Rust SHA `7f1c661fd1ce29d12c69671f034ff5a713e284ed1fcba66ba404ff25479b55b7`; runs=5; runner-equal overall change **-1.021266%**; D contribution **-0.998131 pp**, non-D contribution **-0.023135 pp**.

| run | block | change | D contribution | non-D contribution |
|---|---:|---:|---:|---:|
| 37684506856 | 1 | -0.779580% | -0.733287 pp | -0.046293 pp |
| 37684506856 | 2 | -1.688838% | -1.556872 pp | -0.131966 pp |
| 37688325585 | 1 | -1.113657% | -1.047868 pp | -0.065789 pp |
| 37688325585 | 2 | -1.235494% | -1.177364 pp | -0.058130 pp |
| 37695105461 | 1 | -0.443965% | -0.466226 pp | +0.022261 pp |
| 37695105461 | 2 | -0.523974% | -0.550657 pp | +0.026684 pp |
| 37695964878 | 1 | -1.235348% | -1.253695 pp | +0.018347 pp |
| 37695964878 | 2 | -0.830277% | -0.977780 pp | +0.147502 pp |
| 37698560245 | 1 | -1.248780% | -1.180576 pp | -0.068203 pp |
| 37698560245 | 2 | -1.112750% | -1.036983 pp | -0.075767 pp |

## Pipeline versus record in restore-h

Same-run, same-block output identity held for every file. Pipeline versus record changed the normalized overall axis by **-0.317674%**; D contribution -0.365687 pp and non-D contribution +0.048013 pp.

| block | change | D contribution | non-D contribution |
|---:|---:|---:|---:|
| 1 | -0.222958% | -0.341355 pp | +0.118398 pp |
| 2 | -0.412390% | -0.390020 pp | -0.022371 pp |

## Same-run clone diagnostic

`mid-shadow / public361` block-level movement ranged from **-0.647193%** to **+0.175437%** (maximum absolute 0.647193%). The record runner-equal mean is -1.021266%; absolute record mean exceeds the largest observed clone block movement: **True**.
For pipeline versus record in restore-h, the change was -0.317674% against a same-run clone maximum absolute block movement of 0.647193%; it exceeded that movement: **False**.

This is a finite public stage1 comparison. Untouched-route contribution is measured contribution, not an assumed noise term. Clone movement is descriptive and does not establish a confidence interval or predict private/leaderboard performance.

The JSON file retains per-file axes, contribution values, input SHA, token SHA, output byte count/SHA, per-block equality checks, source hashes, and raw JSONL hashes.

## Additional receipt: 37700280634 (screen)

Pipeline versus record: -0.986714% overall, D -1.111209 pp, non-D +0.124495 pp. Its same-run clone movement was [0.47097189896010416, 0.0044559971410285115]; maximum absolute movement 0.470972%, so the pipeline effect exceeded it: **True**. CI status is `in_progress` with conclusion `UNKNOWN`; completed full gate: **False**; accepted exact pair: **NOT_RUN_IN_RECEIPT**. Performance and proof verdicts are separate.
