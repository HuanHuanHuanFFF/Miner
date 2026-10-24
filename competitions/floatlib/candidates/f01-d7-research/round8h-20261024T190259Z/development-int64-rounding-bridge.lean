/- Development R14 diagnostic fragment. Fixed FloatLib Team / MIT APIs;
   Lean FRO / Apache2 definitions are referenced, not reimplemented.
   NOT_COMPILED: this fragment is not a candidate or acceptance receipt. -/
namespace Submission.R14DIntegerRound

open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

theorem uint64_model_eq_roundDyadic (n : UInt64) :
    Model.ofFloat32Model n.toFloat32.toModel =
      Model.roundDyadic FloatFormat.binary32
        { negative := false, significand := n.toNat, exponent := 0 } := by
  change Model.ofFloat32Model
      (Float32.Model.pack
        (Float.Model.UnpackedFloat.ofUInt64 Float.Model.Format.binary32 n)) = _
  rw [Model.ofFloat32Model_pack]
  change Model.ofModel FloatFormat.binary32
      (Float.Model.UnpackedFloat.ofInt FloatFormat.binary32.toModel
        (n.toNat : Int)) = _
  have hn : ¬ (n.toNat : Int) < 0 := by omega
  simpa [FloatLib.Numerics.Dyadic.ofScaledInt, hn] using
    Model.ofModel_ofInt_eq_roundDyadic FloatFormat.binary32
      (by decide) (n.toNat : Int)

theorem int64_model_eq_roundDyadic (n : Int64) :
    Model.ofFloat32Model n.toFloat32.toModel =
      Model.roundDyadic FloatFormat.binary32
        (FloatLib.Numerics.Dyadic.ofScaledInt n.toInt 0) := by
  change Model.ofFloat32Model
      (Float32.Model.pack
        (Float.Model.UnpackedFloat.ofInt64 Float.Model.Format.binary32 n)) = _
  rw [Model.ofFloat32Model_pack]
  change Model.ofModel FloatFormat.binary32
      (Float.Model.UnpackedFloat.ofInt FloatFormat.binary32.toModel n.toInt) = _
  exact Model.ofModel_ofInt_eq_roundDyadic FloatFormat.binary32
    (by decide) n.toInt

theorem uint64_toInt64_toInt (n : UInt64) (hn : n.toNat < 2 ^ 63) :
    n.toInt64.toInt = (n.toNat : Int) := by
  change n.toBitVec.toInt = (n.toBitVec.toNat : Int)
  apply BitVec.toInt_eq_toNat_of_lt
  change 2 * n.toNat < 18446744073709551616
  have hlimit : n.toNat < 9223372036854775808 := hn
  omega

theorem low_int64_model_eq_roundDyadic (n : UInt64) (hn : n.toNat < 2 ^ 63) :
    Model.ofFloat32Model n.toInt64.toFloat32.toModel =
      Model.roundDyadic FloatFormat.binary32
        { negative := false, significand := n.toNat, exponent := 0 } := by
  rw [int64_model_eq_roundDyadic, uint64_toInt64_toInt n hn]
  have hnonnegative : ¬ (n.toNat : Int) < 0 := by omega
  simp [FloatLib.Numerics.Dyadic.ofScaledInt, hnonnegative]

theorem low_casts_eq (n : UInt64) (hn : n.toNat < 2 ^ 63) :
    n.toInt64.toFloat32 = n.toFloat32 := by
  apply R2W01c.native_eq_of_model_eq
  change Model.ofFloat32Model n.toInt64.toFloat32.toModel =
    Model.ofFloat32Model n.toFloat32.toModel
  rw [low_int64_model_eq_roundDyadic n hn, uint64_model_eq_roundDyadic]

end Submission.R14DIntegerRound
