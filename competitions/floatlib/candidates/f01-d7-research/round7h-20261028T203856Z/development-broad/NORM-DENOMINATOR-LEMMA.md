# Stable norm denominator: a universal finite-normal domain

Status: complete paper argument below, finite extreme model checks; NOT_LEAN_CHECKED. Source domain is current `ContractExact` stable finite branch, not a distribution assumption. No Kernel change or CI. This strengthens the B certificate route; the old native-pair candidate stays frozen.

**Claim.** For either stable RMS or layer norm, whenever the original `stableNormDomain` is true (and the original layer-norm bias checks hold), the rounded denominator `d=sqrtRational(variance+epsilon)` is a positive normal binary32 word. Its exponent field is between52 and254 inclusive. In particular `sv d > 0`; the per-output nonpositive-denominator fallbacks in former2's `Ya7`/`Yba` are unreachable on this stable branch.

Let

`F=(2^24−1)*2^104 = 2^128−2^104`

be the maximum positive finite binary32 number, and let

`T=2^128−2^103 = F+2^103`

be the nearest-even overflow midpoint between F and the next virtual finite lattice value2^128. All stable-domain inputs and epsilon are finite, epsilon is positive, and `n>0`. Hence

`|x_i|≤F`, `2^-149≤epsilon≤F`.

For RMS, `0≤variance=(Σx_i²)/n≤F²`. For layer norm,

`variance=(Σx_i²)/n − ((Σx_i)/n)²`,

so `0≤variance≤(Σx_i²)/n≤F²`. Nonnegativity is Cauchy/Σ(x_i−mean)²≥0; this is precisely the integer-moment nonnegativity already used in former2's proof of `nQ−S²≥0`.

Writing `q=variance+epsilon`, obtain

`2^-149≤q≤F²+F<T²`.

The strict upper inequality follows from

`T²−F²=(T−F)(T+F)=2^103*(T+F)>F`.

Thus `2^-74.5≤sqrt(q)<T`. Nearest-even binary32 rounding cannot be zero/subnormal (the lower value is vastly above2^-126), negative, NaN or infinity (the upper value is strictly below the overflow midpoint). Monotonicity also gives `RN32(sqrt(q))≥2^-75`; the largest possible finite rounded result isF. Biased exponents therefore lie in`[52,254]`.

This is universal over finite input magnitudes, signs and every positive dimension. It does not assume the benchmark's bounded exponents, avoid intermediate rational overflow (rationals are exact), or guarantee finite *final outputs* for arbitrary gains/biases. The specification's legacy branch outside the stable domain stays separate.

## Consequence for exact candidate certificates

The B1 squared-cell certificate can cover every possible stable denominator using positive normal candidates, including maximum finite. At the maximum finite candidate, use the virtual next value2^128 to form its upper midpointT; do not attempt to decode an infinity as an ordinary rational. At minimum normal, the predecessor is a subnormal and the usual half-gap still applies. Ties use the candidate's significand parity; F is odd, so a value exactly atT is rejected for F, correctly selecting infinity outside the stable bound.

No accuracy theorem is needed for the *guesser*: if its candidate is wrong/NaN/subnormal, reject and call the existing exact `sqrtRational`. The domain proof concerns the true denominator, not the native guess. After the denominator is verified once per row, its positive significand/exponent can be stored in row state, avoiding repeated `sv d≤0` classification in every output's rounding path. Actual runtime savings and whether current champion5 already does this are UNKNOWN.

The model added both extremes: `q=2^-149` certifies word`1a3504f3`; `q=F²+F` certifies`7f7fffff`. Those examples support implementation of the bounds/cell edges; the universal claim relies on the argument above, not enumerating inputs.

## First proof interfaces to check if implementation is authorized

- Lift finite-word bounds and epsilon's minimum positive value through `rationalWord`.
- Reuse exact variance nonnegativity and moment identity; prove the average-square upper bound from a finite sum.
- Apply existing `sqrtRational_eq_math` plus nearest-even/overflow rounding boundaries to get `finiteWord d`, positive sign and nonzero normal exponent.
- State the certificate soundness for arbitrary candidate words, then instantiate native guesses. Preserve the raw stable guard and legacy fallback.

The paper proof does not establish these Lean interfaces or the complete new-target obligation. Native C/ASM and whole-model time remain NOT_RUN/UNKNOWN.
