import ContractTensor

namespace Submission.WordFinite

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

theorem modelFiniteOfExp (w : UInt32)
    (hw : Model.NativeBinary32.expField w ≠ 0xff) :
    (Model.toModel (Model.NativeBinary32.ofUInt32 w)).isFinite = true := by
  have hd : ∃ d, Model.toDyadic? (Model.NativeBinary32.ofUInt32 w) = some d := by
    rw [← Model.NativeBinary32.toDyadic_eq]
    simp only [Model.NativeBinary32.toUInt32_ofUInt32]
    unfold Model.NativeBinary32.toDyadic?
    simp only [beq_iff_eq, hw, ite_false]
    split_ifs <;> exact ⟨_, rfl⟩
  obtain ⟨d, hd⟩ := hd
  rw [Model.toDyadic?_ieee_eq_model FloatFormat.binary32 (by decide)] at hd
  cases hm : Model.toModel (Model.NativeBinary32.ofUInt32 w) <;>
    simp_all [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.isFinite]

theorem nativeFiniteOfExp (x : Competition.Binary32)
    (hx : Model.NativeBinary32.expField x.raw.1 ≠ 0xff) :
    (ExecFloat.Binary.toFloat32 x).isFinite = true := by
  change ((Model.toFloat32Model (Model.NativeBinary32.ofUInt32 x.raw.1)).unpack).isFinite = true
  rw [Model.unpack_toFloat32Model]
  exact modelFiniteOfExp x.raw.1 hx

end Submission.WordFinite
