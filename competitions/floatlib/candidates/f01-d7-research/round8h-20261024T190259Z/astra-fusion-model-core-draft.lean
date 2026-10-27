
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
