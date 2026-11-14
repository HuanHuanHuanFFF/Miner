/- Proof views of the existing PortableF64 certify endpoint expressions.
   No entrypoint or runtime checker is modified. -/
namespace Submission.R24RawMidpoint
open FloatLib.Numerics
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

@[inline] def magnitude (q : UInt32) : UInt32 := q &&& 0x7fffffff
@[inline] def eWord (q : UInt32) : UInt64 := (Model.NativeBinary32.expField (magnitude q)).toUInt64
@[inline] def fWord (q : UInt32) : UInt64 := (Model.NativeBinary32.fracField (magnitude q)).toUInt64
@[inline] def base (q : UInt32) : UInt64 := ((eWord q + 896) <<< 52) ||| (fWord q <<< 29)
@[inline] def below (q : UInt32) : UInt64 :=
  base q - (if magnitude q == 0x00800000 then 0x20000000 else 0x10000000)
@[inline] def above (q : UInt32) : UInt64 := base q + 0x10000000
@[inline] def lowerWord (q : UInt32) : UInt64 :=
  if Model.NativeBinary32.signBit q then R24NativeSignOr.word (above q) else below q
@[inline] def upperWord (q : UInt32) : UInt64 :=
  if Model.NativeBinary32.signBit q then R24NativeSignOr.word (below q) else above q

private theorem magnitude_nat (q : UInt32) : (magnitude q).toNat = q.toNat % 2147483648 := by
  rw [magnitude, UInt32.toNat_and]
  change q.toNat &&& (2 ^ 31 - 1) = q.toNat % 2 ^ 31
  exact Nat.and_two_pow_sub_one_eq_mod q.toNat 31

private theorem exp_nat (q : UInt32) :
    (Model.NativeBinary32.expField q).toNat = q.toNat / 8388608 % 256 := by
  rw [Model.NativeBinary32.expField, UInt32.toNat_and, UInt32.toNat_shiftRight]
  change (q.toNat >>> 23) &&& (2 ^ 8 - 1) = q.toNat / 2 ^ 23 % 2 ^ 8
  rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]

private theorem frac_nat (q : UInt32) :
    (Model.NativeBinary32.fracField q).toNat = q.toNat % 8388608 := by
  rw [Model.NativeBinary32.fracField, UInt32.toNat_and]
  change q.toNat &&& (2 ^ 23 - 1) = q.toNat % 2 ^ 23
  exact Nat.and_two_pow_sub_one_eq_mod q.toNat 23

theorem magnitude_exp (q : UInt32) :
    Model.NativeBinary32.expField (magnitude q) = Model.NativeBinary32.expField q := by
  apply UInt32.toNat_inj.mp
  rw [exp_nat, exp_nat, magnitude_nat]
  rw [show (2147483648 : Nat) = 8388608 * 256 by decide,
    Nat.mod_mul_right_div_self, Nat.mod_mod]

theorem magnitude_frac (q : UInt32) :
    Model.NativeBinary32.fracField (magnitude q) = Model.NativeBinary32.fracField q := by
  apply UInt32.toNat_inj.mp
  rw [frac_nat, frac_nat, magnitude_nat]
  rw [show (2147483648 : Nat) = 8388608 * 256 by decide, Nat.mod_mul_right_mod]

theorem fields (q : UInt32) :
    (eWord q).toNat = (Model.NativeBinary32.expField q).toNat ∧
      (fWord q).toNat = (Model.NativeBinary32.fracField q).toNat := by
  simp only [eWord, fWord, magnitude_exp, magnitude_frac, UInt32.toNat_toUInt64, and_self]

private theorem minnormal_iff (q : UInt32) :
    magnitude q = 0x00800000 ↔ eWord q = 1 ∧ fWord q = 0 := by
  constructor
  · intro h
    constructor
    · simp only [eWord, h] <;> decide
    · simp only [fWord, h] <;> decide
  · rintro ⟨he, hf⟩
    have hE : (Model.NativeBinary32.expField q).toNat = 1 := by
      rw [← (fields q).1, he]
    have hF : (Model.NativeBinary32.fracField q).toNat = 0 := by
      rw [← (fields q).2, hf]
    apply UInt32.toNat_inj.mp
    rw [magnitude_nat]
    change q.toNat % 2147483648 = 8388608
    have hsplit := @Nat.mod_mul 8388608 256 q.toNat
    rw [← frac_nat q, ← exp_nat q, hE, hF] at hsplit
    simpa using hsplit

theorem base_eq_center (q : UInt32) : base q = R24MidpointWords.center (eWord q) (fWord q) := by
  have he : eWord q = (R24RepresentationWiden.expWord q).toUInt64 := by
    simp only [eWord, magnitude_exp] <;> rfl
  have hf : fWord q = (R24RepresentationWiden.fracWord q).toUInt64 := by
    simp only [fWord, magnitude_frac] <;> rfl
  have hE : ((eWord q + 896) <<< 52).toNat =
      (R2W01c.wordExp q + 896) * 4503599627370496 := by
    rw [he]
    exact R24RepresentationWiden.expWide_shift_toNat q
  have hF : (fWord q <<< 29).toNat = R2W01c.wordFrac q * 536870912 := by
    rw [hf]
    exact R24RepresentationWiden.fracWide_shift_toNat q
  have hfsmall : R2W01c.wordFrac q * 536870912 < 2 ^ 52 := by
    calc
      _ < (2 ^ 23) * 536870912 :=
        Nat.mul_lt_mul_of_pos_right (R2W01c.wordFrac_lt q) (by norm_num)
      _ = 2 ^ 52 := by norm_num
  have hecount : R2W01c.wordExp q + 896 + 1 ≤ 2048 := by
    have h := R24RepresentationWiden.wordExp_lt q
    omega
  have hsum : (R2W01c.wordExp q + 896) * 4503599627370496 +
      R2W01c.wordFrac q * 536870912 < 18446744073709551616 := by
    calc
      _ < (R2W01c.wordExp q + 896) * 4503599627370496 + 2 ^ 52 :=
        Nat.add_lt_add_left hfsmall _
      _ = 4503599627370496 * (R2W01c.wordExp q + 896 + 1) := by ring
      _ ≤ 4503599627370496 * 2048 := Nat.mul_le_mul_left _ hecount
      _ < 18446744073709551616 := by norm_num
  have hor : ((R2W01c.wordExp q + 896) * 4503599627370496) |||
      (R2W01c.wordFrac q * 536870912) =
      (R2W01c.wordExp q + 896) * 4503599627370496 + R2W01c.wordFrac q * 536870912 := by
    rw [Nat.mul_comm (R2W01c.wordExp q + 896) 4503599627370496]
    exact (Nat.two_pow_add_eq_or_of_lt hfsmall _).symm
  apply UInt64.toNat_inj.mp
  simp only [base, R24MidpointWords.center, UInt64.toNat_or, UInt64.toNat_add, hE, hF]
  rw [hor, Nat.mod_eq_of_lt hsum]

theorem endpoint_words (q : UInt32) :
    below q = R24MidpointWords.lower (eWord q) (fWord q) ∧
      above q = R24MidpointWords.upper (eWord q) (fWord q) := by
  constructor
  · unfold below R24MidpointWords.lower
    rw [base_eq_center]
    simp only [beq_iff_eq]
    rw [show (magnitude q = 0x00800000) = (eWord q = 1 ∧ fWord q = 0) from
      propext (minnormal_iff q)]
    by_cases h : eWord q = 1 ∧ fWord q = 0 <;> simp only [h, ite_true, ite_false]
  · rw [above, R24MidpointWords.upper, base_eq_center]

private theorem lower_negative_real (e f : UInt64)
    (he0 : 0 < e.toNat) (he : e.toNat < 255) (hf : f.toNat < 8388608) :
    R24MidpointReal.nativeReal (R24NativeSignOr.word (R24MidpointWords.lower e f)) =
      -R24MidpointReal.nativeReal (R24MidpointWords.lower e f) := by
  by_cases hf0 : f.toNat = 0
  · have hfw : f = 0 := by
      apply UInt64.toNat_inj.mp
      simpa only [UInt64.toNat_zero] using hf0
    subst f
    by_cases he1 : e.toNat = 1
    · have hew : e = 1 := by apply UInt64.toNat_inj.mp; exact he1
      subst e
      exact R24NativeSignOr.native_real_neg _ _ _ R24MidpointWords.lower_minNormal_decode
    · exact R24NativeSignOr.native_real_neg _ _ _
        (R24MidpointWords.lower_power_decode e (by omega) he)
  · exact R24NativeSignOr.native_real_neg _ _ _
      (R24MidpointWords.lower_inner_decode e f he0 he (by omega) hf)

theorem signed_endpoint_reals (q : UInt32)
    (he0 : 1 ≤ (Model.NativeBinary32.expField q).toNat)
    (he : (Model.NativeBinary32.expField q).toNat ≤ 254) :
    R24MidpointReal.nativeReal (lowerWord q) =
      R24NormalCell.lowerSigned (Model.NativeBinary32.signBit q)
        (Model.NativeBinary32.expField q).toNat (Model.NativeBinary32.fracField q).toNat ∧
    R24MidpointReal.nativeReal (upperWord q) =
      R24NormalCell.upperSigned (Model.NativeBinary32.signBit q)
        (Model.NativeBinary32.expField q).toNat (Model.NativeBinary32.fracField q).toNat := by
  have hE0 : 0 < (eWord q).toNat := by rw [(fields q).1]; omega
  have hE : (eWord q).toNat < 255 := by rw [(fields q).1]; omega
  have hF : (fWord q).toNat < 8388608 := by
    rw [(fields q).2, frac_nat]
    exact Nat.mod_lt _ (by decide)
  have hL := R24MidpointReal.lower_real (eWord q) (fWord q) hE0 hE hF
  have hU := R24MidpointReal.upper_real (eWord q) (fWord q) hE0 hE hF
  have hNL := lower_negative_real (eWord q) (fWord q) hE0 hE hF
  have hNU := R24NativeSignOr.native_real_neg _ _ _
    (R24MidpointWords.upper_decode (eWord q) (fWord q) hE0 hE hF)
  rw [(fields q).1, (fields q).2] at hL hU
  cases hs : Model.NativeBinary32.signBit q <;>
    simp only [lowerWord, upperWord, hs, R24NormalCell.lowerSigned, R24NormalCell.upperSigned,
      Bool.false_eq_true, Bool.true_eq_true, ite_false, ite_true, (endpoint_words q).1,
      (endpoint_words q).2, hNL, hNU, hL, hU, and_self]

theorem roundRatScaled_of_endpoint_bounds (q : UInt32) (sign : Bool) (num den : Nat)
    (source : Int) (S : Real) (hd : 0 < den)
    (he0 : 1 ≤ (Model.NativeBinary32.expField q).toNat)
    (he : (Model.NativeBinary32.expField q).toNat ≤ 254)
    (hsource : S = Model.signedScaledRatToReal sign num den source)
    (hl : R24MidpointReal.nativeReal (lowerWord q) < S)
    (hu : S < R24MidpointReal.nativeReal (upperWord q)) :
    Model.NativeBinary32.roundRatScaled sign num den source = q := by
  have hends := signed_endpoint_reals q he0 he
  rw [hends.1] at hl
  rw [hends.2] at hu
  have hf : (Model.NativeBinary32.fracField q).toNat < 8388608 := by
    rw [frac_nat]
    exact Nat.mod_lt _ (by decide)
  exact R24NormalCell.native32_raw_strict q sign num den source S hd he0 he hf hsource hl hu

end Submission.R24RawMidpoint
