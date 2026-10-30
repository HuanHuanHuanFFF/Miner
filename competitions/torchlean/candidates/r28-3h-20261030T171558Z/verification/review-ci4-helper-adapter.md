# CI4 bounded-helper adapter review

Captured 2026-10-30 18:37 UTC after reading request `183500-ci4-helper-adapter-review.md`. CI3 run `41107618451` remains active; its frozen plan has `helpers=[]`, so this helper path is not active in CI3.

## Control flow that passes

- `materialize()` is defined before the helper loop. Fetched helper inputs use the same exact source SHA check and optional owned transform/size hash as candidate inputs; source files are stored under the private runner tree, not the uploaded reports directory.
- Each successful helper result records name, exact source SHA, exit code, elapsed seconds and cap. A full-gate candidate with `requires_helpers` runs only if each named helper has exit code 0; otherwise the runner records `SKIPPED_AFTER_BOUNDED_HELPER_FAILED` and skips the full gate. A candidate without `requires_helpers` is not affected.
- The plan's gate flag remains the correctness boundary: helper elaboration is only a bounded interface probe, not a candidate proof. CI3's current NativeOnly candidate explicitly has no correctness claim.

## CI4 predispatch fixes needed

1. The code computes `cap = min(entry.get('seconds',120), remaining)`, so the 120-second ceiling depends on each future plan setting `seconds<=120`; the runner itself does not hard-cap it. Clamp with `min(120, entry.get('seconds',120), remaining)` or reject larger entries, then record the actual cap.
2. It writes the complete Lean helper stdout/stderr to `OUT/<name>-helper.log`; the workflow uploads all of `OUT`. A failure diagnostic can contain source excerpts or proof text, which conflicts with keeping the fetched prefix private. Keep raw helper logs in runner-private storage and publish only a sanitized status, elapsed/cap, source hash, and log hash; if the public log is safe, demonstrate that before CI4.
3. A thrown helper timeout/process exception escapes the helper loop before it records a helper result. The outer runner then fails before candidate gating and omits `SKIPPED_AFTER_BOUNDED_HELPER_FAILED`. Catch per-helper exceptions and emit an explicit bounded-helper failure record so required candidates are skipped with that marker.

These are CI4 adapter findings only; CI3 source/commit/plan are frozen and do not invoke helpers. No helper/Lean compile or CI action was run by this verifier.

## Superseded by current runner review

This was an 18:37 snapshot. The later runner now hard-clamps helper caps to 120 seconds and catches per-helper exceptions into recorded diagnostics, so findings 1 and 3 are resolved. Finding 2 is no longer a predispatch blocker: request `184700-ci4-draft-selected.md` explicitly requires retaining original Lean diagnostic logs and inspecting them after collection. Keep each log byte-for-byte with its hash and failure context; do not discard it based on hypothetical source leakage. See [current draft review](review-ci4-current-draft.md) for the post-collection inspection boundary and the actual unresolved mismatch with request `185000-zero-native-cost-decouple.md`.
