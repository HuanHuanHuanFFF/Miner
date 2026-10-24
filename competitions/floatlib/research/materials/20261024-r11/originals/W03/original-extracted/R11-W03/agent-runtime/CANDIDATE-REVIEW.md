# R11-W03 independent short-shared codegen review

**Status: source review only; Lean/codegen/assembly/full-cost measurements NOT_RUN.**

Reviewed `agent-candidates/short-shared.patch` and `short-shared-fragment.lean` against the pinned Lean sources already retained in `agent-runtime/primary`. This review concerns allocation/inlining/scheduling claims, not a claim that the proof script elaborates.

## Supported claims

- On the guarded branch `(n=1 ∨ n=2) ∧ b1=b0 ∧ b2=b0 ∧ b3=b0`, the runtime source has no call to `pack`, no temporary `Vector P12`, and no P12 constructor. It reads 4 A values and 2 B values at n=1; it reads two such slices at n=2. Read32 and shortShared are fully applied and monomorphic; no closure or boxed Float32 is explicitly introduced by these helpers.
- The n=2 expression for every lane is exactly `(z + x*y) + u*v`. The original positive zero addition remains at k=0, multiplication is still separate from addition, and k=0 is before k=1 within each lane. Independent lane scheduling is unconstrained by the semantic specification.
- The helper uses total Nat-indexed getD reads and retains the original finish/raw fallback interface. A raw-index proof assumption has not been substituted for the reads.
- The material difference is removing preparation storage/traversal on a bounded shared-B branch. There is no source argument for speedup until the complete call is measured.

## Claims requiring correction or explicit qualification

### Lexical preload does not enforce machine scheduling

The comment “decode both slices before accumulator arithmetic” describes the source placement of let-bindings. Pure Lean let-bindings are not a volatile sequence or an instruction-scheduling barrier. Lean passes and Clang may reorder independent computations while preserving the per-lane expression graph. They may start a lane before the last independent decode, or complete some lanes before others. Therefore it is not established that the machine code has eight simultaneously live accumulator values, or that all decode calls precede the first accumulator update.

Even if generated C preserves the lexical order, the first decoded operands must survive later out-of-line `lean_float32_of_bits` calls. Saving those input values can use stack memory. If some accumulator updates are hoisted, those values can instead survive calls. A source claim of “no heap P12/Array” can remain valid while “no spills” or “call-free arithmetic interval” fails.

The minimal falsification is inspect the reachable n=2 fast path in final assembly: locate every of_bits call, the first k=0 arithmetic, and k=1 arithmetic; identify memory traffic for decoded inputs versus partial accumulators. An isolated arithmetic helper that is unused by the actual dot8 route is insufficient.

### Terminal F8 remains part of the current interface

`shortShared` returns `F8`, and the patched `dot8` also returns `F8`. `[inline]` on shortShared can expose its body inside dot8, but dot8 remains an ordinary definition. In the ordinary emitted signature F8 is a `lean_object*`; an escaping F8 return materializes one 32-scalar-byte constructor plus header. Current `blockAt` passes this result into `finish8`. If compiler inlining removes that F8, it must be observed; neither the patch nor `[inline]` guarantees it.

The patch does not remove terminal W8 construction, the Vector W8, final flat output construction, or raw NaN replay. Actual `Packed10.finish` retains an out-of-line isNaN check and toBits conversion on its non-NaN branch. Inlining F8 into finish may simply move preservation of other final float results from the object to compiler-selected stack/register storage across those finish calls.

### Local P12 comparison

A local P12 that survives compilation is one 48-byte scalar-payload object, not twelve boxes, and may still incur allocation/destruction. A producer/consumer pair that becomes visible to `SimpValue.simpProj?` can eliminate that object. The shortShared source sidesteps this specific uncertainty by not constructing P12 at all. It does not establish zero allocations for the entire call; F8/W8/output and arbitrary-Nat index arithmetic must be considered separately.

## Scope of inline/noinline attributes in this pinned compiler

- `LCNF/Simp/InlineCandidate.lean:61–108` interprets Lean inline/noinline annotations in the Lean simplifier. Nonrecursive shortShared/read32 are suitable candidates; ordinary recursive wordLoop is not automatically bounded-unrolled by an inline annotation.
- `LCNF/EmitC.lean:485–515, 932–956` emits ordinary C declarations/definitions with `LEAN_EXPORT`, return type and scalar argument types. There is **no noinline/never_inline/inlineAttr/always_inline handling anywhere in this pinned EmitC file**.
- `lean.h` defines a runtime `LEAN_ALWAYS_INLINE` macro, but that fact does not attach a C noinline or always-inline attribute to user functions.

Consequently a proposed Variant B `@[noinline] arith1/arith2` with 7/13 Float32 arguments can prevent Lean-stage inlining and expose a decoder-to-arithmetic function boundary in generated C. It **does not force that boundary to survive Clang22.1.4 -O3**, which may inline the emitted C helper. It also does not promise the ABI argument placement, register allocation, or a persistent stack-scalar architecture. Treat B as an implementable codegen probe whose final structure must be checked, not an enforceable scheduling construction.

## Handoff decision

The bounded shared-B patch is a credible allocation-elimination experiment with exact source-level ordered arithmetic. Its strongest supported wording is “removes explicit P12/Vector preparation on this branch and exposes eight independent ordered lane chains.” The following remain falsifiable targets: no reachable P12/temporary Array allocation in emitted code; no boxed/closure bridge; actual conversion placement; retained or eliminated F8; terminal storage/RC; and complete-call benefit under unchanged gate and timing protocol.
