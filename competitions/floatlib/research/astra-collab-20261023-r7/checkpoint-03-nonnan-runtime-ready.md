# First actual non-NaN runtime candidate ready

2026-10-22 19:00 UTC. Read D04/D05 and independently read803 exact verdict,manifest and successful build/replay diagnostic. bb199701 operation bridge really passed statement on fixed Lean/FloatLib; this is not full gate or a performance result.

**Priority ready candidate: f01-r7-nonnan-runtime**, SHA c76056882d69a1122da44b4bc0bb3ab5274251826f0677af2aec5771926d7435,153390bytes. Exact parent8eb; new source NOT_RUN, full-gate requested at D's available current-public-suite slot. Hash/size/import/BANNED static precheck PASS.

Actual runtime change: NativeFinal.dot, originalSum, Packed10.finish and actual NativeDecodeSumWord sum finish accept any non-NaN terminal result, including infinities. Corresponding ordered induction uses the compiled non-NaN result-preimage, exact raw roundtrip, ofFloat32Add/Mul operation bridges. All four actual/checkable wrappers and proofs are connected; this is not an unused helper append. NaN endpoints still replay the original raw inputs, preserving sign/payload and signaling priority. Scalar add/mul, k order, packing/layout, USize fallback, zero-dimension branches and default getD values remain original.

This also changes NativeFinal.dot used by D's direct-small route, so an eventual exact D combination can benefit there without adding a new mathematical assumption. Do not combine gains arithmetically; run the actual combined source if selected. No measurement of infinity endpoint prevalence has yet been made on current public cases, and no gain is predicted.

Parallel NaN route: R7-W01 ZIP/report recovered toE:/Download, CRC71manifest entries verified. Supplied raw logs/metadata show Lean4.34.0 commit293d5d0 and fixed FloatLib/Contract hashes,27 named allowed-axiom outputs; independent original gate is still required for integration. The original proof file contains audit #print commands and dependency wording that cannot be copied raw into policy input; R removes those in a derived prefix, retaining every original byte separately. Concrete mul-non-signaling/quiet-idempotence/rounder classification are now supplied, rather than R6's unresolved helper parameters.

A draft f01-r7-nan-replay-nat044c43d2 exists but is not yet the requested queue item: R is extending its Nat early-replay helper to the actual direct-dot path as well, to avoid missing D's narrow-shape route. It preserves the tuned Submission scalar operations and allocates no index list. This preparation does not block the priority c7605688 validation.

Next: use real full-suite feedback for c7605688, finish the independently useful NaN fallback integration, and continue the10h window. No Git/CI operations byR, no new subagents or formal submission.
