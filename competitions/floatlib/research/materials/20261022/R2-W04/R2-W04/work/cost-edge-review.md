# R2-W04 independent semantic and complete-cost review

## Scope and evidence

This review uses the exact downloaded parent `Kernel.parent.lean` and the pinned Lean `v4.34.0` runtime sources, plus a finite symbolic model created for this request. It does not use prior discussions, private files, device observations, or performance surrogates. It does not execute Lean or emulate floating-point conversions.

Parent identity, verified by the main executor: 64,087 UTF-8 bytes, SHA256 `5be0735a90d58d9efb8ee2c6d666c11029bca66665dca03b6b5eff5baf6cbfc4`.

The supplied parent gate result and approximately `0.09633 ×` official-reference bmm time remain user-provided parent feedback. They establish no candidate timing or candidate acceptance result.

## 1. Semantic obligations that cannot be replaced by size equality

A successful preparation must establish two independent facts:

1. The resulting FloatArray has the original input length.
2. For every in-range position, narrowing the actual stored Float and importing it to Binary32 yields the original raw word.

The loop invariant must relate the current output to the processed original prefix, not merely assert its length. A useful statement is `out.size = k` together with equality for each index below `k`, where the latter compares the imported narrowed stored value with `xs[i]` or its equal `getD` expression.

The step must compute `d = encode xs[k]` once, compare the raw imported narrowing of that `d` with the original word, and then push that same `d`. The check theorem follows by raw-word extensionality. It assumes nothing about the opaque widening or narrowing functions. The push proof requires both preservation of every old position and the new final position's equality to `d`.

A theorem whose premise is `prepare xs = some out` can then derive the full all-index reading equality required by the unchanged `dot_eq`. At `i >= xs.size`, the successful-length theorem makes the FloatArray branch out of bounds as well; its unchanged `read` returns `Float32.ofBits 0`, whose Binary32 import is the parent positive zero. Returning negative zero would not satisfy this contract.

### Negative cases

Using numerical Float equality would not be sufficient: the raw words `00000000` and `80000000` are different even when numerical equality equates their values. NaN equality is also unsuitable for establishing preservation of its sign, quiet/signaling bit, or payload. Likewise, checking an independently recomputed encoding would leave an unnecessary proof/dataflow issue; the required implementation stores the already checked `d`.

The existence of a successful checked path must not be strengthened into an unconditional roundtrip identity. Actual conversions may reject an input. Fallback is the mechanism preserving the all-input contract in that case.

## 2. A/B evaluation and fallback

The new bmm wrapper should use nested matches in this order:

- Prepare A. On `none`, call `originalBmm batch m n p A B` immediately.
- Only after A returns `some AF`, prepare B. On `none`, call that same `originalBmm` with the original A and B.
- Only when both succeed, pass AF/BF and their proven all-index reading equalities to the unchanged checked dot path.

No prefix array or prepared input is a substitute for an original fallback operand. When B fails, AF is disposable preparation work; it must not change the fallback operands or exact fold. The final nonfinite checked-dot guard and its exact raw-input fold remain necessary even after input preparation succeeds.

## 3. Zero-size and boundary cases

| Case | Required consequence |
|---|---|
| Empty input to prepare | Return `some` with size zero; no element conversion or check. |
| Read at the successful size or above | Both sides return exact positive zero. |
| `batch = 0` | Both input lengths and output length are zero. |
| `n = 0`, nonzero output length | Both input arrays are empty; every unchanged dot starts and ends at positive zero. |
| `m = 0` | Output is empty, A is empty, and B can still be nonempty. The wrapper may still prepare B. |
| `p = 0` | Output is empty, B is empty, and A can still be nonempty. The wrapper may still prepare A. |
| A's first element fails | Allocate A's output capacity, check that element, return immediately; do not evaluate B preparation. |
| A's last element fails | The stored prefix is discarded, original A/B fallback remains exact. |
| B's first/last element fails | Fully prepared A and B's prefix are discarded; use original A/B. |

No dimension or equal-length shortcut proves the element equality obligation. The optimization should not introduce a new policy for skipping all preparation merely because the output is empty: that is outside the requested change.

## 4. Source operation counts and failure costs

Let `a = A.size`, `b = B.size`, and `S = a + b`. These are source-level counts; no cycles or elapsed times are inferred.

### Both preparations succeed

| Item | Parent | Fused candidate |
|---|---:|---:|
| `encode` evaluations | `2S` | `S` |
| Checked narrow/import/raw comparison | `S` | `S` |
| Intermediate mapped `Array Float` elements | `S` | `0` |
| FloatArray payload elements stored | `S` | `S` |
| Preparation traversals per input | check; map; constructor conversion | one checked push traversal |
| Option-like results | not used | one terminal `some` per input |

The stored FloatArray payload contains `8S` bytes of scalar double data, excluding headers, alignment, and allocator behavior. That payload remains; this change removes the explicit pointer-array/boxed-Float intermediate path. The ordinary Binary32 input representation and conversion/check intermediates are not claimed to become allocation-free.

The parent uses `Array.map encode` and the FloatArray constructor after the checks. The pinned runtime constructor allocates the scalar array and loops over the input pointer array, unboxing each double. An optimizing compiler's exact emitted behavior must still be inspected before assigning a concrete allocation count to the parent compiled candidate.

### A fails at zero-based position f

Both structures evaluate encoding/checking for `f + 1` A elements and do not need B preparation. The fused structure additionally requests A's full output capacity and stores `f` passing values before discarding the output. The parent performs no FloatArray preparation on this failed condition.

### A passes, B fails at zero-based position g

Both structures evaluate encoding/checking for `a + g + 1` elements. The fused structure has also reserved A/B output capacity and stored `a + g` values. The parent has not entered either FloatArray preparation. Thus the fused path can lose on failure-heavy inputs. Reduced success-path conversion count is not a proof of lower full-call cost.

The exact complete-call difference is therefore a balance between saved successful-path encoding, pointer-array construction, Float boxing and constructor conversion, and the new per-push capacity/exclusivity checks, terminal Option handling, loop control, allocation timing, and wasted failed-prefix preparation. The unchanged dot arithmetic and its final fallback costs still belong to every bmm timing.

## 5. Expected generated C shape and a concrete copy hazard

Pinned runtime evidence:

- `src/runtime/object.cpp`, `lean_float_array_mk`: allocate scalar storage; loop over pointer Array and `lean_unbox_float` each element; release the Array.
- `src/runtime/object.cpp`, `lean_float_array_data`: allocate pointer Array and `lean_box_float` every stored double. A runtime call to this function would undo the intended optimization.
- `src/runtime/object.cpp`, `lean_float_array_push`: check capacity and exclusivity, store one double, increment size.
- `src/include/lean/lean.h`, `lean_mk_empty_float_array`: allocate scalar storage with requested capacity and size zero.
- `src/include/lean/lean.h`, `lean_float_array_fget`: return the stored double directly.

Source URLs:

- https://github.com/leanprover/lean4/blob/v4.34.0/src/runtime/object.cpp
- https://github.com/leanprover/lean4/blob/v4.34.0/src/include/lean/lean.h

Downloaded source SHA256 values:

- `src_runtime_object.cpp`: `b53499ae7db8ed722a489ae5a79a394b93f6fda2e6663a3784d886867583985a`
- `src_include_lean_lean.h`: `982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13`

The desired C structure is one tail-recursive/iterative preparation loop with independent index and owned output arguments, a double temporary reused by the check and push, one terminal `some`, and immediate `none` on failure. There should be no generated call to FloatArray `.data`, no Array-of-Float map, and no encoded double boxed solely for storage in that intermediate array.

Preallocation prevents capacity growth if the output performs at most the input length's number of pushes. It does not by itself prove that push avoids copying. The runtime copies a scalar array when its reference is shared. Erased prefix proofs must not leave executable references retaining prior outputs, and generated code must transfer the current `out` into the recursive push rather than keeping a second live ownership reference. Inspecting generated C is the practical check. The expected unique-ownership loop permits in-place push; it is not a measured property here.

## 6. Finite symbolic checks executed

`symbolic_prepare_model.py` replaces the opaque encode/narrow/import composite with a pure arbitrary raw-word oracle. It checks control flow and invariant bookkeeping without asserting a floating-point identity. Python object identity verifies that the checked encoded token is the stored token. This is a deliberately limited model, not generated C, Lean execution, a floating-point emulator, or numerical/performance acceptance evidence.

Executed results:

- 24,992 preparation cases over all arrays of length zero through four from a five-word alphabet and all 32 selected rejection oracles.
- 12,800 paired A/B short-circuit cases, verifying no B preparation after A failure and identity of both original fallback operands.
- 81 dimension-bookkeeping combinations with `batch,m,n,p` in zero through two.
- Negative-word examples rejecting modeled negative-zero collapse, NaN payload canonicalization, and minimum-subnormal flushing.
- Prefix size/content and push preservation checked at every modeled step; successful reads include in-range positions, the first three out-of-range positions, and index `2^32`.

All finite checks passed. These results do not determine which special words the fixed Lean conversion actually accepts.

Reproduce locally with `python3 symbolic_prepare_model.py`. The result is written to `symbolic_prepare_results.json`.

## 7. Single minimal real validation request

Run one pinned-environment job containing the following evidence, without official submission or toolchain/configuration changes:

1. Compile the complete candidate in Lean 4.34.0 with the specified FloatLib and official commits, run the unchanged official lexical and proof audit, and report exact source SHA and any compiler error. Candidate proof acceptance must be established independently of this review.
2. Retain emitted C and inspect the preparation function for one encode temporary, direct FloatArray allocation/push, no intermediate Float Array storage, no runtime `.data`, no per-success-step Option constructor, and no repeated whole-prefix copy. The compiler may express this with different symbol names; semantic dataflow is the criterion.
3. Use the existing official complete-call benchmark/gate unchanged to compare the exact parent and candidate on identical input bytes and machine settings. Keep conversions, checks, allocation, deallocation, failure prefixes, and all fallbacks inside the timed bmm call. Alternate parent/candidate runs or otherwise apply the harness's stable paired procedure; report the per-case timings, not just a grand ratio.
4. Include the official finite suite, zero-dimension cases, and raw special-word inputs. Label observed preparation acceptance/rejection separately. For actually rejected words, place the first rejection at the first/middle/last position of A and B; do not falsify a conversion function to obtain a timed failure case. Compare full raw outputs including NaN payload and signed zero using the unchanged comparator.

The main unresolved performance question is whether the success-path savings exceed push/control overhead on the real finite workload and how much the early/late-failure cases regress. No new speed ratio is justified before this paired evidence exists.

## 8. Integrated candidate review

Reviewed the actual integrated `Kernel.lean` snapshot with SHA256 `98cef0f25c29fe22cf7fa32cc3fb0f2bc38bf1faf65f91aae4fd2d995fe13d84`.

- The outer `match CheckedFloatArray.prepare A.toArray` returns `originalBmm batch m n p A B` in its `none` branch. B preparation occurs only inside the A-success branch, so A failure skips B preparation.
- The B-failure branch calls the same original fallback with the original `A` and `B`; it passes neither AF nor a partial BF.
- The both-success branch supplies AF/BF to the unchanged dot function, and `bmm_spec` obtains each all-index reading invariant from that operand's own recorded `prepare = some` equation. It introduces no unproved soundness premise or length-only substitute.
- The whole checked block from `def dotLoop` through `dotLoop_eq`, `dot`, and `dot_eq` is byte-for-byte identical to the corresponding parent block. In particular, the multiplication/addition order, final finite condition, and exact raw-input fallback are preserved.
- `prepareLoop` has independent `k` and `out` arguments, one local `d := encode x`, the check of that d, and `out.push d` in the successful step. Its executable signature carries no prefix record or proof argument and creates no per-step Option wrapper. `Prefix` and the proof declarations are proof-only. No preparation closure explicitly captures historical `out` values; the later output builder captures the final AF/BF for read-only dot work, which does not by itself retain old preparation prefixes.

**Narrow boxing conclusion:** the candidate source removes the explicit intermediate `Array Float` and therefore the boxes required to store Float elements in that intermediate array. This source review does not prove that every temporary Float box is absent from generated C; compiler specialization, calling conventions, ownership handling, and proof erasure in the emitted program remain uninspected because actual Lean compilation is `NOT_RUN`. The same boundary applies to the expectation that push does not copy previous prefixes.

This integration check is source comparison and control-flow review. It is not an additional Lean compilation, proof-kernel audit, or timing result.
