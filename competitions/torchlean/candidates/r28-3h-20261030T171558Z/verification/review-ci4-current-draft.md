# CI4 current draft review

Captured 2026-10-30 18:52 UTC. Read the latest request `185000-zero-native-cost-decouple.md`, root `development-status.json` and `CI-REQUEST.json`, and the current batch4 draft. The root files still show CI3 run `41107618451` as the only active run; there is no CI4 run. The current plan and prefix draft are still the 18:48 versions.

## Exact-source audit

`audit-ci4-current-draft.json` replays the owned transforms in memory from saved official #53 source hash `3dbe2f70…f7a9cb`. All existing entries rebuild byte-for-byte and meet the 256,000-byte bound:

- pointwise NativeOnly: `5ecfdd8c…755afe5d`, 245,424 B, `full_gate=false`, `declares_correct=false`;
- proof-bearing zero-v2: `85eb4a9d…d6d9c62`, 255,748 B, `full_gate=true`, `declares_correct=true`, gated on both exact bounded helpers;
- baseline and repair prefixes: `0161443f…ccaafaf8` / 163,658 B and `a74e72ac…a9cc2b464` / 164,271 B, each capped at 120 s in the plan.

Recipe, probe, source, helper-list, candidate hashes and sizes match the current draft. The exact helper runner now hard-clamps each helper to 120 seconds, catches per-helper exceptions into a failed diagnostic entry, and records `SKIPPED_AFTER_BOUNDED_HELPER_FAILED` for a required candidate if either helper did not exit zero. These resolve the three control-flow findings in the earlier review. Raw Lean helper logs are retained in `OUT` as the latest request directs; after any run, inspect and hash them for source leakage without discarding original failure evidence.

## Current stop condition

The latest request asks for a fourth entry: runtime-identical zero NativeOnly cost candidate, while deferring the proof-bearing whole zero-v2 all12 gate to a later batch. If safe dependency-closure removal cannot be built quickly, the request permits falling back to the bounded helpers plus pointwise NativeOnly candidate.

The current 18:48 draft has neither the new zero NativeOnly candidate nor the fallback set: it still contains only pointwise NativeOnly plus the conditional full-gate zero-v2 candidate. Once both helpers compile, the current runner will attempt the zero-v2 original full gate, contrary to the latest requested batch boundary. Keep CI4 undispatched until the draft is reconciled with the latest request, then independently rebuild/hash every exact entry and recheck the gate flags. No new theorem claim follows from helper or NativeOnly measurements.

For the reconciled batch, the allowed candidate set is either pointwise + runtime-identical zero NativeOnly + the two bounded helpers, or the explicitly permitted fallback of pointwise + the two helpers. Do not include the proof-bearing zero-v2 candidate in this CI4 run; reserve it for a later run with a separately frozen all12 gate and confirmation group.

Audit hashes: plan draft `1c572385…8430290`, prefix draft `34ae83ab…b034549`, runner `bbe7bbff…c1a45cea`, latest request `d4dd131d…8168dcf`. The saved machine-readable audit contains full hashes and field checks. No Lean compile, candidate build, CI dispatch or output inspection was performed.
