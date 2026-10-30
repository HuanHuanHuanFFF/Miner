# CI6 proof-confirmation binder review

Reviewed `development/ci-bridge/bind-confirmation.py` at 20:06 UTC without executing it; CI6's isolated standard group is still in progress.

## Boundary that is correct

- It is read-only over raw sources/evidence and writes a new derived receipt only after `ci-run.json` is completed and `summary.complete` is true.
- It binds the norm26 source hash in the completed CI6 plan to the exact source hash in the earlier CI3 full-gate summary, and verifies the prior summary/verdict file hashes, `axioms` stage, stable verifier fingerprint, and passing verdict.
- The receipt explicitly says the original gate was not replayed in CI6 and that the second input-zero candidate receives no proof.

## Fail-closed checks to add before using the binder

1. Bind `ci-run.json.databaseId` and `root-fixed-audit.json.run` to `41119180001`, and require matching terminal source commit/conclusion/status. The current code checks commit equality but not run identity.
2. Assert the plan still labels norm26 `full_gate=false`, `declares_correct=true`, names it `norm26-standard-confirmation`, and the prior gate entry/verdict are for that same candidate name. The source hash check is strong, but the candidate/gate role flags should also be pinned.
3. Check the second plan entry is exactly the frozen input-zero experimental source, with `full_gate=false`, `declares_correct=false`; also verify the root audit labels it `NOT_PROVED_NATIVE_ONLY` before writing the no-transfer claim.
4. Require the norm26 result to be `COMPLETE_NATIVE_ONLY_EXPLORATION` with both standard seeds and the expected complete paired rows/checksums in the fixed audit. `summary.complete` covers the whole plan, but explicit candidate-level assertions make the confirmation receipt self-contained.

Do not run this binder until CI6 is fully terminal and the whole isolated group is complete. The verifier's own fixed R28 audit should independently pass first; keep all seed/input/result details within Droot/verification until that boundary is met.

## Updated binder review — 2026-10-30 20:11 UTC

Read the revised `bind-confirmation.py` after request `201100-proof-binding-review-response.md`. It now adds the requested run/database ID and terminal audit binding, checks the exact norm26 role and gate flags, checks the second source hash/no-correct flags and no-transfer state, and requires both complete standard roots (396 pairs/396 checksums each and 792 ns values) before writing the receipt. It records whole-batch completion/error separately so a failure in the experimental second source need not invalidate completed Norm26 samples. The four earlier interface findings are closed; the isolation boundary is unchanged. I have not run the binder because CI6 is still active.
