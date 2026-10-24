# R13 read-only tool and evidence preflight

Reviewed at 2026-10-24 11:33:38 UTC. This review is limited to preflight and migration guidance; no cohort, CI, state, model, Git, Lean, or heavy-tool action was taken.

## State and frozen inputs

R13 `round-plan.json` is explicit: the scoring baseline is `f01-d12-scalar-combined` (`df5c61a0…fb172`, 248,144 bytes), while the estimator control remains `f01-r8-combined-result-guard` (`41bce485…ce9a7`). Keep the current estimate frozen at model SHA `5d946420…8a031f`; the plan's official champion is #285 as carried from R12. R13 retains three independent groups, 25 rounds, the public-v2 suite, whole ratio ≤0.97 and bootstrap `gain_p05 > 0`.

R12 is a successful precedent, but its scoring baseline was D11/6c (`6c2d394d…4277d`), so its cohort and adopter cannot be copied unchanged. Its estimator control was already 41 and remains valid. The R12 retained-estimate freeze is the relevant no-recalibration contract for current DF: it binds source df5c, six full-gate run IDs, anchor `d7bcc…1cfbc`, estimator SHA `fe926…46983`, model SHA `5d946…8a031f`, and explicitly records `no_numeric_model_change=true`. Preserve the frozen estimate values: add 1.016106, mul 1.126239, sum 1.140537, bmm 1.844002, whole 1.177389. These are inferred cross-suite projections; direct same-suite champion timing/admission remain UNKNOWN.

The state file's top-level state is `R13_ACTIVE_EXACT_SOURCE_COST_DIAGNOSTIC`, but its nested `collaboration.round` still says `R7`. Root owns this state correction. The currently visible R13 folder has its plan and README; a new R13 cohort/freeze was not part of this read-only preflight.

## Minimum R13 migration

Start from the R12 round tools and make only the identity and pairing changes required by R13:

1. Adapt `prepare-plan.py` and its tests so every measured/confirmation plan has exactly three distinct sources: candidate, scoring baseline df5c, and estimator control 41. Preserve rotations for order balancing. Bind the two baseline identities separately; do not label 41 as the scoring baseline.
2. Adapt `freeze-cohort.py` so `baseline` is df5c and `estimator_control` is 41, each with exact name and SHA. Freeze D/A/B inputs only after the scoring plan and source bytes are fixed; preserve the 25-round suite/generator, source commit, requested/drawn plans, runner, CPU and original execution-file bindings.
3. Adapt `verify-three-groups.py` to compare candidate against df5c for D/A/B, while preserving the R12 statistical policy unchanged: all three independent groups, ≤0.97, p05 strictly >0, 2,000 resamples and the frozen seed. Require actual complete passing full-gate evidence; diagnostics/observer runs cannot stand in for D or unseen A/B.
4. In `adopt-three-confirmed.py`, keep two explicit pair sets: scoring pairs candidate↔df5c, and estimator pairs candidate↔41. The R12 `scoring_pairs` structure already separates these roles conceptually, but its fixed baseline constant/name and validation must move from 6c to df5c. Estimator `select_pairs` continues to use the frozen anchor source 41. Never pool the scoring and estimator pairs.
5. Refresh the R12 `execution-binding.py`, `summarize-run.py`, `sync-ci-state.py`, freeze paths and test fixtures for R13. Bind any new profiling helper and diagnostic outputs by SHA in the R13 run evidence; leave official gate, bench, contracts, pins and runner identity untouched.

### Dry-run and model metadata boundary

The frozen estimator validates that the set of declared source runs exactly equals the set of eligible full-gate records. In the current code this check rejects stale `full_gate_runs` with `Declared gates omit eligible source records`; if R13 creates additional full df5c control records, the current-source view's run list must be supplemented before the adopter's dry-run. The R12 identity-only metadata receipt shows the precedent: only `full_gate_runs` changed, with the old model SHA and frozen anchor unchanged.

For R13, make an evidence-only metadata receipt for df5c if its exact-source full-run list grows. Preserve model SHA `5d946420…8a031f` and its displayed numbers. `estimate_champion_time.py --dry-run` still computes an in-memory projection for df5c versus 41 because df5c is not the anchor source; its output must not be adopted or written back as a same-source recalibration. The dry-run's needed result is official champion identity validation. For a later genuinely new candidate, the estimator may use the new candidate↔41 pairs under the frozen anchor, while the adoption scoring remains candidate↔df5c.

## Existing profiling assets

`profile-entry.py` and `profile-current.py` are not directly reusable for df5c. Both bind parent SHA `8eb63a2f…61e045`; the entry wrapper asserts that exact source. The profiler also hardcodes the old `RowStream_core`, `Packed10_packB`, the old row-output call sites, and exactly four parent-core returns. These assumptions do not establish coverage for df5c's different BMM dispatch and routes. Removing only the SHA guard would leave the profiler either failing on symbol drift or omitting new paths.

The abstract plan-to-call mapping can be reused as a design reference: it maps the exact suite plan, case, phase/repetition and dimensions, with one warm-up/check call plus three timed inner calls and one raw call for untimed cases. Its `instrument()` and stage boundaries need a fresh df5c-specific coverage map, bounded full-function extraction, exact call-count checks, and explicit all-route accounting before any stage result is useful.

R12's 20 inspected requested-plan files have `profile_parent=false`. R12 has full-gate cell/class timing and codegen captures, but no df5c per-invocation stage profile from these scripts. R7 `profile-summary.json` is evidence about the old 8eb parent only; it cannot be carried as current DF stage-cost evidence. Any new observer run is diagnostic, has unknown measurement perturbation, and cannot be the clean D or either frozen confirmation.

## Evidence limits

R12's adoption receipt is accepted for D/A/B against 6c, and the independent final review verifies the df5c model and post-adoption display-update receipt. That supports the starting point and file lineage only. It does not establish a new R13 candidate, stage profile, or champion replacement. R13's selection remains unverified until fresh full gates and frozen unseen confirmations finish.

## Bound source hashes

SHA-256 values for the preflight inputs are recorded in `review-preflight.json`. The JSON also records the exact R13 and R12 identities and the dry-run/profile conclusions above.
