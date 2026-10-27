# One cold-fallback boundary probe is justified

Stage began2026-10-26 21:59:24UTC, cap22:14:24UTC; overall04:46:39UTC unchanged. This stage writes only here and used no Git/index/CI/local Lean/nested agent. Exact frozen b271 remains untouched.

The actual BENCH_PLAN closure is closed__5 → main___lam__3___boxed → main___lam__3. `frame-evidence.json` independently rehashes the original C/ASM bindings for run40404258098, derives that closure from MainFull C, and records register uses and all stack-memory instructions. The original MainFull object hash is only an indexed record; its missing binary is not newly rehashed. This is the statement/bench-build diagnostic object, not a timed ELF.

| Observed item | Actual accepted path | Interpretation |
|---|---|---|
| r14 | Saved/restored, otherwise never read or written | This preservation is attributable to other paths; cold blocks assign raw x to r14 and retain it across calls. |
| rbp | Builds shifted raw y at1e/20 and supplies exponent at23; unused later on success | Cold table decoding later uses that shifted raw y. Its choice as a callee-saved register is consistent with cross-path liveness, not proof that the three hot instructions can be deleted. |
| r15/r12 | Hold exponents for normal guards and sum at7c; no later arithmetic-arm use | They are also needed throughout old software/codec fallback. A separate cold body may permit caller-saved allocation, but current evidence does not prove all saves will vanish. |
| rbx | Carries raw y into accepted mantissa/sign work | It is live on success. Removing its save requires different allocation, not deleting the raw value. |
| 16B frame | No accepted memory access; six `[rsp+0xc]` loads/stores occur at306/311,584/58f,7ef/7fa | The visible spill storage belongs to three rejected-path float spill/reload pairs. Success executes no call, but pays shared frame adjustment. |

Thus the frame and at least one preservation have a concrete cold-path cause. Attributing **all five** saves solely to the cold fallback remains INFERRED until the outlined variant is compiled. Push count or body size is not a cycle estimate, and saves may overlap with other work.

This does not reopen the old W11 proposal on the same evidence. W11's60f normal path itself contained two external ofBits calls, a float spill/reload and a toBits tail call; merely outlining its LowScale block could not remove those hot requirements. The new b271 accepted path has no call or spill, and the proposed boundary is the entire unchanged `R19Base.mul` fallback, including its native/special/software paths, rather than LowScale alone. The old noinline-LowScale parking result is retained.

`Kernel-jam-cold-fallback.lean` is the single complete source attempt: **255173B**, SHA256 **1d15cbf9723de827597cf677b937151b10911e31b446e969ce05e01f5563c552**. It adds only an ordinary `@[noinline]` two-argument `Submission.jamColdFallback := R19Base.mul`, its specification alias, and passes it to the same existing guardedMul. Its guards, arithmetic, fallback values and other public entries are unchanged by definitional equality. `cold-wrapper.patch` is a296B net addition and reverses to exact b271; `Cold-wrapper.lean.inc` is a replacement block, **not an append-only fragment**. `HelperAudit-jam-cold.lean.inc` preserves the original40 roots and adds the two wrapper roots,42 total. All new Lean/codegen/replay/audit/gate/performance are **NOT_RUN**.

Ordinary Lean noinline does not emit a native C noinline attribute, as the fixed W03 compiler review established. The useful boundary here is conditional on the generated MainFull C: it must contain only an external declaration/direct call of the wrapper, not its body. The actual saved MainFull compile command uses separate `clang -c`, `-O3`, and no LTO flag. If Lean keeps that cross-module boundary under the unchanged build, Clang cannot see the wrapper implementation there. This is a specific falsifiable expectation, not a promise that an annotation forces machine layout.

Minimum code-generation acceptance conditions:

1. Bind exact new input, C, selected BENCH_PLAN closure and optimized MainFull object. Do not substitute standalone guardedMul or cold wrapper assembly.
2. The success arm keeps the same Jam numerical chain and guards, with no new call, closure/apply, Nat/heap work, or spill. Compare its complete prologue/epilogue with b271. Target is a small leaf path; record any residual saves/frame instead of assuming zero.
3. Rejection should transfer directly to the exact cold wrapper, preferably by tail jump after ABI argument setup. Verify raw x/y preservation and any boxing/extra call/frame cost on misses. Wrapper numerical work is still fully charged when called.
4. Stop if MainFull still contains the old inlined fallback or the same shared5-save/16B overhead without a new relevant difference. Even a smaller success path is only mechanism evidence; full original workload must include miss overhead and all four operations before claiming gain.

No automatic CI request. Frozen b271's first complete-cost run retains priority; this source does not include bias, a range mask, guard changes or additional variants. Any adoption still requires the original full gate and independent D+A+B.

The old `R19Base.R19Jam17.diagnosticEntry` intentionally still passes `R19Base.mul`; only public `Submission.mul` receives the new wrapper. Its unchanged frame must not be mistaken for a failed public probe. If code generation warrants a complete-cost comparison, include exact b271 as the same-arithmetic control and keep B2 as the retained baseline; do not attribute Jam's own arithmetic change to this ABI boundary or assume their gains add.
