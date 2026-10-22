# R2-W02b decode proof and independent static audit

Status: **NOT_RUN** for Lean elaboration, kernel checking, native compilation, the official verifier, generated C, and benchmarks. No Lean toolchain was installed or invoked. The inspection used only this task's current source drafts and the supplied or pinned public sources.

## Delivered source

`Decode.lean` is a concatenation fragment for insertion while the parent `Submission` namespace is open. Its `namespace Packed4` therefore defines the following exact target:

```lean
theorem Submission.Packed4.decode_bounds
    (batch m p : Nat) (q : Fin (batch * m * p)) :
    (Competition.bmmDecodeC m p q.val).1 < batch ∧
      (Competition.bmmDecodeC m p q.val).2.1 < m ∧
      (Competition.bmmDecodeC m p q.val).2.2 < p
```

The proof derives `q.val < batch * (m * p)` from `q.isLt` using `Nat.mul_assoc`. An inhabited output index rules out `m * p = 0`, which also rules out `p = 0`. The three coordinate bounds then follow from two applications of the positive-denominator division equivalence and two positive-modulus remainder bounds. No caller-supplied positive-size assumption is needed.

The supplied `ContractTensor.lean` defines the zero-size cases of `bmmDecodeC` explicitly. The proof discharges those cases before simplifying that definition; it does not replace or strengthen the contract.

## Exact arithmetic API check

The pinned Lean source at

<https://raw.githubusercontent.com/leanprover/lean4/v4.34.0/src/Init/Data/Nat/Div/Basic.lean>

contains this declaration at line 314:

```lean
theorem div_lt_iff_lt_mul (Hk : 0 < k) : x / k < y ↔ x < y * k
```

The proof uses its reverse implication with the denominator proof as the explicit argument. The local pinned `Nat/Div/Lemmas.lean` also uses `Nat.mod_lt a h` with the dividend and positive-modulus proof in exactly that order.

## Independent review of the current source drafts

The review covered `Layout.lean`, `Dot.lean`, and `Main.lean` after they were written. It found no established source-level blocker in declaration names, parameter order, namespace resolution, or the inspected equality conversions. This is a static result, not a claim that Lean has accepted the files.

Specific checks:

- `Layout.vector_get_ofFn` matches the pinned `Vector.getElem_ofFn` signature. `Vector.get` and the natural-index `GetElem` instance agree definitionally at the constructed `Fin` index. Rewriting all three nested vector layers in `packB_get` and `tileResults_get` therefore uses the intended accessor theorem.
- The finite lane case splits cover precisely `0`, `1`, `2`, and `3`. `lane_update` preserves each lane's floating-point expression `s + a * b`; it introduces no reassociation of floating-point arithmetic.
- `groups_pos_of_col` and `column_decomposition` involve only division and remainder by the literal four, within the intended arithmetic supported by `omega`.
- `Dot.nativeA_getD` uses the pinned `Array.size_map` and `Array.getElem_map` declarations. The positive branch compares the same mapped element, with any index-proof difference confined to proof terms. The negative branch reduces to the concrete positive-zero conversion described below.
- `dot4_lane` uses the same increasing `k` and `n - k` measure as the parent scalar loop. Its recursive call applies the current lane recurrence, the mapped-A read equality, and the supplied B-stream read equality. The current source explicitly handles both ordinary and dependent `if` simplification when unfolding the two loops.
- `finish_eq_dot` has the identical finite-result guard and fallback fold as the parent `NativeFinal.dot`; the initial `zero32` unfolds to `Float32.ofBits 0`. The finite-result bridge is reused through the parent's theorem rather than restated.
- `Main.tile_finish` supplies `packB_lane` with the same `b`, `g`, `k`, and `l`. Its `index_address` rewrite transforms `((b * n + k) * p + column)` into `(b * n * p + column) + k * p`, matching the scalar `baseB` address.
- `outputFromTiles_eq` reconstructs the same local `d`, `b`, `i`, `g`, and `l` values as `outputFromTiles`. Their `Fin` proof fields are proposition-valued; the relevant conversions preserve the same natural values. Its `hc` equality rewrites `4 * g.val + l.val` to the decoded column in both sides of `tile_finish`.
- `core_eq_reference` applies the equality under `Vector.ofFn`, then reuses `NativeFinal.dot_eq` and the parent's `index_address` argument. The final `bmm_spec` uses the parent `referenceBmm_spec` after a vector equality. Both zero-output and zero-reduction branches return `referenceBmm` directly.
- The nested cache types consistently use `batch × groups p × n` for B packets and `batch × m × groups p` for result packets. The `tileResults` body contains one `dot4` expression for each result packet, followed by lane extraction in the output function.

## Positive-zero definitional equality

The FloatLib revision is the manifest-pinned
`0d91825727839f597fd06b22fdd038ea21480f0c`. The following public source chain was read directly at that revision:

1. `FloatLib/Floats/Formats/IEEE754/Native.lean`, lines 68–71 and 131–134: `toFloat32 value` is `Float32.ofBits (toBits32 value)`, and `toBits32` projects `value.raw.1`.
2. `FloatLib/Floats/Formats/BinaryInterchange/Configured/Value/Core.lean`, lines 138–140: `ExecFloat.Binary.zero false` packs `Model.zero format false` using `ofModel`.
3. `FloatLib/Floats/Formats/BinaryInterchange/Model/Carrier.lean`, lines 236–237 and 278–279: the false sign selects `Model.posZero`, defined as `ofNatBits 0`.
4. `FloatLib/Floats/Formats/BinaryInterchange/Configured/Storage/Code/Runtime.lean`, lines 59–64: the binary32 word carrier packs through `StaticStorage.Word32Code.ofNat`.
5. `FloatLib/Numerics/Representations/StaticStorage.lean`, lines 88–92: this transparent definition returns a subtype whose data is `UInt32.ofNat bits`.

Consequently the concrete `ExecFloat.Binary.toFloat32 Competition.posZero` unfolds to `Float32.ofBits 0`; the inspected path contains no opaque conversion. This supports the negative `nativeA_getD` branch's definitional-equality proof. It is still not a substituted compiler result.

The source URL pattern for these files is:

<https://raw.githubusercontent.com/lean-dojo/FloatLib/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native.lean>

## Evidence boundary and next acceptance target

The supplied parent was read and independently hashed as 58,079 bytes with SHA-256
`86312a3759286cb207f946af9db95546777fdb16f1bd147f7892c0f9e1d79217`.

No source outside `Decode.lean` and this audit note was modified by this audit. The exact remaining proof target is the assembled candidate's `Submission.bmm_spec` against the unchanged `Competition.bmmSpec` for all natural dimensions and all input vectors. The official Lean 4.34.0 environment must elaborate and kernel-check the assembled file and run the required verifier before acceptance can be claimed. Runtime sharing, generated C, and performance remain unmeasured.
