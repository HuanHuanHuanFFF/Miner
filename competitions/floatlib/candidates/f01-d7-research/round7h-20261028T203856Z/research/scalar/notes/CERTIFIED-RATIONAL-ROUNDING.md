# Read-only route: native proposal, exact rational rounding certificate

This is a mathematical/cost proposal for target selection, not an authorized new-track implementation. No Lean source, runtime, benchmark or claimed speedup is attached. Former #2 source is publicly readable but reuse license is UNKNOWN; the formulas below are independently described arithmetic.

**21:45 source correction:** the fixed public library already lowers bounded Nat quotient rounding to native UInt64 arithmetic, and the RMS normalized domain satisfies that bound. `PUBLIC-REUSE-AUDIT.md` supersedes any earlier assumption that this RMS tail necessarily performs big-integer division. Native caller cost remains unmeasured; LayerNorm's wider explicit quotient path and interval-statistics removal are separate opportunities.

## Residual work actually present

In public former #2 `cea4422f`, normal RMS output helper `Ya7` forms P=mant(x)*mant(g), D=mant(d), E=idx(x)+idx(g)−idx(d)−149 and calls `YN sign P D E`. The exact fraction has P<2^48 and D<2^24. `YN` computes a ratio exponent, rescales numerator/denominator and calls exact `roundQuotientEven`. Layer output `Yba` separately performs c/D, c%D, r0/D, r0%D, ra/D, ra%D before a final normalized rounder. Compiler sharing of each div/mod pair and actual costs are UNKNOWN.

The denominator d is shared by all outputs of a row. Normal RMS therefore offers a clean first interface: amortize a native reciprocal/proposal representation once per row, compute a proposed binary32 quotient z for P/D, verify its exact rounding cell using machine-word shifts/multiplications/comparisons, and only then exponent-translate to the final value. A rejected proposal uses the original exact rounder. No numeric theorem about the proposal or an opaque cast is required for *soundness*; performance needs actual proposal success and full costs. This is distinct from merely replacing exact reduction by native arithmetic.

## A division-free normal quotient certificate

Assume P>0, D>0. Let positive finite normal candidate z have exponent field Z and mantissa M=2^23+fraction, hence value M*2^(Z−150). Reject proposal fields outside 103..152 for this RMS interface: P/D lies between approximately 2^-24 and 2^25. This restriction is an optimization guard, not a theorem about an opaque proposal.

Set k=151−Z. If k≥0, set A=P*2^k and B=D. If k<0, set A=P and B=D*2^(−k). Require these values and all products below to fit their chosen machine widths; failures go to the unchanged exact fallback.

The upper midpoint comparison is A versus B*(2M+1). For M>2^23, the lower comparison is A versus B*(2M−1). For M=2^23, the predecessor spacing is half the successor spacing, so the lower comparison is **2A versus B*(4M−1)**. Accept strict interior points; accept either endpoint exactly iff M is even. These inequalities characterize the exact RNE cell of z for positive P/D without division. Output-sign handling is symmetric; P=0 is a separate canonical +0 case in stable normalization.

The checker need not compute two separate boundary products. Compute **T=2*(B*M)** once. Then upper=T+B, ordinary lower=T−B, and power-of-two lower=2*T−B to compare with2*A. This is one24-by24-bit multiplication (B may become25-bit for Z=152), shifts/adds/comparisons. Check the upper condition before forming2*A; accepted upper bounds ensure this second value fits. For k≥0, `(P<<k)>>k=P` with0≤k≤48 is an exact unsigned no-loss guard. This is paper algebra, not a native instruction count or tested implementation.

For plausible candidates the certificate products are at most about 50 bits. An arbitrary bad proposal can make P*2^k overflow even though the intended answer is small; the checker must guard the shift and overflow rather than rely on proposal accuracy. Candidate generation can use existing native Float operations, including a conversion with unknown mathematical semantics, because no unvalidated candidate is returned. Exact final theorem axiom audit remains mandatory. Historical checked FloatArray already established this general checked-data pattern under Lean4.34; it does not establish this new certificate.

Scaling a certified z by 2^E can be implemented by raw exponent adjustment only under a proved target-range condition. E=1 at the minimum normal requires care: its lower neighbor spacing differs from an ordinary binade boundary. Conservative rejection of that boundary is acceptable initially; overflow/subnormal/zero cases retain exact fallback. Do not silently assume that scaling commutes with rounding in every exponent range.

The normal-to-normal scaling implication here also requires **source field Z≥2**, automatically true for the RMS ratio guard103..152. C's fixed counterexample to the broader claim uses x=2^-126−3*2^-152: it rounds first to minimum normal, whose raw exponent doubled gives0x01000000, whereas exact doubling rounds to0x00ffffff. Also check the translated exponent *before* any native scaling: checking only that a natively scaled result ended normal can accept a subnormal double-round error. C owns both fixed receipts under `../../rounding-review/notes/` (`normal-upscale-boundary-falsifier.json`, `minnormal-postscale-falsifier.json`). Neither weakens the current source guard or the direct normalized-quotient route.

## Square-root variant and a useful domain bound

A proposed integer root r may be accepted if r²D≤N<(r+1)²D; for D>0 this pins r to floor(sqrt(N/D)). It can then feed the existing exact midpoint/rounder, replacing the original Nat division plus Nat.sqrt. A native seed plus a bounded correction attempt is possible, but the certificate, miss cost and row-level frequency decide value. A root is computed only once per row, whereas final division occurs per output, so final quotient certification has broader operation count unless profiling contradicts this.

For arbitrary rational sqrt inputs, midpoint equality is real: N/D=(2r+1)²/4. Results asserting no sqrt midpoint for same-precision binary inputs cannot justify deleting the rational equality branch.

Possible proof simplification to investigate after authorization: for finite binary32 x and positive finite epsilon, exact RMS/layer variance is bounded by the square of the largest finite binary32 magnitude; epsilon is at least 2^-149. Therefore the rounded square-root denominator should be positive and normal, with a finite upper bound separated from overflow. This would support hoisting positivity/classification out of each output. It is currently PAPER, with the variance bound and overflow margin still requiring a formal argument, and is not used to erase existing fallback.

## Minimum experiment and stop rule

After target authorization, first profile public #2 or an independently licensed baseline on the exact current model suite; separate statistic accumulation, sqrt per row, final quotient per output, and all preparation/miss work. The first tiny implementation should be an arbitrary-proposal checker theorem plus one RMS output callback with exact fallback. Compare the complete normalization kernel, not a bare multiply/compare helper. Stop or redesign if guard/codec costs remove the prospective gain, if the current champion already eliminates this division, or if affected model time cannot support the desired whole gain. No current layer share, hit probability, runtime benefit or ≥10% claim is known.

## Primary mathematical references

- Brent and Zimmermann, *Modern Computer Arithmetic*, section3.5: integer root/remainder enclosures and final rounding. https://members.loria.fr/PZimmermann/mca/mca-cup-0.5.3.pdf
- Sylvie Boldo and Guillaume Melquiond, Flocq `Calc.Sqrt`, LGPL3-or-later source: exact square-root bracketing and rounding interfaces. https://flocq.gitlabpages.inria.fr/flocq/html/Flocq.Calc.Sqrt.html
- Dutton, Anand, Enenkel and Müller, *Inexactness and Correction of Floating-Point Reciprocal, Division and Square Root* (2024 preprint). Its same-precision no-midpoint statement is not an arbitrary-rational theorem. https://arxiv.org/abs/2404.00387

No source from these works was copied into a candidate.
