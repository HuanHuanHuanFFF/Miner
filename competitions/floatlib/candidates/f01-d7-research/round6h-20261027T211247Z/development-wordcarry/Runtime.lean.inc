/- Runtime only: pre-round leading bit, implicit-significand carry into exponent. -/
namespace Submission.R22WordCarry
open FloatLib.Floats Competition
@[inline] def normalCore (sum u v : UInt32) : UInt32 :=
  let a := (u &&& (0x7fffff : UInt32)) ||| (0x800000 : UInt32)
  let b := (v &&& (0x7fffff : UInt32)) ||| (0x800000 : UInt32)
  let p : UInt64 := a.toUInt64 * b.toUInt64
  let high := p >>> 47
  let biased := if p < (0x800000000000 : UInt64) then
      p + (0x3fffff : UInt64) + ((p >>> 23) &&& 1)
    else p + (0x7fffff : UInt64) + ((p >>> 24) &&& 1)
  let q := (biased >>> ((23 : UInt64) + high)).toUInt32
  let e := sum - (128 : UInt32) + high.toUInt32
  ((u ^^^ v) &&& (0x80000000 : UInt32)) ||| ((e <<< 23) + q)
@[inline] def guardedMul (x y : Binary32) : Binary32 :=
  let u := x.raw.1
  let v := y.raw.1
  let eu := (u >>> 23) &&& (255 : UInt32)
  let ev := (v >>> 23) &&& (255 : UInt32)
  if eu - 1 ≤ (253 : UInt32) ∧ ev - 1 ≤ (253 : UInt32) then
    let s := eu + ev
    if s - 128 ≤ (252 : UInt32) then R7W02.fromRaw (normalCore s u v)
    else R22OutlineMul.retainedMul x y
  else R22OutlineMul.retainedMul x y
end Submission.R22WordCarry
