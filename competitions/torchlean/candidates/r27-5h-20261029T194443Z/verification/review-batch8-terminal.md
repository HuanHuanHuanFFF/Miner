# B8 terminal review

Run `40970353723` completed successfully from source commit `72b2e2082449d43d0f8cac80f3d79fb4e93b5666` against official head `27fb1d19c712ead50ad34b4ad0d4ba597161e616`. Independent raw audit [audit-native-run-40970353723.json](audit-native-run-40970353723.json) passes 127/127 outer and 126/126 inner artifact hashes, verifies the public dispatch and frozen source map, and reproduces every measured result with the pinned R25 scorer. The workflow success only means the native exploration completed; all three plan entries explicitly exclude the original correctness gate.

## Native screens

All three candidate outputs match their frozen hashes and are `full_gate=false` / `declares_correct=false`. Each completed 180 paired rows per seed over two local seeds, using five rounds × three repetitions × two milliseconds. The runner held the same x86_64 CPU identity across candidates and seeds; raw checksums match, order alternates, and compiler/link/response flags differ only in target names.

The only human performance metric is the estimated time against current normalized-MLP #43. The fixed scorer and saved #43/#23 report edge yield:

| Candidate | Estimated current #43 time | Result |
|---|---:|---|
| `public23-fp-only-lazy` | **2.405218046×** | Guard failed; slower |
| `public23-prepared-block16-unrolled-native-cost-v2` | **1.090588818×** | Guard passed locally, but above the performance bar and slower than current #43 |
| `public23-prepared-block16-allrows` | **1.125329939×** | Guard failed; slower |

These are INFERRED local-screen estimates across environments and seeds. Current #43's source remains unavailable, and the strict converter returns UNKNOWN because these runs do not match the two production report runs or their 11×3×50 ms input contract. None of the candidates has a new correctness theorem or an all12 gate result; workflow success is not correctness or promotion.

## Reference cost profile

The optional instrumented profile completed on the public #23 calibration binary and verified 36 paired checksums. Across the instrumented kernel entries, it recorded 767,275,110 exclusive nanoseconds: 90.57% in `linear`, 4.77% in `layernorm`, and 4.66% in `rmsnorm`. The profile script explicitly limits these figures to one local runner and six cells; it excludes output work outside the instrumented entries and warns that warmups may enter the counters. They are a route diagnostic, not whole-model savings or official timings.

The generated C profile and source bodies stayed inside the runner. `CI-RESULTS-BATCH8.json` is now saved and matches the independent raw scorer and artifact checks.
