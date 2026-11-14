# RMS native terminal, distinct from row reciprocal

22:37 UTC: public23 still calls generic `Ya7 -> YN` for each RMS output (source lines1161–1163,2958–2963). Its native128 `rsV/FFr` accelerates row statistics/sqrt only. The current reciprocal candidate changes only layernorm `MYbc/Ya7G`; it does not cover the RMS stage. Pinned ExactSuite normalizedMLP executes RMS at widthh followed by layernorm at widthh2.

Own `RmsNativeFinish.lean.inc` reuses public23 existing **rrsG/rrsGe** native quotient-and-round terminal. `N=mant(w)*mant(g)<2^48`, `D=mant(den)<2^24`, `U=idx(w)+idx(g)`, `V=idx(den)+22`; then `E+127=U-V`. Positive denominator and `D<=N` meet the theorem; exactzero returns +0 as originalYa7; tinyproduct, nonpositive denominator, underflow/overflow use original fallback. No FP arithmetic, rowcache, new accumulator, or altered statistic.

`build_rms_native_finish.py` connects actualYbb2 and T4b while retaining originalall12correct. Base23→**254137B/d0e60a6e…**, +1498B. Fullgate and nativecost **not run**. Originalstaticpolicy passed. `CI-REQUEST-RMS-NATIVE-FINISH.json` supplies exact hash/dependency/cost boundary. This is a directly testable source/proof bridge, not a request for a large new proof project.

Finite pre-freeze census:54 complete formula cells,38853 RMS outputs;19443 exactzero and19410native; all matched formula.31728 adversarial triples also includefallback strata; full counts inrms-native-finish-check.json, no mismatch. This gives coverage only, not runtime share or speedup. D should choose one complete NMLP cost sample; preserve allzero/fallback/prepare/return cost.

Optional existing guard26v2 composition (no newqueue): exact accepted patch text producespublic23+guard252990B/ab527c68…; reciprocal9654+guard253850B/e3e247dd…. Fresh fullgate needed for each composition. Do not sum their measured gains or call them accepted.
