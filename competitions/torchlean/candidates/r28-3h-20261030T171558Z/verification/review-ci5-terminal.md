# CI5 typed pointwise terminal verification

CI5 run `41117223550` completed successfully on commit `4c22bfb9652170a85a7785f0d488c1963de8fdd2`. The fixed R28 `audit-native.py` completed independently and is byte-identical to `root-fixed-audit.json`, SHA-256 `d2512c5140c635a092559e0266dfbf0f0b290d046c458daa6a73abd84bf5e8ac`; see [audit-native-run-41117223550.json](audit-native-run-41117223550.json).

## Integrity and result

- The run lasted 324.281 s, 19:42:18.646–19:47:42.927 UTC. All 54 outer and 53 inner artifact files pass their hashes with no missing/unexpected files. The reference source, `MainExact`, and compile/link/response flags pass; original files stayed unchanged.
- Candidate `17befe6a4afb7dac0dc19090970812b1890d147154932f610f015b6dd1b0d044` has two complete seeds, 180 paired rows per seed and 360 matching checksum pairs total. CPU provenance is identical across both seeds: `2ce5abb0…`, `runnervm48cm3`, x86_64, affinity 0.
- The local score is `1.111108` against public #53 with the guard failing. Against saved MobileNet #57 ratio `0.9561003`, the inferred candidate/current estimate is `1.162125×`, about 16.2% slower. The source comparison is still based on the 18:15 champion snapshot; it is not a fresh official score.
- This run produced no current-champion win. It has no `Submission.correct`, is `NOT_PROVED_NATIVE_ONLY`, and has no full proof gate. The successful CI job means the NativeOnly build/measurements completed; it does not establish correctness or promotion eligibility. A fresh confirmation group would still be required for any performance adoption.

The run used the exact CI5 source plan and fresh pair of seeds. No proof or timing was inherited from failed candidate `5ecfdd8c`. Root `development-status.json` and `CI-REQUEST.json` are still stale at CI5 READY/no active run even though the run's own metadata is completed/success; reconcile those status files. No CI5 outputs were modified.
