/- Check expression only; exact equivalence to fb7d is conditional on 37cd typing.
   No additional raw decode, no assumption that the opaque roundtrip passes. -/
namespace Submission.R22ExpectedB2Check
open FloatLib.Floats Competition

@[inline] def check (raw : Binary32) (stored : Float) : Bool :=
  (ExecFloat.Binary.ofFloat32 stored.toFloat32).raw.1 ==
    R22ExpectedNativeWord.expectedWord raw.raw.1

theorem check_eq_native (raw : Binary32) (stored : Float) :
    check raw stored =
      R22FloatArrayBridgeReview.checkNative (ExecFloat.Binary.toFloat32 raw) stored :=
  (R22ExpectedNativeWord.checkNative_eq_expected raw stored).symm

end Submission.R22ExpectedB2Check
