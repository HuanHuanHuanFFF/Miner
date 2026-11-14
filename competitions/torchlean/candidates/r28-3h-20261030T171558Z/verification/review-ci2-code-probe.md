# CI2 code-probe and freeze-draft review

Captured 2026-10-30 17:35 UTC after reading requests `173300-codeprobe-delta.md` and `173400-mobile-freeze-ready.md` with the root status. Batch1 run `41099255272` is still active; batch2 is explicitly `FROZEN_DRAFT_NOT_DISPATCHED` and waits for batch1 terminal collection. This review covers the optional C probe and the new frozen plan metadata only; it does not re-review Mobilezero's theorem or arithmetic transformation.

## Checks that pass

- Draft candidate recipe SHA `88f651e2…9e221b` matches the frozen receipt and plan. The plan carries candidate hash `dc610a60…92b0d4f` / 255,397 bytes and public #53 reference hash `3dbe2f70…f7a9cb`. The plan candidate remains `full_gate=true`; no gate has run for it.
- `code-diagnostics.py` hash `599afc8d…f8a826` matches `plan-draft.json`; requested tokens are `qCtx7` and `qCtx13`. The runner reads generated `Submission.c` bytes and writes only derived JSON metadata (symbol names, body hashes/sizes and counters). It does not write or patch the C file, compiler flags, measured binary, or benchmark request. The uploaded report tree receives no generated C body.
- Plan's MobileNet #57/public #53 edge and response hashes are bound to the fresh R28 snapshot. Current #57 source remains unavailable. The edge is route evidence; any local result against #53 stays inferred and quick until separate confirmation.

## CI2 probe issue before dispatch

`runner.py:105–107` calls `probe_module.inspect(...)` without a diagnostic-only `try/except`. `build(refentry)` runs before the candidate build and original gate, so a probe parser/decode exception while inspecting the reference can abort CI2 before the candidate's all12 gate. Since this is optional metadata, catch and record probe errors as `INCOMPLETE_DIAGNOSTIC_ONLY`, then continue the proof and measurement path, as the runner already does for the profile diagnostic.

Two interpretation limits should remain explicit:

- `inspect()` returns success with an empty `functions` list if neither requested symbol matches. Emit missing tokens or assert expected symbols so a no-match result cannot look like a completed measurement.
- `multiplication_tokens` is `body.count('*')`; this counts pointer syntax and other stars as well as multiplication. Treat it only as a lexical star count. `uint64_multiply_calls` is the explicit `lean_uint64_mul` substring count; neither field is assembly or a performance result.

The brace scanner is a simple brace counter and does not lex C strings/comments. Its function-body hashes/counts are diagnostic-only until a real generated-C result shows the selected functions were extracted correctly. Keep no-body output and preserve the CI1 run's frozen source: its commit `5bd2f0df` predates this uncommitted CI2-only runner change.

No CI2 request is active, and no Mobilezero proof or performance conclusion is made here. Root owns any correction and the next dispatch. For CI2 terminal data use the fixed R28 `audit-native.py` after dispatch.

Static syntax check: `code-diagnostics.py`, current draft `runner.py`, and `batch2/plan-draft.json` parse successfully. This does not compile generated C or Lean and does not remove the nonfatal-error requirement for the optional probe.

## Follow-up — 2026-10-30 17:42 UTC

Read request `174000-queue-and-boundaries.md` with the current root status/CI request. CI1 `41099255272` is still the sole active run; no terminal evidence has appeared. The Mobilezero recipe remains frozen and its CI2 draft waits for CI1 collection.

The requested constructor/UInt64-box/reference-count counters are now present. Current `code-diagnostics.py` SHA `05db9686…e8ae99` matches the draft plan; the #53 recipe SHA and candidate hash match `freeze.json` and `plan-draft.json`. Those new fields remain lexical generated-C diagnostics. `reference_increment_calls`/`reference_decrement_calls` count substring occurrences (`lean_inc`/`lean_dec`), and `multiplication_tokens` counts `*` characters; do not read them as exact semantic operation counts or assembly evidence.

The earlier CI2 integrity finding remains: the `runner.py:107` probe call is uncaught, and `inspect()` does not report requested tokens that match no function. Catch probe errors as diagnostic-only and report missing tokens before dispatching CI2. The current batch1 commit is still frozen at `5bd2f0df`, so these uncommitted CI2 probe changes cannot affect run 41099255272.

## Follow-up — 2026-10-30 17:44 UTC

Rechecked the root status and `CI-REQUEST.json`: run `41099255272` remains the sole active CI; CI2 remains only a frozen draft. Re-reviewed the acknowledged changes. The probe now records missing tokens as `INCOMPLETE_MISSING_SYMBOLS`, runner catches parser/import failures as `INCOMPLETE_DIAGNOSTIC_ONLY`, and the lexical/substring counters have explicit labels. Draft `code_probe_sha256` matches current `code-diagnostics.py` SHA `2f77cc5c…efd7782`; the #53 recipe/freeze hash remains `88f651e2…9e221b`. AST syntax and draft JSON parsing pass.

This clears the earlier CI2 code-probe exception and silent-no-match findings for the current draft. The documented simple-brace-parser limitation remains; probe output stays derived counts only. CI2 is still undispatched and no mobile source/gate/performance conclusion is made. CI1 remains bound to frozen source commit `5bd2f0df` and has no terminal artifacts yet.

## CI2 dispatch follow-up — 2026-10-30 18:05 UTC

Re-read root status/CI request and independently audited the batch2 dispatch. Run `41103226283` is the only active CI, source commit `ff05aa6b`, plan `a767950a…927fbcb3`, candidate `dc610a60…f992b0d4f`. All eight dispatched frozen blobs match both the exact commit and workspace; the public-only sentinel/`allow_private=false` inputs match the root request. The #53 reference hash, #57 response/publication/boards hashes, code-probe hash, and recipe/freeze hashes all match their saved receipts. The candidate still awaits its original full gate; no proof or speed result exists yet.

The code-probe fixes reviewed earlier are in the exact dispatched runner (`99a34005…f9ec7f9`). No generated C body is included in the plan or dispatch receipt. Wait for run `41103226283` terminal status and then use fixed R28 `audit-native.py` for the raw proof/measurement audit.
