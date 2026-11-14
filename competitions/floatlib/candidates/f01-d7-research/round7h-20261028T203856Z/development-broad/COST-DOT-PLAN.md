# Exact-dot cost baseline — interface revised00:08UTC after per-operand cost review

Priority changed to one runnable discriminator. Freeze further mathematical packages; no new-target Kernel/ContractExact, formal submission or local Lean/native build. Shared deadline03:38:56UTC unchanged. Parent owns Git/CI/driver; broad owns only this directory and f01-r24-dev-broad-* source. First source+Fraction fixtures due within30–45min of priority message. Token/cache usage UNKNOWN.

Use the original33043-byte `references/official-incumbent/Kernel.lean` prefix, SHA5d0cef3ff21093ca05cde92e516edfe45afca8e11996ad4858e7fb2407d65868. Four public callbacks remain byte identical. New namespace `Submission.R24ExactDotCost` is diagnostic and initially unproved.

## Common input/cache API for scalar's Float64 path

`structure Operand`: `raw data : Array UInt32`; `minIdx maxIdx : UInt32`; `normal finite hasNonzero : Bool`. `prepareOperand raw` scans one operand independently. `structure Cache`: left/right Operand plus O(1) combined minScale/maxScale and matched status. Compatibility inline getters `c.rawA/rawB/a/b/normal/finite` are supplied. `pair left right` is O(1); `prepare rawA rawB` calls the two independent preparations then pair. This permits actual row/column reuse. No paired raw scan or free per-output metadata.

Normal raw word w is stored as w−0x00800000, preserving sign/fraction and storing the dyadic index(exp−1) in bits23..30. Zero stores index254 with zero fraction and its original sign. Inline accessors: `mant (u) : UInt64` returns0 for index254, otherwise0x800000 OR fraction; `idx (u) : UInt32` extracts index; `neg (u) : Bool` extracts sign. Array UInt32 uses immediate elements on64-bit runtimes, avoiding boxed Array UInt64. Subnormal or exponent255 marks normal=false; its packed placeholder is never used by a native loop. Scalar's optional FloatArray is prepared independently and charged on its full path.

Each operand records min/max finite nonzero raw indices0..253. Pair combines minScale=minA+minB and maxScale=maxA+maxB, a conservative summary when extrema occur at different positions. If either operand has no nonzero finite entries both combined values are0. Scalar uses the same separable H=maxScale policy. All-negative-zero status is computed in the timed MAC/replay loop; no paired prescan prepays it. Nonempty all-negative-zero products produce−0, other exact cancellation produces+0. Empty returns+0.

`fastEligible (c : Cache) : Bool`: matched, normal, n≤2^20 and48+(maxScale−minScale)+ceilLog2(n)≤128. This bounds every positive/negative prefix below2^128. No shape tuning. Zero/empty cases are separate exact constants.

`exactPrepared (c : Cache) : UInt32`; `full (rawA rawB : Array UInt32) : UInt32 := exactPrepared (prepare rawA rawB)`. Scalar's fallback calls exactPrepared on this same cache. The full two-argument callback charges all preparation, failed guards, computation and local cache drop. Prepared reuse is a separately reported mode retaining the cache. Parent's static callers must bind each function directly rather than branch within the timed inner loop.

## Native baseline and exact replay

Fast loop has four UInt64 recursive state arguments: positive low/high and negative low/high. Each term reads two packed words, multiplies24-bit unsigned mantissands directly in UInt64, aligns into128 bits using shifts0..80, selects the sign accumulator and adds with one carry. No Nat multiplication, per-term tuple construction or18-limb array. Final comparison/ordered subtraction gives sign and unsigned128 magnitude.

Final RNE is word arithmetic: six-stage existing FastMul.fastLog2, normal/subnormal target exponent, right shift plus guard/sticky/parity (including shifts64/128/>128), carry and overflow packing. It handles ties, underflow, overflow and signed rounded zero. A precise equivalence proposition against actual NativeBinary32.roundDyadic is recorded; no missing proof is labeled established.

Eligible failure uses exact finite raw replay: same minScale, UInt64 mantissa product converted once to exact Nat/Int and shifted/added, then actual NativeBinary32.roundDyadic. This is the genuine wide-span fallback, not the fast cost control. Unequal lengths or nonfinite raw words return canonical7fc00000 under the **research probe policy** and are reported UNSUPPORTED; no official NaN-payload/dot semantics is claimed. Their rejection prefixes remain in fixtures and results. Finite subnormals use exact replay. Scalar must share this total probe policy.

## First falsifier and evidence

Two new discovery seed groups: ordinary normal, wide span both inside/outside128 guard, cancellation, exact midpoints, empty/signed-zero, subnormal and nonfinite/mismatched rejections. Preserve every fixture and failure. Python Fraction computes all supported exact values and independent IEEE RNE words. The first CI checks all produced words/statuses before bounded timing. It must retain actual selected C/ASM to inspect four-word state, no per-MAC Nat/boxing/log2 loop and full cache release.

Compare exact baseline against scalar's Float64 certified proposal on identical raw inputs; cold/full and prepared reuse stay separate. Charge proposal construction, integer certificates, all failed prefixes and exact fallback. Oracle/prepared hints are engineering controls only. No current champion score, production input share, AMD/ARM qualification or performance claim follows from this probe.
