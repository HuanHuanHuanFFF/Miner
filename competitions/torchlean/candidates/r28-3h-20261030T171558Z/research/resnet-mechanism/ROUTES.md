# ResNet #11 mechanisms and proof interfaces

Authority: R28 UTC17:15:58–20:15:58; actual role start17:22:10. `requests/172118` and `research/requests/1730` processed. Droot owns cost profiling/Git/CI, root research owns coarse ReLU certificate; this role does neither duplicate.

## Verified source structure

Base SHA `ea6f582f…` has 251845B. `Submission.kernels.conv.1=Ybp`, `Ybp=cdQ false`. When the shape, finite/exponent-range, weight bounds and size guards hold, all 3×3 dense convolutions with `9≤K<256` use `Yt3w→Yt3c→Yt3g/Yt3f`. `Yt3g` already reuses each input across two output channels; this is an existing strength. It retains exact two-part dot accumulation, original bias-before-rounding and signed-zero replay. Failed guards use original full fallback.

Current official ExactSuite source at commit `9d4640e4d92b7f29611643e54601d5a114dc70b1`, GitHub blob `f78b33ea5ac54b5210bcaa19a03b70e93f5c5f6d`, was read through GitHub connector. CNN has four 3×3 convolutions with cin3 then c1; the later three take BN/ReLU or residual-ReLU outputs. All production profile c1 values are4–8 (boundary5/7), hence K27 or36–72: the shape-only specialized guard is reachable. Numerical guards and actual hit fractions remain UNKNOWN. Sparse weights are half zero by generator; normal values have exponent span6 and full varying significands. No low-precision input assumption is justified.

## A: exact zero-term elimination

Existing encoding stores signed integer X as `X+2^57`; zero is exactly `0x200000000000000`. Existing two factors are `(x & (2^25−1))` and `(x>>25)−2^32`, so both vanish for this encoding. Four UInt64 products for one input/two outputs can be skipped without any exponent, sign or floating-point premise. The unchanged finalizer handles bias and signed-zero semantics. `build_zero_pair.py` replaces only the paired body with an inline four-accumulator helper and introduces an unconditional helper equality; all-input proof is source-level UNCOMPILED. It makes no correctness claim from inherited source11 acceptance.

Minimal discriminator: one exact-source full cnn quick paired run; inspect generated C if slower/neutral to distinguish surviving branch vs tuple overhead vs optimized-away zero test. Potential is related to actual zero fraction and arithmetic share, both UNKNOWN. Dense nonzero branches can regress; retain all six cells.

## B: spatial F(2×2,3×3) exact-integer Winograd

This is distinct from R27's dot-product Winograd identity `(a0+b1)(a1+b0)−a0a1−b0b1`; that prior route's source12/sparse negative result does not measure this spatial transform. Its warning still applies: preserve #11 fallback and account for new preparation/packing.

Use integer matrices `G2=[[2,0,0],[1,1,1],[1,−1,1],[0,0,2]]`, `BT=[[1,0,−1,0],[0,1,1,0],[0,−1,1,0],[0,1,0,−1]]`, `AT=[[1,1,1,0],[0,1,−1,−1]]`. For signed exact aligned input patch D and kernel W, set V=BT·D·BTᵀ, U=G2·W·G2ᵀ, M=U⊙V. Each of the four direct convolution integers equals the corresponding entry of `AT·M·ATᵀ /4`; divisibility by4 follows the polynomial identity. Thus36 scalar products become16 per channel/tile, a55.6% multiplication-count reduction. These are operation counts, not latency or whole-model speedup.

Raw width growth is material: |V|≤4Xmax, |U|≤9Wmax. Under #11's existing `g+f≤31`, `f≤6`, the original product bound is <2^79, transformed products <2^85. Reusing unbounded full-channel signed64 accumulation is UNSOUND: the direct two-part accumulator proof's <2^55 term bounds no longer apply. Split25 with eight channels per block is safely bounded (the earlier four-channel statement was conservative, not a restriction); merge blocks into exact signed128 before final transforms. `SpatialWordBounds.lean` supplies uncompiled bounds, and `spatial-symbolic-receipt.json` verifies all576bilinear coefficients exactly. Parent's sharper block14/actual15-channel raw-word overflow witness is independently accepted in `parent-spatial-review.json`; block8 remains enough for current CNN shape profiles. Full formal cache/word-loop/array integration remains OPEN.

Frozen acceptance data, if announced, will not be read to tune either route. Existing common seed/public inputs remain research material. Local builds/native tools forbidden; any compiled discriminator goes through Droot request file.
