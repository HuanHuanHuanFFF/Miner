# Broader conditional route: certify normalization from moment intervals

READ-ONLY PAPER. A owns the underlying truncated-accumulator route and confirmed this normalization composition was not already its assignment; B owns these upper-level notes. No runtime/Lean/CI is authorized, no performance is inferred. This route shares a mathematical primitive with A, so it is not an independent measured improvement to add to A's score.

## RMS: exact rounded denominator without a full exact square sum

Assume the stable domain and a proved integer n/L bound for A's truncation scheme. Put H=max input `idxOf`, B2=2H+48+L−62, and accumulate truncated nonnegative square terms into T2. The exact squared sum Q2 is enclosed by

    T2 * 2^(B2−298) ≤ Q2 ≤ (T2+n) * 2^(B2−298).

The upper endpoint is conservative; no discarded-bit count is assumed. Divide both endpoints by positive n and add **the exact epsilon**. The true q=Q2/n+epsilon lies in this positive rational interval.

A native operation may propose a positive normal binary32 denominator d. Let [l,u] be its exact RNE cell, with appropriate open/closed endpoints from mantissa parity and the asymmetric lower spacing at a power of two. Since l,u>0, sqrt(q) lies in that cell whenever q lies between l² and u² with the same endpoint strictness. Certify the entire q interval against these squared bounds. Multiplying comparisons by n avoids forming a rational quotient. If accepted, d is exactly the specified rounded denominator; otherwise compute the unchanged exact row result. The stable denominator bound52≤field≤254 supports the proposed domain; it does not remove the need for the certificate.

This can remove full limb square accumulation and integer sqrt/division on accepted rows. The proposal can be made from T2 and its scale once per row; no separate native floating scan is mathematically required. How to produce it cheaply is unimplemented.

## LayerNorm: moment enclosure and output enclosure

With a common finite input exponent maximum H, A-style truncation for signed sum uses B1=H+24+L−62, while squares use B2 above. Let the exact real moments satisfy S1∈[a,b] and S2∈[c,d]. Then

    n*S2 − S1² ∈ [n*c − max(a²,b²), n*d − minSquare(a,b)],

where minSquare is0 if a≤0≤b, otherwise min(a²,b²). Intersect the lower endpoint with0, since the exact centered variance is nonnegative. Divide by n² and add exact epsilon before the square-root-cell certificate. Scales must be aligned exactly before arithmetic; interval endpoints are not rounded floats.

The two coefficient scales satisfy B2−2*B1=62−L. Thus the main variance comparison can align n*T2 by a left shift of62−L against T1². Under |T1|<2^62, T2<2^62 and n≤2^L with a bounded small L, these main coefficients require roughly128-bit integer arithmetic, not a single64-bit word. Exact epsilon alignment can require more bits and must be charged separately. Do not claim the entire row is fixed64/128 merely from this identity.

**A certified denominator alone is not sufficient for LayerNorm.** The final expression still depends on the exact mean. Keep mean interval[a/n,b/n]. With the now-exact positive d, each final expression

    y_i = (x_i−mean)*gain_i/d + bias_i

is affine in mean. Reverse the interval endpoints when required by the sign of gain, include the exact bias, and certify that the complete resulting interval lies in one binary32 RNE cell. Accepted output is then exact even though S1 was never fully reconstructed. Nonzero normal cells are the conservative first domain; zero/subnormal/infinity results use the exact fallback. Exact zero is canonical+0, so a raw negative-zero shortcut is not justified. If any row certificate fails, the simplest proof uses an exact row fallback; finer per-output fallback needs a shared exact-mean policy and must include that cost.

This extends interval certification to stable normalization, rather than replacing its rational specification by staged native arithmetic. It also explains why replacing only dotFn does not affect the stable branch.

## First discriminators

Before substantial implementation, obtain source-matched model/layer costs and select a licensed implementation base. Current report retrieval is blocked by a preserved403 response, so these costs remain UNKNOWN. If authorized, first compare a complete RMS row path including header scan, coefficient loops, endpoint/proposal checks, output divisions and all fallbacks. Preserve miss-heavy cancellation/near-constant LayerNorm rows and wide-exponent cases. Only a useful whole-model result buys full transport proofs and independent confirmation. Do not add savings from the dot interval and normalization interval paths without testing their actual combined source.

The actual production score uses AMD64 and ARM64 strata and profile-weighted geometric cell ratios. Both normalization families must improve sufficiently to support a large overall reduction; `SCORE-AND-COVERAGE.md` gives the algebra, not a measured forecast.
