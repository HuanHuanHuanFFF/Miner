# R11-W03 — independent Clang / full-cost pressure review

Status: **SOURCE_INSPECTED; Lean compilation NOT_RUN; generated C NOT_RUN; Clang compilation NOT_RUN; assembly NOT_RUN; benchmark NOT_RUN; performance UNKNOWN.**

Input: exact extracted `Kernel.lean`, SHA256 `4bdd1e7db35cd85e17d06511721d5dbf7f654ec12e58633264b08a086ec54fa0`, 252609 bytes. This is an architectural/cost review, not an accepted candidate. No original source, gate, confirmation input, or benchmark configuration was changed. No substitute compiler was used.

## Decision

The two mechanisms are materially different:

1. **n=1 / n=2 bounded staging and unrolling:** convert all operands for the tile before the arithmetic, pass typed scalar `Float32` values to the arithmetic helper or keep them as local lets, execute eight independent ordered chains, finish through the existing exact `finish8`. There is no logical need to construct `Vector P12`. This trades per-tile packet-array/object lifetime for fixed scalar argument/stack traffic. It can be tested without introducing a new storage primitive, foreign code, new compiler API, changed IEEE operations, or changing the output writer. It is the stronger first experiment.
2. **Direct raw gather inside the k-loop:** remove `Vector P12`, but perform actual raw-to-Float32 conversions during each k iteration while eight accumulated values remain live. This removes packing allocations but reintroduces the call barrier that the prepacked loop removed. It is a distinct diagnostic comparator, not a proven faster implementation. Under the ordinary x86-64 SysV ABI, an opaque conversion call does not preserve XMM registers; this makes accumulator saves/reloads a concrete concern.

The first candidate does **not** imply all operands or all accumulators stay in registers. The first eight scalar float arguments use XMM0–XMM7 in the usual SysV x86-64 C ABI; additional scalar float arguments are passed in 8-byte stack slots. Local typed scalars avoid Lean heap boxing but are still subject to register allocation. For n=2, 12 shared-case or 24 general-case input values may exist before any eight-lane arithmetic begins. Holding them across the later conversion calls already imposes call-boundary storage. The useful claim to test is allocation elimination and absence of conversion calls *inside the eight-lane arithmetic region*, not absence of stack traffic everywhere.

## Exact attached source anchors

- `Kernel.lean:6404–6436`: `P12` has twelve `Float32` fields, `F8` eight `Float32`, `W8` eight `UInt32`.
- `6475–6520`: current `packGeneral` and `packShared`. Per k, general pack explicitly decodes four A and eight B words; shared pack explicitly decodes four A and two B words. All-four-equal B bases are required for the shared branch. This source count excludes `ofBits 0` initialization, terminal conversion, fallback, and possible common-subexpression/compiler changes.
- `6526–6529`: the shared-vs-general branch is outside the per-k packet producer.
- `6577–6587`: `wordLoop` already carries eight scalar accumulator parameters; its body reads one P12 and does eight multiplication/addition updates. It creates an F8 only at exit at the source level.
- `6608–6615`: `dot8` creates the pack before `wordLoop`.
- `6639–6648`: `finish8` applies existing `Packed10.finish` eight times and permutes column-major native lanes to row-major words.
- `5450–5454`: `Packed10.finish` uses `result.isNaN`, then native `ofFloat32` for non-NaN, otherwise original `R7NaNReplay.replayEarly`.
- `6679–6687`: `blockRows` computes each flattened row's own B base from `r/m`.
- `6697–6738`: group/tail reconstruction and flat `Vector.ofFn` output stay in the whole-call cost.

These statements are source inspection. They do not certify the current R11 namespace elaborates or generates the intended code.

## Fixed LLVM 22.1.4 primary-source findings

All source URLs below bind to `llvmorg-22.1.4`, and exact fetched SHA256/byte counts are retained in the `sources-*.json` records. Initial browser fetches failed; successful reads used a separately approved, read-only public source fetch. No files were executed. Documentation labeled 22.1.0 was also read through the browser, but conclusions below use the exact patch-tag files wherever possible.

### Enabled optimizations are opportunities, not promises

`clang/lib/Driver/ToolChains/CommonArgs.cpp:3342–3388` selects loop and SLP vectorizers at numeric optimization levels greater than 1, subject to explicit overriding flags. Thus ordinary `-O3` enables the two candidate passes.

Source: <https://github.com/llvm/llvm-project/blob/llvmorg-22.1.4/clang/lib/Driver/ToolChains/CommonArgs.cpp#L3342-L3388>

`llvm/lib/Passes/PassBuilderPipelines.cpp:1322–1323,1394–1420` schedules the loop vectorizer and the SLP pass under its tuning flag. SLP is described as optimizing parallel scalar instruction chains. This does not mean an arbitrary eight-field Lean structure becomes two SSE instructions: Clang sees emitted C/LLVM IR, including remaining allocations, calls, aliasing, control flow, and memory operations.

Source: <https://github.com/llvm/llvm-project/blob/llvmorg-22.1.4/llvm/lib/Passes/PassBuilderPipelines.cpp#L1316-L1422>

`llvm/docs/Vectorizers.rst:8–16,469–499` distinguishes loop widening from combining independent scalar operations. Eight distinct outputs can be grouped into vectors at the same k without changing the order within any output's reduction. Widening k by accumulating partial sums and reducing them later changes the mathematical computation and is forbidden here.

Source: <https://github.com/llvm/llvm-project/blob/llvmorg-22.1.4/llvm/docs/Vectorizers.rst#L469-L499>

### FP constraints

`clang/docs/UsersManual.rst:1746–1774`: `-ffp-contract=off` disables contraction. `1801–1811` retains signed zeros and disables associative-math transformations by default. The default precise mode is round-to-nearest with exceptions ignored; it is not a blanket `fenv` or raw-NaN-payload contract.

Source: <https://github.com/llvm/llvm-project/blob/llvmorg-22.1.4/clang/docs/UsersManual.rst#L1746-L1811>

`llvm/docs/Vectorizers.rst:203–215` explains why common floating reductions require reordering permission, with limited ordered-reduction exceptions on some targets. That rule concerns reduction across k, not packing independent rows/columns. No fast-math flag, FMA pragma, or reassociation flag is needed or allowed for the independent-lane proposal.

Source: <https://github.com/llvm/llvm-project/blob/llvmorg-22.1.4/llvm/docs/Vectorizers.rst#L203-L215>

`UsersManual.rst:1593–1598,2084–2092` explicitly warns that denormal behavior cannot be deduced only from fp-model; MXCSR FTZ/DAZ can be changed globally, and `crtfastmath.o` can set them. Preserve the official invocation/runtime environment; `-ffp-contract=off` alone does not prove gradual subnormals. This is a verification boundary, not a request to change official flags.

Source: <https://github.com/llvm/llvm-project/blob/llvmorg-22.1.4/clang/docs/UsersManual.rst#L2084-L2092>

### No AVX inference from eight floats

`clang/lib/Driver/ToolChains/Arch/X86.cpp:22–34,69–104,132–140`: host CPU discovery is tied to `-march=native`; ordinary Linux x86-64 without a specified CPU selects `x86-64`. Target options, defaults, configuration files, and function target attributes still matter. The absence of `-march=native` alone does not establish the complete target feature set; record the full compiler argv and `-###` output. Under the baseline x86-64 target, SSE-width grouping is plausible, while AVX/YMM generation is not justified merely by writing eight scalars.

Source: <https://github.com/llvm/llvm-project/blob/llvmorg-22.1.4/clang/lib/Driver/ToolChains/Arch/X86.cpp#L22-L140>

### Scalar ABI and calls

`llvm/lib/Target/X86/X86CallingConv.td:570–599` assigns the first eight f32/f64 arguments to XMM0–XMM7 and remaining scalar floating arguments to 8-byte stack slots. `1123–1124` defines ordinary `CSR_64` using integer callee-saved registers only. These findings apply to ordinary SysV x86-64 C calls, not every target or every specialized internal calling convention. Inlining or whole-program visibility can eliminate some call-boundary costs; opaque external/runtime calls cannot be assumed to do so.

Source: <https://github.com/llvm/llvm-project/blob/llvmorg-22.1.4/llvm/lib/Target/X86/X86CallingConv.td#L570-L599>

Source: <https://github.com/llvm/llvm-project/blob/llvmorg-22.1.4/llvm/lib/Target/X86/X86CallingConv.td#L1119-L1135>

Consequence: `@[inline]` on a Lean staging helper must be verified at the Lean-generated-C boundary. C compiler inlining is a second decision. Merely marking a wrapper inline does not inline the body of a runtime function supplied from another object/shared library. Keeping eight accumulators as source parameters is necessary for a good loop shape, but conversion calls inside the loop can still force their values to be saved across each call. Similarly the first terminal `isNaN`/`toBits`/replay call can force storage of the seven other finished lane values. This is terminal O(1)-per-tile overhead rather than k-fold overhead, and it remains relevant for n=1/2.

## Whole-call cost comparison

Let R=batch*m, G=ceil(R/4), q_g=6 for a same-B-base tile and q_g=12 otherwise. Exact source-level pack conversion count is n*sum(q_g). All candidates retain 8n multiply/add updates per computed tile, including unused tail rows, unless a separately proved tail specialization is added.

| Cost component | Existing localP12 | Bounded n1/n2 scalar staging | Direct raw gather loop |
|---|---|---|---|
| Raw input conversion count | 6n or12n per tile | same if sharing branch retained | same if sharing branch retained |
| Conversion placement | before live accumulator loop | before fully unrolled arithmetic | inside k-loop while acc live |
| Per-k P12 objects and packet vector | present in source | absent by construction | absent by construction |
| Input scalar storage | P12 payloads, pointer array | registers or ABI/local stack | raw arrays + current operands |
| Eight ordered accumulator chains | existing | exact fixed n expansion | recursive scalar argument loop |
| Terminal F8/W8 and finishing | present | retained unless proven scalarized | retained |
| B base arithmetic, cross-batch mapping | existing | retained | retained |
| Raw replay on terminal NaN | existing | retained | retained |
| Tail and final vector construction | existing | retained | retained |
| True performance | UNKNOWN for exact R11 | UNKNOWN | UNKNOWN |

The source-level packet allocation removal is a new mechanism relative to the older two-row x4/x8 SIMD trials. Those old results already establish that SIMD and no hot spills are insufficient for adoption. The new candidate needs evidence that avoided packet construction/destruction exceeds added stack transport, extra branches, code size, and unchanged terminal/output costs. Any claim that wider arithmetic alone is the result is invalid.

Old n2p2 exposure14.81% is one seed/group observation from the provided context. It is neither a new workload weight, a recoverable fraction of the call, nor a predicted speedup. The source-level counts above contain no time conversion. The old negative bootstrap outcome of the n1 product/-0 correction proposal does not mathematically rule out a different allocation-removing candidate, but it is evidence that a fresh local gain must survive the unchanged full-call test.

## Smallest falsification plan

### A. Code generation before timing

1. Use the exact supplied Kernel SHA and the local actor's actual pinned Lean4.34/FloatLib/competition workspace. Record Lean executable version, commit, hashes; Clang version and executable hash; actual compiler argv/target; header/runtime archive hashes; dynamic versus static linkage. If missing, stop with NOT_RUN; no toolchain substitution.
2. Emit C for the unmodified R11 control and one bounded candidate. Do not silently treat the uncompiled R11 parent as a working control. Also preserve the retained accepted benchmark control for eventual full tests.
3. From the active specialized entry, follow its reachable C helper graph. Do not grep the whole source and call every occurrence of `P12` active; old functions may remain in the file but be unreachable.
4. On that path, reject the hypothesis if a packet `Array`/`Vector` is still allocated or P12 constructors survive in the bounded branch. Distinguish allocations caused by actual packet preparation from remaining F8/W8/Binary32/output constructors.
5. Mark the region from the last input decode to the first exact finish. Verify no raw `of_bits` conversion calls remain in that region, eight independent accumulator chains remain, separate multiplication/addition is emitted, and no horizontal reduction/FMA/reassociation appears. Do not require every register value to stay off the stack.
6. Inspect final object/disassembly plus relocation/call targets, not only C. Count calls within the actual path; record stack frame size, argument stores, spills/reloads around conversions and finishing, loop backedges, allocation/free calls, native output bit conversion calls, and raw replay branches. The lack of literal `isnan` in assembly can be legitimate inlining; resolve the relevant C/header body rather than treating a missing symbol as zero cost.
7. Keep original flags. A separate diagnostic compile may add `-Rpass=slp-vectorizer`, `-Rpass-missed=slp-vectorizer`, `-Rpass-analysis=slp-vectorizer`, plus analogous `loop-vectorize` and `inline` remarks, and `-fsave-optimization-record`. Diagnostic remarks are only reasons; emitted code is the evidence. No `-march=native`, force-vector-width, new AVX flags, or fast-math.
8. Optionally compare only the directrawgather branch against the bounded branch to discriminate allocation cost from conversion-call liveness cost. If calls remain hot and every k spills all accumulators, report that shape; do not extrapolate cycles from an instruction count.

### B. Exactness / boundaries

Use original spec/gate and raw words, not host float decimal formatting. Include n1/n2 cases below and dimensions:

- n=1,2; p=2; R=4 full group, R=5/6/7 tail groups.
- batch1,m4 (shared B), batch2,m3 (cross-batch plus tail), batch3,m2 (two B bases per full tile), batch4,m1 (four B bases), and a large public shape such as the already described batch2941,m15,n2,p2 **with newly synthetic public inputs**, never final confirmation inputs.
- n=0,p=0,m=0,batch=0, p!=2, R<4 must retain their actual fallback behavior. Unreachable fast-path proofs do not permit replacing the general bmm theorem's domain.
- arbitrary Nat index proofs stay necessary even when runtime tests use small shapes. A bound on total lengths does not automatically bound speculative tail indices. Keep `getD` total reads unless a separately proved exact machine-index bound covers each read.

Full accepted proof/spec/audit gate remains mandatory. Finite cases only falsify errors.

### C. Full cost

The first timing discriminator can be a development measurement for the chosen n1/n2 shapes, using the original entire BMM call including its preparation, pointer arrays, packet destruction, terminal F8/W8 conversion, NaN replay, tail work, output vector construction, and output consumption/lifetime as defined by the unchanged harness. A prepared-only arithmetic benchmark can diagnose codegen but cannot decide adoption.

Freeze candidate and controls before running the original 25 paired full timing rounds, checksum tests, exact four specs, statement build, replay, and axiom audit. Preserve raw per-round/per-case records and the preselected aggregation/uncertainty rule. Include n>2 and shapes routed to fallback so dispatch/code-size costs are visible. Do not choose candidate, group weights, or inputs based on final confirmation results. Without those records, measured gains remain UNKNOWN.

## Concrete negative boundaries

### Removing the initial +0 is not valid even at n1

For `a=0x80000000` (-0), `b=0x3f800000` (+1), product is -0. The required operation is `RN(+0 + RN(-0*1))`, which is +0 under RN-even. Returning the product yields raw `0x80000000`; the required result is `0x00000000`. This is a mathematical IEEE witness, not a newly run test.

For n2 with both products -0, the required two steps still give +0; a direct sum of the products can give -0. Fixed unrolling must retain the exact initial add rather than assume it is algebraically redundant.

### FMA changes n2

One output's A words `[0xbf800000,0x3f800001]`, B words `[0x3f800000,0x3f7ffffe]` represent `[-1,1+2^-23]` and `[1,1-2^-23]`. The first ordered accumulation is -1. The second exact product is `1-2^-46`, which rounds to 1. Separate multiply then add gives +0. Fusing the second multiply/add computes exactly `-2^-46`, raw `0xa8800000`. The separate ordered expected result is `0x00000000`.

### Native final bits are insufficient on NaN

The existing `finish8` needs original A/B words because native input conversions/canonicalization and arithmetic do not preserve the competition's raw signaling priority/payload selection. Two otherwise identical NaN input matrices with different raw payloads can have identical native `Float32` intermediates but different exact final words. Preserve original raw arrays and original `Packed10.finish`/`replayEarly`; n1/n2 unrolling does not remove this obligation. The exact payload expectations must come from the attached Spec, not a guessed host NaN convention.

### Shared B and tail assumptions are local

Within flattened four-row groups, m1/m2/m3 can cross batches. Reusing one B pair for all rows merely because p=2 is wrong. Shared decoding is justified only by equality of the four *actual* B bases, or an equivalent proven relation.

The ceil grouping computes up to three unused rows. Total `getD` semantics return positive zero out of range. A replacement `uget` or raw pointer read is not equivalent merely because retained output rows are valid. Extra tail index `r*n` can exceed a machine maximum even if true array size is below it. Keep Nat/total-read behavior or separately prove bounds/dispatch; do not silently wrap USize.

### Higher-order closure and large unroll boundaries

Typed local scalars alone are not a promise of stack allocation: a captured Float32 inside a surviving closure, generic `Array Float32`, or escaping structure can allocate/box. A continuation-based interface must be fully specialized/inlined before claiming zero temporary allocation. Avoid scaling the bounded expansion beyond n2 without a fresh code size/register pressure measurement. Remaining submission budget is 3391 bytes before any deletions, so adding a large theorem/duplicated finish body can violate the256000 byte limit even if runtime code is good.

## Source fetch records and reproduction scope

Exact patch-tag source records: `sources-escalated.json`, `sources-extra.json`, `sources-commonargs.json`. `sources.json` records the initial restricted-network failure only. No Lean toolchain or Clang compiler was downloaded, installed, built, or run.

The primary documents corroborate compiler mechanisms and ABI constraints. They do not prove what this exact Lean fragment emits; that requires the pinned compiler experiment above. The report deliberately does not convert source or instruction counts into cycles, microseconds, or a gain estimate.

## Adversarial review of the concrete proposed patch

Reviewed `agent-candidates/short-shared.patch` after its production. Candidate source size reported by the producing agent:254458 bytes, +1849 over the exact252609-byte parent, leaving1542 bytes under256000; these are source sizes, not binary code-size predictions. The report's broader bounded staging discussion above includes general tiles for comparison, but **this concrete patch specializes only shared-B tiles**. Mixed-B tiles retain original localP12 exactly on their arithmetic/preparation branch.

The patch adds typed `read32`, inline `shortShared`, and an n1/n2 plus four-base-equality branch in `dot8`. The finite helper explicitly retains `z + product` at k0 and adds the k1 product to that result at n2. It retains p in `b0+p`, so its mathematical lane theorem can hold for arbitrary p even though the BMM fast path enters at p2. `shortShared` itself computes two steps for all n!=1; this is acceptable only because its actual caller and theorem require n=1 or n=2. No global all-n equivalence may be claimed for that helper.

No source-level semantic mismatch was found: its A/B `getD` reads are the same total Nat-indexed reads as `packShared`, all B base equalities are checked, and the tail/cross-batch routing remains under the original wrappers. It retains the existing `dot8_lane` statement and exact `finish8`/`blockRows`/`rowWord` path. This is a pressure review by source inspection, not Lean acceptance.

Three concrete remaining code-generation risks should decide the first diagnostic:

1. **Source staging versus emitted scheduling.** Twelve n2 operand lets occur before the first of eight s-values, but neither Lean optimization nor Clang must preserve that textual ordering for pure/value-safe operations. Source order does not certify the conversion-free machine arithmetic region. Record the first arithmetic operation, every conversion call, and whether partially computed accumulators survive across a call.
2. **Input storage versus accumulator storage.** If all input conversions do execute first, earlier x/y values still survive later conversion calls. Saves/reloads of these staged operands are expected candidates for stack traffic; classify them separately from saves/reloads of s0–s7. For example, an XMM store immediately before an `of_bits` call may preserve a predecoded operand, not a reduction accumulator. Either can cost time, but only the second falsifies the intended live-accumulator boundary.
3. **Terminal boundary and fallback tax.** Returning F8 to existing finish8 leaves possible terminal F8 allocation, eight sequential finish calls, W8 construction and final output reconstruction. The new guard executes for all dot8 calls; n>2 or mixed-B groups fall through and still perform the existing pack shared-base test. Preserve these costs in the full comparison, even if selected shared n2 tiles improve.

For the already described shape batch2941,m15,n2,p2, the parent independently counted R44115, G11029, shared8823, mixed2206, one unused tail row. This is combinatorial coverage of this exact shared predicate, not a time split or recoverable-speedup bound. The actual mixed/shared costs need not be proportional to their counts; mixed packing doubles the declared per-k decode count. The shared short path's opportunity is therefore narrower than the old group exposure14.81%, even before unmodified finishing/output costs are considered.

## Scalar-call variant and Lean noinline boundary

The parent/runtime audit identified, and this reviewer directly checked, pinned Lean `src/Lean/Compiler/LCNF/EmitC.lean:932–956`: ordinary generated function declarations use `LEAN_EXPORT` and the emitted C signature; this path does not emit a C `noinline` attribute. Lean `@[noinline]` is a Lean inlining control. **It does not guarantee that the later Clang optimization preserves a function-call boundary.**

The added `short-scalar-call` variant therefore provides a Lean-stage arithmetic boundary with seven `Float32` arguments at n1 and thirteen at n2 (including the supplied z). If an ordinary SysV x86-64 out-of-line C call survives, n1's seven floats fit the eight FP argument registers; n2's thirteen imply five stack-passed scalar float arguments under the standard convention. These are conditional ABI predictions, not measured stack operations in this candidate. Clang may inline the helper, eliminate a parameter, or use an optimized internal call shape; inspect emitted C and final assembly before assigning that model.

This distinction is precisely what makes the two variants a useful small codegen experiment. A Lean-stage boundary can expose pure arithmetic to its own optimization, while an inline variant can allow C-level optimization across staging and arithmetic. If final machine code converges, they are not distinct machine mechanisms despite distinct Lean definitions. Do not use foreign code, noinline C annotations, modified compiler flags, or gate changes to force the intended distinction. Keep the declared NOT_RUN status until the actual pinned compiler runs.
