# Whole-dot64 after exact common weight scaling

**Finite discriminator closed negative:** the actual oldseen fixture has common mantissa trailing count0 in every inspected weight row (1980 row observations across18 calls). Every otherwise prepared dot fails the new whole64 mass guard, so no implementation, proof or CI is justified for this common-scale variant. The mathematical identity remains valid under its stated premises; this is a representation-premise negative, not an arithmetic counterexample. See whole64-scaling-census.json.

This is isolated next-direction work using only source23/27 and the oldseen27051001 formula fixture available before freeze9. It does not change frozen8/9 or use their new input/output values for candidate selection. No CI request or actual kernel implementation is made here.

The existing prepared product contains the24-bit weight mantissa even when its low bits are all zero. Let t be a common trailing-zero count for the mantissas of one weight row, clipped to23. Dividing every aligned weight coefficient by2^t is exact. Accumulate the correspondingly scaled products in one signed64 word, then shift the complete signed result left by t once, using the existing `shl128` carrier. The original YL bias insertion and YD finalizer can then be reused at the original base. Bias is neither divided nor rounded early.

With source metadata spans sx,sw, each unscaled term has magnitude<2^(48+sx+sw). After exact division the term magnitude is<2^(48+sx+sw-t). If c=ceil(log2 n), the sufficient whole-dot guard is:

`48 + sx + sw + c <= 63 + t`.

The old per-dot word64 mass failure before removing common scale does not eliminate this changed representation. The new condition must be measured on actual sourceYc metadata and all preparation counted. For normal words the hidden mantissa bit is bit23, so clipping t<=23 makes trailing zeros of rawWord's low bits sufficient; subnormal mantissas use the same low fraction bits. OR the raw words in the existing weight metadata pass, then compute t once at the end. This proposes one extra OR per weight entry, without a second full scan, per-dot maximum scan, or another full weight-factor array.

Preserve the existing4-row prepared schedule. In the shared weight decode, shift its aligned mantissa right by t once, serving all4 row products. The hot loop carries only4 low words. At the terminal use existing `shl128 (0-(s>>>63)) s t` to recover each original high/low carrier, then original YL/YD. For t=0 the existing zero-shift arm is essential. All failed bounds, sparse-index handling, zero sentinel and nonfinite behavior retain the original path.

Remaining proof obligations are common divisibility from the OR metadata, exact scaled callback products, signed64 whole-sum mass/uniqueness, sign-extension/shift equality to the old128 fold, metadata projection, and actual scalar/2-row/4-row scheduling. ExistingE2/C9, D8/Qsx and accepted modular word lemmas are foundations, not a proof of this new source. Full source size and proof cost remain UNKNOWN.

First discriminator: finite actualmetadata/common-scale census on oldseen complete formula cells. If it closes the representation premise, a later native-only cost source must retain4-row reuse and fuse the OR into the existing metadata scan. Do not repeat the earlier allrows scalar regression, claim new unboxing, or infer timing from word counts. No native code or speed claim exists yet.
