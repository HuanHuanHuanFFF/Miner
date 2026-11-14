# Isolated next-round primitive: FW nonnegative scaling

This does not change frozen GEMM/RMS candidates or request CI. Actual public23 FW accepts only `t<0`; the existing formula cell27051001/scale/normal/batch8, LN row5 has t=0 and falls back. Its exact32 inputwords and denominator3fa32428 are in `fallback-first-falsifier.json`. This row is not allzero.

For integer S>0 and0<m<2^32, let L=floor(log2S), M=floor(log2m), t=floor((48-L+M)/2), and assume t>=0. Write r=(48-L+M)mod2, so r in{0,1} and2t=48-L+M-r. For A=S*2^(2t):

- 0<=t<=39.
- 2^(48+M-r)<=A<2^(49+M-r), hence A<2^80.
- Since2^M<=m<2^(M+1), A/m>2^(47-r)>=2^46 and A/m<2^(49-r)<=2^49. Thus2^46<=floor(A/m)<2^49.
- If m<2^16, then M<=15 and A<2^64. Both actual normalization denominators, n or n*n with0<n<256, satisfy this stronger bound. Thus this branch can use a UInt64 leftshift and one q/r pair; native128 multiplication is unnecessary.

Let q=A/m, rem=A%m and root=Nat.sqrt q. Then2^23<=root<2^25. Existing FY/sqV quarter-position classification applies: exact ifq=root² andrem=0; belowmidpoint ifq<root²+root or equalityand4rem<m; tie ifequalityand4rem=m; otherwiseabove. Use b2=0,z=true and original exponent(c-298)/2-t, wherec iseven. Original sqV normal-range check and fallback remain.

`fw_nonnegative_probe.py` tested20000 exactinteger cases:18603 nativeword results match exactrational sqrt,1397 retain finalrangefallback; maximumscaled A width80. The actualpreviouslyseen t=0 row becomes nativeandmatches3fa32428. These are finite model results, no Lean/native timing.

Concrete proof interface from exact23 source:

1. `lg128_v`, `shl128_v`, `dv128_v` already connect words to exactS/division. Foractualm<2^16 branch, derive S highword0 and A<2^64 to use existingUInt64 lemmas directly.
2. **FY_v is not directly instantiable with num=A,den=m,K=1:** it requiresden=m*(4*K). A viable bridge setsnum=4*A,den=4*m,K=1,b2=rest=0, then proves commonfactor4 invariance of sqA and the accepted native branch of sqW. This bridge remains NOT_COMPILED/NOT_WRITTEN. Do not silently omit it.
3. `FY_root` or the q bound gives root>=2^23; unfold YaD positivebranch, rewrite its exactshift/division to A/m, and match sqW. Existing FW_v covers thenegative branch; do not alter it without freshall12gate.

Why continue only asproof-space research: one extra native row is not a10percent model opportunity. The potential is replacing expensive customgeneric fallback implementations with pinnedofficialfallback aftercoveringthis practicalgap, allowing their now-dead proofclosure to be removed beforea5/23 crossboard composition. Complete tailcostand source/proofclosure must be measured; rarefallbackcounts alone cannotjustify it.
