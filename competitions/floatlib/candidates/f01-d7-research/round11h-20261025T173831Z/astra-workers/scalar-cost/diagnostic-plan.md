# One runtime-lowering discriminator for D

The current9f9a probe contains mathematics only. To inspect B's actual caller before the final public proof, D can append the following two files to that **exact** source in one owner-managed statement diagnostic:

1. Existing `structural-frontier/inline-u64-mul/probe-b2-v1/Probe-b2-u64-roundtrip-v1.lean` — SHA9f9a297e90f236c349283248cca9aa8f94c35ff24ebe9e26873e2c63d708a933,240164B.
2. Existing `structural-frontier/inline-u64-mul/Runtime-u64-mul-integer-v3-lf.lean.inc` — SHAcd301ba43a18ba2b9db2a8b2f1109406d00242acdd543b26364d9925ffde6c67,1098B.
3. This directory's `Diagnostic-entry-b2.lean.inc` — ordinary public Lean def, no added attribute or foreign implementation.

Use the exact byte concatenation `parent + LF + runtime + LF + diagnostic`. `diagnostic-plan.json` gives the resulting byte count/hash **computed in memory only**; this worker emitted no full Kernel and requested no CI. D controls scheduling, import and any source repair.

The only change from the preserved217B `Diagnostic-entry-v2.lean.inc` is its fallback identifier: c972's `Submission.mulBeforeR16NativeRepack` becomes existing B2's `Submission.mul`. The old name is absent from the9f9a B2 prefix. This avoids a known naming failure without changing any of the four public runtime entries. No low-N, threshold, guard or signed-cast variant is added.

Capture nested candidate `Submission.c`, `MainFull.c`, archived input and their hashes. Discover the exact generated C symbol through the extractor's focus pattern `R17NumericMulInteger`; expected unboxed suffixes are `_R17NumericMulInteger_diagnosticEntry` and `_R17NumericMulInteger_normalCore`. On the same pinned runner, retain disassembly **with relocations and referenced constant values** for those actual symbols from the exact `Submission.c.o.export`. A boxed adapter or matrix loop is insufficient. If normalCore is called instead of inlined, keep both caller and callee. Preserve the object's SHA and the compile trace.

Then use `audit_u64_roundtrip_c.py --operation mul --focus-pattern R17NumericMulInteger` with the nested diagnostics directory, exact archived input/SHA and a new output folder. It will show the official MainFull MUL callback separately; that callback still executes B2 in this diagnostic. The diagnostic def may be removed by final linker garbage collection, so its object code is evidence of **that diagnostic caller's lowering**, not a timed or integrated public kernel.

The decision sought is bounded: whether the diagnostic numeric path has lost `toBits` without gaining a new conversion/helper/object boundary, and what clamp/2^63 work remains after optimization. Source range and static C counts are not performance. The existing mathematics must still compile; unused helper axioms need their explicit audit. No separate signed candidate or second timing queue is proposed, and no full-suite speed conclusion follows from this plan.
