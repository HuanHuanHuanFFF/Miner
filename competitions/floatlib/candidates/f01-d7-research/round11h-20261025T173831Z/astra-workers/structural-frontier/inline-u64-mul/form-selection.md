# Two forms, one selected next probe

**Select the exact UInt64 product -> Float32 -> UInt64 form for the next bounded interface/codegen probe.** This is a source/proof-cost choice, not a measured speed ordering. Preserve the two-F32-casts form as the explicit same-semantics control; do not turn it into a parameter grid or queue two full timings.

| Item | A: native mantissa FP multiply | B: exact integer product (selected) |
|---|---|---|
| Arithmetic before reverse cast | two U32→F32 conversions, one F32 multiply | two zero-extensions, one U64 multiply, one U64→F32 conversion |
| Reverse operation | F32→U64 | same |
| Value fed to repack | RNE24 of exact48-bit product | same RNE24 of exact48-bit product |
| Native source interfaces | all static inline C | all static inline C |
| Main new proof | numerical U64 reverse decode; existing first_product_bits connects FP multiply | numerical U64 reverse decode plus short U64 forward model lemma and no-wrap integer product |
| Cost uncertainty | two forward conversions can overlap; FP MUL latency, reverse unsigned lowering | integer MUL dependency, potentially costly unsigned64 forward and reverse lowering |

B avoids a second forward floating conversion and uses the same exact48-bit multiplication already present in the software MUL family. The upper bound2^48 supplies a simple no-wrap proof and a reusable bounded integer roundtrip. Pinned OfNat.lean explicitly defines UnpackedFloat.ofUInt64 through ofNat/ofInt; the old R14 `uint64_model_eq_roundDyadic` body exists in99c2e2f6, but that diagnostic manifest is still NOT_COMPILED. Reuse is a known proof attempt, not an inherited pass. Its U32 analogue is in the retained full-gated source.

Do not conclude B is faster by adding primitive counts: A's two forward casts can execute in parallel, while B adds an integer multiply before its forward cast. UInt64→F32 may require unsigned conversion lowering if the compiler fails to use the masked product's48-bit range. The selected callback ASM must settle this before broad proof/confirmation work.

The output formulas, original guard, NaN/Inf/subnormal/zero fallback and reversed numeric clamp obligations are identical. No signed-cast alternative or wider ADD implementation is introduced. New files use a separate namespace and preserve v1 bytes.
