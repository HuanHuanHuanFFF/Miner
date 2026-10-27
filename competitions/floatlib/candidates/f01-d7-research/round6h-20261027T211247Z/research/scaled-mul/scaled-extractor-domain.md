# Why the original exponent domain is part of the scaled interface

This is a paper boundary analysis, not a proposed guard expansion or new performance candidate. The R21 e=23/24 premise is retained unchanged.

For an exact scaled integer `Z=m*2^k` with `2^23≤m<2^24` and Z fitting UInt32, the runtime high word is `floor(Z/2^24)`. The proof needs this word to equal k; then the following shift recovers m and the exponent correction is correct.

- k=0: high=0 across the whole 24-bit mantissa range.
- k=1: high=1 across the whole range.
- k=2: high=2 only for `m<3*2^22`; at m=3*2^22 it becomes 3. Thus even exact scaling and a no-clamp cast are insufficient to generalize `scaled_fields` to all e=25.
- k≥3: the lower mantissa bound gives high≥2^(k-1)>k, so the exponent correction is already wrong. With UInt32-fit Z, only k≤8 is relevant.

Checking only recovered q can miss an error because UInt32 shift counts are reduced modulo 32. An exact example is m=8912896 (`0x880000`), k=8: Z=`0x88000000`, high=136, and the second shift uses 136 mod 32=8, so q=m. The mantissa is correct but the exponent increment 136 is wrong. The real proof must carry **both** equalities in R21 `scaled_fields`, not just q recovery.

The included literal Lean examples in `Extractor-boundaries.lean.inc` are **NOT_RUN**, use `decide` rather than native decision axioms, and are not full-domain proofs. All integer values below are exact arithmetic:

| m | k | Z | high | effective shift | q | expected exponent increment |
|---:|---:|---:|---:|---:|---:|---:|
| 12582912 | 2 | 50331648 | 3 | 3 | 6291456 | 2 |
| 8912896 | 8 | 2281701376 | 136 | 8 | 8912896 | 8 |

The current multiplication products do not reach these cases: its already proved product bound gives e=23/24, hence k=0/1. This analysis constrains future reuse; it does not refute the scoped R21 mechanism.
