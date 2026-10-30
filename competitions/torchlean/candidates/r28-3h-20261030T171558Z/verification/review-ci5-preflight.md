# CI5 typed pointwise preflight

Captured 2026-10-30 19:42 UTC. Read request `193900-ci5-typed-pointwise-selected.md`, root status/CI request, current plan and freeze receipt. The request and status are `READY` for batch 5 with no active CI.

## Rebuilt candidate

Independent in-memory reconstruction from official public #53 source passes [audit-ci5-preflight.json](audit-ci5-preflight.json):

- Candidate hash `17befe6a4afb7dac0dc19090970812b1890d147154932f610f015b6dd1b0d044`, 245,601 B; exact source and size match the plan, research producer receipt, and batch5 freeze.
- Builder hash `1bfedefc523e59189c1283908de284014b28a1bae38707ff421f163164388814`; the producer receipt hash also matches freeze. The older batch4 recipe `a5a99f31…` and failed candidate `5ecfdd8c…` remain unchanged.
- The candidate has no `correct` declaration or forbidden proof/evaluator construct. Plan flags remain `full_gate=false`, `declares_correct=false`; it is NativeOnly, unproved, and has no inherited timing.
- I independently rebuilt both the failed `5ecfdd8c…` source and this typed source. The top-level declaration set/count is unchanged (161 defs, 334 lemmas); only runtime defs `r28PC128` and `r28PW`, plus proof lemma `pbD`, have different bytes. The helper diff is the recorded typing/index-expansion patch; constants and threshold `<=15` remain the same. This still does not prove semantic equivalence or successful compilation.

## Root plan and remaining constraints

The root plan hash `a8a3d3b93ae306524dc76912ff7be9391898513d65ebbb0a76612071343a8aab` matches READY. It selects one candidate, no helpers, no full gate, two previously unused seeds, and a 1,200-second driver. The source snapshot for current MobileNet #57 is still from 18:15; re-fetch before dispatch or score adoption. The plan's latest start cutoff is 20:00 UTC, 15 minutes before the shared 20:15:58 deadline; dispatch early enough to leave time for the run and evidence collection.

This preflight verifies exact generation and plan binding only. There has been no Lean/native build of the typed candidate, no model timing, and no proof gate. If it builds, its cost result remains exploratory until a fresh confirmation group; any path toward promotion still needs a source-specific original all12 gate.
