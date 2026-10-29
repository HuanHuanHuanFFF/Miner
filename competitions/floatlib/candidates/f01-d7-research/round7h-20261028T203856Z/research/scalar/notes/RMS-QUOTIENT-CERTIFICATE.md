# Smaller first interface: certified integer quotient for RMS

PAPER ONLY. No new-track implementation, native measurement or Lean execution is authorized at this checkpoint. This is an alternative realization of the exact-certificate route, not an independent claimed speedup.

**Cost premise revised at21:45:** fixed FloatLib already has a compiler substitution from bounded Nat RNE to UInt64 div/mod. This route's A49/B25 falls inside that bound. Its actual competitor may therefore be an existing native word divider with dispatch/normalization; it is not known to pay arbitrary-precision division. See `PUBLIC-REUSE-AUDIT.md` before allocating implementation/proof resources. The algebra below is unchanged.

Suppose x and gain are nonzero normal binary32; the stable denominator bound separately gives a positive normal d. Write their24-bit mantissas a,b,D and raw exponent fields ex,eg,ed. Then P=a*b satisfies2^46≤P<2^48 and2^23≤D<2^24, so2^22<P/D<2^25 (the weaker non-strict lower bound also suffices).

Determine h with two exact comparisons:

- P≥D*2^24 ⇒ h=24;
- otherwise P≥D*2^23 ⇒ h=23;
- otherwise h=22.

Normalize (A,B) to (P*2,D), (P,D), or (P,D*2), respectively for h=22,23,24. Every branch satisfies2^23≤A/B<2^24. A<2^49 and B<2^25, so all subsequent products by a24-bit quotient fit64 bits.

Use any fast computation to propose q: for example, a row-cached binary64 reciprocal times exact P converted to binary64, followed by scale2/1/half and Float.toUInt64. **The proof must not assume this proposal is accurate.** Guard q≤2^24 before multiplication and accept only if q*B≤A<(q+1)*B. A single ±1 correction may be attempted, but the corrected value must pass the same exact inequalities. Otherwise call the unchanged exact fallback.

C's independent boundary review additionally requires the **width guard to be repeated after correction**, before forming either product. In particular UInt64 q−1 wraps when q=0. Either prove/check q>0 before subtracting or reject the wrapped result with a fresh q≤2^24 guard. The original proposal's passed guard does not certify the corrected proposal. The first version can omit correction entirely to keep this interface minimal.

These inequalities prove q=A/B directly. Set r=A−q*B. Since0≤r<B, exact nearest-even rounding is

    m = q + [2*r>B or (2*r=B and q is odd)].

The binary32 output's unadjusted exponent field is

    Ebase = ex + eg − ed + h − 23.

First require1≤Ebase≤253. Then m lies in[2^23,2^24], including the final carry. Magnitude packing `(Ebase−1)*2^23 + m` naturally increments the exponent when m=2^24 and remains finite with field≤254. OR the XOR input sign. All missing/zero/non-normal inputs, exponent-boundary results and failed quotient proposals use the original exact function. The fast path has no Float32.toBits, no cross-width Float cast and no generic log2.

The minimal proof split is: input normal fields→48-bit exact product; two comparison branches→normalized ratio bounds; arbitrary proposal+exact inequalities→Nat quotient/remainder; parity remainder→`roundQuotientEven`; fixed binary32 rational rounder→raw packing. `Model.NativeBinary32.ofUInt32_roundRatScaled` is the public final transport bridge. Native approximation accuracy affects only how often the fast path is accepted, not its logical correctness. A source/axiom gate remains necessary for the actual combined implementation.

That word/model bridge alone does not prove that an arbitrary unreduced P/D*2^E representation equals `roundRational` of the corresponding canonical rational. A separate representation-congruence argument is required. Public foundations include `roundQuotientEven_eq_of_rat_eq`, `floorLog2_bounds`, `scaleByPowerOfTwo_real` and `roundRatScaled_false_eq_of_isIEEE`; alternatively use the finite/nonzero real-semantics bridge once its finiteness premises are established. Former #2 has its own cV/J6 proof, but its unknown reuse license prevents treating that implementation as a freely copyable helper.

This changes the cost premise relative to old FloatLib hardware-cast ADD: the old ADD already had a cheap native operation and the new integer alignment was slower. Here the measured target would be repeated exact rational division and normalization in RMS, and a proposed quotient uses one cached reciprocal multiply plus integer certification. That prospective advantage is not a measured fact. Row setup, data conversion, bounds, miss/fallback, output array work and two hardware environments remain in the full measurement boundary.

RMS alone only affects the normalized_mlp model. `SCORE-AND-COVERAGE.md` shows why a local core speedup must not be reported as a10% overall-score improvement; layer-normalization extension or actual model profiling is required for that claim.
