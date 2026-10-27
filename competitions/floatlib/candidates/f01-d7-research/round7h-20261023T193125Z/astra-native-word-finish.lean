/- DRAFT only, not compiled and not integrated. Append to exact R11 parent for a
   later diagnostic only after the base path is accepted. Uses fixed Lean Model.Valid
   (Lean FRO, Apache2, Julia M. Himmel), not a statement about arbitrary raw NaN words. -/
namespace Submission.R11WordFinish
open FloatLib.Floats Competition
open Float.Model.UnpackedFloat

theorem unpack_nan_iff (b : BitVec 32) :
    (unpack Float.Model.Format.binary32 b).isNaN = true ↔
      unpackExponent (spec := Float.Model.Format.binary32) b = (-1#8) ∧
      unpackMantissa (spec := Float.Model.Format.binary32) b ≠ (0#23) := by
  unfold unpack
  dsimp only
  split
  · rename_i he
    split <;> simp_all [Float.Model.UnpackedFloat.isNaN]
  · rename_i he
    split
    · split <;> simp_all [Float.Model.UnpackedFloat.isNaN]
    · simp_all [Float.Model.UnpackedFloat.isNaN]

theorem native_nan_iff_word (x : Float32) :
    x.isNaN = true ↔ x.toBits = (0x7fc00000 : UInt32) := by
  change (unpack Float.Model.Format.binary32 x.toModel.toBits.toBitVec).isNaN = true ↔
    x.toModel.toBits = (0x7fc00000 : UInt32)
  constructor
  · intro h
    have hc := (unpack_nan_iff _).mp h
    have hb := x.toModel.valid.eq_packedNaN hc.1 hc.2
    have hn : packedNaN Float.Model.Format.binary32 = (0x7fc00000 : UInt32).toBitVec := by decide
    exact UInt32.toBitVec_inj.mp (hb.trans hn)
  · intro h
    rw [h] <;> decide

@[inline] def finishWord (n baseA baseB p : Nat) (A B : Array Binary32)
    (x : Float32) : UInt32 :=
  let w := x.toBits
  if w = 0x7fc00000 then (R7NaNReplay.replayEarly n baseA baseB p A B).raw.1
  else w

theorem finishWord_eq (n baseA baseB p : Nat) (A B : Array Binary32)
    (x : Float32) :
    finishWord n baseA baseB p A B x = (Packed10.finish n baseA baseB p A B x).raw.1 := by
  cases hn : x.isNaN
  · have hw : x.toBits ≠ (0x7fc00000 : UInt32) := by
      intro h
      have hc := (native_nan_iff_word x).mpr h
      simp [hn] at hc
    unfold finishWord Packed10.finish
    dsimp only
    rw [if_neg hw, dif_pos hn] <;> rfl
  · have hw := (native_nan_iff_word x).mp hn
    have hf : ¬x.isNaN = false := by simp [hn]
    unfold finishWord Packed10.finish
    dsimp only
    rw [if_pos hw, dif_neg hf]

end Submission.R11WordFinish
