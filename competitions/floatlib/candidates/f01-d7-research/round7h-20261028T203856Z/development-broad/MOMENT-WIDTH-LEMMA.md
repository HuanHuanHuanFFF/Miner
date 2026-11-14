# Stable norm moments: bounded scalar words instead of eighteen Nat limbs

Paper arithmetic and finite model only; no new Kernel/Lean/native build/CI. Former2 already uses common-exponent integer moments, so the new difference here is **scalar fixed-width moment state and fused traversal**, not rediscovering`nQ−S²`.

For a positive row lengthn, ignore zero mantissands when choosing minimum/maximum raw dyadic exponents. Let their spread beR, `L=ceil(log2 n)`, common scale`e`, and write`x_i=X_i*2^e`. Then`|X_i|<2^(24+R)`. With`S=ΣX_i`, `Q=ΣX_i²`, `T=nQ−S²`, obtain universally

`|S|<2^(24+R+L)`, `Q<2^(48+2R+L)`, `0≤T<2^(48+2R+2L)`.

Proof: triangle inequality boundsS; each square is strictly below2^(48+2R), and`n≤2^L`. Cauchy givesT≥0, whileT≤nQ and the same count bound gives its strict upper bound. Every partial signed sum has the same magnitude bound; every partial square sum is nonnegative and bounded byQ.

Consequently a checked `48+2R+2L≤192` layer-norm guard permits all square accumulation, `nQ`, `S²` and finalT to be computed exactly in192 bits. It also implies`|S|<2^96`, so signed128 bits suffice forS and its192-bit square can be formed once per row. The RMS-only guard can be weaker,`48+2R+L≤192`; for`n≤2^20`, signed128 bits still suffice forS if it is collected.128-bit square/T variants use the analogous bound. Outside the guard, preserve former2's unbounded exact path. All-zero rows haveS=Q=T=0 and need no spread assumption.

For layer norm, the192-bit guard allowsR≤68/66/64/62 at n16/64/256/1024 respectively. The128-bit guard allowsR≤36/34/32/30. Those are mathematical guard domains, not observed model time fractions. Uniformly huge values are easy:256 copies of max finite haveR=0; a row containing min subnormal and max finite hasR=253 and must fall back.

Source comparison: former2`Y2` scans for minimum exponent; `Y7` separately collects signed sum into positive/negative18-limb Nat arrays; `Y6` separately collects squares into another18-limb array. `Y8` then converts those arrays with`limbValA`, formsS/T and calls the denominator path. A fixed-word path would keep2 S words plus2/3 Q words as plain recursive arguments, fuse sum/squares after one min/max scan, and eliminate those array initializations, per-input array modifications, one read/decode pass and array-to-big-integer folds. Convert final word state only once per row when an unchanged downstream helper needs it. New range-summary work, carries, cross-word shifts, state spills and failure cost remain charged. Actual compiler behavior and complete norm gain are UNKNOWN.

The finite model in`moment-width-results.json` checks exact widths and both guard levels on normal/wide/sparse own-generated rows, plus extreme span/constant/near-constant cases. This is not a new-target profile or a production coverage estimate.

One adverse case changes the guesser design:255 copies of1 plus one`1+2^-23` have exact variance`255*2^-62`, but a naive binary64`E[x²]−E[x]²` computes0. With minimum-subnormal epsilon this gives the wrong sqrt guess, rejected by the exact squared-cell certificate. Since exactT is already available, form the native root guess from the positive exact numerator/denominator representation, rather than subtracting nearly equal double moments. That guess passes the same certificate in the model; no accuracy theorem is assumed.

Next discriminator if target implementation is authorized: one full stable norm callback using fixed frozen guards and unchanged control, first inspect actual word-state/loop C/ASM on AMD/ARM, then measure full row summary/moments/root/output/release costs. Compare moment acceleration separately from final-output certificates so a newly added exact numerator does not hide its cost. If final rounding dominates, prioritize the B2 residual certificate instead. Never infer whole-model gain from this word count.

## Fixed-width certificate comparisons need no huge shifts

For nonnegative128-bit coefficientsA/B and arbitrary integer exponentsa/b, compare`A*2^a` with`B*2^b` as follows. Handle zero, then compare their leading exponents`bitLength(A)+a` and`bitLength(B)+b`. Unequal leading exponents decide the order immediately. If equal, align the coefficient with the larger exponent to the other exponent. The shifted coefficient then has exactly the other coefficient's bit length, hence still fits128 bits. The shift is at most127. This is an exact mathematical comparator; there is no unchecked wrap of a large shift. `scaled-compare-results.json` checks20000 random/directed exponent/width combinations against unbounded integers and catches a large-shift truncation mutant.

For a normal candidate`w=M*2^e`, the rational-cell checker compares an exact numerator`|P|*2^k` against`D*(2M±1)*2^(e−1)` (binade lower boundary has`4M−1` and exponent`e−2`). IfP fits128 bits andD fits44 bits, the midpoint coefficient fits69 bits, so the entire checker can use that128-bit scaled comparator; arbitrary exponent differences do not force BigInt construction.

An RMS-specific useful consequence: under the192-bit moment guard, R≤72, hence its exact final numerator satisfies`|X_i*G_i|<2^(48+R)≤2^120`. Its denominator is the24-bit rounded-root mantissa. Therefore the full finite-normal RMS output certificate fits128-bit coefficients for *every* row satisfying that guard, not just the sampled rows. Exponents still require the ordinary bounded raw-word arithmetic proof; zero/subnormal/overflow output guesses retain their exact fallback.

Layer norm needs an additional numerator guard. With`d1=e+e_g−c`, `d2=e_b+e_d−c`, `L=ceil(log2n)`, the two terms satisfy widths below`49+R+L+d1` and`48+L+d2`. A sufficient sum bound is`1+max(those widths)≤128`. Ignore an identically zero bias term when choosingc; otherwise a zero term can force a needless huge alignment. A failed bound preserves the exact fallback. These guarded coefficient bounds, not a blanket assertion that every stable output fits128 bits, are the next implementation premise.

## A provable public-source coverage statement: Mixer's first norm

Source scope is exactly current commit`accb82b6…`, `ExactSuite.profileModel`, `gen`, `scales`, `biases` and `mixerLayers`. This is a paper source-domain argument, not a Lean workload proof or a private-suite claim.

Mixer invokes layer norm twice, each withT rows ofC positions. The first receives the generated input directly; the second receives the residual after token mixing. Thus the first accounts for exactly half of that model's layer-norm row invocations and output positions at either batch size. This is a **call/element count**, never a timing or board-weight fraction.

For every seed and all typical/scale/boundary profiles, the first norm has`C≤48`, hence`L≤6`. Every nonzero generated input has an exponent field in`[87,126]` (normal/sparse actually`[121,126]`), so`R≤39`. Therefore

`48+2R+2L ≤ 48+78+12 = 138 < 192`.

The192-bit moment guard is guaranteed for *all* such first-norm rows, not merely the finite samples.128 bits is not guaranteed for wide inputs. The finite same-seed Mixer model found128-bit guards accepting only12/45 wide rows while192 accepted45/45; all normal/sparse rows fit128. All3675 first-norm output guesses certified in that finite simulation. These observed counts are not success probabilities.

One can also bound the first norm's final affine-certificate numerator universally. Generated gains have exponent`e_g=−23`; nonzero biases after division by256 have`e_b∈[−37,−32]`. Initial`|x|<1` and fixed epsilon lies in`[2^-17,2^-16)`, so the rounded denominator is between2^-9 and2; its decoded exponent satisfies`e_d∈[−32,−22]`. A nonzero row's base exponent`e∈[−63,−24]` obeys`e+R≤−24`.

For`c=min(e−23,e_b+e_d)`, let`d1=e−23−c`, `d2=e_b+e_d−c`. If`d1>0`, then`R+d1 ≤22`; otherwise`R+d1=R≤39`. Also`d2≤32`. The two numerator-term widths are thus bounded by

`49+R+L+d1≤94`, `48+L+d2≤86`.

Their sum has magnitude below2^95, so the128-bit final cell/residual checker always has enough coefficient capacity on these first-norm public-source rows. All-zero rows have exact centered values0 and return the finite bias directly (canonicalizing a zero bias); handle that identity separately instead of choosing an artificial exponent for zero. This capacity claim does **not** promise that an arbitrary native guess passes its certificate; a failed check still returns the exact output.

The later norm's input range is not covered by this generator argument. It retains the general observed-data guard and exact fallback. Actual first/second norm time shares, native state spills and whole-model benefit remainUNKNOWN.

## Exact source distinction and removal ledger

`former2-norm-callgraph.json` is generated by`audit_former_norm.py` against exact former2 SHA`cea4422f…`; it records selected definition line ranges, body hashes and dependency names without copying source bodies. The final norm field at3736 selects`Ybb/Ybc`, not the bounded dense/conv word accumulators:

| Selected path | Actual source work | Proposed change status |
|---|---|---|
| RMS `Ybb2802→YaE2399→Y2/Y6` | Min-exponent scan; `Y6` square fold into18-slot Array Nat, followed by`limbValA` | Scalar fixed-word moments are PAPER_ONLY, NOT_IMPLEMENTED. |
| Layer `Ybc2807→Y82405→Y2/Y7/Y6` | Separate sum and square folds; `Y7` has two18-slot Nat arrays, `Y6` one; three`limbValA` occurrences, then signed`nQ−S²` | Fused scalar S/Q and wordT would replace these exact operations. No such norm-moment path was found in final selected source. |
| Both `YaD2391→sqrtLower/sqW` | Natural logarithmic scaling,`Nat.sqrt(num/den)`, exact midpoint rounding | A moments-only port still pays this. Native guess plus exact word sqrt certificate is a separate required connection. |
| RMS final `Ya72658→YN` and layer `Yba2677→Ya9/Ya8/YN` | Already specialized final rounding;`Yba` contains3 `/D` and3 `%D` expressions | Do not claim no existing word optimization. A new cell checker targets these divisions/remainders separately. |
| Dense/conv `YaV/Ya3`, `Ybp/dwQ→cdQ` | Already use bounded word loops, including two-word`QY6G` and three-word`YE/YS` routes | These are prior art, not the proposed norm state. Public core`kernels0.core` still uses`Yn/Yw` limb accumulation. |

`addLimbs64` already splits each product using64-bit arithmetic before updating Nat slots. The new representation proposal replaces the *whole accumulator state*, not that existing split. For the small/medium rows, slot additions can remain immediate small Nats; no per-MAC GMP allocation is claimed. In the finite Mixer model,45/135 exactQ values exceed63bits, while100 exactT values do; this supports the presence of non-small natural intermediates *if the source path executes as written*. It is not an observed GMP call profile, and the exact multiprecision backend is not established here.

Merely replacing arrays and then convertingQ/S toNat for unchanged`YaD`/`Yba` would move or retain part of the big-number work. An end-to-end accepted word path needs moments, epsilon alignment, root certification and output certification. This has not been implemented or measured. Source attributes contain no local`csimp`/`implemented_by` redirection, but actual selected C/ASM is still required to establish compiled work.

For the first Mixer norm, the epsilon-aligned root numerator also fits the same capacity. Epsilon's exact dyadic exponent is−40; for a nonzero generated row,`e∈[−63,−24]`, hence`−40−2e∈[8,86]`. Write

`N=T+n²*M_eps*2^(-40−2e)`, `q=(N/n²)*2^(2e)`.

Here`T<2^138`, `n²<2^12`, `M_eps<2^24`, so`N<2^138+2^122<2^139`. The denominatorn² is small, and a squared-midpoint coefficient timesn² fits62 bits. A192-bit scaled comparison can therefore certify a native root guess without calling the old natural-number division/sqrt on accepted guesses. This is a concrete missing implementation boundary, not a claim that the current coverage theorem already removed anything.

## Imported compiler substitutions narrow the cost claim

Further primary-source verification at the exact pinned FloatLib`0d918257…` found global compiler substitutions in`FloatLib/Kernels.lean` and`FixedWord/IntegerSquareRoot/Proof.lean`. `Nat.sqrt` arguments below2^64 use a UInt64 Newton loop (`IntegerSquareRoot.sqrtNat`); `roundQuotientEven` with numerator<2^63 and nonzero denominator<2^64 uses a native-word dispatcher. These are imported substitutions even though former2 itself declares no local`csimp`. Newer repository-head floating-guess sqrt code was **not** assumed to exist at this pin; its`Compiler.lean` file is absent here.

Former2's`YaD` actually makes the square-root radicand small. For positive`num0,m`, put`p=floor(log2 num0)`, `q=floor(log2 m)`, and`t=floor((48−p+q)/2)`. Then`p−q+2t∈{47,48}`. Its exactly scaled ratio therefore lies strictly between2^46 and2^49, since `num0/m` lies between2^(p−q−1) and2^(p−q+1). The integer radicand`floor(scaledNum/scaledDen)` is in`[2^46,2^49)`, so its`Nat.sqrt` is always the native-word path, with a24/25-bit root. This is a universal paper bound for that positive domain, not a timing estimate.

Accordingly, B1 should **not** be sold as deleting an arbitrary-precision square root. It would replace a bounded word Newton root plus its scaling/quotient/midpoint work; whether that wins isUNKNOWN. Some aligned quotient operands and the exact numerator can still be large, and the word moment/cell path targets those separately. RMS final numerator is only a48-bit mantissa product, so its existing quotient rounder often already selects the native-word implementation; an added128-bit checker could lose. Keep B1-only work lower priority until actual profile/cost exists, and do not infer GMP time from the visible Nat type.
