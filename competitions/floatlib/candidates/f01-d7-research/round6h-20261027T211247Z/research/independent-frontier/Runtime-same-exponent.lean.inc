
/- R22 independent scalar cost discriminator. New runtime equivalence NOT_PROVED.
   The four original public entries/specs stay exactly B2. No native replacement. -/
namespace Submission.R22SameExponent
open FloatLib.Floats Competition

@[inline] def eligible (u v : UInt32) : Bool :=
  decide ((u ^^^ v) < (0x00800000 : UInt32)) &&
    ((u &&& 0x7f800000) != (0x7f800000 : UInt32))

@[inline] def core (u v : UInt32) : UInt32 :=
  let t := (u &&& 0x007fffff) + (v &&& 0x007fffff)
  let e := u &&& 0x7f800000
  let s := u &&& 0x80000000
  if e == 0 then s ||| t
  else if e == (0x7f000000 : UInt32) then s ||| 0x7f800000
  else s ||| (e + 0x00800000 + ((t + ((t >>> 1) &&& 1)) >>> 1))

@[inline] def diagnosticEntry (x y : Binary32) : Binary32 :=
  if eligible x.raw.1 y.raw.1 then FastMul.ofBits (core x.raw.1 y.raw.1)
  else Submission.add x y

end Submission.R22SameExponent
