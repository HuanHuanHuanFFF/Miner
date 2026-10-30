# R27 batch 2 terminal verification receipt

Checked after reading Droot's 20:35:37 development-status, requests and shared status. CI run 40948208583 is terminal failure; no candidate timing was produced.

## Frozen run and raw artifacts

The plan hash is 459f2e3ccb8a3ba256d8dbeaff97c54e66fc385ece40f127591922b9986e87ff and dispatch commit is bfee42632fd7622375292e98318f5ea16284c3fe. Dispatch source identities bind current normalized_mlp #24/submission 23 and retired predecessor #21/submission 12. The latter remains a calibration source, not the current champion.

The existing narrow audit-native.py was rerun into audit-native-40948208583.json. Its JSON is structurally identical to evidence/40948208583/root-native-audit.json; both SHA-256 values are ff157e5a729a871c10ac7f07a848478d299c143e77d87336404c513d63e2fcb9. The fetched artifact has 24/24 outer and 23/23 inner hashes passing, with no missing or unexpected files. Source preservation passes. MainExact SHA-256 is b324bad32bc4ce449eb69be00e252163b77de4a0295736debe4081b53c4681ab. The calibration reference compile/link/response arguments match after only expected target-name normalization. No candidate binary or candidate flags were produced.

The artifact manifest has no Lean/C/assembly source-like files, and a bounded scan found no known source-definition markers. The official submission 12 source was fetched into the public runner, so source-use permission remains UNKNOWN even though no source body appears in the artifact.

## Candidate and proof outcomes

- public12-guard26 (5fcb3b893600993c1109de8df5849e8765c9562c2e57eeb2c9f052e21cae2b25) reached the unmodified official full verifier. The verdict is passed=false at stage=statement after 68.29s, with deterministic 200000-heartbeat timeouts in isDefEq/tactic execution around lines 1992-2122. The gate did not reach kernel or axioms. The verifier fingerprints match, but that does not turn the failed statement into proof acceptance. The raw full-gate statement log and verdict remain in the original artifact.
- public12-norm-prep (61b98cc582a48723c0f184e49420fe97b449731a145d47d1920d3b871e2e76aa) is NativeOnly and failed its native build: “No goals to be solved” at 1708 and a missing r27SquareLoop_eq rewrite at 2333. There are no timings.
- RealStrict helper compilation passed five named roots with allowed axioms. WordModular64 helper compilation failed at block_exact after a 200000-heartbeat timeout; earlier roots printed, but the final root reported sorryAx in the failed module. Neither helper result is a full candidate gate.

No candidate score or current-champion multiplier exists for batch 2. Current candidate eligibility is UNKNOWN/NOT ESTABLISHED; the failed full gate blocks guard26 and norm-prep has no full gate. The frozen plan's top-level scope and human_performance_target strings conflict with per-candidate fields; use the actual board/current champion fields and full_gates entries when summarizing.

## Continuation

Keep the statement timeout, norm-prep rewrite failure and WordModular block_exact timeout as separate failures. Any repair needs a new frozen candidate/source hash and a fresh full gate for the changed proof-bearing source. No CI was launched or modified by this verification role.

Artifact containment: the 23-file inner manifest contains no Lean/C/assembly source-like files, and a bounded scan of all artifact bytes found none of the known submission 12 definition markers or temporary source names. The source itself was fetched inside the public runner, so its local-only authorization remains unresolved despite the artifact scan.

Raw failure detail: full-gate-raw-statement.log has seven error headers: heartbeats at Submission.lean 2119 (isDefEq), 2122, 2013 and 1998 (tactic execution), 1992 (whnf), then unknown constant Submission.Ya7Ge at 2223 after the proof failure, followed by build failed. No finite counterexample or proof acceptance is reported. Norm-prep build.log has the two errors 1708 (No goals to be solved) and 2333 (r27SquareLoop_eq pattern not found), then build failed.

Receipt hashes: CI-RESULTS-BATCH2.json SHA-256 4af05fb562299438bcdde6964f55c58c4cb54caf0ef0bc61fe7bb2850d186abc; root-native-audit.json ff157e5a729a871c10ac7f07a848478d299c143e77d87336404c513d63e2fcb9; full-gate-verdict.json a2257ff8170beecafd6712e63ac468b1d54d28212ad907b9efbcfac3e43c3c93; full-gate-raw-statement.log 276e4839409802f4b40eebd8599494480e6e6d651af471d5a96dded04913ee31.
