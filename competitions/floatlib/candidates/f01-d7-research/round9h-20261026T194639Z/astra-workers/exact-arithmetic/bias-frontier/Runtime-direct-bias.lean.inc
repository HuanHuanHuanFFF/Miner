namespace Submission.R19DirectBias
open Competition

/-- Existing ties-to-even bias formula; new retained-product caller shape.
    No change to normal/S128..380 domain or fallback. NOT_COMPILED. -/
@[inline] def normalCore (sum u v : UInt32) : UInt32 :=
  let a := (u &&& (0x7fffff : UInt32)) ||| (0x800000 : UInt32)
  let b := (v &&& (0x7fffff : UInt32)) ||| (0x800000 : UInt32)
  let p : UInt64 := a.toUInt64 * b.toUInt64
  let biased := if p < (0x800000000000 : UInt64) then
      p + (0x3fffff : UInt64) + ((p >>> 23) &&& 1)
    else p + (0x7fffff : UInt64) + ((p >>> 24) &&& 1)
  let high := biased >>> 47
  let q := (biased >>> ((23 : UInt64) + high)).toUInt32
  let e := sum - (127 : UInt32) + high.toUInt32
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
end Submission.R19DirectBias
