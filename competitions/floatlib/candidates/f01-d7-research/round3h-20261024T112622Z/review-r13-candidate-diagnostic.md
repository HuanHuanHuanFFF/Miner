# R13 candidate and diagnostic branch review

Reviewed at 2026-10-24 12:00 UTC. This was a read-only source and wiring review. I did not run Lean, CI, the diagnostic, Git operations, or tests.

## Candidate `f01-r13-preparation-convert`

The candidate manifest identifies parent df5c (`df5c61a0…fb172`) and five precise edits. I independently reversed those five replacements from the candidate: each replacement occurs once, and the reconstructed bytes hash exactly to the parent Kernel SHA. This verifies that all other source bytes remain unchanged.

The wrapper `R13NativePrep.toNative` delegates to existing `R2W01b.convert`; its proof uses the already-present unconditional `R2W01c.convert_eq`. The edits replace only the valid B-lane conversion and once-per-input A map, then rewrite `packB_get` and `output_prefix` proofs while retaining their original statements. Static reuse is reasonable: no new arithmetic identity or weakened obligation is introduced. The Lean integration is **not fully verified**: the existing report records a statement-only pass at run 40091246795, while the original full gate and four-obligation acceptance remain NOT_RUN.

All layout, packet width, zero padding, dot order, dispatch, NaN replay, and LowScale definitions are byte-identical to df5c. In `packB`, the `j < p` valid-lane branch alone uses the converter; the `else zero32` padding path remains unchanged. Source size is 248,615 bytes, leaving 7,385 bytes under the 256,000-byte limit.

## Profile path and original-gate boundary

The diagnostic is a direct `ci.py` dispatch of `f01-d13-cost-profile`, whose manifest selects `statement-only`; it does not pass through `public-suite.py`. `run-gates.py` sees a one-candidate diagnostic batch and omits the shipped baseline. `ci-diagnostics.py` replays only intake, policy, and statement stages, then labels its result `diagnostic_only=true` and `full_gate=false`. The workflow has a 45-minute job cap. The original public-suite 180-second statement timeout is not on this direct path.

The profile helper asserts the exact df5c Kernel SHA, official commit, public generator, profile seed, and 500,000-pair plan. It captures the original `Submission.c` from the sandbox upper layer, records the original compile/link traces and pre-build identities, writes instrumentation only into that disposable upper C, and reruns the traced compile/link commands with the original flags. It rejects missing traces, changed source identity, checksum mismatch, incomplete stage rows, or root-call-count mismatch. The uninstrumented whole-plan rows are retained separately; each case is then replayed twice with one-case plans. ELF/object files are not artifacts. This is diagnostic-only timing, not a clean D or performance acceptance result.

The local instrumentation check passes on an actual saved 42c generated-C artifact, with all selected return sites instrumented and negative synthetic checks rejecting bad checksums, missing stages, stack imbalance, wrong root calls, and exclusive time above inclusive time. Its fixture is explicitly **not exact df5c runtime evidence**. The exact df5c C symbols, per-case path coverage, and checksum replay remain unverified until the diagnostic run completes.

### Route and stage interpretation

In df5c, BMM dispatch is ordered as follows. The candidate's A-map and Packed10 conversion edits apply only to the final RowStream/Packed10 route.

| Runtime condition | Route | Relevance to this conversion candidate |
|---|---|---|
| Every A and B value satisfies `UnderflowZero.small` | Scan, then zero fill | Does not run the A map or Packed10 conversion |
| Otherwise `p = 2`, at least four output rows, and the size guards pass | R11CrossRows | Uses CrossRows preparation; does not imply RowStream A-map/Packed10 conversion savings |
| Otherwise `n ≤ 4` and `p > 2` | DirectContinuous | Bypasses RowStream A-map and Packed10 B preparation |
| Otherwise `n ≤ 4` or `p ≤ 2` | DirectSmall | Bypasses RowStream A-map and Packed10 B preparation |
| Otherwise, for nonempty dimensions | RowStream/Packed10 | Runs once-per-input A map and valid-lane Packed10 B preparation |

The `amap` matcher is broad (`Array_mapMUnsafe_map` under `Submission`). In the 42c fixture it selected one symbol, `…Array_mapMUnsafe_map___at___00Submission_RowStream_output_spec__0`; the exact df5c coverage inventory must confirm the same identity and show whether any other map symbols share the category. The profile aggregates timing by category, not by symbol, so if multiple map symbols are selected, their costs cannot be separated. `bpack` covers whole packing helpers, including loop, allocation, padding and branches; those totals are not fully removable by the converter substitution. Never add `amap + bpack` and call that attainable gain. Use exact source symbols, per-case dimensions and dynamic category call counts, and compare full-call costs before making an investment decision.

The instrumented stage counters include checksum/warm-up and all three timed inner sweeps, while the original benchmark rows carry the suite's own case result. Different process/cache context, timers, `printf`, and relink layout make the stage numbers diagnostic only. Fused/inline dispatch, uninstrumented helpers, and residual caller work remain UNKNOWN or inside the root interval; zero calls do not prove zero cost.

## Freeze and dispatch readiness

The diagnostic plan SHA matches its freeze receipt; the plan's profile-request SHA matches the request file. I also checked that all 23 files listed in `freeze-1324001.json` currently match their frozen local SHA-256 and byte length. The freeze includes the entry/current/suite helpers, profile request, wrapper Kernel and manifest, df5c Kernel, old generic row parser, execution-binding and sync helper, plus the shared execution files. `sync-ci-state.py` reads every frozen file back from the actual run HEAD before recording a run.

I did not inspect Git objects or remote state. Root should verify the frozen file set against the exact pushed HEAD before dispatch. One timeout margin needs an explicit decision: `profile-entry` has a 1,000-second cap, but its environment allows a 900-second statement stage and its profile loop has a 300-second budget. A slow statement stage could consume the entry cap before profiling finishes. The adapter-wide deadline is 1,500 seconds, `ci-diagnostics` allows 1,800 seconds, and the GitHub job cap is 2,700 seconds; failures remain diagnostic failures and cannot become performance passes.

## Bound evidence

All source and receipt hashes used for this review are recorded in `review-r13-candidate-diagnostic.json`. The profile request uses already-exposed public seed 1224016 for diagnostics; it is not an unseen confirmation. No profile runtime, new full gate, or performance gain is claimed.
