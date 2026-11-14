/- R24 exact power-of-two rounding cells. Old ContractTensor mathematics only.
   New proofs are NOT_COMPILED. The quotient tie lemma is reused from broad.
   No native proposal accuracy or abstract rounding-cell premise is assumed. -/
namespace Submission.R24PowerCell
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

theorem common_bounds (num den : Nat) (hd : 0 < den)
    (hl : den * 16777215 ≤ 2 * num)
    (hu : 2 * num ≤ den * 16777217) :
    4194304 * den ≤ num ∧ num < 16777216 * den := by
  constructor <;> omega

theorem ratio_log22 (num den : Nat) (hd : 0 < den)
    (hl : 4194304 * den ≤ num) (hu : num < 8388608 * den) :
    FloatLib.Numerics.RationalBinary.floorLog2 num den = 22 := by
  have hn : num ≠ 0 := by intro h; subst num; omega
  have hdr : (0 : Real) < den := by exact_mod_cast hd
  have hlr : (4194304 : Real) ≤ (num : Real) / den := by
    apply (le_div_iff₀ hdr).2
    exact_mod_cast hl
  have hur : (num : Real) / den < (8388608 : Real) := by
    apply (div_lt_iff₀ hdr).2
    exact_mod_cast hu
  apply Model.floorLog2_eq_of_bounds num den 22 hn (Nat.ne_of_gt hd)
  · have hp : Model.bpow (22 : Int) = (4194304 : Real) := by
      norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
        FloatLib.Numerics.binaryRadix, FloatLib.Numerics.Radix.toReal]
    simpa only [hp] using hlr
  · have hp : Model.bpow ((22 : Int) + 1) = (8388608 : Real) := by
      norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
        FloatLib.Numerics.binaryRadix, FloatLib.Numerics.Radix.toReal]
    simpa only [hp] using hur

theorem ratio_log23 (num den : Nat) (hd : 0 < den)
    (hl : 8388608 * den ≤ num) (hu : num < 16777216 * den) :
    FloatLib.Numerics.RationalBinary.floorLog2 num den = 23 := by
  have hn : num ≠ 0 := by intro h; subst num; omega
  have hdr : (0 : Real) < den := by exact_mod_cast hd
  have hlr : (8388608 : Real) ≤ (num : Real) / den := by
    apply (le_div_iff₀ hdr).2
    exact_mod_cast hl
  have hur : (num : Real) / den < (16777216 : Real) := by
    apply (div_lt_iff₀ hdr).2
    exact_mod_cast hu
  apply Model.floorLog2_eq_of_bounds num den 23 hn (Nat.ne_of_gt hd)
  · have hp : Model.bpow (23 : Int) = (8388608 : Real) := by
      norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
        FloatLib.Numerics.binaryRadix, FloatLib.Numerics.Radix.toReal]
    simpa only [hp] using hlr
  · have hp : Model.bpow ((23 : Int) + 1) = (16777216 : Real) := by
      norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
        FloatLib.Numerics.binaryRadix, FloatLib.Numerics.Radix.toReal]
    simpa only [hp] using hur

theorem native32_power_above_min (sign : Bool) (num den : Nat) (exponent : Int)
    (hd : 0 < den) (he0 : 2 ≤ exponent + 150) (he1 : exponent + 150 ≤ 254)
    (hl : den * 33554431 ≤ 4 * num)
    (hu : 2 * num ≤ den * 16777217) :
    Model.NativeBinary32.roundRatScaled sign num den exponent =
      Model.NativeBinary32.mkBits sign (exponent + 150).toNat 0 := by
  have hlold : den * 16777215 ≤ 2 * num := by
    nlinarith only [hl, Nat.zero_le den]
  have hb := common_bounds num den hd hlold hu
  have hn : num ≠ 0 := by intro h; subst num; omega
  have hp23 : Model.pow2 23 = 8388608 := by decide
  have hp24 : Model.pow2 24 = 16777216 := by decide
  by_cases hregion : 8388608 * den ≤ num
  · have hlog := ratio_log23 num den hd hregion hb.2
    have hq := R24CellPrimitive.quotient_even_closed_midpoint num den 8388608
      hd (by decide) (by decide) hlold hu
    have hbig : ¬ (23 : Int) + exponent > 127 := by omega
    have hsmall : ¬ (23 : Int) + exponent < -150 := by omega
    have hnormal : ¬ (23 : Int) + exponent < -126 := by omega
    have hencoded : (23 : Int) + exponent + 127 = exponent + 150 := by omega
    have hround : Model.NativeBinary32.roundRatScaled sign num den exponent =
        Model.NativeBinary32.mkBits sign ((23 : Int) + exponent + 127).toNat
          (8388608 - Model.pow2 23) := by
      simp only [Model.NativeBinary32.roundRatScaled, beq_iff_eq,
        Nat.ne_of_gt hd, hn, if_false, hlog, hbig, hsmall, hnormal,
        sub_self, FloatLib.Numerics.RationalBinary.scaleByPowerOfTwo_zero,
        Prod.fst, Prod.snd]
      rw [hq]
      norm_num [hq, hp23, hp24, hbig]
    simpa only [hp23, hencoded, Nat.sub_self] using hround
  · have hregion' : num < 8388608 * den := by omega
    have hlog := ratio_log22 num den hd hb.1 hregion'
    have hq : FloatLib.Numerics.roundQuotientEven (num * 2) den = 16777216 := by
      apply R24CellPrimitive.quotient_even_closed_midpoint (num * 2) den 16777216
        hd (by decide) (by decide)
      · change den * 33554431 ≤ 2 * (num * 2)
        calc
          den * 33554431 ≤ 4 * num := hl
          _ = 2 * (num * 2) := by ring
      · omega
    have hbig : ¬ (22 : Int) + exponent > 127 := by omega
    have hsmall : ¬ (22 : Int) + exponent < -150 := by omega
    have hnormal : ¬ (22 : Int) + exponent < -126 := by omega
    have hlast : ¬ (22 : Int) + exponent + 1 > 127 := by omega
    have hscaled : FloatLib.Numerics.RationalBinary.scaleByPowerOfTwo num den
        ((23 : Int) - 22) = (num * 2, den) := by
      norm_num [FloatLib.Numerics.RationalBinary.scaleByPowerOfTwo, Nat.shiftLeft_eq]
    have hencoded : (22 : Int) + exponent + 1 + 127 = exponent + 150 := by omega
    have hround : Model.NativeBinary32.roundRatScaled sign num den exponent =
        Model.NativeBinary32.mkBits sign ((22 : Int) + exponent + 1 + 127).toNat 0 := by
      simp only [Model.NativeBinary32.roundRatScaled, beq_iff_eq,
        Nat.ne_of_gt hd, hn, if_false, hlog, hbig, hsmall, hnormal,
        hscaled, Prod.fst, Prod.snd]
      rw [hq]
      norm_num [hq, hp23, hp24, hlast]
    simpa only [hencoded] using hround

theorem native32_min_normal (sign : Bool) (num den : Nat) (hd : 0 < den)
    (hl : den * 16777215 ≤ 2 * num)
    (hu : 2 * num ≤ den * 16777217) :
    Model.NativeBinary32.roundRatScaled sign num den (-149) =
      Model.NativeBinary32.mkBits sign 1 0 := by
  have hb := common_bounds num den hd hl hu
  have hn : num ≠ 0 := by intro h; subst num; omega
  have hq := R24CellPrimitive.quotient_even_closed_midpoint num den 8388608
    hd (by decide) (by decide) hl hu
  have hp23 : Model.pow2 23 = 8388608 := by decide
  have hp24 : Model.pow2 24 = 16777216 := by decide
  by_cases hregion : 8388608 * den ≤ num
  · have hlog := ratio_log23 num den hd hregion hb.2
    simp [Model.NativeBinary32.roundRatScaled, Nat.ne_of_gt hd, hn, hlog,
      hq, hp23, hp24, FloatLib.Numerics.RationalBinary.scaleByPowerOfTwo]
  · have hregion' : num < 8388608 * den := by omega
    have hlog := ratio_log22 num den hd hb.1 hregion'
    simp [Model.NativeBinary32.roundRatScaled, Nat.ne_of_gt hd, hn, hlog,
      hq, hp23, hp24, FloatLib.Numerics.RationalBinary.scaleByPowerOfTwo]
    cases Nat.decLe (Model.pow2 23) (FloatLib.Numerics.roundQuotientEven num den) with
    | isTrue hle => rfl
    | isFalse hnle =>
        exact False.elim (hnle (by
          simpa only [hp23, hq] using (Nat.le_refl 8388608)))

@[inline] def powerCell (num den : Nat) (exponent : Int) : Bool :=
  decide (0 < den ∧ 1 ≤ exponent + 150 ∧ exponent + 150 ≤ 254 ∧
    (if exponent + 150 = 1 then den * 16777215 ≤ 2 * num
      else den * 33554431 ≤ 4 * num) ∧ 2 * num ≤ den * 16777217)

theorem powerCell_sound (sign : Bool) (num den : Nat) (exponent : Int)
    (h : powerCell num den exponent = true) :
    Model.NativeBinary32.roundRatScaled sign num den exponent =
      Model.NativeBinary32.mkBits sign (exponent + 150).toNat 0 := by
  have hh : 0 < den ∧ 1 ≤ exponent + 150 ∧ exponent + 150 ≤ 254 ∧
      (if exponent + 150 = 1 then den * 16777215 ≤ 2 * num
        else den * 33554431 ≤ 4 * num) ∧ 2 * num ≤ den * 16777217 :=
    of_decide_eq_true h
  rcases hh with ⟨hd, he0, he1, hl, hu⟩
  by_cases hmin : exponent + 150 = 1
  · have hl' : den * 16777215 ≤ 2 * num := by simpa [hmin] using hl
    have he : exponent = -149 := by omega
    simpa [he] using native32_min_normal sign num den hd hl' hu
  · have hl' : den * 33554431 ≤ 4 * num := by simpa [hmin] using hl
    exact native32_power_above_min sign num den exponent hd (by omega) he1 hl' hu

end Submission.R24PowerCell
