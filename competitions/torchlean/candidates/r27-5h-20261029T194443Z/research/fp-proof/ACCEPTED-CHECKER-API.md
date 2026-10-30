# Accepted actual-checker interface

Verified artifact: boundary-v2/GuardedNonzeroContractOnly.lean,36650B, SHA fdb7fc1e77abbfbf03b9d0a0ed9a917d270c3fafd16f1ba9f8d2b7b491c938a0. Public standard CI40967910604 at commit3c6b481f242c208fc1b4f00f1f523650deb8f32b elaborated the entire standalone helper and audited all six requested roots; only propext, Classical.choice and Quot.sound appear. The exact source and raw log bindings are in batch6-proof-receipt.json. This is not the original all12 gate.

Use Submission.R27GuardedEndpoints.actual_acceptance_contains_exact_of_error as the main consumer. Its inputs are the actual native sum s, actual radius r, proposed raw32 q and exact real target S, together with three facts:

1. r.isFinite=true.
2. |nativeValue(s)-S|<=nativeValue(r).
3. Submission.R24PortableF64.certify s r s.toBits q=true.

It returns value(lowerWord(q))<S and S<value(upperWord(q)). The third input explicitly binds the word argument to s.toBits. Do not replace it by an arbitrary stored word without proving that equality. The runtime checker source is included exactly and its view equality is proved by reduction.

The accepted proof derives normality of q, finite nonzero raw midpoint words, finiteness of s and both native endpoints, real strict order from the actual UInt64 key comparisons, and the native RNE endpoint equations. The strict real midpoint pullback uses roundAt monotonicity and fixed-point values of representable midpoints. The caller does not supply outward-rounded endpoints or separate endpoint magnitude bounds.

Submission.R27GuardedEndpoints.actual_accepted_exact_nonzero has the same inputs and returns S!=0. actual_accepted_total_nonzero instantiates S=(T:Real)*2^e and returns T!=0. These roots are useful for the official finishWord branch that otherwise tracks signed-zero flags. No RN32 correctness of proposal is assumed: proposal(+0) is actually0x40000000 and is rejected, as the preserved exact negative control shows.

The remaining producer work is substantive. The target S must be related to the actual original input getters/arrays and official dsum; it cannot be a chosen ghost sum. Actual prepareFn/prepare origin, getter values, finite widening, peak/ceilLog2 bounds, native product exactness, exact accumulation order, and the bit-built radius must prove inputs1 and2 for that same S. The already accepted prepare_getter_interface concerns the exact old raw-array prepare source, not an arbitrary record with valid=true or the new ThinPrepared function. The latter calls changed log2word bindings and needs its own connection.

The remaining terminal work must turn the signed strict raw midpoint cell into the official binary32 word. fixed-scale/Fixed298NormalCellContractOnly.lean is a compact optional arithmetic candidate for that step, still NOT_RUN. Its integer magnitude must be T.natAbs and its sign must agree with q; neither is added as a global assumption to the final kernel. Actual exact fallback, bias, cache/index behavior and final twelve-field record equality remain separate.

Current policy: no active FP proof CI request remains. Preserve these accepted roots and wait for the frozen FP23 complete-call cost before expanding the new producer integration. Reuse the original failure and accepted receipt; do not rerun unchanged sources.
