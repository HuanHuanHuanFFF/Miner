namespace Submission.R17NumericMulInteger
open FloatLib.Floats Competition

@[inline] def normalCore (sum u v : UInt32) : UInt32 :=
  let a := (u &&& (0x7fffff : UInt32)) ||| (0x800000 : UInt32)
  let b := (v &&& (0x7fffff : UInt32)) ||| (0x800000 : UInt32)
  let product : UInt64 := a.toUInt64 * b.toUInt64
  let r : UInt64 := product.toFloat32.toUInt64
  let high : UInt64 := if (0x800000000000 : UInt64) ≤ r then 1 else 0
  let q : UInt32 := (r >>> ((23 : UInt64) + high)).toUInt32
  let e : UInt32 := sum - (127 : UInt32) + high.toUInt32
  ((u ^^^ v) &&& (0x80000000 : UInt32)) ||| (e <<< 23) ||| (q - (0x800000 : UInt32))

@[inline] def guardedMul (fallback : Binary32 → Binary32 → Binary32)
    (x y : Binary32) : Binary32 :=
  let u := x.raw.1
  let v := y.raw.1
  let eu := (u >>> 23) &&& (255 : UInt32)
  let ev := (v >>> 23) &&& (255 : UInt32)
  if eu - 1 ≤ (253 : UInt32) ∧ ev - 1 ≤ (253 : UInt32) then
    let s := eu + ev
    if s - 128 ≤ (252 : UInt32) then R7W02.fromRaw (normalCore s u v)
    else fallback x y
  else fallback x y

end Submission.R17NumericMulInteger
