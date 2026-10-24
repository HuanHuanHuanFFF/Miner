# R11-W03 pinned Lean runtime/compiler audit

Status: **SOURCE_INSPECTION only; Lean compilation/code generation/assembly/full-call timing NOT_RUN.** No toolchain was installed, no candidate was compiled, and no gate was changed.

Input: extracted `Kernel.lean`, SHA256 `4bdd1e7db35cd85e17d06511721d5dbf7f654ec12e58633264b08a086ec54fa0`, 252609 bytes. All compiler/runtime sources below were downloaded directly from commit `293d5d0c0c3f3dded4688b3ccd6a33939ac5102b`; their exact URL, byte count, and SHA256 are in `primary/manifest.json`. These are source-level conclusions, not facts about an emitted R11 binary.

## Conclusions that change the experiment

1. The current `wordLoop` already passes eight `Float32` accumulators as scalar arguments. The relevant prospective saving is the preparation array plus P12 objects and their traversal/destruction; this is not a first conversion from boxed accumulators to scalar accumulators.
2. A local Lean structure is not a C stack structure. A materialized P12 is one Lean object with twelve raw scalar float fields. It is **not twelve heap Float32 boxes**. F8 and W8 likewise have one scalar-payload object each. If a producer and all projections are inlined, the compiler's projection simplifier can remove the local constructor. If that evidence is missing, assume a constructor can remain.
3. `Vector P12 n` is an Array of pointers to P12 objects after erasure, rather than a contiguous array of 12-float structs. Its size proof does not allocate; the underlying Array does. Eliminating a Vector wrapper has no saving by itself; eliminating its Array and element objects does.
4. `Float32.ofBits` and `toBits` are genuine out-of-line runtime functions in the pinned headers/runtime; they both canonicalize NaNs. `ofBits` is not generally a freely movable identity or a guaranteed one-instruction bitcast at a generated caller. No allocation occurs inside either function's source body.
5. Actual attached `Packed10.finish` calls `result.isNaN`; it does not call the earlier R7W04 self-comparison helper. A non-NaN result takes `ofFloat32`, hence `toBits`. Eight outputs therefore retain eight `isnan` and eight `to_bits` source calls, absent demonstrated interprocedural optimization. Input-conversion-free arithmetic does not mean conversion-free full BMM.
6. A fully applied scalar worker avoids boxing by its direct signature. Partial application, passing it as a higher-order value, or building an escaping continuation can introduce closures and boxed float arguments. A non-inlined helper with many float arguments can spill/pass arguments on the ABI stack; the pinned Lean source alone cannot determine register allocation.

## 1. Exact conversion and arithmetic primitives

Pinned [`src/Init/Data/Float/Float32.lean`](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Float/Float32.lean):

- Lines 43–44 give extern primitives for model conversion.
- Lines 76 and 90 attach `lean_float32_add` and `lean_float32_mul`.
- Lines 132–146 attach `lean_float32_of_bits` / `lean_float32_to_bits`.
- Lines 257–258 attach `lean_float32_isnan`.

Pinned [`src/runtime/object.cpp`](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/runtime/object.cpp):

- Line 1976: `lean_float32_isnan(float)` returns the Boolean result of `isnan`.
- Lines 1987–1993: `lean_float32_of_bits(uint32_t)` obtains a float with `std::bit_cast`, replaces any NaN with `std::numeric_limits<float>::quiet_NaN()`, and returns a C `float`. Source-level no allocation, no Lean RC, no loop.
- Lines 1995–2004: `lean_float32_to_bits(float)` returns exactly `0x7fc00000` for any NaN, otherwise `std::bit_cast<uint32_t>(d)`. Source-level no allocation.

Pinned [`src/include/lean/lean.h`](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/include/lean/lean.h), lines 3253–3257: bit conversion has external declarations only, whereas addition and multiplication have `static inline` bodies using C `a + b` and `a * b`. The distinction makes a call-free add/mul segment plausible without granting call-free decoding. Whether a runtime call is PLT, direct, or optimized through LTO depends on the actual build/link; source inspection does not determine it.

The generated caller can fold a literal zero into a closed initialization or reuse a constant, so count the `Float32.ofBits 0` initialization in emitted code rather than asserting one zero conversion per output or block. Likewise do not infer exact dynamic calls merely by counting textual expressions after inlining/CSE.

## 2. Scalar layout, allocation and RC

Pinned `LCNF/ToImpureType.lean` lines 64–71 maps Float32 and UInt32 to builtin scalar representations. `setCtorLayout`, lines 190–277, assigns each Float32/UInt32 field 4 scalar bytes, places object fields separately, and groups scalar fields by size. These homogeneous structures therefore have source-deducible unrounded layouts:

| Structure | Object fields | Scalar bytes | Logical allocation size on 64-bit |
|---|---:|---:|---:|
| P12 | 0 | 48 | 8-byte header + 48 = 56 bytes |
| F8 | 0 | 32 | 40 bytes |
| W8 | 0 | 32 | 40 bytes |
| Retained F10 | 0 | 40 | 48 bytes |

This does not establish actual allocation counts: elimination, closed constants, reuse, and the allocator affect them. It does establish that a claim of twelve boxed Float32 allocations per P12 is false for a normally materialized constructor.

`LCNF/EmitC.lean` lines 30–43 maps scalar Float32 to C `float`, UInt32 to `uint32_t`, and ordinary structures to `lean_object*`. Lines 575–588 emit `lean_alloc_ctor` for nonempty constructors; projections/stores use the scalar accessors selected at lines 64–81. `lean.h` lines 772–777 allocates header plus pointer slots plus scalar bytes. Lines 847–850 and 882–885 directly load/store scalar `float` fields. No per-field Float32 boxing occurs.

`lean.h` lines 3007–3014 show that an actual boxed Float32 uses a separate constructor object. Lines 2955–2974 show UInt32 boxing is immediate on 64-bit and a small allocation on 32-bit. Thus `Array Float32` and `Array P12` have quite different boxing costs; replacing P12 with an ordinary `Array Float32` is not a packed FP32-array improvement.

`Vector/Basic.lean` lines 32–36 has one relevant Array field and a proof. Lines 320–321 define Vector.ofFn through Array.ofFn. `LCNF/Irrelevant.lean` lines 39–78 recognizes one-relevant-field structures; `ToImpure.lean` lines 134–139 removes their constructors. This removes the Vector wrapper, not its contents. `lean.h` lines 195–202 defines Array as header, size, capacity, and `lean_object*` slots. `Array/Basic.lean` lines 331–338 constructs `ofFn` using `emptyWithCapacity n` and pushes.

If a pack is fully materialized at capacity n, its logical footprint before allocator accounting is `(24+8n)+56n = 24+64n` bytes on 64-bit: 88 bytes for n=1, 152 for n=2, plus F8/output materialization. This is a representation calculation, **not measured allocated bytes, resident bytes, traffic, or timing**. Allocator metadata/rounding and closure/index intermediates may increase it; optimization may reduce it.

`object.cpp` lines 387–393 decrements Array elements during destruction; lines 431–438 traverses only pointer fields in a constructor. A P12 has no pointer children, so destroying it does not recursively decrement twelve float objects. `lean.h` lines 998–1005 offers both reference-incrementing and borrowed Array reads. Which one the candidate uses is determined by compiler borrow inference; do not charge or erase an RC pair on every iteration without emitted-C evidence.

## 3. Inlining and a local P12

Pinned `LCNF/Simp/SimpValue.lean` lines 16–25 directly simplifies projection from a known constructor to its supplied field. This is the source mechanism enabling nonescaping `let p : P12 := ...; consume p` to disappear when `consume` is inlined and all projections become visible.

`InlineAttrs.lean` lines 44–60 documents `inline`, `always_inline`, and `macro_inline`; macro-inline is limited to nonrecursive functions. `LCNF/Simp/InlineCandidate.lean` lines 61–108 first rejects ordinary recursive definitions (unless the special inline-if-reduce route applies), then handles always-inline/inline/noinline and partial-application policy. Merely adding an inline annotation to the recursive wordLoop is not a justified bounded unroller. Prefer explicitly bounded n=1/n=2 terms and inspect generated code.

The attached R11 P12 construction, update, dot8 and finish8 helpers are plain definitions; they do not presently carry inline annotations. A proposed localP12 variant has two meanings that must be distinguished:

- **Local P12 surviving as a runtime object:** removes the Vector Array but retains one or two P12 heap constructors. It may help, but is not allocation-free.
- **Local P12 completely scalar-replaced after Lean inlining:** removes both the Array and P12 constructors. It is source-equivalent to scalar lets, but emitted C must confirm absence of the constructors and boxing.

A raw decoder/helper call between k=0 accumulation and k=1 arithmetic can force the live accumulator values to survive call boundaries. To preserve a contiguous conversion-free arithmetic region for n=2, predecode both k slices (or provide already decoded scalar operands) before the eight ordered lane chains. This moves the live-storage burden to inputs and can increase stack/register pressure; no result follows from operation count alone.

## 4. Scalar arguments, closure boundaries and loop lowering

`LCNF/ExplicitBoxing.lean` lines 16–21 says boxed versions serve interpreter/closures. Lines 30–74 generates wrappers with boxed parameters and unboxes scalar arguments. Lines 335–350 distinguishes direct fully applied calls from partial applications and unknown function calls: direct calls use their signature, while partial application/unknown calls boxes arguments as required.

`LCNF/EmitC.lean` lines 485–515 emits scalar function parameters as C scalar types; erased/void arguments are removed as appropriate. It does not emit a multi-field F8 as a by-value C struct. Consequently a direct worker returning F8 ordinarily returns a pointer, unless surrounding inlining removes the constructor.

`EmitC.lean` lines 527–531 identifies self tail calls; lines 725–747 turns them into parameter assignments and `goto _start`. Thus the current wordLoop can use a C loop with eight float locals rather than recursive machine stack growth. This is compiler capability/source inference; R11 emitted C was not available. A source-level scalar argument does not promise a physical register, and a function call with more scalar operands can place arguments on the ABI stack without heap allocation.

## 5. Exact terminal cost and ordering

Attached Kernel lines 5451–5455:

- actual finish guard is `result.isNaN = false`;
- non-NaN branch reconstructs the carrier with `ExecFloat.Binary.ofFloat32`;
- NaN branch replays original raw inputs with `R7NaNReplay.replayEarly`.

Attached lines 6639–6648 call that finish eight times and arrange W8 as `s0,s4,s1,s5,s2,s6,s3,s7`. This is column-major accumulator to row-major word reordering, with no change to a lane's IEEE operation order. `wordAt` and `rowWord` later select a UInt32 and rebuild Binary32 through `ofBits32`, **not** through native Float32.ofBits. Keep raw carrier reconstruction distinct from native float conversion.

The arithmetic segment may have no calls while terminal checks/conversions still require calls. Inlining may eliminate F8 but leave some final float values live across earlier lanes' finish calls; the compiler may store them to stack or retain them in the existing object. This is not necessarily a loss: the only meaningful decision is the complete call, including preparation, final checks, raw fallback, W8/word vector materialization, final output traversal, tails, and destruction.

## Reproduction and limitations

A source download with sandbox network failed, followed by authorized read-only public fetches which succeeded. Initial guessed old compiler paths `IR/EmitC.lean`, `IR/Boxing.lean`, and `LCNF/ToIR.lean` returned HTTP 404; the pinned repository tree identified the current LCNF files. No source from another revision was silently substituted. Pinned Lean executable and Clang22.1.4 were not available in the root environment inventory; compilation and benchmarking remain NOT_RUN.

For a minimal codegen falsification, examine the reachable n=1/n=2 worker in generated C and assembly, not just the standalone unused helper. Require no P12 allocation, no temporary Array, no box_float32/closure/application bridge in the intended bounded path; identify actual input decode calls before the arithmetic segment; verify eight separate ordered `+` of rounded products; inspect terminal and caller spills separately. These checks are prerequisites to, not replacements for, the unchanged official full gate and paired full-call timing.
