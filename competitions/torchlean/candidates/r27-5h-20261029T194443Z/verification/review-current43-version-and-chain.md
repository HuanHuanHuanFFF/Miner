# Current champion and report-chain review

Checkpoint: `2026-10-29T22:36:40Z`. Parent status last read at `22:32:34Z`; B5 run `40966581016` was active then. All API values below come from already saved R27 raw bytes and receipts; this review did not fetch or retry any endpoint.

## normalized_mlp: current #43

The latest saved boards response and normalized-MLP champion response share publication `a8167e489762b43fab49513568bb2ba9d218a0713213c7e645c1cfdebf312f21`. The current champion is promotion 28 / submission 43, source SHA-256 `4fef6fd4dbb39fe6fbf8fa85407228d6ebce9fb98dfbecf0d378e6f3b0df7c8b`, with `source_available=false`. The saved #43 report points to public submission 23, source SHA-256 `1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe`; the local-only source bytes and official receipt match.

The official report score is `#43/#23 = 0.9072362322024092`, qualifies with the guard passed, and uses config hash `647ef0dc529f8619a4c17533d87dee76001012ee349f502a6f6c0d720abbd95a`, equal to the latest normalized-MLP board hash. Its six cells and six pinned workloads match, using seed `1300210886`, 11 rounds × 3 repetitions × 50 ms per cell, and two completed production runs with matching identities and weights. The candidate/reference time conversion factor is therefore `#23/#43 = 1.10224874680368`.

The report summary omits `benchmark_identity` and `proof_identity`. B4 helper run `40964374666` supplies the current benchmark identity `6df065ba88f41fef36907eae008f839e5ffd7c0bb408a242daebafcaf3faa5cd` and proof identity `3a69968c7210ab18b325047e518ddfa942e642e21268a241e8693b075377bee6`; its dispatch and artifact manifests pass 11/11 outer and 10/10 inner file hashes. The helper run was diagnostics-only: prepare-agreement and word-modular passed; reciprocal and guarded-nonzero failed with elaboration errors / `sorryAx`. It is not a candidate gate.

Using the pinned R26/R25 `Config.plan`, replaying each of the six saved report plans with only `benchmark_identity` changed reproduces all six hashes in the current saved board response. All six one-build-limit negative controls reject. For normalized-MLP, the replayed hash equals both the current board hash and the #43 report config hash. The official source diff from `accb82b6e2adeda1b41a57a260d68fb3879c427e` to `27fb1d19c712ead50ad34b4ad0d4ba597161e616` lists only `validator/benchmark.py` and `tests/test_benchmark_budgets.py`; proof, contracts, Lean, and gate files did not change.

The #43 policy is now classified **INFERRED**, because the API omitted identity and it was reconstructed from the current official head, helper-run identity, live-board hash replay, and rejected negative controls. `champion-multiplier.py` can convert a future fixed-scorer row only when it binds current #43, public #23, the exact input seed/workloads/cells/timing, inferred benchmark/proof identities, and both complete production run contracts. No current candidate row exists, so there is no new champion result. Quick NativeOnly rows and any row missing the full input contract remain UNKNOWN.

The old #23/#12 report and B3 guard26 screen remain cross-version evidence. The guard26-v2 exact source `dced7848655a50a136750c1837b46f084a25ec26d13df72fe907d4a162bf1cb9` passed its full original gate under the old head. Its `1.1368014094608332x current #43 time` estimate is INFERRED across benchmark version, seeds, and environments, and is slower than the current champion. It is not a current-champion win.

## Mixer: current #36

The latest saved mixer response is bound to the same publication and identifies promotion 27 / submission 36, source SHA-256 `595a90fa2b6bc5d3657434fae7d1292b27910ef653da2b7f409ed9c34c956e2b`, with source unavailable. The existing official #36/#27 report ratio is `0.9622181669992014`, but its report config hash is `ab0fdb552d44b82ee286607a8ad0d914b6426615853ea3fe255878208a744f0e`; the current live mixer config hash is `4a9278fefa8f3799173bf1dfec50c7ea02819d3e312c819e267ecfeb89b5dbf9`. The current policy replay shows the benchmark identity changed, so the old measured ratio is not a current-version result. The ledger correctly keeps mixer calibration UNKNOWN.

B5 targets current #36 with public #27 as its calibration carrier. Its frozen plan uses head `27fb1d19c712ead50ad34b4ad0d4ba597161e616`, two seeds, and two selector variants. Both have `full_gate=false`; the generic schedule equality is described as reused but not compiled. B5 can be reviewed only as an exploration result until a current-identity #36 report edge is saved or source #36 becomes available for a direct pair. Do not report a retired #27 score as the current #36 multiplier.

## Other boards and current status

Only mixer and normalized-MLP have champion responses bound to publication `a816…f312f21`. The latest current IDs for overall, MLP, ResNet, and MobileNet remain UNKNOWN; their previous rows and timestamps stay in the history record. Current state and the fixed conversion interface are in [champion-only-record.json](champion-only-record.json). The report-chain audit and per-row input checks are in [current43-report-chain.json](current43-report-chain.json); the independent six-board replay and B6 source reconstruction are in [audit-batch6-static-and-live-policy.json](audit-batch6-static-and-live-policy.json).
