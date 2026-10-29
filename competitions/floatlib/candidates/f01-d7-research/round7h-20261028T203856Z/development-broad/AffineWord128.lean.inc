/- Old ContractTensor/B2 mathematical component. Accepted evaluation constructs
   the exact signed affine coefficient in words. No target kernel is changed.
   Public FixedWord APIs are from FloatLib0d918257. NOT_COMPILED. -/
namespace Submission.R24AffineWord128

open FloatLib.Numerics.FixedWord
open FloatLib.Floats.Formats.BinaryInterchange

structure CheckedProduct where
  value : UInt128
  valid : Bool

/-- Two full64-bit products suffice for128 by64 multiplication with a fit check. -/
@[inline] def multiply (value : UInt128) (factor : UInt64) : CheckedProduct :=
  let lower := mul64 value.lo factor
  let upper := mul64 value.hi factor
  let middle := add64 lower.hi upper.lo
  ⟨⟨middle.value, lower.lo⟩, upper.hi == 0 && middle.carry == 0⟩

theorem multiply_sound (value : UInt128) (factor : UInt64)
    (h : (multiply value factor).valid = true) :
    (multiply value factor).value.toNat = value.toNat * factor.toNat := by
  let lower := mul64 value.lo factor
  let upper := mul64 value.hi factor
  let middle := add64 lower.hi upper.lo
  have hh : upper.hi = 0 ∧ middle.carry = 0 := by
    simpa only [multiply, Bool.and_eq_true, beq_iff_eq] using h
  have hlo : lower.lo.toNat + lower.hi.toNat * 2 ^ 64 =
      value.lo.toNat * factor.toNat := mul64_toNat value.lo factor
  have hhi : upper.lo.toNat = value.hi.toNat * factor.toNat := by
    have hp := mul64_toNat value.hi factor
    change upper.lo.toNat + upper.hi.toNat * 2 ^ 64 = _ at hp
    simpa only [hh.1, UInt64.toNat_zero, zero_mul, add_zero] using hp
  have hmid : middle.value.toNat = lower.hi.toNat + upper.lo.toNat := by
    have hp := add64_toNat lower.hi upper.lo
    change middle.value.toNat + middle.carry.toNat * 2 ^ 64 = _ at hp
    simpa only [hh.2, UInt64.toNat_zero, zero_mul, add_zero] using hp
  change lower.lo.toNat + middle.value.toNat * 2 ^ 64 = _
  calc
    lower.lo.toNat + middle.value.toNat * 2 ^ 64 =
        (lower.lo.toNat + lower.hi.toNat * 2 ^ 64) + upper.lo.toNat * 2 ^ 64 := by
      rw [hmid]
      ring
    _ = value.lo.toNat * factor.toNat +
        (value.hi.toNat * factor.toNat) * 2 ^ 64 := by rw [hlo, hhi]
    _ = value.toNat * factor.toNat := by unfold UInt128.toNat; ring

structure CheckedSigned where
  negative : Bool
  magnitude : UInt128
  valid : Bool

def coefficient (negative : Bool) (magnitude : UInt128) : Int :=
  if negative then -(magnitude.toNat : Int) else magnitude.toNat

@[inline] def combine (leftNegative rightNegative : Bool)
    (left right : UInt128) : CheckedSigned :=
  if leftNegative == rightNegative then
    let sum := add128 left right
    ⟨leftNegative, sum.value, sum.carry == 0⟩
  else if UInt128.less left right then
    ⟨rightNegative, UInt128.sub right left, true⟩
  else
    ⟨leftNegative, UInt128.sub left right, true⟩

theorem combine_sound (leftNegative rightNegative : Bool) (left right : UInt128)
    (h : (combine leftNegative rightNegative left right).valid = true) :
    coefficient (combine leftNegative rightNegative left right).negative
        (combine leftNegative rightNegative left right).magnitude =
      coefficient leftNegative left + coefficient rightNegative right := by
  by_cases hs : leftNegative = rightNegative
  · have hcarry : (add128 left right).carry = 0 := by
      simpa only [combine, hs, beq_self_eq_true, if_true, beq_iff_eq] using h
    have hsum := add128_value_toNat_of_carry_zero left right hcarry
    have hsumI : ((add128 left right).value.toNat : Int) =
        (left.toNat : Int) + (right.toNat : Int) := by exact_mod_cast hsum
    subst rightNegative
    cases leftNegative
    · change ((add128 left right).value.toNat : Int) =
        (left.toNat : Int) + (right.toNat : Int)
      exact hsumI
    · change -((add128 left right).value.toNat : Int) =
        -(left.toNat : Int) + -(right.toNat : Int)
      rw [hsumI]
      ring
  · by_cases hl : UInt128.less left right = true
    · have hlt := UInt128.less_eq_true_iff.mp hl
      have hsub := UInt128.sub_toNat right left hlt.le
      have hsubI : ((UInt128.sub right left).toNat : Int) =
          (right.toNat : Int) - (left.toNat : Int) := by
        rw [hsub, Nat.cast_sub hlt.le]
      have hc : combine leftNegative rightNegative left right =
          ⟨rightNegative, UInt128.sub right left, true⟩ := by
        simp only [combine, beq_iff_eq, hs, if_false, hl, if_true]
      simp only [hc]
      change (if rightNegative then -((UInt128.sub right left).toNat : Int)
        else ((UInt128.sub right left).toNat : Int)) = _
      rw [hsubI]
      cases leftNegative <;> cases rightNegative <;>
        simp_all [coefficient] <;> omega
    · have hle : right.toNat ≤ left.toNat := by
        by_contra hn
        exact hl (UInt128.less_eq_true_iff.mpr (by omega))
      have hsub := UInt128.sub_toNat left right hle
      have hsubI : ((UInt128.sub left right).toNat : Int) =
          (left.toNat : Int) - (right.toNat : Int) := by
        rw [hsub, Nat.cast_sub hle]
      have hc : combine leftNegative rightNegative left right =
          ⟨leftNegative, UInt128.sub left right, true⟩ := by
        simp only [combine, beq_iff_eq, hs, if_false, hl, if_false]
      simp only [hc]
      change (if leftNegative then -((UInt128.sub left right).toNat : Int)
        else ((UInt128.sub left right).toNat : Int)) = _
      rw [hsubI]
      cases leftNegative <;> cases rightNegative <;>
        simp_all [coefficient] <;> omega

def affineCoefficient (leftNegative rightNegative : Bool)
    (left : UInt128) (factor : UInt64) (right : UInt128) : Int :=
  coefficient leftNegative left * (factor.toNat : Int) + coefficient rightNegative right

theorem affine_word_coefficient (leftNegative rightNegative : Bool)
    (left : UInt128) (factor : UInt64) (right : UInt128)
    (hp : (multiply left factor).valid = true)
    (hs : (combine leftNegative rightNegative (multiply left factor).value right).valid = true) :
    coefficient (combine leftNegative rightNegative (multiply left factor).value right).negative
        (combine leftNegative rightNegative (multiply left factor).value right).magnitude =
      affineCoefficient leftNegative rightNegative left factor right := by
  have hproduct := multiply_sound left factor hp
  have hproductI : ((multiply left factor).value.toNat : Int) =
      (left.toNat : Int) * (factor.toNat : Int) := by exact_mod_cast hproduct
  have hleft : coefficient leftNegative (multiply left factor).value =
      coefficient leftNegative left * (factor.toNat : Int) := by
    cases leftNegative <;> simp [coefficient, hproductI] <;> ring
  rw [combine_sound leftNegative rightNegative (multiply left factor).value right hs, hleft]
  rfl

theorem coefficient_sign_abs (negative : Bool) (magnitude : UInt128)
    (h : magnitude.toNat ≠ 0) :
    decide (coefficient negative magnitude < 0) = negative ∧
      (coefficient negative magnitude).natAbs = magnitude.toNat := by
  have hp : (0 : Int) < magnitude.toNat := by exact_mod_cast Nat.pos_of_ne_zero h
  cases negative <;> simp [coefficient, hp]

/-- Mathematical reference, deliberately constructed only in the fallback branch below. -/
def referenceRound (leftNegative rightNegative : Bool)
    (left : UInt128) (factor : UInt64) (right : UInt128)
    (den : UInt64) (exponent : Int) : UInt32 :=
  let exactCoefficient := affineCoefficient leftNegative rightNegative left factor right
  Model.NativeBinary32.roundRatScaled (decide (exactCoefficient < 0))
    exactCoefficient.natAbs den.toNat exponent

/-- Zero is a miss sentinel; accepted results have normal nonzero magnitude. -/
@[inline] def attempt (leftNegative rightNegative : Bool)
    (left : UInt128) (factor : UInt64) (right : UInt128)
    (den mant : UInt64) (exponent : Int) : UInt32 :=
  let product := multiply left factor
  let result := combine leftNegative rightNegative product.value right
  if product.valid && (result.valid &&
      Submission.R24WordGap128.normalCheck result.magnitude den mant exponent) then
    Model.NativeBinary32.mkBits result.negative (exponent + 150).toNat (mant.toNat - 8388608)
  else 0

theorem attempt_sound (leftNegative rightNegative : Bool)
    (left : UInt128) (factor : UInt64) (right : UInt128)
    (den mant : UInt64) (exponent : Int)
    (h : attempt leftNegative rightNegative left factor right den mant exponent ≠ 0) :
    attempt leftNegative rightNegative left factor right den mant exponent =
      referenceRound leftNegative rightNegative left factor right den exponent := by
  let product := multiply left factor
  let result := combine leftNegative rightNegative product.value right
  have hg : product.valid && (result.valid &&
      Submission.R24WordGap128.normalCheck result.magnitude den mant exponent) = true := by
    by_contra hn
    have hz : attempt leftNegative rightNegative left factor right den mant exponent = 0 := by
      simpa only [attempt, if_neg hn]
    exact h hz
  have hh : product.valid = true ∧ result.valid = true ∧
      Submission.R24WordGap128.normalCheck result.magnitude den mant exponent = true := by
    simpa only [Bool.and_eq_true] using hg
  have hcoefficient : coefficient result.negative result.magnitude =
      affineCoefficient leftNegative rightNegative left factor right :=
    affine_word_coefficient leftNegative rightNegative left factor right hh.1 hh.2.1
  have hbase : Submission.R24WordGap128.check result.magnitude den mant = true := by
    have hc := hh.2.2
    unfold Submission.R24WordGap128.normalCheck at hc
    exact (Bool.and_eq_true.mp hc).1
  obtain ⟨_, _, hl, _⟩ := Submission.R24WordGap128.check_midpoint_bounds
    result.magnitude den mant hbase
  have hn : result.magnitude.toNat ≠ 0 := by
    intro hz
    rw [hz] at hl
    omega
  have hcanonical := coefficient_sign_abs result.negative result.magnitude hn
  simp only [hcoefficient] at hcanonical
  have hround := Submission.R24WordGap128.normalCheck_sound result.negative
    result.magnitude den mant exponent hh.2.2
  have hattempt : attempt leftNegative rightNegative left factor right den mant exponent =
      Model.NativeBinary32.mkBits result.negative (exponent + 150).toNat
        (mant.toNat - 8388608) := by
    simp only [attempt, hg, if_true]
  rw [hattempt, referenceRound, hcanonical.1, hcanonical.2]
  exact hround.symm

/-- Whole generic operation: validation failure constructs the exact reference then. -/
@[inline] def roundWithFallback (leftNegative rightNegative : Bool)
    (left : UInt128) (factor : UInt64) (right : UInt128)
    (den mant : UInt64) (exponent : Int) : UInt32 :=
  let guess := attempt leftNegative rightNegative left factor right den mant exponent
  if guess == 0 then referenceRound leftNegative rightNegative left factor right den exponent
  else guess

theorem roundWithFallback_eq_reference (leftNegative rightNegative : Bool)
    (left : UInt128) (factor : UInt64) (right : UInt128)
    (den mant : UInt64) (exponent : Int) :
    roundWithFallback leftNegative rightNegative left factor right den mant exponent =
      referenceRound leftNegative rightNegative left factor right den exponent := by
  unfold roundWithFallback
  split
  · rfl
  · rename_i hzero
    have hn : attempt leftNegative rightNegative left factor right den mant exponent ≠ 0 := by
      simpa only [beq_iff_eq] using hzero
    exact attempt_sound leftNegative rightNegative left factor right den mant exponent hn

end Submission.R24AffineWord128
