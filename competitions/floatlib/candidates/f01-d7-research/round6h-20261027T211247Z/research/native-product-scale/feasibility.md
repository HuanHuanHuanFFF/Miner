# Native product followed by one combined power-of-two scale

Started **2026-10-27 23:25:59 UTC**, bounded to **23:45:59 UTC**; common deadline remains **2026-10-28 03:12:47 UTC**. No local Lean/CI or full new multiplication proof. The complete guarded runtime is **e51a67d6 / 1043 B**; the exact unchanged-B2-prefix probe is **92ff7182 / 227873 B**.

## History: same mathematical idea, different measured implementation boundary

The exact combined-scale formula and the fixed domain1≤ex,ey≤254,174≤S≤380 were already described in R13 `round3h-20261024T112622Z/astra-scale-fusion-feasibility.json`. It had a paper derivation and8852 source-word cases, explicitly no candidate/Lean/native execution/timing. Its first product was two exact UInt32 mantissa casts followed by native multiplication. R16 `scalar-representation/cost-and-coverage.md` again records the combined-scale form as not built or queued, with final toBits in tail position. This is a continuation, not a novelty claim.

R17's actual `Runtime-u64-mul-integer-v3-lf.lean.inc` and `f01-r17-dev-u64-public2` perform `product.toFloat32.toUInt64`, then threshold/shift/mantissa/sign/exponent output packing. R21/R22 scaled-U32 performs `product.toFloat32 * 2^-23`, reverse-converts toUInt32, then packs output bits. Those negative measurements remain valid for those exact bodies. Neither is this direct-native-result/combined-scale body. The bounded manifest/notes search found no full timing for this exact mechanism; absence of a hit is not a universal history claim.

## Fixed domain and no second precision rounding

For normal inputs, let Mx,My∈[2^23,2^24−1], P=Mx*My and S=ex+ey. The exact original product is signXor*P*2^(S−300). P lies in `[2^46,2^48−2^25+1]`, so UInt64 multiplication does not wrap.

The first **actual UInt64→Float32 conversion** produces positive `m*2^e`, with `2^23≤m<2^24` and e∈{23,24}. It is RNE(P), not the exact48-bit P. The accepted6589 component's `native_integer_product_decode`, R17 `product_word_nat`, `native_uint64_decode`, `rounded_shift_cases`, and the stronger Pmax bound provide precisely this interface. A carry46→47 is allowed; a carry47→48 is excluded by the product maximum.

Construct `w=((S−150)<<23)|signXor`. In the chosen domain, its raw exponent is S−150∈[24,230]. Existing `R2W01b.scaleAt_eq` and the normal-scale decode give:

```text
scaleAt(w) = signXor * 2^(S−300)
canonical dyadic decode = ⟨signXor, 8388608, S−323⟩.
```

This synthetic word is inside the *existing* NormalBand, and the scale itself is normal: its unbiased exponent is S−300∈[−126,80]. Multiplying the already rounded native product by it yields exactly `signXor*m*2^(e+S−300)`. The target has raw exponent `E=e+S−150∈[47,254]` and fraction m−2^23, so it is representable, normal, finite and nonzero. Therefore the second native multiplication needs no further precision rounding. The sign affects no ties-to-even quotient choice.

The original normal rounder uses the same m and rounded carry. Its target exponent is `middleExponent(P)+S−300`; since middleExponent=e+150, this is exactly E above. Thus both actual native operations and original raw multiplication can be connected to the same normal target word. This avoids asserting an unrestricted floating reassociation law.

**S=380 is safe.** At Pmax, the first rounded value is2^48−2^25; the largest final result is2^128−2^105, word`7f7ffffe`. The real carry witness `(2^23+1)*(2^24−2)=2^47−2` rounds to2^47 and gives`7f000000` at380, still finite. Do not drop that carry case.

**S=174 is tied to the existing table.** At173, synthetic exponent23 causes existing scaleBits to return signed zero; a nonzero product then becomes zero. The preserved example u=`2b000000`,v=`2b800000` has correct result`17000000`, forced unguarded core0. The actual new guard rejects it. No threshold search or guard expansion is proposed. Beyond380, the finite-target proof premise can fail; this note makes no new claim for that excluded domain.

## Concrete formal bridge still required

1. Reuse actual UInt64 product/cast decode from accepted6589/R17, rechecked in any assembled source. No Float64 cast or new primitive axiom.
2. Prove the synthetic UInt32 sign/exponent/table-index equalities and NormalBand membership. Only the synthetic word is known to satisfy R2's E≥24 band. **Original inputs may have E1..23**; use accepted R17 `R14NatNormal.raw_normal_decode` with E1..254 for them, not R2 `target_raw_decode` outside its domain.
3. Decode target `mkBits sign (e+S−150) (m−8388608)`. Use `R2W01cModel.mul_eq_of_finite_value` with the exact dyadic real-value product and finite/nonzero target, then `native_mul_eq_of_decoded_raw_model_mul_eq`, to certify the exact second multiplication.
4. Reuse original `R14ExponentShift.model_mul_normal_fields` to identify the same target with actual Model.mul of original raw inputs, then carrier injectivity/spec transport. The old `scaled_decode` for fixed2^-23 is not itself the new variable-scale theorem.
5. Prove the fixed wrapping guard and keep the original B2 fallback for every other word, including NaN/Inf/subnormal/±0. The current probe leaves all four public operations/specs B2; its7 roots are4oldspecs+3runtime definitions, not new mul_spec.

## Cheap discriminator and physical cost

`directed-check.json` contains672 selected exact source-word cases: signs, low original input exponents, min/max products, parity ties, carry and S174/380 boundaries. The fixed exponent/sum guard was checked on767 integer classes. These corroborate the fixed formula and expose the173 failure, but are not native execution, universal proof or performance.

Compared with B2's ordinary decoded-input path, the proposed fast arm uses one UInt64 product, one native numeric cast, one old scale-table lookup and one native multiplication, followed by the original native import/toBits boundary. It removes one lookup, an input-conversion path and two scaling/multiplication operations in that source-level comparison. Compared with the negative integer-extractor paths, it removes the **whole Float32→integer reverse/clamp and manual output-pack chain**; the remaining shift/mask work constructs inputs and the synthetic scale, not the result fields.

The actual tradeoff is not a primitive-count speed proof. Integer multiply precedes the cast, creating a serial dependency; eligibility, sum arithmetic, table loads, rejected-input fallback and the external output toBits still cost time. The table is the existing B2 table, with no new data preparation. Final native import is in source tail position, but only the selected complete callback can show whether a common fallback frame or spills remain.

The first deciding evidence is D's exact statement/codegen and full guarded callback cost, including all misses. Trace the real Main/Bench.Suite callback, not only normalCore. Confirm no reverse conversion/manual result pack, no accidental extra scale lookup or per-call preparation, and inspect the real final toBits call/return and frame. Only a favorable complete-cost signal justifies the remaining formal bridge/full-gate work. No new CI is dispatched by this role.
