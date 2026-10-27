/- Draft / NOT_RUN. Prerequisites: retained df5c/compact-base,
   compiled R14NativeProduct.model_mul_of_nonzero_decodes (native-product2),
   and D's R14DIntegerRound.int64_model_eq_roundDyadic draft a3cf0a4d.
   Exact Lean4 293d5d0c SInt.Lemmas provides the cast lemmas below.
   No standalone candidate/CI request and no performance assertion. -/
namespace Submission.R14IntegerProductSubstitution

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

theorem uint64_toInt64_toInt_of_lt (n : UInt64) (hn : n.toNat < 2 ^ 63) :
    n.toInt64.toInt = (n.toNat : Int) := by
  have h : (UInt64.ofNat n.toNat).toInt64.toInt = (n.toNat : Int) := by
    simpa only [UInt64.toInt64_ofNat'] using (Int64.toInt_ofNat_of_lt hn)
  simpa only [UInt64.ofNat_toNat] using h

theorem uint64_signed_model_round (n : UInt64) (hn : n.toNat < 2 ^ 63) :
    R2W01c.nativeModel n.toInt64.toFloat32 =
      Model.roundDyadic FloatFormat.binary32
        (⟨false, n.toNat, 0⟩ : FloatLib.Numerics.Dyadic) := by
  change Model.ofFloat32Model n.toInt64.toFloat32.toModel = _
  have hm := R14DIntegerRound.int64_model_eq_roundDyadic n.toInt64
  have hcast := uint64_toInt64_toInt_of_lt n hn
  have hnonnegative : ¬ (n.toNat : Int) < 0 := by omega
  simpa [hcast, FloatLib.Numerics.Dyadic.ofScaledInt, hnonnegative] using hm

/-- Drop-in equality of the two actually evaluated Float32 intermediates.
It does not say the 48-bit product is represented exactly in Float32. -/
theorem integer_product_eq_native (a b : UInt32)
    (ha : 8388608 ≤ a.toNat) (ha' : a.toNat < 16777216)
    (hb : 8388608 ≤ b.toNat) (hb' : b.toNat < 16777216) :
    (a.toUInt64 * b.toUInt64).toInt64.toFloat32 = a.toFloat32 * b.toFloat32 := by
  have hbound := Nat.mul_le_mul (Nat.le_of_lt ha') (Nat.le_of_lt hb')
  have hfit : a.toNat * b.toNat < 9223372036854775808 := by
    norm_num at hbound
    omega
  have hp : (a.toUInt64 * b.toUInt64).toNat = a.toNat * b.toNat := by
    rw [UInt64.toNat_mul, UInt32.toNat_toUInt64, UInt32.toNat_toUInt64]
    exact Nat.mod_eq_of_lt (by omega)
  have hcast : (a.toUInt64 * b.toUInt64).toNat < 2 ^ 63 := by
    change (a.toUInt64 * b.toUInt64).toNat < 9223372036854775808
    rw [hp]
    exact hfit
  have hxa := R2W01c.uint32_mantissa_model_decode a ha ha'
  have hxb := R2W01c.uint32_mantissa_model_decode b hb hb'
  apply R2W01c.native_eq_of_model_eq
  rw [uint64_signed_model_round _ hcast, hp]
  change Model.roundDyadic FloatFormat.binary32
      (⟨false, a.toNat * b.toNat, 0⟩ : FloatLib.Numerics.Dyadic) =
    ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat32 (a.toFloat32 * b.toFloat32))
  rw [R2W01c.NativeBridge.toModelNativeMul a.toFloat32 b.toFloat32
    (R2W01c.nativeFinite_of_decode _ hxa) (R2W01c.nativeFinite_of_decode _ hxb)]
  have hm := R14NativeProduct.model_mul_of_nonzero_decodes
    (R2W01c.nativeModel a.toFloat32) (R2W01c.nativeModel b.toFloat32)
    ⟨false, a.toNat, 0⟩ ⟨false, b.toNat, 0⟩ hxa hxb (by omega) (by omega)
  simpa only [Bool.false_xor, Int.zero_add] using hm.symm

end Submission.R14IntegerProductSubstitution
