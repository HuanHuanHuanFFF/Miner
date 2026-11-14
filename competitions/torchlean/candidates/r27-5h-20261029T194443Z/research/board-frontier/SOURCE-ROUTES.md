# Source and mechanism decisions

This is a research index, not a current-ranking receipt. Fresh current holder/report identity belongs to D's `competition-state` receipts.

| Source | Author / version | Mechanism inspected | Decision and legal boundary |
|---|---|---|---|
| Official ExactToolkit/StableNorm and SqrtProof | conjectures-io, accb82b6e2adeda1b41a57a260d68fb3879c427e | Exact rational mean/variance, rounded denominator, one final affine rounding | The actual contract; cannot move rounding or substitute native FP normalization. Root tree has no LICENSE entry. Read-only source pointers, self-authored model only. |
| Retired #12 | official hotkey in fresh source/report receipts; SHA e2c1f1f1… | Prepared exact dense, word128 row statistics, rational-output quotient decomposition | Strong normalized_mlp start; cap8 shifted remainder is a measured opportunity in finite model. Whole source remains ignored/private. |
| Retired #27 | official hotkey in fresh source/report receipts; SHA f92ee2c9… | Four-row/column dense, transposed GEMM via exact linear, continuation norm moments, native sqrt, cap26 quotient | Strong Mixer start; exact public predecessor of current36, never current itself. Source only inspected. |
| Radford Neal xsum | original author; [paper](https://arxiv.org/abs/1505.05571), [author source](https://gitlab.com/radfordneal/xsum) | Small/large superaccumulators with delayed carry; author claims long FP64 sums close to naive sum cost | Mechanism supports full-range accumulators but overlaps D's one-pass raw route; do not duplicate. FP64 sum performance does not prove exact binary32 product runtime here. No source copied. |
| FLINT | FLINT team, 3.7.0-dev docs | [Kronecker substitution](https://flintlib.org/doc/algorithms/polynomials/kronecker.html), [integer matrix routes](https://flintlib.org/doc/algorithms/linear-algebra/integer-matrix-multiplication.html) | Self-authored balanced-output and convolution controls. Polynomial convolution packing incurs huge unused coefficients; finite Python complete-cost probe loses 3.3–10.8x and is paused. |
| Lean UInt64.log2 / Nat.log2 | Lean team, v4.34.0; [UInt logical definition](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/UInt/Log2.lean), [runtime header](https://github.com/leanprover/lean4/blob/v4.34.0/src/include/lean/lean.h), [Nat runtime](https://github.com/leanprover/lean4/blob/v4.34.0/src/runtime/object.cpp) | Both small-word runtime implementations loop while value>=2, rather than promising an intrinsic CLZ | Reject the tempting replacement of #12/#27's six-stage word log by UInt64.log2: actual pinned source does not establish a faster implementation. No compiler-based speed claim. |

Actual Python arithmetic/proxy outputs are in `packed-model-result.json` and `norm-frontier-result.json`; all source/status/CPU limitations are retained there. No source performance is called current-champion performance. Full reconstructed predecessor code is excluded by `.gitignore`.


22:39 update: retired public23 exact source1010c074…, current43 sourcewithheld. NewlocalYbb2/Ya7 terminal finding and realrrsGe reuse inRMS-NATIVE-FINISH.md; Dfrozenreciprocal adoptedCproof-aliascompactor4c3dd792… resulting9654b727/253499B. Fullunknown-license source onlyprivate. These are exactsource/callgraph facts, not authorship attribution or newcurrentperformance.
