# Preparation-scope correction and a separate work-elimination route

This corrects the unqualified statement that all oldQPD Nat entries are immediate. That statement is valid for a row satisfying the actualQPa combined-span<=15 fast guard. It is false for all rows prepared under the globalQPS test.

Exact source reviewed: previously capturedpublic23 SHA2561010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe; original fullsource remains private. Source pointers: QPb/QPD688-692, QPS701-703, QPa705-730, YaV865-875. QPS uses the MINIMUM input-row span plus the maximum weight span; YaV then prepares every row. QPa separately tests each row's actual combined span. Thus one narrow row can enableQPD construction for another wide row that will never consume it.

check_prepare_scope.py independently binds that sourcehash and models two normal16-element rows: all1.0(span0), then15*1.0+one2^40(span40), with all1.0 weights(span0). The global span test is0+0<=15, so both rows are prepared. The second row's consumer span test40+0<=15 is false. Its high element hasM=2^63; both centered UInt64 cache entries are3*2^62=13835058055282163712, larger than the64-bit smallNat limit2^63-1. prepare-scope-counterexample.json records the exact words, formula, timing and hashes. This is source-bound finite arithmetic, not execution of the actual kernel or an allocation measurement.

This does NOT establish aFloatArray benefit. The60-bit codec is valid only where the actual input magnitude boundM<2^39 holds; do not apply it indiscriminately to every globally prepared row. Preserve the row fast guard or the original fallback. Newly packing the wide example would corrupt the factor.

A distinct possible change is to avoid building aligned caches for rows withinputSpan>15. Every weight span is aNat, so such a row cannot pass the originalQPa sum<=15 test for any output. Source also already supplies Yuc4 atline1340, equating the groupedYaUc4 fallback with four scalarYaU results. UnusedCacheElisionProof.lean.inc sketches actualQPa andQPac4 cache-dropping equalities using only that realguard and existingYuc4; NOT_COMPILED, no new arithmetic theorem ornative assumption. It must be grafted into the exactprivatepublic23 environment, not imported as ifContractExact declaredQPa.

The surroundingYaV scheduling andQPa2/QPa4 paths still need exact equality binding before a candidate is called correct. The empty-cache sentinel triggers the existing grouped fallback, not a zero-output assumption; review that caller behavior rather than deletingP blindly. No patch was applied to the actualkernel, noCI was requested, and no newconfirmation input/result was read.

Next decision: measure how often realold-seen rows haveglobalQPStrue butperrowinputSpan>15, and whatQPD preparation fraction is paid, BEFORE implementing this separate route. If absent, keep only thecounterexample as a scope correction. If frequent andcostly, a smallguardedprep-elision candidate can precede any newFloat carrier. No measured prevalence orgain exists yet.

