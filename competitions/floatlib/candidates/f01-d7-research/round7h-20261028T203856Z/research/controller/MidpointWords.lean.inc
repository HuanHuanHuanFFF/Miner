/- R24 positive binary32-normal midpoint words. Actual UInt64 arithmetic;
   no opaque cast premise. This only proves decodes, not a full RNE32 cell
   theorem, negative-sign wrapper, native endpoint computation or speed. -/
namespace Submission.R24MidpointWords
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

abbrev F64 := FloatFormat.binary64
abbrev raw (w : UInt64) : Model F64 := Model.ofBits w.toBitVec

@[inline] def center (e f : UInt64) : UInt64 :=
  ((e + 896) <<< 52) + (f <<< 29)

@[inline] def upper (e f : UInt64) : UInt64 := center e f + 0x10000000

@[inline] def lower (e f : UInt64) : UInt64 :=
  if e = 1 ∧ f = 0 then center e f - 0x20000000
  else center e f - 0x10000000

private theorem center_nat (e f : UInt64)
    (he : e.toNat < 255) (hf : f.toNat < 8388608) :
    (center e f).toNat = (e.toNat + 896) * 4503599627370496 + f.toNat * 536870912 := by
  have hea : (e + 896).toNat = e.toNat + 896 := by
    rw [UInt64.toNat_add]
    change (e.toNat + 896) % 18446744073709551616 = e.toNat + 896
    omega
  have hes : ((e + 896) <<< 52).toNat = (e.toNat + 896) * 4503599627370496 := by
    rw [UInt64.toNat_shiftLeft, hea]
    change ((e.toNat + 896) <<< 52) % 18446744073709551616 = _
    rw [Nat.shiftLeft_eq]
    omega
  have hfs : (f <<< 29).toNat = f.toNat * 536870912 := by
    rw [UInt64.toNat_shiftLeft]
    change (f.toNat <<< 29) % 18446744073709551616 = _
    rw [Nat.shiftLeft_eq]
    omega
  rw [center, UInt64.toNat_add, hes, hfs]
  change ((e.toNat + 896) * 4503599627370496 + f.toNat * 536870912) %
    18446744073709551616 = _
  omega

private theorem raw_sign (w : UInt64) :
    Model.signBit (raw w) = decide (9223372036854775808 ≤ w.toNat) := by
  rw [Model.signBit_eq_msb]
  exact BitVec.msb_eq_decide w.toBitVec

private theorem raw_exp (w : UInt64) :
    Model.expField (raw w) = w.toNat / 4503599627370496 % 2048 := by
  unfold Model.expField
  change ((w.toBitVec >>> 52) &&& (BitVec.ofNat 64 2047)).toNat = _
  rw [BitVec.toNat_and, BitVec.toNat_ushiftRight]
  change (w.toNat >>> 52) &&& (2 ^ 11 - 1) = w.toNat / 4503599627370496 % 2 ^ 11
  rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]

private theorem raw_frac (w : UInt64) :
    Model.fracField (raw w) = w.toNat % 4503599627370496 := by
  unfold Model.fracField
  change (w.toBitVec &&& (BitVec.ofNat 64 4503599627370495)).toNat = _
  rw [BitVec.toNat_and]
  change w.toNat &&& (2 ^ 52 - 1) = w.toNat % 2 ^ 52
  exact Nat.and_two_pow_sub_one_eq_mod w.toNat 52

private theorem raw_fields (w : UInt64) (E F : Nat)
    (he : E < 2047) (hf : F < 4503599627370496)
    (hw : w.toNat = E * 4503599627370496 + F) :
    raw w = Model.ofFields F64 false E F := by
  have hs : Model.signBit (raw w) = false := by
    rw [raw_sign]
    apply Bool.eq_iff_iff.mpr
    simp only [decide_eq_true_eq, Bool.false_eq_true]
    omega
  have hE : Model.expField (raw w) = E := by rw [raw_exp, hw]; omega
  have hF : Model.fracField (raw w) = F := by rw [raw_frac, hw]; omega
  rw [← hs, ← hE, ← hF]
  exact (Model.ofFields_signBit_expField_fracField (raw w)).symm

private theorem decode_fields (w : UInt64) (E F : Nat)
    (he0 : 0 < E) (he : E < 2047) (hf : F < 4503599627370496)
    (hw : w.toNat = E * 4503599627370496 + F) :
    Model.toDyadic? (raw w) =
      some ⟨false, 4503599627370496 + F, (E : Int) - 1023 - 52⟩ := by
  rw [raw_fields w E F he hf hw]
  exact Model.toDyadic?_ofFields_normal F64 false E F (Nat.ne_of_gt he0) he hf

theorem upper_decode (e f : UInt64)
    (he0 : 0 < e.toNat) (he : e.toNat < 255) (hf : f.toNat < 8388608) :
    Model.toDyadic? (raw (upper e f)) =
      some ⟨false, 4503599627370496 + (2 * f.toNat + 1) * 268435456,
        ((e.toNat + 896 : Nat) : Int) - 1023 - 52⟩ := by
  have hw : (upper e f).toNat =
      (e.toNat + 896) * 4503599627370496 + (2 * f.toNat + 1) * 268435456 := by
    rw [upper, UInt64.toNat_add, center_nat e f he hf]
    change ((e.toNat + 896) * 4503599627370496 + f.toNat * 536870912 + 268435456) %
      18446744073709551616 = _
    omega
  exact decode_fields _ _ _ (by omega) (by omega) (by omega) hw

theorem lower_inner_decode (e f : UInt64)
    (he0 : 0 < e.toNat) (he : e.toNat < 255)
    (hf0 : 0 < f.toNat) (hf : f.toNat < 8388608) :
    Model.toDyadic? (raw (lower e f)) =
      some ⟨false, 4503599627370496 + (2 * f.toNat - 1) * 268435456,
        ((e.toNat + 896 : Nat) : Int) - 1023 - 52⟩ := by
  have hn : ¬ (e = 1 ∧ f = 0) := by
    intro h
    have hz : f.toNat = 0 := by rw [h.2]; rfl
    omega
  have hsub : (0x10000000 : UInt64) ≤ center e f := by
    rw [UInt64.le_iff_toNat_le, center_nat e f he hf]
    change 268435456 ≤ _
    omega
  have hw : (lower e f).toNat =
      (e.toNat + 896) * 4503599627370496 + (2 * f.toNat - 1) * 268435456 := by
    rw [lower, if_neg hn, UInt64.toNat_sub_of_le _ _ hsub, center_nat e f he hf]
    change (e.toNat + 896) * 4503599627370496 + f.toNat * 536870912 - 268435456 = _
    omega
  exact decode_fields _ _ _ (by omega) (by omega) (by omega) hw

theorem lower_power_decode (e : UInt64)
    (he0 : 1 < e.toNat) (he : e.toNat < 255) :
    Model.toDyadic? (raw (lower e 0)) =
      some ⟨false, 9007199254740992 - 268435456,
        ((e.toNat + 895 : Nat) : Int) - 1023 - 52⟩ := by
  have hn : ¬ (e = 1 ∧ (0 : UInt64) = 0) := by
    intro h
    have hz : e.toNat = 1 := by rw [h.1]; rfl
    omega
  have hsub : (0x10000000 : UInt64) ≤ center e 0 := by
    rw [UInt64.le_iff_toNat_le, center_nat e 0 he (by decide)]
    change 268435456 ≤ _
    omega
  have hw : (lower e 0).toNat =
      (e.toNat + 895) * 4503599627370496 + (4503599627370496 - 268435456) := by
    rw [lower, if_neg hn, UInt64.toNat_sub_of_le _ _ hsub, center_nat e 0 he (by decide)]
    change (e.toNat + 896) * 4503599627370496 + 0 * 536870912 - 268435456 = _
    omega
  have hd := decode_fields (lower e 0) (e.toNat + 895)
    (4503599627370496 - 268435456) (by omega) (by omega) (by decide) hw
  exact hd

theorem lower_minNormal_decode :
    Model.toDyadic? (raw (lower 1 0)) =
      some ⟨false, 9007199254740992 - 536870912, (-179 : Int)⟩ := by
  decide

end Submission.R24MidpointWords
