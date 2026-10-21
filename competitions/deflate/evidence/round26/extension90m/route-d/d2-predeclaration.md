# D2: one transferred residual budget per main decision

R26 extension90m fixed window 2026-10-12 14:55:17–16:25:17 UTC. The D2 source is a feedback-driven change to D1, not a new budget, independent confirmation or depth sweep.

## Observed D1 feedback

Actual run `38267276245`, `screen90-d1`, completed the original 28-file protocol with 11 measured repetitions and 540 finite decode checks with zero failure. D1 changed tokens in the five expected row9 files. The original extracted `Funs.lean` contains the three helper signatures and unchanged main/lazy state tuples anticipated by proof1; this is interface compatibility only, not a Lean build.

| Role | Public X | Public Y | Competition-pool share |
|---|---:|---:|---|
| D1 primary | 0.46618411018243855 | 35.30763523619238% | UNKNOWN here; parent owns fresh-snapshot replay |
| D2 | UNKNOWN | UNKNOWN | UNKNOWN |

D1 primary is 1.0656602398% slower than its primary public658 reference on the balanced total-time axis. An arithmetic decomposition using each file's total-time median rep locates +0.8946378266 percentage points of that difference in the five changed-token files; their parser component is +0.8598354554 points. The candidate copy also has a positive changed-file parser component. This is not a causal separation or a corrected score. See `d1-cost-feedback.json` for all four candidate/reference views and raw SHA256 bindings.

Source inspection confirms a specific mismatch between D1's intended budget transfer and its actual work: every shallow lazy winner can request a residual11 continuation, even when current already spent its full residual budget, or when a previous lazy winner already received one. Thus D2 tests the minimum work-budget correction supported by both source and real negative feedback.

## Fixed change

- `d2_current` returns `(length, distance, deferred)`. The third field is 1 only on the branch that skipped current's residual continuation after a winning next-head peek; every other branch returns 0.
- Reuse the existing `go` variable: 2 means one transferred budget remains, 1 means ordinary shallow lazy, 0 means stopped. The loop condition becomes `go > 0`.
- `d2_lazy` may run the residual11 continuation only when `budget == 2`. Immediately after the first lazy call, set `go = 1`, even if the shallow candidate is rejected. Later lazy iterations therefore use original depth1.
- Retain D1's exact gain comparison, head peek, current continuation, deeper-result acceptance rule, original insertion, fold and emission. No new threshold, depth, route or persistent metadata.

Using the existing control state avoids adding a separate loop-carried variable or enlarging the lazy result tuple. The original decreasing measure `lim - p + go` remains a plausible proof route: accepting advances p and sets go to 1; rejecting sets go to 0. This argument is INFERRED until the real extraction and Lean gate validate it.

One nominal residual budget does not imply equal actual chain work, equality of runtime cost, preserved compressed size, or positive rewards. The earlier peek and repeated next-head evaluation still add work, and shallow selection may still discard a valuable deeper current match.

## Required experiment and decision

Perform one actual original-protocol paired screen against exact public658, same-source controls and incumbent, including original public encoding, finite decode, per-file measured reps and fresh extraction. D2 must receive this real test before promotion or pause; the local state model cannot replace it. Parent thread performs dispatch and fresh official scoring.

Any actual correctness failure is retained and repaired only as a concrete defect. A valid result is assessed on total X, Y and same-snapshot score, including every counterexample. A positive but control-sensitive signal requires frozen independent confirmation. If the modified domain remains materially slower after this exact work correction, do not add a third threshold/depth variant without a new mechanism or falsifiable diagnosis.

## Identity and proof status

D2 path: `candidates/r26-d-658-once-budget`.

- Rust: `3f866acdc2f16cea804f9abe30094519f9b26e1632cc4585f88c278d5418591f`.
- Initial Lean scaffold: public658 `354d56aa9f58536efdb410f3d5ecdf1945bded607965fe8a48161f96b035c494`.
- D1 source parent: `f6c7f97f9fb275d5a27ff4a52d02f065bb9c4cfd39e73e311c5a7f5a3ea8e0a8`.
- Original author and source receipt retained from public658.

D1 and D1 proof1 remain frozen. D2 proof migration requires the current helper's triple return specification, the lazy helper's U32 budget argument, and rechecking the existing lazy decrease proof under positive-go semantics. No matching invariant, new axiom or cached-match equality is intended. Full gate, native quality/time and shares are UNKNOWN until their actual results arrive.
