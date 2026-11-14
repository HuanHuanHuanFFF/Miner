# Small proof path for the normal RMS quotient wrapper

This is a source-grounded dependency plan, not Lean source or a claimed build. TorchLean target authorization is still pending. Exact output/data boundaries and the full raw fallback remain required.

1. **Decode:** `ExactToolkit.Values.decodeD_toRat` decomposes each raw finite word into signed mantissa and binary exponent. Normal x/g and the independently proved denominator normality give24-bit a,b,D and P=a*b in[2^46,2^48). Formula E=ex+eg−ed−150 follows for normal fields.
2. **Leading interval:** the two comparisons against D*2^23 and D*2^24 determine h∈{22,23,24} with D*2^h≤P<D*2^(h+1). Public `Model.floorLog2_eq_of_bounds` closes the exact floor-logarithm identity after casting these inequalities. This avoids reimplementing the logarithm algorithm.
3. **Normalized quotient:** explicit h cases give A/B=P/D*2^(23−h), with A<2^49,B<2^25 and2^23≤A/B<2^24. Arbitrary proposed q, after its width guard, is accepted only by qB≤A<(q+1)B. The ordinary Nat division characterization yields q=A/B and r=A−qB=A%B. Any correction rechecks its width before products.
4. **RNE and packing:** unfold `roundQuotientEven` using q,r and derive m=q+roundUp∈[2^23,2^24]. The Ebase guard1..253 forces the original normal branch. Both carry/noncarry cases pack the correct word; the public `NativeBinary32.ofUInt32_roundRatScaled` transports this word computation to Model rounding.
5. **Canonical-rational bridge, restricted to this guard:** do not copy former #2's private general cV/J6 proof. Here actual total exponent h+E is in[-126,126], so the exact magnitude lies in[2^-126,2^127). This is strictly below maximum finite. Thus `isFinite_roundRatScaled_of_abs_le_posMaxFinite` proves finiteness for the canonical-rational rounder without assuming the desired result. The word just proved is itself finite/nonzero by its packed normal fields. Apply `toReal_roundRatScaled_eq_roundAt` to the two mathematically equal rational representations, then `eq_of_toReal_eq_of_nonzero` to recover the complete word. This restricted real-semantics bridge is an alternative to rebuilding a full all-range rational-congruence theorem.
6. **Wrapper:** field/shape/normalization guards select the proved normal output; all other cases call the original exact function. Reuse the existing stable-domain split; raw malformed/nonfinite/zero-dimension cases are not removed by checked-input observations. The final `Submission.correct` must include every kernel and receive the exact-source original gate.

The21:45 public reuse audit further reduces step4: use the exact expression from public UInt64 `roundQuotientEven` with certified q/r, establish q=A/B,r=A%B, and rewrite to that existing word rounder. Its public `roundQuotientEven_toNat` handles ties/parity/overflow bounds. No new parity-rounding theorem or256-bit certificate is needed. This is a proof plan, not an implementation or accepted compile.

## Fixed source pointers

TorchLean upstream accb82b6 uses Lean4.34.0 and FloatLib0d91825727839f597fd06b22fdd038ea21480f0c. Searches of default-branch names were only discovery; declarations below were separately fetched at that fixed FloatLib revision.

| Public interface | Fixed file / location | Git blob |
|---|---|---|
| `floorLog2_eq_of_bounds` | `.../DirectedSemantics/Rational/Logarithm.lean:311`; assumes nonzero numerator/denominator and real binary interval | `88c6df468dcb07bcc68e78c998e74a6a9eb7fe01` |
| `isFinite_roundRatScaled_of_abs_le_posMaxFinite` | `.../RoundingSemantics/RoundedReal.lean:387`; denominator nonzero, IEEE and exact absolute bound | `509c43116b5a779dcc0e0007f4df7226355a2bd8` |
| `toReal_roundRatScaled_eq_roundAt` | `.../RoundingSemantics/Executable.lean:142`; explicitly requires finite output and nonzero numerator/denominator | `8d6d6508e32d490d2f06ec6605feca66c473ea62` |
| `ofUInt32_roundRatScaled` | `.../Word/Narrow/Agreement.lean:231`; all signs/numerators/denominators/exponents | `f319e0d19a7aa8f421a169c0c4f8bf6d2497722a` |

Agreement/Executable are saved with byte-exact Git-blob and SHA-256 receipts under `sources/`. The other fixed declarations have been inspected through GitHub; no compilation, transitive current proof audit or native performance has been run. Their MIT source headers identify FloatLib Team; this does not grant a reuse license to the separate former-champion file.

For the denominator itself, use full `sqrtRational_eq_math`. A theorem such as `sqrtModel_correct` with a finite-result assumption cannot be used to establish that same finiteness premise. Pro-B's original artifact and C's exact fixed witnesses document this distinction and the runtime guard failures separately.

## Smaller actual binary32 transport target after the generic probe

The authorized `scalar-quotient1` probe deliberately stops at integer RNE. A subsequent **portable mathematical interface**, not a new RMS kernel, can avoid the full arbitrary-binade problem by accepting an already-normalized exact ratio N/D:

- the new check is true for UInt64 N,D,q;
- `2^23*D.toNat ≤ N.toNat < 2^24*D.toNat`;
- encoded exponent e is in1..253, with scale `(e.toNat:Int)−150`;
- m is the checked word RNE result.

Then N,D are nonzero, floorLog2(N/D)=23, and m lies in[2^23,2^24]. The intended direct word is sign-bit OR `((e−1)<<23)+m.toUInt32`. If m=2^24 it is exactly field e+1/fraction0; otherwise it is field e/fraction m−2^23. Every operation fits32 bits and the magnitude stays below2^31. The exact target is `Model.NativeBinary32.roundRatScaled sign N.toNat D.toNat ((e.toNat:Int)−150)`, then its public word/model agreement theorem.

This specialization makes the original rational rounder's leading exponent a constant23 and its scaleByPowerOfTwo shift0. The normal/overflow guards reduce from e∈1..253, leaving only carry/noncarry packing. It still needs actual available floor-log/packing declarations and word-to-Nat refinements under **old ContractTensor**, rather than merely assuming the new contract's import graph. It does not establish a canonical rational-expression/RMS transport; that remains a separate guarded algebra step. No extra Kernel or Lean source for this extension is being created before the current two-root result.
