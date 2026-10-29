# Exact LayerNorm certificate using one high word and a sticky bit

PAPER ONLY; no candidate, Lean execution or benchmark. C independently checked this new algebraic extension once and found no counterexample under the explicit guards below. This is not another performance claim or an independent confirmation sample.

The final exact LayerNorm value can be represented as sign·(N/D)·2^E with N the **nonnegative absolute value** of its exact integer numerator and D=n*mantissa(d)>0, shared per row. N may be hundreds of bits; do not reuse the RMS48-bit numerator bound. A stable denominator is normal by the separately stated paper bound. D<2^38 is a sufficient machine-certificate guard; n≤16384 suffices because the denominator mantissa is<2^24. Outside the guard retain the exact fallback.

Let an arbitrary positive normal proposed output have field Z∈2..254 and mantissa M∈[2^23,2^24). Set

    j = E + 152 − Z,
    X = N * 2^j = H + f,    H=floor(X), 0≤f<1.

For j≥0, H=N<<j and sticky=false. For j<0, H=N>>(-j) and sticky records whether any discarded low bit is nonzero. An exact form is `H<<(-j) != N`. Since N≥0, sticky is precisely f>0. Do not apply signed arithmetic right shift to a negative numerator and assume this fractional interpretation.

Check H<2^64 **before** converting it to UInt64. A bad proposal can cause H to be too large even when the actual final answer is finite. Compute one product T=2*D*M, then exact integer boundary values:

    U = 2*T + 2*D,
    L = 2*T − 2*D              if M>2^23,
    L = 2*T − D                if M=2^23.

The upper condition is H<U, or H=U with sticky=false and M even. The lower condition is H>L, or H=L with (sticky=true or M even). Together they are equivalent to the original exact RNE-cell inequalities for the positive final value. Restore the exact numerator's sign only after certification; N=0 can return canonical+0 in stable normalization or use the unchanged fallback.

**Word-width proof:** D≤2^38−1 and M≤2^24−1 imply

    U = 2*D*(2*M+1) < 2^39 * 2^25 = 2^64.

All lower bounds are nonnegative and below U. Also D*M<2^62 and T<2^63. Merely stating T<2^63 would not alone justify the addition in2*T+2*D; use the combined strict bound. Native shift counts and Nat-to-word conversions retain explicit range/no-loss guards.

This converts exact comparison of an arbitrarily large numerator to a64-bit mantissa-times-denominator product plus one high-word extraction and sticky test. It avoids exact rational division in the verifier. It does **not** eliminate forming N, computing a useful proposal, or reading/packing the output. Those costs could dominate. A native proposal can be formed from high bits without assuming a numeric theorem about its approximation, but an effective/cheap seed is still an implementation question.

The first conservative version rejects target field1, subnormal, infinity and NaN proposals. C notes field1 can also be handled soundly with a subset certificate at the minimum-normal boundary; that optional extension is not needed to establish this route. Expanding target range after observed feedback would be a new candidate, not a reuse of frozen confirmation.

The intended broad benefit is both LayerNorm and RMS outputs in normalized_mlp/mixer. Actual affected times, proposal hit rates, compiler behavior on both AMD64/ARM64 and whole weighted score remain UNKNOWN. The smallest future implementation remains the RMS quotient witness because its proof and arithmetic state are smaller; this extension prevents treating RMS's single-family coverage as the final whole-score strategy.
