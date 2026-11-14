# B6 static review

Checkpoint: parent status still reported B5 run `40966581016` active at `2026-10-29T22:32:34Z`. B6 request files received after that checkpoint mark cost14 accepted and B6 pending/not dispatched. This review uses only saved R27 files. It did not fetch current API values, compile Lean/native code, write candidate outputs, or dispatch CI.

## Exact source and candidates

The frozen `ci-plan-batch6.json` SHA-256 is `86fa58857e23bd3c3cd6ca849ce45138bca835ce4d949e0d26abb2daaaccd1fc`. Its official source is public retired #23, `1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe`, 252,639 bytes. The current target remains normalized-MLP #43, promotion 28, source unavailable; the current report edge is #43/#23.

I reconstructed both candidate outputs in memory from the exact saved #23 bytes. Their patch hashes, output hashes, and output lengths match the frozen plan:

| Candidate | SHA-256 | Bytes | Gate state |
|---|---|---:|---|
| `public23-row-reciprocal-native-cost-v1` | `c688f1074370dd1436e67e7691de027f231239c0a11357d63c2f06d2dbf6ce32` | 255,415 | `full_gate=false`, `declares_correct=false` |
| `public23-row-reciprocal23-v3` | `9654b727badce93d0727ece982a0ccedce99107ce98235b18e0e5cdc79e8944e` | 253,499 | `full_gate=true`, `declares_correct=true` |

The cost-only variant renames the old theorem to `retainedCorrect` over `retainedKernels`; the new `kernels.norm` uses the new reciprocal path and has no inherited correctness theorem. It remains NativeOnly even if it compiles and measures. The v3 candidate keeps the original all12 `correct` entry, compacts proof aliases without deleting declarations, applies the actual reciprocal proof edits, and includes the pinned v4 helper. Static recipe hash checks cover the source, compactor, prior recipe, helper, and final output. None proves the candidate; the exact v3 bytes still require the original full gate.

The runner takes the full gate branch before building or timing the v3 candidate and requires a passing original verifier result at stage `axioms` with equal start/end fingerprint. It separately allows the cost-only candidate to reach native timing without a full gate, but that result must remain `NOT_PROVED_NATIVE_ONLY`. Standalone v4 reciprocal and guarded-nonzero helpers are diagnostics, not a substitute for the v3 all12 gate.

All seven B6 owned source files and both helper files exist, and public #23's saved official source receipt matches its exact local bytes. Their hashes and the in-memory output checks are recorded in [audit-batch6-static-and-live-policy.json](audit-batch6-static-and-live-policy.json). No dispatch receipt is present yet; the dispatch client must freeze the owned-source hashes before a run because the B6 plan does not list each owned-source hash inline.

## Current champion conversion

The independent pinned-plan replay checked six saved board configs, confirming that the only changed plan field is `benchmark_identity`; all six reconstructed hashes match the latest saved board response. The replayed normalized-MLP hash equals current #43's report config `647ef0dc…abbd95a`. The current #43 benchmark identity is inferred from official head `27fb1d19…d4ba597`, B4 helper-run identity `6df065ba…f3faa5cd`, and the live config hash. The proof identity is `3a69968c…77bee6`.

The report edge gives `#43/#23 = 0.9072362322024092`; a future fixed-scorer candidate/#23 row can be converted to current #43 only as INFERRED when it binds the exact current report contract and both production runs. B6 is a two-seed local native screen, so it does not itself meet that contract. Without a direct #43 source pair or a full matching row, keep the champion multiplier UNKNOWN; do not present the #23 reference as current.

The verification result is `PASS_STATIC_ONLY_NO_PROOF_OR_PERFORMANCE_ACCEPTANCE`. It records recipe consistency and live-policy reconstruction, not gate success, native build success, or a current-champion performance result.
