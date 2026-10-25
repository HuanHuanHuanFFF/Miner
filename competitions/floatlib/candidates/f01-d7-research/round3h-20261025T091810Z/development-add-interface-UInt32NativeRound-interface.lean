/- R16 follow-on ADD feasibility, NOT_COMPILED / NOT_A_KERNEL.
   Append only to a checked B2 proof environment for a future owner-run probe.
   The arbitrary UInt32 model bridge is already in full-gated B2. This fragment
   transports that exact statement to actual native toBits and field projections.
   It does not assume N is exactly representable in binary32.
   No public ADD implementation, guard proof, or performance claim is supplied. -/
namespace Submission.R16AddUInt32Interface

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

theorem uint32_bits_eq_roundDyadic (n : UInt32) :
    n.toFloat32.toBits = Model.NativeBinary32.roundDyadic
      (⟨false, n.toNat, 0⟩ : Dyadic) := by
  have hw : ExecFloat.Binary.ofFloat32 n.toFloat32 =
      ExecFloat.Binary.ofBits32
        (Model.NativeBinary32.roundDyadic (⟨false, n.toNat, 0⟩ : Dyadic)) := by
    apply ExecFloat.Binary.toModel_inj.mp
    change R2W01c.nativeModel n.toFloat32 = R2W01c.rawModel
      (Model.NativeBinary32.roundDyadic (⟨false, n.toNat, 0⟩ : Dyadic))
    rw [R2W01c.rawModel_eq_native32, Model.NativeBinary32.ofUInt32_roundDyadic]
    exact R2W01c.uint32_model_eq_roundDyadic n
  have hbits := congrArg ExecFloat.Binary.toBits32 hw
  simpa only [ExecFloat.Binary.toBits32_ofFloat32,
    ExecFloat.Binary.toBits32_ofBits32] using hbits

/-- The shape premise remains a real obligation. A future complete ADD proof must
prove it for both h>=23 RNE and h<23 exact left-normalization, including carry. -/
theorem uint32_native_fields_of_shape (n : UInt32) (em f : Nat)
    (he : em < 256) (hf : f < 8388608)
    (hshape : Model.NativeBinary32.roundDyadic
      (⟨false, n.toNat, 0⟩ : Dyadic) = Model.NativeBinary32.mkBits false em f) :
    (Model.NativeBinary32.expField n.toFloat32.toBits).toNat = em ∧
    (Model.NativeBinary32.fracField n.toFloat32.toBits).toNat = f := by
  rw [uint32_bits_eq_roundDyadic, hshape]
  constructor
  · rw [← Model.NativeBinary32.toUInt32_ofFields, Model.NativeBinary32.expField_toNat]
    exact Model.expField_ofFields_of_lt FloatFormat.binary32 false em f he
  · rw [← Model.NativeBinary32.toUInt32_ofFields, Model.NativeBinary32.fracField_toNat]
    exact Model.fracField_ofFields_of_lt FloatFormat.binary32 false em f hf

/-- Pure arithmetic check of the postguard argument. The carry-leading premise
must be proved from the real integer converter's rounding; it is not an axiom. -/
theorem postguard_pre_normal (h c a : Nat) (hc : c ≤ 1) (ha : 1 ≤ a)
    (hcarry : c = 1 → 24 ≤ h) (hE : 1 ≤ h + c + a - 23) :
    -126 ≤ (h : Int) + ((a : Int) - 150) := by
  by_cases hz : c = 0
  · rw [hz] at hE
    omega
  · have ho : c = 1 := by omega
    have hh := hcarry ho
    omega

theorem raw_round_positive_zero (e : Int) :
    Model.NativeBinary32.roundDyadic (⟨false, 0, e⟩ : Dyadic) = 0 := by
  rfl

end Submission.R16AddUInt32Interface
