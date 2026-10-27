/- Draft / NOT_RUN. Reuse the retained kernel's actual UInt32-to-Float32 model
bridge for every UInt32, including magnitudes needing RNE. No runtime changes. -/
namespace Submission.R14UInt32Bits

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

theorem native_bits_of_model_eq (value : Float32) (word : UInt32)
    (hm : R2W01c.nativeModel value = R2W01c.rawModel word) :
    value.toBits = word := by
  have hw : ExecFloat.Binary.ofFloat32 value = ExecFloat.Binary.ofBits32 word := by
    apply ExecFloat.Binary.toModel_inj.mp
    exact hm
  have hn := congrArg ExecFloat.Binary.toBits32 hw
  simpa only [ExecFloat.Binary.toBits32_ofFloat32,
    ExecFloat.Binary.toBits32_ofBits32] using hn

theorem uint32_toFloat32_bits (n : UInt32) :
    n.toFloat32.toBits =
      Model.NativeBinary32.roundDyadic
        (⟨false, n.toNat, 0⟩ : FloatLib.Numerics.Dyadic) := by
  apply native_bits_of_model_eq
  rw [R2W01c.rawModel_eq_native32, Model.NativeBinary32.ofUInt32_roundDyadic]
  exact R2W01c.uint32_model_eq_roundDyadic n

end Submission.R14UInt32Bits
