# Direct rounded-word certificate — old ContractTensor mathematical probe

The new runtime checks an arbitrary rounded mantissa directly. For an unsigned128-bit numerator N and unsigned64-bit D,M, form the exact128-bit product P=M·D and the ordered128-bit absolute gap G=|N−P|. Accept only D>0, M>0, G.hi=0, G.lo<D, and G.lo<D−G.lo. The last subtraction cannot wrap after the preceding guard. These checks imply 2G<D, hence D(2M−1)<2N<D(2M+1), hence the **actual** `FloatLib.Numerics.roundQuotientEven N D=M`.

`WordGap128.lean.inc` supplies a proposed full chain from the executable word checks to those inequalities and then actual RNE. `normalCheck` adds the strict interior binary32 mantissa/exponent bounds and concludes actual `NativeBinary32.roundRatScaled` equals `mkBits`. The endpoint uses `CellPrimitive-v2.lean.inc` exactly. It takes no floating-point accuracy hypothesis or abstract cell-containment premise. Ties, zero, subnormal/overflow outputs and mantissa=2^23 are rejected; scalar owns the latter boundary bridge.

The candidate leaves the retained B2 runtime and four public callbacks byte identical. It is a mathematical diagnostic, **not** a new exact-contract Kernel or an integrated runtime optimization. Candidate/proof/source bindings are in `word-gap128-preflight.json`; actual Lean typing, replay and dependency checks are NOT_RUN until the parent's CI.

## What changes relative to existing work

- R's64-bit floor-quotient checker first proves q=N/D under N<2^49,D,q<2^25, then executes word RNE. This checker instead consumes an already-rounded arbitrary M, permits the full128-bit N and full64-bit D, and needs no quotient, remainder or final rounding expression on the accepted path. It rejects ties. These domains and costs differ; neither dominates.
- The pinned public `CertifiedDivision.certificate` already validates external128-bit quotient/remainder proposals with a256-bit Euclidean equation and64<precision≤126. This is not a new proposal/certificate architecture. The new small adapter specifically avoids manufacturing a quotient/remainder pair and the256-bit certificate for a narrow rounded result.
- Public `mul64`, ordered `UInt128.sub` and `UInt128.less` are reused through their exact theorems. `mul64` uses **four**64-bit partial multiplications on32-bit halves, with shifts and carry work. It is not one CPU multiply. The product/gap carriers may allocate unless actual inlining/unboxing removes them; generated-code cost is UNKNOWN.
- The normal wrapper has Int exponent guards in addition to fixed-word checks. It does not prove that source decoding, exact numerator construction, guess preparation, failure fallback or output release is free.

## Falsification and next discriminator

`word_gap128_model.py` exhausts57,600 width4 N/D/M triples, then checks20,000 width64 instances and4,000 signed normal-word outputs using64-bit denominators. All exact assertions pass. It preserves210 rejected midpoint cases. The three minimal structural mutants all fail: dropping the high-gap check accepts N=2^64+3,D=3,M=1; omitting the ordered-subtraction guard accepts N=2^63+1,D=1,M=1; using only the low product accepts N=0,D=2^63,M=2. These are finite exact models, not production pass rates or performance evidence.

The immediate discriminator is statement/replay/dependency acceptance of the exact helper source. Only after that and target authorization would a complete norm-output or filtered-dot caller be justified: charge exact numerator formation, arbitrary native guess, all checks/failure prefixes and fallback, and the whole output lifecycle. Current real-model time coverage, score impact and speedup remain UNKNOWN. In particular, pinned compiler substitutions already implement bounded Nat RNE and Nat.sqrt with native words; this source does not justify claiming saved GMP division or sqrt.

Fixed public source interfaces were checked at FloatLib0d91825727839f597fd06b22fdd038ea21480f0c in the MIT archive `research/representation/notes/CLEAN-FIXEDWORD-SOURCES.json`: Core/Runtime blob71d1bf2462da2cf1d6eff8b8fc3580fb681400b4; Core/Proof/UInt128 d9935670e5d70c31578b908af0134320ad87d8b2; Difference/Runtime96bd41f190ca70058efc1c429dc54e344b2831ae; Difference/Proofd0b29195c0a4caf517c9da1daee7ba4085c75b84. Only their API declarations/refinement contracts are used; no former-champion source body is copied.
