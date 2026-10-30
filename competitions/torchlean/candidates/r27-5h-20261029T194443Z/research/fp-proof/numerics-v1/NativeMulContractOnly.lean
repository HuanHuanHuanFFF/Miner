import ContractExact

namespace R2W01c
namespace NativeBridge

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open Float.Model.UnpackedFloat
open FloatLib.Floats.Formats.BinaryInterchange.Model






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

end NativeBridge
end R2W01c

/-
R24 portable binary64 native multiplication bridge.
The complete retained B2 prefix and its four public endpoints are unchanged.
This reuses B2's format-polymorphic modelMulFinite proof; it does not assume
an opaque Float32/Float cast and does not depend on the uncompiled widen1 helper.
-/
namespace Submission.R24NativeMul

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

abbrev F64 := FloatFormat.binary64
abbrev F32 := FloatFormat.binary32
abbrev view (x : Float) : Model F64 := Model.ofFloatModel x.toModel
noncomputable abbrev value (x : Float) : Real := Model.toReal (view x)
abbrev raw32 (u : UInt32) : Model F32 := Model.ofUInt32 u

/-- Actual native Float multiplication agrees with Model.mul on every finite
input, including signed zeros. The result is allowed to overflow. -/
theorem native_mul_toModel (x y : Float)
    (hx : x.isFinite = true) (hy : y.isFinite = true) :
    ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat (x * y)) =
      Model.mul (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat x))
        (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat y)) := by
  rw [ExecFloat.Binary.toModel_ofFloat, ExecFloat.Binary.toModel_ofFloat,
    ExecFloat.Binary.toModel_ofFloat]
  change Model.ofFloatModel (Float.Model.mul x.toModel y.toModel) = _
  rw [Float.Model.mul, Model.ofFloatModel_pack]
  have h := R2W01c.NativeBridge.modelMulFinite (fmt := F64)
    (by decide) (Model.ofFloatModel x.toModel) (Model.ofFloatModel y.toModel)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite,
      Float.Model.isFinite] using hx)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite,
      Float.Model.isFinite] using hy)
  rw [Model.toModel_ofFloatModel, Model.toModel_ofFloatModel] at h
  exact h.symm

private theorem mul_view (x y : Float)
    (hx : x.isFinite = true) (hy : y.isFinite = true) :
    view (x * y) = Model.mul (view x) (view y) := by
  change Model.ofFloatModel (Float.Model.mul x.toModel y.toModel) = _
  rw [Float.Model.mul, Model.ofFloatModel_pack]
  have h := R2W01c.NativeBridge.modelMulFinite (fmt := F64)
    (by decide) (Model.ofFloatModel x.toModel) (Model.ofFloatModel y.toModel)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite,
      Float.Model.isFinite] using hx)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite,
      Float.Model.isFinite] using hy)
  rw [Model.toModel_ofFloatModel, Model.toModel_ofFloatModel] at h
  exact h.symm

private theorem model_finite (x : Float) (hx : x.isFinite = true) :
    Model.isFinite (view x) = true := by
  have hxmodel : (Model.toModel (view x)).isFinite = true := by
    simpa only [view, Model.toModel_ofFloatModel, Float.isFinite,
      Float.Model.isFinite] using hx
  have hsome : (Model.toDyadic? (view x)).isSome = true := by
    rw [Model.toDyadic?_ieee_eq_model F64 (by decide)]
    cases hm : Model.toModel (view x) <;>
      simp_all [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.isFinite]
  cases hd : Model.toDyadic? (view x) with
  | none => simp [hd] at hsome
  | some d => exact Model.isFinite_eq_true_of_toDyadic?_some hd

private theorem native_finite (x : Float) (hx : Model.isFinite (view x) = true) :
    x.isFinite = true := by
  obtain ⟨d, hd⟩ := Model.exists_toDyadic?_of_isFinite hx
  rw [Model.toDyadic?_ieee_eq_model F64 (by decide),
    Model.toModel_ofFloatModel] at hd
  change x.toModel.unpack.isFinite = true
  cases hm : x.toModel.unpack <;>
    simp_all [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.isFinite]

/-- A symbolic exact-product bound gives finiteness and the real RNE64
semantics of the actual native multiplication; output finiteness is proved. -/
theorem native_mul_finite_roundAt (x y : Float)
    (hx : x.isFinite = true) (hy : y.isFinite = true)
    (hbound : |value x| * |value y| ≤ Model.toReal (Model.posMaxFinite F64)) :
    (x * y).isFinite = true ∧
      value (x * y) = Model.roundAt F64 (value x * value y) := by
  have hmx := model_finite x hx
  have hmy := model_finite y hy
  have hp := Model.isFinite_mul_of_abs_mul_le_posMaxFinite
    (view x) (view y) (by decide) hmx hmy hbound
  have hpview : Model.isFinite (view (x * y)) = true := by
    rw [mul_view x y hx hy]
    exact hp
  refine ⟨native_finite (x * y) hpview, ?_⟩
  change Model.toReal (view (x * y)) = _
  rw [mul_view x y hx hy]
  exact Model.toReal_mul_eq_roundAt (view x) (view y) (by decide) hmx hmy hp

private theorem max32_squared_le_max64 :
    Model.toReal (Model.posMaxFinite F32) * Model.toReal (Model.posMaxFinite F32) ≤
      Model.toReal (Model.posMaxFinite F64) := by
  change Model.toReal (Model.ofFields F32 false 254 8388607) *
      Model.toReal (Model.ofFields F32 false 254 8388607) ≤
    Model.toReal (Model.ofFields F64 false 2046 4503599627370495)
  simp only [Model.toReal_ofFields_normal F32 false 254 8388607
      (by decide) (by decide) (by decide),
    Model.toReal_ofFields_normal F64 false 2046 4503599627370495
      (by decide) (by decide) (by decide)]
  change ((1 : Real) * 16777215 * Model.bpow 104) *
      ((1 : Real) * 16777215 * Model.bpow 104) ≤
    (1 : Real) * 9007199254740991 * Model.bpow 971
  simp only [one_mul]
  have hcoef : (16777215 : Real) * 16777215 ≤ 9007199254740991 := by norm_num
  have hpow : Model.bpow 208 ≤ Model.bpow 971 :=
    Model.bpow_le_bpow_of_le (by decide)
  calc
    ((16777215 : Real) * Model.bpow 104) * (16777215 * Model.bpow 104) =
        (16777215 * 16777215) * Model.bpow 208 := by
      rw [show (208 : Int) = 104 + 104 by decide, Model.bpow_add]
      ring
    _ ≤ (9007199254740991 : Real) * Model.bpow 208 :=
      mul_le_mul_of_nonneg_right hcoef (Model.bpow_nonneg 208)
    _ ≤ (9007199254740991 : Real) * Model.bpow 971 :=
      mul_le_mul_of_nonneg_left hpow (by norm_num)

private theorem f32_product_bound (a b : Model F32)
    (ha : Model.isFinite a = true) (hb : Model.isFinite b = true) :
    |Model.toReal a| * |Model.toReal b| ≤ Model.toReal (Model.posMaxFinite F64) := by
  have hA := Model.abs_toReal_le_posMaxFinite_of_isIEEE_of_isFinite a (by decide) ha
  have hB := Model.abs_toReal_le_posMaxFinite_of_isIEEE_of_isFinite b (by decide) hb
  have hnonneg : 0 ≤ Model.toReal (Model.posMaxFinite F32) :=
    (abs_nonneg (Model.toReal a)).trans hA
  exact (mul_le_mul hA hB (abs_nonneg _) hnonneg).trans max32_squared_le_max64

private theorem f32_product_grid (a b : Model F32)
    (ha : Model.isFinite a = true) (hb : Model.isFinite b = true) :
    FloatLib.Floats.Formats.Flocq.genericFormat FloatLib.Numerics.binaryRadix
      (Model.fexpOf F64) (Model.toReal a * Model.toReal b) := by
  obtain ⟨da, hda⟩ := Model.exists_toDyadic?_of_isFinite ha
  obtain ⟨db, hdb⟩ := Model.exists_toDyadic?_of_isFinite hb
  let d : FloatLib.Numerics.Dyadic :=
    ⟨Bool.xor da.negative db.negative, da.significand * db.significand,
      da.exponent + db.exponent⟩
  have hma := Model.toDyadic?_significand_lt a hda
  have hmb := Model.toDyadic?_significand_lt b hdb
  change da.significand < 2 ^ 24 at hma
  change db.significand < 2 ^ 24 at hmb
  have hsig : d.significand < 2 ^ (F64.fracWidth + 1) := by
    change da.significand * db.significand < 2 ^ 53
    calc
      da.significand * db.significand < 2 ^ 24 * 2 ^ 24 := Nat.mul_lt_mul'' hma hmb
      _ < 2 ^ 53 := by norm_num
  have hea := Model.minSubnormalExponent_le_toDyadic? a hda
  have heb := Model.minSubnormalExponent_le_toDyadic? b hdb
  change (-149 : Int) ≤ da.exponent at hea
  change (-149 : Int) ≤ db.exponent at heb
  have he : F64.minSubnormalExponent ≤ d.exponent := by
    change (-1074 : Int) ≤ da.exponent + db.exponent
    omega
  have hg := Model.Dyadic.genericFormat_of_significand_lt F64 d hsig he
  have hv : d.toReal = Model.toReal a * Model.toReal b := by
    simpa only [d, Model.toReal_eq, hda, hdb] using Model.Dyadic.toReal_mul da db
  rw [hv] at hg
  exact hg

/-- Once two native inputs have finite binary32 values, native binary64 MUL
is finite and exact. The product's 48-bit/grid and magnitude facts are proved,
not assumed. This theorem does not assert correctness of any widening cast. -/
theorem native_mul_exact_from_raw32_values (x y : Float) (a b : UInt32)
    (hx : x.isFinite = true) (hy : y.isFinite = true)
    (ha : Model.isFinite (raw32 a) = true) (hb : Model.isFinite (raw32 b) = true)
    (hxa : value x = Model.toReal (raw32 a))
    (hyb : value y = Model.toReal (raw32 b)) :
    (x * y).isFinite = true ∧
      value (x * y) = Model.toReal (raw32 a) * Model.toReal (raw32 b) := by
  have hbound : |value x| * |value y| ≤ Model.toReal (Model.posMaxFinite F64) := by
    rw [hxa, hyb]
    exact f32_product_bound (raw32 a) (raw32 b) ha hb
  obtain ⟨hfinite, hround⟩ := native_mul_finite_roundAt x y hx hy hbound
  refine ⟨hfinite, ?_⟩
  rw [hround, hxa, hyb]
  exact FloatLib.Floats.Formats.Flocq.round_preserves_generic
    FloatLib.Floats.Formats.Flocq.nearestEven _
    (f32_product_grid (raw32 a) (raw32 b) ha hb)

end Submission.R24NativeMul
