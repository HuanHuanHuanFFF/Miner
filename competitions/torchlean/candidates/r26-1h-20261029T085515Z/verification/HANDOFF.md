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
