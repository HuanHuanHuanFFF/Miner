# R2-W04: independent Lean core API and runtime review

Status: pinned-source inspection completed. Lean compilation was not run by this reviewer; `lean`, `lake`, and `elan` were absent from PATH in the parent environment. This report distinguishes confirmed upstream definitions from generated-code expectations.

## Exact public source anchors

All Lean files below were fetched directly from `leanprover/lean4` tag `v4.34.0`. The local snapshots and their complete SHA256/byte records are in `upstream/lean-core-review/SOURCES.json`. No previous project source or private context was consulted.

| File | Public source | SHA256 |
|---|---|---|
| FloatArray logical API | [Init/Data/FloatArray/Basic.lean](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/FloatArray/Basic.lean) | `80f3eff556a5316357ceff025f8b094f9c47915abdb61d4bbb843b92bc8075de` |
| Array preliminary lemmas | [Init/Data/Array/Basic.lean](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Array/Basic.lean) | `85b1fcc2eac430164656c02295d9cf5d3549826517a2a89083a7afae28b1e4f2` |
| Array element lemmas | [Init/Data/Array/Lemmas.lean](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Array/Lemmas.lean) | `232a65023b867747afdd948b4123b4636ae9809047a094e1b63de8939501825c` |
| Scalar array runtime implementation | [runtime/object.cpp](https://github.com/leanprover/lean4/blob/v4.34.0/src/runtime/object.cpp) | `b53499ae7db8ed722a489ae5a79a394b93f6fda2e6663a3784d886867583985a` |
| Scalar array C ABI | [include/lean/lean.h](https://github.com/leanprover/lean4/blob/v4.34.0/src/include/lean/lean.h) | `982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13` |

The sources retain their upstream license notices. They are evidence snapshots, not additional imports or dependencies of the candidate.

## APIs available at the fixed version

`FloatArray` has logical field `data : Array Float`. The production APIs needed by the candidate are:

- `FloatArray.emptyWithCapacity (c : Nat) : FloatArray`; logical data are the empty Array, while the native primitive reserves capacity `c`.
- `FloatArray.push : FloatArray → Float → FloatArray`; logically pushes one value to the represented Array.
- `FloatArray.size : FloatArray → Nat`; logically returns represented Array size.
- `FloatArray.get (ds : FloatArray) (i : Nat) (h : i < ds.size) : Float`; logically retrieves the represented Array element.

No additional runtime representation conversion is needed. `FloatArray.data` can appear when unfolding or destructing values inside a theorem; calling it from a computational definition would rematerialize the Array of boxed Float values and defeat the objective.

The relevant exact Array lemmas are:

- `Array.size_push (v : α) : (xs.push v).size = xs.size + 1`.
- `Array.getElem_push_lt (h : i < xs.size) : (xs.push x)[i] = xs[i]`.
- `Array.getElem_push_eq : (xs.push x)[xs.size] = x`.
- `Array.getElem_push (h : i < (xs.push x).size) : (xs.push x)[i] = if h : i < xs.size then xs[i] else x`.
- `Array.getElem_eq_getD (fallback : α) : xs[i] = xs.getD i fallback`, with the index bound implicit.

A suitable FloatArray size/get lemma can be proved by destructing the FloatArray, unfolding its logical operations inside the theorem, then applying the Array lemma. Proof irrelevance handles differences between bound proofs for the same index. Such proof reduction does not request a runtime `.data` call.

The existing parent already uses `Array.all_eq_true`, other Array lemmas, `omega`, and extensionality through `ContractTensor`; the new proof need not add an import. Exact candidate elaboration remains a compiler check.

## Required induction shape

A complete prefix invariant needs all three facts:

1. `k ≤ xs.size`;
2. `out.size = k`;
3. every `i < k`, after reading the stored Float and narrowing/importing it, equals the original `xs[i]` word value.

The bound in item 1 is necessary: at the terminal branch, `¬ k < xs.size` alone gives `xs.size ≤ k`; it does not establish successful length equality without the maintained upper bound. A successful check on the newly computed `d` supplies the new element equality by applying `beq_iff_eq`, `Subtype.ext`, and `ExecFloat.ext`. It does not require a numeric theorem about either opaque conversion.

Push preservation splits a processed index into `i < k` and `i = k`. The first case uses get-on-push-below-size; the second uses get-on-push-at-old-size plus the successful raw-word check. At termination the two bounds imply `k = xs.size`, and the prefix invariant covers every in-bounds index. For `i ≥ xs.size`, equal length makes the unchanged `read` choose `Float32.ofBits 0`, and the original `Array.getD` chooses `posZero`. The equality here is the parent's existing positive-zero import fact by reduction; it is not an opaque widening/narrowing roundtrip assertion.

## Confirmed runtime mechanisms

The pinned runtime's `lean_float_array_mk` allocates a scalar array and traverses its incoming pointer Array, unboxing every Float into a `double`. The old logical constructor around `xs.map encode` therefore has an intermediate pointer Array and Float element objects in the ordinary runtime path.

`lean_float_array_data` performs the inverse materialization: it allocates a pointer Array and boxes every `double`. This is precisely the runtime call the candidate must avoid.

`lean_mk_empty_float_array` reserves `sizeof(double) * capacity` scalar storage and sets initial size to zero. `lean_float_array_push` accepts an unboxed `double`, ensures capacity and exclusive ownership, stores the double, and increments size. With capacity equal to the original size and exclusive ownership throughout, the capacity/ownership checks return the same scalar array. This avoids per-element capacity growth and copy. Whether generated code actually maintains that uniqueness is a C-generation inspection item; source-level ownership reasoning alone is not a timing measurement.

`lean_float_array_fget` returns a `double` directly. Retaining the parent `read` function therefore retains its direct FloatArray read and narrowing behavior.

## Compilation/code-generation checklist

The real fixed environment should verify that:

- the candidate accepts under only `import ContractTensor` and the pinned dependency graph;
- all four requested specification theorems audit to the allowed axiom set;
- no Float widening/narrowing roundtrip fact was added;
- `prepareLoop` calls `encode` once for each visited element and passes that same `d` to check and push;
- its recursion is tail-shaped with independent `k` and `out` runtime state;
- proof terms and the prefix invariant erase;
- failure and terminal branches are the only Option result constructors;
- generated preparation contains no `lean_float_array_mk` or `lean_float_array_data`, and no Array-of-Float builder or per-element `lean_box_float` attributable to preparation;
- no premature reference-count increment makes the pushed FloatArray shared;
- all checking, allocation, destruction, and preparation costs remain inside the measured full bmm call.

These are exact proof/runtime acceptance points, not claims that the compiler has already emitted the desired C or that the complete bmm became faster.

## Candidate preparation review

Reviewed `work/prepare-block.lean.txt` after the implementation agent supplied it (5,333 bytes at review time). No concrete proof defect was found by source inspection.

The implementation defines the raw check on an explicit supplied `d`, computes that `d` once in `prepareLoop`, and passes the same value to `out.push`. It uses `Prefix` in `Prop` with all three required facts, explicit old/new push lemmas, a recursive `prepareLoop_sound`, `prepare_sound`, `prepare_size_eq`, and `read_prepare_eq`.

The bound arguments used by `FloatArray.get` differ only by proof terms and are definitionally compatible by proof irrelevance. `congrArg Float.toFloat32` transports the exact stored `Float` equality without reducing or axiomatizing the opaque conversion. The terminal case imports the same positive-zero value as the unchanged parent. No runtime `.data` materialization is present in this snippet.

This is an independent manual review, not a successful Lean elaboration or axiom audit. No actual compiler diagnostic was available to eliminate possible tactic elaboration issues.

## Integrated Kernel review

Reviewed integrated `Kernel.lean`, 68,415 bytes, SHA256 `98cef0f25c29fe22cf7fa32cc3fb0f2bc38bf1faf65f91aae4fd2d995fe13d84`.

- The nested matches require successful A preparation before B preparation starts. Either failure uses `originalBmm batch m n p A B`, retaining the original input vectors.
- `cases hAF : prepare A.toArray` and `cases hBF : prepare B.toArray` preserve exactly the success equations consumed by `read_prepare_eq`. The subsequent `simp only` reduces the selected match branch without assuming any conversion equality.
- `read_prepare_eq A.toArray AF hAF` and its B counterpart are functions over all Nat indices, matching the unchanged `dot_eq` hypotheses exactly.
- The `dot_eq` invocation supplies its eight explicit data arguments (n, baseA, baseB, p, A, B, AF, BF), followed by the two proved invariants.
- The final `Vector.ofFn`/address-normalization proof retains the parent's structure and reference theorem.
- An independent byte comparison found the full file prefix preceding `namespace CheckedFloatArray` unchanged, and found the region from `CheckedFloatArray.dotLoop` through `end CheckedFloatArray` unchanged. This includes all arithmetic, the final finite guard, and the original exact fallback.

No concrete elaboration or logic issue was found by this static review. This does not upgrade compilation or axiom auditing from NOT_RUN.
