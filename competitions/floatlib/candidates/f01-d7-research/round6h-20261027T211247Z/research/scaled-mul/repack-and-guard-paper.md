# R22 repack and original guard closure

State: paper derivation plus independent Lean fragments, **NOT_RUN**. No public entry has been changed. `Kernel-probe2.lean` is a 253674 B interface probe, SHA-256 `68264edadbde4f03e4eb6e6b8c856632f94696af0b44fc60eadc9c7eb1e777e8`.

## Exact remaining unproved interfaces at this checkpoint

1. Pinned Lean compilation/replay of probe1's actual UInt64 product decode composition.
2. Pinned Lean compilation/replay of `R22ScaledFields.normalCore_eq_fields` and `R22ScaledGuard.guard_conditions` in probe2.
3. The model-side equation for the *same* `mkBits` result and `Model.mul` on the two original raw inputs. Old R18 support contains a suitable theorem but has not been transplanted into this new artifact.
4. Transport of that equation through `Configured.Family.toModel_injective`, eliminating the explicit `hcore` premise of `guardedMul_spec_of_core_spec`.
5. A public-entry carrier under 256000 B, source-bound complete gate, and actual performance. Old four public specs still refer to B2.

## Paper derivation

Write `P=A*B`, where `A,B` are the hidden-one significands in `[2^23,2^24)`. The exact UInt64 multiplication does not wrap: `P≤(2^24-1)^2<2^48<2^64`. The native conversion rounds once to positive `m*2^e` with `2^23≤m<2^24`, `e∈{23,24}`. The old upper product bound excludes the otherwise possible carry to `2^48`.

R21's scaling yields the exact integer `Z=m*2^(e-23)`. Thus `Z>>>24=e-23`, and `Z>>>(Z>>>24)=m`. When `e=24`, Z is even, so the final shift is exact. The normalization bit is computed after rounding; the retained counterexample `A=8388609,B=16777214` shows why reading it from P before rounding would fail.

Let `M=middleExponent(P)=e+150`, so `M∈{173,174}`. The actual high word has value `M-173`, and the actual fraction word `q-8388608` has value `m-8388608<8388608` because q is at least 8388608. Its UInt32 subtraction does not wrap.

For the original guarded sum S in `[128,380]`, the actual exponent word `S-127+high` has value `M+S-300∈[1,254]`. Neither subtraction nor addition wraps in UInt32. Consequently the exponent and fraction masks in `FastMul.mkW` are identities; the runtime three-way OR equals the exact `NativeBinary32.mkBits` target. `Repack-scaled.lean.inc` expresses this chain with fixed-width field equalities, not only real-number equality.

The original exponent extraction yields values in `[0,255]`, so their sum is at most 510 and cannot wrap. The check `eu-1≤253` rejects eu=0 by UInt32 wrap and rejects eu=255 directly; it is exactly `1≤eu≤254`. The check `S-128≤252` rejects S<128 by wrap and rejects S>380 directly; it is exactly `128≤S≤380`. `Guard-scaled.lean.inc` uses the accepted old Nat/modulo argument. It leaves fallback unchanged and records the remaining normal-core correctness as an explicit premise.

NaN, infinities, signed zeros, subnormals, and the excluded exponent-sum boundaries continue through the same fallback. This statement is a branch-coverage observation; full bitwise multiplication equivalence still needs interfaces 3–5 above.

## Next decision

Use the smaller frozen probe1 for the first cast/decode discriminator already handed to D. Probe2 is a follow-up interface artifact, not a second performance candidate. Expand to the actual public `mul_spec` only when the complete runtime cost signal supports the route. If full integration needs source space, use the existing reviewed source-budget path and retain licenses; do not alter old snapshots.
