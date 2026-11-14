namespace Submission.R14ExponentShift
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
@[inline] def ex (u : UInt32) : UInt32 := Model.NativeBinary32.expField u

@[inline] def sign (u v : UInt32) : Bool :=
  Bool.xor (decide ((2147483648 : UInt32) ≤ u)) (decide ((2147483648 : UInt32) ≤ v))
end Submission.R14ExponentShift

namespace Submission.R14DIntegerNormal
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
@[inline] def productWord (u v : UInt32) : UInt64 :=
  (R2W01b.mantissa u).toUInt64 * (R2W01b.mantissa v).toUInt64

@[inline] def highWord (u v : UInt32) : UInt64 := productWord u v >>> 47

@[inline] def shiftWord (u v : UInt32) : UInt64 := 23 + highWord u v

@[inline] def roundedWord (u v : UInt32) : UInt64 :=
  FastMul.rseAny (productWord u v) (shiftWord u v)

@[inline] def carryWord (u v : UInt32) : UInt64 := roundedWord u v >>> 24

@[inline] def exponentWord (u v : UInt32) : UInt32 :=
  R14ExponentShift.ex u + R14ExponentShift.ex v - 127 +
    (highWord u v).toUInt32 + (carryWord u v).toUInt32

@[inline] def fractionWord (u v : UInt32) : UInt32 :=
  (roundedWord u v).toUInt32 &&& 0x007fffff

@[inline] def core (u v : UInt32) : UInt32 :=
  FastMul.mkW (R14ExponentShift.sign u v) (exponentWord u v) (fractionWord u v)
end Submission.R14DIntegerNormal

namespace Submission.R14ExponentShift
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
@[inline] def core (u v : UInt32) : UInt32 := R14DIntegerNormal.core u v

@[inline] def eligible (u v : UInt32) : Bool :=
  (decide (ex u - 1 ≤ 253) && decide (ex v - 1 ≤ 253)) &&
    decide (ex u + ex v - 128 ≤ 252)

@[inline] def guardedMul (fallback : Binary32 → Binary32 → Binary32)
    (x y : Binary32) : Binary32 :=
  if eligible x.raw.1 y.raw.1 then R7W02.fromRaw (core x.raw.1 y.raw.1)
  else fallback x y
end Submission.R14ExponentShift

namespace Submission.R22RseCold
open Competition
@[noinline] def retainedB2 (x y : Binary32) : Binary32 := Submission.mul x y
@[inline] def inlineOld (x y : Binary32) : Binary32 :=
  R14ExponentShift.guardedMul Submission.mul x y
@[inline] def outlined (x y : Binary32) : Binary32 :=
  R14ExponentShift.guardedMul retainedB2 x y
end Submission.R22RseCold
