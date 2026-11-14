import ContractExact

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


/- Logical exact rescaling for the actual native32 rational rounder.
   No shifted numerator/denominator is introduced by an executable caller.
   Old ContractTensor helper; typing/replay/AX still NOT_RUN. -/
namespace Submission.R24RescaleNative32
open FloatLib.Numerics
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

private theorem scale_zero_num (den : Nat) (scale : Int) :
    (RationalBinary.scaleByPowerOfTwo 0 den scale).1 = 0 := by
  cases scale <;> simp [RationalBinary.scaleByPowerOfTwo, Nat.shiftLeft_eq]

private theorem scale_zero_den (num : Nat) (scale : Int) :
    (RationalBinary.scaleByPowerOfTwo num 0 scale).2 = 0 := by
  cases scale <;> simp [RationalBinary.scaleByPowerOfTwo, Nat.shiftLeft_eq]

theorem roundRatScaled_rescale (sign : Bool) (num den : Nat) (source target : Int) :
    let scaled := RationalBinary.scaleByPowerOfTwo num den (source - target)
    Model.NativeBinary32.roundRatScaled sign num den source =
      Model.NativeBinary32.roundRatScaled sign scaled.1 scaled.2 target := by
  let delta := source - target
  let scaled := RationalBinary.scaleByPowerOfTwo num den delta
  change Model.NativeBinary32.roundRatScaled sign num den source =
    Model.NativeBinary32.roundRatScaled sign scaled.1 scaled.2 target
  by_cases hd : den = 0
  · have hsd : scaled.2 = 0 := by
      simpa only [scaled, hd] using scale_zero_den num delta
    simp only [Model.NativeBinary32.roundRatScaled, beq_iff_eq, hd, hsd, if_true]
  have hsd : scaled.2 ≠ 0 :=
    RationalBinary.scaleByPowerOfTwo_snd_ne_zero num den delta hd
  by_cases hn : num = 0
  · have hsn : scaled.1 = 0 := by
      simpa only [scaled, hn] using scale_zero_num den delta
    simp only [Model.NativeBinary32.roundRatScaled, beq_iff_eq, hd, hsd, hn, hsn, if_false, if_true]
  have hsn : scaled.1 ≠ 0 :=
    RationalBinary.scaleByPowerOfTwo_fst_ne_zero num den delta hn
  have hlog : RationalBinary.floorLog2 scaled.1 scaled.2 =
      RationalBinary.floorLog2 num den + delta :=
    Model.floorLog2_scaleByPowerOfTwo num den delta hn hd
  have htotal : RationalBinary.floorLog2 num den + delta + target =
      RationalBinary.floorLog2 num den + source := by dsimp [delta]; omega
  have hsub : delta + (target + 149) = source + 149 := by dsimp [delta]; omega
  have hnormal : delta + (23 - (RationalBinary.floorLog2 num den + delta)) =
      23 - RationalBinary.floorLog2 num den := by omega
  have hqsub := Model.roundQuotientEven_scaleByPowerOfTwo_add num den delta (target + 149) hd
  dsimp only at hqsub
  change roundQuotientEven (RationalBinary.scaleByPowerOfTwo scaled.1 scaled.2 (target + 149)).1
      (RationalBinary.scaleByPowerOfTwo scaled.1 scaled.2 (target + 149)).2 =
    roundQuotientEven (RationalBinary.scaleByPowerOfTwo num den (delta + (target + 149))).1
      (RationalBinary.scaleByPowerOfTwo num den (delta + (target + 149))).2 at hqsub
  rw [hsub] at hqsub
  have hqnormal := Model.roundQuotientEven_scaleByPowerOfTwo_add num den delta
    (23 - (RationalBinary.floorLog2 num den + delta)) hd
  dsimp only at hqnormal
  change roundQuotientEven
      (RationalBinary.scaleByPowerOfTwo scaled.1 scaled.2 (23 - (RationalBinary.floorLog2 num den + delta))).1
      (RationalBinary.scaleByPowerOfTwo scaled.1 scaled.2 (23 - (RationalBinary.floorLog2 num den + delta))).2 =
    roundQuotientEven (RationalBinary.scaleByPowerOfTwo num den
      (delta + (23 - (RationalBinary.floorLog2 num den + delta)))).1
      (RationalBinary.scaleByPowerOfTwo num den
        (delta + (23 - (RationalBinary.floorLog2 num den + delta)))).2 at hqnormal
  rw [hnormal] at hqnormal
  simp only [Model.NativeBinary32.roundRatScaled, beq_iff_eq, hd, hsd, hn, hsn,
    if_false, hlog, htotal, hqsub, hqnormal]

end Submission.R24RescaleNative32


/- Actual native32 dyadic / denominator-one rational agreement.
   The normalized quotient proof below is adapted from FloatLib Team,
   MIT license, IEEE754/Native/Integer/Rounding.lean, fixed blob
   0f79753745f67a8e29e539570b2c66139cc29313. Other statements close
   the arbitrary-exponent subnormal and early-exit branches directly. -/
namespace Submission.R24DyadicAgreement
open FloatLib.Numerics
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

private def fraction (num : Nat) (exponent : Int) : Nat :=
  match exponent + 149 with
  | .ofNat shift => num <<< shift
  | .negSucc shift => roundShiftRightEven num (shift + 1)

private theorem quotient_scale_one (num : Nat) (exponent : Int) :
    let scaled := RationalBinary.scaleByPowerOfTwo num 1 exponent
    roundQuotientEven scaled.1 scaled.2 =
      match exponent with
      | .ofNat shift => num <<< shift
      | .negSucc shift => roundShiftRightEven num (shift + 1) := by
  cases exponent with
  | ofNat shift => simp [RationalBinary.scaleByPowerOfTwo, roundQuotientEven]
  | negSucc shift =>
      simpa [RationalBinary.scaleByPowerOfTwo, Nat.shiftLeft_eq] using
        (roundShiftRightEven_eq_roundQuotientEven num (shift + 1)).symm

private theorem quotient_normal_one (num p : Nat) :
    let scaled := RationalBinary.scaleByPowerOfTwo num 1 ((p : Int) - num.log2)
    roundQuotientEven scaled.1 scaled.2 =
      if p ≤ num.log2 then roundShiftRightEven num (num.log2 - p)
      else num <<< (p - num.log2) := by
  by_cases h : p ≤ num.log2
  · obtain ⟨k, hk⟩ := Nat.exists_eq_add_of_le h
    rw [hk]
    cases k with
    | zero =>
        simp [RationalBinary.scaleByPowerOfTwo, roundQuotientEven, Nat.mod_one,
          roundShiftRightEven_def]
    | succ k =>
        have he : (p : Int) - (p + (k + 1)) = Int.negSucc k := by omega
        simp [he, RationalBinary.scaleByPowerOfTwo, Nat.shiftLeft_eq,
          ← roundShiftRightEven_eq_roundQuotientEven]
  · have he : (p : Int) - num.log2 = Int.ofNat (p - num.log2) := by
      simp only [Int.ofNat_eq_natCast]
      omega
    simp [he, RationalBinary.scaleByPowerOfTwo, roundQuotientEven, Nat.mod_one, h]

private theorem fraction_zero (num : Nat) (exponent : Int)
    (hsmall : (num.log2 : Int) + exponent < -150) : fraction num exponent = 0 := by
  cases hshift : exponent + 149 with
  | ofNat shift => omega
  | negSucc shift =>
      have hdeep : num.log2 + 1 < shift + 1 := by omega
      have hnonzero : shift + 1 ≠ 0 := by omega
      simp only [fraction, hshift, roundShiftRightEven, beq_iff_eq,
        hnonzero, ite_false, hdeep, ite_true]

private theorem fraction_le (num : Nat) (exponent : Int) (hn : num ≠ 0)
    (hsub : (num.log2 : Int) + exponent < -126) :
    fraction num exponent ≤ Model.pow2 23 := by
  have hp : Model.pow2 23 = 8388608 := by decide
  cases hshift : exponent + 149 with
  | ofNat shift =>
      have hnBound : num < 2 ^ (num.log2 + 1) :=
        (Nat.log2_lt hn).mp (by omega)
      have hsum : num.log2 + 1 + shift ≤ 23 := by omega
      have hlt : num <<< shift < 2 ^ 23 := by
        rw [Nat.shiftLeft_eq]
        calc
          num * 2 ^ shift < 2 ^ (num.log2 + 1) * 2 ^ shift :=
            Nat.mul_lt_mul_of_pos_right hnBound (Nat.two_pow_pos shift)
          _ = 2 ^ (num.log2 + 1 + shift) := (Nat.pow_add _ _ _).symm
          _ ≤ 2 ^ 23 := Nat.pow_le_pow_right (by decide) hsum
      simpa only [fraction, hshift, hp] using Nat.le_of_lt hlt
  | negSucc shift =>
      have hlog : num.log2 < 23 + (shift + 1) := by omega
      have hnBound : num < 2 ^ (23 + (shift + 1)) := (Nat.log2_lt hn).mp hlog
      have hdiv : num / 2 ^ (shift + 1) < 2 ^ 23 := by
        apply (Nat.div_lt_iff_lt_mul (Nat.two_pow_pos (shift + 1))).mpr
        simpa only [Nat.pow_add] using hnBound
      have hround := roundShiftRightEven_le_shiftRight_add1 num (shift + 1)
      rw [Nat.shiftRight_eq_div_pow] at hround
      have hle : roundShiftRightEven num (shift + 1) ≤ 8388608 := by omega
      simpa only [fraction, hshift, hp] using hle

private theorem subnormal_pack (sign : Bool) (f : Nat) (hf : f ≤ Model.pow2 23) :
    (if f == 0 then (if sign then (0x80000000 : UInt32) else 0)
      else if f == Model.pow2 23 then Model.NativeBinary32.mkBits sign 1 0
      else Model.NativeBinary32.mkBits sign 0 f) =
    (if f == 0 then (if sign then (0x80000000 : UInt32) else 0)
      else match Nat.decLe (Model.pow2 23) f with
        | isTrue _ => Model.NativeBinary32.mkBits sign 1 0
        | isFalse _ => Model.NativeBinary32.mkBits sign 0 f) := by
  simp only [beq_iff_eq]
  by_cases hz : f = 0
  · simp only [hz, ite_true]
  · simp only [hz, ite_false]
    cases Nat.decLe (Model.pow2 23) f with
    | isTrue hge =>
        have heq : f = Model.pow2 23 := Nat.le_antisymm hf hge
        simp only [heq, ite_true]
    | isFalse hnot =>
        have hne : f ≠ Model.pow2 23 := by
          intro heq
          exact hnot (by simpa only [heq] using (Nat.le_refl (Model.pow2 23)))
        simp only [hne, ite_false]

theorem roundDyadic_eq_roundRatScaled (sign : Bool) (num : Nat) (exponent : Int) :
    Model.NativeBinary32.roundDyadic ⟨sign, num, exponent⟩ =
      Model.NativeBinary32.roundRatScaled sign num 1 exponent := by
  by_cases hn : num = 0
  · subst num
    simp [Model.NativeBinary32.roundDyadic, Model.NativeBinary32.roundRatScaled]
  have hlog := Model.floorLog2_den_one num hn
  by_cases hbig : (num.log2 : Int) + exponent > 127
  · have hnormal : ¬ (num.log2 : Int) + exponent < -126 := by omega
    simp only [Model.NativeBinary32.roundDyadic, Model.NativeBinary32.roundRatScaled,
      beq_iff_eq, hn, Nat.one_ne_zero, ite_false, hlog, hbig, hnormal, ite_true]
    split_ifs <;> first | rfl | omega
  by_cases hsmall : (num.log2 : Int) + exponent < -150
  · have hsub : (num.log2 : Int) + exponent < -126 := by omega
    have hf := fraction_zero num exponent hsmall
    dsimp only [fraction] at hf
    simp only [Model.NativeBinary32.roundDyadic, Model.NativeBinary32.roundRatScaled,
      beq_iff_eq, hn, Nat.one_ne_zero, ite_false, hlog, hbig, hsmall, hsub,
      ite_true, hf]
  have hqsub := quotient_scale_one num (exponent + 149)
  dsimp only at hqsub
  have hqnormal := quotient_normal_one num 23
  dsimp only at hqnormal
  by_cases hsub : (num.log2 : Int) + exponent < -126
  · have hpack := subnormal_pack sign (fraction num exponent) (fraction_le num exponent hn hsub)
    dsimp only [fraction] at hpack
    simpa only [Model.NativeBinary32.roundDyadic, Model.NativeBinary32.roundRatScaled,
      beq_iff_eq, hn, Nat.one_ne_zero, ite_false, hlog, hbig, hsmall, hsub,
      ite_true, hqsub] using hpack
  · simp only [Model.NativeBinary32.roundDyadic, Model.NativeBinary32.roundRatScaled,
      beq_iff_eq, hn, Nat.one_ne_zero, ite_false, hlog, hbig, hsmall, hsub,
      hqnormal, Int.ofNat_eq_natCast]

end Submission.R24DyadicAgreement
