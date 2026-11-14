namespace Submission.R25ContractWordBridge
open ExactRuntime FloatLib.Numerics
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

theorem finishWord_of_native_denOne_result
    (sign : Bool) (num : Nat) (source T e : Int) (negZero : Bool) (q : UInt32)
    (hT : T ≠ 0)
    (hd : (Dyadic.mk sign num source).toRat = (T : Rat) * 2 ^ e)
    (hq : Model.NativeBinary32.roundRatScaled sign num 1 source = q) :
    finishWord T e negZero = q := by
  have hround : Model.NativeBinary32.roundDyadic ⟨sign, num, source⟩ = q := by
    rw [R24DyadicAgreement.roundDyadic_eq_roundRatScaled]
    exact hq
  exact finishWord_of_native_result ⟨sign, num, source⟩ T e negZero q hT hd hround

end Submission.R25ContractWordBridge

