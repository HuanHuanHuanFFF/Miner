namespace Submission.R22ProductCast
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

/-- Alternative same-width route: both sides round the exact integer product
    once to Float32. No Float64 intermediate or cross-width cast axiom. -/
theorem native_product_eq_uint64_cast (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    a.toFloat32*b.toFloat32 = (a.toUInt64*b.toUInt64).toFloat32 := by
  have hda := R2W01c.uint32_mantissa_model_decode a ha0 ha
  have hdb := R2W01c.uint32_mantissa_model_decode b hb0 hb
  have hm : Model.mul (R2W01c.nativeModel a.toFloat32) (R2W01c.nativeModel b.toFloat32) =
      Model.roundDyadic FloatFormat.binary32
        ⟨false,R14ExponentShift.product a b,0⟩ := by
    rw [Model.Proof.mul_eq_spec]
    unfold Model.Spec.mul
    rw [hda,hdb]
    simp [show a.toNat ≠ 0 by omega,show b.toNat ≠ 0 by omega,R14ExponentShift.product]
  have hn := R2W01c.NativeBridge.toModelNativeMul a.toFloat32 b.toFloat32
    (R2W01c.nativeFinite_of_decode _ hda) (R2W01c.nativeFinite_of_decode _ hdb)
  have hw := R17UInt64Integer.product_word_nat a b ha0 ha hb0 hb
  apply R2W01c.native_eq_of_model_eq
  calc
    R2W01c.nativeModel (a.toFloat32*b.toFloat32) =
        Model.mul (R2W01c.nativeModel a.toFloat32) (R2W01c.nativeModel b.toFloat32) := by
      simpa only [ExecFloat.Binary.toModel_ofFloat32] using hn
    _ = Model.roundDyadic FloatFormat.binary32 ⟨false,R14ExponentShift.product a b,0⟩ := hm
    _ = R2W01c.nativeModel (a.toUInt64*b.toUInt64).toFloat32 := by
      rw [R17UInt64Integer.uint64_model_eq_roundDyadic,hw]

/-- Any continuation may consume the same native Float32 value. This is useful
    for a future implementation comparison, but includes no runtime cost claim. -/
theorem replace_native_product {α : Sort _} (k : Float32 → α) (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    k (a.toFloat32*b.toFloat32) = k (a.toUInt64*b.toUInt64).toFloat32 := by
  rw [native_product_eq_uint64_cast a b ha0 ha hb0 hb]

end Submission.R22ProductCast
