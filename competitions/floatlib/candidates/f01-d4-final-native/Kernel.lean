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


/-!
The full entry's incumbent, what every entry starts from and must beat: the best proven `add`
(`tuned`, 0.50x of `ExecFloat.add`) and `mul` (`mul/fast`, 0.55x of `ExecFloat.mul`), copied with
their proofs into namespaces of their own, with TorchLean's `sum` and `bmm` built from them, at
0.56x of the baseline's time.
-/

namespace R2W01b

@[inline] def magnitude (u : UInt32) : UInt32 :=
  u &&& 0x7fffffff

@[inline] def fastOK (u : UInt32) : Bool :=
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

@[inline] def tableIndex (u : UInt32) : UInt32 :=
  u >>> 23

@[inline] def mantissa (u : UInt32) : UInt32 :=
  (u &&& 0x7fffff) ||| 0x800000

@[inline] def scaleBits (j : UInt32) : UInt32 :=
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

@[inline] def scaleAt (u : UInt32) : Float32 :=
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

@[inline] def tableProduct (u : UInt32) : Float32 :=
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

@[inline] def convert (u : UInt32) : Float32 :=
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
  Model.ofFloat32Model x.toModel

abbrev rawModel (u : UInt32) : Model FloatFormat.binary32 :=
  ExecFloat.Binary.toModel (ExecFloat.Binary.ofBits32 u)

theorem rawModel_eq_native32 (u : UInt32) :
    rawModel u = Model.NativeBinary32.ofUInt32 u := rfl

theorem rawModel_eq_ofUInt32 (u : UInt32) :
    rawModel u = Model.ofUInt32 (fmt := FloatFormat.binary32) u := by
  change Model.ofModelBits (fmt := FloatFormat.binary32) u.toBitVec =
    Model.ofModelBits (fmt := FloatFormat.binary32) (BitVec.ofNat 32 u.toBitVec.toNat)
  simp [BitVec.ofNat_toNat]

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
  change Model.ofFloat32Model
    (ExecFloat.Binary.toFloat32 (ExecFloat.Binary.ofBits32 u)).toModel = rawModel u
  rw [ExecFloat.Binary.toModel_toFloat32_eq, Model.ofFloat32Model_toFloat32Model]
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
  rw [nativeModel, Model.toModel_ofFloat32Model] at hd
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
  have hn : ¬ (n.toNat : Int) < 0 := by omega
  simpa [Dyadic.ofScaledInt, hn] using
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
      some ⟨s, 8388608 + f, (e : Int) - 150⟩ := by
  have h := Model.toDyadic?_ofFields_normal FloatFormat.binary32 s e f
    (Nat.ne_of_gt he0) he hf
  change Model.toDyadic? (Model.ofFields FloatFormat.binary32 s e f) =
    some ⟨s, 8388608 + f, (e : Int) - 127 - 23⟩ at h
  have hexp : (e : Int) - 127 - 23 = (e : Int) - 150 := by omega
  simpa only [hexp] using h

theorem uint32_mantissa_model_eq_fields (n : UInt32)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat < 16777216) :
    Model.ofFloat32Model n.toFloat32.toModel =
      Model.ofFields FloatFormat.binary32 false 150 (n.toNat - 8388608) := by
  apply uint32_model_eq_of_decode
  have hf : n.toNat - 8388608 < 8388608 := by omega
  have hsum : 8388608 + (n.toNat - 8388608) = n.toNat := by omega
  simpa [hsum] using
    fields32_toDyadic false 150 (n.toNat - 8388608) (by decide) (by decide) hf

theorem uint32_mantissa_model_decode (n : UInt32)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat < 16777216) :
    Model.toDyadic? (Model.ofFloat32Model n.toFloat32.toModel) =
      some { negative := false, significand := n.toNat, exponent := 0 } := by
  rw [uint32_mantissa_model_eq_fields n hlo hhi]
  have hf : n.toNat - 8388608 < 8388608 := by omega
  have hsum : 8388608 + (n.toNat - 8388608) = n.toNat := by omega
  simpa [hsum] using
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
      zpow_add₀ (by norm_num : (2 : ℝ) ≠ 0)] <;> ring <;> simp

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
  rw [Model.signBit_eq_msb, raw32_bits]
  exact BitVec.msb_eq_decide u.toBitVec

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
    have h := UInt32.toNat_sub_of_le (tableIndex u &&& 255) 23 hle
    change ((tableIndex u &&& 255) - 23).toNat = (tableIndex u &&& 255).toNat - 23 at h
    simpa only [het] using h
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
  simpa only [nativeModel] using
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


namespace Submission

/-!
`fastlog` with two cheap-tier changes, and the proof that they change nothing.

The special-operand test is one compare per operand, `(a <<< 1) - 1 ≥ 0xfeffffff`, instead of
four comparisons: shifting out the sign and subtracting one wraps a zero to the top and puts every
exponent-0xff word above the bound. The rounding step never leaves machine words: `rseAny` is
`roundShiftRightEven` with a `UInt64` shift and `mkW` packs the fields as `UInt32`. `sp1_eq`,
`rseAny_eq` and `mkW_ofNat` prove each equal to what it replaces; everything after reuses
fastlog's chain down to `wordAdd_eq_spec`. No new floating-point reasoning.
-/

namespace TunedAdd

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
open Model.NativeBinary32

/-- One binary-search step for `log2` on the value: shift down by `k` if anything is left there. -/
@[inline] def sx (k x : UInt64) : UInt64 := bif x >>> k == 0 then x else x >>> k

/-- The same step on the running result: add `k` when the value moved. -/
@[inline] def sr (k x r : UInt64) : UInt64 := bif x >>> k == 0 then r else r + k

/-- `UInt64.log2` by binary search: six steps instead of one per bit. -/
@[inline] def fastLog2 (x0 : UInt64) : UInt64 :=
  let x1 := sx 32 x0
  let r1 := sr 32 x0 0
  let x2 := sx 16 x1
  let r2 := sr 16 x1 r1
  let x3 := sx 8 x2
  let r3 := sr 8 x2 r2
  let x4 := sx 4 x3
  let r4 := sr 4 x3 r3
  let x5 := sx 2 x4
  let r5 := sr 2 x4 r4
  sr 1 x5 r5

/-- `roundShiftRightEven` with a word shift; the caller passes 1 ≤ shift < 64. -/
@[inline] def rse (value shift : UInt64) : UInt64 :=
  let quotient := value >>> shift
  let remainder := value &&& ((1 <<< shift) - 1)
  let half := (1 : UInt64) <<< (shift - 1)
  if remainder < half then quotient
  else if remainder > half then quotient + 1
  else if (quotient &&& 1) == 0 then quotient
  else quotient + 1

/-- `rse` for any shift, matching roundShiftRightEven's 0 and ≥ 64 cases. -/
@[inline] def rseAny (value shift : UInt64) : UInt64 :=
  if shift == 0 then value
  else if shift < 64 then rse value shift
  else if shift == 64 then (if value > 0x8000000000000000 then 1 else 0)
  else 0

/-- `mkBits` on words. -/
@[inline] def mkW (sign : Bool) (e f : UInt32) : UInt32 :=
  (if sign then (0x80000000 : UInt32) else 0) ||| ((e &&& 0xff) <<< 23) ||| (f &&& 0x007fffff)

/-- The stored fraction of a normalised mantissa, as `mkBits` receives it: zero below 2^23. -/
@[inline] def fracW (n : UInt64) : UInt32 :=
  (if n < 0x800000 then 0 else n - 0x800000).toUInt32

/-- `roundProduct` with `fastLog2`, on words throughout. -/
@[inline] def roundP (sign : Bool) (product scale : UInt64) : UInt32 :=
  if product == 0 then
    if sign then 0x80000000 else 0
  else
    let leading := fastLog2 product
    let position := leading + scale
    if position < 172 then
      let fraction :=
        if scale < 149 then
          rseAny product (149 - scale)
        else
          product <<< (scale - 149)
      if fraction == 0 then
        if sign then 0x80000000 else 0
      else if fraction == 0x800000 then
        mkW sign 1 0
      else
        mkW sign 0 fraction.toUInt32
    else
      let roundedMantissa :=
        if leading < 23 then
          product <<< (23 - leading)
        else
          rseAny product (leading - 23)
      let carry := roundedMantissa == 0x1000000
      let normalizedPosition := if carry then position + 1 else position
      if normalizedPosition > 425 then
        if sign then 0xff800000 else 0x7f800000
      else
        let normalizedMantissa := if carry then 0x800000 else roundedMantissa
        let encodedExponent := normalizedPosition - 171
        mkW sign encodedExponent.toUInt32 (fracW normalizedMantissa)

/-- The word kernel's finite path on bits; the caller has excluded NaN, infinity and zero. -/
@[inline] def core (xBits yBits : UInt32) : UInt32 :=
  let xExponent := expField xBits
  let yExponent := expField yBits
  let xSign := signBit xBits
  let ySign := signBit yBits
  let xMantissa := finiteMantissa xExponent (fracField xBits)
  let yMantissa := finiteMantissa yExponent (fracField yBits)
  let xScale := finiteScale xExponent
  let yScale := finiteScale yExponent
  if xScale ≤ yScale then
    let shift := yScale - xScale
    if shift ≤ 39 then
      let sum := FloatLib.Numerics.FixedWord.addSignedMagnitudes xSign ySign xMantissa (yMantissa <<< shift)
      roundP sum.1 sum.2 (xScale + 149)
    else yBits
  else
    let shift := xScale - yScale
    if shift ≤ 39 then
      let sum := FloatLib.Numerics.FixedWord.addSignedMagnitudes xSign ySign (xMantissa <<< shift) yMantissa
      roundP sum.1 sum.2 (yScale + 149)
    else xBits

/-- One operand is a NaN, an infinity or a zero, in one compare. -/
@[inline] def sp1 (a : UInt32) : Bool := (a <<< 1) - 1 ≥ 0xfeffffff

/-- The operands `core` leaves to the certified kernel: a NaN, an infinity or a zero. -/
@[inline] def special (a b : UInt32) : Bool := sp1 a || sp1 b

/-- Stored bits as a `Binary32`; the wrapper keeps goal terms well typed for `split` and `rw`. -/
@[inline] def ofBits (w : UInt32) : Binary32 := Configured.NativeFPU.ofBinary32Bits w

/-- `core` on ordinary operands, the certified kernel on special ones. -/
def add (x y : Binary32) : Binary32 :=
  if special x.raw.1 y.raw.1 then ExecFloat.add x y
  else ofBits (core x.raw.1 y.raw.1)

/-- The binary32 descriptor, storage plan and family that `Binary32` unfolds to. -/
abbrev Fmt := ExecFloat.Binary.format (exponentBits := 8) (fractionBits := 23)
abbrev Plan := Configured.StoragePlan.forKnownWidth Fmt (1 + 8 + 23) (by rfl)
abbrev Fam := Configured.Family Fmt (Configured.Code Plan) Plan

/-- The carrier's decode, with its codec instance pinned. -/
def dec (z : Binary32) : Model Fmt :=
  ExecFloat.ModelCodec.decode (F := Fam) (plan := Plan) (Model := Model Fmt) z

/-- Decoding a stored value is reading its bits. -/
theorem dec_eq (z : Binary32) : dec z = ofUInt32 z.raw.1 := rfl

/-- Decoding wrapped bits is rewrapping them in the model. -/
theorem dec_ofBits (w : UInt32) : dec (ofBits w) = ofUInt32 w := rfl

/-- On binary32 the dispatcher is the word kernel with the generic fallback. -/
theorem word32 (a b : Model Fmt) :
    Model.AddBackend.word a b =
      match addFiniteImpl? a b with
      | some s => s
      | none => Model.AddBackend.generic a b := by
  unfold Model.AddBackend.word
  rw [dif_pos (by decide)]
  rfl

/-- The planner's `wordAdd` decodes to the dispatcher on the decoded operands. -/
theorem dec_word (x y : Binary32) :
    dec (Configured.Backend.wordAdd x y) = Model.AddBackend.word (dec x) (dec y) :=
  ExecFloat.ModelCodec.decode_liftBinary (F := Fam) (plan := Plan) (Model := Model Fmt) _ x y

/-- Rewrapping a word and reading it back gives the word. -/
theorem toUInt32_ofUInt32 (b : UInt32) : toUInt32 (ofUInt32 b) = b := by
  simp [toUInt32, ofUInt32, Model.ofBits]

/-- Shifting out `k` low bits lowers `log2` by exactly `k`, while anything is left. -/
theorem log2_shift (n k : Nat) (h : n >>> k ≠ 0) : n.log2 = k + (n >>> k).log2 := by
  have hn : n ≠ 0 := by rintro rfl; simp at h
  rw [Nat.log2_eq_iff hn]
  rw [Nat.shiftRight_eq_div_pow] at h ⊢
  have h1 := Nat.log2_self_le h
  have h2 := Nat.lt_log2_self (n := n / 2 ^ k)
  have hk : 0 < 2 ^ k := Nat.two_pow_pos k
  constructor
  · calc 2 ^ (k + (n / 2 ^ k).log2) = 2 ^ k * 2 ^ (n / 2 ^ k).log2 := Nat.pow_add 2 _ _
      _ ≤ 2 ^ k * (n / 2 ^ k) := Nat.mul_le_mul_left _ h1
      _ ≤ n := Nat.mul_div_le n (2 ^ k)
  · calc n < 2 ^ k * (n / 2 ^ k + 1) := Nat.lt_mul_div_succ n hk
      _ ≤ 2 ^ k * 2 ^ ((n / 2 ^ k).log2 + 1) := Nat.mul_le_mul_left _ h2
      _ = 2 ^ (k + (n / 2 ^ k).log2 + 1) := by rw [← Nat.pow_add]; ring_nf

/-- Every 64-bit word has `log2` below 64. -/
theorem log2_lt_64 (x : UInt64) : x.toNat.log2 < 64 := by
  rcases Nat.eq_zero_or_pos x.toNat with h | h
  · simp [h]
  · exact (Nat.log2_lt (by omega)).mpr x.toNat_lt

/-- One `sx`/`sr` step keeps `log2 x0 = r + log2 x` and halves the bound on `x`. -/
theorem step (x0 r x k : UInt64) (hk : k.toNat ≤ 32) (hk0 : 0 < k.toNat)
    (hinv : x0.toNat.log2 = r.toNat + x.toNat.log2) (hb : x.toNat < 2 ^ (2 * k.toNat)) :
    x0.toNat.log2 = (sr k x r).toNat + (sx k x).toNat.log2 ∧ (sx k x).toNat < 2 ^ k.toNat := by
  have hs : (x >>> k).toNat = x.toNat >>> k.toNat := by
    rw [UInt64.toNat_shiftRight, Nat.mod_eq_of_lt (by omega)]
  unfold sx sr
  by_cases hz : x >>> k = 0
  · simp only [hz, beq_self_eq_true, Bool.cond_true]
    refine ⟨hinv, ?_⟩
    have h0 : x.toNat >>> k.toNat = 0 := by rw [← hs, hz]; rfl
    rw [Nat.shiftRight_eq_div_pow, Nat.div_eq_zero_iff] at h0
    rcases h0 with h0 | h0
    · exact absurd h0 (Nat.two_pow_pos _).ne'
    · exact h0
  · have hz' : (x >>> k == 0) = false := by simpa using hz
    simp only [hz', Bool.cond_false]
    have hne : x.toNat >>> k.toNat ≠ 0 := by
      rw [← hs]
      intro h
      exact hz (UInt64.toNat_inj.mp (by simpa using h))
    have hl := log2_shift x.toNat k.toNat hne
    have h64 := log2_lt_64 x0
    constructor
    · rw [UInt64.toNat_add, Nat.mod_eq_of_lt (by omega), hs]
      omega
    · rw [hs, Nat.shiftRight_eq_div_pow]
      apply Nat.div_lt_of_lt_mul
      rw [← Nat.pow_add]
      exact lt_of_lt_of_eq hb (by congr 1; omega)

/-- Zero and one have `log2` zero. -/
theorem log2_lt_two (n : Nat) (h : n < 2) : n.log2 = 0 := by
  interval_cases n <;> decide

/-- The binary search computes `UInt64.log2` on every word. -/
theorem fastLog2_eq (x : UInt64) : fastLog2 x = x.log2 := by
  apply UInt64.toNat_inj.mp
  rw [show x.log2.toNat = x.toNat.log2 from rfl]
  have b0 : x.toNat < 2 ^ (2 * (32 : UInt64).toNat) := x.toNat_lt
  obtain ⟨e1, b1⟩ := step x 0 x 32 (by decide) (by decide) (by simp) b0
  obtain ⟨e2, b2⟩ := step x _ _ 16 (by decide) (by decide) e1 (by simpa using b1)
  obtain ⟨e3, b3⟩ := step x _ _ 8 (by decide) (by decide) e2 (by simpa using b2)
  obtain ⟨e4, b4⟩ := step x _ _ 4 (by decide) (by decide) e3 (by simpa using b3)
  obtain ⟨e5, b5⟩ := step x _ _ 2 (by decide) (by decide) e4 (by simpa using b4)
  obtain ⟨e6, b6⟩ := step x _ _ 1 (by decide) (by decide) e5 (by simpa using b5)
  rw [log2_lt_two (sx 1 (sx 2 (sx 4 (sx 8 (sx 16 (sx 32 x)))))).toNat (by simpa using b6)] at e6
  unfold fastLog2
  dsimp only
  omega
/-- The exponent field as a natural number. -/
theorem expField_toNat (a : UInt32) : (expField a).toNat = a.toNat / 2 ^ 23 % 2 ^ 8 := by
  unfold expField
  rw [UInt32.toNat_and, UInt32.toNat_shiftRight]
  rw [show (0xff : UInt32).toNat = 2 ^ 8 - 1 from rfl, Nat.and_two_pow_sub_one_eq_mod]
  simp [Nat.shiftRight_eq_div_pow]

/-- The fraction field as a natural number. -/
theorem fracField_toNat (a : UInt32) : (fracField a).toNat = a.toNat % 2 ^ 23 := by
  unfold fracField
  rw [UInt32.toNat_and, show (0x007fffff : UInt32).toNat = 2 ^ 23 - 1 from rfl,
    Nat.and_two_pow_sub_one_eq_mod]

/-- The one-compare test as a natural-number condition. -/
theorem sp1_iff (a : UInt32) :
    sp1 a = true ↔ (a.toNat % 2 ^ 31 = 0 ∨ a.toNat % 2 ^ 31 ≥ 0x7f800000) := by
  have ha := a.toNat_lt
  unfold sp1
  simp only [decide_eq_true_eq, ge_iff_le, UInt32.le_iff_toNat_le, UInt32.toNat_sub,
    UInt32.toNat_shiftLeft]
  simp
  omega

/-- The mantissa is zero exactly when the exponent and the fraction both are. -/
theorem finiteMantissa_eq_zero (e f : UInt32) :
    finiteMantissa e f = 0 ↔ e = 0 ∧ f = 0 := by
  unfold finiteMantissa
  split
  · rename_i he
    have he : e = 0 := by simpa using he
    simp only [he, true_and]
    constructor
    · intro h
      apply UInt32.toNat_inj.mp
      simpa using congrArg UInt64.toNat h
    · rintro rfl; rfl
  · rename_i he
    have he : ¬e = 0 := by simpa using he
    simp only [he, false_and, iff_false]
    intro h
    have := congrArg (fun x => x.toNat.testBit 23) h
    simp [UInt64.toNat_or, Nat.testBit_or] at this
    exact absurd this.2 (by decide)

/-- The one-compare test is the four-comparison test, on one operand. -/
theorem sp1_eq (a : UInt32) :
    sp1 a = (expField a == 0xff || finiteMantissa (expField a) (fracField a) == 0) := by
  have ha := a.toNat_lt
  have he := expField_toNat a
  have hf := fracField_toNat a
  apply Bool.eq_iff_iff.mpr
  rw [sp1_iff]
  simp only [Bool.or_eq_true, beq_iff_eq, finiteMantissa_eq_zero]
  rw [← UInt32.toNat_inj, ← UInt32.toNat_inj, ← UInt32.toNat_inj, he, hf]
  simp only [show (0xff : UInt32).toNat = 255 from rfl, show (0 : UInt32).toNat = 0 from rfl]
  omega
/-- The word shift rounds exactly as FloatLib's natural-number-shift version. -/
theorem rseAny_eq (value shift : UInt64) :
    rseAny value shift = FloatLib.Numerics.FixedWord.roundShiftRightEven value shift.toNat := by
  unfold rseAny rse FloatLib.Numerics.FixedWord.roundShiftRightEven
  have hs := shift.toNat_lt
  by_cases h0 : shift = 0
  · subst h0; rfl
  · have h0' : shift.toNat ≠ 0 := by
      intro h; exact h0 (UInt64.toNat_inj.mp (by simpa using h))
    simp only [h0, beq_iff_eq, h0', reduceIte]
    have e1 : UInt64.ofNat shift.toNat = shift := UInt64.ofNat_toNat
    have e2 : UInt64.ofNat (shift.toNat - 1) = shift - 1 := by
      apply UInt64.toNat_inj.mp
      have hle : (1 : UInt64) ≤ shift := by rw [UInt64.le_iff_toNat_le]; simp; omega
      rw [UInt64.toNat_sub_of_le _ _ hle]
      simp
      omega
    have c1 : (shift < 64) ↔ shift.toNat < 64 := UInt64.lt_iff_toNat_lt
    have c2 : shift = 64 ↔ shift.toNat = 64 := by rw [← UInt64.toNat_inj]; rfl
    simp only [e1, e2, ← c1, ← c2]

/-- `mkW` packs what `mkBits` packs: `mkBits` only ever reads its fields through `ofNat`. -/
theorem mkW_ofNat (sign : Bool) (e f : Nat) :
    mkW sign (UInt32.ofNat e) (UInt32.ofNat f) = mkBits sign e f := by
  unfold mkW mkBits
  cases sign <;> rfl

/-- A 64-bit word narrowed to 32 bits is its value taken mod 2^32. -/
theorem toUInt32_eq (x : UInt64) : x.toUInt32 = UInt32.ofNat x.toNat := rfl

/-- `fracW` is the natural-number subtraction it replaces. -/
theorem fracW_eq (n : UInt64) : fracW n = UInt32.ofNat (n.toNat - 0x800000) := by
  unfold fracW
  split
  · rename_i h
    rw [UInt64.lt_iff_toNat_lt] at h
    simp only [toUInt32_eq]
    rw [show n.toNat - 0x800000 = 0 by simp at h; omega]
    rfl
  · rename_i h
    rw [UInt64.lt_iff_toNat_lt] at h
    simp only [toUInt32_eq]
    rw [UInt64.toNat_sub_of_le _ _ (by rw [UInt64.le_iff_toNat_le]; simp at h ⊢; omega)]
    rfl

/-- `roundP` is FloatLib's `roundProduct`: they differ in `log2` and in staying on words. -/
theorem roundP_eq (sign : Bool) (product scale : UInt64) :
    roundP sign product scale = roundProduct sign product scale := by
  unfold roundP roundProduct
  simp only [fastLog2_eq, rseAny_eq, fracW_eq, toUInt32_eq]
  rw [show (1 : UInt32) = UInt32.ofNat 1 from rfl, show (0 : UInt32) = UInt32.ofNat 0 from rfl]
  simp only [mkW_ofNat]

/-- Off the fallback, the word kernel returns exactly `core` on the same bits. -/
theorem impl_eq (a b : UInt32) (ha : expField a ≠ 0xff) (hb : expField b ≠ 0xff)
    (hma : finiteMantissa (expField a) (fracField a) ≠ 0)
    (hmb : finiteMantissa (expField b) (fracField b) ≠ 0) :
    addFiniteImpl? (ofUInt32 a) (ofUInt32 b) = some (ofUInt32 (core a b)) := by
  unfold addFiniteImpl? core
  simp only [roundP_eq, toUInt32_ofUInt32, ha, hb, hma, hmb, beq_iff_eq, Bool.or_eq_true, or_self,
    if_false]
  split_ifs <;> rfl

/-- The kernel equals the planner's word addition on every pair of operands. -/
theorem add_eq_word (x y : Binary32) : add x y = Configured.Backend.wordAdd x y := by
  unfold add
  split
  · rfl
  · rename_i h
    simp only [special, sp1_eq, Bool.or_eq_true, beq_iff_eq, not_or] at h
    obtain ⟨⟨ha, hma⟩, hb, hmb⟩ := h
    apply ExecFloat.ModelCodec.decode_injective (F := Fam) (plan := Plan) (Model := Model Fmt)
    change dec (ofBits (core x.raw.1 y.raw.1)) = dec (Configured.Backend.wordAdd x y)
    rw [dec_ofBits, dec_word, word32, dec_eq x, dec_eq y, impl_eq _ _ ha hb hma hmb]

theorem add_spec : ∀ x y : Binary32, add x y = ExecFloat.Spec.add x y := fun x y => by
  rw [add_eq_word]
  exact Configured.Backend.wordAdd_eq_spec x y

end TunedAdd

/-!
FloatLib's binary32 word multiplication on raw bits, with tuned's rounding step.

`ExecFloat.mul` decodes into the generic model, runs `mulFiniteImpl?` inside an `Option` and
encodes back, and its `roundProduct` computes `UInt64.log2` one bit at a time over a product of up
to 48 bits. `core` is `mulFiniteImpl?` on bare words and `roundP` is `roundProduct` with a six-step
binary-search `log2` and no `Nat` round trips, both taken from `tuned` with their proofs. NaN and
infinity go to `ExecFloat.mul`; zeros need no fallback, the rounding step signs them. `sm1_eq`
proves the one-compare test, and the rest reuses `wordMul_eq_spec`: no floating-point reasoning.
-/

namespace FastMul

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
open Model.NativeBinary32

/-- One binary-search step for `log2` on the value: shift down by `k` if anything is left there. -/
@[inline] def sx (k x : UInt64) : UInt64 := bif x >>> k == 0 then x else x >>> k

/-- The same step on the running result: add `k` when the value moved. -/
@[inline] def sr (k x r : UInt64) : UInt64 := bif x >>> k == 0 then r else r + k

/-- `UInt64.log2` by binary search: six steps instead of one per bit. -/
@[inline] def fastLog2 (x0 : UInt64) : UInt64 :=
  let x1 := sx 32 x0
  let r1 := sr 32 x0 0
  let x2 := sx 16 x1
  let r2 := sr 16 x1 r1
  let x3 := sx 8 x2
  let r3 := sr 8 x2 r2
  let x4 := sx 4 x3
  let r4 := sr 4 x3 r3
  let x5 := sx 2 x4
  let r5 := sr 2 x4 r4
  sr 1 x5 r5

/-- `roundShiftRightEven` with a word shift; the caller passes 1 ≤ shift < 64. -/
@[inline] def rse (value shift : UInt64) : UInt64 :=
  let quotient := value >>> shift
  let remainder := value &&& ((1 <<< shift) - 1)
  let half := (1 : UInt64) <<< (shift - 1)
  if remainder < half then quotient
  else if remainder > half then quotient + 1
  else if (quotient &&& 1) == 0 then quotient
  else quotient + 1

/-- `rse` for any shift, matching roundShiftRightEven's 0 and ≥ 64 cases. -/
@[inline] def rseAny (value shift : UInt64) : UInt64 :=
  if shift == 0 then value
  else if shift < 64 then rse value shift
  else if shift == 64 then (if value > 0x8000000000000000 then 1 else 0)
  else 0

/-- `mkBits` on words. -/
@[inline] def mkW (sign : Bool) (e f : UInt32) : UInt32 :=
  (if sign then (0x80000000 : UInt32) else 0) ||| ((e &&& 0xff) <<< 23) ||| (f &&& 0x007fffff)

/-- The stored fraction of a normalised mantissa, as `mkBits` receives it: zero below 2^23. -/
@[inline] def fracW (n : UInt64) : UInt32 :=
  (if n < 0x800000 then 0 else n - 0x800000).toUInt32

/-- `roundProduct` with `fastLog2`, on words throughout. -/
@[inline] def roundP (sign : Bool) (product scale : UInt64) : UInt32 :=
  if product == 0 then
    if sign then 0x80000000 else 0
  else
    let leading := fastLog2 product
    let position := leading + scale
    if position < 172 then
      let fraction :=
        if scale < 149 then
          rseAny product (149 - scale)
        else
          product <<< (scale - 149)
      if fraction == 0 then
        if sign then 0x80000000 else 0
      else if fraction == 0x800000 then
        mkW sign 1 0
      else
        mkW sign 0 fraction.toUInt32
    else
      let roundedMantissa :=
        if leading < 23 then
          product <<< (23 - leading)
        else
          rseAny product (leading - 23)
      let carry := roundedMantissa == 0x1000000
      let normalizedPosition := if carry then position + 1 else position
      if normalizedPosition > 425 then
        if sign then 0xff800000 else 0x7f800000
      else
        let normalizedMantissa := if carry then 0x800000 else roundedMantissa
        let encodedExponent := normalizedPosition - 171
        mkW sign encodedExponent.toUInt32 (fracW normalizedMantissa)

/-- The word multiplication's finite path on bits; the caller has excluded NaN and infinity. -/
@[inline] def core (xBits yBits : UInt32) : UInt32 :=
  let xExponent := expField xBits
  let yExponent := expField yBits
  let sign := Bool.xor (signBit xBits) (signBit yBits)
  let xFraction := fracField xBits
  let yFraction := fracField yBits
  let xMantissa := finiteMantissa xExponent xFraction
  let yMantissa := finiteMantissa yExponent yFraction
  let xScale := finiteScale xExponent
  let yScale := finiteScale yExponent
  roundP sign (xMantissa * yMantissa) (xScale + yScale)

/-- One operand is a NaN or an infinity, in one compare: its exponent field is all ones. -/
@[inline] def sm1 (a : UInt32) : Bool := a <<< 1 ≥ 0xff000000

/-- The operands `core` leaves to the certified kernel: a NaN or an infinity. -/
@[inline] def special (a b : UInt32) : Bool := sm1 a || sm1 b

/-- Stored bits as a `Binary32`; the wrapper keeps goal terms well typed for `split` and `rw`. -/
@[inline] def ofBits (w : UInt32) : Binary32 := Configured.NativeFPU.ofBinary32Bits w

/-- `core` on ordinary operands, the certified kernel on special ones. -/
def mul (x y : Binary32) : Binary32 :=
  if special x.raw.1 y.raw.1 then ExecFloat.mul x y
  else ofBits (core x.raw.1 y.raw.1)

/-- The binary32 descriptor, storage plan and family that `Binary32` unfolds to. -/
abbrev Fmt := ExecFloat.Binary.format (exponentBits := 8) (fractionBits := 23)
abbrev Plan := Configured.StoragePlan.forKnownWidth Fmt (1 + 8 + 23) (by rfl)
abbrev Fam := Configured.Family Fmt (Configured.Code Plan) Plan

/-- The carrier's decode, with its codec instance pinned. -/
def dec (z : Binary32) : Model Fmt :=
  ExecFloat.ModelCodec.decode (F := Fam) (plan := Plan) (Model := Model Fmt) z

/-- Decoding a stored value is reading its bits. -/
theorem dec_eq (z : Binary32) : dec z = ofUInt32 z.raw.1 := rfl

/-- Decoding wrapped bits is rewrapping them in the model. -/
theorem dec_ofBits (w : UInt32) : dec (ofBits w) = ofUInt32 w := rfl

/-- On binary32 the dispatcher is the word kernel with the generic fallback. -/
theorem word32 (a b : Model Fmt) :
    Model.MulBackend.word a b =
      match mulFiniteImpl? a b with
      | some s => s
      | none => Model.MulBackend.generic a b := by
  unfold Model.MulBackend.word
  rw [dif_pos (by decide)]
  rfl

/-- The planner's `wordMul` decodes to the dispatcher on the decoded operands. -/
theorem dec_word (x y : Binary32) :
    dec (Configured.Backend.wordMul x y) = Model.MulBackend.word (dec x) (dec y) :=
  ExecFloat.ModelCodec.decode_liftBinary (F := Fam) (plan := Plan) (Model := Model Fmt) _ x y

/-- Rewrapping a word and reading it back gives the word. -/
theorem toUInt32_ofUInt32 (b : UInt32) : toUInt32 (ofUInt32 b) = b := by
  simp [toUInt32, ofUInt32, Model.ofBits]

/-- Shifting out `k` low bits lowers `log2` by exactly `k`, while anything is left. -/
theorem log2_shift (n k : Nat) (h : n >>> k ≠ 0) : n.log2 = k + (n >>> k).log2 := by
  have hn : n ≠ 0 := by rintro rfl; simp at h
  rw [Nat.log2_eq_iff hn]
  rw [Nat.shiftRight_eq_div_pow] at h ⊢
  have h1 := Nat.log2_self_le h
  have h2 := Nat.lt_log2_self (n := n / 2 ^ k)
  have hk : 0 < 2 ^ k := Nat.two_pow_pos k
  constructor
  · calc 2 ^ (k + (n / 2 ^ k).log2) = 2 ^ k * 2 ^ (n / 2 ^ k).log2 := Nat.pow_add 2 _ _
      _ ≤ 2 ^ k * (n / 2 ^ k) := Nat.mul_le_mul_left _ h1
      _ ≤ n := Nat.mul_div_le n (2 ^ k)
  · calc n < 2 ^ k * (n / 2 ^ k + 1) := Nat.lt_mul_div_succ n hk
      _ ≤ 2 ^ k * 2 ^ ((n / 2 ^ k).log2 + 1) := Nat.mul_le_mul_left _ h2
      _ = 2 ^ (k + (n / 2 ^ k).log2 + 1) := by rw [← Nat.pow_add]; ring_nf

/-- Every 64-bit word has `log2` below 64. -/
theorem log2_lt_64 (x : UInt64) : x.toNat.log2 < 64 := by
  rcases Nat.eq_zero_or_pos x.toNat with h | h
  · simp [h]
  · exact (Nat.log2_lt (by omega)).mpr x.toNat_lt

/-- One `sx`/`sr` step keeps `log2 x0 = r + log2 x` and halves the bound on `x`. -/
theorem step (x0 r x k : UInt64) (hk : k.toNat ≤ 32) (hk0 : 0 < k.toNat)
    (hinv : x0.toNat.log2 = r.toNat + x.toNat.log2) (hb : x.toNat < 2 ^ (2 * k.toNat)) :
    x0.toNat.log2 = (sr k x r).toNat + (sx k x).toNat.log2 ∧ (sx k x).toNat < 2 ^ k.toNat := by
  have hs : (x >>> k).toNat = x.toNat >>> k.toNat := by
    rw [UInt64.toNat_shiftRight, Nat.mod_eq_of_lt (by omega)]
  unfold sx sr
  by_cases hz : x >>> k = 0
  · simp only [hz, beq_self_eq_true, Bool.cond_true]
    refine ⟨hinv, ?_⟩
    have h0 : x.toNat >>> k.toNat = 0 := by rw [← hs, hz]; rfl
    rw [Nat.shiftRight_eq_div_pow, Nat.div_eq_zero_iff] at h0
    rcases h0 with h0 | h0
    · exact absurd h0 (Nat.two_pow_pos _).ne'
    · exact h0
  · have hz' : (x >>> k == 0) = false := by simpa using hz
    simp only [hz', Bool.cond_false]
    have hne : x.toNat >>> k.toNat ≠ 0 := by
      rw [← hs]
      intro h
      exact hz (UInt64.toNat_inj.mp (by simpa using h))
    have hl := log2_shift x.toNat k.toNat hne
    have h64 := log2_lt_64 x0
    constructor
    · rw [UInt64.toNat_add, Nat.mod_eq_of_lt (by omega), hs]
      omega
    · rw [hs, Nat.shiftRight_eq_div_pow]
      apply Nat.div_lt_of_lt_mul
      rw [← Nat.pow_add]
      exact lt_of_lt_of_eq hb (by congr 1; omega)

/-- Zero and one have `log2` zero. -/
theorem log2_lt_two (n : Nat) (h : n < 2) : n.log2 = 0 := by
  interval_cases n <;> decide

/-- The binary search computes `UInt64.log2` on every word. -/
theorem fastLog2_eq (x : UInt64) : fastLog2 x = x.log2 := by
  apply UInt64.toNat_inj.mp
  rw [show x.log2.toNat = x.toNat.log2 from rfl]
  have b0 : x.toNat < 2 ^ (2 * (32 : UInt64).toNat) := x.toNat_lt
  obtain ⟨e1, b1⟩ := step x 0 x 32 (by decide) (by decide) (by simp) b0
  obtain ⟨e2, b2⟩ := step x _ _ 16 (by decide) (by decide) e1 (by simpa using b1)
  obtain ⟨e3, b3⟩ := step x _ _ 8 (by decide) (by decide) e2 (by simpa using b2)
  obtain ⟨e4, b4⟩ := step x _ _ 4 (by decide) (by decide) e3 (by simpa using b3)
  obtain ⟨e5, b5⟩ := step x _ _ 2 (by decide) (by decide) e4 (by simpa using b4)
  obtain ⟨e6, b6⟩ := step x _ _ 1 (by decide) (by decide) e5 (by simpa using b5)
  rw [log2_lt_two (sx 1 (sx 2 (sx 4 (sx 8 (sx 16 (sx 32 x)))))).toNat (by simpa using b6)] at e6
  unfold fastLog2
  dsimp only
  omega
/-- The exponent field as a natural number. -/
theorem expField_toNat (a : UInt32) : (expField a).toNat = a.toNat / 2 ^ 23 % 2 ^ 8 := by
  unfold expField
  rw [UInt32.toNat_and, UInt32.toNat_shiftRight]
  rw [show (0xff : UInt32).toNat = 2 ^ 8 - 1 from rfl, Nat.and_two_pow_sub_one_eq_mod]
  simp [Nat.shiftRight_eq_div_pow]

/-- The one-compare test is the exponent-field test, on one operand. -/
theorem sm1_eq (a : UInt32) : sm1 a = (expField a == 0xff) := by
  have ha := a.toNat_lt
  have he := expField_toNat a
  apply Bool.eq_iff_iff.mpr
  unfold sm1
  simp only [decide_eq_true_eq, ge_iff_le, UInt32.le_iff_toNat_le, UInt32.toNat_shiftLeft,
    beq_iff_eq]
  rw [← UInt32.toNat_inj, he]
  simp only [show (0xff : UInt32).toNat = 255 from rfl]
  simp
  omega

/-- The word shift rounds exactly as FloatLib's natural-number-shift version. -/
theorem rseAny_eq (value shift : UInt64) :
    rseAny value shift = FloatLib.Numerics.FixedWord.roundShiftRightEven value shift.toNat := by
  unfold rseAny rse FloatLib.Numerics.FixedWord.roundShiftRightEven
  have hs := shift.toNat_lt
  by_cases h0 : shift = 0
  · subst h0; rfl
  · have h0' : shift.toNat ≠ 0 := by
      intro h; exact h0 (UInt64.toNat_inj.mp (by simpa using h))
    simp only [h0, beq_iff_eq, h0', reduceIte]
    have e1 : UInt64.ofNat shift.toNat = shift := UInt64.ofNat_toNat
    have e2 : UInt64.ofNat (shift.toNat - 1) = shift - 1 := by
      apply UInt64.toNat_inj.mp
      have hle : (1 : UInt64) ≤ shift := by rw [UInt64.le_iff_toNat_le]; simp; omega
      rw [UInt64.toNat_sub_of_le _ _ hle]
      simp
      omega
    have c1 : (shift < 64) ↔ shift.toNat < 64 := UInt64.lt_iff_toNat_lt
    have c2 : shift = 64 ↔ shift.toNat = 64 := by rw [← UInt64.toNat_inj]; rfl
    simp only [e1, e2, ← c1, ← c2]

/-- `mkW` packs what `mkBits` packs: `mkBits` only ever reads its fields through `ofNat`. -/
theorem mkW_ofNat (sign : Bool) (e f : Nat) :
    mkW sign (UInt32.ofNat e) (UInt32.ofNat f) = mkBits sign e f := by
  unfold mkW mkBits
  cases sign <;> rfl

/-- A 64-bit word narrowed to 32 bits is its value taken mod 2^32. -/
theorem toUInt32_eq (x : UInt64) : x.toUInt32 = UInt32.ofNat x.toNat := rfl

/-- `fracW` is the natural-number subtraction it replaces. -/
theorem fracW_eq (n : UInt64) : fracW n = UInt32.ofNat (n.toNat - 0x800000) := by
  unfold fracW
  split
  · rename_i h
    rw [UInt64.lt_iff_toNat_lt] at h
    simp only [toUInt32_eq]
    rw [show n.toNat - 0x800000 = 0 by simp at h; omega]
    rfl
  · rename_i h
    rw [UInt64.lt_iff_toNat_lt] at h
    simp only [toUInt32_eq]
    rw [UInt64.toNat_sub_of_le _ _ (by rw [UInt64.le_iff_toNat_le]; simp at h ⊢; omega)]
    rfl

/-- `roundP` is FloatLib's `roundProduct`: they differ in `log2` and in staying on words. -/
theorem roundP_eq (sign : Bool) (product scale : UInt64) :
    roundP sign product scale = roundProduct sign product scale := by
  unfold roundP roundProduct
  simp only [fastLog2_eq, rseAny_eq, fracW_eq, toUInt32_eq]
  rw [show (1 : UInt32) = UInt32.ofNat 1 from rfl, show (0 : UInt32) = UInt32.ofNat 0 from rfl]
  simp only [mkW_ofNat]

/-- Off the fallback, the word kernel returns exactly `core` on the same bits. -/
theorem impl_eq (a b : UInt32) (ha : expField a ≠ 0xff) (hb : expField b ≠ 0xff) :
    mulFiniteImpl? (ofUInt32 a) (ofUInt32 b) = some (ofUInt32 (core a b)) := by
  unfold mulFiniteImpl? core
  simp only [roundP_eq, toUInt32_ofUInt32, ha, hb, beq_iff_eq, Bool.or_eq_true, or_self,
    if_false]

/-- The kernel equals the planner's word multiplication on every pair of operands. -/
theorem mul_eq_word (x y : Binary32) : mul x y = Configured.Backend.wordMul x y := by
  unfold mul
  split
  · rfl
  · rename_i h
    simp only [special, sm1_eq, Bool.or_eq_true, beq_iff_eq, not_or] at h
    obtain ⟨ha, hb⟩ := h
    apply ExecFloat.ModelCodec.decode_injective (F := Fam) (plan := Plan) (Model := Model Fmt)
    change dec (ofBits (core x.raw.1 y.raw.1)) = dec (Configured.Backend.wordMul x y)
    rw [dec_ofBits, dec_word, word32, dec_eq x, dec_eq y, impl_eq _ _ ha hb]

theorem mul_spec : ∀ x y : Binary32, mul x y = ExecFloat.Spec.mul x y := fun x y => by
  rw [mul_eq_word]
  exact Configured.Backend.wordMul_eq_spec x y

end FastMul

open FloatLib.Floats Competition



namespace GuardBridge

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

/-- Finiteness excludes the noncanonical NaN representation case. -/
theorem modelCanonicalOfFinite {fmt : FloatFormat} (x : Model fmt)
    (hx : (Model.toModel x).isFinite = true) : Model.IsModelCanonical x := by
  constructor
  intro he hm
  have hnan : Model.toModel x = Float.Model.UnpackedFloat.notANumber := by
    simp only [Model.toModel, Float.Model.UnpackedFloat.unpack, he, hm, ite_true, ite_false]
  rw [hnan] at hx
  cases hx

theorem finiteRoundtrip (x : Competition.Binary32)
    (hx : (ExecFloat.Binary.toFloat32 x).isFinite = true) :
    ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x) = x := by
  have hcanonical : Model.IsModelCanonical (ExecFloat.Binary.toModel x) := by
    apply modelCanonicalOfFinite
    have hf := hx
    change ((Model.toFloat32Model (ExecFloat.Binary.toModel x)).unpack).isFinite = true at hf
    rw [Model.unpack_toFloat32Model] at hf
    exact hf
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel
      (ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x)) =
    ExecFloat.Binary.toModel x
  rw [ExecFloat.Binary.toModel_ofFloat32, ExecFloat.Binary.toModel_toFloat32_eq,
    Model.ofFloat32Model_toFloat32Model]
  exact Model.canonicalizeModel_eq_self _ hcanonical

end GuardBridge

namespace WordFinite

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

theorem modelFiniteOfExp (w : UInt32)
    (hw : FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField w ≠ 0xff) :
    (Model.toModel (Model.NativeBinary32.ofUInt32 w)).isFinite = true := by
  have hd : ∃ d, Model.toDyadic? (Model.NativeBinary32.ofUInt32 w) = some d := by
    rw [← Model.NativeBinary32.toDyadic_eq]
    simp only [Model.NativeBinary32.toUInt32_ofUInt32]
    unfold Model.NativeBinary32.toDyadic?
    simp only [beq_iff_eq, hw, ite_false]
    split_ifs <;> exact ⟨_, rfl⟩
  obtain ⟨d, hd⟩ := hd
  rw [Model.toDyadic?_ieee_eq_model FloatFormat.binary32 (by decide)] at hd
  cases hm : Model.toModel (Model.NativeBinary32.ofUInt32 w) <;>
    simp_all [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.isFinite]

theorem nativeFiniteOfExp (x : Competition.Binary32)
    (hx : FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField x.raw.1 ≠ 0xff) :
    (ExecFloat.Binary.toFloat32 x).isFinite = true := by
  change ((Model.toFloat32Model (Model.NativeBinary32.ofUInt32 x.raw.1)).unpack).isFinite = true
  rw [Model.unpack_toFloat32Model]
  exact modelFiniteOfExp x.raw.1 hx

end WordFinite

/-- Raw exponent tests establish both native input conditions. -/
@[inline] def add (x y : Binary32) : Binary32 :=
  if hf : FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField x.raw.1 ≠ 0xff ∧
      FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField y.raw.1 ≠ 0xff then
    ExecFloat.Binary.ofFloat32 (R2W01b.convert x.raw.1 + R2W01b.convert y.raw.1)
  else TunedAdd.add x y

theorem add_spec : ∀ x y : Binary32, add x y = ExecFloat.Spec.add x y := by
  intro x y
  unfold add
  split
  · rename_i hf
    have hx := WordFinite.nativeFiniteOfExp x hf.1
    have hy := WordFinite.nativeFiniteOfExp y hf.2
    rw [R2W01c.convert_eq, R2W01c.convert_eq]
    change ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y) = _
    rw [ExecFloat.Binary.ofFloat32_add_of_isFinite _ _ hx hy,
      GuardBridge.finiteRoundtrip x hx, GuardBridge.finiteRoundtrip y hy]
    exact ExecFloat.Proof.add_eq_spec x y
  · exact TunedAdd.add_spec x y

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

theorem toModelExecMul (x y : Competition.Binary32) :
    ExecFloat.Binary.toModel (ExecFloat.mul x y) =
      Model.Spec.mul (ExecFloat.Binary.toModel x) (ExecFloat.Binary.toModel y) := by
  rw [ExecFloat.Proof.mul_eq_spec]
  change Configured.Family.toModel
    (ExecFloat.ModelCodec.liftBinary Model.Spec.mul x y) = _
  simp [Configured.Family.toModel, ExecFloat.Binary.toModel]

theorem ofFloat32Mul (x y : Float32)
    (hx : x.isFinite = true) (hy : y.isFinite = true) :
    ExecFloat.Binary.ofFloat32 (x * y) =
      ExecFloat.mul (ExecFloat.Binary.ofFloat32 x) (ExecFloat.Binary.ofFloat32 y) := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 (x * y)) =
    ExecFloat.Binary.toModel
      (ExecFloat.mul (ExecFloat.Binary.ofFloat32 x) (ExecFloat.Binary.ofFloat32 y))
  rw [toModelExecMul, ← Model.Proof.mul_eq_spec]
  exact toModelNativeMul x y hx hy

end NativeBridge

/-- Raw finite input guards retain the original multiplication fallback. -/
@[inline] def nativeMul (x y : Binary32) : Binary32 :=
  if hf : FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField x.raw.1 ≠ 0xff ∧
      FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField y.raw.1 ≠ 0xff then
    ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y)
  else FastMul.mul x y

theorem nativeMul_spec : ∀ x y : Binary32, nativeMul x y = ExecFloat.Spec.mul x y := by
  intro x y
  unfold nativeMul
  split
  · rename_i hf
    have hx := WordFinite.nativeFiniteOfExp x hf.1
    have hy := WordFinite.nativeFiniteOfExp y hf.2
    rw [NativeBridge.ofFloat32Mul _ _ hx hy,
      GuardBridge.finiteRoundtrip x hx, GuardBridge.finiteRoundtrip y hy]
    exact ExecFloat.Proof.mul_eq_spec x y
  · exact FastMul.mul_spec x y

@[inline] def mul (x y : Binary32) : Binary32 := nativeMul x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y :=
  nativeMul_spec x y

/-- `add` and `mul` are FloatLib's executable operations, whatever they compute internally. -/
theorem add_eq : add = ExecFloat.add := by
  funext x y
  rw [add_spec, ExecFloat.Proof.add_eq_spec]

theorem mul_eq : mul = ExecFloat.mul := by
  funext x y
  rw [mul_spec, ExecFloat.Proof.mul_eq_spec]

/-- TorchLean's sum: the elements left to right, from +0, with `add`. -/
def referenceSum {n : Nat} (x : Vector Binary32 n) : Binary32 := x.foldl add posZero

theorem referenceSum_spec : ∀ (n : Nat) (x : Vector Binary32 n), referenceSum x = sumSpec x.get := by
  intro n x
  conv_lhs => rw [referenceSum, add_eq, ← Vector.ofFn_getElem (xs := x)]
  rw [← Vector.foldl_toList, Vector.toList_ofFn, List.ofFn_eq_map, List.foldl_map]
  rfl

/-- TorchLean's batched matmul: each output a left fold over `k` of `add acc (mul a b)`. -/
def referenceBmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  Vector.ofFn fun q =>
    let (b, i, j) := bmmDecodeC m p q.val
    Fin.foldl n
      (fun acc k =>
        add acc (mul (A.toArray.getD ((b * m + i) * n + k.val) posZero)
          (B.toArray.getD ((b * n + k.val) * p + j) posZero)))
      posZero

/-- The kernel's bounded read is the rule's `getD`: same element in bounds, +0 outside. -/
theorem toArray_getD {N : Nat} (A : Vector Binary32 N) (i : Nat) :
    A.toArray.getD i posZero = getD A.get i := by
  unfold getD
  split <;> simp_all [Array.getD, Vector.get]

theorem referenceBmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (referenceBmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  funext q
  simp only [referenceBmm, add_eq, mul_eq, Vector.get, Vector.toArray_ofFn, Array.getElem_ofFn,
    Fin.foldl_eq_finRange_foldl, toArray_getD]
  rfl


namespace FinalFinite

/- These lemmas expose the finite-result preimage of native binary32 operations.
   They use Lean 4.34's actual packed model; derived from the actual arithmetic definitions.
   Source definitions: Lean FRO / Apache-2.0, Float.Model.UnpackedFloat.add/mul.
   Proofs below are new, candidate-local proofs. -/

theorem packNaN_notFinite :
    (Float32.Model.pack Float.Model.UnpackedFloat.notANumber).isFinite = false := by
  decide

theorem packInfinity_notFinite (sign : Float.Model.UnpackedFloat.Sign) :
    (Float32.Model.pack (Float.Model.UnpackedFloat.infinity sign)).isFinite = false := by
  cases sign <;> decide

/-- A native finite sum has finite operands, including either sign of zero. -/
theorem add_finite_inputs (x y : Float32) (h : (x + y).isFinite = true) :
    x.isFinite = true ∧ y.isFinite = true := by
  change (Float32.Model.pack
    (Float.Model.UnpackedFloat.add Float.Model.Format.binary32
      x.toModel.unpack y.toModel.unpack)).isFinite = true at h
  change x.toModel.unpack.isFinite = true ∧ y.toModel.unpack.isFinite = true
  cases hx : x.toModel.unpack <;> cases hy : y.toModel.unpack <;>
    simp_all [Float.Model.UnpackedFloat.add, Float.Model.UnpackedFloat.isFinite,
      packNaN_notFinite, packInfinity_notFinite]
  all_goals split at h <;> simp_all [packNaN_notFinite, packInfinity_notFinite]

/-- A native finite product has finite factors; infinity times zero is excluded. -/
theorem mul_finite_inputs (x y : Float32) (h : (x * y).isFinite = true) :
    x.isFinite = true ∧ y.isFinite = true := by
  change (Float32.Model.pack
    (Float.Model.UnpackedFloat.mul Float.Model.Format.binary32
      x.toModel.unpack y.toModel.unpack)).isFinite = true at h
  change x.toModel.unpack.isFinite = true ∧ y.toModel.unpack.isFinite = true
  cases hx : x.toModel.unpack <;> cases hy : y.toModel.unpack <;>
    simp_all [Float.Model.UnpackedFloat.mul, Float.Model.UnpackedFloat.isFinite,
      packNaN_notFinite, packInfinity_notFinite]

end FinalFinite


namespace NativeFinal

def sumLoop {n : Nat} (x : Vector Binary32 n) (k : Nat) (acc : Float32) : Float32 :=
  if hk : k < n then
    sumLoop x (k + 1) (acc + ExecFloat.Binary.toFloat32 (x.get ⟨k, hk⟩))
  else acc
termination_by n - k

theorem sumLoop_eq {n : Nat} (x : Vector Binary32 n) (k : Nat)
    (acc result : Float32) (hs : sumLoop x k acc = result)
    (hf : result.isFinite = true) :
    acc.isFinite = true ∧ ExecFloat.Binary.ofFloat32 result =
      Fin.foldl.loop n (fun a i => ExecFloat.add a (x.get i))
        (ExecFloat.Binary.ofFloat32 acc) k := by
  rw [sumLoop] at hs
  split at hs
  · rename_i hk
    have ih := sumLoop_eq x (k + 1)
      (acc + ExecFloat.Binary.toFloat32 (x.get ⟨k, hk⟩)) result hs hf
    have ha := FinalFinite.add_finite_inputs acc
      (ExecFloat.Binary.toFloat32 (x.get ⟨k, hk⟩)) ih.1
    refine ⟨ha.1, ?_⟩
    rw [Fin.foldl.loop, dif_pos hk]
    have hnext := ih.2
    rw [ExecFloat.Binary.ofFloat32_add_of_isFinite _ _ ha.1 ha.2,
      GuardBridge.finiteRoundtrip _ ha.2] at hnext
    exact hnext
  · rename_i hk
    refine ⟨?_, ?_⟩
    · simpa only [hs] using hf
    · rw [Fin.foldl.loop, dif_neg hk]
      exact congrArg ExecFloat.Binary.ofFloat32 hs.symm
termination_by n - k

def dotLoop (n baseA baseB p : Nat) (A B : Array Binary32)
    (k : Nat) (acc : Float32) : Float32 :=
  if hk : k < n then
    let fa := ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero)
    let fb := ExecFloat.Binary.toFloat32 (B.getD (baseB + k * p) posZero)
    dotLoop n baseA baseB p A B (k + 1) (acc + fa * fb)
  else acc
termination_by n - k

theorem dotLoop_eq (n baseA baseB p : Nat) (A B : Array Binary32)
    (k : Nat) (acc result : Float32)
    (hs : dotLoop n baseA baseB p A B k acc = result) (hf : result.isFinite = true) :
    acc.isFinite = true ∧ ExecFloat.Binary.ofFloat32 result =
      Fin.foldl.loop n
        (fun a i => ExecFloat.add a
          (ExecFloat.mul (A.getD (baseA + i.val) posZero)
            (B.getD (baseB + i.val * p) posZero)))
        (ExecFloat.Binary.ofFloat32 acc) k := by
  rw [dotLoop] at hs
  split at hs
  · rename_i hk
    dsimp only at hs
    have ih := dotLoop_eq n baseA baseB p A B (k + 1)
      (acc + ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero) *
        ExecFloat.Binary.toFloat32 (B.getD (baseB + k * p) posZero)) result hs hf
    have ha := FinalFinite.add_finite_inputs acc
      (ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero) *
        ExecFloat.Binary.toFloat32 (B.getD (baseB + k * p) posZero)) ih.1
    have hm := FinalFinite.mul_finite_inputs
      (ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero))
      (ExecFloat.Binary.toFloat32 (B.getD (baseB + k * p) posZero)) ha.2
    refine ⟨ha.1, ?_⟩
    rw [Fin.foldl.loop, dif_pos hk]
    have hnext := ih.2
    rw [ExecFloat.Binary.ofFloat32_add_of_isFinite _ _ ha.1 ha.2,
      NativeBridge.ofFloat32Mul _ _ hm.1 hm.2,
      GuardBridge.finiteRoundtrip _ hm.1, GuardBridge.finiteRoundtrip _ hm.2] at hnext
    exact hnext
  · rename_i hk
    refine ⟨?_, ?_⟩
    · simpa only [hs] using hf
    · rw [Fin.foldl.loop, dif_neg hk]
      exact congrArg ExecFloat.Binary.ofFloat32 hs.symm
termination_by n - k

def dot (n baseA baseB p : Nat) (A B : Array Binary32) : Binary32 :=
  let result := dotLoop n baseA baseB p A B 0 (Float32.ofBits 0)
  if hf : result.isFinite = true then ExecFloat.Binary.ofFloat32 result
  else Fin.foldl n
    (fun a i => add a (mul (A.getD (baseA + i.val) posZero)
      (B.getD (baseB + i.val * p) posZero))) posZero

theorem dot_eq (n baseA baseB p : Nat) (A B : Array Binary32) :
    dot n baseA baseB p A B = Fin.foldl n
      (fun a i => ExecFloat.add a (ExecFloat.mul (A.getD (baseA + i.val) posZero)
        (B.getD (baseB + i.val * p) posZero))) posZero := by
  unfold dot
  dsimp only
  split
  · rename_i hf
    have h := (dotLoop_eq n baseA baseB p A B 0 (Float32.ofBits 0) _ rfl hf).2
    change ExecFloat.Binary.ofFloat32 _ = Fin.foldl n _ posZero at h
    exact h
  · simp only [add_eq, mul_eq]

end NativeFinal

def originalSum {n : Nat} (x : Vector Binary32 n) : Binary32 :=
  let result := NativeFinal.sumLoop x 0 (Float32.ofBits 0)
  if hf : result.isFinite = true then ExecFloat.Binary.ofFloat32 result
  else referenceSum x

theorem originalSum_spec : ∀ (n : Nat) (x : Vector Binary32 n), originalSum x = sumSpec x.get := by
  intro n x
  unfold originalSum
  dsimp only
  split
  · rename_i hf
    have h := (NativeFinal.sumLoop_eq x 0 (Float32.ofBits 0) _ rfl hf).2
    change ExecFloat.Binary.ofFloat32 _ = Fin.foldl n _ posZero at h
    rw [Fin.foldl_eq_finRange_foldl] at h
    exact h
  · exact referenceSum_spec n x

theorem index_address (a b c d : Nat) : (a + b) * c + d = (a * c + d) + b * c := by
  rw [Nat.add_mul]
  omega

namespace Packed10

structure F10 where
  s0 : Float32
  s1 : Float32
  s2 : Float32
  s3 : Float32
  s4 : Float32
  s5 : Float32
  s6 : Float32
  s7 : Float32
  s8 : Float32
  s9 : Float32

@[inline] def zero32 : Float32 := Float32.ofBits 0

@[inline] def zero10 : F10 := ⟨zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32⟩

@[inline] def lane (v : F10) (l : Fin 10) : Float32 :=
  match l.val with
  | 0 => v.s0
  | 1 => v.s1
  | 2 => v.s2
  | 3 => v.s3
  | 4 => v.s4
  | 5 => v.s5
  | 6 => v.s6
  | 7 => v.s7
  | 8 => v.s8
  | _ => v.s9

@[inline] def packet (read : Nat → Float32) (col : Nat) : F10 :=
  ⟨read col, read (col + 1), read (col + 2), read (col + 3), read (col + 4), read (col + 5), read (col + 6), read (col + 7), read (col + 8), read (col + 9)⟩

@[inline] def update (acc : F10) (a : Float32) (v : F10) : F10 :=
  ⟨acc.s0 + a * v.s0, acc.s1 + a * v.s1, acc.s2 + a * v.s2, acc.s3 + a * v.s3, acc.s4 + a * v.s4, acc.s5 + a * v.s5, acc.s6 + a * v.s6, acc.s7 + a * v.s7, acc.s8 + a * v.s8, acc.s9 + a * v.s9⟩

theorem lane_packet (read : Nat → Float32) (col : Nat) (l : Fin 10) :
    lane (packet read col) l = read (col + l.val) := by
  rcases l with ⟨l, hl⟩
  have h : l = 0 ∨ l = 1 ∨ l = 2 ∨ l = 3 ∨ l = 4 ∨ l = 5 ∨ l = 6 ∨ l = 7 ∨ l = 8 ∨ l = 9 := by omega
  rcases h with rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> rfl

theorem lane_zero10 (l : Fin 10) : lane zero10 l = zero32 := by
  rcases l with ⟨l, hl⟩
  have h : l = 0 ∨ l = 1 ∨ l = 2 ∨ l = 3 ∨ l = 4 ∨ l = 5 ∨ l = 6 ∨ l = 7 ∨ l = 8 ∨ l = 9 := by omega
  rcases h with rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> rfl

theorem lane_zero (l : Fin 10) : lane zero10 l = zero32 :=
  lane_zero10 l

theorem lane_update (acc : F10) (a : Float32) (v : F10) (l : Fin 10) :
    lane (update acc a v) l = lane acc l + a * lane v l := by
  rcases l with ⟨l, hl⟩
  have h : l = 0 ∨ l = 1 ∨ l = 2 ∨ l = 3 ∨ l = 4 ∨ l = 5 ∨ l = 6 ∨ l = 7 ∨ l = 8 ∨ l = 9 := by omega
  rcases h with rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> rfl

@[inline] def groups (p : Nat) : Nat := (p + 9) / 10

theorem groups_pos_of_col (p j : Nat) (hj : j < p) :
    j / 10 < groups p := by
  unfold groups
  omega

theorem column_decomposition (j : Nat) :
    10 * (j / 10) + j % 10 = j := by
  omega

theorem vector_get_ofFn {α : Type} {n : Nat}
    (f : Fin n → α) (i : Fin n) : (Vector.ofFn f).get i = f i := by
  change (Vector.ofFn f)[i.val]'i.isLt = f i
  exact Vector.getElem_ofFn i.isLt

def packB (batch n p : Nat) (B : Vector Binary32 (batch * n * p)) :
    Vector (Vector (Vector F10 n) (groups p)) batch :=
  Vector.ofFn fun b =>
    Vector.ofFn fun g =>
      Vector.ofFn fun k =>
        packet (fun j =>
          if j < p then
            ExecFloat.Binary.toFloat32
              (B.toArray.getD ((b.val * n + k.val) * p + j) posZero)
          else zero32) (10 * g.val)

theorem packB_get (batch n p : Nat)
    (B : Vector Binary32 (batch * n * p))
    (b : Fin batch) (g : Fin (groups p)) (k : Fin n) :
    (((packB batch n p B).get b).get g).get k =
      packet (fun j =>
        if j < p then
          ExecFloat.Binary.toFloat32
            (B.toArray.getD ((b.val * n + k.val) * p + j) posZero)
        else zero32) (10 * g.val) := by
  simp only [packB, vector_get_ofFn]

theorem packB_lane (batch n p : Nat)
    (B : Vector Binary32 (batch * n * p))
    (b : Fin batch) (g : Fin (groups p)) (k : Fin n) (l : Fin 10)
    (hcol : 10 * g.val + l.val < p) :
    lane ((((packB batch n p B).get b).get g).get k) l =
      ExecFloat.Binary.toFloat32
        (B.toArray.getD
          ((b.val * n + k.val) * p + (10 * g.val + l.val)) posZero) := by
  rw [packB_get, lane_packet, if_pos hcol]

end Packed10


namespace Packed10

open FloatLib.Floats Competition

/-- Mapping the input preserves the total read, including the positive-zero default. -/
theorem nativeA_getD (Araw : Array Binary32) (i : Nat) :
    (Araw.map ExecFloat.Binary.toFloat32).getD i zero32 =
      ExecFloat.Binary.toFloat32 (Araw.getD i posZero) := by
  by_cases hi : i < Araw.size
  · simp [Array.getD, hi, zero32]
  · simp [Array.getD, hi, zero32] <;> rfl

/-- Ten independent left folds share each input load from the left operand. -/
def dot10 (n baseA : Nat) (A : Array Float32) (B : Vector F10 n)
    (k : Nat) (s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 : Float32) : F10 :=
  if hk : k < n then
    let sharedA := A.getD (baseA + k) zero32
    let v := B.get ⟨k, hk⟩
    dot10 n baseA A B (k + 1)
      (s0 + sharedA * v.s0)
      (s1 + sharedA * v.s1)
      (s2 + sharedA * v.s2)
      (s3 + sharedA * v.s3)
      (s4 + sharedA * v.s4)
      (s5 + sharedA * v.s5)
      (s6 + sharedA * v.s6)
      (s7 + sharedA * v.s7) (s8 + sharedA * v.s8) (s9 + sharedA * v.s9)
  else ⟨s0, s1, s2, s3, s4, s5, s6, s7, s8, s9⟩
termination_by n - k

theorem dot10_lane (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (B : Vector F10 n) (l : Fin 10)
    (hb : ∀ i : Fin n, lane (B.get i) l =
      ExecFloat.Binary.toFloat32 (Braw.getD (baseB + i.val * p) posZero))
    (k : Nat) (s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 : Float32) :
    lane (dot10 n baseA (Araw.map ExecFloat.Binary.toFloat32) B k s0 s1 s2 s3 s4 s5 s6 s7 s8 s9) l =
      NativeFinal.dotLoop n baseA baseB p Araw Braw k (lane ⟨s0, s1, s2, s3, s4, s5, s6, s7, s8, s9⟩ l) := by
  by_cases hk : k < n
  · rw [dot10, NativeFinal.dotLoop]
    simp only [dif_pos hk, if_pos hk]
    try dsimp only
    have ih := dot10_lane n baseA baseB p Araw Braw B l hb (k + 1)
      (s0 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s0)
      (s1 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s1)
      (s2 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s2)
      (s3 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s3)
      (s4 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s4)
      (s5 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s5)
      (s6 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s6)
      (s7 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s7)
      (s8 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s8)
      (s9 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s9)
    have hacc :
        lane ⟨s0 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s0, s1 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s1, s2 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s2, s3 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s3, s4 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s4, s5 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s5, s6 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s6, s7 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s7, s8 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s8, s9 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s9⟩ l =
          lane ⟨s0, s1, s2, s3, s4, s5, s6, s7, s8, s9⟩ l +
            ExecFloat.Binary.toFloat32 (Araw.getD (baseA + k) posZero) *
              ExecFloat.Binary.toFloat32 (Braw.getD (baseB + k * p) posZero) := by
      change lane (update ⟨s0, s1, s2, s3, s4, s5, s6, s7, s8, s9⟩
        ((Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32)
        (B.get ⟨k, hk⟩)) l = _
      rw [lane_update, nativeA_getD, hb ⟨k, hk⟩]
    rw [hacc] at ih
    exact ih
  · rw [dot10, NativeFinal.dotLoop]
    simp only [dif_neg hk, if_neg hk]
termination_by n - k

/-- The result guard and exact fallback are the same as in the scalar implementation. -/
def finish (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (result : Float32) : Binary32 :=
  if hf : result.isFinite = true then ExecFloat.Binary.ofFloat32 result
  else Fin.foldl n
    (fun a i => Submission.add a
      (Submission.mul (Araw.getD (baseA + i.val) posZero)
        (Braw.getD (baseB + i.val * p) posZero))) posZero

theorem finish_eq_dot (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (result : Float32)
    (hs : result = NativeFinal.dotLoop n baseA baseB p Araw Braw 0 zero32) :
    finish n baseA baseB p Araw Braw result =
      NativeFinal.dot n baseA baseB p Araw Braw := by
  rw [hs] <;> rfl

theorem finish_eq_fold (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (result : Float32)
    (hs : result = NativeFinal.dotLoop n baseA baseB p Araw Braw 0 zero32) :
    finish n baseA baseB p Araw Braw result =
      Fin.foldl n
        (fun a i => ExecFloat.add a
          (ExecFloat.mul (Araw.getD (baseA + i.val) posZero)
            (Braw.getD (baseB + i.val * p) posZero))) posZero := by
  rw [finish_eq_dot n baseA baseB p Araw Braw result hs, NativeFinal.dot_eq]

theorem finish_eq_kernel_fold (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (result : Float32)
    (hs : result = NativeFinal.dotLoop n baseA baseB p Araw Braw 0 zero32) :
    finish n baseA baseB p Araw Braw result =
      Fin.foldl n
        (fun a i => Submission.add a
          (Submission.mul (Araw.getD (baseA + i.val) posZero)
            (Braw.getD (baseB + i.val * p) posZero))) posZero := by
  rw [finish_eq_fold n baseA baseB p Araw Braw result hs]
  simp only [Submission.add_eq, Submission.mul_eq]

theorem finish_dot10_lane (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (B : Vector F10 n) (l : Fin 10)
    (hb : ∀ i : Fin n, lane (B.get i) l =
      ExecFloat.Binary.toFloat32 (Braw.getD (baseB + i.val * p) posZero)) :
    finish n baseA baseB p Araw Braw
        (lane (dot10 n baseA (Araw.map ExecFloat.Binary.toFloat32) B 0
          zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32) l) =
      NativeFinal.dot n baseA baseB p Araw Braw := by
  have hs := dot10_lane n baseA baseB p Araw Braw B l hb 0
    zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32
  have hz : lane (⟨zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32⟩ : F10) l = zero32 :=
    lane_zero10 l
  rw [hz] at hs
  exact finish_eq_dot n baseA baseB p Araw Braw _ hs

theorem finish_dot10_lane_fold (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (B : Vector F10 n) (l : Fin 10)
    (hb : ∀ i : Fin n, lane (B.get i) l =
      ExecFloat.Binary.toFloat32 (Braw.getD (baseB + i.val * p) posZero)) :
    finish n baseA baseB p Araw Braw
        (lane (dot10 n baseA (Araw.map ExecFloat.Binary.toFloat32) B 0
          zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32) l) =
      Fin.foldl n
        (fun a i => ExecFloat.add a
          (ExecFloat.mul (Araw.getD (baseA + i.val) posZero)
            (Braw.getD (baseB + i.val * p) posZero))) posZero := by
  rw [finish_dot10_lane n baseA baseB p Araw Braw B l hb, NativeFinal.dot_eq]

end Packed10


namespace Packed10

open Competition

/-- Every inhabited row-major output index decodes to valid tensor coordinates. -/
theorem decode_bounds (batch m p : Nat) (q : Fin (batch * m * p)) :
    (bmmDecodeC m p q.val).1 < batch ∧
      (bmmDecodeC m p q.val).2.1 < m ∧
      (bmmDecodeC m p q.val).2.2 < p := by
  have hq : q.val < batch * (m * p) := by
    simpa only [Nat.mul_assoc] using q.isLt
  have hmp : m * p ≠ 0 := by
    intro h
    rw [h, Nat.mul_zero] at hq
    omega
  have hp : p ≠ 0 := by
    intro h
    apply hmp
    simp only [h, Nat.mul_zero]
  have hmpPos : 0 < m * p := by omega
  have hpPos : 0 < p := by omega
  simp only [bmmDecodeC, hmp, hp, if_false]
  refine ⟨?_, ?_, ?_⟩
  · exact (Nat.div_lt_iff_lt_mul hmpPos).2 hq
  · exact (Nat.div_lt_iff_lt_mul hpPos).2 (Nat.mod_lt q.val hmpPos)
  · exact Nat.mod_lt _ hpPos

end Packed10


namespace Packed10Index

open Packed10

theorem addNat (a b : USize) (h : a.toNat + b.toNat < USize.size) :
    (a + b).toNat = a.toNat + b.toNat := by
  rw [USize.toNat_add]
  exact Nat.mod_eq_of_lt h

theorem stepNat {n k : USize} (hk : k < n) : (k + 1).toNat = k.toNat + 1 := by
  rw [USize.toNat_add, USize.toNat_one]
  have hkn := USize.lt_iff_toNat_lt.mp hk
  have hn := USize.toNat_lt_size n
  apply Nat.mod_eq_of_lt
  change k.toNat + 1 < USize.size
  omega

theorem next_decreases {n k : USize} (hk : k < n) :
    n.toNat - (k + 1).toNat < n.toNat - k.toNat := by
  rw [stepNat hk]
  have hkn := USize.lt_iff_toNat_lt.mp hk
  omega

theorem boundA (base n k size : Nat) (h : base + (n - 1) < size) (hk : k < n) :
    base + k < size := by omega

theorem ugetA_getD (A : Array Float32) (i : USize) (h : i.toNat < A.size) :
    A.uget i h = A.getD i.toNat zero32 := by
  simp [Array.uget, Array.getD, h]

theorem ugetB_get {n : Nat} (B : Vector F10 n) (i : USize)
    (hi : i.toNat < n) :
    B.toArray.uget i (by simpa only [B.size_toArray] using hi) =
      B.get ⟨i.toNat, hi⟩ := by
  rfl

/-- The bounds are established once; each iteration reads with machine-word indices. -/
def loop {n : Nat} (count baseA : USize) (A : Array Float32) (B : Vector F10 n)
    (hn : count.toNat = n)
    (hA : baseA.toNat + (count.toNat - 1) < A.size)
    (hAS : A.size < USize.size)
    (k : USize) (s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 : Float32) : F10 :=
  if hk : k < count then
    have hkn : k.toNat < n := by
      rw [← hn]
      exact USize.lt_iff_toNat_lt.mp hk
    have ha := boundA baseA.toNat count.toNat k.toNat A.size hA
      (USize.lt_iff_toNat_lt.mp hk)
    let a := A.uget (baseA + k)
      (by rw [addNat baseA k (Nat.lt_trans ha hAS)]; exact ha)
    let v := B.toArray.uget k (by simpa only [B.size_toArray] using hkn)
    loop count baseA A B hn hA hAS (k + 1)
      (s0 + a * v.s0) (s1 + a * v.s1)
      (s2 + a * v.s2) (s3 + a * v.s3)
      (s4 + a * v.s4) (s5 + a * v.s5)
      (s6 + a * v.s6) (s7 + a * v.s7) (s8 + a * v.s8) (s9 + a * v.s9)
  else ⟨s0, s1, s2, s3, s4, s5, s6, s7, s8, s9⟩
termination_by count.toNat - k.toNat
decreasing_by
  apply next_decreases
  assumption

theorem loop_eq {n : Nat} (count baseA : USize) (A : Array Float32) (B : Vector F10 n)
    (hn : count.toNat = n)
    (hA : baseA.toNat + (count.toNat - 1) < A.size)
    (hAS : A.size < USize.size)
    (k : USize) (s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 : Float32) :
    loop count baseA A B hn hA hAS k s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 =
      Packed10.dot10 n baseA.toNat A B k.toNat s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 := by
  rw [loop]
  split
  · rename_i hk
    have hkn : k.toNat < n := by
      rw [← hn]
      exact USize.lt_iff_toNat_lt.mp hk
    have ha := boundA baseA.toNat count.toNat k.toNat A.size hA
      (USize.lt_iff_toNat_lt.mp hk)
    rw [Packed10.dot10, dif_pos hkn]
    dsimp only
    rw [loop_eq, stepNat hk]
    simp only [ugetA_getD, addNat baseA k (Nat.lt_trans ha hAS), ugetB_get]
    rfl
  · rename_i hk
    have hkn : ¬ k.toNat < n := by
      rw [← hn]
      simpa only [USize.lt_iff_toNat_lt] using hk
    rw [Packed10.dot10, dif_neg hkn]
termination_by count.toNat - k.toNat
decreasing_by
  apply next_decreases
  assumption

@[inline] def within (n baseA : Nat) (A : Array Float32) (B : Vector F10 n)
    (hn : n < USize.size) (ha : baseA < USize.size)
    (hA : baseA + (n - 1) < A.size) (hAS : A.size < USize.size) : F10 :=
  loop (USize.ofNat n) (USize.ofNat baseA) A B
    (USize.toNat_ofNat_of_lt' hn)
    (by simpa only [USize.toNat_ofNat_of_lt' hn, USize.toNat_ofNat_of_lt' ha] using hA)
    hAS 0 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32

theorem within_eq (n baseA : Nat) (A : Array Float32) (B : Vector F10 n)
    (hn : n < USize.size) (ha : baseA < USize.size)
    (hA : baseA + (n - 1) < A.size) (hAS : A.size < USize.size) :
    within n baseA A B hn ha hA hAS =
      Packed10.dot10 n baseA A B 0 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 := by
  simp only [within, loop_eq, USize.toNat_ofNat_of_lt' hn,
    USize.toNat_ofNat_of_lt' ha, USize.toNat_zero]

@[inline] def runDot (n baseA : Nat) (A : Array Float32) (B : Vector F10 n) : F10 :=
  if h : n < USize.size ∧ baseA < USize.size ∧
      baseA + (n - 1) < A.size ∧ A.size < USize.size then
    within n baseA A B h.1 h.2.1 h.2.2.1 h.2.2.2
  else Packed10.dot10 n baseA A B 0 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32

theorem runDot_eq (n baseA : Nat) (A : Array Float32) (B : Vector F10 n) :
    runDot n baseA A B =
      Packed10.dot10 n baseA A B 0 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 := by
  unfold runDot
  split
  · rename_i h
    exact within_eq n baseA A B h.1 h.2.1 h.2.2.1 h.2.2.2
  · rfl

end Packed10Index

namespace Packed10

def tileResults (batch m n p : Nat) (A : Array Float32)
    (B : Vector (Vector (Vector F10 n) (groups p)) batch) :
    Vector (Vector (Vector F10 (groups p)) m) batch :=
  Vector.ofFn fun b =>
    Vector.ofFn fun i =>
      Vector.ofFn fun g =>
        Packed10Index.runDot n ((b.val * m + i.val) * n) A ((B.get b).get g)

theorem tileResults_get (batch m n p : Nat) (A : Array Float32)
    (B : Vector (Vector (Vector F10 n) (groups p)) batch)
    (b : Fin batch) (i : Fin m) (g : Fin (groups p)) :
    (((tileResults batch m n p A B).get b).get i).get g =
      dot10 n ((b.val * m + i.val) * n) A ((B.get b).get g) 0
        zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 := by
  simp only [tileResults, vector_get_ofFn, Packed10Index.runDot_eq]

theorem tile_finish (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (b : Fin batch) (i : Fin m) (g : Fin (groups p)) (l : Fin 10)
    (hcol : 10 * g.val + l.val < p) :
    finish n ((b.val * m + i.val) * n)
        (b.val * n * p + (10 * g.val + l.val)) p A.toArray B.toArray
        (lane ((((tileResults batch m n p
          (A.toArray.map ExecFloat.Binary.toFloat32) (packB batch n p B)).get b).get i).get g) l) =
      NativeFinal.dot n ((b.val * m + i.val) * n)
        (b.val * n * p + (10 * g.val + l.val)) p A.toArray B.toArray := by
  rw [tileResults_get]
  apply finish_dot10_lane
  intro k
  rw [packB_lane batch n p B b g k l hcol]
  rw [index_address (b.val * n) k.val p (10 * g.val + l.val)]

@[inline] def inlineDecodeC (m p : Nat) (q : Nat) : Nat × Nat × Nat :=
  let rowSize := m * p
  let b := if rowSize = 0 then 0 else q / rowSize
  let r := if rowSize = 0 then 0 else q % rowSize
  let i := if p = 0 then 0 else r / p
  let j := if p = 0 then 0 else r % p
  (b, i, j)

theorem inlineDecodeC_eq (m p q : Nat) :
    inlineDecodeC m p q = bmmDecodeC m p q := by
  rfl

def outputFromTiles (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (tiles : Vector (Vector (Vector F10 (groups p)) m) batch)
    (q : Fin (batch * m * p)) : Binary32 :=
  let d := inlineDecodeC m p q.val
  let b : Fin batch := ⟨d.1, (decode_bounds batch m p q).1⟩
  let i : Fin m := ⟨d.2.1, (decode_bounds batch m p q).2.1⟩
  let g : Fin (groups p) :=
    ⟨d.2.2 / 10, groups_pos_of_col p d.2.2 (decode_bounds batch m p q).2.2⟩
  let l : Fin 10 := ⟨d.2.2 % 10, Nat.mod_lt _ (by decide)⟩
  finish n ((d.1 * m + d.2.1) * n) (d.1 * n * p + d.2.2) p A.toArray B.toArray
    (lane (((tiles.get b).get i).get g) l)

theorem outputFromTiles_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (q : Fin (batch * m * p)) :
    outputFromTiles batch m n p A B
        (tileResults batch m n p (A.toArray.map ExecFloat.Binary.toFloat32)
          (packB batch n p B)) q =
      let (b, i, j) := bmmDecodeC m p q.val
      NativeFinal.dot n ((b * m + i) * n) (b * n * p + j) p A.toArray B.toArray := by
  let d := bmmDecodeC m p q.val
  let b : Fin batch := ⟨d.1, (decode_bounds batch m p q).1⟩
  let i : Fin m := ⟨d.2.1, (decode_bounds batch m p q).2.1⟩
  let g : Fin (groups p) :=
    ⟨d.2.2 / 10, groups_pos_of_col p d.2.2 (decode_bounds batch m p q).2.2⟩
  let l : Fin 10 := ⟨d.2.2 % 10, Nat.mod_lt _ (by decide)⟩
  have hc : 10 * g.val + l.val = d.2.2 := column_decomposition d.2.2
  have hcol : 10 * g.val + l.val < p := by
    rw [hc]
    exact (decode_bounds batch m p q).2.2
  have ht := tile_finish batch m n p A B b i g l hcol
  change finish n ((b.val * m + i.val) * n) (b.val * n * p + d.2.2) p
      A.toArray B.toArray
      (lane ((((tileResults batch m n p
        (A.toArray.map ExecFloat.Binary.toFloat32) (packB batch n p B)).get b).get i).get g) l) =
    NativeFinal.dot n ((b.val * m + i.val) * n) (b.val * n * p + d.2.2) p
      A.toArray B.toArray
  simpa only [hc] using ht

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
  let packedB := packB batch n p B
  let tiles := tileResults batch m n p nativeA packedB
  Vector.ofFn (outputFromTiles batch m n p A B tiles)

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = referenceBmm batch m n p A B := by
  unfold core referenceBmm
  dsimp only
  apply congrArg (fun (f : Fin (batch * m * p) → Binary32) => Vector.ofFn f)
  funext q
  rw [outputFromTiles_eq]
  dsimp only
  rw [NativeFinal.dot_eq]
  simp only [add_eq, mul_eq]
  apply congrArg (fun (f : Binary32 → Fin n → Binary32) => Fin.foldl n f posZero)
  funext acc k
  have hi := index_address ((bmmDecodeC m p q.val).1 * n) k.val p
    (bmmDecodeC m p q.val).2.2
  rw [hi]

end Packed10

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if batch * m * p = 0 then referenceBmm batch m n p A B
  else if n = 0 then referenceBmm batch m n p A B
  else Packed10.core batch m n p A B

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  have h : bmm batch m n p A B = referenceBmm batch m n p A B := by
    unfold bmm
    split
    · rfl
    · split
      · rfl
      · exact Packed10.core_eq_reference batch m n p A B
  exact (congrArg (fun v : Vector Binary32 (batch * m * p) => v.get) h).trans
    (referenceBmm_spec batch m n p A B)


end Submission

namespace Submission.NativeDecodeSum

open FloatLib.Floats Competition

@[inline] def decode (x : Binary32) : Float32 := R2W01b.convert x.raw.1

theorem decode_eq (x : Binary32) : decode x = ExecFloat.Binary.toFloat32 x := by
  unfold decode
  rw [R2W01c.convert_eq]
  rfl

def loop {n : Nat} (x : Vector Binary32 n) (k : Nat) (acc : Float32) : Float32 :=
  if hk : k < n then
    loop x (k + 1) (acc + decode (x.get ⟨k, hk⟩))
  else acc
termination_by n - k

theorem loop_eq {n : Nat} (x : Vector Binary32 n) (k : Nat) (acc : Float32) :
    loop x k acc = NativeFinal.sumLoop x k acc := by
  by_cases hk : k < n
  · rw [loop, NativeFinal.sumLoop]
    simp only [dif_pos hk]
    rw [decode_eq]
    exact loop_eq x (k + 1) (acc + ExecFloat.Binary.toFloat32 (x.get ⟨k, hk⟩))
  · rw [loop, NativeFinal.sumLoop]
    simp only [dif_neg hk]
termination_by n - k

end Submission.NativeDecodeSum

namespace Submission.NativeDecodeSumWord

open FloatLib.Floats Competition

def loop {n : Nat} (x : Vector Binary32 n) (count : USize)
    (hn : count.toNat = n) (k : USize) (acc : Float32) : Float32 :=
  if hk : k < count then
    have hkn : k.toNat < n := by rw [← hn]; exact USize.lt_iff_toNat_lt.mp hk
    let value := x.toArray.uget k (by simpa only [x.size_toArray] using hkn)
    loop x count hn (k + 1) (acc + NativeDecodeSum.decode value)
  else acc
termination_by count.toNat - k.toNat
decreasing_by exact Packed10Index.next_decreases (by assumption)

theorem loop_eq {n : Nat} (x : Vector Binary32 n) (count : USize)
    (hn : count.toNat = n) (k : USize) (acc : Float32) :
    loop x count hn k acc = NativeDecodeSum.loop x k.toNat acc := by
  rw [loop]
  split
  · rename_i hk
    have hkn : k.toNat < n := by rw [← hn]; exact USize.lt_iff_toNat_lt.mp hk
    rw [NativeDecodeSum.loop, dif_pos hkn]
    dsimp only
    rw [loop_eq, Packed10Index.stepNat hk]
    rfl
  · rename_i hk
    have hkn : ¬ k.toNat < n := by
      rw [← hn]
      simpa only [USize.lt_iff_toNat_lt] using hk
    rw [NativeDecodeSum.loop, dif_neg hkn]
termination_by count.toNat - k.toNat
decreasing_by exact Packed10Index.next_decreases (by assumption)

@[inline] def run {n : Nat} (x : Vector Binary32 n) : Float32 :=
  if hn : n < USize.size then
    loop x (USize.ofNat n) (USize.toNat_ofNat_of_lt' hn) 0 (Float32.ofBits 0)
  else NativeDecodeSum.loop x 0 (Float32.ofBits 0)

theorem run_eq {n : Nat} (x : Vector Binary32 n) :
    run x = NativeDecodeSum.loop x 0 (Float32.ofBits 0) := by
  unfold run
  split
  · rw [loop_eq, USize.toNat_zero]
  · rfl

end Submission.NativeDecodeSumWord

namespace Submission

open FloatLib.Floats Competition

def sum {n : Nat} (x : Vector Binary32 n) : Binary32 :=
  let result := NativeDecodeSumWord.run x
  if hf : result.isFinite = true then ExecFloat.Binary.ofFloat32 result
  else referenceSum x

theorem sum_spec : ∀ (n : Nat) (x : Vector Binary32 n), sum x = sumSpec x.get := by
  intro n x
  have h : sum x = originalSum x := by
    unfold sum originalSum
    rw [NativeDecodeSumWord.run_eq, NativeDecodeSum.loop_eq]
  exact h.trans (originalSum_spec n x)

end Submission
