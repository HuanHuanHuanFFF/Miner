/- NOT_RUN. Append after frozen R19DirectBias and R22OutlineMul diagnostics.
   Only a cold-layer experiment; no new public MUL theorem. -/
namespace Submission.R22ExtremeColdMul
open FloatLib.Floats Competition

@[noinline] def coldMul (x y : Binary32) : Binary32 :=
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
  else R22OutlineMul.retainedMul x y

@[inline] def diagnosticEntry (x y : Binary32) : Binary32 :=
  R19DirectBias.guardedMul coldMul x y

end Submission.R22ExtremeColdMul
