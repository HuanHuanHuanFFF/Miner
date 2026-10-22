import ContractTensor

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
