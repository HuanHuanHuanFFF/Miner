/- NOT_RUN. Frozen native pair/hot definitions reused; only the miss target changes. -/
namespace Submission.R22ExtremeNativeCold
open FloatLib.Floats Competition

@[noinline] def endpointMiss (x y : Binary32) : Binary32 :=
  let u := x.raw.1
  let v := y.raw.1
  let ex := (u >>> (23 : UInt32)) &&& (255 : UInt32)
  let ey := (v >>> (23 : UInt32)) &&& (255 : UInt32)
  let s := ex + ey
  let sign := (u ^^^ v) &&& (0x80000000 : UInt32)
  if s <= (102 : UInt32) then FastMul.ofBits sign
  else if decide ((382 : UInt32) <= s) &&
      decide (ex < (255 : UInt32)) && decide (ey < (255 : UInt32)) then
    FastMul.ofBits (sign ||| (0x7f800000 : UInt32))
  else R22NativeCold.retainedMul x y

@[inline] def diagnosticEntry (x y : Binary32) : Binary32 :=
  if R22NativeCold.pairOK x.raw.1 y.raw.1 then R22NativeCold.hotMul x y
  else endpointMiss x y

end Submission.R22ExtremeNativeCold
