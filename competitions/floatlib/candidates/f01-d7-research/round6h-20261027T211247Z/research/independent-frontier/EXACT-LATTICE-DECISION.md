# Cheap exact-lattice dot certificate: valid paper domain, insufficient exposure

The20-minute prerequisite screen started22:22:52 UTC, deadline22:42:52. It created no candidate, new Lean proof, CI or random search. The source-model screen uses only the same three completed R15 plans, exact B2 and archived official generator/cell timing identities.

**PARK under the requested roughly10% whole investment test.** There is no newly certified whole matrix in any draw. Row/column certificates with genuinely nonzero products occur only in two ML cases of the third draw; their *entire* ML cell is6.3902% of the historical whole. The first two draws have no nonzero-product certificate hits at all. The entire-cell ceiling already assumes erasing much more work than the actual selected subset; actual preparation, guard, output and miss costs make it weaker, not a speed prediction.

| Completed B2 draw | Complete input words | n*maxA*maxB certified nonzero-product dots | Tighter summary-L1 certified nonzero-product dots | Certified zero-product dots |
|---|---:|---:|---:|---:|
|40168687803|2890628|0|0|147809|
|40169957447|2307906|0|0|178535|
|40171180249|2928022|28314|31416|14164|

All34 timed BMM cases per draw were scanned. A/B source byte hashes exactly match the prior complete underflow scan. The three sequential scans took13.13/9.57/11.83 seconds with individual30-second external limits. Zero terms were classified separately with analysis-only position masks; those masks are not a proposed runtime certificate. Zero-product hits cannot be advertised as evidence for faster nonzero integer arithmetic.

The two nonzero cases are:

- `bmm:ml:0`,shape1400×(3,6,7),10 fractional bits: nmax35/29400 dots, tighterL1 295/29400. A standalone summary pass reads84000 words, stores14000 row/column summaries and checks29400 outputs.
- `bmm:ml:7`,shape8823×(2,5,2),7 fractional bits: nmax28279/35292 dots, tighterL1 31121/35292. Summary pass176460 words,35292 summaries and35292 output checks. Both cases have very short n5/6; there is limited arithmetic to amortize preparation and final packing.

These counts are exact for the source transcription, not actual Lean operand dumps, private-suite prevalence, cycle counts or speed. Per-case eligible time was not retained by the old public gate; only class totals support the coarse6.39% ceiling. No MAC or output fraction was used to apportion cell time.

**Paper certificate, not a new theorem.** For every finite input row/column, take its largest common dyadic quantum from actual mantissa trailing zeros and exponent, and express values as integer coefficients: `a_k=A_k*2^eA`, `b_k=B_k*2^eB`. Let `M_A=max|A_k|`, `L_A=sum|A_k|` and likewise for B. Require `-149<=eA+eB<=103` and

`C=min(n*M_A*M_B, L_A*M_B, M_A*L_B)<=2^24`.

Then every exact product coefficient and every ordered prefix coefficient is bounded by the total absolute product sum, itself<=C. Such coefficients at the specified quantum are exactly representable in binary32: no subnormal-grid truncation and no overflow. Therefore each original multiplication and each original prefix addition has no rounding error. Only after transporting that invariant to the actual specification may an integer reduction or reassociation be used. L1 is a tighter sufficient condition than nmax, not equivalent to it.

Integer-machine bounds, exact raw output packing, finite input rejection, and+0/sign-zero semantics still need full proof. The+0-seeded original fold cannot be replaced by an arbitrary signed-zero convention. No claim is made that arbitrary real-valued reassociation or one final rounding preserves the original program.

**Minimal finite corroboration.** `exact-lattice-witnesses.json` contains six deterministic first nonzero witnesses from the completed summary: three n6 cases using the tighterL1 bound and three n5 cases passing nmax. It checks33 original products and33 prefixes with the fixed exact-integer word oracle, and all six final words equal the integer reduction. This is a finite oracle check, not Lean or host-FP proof. No additional random samples were generated.

**History matters.** R19 `astra-quantized-certificate.md/.py/.json` already used the same general common-grid/L1 paper condition and retained the `[2^24,1,-2^24]` sequential-versus-once-rounding counterexample. Its8/102 BMM sample hits were allzero terms (`bound_bits=0`); its apparently broad sampled hit percentage was not nonzero exact-dot evidence. R12's low-exponent integer-unit route found no incremental whole hits beyond UnderflowZero and still required per-step rounding. The present changed premise is a cheap input-summary guard reusable across output dots, screened on complete newer exposed draws; it does not erase those old negative decisions or provide runtime proof/performance.

Standalone summary scans, coefficient preparation, signed arithmetic, failed-certificate fallback and output encoding must be paid. Early rejection or fusion with existing preparation may reduce scans but is UNKNOWN without an actual implementation; no free preprocessing is assumed. Since even the nonzero affected entire-cell ceiling is below10%, stop before constructing that implementation. Preserve the sufficient condition and six concrete nonzero witnesses for a future input distribution or independent cost premise.
