namespace Submission.R21ScaledU32
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

/-- Actual UInt64 word product, without modular wrap, feeds the native cast. -/
theorem native_integer_product_decode (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    Model.toDyadic? (R2W01c.nativeModel (a.toUInt64*b.toUInt64).toFloat32) =
      some ⟨false,R14NatNormal.mantissa (R14ExponentShift.product a b),
        (R17UInt64Integer.roundedShift (R14ExponentShift.product a b) : Int)⟩ := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  have hw := R17UInt64Integer.product_word_nat a b ha0 ha hb0 hb
  have hd := R17UInt64Integer.native_uint64_decode (a.toUInt64*b.toUInt64)
    (by rw [hw]; exact hp.1) (by rw [hw]; exact hp.2)
  simpa only [hw] using hd

/-- Closes the R21 conditional scaled field interface for the runtime product.
    Still not a public guarded multiplication specification. -/
theorem integer_product_scaled_fields (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    let p := R14ExponentShift.product a b
    let z := ((a.toUInt64*b.toUInt64).toFloat32*powNeg23).toUInt32
    (z >>> 24).toNat = R17UInt64Integer.roundedShift p-23 ∧
      (z >>> (z >>> 24)).toNat = R14NatNormal.mantissa p := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  have hm := R14NatNormal.mantissa_bounds (R14ExponentShift.product a b)
    hp.1 (by omega)
  exact scaled_fields (a.toUInt64*b.toUInt64).toFloat32 _ _ hm.1 hm.2
    (R17UInt64Integer.rounded_shift_cases _ hp.1 hp.2)
    (native_integer_product_decode a b ha0 ha hb0 hb)

end Submission.R21ScaledU32
