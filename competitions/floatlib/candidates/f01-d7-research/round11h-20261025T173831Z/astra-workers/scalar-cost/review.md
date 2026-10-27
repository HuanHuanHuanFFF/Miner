# R17 exact UInt64 product roundtrip: one independent cost review

**B removes R16's explicit external `Float32.toBits` boundary from the new fast-arm expression. It does not yet establish cheaper machine code.** The fixed unsigned reverse primitive has two clamp comparisons; unsigned conversion lowering may add a2^63 handling path. The masked product exposes useful bounds in executable arithmetic, but Lean proofs are erased and supply no optimizer assumptions. Actual removal of these paths remains UNKNOWN until D captures the selected optimized code.

## Correct source and comparison

Selected B is `Runtime-u64-mul-integer-v3-lf.lean.inc`,1098B, SHA **cd301ba43a18ba2b9db2a8b2f1109406d00242acdd543b26364d9925ffde6c67**. Its mathematical bridge is6664B/2261f1e3…. V1 and the older cost-contract paragraph describe A: two UInt32 conversions plus Float32 multiply before the reverse conversion. Those originals remain unchanged. The current9f9a B2-prefix probe is proof-only and contains no new runtime entry, so its unchanged MainFull callback cannot decide B's cost.

Old c972's exact selected C had two UInt32 casts, one Float32 multiply and one exported `toBits` call; its full-gate whole1.03055/MUL1.08190 negative result remains. B instead has two zero extensions, an exact UInt64 multiply, one UInt64→Float32 and one Float32→UInt64. The integer multiply and forward cast are serial dependencies; the two old forward casts could overlap. Primitive counts therefore do not establish a latency or whole-time improvement.

## Fixed Lean runtime, not name-based guesses

The referenced header is pinned Lean293d5d0c, SHA982c731a…. The relevant definitions are:

|Operation|Verified fixed-source implementation|What remains to inspect|
|---|---|---|
|UInt32→UInt64|`static inline`, C zero extension, line2120|Whether original operands stay unboxed through the actual caller|
|UInt64 multiply|`static inline` unsigned64 multiplication, line2132|Its serial dependency and target instructions; no-wrap is semantically valid here|
|UInt64→Float32|`static inline (float)a`, line3266; no explicit C clamp/helper|Unsigned64 machine lowering may need a high-bit/2^63 path if P's bound is lost; direct scalar instruction/helper choice UNKNOWN|
|Float32→UInt64|`static inline`, line3207: `0. <= a ? (a < 2^64 ? (uint64_t)a : UINT64_MAX) : 0`|Both clamp comparisons and any2^63 conversion adjustment after optimization; no external subcall exists in this unsigned primitive's source|
|Old Float32.toBits|Header line3254 is exported declaration; object.cpp line2000 performs NaN normalization and bit cast|It is absent from B's new expression, but legitimately remains in the fallback|
|UInt64 boxing|`lean_box_uint64` at2977 always allocates a scalar payload object; UInt32 boxing is tagged on64-bit|A selected `___boxed` wrapper, generic container or un-specialized helper must not accidentally carry P/R as objects. A wrapper's mere existence is not evidence it executes|

The v3 body uses machine words only and never calls `.toNat`, constructs a tuple/array or returns a UInt64 object. `normalCore(sum,u,v)` has UInt32 input/output and local UInt64 temporaries. Its attributes and the concrete caller should expose scalar operations, but this is not a substitute for emitted C. Generic `guardedMul` has a function-valued fallback: any closure/apply in its generic implementation must be traced to the concrete selected caller and branch before calling it a fast-arm regression.

## What the actual expression makes visible

For every raw u,v, even before the normal-input guard:

`a=(u & (2^23−1)) |2^23`, `b=(v & (2^23−1)) |2^23` give a,b∈[2^23,2^24−1]. Their zero-extended product satisfies

`2^46 <= P <= (2^24−1)^2 = 281474943156225 <2^48`.

Under the specified binary32 RNE, monotonic rounding gives

`2^46 <= R <= 2^48−2^25 =281474943156224 <2^48`.

This bound makes both numeric reverse clamp arms semantically unreachable; R is positive, finite and integral. It also puts both forward P and reverse R far below2^63. For cost elimination, even the weaker conservative R<=2^48 is sufficient. The strict product-specific lemma remains relevant to the mathematical reconstruction, but the optimizer need not know its full strength merely to eliminate2^63/2^64 paths.

There are three distinct compiler questions:

1. `uitofp` of any UInt64 is nonnegative and finite, so the lower/NaN clamp is mathematically redundant even without the48-bit bound. Whether the optimizer recognizes it is an emitted-code question.
2. The upper2^64 clamp is **not** redundant for arbitrary UInt64: near UINT64_MAX, conversion can round to2^64. Here its redundancy depends on preserving the masked-product range across the integer multiply and floating conversion.
3. Backend2^63 adjustment is separate from the source's0/2^64 clamp. Integer range visibility may simplify the forward cast while float-range propagation still fails to simplify the reverse cast; elimination of one does not prove elimination of the other.

The masks and zero extensions are executable facts and can be visible inside normalCore even if it is a separate scalar helper. `@[inline]` can also expose them to the public caller and remove helper boundaries, but does not guarantee Clang uses floating bounds. The theorem `R<2^48` is a Prop and is erased. If a revised runtime passes an opaque UInt64/Float32 to an un-inlined helper instead of computing the masks locally, that helper has no such source range. No `assume` or altered compiler flags are proposed.

The output needs a post-round R threshold2^47, then shift23/24, narrowing to UInt32 and fraction/exponent/sign packing. Choosing the threshold from P would be wrong at the documented46→47 rounding carry. The 0/1 high flag is executable and may permit simplification of the machine shift modulo64; actual simplification is likewise UNKNOWN. The old guard/fallback must remain part of complete timing.

## Signed64 alternative: API exists, new call boundary found

Fixed `SInt.Basic` has `Int64` as a compiler-supported unboxed64-bit structure (lines63–71); `UInt64.toInt64` is an inline constructor at1216, and `Int64.toUInt64` is its transparent field. `SInt.Float32` defines `Int64.toFloat32` via its model at104 and `Float32.toInt64` via its model at61. There is no opaque cross-width obstacle to these APIs. Positive P/R<2^48 would permit the intended numerical interpretation, but no new bridge proof or candidate was built.

The complete signed roundtrip is **not a clean replacement for the external call**: header3234–3238's inline reverse `lean_float32_to_int64` first invokes **`lean_float32_isnan`**, declared only as `LEAN_EXPORT` at2948 and separately implemented in object.cpp1976. It then performs signed lower/upper clamp comparisons and a signed cast. Forward signed conversion avoids unsigned-forward semantics, and signed reverse avoids the unsigned conversion's2^63 adjustment, but introduces this source-level external NaN-check boundary. In ordinary separate compilation the caller has no visible body for that function; a proof of finiteness does not erase the call. Actual disappearance would need exact optimized-code evidence. Per root decision this is sufficient to park a full signed alternative; no signed proof/CI queue was opened.

## One reusable discriminator

`audit_u64_roundtrip_c.py` verifies input/C hashes, follows the actual suite closure, extracts the chosen callback plus requested diagnostic helpers, traces recognizable numeric chains and reports visible masked-product bounds. It separately records whole-function fallback sites, object/Nat/apply sites and matching ASM hints. It never labels C-site absence as elimination of a standard inline primitive's internal clamp, or diagnostic-helper code as a timed public entry. Missing scalar ASM/constants remain UNKNOWN.

On the first actual runtime-containing B C, check: the selected or explicitly diagnosed arm has the intended single integer multiply/forward cast/reverse cast, no external bits conversion, no new cast helper/boxing boundary, and the mask-to-product chain is still visible. Then the accepted-path optimized ASM/IR must determine clamps,2^63 handling, calls and spills. Whole gate/timing decides adoption. No new candidate, local compile, Git, CI, bootstrap, source timing refresh or held-out input was used in this review.
