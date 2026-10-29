import ContractExact

namespace Submission.R25ContractWordBridge
open ExactRuntime FloatLib.Numerics
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

theorem toWord_native32 (w : UInt32) :
    toWord (Model.NativeBinary32.ofUInt32 w) = w := by
  change UInt32.ofNat w.toNat = w
  exact UInt32.ofNat_toNat

theorem native_dyadic_word (d : Dyadic) :
    toWord (Model.roundDyadic Fmt d) = Model.NativeBinary32.roundDyadic d := by
  change toWord (Model.roundDyadic FloatFormat.binary32 d) = _
  rw [← Model.NativeBinary32.ofUInt32_roundDyadic, toWord_native32]

theorem native_ratScaled_word (sign : Bool) (num den : Nat) (e : Int) :
    toWord (Model.roundRatScaled Fmt sign num den e) =
      Model.NativeBinary32.roundRatScaled sign num den e := by
  change toWord (Model.roundRatScaled FloatFormat.binary32 sign num den e) = _
  rw [← Model.NativeBinary32.ofUInt32_roundRatScaled, toWord_native32]

theorem native_dyadic_result (d : Dyadic) (q : UInt32)
    (hq : Model.NativeBinary32.roundDyadic d = q) :
    toWord (Model.roundDyadic Fmt d) = q := by
  rw [native_dyadic_word, hq]

theorem native_ratScaled_result (sign : Bool) (num den : Nat) (e : Int) (q : UInt32)
    (hq : Model.NativeBinary32.roundRatScaled sign num den e = q) :
    toWord (Model.roundRatScaled Fmt sign num den e) = q := by
  rw [native_ratScaled_word, hq]

theorem finishWord_of_native_result (d : Dyadic) (T e : Int) (negZero : Bool)
    (q : UInt32) (hT : T ≠ 0)
    (hd : d.toRat = (T : Rat) * 2 ^ e)
    (hq : Model.NativeBinary32.roundDyadic d = q) :
    finishWord T e negZero = q := by
  rw [finishWord_of_ne d T e negZero hT hd]
  exact native_dyadic_result d q hq

theorem finishWord_of_native_real_result (d : Dyadic) (T e : Int) (negZero : Bool)
    (q : UInt32) (hT : T ≠ 0)
    (hd : d.toReal = (T : Real) * (2 : Real) ^ e)
    (hq : Model.NativeBinary32.roundDyadic d = q) :
    finishWord T e negZero = q := by
  have hr : d.toRat = (T : Rat) * 2 ^ e := by
    rw [← Dyadic.cast_toRat] at hd
    exact_mod_cast hd
  exact finishWord_of_native_result d T e negZero q hT hr hq

theorem finishWord_exact_zero (e : Int) (negZero : Bool) :
    finishWord 0 e negZero = if negZero then 0x80000000 else 0 := rfl

theorem finishWord_exact_zero_native (e : Int) (negZero : Bool) :
    finishWord 0 e negZero =
      Model.NativeBinary32.roundDyadic ⟨negZero, 0, e⟩ := by
  cases negZero <;> rfl

theorem zero_sign_cannot_be_erased (e : Int) :
    finishWord 0 e true ≠ Model.NativeBinary32.roundDyadic (ofIntDyadic 0 e) := by
  change (0x80000000 : UInt32) ≠ 0
  decide

end Submission.R25ContractWordBridge
