namespace Submission.R25ContractWordBridge
open ExactRuntime FloatLib.Numerics
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

def actualDotZeroSign (n : Nat) (fa fb : Nat → UInt32) : Bool :=
  let st : Model.Reduction.Internal.State Fmt :=
    Model.Reduction.Internal.dotState (inputModels n fa) (inputModels n fb)
      (by rw [inputModels_size, inputModels_size])
  st.sawFiniteTerm && st.allTermsNegativeZero

theorem dotOf_actual_zero
    (n : Nat) (fa fb : Nat → UInt32)
    (ha : ∀ k (hk : k < (inputModels n fa).size),
      Model.isFinite (inputModels n fa)[k] = true)
    (hb : ∀ k (hk : k < (inputModels n fb).size),
      Model.isFinite (inputModels n fb)[k] = true)
    (hz : (actualDotExact n fa fb).significand = 0) :
    dotOf n fa fb = finishWord 0 (-298) (actualDotZeroSign n fa fb) := by
  have hsize : (inputModels n fa).size = (inputModels n fb).size := by
    rw [inputModels_size, inputModels_size]
  change dotSpec (inputWords n fa) (inputWords n fb) = _
  unfold dotSpec
  change (match Model.dot Fmt (inputModels n fa) (inputModels n fb) .nearestEven with
    | .ok z => toWord z
    | .error _ => 0) = _
  unfold Model.dot
  rw [Model.Reduction.dotWithStatus_eq_zero_of_finite Fmt
    (inputModels n fa) (inputModels n fb) .nearestEven hsize ha hb hz]
  simpa [Except.map, actualDotZeroSign] using
    (finishWord_zero (-298) (actualDotZeroSign n fa fb)).symm

end Submission.R25ContractWordBridge

