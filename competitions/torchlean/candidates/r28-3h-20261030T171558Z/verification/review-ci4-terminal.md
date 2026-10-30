# CI4 terminal verification

Captured 2026-10-30 19:34 UTC after root marked run `41113231015` collected/terminal. The fixed R28 auditor completed independently. Our output is byte-identical to `root-fixed-audit.json`, SHA-256 `01b34a5931dcc2d2ffb9126387abcb60dc5fae6c4cabf711bcba62efb5e09f48`; see [audit-native-run-41113231015.json](audit-native-run-41113231015.json).

## Integrity and measured source

- CI ended `failure` because the pointwise NativeOnly build failed. Run commit `95d9df2392b0a686f50e114d4a9e791138484567`; elapsed 550.785 s, 19:13:07.950–19:22:18.735 UTC. Root status has zero active runs, but `CI-REQUEST.json` still says `RUN_IDENTIFIED` for this run and should be reconciled.
- All 57 outer files and 56 inner files pass hashes with no missing/unexpected entries. The pinned reference flags and source preservation pass; `MainExact` is unchanged.
- Zero NativeOnly `474eff80…384d74` completed two seeds, 360 paired rows and 360 checksum pairs, all raw rounds validated against aggregate measurements. CPU identity is the same across both seeds: `2ce5abb0…`, `runnervm48cm3`, x86_64, affinity 0. It remains `NOT_PROVED_NATIVE_ONLY`; this run contained no full proof gate.
- Local score against public #53 is `1.215398`. Conversion through the plan's saved MobileNet #57 ratio gives an **inferred** `1.271203×` current-champion estimate (about 27.1% slower). The conversion uses the 18:15 snapshot, not a fresh comparison. This is negative cost evidence; stop this exact zero-consumer proof path and do not treat the result as a full theorem candidate.
- Pointwise NativeOnly `5ecfdd8cd007…` built from the exact frozen source but was not timed. Its build log records seven source errors (then the aggregate “build failed” line): a failed `decide`, two missing `HSub Nat UInt64` instances, three lookup errors at 4183/4184 (application type mismatch and typeclass failure), and a failed `rw` rewrite. There are no pointwise measurement files; score is UNKNOWN. No full gate ran for either entry.

## Bounded prefix results and log retention

- Baseline qCtx8: exact source hash `0161443f…ccaafaf8`, exit 0 in 63.534 s. This is only a helper-prefix elaboration result.
- Repair qCtx14: exact source hash `77b58fc87c28…`, exit 1 in 65.987 s. Its raw log has two `unsolved goals`, at qCtx8 and qCtx14. Both show the remaining natural-number termination inequality for `n.toNat - (k+1).toNat < n.toNat - k.toNat`. The qCtx14 log's `sorryAx` line follows the failed compilation and is not an accepted proof.
- Both original helper logs are preserved byte-for-byte and match the fixed audit's SHA-256 values. I scanned them against the exact rebuilt prefixes: the logs are much smaller than the prefixes, neither contains a full prefix body, and neither contains any of 1,396/1,446 unique source lines of length at least 40. No full-source dump was detected; the raw error excerpts remain intact.

The helper checks do not transfer proof to zero NativeOnly. A successful bounded prefix is not an all12 result. The next proof experiment must use new source hashes and an exact full gate; the root request suggests fixing the one-step termination obligations before another full proof attempt.
