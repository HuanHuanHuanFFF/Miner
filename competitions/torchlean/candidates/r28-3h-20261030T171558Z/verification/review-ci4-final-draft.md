# CI4 cost only final draft review

Captured 2026-10-30 18:58 UTC after reading request `185600-ci4-cost-only-final-draft.md`, the root status and CI request, the final plan draft, and `cost-source-freeze.json`. Root files remain at their 18:33 snapshots with CI3 run `41107618451` identified as the only active run. CI4 has not been dispatched.

## Frozen source review

The independent in-memory rebuild and source-structure audit in [audit-ci4-final-draft.json](audit-ci4-final-draft.json) passes all recorded checks:

- `public53-zero-runtime-native-only`: hash `474eff804a9dd25973e89b597e639acc335ee7993d5ec1e86ea7cd12cd384d74`, 244,294 B. Rebuild matches the final draft and cost freeze. Its 158 ordered runtime declaration blocks match the proof-bearing zero-v2 candidate byte for byte. Relative to its pinned pre-prune zero baseline it removes exactly 12 proof declarations, including `qCtx8`, `qCtx14`, and `correct`; no remaining runtime/proof declaration refers to a removed name. It has no `correct` declaration or `sorry`, `axiom`, `unsafe`, `admit`, `native_decide`, `implemented_by`, or `extern` token. It remains `full_gate=false`, `declares_correct=false` and is **not proved**.
- Pointwise NativeOnly remains exactly `5ecfdd8cd007…`, 245,424 B; no full gate and no correctness claim.
- The two bounded prefixes independently rebuild to `0161443f3c57…` / 163,658 B at `Submission.qCtx8`, and `77b58fc87c28…` / 170,167 B at `Submission.qCtx14`; each planned cap is 120 s.
- The final plan contains only the two NativeOnly cost sources. It has no whole zero-v2 candidate and no `full_gate=true` entry. The 85eb proof candidate is held for a later decision.

This is a static source/hash/dependency review, not a Lean elaboration, native build, full theorem proof, benchmark, or correctness result. The proof gate cannot be inferred from runtime-byte identity.

## Earlier helper adapter findings

The latest runner closes the earlier control-flow findings: hard 120 s helper clamp, per-helper exception recording, and required-helper skip marker are all present. The user explicitly directed keeping raw Lean diagnostic logs and checking them after collection. Keep uploaded logs byte-for-byte with their hashes and failure context; inspect for full source after CI and retain all original evidence even if a leak is found.

The cost plan has 1,500 s for setup, two bounded prefixes, a reference build, two cost candidates, and two seeds per candidate. The runner caps work by the shared deadline and records each measurement only after the complete paired rounds; if any portion is clipped or absent, treat that candidate's model cost as UNKNOWN. A fresh freeze-confirmation group remains required before adopting any performance claim.

## Remaining handoff item

The authoritative `plan-draft.json` and `cost-source-freeze.json` now reflect the final two-source, no-full-gate request. The sibling `prefix-and-whole-draft.json` is stale: it still says `NOT_DISPATCHED_FROZEN_PREFIXES_AND_CONDITIONAL_WHOLE`, includes full candidate `public53-zero-proof-v2`, and lists the earlier q8 repair helper. Ensure it is not used to construct or describe the dispatch freeze; root can update/mark that file when assembling the final plan.

The current MobileNet #57 identity, ratio, publication, and response hashes match the verified 18:15 snapshot. No later refresh directory exists in the workspace. Refresh official champion state before dispatch or any score adoption; the stored ratio is a snapshot, not a current guarantee.

At 19:02 UTC, request `190100-mobile-step-proof-alternative.md` added a future nonrecursive step-lemma hypothesis only. It does not revise this frozen cost-only draft or authorize changing its hashes; wait for cost/prefix evidence before proof work. Root status still identifies CI3 as the only active run.

## 19:06 dispatch preflight

Root has now materialized `ci-plan.json` and set CI-REQUEST to READY for batch 4. The plan hash `ae7eeae6fd7bedcc59625f0943948190233b2423e477b7b8a16c7f55e808e1cf` exactly matches the request; both candidate hashes and the two helper names match the independently audited final plan. The only differences from `plan-draft.json` are earlier dispatch/start cutoffs (19:30 / 19:35 UTC). Root status lists no active run. The stale sibling `prefix-and-whole-draft.json` remains old but is not the root dispatch plan.

The root plan still binds MobileNet #57 to the verified 18:15 response and publication. There is no later refresh snapshot in this workspace; fetch current official board data immediately before dispatch so any current-champion estimate stays current. Until then, the candidate source/cost experiment is precisely pinned, but champion-relative comparison is an 18:15 snapshot inference.
