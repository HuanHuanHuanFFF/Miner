# B12 terminal typefix cost audit

Review time: 2026-10-30 00:42 UTC, under the parent request to perform one independent B12 raw/hash/scorer audit and rebind the current champions. No local compile or API request was made.

- Run `40979775217` completed successfully with candidate `public23-band64-weightcache-typefix`, SHA-256 `afd08cbf53ca1fbcba790814124d4f7949b51549a20d7205b639142ff62541e9`, 252,693 bytes. The saved public #23 source and frozen builder reproduce that exact candidate hash. Outer/inner manifests pass 52/52 and 51/51.
- This is NativeOnly cost evidence: `full_gate=false`, `declares_correct=false`, proof state `NOT_PROVED_NATIVE_ONLY`. No Correct or champion claim.
- Two local quick roots each have five rounds × 36 cell/workload rows (180 pairs), 360 reported ns values and 180 matching checksums. Combined: 360 pairs, 360 checksum pairs, no mismatches; round order alternates and both roots use the same x86_64 CPU. Native compile/link/response traces match after expected target-name mapping.
- Independent fixed R25 score reproduces the root result. Human comparison is **2.5619087264× current normalized MLP #43 time** (`INFERRED`, slower); guard failed. The candidate uses local roots; current #43 source is unavailable, so strict current-report conversion remains UNKNOWN. The request cell schedule matches quick 5×3×2 ms, but operational run/cache/benchmark limits differ from the saved `Config` defaults; this is another reason to keep the cross-environment estimate INFERRED.
- The run root result in [CI-RESULTS-BATCH12.json](../CI-RESULTS-BATCH12.json) agrees: `TYPEFIX_COMPLETE_NATIVE_COST_NEGATIVE_NO_ACTUAL_CORRECT`, score guard failed, no champion.

Latest saved board/champion responses were rebound from raw bytes in [audit-current-board-binding-003007.json](audit-current-board-binding-003007.json): all six current identities are verified against publication `a8167e…f312f21`, while all six current source bodies remain unavailable. No new-champion claim follows.
