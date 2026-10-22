import ContractTensor

namespace R2W01b

def magnitude (u : UInt32) : UInt32 :=
  u &&& 0x7fffffff

def fastOK (u : UInt32) : Bool :=
  let a := magnitude u
  decide (0x0bffffff ≤ a - 1) && decide (a < 0x7f800000)

def NormalBand (u : UInt32) : Prop :=
  0x0c000000 ≤ magnitude u ∧ magnitude u < 0x7f800000

theorem wrap_gate_iff (a : UInt32) :
    (decide (0x0bffffff ≤ a - 1) && decide (a < 0x7f800000)) = true ↔
      a = 0 ∨ (0x0c000000 ≤ a ∧ a < 0x7f800000) := by
  have ha := a.toNat_lt_size
  simp only [Bool.and_eq_true, decide_eq_true_eq, UInt32.le_iff_toNat_le,
    UInt32.lt_iff_toNat_lt, UInt32.toNat_sub, ← UInt32.toNat_inj]
  change a.toNat < 4294967296 at ha
  change
    (201326591 ≤ (4294967295 + a.toNat) % 4294967296 ∧
      a.toNat < 2139095040) ↔
    (a.toNat = 0 ∨ (201326592 ≤ a.toNat ∧ a.toNat < 2139095040))
  omega

theorem fastOK_iff (u : UInt32) :
    fastOK u = true ↔ magnitude u = 0 ∨ NormalBand u := by
  exact wrap_gate_iff (magnitude u)

theorem magnitude_toNat (u : UInt32) :
    (magnitude u).toNat = u.toNat % 2147483648 := by
  rw [magnitude, UInt32.toNat_and]
  change u.toNat &&& (2 ^ 31 - 1) = u.toNat % 2 ^ 31
  exact Nat.and_two_pow_sub_one_eq_mod u.toNat 31

theorem magnitude_zero_iff (u : UInt32) :
    magnitude u = 0 ↔ u = 0 ∨ u = 0x80000000 := by
  have hu := u.toNat_lt_size
  simp only [← UInt32.toNat_inj, magnitude_toNat]
  change u.toNat < 4294967296 at hu
  change
    u.toNat % 2147483648 = 0 ↔ u.toNat = 0 ∨ u.toNat = 2147483648
  omega

theorem fastOK_positive_zero : fastOK 0 = true := by
  decide

theorem fastOK_negative_zero : fastOK 0x80000000 = true := by
  decide

def tableIndex (u : UInt32) : UInt32 :=
  u >>> 23

def mantissa (u : UInt32) : UInt32 :=
  (u &&& 0x7fffff) ||| 0x800000

def scaleBits (j : UInt32) : UInt32 :=
  let e := j &&& 255
  let s := (j &&& 256) <<< 23
  if decide (24 ≤ e) && decide (e ≤ 254) then
    s ||| ((e - 23) <<< 23)
  else
    s

theorem tableIndex_toNat_lt (u : UInt32) :
    (tableIndex u).toNat < 512 := by
  have hu := u.toNat_lt_size
  rw [tableIndex, UInt32.toNat_shiftRight]
  change u.toNat >>> 23 < 512
  rw [Nat.shiftRight_eq_div_pow]
  change u.toNat < 4294967296 at hu
  change u.toNat / 8388608 < 512
  omega

def scaleTable : Array Float32 :=
  Array.ofFn fun j : Fin 512 => Float32.ofBits (scaleBits (UInt32.ofNat j.val))

theorem scaleTable_size : scaleTable.size = 512 := by
  simp only [scaleTable, Array.size_ofFn]

theorem scaleTable_entry (j : Fin 512) :
    scaleTable[j.val]'(by rw [scaleTable_size]; exact j.isLt) =
      Float32.ofBits (scaleBits (UInt32.ofNat j.val)) := by
  simp only [scaleTable, Array.getElem_ofFn]

def scaleAt (u : UInt32) : Float32 :=
  scaleTable[(tableIndex u).toNat]'(by
    rw [scaleTable_size]
    exact tableIndex_toNat_lt u)

theorem scaleAt_eq (u : UInt32) :
    scaleAt u = Float32.ofBits (scaleBits (tableIndex u)) := by
  simp only [scaleAt, scaleTable, Array.getElem_ofFn, UInt32.ofNat_toNat]

theorem zero_fields (u : UInt32) (h : magnitude u = 0) :
    (u = 0 ∧ tableIndex u = 0 ∧ mantissa u = 0x800000 ∧
      scaleBits (tableIndex u) = 0) ∨
    (u = 0x80000000 ∧ tableIndex u = 256 ∧ mantissa u = 0x800000 ∧
      scaleBits (tableIndex u) = 0x80000000) := by
  cases (magnitude_zero_iff u).mp h with
  | inl hu =>
    subst u
    left
    decide
  | inr hu =>
    subst u
    right
    decide

theorem scaleAt_positive_zero : scaleAt 0 = Float32.ofBits 0 := by
  rw [scaleAt_eq]
  exact congrArg Float32.ofBits (by decide : scaleBits (tableIndex 0) = 0)

theorem scaleAt_negative_zero :
    scaleAt 0x80000000 = Float32.ofBits 0x80000000 := by
  rw [scaleAt_eq]
  exact congrArg Float32.ofBits
    (by decide : scaleBits (tableIndex 0x80000000) = 0x80000000)

theorem zero_mantissa_conversion :
    (0x800000 : UInt32).toFloat32 = Float32.ofBits 0x4b000000 := by
  decide

def tableProduct (u : UInt32) : Float32 :=
  (mantissa u).toFloat32 * scaleAt u

theorem tableProduct_positive_zero : tableProduct 0 = Float32.ofBits 0 := by
  rw [tableProduct, scaleAt_positive_zero]
  decide

theorem tableProduct_negative_zero :
    tableProduct 0x80000000 = Float32.ofBits 0x80000000 := by
  rw [tableProduct, scaleAt_negative_zero]
  decide

theorem tableProduct_zero_eq (u : UInt32) (h : magnitude u = 0) :
    tableProduct u = Float32.ofBits u := by
  cases (magnitude_zero_iff u).mp h with
  | inl hu =>
    subst u
    exact tableProduct_positive_zero
  | inr hu =>
    subst u
    exact tableProduct_negative_zero

theorem tableProduct_zero_bits_eq (u : UInt32) (h : magnitude u = 0) :
    (tableProduct u).toBits = (Float32.ofBits u).toBits := by
  exact congrArg Float32.toBits (tableProduct_zero_eq u h)

theorem zero_ofBits_toBits (u : UInt32) (h : magnitude u = 0) :
    (Float32.ofBits u).toBits = u := by
  cases (magnitude_zero_iff u).mp h with
  | inl hu => subst u; decide
  | inr hu => subst u; decide

theorem tableProduct_zero_bits (u : UInt32) (h : magnitude u = 0) :
    (tableProduct u).toBits = u := by
  exact (tableProduct_zero_bits_eq u h).trans (zero_ofBits_toBits u h)

theorem float32_eq_of_toBits_eq {x y : Float32} (h : x.toBits = y.toBits) :
    x = y := by
  cases x with
  | ofModel xm =>
    cases y with
    | ofModel ym =>
      cases xm with
      | mk xb xv =>
        cases ym with
        | mk yb yv =>
          change xb = yb at h
          cases h
          rfl

theorem float32_ofBits_toBits (x : Float32) : Float32.ofBits x.toBits = x := by
  simpa only [FloatLib.Floats.ExecFloat.Binary.toFloat32,
    FloatLib.Floats.ExecFloat.Binary.toBits32_ofFloat32] using
    FloatLib.Floats.ExecFloat.Binary.toFloat32_ofFloat32 x

theorem float32_eq_of_raw_bits {x : Float32} {u : UInt32} (h : x.toBits = u) :
    x = Float32.ofBits u := by
  calc
    x = Float32.ofBits x.toBits := (float32_ofBits_toBits x).symm
    _ = Float32.ofBits u := congrArg Float32.ofBits h

theorem normal_value_of_bits
    (hNormalBits : ∀ u, NormalBand u →
      (tableProduct u).toBits = (Float32.ofBits u).toBits) :
    ∀ u, NormalBand u → tableProduct u = Float32.ofBits u := by
  intro u hn
  exact float32_eq_of_toBits_eq (hNormalBits u hn)

theorem normal_value_of_raw_bits
    (hNormalRawBits : ∀ u, NormalBand u → (tableProduct u).toBits = u) :
    ∀ u, NormalBand u → tableProduct u = Float32.ofBits u := by
  intro u hn
  exact float32_eq_of_raw_bits (hNormalRawBits u hn)

theorem tableProduct_of_fastOK
    (hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u)
    (u : UInt32) (h : fastOK u = true) :
    tableProduct u = Float32.ofBits u := by
  cases (fastOK_iff u).mp h with
  | inl hz => exact tableProduct_zero_eq u hz
  | inr hn => exact hNormal u hn

def convert (u : UInt32) : Float32 :=
  if fastOK u then tableProduct u else Float32.ofBits u

theorem convert_zero_path (u : UInt32) (h : magnitude u = 0) :
    convert u = tableProduct u := by
  have hf : fastOK u = true := (fastOK_iff u).mpr (Or.inl h)
  rw [convert, if_pos hf]

theorem convert_fallback (u : UInt32) (h : fastOK u = false) :
    convert u = Float32.ofBits u := by
  simp [convert, h]

theorem convert_eq
    (hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u)
    (u : UInt32) : convert u = Float32.ofBits u := by
  by_cases h : fastOK u = true
  · rw [convert, if_pos h]
    exact tableProduct_of_fastOK hNormal u h
  · rw [convert, if_neg h]

theorem convert_bits_eq
    (hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u)
    (u : UInt32) : (convert u).toBits = (Float32.ofBits u).toBits := by
  exact congrArg Float32.toBits (convert_eq hNormal u)

theorem convert_eq_of_normal_bits
    (hNormalBits : ∀ u, NormalBand u →
      (tableProduct u).toBits = (Float32.ofBits u).toBits)
    (u : UInt32) : convert u = Float32.ofBits u := by
  exact convert_eq (normal_value_of_bits hNormalBits) u

theorem convert_eq_of_normal_raw_bits
    (hNormalRawBits : ∀ u, NormalBand u → (tableProduct u).toBits = u)
    (u : UInt32) : convert u = Float32.ofBits u := by
  exact convert_eq (normal_value_of_raw_bits hNormalRawBits) u

theorem replace_decoder {α : Sort _}
    (hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u)
    (core : (UInt32 → Float32) → α) : core convert = core Float32.ofBits := by
  exact congrArg core (funext (convert_eq hNormal))

theorem foldl_convert_eq
    (hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u)
    (xs : List UInt32) (step : Float32 → Float32 → Float32) (acc : Float32) :
    xs.foldl (fun z u => step z (convert u)) acc =
      xs.foldl (fun z u => step z (Float32.ofBits u)) acc := by
  induction xs generalizing acc with
  | nil => rfl
  | cons u us ih =>
    simp only [List.foldl_cons, convert_eq hNormal u]
    exact ih _

end R2W01b

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

namespace R2W01c

open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

theorem uint32_model_eq_roundDyadic (n : UInt32) :
    Model.ofFloat32Model n.toFloat32.toModel =
      Model.roundDyadic FloatFormat.binary32
        { negative := false, significand := n.toNat, exponent := 0 } := by
  change Model.ofFloat32Model
      (Float32.Model.pack
        (Float.Model.UnpackedFloat.ofUInt32 Float.Model.Format.binary32 n)) = _
  rw [Model.ofFloat32Model_pack]
  change Model.ofModel FloatFormat.binary32
      (Float.Model.UnpackedFloat.ofInt FloatFormat.binary32.toModel
        (n.toNat : Int)) = _
  simpa [Dyadic.ofScaledInt] using
    Model.ofModel_ofInt_eq_roundDyadic FloatFormat.binary32
      (by decide) (n.toNat : Int)

theorem uint32_model_eq_of_decode (n : UInt32)
    (z : Model FloatFormat.binary32)
    (hz : Model.toDyadic? z =
      some { negative := false, significand := n.toNat, exponent := 0 }) :
    Model.ofFloat32Model n.toFloat32.toModel = z := by
  rw [uint32_model_eq_roundDyadic]
  change Model.roundDyadicWithRounding FloatFormat.binary32 .nearestEven
    { negative := false, significand := n.toNat, exponent := 0 } = z
  exact Model.roundDyadicWithRounding_toDyadic? (by decide) .nearestEven hz

theorem fields32_toDyadic (s : Bool) (e f : Nat)
    (he0 : 0 < e) (he : e < 255) (hf : f < 8388608) :
    Model.toDyadic? (Model.ofFields FloatFormat.binary32 s e f) =
      some { negative := s, significand := 8388608 + f,
        exponent := (e : Int) - 150 } := by
  have h := Model.toDyadic?_ofFields_normal FloatFormat.binary32 s e f
    (Nat.ne_of_gt he0) he hf
  change Model.toDyadic? (Model.ofFields FloatFormat.binary32 s e f) =
    some { negative := s, significand := 8388608 + f,
      exponent := (e : Int) - 127 - 23 } at h
  have hexp : (e : Int) - 127 - 23 = (e : Int) - 150 := by omega
  simpa only [hexp] using h

theorem uint32_mantissa_model_eq_fields (n : UInt32)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat < 16777216) :
    Model.ofFloat32Model n.toFloat32.toModel =
      Model.ofFields FloatFormat.binary32 false 150 (n.toNat - 8388608) := by
  apply uint32_model_eq_of_decode
  have hf : n.toNat - 8388608 < 8388608 := by omega
  have hsum : 8388608 + (n.toNat - 8388608) = n.toNat := by omega
  simpa only [hsum] using
    fields32_toDyadic false 150 (n.toNat - 8388608) (by decide) (by decide) hf

theorem uint32_mantissa_model_decode (n : UInt32)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat < 16777216) :
    Model.toDyadic? (Model.ofFloat32Model n.toFloat32.toModel) =
      some { negative := false, significand := n.toNat, exponent := 0 } := by
  rw [uint32_mantissa_model_eq_fields n hlo hhi]
  have hf : n.toNat - 8388608 < 8388608 := by omega
  have hsum : 8388608 + (n.toNat - 8388608) = n.toNat := by omega
  simpa only [hsum] using
    fields32_toDyadic false 150 (n.toNat - 8388608) (by decide) (by decide) hf

theorem uint32_mantissa_model_finite (n : UInt32)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat < 16777216) :
    Model.isFinite (Model.ofFloat32Model n.toFloat32.toModel) = true := by
  exact Model.isFinite_eq_true_of_toDyadic?_some
    (uint32_mantissa_model_decode n hlo hhi)

theorem uint32_mantissa_model_toReal (n : UInt32)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat < 16777216) :
    Model.toReal (Model.ofFloat32Model n.toFloat32.toModel) = (n.toNat : Real) := by
  rw [Model.toReal_eq, uint32_mantissa_model_decode n hlo hhi]
  simp [Dyadic.toReal, Dyadic.signedSignificand]

end R2W01c

namespace R2W01cModel

open FloatLib
open FloatLib.Floats.Formats.BinaryInterchange
open Model

theorem mul_eq_of_finite_value
    {fmt : FloatFormat} (x y z : Model fmt)
    (hfmt : fmt.isIEEE = true)
    (hx : isFinite x = true) (hy : isFinite y = true)
    (hz : isFinite z = true) (hz0 : toReal z ≠ 0)
    (hvalue : toReal x * toReal y = toReal z) :
    mul x y = z := by
  have hbound : |toReal x| * |toReal y| ≤ toReal (posMaxFinite fmt) := by
    rw [← abs_mul, hvalue]
    exact abs_toReal_le_posMaxFinite_of_isIEEE_of_isFinite z hfmt hz
  have hmulfinite : isFinite (mul x y) = true :=
    isFinite_mul_of_abs_mul_le_posMaxFinite x y hfmt hx hy hbound
  have hmulvalue : toReal (mul x y) = toReal z := by
    rw [toReal_mul_eq_roundAt x y hfmt hx hy hmulfinite,
      hvalue, roundAt_toReal_eq z hz]
  exact eq_of_toReal_eq_of_nonzero hmulfinite hz hmulvalue
    (by rw [hmulvalue]; exact hz0)

theorem dyadic_scale_value (sign : Bool) (m k : Nat) (e : Int) :
    (Numerics.Dyadic.mk false m 0).toReal *
      (Numerics.Dyadic.mk sign (2 ^ k) e).toReal =
      (Numerics.Dyadic.mk sign m (e + (k : Int))).toReal := by
  cases sign <;>
    simp [Numerics.Dyadic.toReal, Numerics.Dyadic.signedSignificand,
      zpow_add₀ (by norm_num : (2 : ℝ) ≠ 0)] <;> ring

theorem mul_eq_of_scale_decodes
    {fmt : FloatFormat} (x y z : Model fmt)
    (hfmt : fmt.isIEEE = true) (sign : Bool) (m k : Nat) (e : Int)
    (hm : m ≠ 0)
    (hx : toDyadic? x = some ⟨false, m, 0⟩)
    (hy : toDyadic? y = some ⟨sign, 2 ^ k, e⟩)
    (hz : toDyadic? z = some ⟨sign, m, e + (k : Int)⟩) :
    mul x y = z := by
  have hxfinite : isFinite x = true := isFinite_eq_true_of_toDyadic?_some hx
  have hyfinite : isFinite y = true := isFinite_eq_true_of_toDyadic?_some hy
  have hzfinite : isFinite z = true := isFinite_eq_true_of_toDyadic?_some hz
  have hz0 : toReal z ≠ 0 := by
    have hd0 : (Numerics.Dyadic.mk sign m (e + (k : Int))).toReal ≠ 0 :=
      (Dyadic.toReal_eq_zero_iff _).not.mpr hm
    simpa only [toReal_eq, hz] using hd0
  apply mul_eq_of_finite_value x y z hfmt hxfinite hyfinite hzfinite hz0
  simpa only [toReal_eq, hx, hy, hz] using dyadic_scale_value sign m k e

theorem binary32_mantissa_scale_mul
    (x y z : Model FloatFormat.binary32) (sign : Bool) (m E : Nat)
    (hm : m ≠ 0)
    (hx : toDyadic? x = some ⟨false, m, 0⟩)
    (hy : toDyadic? y = some ⟨sign, 2 ^ 23, (E : Int) - 173⟩)
    (hz : toDyadic? z = some ⟨sign, m, (E : Int) - 150⟩) :
    mul x y = z := by
  apply mul_eq_of_scale_decodes x y z (by decide)
    sign m 23 ((E : Int) - 173) hm hx hy
  have he : (E : Int) - 173 + ((23 : Nat) : Int) = (E : Int) - 150 := by
    omega
  simpa only [he] using hz

end R2W01cModel

namespace R2W01c

open FloatLib.Floats.Formats.BinaryInterchange
open R2W01b

abbrev raw32 (u : UInt32) : Model FloatFormat.binary32 :=
  Model.ofUInt32 u

def wordSign (u : UInt32) : Bool :=
  decide (2147483648 ≤ u.toNat)

def wordExp (u : UInt32) : Nat :=
  u.toNat / 8388608 % 256

def wordFrac (u : UInt32) : Nat :=
  u.toNat % 8388608

theorem raw32_bits (u : UInt32) : (raw32 u).bits = u.toBitVec := by
  change BitVec.ofNat 32 u.toNat = u.toBitVec
  exact BitVec.ofNat_uInt32ToNat u

theorem raw32_sign (u : UInt32) : Model.signBit (raw32 u) = wordSign u := by
  simp only [Model.signBit_eq_msb, raw32_bits, BitVec.msb_eq_decide, wordSign]

theorem raw32_exp (u : UInt32) : Model.expField (raw32 u) = wordExp u := by
  unfold Model.expField
  rw [raw32_bits]
  change ((u.toBitVec >>> 23) &&& (BitVec.ofNat 32 255)).toNat = wordExp u
  rw [BitVec.toNat_and, BitVec.toNat_ushiftRight]
  change (u.toNat >>> 23) &&& (2 ^ 8 - 1) = u.toNat / 8388608 % 256
  rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]

theorem raw32_frac (u : UInt32) : Model.fracField (raw32 u) = wordFrac u := by
  unfold Model.fracField
  rw [raw32_bits]
  change (u.toBitVec &&& (BitVec.ofNat 32 8388607)).toNat = wordFrac u
  rw [BitVec.toNat_and]
  change u.toNat &&& (2 ^ 23 - 1) = u.toNat % 2 ^ 23
  exact Nat.and_two_pow_sub_one_eq_mod u.toNat 23

theorem raw32_eq_fields (u : UInt32) :
    raw32 u = Model.ofFields FloatFormat.binary32 (wordSign u) (wordExp u)
      (wordFrac u) := by
  rw [← raw32_sign, ← raw32_exp, ← raw32_frac]
  exact (Model.ofFields_signBit_expField_fracField (raw32 u)).symm

theorem wordFrac_lt (u : UInt32) : wordFrac u < 8388608 :=
  Nat.mod_lt _ (by decide)

theorem mantissa_toNat (u : UInt32) :
    (mantissa u).toNat = 8388608 + wordFrac u := by
  rw [mantissa, UInt32.toNat_or, UInt32.toNat_and]
  change (u.toNat &&& (2 ^ 23 - 1)) ||| 2 ^ 23 = 8388608 + wordFrac u
  rw [Nat.and_two_pow_sub_one_eq_mod,
    Nat.or_two_pow_eq_add_of_lt (Nat.mod_lt u.toNat (by decide : 0 < 2 ^ 23))]
  exact Nat.add_comm _ _

theorem mantissa_bounds (u : UInt32) :
    8388608 ≤ (mantissa u).toNat ∧ (mantissa u).toNat < 16777216 := by
  rw [mantissa_toNat]
  have hf := wordFrac_lt u
  omega

theorem normal_wordExp_bounds (u : UInt32) (hn : NormalBand u) :
    24 ≤ wordExp u ∧ wordExp u < 255 := by
  rcases hn with ⟨hl, hh⟩
  rw [UInt32.le_iff_toNat_le, magnitude_toNat] at hl
  rw [UInt32.lt_iff_toNat_lt, magnitude_toNat] at hh
  change 201326592 ≤ u.toNat % 2147483648 at hl
  change u.toNat % 2147483648 < 2139095040 at hh
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  unfold wordExp
  omega

theorem tableIndex_nat (u : UInt32) :
    (tableIndex u).toNat = u.toNat / 8388608 := by
  rw [tableIndex, UInt32.toNat_shiftRight]
  change u.toNat >>> 23 = u.toNat / 8388608
  exact Nat.shiftRight_eq_div_pow u.toNat 23

theorem tableExp_nat (u : UInt32) :
    (tableIndex u &&& 255).toNat = wordExp u := by
  rw [UInt32.toNat_and, tableIndex_nat]
  change (u.toNat / 8388608) &&& (2 ^ 8 - 1) =
    u.toNat / 8388608 % 2 ^ 8
  exact Nat.and_two_pow_sub_one_eq_mod _ 8

theorem high_bit_of_lt512 (n : Nat) (hn : n < 512) :
    n &&& 256 = n / 256 * 256 := by
  change n &&& 2 ^ 8 = n / 256 * 256
  rw [Nat.and_two_pow, Nat.testBit_eq_decide_div_mod_eq]
  change (decide (n / 256 % 2 = 1)).toNat * 256 = n / 256 * 256
  by_cases h : n < 256
  · have hd : n / 256 = 0 := Nat.div_eq_of_lt h
    simp [hd]
  · have hd : n / 256 = 1 := by omega
    simp [hd]

theorem tableSign_nat (u : UInt32) :
    ((tableIndex u &&& 256) <<< 23).toNat =
      u.toNat / 2147483648 * 2147483648 := by
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  have hj : u.toNat / 8388608 < 512 := by omega
  rw [UInt32.toNat_shiftLeft, UInt32.toNat_and, tableIndex_nat]
  change (((u.toNat / 8388608) &&& 256) <<< 23) % 4294967296 = _
  rw [high_bit_of_lt512 _ hj, Nat.shiftLeft_eq]
  change (u.toNat / 8388608 / 256 * 256 * 8388608) % 4294967296 = _
  omega

theorem scaleBits_nat (u : UInt32) (hn : NormalBand u) :
    (scaleBits (tableIndex u)).toNat =
      u.toNat / 2147483648 * 2147483648 + (wordExp u - 23) * 8388608 := by
  have he := normal_wordExp_bounds u hn
  have het := tableExp_nat u
  have helo : (24 : UInt32) ≤ (tableIndex u &&& 255) := by
    rw [UInt32.le_iff_toNat_le, het]
    exact he.1
  have hehi : (tableIndex u &&& 255) ≤ (254 : UInt32) := by
    rw [UInt32.le_iff_toNat_le, het]
    change wordExp u ≤ 254
    omega
  have hg :
      (decide (24 ≤ (tableIndex u &&& 255)) &&
        decide ((tableIndex u &&& 255) ≤ 254)) = true := by
    simp only [Bool.and_eq_true, decide_eq_true_eq]
    exact ⟨helo, hehi⟩
  have hsub : ((tableIndex u &&& 255) - 23).toNat = wordExp u - 23 := by
    have hle : (23 : UInt32) ≤ (tableIndex u &&& 255) := by
      rw [UInt32.le_iff_toNat_le, het]
      change 23 ≤ wordExp u
      omega
    simpa only [het] using
      UInt32.toNat_sub_of_le (tableIndex u &&& 255) 23 hle
  have hshift : (((tableIndex u &&& 255) - 23) <<< 23).toNat =
      (wordExp u - 23) * 8388608 := by
    rw [UInt32.toNat_shiftLeft, hsub]
    change ((wordExp u - 23) <<< 23) % 4294967296 = _
    rw [Nat.shiftLeft_eq]
    change ((wordExp u - 23) * 8388608) % 4294967296 = _
    exact Nat.mod_eq_of_lt (by omega)
  unfold scaleBits
  dsimp only
  rw [if_pos hg, UInt32.toNat_or, tableSign_nat, hshift]
  have hlo : (wordExp u - 23) * 8388608 < 2 ^ 31 := by
    change (wordExp u - 23) * 8388608 < 2147483648
    omega
  rw [Nat.mul_comm (u.toNat / 2147483648) 2147483648]
  exact (Nat.two_pow_add_eq_or_of_lt hlo (u.toNat / 2147483648)).symm

theorem scale_wordSign (u : UInt32) (hn : NormalBand u) :
    wordSign (scaleBits (tableIndex u)) = wordSign u := by
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  have he := normal_wordExp_bounds u hn
  apply Bool.eq_iff_iff.mpr
  simp only [wordSign, decide_eq_true_eq]
  rw [scaleBits_nat u hn]
  omega

theorem scale_wordExp (u : UInt32) (hn : NormalBand u) :
    wordExp (scaleBits (tableIndex u)) = wordExp u - 23 := by
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  have he := normal_wordExp_bounds u hn
  change (scaleBits (tableIndex u)).toNat / 8388608 % 256 = wordExp u - 23
  rw [scaleBits_nat u hn]
  omega

theorem scale_wordFrac (u : UInt32) (hn : NormalBand u) :
    wordFrac (scaleBits (tableIndex u)) = 0 := by
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  have he := normal_wordExp_bounds u hn
  change (scaleBits (tableIndex u)).toNat % 8388608 = 0
  rw [scaleBits_nat u hn]
  omega

theorem normal_raw32_decode (u : UInt32) (hn : NormalBand u) :
    Model.toDyadic? (raw32 u) =
      some ⟨wordSign u, (mantissa u).toNat, (wordExp u : Int) - 150⟩ := by
  have he := normal_wordExp_bounds u hn
  rw [raw32_eq_fields, mantissa_toNat]
  exact fields32_toDyadic (wordSign u) (wordExp u) (wordFrac u)
    (by omega) he.2 (wordFrac_lt u)

theorem scale_raw32_decode (u : UInt32) (hn : NormalBand u) :
    Model.toDyadic? (raw32 (scaleBits (tableIndex u))) =
      some ⟨wordSign u, 8388608, (wordExp u : Int) - 173⟩ := by
  have he := normal_wordExp_bounds u hn
  rw [raw32_eq_fields, scale_wordSign u hn, scale_wordExp u hn, scale_wordFrac u hn]
  have hd := fields32_toDyadic (wordSign u) (wordExp u - 23) 0
    (by omega) (by omega) (by decide)
  have hexp : ((wordExp u - 23 : Nat) : Int) - 150 =
      (wordExp u : Int) - 173 := by omega
  simpa only [Nat.add_zero, hexp] using hd

end R2W01c

namespace R2W01c

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open R2W01b

theorem mantissa_native_decode (u : UInt32) :
    Model.toDyadic? (nativeModel (mantissa u).toFloat32) =
      some ⟨false, (mantissa u).toNat, 0⟩ := by
  have hm := mantissa_bounds u
  simpa only [nativeModel, ExecFloat.Binary.toModel_ofFloat32] using
    uint32_mantissa_model_decode (mantissa u) hm.1 hm.2

theorem scale_native_decode (u : UInt32) (hn : NormalBand u) :
    Model.toDyadic? (nativeModel (scaleAt u)) =
      some ⟨wordSign u, 2 ^ 23, (wordExp u : Int) - 173⟩ := by
  rw [scaleAt_eq]
  apply nativeModel_ofBits_decode
  rw [rawModel_eq_ofUInt32]
  exact scale_raw32_decode u hn

theorem target_raw_decode (u : UInt32) (hn : NormalBand u) :
    Model.toDyadic? (rawModel u) =
      some ⟨wordSign u, (mantissa u).toNat, (wordExp u : Int) - 150⟩ := by
  rw [rawModel_eq_ofUInt32]
  exact normal_raw32_decode u hn

theorem normal_model_mul (u : UInt32) (hn : NormalBand u) :
    Model.mul (nativeModel (mantissa u).toFloat32) (nativeModel (scaleAt u)) =
      rawModel u := by
  apply R2W01cModel.binary32_mantissa_scale_mul
    (nativeModel (mantissa u).toFloat32) (nativeModel (scaleAt u)) (rawModel u)
    (wordSign u) (mantissa u).toNat (wordExp u)
  · have hm := (mantissa_bounds u).1
    omega
  · exact mantissa_native_decode u
  · exact scale_native_decode u hn
  · exact target_raw_decode u hn

theorem normal_eq (u : UInt32) (hn : NormalBand u) :
    tableProduct u = Float32.ofBits u := by
  exact native_mul_eq_of_decoded_raw_model_mul_eq
    (mantissa u).toFloat32 (scaleAt u) u
    (mantissa_native_decode u) (scale_native_decode u hn) (normal_model_mul u hn)

theorem normal_bits (u : UInt32) (hn : NormalBand u) :
    (tableProduct u).toBits = u := by
  exact native_mul_bits_eq_of_raw_model_mul_eq
    (mantissa u).toFloat32 (scaleAt u) u
    (nativeFinite_of_decode _ (mantissa_native_decode u))
    (nativeFinite_of_decode _ (scale_native_decode u hn)) (normal_model_mul u hn)

theorem normal_finite (u : UInt32) (hn : NormalBand u) :
    (tableProduct u).isFinite = true := by
  rw [normal_eq u hn]
  exact nativeFinite_of_decode _
    (nativeModel_ofBits_decode u (target_raw_decode u hn))

theorem convert_eq (u : UInt32) : convert u = Float32.ofBits u := by
  exact R2W01b.convert_eq normal_eq u

theorem convert_bits_eq (u : UInt32) :
    (convert u).toBits = (Float32.ofBits u).toBits := by
  exact congrArg Float32.toBits (convert_eq u)

theorem replace_decoder {α : Sort _}
    (core : (UInt32 → Float32) → α) : core convert = core Float32.ofBits := by
  exact congrArg core (funext convert_eq)

theorem foldl_convert_eq
    (xs : List UInt32) (step : Float32 → Float32 → Float32) (acc : Float32) :
    xs.foldl (fun z u => step z (convert u)) acc =
      xs.foldl (fun z u => step z (Float32.ofBits u)) acc := by
  exact R2W01b.foldl_convert_eq normal_eq xs step acc

end R2W01c
