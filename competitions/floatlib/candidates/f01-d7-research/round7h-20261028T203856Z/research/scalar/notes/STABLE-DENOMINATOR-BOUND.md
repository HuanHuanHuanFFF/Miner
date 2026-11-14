# Paper bound: stable normalization denominator is positive finite normal

Status: independently derived mathematical argument, not a compiled Lean theorem or performance result. Only read-only source/mathematics work is authorized here.

Let M=(2−2^-23)2^127=2^128−2^104 be the largest finite positive binary32 value. In the stable domain, n>0, every x_i is finite, and epsilon is positive finite binary32. Consequently |x_i|≤M and 2^-149≤epsilon≤M.

For RMS, v=(sum x_i²)/n satisfies 0≤v≤M². For layer norm, the exact identity v=(sum x_i²)/n−mean², together with the original sum-of-squares definition, gives the same bounds 0≤v≤M². Neither statement relies on a floating-point approximation or on the benchmark input distribution.

Therefore q=v+epsilon satisfies 2^-149≤q≤M²+M. Its exact square root obeys

    2^-75 < sqrt(q) < M + 1/2.

The lower strict inequality follows from (2^-75)²=2^-150<2^-149≤q. The upper follows from (M+1/2)²=M²+M+1/4>q.

RNE32 is monotone. Since 2^-75 is representable, rounding sqrt(q) cannot fall below 2^-75. The overflow midpoint above M is M+2^103, vastly above M+1/2, so rounding cannot produce infinity or exceed M. Thus the rounded denominator d is positive finite normal, with raw exponent field **52≤E_d≤254**. Its mantissa is in [2^23,2^24), and its sign bit is false.

This is stronger than merely observing positive denominators on tests. To formalize against the fixed contract, connect `sqrtRational_eq_math`, finite-word exact value bounds, the rational variance identity, monotonic nearest-even rounding and the precise overflow midpoint. No need to prove a statement about the native sqrt implementation. Cases outside `stableNormDomain` retain the existing staged fallback.

Consequences if actually proved and integrated:

- Hoist denominator sign/finite/nonzero classification once per row; the stable per-output slow branch for nonpositive denominator is unreachable.
- Reuse a row record containing the rounded raw denominator and its24-bit mantissa/exponent. This avoids repeated field extraction but adds record/array costs that must be measured.
- The RMS output numerator P=mant(x)*mant(g) is<2^48 and denominator D=mant(d) is24-bit nonzero. This is the bounded rational input for `CERTIFIED-RATIONAL-ROUNDING.md`; a candidate proposal quotient may use only this ratio, with the original exponent handled separately.

These consequences do not by themselves establish a large runtime gain. The prospective benefit of the exact-cell checker is replacing per-output division/normalization; the denominator theorem supplies a uniform domain and simpler guards.
