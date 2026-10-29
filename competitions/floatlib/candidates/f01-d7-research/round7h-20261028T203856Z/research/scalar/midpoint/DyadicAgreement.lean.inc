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
