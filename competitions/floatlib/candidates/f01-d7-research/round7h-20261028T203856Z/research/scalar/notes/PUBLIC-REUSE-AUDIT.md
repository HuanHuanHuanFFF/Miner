# Fixed public arithmetic reuse audit — cost premise revised at21:45 UTC

Read-only at FloatLib0d91825727839f597fd06b22fdd038ea21480f0c, the exact dependency in the new contract. A checked the legal single-import transitive chain through `ContractExact → Values → Decode → Congr → Round → FloatLib → Kernels → FixedWord`. This is source visibility, not a new compile or axiom report.

## Existing mechanisms and actual preconditions

| Interface | Verified source contract | Reuse decision |
|---|---|---|
| `FixedWord.roundQuotientEven` | UInt64 quotient/modulo, remainder versus denominator−remainder, tie parity; no remainder doubling overflow | Useful existing executable comparator. It still performs division, so it does not consume an externally proposed q. |
| `FixedWord.roundQuotientEven_toNat` | den≠0 and num/den+1<2^64 imply equality to Nat RNE | Public64-bit bridge; candidate's quotient witness still needs its own refinement. |
| `FixedWord.roundQuotientEvenNat` | num<2^63,0<den<2^64 select the UInt64 implementation; otherwise original Nat definition | **Already registered by a fixed `@[csimp]` theorem.** The compiler can choose this existing native path for bounded Nat RNE. |
| `RestoringQuotient.roundQuotientState` | Single-word state rounder; comments require denominator/remainder/quotient bounds | Runtime is reusable; the fixed file's public theorem bundles rounding with the restoring computation, not an arbitrary proposal state. |
| `CertifiedDivision.certificate` / `certificate_sound` | UInt128 quotient/remainder checked by a256-bit Euclidean product/equation and remainder bound; theorem requires64<precision≤126 and a shift ofprecision orprecision+1 | Sound independent-proposal architecture already exists, but its domain/layout does not directly fit the24-bit RMS quotient. Do not silently setprecision=23. |
| `CertifiedDivision.checkedCandidate` | Fixed Algorithm-D proposal followed by certificate and restoring fallback | Not a configurable native proposal wrapper. Replacing its producer changes the function and requires a new bridge. |
| `CertifiedDivision.roundQuotient_toNat` | den<2^127, qD+r=N, r<D, q+1<2^128; equality to Nat RNE | General public rounding bridge. It can inform or prove a zero-high-word adapter, but making the RMS runtime256-bit merely to reuse the certificate may erase its purpose. |

## Corrected RMS baseline cost premise

RMS's normalized A<2^49,B<2^25 meets the existing Nat-dispatch condition. Consequently **Nat syntax alone is not evidence that RMS pays arbitrary-precision division**. The precise #2 native caller, csimp application/inlining, combined div/mod instruction and cycle cost remain UNKNOWN without actual generated code. The checked native proposal would compete with an available machine-word divider plus its dispatcher/normalization, not necessarily a slow big-integer operation. Earlier paper remarks about removing big-integer RMS division were an unverified premise and are superseded by this source evidence.

LayerNorm's explicit c/D,r0/D,ra/D and related remainders are a different path; their widths and native lowering must be inspected separately. Do not infer that all of them are big-integer calls either. `LAYERNORM-HIGH-WORD-CERTIFICATE.md` still eliminates division inside the new checker, but must charge constructing its exact numerator and proposal. `INTERVAL-NORMALIZATION.md` is the broader prospective work removal, because it may avoid full statistics reconstruction as well as output division.

The first RMS quotient probe remains valuable as the smallest exact arithmetic/proof discriminator, with no promised speedup. It should not be promoted as the main≥10% opportunity without complete model cost evidence.

## Integer sqrt dispatch and a later public checked implementation

At21:51 a second fixed compiler substitution was confirmed: `IntegerSquareRoot/Proof.lean:136` maps `Nat.sqrt` to `sqrtNat`. The fixed `Runtime.lean` selects UInt64 Newton iteration when its integer argument fits64 bits. Former #2 normalizes its square-root input so the quotient passed to Nat.sqrt is roughly46–49 bits; therefore its sqrt stage may already use native-word Newton division. The preceding **num/den division may still have wider operands**. Quotient width, numerator/denominator width and root width must not be conflated; actual selected code is still uninspected.

The quotient-width premise can be made precise on paper. For positive original N0,D, let a=floor(log2 N0), b=floor(log2 D), t=floor((48−a+b)/2), and scale the rational by2^(2t), shifting either numerator or denominator exactly. Then a−b+2t is47 or48. Since2^a≤N0<2^(a+1) and2^b≤D<2^(b+1), the scaled rational lies strictly between2^46 and2^49. Its integer quotient Q satisfies2^46≤Q<2^49; its floor root lies in[2^23,2^25). Thus the integer sqrt argument is bounded even if the scaled dividend/divisor themselves are large. The old `root≥2^23` fallback condition is unreachable under these positive-input premises, but any caller/closure-cost consequence still needs actual code inspection. This is a paper bound, not a compiled theorem or instruction-count inference.

A later public FloatLib revision8c8871576a941a86e73dcf0882702b823139aa93 has a relevant MIT algorithm absent from the fixed dependency: `IntegerSquareRoot.sqrtChecked` obtains `(Float.sqrt value.toFloat).toUInt64`, validates the candidate and each±1 neighbour by exact squares, then falls back to the old Newton sqrt. Its `isFloorRoot` repeats the<2^32 guard on every proposal and handles the2^32−1 root separately to avoid squaring2^32 in UInt64. `isFloorRoot_spec` and `sqrtChecked_toNat` do not assume any floating-point accuracy.

This is **an existing public algorithm, not a new research discovery**. If the target is authorized, a possible source-level adaptation is only the two safe definitions and their two proofs in a candidate-local namespace, with explicit norm calls and the old public sqrt/sqrt_toNat as fallback. Do not import the newer library, install its compiler substitution or change the toolchain. The old pinned Mathlib5ed296 `Data/Nat/Sqrt.lean:52` contains `Nat.eq_sqrt` with the exact square-bracket characterization used by the later proof, so that key API is available. Actual typing, remaining dependencies, permitted attributes and full proof/cost remain NOT_RUN. This small adaptation would replace word Newton after num/den; it would not remove that division, and sqrt only occurs once per row.

Source identities: fixed sqrt Runtime `c8967baf65b9906cb81b94c34fba80eab905709d`, Proof `37bce9010ee619d991d30fcebdbb51bc9c8d451e`; later Runtime `8bd808e5dde14b6670426459fc4e64667220009d`, Proof `4f9695c6232535deab63dcd78b5ef9e5d8427bbd`; fixed Mathlib sqrt file `6e0e55b225761cc0112e2b1c8d1d394ef867bfec`. All were fetched at their stated refs. The newer `CheckedSqrt` directory and `quotientRemainder ... guess` search hits are not assumed present at0d918.

## Smallest direct reuse strategy

Do not rebuild the RNE parity proof. A new fast branch can use its certified q and r=A−qB, then execute the same remainder-versus-(B−remainder) and quotient-parity expression as the existing UInt64 `roundQuotientEven`. Prove only q=A/B and r=A%B as words: the width guard lifts products/inequalities to Nat, `Nat.div_mod_unique` pins the decomposition, and UInt64.toNat injectivity returns the word equalities. Substitution then makes the new fast expression equal to the existing public word rounder. `roundQuotientEven_toNat` supplies its already-proved RNE semantics. This leaves a small quotient-witness refinement instead of a new rounding theorem and avoids adding UInt128/256 arithmetic to the runtime merely for proof reuse.

The formula's exact identity matters: using a different unchecked doubling or an unsigned correction can reintroduce overflow. Current normalized bounds would also permit doubled remainder, but matching the public formula is the simpler proof interface. The exact compiled candidate still requires all original checks after implementation is authorized.

## Source identity and drift boundary

- `Core/Runtime.lean`, blob `71d1bf2462da2cf1d6eff8b8fc3580fb681400b4`, lines95/120: native RNE and bounded dispatcher.
- `Core/Proof/Rounding.lean`, blob `d40ac633b17170af3e868f88539d6f1f8cd2bfc5`, lines174/247: public UInt64 proof and compiler substitution.
- `CertifiedDivision/Runtime.lean`, blob `218abe60e4d109fd051c7e2206d774a8771623bf`, lines246/301/318; `Proof.lean`, blob `b27c722e18e761cdfb8826e23f1a947f7d5820f3`, lines120/366/408.
- `Quotient/Runtime.lean`, blob `0a9530b99b15e5099403a7168fbd072c3fe8053c`; `Quotient/Proof.lean`, blob `b5bd0b5280fa85322f424525dd582bd6ab4f8660`.

GitHub default-branch search returned a newer `quotientRemainder ... guess` proof excerpt at8c887157. Fetching the fixed0d918 file showed it absent. The newer API is not available merely because search found it; no library/toolchain change is proposed. The inspected fixed files carry FloatLib Team/MIT headers. Candidate code remains absent while target authorization is pending.
