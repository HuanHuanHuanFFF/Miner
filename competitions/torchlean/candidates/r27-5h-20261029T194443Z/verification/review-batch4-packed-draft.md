# Batch 4 packed-MLP draft preflight

This is a static review of `ci-plan-batch4-packed-draft.json` and its frozen recipe receipt. It is still a draft; no dispatch was found, and I did not launch CI or modify the runner.

## Bound inputs

- Both generated candidate entries match `development/packed/receipt.json`. The recipe script SHA-256 is `a75f92a7bb3661e42ccf6b524a247178af4700d7b9210dc23e0aae1221d24edf`; `PackedLinearRuntime.lean` matches receipt SHA-256 `2a416a233a96566f344477d9aa8999c96d0593f4528036f5e62af909dd75ec5b`.
- The two recipe outputs are `public13-packed8` (`c7cf3cf6…5f22b4f`, 159,055 bytes) and `public13-packed32` (`7f3c7452…38f9ad0`, 159,056 bytes). Both are below the source size limit and match the receipt.
- The plan targets only current MLP champion #33, whose saved champion row confirms source unavailable. Submission #13 is only the official report-chain calibration anchor; the champion record's report-derived factor and source hashes match the draft. The plan correctly sets `full_gate=false`, `declares_correct=false`, and `UNPROVED_NATIVE_RESEARCH_ONLY` for both candidates.
- The new path packs multiple output columns into an integer product. The two tile widths are variants of one mechanism. The written scope explicitly includes preparation, bias, zero, output and fallback handling; the existing independent algebra review remains paper-level only.

## Proof-state adapter update

This draft was first reviewed against the B3 runner `58b20a75…e660782`, which ignored `declares_correct=false`. The later B4 runner `ec0e0685…c99b20ac` now checks `entry.get('declares_correct', True)` and labels fetched entries with an explicit false value `NOT_PROVED_NATIVE_ONLY`. Both packed entries set that value, but the packed draft remains undispatched. The earlier concern is resolved only if a future packed dispatch freezes and uses this newer runner; no packed result or correctness claim exists.

## Performance evidence boundary

The current MLP report uses its official seed `2777525764`, 11 rounds, inner 3, 50 ms/cell and both production environments. This draft instead lists two exploration seeds, `27102931` and `27102933`; its performance is a route screen, not a production-plan comparison. The draft also lacks a separately frozen per-run timing/environment contract. Keep any future human performance result as the inferred multiplier against current #33; no original-source comparison or current-source direct pair is available.

The source #13 receipt is local-only pending license review. `allow_private=false` and the no-source-artifact policy are present, but a public-runner source fetch still leaves source-use policy UNKNOWN. Review the terminal artifact and logs for source excerpts. No part of this draft establishes correctness, qualification or promotion.
