# B9 public23/public27 GEMM graft static review

Static review of the frozen candidate recipe only. The candidate has not been compiled or run through the original gate here; no CI was dispatched by this role.

## Frozen identity and construction

The current B9 plan hash is `15f477331026f648deafe1f218c20c75024eff2759dc3cb202c5d12941a99a77`. It targets only current mixer #36, using retired public #27 as its calibration carrier. The two saved official source receipts match public #23 (`1010c074…df0665fe`) and public #27 (`f92ee2c9…3481aa67`). The one candidate reconstructs in memory to SHA-256 `6fe5feb6cf0b919a9700f5f05264b1e98e24d7ee74b9d2853c1e55be866d4ada`, 252,719 bytes, with 3,281 bytes below the 256,000-byte cap. No source body is included in the verification output.

The v2 recipe hash matches the plan and pins its base recipe and proof-alias compactor. The base recipe checks exact public23/public27 hashes, requires ten donor declarations missing from #23, verifies the shared `Yo`, `Yq`, `Zy`, `Yn`, `Zi`, and `Z5` declarations byte-for-byte, checks that the `ZcC` interface statement matches, and asserts the alias difference is exactly `CQ` before rewriting it. It rewrites the donor graft's missing small-k `Ya3` call to the already-present `gemmWith Yn` path and connects the final kernel to `Ya3Q` with `Zc0Q`; the public23 `ZcC` interface supplies the existing linear side of the all12 proof. The v2 variant uses the all-positive-k proof path (`k ≥ 1`) and keeps `k=0` or nonfinite inputs on the existing proved fallback. The recipe checks the exact final candidate bytes.

The runner supports the plan's `extra_fetches` field. It stores downloaded donors under `TORCHLEAN_ROOT/r27-source-private/official-27.lean`; the graft recipe reads that pinned file when the runner does not pass donor bytes directly. The planned official verification branch is required before native build and timing. The saved freeze request selects standard 11×3×50 ms inputs and two fresh roots; this audit confirms the plan flags and runner branch, not the claimed OS entropy provenance.

## Proof and champion boundary

Unlike the B8 native-cost candidates, B9 preserves the original `theorem correct:Obligation kernels:=...` entry and changes the final simplification to include the graft's `Zc0Q`. The plan sets `full_gate=true` and `declares_correct=true`, so the exact candidate must pass the original all12 gate before any native measurement. Static proof composition is not an accepted proof; a gate failure means no timing for this candidate.

The latest mixer champion remains #36 / promotion 27, source unavailable. The saved #36/#27 report ratio is `0.9622181669992014`, but its config hash predates the live mixer config after the benchmark identity change. Any B9 local or standard candidate/#27 comparison can only be an INFERRED current-#36 multiplier through that old report edge; the strict converter remains UNKNOWN. Do not call public #27 the current champion or treat a CI success as official promotion.

The reproducible checks and exact dependency hashes are in [audit-batch9-gemm27-static.json](audit-batch9-gemm27-static.json). The B9 candidate uses the distinct roots `113424343` and `1997857825` in the standard 11×3×50 ms mode; the static review confirms those values are pinned, not their OS entropy provenance.

After the static review, Droot dispatched run `40972962791` from source commit `9b8b74f3d7839a4b38dcdd50d0b2b8d6ea3a5616dc`. The receipt freezes the plan hash, all three recipe/compactor files, the standard runner, and `allow_private=false`. The `FREEZE9-STANDARD-READING-BARRIER` says new inputs/results are acceptance-only until the run completes; this role checked only pre-freeze source bytes and the dispatch receipt, not run outputs. No terminal gate result exists yet.
