/- R14 developer proof attempt, NOT_COMPILED.
   Exact UInt32/UInt64 fields for the fixed narrow normal add domain.
   All overflow bounds concern complete words, before the result guard. -/
namespace Submission.R14WordAdd

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

abbrev magnitudeNat (u v : UInt32) : Nat :=
  R14WordAddAlignment.magnitude (R2W01c.wordSign (high u v))
    (R2W01c.wordSign (low u v)) (R2W01b.mantissa (high u v)).toNat
    (R2W01b.mantissa (low u v)).toNat (gap u v).toNat

abbrev baseNat (u v : UInt32) : Nat :=
  R14WordAddAlignment.leadingBase (R2W01c.wordSign (high u v))
    (R2W01c.wordSign (low u v)) (gap u v).toNat

theorem gap_pair (u v : UInt32) :
    (gap u v).toNat = R2W01c.wordExp (high u v) - R2W01c.wordExp (low u v) := by
  rw [gap_nat, (sorted_exponents u v).1, (sorted_exponents u v).2]

theorem sameSign_sorted (u v : UInt32) :
    sameSign u v = (R2W01c.wordSign (high u v) == R2W01c.wordSign (low u v)) := by
  rw [sameSign_eq]
  by_cases h : R14ExponentShift.ex u < R14ExponentShift.ex v
  · simp only [high, low, if_pos h]
    cases R2W01c.wordSign u <;> cases R2W01c.wordSign v <;> rfl
  · simp only [high, low, if_neg h]

theorem sorted_domain (u v : UInt32) (hd : eligible u v = true) :
    (0 < R2W01c.wordExp (high u v) ∧ R2W01c.wordExp (high u v) < 255) ∧
    (0 < R2W01c.wordExp (low u v) ∧ R2W01c.wordExp (low u v) < 255) ∧
    (gap u v).toNat ≤ 7 ∧
    (R2W01c.wordSign (high u v) = R2W01c.wordSign (low u v) ∨
      2 ≤ (gap u v).toNat) := by
  have hc := eligible_conditions u v hd
  have hs := sorted_exponents u v
  have hehi : 0 < R2W01c.wordExp (high u v) ∧
      R2W01c.wordExp (high u v) < 255 := by rw [hs.1]; omega
  have helo : 0 < R2W01c.wordExp (low u v) ∧
      R2W01c.wordExp (low u v) < 255 := by rw [hs.2]; omega
  refine ⟨hehi, helo, hc.2.2.1, ?_⟩
  · rcases hc.2.2.2 with hsign | hgap
    · left
      by_cases h : R14ExponentShift.ex u < R14ExponentShift.ex v
      · simpa only [high, low, if_pos h] using hsign.symm
      · simpa only [high, low, if_neg h] using hsign
    · exact Or.inr hgap

theorem magnitudeNat_bounds (u v : UInt32) (hd : eligible u v = true) :
    16777216 ≤ magnitudeNat u v ∧ magnitudeNat u v ≤ 2164260735 := by
  have hh := R2W01c.mantissa_bounds (high u v)
  have hl := R2W01c.mantissa_bounds (low u v)
  have hs := sorted_domain u v hd
  have hb := R14WordAddAlignment.magnitude_bounds _ _ _ _ _
    hh.1 hh.2 hl.1 hl.2 hs.2.2.1 hs.2.2.2
  exact ⟨hb.1, hb.2.1⟩

theorem magnitudeNat_log_bounds (u v : UInt32) (hd : eligible u v = true) :
    24 ≤ (magnitudeNat u v).log2 ∧ (magnitudeNat u v).log2 ≤ 31 ∧
      (magnitudeNat u v).log2 ≤ (gap u v).toNat + 24 := by
  have hh := R2W01c.mantissa_bounds (high u v)
  have hl := R2W01c.mantissa_bounds (low u v)
  have hs := sorted_domain u v hd
  exact R14WordAddAlignment.log2_bounds _ _ _ _ _
    hh.1 hh.2 hl.1 hl.2 hs.2.2.1 hs.2.2.2

theorem left_word_nat (u v : UInt32) (hd : eligible u v = true) :
    (R2W01b.mantissa (high u v) <<< gap u v).toNat =
      (R2W01b.mantissa (high u v)).toNat <<< (gap u v).toNat := by
  have hm := R2W01c.mantissa_bounds (high u v)
  have hg := (eligible_conditions u v hd).2.2.1
  have hp : 2 ^ (gap u v).toNat ≤ 128 := by
    have h : 2 ^ (gap u v).toNat ≤ 2 ^ 7 :=
      Nat.pow_le_pow_right (by decide : 1 ≤ (2 : Nat)) hg
    norm_num at h
    exact h
  have hx := Nat.mul_le_mul_left (R2W01b.mantissa (high u v)).toNat hp
  rw [UInt32.toNat_shiftLeft, Nat.mod_eq_of_lt (by omega)]
  rw [Nat.shiftLeft_eq]
  exact Nat.mod_eq_of_lt (by omega)

theorem magnitudeWord_nat (u v : UInt32) (hd : eligible u v = true) :
    (magnitudeWord u v).toNat = magnitudeNat u v := by
  have hb := magnitudeNat_bounds u v hd
  have hs := sorted_domain u v hd
  by_cases hsame : sameSign u v = true
  · have heq : R2W01c.wordSign (high u v) = R2W01c.wordSign (low u v) := by
      rw [sameSign_sorted, beq_iff_eq] at hsame
      exact hsame
    rw [magnitudeWord, if_pos hsame, UInt32.toNat_add, left_word_nat u v hd]
    have hn : magnitudeNat u v =
        ((R2W01b.mantissa (high u v)).toNat <<< (gap u v).toNat) +
          (R2W01b.mantissa (low u v)).toNat := by
      simp only [magnitudeNat, R14WordAddAlignment.magnitude, if_pos heq]
    rw [hn] at hb ⊢
    exact Nat.mod_eq_of_lt (by omega)
  · have hne : R2W01c.wordSign (high u v) ≠ R2W01c.wordSign (low u v) := by
      intro heq
      have ht : sameSign u v = true := by rw [sameSign_sorted, heq]; rfl
      exact hsame ht
    have hg : 2 ≤ (gap u v).toNat := hs.2.2.2.resolve_left hne
    have hleft := R14WordAddAlignment.large_left _ _ _
      (R2W01c.mantissa_bounds (high u v)).1
      (R2W01c.mantissa_bounds (low u v)).2 hg
    have hle : R2W01b.mantissa (low u v) ≤ R2W01b.mantissa (high u v) <<< gap u v := by
      rw [UInt32.le_iff_toNat_le, left_word_nat u v hd]
      omega
    rw [magnitudeWord, if_neg hsame, UInt32.toNat_sub_of_le _ _ hle, left_word_nat u v hd]
    exact (if_neg hne).symm

theorem base_word_nat (u v : UInt32) (hd : eligible u v = true) :
    ((if sameSign u v then (23 : UInt32) else 22) + gap u v).toNat = baseNat u v := by
  have hg := (eligible_conditions u v hd).2.2.1
  rw [UInt32.toNat_add, sameSign_sorted]
  by_cases hs : R2W01c.wordSign (high u v) = R2W01c.wordSign (low u v)
  · simp only [baseNat, R14WordAddAlignment.leadingBase, hs, beq_self_eq_true, ↓reduceIte]
    change (23 + (gap u v).toNat) % 4294967296 = 23 + (gap u v).toNat
    exact Nat.mod_eq_of_lt (by omega)
  · have hb : (R2W01c.wordSign (high u v) == R2W01c.wordSign (low u v)) = false := by
      cases h1 : R2W01c.wordSign (high u v) <;>
        cases h2 : R2W01c.wordSign (low u v) <;> simp_all
    simp only [baseNat, R14WordAddAlignment.leadingBase, if_neg hs, hb, Bool.false_eq_true, ↓reduceIte]
    change (22 + (gap u v).toNat) % 4294967296 = 22 + (gap u v).toNat
    exact Nat.mod_eq_of_lt (by omega)

theorem baseNat_bounds (u v : UInt32) (hd : eligible u v = true) :
    22 ≤ baseNat u v ∧ baseNat u v ≤ 30 := by
  have hg := (eligible_conditions u v hd).2.2.1
  unfold baseNat R14WordAddAlignment.leadingBase
  split <;> omega

theorem leadingWord_nat (u v : UInt32) (hd : eligible u v = true) :
    (leadingWord u v).toNat = (magnitudeNat u v).log2 := by
  have hb := baseNat_bounds u v hd
  have hl := magnitudeNat_log_bounds u v hd
  have hs := sorted_domain u v hd
  have he := R14WordAddAlignment.exact_log2 _ _ _ _ _
    (R2W01c.mantissa_bounds (high u v)).1 (R2W01c.mantissa_bounds (high u v)).2
    (R2W01c.mantissa_bounds (low u v)).1 (R2W01c.mantissa_bounds (low u v)).2
    hs.2.2.1 hs.2.2.2
  change (magnitudeNat u v).log2 = baseNat u v +
    (magnitudeNat u v >>> (baseNat u v + 1)) at he
  have hplus : (((if sameSign u v then (23 : UInt32) else 22) + gap u v) + 1).toNat =
      baseNat u v + 1 := by
    rw [UInt32.toNat_add, base_word_nat u v hd]
    change (baseNat u v + 1) % 4294967296 = _
    exact Nat.mod_eq_of_lt (by omega)
  unfold leadingWord
  rw [UInt32.toNat_add, UInt32.toNat_shiftRight, hplus,
    Nat.mod_eq_of_lt (by omega), magnitudeWord_nat u v hd, base_word_nat u v hd]
  rw [← he]
  exact Nat.mod_eq_of_lt (by omega)

theorem roundedWord_nat (u v : UInt32) (hd : eligible u v = true) :
    (roundedWord u v).toNat = R14NatNormal.rounded (magnitudeNat u v) := by
  have hb := magnitudeNat_bounds u v hd
  have hl := magnitudeNat_log_bounds u v hd
  have hle : (23 : UInt32) ≤ leadingWord u v := by
    rw [UInt32.le_iff_toNat_le, leadingWord_nat u v hd]
    change 23 ≤ (magnitudeNat u v).log2
    omega
  have hsub : ((leadingWord u v - 23).toUInt64).toNat = (magnitudeNat u v).log2 - 23 := by
    rw [UInt32.toNat_toUInt64, UInt32.toNat_sub_of_le _ _ hle, leadingWord_nat u v hd]
    rfl
  have hp : ((magnitudeWord u v).toUInt64).toNat < 281474976710656 := by
    rw [UInt32.toNat_toUInt64, magnitudeWord_nat u v hd]
    omega
  rw [roundedWord, R14SmallShiftBias.word_bias _ _ hp (by rw [hsub]; omega)
    (by rw [hsub]; omega), FixedWord.roundShiftRightEven_toNat,
    UInt32.toNat_toUInt64, magnitudeWord_nat u v hd, hsub]
  rfl

theorem small64_to32_nat (x : UInt64) (hx : x.toNat < 4294967296) :
    x.toUInt32.toNat = x.toNat := by
  rw [FastMul.toUInt32_eq]
  change x.toNat % 4294967296 = x.toNat
  exact Nat.mod_eq_of_lt hx

theorem carry_word_nat (u v : UInt32) (hd : eligible u v = true) :
    (roundedWord u v >>> 24).toUInt32.toNat = R14NatNormal.carry (magnitudeNat u v) := by
  have hb := magnitudeNat_bounds u v hd
  have hl := magnitudeNat_log_bounds u v hd
  have hn : magnitudeNat u v ≠ 0 := by omega
  have hh : 23 ≤ (magnitudeNat u v).log2 := by omega
  have hc := R14NatNormal.carry_le (magnitudeNat u v)
  have hr : (roundedWord u v >>> 24).toNat = R14NatNormal.carry (magnitudeNat u v) := by
    rw [UInt64.toNat_shiftRight, roundedWord_nat u v hd]
    exact R14WordAddRounding.shift_carry _ hn hh
  rw [small64_to32_nat _ (by rw [hr]; omega), hr]

theorem exponentWord_nat (u v : UInt32) (hd : eligible u v = true) :
    (exponentWord u v).toNat = (magnitudeNat u v).log2 +
      R2W01c.wordExp (low u v) - 23 + R14NatNormal.carry (magnitudeNat u v) := by
  have hl := magnitudeNat_log_bounds u v hd
  have he := (sorted_domain u v hd).2.1
  have hc := R14NatNormal.carry_le (magnitudeNat u v)
  have hsum : (leadingWord u v + R14ExponentShift.ex (low u v)).toNat =
      (magnitudeNat u v).log2 + R2W01c.wordExp (low u v) := by
    rw [UInt32.toNat_add, leadingWord_nat u v hd, R14ExponentShift.ex_nat]
    exact Nat.mod_eq_of_lt (by omega)
  have hle : (23 : UInt32) ≤ leadingWord u v + R14ExponentShift.ex (low u v) := by
    rw [UInt32.le_iff_toNat_le, hsum]
    change 23 ≤ (magnitudeNat u v).log2 + R2W01c.wordExp (low u v)
    omega
  rw [exponentWord, UInt32.toNat_add, UInt32.toNat_sub_of_le _ _ hle,
    hsum, carry_word_nat u v hd]
  change ((_ + _ - 23) + _) % 4294967296 = _
  exact Nat.mod_eq_of_lt (by omega)

theorem exponent_nat_lower (u v : UInt32) (hd : eligible u v = true) :
    2 ≤ (exponentWord u v).toNat := by
  have hl := magnitudeNat_log_bounds u v hd
  have he := (sorted_domain u v hd).2.1
  rw [exponentWord_nat u v hd]
  omega

theorem fractionWord_nat (u v : UInt32) (hd : eligible u v = true) :
    (fractionWord u v).toNat = R14NatNormal.mantissa (magnitudeNat u v) - 8388608 := by
  have hb := magnitudeNat_bounds u v hd
  have hl := magnitudeNat_log_bounds u v hd
  have hn : magnitudeNat u v ≠ 0 := by omega
  have hh : 23 ≤ (magnitudeNat u v).log2 := by omega
  have hr := R14WordAddRounding.rounded_bounds (magnitudeNat u v) hn hh
  rw [fractionWord, UInt32.toNat_and,
    small64_to32_nat _ (by rw [roundedWord_nat u v hd]; omega), roundedWord_nat u v hd]
  change R14NatNormal.rounded (magnitudeNat u v) &&& (2 ^ 23 - 1) = _
  rw [Nat.and_two_pow_sub_one_eq_mod]
  exact R14WordAddRounding.masked_fraction _ hn hh

theorem core_word (u v : UInt32) (hd : eligible u v = true) :
    core u v = Model.NativeBinary32.mkBits (R2W01c.wordSign (high u v))
      ((magnitudeNat u v).log2 + R2W01c.wordExp (low u v) - 23 +
        R14NatNormal.carry (magnitudeNat u v))
      (R14NatNormal.mantissa (magnitudeNat u v) - 8388608) := by
  have hsign : decide ((2147483648 : UInt32) ≤ high u v) = R2W01c.wordSign (high u v) := by
    simp only [R2W01c.wordSign, UInt32.le_iff_toNat_le]
    rfl
  calc
    core u v = FastMul.mkW (R2W01c.wordSign (high u v))
        (UInt32.ofNat (exponentWord u v).toNat) (UInt32.ofNat (fractionWord u v).toNat) := by
          rw [UInt32.ofNat_toNat, UInt32.ofNat_toNat]
          exact congrArg (fun s => FastMul.mkW s (exponentWord u v) (fractionWord u v)) hsign
    _ = Model.NativeBinary32.mkBits (R2W01c.wordSign (high u v))
        (exponentWord u v).toNat (fractionWord u v).toNat := FastMul.mkW_ofNat _ _ _
    _ = _ := by rw [exponentWord_nat u v hd, fractionWord_nat u v hd]

end Submission.R14WordAdd
