import ContractTensor

namespace R2W01c

open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

theorem uint32_model_eq_roundDyadic (n : UInt32) :
    Model.ofFloat32Model n.toFloat32.toModel =
      Model.roundDyadic FloatFormat.binary32
        { negative := false, significand := n.toNat, exponent := 0 } := by
  change Model.ofFloat32Model
      (Float32.Model.pack
        (Float.Model.UnpackedFloat.ofUInt32 Float.Model.Format.binary32 n)) = _
  rw [Model.ofFloat32Model_pack]
  change Model.ofModel FloatFormat.binary32
      (Float.Model.UnpackedFloat.ofInt FloatFormat.binary32.toModel
        (n.toNat : Int)) = _
  simpa [Dyadic.ofScaledInt] using
    Model.ofModel_ofInt_eq_roundDyadic FloatFormat.binary32
      (by decide) (n.toNat : Int)

theorem uint32_model_eq_of_decode (n : UInt32)
    (z : Model FloatFormat.binary32)
    (hz : Model.toDyadic? z =
      some { negative := false, significand := n.toNat, exponent := 0 }) :
    Model.ofFloat32Model n.toFloat32.toModel = z := by
  rw [uint32_model_eq_roundDyadic]
  change Model.roundDyadicWithRounding FloatFormat.binary32 .nearestEven
    { negative := false, significand := n.toNat, exponent := 0 } = z
  exact Model.roundDyadicWithRounding_toDyadic? (by decide) .nearestEven hz

theorem fields32_toDyadic (s : Bool) (e f : Nat)
    (he0 : 0 < e) (he : e < 255) (hf : f < 8388608) :
    Model.toDyadic? (Model.ofFields FloatFormat.binary32 s e f) =
      some { negative := s, significand := 8388608 + f,
        exponent := (e : Int) - 150 } := by
  have h := Model.toDyadic?_ofFields_normal FloatFormat.binary32 s e f
    (Nat.ne_of_gt he0) he hf
  change Model.toDyadic? (Model.ofFields FloatFormat.binary32 s e f) =
    some { negative := s, significand := 8388608 + f,
      exponent := (e : Int) - 127 - 23 } at h
  have hexp : (e : Int) - 127 - 23 = (e : Int) - 150 := by omega
  simpa only [hexp] using h

theorem uint32_mantissa_model_eq_fields (n : UInt32)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat < 16777216) :
    Model.ofFloat32Model n.toFloat32.toModel =
      Model.ofFields FloatFormat.binary32 false 150 (n.toNat - 8388608) := by
  apply uint32_model_eq_of_decode
  have hf : n.toNat - 8388608 < 8388608 := by omega
  have hsum : 8388608 + (n.toNat - 8388608) = n.toNat := by omega
  simpa only [hsum] using
    fields32_toDyadic false 150 (n.toNat - 8388608) (by decide) (by decide) hf

theorem uint32_mantissa_model_decode (n : UInt32)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat < 16777216) :
    Model.toDyadic? (Model.ofFloat32Model n.toFloat32.toModel) =
      some { negative := false, significand := n.toNat, exponent := 0 } := by
  rw [uint32_mantissa_model_eq_fields n hlo hhi]
  have hf : n.toNat - 8388608 < 8388608 := by omega
  have hsum : 8388608 + (n.toNat - 8388608) = n.toNat := by omega
  simpa only [hsum] using
    fields32_toDyadic false 150 (n.toNat - 8388608) (by decide) (by decide) hf

theorem uint32_mantissa_model_finite (n : UInt32)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat < 16777216) :
    Model.isFinite (Model.ofFloat32Model n.toFloat32.toModel) = true := by
  exact Model.isFinite_eq_true_of_toDyadic?_some
    (uint32_mantissa_model_decode n hlo hhi)

theorem uint32_mantissa_model_toReal (n : UInt32)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat < 16777216) :
    Model.toReal (Model.ofFloat32Model n.toFloat32.toModel) = (n.toNat : Real) := by
  rw [Model.toReal_eq, uint32_mantissa_model_decode n hlo hhi]
  simp [Dyadic.toReal, Dyadic.signedSignificand]

end R2W01c
