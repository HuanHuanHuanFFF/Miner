/-
R7 product-seed proof probe. All new declarations are NOT_RUN.
Append to the frozen 97f77e2c direct/nonfinite base.
Sources: supplied W10 NativeZero/General, W10b Core and W05 classifier proofs.
Fixed FloatLib definitions are MIT; Lean definitions are Apache-2.0.
The retained source notices remain intact. New local proof glue is NOT_RUN.
The only new runtime definition selects a UInt32 before wrapping its carrier.
-/
namespace D7SeedNormalize

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
open Float.Model.UnpackedFloat

/-- Select the original word first; no native conversion or NaN canonicalization. -/
@[inline] def normalizeProductSeedRaw (q : Competition.Binary32) : Competition.Binary32 :=
  let u : UInt32 := if q.raw.1 == (0x80000000 : UInt32) then (0 : UInt32) else q.raw.1
  ExecFloat.ofRaw ⟨u, u.toNat_lt⟩

theorem normalizeProductSeedRaw_raw (q : Competition.Binary32) :
    (normalizeProductSeedRaw q).raw.1 =
      if q.raw.1 == (0x80000000 : UInt32) then (0 : UInt32) else q.raw.1 := rfl

/-- This full-carrier conditional appears only in the proof layer. -/
theorem normalizeProductSeedRaw_eq_conditional (q : Competition.Binary32) :
    normalizeProductSeedRaw q =
      if q.raw.1 == (0x80000000 : UInt32) then Competition.posZero else q := by
  apply ExecFloat.ext
  apply Subtype.ext
  have h :
      ((if q.raw.1 == (0x80000000 : UInt32)
        then Competition.posZero else q) : Competition.Binary32).raw.1 =
      if q.raw.1 == (0x80000000 : UInt32) then (0 : UInt32) else q.raw.1 := by
    split <;> rfl
  exact (normalizeProductSeedRaw_raw q).trans h.symm

theorem normalizeProductSeedRaw_eq_self (q : Competition.Binary32)
    (hq : q.raw.1 ≠ (0x80000000 : UInt32)) :
    normalizeProductSeedRaw q = q := by
  simpa only [normalizeProductSeedRaw_eq_conditional, beq_iff_eq, hq, ite_false]

/-- Exact fixed binary32 classifier transport. -/
theorem model_toModel_isNaN (x : Model FloatFormat.binary32) :
    (Model.toModel x).isNaN = Model.isNaN x := by
  have he : unpackExponent (Model.toModelBits x) = (-1 : BitVec 8) ↔
      Model.expField x = FloatFormat.binary32.expAllOnesNat := by
    rw [← BitVec.toNat_inj, Model.unpackExponent_toNat,
      Model.toNat_neg_one_exponentBits FloatFormat.binary32]
  have hm : unpackMantissa (Model.toModelBits x) = (0 : BitVec 23) ↔
      Model.fracField x = 0 := by
    rw [← BitVec.toNat_inj, Model.unpackMantissa_toNat]
    rfl
  change (Model.toModel x).isNaN = Model.IEEE.isNaN x
  unfold Model.toModel unpack
  dsimp only
  split_ifs <;>
    simp_all [Float.Model.UnpackedFloat.isNaN, Model.IEEE.isNaN]

theorem toFloat32_isNaN (x : Competition.Binary32) :
    (ExecFloat.Binary.toFloat32 x).isNaN =
      Model.isNaN (ExecFloat.Binary.toModel x) := by
  change ((Model.toFloat32Model (ExecFloat.Binary.toModel x)).unpack).isNaN = _
  rw [Model.unpack_toFloat32Model]
  exact model_toModel_isNaN _

theorem native_pack_unpack (x : Float32) :
    Float32.ofModel (Float32.Model.pack x.toModel.unpack) = x := by
  cases x with
  | ofModel m =>
      apply congrArg Float32.ofModel
      exact Model.toFloat32Model_ofFloat32Model m

theorem native_posZero_unpack :
    (Float32.ofBits 0).toModel.unpack = .zero .positive := rfl

theorem native_negZero_unpack :
    (Float32.ofBits 0x80000000).toModel.unpack = .zero .negative := rfl

theorem native_unpack_eq_negZero (x : Float32) :
    x.toModel.unpack = .zero .negative ↔ x = Float32.ofBits 0x80000000 := by
  constructor
  · intro h
    rw [← native_pack_unpack x, h]
    rfl
  · intro h
    rw [h]
    exact native_negZero_unpack

/-- The chosen decision procedure is explicit in this proof-only proposition. -/
theorem unpacked_posZero_add (x : Float.Model.UnpackedFloat) :
    Float.Model.UnpackedFloat.add Float.Model.Format.binary32 (.zero .positive) x =
      @ite Float.Model.UnpackedFloat (x = .zero .negative)
        (Classical.propDecidable _) (.zero .positive) x := by
  classical
  cases x with
  | notANumber => simp [Float.Model.UnpackedFloat.add]
  | infinity s => simp [Float.Model.UnpackedFloat.add]
  | zero s => cases s <;> simp [Float.Model.UnpackedFloat.add]
  | finite s m e h => simp [Float.Model.UnpackedFloat.add]

theorem native_posZero_add (x : Float32) :
    Float32.ofBits 0 + x =
      @ite Float32 (x = Float32.ofBits 0x80000000)
        (Classical.propDecidable _) (Float32.ofBits 0) x := by
  classical
  change Float32.ofModel (Float32.Model.pack
    (Float.Model.UnpackedFloat.add Float.Model.Format.binary32
      (Float32.ofBits 0).toModel.unpack x.toModel.unpack)) = _
  rw [native_posZero_unpack, unpacked_posZero_add]
  by_cases h : x.toModel.unpack = .zero .negative
  · rw [if_pos h, if_pos ((native_unpack_eq_negZero x).mp h)]
    rfl
  · have hx := mt (native_unpack_eq_negZero x).mpr h
    rw [if_neg h, if_neg hx]
    exact native_pack_unpack x

/-- A native negative-zero image itself supplies the non-NaN roundtrip premise. -/
theorem native_eq_negZero_iff_raw (q : Competition.Binary32) :
    ExecFloat.Binary.toFloat32 q = Float32.ofBits 0x80000000 ↔
      q.raw.1 = (0x80000000 : UInt32) := by
  constructor
  · intro h
    have hq : (ExecFloat.Binary.toFloat32 q).isNaN = false := by
      rw [h]
      decide
    have hr := Submission.NotNaNProbe.roundtrip q hq
    rw [h] at hr
    have hb := congrArg (fun z : Competition.Binary32 => z.raw.1) hr
    change (0x80000000 : UInt32) = q.raw.1 at hb
    exact hb.symm
  · intro h
    change Float32.ofBits q.raw.1 = Float32.ofBits 0x80000000
    rw [h]

/-- Use the retained exact native-add bridge, then the actual non-NaN roundtrip. -/
theorem add_posZero_of_not_nan (q : Competition.Binary32)
    (hq : (ExecFloat.Binary.toFloat32 q).isNaN = false) :
    ExecFloat.add Competition.posZero q = normalizeProductSeedRaw q := by
  rw [normalizeProductSeedRaw_eq_conditional]
  have hzero : ExecFloat.Binary.ofFloat32 (Float32.ofBits 0) =
      Competition.posZero := rfl
  have hn := Submission.R7Native.ofFloat32Add
    (Float32.ofBits 0) (ExecFloat.Binary.toFloat32 q) (by decide) hq
  rw [hzero, Submission.NotNaNProbe.roundtrip q hq] at hn
  rw [native_posZero_add] at hn
  by_cases hz : q.raw.1 = (0x80000000 : UInt32)
  · have he := (native_eq_negZero_iff_raw q).mpr hz
    rw [if_pos he] at hn
    simpa only [hzero, hz, beq_self_eq_true, Bool.true_eq, ite_true] using hn.symm
  · have he : ExecFloat.Binary.toFloat32 q ≠ Float32.ofBits 0x80000000 :=
      mt (native_eq_negZero_iff_raw q).mp hz
    rw [if_neg he] at hn
    rw [Submission.NotNaNProbe.roundtrip q hq] at hn
    simpa only [beq_iff_eq, hz, ite_false] using hn.symm

theorem model_posZero_add_quiet (q : Model FloatFormat.binary32)
    (hq : Model.isNaN q = true) (hs : Model.isSNaN q = false) :
    Model.Spec.add (Model.posZero FloatFormat.binary32) q = q := by
  have hd := Model.toDyadic?_eq_none_of_isNaN hq
  have hz : Model.isNaN (Model.posZero FloatFormat.binary32) = false := by decide
  have hsz : Model.isSNaN (Model.posZero FloatFormat.binary32) = false := by decide
  have hquiet := R7W01.quietNaN32_eq_self q hq hs
  simp [Model.Spec.add, hd, Model.chooseNaN2, hz, hsz, hq, hs, hquiet]

theorem exec_posZero_add_quiet (q : Competition.Binary32)
    (hq : Model.isNaN (ExecFloat.Binary.toModel q) = true)
    (hs : Model.isSNaN (ExecFloat.Binary.toModel q) = false) :
    ExecFloat.add Competition.posZero q = q := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel (ExecFloat.add Competition.posZero q) =
    ExecFloat.Binary.toModel q
  rw [R7W01.exec_toModel_add]
  exact model_posZero_add_quiet _ hq hs

theorem normalizeProductSeedRaw_of_nan (q : Competition.Binary32)
    (hq : Model.isNaN (ExecFloat.Binary.toModel q) = true) :
    normalizeProductSeedRaw q = q := by
  have hnative : (ExecFloat.Binary.toFloat32 q).isNaN = true :=
    (toFloat32_isNaN q).trans hq
  have hne : q.raw.1 ≠ (0x80000000 : UInt32) := by
    intro hz
    have he := (native_eq_negZero_iff_raw q).mpr hz
    rw [he] at hnative
    have hn : (Float32.ofBits 0x80000000).isNaN = false := by decide
    have hbad : (false : Bool) = true := hn.symm.trans hnative
    cases hbad
  exact normalizeProductSeedRaw_eq_self q hne

/-- Arbitrary signaling q is deliberately excluded from this general identity. -/
theorem add_posZero_of_not_snan (q : Competition.Binary32)
    (hq : Model.isSNaN (ExecFloat.Binary.toModel q) = false) :
    ExecFloat.add Competition.posZero q = normalizeProductSeedRaw q := by
  cases hn : (ExecFloat.Binary.toFloat32 q).isNaN with
  | false => exact add_posZero_of_not_nan q hn
  | true =>
      have hnan : Model.isNaN (ExecFloat.Binary.toModel q) = true :=
        (toFloat32_isNaN q).symm.trans hn
      exact (exec_posZero_add_quiet q hnan hq).trans
        (normalizeProductSeedRaw_of_nan q hnan).symm

theorem exec_mul_not_snan (x y : Competition.Binary32) :
    Model.isSNaN (ExecFloat.Binary.toModel (ExecFloat.mul x y)) = false := by
  rw [R7W01.exec_toModel_mul]
  exact R7W01.mul32_not_snan _ _

/-- Full-carrier equality, with no assumptions on either original input word. -/
theorem add_posZero_mul (x y : Competition.Binary32) :
    ExecFloat.add Competition.posZero (ExecFloat.mul x y) =
      normalizeProductSeedRaw (ExecFloat.mul x y) :=
  add_posZero_of_not_snan _ (exec_mul_not_snan x y)

theorem add_posZero_mul_raw (x y : Competition.Binary32) :
    (ExecFloat.add Competition.posZero (ExecFloat.mul x y)).raw.1 =
      (normalizeProductSeedRaw (ExecFloat.mul x y)).raw.1 :=
  congrArg (fun q : Competition.Binary32 => q.raw.1) (add_posZero_mul x y)

theorem add_posZero_mul_raw_conditional (x y : Competition.Binary32) :
    (ExecFloat.add Competition.posZero (ExecFloat.mul x y)).raw.1 =
      if (ExecFloat.mul x y).raw.1 == (0x80000000 : UInt32)
      then (0 : UInt32) else (ExecFloat.mul x y).raw.1 := by
  rw [add_posZero_mul, normalizeProductSeedRaw_raw]

theorem submission_add_posZero_mul (x y : Competition.Binary32) :
    Submission.add Competition.posZero (Submission.mul x y) =
      normalizeProductSeedRaw (Submission.mul x y) := by
  simpa only [Submission.add_eq, Submission.mul_eq] using add_posZero_mul x y

theorem normalize_submission_mul_eq_add (x y : Competition.Binary32) :
    normalizeProductSeedRaw (Submission.mul x y) =
      Submission.add Competition.posZero (Submission.mul x y) :=
  (submission_add_posZero_mul x y).symm

theorem submission_add_posZero_mul_raw_conditional (x y : Competition.Binary32) :
    (Submission.add Competition.posZero (Submission.mul x y)).raw.1 =
      if (Submission.mul x y).raw.1 == (0x80000000 : UInt32)
      then (0 : UInt32) else (Submission.mul x y).raw.1 := by
  simpa only [Submission.add_eq, Submission.mul_eq] using
    add_posZero_mul_raw_conditional x y

end D7SeedNormalize
