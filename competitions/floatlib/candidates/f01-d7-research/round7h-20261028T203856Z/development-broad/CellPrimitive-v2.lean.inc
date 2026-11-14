/- R24 portable mathematical primitive. Old ContractTensor/B2 only.
   Real FloatLib quotient and binary32 word-rounder conclusions; NOT_COMPILED.
   Public interfaces remain unchanged; no native assumption or abstract hcell input. -/
namespace Submission.R24CellPrimitive

open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

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

theorem quotient_even_closed_midpoint (num den mant : Nat)
    (hd : 0 < den) (hm : 0 < mant) (heven : mant % 2 = 0)
    (hl : den * (2 * mant - 1) ≤ 2 * num)
    (hu : 2 * num ≤ den * (2 * mant + 1)) :
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
    · have hr : den ≤ 2 * (num % den) := by rw [hq] at hdiv; nlinarith
      have hn : ¬ 2 * (num % den) < den := by omega
      by_cases hs : den < 2 * (num % den)
      · simp [FloatLib.Numerics.roundQuotientEven, hq, hn, hs]
      · have he : 2 * (num % den) = den := by omega
        have hk : k % 2 = 1 := by omega
        simp [FloatLib.Numerics.roundQuotientEven, hq, he, hk]
    · have hr : 2 * (num % den) ≤ den := by rw [hq] at hdiv; nlinarith
      by_cases hs : 2 * (num % den) < den
      · simp [FloatLib.Numerics.roundQuotientEven, hq, hs]
      · have he : 2 * (num % den) = den := by omega
        simp [FloatLib.Numerics.roundQuotientEven, hq, he, heven]

@[inline] def strictCell (num den mant : Nat) : Bool :=
  decide (0 < den ∧ 0 < mant ∧ den * (2 * mant - 1) < 2 * num ∧
    2 * num < den * (2 * mant + 1))

theorem strictCell_sound (num den mant : Nat) (h : strictCell num den mant = true) :
    FloatLib.Numerics.roundQuotientEven num den = mant := by
  have hh : 0 < den ∧ 0 < mant ∧ den * (2 * mant - 1) < 2 * num ∧
      2 * num < den * (2 * mant + 1) := of_decide_eq_true h
  exact quotient_strict_midpoint num den mant hh.1 hh.2.1 hh.2.2.1 hh.2.2.2

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

theorem normal_ratio_log23 (num den mant : Nat)
    (hd : 0 < den) (hmlo : 8388608 < mant) (hmhi : mant < 16777216)
    (hl : den * (2 * mant - 1) < 2 * num)
    (hu : 2 * num < den * (2 * mant + 1)) :
    FloatLib.Numerics.RationalBinary.floorLog2 num den = 23 := by
  obtain ⟨hlo, hhi⟩ := normal_ratio_nat_bounds num den mant hd hmlo hmhi hl hu
  have hn : num ≠ 0 := by intro h; subst num; nlinarith
  have hdr : (0 : Real) < den := by exact_mod_cast hd
  have hlr : (8388608 : Real) ≤ (num : Real) / den := by
    apply (le_div_iff₀ hdr).2
    exact_mod_cast hlo
  have hur : (num : Real) / den < (16777216 : Real) := by
    apply (div_lt_iff₀ hdr).2
    exact_mod_cast hhi
  apply Model.floorLog2_eq_of_bounds num den 23 hn (Nat.ne_of_gt hd)
  · have hp : Model.bpow (23 : Int) = (8388608 : Real) := by
      norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
        FloatLib.Numerics.binaryRadix, FloatLib.Numerics.Radix.toReal]
    simpa only [hp] using hlr
  · have hp : Model.bpow ((23 : Int) + 1) = (16777216 : Real) := by
      norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
        FloatLib.Numerics.binaryRadix, FloatLib.Numerics.Radix.toReal]
    simpa only [hp] using hur

theorem native32_strict_cell (sign : Bool) (num den mant : Nat) (exponent : Int)
    (hd : 0 < den) (hmlo : 8388608 < mant) (hmhi : mant < 16777216)
    (hexplo : 1 ≤ exponent + 150) (hexphi : exponent + 150 ≤ 254)
    (hl : den * (2 * mant - 1) < 2 * num)
    (hu : 2 * num < den * (2 * mant + 1)) :
    Model.NativeBinary32.roundRatScaled sign num den exponent =
      Model.NativeBinary32.mkBits sign (exponent + 150).toNat (mant - 8388608) := by
  have hn : num ≠ 0 := by
    have hb := (normal_ratio_nat_bounds num den mant hd hmlo hmhi hl hu).1
    intro h; subst num; nlinarith
  have hlog := normal_ratio_log23 num den mant hd hmlo hmhi hl hu
  have hr := quotient_strict_midpoint num den mant hd (by omega) hl hu
  have hbig : ¬ (23 : Int) + exponent > 127 := by omega
  have hsmall : ¬ (23 : Int) + exponent < -150 := by omega
  have hnormal : ¬ (23 : Int) + exponent < -126 := by omega
  have hp23 : Model.pow2 23 = 8388608 := by decide
  have hp24 : Model.pow2 24 = 16777216 := by decide
  have hc : mant ≠ Model.pow2 24 := by rw [hp24]; omega
  have hencoded : (23 : Int) + exponent + 127 = exponent + 150 := by omega
  have hround : Model.NativeBinary32.roundRatScaled sign num den exponent =
      Model.NativeBinary32.mkBits sign ((23 : Int) + exponent + 127).toNat
        (mant - Model.pow2 23) := by
    simp only [Model.NativeBinary32.roundRatScaled, beq_iff_eq,
      Nat.ne_of_gt hd, hn, if_false, hlog, hbig, hsmall, hnormal,
      sub_self, FloatLib.Numerics.RationalBinary.scaleByPowerOfTwo_zero,
      Prod.fst, Prod.snd]
    rw [hr]
    simp only [hr, beq_iff_eq, hc, if_false, hbig]
  simpa only [hp23, hencoded] using hround

@[inline] def normalStrictCell (num den mant : Nat) (exponent : Int) : Bool :=
  decide (0 < den ∧ 8388608 < mant ∧ mant < 16777216 ∧
    1 ≤ exponent + 150 ∧ exponent + 150 ≤ 254 ∧
    den * (2 * mant - 1) < 2 * num ∧ 2 * num < den * (2 * mant + 1))

theorem normalStrictCell_sound (sign : Bool) (num den mant : Nat) (exponent : Int)
    (h : normalStrictCell num den mant exponent = true) :
    Model.NativeBinary32.roundRatScaled sign num den exponent =
      Model.NativeBinary32.mkBits sign (exponent + 150).toNat (mant - 8388608) := by
  have hh : 0 < den ∧ 8388608 < mant ∧ mant < 16777216 ∧
      1 ≤ exponent + 150 ∧ exponent + 150 ≤ 254 ∧
      den * (2 * mant - 1) < 2 * num ∧ 2 * num < den * (2 * mant + 1) :=
    of_decide_eq_true h
  exact native32_strict_cell sign num den mant exponent hh.1 hh.2.1 hh.2.2.1
    hh.2.2.2.1 hh.2.2.2.2.1 hh.2.2.2.2.2.1 hh.2.2.2.2.2.2

end Submission.R24CellPrimitive
