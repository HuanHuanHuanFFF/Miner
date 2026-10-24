# R13 cohort, adoption and retained-model review

Reviewed at 2026-10-24 12:05 UTC. Read-only review; I did not run tests or adoption, and did not change CI, Git, shared state, index, model, or tools.

## Correctly separated scoring and estimator identities

R13's scoring baseline is df5c (`f01-d12-scalar-combined`, `df5c61a0…fb172`). The estimator control remains 41 (`f01-r8-combined-result-guard`, `41bce485…ce9a7`). `freeze-cohort.py` puts both in each group order; `verify-three-groups.py` checks the frozen df5c identity and separately requires a complete, matching 41 full gate in each D/A/B packet. It uses the existing three-group guard and unchanged 25-round, ≤0.97, p05>0 policy. `adopt-three-confirmed.py` also keeps distinct pairs: `scoring_pairs` authenticates candidate↔df5c from the same artifact/runner, while estimator `select_pairs` authenticates candidate↔41.

The core comparisons no longer use 6c or an R11 cohort. The literal df5c and 41 hashes are correct. A few rejection strings/comments still say “no longer6c,” “retained41” for the baseline, or describe a 6c score baseline; these are misleading diagnostics/comments, not active hash checks.

## Two adoption blockers before R13 has new full runs

1. **The public-results index and declared-run metadata must be updated first.** Current `multiplier-comparison.json` points to `public-suite-results.json`; it has 219 records but only the six R12 full df5c runs, and `view.full_gate_runs` lists those same six. R13 `sync-ci-state.py` records started/completed CI in `development-status.json`; it does not merge R13 gate records into `public-suite-results.json` or update `view.full_gate_runs`. After R13 scored runs, leaving this unchanged means the adopter either sees no candidate rows, or the estimator dry-run rejects the new df5c rows as undeclared.

   Specifically, the adopter calls `estimate_champion_time.py --dry-run` before it reads the records for the new candidate. The estimator requires declared exact-source run IDs to equal all eligible full-gate run IDs. R13 D/A/B each include a full df5c baseline row, so a stale six-run list will fail with `Declared gates omit eligible source records`. Add a separate metadata-only step that first merges/authenticates the raw full-gate records into the referenced public-results index, then extends `view.full_gate_runs` and the matching state metadata to exactly the full df5c run set. Record before/after hashes and preserve the estimate bytes.

2. **The R12 retained-model freeze is not currently enforced by the R13 cohort/adopter.** R13 `round-plan.json` declares model SHA `5d946420…8a031f`, and both current view/state freeze pointers reference R12's retained-estimate freeze (`f6fd05df…40b518`). But R13 `freeze-cohort.py` does not bind those identities, and `verify-three-groups.py` does not require them. `adopt-three-confirmed.py` freezes the estimator code and anchor, but it does not check that the current model bytes are still `5d946…8a031f` or that the view/state freeze pointers still match the R12 retained freeze before dry-run or writes.

   The proposed split is sound: record a `retained_model` identity in the R13 cohort (source df5c, model SHA 5d946, R12 freeze path/SHA) and include the immutable R12 freeze receipt in cohort files; check current model SHA against that identity before preflight writes/adoption. Do not place the mutable `champion-time-estimate.json` in the generic post-adoption `frozen()` set, because successful adoption intentionally writes a new candidate model there. Use the transaction's pre-write SHA and receipt to bind the old model, then separately verify the new model matches the new source after adoption.

The metadata-only step must not call the estimator's persistent write path for df5c. Its receipt should show only index/view/state run metadata changed and that the model SHA stayed `5d946…8a031f`. The R12 `retained-control-metadata-101358Z.json` is a historical 6c receipt and cannot serve this R13 purpose.

## Status of existing helpers and tests

The R13 verifier and freeze logic are otherwise aligned with df5c/41. `verify-three-groups.py` authenticates control-41 raw verdicts, 25 rounds, reference and execution bindings; `freeze-cohort.py` freezes all three sources and a distinct D plus unseen A/B cohort. `adopt-three-confirmed.py` reauthenticates raw full gates and rejects diagnostic rows. Its `prepare_views` clears the prior source's numeric-model freeze only when preparing the newly accepted source, which is appropriate once the pre-adoption frozen model has been checked.

The test fixtures exercise the df5c↔41 pair split, same-run source identity and clearing the old view freeze. They do not exercise the real estimator's stale `full_gate_runs` rejection against new R13 df5c records, nor do they assert the current on-disk model is SHA `5d946…8a031f` before adoption. The R13 tests should add those checks before any write-mode adopter run.

## Evidence snapshot

- Current model file SHA is `5d946420b8e1a7ecc68aacde44b0e2910a467ee3e3546724d502f252fe8a031f`; it is still bound to df5c.
- Current `view.full_gate_runs` is `[40074431355, 40076675251, 40078982864, 40080782614, 40083425886, 40083571000]`.
- Current public-results index SHA is `0ee6c1f4c4b4fd9de8cd57bc874aed5bd959d0197ac6ff617fe720f7df0be7d5`; it contains six df5c full-gate rows at this review snapshot.
- R12 `retained-estimate-freeze.json` SHA is `f6fd05df105e55a73910cf01ef89188254092de6fbf3a0a0cb89adb68540b518`, with model SHA `5d946…8a031f`, source df5c and `no_numeric_model_change=true`.
- The estimator's run-set check is in `competitions/floatlib/scripts/estimate_champion_time.py`; exact helper and state hashes are recorded in `review-r13-adoption-preflight.json`.

**Assessment:** scoring and estimator pairs are correctly separated. A later R13 adoption remains blocked until the public index/run-list metadata is reconciled and the retained df5c model identity is checked against the R12 freeze. No current code path performs those two steps yet.
