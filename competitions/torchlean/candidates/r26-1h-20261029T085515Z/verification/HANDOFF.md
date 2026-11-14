# R26 Native-only verification handoff

## Current stage

**Phase 1 complete; phase 2 awaits the root-owned bridge and saved run artifacts.** This folder is the only write scope for this role. The task and research files outside it remain untouched.

## Findings from R25

- `verification/analyze-results.py` is not reusable as a whole: it binds paths and candidate schema to R25, uses R25 summary proof states to decide whether measurement inputs exist, and conditions score rows on the R25 proof/measurement records. Its generic per-result code is not enough to certify R26 source identity or the native-only boundary.
- `verification/exact-policy-preflight.py` is an intake/policy-only audit. Its own output marks statement/kernel/axiom checking and native measurement `NOT_RUN`; it is not a proof result. R26 must not turn this into `Correct` or `FULL_ORIGINAL_PROOF_GATE_PASS`.
- `scripts/ci-r25.py` records the reference execution shape: official quick config, request generation from pinned modules, then the original `-m benchmark --request ... --candidate ... --reference ... --result ...` invocation. R26 bridge review will inspect its actual argv and flags against this baseline, not assume the R25 environment values are automatically correct for a new target.
- The prior R25 analysis attempt's Windows default-temp `WinError 5` is documented in its handoff. R26 analysis will read extracted evidence in place; if an archive requires a temporary config file, use a workspace-local `.local-maintenance` path and retain any failed derived JSON.

## Minimal reusable analysis design

Use a small R26-specific analyzer that imports only the frozen R25 `config.py`, `multiseed.py`, and `scoring.py` modules after verifying their Git blob IDs. Do not copy the 47 KB R25 analyzer or use its proof-gated candidate loop. `scoring.validate_result(request, result, weights)` supplies the original request-hash, workload, alternation/order, full-cell, positive-nanosecond, and paired-checksum checks; `scoring.assess(plan, measurements)` supplies the original overall aggregation. The R26 wrapper must separately check saved run terminal state, the frozen plan and two source hashes, all raw `file-hashes.json` entries, exact target/flags/source identities, actual source filenames, and consistent CPU provenance before calling the scorer.

Frozen scorer dependencies, read-only at `R25/verification/pinned-source`:

- `config.py`: 6743c5c0060b7babab5155ffe1e0dc94dbf8a742
- `multiseed.py`: 299b2e77db596a2720db3d54c2df46b3e5d2c3b3
- `scoring.py`: f5e1b500bc3976764eea0451c500907e08e17dda
- `timing.py`: 5b52a105a53089369977a7148541885904496d1c (not needed unless the bridge's saved schema requires it)

Do not fall back to a live `round-plan.json` if the saved artifact plan is missing. In that case record the score as `UNKNOWN`. Candidate label remains `UNPROVED_NATIVE_RESEARCH_ONLY`; only `originalshipped`/`retained` can be described as previously gate-accepted references. A native checksum/score result does not prove the new candidate or certify the original gate.

## Phase 2 gate

At the next natural checkpoint, inspect the root-owned bridge/READY and request/status files once. Before any analysis, check exact candidate and baseline SHA/byte identity; target inputs and `MainExact.lean` byte identity; official benchmark/request generator use; actual command arguments and compiler/native flags; and the unmodified official gate/contracts. If any input is absent or ambiguous, preserve `UNKNOWN` and record the missing evidence in this folder.

After the root stores a terminal run in `evidence/<run>`, verify the exact terminal `ci-run.json`, every listed raw file hash and saved plan, then validate the full 30 cells × 6 workloads × 5 rounds × 2 seeds with all timing/checksum pairs, source filenames, and same-machine CPU identity/order. No missing values become zero. Report only `NativeOnly` diagnostics; proof remains `NOT_RUN` for this candidate.

## Checkpoint observations (09:08–09:10 UTC)

- The root status is still `INITIAL_NATIVE_BRIDGE_PREPARATION`; `active_CI` and `current_requests` are empty, and `development/ci-bridge/` has no files. No analysis run or bridge preflight has started in this role.
- Native source owner now lists three unproved/uncompiled options: `fp1` (e6fbf941…96d034), `fp-word2` (549a1d6c…a0ac57), and `fp-word-conv3` (08d876ca…40fe64). All receipts state `Submission.retainedCorrect` covers only retained kernels. The saved run plan must determine which frozen sources belong to the run; do not infer selection from the mutable source READY file.
- Native model preflight is explicitly Python exact-model evidence only; Lean/native compile, all-input proof, and official full-model run remain `NOT_RUN`/`PENDING_ROOT_RUNNER` there. It does not replace the bridge or native-result audit.

## Budget and authority

- Common round window: 2026-10-29 08:55:15–09:55:15 UTC; stop new long experiments at 09:38 UTC. Exact role start time was not captured, so it remains `UNKNOWN`; first durable verification artifact was written at 09:05:30 UTC.
- Accepted work: inspect saved sources/configuration, create and run a narrow analyzer over already-collected public runner evidence, and write verification receipts in this folder only. No local Lean/native build, no CI launch, no Git operation, no child agent, no formal submission or funds. Root owns the only Git/CI actions.
- Actual token/cache/model CPU and continuous model CPU remain `UNKNOWN`; elapsed wall time will not be reported as model CPU.
- Local source anchors: `retained.json` records the gate-accepted R25 source `norm-cache-proof1` at SHA-256 `bcb8172381346b26afc69e2582442510865f74415c657d7ee208045474ca1ea7`, and shipped source hash `9b2d940338dfcc42a38443324d63041a27cc9b5df1b18675103c7d67934d1df8`. No local `competitions/torchlean/references/` directory exists, so shipped-source byte identity must be established from the saved runner evidence/official checkout; do not claim a local rehash.
- Expected cohort arithmetic per candidate/reference comparison: 30 × 6 = 180 expanded cells per round; 5 rounds = 900 paired rows per seed; two seeds = 1,800 paired rows, 3,600 reported nanosecond values, and 1,800 checksum pairs. Any mismatch is incomplete/failed evidence, never imputed.

## Single bridge preflight (09:17 UTC)

Static review is complete; runtime confirmations remain pending.

- The selected plan hash is `2cc6a756…3a3c9c`. Both `ci-plan.json` and `ci-plan-batch1.json` are 1,602 bytes and byte-identical. However, READY says `ci-plan-batch1.json` while both `client.py` and `runner.py` load and freeze `ci-plan.json`. This is safe for the current matching bytes but the READY filename should match the executable input before dispatch.
- The two selected candidate files match the frozen plan hashes and byte counts: `fp1` `e6fbf941…96d034` (49,755 B) and `fp-word-conv3` `08d876ca…40fe64` (60,137 B). The retained reference source matches `bcb81723…ca1ea7` (42,013 B), recorded by R25 as full original 12-obligation gate accepted. The plan runs that original reference proof again.
- This batch compares both prototypes to retained only. No same-run `originalshipped` reference is included; the local R25 retained record contains only a historical shipped comparison. I have recorded this as a scope gap rather than conflating prior results with a direct R26 pair.
- Workflow dispatch is gated to public `ubuntu-24.04` and `allow_private=false`. The `torchlean_r26` job matches the helper's `floatlib` + `__torchlean_r26__` dispatch inputs. The helper freezes `ci-plan.json`, runner, workflow, prep script, selected candidate sources, and reference against the current commit.
- The runner uses the pinned official checkout; verifies the retained source with the original proof CLI; copies `bench/MainExact.lean` byte-for-byte into one added `r26Native` target; uses unchanged official intake/policy, original config/workload generator and `benchmark.run_binary`; records and asserts original-versus-owned compile/link/response argument equivalence after only expected target-name mapping; and checks protected original files and Lakefile unchanged. Candidate and reference pass through the same target builder.
- The selected candidate sources contain `retainedCorrect : Obligation retainedKernels`; no `correct`, `originalVerifyExact`, `fastkernels`, `AX6`, or `#print axioms` match was found. The bridge does not run the original proof gate on prototypes and labels them unproved. It must remain reported as native-only even if compilation and finite checksum comparison succeed.
- `runner.py` does not compute the overall score. Once immutable runner output is collected, the R26 analyzer must use the pinned R25 `scoring.assess` path and independently check all 1,800 pairs / 3,600 ns values / 1,800 checksums per complete candidate-reference cohort across both seeds. Actual source hashes, `MainExact` hash, raw flag args, CPU identity/order, and every output file hash are still runtime checks.

Detailed fields and file hashes are in `preflight.json`. No CI or local build was started by this role.

## Revised frozen input and dispatch (delta review at 09:30 UTC)

The first review's plan and runner were replaced before the dispatch receipt was written. The active public workflow dispatch used run `40849705068`, source commit `9a2e9451fc0ab16bfea3584423e9ff5f16afe214`, plan SHA `f2b3bc9e…b9cc6de1`, and runner SHA `2029d04d…ed8411a8`. At dispatch the receipt said `in_progress`; the root status file still showed `active_CI: []`, so that status file was stale. I did not query GitHub or send a message.

This run freezes one candidate, `fp-word-conv6` (`fp-word-conv6-local/Kernel.lean`, 60,479 B, SHA `ad9bde3e…b4b22540`) against retained R25 `norm-cache-proof1` (42,013 B, SHA `bcb81723…ca1ea7`). The candidate receipt says its only theorem is `retainedCorrect` over `retainedKernels`; the source now uses local instances after the prior `fp-word-conv3` global-instance policy rejection. My direct source scan found no new `correct`, `originalVerifyExact`, `fastkernels`, `AX6`, or `#print axioms` occurrence. It remains unproved.

The revised plan adds `order-key-policy1` and `finite-widen` as `measure:false` proof diagnostics. The runner compiles `VerifyExact` for those sources after the native cohort, emits raw statement logs, and labels the rows `RAW_STATEMENT_DIAGNOSTIC_ONLY_NOT_FULL_GATE`; it does not pass them through as candidate proofs or helper-axiom acceptance. They are separate from the measured candidate and retained reference.

The revised native target, original `MainExact` copy assertion, flags trace checks, benchmark generator/`run_binary` path, alternating paired order and checksum assertion remain as reviewed. The scorer still needs to be run from saved artifacts; the bridge itself does not aggregate the overall score. This batch still has no direct `originalshipped` pair.

The R26 analyzer's first preflight hash anchors are now historical. I am switching its current-run anchors to `preflight-delta.json`; the saved artifact plan remains the only scoring input. Full runtime verification awaits a terminal CI receipt and the downloaded artifact.
- Plan filename metadata remains inconsistent: `CI-BRIDGE-READY.json` says `ci-plan-batch1.json`, while `runner.py` and `client.py` read/freeze `ci-plan.json`. At the delta review both files were exactly byte-identical (5,435 B; SHA-256 `f2b3bc9e…b9cc6de1`), and the runner artifact plan is copied from `ci-plan.json`.
- R26-specific analyzer entry is `verification/analyze-native-only.py`; it selects a saved preflight by the artifact plan hash/run ID, uses only pinned R25 `config`/`multiseed`/`scoring` blobs, validates outer and inner hashes, raw per-side round files, all 30×6×5×2 timing/checksum rows, same CPU identity/affinity, and computes the original quick score against the saved reference. It also records optional old-source `proof_diagnostics` separately as raw statement diagnostics. Syntax parsing passed at 09:32 UTC; no R26 result data has been analyzed yet, and the analyzer does not launch CI or Lean.
- Analyzer refactor after the frozen-plan delta review now imports only the pinned R25 `load_pinned_modules` and generic `measurement_check`/score functions instead of duplicating the R25 framework. The R26-specific entry is 20,808 bytes; its syntax was parsed at 09:35 UTC. It has not been run because the first R26 artifact is not collected yet.

## First CI terminal audit (run 40849705068)

The saved terminal receipt and both raw hash layers were verified. The workflow and `torchlean_r26` job concluded `failure`; the artifact's outer 7-file manifest and runner's inner 6-file manifest both match exactly. `summary.json` records `ModuleNotFoundError: No module named 'loguru'` while loading the original benchmark modules after setup.

Only `setup` and `setup-check` ran successfully. `summary.results` is empty; the reference proof, candidate native compilation, and candidate measurements are all `NOT_RUN`. No candidate score was computed (`UNKNOWN`), and the runner did not produce `originals_unchanged` post-check evidence. This is a bridge import failure, not a candidate algorithm result. Full receipt: `verification/analysis-40849705068.json`.

A second dispatch receipt appeared at `evidence/dispatch-20261029T093711Z`; it was created before the 09:38 experiment cutoff. Its run and revised runner need their own frozen-source hash check before the collected result can be analyzed.

## Second dispatch delta review (09:40 UTC)

Run `40851060907` was identified at 09:37:13 UTC on commit `edd41c939a772d634dc118a9201dc1946351369d`; its dispatch receipt said `in_progress`. The new runner resolves the first failure by adding the official venv's ABI-specific `site-packages` directory before importing the original benchmark modules and asserts that directory exists. The change does not modify the original proof gate, target, measured source, or compiler/linker flag checks. The current selected source and retained reference hashes are unchanged, and both old sources remain `measure:false` raw diagnostics.

One metadata issue remains: `CI-BRIDGE-READY.json` still names `ci-plan-batch1.json`, while the runner/client read and freeze `ci-plan.json`. The two files are no longer byte-identical, though the reviewed fields selecting the source, reference, seeds, public billing, and separate proof diagnostics match. The current run's actual frozen input is `ci-plan.json` at SHA `65028ca5…a6f6599`; analysis will use its downloaded artifact copy only.

The first run's original artifact files all passed both hash layers, and its failure receipt is saved as `analysis-40849705068.json`: import failed before reference proof, native compilation, or measurement. No score was produced. The second run remains pending; there is no result to analyze yet.
- Final failure audit receipt for run `40849705068` is `analysis-40849705068-v3.json` (the earlier derived JSON attempts are preserved). The final receipt reports exact outer/inner hash PASS, `loguru` import failure, reference proof `NOT_RUN`, candidate build `NOT_RUN`, measurements `NOT_RUN`, score `UNKNOWN`, and original-source postcheck `UNKNOWN`.

## Second CI terminal audit (run 40851060907)

The terminal `ci-run.json` is `failure`; it was collected into `evidence/40851060907`. Both outer and inner file hash manifests pass (3 outer files, 2 runner files). The artifact contains no `plan.json`, so the audit explicitly did not fall back to the live workspace plan. Its expected frozen plan hash is recorded from the dispatch receipt/preflight as `65028ca5…a6f6599`.

`summary.json` has `error_type: AssertionError`, an empty error string, zero commands and zero result rows, with `started_at_utc=2026-10-29T09:39:19.382887Z`. The frozen run cutoff was `2026-10-29T09:38:00Z`. The runner's first `main()` action asserts the current time is before that cutoff, so the timestamp and empty command list match a cutoff rejection before reference proof, tool imports, native compilation, or measurement. The venv `loguru` import fix was therefore not exercised. Score remains `UNKNOWN`; no missing sample values were filled.

The final no-plan receipt is `verification/analysis-40851060907-v2.json`. `development-status.json` still said `NATIVE_ENV_REPAIR_CI_RUNNING` at 09:46 even though the local terminal receipt and downloaded artifact already showed failure; that status was stale. Root's last status said new experiments were closed at 09:38. No third dispatch is present in the evidence tree at this checkpoint.

## Final verification checkpoint (09:48 UTC)

Fresh final audits now exist at `analysis-40849705068-final.json` and `analysis-40851060907-final.json`; the prior derived attempts remain preserved. Both receipts independently rechecked the original downloaded bytes. Run 40849705068 has outer/inner hash `PASS`, the exact `loguru` import failure, and no reference proof/native compile/measurements. Run 40851060907 has outer/inner hash `PASS`, no saved artifact plan, a recorded runner start after the frozen cutoff, empty command/result arrays, and no proof/native compile/measurements. The final analyzer syntax and every verification JSON parse successfully. Neither run produced a score; both remain `UNKNOWN`.

The second run was submitted at 09:37:13 but the runner began at 09:39:19, after the 09:38 cutoff, and hit its early assertion before saving `plan.json`. The missing-plan audit used the matching frozen preflight receipt only to verify the expected plan hash; it did not read the live plan or substitute any model results.

## Post-cutoff dispatch observed (09:52 UTC)

A third public workflow dispatch was created at `2026-10-29T09:50:23Z` (run `40852769757`), after the frozen 09:38 stop-new-experiments cutoff. Its dispatch receipt says `in_progress`, `allow_private=false`, plan SHA `985f2bbf…e6ee1e`, and runner SHA `bf1c8d49…40e93d42`. This is outside the stated window; it is not covered by either preflight review. I did not dispatch or cancel it. No terminal artifact exists in the local evidence tree at this checkpoint, so it cannot be scored. Any later artifact should be reported as an unreviewed post-cutoff run with score `UNKNOWN` unless a corresponding preflight receipt is present.
- At 09:54, root status classifies run `40852769757` as an already-launched same-source/same-input repair and marks it `IN_PROGRESS_NATIVE_STEP`; it is still collecting no artifact locally. The dispatch receipt is a distinct run with new source commit `12e6d73f…a74c0043`, runner SHA `bf1c8d49…40e93d42`, and plan SHA `985f2bbf…e6ee1e`, while candidate/reference/seed inputs match the preceding batch. It has no matching verification preflight receipt yet, so any eventual output remains unscored until its raw terminal artifact is checked against that new frozen version.

## Third dispatch / completed run 40852769757 (post-cutoff)

Run `40852769757` finished successfully and its artifact directory is now collected. The status file calls it a same-source/same-input repair, but its dispatch is a distinct run from commit `12e6d73f…a74c0043` with a new runner (`bf1c8d49…40e93d42`) and plan (`985f2bbf…e6ee1e`). The artifact plan moved `start_cutoff_utc` to 09:55, while the R26 round deadline stayed 09:55:15. The runner began at 09:52:30 and finished at 09:59:38, after both the original 09:38 stop-new-experiments cutoff and the common round end.

The runner completed one `UNPROVED_NATIVE_RESEARCH_ONLY` candidate against the retained R25 reference; the source hash is unchanged. It reports the retained reference full proof passed, candidate proof `NOT_PROVED_NATIVE_ONLY`, original sources unchanged, and complete measurements. The target is the same one-target native-only build with original `MainExact` byte copy and raw flag comparisons; the venv fix adds the official site-packages path. The two old proof sources remain separate `measure:false` diagnostics. I am auditing the artifact's original file hashes, raw rounds, checksums, same-CPU identity/order, and original pinned score now. Any resulting score will be explicitly labeled post-cutoff NativeOnly evidence.

## Third run artifact audit and NativeOnly result (10:03 UTC)

Run `40852769757` reached CI conclusion `success`, and the downloaded artifact is now fully audited: all 61 outer files and 60 runner-manifest files match. The saved plan, frozen runner, source paths/hashes, request identities, raw `run_binary` side files, compiler/link/response arguments, alternating order, checksums, CPU identity, and original scorer inputs all passed the R26 analyzer.

The measured candidate `fp-word-conv6` (`Kernel.lean`, SHA `ad9bde3e…b4b22540`) was compared only with retained `norm-cache-proof1` (`Kernel.lean`, SHA `bcb81723…ca1ea7`). The two seeds each contain 900 paired rows, 1,800 nanosecond values, and 900 matching checksum pairs; total 1,800 paired rows, 3,600 ns values, 1,800 checksum pairs. Both seeds show the same machine identity, host, architecture, and CPU affinity. Compile, link, and response-file flags matched the original after only target-name normalization.

Pinned original quick scorer result: candidate/retained aggregate ratio **0.7854×**, lower bootstrap gain **20.28%**, but **guard failed** (threshold 1.10). Each seed has 36 of 180 per-workload cells above the guard; the worst is `mlp:b1:sparse` at 3.28× and 3.78× respectively. This is an overall exploratory ratio with a material per-cell regression, not a stable-win or champion result.

The retained reference passed the full original proof replay (`stage=axioms`, start/end verifier fingerprints match). The new candidate remains `NOT_PROVED_NATIVE_RESEARCH_ONLY`; the original proof gate was not run for it. The two R25 proof-diagnostic sources each exit 1 under the raw `VerifyExact` diagnostic and are not proof acceptance. No same-run originalshipped or current-champion comparison exists.

This complete diagnostic was collected after the original 09:38 stop-new-experiments cutoff; runner time was 09:52:30–09:59:38 UTC. Preserve it as post-cutoff NativeOnly research evidence. It does not count as a within-window result or establish a candidate correctness/proof claim. Final receipt: `verification/analysis-40852769757-final.json`.
- Compact final audit with the configured 1.10 guard threshold is `analysis-40852769757-final-v2.json`; it preserves the earlier full receipt. It confirms a 0.7854107× aggregate ratio vs retained and 20.28% lower bootstrap gain, but 36/180 per-workload cells per seed exceed the guard; worst is `mlp:b1:sparse` at 3.280× and 3.775×. The result is guard-failed, and remains post-cutoff NativeOnly evidence only.
