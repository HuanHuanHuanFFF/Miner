/- R22 cost discriminator only. New semantic proof NOT_RUN. -/
namespace Submission.R22BroadWordAdd
open FloatLib.Floats Competition

@[inline] def core (hi lo eh d : UInt32) : UInt32 :=
  if d >= (25 : UInt32) then hi else
  let a := ((hi &&& (0x7fffff : UInt32)) ||| (0x800000 : UInt32)) <<< (3 : UInt32)
  let b := ((lo &&& (0x7fffff : UInt32)) ||| (0x800000 : UInt32)) <<< (3 : UInt32)
  let mask := ((1 : UInt32) <<< d) - (1 : UInt32)
  let sticky := if (b &&& mask) == (0 : UInt32) then (0 : UInt32) else (1 : UInt32)
  let t := a + ((b >>> d) ||| sticky)
  let carry := t >>> (27 : UInt32)
  let t := if carry == (0 : UInt32) then t else (t >>> (1 : UInt32)) ||| (t &&& (1 : UInt32))
  let e := eh + carry
  let s := hi &&& (0x80000000 : UInt32)
  if e >= (255 : UInt32) then s ||| (0x7f800000 : UInt32) else
  let m := (t + (3 : UInt32) + ((t >>> (3 : UInt32)) &&& (1 : UInt32))) >>> (3 : UInt32)
  s ||| (((e - (1 : UInt32)) <<< (23 : UInt32)) + m)

@[inline] def diagnosticEntry (x y : Binary32) : Binary32 :=
  let u := x.raw.1
  let v := y.raw.1
  let eu := (u >>> (23 : UInt32)) &&& (255 : UInt32)
  let ev := (v >>> (23 : UInt32)) &&& (255 : UInt32)
  if decide ((u ^^^ v) < (0x80000000 : UInt32)) &&
      decide (eu - (1 : UInt32) < (254 : UInt32)) &&
      decide (ev - (1 : UInt32) < (254 : UInt32)) then
    FastMul.ofBits (if eu < ev then core v u ev (ev - eu) else core u v eu (eu - ev))
  else Submission.add x y

end Submission.R22BroadWordAdd
