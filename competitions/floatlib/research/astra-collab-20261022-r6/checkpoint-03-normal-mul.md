# R6 distinct multiplication route ready, 2026-10-22 13:37 UTC

Read D r6-feedback-02. Started703/704 must finish; R does not cancel or dispatch. No more add guard variants planned. Existing R normal-add preferred two-compare front door differs from D finite-decode's retained finite guard; both need actual whole-call comparison.

**New independent candidate:** f01-r6-normal-mul, SHA `f6acc4bc211eb1724a4152a60f2dea391959c5ddfa9ba09b7b15455025563d8a`,143655bytes. Exact parent8eb, original add/sum/bmm unchanged. Static hash/size/import/BANNED PASS; Lean and timing NOT_RUN.

Current native normal multiplication invokes two out-of-line ofBits conversions and one toBits (actual608 C). The earlier all-numeric converter replacement regressed mul, so this does not repeat it. This candidate instead reuses the exact integer word multiplier and shortens its leading-bit search: if the product lies in[2^46,2^48), its log2 is46 or47, selected at2^47. Outside the band original fastLog2 remains. The key lemma uses Nat.log2_eq_iff and word-toNat bounds; roundP/core/mul bridges reuse the accepted FastMul spec. No fresh IEEE arithmetic proof is introduced.

The public mul still routes ex+ey<128 to unchanged LowScale; the other route now uses this word multiplier. For both normal operands, 24-bit significand products always lie in the specialized band. All near-one, and spread samples not taken by LowScale, are eligible; raw/special values retain the original exact fallback. Native vs integer arithmetic remains a real tradeoff, and observed benefit is UNKNOWN. The gain could affect a substantial part of52.7% scored mul share, but still needs full12-class25-round gate and whole-package comparison. If near-one/spread regress, park this concrete replacement rather than claiming all integer normal multiplication is impossible.

Minimum decision experiment is one full candidate/8eb paired run; if runner budget requires ordering, R normal-add has the smaller change while this is the distinct higher-uncertainty mechanism. No need to benchmark standalone log2 as a proxy. R will continue byte/proof review and recover both web jobs before freeze14:15.
