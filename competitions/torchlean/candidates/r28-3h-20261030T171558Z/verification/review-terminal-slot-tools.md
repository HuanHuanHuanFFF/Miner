# Terminal-slot evidence handoff review

Captured 2026-10-30 18:02 UTC after reading `175300-terminal-review-schema.md` and `175400-ci1-profile-direction.md`.

- `terminal-evidence.py` releases a stale platform slot only after a non-pending review path/hash is bound in `execution-reconciliation.json`; it checks exact run ID/source SHA, the outer artifact manifest hash, every extracted file hash/size, summary run/source/finish time, job-log hash, artifact-finalized/post-job/orphan-cleanup markers, and the failure/success terminal condition. It returns false when the review is pending; it does not call GitHub or rewrite run status.
- `harvest-final.py` is read-only against GitHub: it fetches run/job/log/artifact metadata, checks the final artifact and its archive digest, safely extracts to the run evidence folder, writes a reconciliation receipt as `PENDING`, and does not cancel, retry, or free a slot by itself.
- `client.py` rechecks the exact pushed branch commit and frozen files. Before dispatch it permits an otherwise active same-branch workflow only when `terminal-evidence.verified(run_dir, headSha)` passes for that exact run/commit; other active runs block. The collection path applies the same terminal-evidence check for stale platform metadata.
- The fixed `audit-native.py` output for CI1 preserves `ci_metadata_status="in_progress"` and empty conclusion. Our independent terminal review is bound by path/SHA in the reconciliation receipt, and `terminal-evidence.verified(...)` independently returns true. The root status now has no active CI entry and CI2 batch2 is READY. No status was fabricated as completed.

Review artifacts: [terminal review](ci1-execution-terminal-review.json), [fixed native audit](audit-native-run-41099255272.json). This tooling review does not approve or execute CI2; root still must commit/push the exact plan and frozen files before its dispatcher can pass its own checks.
