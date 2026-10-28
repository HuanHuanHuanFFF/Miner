# Joint middle-exponent ADD: historical mechanism already tested

Closed under the requested stop condition. The20-minute-capped stage began22:43:55Z; the decisive history/actual-caller result was available by22:48:58Z. No new runtime, proof or CI.

The premise that ADD might not have used this entry is false for R11. Exact `f01-d11-scalar-normal-band`/e279b354/240454B changes public ADD at3353–3370 to joint eligibility, two bare `tableProduct` conversions, native add and `ofFloat32`. Both original per-converter eligibility checks and the result self-BEq disappear on its hit arm. Its original fallback remains for NaN/Inf/zero/subnormal/out-of-band words.

The archived statement C was pruned from the working tree, so it was read from immutable Git blob55731815… and recovered **only into this C directory**.88806B and SHA9fb8629f… match the recovery catalog and original receipt. Actual `BENCH_PLAN -> closed1 -> main.lam0.boxed -> main.lam0` has exactly that accepted path, with2 UInt32 casts,2 table reads,2 scale multiplies,1 native ADD and1 output codec; no converter eligibility or result classifier inside the hit. `historical-e279-add-accepted.c` is the bounded exact excerpt. This is selected C evidence, not a retained timed scalar assembly artifact.

Original full public-v2 run40037275281 was rechecked from its source/verdict/work receipts. Reference-normalized comparison is ADD1.051906 and whole1.008306 versus41; versus its actual a066 parent, ADD1.043497 and whole1.017595. These are historical comparisons, **not a new B2 verdict**. `middle-domain-history-audit.json` keeps raw and normalized values separately.

R19 aeaae was MUL-only and kept ADD unchanged because this ADD mechanism had already been tested. Its MUL parent did materially change from raw ofBits to guarded numerical decoders; that is why the old restricted MUL revisit was separately retained. Jam17/b271 changes integer-product rounding and is not evidence that a new ADD joint guard was tested. None of these statuses is upgraded here.

The proposed bit predicate depends only on exponent bits7/6: bit30 of `u xor(u<<1)` is `E7 xor E6`, independent of sign/fraction. Its set domain is therefore exactlyE64..191 for each operand. The old masked-offset OR guard also selects exactly those intervals. Replacing the old two masks/two subtractions/OR/compare with shifts/xors/AND/test is a different guard expression on the **same** domain and accepted body. Optimized machine equivalence or a cycle advantage is UNKNOWN; it does not uncover three new removable guards. No instruction count is promoted to a speed estimate.

This closes the hypothesized missing ADD entry before generating another probe. Revisit only with a demonstrated new runtime cost premise beyond re-encoding that historical guard; no threshold or seed grid.
