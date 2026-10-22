# R6 proof repair and changed benchmark scope, 2026-10-22 13:51 UTC

Read D r6-feedback-03 and original public-delta patches. Officiala0e80de/70d6da introduced private paid-suite scoring and public-v2 practice suite, with timed specials/subnormal/paired/extremes and multiple sizes. **All R6 old-class39.7/52.7 share calculations and ALL_TIMED_INPUTS guard coverage are legacy-only. New suite shares and actual hit/cost distributions UNKNOWN pending D baseline.** Old pins/original evidence remain untouched. Future adoption must bind the actual new suite version/hash and fresh whole results; do not carry the old champion inference chain across it.

704 exact fused-addb911 failed statement, not performance: `Unknown constant Bool.and_eq_true.mp`, line2099. R read actual full-build-output and verdict; the preceding finite_of_fastOK proof has no reported error. Original source retained. Fixed proofs use `simp only [Bool.and_eq_true] at h` then h.1/h.2; no runtime definition change.

- Preferred repaired normal-add: f01-r6-normal-add-proof1, SHA8a0e40fb8154987496d751827e382003c88b5f096df0ee4baeb55e2ca8a4b373,142431bytes, NOT_RUN.
- Optional repaired fused-add: f01-r6-fused-add-proof1, SHAbdbcdd13217166bcb2a086fa228b061316c98eb2ccba247eecb744b1e9619f45,141487bytes, NOT_RUN.

Both static checks PASS. Normal-add original3693 has the same proof typo and should not be newly queued. D owns deciding if/when any repaired candidate gets suite timing; no duplicate mandatory runs requested. R normal-mulf6acc4bc is in D705; waiting actual feedback.

New-suite investigation: fixed FloatLib `Model.chooseNaN2` prioritizes signaling NaNs before quiet NaNs, ties left-to-right. Thus “a quiet NaN accumulator absorbs every later sum input” is FALSE: a later signaling NaN replaces it with its quieted payload/sign. This is a real semantic guard against premature sum termination. In a dot product, however, each multiply output should already be quiet/non-signaling, which may allow an absorbing NaN accumulator and skipping the remaining dot products; this needs an all-input mul-output theorem and a fold bridge. This distinct route targets potentially large poisoned-input fallback cost, but no timing share or proof acceptance is claimed yet.

R6-W02 original ZIP/report downloaded to E:/Download at13:51; integrity/review underway. W01b ordinary UInt64 bias proof still running. R will finish these existing artifacts and narrowly investigate nonfinite fold semantics before14:15 freeze; preserve full confirmation reserve.
