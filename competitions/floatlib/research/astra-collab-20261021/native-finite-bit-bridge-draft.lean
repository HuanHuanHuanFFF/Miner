import ContractTensor

namespace Submission.NativeBridge

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

/-- The existing word exponent check proves finiteness of the converted native value. -/
theorem nativeFiniteOfExp (x : Competition.Binary32)
    (hx : Model.NativeBinary32.expField x.raw.1 ≠ 0xff) :
    (ExecFloat.Binary.toFloat32 x).isFinite = true := by
  change ((Model.toFloat32Model (ExecFloat.Binary.toModel x)).unpack).isFinite = true
  rw [Model.unpack_toFloat32Model]
  have hd : ∃ d, Model.toDyadic? (ExecFloat.Binary.toModel x) = some d := by
    change ∃ d, Model.toDyadic? (Model.NativeBinary32.ofUInt32 x.raw.1) = some d
    rw [← Model.NativeBinary32.toDyadic_eq]
    simp only [Model.NativeBinary32.toUInt32_ofUInt32]
    unfold Model.NativeBinary32.toDyadic?
    simp only [beq_iff_eq, hx, ite_false]
    split_ifs <;> exact ⟨_, rfl⟩
  obtain ⟨d, hd⟩ := hd
  rw [Model.toDyadic?_ieee_eq_model FloatFormat.binary32 (by decide)] at hd
  cases hm : Model.toModel (ExecFloat.Binary.toModel x) <;>
    simp_all [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.isFinite]

end Submission.NativeBridge
