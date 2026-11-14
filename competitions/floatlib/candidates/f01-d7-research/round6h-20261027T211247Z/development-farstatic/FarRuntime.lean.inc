/- R22 complete guarded cost probe; new ADD proof NOT_RUN. -/
namespace Submission.R22FarOnlyAdd
open FloatLib.Floats Competition

@[noinline] def coldAdd (x y : Binary32) : Binary32 := Submission.add x y

@[inline] def diagnosticEntry (x y : Binary32) : Binary32 :=
  let u := x.raw.1
  let v := y.raw.1
  let a := u &&& (0x7fffffff : UInt32)
  let b := v &&& (0x7fffffff : UInt32)
  let swap := decide (a < b)
  let hi := if swap then v else u
  let hiAbs := if swap then b else a
  let loAbs := if swap then a else b
  if decide (hiAbs < (0x7f800000 : UInt32)) &&
      decide (hiAbs - loAbs >= ((26 : UInt32) <<< (23 : UInt32))) then
    FastMul.ofBits hi
  else coldAdd x y

end Submission.R22FarOnlyAdd
