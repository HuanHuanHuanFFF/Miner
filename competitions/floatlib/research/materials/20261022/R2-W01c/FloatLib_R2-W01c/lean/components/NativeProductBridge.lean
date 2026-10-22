import ContractTensor

/-
MIT License

Copyright (c) 2026 Conjectures.io

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

# Third-party notices

This repository is under the MIT licence in [LICENSE](LICENSE). Some of its files reproduce, adapt
or restate code from the projects below, whose licences ask that their notices travel with that
code; those notices are reproduced here in full. [REUSE.toml](REUSE.toml) records, file by file,
which notices apply, and `reuse lint` checks it.

If you copy a shipped kernel, contract or migration file into your own work, a submission
included, keep the notices that apply to it.

## Included in this repository

### FloatLib

[FloatLib](https://github.com/lean-dojo/FloatLib), MIT licence. The contract
(`lean/contract/`) restates FloatLib's IEEE 754 specification as the obligations a kernel must meet,
and the kernels (`kernels/`) and stage 2 (`lean/stage2/`) reproduce or adapt FloatLib's certified
binary32 word kernels and their helpers: `kernels/add/mirror` runs FloatLib's word addition step
for step on bare words, and the faster kernels are built from it.

```text
MIT License

Copyright (c) 2026 FloatLib

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

### TorchLean

[TorchLean](https://github.com/lean-dojo/TorchLean), MIT licence. The tensor contract
(`lean/contract/ContractTensor.lean`) restates TorchLean's `reduceSumLeftSpec` and `bmmSpec`, and
the `sum`, `bmm` and full-entry kernels and `lean/stage2/` are written against those definitions;
`lean/stage2/Stage2/Link.lean` proves the restatements equal to TorchLean's own.

```text
MIT License

Copyright (c) 2026 TorchLean

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```


-/

namespace R2W01c

namespace NativeBridge

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open Float.Model.UnpackedFloat
open FloatLib.Floats.Formats.BinaryInterchange.Model

/-
The three target-exponent lemmas below are ported from FloatLib Team, MIT,
commit 1f5771b3e36a98f17fcac2c6d76aaa024b36aa37,
Arithmetic/LeanModel/MulDiv.lean. Official pinned dependencies are unchanged.
-/
theorem le_targetExponent_totalExponent_iff (spec : Float.Model.Format)
    (mantissa : Nat) (exponent : Int) :
    exponent ≤ spec.targetExponent (Float.Model.totalExponent mantissa exponent) ↔
      exponent ≤ spec.minExponent ∨ 2 ^ spec.mantissaBitsWithoutImplicit ≤ mantissa := by
  have hlog : spec.mantissaBitsWithoutImplicit ≤ mantissa.log2 ↔
      2 ^ spec.mantissaBitsWithoutImplicit ≤ mantissa := by
    rcases Nat.eq_zero_or_pos mantissa with rfl | hmantissa
    · have hwidth := spec.hm
      have hpow := Nat.two_pow_pos spec.mantissaBitsWithoutImplicit
      rw [Nat.log2_zero]
      omega
    · exact Nat.le_log2 hmantissa.ne'
  rw [← hlog]
  simp only [Float.Model.Format.targetExponent, Float.Model.totalExponent,
    Float.Model.Format.mantissaBits]
  omega

/--
If two nonzero mantissas and their exponents satisfy Lean's `roundWithAccuracy` precondition, so
do the product of the mantissas and the sum of the exponents.
-/
theorem add_le_targetExponent_totalExponent_mul (spec : Float.Model.Format)
    {mantissa₁ mantissa₂ : Nat} {exponent₁ exponent₂ : Int}
    (hmantissa₁ : 0 < mantissa₁) (hmantissa₂ : 0 < mantissa₂)
    (hle₁ :
      exponent₁ ≤ spec.targetExponent (Float.Model.totalExponent mantissa₁ exponent₁))
    (hle₂ :
      exponent₂ ≤ spec.targetExponent (Float.Model.totalExponent mantissa₂ exponent₂)) :
    exponent₁ + exponent₂ ≤
      spec.targetExponent
        (Float.Model.totalExponent (mantissa₁ * mantissa₂) (exponent₁ + exponent₂)) := by
  rw [le_targetExponent_totalExponent_iff] at hle₁ hle₂ ⊢
  have hmin : spec.minExponent ≤ 0 := by
    have hwidth := spec.hm
    have hpow : (1 : Int) ≤ 2 ^ (spec.exponentBits - 1) := by
      exact_mod_cast Nat.two_pow_pos (spec.exponentBits - 1)
    simp only [Float.Model.Format.minExponent, Float.Model.Format.mantissaBits]
    omega
  rcases hle₁ with hle₁ | hle₁
  · rcases hle₂ with hle₂ | hle₂
    · exact Or.inl (by omega)
    · exact Or.inr (hle₂.trans (Nat.le_mul_of_pos_left mantissa₂ hmantissa₁))
  · exact Or.inr (hle₁.trans (Nat.le_mul_of_pos_right mantissa₁ hmantissa₂))

/--
A finite nonzero value unpacked from a format word satisfies Lean's `roundWithAccuracy`
precondition: a subnormal has the minimum exponent and a normal has its leading bit set.
-/
theorem le_targetExponent_totalExponent_of_toModel_eq_finite {fmt : FloatFormat} (x : Model fmt)
    {sign : Sign} {mantissa : Nat} {exponent : Int} {hmantissa : 0 < mantissa}
    (hx : toModel x = .finite sign mantissa exponent hmantissa) :
    exponent ≤
      (FloatFormat.toModel fmt).targetExponent (Float.Model.totalExponent mantissa exponent) := by
  rw [le_targetExponent_totalExponent_iff, toModel_minExponent]
  change exponent ≤ FloatFormat.ieeeMinSubnormalExponent fmt ∨ 2 ^ fmt.fracWidth ≤ mantissa
  have hdecode := ieeeToDyadic?_eq_unpackedToDyadic?_toModel x
  rw [hx] at hdecode
  simp only [unpackedToDyadic?, ieeeToDyadic?] at hdecode
  split_ifs at hdecode
  · simp only [Option.some.injEq, FloatLib.Numerics.Dyadic.mk.injEq] at hdecode
    exact absurd hdecode.2.1.symm hmantissa.ne'
  · simp only [Option.some.injEq, FloatLib.Numerics.Dyadic.mk.injEq] at hdecode
    exact Or.inl hdecode.2.2.symm.le
  · simp only [Option.some.injEq, FloatLib.Numerics.Dyadic.mk.injEq] at hdecode
    refine Or.inr ?_
    rw [← hdecode.2.1, pow2_eq_two_pow]
    exact Nat.le_add_right _ _


/-- The finite multiplication specifications perform the same exact product and one rounding. -/
theorem modelMulFinite {fmt : FloatFormat} (hfmt : fmt.isIEEE = true)
    (x y : Model fmt) (hx : (Model.toModel x).isFinite = true)
    (hy : (Model.toModel y).isFinite = true) :
    Model.mul x y =
      Model.ofModel fmt
        (Float.Model.UnpackedFloat.mul (FloatFormat.toModel fmt)
          (Model.toModel x) (Model.toModel y)) := by
  have hzero := FloatFormat.supportsSignedZero_eq_true_of_isIEEE fmt hfmt
  cases hxmodel : Model.toModel x <;> cases hymodel : Model.toModel y <;>
    simp only [hxmodel, hymodel, Float.Model.UnpackedFloat.isFinite,
      Bool.false_eq_true] at hx hy
  case zero.zero sign₁ sign₂ =>
    rw [Model.Proof.mul_eq_spec, Model.Spec.mul,
      Model.toDyadic?_ieee_eq_model fmt hfmt x,
      Model.toDyadic?_ieee_eq_model fmt hfmt y, hxmodel, hymodel]
    cases sign₁ <;> cases sign₂ <;>
      simp [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.mul,
        Model.modelSignBit, Model.zero, Model.posZero_eq_ofModel_zero,
        Model.negZero_eq_ofModel_zero, hzero,
        show Sign.negative * Sign.negative = Sign.positive from rfl,
        show Sign.negative * Sign.positive = Sign.negative from rfl,
        show Sign.positive * Sign.negative = Sign.negative from rfl,
        show Sign.positive * Sign.positive = Sign.positive from rfl]
  case zero.finite sign₁ sign₂ mantissa₂ exponent₂ hmantissa₂ =>
    rw [Model.Proof.mul_eq_spec, Model.Spec.mul,
      Model.toDyadic?_ieee_eq_model fmt hfmt x,
      Model.toDyadic?_ieee_eq_model fmt hfmt y, hxmodel, hymodel]
    cases sign₁ <;> cases sign₂ <;>
      simp [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.mul,
        Model.modelSignBit, Model.zero, Model.posZero_eq_ofModel_zero,
        Model.negZero_eq_ofModel_zero, hzero,
        show Sign.negative * Sign.negative = Sign.positive from rfl,
        show Sign.negative * Sign.positive = Sign.negative from rfl,
        show Sign.positive * Sign.negative = Sign.negative from rfl,
        show Sign.positive * Sign.positive = Sign.positive from rfl]
  case finite.zero sign₁ mantissa₁ exponent₁ hmantissa₁ sign₂ =>
    rw [Model.Proof.mul_eq_spec, Model.Spec.mul,
      Model.toDyadic?_ieee_eq_model fmt hfmt x,
      Model.toDyadic?_ieee_eq_model fmt hfmt y, hxmodel, hymodel]
    cases sign₁ <;> cases sign₂ <;>
      simp [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.mul,
        Model.modelSignBit, Model.zero, Model.posZero_eq_ofModel_zero,
        Model.negZero_eq_ofModel_zero, hzero,
        show Sign.negative * Sign.negative = Sign.positive from rfl,
        show Sign.negative * Sign.positive = Sign.negative from rfl,
        show Sign.positive * Sign.negative = Sign.negative from rfl,
        show Sign.positive * Sign.positive = Sign.positive from rfl]
  case finite.finite sign₁ mantissa₁ exponent₁ hmantissa₁ sign₂ mantissa₂ exponent₂ hmantissa₂ =>
    have hle := add_le_targetExponent_totalExponent_mul (FloatFormat.toModel fmt)
      hmantissa₁ hmantissa₂
      (le_targetExponent_totalExponent_of_toModel_eq_finite x hxmodel)
      (le_targetExponent_totalExponent_of_toModel_eq_finite y hymodel)
    have hr (sign : Sign) :
        Float.Model.UnpackedFloat.roundWithAccuracy (FloatFormat.toModel fmt) sign
          (mantissa₁ * mantissa₂) (exponent₁ + exponent₂) .exact =
        Float.Model.UnpackedFloat.round (FloatFormat.toModel fmt) sign
          (mantissa₁ * mantissa₂) (exponent₁ + exponent₂) :=
      Model.roundWithAccuracy_exact_eq_round_of_le_targetExponent _ _ _ _ hle
    rw [Model.Proof.mul_eq_spec, Model.Spec.mul,
      Model.toDyadic?_ieee_eq_model fmt hfmt x,
      Model.toDyadic?_ieee_eq_model fmt hfmt y, hxmodel, hymodel]
    cases sign₁ <;> cases sign₂ <;>
      simp [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.mul,
        Model.roundDyadic, hfmt, Model.ieeeRoundDyadic,
        Model.modelSignBit, Model.modelSign, hmantissa₁.ne', hmantissa₂.ne',
        hr,
        show Sign.negative * Sign.negative = Sign.positive from rfl,
        show Sign.negative * Sign.positive = Sign.negative from rfl,
        show Sign.positive * Sign.negative = Sign.negative from rfl,
        show Sign.positive * Sign.positive = Sign.positive from rfl]

theorem toModelNativeMul (x y : Float32)
    (hx : x.isFinite = true) (hy : y.isFinite = true) :
    ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 (x * y)) =
      Model.mul (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 x))
        (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 y)) := by
  rw [ExecFloat.Binary.toModel_ofFloat32, ExecFloat.Binary.toModel_ofFloat32,
    ExecFloat.Binary.toModel_ofFloat32]
  change Model.ofFloat32Model (Float32.Model.mul x.toModel y.toModel) = _
  rw [Float32.Model.mul, Model.ofFloat32Model_pack]
  have h := modelMulFinite (fmt := FloatFormat.binary32)
    (by decide) (Model.ofFloat32Model x.toModel) (Model.ofFloat32Model y.toModel)
    (by simpa only [Model.toModel_ofFloat32Model, Float32.isFinite,
      Float32.Model.isFinite] using hx)
    (by simpa only [Model.toModel_ofFloat32Model, Float32.isFinite,
      Float32.Model.isFinite] using hy)
  rw [Model.toModel_ofFloat32Model, Model.toModel_ofFloat32Model] at h
  exact h.symm

end NativeBridge

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

abbrev nativeModel (x : Float32) : Model FloatFormat.binary32 :=
  ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 x)

abbrev rawModel (u : UInt32) : Model FloatFormat.binary32 :=
  ExecFloat.Binary.toModel (ExecFloat.Binary.ofBits32 u)

theorem rawModel_eq_native32 (u : UInt32) :
    rawModel u = Model.NativeBinary32.ofUInt32 u := rfl

theorem rawModel_eq_ofUInt32 (u : UInt32) :
    rawModel u = Model.ofUInt32 (fmt := FloatFormat.binary32) u := by
  change Model.ofBits u.toBitVec =
    Model.ofBits (BitVec.ofNat 32 u.toBitVec.toNat)
  rw [BitVec.ofNat_toNat]

theorem modelCanonicalOfFinite {fmt : FloatFormat} (x : Model fmt)
    (hx : (Model.toModel x).isFinite = true) : Model.IsModelCanonical x := by
  constructor
  intro he hm
  have hnan : Model.toModel x = Float.Model.UnpackedFloat.notANumber := by
    simp only [Model.toModel, Float.Model.UnpackedFloat.unpack, he, hm, ite_true, ite_false]
  rw [hnan] at hx
  cases hx

theorem modelCanonical_of_decode {fmt : FloatFormat}
    (hfmt : fmt.isIEEE = true) (x : Model fmt) {d : FloatLib.Numerics.Dyadic}
    (hd : Model.toDyadic? x = some d) : Model.IsModelCanonical x := by
  apply modelCanonicalOfFinite
  rw [Model.toDyadic?_ieee_eq_model fmt hfmt x] at hd
  cases hx : Model.toModel x <;>
    simp_all [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.isFinite]

theorem nativeModel_ofBits_of_decode (u : UInt32) {d : FloatLib.Numerics.Dyadic}
    (hd : Model.toDyadic? (rawModel u) = some d) :
    nativeModel (Float32.ofBits u) = rawModel u := by
  have hc : Model.IsModelCanonical (rawModel u) :=
    modelCanonical_of_decode (by decide) (rawModel u) hd
  change nativeModel (ExecFloat.Binary.toFloat32 (ExecFloat.Binary.ofBits32 u)) = rawModel u
  unfold nativeModel
  rw [ExecFloat.Binary.toModel_ofFloat32, ExecFloat.Binary.toModel_toFloat32_eq,
    Model.ofFloat32Model_toFloat32Model]
  exact Model.canonicalizeModel_eq_self _ hc

theorem nativeModel_ofBits_decode (u : UInt32) {d : FloatLib.Numerics.Dyadic}
    (hd : Model.toDyadic? (rawModel u) = some d) :
    Model.toDyadic? (nativeModel (Float32.ofBits u)) = some d := by
  rw [nativeModel_ofBits_of_decode u hd]
  exact hd

theorem nativeFinite_of_decode (x : Float32) {d : FloatLib.Numerics.Dyadic}
    (hd : Model.toDyadic? (nativeModel x) = some d) :
    x.isFinite = true := by
  rw [Model.toDyadic?_ieee_eq_model FloatFormat.binary32 (by decide)
    (nativeModel x)] at hd
  rw [nativeModel, ExecFloat.Binary.toModel_ofFloat32,
    Model.toModel_ofFloat32Model] at hd
  change x.toModel.unpack.isFinite = true
  cases hx : x.toModel.unpack <;>
    simp_all [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.isFinite]

theorem native_eq_of_model_eq (x y : Float32)
    (h : nativeModel x = nativeModel y) : x = y := by
  have hw : ExecFloat.Binary.ofFloat32 x = ExecFloat.Binary.ofFloat32 y :=
    ExecFloat.Binary.toModel_inj.mp h
  have hn := congrArg ExecFloat.Binary.toFloat32 hw
  simpa only [ExecFloat.Binary.toFloat32_ofFloat32] using hn

theorem native_mul_eq_of_raw_model_mul_eq
    (x y : Float32) (u : UInt32)
    (hx : x.isFinite = true) (hy : y.isFinite = true)
    (hm : Model.mul (nativeModel x) (nativeModel y) = rawModel u) :
    x * y = Float32.ofBits u := by
  have hw : ExecFloat.Binary.ofFloat32 (x * y) = ExecFloat.Binary.ofBits32 u := by
    apply ExecFloat.Binary.toModel_inj.mp
    rw [NativeBridge.toModelNativeMul x y hx hy]
    exact hm
  calc
    x * y = ExecFloat.Binary.toFloat32 (ExecFloat.Binary.ofFloat32 (x * y)) :=
      (ExecFloat.Binary.toFloat32_ofFloat32 _).symm
    _ = ExecFloat.Binary.toFloat32 (ExecFloat.Binary.ofBits32 u) :=
      congrArg ExecFloat.Binary.toFloat32 hw
    _ = Float32.ofBits u := rfl

theorem native_mul_bits_eq_of_raw_model_mul_eq
    (x y : Float32) (u : UInt32)
    (hx : x.isFinite = true) (hy : y.isFinite = true)
    (hm : Model.mul (nativeModel x) (nativeModel y) = rawModel u) :
    (x * y).toBits = u := by
  have hw : ExecFloat.Binary.ofFloat32 (x * y) = ExecFloat.Binary.ofBits32 u := by
    apply ExecFloat.Binary.toModel_inj.mp
    rw [NativeBridge.toModelNativeMul x y hx hy]
    exact hm
  have hn := congrArg ExecFloat.Binary.toBits32 hw
  simpa only [ExecFloat.Binary.toBits32_ofFloat32,
    ExecFloat.Binary.toBits32_ofBits32] using hn

theorem native_mul_eq_of_decoded_raw_model_mul_eq
    (x y : Float32) (u : UInt32)
    {dx dy : FloatLib.Numerics.Dyadic}
    (hx : Model.toDyadic? (nativeModel x) = some dx)
    (hy : Model.toDyadic? (nativeModel y) = some dy)
    (hm : Model.mul (nativeModel x) (nativeModel y) = rawModel u) :
    x * y = Float32.ofBits u :=
  native_mul_eq_of_raw_model_mul_eq x y u
    (nativeFinite_of_decode x hx) (nativeFinite_of_decode y hy) hm

end R2W01c
