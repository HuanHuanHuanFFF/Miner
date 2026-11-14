# B8 FP23 and prepared-block16 static review

This review is static. It reconstructs candidate bytes in memory, checks recipe and dependency hashes, and inspects proof binding; it does not write candidate files, compile Lean/native code, contact the API, or dispatch CI. The results are in [audit-batch8-fp23-static.json](audit-batch8-fp23-static.json).

## Exact source and recipes

The current `ci-plan-batch8.json` hashes to `b646b015e07100268f4fcc6c486c82e1bcad0b0920e71c6cf3282a7e3a66e58a`. The saved public #23 source receipt matches the 252,639-byte source hash `1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe`. The FP transformation and both block16 variants rebuild to the plan's exact output hashes:

| Candidate | Candidate SHA-256 | Bytes | Gate flags |
|---|---|---:|---|
| `public23-fp-only-lazy` | `4950ac8f159acbf7dbdd2dc3a9459cf805abf8272fd8e1fbb0ad43c20a15a094` | 255,418 | `full_gate=false`, `declares_correct=false` |
| `public23-prepared-block16-unrolled-native-cost-v2` | `14ab9f4fcd9e05a25bf8fdd30248eb3044742a2671661ef53ab552ec301beebc` | 252,115 | `full_gate=false`, `declares_correct=false` |
| `public23-prepared-block16-allrows` | `659c694a19d6765618dc254fc2fd6a8b0d50ad488fb4a40f75918a01953f12db` | 252,119 | `full_gate=false`, `declares_correct=false` |

The FP recipe pins the proof-only compactor, adapter, and `LazyFPOnly.lean` helper hashes. It preserves the original proof as `retainedCorrect` over `retainedKernels`; the new `Submission.kernels.dense.linear` calls `R27FPOnly.linear`, with no new `correct` theorem. Public #23 contains the referenced `YaU` and `Yc` providers, and the generated candidate includes the explicit slow path. Its 582-byte margin under the 256,000-byte cap is small, so this exact hash must remain fixed through dispatch.

The block16 recipe pins `public23_block16_cost.py`, the alias compactor, and `Block16PreparedUnrolled.lean.inc`. It retains the old theorem only over `retainedKernels` and replaces the runtime kernel without adding a proof. The block16 files describe a per-term `<2^59` bound and a 16-term signed-64 sum, but they do not connect that argument to a new theorem about the actual prepared values or fallback path. All three candidates are cost-only research inputs; none is Correct or admissible as a proof result.

The plan contains three candidate entries across two mechanism families: one FP-only candidate and two block16 variants. `public23-prepared-block16-allrows` widens the block16 path guard from the one-row case to `rows < 65536`; it remains unproved. The initial `FP23-INTEGRATED-4950AC8F` and `BATCH6-NEGATIVE-TO-DENSE8` requests did not name the third variant, and `ci-plan-batch8.json` plus `block16_allrows.py` were updated at `22:58:44Z` after those requests. The later `BATCH8-INTENDED-THIRD-VARIANT` request at `23:02:24Z` explicitly confirms its candidate hash `659c694a…53f12db` and describes it as a second block16 variant.

## Diagnostic profile and current champion

The B8 profile adapter hash matches the plan. It adds host include paths only to a separate instrumented C diagnostic, writes a separate profile binary, and the runner calls it for the reference build only. It records entry-time shares for `YaV`, `Ybb2`, and `MYbc`; those are diagnostic counters, not official timings or whole-model savings.

The sole human comparison target remains current normalized-MLP #43. Its source is unavailable; public #23 is only the official report-chain calibration source. Any local native screen is an INFERRED current-#43 multiplier and the strict converter returns UNKNOWN because it lacks both current production environment runs and the report's 11×3×50 ms input contract.

After this review, B8 was dispatched as run `40970353723` from source commit `72b2e2082449d43d0f8cac80f3d79fb4e93b5666`. Its receipt freezes plan hash `b646b015…e3a66e58a`, all three candidate scripts, the profile adapter, helpers, and owned sources with `repository_public=true` and `allow_private=false`. The independent static audit now passes with the follow-up scope note resolved. Parent status read at `23:05:09Z` has B8 running and no terminal result yet. Keep the current #43 champion binding and public #23 receipt attached to its eventual measurement record.
