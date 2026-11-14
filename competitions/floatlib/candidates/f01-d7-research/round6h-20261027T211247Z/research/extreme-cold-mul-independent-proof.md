# Cold-only finite endpoints: independent uniform-mantissa argument

Scope: ac7c/869B fixed runtime. No Lean proof or performance is claimed. The wrapper is only a candidate cold target for the existing S128..380 normal hot arm, not a new guard on every ordinary call.

For a finite raw word with exponent E and fraction f, define q=f·2 when E=0, and q=2²³+f otherwise. Its magnitude is **q·2^(E−150)** uniformly. Both cases satisfy0≤q<2²⁴. Thus subnormal exponents need no unsafe normal-only formula or independent effective-exponent increase: the doubled fraction exactly accounts for raw E0.

If S=E₁+E₂≤102, both inputs are automatically finite because each exponent is nonnegative and less than255. Their exact product magnitude is q₁q₂·2^(S−300)<2⁴⁸·2^(102−300)=2⁻¹⁵⁰. This is strictly below half the least positive binary32 subnormal, so ties-to-even returns a zero with the product's XOR sign, including either signed-zero input. The strict bound handles the tie boundary; no finite input satisfies equality here.

If S≥382 and each Eᵢ<255, then Eᵢ≥128, so both inputs are normal and qᵢ≥2²³. Product magnitude is at least2⁴⁶·2^(382−300)=2¹²⁸, which is above binary32's RNE overflow threshold2¹²⁸−2¹⁰³. The correct result is the XOR-signed infinity. Inf/NaN input exponents255 must retain the original fallback, since Inf·0 is invalid and NaN payload/quieting follows the original operand rules.

Neither endpoint can be expanded by one without examining mantissas: at S103, two maximal mantissas round to the minimum subnormal; at S381, two minimal mantissas give the finite2¹²⁷. The independent model preserves those witnesses and rejects zero·Inf and payload NaNs from selection. The UInt32 sum of two8-bit exponent fields is at most510, hence cannot wrap.

The universal arithmetic premise is sound; the all-input public MUL transport, exact hot-caller identity and complete cold/miss cost remain separate unrun requirements. Source sample exposure is not a time-saving bound. No new formal source or CI was created by this review.
