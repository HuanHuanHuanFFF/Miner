/- Proof-only expected native readback word. NOT_RUN; no runtime integration.
   Requires exact622d and fb7d NativeTarget. No cross-width roundtrip assumption. -/
namespace Submission.R22ExpectedNativeWord
open FloatLib.Floats Competition

def expectedWord (u : UInt32) : UInt32 :=
  if R7W12.rawNotNaN u then u else (0x7fc00000 : UInt32)

/-- Closed pinned constant: canonicalNaN is expMask OR quietBit. -/
theorem canonical_nan_raw :
    (ExecFloat.Binary.ofFloat32 Float32.nan).raw.1 = (0x7fc00000 : UInt32) := by
  decide

theorem import_raw_eq_expected (x : Binary32) :
    (ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x)).raw.1 =
      expectedWord x.raw.1 := by
  cases hr : R7W12.rawNotNaN x.raw.1 with
  | false =>
    have hn : (ExecFloat.Binary.toFloat32 x).isNaN = true := by
      apply Bool.not_inj
      exact (R7W12.rawNotNaN_eq_native_classifier x).symm.trans hr
    rw [R7W05.native_eq_nan_of_isNaN _ hn, canonical_nan_raw]
    simp only [expectedWord, hr, Bool.false_eq_true, if_false]
  | true =>
    have hn : (ExecFloat.Binary.toFloat32 x).isNaN = false := by
      apply Bool.not_inj
      exact (R7W12.rawNotNaN_eq_native_classifier x).symm.trans hr
    rw [NotNaNProbe.roundtrip x hn]
    simp only [expectedWord, hr, ↓reduceIte]

/-- Same check result for every stored value, including a failed opaque cast. -/
theorem checkNative_eq_expected (x : Binary32) (stored : Float) :
    R22FloatArrayBridgeReview.checkNative (ExecFloat.Binary.toFloat32 x) stored =
      ((ExecFloat.Binary.ofFloat32 stored.toFloat32).raw.1 == expectedWord x.raw.1) := by
  simp only [R22FloatArrayBridgeReview.checkNative, import_raw_eq_expected]

end Submission.R22ExpectedNativeWord
