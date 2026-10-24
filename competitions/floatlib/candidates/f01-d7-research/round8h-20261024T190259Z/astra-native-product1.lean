
/- R14: first native product and exact second scaling, without a fusion runtime. -/
namespace Submission.R14NativeProduct

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics
open Model.NativeBinary32

theorem model_mul_of_nonzero_decodes {fmt : FloatFormat}
    (x y : Model fmt) (dx dy : Dyadic)
    (hx : Model.toDyadic? x = some dx) (hy : Model.toDyadic? y = some dy)
    (hx0 : dx.significand ≠ 0) (hy0 : dy.significand ≠ 0) :
    Model.mul x y = Model.roundDyadic fmt
      ⟨Bool.xor dx.negative dy.negative, dx.significand * dy.significand,
        dx.exponent + dy.exponent⟩ := by
  rw [Model.Proof.mul_eq_spec]
  unfold Model.Spec.mul
  rw [hx, hy]
  simp [hx0, hy0]

/-- UInt32 conversion is exact on 24-bit mantissas. The native multiplication is NOT exact:
its result is precisely the original roundProduct at integer scale 298. -/
theorem native_mantissa_product (a b : UInt32)
    (ha : 8388608 ≤ a.toNat) (ha' : a.toNat < 16777216)
    (hb : 8388608 ≤ b.toNat) (hb' : b.toNat < 16777216) :
    a.toFloat32 * b.toFloat32 =
      Float32.ofBits (roundProduct false (a.toUInt64 * b.toUInt64) 298) := by
  have hxa := R2W01c.uint32_mantissa_model_decode a ha ha'
  have hxb := R2W01c.uint32_mantissa_model_decode b hb hb'
  have ha0 : a.toNat ≠ 0 := by omega
  have hb0 : b.toNat ≠ 0 := by omega
  have hbound := Nat.mul_le_mul (Nat.le_of_lt ha') (Nat.le_of_lt hb')
  have hfit : a.toNat * b.toNat < 18446744073709551616 := by
    norm_num at hbound
    omega
  have hp : (a.toUInt64 * b.toUInt64).toNat = a.toNat * b.toNat := by
    rw [UInt64.toNat_mul, UInt32.toNat_toUInt64, UInt32.toNat_toUInt64]
    exact Nat.mod_eq_of_lt hfit
  apply R2W01c.native_mul_eq_of_decoded_raw_model_mul_eq
  · exact hxa
  · exact hxb
  · have hm := model_mul_of_nonzero_decodes
      (R2W01c.nativeModel a.toFloat32) (R2W01c.nativeModel b.toFloat32)
      ⟨false, a.toNat, 0⟩ ⟨false, b.toNat, 0⟩ hxa hxb ha0 hb0
    have hw : R2W01c.rawModel
        (roundProduct false (a.toUInt64 * b.toUInt64) 298) =
        Model.roundDyadic FloatFormat.binary32
          ⟨false, a.toNat * b.toNat, 0⟩ := by
      rw [R2W01c.rawModel_eq_native32,
        roundProduct_eq_roundDyadic false (a.toUInt64 * b.toUInt64) 298 (by decide),
        ofUInt32_roundDyadic]
      change Model.roundDyadic FloatFormat.binary32
          ⟨false, (a.toUInt64 * b.toUInt64).toNat, 0⟩ = _
      rw [hp]
    simpa only [Bool.false_xor, Int.zero_add] using hm.trans hw.symm

theorem dyadic_general_scale_value (sign : Bool) (m k : Nat) (a b : Int) :
    (Dyadic.mk false m a).toReal * (Dyadic.mk sign (2 ^ k) b).toReal =
      (Dyadic.mk sign m (a + b + (k : Int))).toReal := by
  cases sign <;>
    simp [Dyadic.toReal, Dyadic.signedSignificand,
      zpow_add₀ (by norm_num : (2 : ℝ) ≠ 0)] <;> ring <;> simp

/-- Exact power-of-two rescaling of a decoded rounded intermediate. Finiteness/nonzero of the
target is supplied by its actual decode, not an assumption that rounding is associative. -/
theorem model_mul_of_general_scale_decodes {fmt : FloatFormat}
    (x y z : Model fmt) (hfmt : fmt.isIEEE = true)
    (sign : Bool) (m k : Nat) (a b : Int) (hm : m ≠ 0)
    (hx : Model.toDyadic? x = some ⟨false, m, a⟩)
    (hy : Model.toDyadic? y = some ⟨sign, 2 ^ k, b⟩)
    (hz : Model.toDyadic? z = some ⟨sign, m, a + b + (k : Int)⟩) :
    Model.mul x y = z := by
  have hxfinite := Model.isFinite_eq_true_of_toDyadic?_some hx
  have hyfinite := Model.isFinite_eq_true_of_toDyadic?_some hy
  have hzfinite := Model.isFinite_eq_true_of_toDyadic?_some hz
  have hz0 : Model.toReal z ≠ 0 := by
    have hd0 : (Dyadic.mk sign m (a + b + (k : Int))).toReal ≠ 0 :=
      (Dyadic.toReal_eq_zero_iff _).not.mpr hm
    simpa only [Model.toReal_eq, hz] using hd0
  apply R2W01cModel.mul_eq_of_finite_value x y z hfmt
    hxfinite hyfinite hzfinite hz0
  simpa only [Model.toReal_eq, hx, hy, hz] using
    dyadic_general_scale_value sign m k a b

end Submission.R14NativeProduct
