# Remaining scaled UInt32 bridge

Evidence checked 2026-10-27, before the R22 complete-call cost result. The minimal product probe is frozen separately. This map does not report a Lean result.

## Exact established ingredients

- R21 `56cdb076` has `scaled_fields x m e`: it requires the actual native Float32 decode, `2^23 ≤ m < 2^24`, and `e=23 ∨ e=24`. Its proof uses same-width Float32 multiplication by the exact `0x34000000` constant and UInt32 toward-zero conversion with a no-clamp bound.
- R17 repair fragment `b610a60d` has `native_uint64_decode` and `product_word_nat`. The first gives the real native UInt64-to-Float32 cast decode; the second proves the two 24-bit significands do not wrap in UInt64. `Kernel-probe1.lean` composes these, retaining the actual product rather than substituting a float product.
- The original R18 full source `f01-r17-dev-u64-public2/Kernel.lean` uses the same exponent guard: each exponent is in `[1,254]`, their sum in `[128,380]`. Its `R18.R14ExponentShift.eligible_conditions` discharges UInt32 subtraction wrap precisely. Reuse this guard lemma with names changed; do not strengthen the guard or alter fallback coverage.
- Its model-side theorem `R18.R14ExponentShift.model_mul_normal_fields` is independent of the UInt64 reverse conversion. It already carries rounded overflow at the 46/47-bit transition and gives the exact target exponent and fraction.

## Small new field interface

For `p=a.toNat*b.toNat`, set `z=((a.toUInt64*b.toUInt64).toFloat32*powNeg23).toUInt32`, `high=z>>>24`, `q=z>>>high`.

1. The two new probe roots give `high.toNat=roundedShift(p)-23` and `q.toNat=mantissa(p)`.
2. `roundedShift(p)=middleExponent(p)-150` and `173≤middleExponent(p)≤174` imply `high.toNat=middleExponent(p)-173`. This is Nat subtraction; use `omega` with those bounds rather than treating subtraction as ring subtraction.
3. `q≥8388608` allows `UInt32.toNat_sub_of_le` for `q-8388608` without wrap. This equals `storedFraction(p)` and is `<8388608`.
4. `sum≥128` allows no-wrap `sum-127`. Together with `high≤1`, the exponent word has Nat value `middleExponent(p)+sum.toNat-300`, in `[1,254]`.
5. Reuse the old `low_mask_eq_self`, `mkW_eq_unmasked`, and `FastMul.mkW_ofNat` packing route. It equates the actual three OR fields with `NativeBinary32.mkBits` and does not replace the runtime operation.
6. Reuse the old `sign_word_eq`, `model_mul_normal_fields`, and `Configured.Family.toModel_injective` transport to the original `ExecFloat.Spec.mul`.
7. Reuse the original nested guard proof, keeping `hf : ∀ x y, fallback x y = ExecFloat.Spec.mul x y`. A public alias carrier is a separate integration change, to be checked on its exact source.

## Capacity and first decision

Current minimal probe is 244553 B, leaving 11447 B below the 256000 B limit. The unmodified old model/guard support is 5872 B and old entry/spec is 4823 B, before the new field repack proof. Therefore a naive append of the full proof will exceed the package limit. Do not create an oversized purported entry and call it ready. First check the complete-call runtime cost; if useful, prune unused old support and compress only proof text or build a compact carrier, with exact byte accounting and a new source hash. Removing comments does not change semantics but still needs source-bound verification.

Two independent blockers remain: compiling the new native product composition and earning enough runtime benefit to justify the remaining field proof/package work. A successful minimal probe resolves only the first.
