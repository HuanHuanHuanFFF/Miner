namespace Submission.R7Native

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
open Float.Model.UnpackedFloat

abbrev F := FloatFormat.binary32
abbrev M := Model F

theorem finiteDecode (x : M) (hx : (Model.toModel x).isFinite = true) :
    ∃ d, Model.toDyadic? x = some d := by
  have hsome : (Model.toDyadic? x).isSome = true := by
    rw [Model.toDyadic?_ieee_eq_model F (by decide)]
    cases hm : Model.toModel x <;>
      simp_all [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.isFinite]
  cases hd : Model.toDyadic? x with
  | none => simp [hd] at hsome
  | some d => exact ⟨d, rfl⟩

theorem nonNaNView (x : M) (hx : (Model.toModel x).isNaN = false) :
    (Model.toModel x).isFinite = true ∨ ∃ s, Model.toModel x = .infinity s := by
  cases hm : Model.toModel x with
  | notANumber => simp [hm, Float.Model.UnpackedFloat.isNaN] at hx
  | infinity s => exact Or.inr ⟨s, rfl⟩
  | zero s => exact Or.inl rfl
  | finite s m e h => exact Or.inl rfl

theorem eqOfInfinity (x : M) (s : Sign) (hx : Model.toModel x = .infinity s) :
    x = Model.ofModel F (.infinity s) := by
  have hc := NotNaNProbe.modelCanonicalOfNotNaN x
    (by simp [hx, Float.Model.UnpackedFloat.isNaN])
  have h := Model.canonicalizeModel_eq_self x hc
  change Model.ofModel F (Model.toModel x) = x at h
  rw [hx] at h
  exact h.symm

theorem eqOfZero (x : M) (s : Sign) (hx : Model.toModel x = .zero s) :
    x = Model.ofModel F (.zero s) := by
  have hc := NotNaNProbe.modelCanonicalOfNotNaN x
    (by simp [hx, Float.Model.UnpackedFloat.isNaN])
  have h := Model.canonicalizeModel_eq_self x hc
  change Model.ofModel F (Model.toModel x) = x at h
  rw [hx] at h
  exact h.symm

theorem infinityDecode (s : Sign) :
    Model.toDyadic? (Model.ofModel F (.infinity s)) = none := by
  rw [Model.toDyadic?_ieee_eq_model F (by decide), Model.toModel_ofModel_infinity]
  rfl

theorem nativeOverflow_eq (b : Bool) :
    Model.nativeOverflow F b = Model.ofModel F (.infinity (Model.modelSign b)) := by
  cases b <;> decide

theorem specAddInfLeft (s : Sign) (y : M)
    (hn : Model.isNaN y = false) (hi : Model.isInf y = false) :
    Model.Spec.add (Model.ofModel F (.infinity s)) y = Model.ofModel F (.infinity s) := by
  have hxnan := Model.isNaN_ofModel_infinity F (by decide) s
  have hxinf := Model.isInf_ofModel_infinity F (by decide) s
  have hsel := (Model.chooseNaN2_eq_none_iff (Model.ofModel F (.infinity s)) y).mpr
    ⟨hxnan, hn⟩
  unfold Model.Spec.add
  rw [infinityDecode]
  cases hd : Model.toDyadic? y <;> simp [hd, hsel, hxinf, hi]

theorem specAddInfRight (s : Sign) (x : M)
    (hn : Model.isNaN x = false) (hi : Model.isInf x = false) :
    Model.Spec.add x (Model.ofModel F (.infinity s)) = Model.ofModel F (.infinity s) := by
  have hynan := Model.isNaN_ofModel_infinity F (by decide) s
  have hyinf := Model.isInf_ofModel_infinity F (by decide) s
  have hsel := (Model.chooseNaN2_eq_none_iff x (Model.ofModel F (.infinity s))).mpr
    ⟨hn, hynan⟩
  unfold Model.Spec.add
  rw [infinityDecode]
  cases hd : Model.toDyadic? x <;> simp [hd, hsel, hi, hyinf]

theorem specMulInfLeft (s : Sign) (y : M) (d : FloatLib.Numerics.Dyadic)
    (hd : Model.toDyadic? y = some d) (hnz : d.significand ≠ 0) :
    Model.Spec.mul (Model.ofModel F (.infinity s)) y =
      Model.nativeOverflow F (Model.modelSignBit s != d.negative) := by
  have hxnan := Model.isNaN_ofModel_infinity F (by decide) s
  have hxinf := Model.isInf_ofModel_infinity F (by decide) s
  have hynan := Model.isNaN_eq_false_of_toDyadic?_some hd
  have hsel := (Model.chooseNaN2_eq_none_iff (Model.ofModel F (.infinity s)) y).mpr
    ⟨hxnan, hynan⟩
  have hzero := Model.isZero_eq_beq_zero_of_toDyadic?_some hd
  have hsign := Model.sign_eq_signBit_of_toDyadic?_some hd
  simp [Model.Spec.mul, infinityDecode, hd, hsel, hxinf, hzero, hnz,
    Model.signBit_ofModel_infinity, ← hsign]

theorem specMulInfRight (s : Sign) (x : M) (d : FloatLib.Numerics.Dyadic)
    (hd : Model.toDyadic? x = some d) (hnz : d.significand ≠ 0) :
    Model.Spec.mul x (Model.ofModel F (.infinity s)) =
      Model.nativeOverflow F (d.negative != Model.modelSignBit s) := by
  have hynan := Model.isNaN_ofModel_infinity F (by decide) s
  have hyinf := Model.isInf_ofModel_infinity F (by decide) s
  have hxnan := Model.isNaN_eq_false_of_toDyadic?_some hd
  have hxinf := Model.isInf_eq_false_of_toDyadic?_some hd
  have hsel := (Model.chooseNaN2_eq_none_iff x (Model.ofModel F (.infinity s))).mpr
    ⟨hxnan, hynan⟩
  have hzero := Model.isZero_eq_beq_zero_of_toDyadic?_some hd
  have hsign := Model.sign_eq_signBit_of_toDyadic?_some hd
  simp [Model.Spec.mul, infinityDecode, hd, hsel, hxinf, hyinf, hzero, hnz,
    Model.signBit_ofModel_infinity, ← hsign]

theorem modelAdd (x y : M)
    (hx : (Model.toModel x).isNaN = false) (hy : (Model.toModel y).isNaN = false) :
    Model.add x y = Model.ofModel F
      (Float.Model.UnpackedFloat.add F.toModel (Model.toModel x) (Model.toModel y)) := by
  rcases nonNaNView x hx with hxf | ⟨sx, hxi⟩
  · rcases nonNaNView y hy with hyf | ⟨sy, hyi⟩
    · exact Model.add_eq_ofModel_add_of_isFinite (by decide) x y hxf hyf
    · obtain ⟨dx, hdx⟩ := finiteDecode x hxf
      rw [eqOfInfinity y sy hyi, Model.Proof.add_eq_spec,
        specAddInfRight sy x (Model.isNaN_eq_false_of_toDyadic?_some hdx)
          (Model.isInf_eq_false_of_toDyadic?_some hdx)]
      cases hm : Model.toModel x <;>
        simp_all [Float.Model.UnpackedFloat.isFinite, Float.Model.UnpackedFloat.add]
  · rcases nonNaNView y hy with hyf | ⟨sy, hyi⟩
    · obtain ⟨dy, hdy⟩ := finiteDecode y hyf
      rw [eqOfInfinity x sx hxi, Model.Proof.add_eq_spec,
        specAddInfLeft sx y (Model.isNaN_eq_false_of_toDyadic?_some hdy)
          (Model.isInf_eq_false_of_toDyadic?_some hdy)]
      cases hm : Model.toModel y <;>
        simp_all [Float.Model.UnpackedFloat.isFinite, Float.Model.UnpackedFloat.add]
    · rw [eqOfInfinity x sx hxi, eqOfInfinity y sy hyi]
      cases sx <;> cases sy <;> decide

theorem modelMulInfLeft (s : Sign) (y : M)
    (hy : (Model.toModel y).isFinite = true) :
    Model.mul (Model.ofModel F (.infinity s)) y = Model.ofModel F
      (Float.Model.UnpackedFloat.mul F.toModel (.infinity s) (Model.toModel y)) := by
  cases hm : Model.toModel y with
  | notANumber => simp [hm, Float.Model.UnpackedFloat.isFinite] at hy
  | infinity t => simp [hm, Float.Model.UnpackedFloat.isFinite] at hy
  | zero t =>
      rw [eqOfZero y t hm]
      cases s <;> cases t <;> decide
  | finite t m e hp =>
      have hd : Model.toDyadic? y = some ⟨Model.modelSignBit t, m, e⟩ := by
        rw [Model.toDyadic?_ieee_eq_model F (by decide), hm]
        rfl
      rw [Model.Proof.mul_eq_spec, specMulInfLeft s y _ hd (Nat.ne_of_gt hp),
        nativeOverflow_eq]
      cases s <;> cases t <;> rfl

theorem modelMulInfRight (s : Sign) (x : M)
    (hx : (Model.toModel x).isFinite = true) :
    Model.mul x (Model.ofModel F (.infinity s)) = Model.ofModel F
      (Float.Model.UnpackedFloat.mul F.toModel (Model.toModel x) (.infinity s)) := by
  cases hm : Model.toModel x with
  | notANumber => simp [hm, Float.Model.UnpackedFloat.isFinite] at hx
  | infinity t => simp [hm, Float.Model.UnpackedFloat.isFinite] at hx
  | zero t =>
      rw [eqOfZero x t hm]
      cases s <;> cases t <;> decide
  | finite t m e hp =>
      have hd : Model.toDyadic? x = some ⟨Model.modelSignBit t, m, e⟩ := by
        rw [Model.toDyadic?_ieee_eq_model F (by decide), hm]
        rfl
      rw [Model.Proof.mul_eq_spec, specMulInfRight s x _ hd (Nat.ne_of_gt hp),
        nativeOverflow_eq]
      cases s <;> cases t <;> rfl

theorem modelMul (x y : M)
    (hx : (Model.toModel x).isNaN = false) (hy : (Model.toModel y).isNaN = false) :
    Model.mul x y = Model.ofModel F
      (Float.Model.UnpackedFloat.mul F.toModel (Model.toModel x) (Model.toModel y)) := by
  rcases nonNaNView x hx with hxf | ⟨sx, hxi⟩
  · rcases nonNaNView y hy with hyf | ⟨sy, hyi⟩
    · exact NativeBridge.modelMulFinite (by decide) x y hxf hyf
    · rw [eqOfInfinity y sy hyi, Model.toModel_ofModel_infinity]
      exact modelMulInfRight sy x hxf
  · rcases nonNaNView y hy with hyf | ⟨sy, hyi⟩
    · rw [eqOfInfinity x sx hxi, Model.toModel_ofModel_infinity]
      exact modelMulInfLeft sx y hyf
    · rw [eqOfInfinity x sx hxi, eqOfInfinity y sy hyi]
      cases sx <;> cases sy <;> decide

theorem toModelExecAdd (x y : Binary32) :
    ExecFloat.Binary.toModel (ExecFloat.add x y) =
      Model.Spec.add (ExecFloat.Binary.toModel x) (ExecFloat.Binary.toModel y) := by
  rw [ExecFloat.Proof.add_eq_spec]
  change Configured.Family.toModel
    (ExecFloat.ModelCodec.liftBinary Model.Spec.add x y) = _
  simp [Configured.Family.toModel, ExecFloat.Binary.toModel]

theorem ofFloat32Add (x y : Float32) (hx : x.isNaN = false) (hy : y.isNaN = false) :
    ExecFloat.Binary.ofFloat32 (x + y) =
      ExecFloat.add (ExecFloat.Binary.ofFloat32 x) (ExecFloat.Binary.ofFloat32 y) := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 (x + y)) =
    ExecFloat.Binary.toModel
      (ExecFloat.add (ExecFloat.Binary.ofFloat32 x) (ExecFloat.Binary.ofFloat32 y))
  rw [toModelExecAdd, ← Model.Proof.add_eq_spec]
  rw [ExecFloat.Binary.toModel_ofFloat32, ExecFloat.Binary.toModel_ofFloat32,
    ExecFloat.Binary.toModel_ofFloat32]
  change Model.ofFloat32Model (Float32.Model.add x.toModel y.toModel) = _
  rw [Float32.Model.add, Model.ofFloat32Model_pack]
  have h := modelAdd (Model.ofFloat32Model x.toModel) (Model.ofFloat32Model y.toModel)
    (by simpa only [Model.toModel_ofFloat32Model, Float32.isNaN, Float32.Model.isNaN] using hx)
    (by simpa only [Model.toModel_ofFloat32Model, Float32.isNaN, Float32.Model.isNaN] using hy)
  rw [Model.toModel_ofFloat32Model, Model.toModel_ofFloat32Model] at h
  exact h.symm

theorem ofFloat32Mul (x y : Float32) (hx : x.isNaN = false) (hy : y.isNaN = false) :
    ExecFloat.Binary.ofFloat32 (x * y) =
      ExecFloat.mul (ExecFloat.Binary.ofFloat32 x) (ExecFloat.Binary.ofFloat32 y) := by
  apply Configured.Family.toModel_injective
  change ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 (x * y)) =
    ExecFloat.Binary.toModel
      (ExecFloat.mul (ExecFloat.Binary.ofFloat32 x) (ExecFloat.Binary.ofFloat32 y))
  rw [NativeBridge.toModelExecMul, ← Model.Proof.mul_eq_spec]
  rw [ExecFloat.Binary.toModel_ofFloat32, ExecFloat.Binary.toModel_ofFloat32,
    ExecFloat.Binary.toModel_ofFloat32]
  change Model.ofFloat32Model (Float32.Model.mul x.toModel y.toModel) = _
  rw [Float32.Model.mul, Model.ofFloat32Model_pack]
  have h := modelMul (Model.ofFloat32Model x.toModel) (Model.ofFloat32Model y.toModel)
    (by simpa only [Model.toModel_ofFloat32Model, Float32.isNaN, Float32.Model.isNaN] using hx)
    (by simpa only [Model.toModel_ofFloat32Model, Float32.isNaN, Float32.Model.isNaN] using hy)
  rw [Model.toModel_ofFloat32Model, Model.toModel_ofFloat32Model] at h
  exact h.symm

end Submission.R7Native
