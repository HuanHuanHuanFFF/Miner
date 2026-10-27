# a066 TunedAdd fallback capacity

Read-only review starting2026-10-23 22:42:21UTC. Exact a066 is237142B, SHA `a06608bdc419d4647af301bfdd617d52e4796c404661a28672a022eef4a10b78`. No Kernel/manifest/tool/state was generated or changed; only this report pair is written. Current16/17 validation remains the priority.

**VIABLE_CAPACITY_LEAD, NOT_IMPLEMENTED:** replacing the existing NaN-result add fallback with original ExecFloat.add and its existing specification theorem permits a statically isolated15524B namespace deletion, net15513B after the two replacement identifiers. This clears the5KB threshold without a new arithmetic proof. It is a source-capacity opportunity, not a measured speedup or compilation result.

## Exact removal and reconnection

Keep the outer `namespace Submission` at1922 and every legal/author/source notice. Remove only the unique balanced block starting with `namespace TunedAdd\n` at1934 and ending through `end TunedAdd\n` at2297, immediately before the FastMul explanatory block. Zero-based UTF-8 byte interval **[79586,95110)**,15524B, SHA `04f2b622654ce1c70972fa600a27736339b74129a8cd5ca38c922cca6cef9743`. This removes40 declarations, including its private copies of rounding/log2/word-add proofs and TunedAdd.add/add_spec. No surrounding namespace closure is removed. The preceding descriptive comment is not counted as reclaimed capacity; preserve attribution even if later editing obsolete explanatory prose.

There are exactly two external qualified references to TunedAdd in this exact source:

| Source line | Existing reference | Minimum replacement |
|---|---|---|
|3266|`else TunedAdd.add x y`|`else ExecFloat.add x y`|
|3281|`exact TunedAdd.add_spec x y`|`exact ExecFloat.Proof.add_eq_spec x y`|

The new slow proof target is simply `ExecFloat.add x y = ExecFloat.Spec.add x y`. The existing fast branch already uses that exact theorem at3280. Submission.add_spec's statement and Submission.add_eq at3314–3317 stay unchanged, so sum/BMM/replay consumers keep their existing public bridge. No new NaN/rounding theorem is required for this change.

The runtime identifier grows by1B and the proof identifier by10B. Size arithmetic gives237142−15524+11=**221629B**, with34371B below256000. This is arithmetic on exact byte spans, not a written or compiled candidate. A future combination must independently verify the same block SHA and references; its size cannot be inferred from a066 alone.

The request mentions two native scalar adds. In exact a066, only **one source fallback directly names TunedAdd.add** (3266), plus its one proof reference. TunedAdd.add itself is the old pure word implementation. There is no second distinct native scalar add declaration directly consuming this namespace. Generated C has multiple inlined copies of the single Submission.add wrapper; all must be inspected after a future edit, rather than editing only one generated call site.

## What must remain

- FastMul has its **own37 declarations**, including sx/sr/fastLog2/rse/rseAny/mkW/roundP/Fmt/Plan/Fam/word32 and its own correctness chain. Its shared-looking names resolve inside FastMul, not TunedAdd. LowScale explicitly consumes FastMul.rseAny/mkW/roundP/fastLog2/core/mul/spec at2635–2721. Do not delete or deduplicate this multiplication chain as part of the capacity edit.
- Actual native bridges are NativeBridge and R7Native (there is no namespace NativeAdd here). R7Native.ofFloat32Add remains needed by native add at3278, other native/canonical bridges at3870/4904 and NativeFinal.sumLoop/dotLoop proofs at5146/5190. Multiplication also consumes NativeBridge/R7Native. Keep them.
- R2W01b/R2W01c decoder/table machinery remains used by the finite native add and native sum/BMM decoding; the raw fallback replacement does not make it dead.
- R7NaNReplay and R7SinglePassSum continue to use Submission.add_eq/mul_eq, including5028/5054/5220 and6327. They do not name TunedAdd directly. Their runtime calls can change through the exported add wrapper even though their proofs/interfaces remain unchanged.

The removed namespace has only inline declaration attributes: no instance, global simp attribute, notation, macro, export or open-TunedAdd registration was found. Outside it, all occurrences are precisely the two references above. This is strong static closure evidence, **not Lean elaboration/kernel acceptance**; any hidden name-resolution/elaboration dependence remains falsifiable by the original statement build.

## Actual code generation and specials risk

914's captured28af source has the exact same961B Submission.add+add_spec fragment as a066, SHA `f36ef5737f0be6697f8137214557ac9e254f8b388ca636c8e83c32d161884b45`, so its existing C/asm is a concrete before image for this scalar route. C26391–26518 computes the native result, tests self-BEq at26418, and calls TunedAdd.add only on the NaN-result branch at26422. Actual add asm17 lines379–394 shows addss/ucomiss, a parity branch and a tail jump to TunedAdd.add. The compiler has **not eliminated that function**: nm reports TunedAdd.add size0x8c0, alongside the225B exported add. No future edited binary has been inspected.

TunedAdd.add's C16268–18690 still contains the word-add core and its special test. Its special branch at18678–18686 reaches the certified software backend corresponding to the source's ExecFloat.add. Under ordinary IEEE binary32 addition, a genuine NaN result arises from a NaN input or opposite infinities, which already satisfy the old special guard. Thus skipping that guard is a plausible simplification, **not a reason to assume the generic path is free or equally fast**. The capacity proof does not depend on proving this branch-frequency inference.

The generated C also contains TunedAdd.add calls inside referenceSum/referenceBmm, R7SumRepair.step, R7NaNReplay.replayStep/replayLoop and R7SinglePassSum's Nat/USize loops. Some retained helpers may not be the timed entry; call presence is not execution count. The edit may affect special repair cost in more than the exported scalar add. Original generic arithmetic/codec conversions still cost time, and new inlining/layout can change even when finite source expressions are retained.

Actual914 a066 full-cell exposure illustrates the risk: add:specials13,047,257ns (5.9901% whole), sum:specials4,099,315ns (1.8820%), bmm:specials5,141,985ns (2.3607%). These are complete-cell sums including all paths, **not fallback-only costs or a complete bound on fallback exposure**; other cells can encounter invalid intermediate results. No call/hit count or preparation/replay profile was captured. Use these only to reject the assumption that a “cold” branch is automatically negligible.

## Smallest falsification/validation sequence

If Root later needs the15.5KB, make one isolated source transformation: the two exact replacements and the one exact namespace deletion. Keep finite add expressions, four exported interfaces, multiplication, sum/BMM dispatch, decoder and all notices unchanged. First run the original current statement/kernel/axiom checks: this immediately tests whether the static dependency closure is real. Then run the complete fixed public suite with identical control, including specials, and a clean frozen confirmation if selected. Inspect the new actual add and repair call sites; the expected capacity saving is independent of any timing gain.

Targeted semantic witnesses should retain both signaling-NaN priorities, two quiet payloads/signs, ±Inf cancellation/invalid result, -0+-0, +0+-0, minimum subnormal cancellation and finite overflow to infinity. They help expose wiring mistakes but cannot replace the original all-input proof/full gate. New integration Lean/fullgate/codegen/performance are all NOT_RUN. There is no mathematical blocker found, but this direction should remain capacity preparation until current16/17 validation finishes.
