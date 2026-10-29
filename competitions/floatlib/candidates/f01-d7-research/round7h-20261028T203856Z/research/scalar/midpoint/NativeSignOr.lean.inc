/- Actual positive native64 words with the sign bit set by OR.
   The stored-word model equality is established before real negation. -/
namespace Submission.R24NativeSignOr
open FloatLib.Numerics
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

@[inline] def word (w : UInt64) : UInt64 := w ||| 0x8000000000000000

theorem raw_eq_neg (w : UInt64) (hw : w.toNat < 9223372036854775808) :
    R24RepresentationWiden.raw64 (word w) = Model.neg (R24RepresentationWiden.raw64 w) := by
  have hp : w.toNat < 2 ^ 63 := hw
  have hword : (word w).toNat = w.toNat + 9223372036854775808 := by
    rw [word, UInt64.toNat_or]
    change w.toNat ||| 2 ^ 63 = w.toNat + 2 ^ 63
    rw [Nat.or_comm]
    simpa only [Nat.mul_one, Nat.add_comm] using (Nat.two_pow_add_eq_or_of_lt hp 1).symm
  have hs0 : decide (9223372036854775808 ≤ w.toNat) = false := by
    simp only [show ¬ 9223372036854775808 ≤ w.toNat by omega, decide_false]
  have hs1 : decide (9223372036854775808 ≤ w.toNat + 9223372036854775808) = true := by
    simp only [show 9223372036854775808 ≤ w.toNat + 9223372036854775808 by omega, decide_true]
  have he : (w.toNat + 9223372036854775808) / 4503599627370496 % 2048 =
      w.toNat / 4503599627370496 % 2048 := by
    rw [show (9223372036854775808 : Nat) = 4503599627370496 * 2048 by decide,
      Nat.add_mul_div_left _ _ (by decide)]
    simp only [Nat.add_mod, Nat.mod_self, Nat.add_zero, Nat.mod_mod]
  have hf : (w.toNat + 9223372036854775808) % 4503599627370496 =
      w.toNat % 4503599627370496 := by
    rw [Nat.add_mod]
    norm_num
  rw [R24RepresentationWiden.raw64_eq_fields (word w),
    R24RepresentationWiden.raw64_eq_fields w,
    Model.neg_ofFields_of_supportsSignedZero FloatFormat.binary64 (by decide)]
  simp only [hword, hs0, hs1, he, hf, Bool.not_false]

theorem native_real_neg (w : UInt64) (mantissa : Nat) (exponent : Int)
    (hd : Model.toDyadic? (R24RepresentationWiden.raw64 w) =
      some ⟨false, mantissa, exponent⟩) :
    R24MidpointReal.nativeReal (word w) = -R24MidpointReal.nativeReal w := by
  have hs : Model.signBit (R24RepresentationWiden.raw64 w) = false :=
    (Model.sign_eq_signBit_of_toDyadic?_some hd).symm
  rw [R24RepresentationWiden.raw64_sign] at hs
  have hnot := of_decide_eq_false hs
  have hw : w.toNat < 9223372036854775808 := by omega
  have hword := raw_eq_neg w hw
  have hdneg := Model.toDyadic?_neg_of_toDyadic?_some (R24RepresentationWiden.raw64 w) hd
  rw [← hword] at hdneg
  unfold R24MidpointReal.nativeReal
  rw [R24RepresentationWiden.native_ofBits_of_decode (word w) hdneg,
    R24RepresentationWiden.native_ofBits_of_decode w hd, hword,
    Model.toReal_neg _ (Model.isFinite_eq_true_of_toDyadic?_some hd)]

end Submission.R24NativeSignOr
