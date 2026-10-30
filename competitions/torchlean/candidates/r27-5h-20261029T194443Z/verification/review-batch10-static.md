# B10 NativeAdd portfolio static review

Review time: 2026-10-30 00:05 UTC. Run `40977309820` is in progress; this review uses only the frozen plan, dispatch receipt, saved public sources, and source transformation. No B10 measurements or run logs were read.

## Frozen candidate

- Candidate `public23-gemm27-native-add-qualified`, SHA-256 `f60551d55be31d2d2d4a59ba2646c8769d1cb8e31538176041070a0477881bea`, 255,666 bytes (334 bytes below the 256,000-byte limit).
- In-memory reconstruction from saved public submissions 23 and 27 reproduces the exact hash and byte count. All eight owned files match the dispatch commit. Plan SHA-256 `19b23f27e05f9ceb97eda3dd1ae182d3d738fff8007b39cb05bb56b83e791bd2` matches the canonical plan, dispatch freeze, and selected candidate.
- Public run, `allow_private=false`, source commit `e0019e9ce2a5000ec882a963c51e55fbec1b08ae`. The plan calls the original full gate and standard 11×3×50 ms confirmation on two fresh roots.
- Static transform metadata reports a 7,972-byte NativeAdd closure; it removes only the enumerated RMS-exclusive declarations whose donor reference counts are zero, uses no late namespace open, and fully qualifies nine alias differences. These are construction facts, not proof or cost acceptance.

## Correctness and champion boundary

The plan declares an actual `Submission.correct` and all12 connection, but this candidate has not passed the official gate yet. Until the run's exact source hash passes, it is not Correct. The candidate adds the qualified NativeAdd closure while retaining the C9 GEMM path; it does **not** restore the original submission 27 small-k engine.

The comparison target is current Mixer submission 36. Its source is unavailable; the public submission 27 source is only the historical calibration carrier. The saved #36 report uses config hash `ab0fdb…` while the latest live Mixer config is `4a9278…`, so any eventual current-champion multiplier must be labelled **INFERRED** if the report edge is usable; the strict converter remains **UNKNOWN** for mismatching local rows.

The compact reconstruction and dispatch checks are in [audit-batch10-static.json](audit-batch10-static.json). This static review makes no correctness or performance claim.
