# Moment representation: where wide Nat work actually starts

The exact source does **not** propagate a carry through18 limbs on every term. Public `ExactToolkit/Limbs.lean:70` splits an incoming UInt64 term into a low and high part and adds each to one Nat slot. Slots are allowed to accumulate above2^32. Former2's norm `Y6` uses this for squared24-bit mantissands; `Y7` uses it for signed24-bit mantissands in separate positive/negative arrays. Both finish with public `limbValA` only after the row loop.

There is a stronger universal cost premise than the earlier sample bit-width count:

- A sum update has low part<2^32 and high part<2^23. Hence each positive/negative dirty slot is<n·2^32.
- A square update has m²<2^48 and shift2·(idx−base). That shift is even, so the split remainder is at most30; the high part is therefore<2^46, while the low part is<2^32. Every square dirty slot is<n·2^46.
- If n≤2^17, every dirty slot is strictly below2^63, for **all finite binary32 values and exponent spreads**. The mantissa square itself is also below2^48. All published legacy/typical/scale/boundary norm widths are at most257, far below this bound.

The pinned64-bit Lean header sets `LEAN_MAX_SMALL_NAT=SIZE_MAX>>1`. Its `lean_nat_add` and UInt64→Nat conversion stay scalar when these bounds hold; the square product stays below the small-Nat multiplication overflow threshold. Therefore replacing these row updates cannot honestly be described as eliminating per-term GMP arithmetic. Actual selected compiler code is still uninspected; this is a source/representation bound, not a measured instruction or GMP-call count.

`dirty_moment_model.py` independently interprets the public split algorithm and verifies equality to exact integer moments. At the one frozen own-seed first-Mixer layer (135 rows,3,675 inputs), the largest dirty slot is47 bits. There are14,700 source Array.modify calls and7,290 source `limbValA` fold steps;96 fold results are at least2^63. Those are source operations/value widths, **not native call counts**. A constructed257-input row achieves a54-bit dirty slot and an86-bit Q, cleanly separating narrow update slots from the final wide value.

The remaining plausible deletion from S128/Q192 is concrete but narrower: replace54 initialized array cells per layer-norm row, four dynamic slot modifications per input, three18-step final folds, and the final construction/conversion of wide Nat values. Fusing S/Q after the existing minimum-exponent scan can also reduce three raw row traversals to two, provided the additional maximum-exponent/capacity summary is charged. This must compete against the existing two-slot updates, rather than an imagined18-limb carry loop. Carry propagation and shifted128/192-bit term construction are new costs in a fixed-word rewrite.

This evidence lowers the case for a **moments-only** port. An end-to-end word path that also avoids the wide `limbValA → nQ−S² → sqrt scaling / exact output numerator` boundary remains a different candidate, but complete cost and whole-time share are UNKNOWN. The proposed word certificate helper does not make exact statistics, native guesses, failure replay or output release free.

Reproducibility: `dirty-moment-results.json` binds its script; `dirty-moment-source-receipt.json` binds the public Limbs source, fixed header, public shape formulas and prior former2 definition audit. Former2 is read-only with licenseUNKNOWN; no source body is copied into a candidate.
