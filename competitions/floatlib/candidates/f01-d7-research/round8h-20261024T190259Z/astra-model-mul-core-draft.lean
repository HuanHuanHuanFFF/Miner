
/- R14: first native product and exact second scaling, without a fusion runtime. -/
namespace Submission.R14NativeProduct

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics
open Model.NativeBinary32

theorem model_mul_of_nonzero_decodes {fmt : FloatFormat}
    (x y : Model fmt) (dx dy : FloatLib.Numerics.Dyadic)
    (hx : Model.toDyadic? x = some dx) (hy : Model.toDyadic? y = some dy)
    (hx0 : dx.significand ≠ 0) (hy0 : dy.significand ≠ 0) :
    Model.mul x y = Model.roundDyadic fmt
      ⟨Bool.xor dx.negative dy.negative, dx.significand * dy.significand,
        dx.exponent + dy.exponent⟩ := by
  rw [Model.Proof.mul_eq_spec]
  unfold Model.Spec.mul
  rw [hx, hy]
  simp [hx0, hy0]

end Submission.R14NativeProduct
