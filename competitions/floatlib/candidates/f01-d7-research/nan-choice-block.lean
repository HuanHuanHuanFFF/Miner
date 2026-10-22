/- Word NaN selection: fixed public binary32 fields and exact quieting/priority.
   Newly integrated statement probe; NOT_RUN in the official compiler. -/
namespace DWordNaN

open FloatLib.Floats.Formats.BinaryInterchange
abbrev M := Model FloatFormat.binary32

@[inline] def rawNaN (u : UInt32) : Bool :=
  Model.NativeBinary32.expField u == 0xff && Model.NativeBinary32.fracField u != 0

@[inline] def rawSNaN (u : UInt32) : Bool :=
  rawNaN u && (u &&& 0x00400000) == 0

theorem rawNaN_eq (u : UInt32) :
    rawNaN u = Model.isNaN (Model.NativeBinary32.ofUInt32 u) := by
  apply Bool.eq_iff_iff.mpr
  change ((Model.NativeBinary32.expField u == 0xff && Model.NativeBinary32.fracField u != 0) = true) ↔
    ((Model.expField (Model.NativeBinary32.ofUInt32 u) == 255 &&
      Model.fracField (Model.NativeBinary32.ofUInt32 u) != 0) = true)
  simp only [Bool.and_eq_true, beq_iff_eq, bne_iff_ne]
  have he : Model.NativeBinary32.expField u = 0xff ↔
      Model.expField (Model.NativeBinary32.ofUInt32 u) = 255 := by
    change Model.NativeBinary32.expField u = 0xff ↔
      (Model.NativeBinary32.expField u).toNat = 255
    exact UInt32.toNat_inj.symm
  have hf : Model.NativeBinary32.fracField u = 0 ↔
      Model.fracField (Model.NativeBinary32.ofUInt32 u) = 0 := by
    change Model.NativeBinary32.fracField u = 0 ↔
      (Model.NativeBinary32.fracField u).toNat = 0
    exact UInt32.toNat_inj.symm
  exact and_congr he (not_congr hf)

theorem rawSNaN_eq (u : UInt32) :
    rawSNaN u = Model.isSNaN (Model.NativeBinary32.ofUInt32 u) := by
  unfold rawSNaN
  rw [rawNaN_eq]
  change (Model.isNaN (Model.NativeBinary32.ofUInt32 u) && ((u &&& 0x00400000) == 0)) =
    (Model.isNaN (Model.NativeBinary32.ofUInt32 u) &&
      ((u.toBitVec &&& (4194304#32)) == 0))
  apply congrArg (fun b : Bool => Model.isNaN (Model.NativeBinary32.ofUInt32 u) && b)
  apply Bool.eq_iff_iff.mpr
  simp only [beq_iff_eq]
  rw [← UInt32.toBitVec_inj, UInt32.toBitVec_and]
  rfl

theorem quietWord_eq (u : UInt32) (hu : rawNaN u = true) :
    Model.NativeBinary32.ofUInt32 (u ||| 0x00400000) =
      Model.quietNaN (Model.NativeBinary32.ofUInt32 u) := by
  have hm : Model.isNaN (Model.NativeBinary32.ofUInt32 u) = true := by
    rw [← rawNaN_eq]
    exact hu
  have h := Model.NativeBinary32.ofUInt32_or_quietBit
    (Model.NativeBinary32.ofUInt32 u)
  simp only [Model.NativeBinary32.toUInt32_ofUInt32] at h
  rw [h]
  change _ = if Model.isNaN (Model.NativeBinary32.ofUInt32 u) then
    Model.ofBits ((Model.NativeBinary32.ofUInt32 u).bits |||
      FloatFormat.quietBit FloatFormat.binary32)
    else Model.NativeBinary32.ofUInt32 u
  rw [hm]

theorem quietWord_eq_snan (u : UInt32) (hu : rawSNaN u = true) :
    Model.NativeBinary32.ofUInt32 (u ||| 0x00400000) =
      Model.quietNaN (Model.NativeBinary32.ofUInt32 u) := by
  apply quietWord_eq
  change (rawNaN u && ((u &&& 0x00400000) == 0)) = true at hu
  exact (Bool.and_eq_true.mp hu).1

@[inline] def rawChoose (a b : UInt32) : Option UInt32 :=
  if rawSNaN a then some (a ||| 0x00400000)
  else if rawSNaN b then some (b ||| 0x00400000)
  else if rawNaN a then some (a ||| 0x00400000)
  else if rawNaN b then some (b ||| 0x00400000)
  else none

theorem rawChoose_eq (a b : UInt32) :
    (rawChoose a b).map Model.NativeBinary32.ofUInt32 =
      Model.chooseNaN2 (Model.NativeBinary32.ofUInt32 a)
        (Model.NativeBinary32.ofUInt32 b) := by
  unfold rawChoose Model.chooseNaN2
  rw [← rawSNaN_eq a, ← rawSNaN_eq b, ← rawNaN_eq a, ← rawNaN_eq b]
  by_cases ha : rawSNaN a = true
  · simp only [ha, ite_true, Option.map_some]
    exact congrArg some (quietWord_eq_snan a ha)
  · by_cases hb : rawSNaN b = true
    · simp only [ha, hb, ite_false, ite_true, Option.map_some]
      exact congrArg some (quietWord_eq_snan b hb)
    · by_cases hna : rawNaN a = true
      · simp only [ha, hb, hna, ite_false, ite_true, Option.map_some]
        exact congrArg some (quietWord_eq a hna)
      · by_cases hnb : rawNaN b = true
        · simp only [ha, hb, hna, hnb, ite_false, ite_true, Option.map_some]
          exact congrArg some (quietWord_eq b hnb)
        · simp only [ha, hb, hna, hnb, ite_false, Option.map_none]

theorem rawNaN_exp (u : UInt32) (hu : rawNaN u = true) :
    Model.NativeBinary32.expField u = 0xff := by
  have h := (Bool.and_eq_true.mp hu).1
  exact beq_iff_eq.mp h

theorem rawChoose_nonfinite (a b w : UInt32) (hw : rawChoose a b = some w) :
    Model.NativeBinary32.expField a = 0xff ∨ Model.NativeBinary32.expField b = 0xff := by
  unfold rawChoose at hw
  split at hw
  · rename_i ha
    exact Or.inl (rawNaN_exp a (Bool.and_eq_true.mp ha).1)
  · split at hw
    · rename_i hb
      exact Or.inr (rawNaN_exp b (Bool.and_eq_true.mp hb).1)
    · split at hw
      · rename_i ha
        exact Or.inl (rawNaN_exp a ha)
      · split at hw
        · rename_i hb
          exact Or.inr (rawNaN_exp b hb)
        · cases hw

theorem specialDecode (u : UInt32) (hu : Model.NativeBinary32.expField u = 0xff) :
    Model.toDyadic? (Model.NativeBinary32.ofUInt32 u) = none := by
  rw [← Model.NativeBinary32.toDyadic_eq]
  simp only [Model.NativeBinary32.toUInt32_ofUInt32]
  unfold Model.NativeBinary32.toDyadic?
  simp [hu]

theorem selected_model_add (a b w : UInt32) (hw : rawChoose a b = some w) :
    Model.NativeBinary32.ofUInt32 w = Model.Spec.add
      (Model.NativeBinary32.ofUInt32 a) (Model.NativeBinary32.ofUInt32 b) := by
  have hc : Model.chooseNaN2 (Model.NativeBinary32.ofUInt32 a)
      (Model.NativeBinary32.ofUInt32 b) = some (Model.NativeBinary32.ofUInt32 w) := by
    rw [← rawChoose_eq, hw]
    rfl
  rcases rawChoose_nonfinite a b w hw with ha | hb
  · unfold Model.Spec.add
    rw [specialDecode a ha]
    cases Model.toDyadic? (Model.NativeBinary32.ofUInt32 b) <;> simp only [hc]
  · unfold Model.Spec.add
    rw [specialDecode b hb]
    cases Model.toDyadic? (Model.NativeBinary32.ofUInt32 a) <;> simp only [hc]

theorem selected_model_mul (a b w : UInt32) (hw : rawChoose a b = some w) :
    Model.NativeBinary32.ofUInt32 w = Model.Spec.mul
      (Model.NativeBinary32.ofUInt32 a) (Model.NativeBinary32.ofUInt32 b) := by
  have hc : Model.chooseNaN2 (Model.NativeBinary32.ofUInt32 a)
      (Model.NativeBinary32.ofUInt32 b) = some (Model.NativeBinary32.ofUInt32 w) := by
    rw [← rawChoose_eq, hw]
    rfl
  rcases rawChoose_nonfinite a b w hw with ha | hb
  · unfold Model.Spec.mul
    rw [specialDecode a ha]
    cases Model.toDyadic? (Model.NativeBinary32.ofUInt32 b) <;> simp only [hc]
  · unfold Model.Spec.mul
    rw [specialDecode b hb]
    cases Model.toDyadic? (Model.NativeBinary32.ofUInt32 a) <;> simp only [hc]

open FloatLib.Floats Competition

theorem selected_add (x y : Binary32) (w : UInt32)
    (hw : rawChoose x.raw.1 y.raw.1 = some w) :
    Submission.FastMul.ofBits w = ExecFloat.Spec.add x y := by
  rw [← ExecFloat.Proof.add_eq_spec]
  apply Configured.Family.toModel_injective
  change Model.NativeBinary32.ofUInt32 w = ExecFloat.Binary.toModel (ExecFloat.add x y)
  rw [Submission.R7Native.toModelExecAdd]
  exact selected_model_add x.raw.1 y.raw.1 w hw

theorem selected_mul (x y : Binary32) (w : UInt32)
    (hw : rawChoose x.raw.1 y.raw.1 = some w) :
    Submission.FastMul.ofBits w = ExecFloat.Spec.mul x y := by
  rw [← ExecFloat.Proof.mul_eq_spec]
  apply Configured.Family.toModel_injective
  change Model.NativeBinary32.ofUInt32 w = ExecFloat.Binary.toModel (ExecFloat.mul x y)
  rw [Submission.NativeBridge.toModelExecMul]
  exact selected_model_mul x.raw.1 y.raw.1 w hw

end DWordNaN
