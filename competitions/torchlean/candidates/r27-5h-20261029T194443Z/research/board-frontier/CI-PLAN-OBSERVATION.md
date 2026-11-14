# Batch2 metadata observation — 20:21 UTC

Read-only observation of root `ci-plan-batch2.json`, before C knows any dispatch state:

- The requested guard26 candidate identity is correct: SHA5fcb3b89…,218531B, `full_gate:true`.
- Root `board` and `champion` identify normalized_mlp/current23, but `human_performance_target` still says mixer/current36. Please normalize that stale text to the actual board; it must not change the runtime source or comparison target.
- Root scope says `NO_FULL_GATE_REPLAY` while guard26 requests the full gate. Preserve actual stage/log facts and distinguish gate execution from the plan's stale umbrella text.
- The plan's numerical chain formula is only a planning/screen description until Dverify's live-board/report configuration difference is reconciled. Do not label a quick-run ratio current-champion qualification merely because this formula is present.

These are metadata observations, not algorithm negatives or authority to cancel a dispatched run. C has not changed the plan and will inspect exact logs when supplied.
