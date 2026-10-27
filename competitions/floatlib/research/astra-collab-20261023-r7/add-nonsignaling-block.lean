
/- Append after the concrete Dependencies.lean under the sole ContractTensor dependency.
   This section closes every real binary32 Model.Spec.add branch. -/
namespace R7W03
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Floats.Formats.BinaryInterchange.Model

private theorem chooseNaN2_none_not_snan
    (x y : Model FloatFormat.binary32) (h : chooseNaN2 x y = none) :
    isSNaN x = false ∧ isSNaN y = false := by
  have hn := (chooseNaN2_eq_none_iff x y).mp h
  exact ⟨isSNaN_eq_false_of_isNaN_eq_false x hn.1,
    isSNaN_eq_false_of_isNaN_eq_false y hn.2⟩

/-- The actual binary32 addition specification never emits a signaling NaN.
No finite, normal, non-NaN, sign, or payload assumption is made. -/
theorem model_add_not_snan (x y : Model FloatFormat.binary32) :
    isSNaN (Spec.add x y) = false := by
  unfold Spec.add
  split
  · exact R7W01.roundDyadic32_not_snan _
  · split
    · rename_i n hn
      exact R7W01.chooseNaN2_32_not_snan x y n hn
    · rename_i hnone
      have hxy := chooseNaN2_none_not_snan x y hnone
      split
      · split
        · split
          · exact hxy.1
          · exact R7W01.invalidResult32_not_snan
        · exact hxy.1
      · split
        · exact hxy.2
        · exact R7W01.invalidResult32_not_snan

/-- Every NaN arithmetic-add result is already quiet. -/
theorem model_add_isQNaN_eq_isNaN (x y : Model FloatFormat.binary32) :
    isQNaN (Spec.add x y) = isNaN (Spec.add x y) := by
  rw [isQNaN_eq_nan_and_not_signaling, model_add_not_snan]
  simp

/-- A right signaling NaN takes precedence whenever the left word is non-signaling.
The result is the actual right word quieted, with its complete sign and payload. -/
theorem model_add_of_right_snan (x y : Model FloatFormat.binary32)
    (hx : isSNaN x = false) (hy : isSNaN y = true) :
    Spec.add x y = quietNaN y := by
  have hny : isNaN y = true := isNaN_of_isSNaN hy
  have hdy : toDyadic? y = none := toDyadic?_eq_none_of_isNaN hny
  have hc : chooseNaN2 x y = some (quietNaN y) := by
    simp [chooseNaN2, hx, hy]
  cases hdx : toDyadic? x <;> simp [Spec.add, hdx, hdy, hc]

/-- The right-signaling branch concretely establishes the quiet invariant. -/
theorem model_add_of_right_snan_isQNaN (x y : Model FloatFormat.binary32)
    (hx : isSNaN x = false) (hy : isSNaN y = true) :
    isQNaN (Spec.add x y) = true := by
  rw [model_add_of_right_snan x y hx hy]
  exact R7W01.quietNaN32_is_qnan y (isNaN_of_isSNaN hy)

/-- Explicit stored-word version of the exact result, with no quotient of NaNs. -/
theorem model_add_of_right_snan_bits (x y : Model FloatFormat.binary32)
    (hx : isSNaN x = false) (hy : isSNaN y = true) :
    (Spec.add x y).bits = (quietNaN y).bits := by
  rw [model_add_of_right_snan x y hx hy]

end R7W03

/- Append after Dependencies.lean and ModelAdd.lean under only dependency ContractTensor.
   No quiet initial accumulator is required: ordinary +0 is concretely non-signaling. -/
namespace R7W03
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

/-- Exact transport of the actual addition's non-signaling output property. -/
theorem exec_add_not_snan (x y : Competition.Binary32) :
    Model.isSNaN (ExecFloat.Binary.toModel (ExecFloat.add x y)) = false := by
  exact (congrArg (fun m : Model FloatFormat.binary32 => Model.isSNaN m)
    (Submission.R7Native.toModelExecAdd x y)).trans
      (model_add_not_snan (ExecFloat.Binary.toModel x) (ExecFloat.Binary.toModel y))


end R7W03
