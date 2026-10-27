namespace R7W05
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
open Float.Model.UnpackedFloat

/-- The actual raw binary32 NaN classifier agrees exactly with Lean's unpacked model. -/
theorem model_toModel_isNaN (x : Model FloatFormat.binary32) :
    (Model.toModel x).isNaN = Model.isNaN x := by
  have he : unpackExponent (Model.toModelBits x) = -1#(FloatFormat.binary32.toModel.exponentBits) ↔
      Model.expField x = FloatFormat.binary32.expAllOnesNat := by
    rw [← BitVec.toNat_inj, Model.unpackExponent_toNat,
      Model.toNat_neg_one_exponentBits]
  have hm : unpackMantissa (Model.toModelBits x) = 0#(FloatFormat.binary32.toModel.mantissaBitsWithoutImplicit) ↔
      Model.fracField x = 0 := by
    rw [← BitVec.toNat_inj, Model.unpackMantissa_toNat]
    rfl
  change (Model.toModel x).isNaN = Model.IEEE.isNaN x
  unfold Model.toModel unpack
  dsimp only
  split_ifs <;>
    simp_all [Float.Model.UnpackedFloat.isNaN, Model.IEEE.isNaN]

/-- Exact classifier transport for every real competition carrier, including all NaN words. -/
theorem toFloat32_isNaN (x : Binary32) :
    (ExecFloat.Binary.toFloat32 x).isNaN = Model.isNaN (ExecFloat.Binary.toModel x) := by
  change ((Model.toFloat32Model (ExecFloat.Binary.toModel x)).unpack).isNaN = _
  rw [Model.unpack_toFloat32Model]
  exact model_toModel_isNaN _

/-- In Lean's actual canonical Float32 model, a NaN is propositionally equal to native NaN. -/
theorem native_eq_nan_of_isNaN (x : Float32) (hx : x.isNaN = true) :
    x = Float32.nan := by
  have hunpack : x.toModel.unpack = .notANumber := by
    change x.toModel.unpack.isNaN = true at hx
    cases h : x.toModel.unpack <;> simp_all [Float.Model.UnpackedFloat.isNaN]
  cases x with
  | ofModel m =>
      apply congrArg Float32.ofModel
      change m = Float32.Model.pack .notANumber
      have hr := Model.toFloat32Model_ofFloat32Model m
      change Float32.Model.pack m.unpack = m at hr
      change m.unpack = .notANumber at hunpack
      rw [← hr, hunpack]

/-- Raw NaN metadata is erased only by this explicit native conversion boundary. -/
theorem toFloat32_eq_nan_of_model_nan (x : Binary32)
    (hx : Model.isNaN (ExecFloat.Binary.toModel x) = true) :
    ExecFloat.Binary.toFloat32 x = Float32.nan := by
  apply native_eq_nan_of_isNaN
  rw [toFloat32_isNaN]
  exact hx

/-- Every actual binary32 NaN selection returns a NaN, with quieting proved concretely. -/
theorem chooseNaN2_some_nan (x y z : Model FloatFormat.binary32)
    (h : Model.chooseNaN2 x y = some z) : Model.isNaN z = true := by
  unfold Model.chooseNaN2 at h
  split_ifs at h with hsx hsy hnx hny
  · simp only [Option.some.injEq] at h
    cases h
    exact R7W01.quietNaN32_is_nan x (Model.isNaN_of_isSNaN hsx)
  · simp only [Option.some.injEq] at h
    cases h
    exact R7W01.quietNaN32_is_nan y (Model.isNaN_of_isSNaN hsy)
  · simp only [Option.some.injEq] at h
    cases h
    exact R7W01.quietNaN32_is_nan x hnx
  · simp only [Option.some.injEq] at h
    cases h
    exact R7W01.quietNaN32_is_nan y hny

/-- A real left NaN produces a real NaN under the public addition specification. -/
theorem model_add_nan_left (x y : Model FloatFormat.binary32)
    (hx : Model.isNaN x = true) : Model.isNaN (Model.Spec.add x y) = true := by
  have hd := Model.toDyadic?_eq_none_of_isNaN hx
  cases hc : Model.chooseNaN2 x y with
  | none =>
      have hn := (Model.chooseNaN2_eq_none_iff x y).mp hc
      simp [hx] at hn
  | some z =>
      have hout : Model.Spec.add x y = z := by
        cases hdy : Model.toDyadic? y <;> simp [Model.Spec.add, hd, hdy, hc]
      rw [hout]
      exact chooseNaN2_some_nan x y z hc

/-- A real right NaN produces a real NaN, irrespective of left NaN precedence. -/
theorem model_add_nan_right (x y : Model FloatFormat.binary32)
    (hy : Model.isNaN y = true) : Model.isNaN (Model.Spec.add x y) = true := by
  have hd := Model.toDyadic?_eq_none_of_isNaN hy
  cases hc : Model.chooseNaN2 x y with
  | none =>
      have hn := (Model.chooseNaN2_eq_none_iff x y).mp hc
      simp [hy] at hn
  | some z =>
      have hout : Model.Spec.add x y = z := by
        cases hdx : Model.toDyadic? x <;> simp [Model.Spec.add, hd, hdx, hc]
      rw [hout]
      exact chooseNaN2_some_nan x y z hc

/-- Actual native addition propagates a left NaN to its canonical native NaN. -/
theorem native_add_nan_left (x y : Float32) (hx : x.isNaN = true) :
    x + y = Float32.nan := by
  apply native_eq_nan_of_isNaN
  cases h : (x + y).isNaN with
  | true => rfl
  | false =>
      have hn := Submission.NotNaNProbe.add_inputs x y h
      simp [hx] at hn

/-- Actual native addition propagates a right NaN to its canonical native NaN. -/
theorem native_add_nan_right (x y : Float32) (hy : y.isNaN = true) :
    x + y = Float32.nan := by
  apply native_eq_nan_of_isNaN
  cases h : (x + y).isNaN with
  | true => rfl
  | false =>
      have hn := Submission.NotNaNProbe.add_inputs x y h
      simp [hy] at hn

/-- ALL INPUTS: canonical native conversion commutes with the actual binary32 add.
This includes arbitrary signaling/quiet NaN signs and payloads. The equality is
of native Float32 values, not an assertion that canonical conversion retains raw NaN metadata. -/
theorem add_toFloat32 (x y : Binary32) :
    ExecFloat.Binary.toFloat32 (ExecFloat.add x y) =
      ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y := by
  cases hx : (ExecFloat.Binary.toFloat32 x).isNaN with
  | false =>
      cases hy : (ExecFloat.Binary.toFloat32 y).isNaN with
      | false =>
          have h := Submission.R7Native.ofFloat32Add
            (ExecFloat.Binary.toFloat32 x) (ExecFloat.Binary.toFloat32 y) hx hy
          rw [Submission.NotNaNProbe.roundtrip x hx,
            Submission.NotNaNProbe.roundtrip y hy] at h
          have hp := congrArg ExecFloat.Binary.toFloat32 h
          simpa only [ExecFloat.Binary.toFloat32_ofFloat32] using hp.symm
      | true =>
          have hmy : Model.isNaN (ExecFloat.Binary.toModel y) = true := by
            rw [← toFloat32_isNaN]
            exact hy
          have hz : Model.isNaN (ExecFloat.Binary.toModel (ExecFloat.add x y)) = true := by
            rw [Submission.R7Native.toModelExecAdd]
            exact model_add_nan_right _ _ hmy
          rw [toFloat32_eq_nan_of_model_nan _ hz,
            native_add_nan_right _ _ hy]
  | true =>
      have hmx : Model.isNaN (ExecFloat.Binary.toModel x) = true := by
        rw [← toFloat32_isNaN]
        exact hx
      have hz : Model.isNaN (ExecFloat.Binary.toModel (ExecFloat.add x y)) = true := by
        rw [Submission.R7Native.toModelExecAdd]
        exact model_add_nan_left _ _ hmx
      rw [toFloat32_eq_nan_of_model_nan _ hz,
        native_add_nan_left _ _ hx]

end R7W05



/- Append after the concretely proved Add.lean. These are exact Bool equalities,
   so they transport both the NaN event and its absence in either direction. -/
namespace R7W05
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

/-- Actual raw-result NaN classifier equals the native sum-result classifier on all inputs. -/
theorem add_isNaN_eq_native (x y : Competition.Binary32) :
    ExecFloat.Binary.isNaN (ExecFloat.add x y) =
      (ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y).isNaN := by
  change Model.isNaN (ExecFloat.Binary.toModel (ExecFloat.add x y)) = _
  rw [← toFloat32_isNaN, add_toFloat32]

/-- The same classifier equality written on the actual model of the executable result. -/
theorem add_model_isNaN_eq_native (x y : Competition.Binary32) :
    Model.isNaN (ExecFloat.Binary.toModel (ExecFloat.add x y)) =
      (ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y).isNaN :=
  add_isNaN_eq_native x y

/-- The concrete Model.Spec.add classification, without an assumed execution/model bridge. -/
theorem add_spec_isNaN_eq_native (x y : Competition.Binary32) :
    Model.isNaN (Model.Spec.add (ExecFloat.Binary.toModel x) (ExecFloat.Binary.toModel y)) =
      (ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y).isNaN := by
  rw [← Submission.R7Native.toModelExecAdd]
  exact add_model_isNaN_eq_native x y

/-- A native sum NaN event is equivalent to an actual raw add-result NaN. -/
theorem add_isNaN_true_iff (x y : Competition.Binary32) :
    ExecFloat.Binary.isNaN (ExecFloat.add x y) = true ↔
      (ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y).isNaN = true := by
  rw [add_isNaN_eq_native]

/-- A native non-NaN result is equivalent to an actual raw add-result non-NaN. -/
theorem add_isNaN_false_iff (x y : Competition.Binary32) :
    ExecFloat.Binary.isNaN (ExecFloat.add x y) = false ↔
      (ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y).isNaN = false := by
  rw [add_isNaN_eq_native]

end R7W05


/- All-input canonical native multiplication bridge.
Append after Dependencies.lean and Add.lean under the sole ContractTensor dependency. -/
namespace R7W05
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

private theorem mul_unpack_of_isNaN (x : Float32) (hx : x.isNaN = true) :
    x.toModel.unpack = Float.Model.UnpackedFloat.notANumber := by
  change x.toModel.unpack.isNaN = true at hx
  cases h : x.toModel.unpack <;>
    simp_all [Float.Model.UnpackedFloat.isNaN]

/-- Native-model multiplication maps any left NaN to the canonical native NaN. -/
theorem native_mul_nan_left (x y : Float32) (hx : x.isNaN = true) :
    x * y = Float32.nan := by
  change Float32.ofModel (Float32.Model.pack
    (Float.Model.UnpackedFloat.mul Float.Model.Format.binary32
      x.toModel.unpack y.toModel.unpack)) = Float32.nan
  rw [mul_unpack_of_isNaN x hx]
  rfl

/-- Native-model multiplication maps any right NaN to the canonical native NaN. -/
theorem native_mul_nan_right (x y : Float32) (hy : y.isNaN = true) :
    x * y = Float32.nan := by
  change Float32.ofModel (Float32.Model.pack
    (Float.Model.UnpackedFloat.mul Float.Model.Format.binary32
      x.toModel.unpack y.toModel.unpack)) = Float32.nan
  rw [mul_unpack_of_isNaN y hy]
  cases x.toModel.unpack <;> rfl

/-- Public non-NaN-input bridge projected to canonical native values.
The public finite proof includes one exact-product rounding; infinities and invalid
zero-times-infinity cases are covered by the public R7Native extension. -/
theorem mul_toFloat32_of_not_nan (x y : Competition.Binary32)
    (hx : (ExecFloat.Binary.toFloat32 x).isNaN = false)
    (hy : (ExecFloat.Binary.toFloat32 y).isNaN = false) :
    ExecFloat.Binary.toFloat32 (ExecFloat.mul x y) =
      ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y := by
  have h := Submission.R7Native.ofFloat32Mul
    (ExecFloat.Binary.toFloat32 x) (ExecFloat.Binary.toFloat32 y) hx hy
  rw [Submission.NotNaNProbe.roundtrip x hx,
    Submission.NotNaNProbe.roundtrip y hy] at h
  have hn := congrArg (fun v : Competition.Binary32 => ExecFloat.Binary.toFloat32 v) h.symm
  simpa only [ExecFloat.Binary.toFloat32_ofFloat32] using hn

/-- A left NaN makes actual Model.Spec.mul return a NaN. Its selected metadata
is retained by the raw model; only the later native conversion canonicalizes it. -/
theorem model_mul_nan_left (x y : Model FloatFormat.binary32)
    (hx : Model.isNaN x = true) : Model.isNaN (Model.Spec.mul x y) = true := by
  have hdx := Model.toDyadic?_eq_none_of_isNaN hx
  cases hchoose : Model.chooseNaN2 x y with
  | none =>
      have hnot := ((Model.chooseNaN2_eq_none_iff x y).mp hchoose).1
      simp [hx] at hnot
  | some z =>
      have hz := chooseNaN2_some_nan x y z hchoose
      cases hd : Model.toDyadic? y <;>
        simpa only [Model.Spec.mul, hdx, hd, hchoose] using hz

/-- The corresponding right NaN classification for actual Model.Spec.mul. -/
theorem model_mul_nan_right (x y : Model FloatFormat.binary32)
    (hy : Model.isNaN y = true) : Model.isNaN (Model.Spec.mul x y) = true := by
  have hdy := Model.toDyadic?_eq_none_of_isNaN hy
  cases hchoose : Model.chooseNaN2 x y with
  | none =>
      have hnot := ((Model.chooseNaN2_eq_none_iff x y).mp hchoose).2
      simp [hy] at hnot
  | some z =>
      have hz := chooseNaN2_some_nan x y z hchoose
      cases hd : Model.toDyadic? x <;>
        simpa only [Model.Spec.mul, hdy, hd, hchoose] using hz

/-- All-input canonical native multiplication bridge. No finiteness, non-NaN,
or payload restrictions are imposed on the original Competition.Binary32 inputs. -/
theorem mul_toFloat32 (x y : Competition.Binary32) :
    ExecFloat.Binary.toFloat32 (ExecFloat.mul x y) =
      ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y := by
  cases hx : (ExecFloat.Binary.toFloat32 x).isNaN with
  | false =>
      cases hy : (ExecFloat.Binary.toFloat32 y).isNaN with
      | false => exact mul_toFloat32_of_not_nan x y hx hy
      | true =>
          rw [native_mul_nan_right _ _ hy]
          apply toFloat32_eq_nan_of_model_nan
          rw [Submission.NativeBridge.toModelExecMul]
          exact model_mul_nan_right _ _ ((toFloat32_isNaN y).symm.trans hy)
  | true =>
      rw [native_mul_nan_left _ _ hx]
      apply toFloat32_eq_nan_of_model_nan
      rw [Submission.NativeBridge.toModelExecMul]
      exact model_mul_nan_left _ _ ((toFloat32_isNaN x).symm.trans hx)

/-- Exact equality of the actual stored-result classifier and the native product classifier. -/
theorem mul_isNaN_eq_native (x y : Competition.Binary32) :
    ExecFloat.Binary.isNaN (ExecFloat.mul x y) =
      (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y).isNaN := by
  change Model.isNaN (ExecFloat.Binary.toModel (ExecFloat.mul x y)) = _
  rw [← toFloat32_isNaN, mul_toFloat32]

/-- The same classifier equality written on the complete raw model value. -/
theorem mul_model_isNaN_eq_native (x y : Competition.Binary32) :
    Model.isNaN (ExecFloat.Binary.toModel (ExecFloat.mul x y)) =
      (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y).isNaN :=
  mul_isNaN_eq_native x y

/-- Every native-product NaN event is exactly an actual raw multiplication NaN event. -/
theorem mul_isNaN_true_iff (x y : Competition.Binary32) :
    ExecFloat.Binary.isNaN (ExecFloat.mul x y) = true ↔
      (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y).isNaN = true := by
  rw [mul_isNaN_eq_native]

/-- Every native-product non-NaN event is exactly an actual raw multiplication non-NaN event. -/
theorem mul_isNaN_false_iff (x y : Competition.Binary32) :
    ExecFloat.Binary.isNaN (ExecFloat.mul x y) = false ↔
      (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y).isNaN = false := by
  rw [mul_isNaN_eq_native]

end R7W05


/- Exact repair at a native NaN transition. Append after Dependencies, Add and Mul.
   Only the prior non-NaN native accumulator is imported; original current input
   words are retained for metadata-sensitive recomputation. -/
namespace R7W05
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

@[inline] def nativeSumStep (acc : Float32) (x : Competition.Binary32) : Float32 :=
  acc + ExecFloat.Binary.toFloat32 x

/-- Two separate original-order rounded operations; no fused operation is used. -/
@[inline] def nativeDotStep (acc : Float32) (x y : Competition.Binary32) : Float32 :=
  acc + (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y)

@[inline] def repairSumStep (acc : Float32) (x : Competition.Binary32) : Competition.Binary32 :=
  ExecFloat.add (ExecFloat.Binary.ofFloat32 acc) x

@[inline] def repairDotStep (acc : Float32) (x y : Competition.Binary32) : Competition.Binary32 :=
  ExecFloat.add (ExecFloat.Binary.ofFloat32 acc) (ExecFloat.mul x y)

/-- A matching non-NaN native state reconstructs the original full carrier word.
    This includes signed zero and infinity; no finite-only restriction is imposed. -/
theorem native_acc_roundtrip (q : Competition.Binary32) (acc : Float32)
    (hmatch : ExecFloat.Binary.toFloat32 q = acc) (hacc : acc.isNaN = false) :
    ExecFloat.Binary.ofFloat32 acc = q := by
  rw [← hmatch]
  apply Submission.NotNaNProbe.roundtrip
  simpa only [hmatch] using hacc

/-- Exact canonical native result of the ordered mul-then-add reference step. -/
theorem dot_toFloat32 (q x y : Competition.Binary32) :
    ExecFloat.Binary.toFloat32 (ExecFloat.add q (ExecFloat.mul x y)) =
      nativeDotStep (ExecFloat.Binary.toFloat32 q) x y := by
  rw [add_toFloat32, mul_toFloat32]
  rfl

/-- A native sum NaN event is precisely a NaN of the full raw reference result. -/
theorem native_sum_isNaN_eq_raw (q x : Competition.Binary32) :
    (nativeSumStep (ExecFloat.Binary.toFloat32 q) x).isNaN =
      Model.isNaN (ExecFloat.Binary.toModel (ExecFloat.add q x)) := by
  exact (congrArg Float32.isNaN (add_toFloat32 q x)).symm.trans
    (toFloat32_isNaN (ExecFloat.add q x))

/-- The same exact event classification for two separately rounded dot operations. -/
theorem native_dot_isNaN_eq_raw (q x y : Competition.Binary32) :
    (nativeDotStep (ExecFloat.Binary.toFloat32 q) x y).isNaN =
      Model.isNaN (ExecFloat.Binary.toModel (ExecFloat.add q (ExecFloat.mul x y))) := by
  exact (congrArg Float32.isNaN (dot_toFloat32 q x y)).symm.trans
    (toFloat32_isNaN (ExecFloat.add q (ExecFloat.mul x y)))

/-- Metadata-exact recomputation from the prior native state and the original input. -/
theorem repairSumStep_eq_original (q : Competition.Binary32) (acc : Float32)
    (x : Competition.Binary32)
    (hmatch : ExecFloat.Binary.toFloat32 q = acc) (hacc : acc.isNaN = false) :
    repairSumStep acc x = ExecFloat.add q x := by
  unfold repairSumStep
  rw [native_acc_roundtrip q acc hmatch hacc]

/-- The product is recomputed from both original raw words before ordinary addition. -/
theorem repairDotStep_eq_original (q : Competition.Binary32) (acc : Float32)
    (x y : Competition.Binary32)
    (hmatch : ExecFloat.Binary.toFloat32 q = acc) (hacc : acc.isNaN = false) :
    repairDotStep acc x y = ExecFloat.add q (ExecFloat.mul x y) := by
  unfold repairDotStep
  rw [native_acc_roundtrip q acc hmatch hacc]

/-- Exact classification of the repair computation, independent of metadata canonicalization. -/
theorem repairSumStep_isNaN_eq (acc : Float32) (x : Competition.Binary32) :
    Model.isNaN (ExecFloat.Binary.toModel (repairSumStep acc x)) =
      (nativeSumStep acc x).isNaN := by
  have h := native_sum_isNaN_eq_raw (ExecFloat.Binary.ofFloat32 acc) x
  simpa only [ExecFloat.Binary.toFloat32_ofFloat32, repairSumStep] using h.symm

/-- Exact classification of the repaired original-order dot step. -/
theorem repairDotStep_isNaN_eq (acc : Float32) (x y : Competition.Binary32) :
    Model.isNaN (ExecFloat.Binary.toModel (repairDotStep acc x y)) =
      (nativeDotStep acc x y).isNaN := by
  have h := native_dot_isNaN_eq_raw (ExecFloat.Binary.ofFloat32 acc) x y
  simpa only [ExecFloat.Binary.toFloat32_ofFloat32, repairDotStep] using h.symm

/-- An observed native sum NaN event produces a concretely proved quiet repair result. -/
theorem repairSumStep_isQNaN (acc : Float32) (x : Competition.Binary32)
    (hevent : (nativeSumStep acc x).isNaN = true) :
    Model.isQNaN (ExecFloat.Binary.toModel (repairSumStep acc x)) = true := by
  rw [Model.isQNaN_eq_nan_and_not_signaling]
  have hn := (repairSumStep_isNaN_eq acc x).trans hevent
  have hs := Submission.R7W03.exec_add_not_snan (ExecFloat.Binary.ofFloat32 acc) x
  change Model.isSNaN (ExecFloat.Binary.toModel (repairSumStep acc x)) = false at hs
  rw [hn, hs]
  rfl

/-- The outer actual addition guarantees that a repaired dot event is quiet as well. -/
theorem repairDotStep_isQNaN (acc : Float32) (x y : Competition.Binary32)
    (hevent : (nativeDotStep acc x y).isNaN = true) :
    Model.isQNaN (ExecFloat.Binary.toModel (repairDotStep acc x y)) = true := by
  rw [Model.isQNaN_eq_nan_and_not_signaling]
  have hn := (repairDotStep_isNaN_eq acc x y).trans hevent
  have hs := Submission.R7W03.exec_add_not_snan
    (ExecFloat.Binary.ofFloat32 acc) (ExecFloat.mul x y)
  change Model.isSNaN (ExecFloat.Binary.toModel (repairDotStep acc x y)) = false at hs
  rw [hn, hs]
  rfl


end R7W05
