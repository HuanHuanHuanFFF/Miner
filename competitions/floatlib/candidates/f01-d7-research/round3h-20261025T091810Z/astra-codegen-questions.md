# First codegen questions — source-level risks, not regression claims

Keep the two queued entries unchanged until actual compiler feedback.

- Scalar c972: normal B2 selected caller ends in toBits; c972 must repack after the external toBits call. Inspect preserved exponent/sign values, tailcall loss and spill/reload in the actual selected caller. Removing2 MUL and2 table reads is established source intent, not cycle savings. Exact B2 caller evidence and new checklist: astra-workers/scalar-representation/caller-review-checklist.md and b2-caller-review.json.
- Matrix5f53: A4 preparation and F8 tile results add allocations. Current source conditional requested-byte formula per4-row block versus B2 is32n+48−16G; p2 gives32n+32, always positive. Check actual direct-field layout, panel lifetime outside g, selected loop and full costs including prepare/free/output/replay. Do not narrow to p2 merely for convenient SIMD: current B2 A completed sample p2 touched-class whole-time upper bound is only2.818%; domains overlap, never sum upper bounds. Details: astra-workers/matrix-architecture/domain-cost-summary.md.

These two risks change what we inspect, not the fixed original gate/adoption criteria. Remaining continuous worker budget targets actual errors and codegen questions; no seed/guard grid or repeated full-source review.