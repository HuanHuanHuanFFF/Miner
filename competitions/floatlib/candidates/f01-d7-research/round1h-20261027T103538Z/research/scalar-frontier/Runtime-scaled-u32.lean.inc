namespace Submission.R21ScaledU32
open Competition

/-- Exact 2^-23. The real once/load/initialization cost must be inspected. -/
def powNeg23 : Float32 := Float32.ofBits (0x34000000 : UInt32)

@[inline] def normalCore (sum u v : UInt32) : UInt32 :=
  let scale := powNeg23
  let a := (u &&& (0x7fffff : UInt32)) ||| (0x800000 : UInt32)
  let b := (v &&& (0x7fffff : UInt32)) ||| (0x800000 : UInt32)
  let p : UInt64 := a.toUInt64 * b.toUInt64
  let z : UInt32 := (p.toFloat32 * scale).toUInt32
  let high := z >>> 24
  let q := z >>> high
  let e := sum - (127 : UInt32) + high
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

@[noinline] def diagnosticEntry (x y : Binary32) : Binary32 :=
  guardedMul Submission.mul x y
end Submission.R21ScaledU32
