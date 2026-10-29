/- R25 minimal carrier of the existing R24PortableF64.widenBits nonzero-subnormal branch.
   This fragment defines proof abbreviations, not a new widening runtime.
   Include the unchanged actual PortableF64Dot definition and retained FastMul.
   Normal inputs, zero inputs and exponent255 are outside this theorem. -/
namespace Submission.R24SubnormalWiden
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

abbrev F64 := FloatFormat.binary64
abbrev raw (w : UInt64) : Model F64 := Model.ofBits w.toBitVec
abbrev native (x : Float) : Model F64 := Model.ofFloatModel x.toModel
abbrev frac (u : UInt32) : UInt64 := (u &&& 0x7fffff).toUInt64
abbrev n (u : UInt32) : Nat := (u &&& 0x7fffff).toNat
abbrev lead (u : UInt32) : UInt64 := Submission.FastMul.fastLog2 (frac u)
abbrev ell (u : UInt32) : Nat := (n u).log2
abbrev remWide (u : UInt32) : Nat := (n u - 2 ^ ell u) * 2 ^ (52 - ell u)

private theorem frac_nat (u : UInt32) : (frac u).toNat = n u :=
  UInt32.toNat_toUInt64 _

private theorem frac_lt (u : UInt32) : n u < 2 ^ 23 := by
  rw [n, UInt32.toNat_and]
  change u.toNat &&& (2 ^ 23 - 1) < 2 ^ 23
  rw [Nat.and_two_pow_sub_one_eq_mod]
  exact Nat.mod_lt _ (by decide)

private theorem lead_nat (u : UInt32) : (lead u).toNat = ell u := by
  rw [lead, Submission.FastMul.fastLog2_eq]
  change (frac u).toNat.log2 = (n u).log2
  rw [frac_nat]

private theorem bounds (u : UInt32) (hn : 0 < n u) :
    ell u ≤ 22 ∧ 2 ^ ell u ≤ n u ∧ n u < 2 ^ (ell u + 1) ∧
      2 ^ ell u * 2 ^ (52 - ell u) = 2 ^ 52 ∧ remWide u < 2 ^ 52 := by
  have hl : ell u < 23 := (Nat.log2_lt hn.ne').mpr (frac_lt u)
  have hlo : 2 ^ ell u ≤ n u := Nat.log2_self_le hn.ne'
  have hhi : n u < 2 ^ (ell u + 1) := Nat.lt_log2_self
  have hpow : 2 ^ ell u * 2 ^ (52 - ell u) = 2 ^ 52 := by
    rw [← Nat.pow_add]
    congr 1
    omega
  have hdiff : n u - 2 ^ ell u < 2 ^ ell u := by
    have hh := hhi
    rw [Nat.pow_succ] at hh
    omega
  have hr : remWide u < 2 ^ 52 := by
    unfold remWide
    calc
      _ < 2 ^ ell u * 2 ^ (52 - ell u) :=
        Nat.mul_lt_mul_of_pos_right hdiff (Nat.two_pow_pos _)
      _ = 2 ^ 52 := hpow
  exact ⟨by omega, hlo, hhi, hpow, hr⟩

private theorem one_shift_nat (u : UInt32) (hn : 0 < n u) :
    ((1 : UInt64) <<< lead u).toNat = 2 ^ ell u := by
  have hl := (bounds u hn).1
  have hp : 2 ^ ell u < 2 ^ 64 := Nat.pow_lt_pow_right (by decide) (by omega)
  rw [UInt64.toNat_shiftLeft, lead_nat, Nat.mod_eq_of_lt (by omega : ell u < 64)]
  change ((1 : Nat) <<< ell u) % 18446744073709551616 = _
  rw [Nat.shiftLeft_eq]
  simpa only [one_mul] using Nat.mod_eq_of_lt hp

private theorem count_nat (u : UInt32) (hn : 0 < n u) :
    ((52 : UInt64) - lead u).toNat = 52 - ell u := by
  have hl := (bounds u hn).1
  have hle : lead u ≤ (52 : UInt64) := by
    rw [UInt64.le_iff_toNat_le, lead_nat]
    change ell u ≤ 52
    omega
  simpa only [lead_nat] using UInt64.toNat_sub_of_le (52 : UInt64) (lead u) hle

private theorem fraction_shift_nat (u : UInt32) (hn : 0 < n u) :
    ((frac u - ((1 : UInt64) <<< lead u)) <<< (52 - lead u)).toNat = remWide u := by
  have hb := bounds u hn
  have hle : (1 : UInt64) <<< lead u ≤ frac u := by
    rw [UInt64.le_iff_toNat_le, one_shift_nat u hn, frac_nat]
    exact hb.2.1
  have hcount : 52 - ell u < 64 := by omega
  have hr64 : remWide u < 2 ^ 64 := hb.2.2.2.2.trans (by norm_num)
  rw [UInt64.toNat_shiftLeft, count_nat u hn, Nat.mod_eq_of_lt hcount,
    UInt64.toNat_sub_of_le _ _ hle, frac_nat, one_shift_nat u hn,
    Nat.shiftLeft_eq]
  change remWide u % 18446744073709551616 = remWide u
  exact Nat.mod_eq_of_lt hr64

private theorem exponent_shift_nat (u : UInt32) (hn : 0 < n u) :
    ((lead u + 874) <<< 52).toNat = (ell u + 874) * 4503599627370496 := by
  have hl := (bounds u hn).1
  have hE : (lead u + 874).toNat = ell u + 874 := by
    rw [UInt64.toNat_add, lead_nat]
    change (ell u + 874) % 18446744073709551616 = _
    omega
  rw [UInt64.toNat_shiftLeft, hE]
  change ((ell u + 874) <<< 52) % 18446744073709551616 = _
  rw [Nat.shiftLeft_eq]
  omega

private theorem sign_shift_nat (u : UInt32) :
    ((u.toUInt64 &&& 0x80000000) <<< 32).toNat =
      u.toNat / 2147483648 * 9223372036854775808 := by
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  have hmask : u.toNat &&& 2 ^ 31 = u.toNat / 2147483648 * 2147483648 := by
    rw [Nat.and_two_pow, Nat.testBit_eq_decide_div_mod_eq]
    change (decide (u.toNat / 2147483648 % 2 = 1)).toNat * 2147483648 = _
    by_cases h : u.toNat < 2147483648
    · have hq : u.toNat / 2147483648 = 0 := Nat.div_eq_of_lt h
      simp [hq]
    · have hq : u.toNat / 2147483648 = 1 := by omega
      simp [hq]
  rw [UInt64.toNat_shiftLeft, UInt64.toNat_and, UInt32.toNat_toUInt64]
  change ((u.toNat &&& 2 ^ 31) <<< 32) % 18446744073709551616 = _
  rw [hmask, Nat.shiftLeft_eq]
  omega

private theorem widen_nat (u : UInt32)
    (he : ((u >>> 23) &&& 255) = 0) (hn : 0 < n u) :
    (Submission.R24PortableF64.widenBits u).toNat =
      u.toNat / 2147483648 * 9223372036854775808 +
        (ell u + 874) * 4503599627370496 + remWide u := by
  have hb := bounds u hn
  have hl := hb.1
  have hf : frac u ≠ 0 := by
    intro h
    have h0 : (frac u).toNat = 0 := by rw [h]; rfl
    rw [frac_nat] at h0
    omega
  have hf0 : ((u &&& 0x7fffff).toUInt64 == 0) = false := by
    simpa [frac] using hf
  have hbody : Submission.R24PortableF64.widenBits u =
      ((u.toUInt64 &&& 0x80000000) <<< 32) ||| ((lead u + 874) <<< 52) |||
        ((frac u - ((1 : UInt64) <<< lead u)) <<< (52 - lead u)) := by
    simp [Submission.R24PortableF64.widenBits, he, frac, lead, hf0]
  rw [hbody, UInt64.toNat_or, UInt64.toNat_or, sign_shift_nat,
    exponent_shift_nat u hn, fraction_shift_nat u hn]
  have hE : (ell u + 874) * 4503599627370496 < 2 ^ 63 := by
    change (ell u + 874) * 4503599627370496 < 9223372036854775808
    omega
  have hSE : (u.toNat / 2147483648 * 9223372036854775808) |||
      ((ell u + 874) * 4503599627370496) =
      u.toNat / 2147483648 * 9223372036854775808 +
        (ell u + 874) * 4503599627370496 := by
    rw [Nat.mul_comm (u.toNat / 2147483648) 9223372036854775808]
    exact (Nat.two_pow_add_eq_or_of_lt hE (u.toNat / 2147483648)).symm
  rw [hSE]
  have hbase : u.toNat / 2147483648 * 9223372036854775808 +
      (ell u + 874) * 4503599627370496 =
        2 ^ 52 * (u.toNat / 2147483648 * 2048 + ell u + 874) := by
    change _ = 4503599627370496 * _
    omega
  rw [hbase]
  exact (Nat.two_pow_add_eq_or_of_lt hb.2.2.2.2 _).symm

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

private theorem subnormal_decode (u : UInt32)
    (he : ((u >>> 23) &&& 255) = 0) (hn : 0 < n u) :
    Model.toDyadic? (raw (Submission.R24PortableF64.widenBits u)) =
      some ⟨decide (2147483648 ≤ u.toNat), n u * 2 ^ (52 - ell u), (ell u : Int) - 201⟩ := by
  have hb := bounds u hn
  have hl := hb.1
  have hlo := hb.2.1
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  have hw := widen_nat u he hn
  have hs : Model.signBit (raw (Submission.R24PortableF64.widenBits u)) =
      decide (2147483648 ≤ u.toNat) := by
    rw [raw_sign]
    apply Bool.eq_iff_iff.mpr
    simp only [decide_eq_true_eq]
    have hr := hb.2.2.2.2
    change remWide u < 4503599627370496 at hr
    omega
  have hE : Model.expField (raw (Submission.R24PortableF64.widenBits u)) = ell u + 874 := by
    rw [raw_exp, hw]
    have hr := hb.2.2.2.2
    change remWide u < 4503599627370496 at hr
    omega
  have hF : Model.fracField (raw (Submission.R24PortableF64.widenBits u)) = remWide u := by
    rw [raw_frac, hw]
    have hr := hb.2.2.2.2
    change remWide u < 4503599627370496 at hr
    omega
  have hfields : raw (Submission.R24PortableF64.widenBits u) =
      Model.ofFields F64 (decide (2147483648 ≤ u.toNat)) (ell u + 874) (remWide u) := by
    rw [← hs, ← hE, ← hF]
    exact (Model.ofFields_signBit_expField_fracField _).symm
  rw [hfields]
  have hd := Model.toDyadic?_ofFields_normal F64 (decide (2147483648 ≤ u.toNat))
    (ell u + 874) (remWide u) (by omega) (by change ell u + 874 < 2047; omega) hb.2.2.2.2
  have hm : 4503599627370496 + remWide u = n u * 2 ^ (52 - ell u) := by
    have hp := hb.2.2.2.1
    change 2 ^ ell u * 2 ^ (52 - ell u) = 4503599627370496 at hp
    rw [← hp, remWide, ← Nat.add_mul]
    congr 1
    omega
  have hexp : ((ell u + 874 : Nat) : Int) - 1023 - 52 = (ell u : Int) - 201 := by omega
  simpa only [hm, hexp] using hd

private theorem native_finite_eq (x : Float) : Model.isFinite (native x) = x.isFinite := by
  rw [← Model.toDyadic?_isSome_eq_isFinite,
    Model.toDyadic?_ieee_eq_model F64 (by decide), Model.toModel_ofFloatModel]
  change (Model.unpackedToDyadic? x.toModel.unpack).isSome = x.toModel.unpack.isFinite
  cases x.toModel.unpack <;> rfl

private theorem native_ofBits_decode (w : UInt64) {d : FloatLib.Numerics.Dyadic}
    (hd : Model.toDyadic? (raw w) = some d) : native (Float.ofBits w) = raw w := by
  exact Submission.R24RepresentationWiden.native_ofBits_of_decode w hd

private theorem shift_value (s : Bool) (m k : Nat) (e : Int) :
    (FloatLib.Numerics.Dyadic.mk s (m * 2 ^ k) (e - (k : Int))).toReal =
      (FloatLib.Numerics.Dyadic.mk s m e).toReal := by
  have hp : (2 : Real) ^ k * (2 : Real) ^ (e - (k : Int)) = (2 : Real) ^ e := by
    rw [← zpow_natCast, ← zpow_add₀ (by norm_num : (2 : Real) ≠ 0)]
    congr 1
    omega
  have hcast (n : Nat) : ((Int.ofNat n : Int) : Real) = (n : Real) := by
    rw [Int.ofNat_eq_natCast, Int.cast_natCast]
  cases s with
  | false =>
    simpa only [FloatLib.Numerics.Dyadic.toReal, FloatLib.Numerics.Dyadic.signedSignificand,
      Bool.false_eq_true, ite_false, ite_true, hcast, Nat.cast_mul, Nat.cast_pow,
      Nat.cast_ofNat, mul_assoc] using congrArg (fun x : Real => (m : Real) * x) hp
  | true =>
    simpa only [FloatLib.Numerics.Dyadic.toReal, FloatLib.Numerics.Dyadic.signedSignificand,
      Bool.false_eq_true, ite_false, ite_true, Int.cast_neg, hcast, Nat.cast_mul,
      Nat.cast_pow, Nat.cast_ofNat, neg_mul, mul_assoc] using
      congrArg (fun x : Real => -(m : Real) * x) hp

/-- The existing cost-body widening of a nonzero subnormal produces a finite
native binary64 with the exact signed value f*2^-149. No normal-branch claim. -/
theorem subnormal_finite_value (u : UInt32)
    (he : ((u >>> 23) &&& 255) = 0) (hn : 0 < n u) :
    (Float.ofBits (Submission.R24PortableF64.widenBits u)).isFinite = true ∧
      Model.toReal (native (Float.ofBits (Submission.R24PortableF64.widenBits u))) =
        (if 2147483648 ≤ u.toNat then -(n u : Real) else (n u : Real)) *
          FloatLib.Floats.Formats.Flocq.bpow FloatLib.Numerics.binaryRadix (-149) := by
  have hd := subnormal_decode u he hn
  have hnative := native_ofBits_decode _ hd
  constructor
  · rw [← native_finite_eq, hnative]
    exact Model.isFinite_eq_true_of_toDyadic?_some hd
  · rw [hnative, Model.toReal_eq, hd]
    have hl := (bounds u hn).1
    have hexp : (ell u : Int) - 201 = (-149 : Int) - ((52 - ell u : Nat) : Int) := by omega
    rw [hexp, shift_value, Model.Dyadic.toReal_eq_signedSignificand]
    congr 1
    by_cases hs : 2147483648 ≤ u.toNat <;>
      simp [FloatLib.Numerics.Dyadic.signedSignificand, hs]

end Submission.R24SubnormalWiden
