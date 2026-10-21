import ContractTensor

namespace Submission.NativeBridge

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

/-- Finiteness of the converted native value excludes the only lossy conversion case, NaN. -/
theorem finiteRoundtrip (x : Competition.Binary32)
    (hx : (ExecFloat.Binary.toFloat32 x).isFinite = true) :
    ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x) = x := by
  have hcanonical : Model.IsModelCanonical (ExecFloat.Binary.toModel x) := by
    constructor
    intro he hm
    have hnan : Model.toModel (ExecFloat.Binary.toModel x) =
        Float.Model.UnpackedFloat.notANumber := by
      simp only [Model.toModel, Model.unpack, he, hm, ite_true, ite_false]
    have hf := hx
    change ((Model.toFloat32Model (ExecFloat.Binary.toModel x)).unpack).isFinite = true at hf
    rw [Model.unpack_toFloat32Model, hnan] at hf
    cases hf
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel
      (ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x)) =
    ExecFloat.Binary.toModel x
  rw [ExecFloat.Binary.toModel_ofFloat32, ExecFloat.Binary.toModel_toFloat32_eq,
    Model.ofFloat32Model_toFloat32Model]
  exact Model.canonicalizeModel_eq_self _ hcanonical

end Submission.NativeBridge
