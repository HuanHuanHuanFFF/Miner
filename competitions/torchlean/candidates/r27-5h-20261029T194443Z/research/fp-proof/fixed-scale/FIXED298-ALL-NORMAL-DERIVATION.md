# Fixed298 extension to every normal proposal cell

Status: mathematical derivation plus finite boundary replay; not Lean acceptance and not selected for integration. Current requested checker repair and the smaller conditional narrow-domain source stay unchanged. No new CI is requested here.

Let q have sign s, normal biased exponent E in [1,254], fraction F in [0,2^23-1], M=2^23+F, and D=2^(E+148). For an exact integer total T, its positive magnitude is N=|T| and its real magnitude is N*2^-298. A binary32 unit in this bin is U=2^(E-150)=D*2^-298. The actual raw64 checker cells therefore reduce exactly to the integer inequalities below. The checker must first supply the correct sign and strict real cell; neither is silently assumed by the final kernel.

| Proposal branch | Lower inequality | Upper inequality |
|---|---|---|
| F>0 | D*(2M-1)<2N | 2N<D*(2M+1) |
| F=0, E>1 | D*(4M-1)<4N | 2N<D*(2M+1) |
| F=0, E=1 | D*(2M-1)<2N | 2N<D*(2M+1) |

For F>0, M>2^23. The bounds give 2^(E+171)<=N<2^(E+172), so N.log2=E+171. NativeBinary32.roundDyadic at exponent -298 uses shift E+148 and roundQuotientEven(N,D)=M. There is no carry because M<2^24. Its encoded exponent is E. This branch also covers E=254 and F=2^23-1; it never assumes the exact magnitude is at most maxFinite32. The strict upper cell boundary itself controls overflow rounding.

For F=0, split at N=M*D. At or above that point, the same log/shift/quotient argument gives mantissa M=2^23; the missing strict-nonpower lower bound is supplied directly by N>=M*D and D>0.

For F=0, E>1, and N<M*D, put P=2^(E+147), so D=2P. The lower quarter-ULP inequality gives P*(2*(2M)-1)<2N. The upper half of the quotient-cell inequality follows from N<M*D. Hence roundQuotientEven(N,P)=2M=2^24. Also 2^(E+170)<=N<2^(E+171), so leading=E+170. The native normal branch uses shift E+147, then carries the rounded mantissa; total exponent E-128 becomes E-127, giving encoded exponent E and fraction0. E>=2 is precisely what makes this a normal-branch case before the carry.

For E=1, F=0, and N<M*D, leading=171 and total exponent is -127. The native subnormal branch evaluates the fixed expression -298+149=-149 and therefore rounds N right by149, exactly N/D. The symmetric half-ULP bounds give rounded fraction M=2^23; the implementation's explicit fraction==2^23 branch emits minimum-normal (exponent1, fraction0). No general rational rescaling lemma or generic dyadic cell theorem is needed.

Sign handling is orthogonal. The prepared append fragment ActualTotalSign.lean.inc derives sign(T)=sign(q) from actual checker acceptance, radius finiteness and the producer error bound through strict RNE fixed-point pullback. The official finishWord has the desired sign because it constructs ofIntDyadic T -298. The accepted cell also proves T!=0, so negative-zero finish behavior remains exclusively on exact fallback paths.

The exact finite probe in NORMAL-BOUNDARY-RECEIPT.json covers every E1..254, six representative fractions (including0,1,2 and both upper edge fractions), both signs, and nine positions around each lower/Q/upper boundary:27432 integer totals. All expected adjacent/tie/strict-cell results matched the independent exact integer rounder. normal-boundaries.csv preserves all inputs/results (SHA2626e813e4ae78d0aac5fdc3a372d5897c58b42c13e2c7dd4d78124c5999d009). This is a branch falsification probe, not a proof for every fraction, a benchmark, or a probability estimate.

Decision: retain the smaller E2..253/nonpower helper as the immediate optional diagnostic. If its exact Lean result and FP native cost justify more work, this four-case derivation provides a bounded path to the original all-normal checker without a proposal-domain restriction. It does not eliminate the actual producer, raw midpoint decoding, fallback, cache/bias or final all12 obligations.
