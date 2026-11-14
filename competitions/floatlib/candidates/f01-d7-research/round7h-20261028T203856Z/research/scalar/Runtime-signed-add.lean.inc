/- R24 diagnostic. Original two's-complement alignment implementation.
   Int64 conversion references Lean FRO Apache2 definitions; no new extern/axiom.
   All-input proof and native cost NOT_RUN. Original public endpoints stay B2. -/
namespace Submission.R24SignedAdd
open FloatLib.Floats Competition

@[inline] def signedMantissa (u : UInt32) : UInt64 :=
  let m := ((u &&& 0x7fffff) ||| 0x800000).toUInt64
  let mask := (0 : UInt64) - (u >>> 31).toUInt64
  (m ^^^ mask) - mask

@[inline] def aligned (hi lo elo gap : UInt32) : UInt32 :=
  let n := (signedMantissa hi <<< gap.toUInt64) + signedMantissa lo
  if n == 0 then 0 else
  n.toInt64.toFloat32.toBits + ((elo - 150) <<< 23)

@[noinline] def cold (x y : Binary32) : Binary32 := Submission.add x y

@[inline] def diagnosticEntry (x y : Binary32) : Binary32 :=
  let u := x.raw.1
  let v := y.raw.1
  let eu := (u >>> 23) &&& 255
  let ev := (v >>> 23) &&& 255
  if decide (eu - 24 ≤ (228 : UInt32)) && decide (ev - 24 ≤ (228 : UInt32)) then
    if eu < ev then
      let gap := ev - eu
      if gap ≤ 38 then FastMul.ofBits (aligned v u eu gap) else cold x y
    else
      let gap := eu - ev
      if gap ≤ 38 then FastMul.ofBits (aligned u v ev gap) else cold x y
  else cold x y

end Submission.R24SignedAdd
