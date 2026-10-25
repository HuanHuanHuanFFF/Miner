/- R14 runtime component only, NOT_COMPILED.
   Domain deliberately excludes opposite-sign exponent gaps0/1, so there is
   no deep-cancellation leading-zero search or subnormal result in the fast arm.
   Requires the existing R14BiasRNE runtime and native word helpers.
   A complete add_spec is still pending; this file is not a candidate package. -/
namespace Submission.R14WordAdd

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

@[inline] def high (u v : UInt32) : UInt32 :=
  if R14ExponentShift.ex u < R14ExponentShift.ex v then v else u

@[inline] def low (u v : UInt32) : UInt32 :=
  if R14ExponentShift.ex u < R14ExponentShift.ex v then u else v

@[inline] def gap (u v : UInt32) : UInt32 :=
  R14ExponentShift.ex (high u v) - R14ExponentShift.ex (low u v)

@[inline] def sameSign (u v : UInt32) : Bool :=
  (u ^^^ v) >>> 31 == (0 : UInt32)

@[inline] def eligible (u v : UInt32) : Bool :=
  (decide (R14ExponentShift.ex u - 1 ≤ (253 : UInt32)) &&
    decide (R14ExponentShift.ex v - 1 ≤ (253 : UInt32))) &&
  (decide (gap u v ≤ (7 : UInt32)) && (sameSign u v || decide ((2 : UInt32) ≤ gap u v)))

@[inline] def magnitudeWord (u v : UInt32) : UInt32 :=
  let left := R2W01b.mantissa (high u v) <<< gap u v
  let right := R2W01b.mantissa (low u v)
  if sameSign u v then left + right else left - right

@[inline] def leadingWord (u v : UInt32) : UInt32 :=
  let base := (if sameSign u v then (23 : UInt32) else 22) + gap u v
  base + (magnitudeWord u v >>> (base + 1))

@[inline] def roundedWord (u v : UInt32) : UInt64 :=
  R14BiasRNE.biased (magnitudeWord u v).toUInt64 ((leadingWord u v - 23).toUInt64)

@[inline] def exponentWord (u v : UInt32) : UInt32 :=
  leadingWord u v + R14ExponentShift.ex (low u v) - 23 + (roundedWord u v >>> 24).toUInt32

@[inline] def fractionWord (u v : UInt32) : UInt32 :=
  (roundedWord u v).toUInt32 &&& (0x007fffff : UInt32)

@[inline] def core (u v : UInt32) : UInt32 :=
  FastMul.mkW (decide ((2147483648 : UInt32) ≤ high u v))
    (exponentWord u v) (fractionWord u v)

@[inline] def guardedAdd (fallback : Binary32 → Binary32 → Binary32)
    (x y : Binary32) : Binary32 :=
  let u := x.raw.1
  let v := y.raw.1
  if eligible u v then
    let hi := high u v
    let lo := low u v
    let d := R14ExponentShift.ex hi - R14ExponentShift.ex lo
    let same := sameSign u v
    let left := R2W01b.mantissa hi <<< d
    let right := R2W01b.mantissa lo
    let n := if same then left + right else left - right
    let base := (if same then (23 : UInt32) else 22) + d
    let h := base + (n >>> (base + 1))
    let q := R14BiasRNE.biased n.toUInt64 ((h - 23).toUInt64)
    let e := h + R14ExponentShift.ex lo - 23 + (q >>> 24).toUInt32
    if e - 1 ≤ (253 : UInt32) then
      R7W02.fromRaw (FastMul.mkW (decide ((2147483648 : UInt32) ≤ hi))
        e (q.toUInt32 &&& (0x007fffff : UInt32)))
    else fallback x y
  else fallback x y

theorem guardedAdd_of_ineligible (fallback : Binary32 → Binary32 → Binary32)
    (x y : Binary32) (h : eligible x.raw.1 y.raw.1 = false) :
    guardedAdd fallback x y = fallback x y := by
  simp [guardedAdd, h]

theorem guardedAdd_of_normal (fallback : Binary32 → Binary32 → Binary32)
    (x y : Binary32) (h : eligible x.raw.1 y.raw.1 = true)
    (he : exponentWord x.raw.1 y.raw.1 - 1 ≤ (253 : UInt32)) :
    guardedAdd fallback x y = R7W02.fromRaw (core x.raw.1 y.raw.1) := by
  unfold guardedAdd
  simp only [h, ↓reduceIte]
  change (if exponentWord x.raw.1 y.raw.1 - 1 ≤ (253 : UInt32) then
    R7W02.fromRaw (core x.raw.1 y.raw.1) else fallback x y) = _
  rw [if_pos he]

end Submission.R14WordAdd
