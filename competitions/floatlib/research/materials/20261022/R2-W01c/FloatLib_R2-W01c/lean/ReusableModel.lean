import ContractTensor

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
