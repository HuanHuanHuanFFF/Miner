/- R14 developer closure attempt, NOT_COMPILED.
   Requires the original-order R14WordAdd.raw_add_model lemma supplied separately.
   The finite fast arm is guarded by the complete, unmasked result exponent. -/
namespace Submission.R14WordAdd

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

theorem core_model (u v : UInt32) (hd : eligible u v = true)
    (he : exponentWord u v - 1 ≤ (253 : UInt32)) :
    Model.NativeBinary32.ofUInt32 (core u v) =
      Model.add (R2W01c.rawModel u) (R2W01c.rawModel v) := by
  have hn := (R14WordAddAlignment.word_exponent_accept_iff (exponentWord u v)
    (exponent_nat_lower u v hd)).mp he
  rw [exponentWord_nat u v hd] at hn
  rw [core_word u v hd, Model.NativeBinary32.ofUInt32_mkBits]
  exact (raw_add_model u v hd hn).symm

theorem core_spec (x y : Binary32) (hd : eligible x.raw.1 y.raw.1 = true)
    (he : exponentWord x.raw.1 y.raw.1 - 1 ≤ (253 : UInt32)) :
    R7W02.fromRaw (core x.raw.1 y.raw.1) = ExecFloat.Spec.add x y := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel (R7W02.fromRaw (core x.raw.1 y.raw.1)) =
    ExecFloat.Binary.toModel (ExecFloat.Spec.add x y)
  rw [R7W02.fromRaw_toModel, ← ExecFloat.Proof.add_eq_spec x y,
    R7Native.toModelExecAdd, ← Model.Proof.add_eq_spec,
    R7W02.exec_toModel_eq_rawModel, R7W02.exec_toModel_eq_rawModel]
  simpa only [R2W01c.rawModel_eq_native32] using core_model x.raw.1 y.raw.1 hd he

theorem guardedAdd_spec (fallback : Binary32 → Binary32 → Binary32)
    (hf : ∀ x y, fallback x y = ExecFloat.Spec.add x y) (x y : Binary32) :
    guardedAdd fallback x y = ExecFloat.Spec.add x y := by
  by_cases hd : eligible x.raw.1 y.raw.1 = true
  · by_cases he : exponentWord x.raw.1 y.raw.1 - 1 ≤ (253 : UInt32)
    · rw [guardedAdd_of_normal fallback x y hd he]
      exact core_spec x y hd he
    · unfold guardedAdd
      simp only [hd, ↓reduceIte]
      change (if exponentWord x.raw.1 y.raw.1 - 1 ≤ (253 : UInt32) then
        R7W02.fromRaw (core x.raw.1 y.raw.1) else fallback x y) = _
      rw [if_neg he]
      exact hf x y
  · have hfalse : eligible x.raw.1 y.raw.1 = false := by
      cases h : eligible x.raw.1 y.raw.1 <;> simp_all
    rw [guardedAdd_of_ineligible fallback x y hfalse]
    exact hf x y

end Submission.R14WordAdd
