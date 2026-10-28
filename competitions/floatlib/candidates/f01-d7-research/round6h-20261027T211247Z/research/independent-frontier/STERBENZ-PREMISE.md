# Same-E opposite-sign prerequisite screen

Decision: **no new full candidate or independent wrapper**. The requested cheap native CLZ premise was not established. Keep the exact subtraction as a possible shared-adder component only after the existing c37/typefixed accepted-path cost is known.

Fresh fixed Lean293d5d0c `UInt/Basic.lean` and `UInt/Log2.lean` match their Git blobs (`uint-source-index.json`). Basic's author is Leonardo de Moura/Microsoft, Log2's Henrik Böving, Apache2.0. `UInt32.log2` is defined through `Fin.log2` with existing runtime binding `lean_uint32_log2`. The already archived exact fixed header982c731a has the inline `while(a>=2){res++; a/=2;}` implementation at2105. No CLZ/leading-zero primitive is present in these inspected API/runtime surfaces. This is source evidence; whether a particular optimized caller replaces the loop with a machine instruction remains UNKNOWN. No local compiler or new CI probe was run.

Existing B2 `FastMul.fastLog2` and `fastLog2_eq` provide a legal six-stage binary-search implementation/proof. For same-E opposite signs the implicit bits cancel, so `N=|fx-fy|<2^23`; the 32-bit stage is redundant and five stages16/8/4/2/1 remain possible. Removing a semantically redundant stage is not measured cost. This is the same normalization issue retained in R17 `exact-add-domains/cost-contract.md`, where an independent wrapper was parked; it is not a new cheap primitive.

The shared guard would first check equal exponent while ignoring sign, then choose same-sign 1-bit RNE or opposite-sign exact subtraction. This can share an exponent classifier, but adds a sign dispatch, magnitude order, zero handling, leading search, potential subnormal case and pack. Nonzero E0/E1 differences need no normalization, but their equal-cost incremental proxy is only0.018–0.033% whole in the exposed sample.

`sterbenz-same-e-screen.json` reuses the fixed256-strata old input screen, with no correctness enumeration. Added opposite-sign same-E proxy is3.16/4.34/6.21% whole; union with same-sign is9.96/9.63/9.70%. These assume equal pair cost within each historical cell and are **not speed estimates or upper bounds**. Nonzero E>=2 differences imply source UInt32.log2 means15.55/15.69/12.93 iterations; these are neither observed executed iterations nor cycles. True target-subset timings and miss costs are UNKNOWN.

The adjacent-E exact-close mathematical domain and its limited exposed coverage already existed in R17. R14 software ADD and R16/R18 numeric-roundtrip negative results remain; no source, proof, gate or benchmark is inherited by this proposed no-conversion arm. The initial identity/cancellation-only screen was not repeated.

Next trigger: actual cost of the complete same-sign guarded caller, plus evidence that a shared normalizer can beat its extra guard/order/search costs. Until then, do not expand large proofs or claim a ≥10% whole route.
