# Round 10 measurement audit

The six completed `gate` receipts support **114 public paired measurement rows** and **12 distinct new Rust source hashes**. I recomputed all 114 rows from their raw JSONL files: each has 28 public files, 11 measured repetitions plus one warmup, no recorded method errors, and its time/size/source hash agrees with `state.metrics`. All 279 entries across the six `raw-artifact-files.json` manifests match their recorded byte counts and SHA-256 hashes. The count uses only the final `gate` phase; preliminary `screen` and `extraction` files are excluded.

| CI job | CI result | Paired rows | New Rust sources in job | Manifest mismatches |
|---|---:|---:|---:|---:|
| `37679261323/explore-a` | success | 24 | 5 | 0 |
| `37680712729/rmq-a` | success | 16 | 1 | 0 |
| `37682364860/prove-a` | failure | 18 | 2 | 0 |
| `37684506856/struct-b` | success | 22 | 4 | 0 |
| `37688325585/row-c` | success | 18 | 2 | 0 |
| `37689247460/rebase-d` | success | 16 | 1 | 0 |
| **Total** | **5 success, 1 failure** | **114** | **12 distinct hashes across jobs** | **0** |

Here “paired process” follows the round10 summarizer: one candidate/control method and block row over the 28-file corpus. It is not one per-file timing or one individual repetition. The six runs contain 15 `r10-*` entry labels; seed’s proof variant reuses the seed Rust hash, and row-c reuses record-nonempty, leaving 12 unique `parse.rs` hashes. The third-loop summary’s six runs, 12 candidates and 114 paired rows match the raw gate receipts. Its counts are consistent with the first-loop 40-row and second-loop 80-row rollups.

`r10-record-nonempty` matches scalar compressed-output byte counts and SHA-256s for all 28 files in each of four blocks; token hashes also match in all 112 file-block comparisons. Using the score-axis normalization in `summarize-round10.py`—candidate’s equal-file mean of per-file median total-time ratios divided by scalar’s corresponding score for the same block—the results are:

| Run / block | Relative to scalar | Same compressed bytes |
|---|---:|---:|
| `37684506856` block 1 | −0.7796% | 28/28 |
| `37684506856` block 2 | −1.6888% | 28/28 |
| `37688325585` block 1 | −1.1137% | 28/28 |
| `37688325585` block 2 | −1.2355% | 28/28 |

The run means are −1.2342% for struct-b and −1.1746% for row-c; their equal-run mean is **−1.2044%**. Only the exact source/proof pair in struct-b has an accepted complete public gate (`parse.rs` SHA `7f1c661f…79b55b7`, `Parse.lean` SHA `86cfc36a…e95592d`). Row-c is an independent performance rerun; its `state.gates` is empty, so it is not a second proof pass. The four raw record measurements and their full hashes are indexed in [measurement-audit.json](measurement-audit.json).

The seed measurements reproduce exactly across `37679261323` and `37682364860`: `r10-forward-seed` / `r10-forward-seed-proof` share Rust SHA `0641cc84…49f7d489`, and `r10-forward-seed2` shares SHA `773ff3ec…7da80037`. For both versions and both blocks, all 28 input hashes, token hashes, compressed-output hashes and output sizes agree across the two runs. This confirms the public output/quality reproduction, not proof acceptance.

The proof failure is explicit in [the original Lake log](37682364860/prove-a/gate/r10-forward-seed-proof-005-lake.log): extracted `Proof/Parse.lean` has four `omega could not prove the goal` errors at `3676:68`, `3815:39`, `3821:34`, and `3945:49`. The gate records `accepted=false`, `gate_exit=1`, and the CI job concludes failure. The Miri setup warning is separate; the job did not fail from timeout.

The current fast3 sensitivity file is a counterfactual model built from the first four completed runs: it lists eight raw rounds and 224 file-blocks. It omits the later row-c and rebase-d receipts; all six runs would cover 336 fast3 file-blocks. Keep its model values labeled as model-only and do not describe them as a six-run recomputation. This audit used no historical round 3 measurements.

One aggregation detail can look like a discrepancy: raw `total_s` values from separate candidate and scalar JSONL processes do not share the same measured incumbent. Comparing those durations directly gives different percentages. The reported record result uses each process’s paired incumbent to form its score axis, then compares candidate and scalar axes block by block; this reproduces the summary values above. No mismatch was found between that aggregation and the summaries.
