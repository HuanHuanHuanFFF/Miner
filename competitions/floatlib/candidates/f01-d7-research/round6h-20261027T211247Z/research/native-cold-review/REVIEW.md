# Native cold ADD and MUL: independent semantic review

Start **2026-10-28 00:38:36 UTC**, bounded to **00:58:36 UTC**; common cutoff remains 03:12:47. This reviews exact D MUL **e3b93d3a / 784 B** and ADD **21cd9128 / 490 B** against B2 **622d8394**. No D source edits, public candidate, local Lean, native execution or CI.

## Verdict and exact boundaries

The two hit arms have a valid existing mathematical route to the original specifications. Removing the source-level result NaN test is justified **inside these hit arms**. This is not permission to remove the old B2 result test globally, nor a performance conclusion.

MUL `pairOK` accepts exactly both unsigned magnitudes in `[0x20000000,0x60000000)`, equivalently raw exponents 64..191 with arbitrary fractions and signs. Subtraction is wrapping UInt32 subtraction. OR below `2^30` implies each shifted magnitude is below `2^30`; subtraction underflow is therefore rejected. Both inputs satisfy the old table's NormalBand and are finite/nonzero. The smallest absolute product is `2^-126`; overflow to signed infinity remains legal. For example, `20000000*20000000=00800000`, while `5fffffff*5fffffff=7f800000`. It would be wrong to require the **output** to be finite. ±0, every subnormal, E1..63, E192..254, infinities and NaNs all retain the exact old B2 fallback, with operand order preserved.

ADD accepts the existing `fastOK` predicate for each input: either signed zero or raw exponent 24..254. Its bare table decode is already exact on both signed zeros and that normal band. All four zero pairs are valid hit cases: `-0 + -0 = -0`; the other three zero pairs produce +0 under the original nearest-even operation. Finite cancellation and overflow retain the original semantics; `7f7fffff+7f7fffff=7f800000` is a valid hit. Nonzero E1..23, subnormals, infinities and NaNs use exact B2 fallback.

The lower decode boundary is substantive. `0b800001 + 8b800000` (E23 inputs) produces subnormal `00400000`; forced bare table decoding instead produces +0. The actual guard rejects this pair. Similarly, the current MUL pair domain does not silently broaden to the larger table domain merely because the table can decode more inputs.

## NaN payload and the result-test distinction

No hit input is a NaN or infinity. Native addition or multiplication of finite inputs cannot produce NaN, and the existing native-to-original arithmetic lemmas cover their overflow and signed-zero results. More directly, those lemmas require only **input** `isNaN=false`, so no separate new theorem about the result classifier is needed to remove the result test in the proof.

Outside the hit domain, original raw NaN semantics remain essential. The original source-word model gives `7fc00001 + 3f800000 = 7fc00001`, while unconditional native import gives canonical `7fc00000`. A qNaN followed by negative sNaN, `7fc00456 + ff800123`, gives `ffc00123`, preserving the first signaling NaN's sign/payload after quieting. Both new entries reject these inputs and preserve old B2 repair. R7W12's all-native image closure does not prove raw-NaN roundtrip: converting a raw NaN to native has already discarded its original representation.

This priority is also directly visible in the retained B2 source, not only the finite oracle: `Submission.DWordNaN.rawChoose` at lines 2879–2884 tests left sNaN, right sNaN, left NaN, right NaN, then ORs the quiet bit. Its existing `rawChoose_eq`, `selected_add` and `selected_mul` connect that selection to the original model/specification. The new wrappers preserve the original x,y order on every miss. The runtime native codec/toBits implementation is unchanged; only the source-level test around the hit result is absent.

`Inf*0` and `Inf+(-Inf)` are rejected here. Their original invalid-operation result is canonical NaN, so they are not themselves payload counterexamples. The present bare table decoder cannot decode infinity correctly; they must not be admitted merely because a broader native-image theorem exists. No guard expansion is proposed.

## Minimal real interfaces

All required model bridges are already in exact B2. The proof-only `FastOKNativeBridges.lean.inc` has three **NOT_RUN** roots under `Submission.R22NativeColdReview`:

- `fastOK_notNaN`: `R2W01b.fastOK_iff` gives magnitude below infinity (or zero); `Submission.R7W12.rawNotNaN_eq_native_classifier` gives the actual native input classifier. It uses the same `Bool.not_inj` pattern already in B2's `native_step_eq`.
- `native_add_spec_of_fastOK`: `R2W01b.tableProduct_of_fastOK R2W01c.normal_eq`, then `Submission.R7Native.ofFloat32Add`, `Submission.NotNaNProbe.roundtrip`, and `ExecFloat.Proof.add_eq_spec`.
- `native_mul_spec_of_fastOK`: the same decoder/input bridge, using `Submission.R7Native.ofFloat32Mul` and `ExecFloat.Proof.mul_eq_spec`.

`PairDomain.lean.inc` adds one separate **NOT_RUN** root `pairOK_normal`, after B2 and the exact e3b runtime. It is the original R11 joint-OR argument with an explicit bound on `(magnitude w).toNat`. Its result converts to the needed `fastOK` assumptions through `fastOK_iff.mpr (Or.inr ...)`. ADD obtains its two hypotheses by `Bool.and_eq_true`; no new exponent arithmetic is needed. Public `if`/fallback transport is intentionally not assembled.

The MUL inline/cold variants differ only by the reducible definition `retainedMul x y := Submission.mul x y`; their pointwise equality is definitionally `rfl`. The noinline attribute changes compiler treatment, not kernel equality. This does not make either wrapper definition a proof of the new public multiplication specification.

## Likely proof-port pitfalls, not observed compiler failures

1. Exact B2 does **not** contain `R2W01c.normal_finite` or `GuardBridge.finiteRoundtrip`, although the old R11 fragment refers to them in its older parent. Do not paste the complete old fragment unchanged. The three new small interfaces avoid both dependencies using existing B2 `NotNaNProbe.roundtrip`.
2. The uncompiled R19 `Postguard-mul.lean.inc` uses `have hu := u.toNat_lt_size` inside `normal_of_shift`, but its modular expression concerns `(magnitude u).toNat`. The R11 form supplies the directly relevant `(magnitude u).toNat_lt_size`. If that old R19 omega goal is the first real failure, this exact bound is the small repair; this review does not assert that omega necessarily fails without it.
3. A native finite-input bridge does not require finite output. Rejecting overflow would change the guard/body and is unnecessary.
4. Proofs about output `nonNaN` do not recover arbitrary raw NaN payloads after import; maintain the original miss branch and input order.

`boundary-witnesses.json` records 50 fixed cases using the already pinned integer/source-word oracle, with zero guarded-model differences and explicit forced-decode/payload counterexamples. It is not Lean, native runtime or exhaustive verification. `manifest.json` binds the exact runtime, base, old fragments and new proof-only bytes. Caller frame/ABI changes, timings and adoption remain UNKNOWN pending D's actual selected caller and complete cost.
