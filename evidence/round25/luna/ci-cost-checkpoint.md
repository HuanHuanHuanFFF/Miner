# R25 cloud-run cost and coverage checkpoint

This checkpoint uses only saved `dispatch-*.json` and original `ci-run.json` evidence. It does not poll or query CI. It counts each run ID once and measures only job-level `startedAt` to `completedAt` for executed, non-skipped jobs. Authorized timeout minutes are not treated as consumption.

| Mode | Collected successful runs | Queue (sum) | Per-run experiment wall (sum) | Runner cumulative (sum) |
|---|---:|---:|---:|---:|
| Native | 10 | 0.533 min | 6.600 min | 6.600 min |
| Standard paired measurement | 5 | 0.317 min | 59.200 min | 59.200 min |
| Extract | 3 | 0.167 min | 19.767 min | 19.767 min |
| Full gate | 1 | 0.050 min | 16.083 min | 16.083 min |
| **Total collected** | **19** | **1.067 min** | **101.650 min** | **101.650 min** |

All 19 saved CI run receipts conclude success; no failure is present in the captured set. One additional dispatch, run `38130996700` (`gate-tiny-pc8-proof1`), has no raw `ci-run.json` in the checkpoint evidence and is excluded from time totals. Its actual status and consumption are UNKNOWN here. Across collected runs, the global observed runner window is 2026-10-11 08:17:54Z–10:13:04Z (115.167 minutes); this wall-clock envelope includes idle gaps and overlaps, while summed run wall and runner elapsed are 101.650 minutes. The queue sum is measured from GitHub run `createdAt` to its first actual job start.

Each collected run has one actual runner job and ten skipped jobs. The 190 skipped jobs are excluded even where their timestamps run backward; 122 skipped intervals were negative. The mode totals are raw elapsed minutes, not billed/rounded minutes, and do not estimate a monetary charge.

Coverage visible in these files: five successful original-protocol paired-measurement workflow steps, one successful frozen-pair original full-gate step (`38125243582`), and one gate dispatch without a saved run receipt. The exact number of child paired processes, unique Rust/Lean source pairs, and post-freeze independent confirmations cannot be established from these two JSON families: process-level counts and pair hashes are absent, and no explicit frozen-pair marker is recorded. The five successful standard jobs have five distinct dispatch Git SHAs (zero repeated SHA), which is not by itself proof that the candidate source changed or stayed fixed.

`ci-cost-checkpoint.json` contains each dispatch/CI receipt path and SHA-256, run-level job interval, queue/wall/runner seconds, conclusion, and coverage step result. This is a checkpoint, not the final spend or verification report.
