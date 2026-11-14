# Prepared-B four-lane continuation interface

Read-only inspected runtime: `development-cost2/PreparedQuad.lean.inc`, SHA-256 `c7e661118485000b351ab688d4bb653905562fd01a8c34e0421ee42057aa6fd7`. No full prepared candidate or large proof has been assembled.

The minimal source `PreparedPointwise.lean.inc` (SHA-256 `8303c12e8282a4ee677998c374e840530445f65c5579a4eeab74ff94afcbd878`) has two **NOT_RUN** roots:

- `Submission.R22PreparedQuad.prepared_getD`: the existing accepted `Packed10.nativeA_getD` theorem applies equally to B. It includes out-of-bounds positive-zero defaults, so no extra shape proof is needed.
- `Submission.R22PreparedQuad.advance_get_of_prepared`: for `hprepared : ∀ i, prepared.getD i zero32 = toFloat32 (B.getD i posZero)`, the actual prepared runtime's state update is the same four raw-input multiply/add expressions as the raw quad. No real arithmetic approximation or float equality test is used.

If D's complete cost favors prepared B, the rest is a mechanical instance of the same `R20WideRowRefinement.storageLoop_lane`: select each actual prepared `Cell` field as view and retain hprepared in the per-step hypothesis. The raw and prepared Cell structures are distinct Lean types; do not rewrite their states as definitionally equal. The generic R20 interface avoids that problem.

`rows4` still receives the original B array for `Packed10.finish`; raw replay and NaN payload handling therefore remain in the original location. Only the accumulation consumes the preconverted array. Public `core` discharges hprepared with `prepared_getD` after its explicit whole-B map. Any performance comparison must include that map and the original fallback, as D's runtime does.

Source capacity and full public transport will be recalculated for whichever exact runtime is selected. This plan does not transfer raw-quad compilation or performance to prepared quad.
