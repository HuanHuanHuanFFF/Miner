/- R17 runtime fragment. Fixed-environment elaboration and correctness checks are pending. -/
namespace Submission.R17NumericAdd

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

@[inline] def sortedAdd
    (fallback : Binary32 → Binary32 → Binary32) (x y : Binary32)
    (hi lo ehi elo : UInt32) : Binary32 :=
  let d := ehi - elo
  let highSign := decide ((0x80000000 : UInt32) ≤ hi)
  let lowSign := decide ((0x80000000 : UInt32) ≤ lo)
  let same := highSign == lowSign
  let adjust : UInt32 := if same then 0 else 1
  if decide (d ≤ (7 : UInt32)) && decide (adjust ≤ d) then
    let ma := R2W01b.mantissa hi
    let mb := R2W01b.mantissa lo
    let left := ma <<< d
    let n := if same then left + mb else left - mb
    if (8388608 : UInt32) ≤ n then
      let r := n.toFloat32.toUInt32
      let baseShift := d - adjust
      let threshold := (1 : UInt32) <<< (baseShift + 24)
      let bump : UInt32 := if threshold ≤ r then 1 else 0
      let shift := baseShift + bump
      let e := (ehi - adjust) + bump
      if e ≤ (254 : UInt32) then
        R7W02.fromRaw (FastMul.mkW highSign e (r >>> shift))
      else fallback x y
    else fallback x y
  else fallback x y

@[inline] def guardedAdd
    (fallback : Binary32 → Binary32 → Binary32) (x y : Binary32) : Binary32 :=
  let u := x.raw.1
  let v := y.raw.1
  let eu := Model.NativeBinary32.expField u
  let ev := Model.NativeBinary32.expField v
  if decide (eu - 1 ≤ (253 : UInt32)) && decide (ev - 1 ≤ (253 : UInt32)) then
    if eu < ev then
      sortedAdd fallback x y v u ev eu
    else
      sortedAdd fallback x y u v eu ev
  else fallback x y

end Submission.R17NumericAdd
