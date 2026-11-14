# B6 terminal review

Checkpoint: run `40967910604` from source commit `3c6b481f242c208fc1b4f00f1f523650deb8f32b`, dispatched against official head `27fb1d19c712ead50ad34b4ad0d4ba597161e616`. The saved CI run is terminal with workflow failure; parent development status still showed B6 active at its last update `22:46:07Z`. The latest request file says B6 completed while a separate FP23 integrated recipe is frozen for later review. No API calls were made by this role.

## Artifact and dispatch integrity

The independent raw audit [audit-native-run-40967910604.json](audit-native-run-40967910604.json) passes 58/58 outer and 57/57 inner file hashes, verifies the dispatch run ID and public `allow_private=false` setting, confirms the frozen plan/source hashes, and checks the saved #23 source receipt against the exact local bytes. Both candidate outputs reconstruct in memory to their planned hashes. The frozen runner and preparation script are tied to the run commit. MainExact is recorded as `b324bad32bc4ce449eb69be00e252163b77de4a0295736debe4081b53c4681ab`; the dispatched runner includes the byte-copy assertion. Native compile, link and response flags match after only target-name mapping for the cost-only candidate.

The current official normalized-MLP champion is #43 / promotion 28, source unavailable. The saved #43/#23 report edge is `0.9072362322024092`; #23 remains the calibration carrier. Its report config matches the latest live board, and the benchmark/proof identity remains INFERRED from the saved head/helper/hash replay. B6 used the local 5×3×2 ms cohort and two different seeds, so the fixed strict converter returns UNKNOWN for these rows.

## Results

`public23-row-reciprocal-native-cost-v1`, SHA-256 `c688f1074370dd1436e67e7691de027f231239c0a11357d63c2f06d2dbf6ce32`, is explicitly `full_gate=false` and `declares_correct=false`. It builds and produces 180 paired rows for each of two seeds; the pinned R25 scorer reproduces the saved local candidate/#23 ratio, all checksums match, the round order alternates, and the CPU identity is stable. Converting through the saved current #43/#23 edge gives **1.129789686x current #43 time**, INFERRED across local versus production environments and seeds; it is slower and not a champion result. The candidate has no correctness claim because the new kernels have no inherited proof.

`public23-row-reciprocal23-v3`, SHA-256 `9654b727badce93d0727ece982a0ccedce99107ce98235b18e0e5cdc79e8944e`, entered the official full-gate branch before any candidate build or timing. It failed at the `statement` stage with type mismatches, unexpected tokens, an unsolved goal, an unresolved `R27D.v`, and downstream rewrite failures. The starting and ending verifier fingerprints match and the run was not exhausted. The exact source is therefore **not Correct**, and no multiplier exists for this candidate.

Standalone `reciprocal_u64_v4` and `guarded_nonzero_v2` helper diagnostics both exited zero and printed only their requested roots. They remain helper-only diagnostics; neither substitutes for the failed all12 gate. The optional cost-profile diagnostic could not compile its C probe because `stdio.h` was unavailable, so no operator cost breakdown was collected. The native cost screen remains intact.

The CI workflow failed on the planned v3 full-gate rejection after collecting the terminal artifact. `CI-RESULTS-BATCH6.json` was not present at this audit checkpoint; the analysis uses the raw `summary.json`, `ci-run.json`, artifact manifests, and the saved root audit.
