namespace R7W05
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
open Float.Model.UnpackedFloat

theorem model_toModel_isNaN (x : Model FloatFormat.binary32) :
    (Model.toModel x).isNaN = Model.isNaN x := by
  have he : unpackExponent (Model.toModelBits x) = -1#(FloatFormat.binary32.toModel.exponentBits) ↔
      Model.expField x = FloatFormat.binary32.expAllOnesNat := by
    rw [← BitVec.toNat_inj, Model.unpackExponent_toNat,
      Model.toNat_neg_one_exponentBits]
  have hm : unpackMantissa (Model.toModelBits x) = 0#(FloatFormat.binary32.toModel.mantissaBitsWithoutImplicit) ↔
      Model.fracField x = 0 := by
    rw [← BitVec.toNat_inj, Model.unpackMantissa_toNat]
    rfl
  change (Model.toModel x).isNaN = Model.IEEE.isNaN x
  unfold Model.toModel unpack
  dsimp only
  split_ifs <;>
    simp_all [Float.Model.UnpackedFloat.isNaN, Model.IEEE.isNaN]

theorem toFloat32_isNaN (x : Binary32) :
    (ExecFloat.Binary.toFloat32 x).isNaN = Model.isNaN (ExecFloat.Binary.toModel x) := by
  change ((Model.toFloat32Model (ExecFloat.Binary.toModel x)).unpack).isNaN = _
  rw [Model.unpack_toFloat32Model]
  exact model_toModel_isNaN _

theorem native_eq_nan_of_isNaN (x : Float32) (hx : x.isNaN = true) :
    x = Float32.nan := by
  have hunpack : x.toModel.unpack = .notANumber := by
    change x.toModel.unpack.isNaN = true at hx
    cases h : x.toModel.unpack <;> simp_all [Float.Model.UnpackedFloat.isNaN]
  cases x with
  | ofModel m =>
      apply congrArg Float32.ofModel
      change m = Float32.Model.pack .notANumber
      have hr := Model.toFloat32Model_ofFloat32Model m
      change Float32.Model.pack m.unpack = m at hr
      change m.unpack = .notANumber at hunpack
      rw [← hr, hunpack]

theorem native_add_nan_left (x y : Float32) (hx : x.isNaN = true) :
    x + y = Float32.nan := by
  apply native_eq_nan_of_isNaN
  cases h : (x + y).isNaN with
  | true => rfl
  | false =>
      have hn := Submission.NotNaNProbe.add_inputs x y h
      simp [hx] at hn

theorem native_add_nan_right (x y : Float32) (hy : y.isNaN = true) :
    x + y = Float32.nan := by
  apply native_eq_nan_of_isNaN
  cases h : (x + y).isNaN with
  | true => rfl
  | false =>
      have hn := Submission.NotNaNProbe.add_inputs x y h
      simp [hy] at hn

private theorem mul_unpack_of_isNaN (x : Float32) (hx : x.isNaN = true) :
    x.toModel.unpack = Float.Model.UnpackedFloat.notANumber := by
  change x.toModel.unpack.isNaN = true at hx
  cases h : x.toModel.unpack <;>
    simp_all [Float.Model.UnpackedFloat.isNaN]

theorem native_mul_nan_left (x y : Float32) (hx : x.isNaN = true) :
    x * y = Float32.nan := by
  change Float32.ofModel (Float32.Model.pack
    (Float.Model.UnpackedFloat.mul Float.Model.Format.binary32
      x.toModel.unpack y.toModel.unpack)) = Float32.nan
  rw [mul_unpack_of_isNaN x hx]
  rfl

theorem native_mul_nan_right (x y : Float32) (hy : y.isNaN = true) :
    x * y = Float32.nan := by
  change Float32.ofModel (Float32.Model.pack
    (Float.Model.UnpackedFloat.mul Float.Model.Format.binary32
      x.toModel.unpack y.toModel.unpack)) = Float32.nan
  rw [mul_unpack_of_isNaN y hy]
  cases x.toModel.unpack <;> rfl

end R7W05

namespace R7W12
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

/-- The actual native NaN imports to precisely the positive canonical quiet word. -/
theorem ofFloat32_nan_raw :
    (ExecFloat.Binary.ofFloat32 Float32.nan).raw.1 = (0x7fc00000 : UInt32) := rfl

theorem ofFloat32_nan_toModel :
    ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 Float32.nan) =
      Model.canonicalNaN FloatFormat.binary32 := rfl

/-- Actual classifier transport on every canonical native input. -/
theorem ofFloat32_isNaN (x : Float32) :
    Model.isNaN (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 x)) = x.isNaN := by
  have h := (R7W05.toFloat32_isNaN (ExecFloat.Binary.ofFloat32 x)).symm
  simpa only [ExecFloat.Binary.toFloat32_ofFloat32] using h

/-- No actual native Float32 conversion is signaling, including the native NaN. -/
theorem ofFloat32_not_snan (x : Float32) :
    Model.isSNaN (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 x)) = false := by
  cases hx : x.isNaN with
  | false =>
      exact Model.isSNaN_eq_false_of_isNaN_eq_false _ ((ofFloat32_isNaN x).trans hx)
  | true =>
      rw [R7W05.native_eq_nan_of_isNaN x hx, ofFloat32_nan_toModel]
      decide

theorem canonicalNaN_is_nan :
    Model.isNaN (Model.canonicalNaN FloatFormat.binary32) = true := by decide

theorem canonicalNaN_not_snan :
    Model.isSNaN (Model.canonicalNaN FloatFormat.binary32) = false := by decide

theorem canonicalNaN_quiet_self :
    Model.quietNaN (Model.canonicalNaN FloatFormat.binary32) =
      Model.canonicalNaN FloatFormat.binary32 := by decide

/-- Actual binary32 invalid operations use exactly the same canonical NaN. -/
theorem invalidResult_eq_canonical :
    Model.invalidResult FloatFormat.binary32 = Model.canonicalNaN FloatFormat.binary32 := rfl

/-- The real selector keeps the canonical left NaN when the right input is not signaling. -/
theorem chooseCanonicalNaN_left (q : Model FloatFormat.binary32)
    (hs : Model.isSNaN q = false) :
    Model.chooseNaN2 (Model.canonicalNaN FloatFormat.binary32) q =
      some (Model.canonicalNaN FloatFormat.binary32) := by
  simp [Model.chooseNaN2, canonicalNaN_is_nan, canonicalNaN_not_snan,
    canonicalNaN_quiet_self, hs]

/-- A non-NaN left operand allows the actual right canonical NaN to be selected. -/
theorem chooseCanonicalNaN_right (q : Model FloatFormat.binary32)
    (hn : Model.isNaN q = false) :
    Model.chooseNaN2 q (Model.canonicalNaN FloatFormat.binary32) =
      some (Model.canonicalNaN FloatFormat.binary32) := by
  have hs := Model.isSNaN_eq_false_of_isNaN_eq_false q hn
  simp [Model.chooseNaN2, canonicalNaN_is_nan, canonicalNaN_not_snan,
    canonicalNaN_quiet_self, hs, hn]

theorem model_add_canonical_left (q : Model FloatFormat.binary32)
    (hs : Model.isSNaN q = false) :
    Model.Spec.add (Model.canonicalNaN FloatFormat.binary32) q =
      Model.canonicalNaN FloatFormat.binary32 := by
  have hd := Model.toDyadic?_eq_none_of_isNaN canonicalNaN_is_nan
  simp [Model.Spec.add, hd, chooseCanonicalNaN_left q hs]

theorem model_add_canonical_right (q : Model FloatFormat.binary32)
    (hn : Model.isNaN q = false) :
    Model.Spec.add q (Model.canonicalNaN FloatFormat.binary32) =
      Model.canonicalNaN FloatFormat.binary32 := by
  have hd := Model.toDyadic?_eq_none_of_isNaN canonicalNaN_is_nan
  cases hq : Model.toDyadic? q <;>
    simp [Model.Spec.add, hd, hq, chooseCanonicalNaN_right q hn]

theorem model_mul_canonical_left (q : Model FloatFormat.binary32)
    (hs : Model.isSNaN q = false) :
    Model.Spec.mul (Model.canonicalNaN FloatFormat.binary32) q =
      Model.canonicalNaN FloatFormat.binary32 := by
  have hd := Model.toDyadic?_eq_none_of_isNaN canonicalNaN_is_nan
  simp [Model.Spec.mul, hd, chooseCanonicalNaN_left q hs]

theorem model_mul_canonical_right (q : Model FloatFormat.binary32)
    (hn : Model.isNaN q = false) :
    Model.Spec.mul q (Model.canonicalNaN FloatFormat.binary32) =
      Model.canonicalNaN FloatFormat.binary32 := by
  have hd := Model.toDyadic?_eq_none_of_isNaN canonicalNaN_is_nan
  cases hq : Model.toDyadic? q <;>
    simp [Model.Spec.mul, hd, hq, chooseCanonicalNaN_right q hn]

/-- Canonical left NaN propagation is a full-carrier equality on imported inputs. -/
theorem exec_add_import_nan_left (x : Float32) :
    ExecFloat.add (ExecFloat.Binary.ofFloat32 Float32.nan) (ExecFloat.Binary.ofFloat32 x) =
      ExecFloat.Binary.ofFloat32 Float32.nan := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel
    (ExecFloat.add (ExecFloat.Binary.ofFloat32 Float32.nan) (ExecFloat.Binary.ofFloat32 x)) =
      ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 Float32.nan)
  rw [Submission.R7Native.toModelExecAdd]
  change Model.Spec.add (Model.canonicalNaN FloatFormat.binary32)
    (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 x)) =
      Model.canonicalNaN FloatFormat.binary32
  exact model_add_canonical_left _ (ofFloat32_not_snan x)

theorem exec_add_import_nan_right (x : Float32) (hx : x.isNaN = false) :
    ExecFloat.add (ExecFloat.Binary.ofFloat32 x) (ExecFloat.Binary.ofFloat32 Float32.nan) =
      ExecFloat.Binary.ofFloat32 Float32.nan := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel
    (ExecFloat.add (ExecFloat.Binary.ofFloat32 x) (ExecFloat.Binary.ofFloat32 Float32.nan)) =
      ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 Float32.nan)
  rw [Submission.R7Native.toModelExecAdd]
  change Model.Spec.add (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 x))
    (Model.canonicalNaN FloatFormat.binary32) = Model.canonicalNaN FloatFormat.binary32
  exact model_add_canonical_right _ ((ofFloat32_isNaN x).trans hx)

theorem exec_mul_import_nan_left (x : Float32) :
    ExecFloat.mul (ExecFloat.Binary.ofFloat32 Float32.nan) (ExecFloat.Binary.ofFloat32 x) =
      ExecFloat.Binary.ofFloat32 Float32.nan := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel
    (ExecFloat.mul (ExecFloat.Binary.ofFloat32 Float32.nan) (ExecFloat.Binary.ofFloat32 x)) =
      ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 Float32.nan)
  rw [Submission.NativeBridge.toModelExecMul]
  change Model.Spec.mul (Model.canonicalNaN FloatFormat.binary32)
    (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 x)) =
      Model.canonicalNaN FloatFormat.binary32
  exact model_mul_canonical_left _ (ofFloat32_not_snan x)

theorem exec_mul_import_nan_right (x : Float32) (hx : x.isNaN = false) :
    ExecFloat.mul (ExecFloat.Binary.ofFloat32 x) (ExecFloat.Binary.ofFloat32 Float32.nan) =
      ExecFloat.Binary.ofFloat32 Float32.nan := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel
    (ExecFloat.mul (ExecFloat.Binary.ofFloat32 x) (ExecFloat.Binary.ofFloat32 Float32.nan)) =
      ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 Float32.nan)
  rw [Submission.NativeBridge.toModelExecMul]
  change Model.Spec.mul (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 x))
    (Model.canonicalNaN FloatFormat.binary32) = Model.canonicalNaN FloatFormat.binary32
  exact model_mul_canonical_right _ ((ofFloat32_isNaN x).trans hx)

/-- ALL native inputs: the actual native conversion is closed under ordinary addition. -/
theorem ofFloat32_add (a b : Float32) :
    ExecFloat.Binary.ofFloat32 (a + b) =
      ExecFloat.add (ExecFloat.Binary.ofFloat32 a) (ExecFloat.Binary.ofFloat32 b) := by
  cases ha : a.isNaN with
  | false =>
      cases hb : b.isNaN with
      | false => exact Submission.R7Native.ofFloat32Add a b ha hb
      | true =>
          rw [R7W05.native_add_nan_right a b hb, R7W05.native_eq_nan_of_isNaN b hb]
          exact (exec_add_import_nan_right a ha).symm
  | true =>
      rw [R7W05.native_add_nan_left a b ha, R7W05.native_eq_nan_of_isNaN a ha]
      exact (exec_add_import_nan_left b).symm

/-- ALL native inputs: multiplication is separate and preserves the canonical image. -/
theorem ofFloat32_mul (a b : Float32) :
    ExecFloat.Binary.ofFloat32 (a * b) =
      ExecFloat.mul (ExecFloat.Binary.ofFloat32 a) (ExecFloat.Binary.ofFloat32 b) := by
  cases ha : a.isNaN with
  | false =>
      cases hb : b.isNaN with
      | false => exact Submission.R7Native.ofFloat32Mul a b ha hb
      | true =>
          rw [R7W05.native_mul_nan_right a b hb, R7W05.native_eq_nan_of_isNaN b hb]
          exact (exec_mul_import_nan_right a ha).symm
  | true =>
      rw [R7W05.native_mul_nan_left a b ha, R7W05.native_eq_nan_of_isNaN a ha]
      exact (exec_mul_import_nan_left b).symm

/-- Requested execution-to-conversion orientation, with no non-NaN premise. -/
theorem add_ofFloat32 (a b : Float32) :
    ExecFloat.add (ExecFloat.Binary.ofFloat32 a) (ExecFloat.Binary.ofFloat32 b) =
      ExecFloat.Binary.ofFloat32 (a + b) := (ofFloat32_add a b).symm

theorem mul_ofFloat32 (a b : Float32) :
    ExecFloat.mul (ExecFloat.Binary.ofFloat32 a) (ExecFloat.Binary.ofFloat32 b) =
      ExecFloat.Binary.ofFloat32 (a * b) := (ofFloat32_mul a b).symm

end R7W12
