import ContractExact

/- ExactRuntime finite dot integer totals have the fixed scale2^-298.
This root targets that scale directly; it is not the actual caller theorem. -/
namespace Submission.R27FixedScaleCell
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

theorem quotient_strict_midpoint (num den mant : Nat)
    (hd : 0 < den) (hm : 0 < mant)
    (hl : den * (2 * mant - 1) < 2 * num)
    (hu : 2 * num < den * (2 * mant + 1)) :
    FloatLib.Numerics.roundQuotientEven num den = mant := by
  cases mant with
  | zero => omega
  | succ k =>
    have hleft : 2 * (k + 1) - 1 = 2 * k + 1 := by omega
    have hright : 2 * (k + 1) + 1 = 2 * k + 3 := by omega
    rw [hleft] at hl
    rw [hright] at hu
    have hlo : k * den ≤ num := by nlinarith
    have hhi : num < (k + 2) * den := by nlinarith
    have hql : k ≤ num / den := (Nat.le_div_iff_mul_le hd).2 hlo
    have hqu : num / den < k + 2 := (Nat.div_lt_iff_lt_mul hd).2 hhi
    have hdiv := Nat.mod_add_div num den
    have hcases : num / den = k ∨ num / den = k + 1 := by omega
    rcases hcases with hq | hq
    · have hr : den < 2 * (num % den) := by rw [hq] at hdiv; nlinarith
      have hn : ¬ 2 * (num % den) < den := by omega
      simp [FloatLib.Numerics.roundQuotientEven, hq, hn, hr]
    · have hr : 2 * (num % den) < den := by rw [hq] at hdiv; nlinarith
      simp [FloatLib.Numerics.roundQuotientEven, hq, hr]


theorem normal_ratio_nat_bounds (num den mant : Nat)
    (hd : 0 < den) (hmlo : 8388608 < mant) (hmhi : mant < 16777216)
    (hl : den * (2 * mant - 1) < 2 * num)
    (hu : 2 * num < den * (2 * mant + 1)) :
    8388608 * den ≤ num ∧ num < 16777216 * den := by
  have hmlo' : 8388609 ≤ mant := by omega
  have hmhi' : mant ≤ 16777215 := by omega
  have hscaleL := Nat.mul_le_mul_right den hmlo'
  have hscaleU := Nat.mul_le_mul_right den hmhi'
  have hcut : 2 * mant - 1 + 1 = 2 * mant := by omega
  have hexpand : den * (2 * mant - 1) + den = 2 * (mant * den) := by
    calc
      den * (2 * mant - 1) + den = den * ((2 * mant - 1) + 1) := by ring
      _ = den * (2 * mant) := by rw [hcut]
      _ = 2 * (mant * den) := by ring
  constructor <;> nlinarith



/-- Interior normal non-power cell at the official dot's fixed integer scale.
No general dyadic/rational rescaling bridge is needed for this statement. -/
theorem native32_fixed298_strict (sign : Bool) (num E mant : Nat)
    (hElo : 2 ≤ E) (hEhi : E ≤ 253)
    (hmlo : 8388608 < mant) (hmhi : mant < 16777216)
    (hl : 2 ^ (E + 148) * (2 * mant - 1) < 2 * num)
    (hu : 2 * num < 2 ^ (E + 148) * (2 * mant + 1)) :
    Model.NativeBinary32.roundDyadic ⟨sign, num, -298⟩ =
      Model.NativeBinary32.mkBits sign E (mant - 8388608) := by
  have hd : 0 < 2 ^ (E + 148) := Nat.two_pow_pos _
  obtain ⟨hlo, hhi⟩ := normal_ratio_nat_bounds num (2 ^ (E + 148)) mant
    hd hmlo hmhi hl hu
  have hn : num ≠ 0 := by omega
  have hlog : num.log2 = E + 171 := by
    rw [Nat.log2_eq_iff hn]
    constructor
    · rw [show E + 171 = 23 + (E + 148) by omega, Nat.pow_add]
      change 8388608 * 2 ^ (E + 148) ≤ num
      exact hlo
    · rw [show E + 171 + 1 = 24 + (E + 148) by omega, Nat.pow_add]
      change num < 16777216 * 2 ^ (E + 148)
      exact hhi
  have hr : roundShiftRightEven num (E + 148) = mant := by
    rw [roundShiftRightEven_eq_roundQuotientEven]
    exact quotient_strict_midpoint num (2 ^ (E + 148)) mant hd (by omega) hl hu
  have htotal : ((E + 171 : Nat) : Int) + (-298) = (E : Int) - 127 := by omega
  have hsub : ¬ (E : Int) - 127 < -126 := by omega
  have hlead : 23 ≤ E + 171 := by omega
  have hshift : E + 171 - 23 = E + 148 := by omega
  have hcarry : mant ≠ Model.pow2 24 := by change mant ≠ 16777216; omega
  have hbig : ¬ (E : Int) - 127 > 127 := by omega
  have hencoded : ((E : Int) - 127 + 127).toNat = E := by omega
  simp only [Model.NativeBinary32.roundDyadic, beq_iff_eq, hn, ite_false,
    hlog, htotal, hsub, hlead, ite_true, hshift, hr, hcarry, hbig,
    hencoded, show Model.pow2 23 = 8388608 by decide]

end Submission.R27FixedScaleCell


namespace Submission.R27FixedScaleCell
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics ExactRuntime

/-- Convert a strict symmetric real cell into the exact natural cross products.
The positive fixed scale cancels, without any floating endpoint assumption. -/
theorem real_cell_to_nat_cross (num E mant : Nat) (hm : 0 < mant)
    (hl : ((mant : Real) - (1 : Real) / 2) * (2 : Real) ^ ((E : Int) - 150) <
      (num : Real) * (2 : Real) ^ (-298 : Int))
    (hu : (num : Real) * (2 : Real) ^ (-298 : Int) <
      ((mant : Real) + (1 : Real) / 2) * (2 : Real) ^ ((E : Int) - 150)) :
    2 ^ (E + 148) * (2 * mant - 1) < 2 * num ∧
      2 * num < 2 ^ (E + 148) * (2 * mant + 1) := by
  have hs : 0 < (2 : Real) ^ (-298 : Int) := zpow_pos (by norm_num) _
  have hp : (2 : Real) ^ ((E : Int) - 150) =
      ((2 ^ (E + 148) : Nat) : Real) * (2 : Real) ^ (-298 : Int) := by
    rw [show (E : Int) - 150 = ((E + 148 : Nat) : Int) + (-298) by omega,
      zpow_add₀ (by norm_num : (2 : Real) ≠ 0)]
    simp only [zpow_natCast, Nat.cast_pow, Nat.cast_ofNat]
  rw [hp, ← mul_assoc] at hl hu
  have hl' := (mul_lt_mul_right hs).mp hl
  have hu' := (mul_lt_mul_right hs).mp hu
  have hm1 : 1 ≤ 2 * mant := by omega
  constructor
  · have ht : (((2 ^ (E + 148) * (2 * mant - 1) : Nat) : Real)) <
        ((2 * num : Nat) : Real) := by
      push_cast [Nat.cast_sub hm1]
      nlinarith
    exact_mod_cast ht
  · have ht : ((2 * num : Nat) : Real) <
        (((2 ^ (E + 148) * (2 * mant + 1) : Nat) : Real)) := by
      push_cast
      nlinarith
    exact_mod_cast ht

/-- A real-cell primitive at the exact runtime's scale. Sign is a parameter;
the actual checker must separately establish its relation to the integer total. -/
theorem native32_fixed298_real_cell (sign : Bool) (num E mant : Nat)
    (hElo : 2 ≤ E) (hEhi : E ≤ 253)
    (hmlo : 8388608 < mant) (hmhi : mant < 16777216)
    (hl : ((mant : Real) - (1 : Real) / 2) * (2 : Real) ^ ((E : Int) - 150) <
      (num : Real) * (2 : Real) ^ (-298 : Int))
    (hu : (num : Real) * (2 : Real) ^ (-298 : Int) <
      ((mant : Real) + (1 : Real) / 2) * (2 : Real) ^ ((E : Int) - 150)) :
    Model.NativeBinary32.roundDyadic ⟨sign, num, -298⟩ =
      Model.NativeBinary32.mkBits sign E (mant - 8388608) := by
  obtain ⟨hl', hu'⟩ := real_cell_to_nat_cross num E mant (by omega) hl hu
  exact native32_fixed298_strict sign num E mant hElo hEhi hmlo hmhi hl' hu'

/-- Link the fixed-scale rounder directly to the official integer finishWord.
This helper does not assume the source of T or its sign; ofIntDyadic supplies it. -/
theorem finishWord_fixed298_of_cross (T : Int) (negZero : Bool) (E mant : Nat)
    (hT : T ≠ 0) (hElo : 2 ≤ E) (hEhi : E ≤ 253)
    (hmlo : 8388608 < mant) (hmhi : mant < 16777216)
    (hl : 2 ^ (E + 148) * (2 * mant - 1) < 2 * T.natAbs)
    (hu : 2 * T.natAbs < 2 ^ (E + 148) * (2 * mant + 1)) :
    finishWord T (-298) negZero =
      Model.NativeBinary32.mkBits (decide (T < 0)) E (mant - 8388608) := by
  have hr := native32_fixed298_strict (decide (T < 0)) T.natAbs E mant
    hElo hEhi hmlo hmhi hl hu
  simp only [finishWord, hT, ite_false]
  rw [← Model.NativeBinary32.ofUInt32_roundDyadic]
  change UInt32.ofNat (Model.NativeBinary32.roundDyadic (ofIntDyadic T (-298))).toNat = _
  rw [UInt32.ofNat_toNat]
  exact hr

end Submission.R27FixedScaleCell
