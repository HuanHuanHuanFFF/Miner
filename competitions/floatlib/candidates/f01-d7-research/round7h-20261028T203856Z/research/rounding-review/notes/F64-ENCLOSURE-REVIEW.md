# C: deterministic binary64 fold enclosure and native-model bridge

New proof obligation assigned after the initial cell review. First observed clock UTC 2026-10-28 21:42:11; unchanged shared cutoff UTC 2026-10-29 03:38:56. Read-only source/mathematics plus a bounded exact model is authorized; no new-track kernel, Lean implementation/build, CI or Git/index changes. This note does not reopen the previously closed binary32 cell algebra.

## Main conclusion

For the stated IEEE binary64 nearest-even model, the proposed H-based radius **2^(H+2L-303) is safe** for n<=2^L with L<=30, and also under the existing source's larger L<=51 guard. The coordinator's representable jM induction is valid when M is the specified power of two. It removes the error-growth recursion and even leaves a factor-two margin in this radius. The source's non-power-of-two separable maximum requires its original recurrence proof instead; jM need not be representable there.

The pinned library contains a real native-binary64 addition bridge and generic real rounding/error lemmas. Multiplication has a conditional unpacked-model bridge, but its extra premises and the exact raw32-to-raw64 conversion still need an actual proof. Source availability is not a compiled proof or axiom audit, and opaque cross-width casts cannot fill that gap.

## Exact domain and product preparation

For each finite binary32 input, decode magnitude mantissa m<2^24 and index I32 in [0,253], giving signed value m*2^(I32-149). Thus each exact product is t_i=sign_i*p_i*2^(I_i-298), with p_i<2^48 and 0<=I_i<=H<=506. A nonzero product lies on the 2^-298 lattice, has at most 48 significant bits, and magnitude below 2^256. It is an exact **normal** binary64 value. Zero products are exact as real values; their signs are treated separately below.

Direct bit expansion can avoid opaque `Float32.toFloat`:

- For normal binary32 field e in [1,254], use binary64 field e+896 and fraction f<<29.
- For nonzero subnormal fraction f with leading bit l in [0,22], use field l+874 and fraction (f-2^l)<<(52-l).
- Zero takes its own branch, preserving the sign bit. Move sign bit31 to bit63.

All generated binary64 fields are normal and below 2047. Fraction shifts fit 52 bits. These formulas have an elementary exact decode proof; their implementation and that proof are not present in this review. A zero branch is essential before applying the subnormal leading-bit formula. `Float.ofBits` has a logical definition and canonicalizes NaNs, but no NaN bit patterns occur on this finite conversion path.

## Prefix bound without a gamma_n factor

Let M=2^(H-250), u=2^-53, s_0=0 and r_j=s_(j-1)+t_j, s_j=RNE64(r_j). Every |t_j|<M.

For every integer j<=n<=2^51, jM is exactly binary64-representable: j needs at most 52 significant integer bits, and multiplication by a power of two does not add significant bits. Its exponent is at most H+L-250<=307 and at least -250 for j>0. Thus it is finite and normal; zero is also exact.

Inductively assume |s_(j-1)|<=(j-1)M. Then

    |r_j| <= |s_(j-1)|+|t_j| < jM.

Monotonicity and exact rounding of +/-jM give |s_j|<=jM. The conclusion for the rounded prefix is non-strict; rounding can reach a representable bound. The strict inequality belongs to the **unrounded addition input r_j**. This distinction controls the half-ULP exponent at a power-of-two boundary.

The finite-output premise in the native addition bridge can be established at each step before applying real semantics: |s_(j-1)|+|t_j|<jM<=2^307, far below binary64 max finite. This avoids circularly assuming the output finite in order to prove it finite.

## Lattice and local error

Each r_j and s_j is an integer multiple of 2^-298. For r_j this follows by addition. For s_j, either r_j is already representable at that stored exponent, or binary64 rounding uses a coarser power-of-two grid. `round_toReal_exists_same_exponent` is an inspected library lemma for precisely this preservation statement. Hence a nonzero r_j or s_j has magnitude at least 2^-298, well above binary64 min-normal 2^-1022. Cancellation produces exact zero; it cannot create a binary64 subnormal.

Set K=H+L-250, so |r_j|<2^K. At nonzero r_j, its binade exponent is at most K-1. Binary64 precision is 53, so its ULP is at most 2^(K-53), and nearest-even error is at most half of that:

    |s_j-r_j| <= 2^(K-54) = 2^(H+L-304).

At r_j=0 the error is exactly zero. This bound can also be obtained from the generic half-ULP theorem without the normality shortcut, because the subnormal grid is far finer than this upper bound. The lattice argument remains useful for the source's relative-error formulation.

Telescoping the signed local errors gives

    |s_n - sum(t_i)| <= n*2^(H+L-304) <= 2^(H+2L-304).

The first addition is exact because t_1 itself is binary64-representable, so n>0 gives the stronger strict enclosure

    |s_n - sum(t_i)| <= (n-1)*2^(H+L-304) < 2^(H+2L-304).

The proposed 2^(H+2L-303) is therefore a valid conservative radius, including n exactly a power of two. This does not establish that the sharper radius is already implemented or formally proved. If using only the coarser relative inequality |round(r)-r|<=u|r|, summing also establishes the proposed radius; no precision-dependent gamma denominator is necessary under the power-of-two prefix bound.

The existing source uses E>=floor(log2|t_i|), M=2^(E+1), and radius 2^(E+2L-52). From the coarse product bound E<=H-251, this is no larger than 2^(H+2L-303). E need not equal H-251; small significands can make the E-based radius substantially tighter. Do not equate the two metadata policies when comparing coverage or costs.

## Non-power-of-two summary maximum is a different proof case

The development model also tries M_sep=max|a|*max|b|, enlarged for bias. That M_sep need not be a power of two. It is incorrect to reuse the statement “j*M_sep is exact” merely because each product is exact. For example, repeat 33 copies of the product of words `0x3fffffff` and `0x3ffffffd`. Each product M_sep has 48 significant bits, but 33*M_sep has 54 with an odd coefficient. The exact binary64 fold at the 33rd step rounds **above** 33*M_sep by 2^-46. Thus even the bound |s_j|<=j*M_sep is false in this example.

This does not refute the source's n^2*u*M_sep error radius. Its stated recurrence is valid in the finite, normal-or-zero domain:

    e_j <= (1+u)e_(j-1) + j*u*M_sep.

Induction e_(j-1)<=(j-1)^2*u*M_sep works because u*(j-1)<=1. The domain is established simultaneously: |s_j|<=j*M_sep+e_j<=j*M_sep*(1+j*u), and j<=2^51, M_sep<2^256 keep it below 2^308. The lattice keeps nonzero pre-round values normal. The sum of the domain induction and recurrence is required; simply borrowing the power-of-two monotone proof loses a necessary hypothesis.

## Zero, bias, order and endpoint arithmetic

- The real error theorem forgets zero signs. Starting a binary64 fold at +0 and adding a sole -0 product yields +0, whereas the exact-dot source can return -0 for an all-negative-zero input. This is not an error-bound failure; a final zero result must follow the original source convention or use the existing fallback. The proposed strict normal binary32 cell acceptance excludes this case.
- A bias is one more exact term. Include it in n and H, or use an explicitly equivalent proof where it is the exact first seed and count that seed as a term. Adding bias only after certification or preserving the old n/H without accounting for it is not the stated theorem.
- Separate exact products followed by one RNE64 addition per term is the stated evaluation order. Source changes such as regrouping need a corresponding fold proof; the bound cannot be attached by label alone. Actual input preparation and selected compiled operation remain unverified.
- If s+/-B is later computed with binary64 arithmetic, those rounded endpoints need not be outward bounds. For example s=1-3*2^-53 and B=2^-50 gives RNE64(s+B)<s+B. However a **strict** comparison against an exactly representable binary32 midpoint remains sound by monotonicity: RNE64(s+B)<U implies s+B<U when RNE64(U)=U, and similarly on the lower side. Equality/tie acceptance cannot be justified by the same implication. The current source's exact dyadic comparisons are already sufficient; no implementation change is requested here.

## Inspected primary interfaces and exact remaining work

Pinned FloatLib is `0d91825727839f597fd06b22fdd038ea21480f0c`; Lean is v4.34.0. Source files are inspected at these refs or reused from this round's verified source receipts. No claim below is a new local compilation.

1. `Float.add` and `Float.mul` in Lean `src/Init/Data/Float/Float.lean:76,91` are logical definitions through `Float.Model`, despite their native extern compilation attributes. `Float.ofBits`/`Float.toBits` at 134/147 are defined too. `Float32.toFloat` and `Float.toFloat32` in `Float32.lean:548,555`, plus `Float.scaleB`, remain opaque; no value theorem may be inferred for them.
2. Lean `Float.Model.add`/`mul` at `src/Init/Data/Float/Model/Float.lean:71,83` pack the corresponding `UnpackedFloat` operation. Fixed blob `993df090b5259e8ec772dc981616b42c0b1a0576`.
3. `FloatLib.Floats.ExecFloat.Binary.toModel_ofFloat_add_of_isFinite` in `IEEE754/Native/AddSub.lean:184` maps native Float addition to `Model.add`, requiring both native operands finite. Fixed blob `54e10180ea58eec26c01c516b45c7810038c210c`. This is an actual bridge theorem, not merely a comment that Float models exist.
4. `Model.toReal_add_eq_roundAt_of_abs_add_le_posMaxFinite` in `Arithmetic/Semantics.lean:94` gives the next bridge to nearest-even real rounding, with IEEE, finite input and a symbolic magnitude bound. The same file's finite-sum lemma at 37/56 can establish result finiteness first. Fixed blob `69183b7446f43590916b6194117e16bca276c098`.
5. `Model.toReal_ofModel_mul_finite_eq_roundAt` in `Arithmetic/LeanModel.lean:297` is available for the unpacked product, but requires positive unpacked mantissas, exponentSum<=targetExponent, and result finiteness. Fixed blob `878a35b6f2b3774f31319d9e56a53786f866d44c`. The scoped Native module inventory has no symmetric top-level `ofFloat_mul` theorem; do not say the final native multiply bridge is already closed. The widened inputs have normal 53-bit decoded significands with at least 29 trailing zero bits each, so their product has enough trailing zeros for the 52/53-bit normalization shift to be exact. Zero cases and the finite bound must be proved separately before composing this lemma.
6. `Flocq.round_toReal_exists_same_exponent` in `Theory/Error/Exactness.lean:34` supplies lattice preservation. Fixed blob `928428619831d413d58168d9622ada710aafeb9e`.
7. `Flocq.round_preserves_generic` at `Theory/Rounding/Core.lean:349` and `Flocq.error_bound_ulp` at 404 supply exactness and half-ULP error. Fixed blob `9a7f713030eeb7031d5c1d2a61e82d181e9f4eed`. `Theory/Error/Relative.lean` also supplies `relative_error_round_FLT_normal` for the recurrence route.

A nearby widening interface must not be confused with the required conversion. `Conversion/Cast/Widening.lean` (fixed blob `b904aada62fa665ace331b44970dc817433e451c`) proves storage widening only when source and destination exponent widths agree. Binary32 has width8 and binary64 width11, so that theorem does not establish this conversion. `Conversion/Cast/Proof.lean:468`, blob `1808bedc19cd71dbbaf7db0633e7c555e568ddf5`, has `cast_exact_of_gridExtension` under source/destination IEEE, fraction-width/range inclusion, finite input and finite **Model.cast** result. It is a useful reference semantic path, but it neither identifies opaque `Float32.toFloat` with `Model.cast` nor proves the proposed direct bit expansion. Those transport obligations remain explicit.

Still uncompiled: the full raw32-to-Float expansion theorem; native product exactness including zero; generic representation of jM; native-finite preservation across the actual fold; conversion of the final Float to the exact dyadic used by the checker; the sum-error theorem in pinned Lean; and complete helper/candidate axiom audit. Existing proofs inspected here use ordinary theorem definitions, but no `#print axioms` or kernel replay was run. The allowed project axioms remain propext, Classical.choice and Quot.sound; no new axiom for native casts or hardware arithmetic is authorized.

The fixed TorchLean `docs/PROOFS.md:13,19` was also read: it permits only those three axioms and rejects extra axioms, native-decision proof shortcuts and external/unsafe source constructs. That is a source-policy check, not a gate pass for a prospective Float64 candidate. The inspected files contain no new explicit `axiom`, `sorry`, `unsafe` or `implemented_by` declarations; that scoped text check does not replace a transitive theorem axiom audit.

### Availability from the sole permitted import

The source import path is present: `ContractExact -> ExactToolkit.Values -> Decode -> Congr -> Round -> FloatLib -> Floats -> Formats`. `Formats` publicly imports `IEEE754`, which publicly imports `Native.AddSub`; it also imports `BinaryInterchange`, whose `Semantics` barrel publicly imports `Arithmetic.Semantics` and `Arithmetic.LeanModel`. The parallel `Formats -> Flocq -> Theory` path publicly imports `Rounding.Core`, `Error.Exactness` and `Error.Relative`. Thus the named source interfaces are reachable through the allowed `ContractExact` import without adding a forbidden second import. Nine pinned import-node sources and their verified Git blob identities are retained in `f64-import-closure.json`. This closes the source-import discovery question, not elaboration/compilation of a theorem using them.

### Bounded exact checker and fixed falsifiers

`f64_exact_check.py`, SHA-256 `32a89f918ed9a839a897ce45e9606270ebaa9ff7a24dc86d9e1f1f5fe7f2498e`, evaluated binary64 nearest-even by exact integer quotient/remainder, with no host floating arithmetic. `f64-exact-check-result.json` records PASS for 24 finite raw-expansion boundary words, their 576 product pairs, 38 deterministic folds of length at most 64, and 24 exact jM checks at selected count boundaries through 2^51. These finite checks supplement, and do not prove, the all-input/count paper theorem.

The same receipt records the non-power-of-two prefix counterexample above and a concrete bias omission: bias=1 (`0x3f800000`), one product `0x32000000 * 0x32000000`=2^-54. A fold seeded with the bias has error 2^-54, exceeding the invalid product-only H=198,n=1 radius 2^-105. Counting the bias as a term restores H=252,n=2 and the proved bound. The endpoint inward-rounding example is also checked. No random batch, hardware timing or production acceptance estimate is attached.

## Comparison boundary

With the same H,L and overlapping guards, A's integer truncation radius is bounded by 2^(H+2L-312), versus the proposed F64 radius 2^(H+2L-303): **nine bits, a factor 512**, purely as a worst-case mathematical comparison. The sharper paper F64 bound above reduces that to eight bits, without changing any implementation. Neither ratio gives acceptance probability, runtime, full-model speedup or champion comparison. The native route has a different unresolved semantic bridge and preparation cost; A has machine-integer truncation/overflow proof work.
