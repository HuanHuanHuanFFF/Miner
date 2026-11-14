/- Proof-only normalization for an A-only decoder substitution. NOT_RUN.
   No F8 runtime, shape guard, packet layout or public candidate is defined here. -/
namespace Submission.R22ADecoderNormalization
open FloatLib.Floats Competition

theorem carrier_decode (a : Binary32) :
    R2W01b.convert a.raw.1 = ExecFloat.Binary.toFloat32 a := by
  rw [R2W01c.convert_eq]
  rfl

theorem array_getD_decode (A : Array Binary32) (i : Nat) :
    R2W01b.convert (A.getD i posZero).raw.1 =
      ExecFloat.Binary.toFloat32 (A.getD i posZero) :=
  carrier_decode (A.getD i posZero)

theorem replace_four_A {α : Sort _}
    (body : Float32 → Float32 → Float32 → Float32 → α)
    (a0 a1 a2 a3 : Binary32) :
    body (R2W01b.convert a0.raw.1) (R2W01b.convert a1.raw.1)
      (R2W01b.convert a2.raw.1) (R2W01b.convert a3.raw.1) =
    body (ExecFloat.Binary.toFloat32 a0) (ExecFloat.Binary.toFloat32 a1)
      (ExecFloat.Binary.toFloat32 a2) (ExecFloat.Binary.toFloat32 a3) := by
  rw [carrier_decode,carrier_decode,carrier_decode,carrier_decode]

theorem normalize_A4B2_step {S : Type}
    (update : Float32 → Float32 → Float32 → Float32 → Float32 → Float32 → S → S)
    (a0 a1 a2 a3 : Binary32) (b0 b1 : Float32) (s : S) :
    update (R2W01b.convert a0.raw.1) (R2W01b.convert a1.raw.1)
      (R2W01b.convert a2.raw.1) (R2W01b.convert a3.raw.1) b0 b1 s =
    update (ExecFloat.Binary.toFloat32 a0) (ExecFloat.Binary.toFloat32 a1)
      (ExecFloat.Binary.toFloat32 a2) (ExecFloat.Binary.toFloat32 a3) b0 b1 s := by
  exact replace_four_A (fun x0 x1 x2 x3 => update x0 x1 x2 x3 b0 b1 s) a0 a1 a2 a3

end Submission.R22ADecoderNormalization
