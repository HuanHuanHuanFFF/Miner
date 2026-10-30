# Batch 4 normalized-MLP preflight

I reread the 21:49:54 parent status, `BATCH4-READY.json`, and saved public champion request before reviewing the frozen plan. No batch 4 dispatch was present at this checkpoint.

## Frozen identities and source route

- `ci-plan-batch4.json` matches READY at SHA-256 `fc9212a81326b7c290be8d0f6ad01e83d9d874d303ef34296fe1eb341a04db61`; the runner matches READY at `ec0e0685e4bca74f039b3090c62038507cfe95ad19a1cce7adfd5653c99b20ac`. Both candidate patch hashes, all three helper hashes, and the profile adapter hash match the files on disk.
- The native128 graft is unchanged from the blocked B3 candidate: `1bd6e153…4463e8b`, 255,969 bytes, `full_gate=false`. The new norm-prep proof3 source is `39f377f9…6e2160a`, 222,247 bytes, also `full_gate=false` and not yet compiled. No full gate is scheduled for either candidate.
- The receipt for submission #27 source is HTTP 200 at 21:34:46 UTC, SHA-256 `f92ee2c9…3481aa67`, 255,647 bytes; the saved body hash matches the earlier local file and the extra-fetch pin. The preceding frozen urllib request returned Cloudflare 1010 / 403; Droot then made a separate request through the documented project client to the same official endpoint, which returned the pinned bytes. This verification role made no source request. The B4 adapter uses that same transparent project client for #12 and #27, verifies/caches hashes, and declares no auth, proxy, alternate endpoint or in-run retry. Keep source bytes local-only and exclude them from public artifacts; the successful fetch does not settle the unknown license boundary or authorize access to private current sources.
- The latest mixer champion response is not usable as current-state evidence because its publication hash does not match saved `boards.raw`; that does not affect this plan's normalized-MLP #23 target. The normalized-MLP row remains bound to its saved report snapshot, with source #23 unavailable.

## Proof labels and claim boundary

The runner now respects an explicit `declares_correct=false` and returns `NOT_PROVED_NATIVE_ONLY` for fetched sources with that flag; this resolves the packed-draft adapter issue for a future plan that sets it. The current norm candidates have `full_gate=false` and carry uncompiled proof-state notes. The runner ignores the notes and derives `DECLARED_CORRECT_TYPECHECKED_NO_FULL_ORIGINAL_REPLAY` from a successful fetch unless the plan explicitly says `declares_correct=false`. That derived state still is not `FULL_ORIGINAL_GATE_REPLAYED` or `Correct`; before interpreting results, preserve the distinction and ensure the declaration matches the candidate author's intended claim.

Both B4 seeds, 27102921 and 27102923, differ from current #23's report seed 3542272469. Any native result is an inferred route screen and must display only its current-champion multiplier. It cannot qualify the candidate for a current-board win or substitute for the original twelve-obligation gate.

## Profile budget

The profile is a separate instrumented control binary, and its timings do not enter the scorer. It runs while building the calibration reference, before candidate measurements. Its caps allow 120 seconds each for compile and link, then six cells with up to 60 seconds for each control and instrumented call (up to 720 seconds), for a profile maximum of 960 seconds. Three helper checks have 360 seconds of caps and the reference native build has a 300-second cap. Those maxima total 1,620 seconds before the candidate builds and measurements, against the runner's 1,800-second internal deadline. The actual run may use much less; if the remaining deadline clips a candidate build or pair set, classify it as incomplete/budget-limited and do not convert missing rows to zero.

The 21:49 READY request also says the profile v2 matches the actual Lean C prefix and three nested MLP entries, uses a separate binary, catches diagnostic errors, and never rescales profile times as benchmark results. Recheck its terminal raw manifest, checksums and elapsed caps. No source compile, native run, CI action or Git operation was performed in this preflight review.
