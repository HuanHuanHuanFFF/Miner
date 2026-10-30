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
    (hElo : 1 ≤ E) (hEhi : E ≤ 254)
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
open FloatLib.Numerics

/-- The part of a power-of-two cell at or above the proposed value. -/
theorem native32_fixed298_power_upper (sign : Bool) (num E : Nat)
    (hElo : 1 ≤ E) (hEhi : E ≤ 254)
    (hl : 8388608 * 2 ^ (E + 148) ≤ num)
    (hu : 2 * num < 2 ^ (E + 148) * 16777217) :
    Model.NativeBinary32.roundDyadic ⟨sign, num, -298⟩ =
      Model.NativeBinary32.mkBits sign E 0 := by
  have hd : 0 < 2 ^ (E + 148) := Nat.two_pow_pos _
  have hn : num ≠ 0 := by omega
  have hnhi : num < 16777216 * 2 ^ (E + 148) := by omega
  have hlog : num.log2 = E + 171 := by
    rw [Nat.log2_eq_iff hn]
    constructor
    · rw [show E + 171 = 23 + (E + 148) by omega, Nat.pow_add]
      change 8388608 * 2 ^ (E + 148) ≤ num
      exact hl
    · rw [show E + 171 + 1 = 24 + (E + 148) by omega, Nat.pow_add]
      change num < 16777216 * 2 ^ (E + 148)
      exact hnhi
  have hlo : 2 ^ (E + 148) * (2 * 8388608 - 1) < 2 * num := by omega
  have hr : roundShiftRightEven num (E + 148) = 8388608 := by
    rw [roundShiftRightEven_eq_roundQuotientEven]
    exact quotient_strict_midpoint num (2 ^ (E + 148)) 8388608 hd (by decide) hlo hu
  have htotal : ((E + 171 : Nat) : Int) + (-298) = (E : Int) - 127 := by omega
  have hsub : ¬ (E : Int) - 127 < -126 := by omega
  have hlead : 23 ≤ E + 171 := by omega
  have hshift : E + 171 - 23 = E + 148 := by omega
  have hbig : ¬ (E : Int) - 127 > 127 := by omega
  have hencoded : ((E : Int) - 127 + 127).toNat = E := by omega
  simp only [Model.NativeBinary32.roundDyadic, beq_iff_eq, hn, ite_false,
    hlog, htotal, hsub, hlead, ite_true, hshift, hr, hbig, hencoded,
    show Model.pow2 24 = 16777216 by decide, show Model.pow2 23 = 8388608 by decide] <;> rfl

/-- Below a normal power of two, a normal significand carries into q's bin. -/
theorem native32_fixed298_power_lower (sign : Bool) (num E : Nat)
    (hElo : 2 ≤ E) (hEhi : E ≤ 254)
    (hl : 2 ^ (E + 148) * 33554431 < 4 * num)
    (hu : num < 8388608 * 2 ^ (E + 148)) :
    Model.NativeBinary32.roundDyadic ⟨sign, num, -298⟩ =
      Model.NativeBinary32.mkBits sign E 0 := by
  have hp : 0 < 2 ^ (E + 147) := Nat.two_pow_pos _
  have hden : 2 ^ (E + 148) = 2 * 2 ^ (E + 147) := by
    rw [show E + 148 = (E + 147) + 1 by omega, Nat.pow_add]
    simp only [Nat.pow_one, Nat.mul_comm]
  rw [hden] at hl hu
  have hn : num ≠ 0 := by omega
  have hnlo : 8388608 * 2 ^ (E + 147) ≤ num := by omega
  have hnhi : num < 16777216 * 2 ^ (E + 147) := by omega
  have hlog : num.log2 = E + 170 := by
    rw [Nat.log2_eq_iff hn]
    constructor
    · rw [show E + 170 = 23 + (E + 147) by omega, Nat.pow_add]
      change 8388608 * 2 ^ (E + 147) ≤ num
      exact hnlo
    · rw [show E + 170 + 1 = 24 + (E + 147) by omega, Nat.pow_add]
      change num < 16777216 * 2 ^ (E + 147)
      exact hnhi
  have hlo : 2 ^ (E + 147) * (2 * 16777216 - 1) < 2 * num := by omega
  have hhi : 2 * num < 2 ^ (E + 147) * (2 * 16777216 + 1) := by omega
  have hr : roundShiftRightEven num (E + 147) = 16777216 := by
    rw [roundShiftRightEven_eq_roundQuotientEven]
    exact quotient_strict_midpoint num (2 ^ (E + 147)) 16777216 hp (by decide) hlo hhi
  have htotal : ((E + 170 : Nat) : Int) + (-298) = (E : Int) - 128 := by omega
  have hsub : ¬ (E : Int) - 128 < -126 := by omega
  have hlead : 23 ≤ E + 170 := by omega
  have hshift : E + 170 - 23 = E + 147 := by omega
  have hbig : ¬ (E : Int) - 128 + 1 > 127 := by omega
  have hencoded : ((E : Int) - 128 + 1 + 127).toNat = E := by omega
  simp only [Model.NativeBinary32.roundDyadic, beq_iff_eq, hn, ite_false,
    hlog, htotal, hsub, hlead, ite_true, hshift, hr, hbig, hencoded,
    show Model.pow2 24 = 16777216 by decide, show Model.pow2 23 = 8388608 by decide] <;> rfl

/-- Minimum-normal's lower half is produced by the subnormal carry branch. -/
theorem native32_fixed298_minnormal_lower (sign : Bool) (num : Nat)
    (hl : 2 ^ 149 * 16777215 < 2 * num)
    (hu : num < 8388608 * 2 ^ 149) :
    Model.NativeBinary32.roundDyadic ⟨sign, num, -298⟩ =
      Model.NativeBinary32.mkBits sign 1 0 := by
  have hn : num ≠ 0 := by omega
  have hlog : num.log2 = 171 := by
    rw [Nat.log2_eq_iff hn]
    constructor <;> norm_num at * <;> omega
  have hhi : 2 * num < 2 ^ 149 * (2 * 8388608 + 1) := by omega
  have hr : roundShiftRightEven num 149 = 8388608 := by
    rw [roundShiftRightEven_eq_roundQuotientEven]
    exact quotient_strict_midpoint num (2 ^ 149) 8388608 (by decide) (by decide) hl hhi
  simp [Model.NativeBinary32.roundDyadic, hn, hlog, hr, Model.pow2]

end Submission.R27FixedScaleCell
