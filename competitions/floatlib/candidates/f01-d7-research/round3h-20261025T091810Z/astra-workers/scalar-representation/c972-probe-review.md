# c972 first compiled evidence — 2026-10-25 10:04 UTC

**Statement PASS; proposed eligible runtime structure is present in the actual selected C. Full gate, kernel replay/helper axioms, scalar machine cost and performance remain unverified.** Exact worker source, D candidate and archived input all hash to `c972fd72694d4d7db4660d2dbcd640d766d013d58bd9c9a27a6c68d47010b7ac` (247533B). Original run40182114389, source commit8d7590e44bffd0dd1929ae90d1cbc2dde3caacbf; raw verdict SHA90a3e8a4046ca0a19f2e3ce1a0d7a065002325a83b08102af08367f82df0e125.

| Check | Evidence and boundary |
|---|---|
| Correct caller | `BENCH_PLAN` branch → `Bench.Suite.run` second closure `closed__5` → `main___lam__3___boxed` → unboxed `main___lam__3`; actual MainFull.c line4249. |
| Eligible arm | Exactly2 UInt32→Float32 casts,1 native MUL,0 table read,0 ofBits,0 self-beq,1 toBits. Subsequent sign/exponent/fraction joins are integer operations only; no repeated midpoint, Nat arithmetic, allocation or closure application in that arm. |
| Guard/fallback | Raw-normal guard comes first, then `(exu+ey−128)<=252`; each failure returns through the original B2 LowScale/native/NaN logic. Two inlined copies of the fallback appear in distinct failure paths. |
| toBits boundary | Actual selected C uses original raw u/v for sign checks *after* toBits and carries precomputed exu/ey into repack joins. Thus the earlier live-value risk is concrete at C level. Actual spills, register choice and B2 tailcall remain UNKNOWN. |
| Code size | Selected callback generated C104322B versus B2's42488B; total static sites7 MUL/4 table reads comprise2 fallback copies plus1 fast arm. This is not7 multiplies per normal call or a measured machine-code-size regression; Clang merging is UNKNOWN. |
| Assembly | **Scalar ASM was not captured.** Archive has only Packed10Index loop, its redArg and R15PackedB2 loop; all their hashes checked. They cannot answer scalar tailcall/spill questions. No local compile/disassembly was attempted. |

The mathematical interface blocker is cleared at statement level without changing c972 or adding a proof variant. The next justified action is original full gate plus complete paired D cost. If D can include selected scalar symbol disassembly in that already-needed runner, request `lp_competition_main___lam__3` from MainFull and/or `lp_competition_Submission_mul` plus `lp_competition_Submission_R14ExponentShift_core` from Submission, binding the exact object. Do not run a separate long proof chain solely to guess spills. Machine evidence is useful for attribution; full timing still decides adoption.

`c972-caller-review.json` binds all source/input/C/available-ASM identities and extracted bodies. Reviewer script `review-c972-caller.py` exited0. All original files and c972 remain unchanged. No current R16 confirmation input/result was read; this is the explicitly provided statement diagnostic.
