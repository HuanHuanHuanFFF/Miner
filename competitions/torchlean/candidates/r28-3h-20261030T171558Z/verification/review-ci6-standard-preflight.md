# CI6 isolated standard confirmation preflight

Captured 2026-10-30 19:57 UTC after reading request `195300-standard-freeze-isolation.md`, the current plan, CI-REQUEST and status. The batch6 plan is READY with no active run. The full source/seed audit is in [audit-ci6-standard-preflight.json](audit-ci6-standard-preflight.json); exact group inputs remain restricted to Droot/verification until the whole group finishes, so this summary does not repeat seed values.

## Exact sources and proof boundary

- The frozen norm26 candidate rebuilds exactly to `79615bd5c5c697d27631b999d7211c41dc5d0c4374cd9604324b417b1ad417d7`, 255,514 B. The same exact source hash passed the original all12 gate in CI3: its saved summary/verdict hashes match this plan, stage `axioms`, and verifier fingerprint stable. The confirmation runner correctly sets `full_gate=false` for this exact previously gated source; this avoids replaying proof while preserving the exact-source proof link.
- The input-zero companion rebuilds exactly to `29e71174da3a86aa6607cca050618256bf38b3aafadf4a617cd4c62497653eae`, 253,816 B. The batch6 recipe differs from the prepared native recipe only in the adjacent Norm26 loader path; the rebuilt candidate bytes match the prepared kernel file. It has no `correct` and remains `EXPERIMENT_ONLY_NO_CORRECT_NOT_ADOPTABLE` with no gate.
- Both recipe hashes, the freeze receipt, the root plan hash `68c6633d07b021d4de3399cd1be3a5555101250292b3faf62b929d2e5559884d`, and CI-REQUEST candidate hashes match.

## Current reference and isolation

The plan is bound to a fresh 19:52:15 official six-board snapshot. The Mixer response and boards hashes match the raw-response receipts; current Mixer is still #56 / promotion 34 with saved ratio `0.8574912831` against the retired #36 calibration. This is a snapshot for the experiment, not an official promotion claim.

The six verified current IDs in that snapshot are overall #59, MLP #33, Mixer #56, ResNet #64, MobileNet #57, and normalized MLP #51. MobileNet #57's source hash and ratio match the preceding CI5 snapshot, so its earlier current-champion conversion remains unchanged at the time of this refresh.

The standard group uses two new, previously unused seeds, 11 rounds, 3 inner iterations and 50 ms per cell. Full seed values are only in the restricted machine audit. Keep them and any per-seed inputs/results away from research/native until the whole group completes.

The 1,800-second driver can run past the 20:15:58 research cutoff if queued at the last allowed start. Root should dispatch early enough to collect before cutoff if possible; any run already started by cutoff can be collected to completion. The NativeOnly input-zero result is experimental and cannot establish proof or adoption.
