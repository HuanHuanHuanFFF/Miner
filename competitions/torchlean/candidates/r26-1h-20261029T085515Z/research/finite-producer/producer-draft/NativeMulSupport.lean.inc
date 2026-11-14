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
