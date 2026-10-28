namespace Submission.R22NativeProductScale
open FloatLib.Floats Competition

@[inline] def normalCore (s u v : UInt32) : Binary32 :=
  let a := (u &&& (0x7fffff : UInt32)) ||| (0x800000 : UInt32)
  let b := (v &&& (0x7fffff : UInt32)) ||| (0x800000 : UInt32)
  let p : UInt64 := a.toUInt64*b.toUInt64
  let w := ((s-(150 : UInt32)) <<< (23 : UInt32)) ||| ((u ^^^ v) &&& (0x80000000 : UInt32))
  ExecFloat.Binary.ofFloat32 (p.toFloat32*R2W01b.scaleAt w)

@[inline] def guardedMul (fallback : Binary32 → Binary32 → Binary32)
    (x y : Binary32) : Binary32 :=
  let u := x.raw.1
  let v := y.raw.1
  let eu := (u >>> (23 : UInt32)) &&& (255 : UInt32)
  let ev := (v >>> (23 : UInt32)) &&& (255 : UInt32)
  if eu-(1 : UInt32) ≤ (253 : UInt32) ∧ ev-(1 : UInt32) ≤ (253 : UInt32) then
    let s := eu+ev
    if s-(174 : UInt32) ≤ (206 : UInt32) then normalCore s u v else fallback x y
  else fallback x y

@[noinline] def diagnosticEntry (x y : Binary32) : Binary32 := guardedMul Submission.mul x y
end Submission.R22NativeProductScale
