namespace Submission.R22SubnormalColdAdd
open FloatLib.Floats Competition

@[inline] def words (u v : UInt32) : UInt32 :=
  let a := u &&& 0x7fffff
  let b := v &&& 0x7fffff
  let s := u &&& 0x80000000
  if ((u ^^^ v) &&& 0x80000000) == 0 then s ||| (a+b)
  else if a == b then 0
  else if b < a then s ||| (a-b)
  else (v &&& 0x80000000) ||| (b-a)

@[noinline] def miss (x y : Binary32) : Binary32 :=
  let u := x.raw.1
  let v := y.raw.1
  if ((u ||| v) &&& 0x7f800000) == 0 then FastMul.ofBits (words u v)
  else R22NativeColdAdd.coldAdd x y

@[inline] def diagnosticEntry (x y : Binary32) : Binary32 :=
  if R2W01b.fastOK x.raw.1 && R2W01b.fastOK y.raw.1 then
    ExecFloat.Binary.ofFloat32 (R2W01b.tableProduct x.raw.1 + R2W01b.tableProduct y.raw.1)
  else miss x y

end Submission.R22SubnormalColdAdd
