# R24 two certificate routes — first decision package

Read-only investigation resumed20:57:50UTC; shared cutoff2026-10-29T03:38:56Z unchanged. No new-track Kernel/Lean/native build/CI. Old223426ec native-pair package remains frozen. Current champ5 source and actual model/layer cost shares UNKNOWN. Own finite models are in `certificates.py` and hash-bound `certificate-model-results.json`; no holdout/adoption data used. Parent snapshot former2 is exactly `cea4422fb6d3bd613b306127e7017331560875ddb840a7f2e174f6c03bdb480f`,254884B, licenseUNKNOWN, inspected without copying bodies into a candidate.

**First decision:** retain Float64 interval dot and division-free norm output certificates as genuinely different next discriminators. Park an ordinary Float32 forward-error filter: its conservative enclosures accepted0/384 of the same finite synthetic dots. The model's Float64 enclosure accepted384/384 and norm certificates16128/16128 ordinary synthetic outputs, but those are observed finite cases, not time shares, production success probabilities or performance evidence. Both routes still need real complete-lifecycle cost before substantial proof investment.

## A. Float64 dot with an exact rounding-cell certificate

### Mathematical claim

Take finite binary32 operands, `1≤n≤2^51`, exact products `p_i=a_i*b_i`, and a binary64 nearest-even fold `s_hat`. Every binary32 product has at most48 significant bits and exponent between−298 and255, so it is exactly representable as a normal binary64 value or zero. Choose `M=2^(E+1)`, where `E` is any upper bound on the floor exponent of every nonzero product, and `u=2^-53`.

The conditional enclosure to formalize is

`|s_hat − Σ p_i| ≤ n² u M ≤ B := 2^(E+2*ceil(log2 n)−52)`.

Derivation: finite products lie on the2^-298 lattice. A rounded binary64 prefix stays on that lattice, so every nonzero prefix is normal; the product and count bounds keep every prefix far below binary64 overflow. With `e_k` the absolute prefix error,

`e_k ≤ (1+u)e_(k−1)+k*u*M`.

Inductively `e_k≤k²*u*M`, since `u*(k−1)≤1`. The binary64 arithmetic/enclosure bridge is still a proof obligation, not a Lean-checked theorem here.

For an arbitrary guessed finite nonzero normal binary32 word `w`, decode its exact predecessor/current/successor values and set `L=(prev+w)/2`, `U=(w+next)/2`. Accept only if the exact dyadic comparisons certify

`L < s_hat−B` and `s_hat+B < U`.

Then exact nearest-even binary32 rounding of the true dot must be `w`. The guess need not itself be a proved correct Float64→Float32 cast. Strict inequalities deliberately send ties, zeros, underflow, overflow and ambiguous cases to the original exact dot. Any NaN/Inf input also goes to that full raw-word fallback, preserving payload/order/negative-zero semantics. Bias is an additional exact term, not a separately rounded add.

### Concrete difference from former2

Former2's `YaU` (line1267), `YaC` (line2006) and `Ya2` (line2177) use exponent summaries and reject `hi−lo>122`; inside that domain they preserve all significant bits with machine-word accumulators. Its final record (line3736) selects those dense/conv implementations, while core still uses the older exact accumulator. Replacing only its core dot would not automatically reach the optimized model paths.

The interval route can ignore low bits only after proving they cannot affect final rounding. Directed example `[1,2^-149]·[1,2^-149]` has an exact299-bit integer span, yet the certificate accepts1. This differs from fitting the entire exact sum into a bounded accumulator. By contrast `[1,2^-26,−1]·[1,2^-27,1]` fools an unchecked double fold (0 instead of2^-53); the enclosure rejects it. An exact binary32 midpoint also rejects even when the native guess happens to be correct. These are in the result file.

### Native interface/cost premise

Pinned Lean4.34 `Float.add`, `Float.mul`, `Float.ofBits` and `Float.sqrt` have logical `Float.Model` definitions (upstream `src/Init/Data/Float/Float.lean`, lines76,91,134,478); these operations are not all opaque. Avoid relying on the opaque cross-width cast: finite binary32 words can be expanded directly to binary64 bits. For a normal input with exponent field`e`, use double exponent`e+896` and fraction shifted29; a subnormal with leading fraction bit`l` has double exponent`l+874` and fraction `(frac−2^l) << (52−l)`. Signed zero maps by sign only. The resulting exact native input bridge needs proof, but no assumed cast roundtrip.

Prepared `FloatArray` stores/reads Float directly, so the new hot arithmetic is genuinely binary64 and has no Float64→Float32 narrowing per MAC. Preparation/ownership may dominate short dots; raw-word `Float.ofBits` calls must occur once per reusable input, not once per output. A supported happy path would delete the exact limb arrays/updates/final digit work, adding native-double input preparation, one F64 multiply/add per term and an exact dyadic cell check per output. Failure adds that whole attempted path before the original dot. Actual C/ASM, caller cache reuse, required AMD/ARM time, new model exposure and net gain are UNKNOWN.

Smallest next cost discriminator, only after target authorization: one actual model callback plus unchanged control, frozen n/input sets, finite summary/cache preparation, failure replay, output release; inspect the selected caller for repeated decode, a per-MAC call or hidden container work. Stop if preparation or final cell arithmetic erases the expected limb-work reduction. No large proof before that result.

## B. Stable norms: arbitrary guesses plus exact certificates

### Existing work that must not be repeated

The contract's stable norm statistics are exact rationals. Former2 already removes generic rational mean/variance work: `Y2`/`Y6`/`Y7` (lines2366–2374) find a common exponent and collect integer sum/squares; `Y8` (2405) uses `n*Q−S²`. `YaD` (2391) scales a numerator/denominator, then `sqrtLower = Nat.sqrt(num/den)` and `sqW` certify/round it. `Ybb`/`Ybc` (2802/2807) reuse the row denominator/statistics. Final RMS `Ya7` calls `YN`; layer `Yba` (2677) uses a common denominator plus three explicit `/D` and three `%D` expressions before its rounding branch. These source expressions are not asserted to be six distinct runtime divisions; compiler CSE and machine costs have not been measured.

Therefore “use nQ−S²”, “avoid Rational GCD by integer moments”, or “share the denominator” are already implemented, not new routes. A fused moments pass could save one row read/decode traversal but is a smaller independent change with whole-time coverageUNKNOWN.

### B1. Square-root cell certificate

For exact `q=N/D*2^E>0` and an arbitrary guessed positive normal binary32 `w`, form exact positive midpoints `L,U`. Accept when `L²<q<U²`, also allowing equality at either boundary only when the candidate's low significand bit is even. Since squaring is strictly increasing on nonnegative reals, this certifies `RN32(sqrt(q))=w` without proving the native sqrt or conversion that proposed `w`.

For a normal candidate `w=M*2^e`, `2^23≤M<2^24`, the upper midpoint is `(2M+1)*2^(e−1)`. The lower midpoint is `(2M−1)*2^(e−1)`, except at a normal binade boundary where it is `(4M−1)*2^(e−2)` (minimum-normal transition uses the first form). Thus the check needs exact integer products by <50-bit squared midpoint coefficients and shifts/comparisons, not an integer square root or division. Guarded sizes can use multiword arithmetic; larger sizes fall back to the existing exact sqrt. The exact stats numerator remains necessary.

The finite model accepted288/288 ordinary RMS/layer row denominators and handled six exact midpoint ties with parity. At `q=((1+2^-24)^2)+2^-200`, native double sqrt/cast guesses1 incorrectly, and the certificate rejects it. Actual row sqrt time and complete norm gain remainUNKNOWN.

### B2. Division-free final affine rounding certificate

Let raw inputs share exponent `e`: `x_i=X_i*2^e`, `S=ΣX_i`. Let verified rounded denominator `d=M_d*2^e_d>0`, gain `g_i=G_i*2^e_g` and bias `b_i=B_i*2^e_b`. RMS exact output before final rounding is

`(X_i*G_i / M_d)*2^(e+e_g−e_d)`.

For layer norm choose `c=min(e+e_g,e_b+e_d)`, then

`P=((n*X_i−S)*G_i)*2^(e+e_g−c) + n*B_i*M_d*2^(e_b+e_d−c)`,

and exact output is `(P/(n*M_d))*2^(c−e_d)`.

These are already related to former2's fraction-free algebra. The new step is to **replace quotient/remainder rounding with a guessed-word certificate**. For exact value `v=P/D*2^k`, accept arbitrary normal `w` only when `D*L < P*2^k < D*U`; strict inequalities again avoid ties. Equivalently compute one exact residual `R=P*2^k−D*w`, then compare it with the two half-ULP powers of two multiplied byD. This uses one candidate significand multiply, shifts/subtract/compare and zero detection, not `/D`, `%D`, floor-log-ratio or GCD. Exact zero returns+0; other unhandled domains preserve the old final rounder.

No numerical accuracy theorem is needed for a native approximate mean/affine guess: soundness is entirely in the exact integer certificate. The raw stable-domain guard and malformed/legacy fallback stay unchanged. A guessed mean losing the middle term of `[2^100,1,−2^100]` produces one wrong output; the checker accepts only the other two. Ordinary synthetic outputs all passed the certificate, but output success frequency is not a performance model.

### Cost/risk discriminator

For the model's finite generated rows, unreduced RMS numerators needed53bits normal/sparse and87bits wide; layer numerators67–72bits normal/sparse and90–95bits wide, with denominators≤32bits. This suggests a128-bit checked arithmetic discriminator. Directed zero-bias/extreme rows reached175–179bits under the naive common-exponent choice, so “all norm intermediates fit64/128” is false. Such cases require a wider path or exact fallback; avoid building a huge shifted zero-bias term when its coefficient is0. These are observed sizes only.

B2 has better proof isolation thanA: certificate soundness quantifies over any guessed word and can reuse the existing exact expression, so no Float64 fold-error bridge is needed. It also targets n final outputs per row rather than only one root per row. Prefer its minimal complete norm callback cost before B1-only native sqrt work. Charge numerator construction, candidate generation, integer certificate, failures and complete release. New model-family layer time and current champion5's implementation are UNKNOWN, so no ≥10% whole claim is justified yet.

## Evidence status and next work

All model assertions passed, including exact enclosure checks, exact fraction-free output identities and rejection of planted wrong guesses. They establish finite mathematical-model evidence only. Neither route has a Lean proof, an actual selected new-target caller, complete lifecycle timing, official gate, independent confirmation or adoption. The old FloatLib benchmark percentages are not reused. Continue by tightening/checking the proposed certificates and constructing adverse cases while target implementation remains unapproved.

## 21:42 update: price the max bound and keep the final checker in words

The original dot-model envelope observes the actual largest product. A real implementation cannot treat that observation as free when it has already prepared only native-double arrays. A cheaper deployable premise is a max-absolute-word summary, collected while each input cache is built. Finite positive binary32 magnitude is monotone in its sign-cleared word, so this summary needs integer comparisons, not another native conversion per MAC.

For a row/filter pair let`M0=maxAbs(A)*maxAbs(B)`, an exact product of two binary32 values. For a linear/conv bias term use`M=max(M0,abs(bias))`; do not inject the synthetic one into the activation summary and inflateM for a pairing that never occurs. Its at-most48-bit integer mantissa/exponent can be computed from the two maximum raw words. The same induction gives the more precise bound`B=n²*2^-53*M`, without roundingn up to a power of two. Under the explicit fast-domain cap`n≤2^20`, its mantissa coefficient is below2^88 and fits88 bits. This changes representation/price, not shape thresholds selected from timings. Other shapes and special inputs preserve the exact fallback.

`nmlp_coverage_model.py` now follows the public current`profileModel/nmlpLayers` formulas on one own seed and all three typical/scale/boundary profiles × normal/wide/sparse inputs, batch1. This is a mathematical simulation, not an official Lean/native checksum run. Across these9 models, old product-peak/power-of-two envelopes accepted2061/2064 linear outputs. The cheaper separable exactM envelope accepted2064/2064, with all nine exact reference-output checksums unchanged. All raw rejected old envelopes remain in the result file, and previous model/source bytes are preserved under`math-checkpoints/20261028T213836Z/`. Eighteen internal norm rows hadR≤11 and satisfied the128-bit moment guard; all1974 norm-output guesses certified. No other seed, batch, model family, architecture or time fraction is inferred from these cases.

The A final rounding-cell check need not build unbounded dyadics either. Decode a finite normal double sum as`Ms*2^es` with a53-bit coefficient. Decode each positive normal guessed32-bit midpoint as`Ml*2^el`/`Mu*2^eu`, with at-most25-bit coefficients. Require both exponent gaps`el−es`/`eu−es` to lie in`[0,64]`; otherwise fallback. The shifted midpoint coefficients then fit89 bits. Check that`deltaLo=Ms−(Ml<<gapLo)>0` and`deltaHi=(Mu<<gapHi)−Ms>0`, and compare`delta*2^es` to the88-bit bound coefficient times its power of two using the exact scaled128-bit comparator from`MOMENT-WIDTH-LEMMA.md`. Same-sign negative sums/candidates are handled by magnitude symmetry. Incorrect guesses can only fail the check. Thus both A's output enclosure and B's output residual have a fixed-word certificate path; actual word arithmetic/ABI/calls and C/ASM costs are still untested.

## Primary-source cross-check, not inherited performance

[Rump, Ogita and Oishi, Part II](https://www.tuhh.de/ti3/paper/rump/RuOgOi07II.pdf) separates faithful from nearest rounding and explains why exact midpoint cases can require exact information. This supports retaining an exact fallback rather than accepting a merely faithful double result. Its expansion/refinement algorithms are not implemented or benchmarked here.

[Rump's error-estimation paper](https://www.tuhh.de/ti3/paper/rump/altRu11.pdf) gives a sharper computable bound using a rounded absolute sum and its leading power of two. It is a possible second discriminator if fallback is measured to dominate; the simpler max-summary enclosure currently avoids an extra absolute-sum fold. No theorem from that paper is promoted to Lean acceptance.

[ExBLAS at856130e](https://github.com/riakymch/exblas/tree/856130ebcfe906f519a623d57d1359e744e29042) has actual floating-expansion code in`src/cpu/blas1/ExSUM.FPE.hpp`: early exit handles zero residuals inside expansion insertion, while remaining residuals are flushed to a superaccumulator. Its AVX/TBB implementation and timings do not transfer to pure Lean/AMD+ARM. The repository's redistribution license was read; no source body was copied into a candidate. This is prior-art/implementation evidence, not a new high-performance claim.

## After the negative08a scalar cost: a distinct exact-product premise

Scalar's exact08a ADD body is parked: actual legal FloatArray+GRS ADD was1.049–1.077×B2, four whole blocks all slower. Its audited caller performs *two* numeric decodes (two casts, scale loads and multiplies), one F64 add, then same-width toBits/GRS on **every scalar ADD**. That result is retained and no threshold/seed retry is proposed. Old R22`FloatProduct.lean.inc` was a different F32-product construction and already cost-negative; it is not this exact F64 representation.

For an exact dot there is another concrete representation to investigate on paper. Decode finite raw words to unsigned24-bit mantissands`ma,mb` and dyadic indices`ia,ib∈[0,253]`. First form the exact integer`mp=ma*mb<2^48`, then compute

`product64 = sign * (Float(mp) * scale[ia+ib])`,

where`scale[i]=2^(i−298)`, i0..506. The scale's binary64 exponent bits are`(i+725)<<52`; all507 values are exact normal doubles. The integer cast and scaled result are exact binary64 (≤48 significant bits, no underflow/overflow), including min-subnormal inputs; sign also preserves zero. Thus this requires **one** cast/scale read/multiply per product, not separately decoding two floating inputs and then multiplying them, and no per-call tensor caches. The507-entry constant table has real startup/memory costs. `product64-results.json` checks20000 finite pairs and extreme/signed-zero cases against exact fractions. It is no implementation or cost result.

The pinned actual header982c731a shows UInt64/Int64→Float casts and Float add/mul/negate are static inline, so a per-MAC conversion FFI call is not forced by the API. Actual selected C/ASM is still required (unsigned-cast expansion, getter bounds, callback specialization, state spills). A UInt32 callback is immediate on64-bit targets; no nonexistent heap boxing savings are claimed.

Once per completed dot, same-width`Float.toBits` serves both a guessed32-bit word and its exact cell certificate.08a's unproved integer GRS can be reused *as an arbitrary guesser*, since accepted output follows from the independent certificate; there is no need to prove that guesser's narrowing accurate first. Its cost and the exported toBits call are then per dot, not per MAC. This does not remove the required proof that the native F64 fold obeys its enclosure.

For a cheap in-loop max bound, the product integer already computed supplies a conservative leading exponent: top bit47 selects47, otherwise46 is an upper bound (subnormal products may make it loose). Track the maximum`ia+ib+leading` only on nonzero products, and use `M=2^(maxLeading−297)`. This adds one peak field, avoids another raw decode, and remains sound for finite subnormal inputs; a loose interval can only cause exact fallback. Whether this loop or cache preparation is cheaper is stillUNKNOWN and must be discriminated by a complete portable primitive/model caller if authorized. The negative08a ADD result establishes neither success nor failure of this different dot lifecycle.
