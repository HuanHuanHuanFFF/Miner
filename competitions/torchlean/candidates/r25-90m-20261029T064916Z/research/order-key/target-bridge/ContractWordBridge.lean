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

def inputWords (n : Nat) (f : Nat → UInt32) : Array UInt32 :=
  Array.ofFn (n := n) fun i => f i.val

def inputModels (n : Nat) (f : Nat → UInt32) : Array (Model Fmt) :=
  (inputWords n f).map (Model.ofUInt32 (fmt := Fmt))

theorem inputModels_size (n : Nat) (f : Nat → UInt32) :
    (inputModels n f).size = n := by
  simp [inputModels, inputWords]

def actualDotExact (n : Nat) (fa fb : Nat → UInt32) : Dyadic :=
  (Model.Reduction.Internal.dotState (inputModels n fa) (inputModels n fb)
    (by rw [inputModels_size, inputModels_size]) : Model.Reduction.Internal.State Fmt).exact

theorem dotOf_of_native_nonzero
    (n : Nat) (fa fb : Nat → UInt32) (q : UInt32)
    (ha : ∀ k (hk : k < (inputModels n fa).size),
      Model.isFinite (inputModels n fa)[k] = true)
    (hb : ∀ k (hk : k < (inputModels n fb).size),
      Model.isFinite (inputModels n fb)[k] = true)
    (hnz : Model.Reduction.Semantics.finiteDot
      (inputModels n fa).toList (inputModels n fb).toList ≠ .ok 0)
    (hq : Model.NativeBinary32.roundDyadic (actualDotExact n fa fb) = q) :
    dotOf n fa fb = q := by
  have hsize : (inputModels n fa).size = (inputModels n fb).size := by
    rw [inputModels_size, inputModels_size]
  change dotSpec (inputWords n fa) (inputWords n fb) = q
  unfold dotSpec
  change (match Model.dot Fmt (inputModels n fa) (inputModels n fb) .nearestEven with
    | .ok z => toWord z
    | .error _ => 0) = q
  unfold Model.dot
  rw [Model.Reduction.dotWithStatus_eq_round_of_finite_nonzero Fmt
    (inputModels n fa) (inputModels n fb) .nearestEven hsize ha hb hnz]
  simp only [Except.map]
  exact native_dyadic_result (actualDotExact n fa fb) q hq

end Submission.R25ContractWordBridge

