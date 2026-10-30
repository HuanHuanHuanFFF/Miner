# Radius718 can accept an actually wrong adjacent word

This independent finite counterexample goes beyond an error-bound violation. It changes only the last two terms of the pre-freeze512-term witness. All1024 input words are normal binary32, n=512, H=252, L=9; the proposed word also passes the optional interior/nonpower domain. The exact inputs are the seven RLE pairs in WRONG-ACCEPT-718.json. No frozen source was changed.

In units Q=2^-46, let M=143552096388513792. Exact integer arithmetic gives true total S=M-1, while the native64 left-fold replay gives s=M+2704. The latter is binary64 word0x409fdffdf00000a9. Host IEEE double arithmetic reproduces every normal widening value, the final sum and both endpoints.

The true correctly rounded binary32 word is0x44feffef. The actual proposal formula gives its adjacent upper word0x44fefff0. Exact rational decoding verifies that M is their midpoint. Crucially, the true answer is computed from the exact integer total, not by converting a rounded Float64 sum to Float32.

For hypothetical offset718, the radius is2048Q. Both endpoint calculations are exactly on the binary64 grid16Q, so the lower endpoint is M+656Q and the upper is M+4752Q. The proposed upper word's strict cell is (M,M+2^33Q). Both raw midpoint key comparisons therefore pass, while S=M-Q lies in the lower word's cell. The actual checker formula accepts the wrong adjacent word.

The current offset720 radius8192Q rejects this witness. Offset719 radius4096Q also rejects it. Thus this is neither a defect in the accepted strict RNE fixed-point pullback nor a counterexample to the frozen720 implementation: the718 variant violates the error premise needed by that sound consumer. It also shows that restricting inputs to normal/zero and proposals to interior nonpowers cannot repair the718 bound.

Evidence scope: exact integer53-bit RNE model, independently checked midpoint arithmetic, actual owned bit-checker formula and host IEEE double replay. No Lean candidate was compiled or formally evaluated, and no performance conclusion follows. The construction uses only the arithmetic witness created23:11:31 and pre-freeze owned checker/formula sources; no batch9 confirmation data or FP23 timing data selected the terms.

Read-only independent-formula replay: run verify_wrong_accept718.py. It uses exact Fraction decoding and host IEEE arithmetic, writes no files, and compares direct real-cell membership with the bit comparisons. WRONG-ACCEPT-718-READONLY-VERIFICATION.json binds its passing source hash and the immutable witness hash. Other roles can run this verifier without overwriting this role's original counterexample.
