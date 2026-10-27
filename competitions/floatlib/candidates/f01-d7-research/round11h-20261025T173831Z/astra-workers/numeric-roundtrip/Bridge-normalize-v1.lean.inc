/- R17 conditional normalization helpers. Fixed-environment elaboration is pending. -/
namespace Submission.R17NumericNormalize

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

theorem output_exponent_bounds (ehi elo d adjust bump : Nat)
    (helo : 1 ≤ elo) (horder : elo ≤ ehi) (hehi : ehi ≤ 254)
    (hd : d = ehi - elo) (ha : adjust ≤ 1) (had : adjust ≤ d)
    (hb : bump ≤ 1) :
    1 ≤ ehi - adjust + bump ∧ ehi - adjust + bump ≤ 255 := by
  omega

theorem output_exponent_guard (ehi elo d adjust bump : Nat)
    (helo : 1 ≤ elo) (horder : elo ≤ ehi) (hehi : ehi ≤ 254)
    (hd : d = ehi - elo) (ha : adjust ≤ 1) (had : adjust ≤ d)
    (hb : bump ≤ 1) (hg : ehi - adjust + bump ≤ 254) :
    0 < ehi - adjust + bump ∧ ehi - adjust + bump < 255 := by
  have h := output_exponent_bounds ehi elo d adjust bump helo horder hehi hd ha had hb
  omega

theorem numeric_shift_toNat (n shift : UInt32)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat ≤ 2164260735)
    (hs : shift.toNat = R16UInt32Roundtrip.roundedShift n.toNat) :
    (n.toFloat32.toUInt32 >>> shift).toNat = R14NatNormal.mantissa n.toNat := by
  have hl := R16UInt32Roundtrip.rounded_leading n.toNat hlo hhi
  have hsb : shift.toNat < 32 := by
    rw [hs]
    unfold R16UInt32Roundtrip.roundedShift
    omega
  rw [UInt32.toNat_shiftRight, Nat.mod_eq_of_lt hsb, hs,
    R16UInt32Roundtrip.high_roundtrip n hlo hhi]
  unfold R16UInt32Roundtrip.roundedInteger
  simp [Nat.shiftRight_eq_div_pow, Nat.two_pow_pos]

theorem numeric_fraction_toNat (n shift : UInt32)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat ≤ 2164260735)
    (hs : shift.toNat = R16UInt32Roundtrip.roundedShift n.toNat) :
    ((n.toFloat32.toUInt32 >>> shift) &&& (0x7fffff : UInt32)).toNat =
      R14NatNormal.mantissa n.toNat - 8388608 := by
  have hm := R16UInt32Roundtrip.high_mantissa n.toNat hlo hhi
  rw [UInt32.toNat_and, numeric_shift_toNat n shift hlo hhi hs]
  change R14NatNormal.mantissa n.toNat &&& (2 ^ 23 - 1) = _
  rw [Nat.and_two_pow_sub_one_eq_mod]
  norm_num
  omega

end Submission.R17NumericNormalize
