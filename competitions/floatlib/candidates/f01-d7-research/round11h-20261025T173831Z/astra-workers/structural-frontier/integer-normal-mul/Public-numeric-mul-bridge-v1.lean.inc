namespace Submission.R18NumericMulSpec

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

theorem sign_word_eq (u v : UInt32) :
    ((u ^^^ v) &&& (0x80000000 : UInt32)) =
      (if Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v) then
        (0x80000000 : UInt32) else 0) := by
  apply UInt32.toBitVec_inj.mp
  rw [UInt32.toBitVec_and,UInt32.toBitVec_xor]
  change (u.toBitVec ^^^ v.toBitVec) &&& BitVec.twoPow 32 31 =
    (if Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v) then
      (0x80000000 : UInt32) else 0).toBitVec
  rw [BitVec.and_twoPow]
  have hm : (u.toBitVec ^^^ v.toBitVec).getLsbD 31 =
      Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v) := by
    calc
      _ = (u.toBitVec ^^^ v.toBitVec).msb := by
        simpa using (BitVec.msb_eq_getLsbD_last (u.toBitVec ^^^ v.toBitVec)).symm
      _ = _ := by
        rw [BitVec.msb_xor,BitVec.msb_eq_decide,BitVec.msb_eq_decide]
        rfl
  rw [hm]
  cases hs : Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v) <;> rfl

def core (u v : UInt32) : UInt32 :=
  R17NumericMulInteger.normalCore (R14ExponentShift.ex u + R14ExponentShift.ex v) u v

theorem core_word (u v : UInt32)
    (hs : 128 ≤ R2W01c.wordExp u + R2W01c.wordExp v)
    (hs' : R2W01c.wordExp u + R2W01c.wordExp v ≤ 380) :
    core u v = Model.NativeBinary32.mkBits
      (Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v))
      (R14ExponentShift.middleExponent
          (R14ExponentShift.product (R2W01b.mantissa u) (R2W01b.mantissa v))+
        R2W01c.wordExp u+R2W01c.wordExp v-300)
      (R14ExponentShift.storedFraction
        (R14ExponentShift.product (R2W01b.mantissa u) (R2W01b.mantissa v))) := by
  have h := R17UInt64Fields.normalCore_eq_fields
    (R14ExponentShift.ex u+R14ExponentShift.ex v) u v
    (Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v))
    (by rw [R14ExponentShift.sum_nat]; exact hs)
    (by rw [R14ExponentShift.sum_nat]; exact hs') (sign_word_eq u v)
  rw [R14ExponentShift.sum_nat] at h
  simpa only [core,Nat.add_assoc] using h

theorem core_model (u v : UInt32)
    (hu0 : 0 < R2W01c.wordExp u) (hu : R2W01c.wordExp u < 255)
    (hv0 : 0 < R2W01c.wordExp v) (hv : R2W01c.wordExp v < 255)
    (hs : 128 ≤ R2W01c.wordExp u + R2W01c.wordExp v)
    (hs' : R2W01c.wordExp u + R2W01c.wordExp v ≤ 380) :
    Model.NativeBinary32.ofUInt32 (core u v) =
      Model.mul (R2W01c.rawModel u) (R2W01c.rawModel v) := by
  have hx := R14NatNormal.raw_normal_decode u hu0 hu
  have hy := R14NatNormal.raw_normal_decode v hv0 hv
  have ha := R2W01c.mantissa_bounds u
  have hb := R2W01c.mantissa_bounds v
  have hm := R14ExponentShift.model_mul_normal_fields (R2W01c.rawModel u) (R2W01c.rawModel v)
    (R2W01c.wordSign u) (R2W01c.wordSign v)
    (R2W01b.mantissa u).toNat (R2W01b.mantissa v).toNat
    (R2W01c.wordExp u) (R2W01c.wordExp v)
    ha.1 ha.2 hb.1 hb.2 hs hs' hx hy
  rw [core_word u v hs hs',Model.NativeBinary32.ofUInt32_mkBits]
  exact hm.symm

theorem core_spec (x y : Binary32)
    (hx0 : 0 < R2W01c.wordExp x.raw.1) (hx : R2W01c.wordExp x.raw.1 < 255)
    (hy0 : 0 < R2W01c.wordExp y.raw.1) (hy : R2W01c.wordExp y.raw.1 < 255)
    (hs : 128 ≤ R2W01c.wordExp x.raw.1 + R2W01c.wordExp y.raw.1)
    (hs' : R2W01c.wordExp x.raw.1 + R2W01c.wordExp y.raw.1 ≤ 380) :
    R7W02.fromRaw (core x.raw.1 y.raw.1) = ExecFloat.Spec.mul x y := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel (R7W02.fromRaw (core x.raw.1 y.raw.1)) =
    ExecFloat.Binary.toModel (ExecFloat.Spec.mul x y)
  rw [R7W02.fromRaw_toModel,← ExecFloat.Proof.mul_eq_spec,R7W01.exec_toModel_mul,
    ← Model.Proof.mul_eq_spec,R7W02.exec_toModel_eq_rawModel x,
    R7W02.exec_toModel_eq_rawModel y,← R2W01c.rawModel_eq_native32 x.raw.1,
    ← R2W01c.rawModel_eq_native32 y.raw.1]
  exact core_model x.raw.1 y.raw.1 hx0 hx hy0 hy hs hs'

theorem guardedMul_spec (fallback : Binary32 → Binary32 → Binary32)
    (hf : ∀ x y, fallback x y = ExecFloat.Spec.mul x y) (x y : Binary32) :
    R17NumericMulInteger.guardedMul fallback x y = ExecFloat.Spec.mul x y := by
  unfold R17NumericMulInteger.guardedMul
  dsimp only
  split
  · rename_i hnormal
    split
    · rename_i hsum
      have he : R14ExponentShift.eligible x.raw.1 y.raw.1 = true := by
        simp only [R14ExponentShift.eligible,Bool.and_eq_true,decide_eq_true_eq]
        exact ⟨hnormal,hsum⟩
      rcases R14ExponentShift.eligible_conditions x.raw.1 y.raw.1 he with
        ⟨hx0,hx,hy0,hy,hs,hs'⟩
      change R7W02.fromRaw (core x.raw.1 y.raw.1) = _
      exact core_spec x y hx0 hx hy0 hy hs hs'
    · exact hf x y
  · exact hf x y

theorem preserved_fallback_entry_spec (x y : Binary32) :
    R17NumericMulInteger.guardedMul Submission.mul x y = ExecFloat.Spec.mul x y :=
  guardedMul_spec Submission.mul Submission.mul_spec x y

end Submission.R18NumericMulSpec
