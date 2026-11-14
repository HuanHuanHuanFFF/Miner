# Checked Float proposal: exact integration surface

`CheckedFloatDivision.lean` 2980B/518dcc9d… is NOT_COMPILED. It is a distinct
primitive from D07's exact integer reciprocal and4-partial-product mulHigh.
No current-champion or native speed claim is made.

The fast denominator and proposal are UInt32. Their widened product always
fits UInt64, so accepting p≤a and a-p<d certifies the exact quotient/remainder.
The UInt64 wrapper tests d<2^32 before truncation; otherwise it uses the
original operations. Neighbor proposals wrap as UInt32 and each is independently
checked. Zero denominator cannot pass the remainder check and retains the
original division/modulo semantics.

The proof target `fromFloat_exact a d reciprocal` quantifies **any Float**.
Neither floating-error theory nor reciprocal-cache identity is a correctness
premise. NaN, infinities, wrong row and rounded proposals are harmless to the
result if the checker compiles as proved; they may make the fast path useless.
The pinned runtime's guarded Float.toUInt32 conversion maps NaN/negative to0
and clamps large positive values, so no unchecked out-of-range cast is added.

## D-owned caller changes after the small helper accepts

Use the existing source12 Ya7G integration recipe. Preserve its original
arithmetic, guards and final rrsG/MYa7 fallback. Replace exactly these pairs:

| Pair input | Existing uses | New call |
|---|---|---|
| cv,D | q0=cv/D; cv%D in r0 | fromFloat cv D inverse |
| r0,D | quotient in qq; r0%D in ra | fromFloat r0 D inverse |
| ra,D | quotient in qa; rr=ra%D | fromFloat ra D inverse |

`fromFloat` returns the same UInt64×UInt64 type as D07.divRem. Only the cached
inverse's type becomes Float. Compute prepare(nU*Yf(dw)) once per actual row
inside the kernel boundary; include its allocation/destruction and all failed
certificates in timing. Avoid FloatArray/UInt64 bit reinterpretation: this is
a numeric reciprocal, not raw word bits.

The element equality theorem can quantify arbitrary inverse and close by
unfolding the new/old Ya7G and rewriting `fromFloat_exact` for all three pairs.
The row equality therefore does not need to prove each cached inverse matches
its row denominator. The actual assembled12 kernels/correct still need the
original complete gate, including exact getter/layout binding. No retained
proof may be relabeled as proof of the new runtime before these rewrites.

Standalone helper uses namespace Submission.R27CheckedDivision. To insert
inside the predecessor's existing Submission namespace, remove its import
and change only that opening/closing namespace to R27CheckedDivision, then
place the new caller after it. Keep the self-authored proof bytes/namespace
adaptation in a hash-bound recipe; do not publish the whole predecessor.

## Evidence and next discriminator

Seen formula census uses the previously recorded seed27051001 typical rows1
normal/wide/sparse cells, shape472/240/80/10. All720 actual cv/r0/ra pairs take
the first certificate and all3 complete formula output hashes match the prior
C record. The observer leaves the model output calculation on its original
rational path and checks each captured division separately against divmod.
Thus the whole-output hash binds the fixture; it is not an integrated new
kernel checksum. Generic finite tests cover50000 UInt32-sized quotient cases and504
arbitrary Float/directed edge cases. This is not native hitrate or a success
probability, and the old larger suite remains untouched.

First compile the3KB helper and print its3 roots. Then compare actual native
primitive/Ya7G complete-call cost, including prepare, Float casts, tuple
elimination and misses. D07's4partialproducts could still be cheaper than
the Float proposal; source-level operation counts cannot choose the winner.
If productive, bind the actual public12 caller and measure the complete model
under D's fixed report/confirmation policy. Keep the report-policy identity
verified, current source private and cross-environment calibration INFERRED.

Wrong-cache negative control differs from D07: output must remain correct;
only certificate hit/miss counts should change. Checksum agreement alone
cannot prove this optimization ever ran successfully.

Investment screen: `division-opportunity-screen.json` counts all54oldformula
cells. A10percent wholegain requires baseline costperreplaceablepair versus
meanlogicaldenseMAC cost of at least7.04..62.22 (median35.93), even with
perfectpaircostelimination and no newoverhead. The firstsample needs61.70;
ifhalf thepaircostis saved it needs138.83. Additionalunchanged costs raise
the requirement. These are algebraic necessaryconditions, not CPUtimings or
an impossibilityproof. Keepwholemodel integration onhold until actualprofile
supports thecostcase; a smallacceptedprimitive remains reusable.
