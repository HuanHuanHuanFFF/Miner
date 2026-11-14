# R27 batch 1 independent static review

Review time: 2026-10-29 20:10 UTC. CI run 40945451009 is already in progress. This review is pre-terminal; no runner result or native score has been analyzed.

## Frozen identity: PASS

- ci-plan.json and ci-plan-batch1.json are both 4,053 bytes and byte-identical, SHA-256 35eba486eb140f0773f2460e7d9e2108417ae21097e41d7137346020a3baeed4. This matches CI-QUEUE.json and dispatch-20261029T200227Z.
- The dispatch receipt names public repo HuanHuanHuanFFF/Miner, branch huan/codex-gpt, source commit 2da31f12bea8fce8540630bde77ce053931b8aa0, allow_private=false, and run 40945451009. All nine locally present files listed in its frozen_files map still match their recorded hashes.
- Frozen patch hash 00c60482ee119df85a78656c7e2ff33d2ad5931f3fbe7580d8e0789ee12602e1 matches the plan. The owned-source paths are separately hash-bound by the dispatch receipt.
- Plan candidate public27-inline-linear SHA-256 a74687f8a3485756e863bd4da64cd0cff160c8c8bb6636dcff9639ac04b2215f matches public27-inline-linear-receipt.json. It is the one declared-attribute change to submission 27. The reference hash f92ee2c9a29de78dc434ad158b7141c0e4b5a67a5a198a353d59a4703481aa67 matches the official retired submission 27 receipt.
- The plan's current target is mixer promotion 27 / submission 36 / SHA 595a90fa2b6bc5d3657434fae7d1292b27910ef653da2b7f409ed9c34c956e2b. The current champion report matches reference promotion 25 / submission 27 / reference SHA f92..., and its score 0.9622181669992014 matches plan champion.current_champion_over_calibration. Submission 27 is a retired calibration source, not the current champion.

## Runner boundary: PASS statically; runtime checks pending

- The runner checks the pinned official checkout at accb82b6e2adeda1b41a57a260d68fb3879c427e.
- It fetches the selected source through the official submission 27 source endpoint, checks the exact SHA, applies the frozen owned patch, and checks the resulting candidate SHA and byte count.
- Candidate and calibration reference are passed through the same added Lake target. The runner asserts MainExact bytes were copied exactly, captures compile/link/response arguments, normalizes only the target names, and fails on any other flag change. It also asserts protected official source files are unchanged. At terminal review, verify the recorded MainExact SHA equals the prior pinned R26 baseline b324bad32bc4ce449eb69be00e252163b77de4a0295736debe4081b53c4681ab and inspect all raw traces/flags.
- The exact official benchmark generator and run_binary are used; paired order alternates each round and every reference/candidate checksum is asserted equal. CPU identity, host, architecture, affinity and load are recorded.
- The runner explicitly sets current_champion_measurement=false. It records a native-only cohort and does not run the full original candidate gate.

## Performance boundary: this run is exploration only

The runner calls exact-config.py with --quick for mixer and uses local root seeds 27102901 and 27102903. It sets local build/run/benchmark budgets and runs the quick timing plan. The fresh official current champion report uses root seed 1593160531, six exact profiled workload seeds, 11 rounds x inner 3 x 50 ms/cell, and production AMD64 plus ARM64 measurements. These input contracts differ, so this run's candidate/submission-27 ratio cannot be multiplied by 0.9622181669992014 into a current mixer champion multiplier. Treat it as NativeOnly route feedback; current-champion comparison from this run is UNKNOWN.

For the exact official winner workload seeds, profiles, weights, cells, timing and environment identities, use official-report-chain.json. Config.plan hashes include initial_reference, so the live board hash can differ after the reference changes. The report-chain audit reconciles the visible cells/weights, environment identities and weights, workload seeds/profiles/weights, timing and admission inputs. The quick run still differs from the report plan and is not a calibrated comparison.

## Proof boundary

The plan scope is NATIVE_EXPLORATION_NO_FULL_GATE_REPLAY. Runner intake/policy calls cover only those two stages for the candidate. The three helpers are standalone elaboration plus optional named-axiom prints; none establishes the full gate. Submission.correct is declared unchanged but is not replayed, and CI success would not prove correctness. Candidate remains UNPROVED_NATIVE_RESEARCH_ONLY until a separate complete twelve-obligation gate binds the exact candidate bytes.

## Source handling risk

The source receipt marks retired submission 27 LOCAL_ONLY pending license-policy review. The workflow uploads only RUNNER_TEMP/torchlean-reports; the reference source is fetched inside the public hosted runner into RUNNER_TEMP/floatlib-upstream/r27-source-private. Sandbox build writes use the temporary overlay and the workflow cache saves only the pinned .lake dependency tree, so the source itself is not in the artifact path or cache. The public runner still receives the source bytes; publication/use authorization remains UNKNOWN under the local-only policy note. Record that boundary; do not claim the source was locally processed.

## Terminal audit waiting for collected artifacts

When Droot records terminal evidence, verify its original file-hashes.json and plan hash before scoring. Check candidate/reference exact source hashes, MainExact hash, every compile/link/response trace, full 6 cells x 6 workloads x 5 rounds per seed for this quick exploration, all timing/checksum pairs, CPU identity, alternating order and protected-source post-check. Preserve helper outputs as standalone diagnostics. Do not label this batch a current champion score or full proof.

### Report-plan reconciliation

The current mixer report config is ab0fdb552d44b82ee286607a8ad0d914b6426615853ea3fe255878208a744f0e; the live boards response has 4a9278fefa8f3799173bf1dfec50c7ea02819d3e312c819e267ecfeb89b5dbf9. The pinned Config.plan identity includes initial_reference, so this config-hash difference can be reference-only. The saved current report confirms submission 36 vs reference promotion 25/submission 27/hash f92ee2c9..., score 0.9622181669992014.

The report's exact mixer workloads are s0 typical seed 773756433 weight .25; s1 typical 540628936 weight .25; s2 scale 2807821738 weight .15; s3 scale 4117881962 weight .15; s4 boundary 790473172 weight .1; s5 boundary 2163708875 weight .1. Its root seed is 1593160531. The batch1 root seeds 27102901 and 27102903 generate different sub-seeds and use quick timing. The report factor cannot calibrate this exploration run.

The saved report audit reconciles every exposed non-reference dimension: model-to-cell weights, environment IDs/identities/weights, workload profiles and sub-seeds, timing, admission, and the exact current-to-predecessor report edge. proof_identity and benchmark_identity are not exposed by these API responses. A later candidate/predecessor score must use the exact report config and inputs, or remain UNKNOWN.

### Updated report input and config identity check

The official-report-chain audit now imports the pinned multiseed.py only after verifying Git blob 299b2e77db596a2720db3d54c2df46b3e5d2c3b3 and SHA-256 f171929b08cce37d848e736bb1d3c0bb422daeda1bbbd0da2ba3707d43d19341. All six official report workload lists exactly match workloads(root_seed) from this pinned generator; both production environment records carry the same six workload descriptors, seeds, profiles and weights. The score reconstructed as the geometric mean of the two environment scores and boards.raw weights matches the decision.score exactly on all six reports.

For the current mixer report, the official root seed is 1593160531, with s0 typical/773756433/.25, s1 typical/540628936/.25, s2 scale/2807821738/.15, s3 scale/4117881962/.15, s4 boundary/790473172/.1 and s5 boundary/2163708875/.1. This differs from batch1 roots 27102901 and 27102903.

The pinned Config.plan hash includes initial_reference. Therefore the live-board/report hash difference is not, by itself, a failure. The report-chain audit reconciles all exposed dimensions—model/cell weights, production environment identity and weights, generated workload seeds/profiles/weights, timing and admission—and binds the report edge to the exact current promotion and predecessor source. The API does not expose proof_identity and benchmark_identity. A final inferred result must be tied to the exact report plan hash and inputs; any unbound plan field leaves the score UNKNOWN.

## Batch 1 terminal raw audit (run 40945451009)

I re-read the root status, requests and public board after the run completed, then ran the existing narrow audit-native.py to a receipt in this verification folder. It imports R26's reviewed raw-file primitives and the unchanged pinned R25 config/multiseed/scoring sources; no new scoring wrapper was created.

- CI terminal: success; exact source commit 2da31f12bea8fce8540630bde77ce053931b8aa0. The fetched artifact has 54/54 outer files and 53/53 inner files passing their SHA-256 manifests, with no missing or unexpected files. The exact plan, dispatch and run identities match.
- Source identities: candidate a74687f8…04b2215f; reference retired submission 27 f92ee2c9…3481aa67; current mixer champion remains submission 36, source 595a90fa…c956e2b. No direct current-source pair was run.
- MainExact SHA-256 is b324bad32bc4ce449eb69be00e252163b77de4a0295736debe4081b53c4681ab, matching the prior pinned R26 byte-copy baseline. Compile, link and response-file arguments all match after only target-name normalization. Protected official files and original Lakefile/MainExact remained unchanged.
- Per seed: 180 paired rows, 360 ns values, 180 checksum pairs. Across both seeds: 360 pairs, 720 ns values, 360 matching checksums. Alternating order is reference-first on rounds 0/2/4 and candidate-first on 1/3. CPU identity/machine/architecture/affinity are consistent across seeds: 2ce5abb04d8b8d106a99eeacff32cdd36c4a2a287452e1942dd47af0516aa884 / runnervm48cm3 / x86_64 / CPU 0.
- Pinned scorer candidate/retired-27 ratio is 0.9980966843843952; lower gain bound is -0.0017665562284339908; per-cell median guard passes. Outcome is above the official .97 bar. Worst per-seed median guards are 1.04405 (s0|mixer:b1:normal) and 1.00853 (s5|mixer:b4:wide). The slowest retained single pair is seed 27102901, round 4, s5|mixer:b4:normal: candidate 2,845,983 ns vs reference 2,375,510 ns (1.19805x), checksum equal. It remains in the raw records.
- Applying the official current-36/retired-27 report factor 0.9622181669992014 yields 1.0372872999239722x current champion time. This is INFERRED quick cross-environment/seed route-planning evidence only; it is not a direct current-source run, production-config result, qualification or promotion.
- Helper core and word runtime logs exit 0 with only allowed axioms printed. PrepareCore exits 1 with four unresolved elaboration goals (split_ifs on a no-if goal, a large-state pure/run equality, and two forIn/fold projection equalities). These are standalone helper results, not the original twelve-obligation gate.
- The 53-file artifact manifest contains no Lean/C/assembly source-like files, and a bounded scan of build/helper logs found none of the known upstream source definition markers. The official retired source was still fetched inside the ephemeral public runner; license/use policy remains UNKNOWN.

Independent audit receipt: audit-native-40945451009.json. Root summary: evidence/40945451009/root-native-audit.json. The candidate remains UNPROVED_NATIVE_RESEARCH_ONLY.

Cross-check: my rerun of the frozen audit-native.py produced JSON structurally identical to root-native-audit.json; both receipts have SHA-256 4635c884f668285436182fa023a0946277160f4670108dad79e1333923833c40.
