/- Concrete fixed-word check with independent source/candidate exponents.
   No normalized denominator is constructed by this runtime. NOT_COMPILED. -/
namespace Submission.R24ScaledWord128

open FloatLib.Numerics FloatLib.Numerics.FixedWord
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

@[inline] def fastAllowed (num : UInt128) (source : Int) (word : UInt64) (target : Int) : Bool :=
  if num.hi != 0 then true
  else if source ≤ target then
    let shift := (target - source).toNat
    decide (shift < 64) && decide (DyadicCompare.shiftFits word shift)
  else
    let shift := (source - target).toNat
    decide (shift < 64) && decide (DyadicCompare.shiftFits num.lo shift)

@[inline] def midpointWords (den mant : UInt64) : UInt64 × UInt64 :=
  let twice := den * (mant + mant)
  (twice - den, twice + den)

theorem midpointWords_exact (den mant : UInt64)
    (hdcap : den.toNat < 274877906944)
    (hmlo : 8388608 < mant.toNat) (hmhi : mant.toNat < 16777216) :
    (midpointWords den mant).1.toNat = den.toNat * (2 * mant.toNat - 1) ∧
      (midpointWords den mant).2.toNat = den.toNat * (2 * mant.toNat + 1) := by
  have htwiceFit : mant.toNat + mant.toNat < UInt64.size := by
    change mant.toNat + mant.toNat < 18446744073709551616
    omega
  have htwice : (mant + mant).toNat = 2 * mant.toNat := by
    rw [UInt64.toNat_add, Nat.mod_eq_of_lt htwiceFit]
    omega
  have hbound : den.toNat * (2 * mant.toNat + 1) < 9223372036854775808 := by
    calc
      den.toNat * (2 * mant.toNat + 1) < 274877906944 * 33554432 :=
        Nat.mul_lt_mul'' hdcap (by omega)
      _ = 9223372036854775808 := by decide
  have hmidFit : den.toNat * (2 * mant.toNat) < UInt64.size := by
    change den.toNat * (2 * mant.toNat) < 18446744073709551616
    nlinarith
  have hmid : (den * (mant + mant)).toNat = den.toNat * (2 * mant.toNat) := by
    rw [UInt64.toNat_mul, htwice, Nat.mod_eq_of_lt hmidFit]
  have hle : den ≤ den * (mant + mant) := by
    apply UInt64.le_iff_toNat_le.mpr
    rw [hmid]
    nlinarith
  have hupperFit : (den * (mant + mant)).toNat + den.toNat < UInt64.size := by
    rw [hmid]
    change den.toNat * (2 * mant.toNat) + den.toNat < 18446744073709551616
    nlinarith
  have hcut : 2 * mant.toNat - 1 + 1 = 2 * mant.toNat := by omega
  have hcutD : den.toNat * (2 * mant.toNat - 1) + den.toNat =
      den.toNat * (2 * mant.toNat) := by
    calc
      den.toNat * (2 * mant.toNat - 1) + den.toNat =
          den.toNat * ((2 * mant.toNat - 1) + 1) := by ring
      _ = _ := by rw [hcut]
  constructor
  · change (den * (mant + mant) - den).toNat = _
    rw [UInt64.toNat_sub_of_le _ _ hle, hmid]
    omega
  · change (den * (mant + mant) + den).toNat = _
    rw [UInt64.toNat_add, Nat.mod_eq_of_lt hupperFit, hmid]
    ring

theorem compare_lt (num : UInt128) (source : Int) (word : UInt64) (target : Int)
    (h : DyadicCompare.compareNonnegative128ToWord num source word target = .lt) :
    (num.toNat : Real) * Model.bpow source < (word.toNat : Real) * Model.bpow target := by
  rw [DyadicCompare.compareNonnegative128ToWord_eq,
    Dyadic.compareNonnegativeFields_eq_compareFields, Dyadic.compareFields_eq] at h
  let left : Dyadic := ⟨false, num.toNat, source⟩
  let right : Dyadic := ⟨false, word.toNat, target⟩
  change left.compare right = .lt at h
  have hr := (Dyadic.compare_eq_lt_iff left right).mp h
  have hrR : (left.toRat : Real) < (right.toRat : Real) := by exact_mod_cast hr
  simpa [left, right, Dyadic.toRat, Dyadic.signedSignificand, Model.bpow,
    FloatLib.Floats.Formats.Flocq.bpow, binaryRadix, Radix.toReal] using hrR

theorem compare_gt (num : UInt128) (source : Int) (word : UInt64) (target : Int)
    (h : DyadicCompare.compareNonnegative128ToWord num source word target = .gt) :
    (word.toNat : Real) * Model.bpow target < (num.toNat : Real) * Model.bpow source := by
  rw [DyadicCompare.compareNonnegative128ToWord_eq,
    Dyadic.compareNonnegativeFields_eq_compareFields, Dyadic.compareFields_eq] at h
  let left : Dyadic := ⟨false, num.toNat, source⟩
  let right : Dyadic := ⟨false, word.toNat, target⟩
  change left.compare right = .gt at h
  have hr := (Dyadic.compare_eq_gt_iff left right).mp h
  have hrR : (right.toRat : Real) < (left.toRat : Real) := by exact_mod_cast hr
  simpa [left, right, Dyadic.toRat, Dyadic.signedSignificand, Model.bpow,
    FloatLib.Floats.Formats.Flocq.bpow, binaryRadix, Radix.toReal] using hrR

@[inline] def check (num : UInt128) (den mant : UInt64) (source target : Int) : Bool :=
  if (0 : UInt64) < den ∧ den < 274877906944 ∧ 8388608 < mant ∧ mant < 16777216 ∧
      1 ≤ target + 150 ∧ target + 150 ≤ 254 then
    let bounds := midpointWords den mant
    if fastAllowed num (source + 1) bounds.1 target && fastAllowed num (source + 1) bounds.2 target then
      DyadicCompare.compareNonnegative128ToWord num (source + 1) bounds.1 target == .gt &&
        DyadicCompare.compareNonnegative128ToWord num (source + 1) bounds.2 target == .lt
    else false
  else false

theorem check_sound (sign : Bool) (num : UInt128) (den mant : UInt64) (source target : Int)
    (h : check num den mant source target = true) :
    Model.NativeBinary32.roundRatScaled sign num.toNat den.toNat source =
      Model.NativeBinary32.mkBits sign (target + 150).toNat (mant.toNat - 8388608) := by
  have hfit : (0 : UInt64) < den ∧ den < 274877906944 ∧ 8388608 < mant ∧ mant < 16777216 ∧
      1 ≤ target + 150 ∧ target + 150 ≤ 254 := by
    by_contra hn
    simp only [check, if_neg hn] at h
    contradiction
  have hd : 0 < den.toNat := UInt64.lt_iff_toNat_lt.mp hfit.1
  have hdcap : den.toNat < 274877906944 := UInt64.lt_iff_toNat_lt.mp hfit.2.1
  have hmlo : 8388608 < mant.toNat := UInt64.lt_iff_toNat_lt.mp hfit.2.2.1
  have hmhi : mant.toNat < 16777216 := UInt64.lt_iff_toNat_lt.mp hfit.2.2.2.1
  let bounds := midpointWords den mant
  have hcmp : DyadicCompare.compareNonnegative128ToWord num (source + 1) bounds.1 target = .gt ∧
      DyadicCompare.compareNonnegative128ToWord num (source + 1) bounds.2 target = .lt := by
    unfold check at h
    simp only [if_pos hfit] at h
    split at h
    · simpa only [Bool.and_eq_true, beq_iff_eq] using h
    · simp at h
  have hl := compare_gt num (source + 1) bounds.1 target hcmp.1
  have hu := compare_lt num (source + 1) bounds.2 target hcmp.2
  obtain ⟨hbl, hbu⟩ := midpointWords_exact den mant hdcap hmlo hmhi
  have hpower : (num.toNat : Real) * Model.bpow (source + 1) =
      2 * (num.toNat : Real) * Model.bpow source := by
    rw [Model.bpow_add, Model.bpow_one]
    ring
  apply Submission.R24ScaledCell.native32_scaled_strict sign num.toNat den.toNat mant.toNat
    source target hd hmlo hmhi hfit.2.2.2.2.1 hfit.2.2.2.2.2
  · simpa only [bounds, hbl, Nat.cast_mul, hpower] using hl
  · simpa only [bounds, hbu, Nat.cast_mul, hpower] using hu

end Submission.R24ScaledWord128
