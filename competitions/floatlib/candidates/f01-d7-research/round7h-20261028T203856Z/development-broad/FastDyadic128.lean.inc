/-
Copyright (c)2026 FloatLib; original comparator definitions by FloatLib Team.
Released under MIT license, as in the original source.
Adapted from FloatLib/Kernels/FixedWord/DyadicCompare/Runtime.lean at0d918257,
blob37eb178cdeb85584cb892d10b97ecfc624f00a90. Changes substitute B2's
proved six-stage FastMul.fastLog2; public comparison semantics are retained.
-/
namespace Submission.R24FastDyadic128
open FloatLib.Numerics FloatLib.Numerics.FixedWord
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

@[inline] def shiftFitsFast (significand : UInt64) (shift : Nat) : Prop :=
  significand = 0 ∨ (Submission.FastMul.fastLog2 significand).toNat + shift < 64

instance (significand : UInt64) (shift : Nat) : Decidable (shiftFitsFast significand shift) := by
  unfold shiftFitsFast
  infer_instance

theorem shiftFitsFast_eq (significand : UInt64) (shift : Nat) :
    shiftFitsFast significand shift = DyadicCompare.shiftFits significand shift := by
  simp only [shiftFitsFast, DyadicCompare.shiftFits, Submission.FastMul.fastLog2_eq]

@[inline] def compareWord
    (leftSignificand : UInt64) (leftExponent : Int)
    (rightSignificand : UInt64) (rightExponent : Int) : Ordering :=
  if leftSignificand == 0 && rightSignificand == 0 then
    .eq
  else if leftExponent ≤ rightExponent then
    let shift := Int.toNat (rightExponent - leftExponent)
    if _hshift : shift < 64 then
      if _hfit : shiftFitsFast rightSignificand shift then
        Ord.compare leftSignificand
          (rightSignificand <<< UInt64.ofNat shift)
      else
        Dyadic.compareNonnegativeFields
          leftSignificand.toNat leftExponent
          rightSignificand.toNat rightExponent
    else
      Dyadic.compareNonnegativeFields
        leftSignificand.toNat leftExponent
        rightSignificand.toNat rightExponent
  else
    let shift := Int.toNat (leftExponent - rightExponent)
    if _hshift : shift < 64 then
      if _hfit : shiftFitsFast leftSignificand shift then
        Ord.compare
          (leftSignificand <<< UInt64.ofNat shift)
          rightSignificand
      else
        Dyadic.compareNonnegativeFields
          leftSignificand.toNat leftExponent
          rightSignificand.toNat rightExponent
    else
      Dyadic.compareNonnegativeFields
        leftSignificand.toNat leftExponent
        rightSignificand.toNat rightExponent

@[inline] def compareWide
    (leftSignificand : UInt128) (leftExponent : Int)
    (rightSignificand : UInt64) (rightExponent : Int) : Ordering :=
  if leftSignificand.hi == 0 then
    compareWord leftSignificand.lo leftExponent
      rightSignificand rightExponent
  else if rightSignificand == 0 then
    .gt
  else if leftExponent ≤ rightExponent then
    let shift := Int.toNat (rightExponent - leftExponent)
    if _hshift : shift < 128 then
      if _hfit : (Submission.FastMul.fastLog2 rightSignificand).toNat + shift < 128 then
        UInt128.compare leftSignificand
          (UInt128.shiftLeft { hi := 0, lo := rightSignificand } shift)
      else
        .lt
    else
      .lt
  else
    .gt

theorem compareWord_eq (left : UInt64) (source : Int) (right : UInt64) (target : Int) :
    compareWord left source right target = DyadicCompare.compareNonnegative left source right target := by
  simp only [compareWord, DyadicCompare.compareNonnegative, shiftFitsFast_eq]

theorem compareWide_eq (left : UInt128) (source : Int) (right : UInt64) (target : Int) :
    compareWide left source right target = DyadicCompare.compareNonnegative128ToWord left source right target := by
  simp only [compareWide, DyadicCompare.compareNonnegative128ToWord, compareWord_eq,
    Submission.FastMul.fastLog2_eq]

@[inline] def fastAllowedFast (num : UInt128) (source : Int) (word : UInt64) (target : Int) : Bool :=
  if num.hi != 0 then true
  else if source ≤ target then
    let shift := (target - source).toNat
    decide (shift < 64) && decide (shiftFitsFast word shift)
  else
    let shift := (source - target).toNat
    decide (shift < 64) && decide (shiftFitsFast num.lo shift)

theorem fastAllowedFast_eq (num : UInt128) (source : Int) (word : UInt64) (target : Int) :
    fastAllowedFast num source word target = Submission.R24ScaledWord128.fastAllowed num source word target := by
  simp only [fastAllowedFast, Submission.R24ScaledWord128.fastAllowed, shiftFitsFast_eq]

@[inline] def checkFast (num : UInt128) (den mant : UInt64) (source target : Int) : Bool :=
  if (0 : UInt64) < den ∧ den < 274877906944 ∧ 8388608 < mant ∧ mant < 16777216 ∧
      1 ≤ target + 150 ∧ target + 150 ≤ 254 then
    let bounds := Submission.R24ScaledWord128.midpointWords den mant
    if fastAllowedFast num (source + 1) bounds.1 target && fastAllowedFast num (source + 1) bounds.2 target then
      compareWide num (source + 1) bounds.1 target == .gt &&
        compareWide num (source + 1) bounds.2 target == .lt
    else false
  else false

theorem checkFast_eq (num : UInt128) (den mant : UInt64) (source target : Int) :
    checkFast num den mant source target = Submission.R24ScaledWord128.check num den mant source target := by
  simp only [checkFast, Submission.R24ScaledWord128.check, fastAllowedFast_eq, compareWide_eq]

theorem checkFast_sound (sign : Bool) (num : UInt128) (den mant : UInt64) (source target : Int)
    (h : checkFast num den mant source target = true) :
    Model.NativeBinary32.roundRatScaled sign num.toNat den.toNat source =
      Model.NativeBinary32.mkBits sign (target + 150).toNat (mant.toNat - 8388608) := by
  apply Submission.R24ScaledWord128.check_sound sign num den mant source target
  simpa only [checkFast_eq] using h

end Submission.R24FastDyadic128
