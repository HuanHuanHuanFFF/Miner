# R11-W01: concrete packing and ordered-loop audit

Status: **SOURCE_INSPECTION; LEAN NOT_RUN**. No concrete defect was found in this segment. No edit to its runtime definitions, theorem statements, or proof bodies is recommended on the available evidence. In particular, a speculative rewrite of already adequate packing proofs would spend the 3,391-byte source margin without closing a demonstrated gap.

Source: `Kernel.original.lean`, SHA256 `4bdd1e7db35cd85e17d06511721d5dbf7f654ec12e58633264b08a086ec54fa0`, 252,609 bytes. The relevant declarations are the actual `Submission.R11CrossRows.packGeneral_a`, `packGeneral_b`, `packShared_eq`, `pack_eq_general`, `pack_a`, `pack_b`, `natLoop_lane`, `wordLoop_eq`, and `dot8_lane`.

## Concrete lane/read correspondence

Let `a_r = select4 a0 a1 a2 a3 r`, and similarly for `b_r`. For every actual `k : Fin n`, the fields constructed by `packGeneral` are:

| lane | row | col | packed A read | packed B read | update |
|---|---:|---:|---|---|---|
| 0 | 0 | 0 | `A.getD (a0+k.val) posZero` | `B.getD (b0+k.val*p) posZero` | `s0 + a0*b0` |
| 1 | 1 | 0 | `A.getD (a1+k.val) posZero` | `B.getD (b1+k.val*p) posZero` | `s1 + a1*b1` |
| 2 | 2 | 0 | `A.getD (a2+k.val) posZero` | `B.getD (b2+k.val*p) posZero` | `s2 + a2*b2` |
| 3 | 3 | 0 | `A.getD (a3+k.val) posZero` | `B.getD (b3+k.val*p) posZero` | `s3 + a3*b3` |
| 4 | 0 | 1 | `A.getD (a0+k.val) posZero` | `B.getD ((b0+1)+k.val*p) posZero` | `s4 + a0*b4` |
| 5 | 1 | 1 | `A.getD (a1+k.val) posZero` | `B.getD ((b1+1)+k.val*p) posZero` | `s5 + a1*b5` |
| 6 | 2 | 1 | `A.getD (a2+k.val) posZero` | `B.getD ((b2+1)+k.val*p) posZero` | `s6 + a2*b6` |
| 7 | 3 | 1 | `A.getD (a3+k.val) posZero` | `B.getD ((b3+1)+k.val*p) posZero` | `s7 + a3*b7` |

Each table read is passed to the actual `ExecFloat.Binary.toFloat32`. The table's update column uses P12 field names, not raw array values. The coefficient stride is `p`, not hardcoded to two, so the theorems retain their stated arbitrary-Nat `p` domain.

`packGeneral_a/b` enumerate all eight `Fin 8` values and reduce the actual `Vector.ofFn` read with the earlier in-file `Packed10.vector_get_ofFn`. The B formula is precisely `(b_(l%4)+l/4)+k*p`: lanes 0..3 use column zero and lanes 4..7 use column one. No commutation or reassociation of Float32 arithmetic is involved.

`packShared_eq` is a definitional equality: when all four B bases coincide, the shared `c0` and `c1` fields unfold to exactly the corresponding general fields. `pack_eq_general` substitutes all three equalities from the actual conjunction guard. Its other branch is reflexivity. Consequently `pack_a/b` establish concrete reads in either executable branch; no abstract pack/read assumption is substituted.

## Ordered recursion

For an arbitrary starting Nat `k` and F8 accumulator `s`, `natLoop_lane` identifies one lane with the actual `NativeFinal.dotLoop` using the same `k<n` branch. In the recursive branch, `lane_update`, `pack_a`, and `pack_b` rewrite the induction hypothesis to the same scalar expression

```text
lane s l + toFloat32(A.getD (a_r+k) posZero)
             * toFloat32(B.getD ((b_r+j)+k*p) posZero)
```

and the same next index `k+1`. Parenthesization is multiply then add; each lane starts at positive zero and follows ascending k. The false branch returns its incoming accumulator in both programs, including `k>n`.

The measure `n-k` strictly decreases under `k<n`. The attached parent already uses this same well-founded recursive proof pattern for `NativeFinal.dotLoop_eq` and other declarations. There is no evidence that a new termination measure or a runtime change is required here. If the exact compiler reports a failure at this theorem's generated decrease obligation, the precise proof obligation is

```lean
-- hk : k < n
n - (k + 1) < n - k
```

and the narrowly scoped proof repair hypothesis is appending `decreasing_by omega` to `natLoop_lane` only. This is a contingency, **not a demonstrated required patch and not compiled evidence**.

## Actual machine premises

The only USize arithmetic in this segment is the packed-loop counter. Raw A/B offsets in `packGeneral` and `packShared` remain arbitrary-precision Nat and use total `Array.getD`.

1. `hn : n < USize.size` gives `(USize.ofNat n).toNat = n` through the exact existing `USize.toNat_ofNat_of_lt'` use.
2. `hk : k < count` and `count.toNat = n` give `hkn : k.toNat < n`.
3. The packed vector's actual array has size `n`, so `v.toArray.uget k` is justified by `v.size_toArray` and `hkn`.
4. The proof-local `hread` equates this uget with `v.get <k.toNat,hkn>` by reflexivity. The parent already has `Packed10Index.ugetB_get` with the same proof pattern for a `Vector F10`; the element type does not affect the read identity.
5. `hk` gives `k.toNat+1 <= count.toNat < USize.size`. Thus increment does not wrap. The already attached `Packed10Index.stepNat` proves `(k+1).toNat = k.toNat+1` and `next_decreases` proves the machine-loop measure decrease.

Neither an in-range A/B array assumption nor a USize bound for phantom tail offsets is necessary for these packing equalities: out-of-range Nat reads use the existing `posZero` default. Such a bound must not be silently assumed or incorrectly demanded. Later live-output correctness still has to connect actual retained rows and original matrix indices; that is a separate row/core proof obligation.

## Empty and unbounded dimensions

When `n=0`, `pack` is an empty Vector, `wordLoop` begins with count zero, no `uget` occurs, and all eight lanes remain `Float32.ofBits 0`. The quantified `pack_a/b` statements have no `k : Fin 0` instance. The loop theorem itself remains valid for zero n.

The packing and Nat-loop theorems quantify arbitrary Nat dimensions, bases, stride, and starting index. Machine equivalence explicitly requires the available bounded `count`/`hn` premises; it does not generalize a wrapping counter to arbitrary n. The top-level dispatch bypasses this route when n is too large or zero. The `m=0`, `p=0`, and tail/core bridges must be audited at their own actual definitions rather than inserted into these read lemmas as unnecessary assumptions.

## Remaining verification

No pinned Lean/lake/elan executable was available in the initial environment check. Primary-source opens of the pinned Lean `src/Init/Data/Vector/Basic.lean` and `Array/Basic.lean` returned `DisabledError`; a bounded direct fetch also returned `Operation not permitted`. These are retrieval limitations, not evidence that the files or APIs are absent. No alternate Lean version, mock floating model, finite numerical test, runtime timing, or claim of typechecking acceptance is used here.

The exact compiler must still elaborate these unchanged declarations under the official command-line options, compile the full original-spec bridge, and perform the original statement/axiom/checksum/replay gate. Source inspection alone does not close that acceptance requirement.
