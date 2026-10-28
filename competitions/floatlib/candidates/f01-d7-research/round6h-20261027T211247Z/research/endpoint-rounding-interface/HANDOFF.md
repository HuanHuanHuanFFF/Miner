# R22 B: strict half-bound rounding-to-zero interface

First tool **02:01:46 UTC**, bound **02:16:46**, shared cutoff **03:12:47**. `HalfZero.lean.inc` has **two proof-only roots**, both **NOT_RUN**; no public early-zero/early-Inf source, runtime or CI.

- `Submission.R22EndpointRounding.nat_rne_zero_of_lt_half`: `0 < shift` and `p < 2^(shift-1)` imply original `FloatLib.Numerics.roundShiftRightEven p shift = 0`. Monotonicity gives `p < 2^shift`, so the quotient is zero. The fixed `roundShiftRightEven_def` then has remainder p and takes its strict-below-half branch. No new omega/division search is introduced.
- `Submission.R22EndpointRounding.rseAny_zero_of_lt_half`: applies exact B2 `FastMul.rseAny_eq`, fixed `FixedWord.roundShiftRightEven_toNat`, and UInt64.toNat injectivity. It has **no shift<64 restriction** because it uses rseAny's full boundary handling, not a masked primitive word shift. E.g. bare UInt64 shift64 is not a substitute for this bridge.

The pinned FloatLib Team/MIT `ShiftRight.lean` was read from the existing primary receipt (commit0d918257..., blob d53bd9e..., SHA7727da57...). The FixedWord theorem signature was corroborated in the existing checked-in `Core/Proof/Rounding.lean` copy; B2's actual rseAny bridge is at2111. Exact file hashes are in `manifest.json`. No source file was copied wholesale or altered.

Strictness is intentional: the tie p=half is outside this interface even though the zero-quotient even tie also rounds to zero. This is not a request to widen C's guard. Still missing for any public endpoint: actual guard→positive shift/strict product bound, nonwrapping product linkage, the selected roundP branch, correct signed-zero packing and original exceptional/fallback behavior. Infinity is not addressed. New typing/replay and actual cost remain untested; do not infer time saved from this mathematical endpoint.
