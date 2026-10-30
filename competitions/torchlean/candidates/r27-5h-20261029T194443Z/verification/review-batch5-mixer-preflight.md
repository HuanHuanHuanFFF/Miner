# B5 mixer plan review

This is a static review of the already dispatched plan, not a request to alter or stop CI. Parent status read at `2026-10-29T22:32:34.599536Z` showed run `40966581016` active on source commit `29ea9be2e8b75339da81801815ba94196fec936a`; no B5 terminal result was in that checkpoint.

## Frozen target and inputs

- Plan SHA-256: `c302840aeaae8586b0916626a072e7b995c68df0b07ded2646b128664849f07c`.
- Official head: `27fb1d19c712ead50ad34b4ad0d4ba597161e616`; seeds `27102951` and `27102953`.
- Current mixer champion: promotion 27 / submission 36, source SHA-256 `595a90fa2b6bc5d3657434fae7d1292b27910ef653da2b7f409ed9c34c956e2b`, source unavailable, confirmed by the saved response matching the latest boards publication.
- Calibration carrier: public retired #27, source SHA-256 `f92ee2c9a29de78dc434ad158b7141c0e4b5a67a5a198a353d59a4703481aa67`, 255,647 bytes. The exact source bytes are in the R27 local-only source cache and hash-match the planned source.
- Owned patch script SHA-256: `459e8384c4f1b531a5eb2e2a2c29b5fc7d8e00d464d25273aaba125f990c7251`.

The plan declares both `public27-columns-all` and `public27-adaptive` as `full_gate=false`, `declares_correct=true`, with proof state `ORIGINAL_ALL12_CORRECT_REUSED_GENERIC_SCHEDULER_NOT_COMPILED`. The fixed source/result hashes are `e739a55d0d3262d08332f387e9b5660b9a419018b2b2a7bcd53fe0dfee6849b3` (255,655 bytes) and `1edaff963f646de0e62b3e50064a31e205142e6aebea6fb5afa2bde61303052f` (255,725 bytes). The patch changes the selector and reuses an equality theorem, but neither exact candidate has been through the original all-twelve gate. They are not Correct results until the full gate accepts the exact candidate SHA.

## Comparison boundary

The existing official #36/#27 report score is `0.9622181669992014`, but it uses config hash `ab0fdb552d44b82ee286607a8ad0d914b6426615853ea3fe255878208a744f0e`. The latest live mixer config is `4a9278fefa8f3799173bf1dfec50c7ea02819d3e312c819e267ecfeb89b5dbf9`; the new official benchmark identity is `6df065ba…f3faa5cd`. The policy replay explains the hash difference as the benchmark-identity field, but the #36 report's measured timing is still from the old config. Thus a new native candidate/#27 ratio cannot be called an exact current #36 multiplier from that old score. Preserve the old report as historical and keep the mixer conversion UNKNOWN unless a current-version official #36/#27 edge or a direct #36 source pair becomes available.

The plan compares only with current #36 through public #27 as the calibration carrier. Its `profile_control=false`, and it leaves the fixed contracts/gate/benchmark files untouched. Any native result remains a route screen with the plan's exact hashes, raw timings, checksums, CPU, and order. Do not label the old #27 submission as the current champion. This role did not build the candidate, execute Lean/native code, or dispatch CI.

The shared runner copies `bench/MainExact.lean` byte-for-byte and asserts the copy hash; it builds the original and candidate with the same target configuration, then requires compile, link, and response-file arguments to match after only the target-name mapping. It creates six mixer cells from pinned `Config.plan`, uses the plan's two local seeds and six pinned workloads, with a 5×3×2 ms timing cohort. Its environment is local, so it does not reproduce the official pair of production runner identities. Native correctness stays separate from the absent full all12 gate. A future B5 multiplier against current #36 must stay UNKNOWN under the fixed strict converter unless a compatible official edge or direct #36 pair becomes available.

## B5 terminal audit

At `2026-10-29T22:42:15Z`, the saved run was terminal with workflow failure and all requested artifacts collected. The independent audit [audit-native-run-40966581016.json](audit-native-run-40966581016.json) confirms 53/53 outer and 52/52 inner hashes; it reconstructs the candidate bytes, checks the frozen public dispatch, parses every row with the pinned R25 scorer, checks raw rows against aggregates, verifies alternating order and equal checksums, and rechecks compile/link/response flags. The recorded MainExact hash is `b324bad32bc4ce449eb69be00e252163b77de4a0295736debe4081b53c4681ab`; the frozen runner blob is dispatch-bound and contains the byte-copy assertion.

Only `public27-columns-all` produced timings: 180 paired rows per seed, 360 total, across two seeds on the same pinned local x86_64 runner. The fixed scorer gives `1.0136568824602852` candidate time over the retired #27 calibration source. The old official #36/#27 report ratio is `0.9622181669992014`, under the historical mixer config hash; the current board hash differs after the benchmark identity change. The cross-version conversion is therefore INFERRED: `1.053458474621719x current #36 time`, slower than the current champion. The strict converter remains UNKNOWN because the candidate cohort is local 5×3×2 ms while the current #36 report uses production identities and 11×3×50 ms. No candidate passes the full original gate, so none is Correct or a champion.

`public27-adaptive` did not build: Lean reported `HAnd UInt32 Nat` inference errors twice at line 813. It has no timing or score. The overall CI failure is due to that build error; preserve the successful columns-all screen and adaptive failure separately.
