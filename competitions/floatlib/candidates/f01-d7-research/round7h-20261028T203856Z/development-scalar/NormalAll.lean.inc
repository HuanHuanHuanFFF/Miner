/- Research draft only: all normal input pairs, without widening old normalCore.
   New low and overflow branches have NO Lean proof or measured cost. -/
namespace R24ScalarNormalAll
open Competition
@[inline] def bits (s u v : UInt32) : UInt32 :=
  let sign := (u ^^^ v) &&& (0x80000000 : UInt32)
  if s < 103 then sign
  else if s > 381 then sign ||| 0x7f800000
  else
    let a := (u &&& 0x7fffff) ||| (0x800000 : UInt32)
    let b := (v &&& 0x7fffff) ||| (0x800000 : UInt32)
    let p : UInt64 := a.toUInt64 * b.toUInt64
    if s < 128 then
      let d := (151-s).toUInt64
      let q := (p + (((1 : UInt64) <<< (d-1))-1) + ((p >>> d) &&& 1)) >>> d
      sign ||| q.toUInt32
    else
      let biased := if p < (0x800000000000 : UInt64) then
          p + (0x3fffff : UInt64) + ((p >>> 23) &&& 1)
        else p + (0x7fffff : UInt64) + ((p >>> 24) &&& 1)
      let high := biased >>> 47
      let e := s-127+high.toUInt32
      if e >= 255 then sign ||| 0x7f800000
      else
        let q := (biased >>> ((23 : UInt64)+high)).toUInt32
        sign ||| (e <<< 23) ||| (q-0x800000)
@[inline] def guarded (fallback : Binary32 → Binary32 → Binary32)
    (x y : Binary32) : Binary32 :=
  let u := x.raw.1
  let v := y.raw.1
  let eu := (u >>> 23) &&& (255 : UInt32)
  let ev := (v >>> 23) &&& (255 : UInt32)
  if eu-1 <= (253 : UInt32) ∧ ev-1 <= (253 : UInt32) then
    R7W02.fromRaw (bits (eu+ev) u v)
  else fallback x y
end R24ScalarNormalAll
