/-
R12 scratch proof text ONLY, NOT_RUN. Intended after exactdf5c full source.
This is not Kernel.lean and has no compile or gate receipt.
Uses already accepted full-input native bridges and classifier transport;
no new axiom, resource option, numerical enumeration or finite-domain premise.
An early runtime integration must move the two closed R7W05 classifier theorems
before these helpers, or copy their exact accepted proof under fresh local names.
-/
namespace Submission.NoneNativeProof

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

theorem raw_none_model (x y : Binary32)
    (hnone : DWordNaN.rawChoose x.raw.1 y.raw.1 = none) :
    Model.chooseNaN2 (Model.NativeBinary32.ofUInt32 x.raw.1)
      (Model.NativeBinary32.ofUInt32 y.raw.1) = none := by
  rw [← DWordNaN.rawChoose_eq, hnone]
  rfl

theorem raw_none_native_inputs (x y : Binary32)
    (hnone : DWordNaN.rawChoose x.raw.1 y.raw.1 = none) :
    (ExecFloat.Binary.toFloat32 x).isNaN = false ∧
      (ExecFloat.Binary.toFloat32 y).isNaN = false := by
  have hm := (Model.chooseNaN2_eq_none_iff
    (Model.NativeBinary32.ofUInt32 x.raw.1)
    (Model.NativeBinary32.ofUInt32 y.raw.1)).mp (raw_none_model x y hnone)
  constructor
  · rw [R7W05.toFloat32_isNaN, R7W02.exec_toModel_eq_rawModel]
    exact hm.1
  · rw [R7W05.toFloat32_isNaN, R7W02.exec_toModel_eq_rawModel]
    exact hm.2

theorem native_add_spec_of_none (x y : Binary32)
    (hnone : DWordNaN.rawChoose x.raw.1 y.raw.1 = none) :
    ExecFloat.Binary.ofFloat32
      (ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y) =
        ExecFloat.Spec.add x y := by
  have hn := raw_none_native_inputs x y hnone
  rw [R7Native.ofFloat32Add _ _ hn.1 hn.2,
    NotNaNProbe.roundtrip x hn.1, NotNaNProbe.roundtrip y hn.2]
  exact ExecFloat.Proof.add_eq_spec x y

theorem native_mul_spec_of_none (x y : Binary32)
    (hnone : DWordNaN.rawChoose x.raw.1 y.raw.1 = none) :
    ExecFloat.Binary.ofFloat32
      (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y) =
        ExecFloat.Spec.mul x y := by
  have hn := raw_none_native_inputs x y hnone
  rw [R7Native.ofFloat32Mul _ _ hn.1 hn.2,
    NotNaNProbe.roundtrip x hn.1, NotNaNProbe.roundtrip y hn.2]
  exact ExecFloat.Proof.mul_eq_spec x y

@[inline] def addColdResult (x y : Binary32) (result : Float32) : Binary32 :=
  match DWordNaN.rawChoose x.raw.1 y.raw.1 with
  | some w => FastMul.ofBits w
  | none => ExecFloat.Binary.ofFloat32 result

theorem addColdResult_spec (x y : Binary32) (result : Float32)
    (hr : result = R2W01b.convert x.raw.1 + R2W01b.convert y.raw.1) :
    addColdResult x y result = ExecFloat.Spec.add x y := by
  unfold addColdResult
  split
  · rename_i w hw
    exact DWordNaN.selected_add x y w hw
  · rename_i hw
    rw [hr, R2W01c.convert_eq, R2W01c.convert_eq]
    change ExecFloat.Binary.ofFloat32
      (ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y) = _
    exact native_add_spec_of_none x y hw

@[inline] def mulColdResult (x y : Binary32) (result : Float32) : Binary32 :=
  match DWordNaN.rawChoose x.raw.1 y.raw.1 with
  | some w => FastMul.ofBits w
  | none => ExecFloat.Binary.ofFloat32 result

theorem mulColdResult_spec (x y : Binary32) (result : Float32)
    (hr : result = R2W01b.convert x.raw.1 * R2W01b.convert y.raw.1) :
    mulColdResult x y result = ExecFloat.Spec.mul x y := by
  unfold mulColdResult
  split
  · rename_i w hw
    exact DWordNaN.selected_mul x y w hw
  · rename_i hw
    rw [hr, R2W01c.convert_eq, R2W01c.convert_eq]
    change ExecFloat.Binary.ofFloat32
      (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y) = _
    exact native_mul_spec_of_none x y hw

end Submission.NoneNativeProof
