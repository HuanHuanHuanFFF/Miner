# First discriminator: compress exact product with sticky before U32 roundtrip

UTC 2026-10-26 20:01:53. State: CONTINUE_MATHEMATICAL_DISCRIMINATOR; no Lean/CI/native timing run.

Historical exclusions freshly checked: R14 9038 normal integer MUL whole1.04714/MUL1.29080; R18 00ab numeric U64 roundtrip whole1.01402/MUL1.03257. R15 f529 flag branchless runtime has its own real C and full-run trail, so branchless naming is not a new route. R18 signed64 audit plus fixed lean.h confirms toInt64 introduces external lean_float32_isnan; do not develop the full signed alternative. R18 scaled-U32 adds an FP multiply and constant access.

New selected mechanism: for P=24-bit mantissa product, form J=(P>>16) OR [P mod2^16 !=0], then J.toUInt32.toFloat32.toUInt32. J has at most32 bits and retains at least7 discarded bits before target RN24. Shift-right-jam is intended to preserve RN24(P) exactly after a2^16 rescale, eliminating both UInt64 conversions and any added floating scale multiply. Obtain normalized mantissa from rounded J>>7 or8, with postround threshold2^31. Guards/sign/exponent/fallback remain the00ab normal/S128..380 path. This is not claimed new globally; targeted history search found sticky ADD but no such U32 jam MUL implementation.

Cost premise: one48-bit integer product, fixed>>16, lowmask/nonzero flag/OR, U32 forward+reverse; compare00ab's U64 forward+reverse and scaled-U32's extra FPmultiply. Lean range proofs are erased; actual emitted complete caller must confirm clamp and conversion costs. Known fixed runtime U32 casts are inline and have no external NaN call or unsigned64 reverse2^63 path. Whole improvement UNKNOWN. Global previous model MUL share38.72%; 10% whole needs about25.83% MUL reduction if all MUL affected, eligible-time coverage UNKNOWN.

Smallest falsifier: exact integer model over directed halfway/carry/max cases, compare RN24(P) with RN24(J)*2^16. In particular sticky must preserve exact half versus just-above-half; choosing J=P>>16 without jam is expected false. Then write a Nat quotient/remainder identity with explicit discarded-width bound, bridge actual U32 primitive using R18 native conversion assets, and produce full path source or exact blocking obligation within45min of startup. No generic Float64/opaque bridge is required.

Coverage: two normal inputs, sum exponent128..380; all other input classes retain certified B2 fallback. Proof obligations: jam-RNE equivalence at P.log2=46/47, J leading bits30/31, UInt32 bound including rounded max, high/carry recovery and transport to existing00ab public spec. Full256000B package and four official roots remain mandatory. Native timing/full gate/helper audit/kernel replay NOT_RUN. Source/primary author evidence reused fixed Lean293d5d0c Apache2 and FloatLib0d918257 MIT; no upstream mutations.

Next checkpoint: exact finite falsifier and proof/source footprint; stop this route on an equivalence counterexample or a costly opaque interface. Actual token/cache usage UNKNOWN; worker CI0.

