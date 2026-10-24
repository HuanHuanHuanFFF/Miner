# R13 retained-model binding and metadata transaction review

Reviewed at 2026-10-24 12:24 UTC. This is a read-only review of the new helper and its adoption bindings. No helper, test, CI, Git, model, or shared-state write was performed.

## Model binding

The updated R13 path carries the frozen R12 model identity without putting the mutable model file in the cohort's post-write immutable file set. `verify-three-groups.retained_model_identity()` derives the identity from the R12 retained-estimate freeze and the R13 round plan; the R12 freeze receipt itself is included in the bound local files. `freeze-cohort.py` checks the live model SHA before writing the cohort. `verify_freeze()` requires the cohort's `retained_model` object to equal the derived identity. The adopter checks that the pre-adoption model path/source/SHA still match before its write transaction. Its later `frozen()` checks do not require the old model SHA after a successful new-source estimate, so the model replacement is not incorrectly rolled back.

The current model remains SHA `5d946420…8a031f`, source df5c, with the R12 retained freeze SHA `f6fd05df…540b518`. The current view and state still point at that same R12 freeze.

## Metadata-only refresh

The R13 helper rejects optimized Python, requires the view's `public_results` path to match its index input, authenticates every full df5c row through `estimate_champion_time.checked_record`, and derives the exact run set from those rows. It checks the live model and raw index bytes before and after the view/state update. View and state writes use the adopter's content-CAS transaction; caught exceptions call rollback and the updated helper writes a failure receipt with rollback statuses.

The successful receipt `retained-control-metadata-20261024T121622Z.json` records the df5c run list expanding from six to seven, the input index SHA, and unchanged model SHA `5d946…8a031f`. The current public-results index has seven complete df5c rows, and each of those seven runs has exactly one complete 41 control row in the same run. Thus the estimator's exact declared-run set can be satisfied before dry-run, while score pairs remain candidate↔df5c and estimator pairs remain candidate↔41.

## Remaining boundaries

The helper does not call the persistent estimator or edit `champion-time-estimate.json`; the existing model stays byte-identical. Its receipt proves the normal update transaction, but abrupt process termination between separate view/state replacements and the final receipt write is not journal-recovered. Root has accepted that crash window as the metadata helper's boundary. The helper also does not pre-authenticate a 41 row for every df5c run; the later estimator dry-run/adopter selection will reject any missing pair, so this remains fail-closed but can leave a metadata-only update that needs correction.

The checked R13 test files cover the cohort's retained-model identity and adopter pre-write model mismatch, plus transaction rollback. They do not directly test `refresh-retained-metadata.py`, its optimized-Python rejection, pointer mismatch, failure-receipt path, or crash boundary. No tests were run during this review.

## Source snapshot

See `review-r13-retained-metadata.json` for the bound script, receipt, index, view, model, and R12 freeze hashes. This review does not claim that an R13 candidate has passed its three independent groups or replaced the official champion.
