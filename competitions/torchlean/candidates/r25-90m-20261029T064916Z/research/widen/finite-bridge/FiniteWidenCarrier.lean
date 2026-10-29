import ContractExact

/- Minimal dependency closure extracted from the retained B2 source.
   Only word decoding and model canonicality; no B2 runtime or public endpoints. -/
namespace R2W01c
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

theorem modelCanonicalOfFinite {fmt : FloatFormat} (x : Model fmt)
    (hx : (Model.toModel x).isFinite = true) : Model.IsModelCanonical x := by
  constructor
  intro he hm
  have hnan : Model.toModel x = Float.Model.UnpackedFloat.notANumber := by
    simp only [Model.toModel, Float.Model.UnpackedFloat.unpack, he, hm, ite_true, ite_false]
  rw [hnan] at hx
  cases hx

theorem modelCanonical_of_decode {fmt : FloatFormat}
    (hfmt : fmt.isIEEE = true) (x : Model fmt) {d : FloatLib.Numerics.Dyadic}
    (hd : Model.toDyadic? x = some d) : Model.IsModelCanonical x := by
  apply modelCanonicalOfFinite
  rw [Model.toDyadic?_ieee_eq_model fmt hfmt x] at hd
  cases hx : Model.toModel x <;>
    simp_all [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.isFinite]

theorem fields32_toDyadic (s : Bool) (e f : Nat)
    (he0 : 0 < e) (he : e < 255) (hf : f < 8388608) :
    Model.toDyadic? (Model.ofFields FloatFormat.binary32 s e f) =
      some ⟨s, 8388608 + f, (e : Int) - 150⟩ := by
  have h := Model.toDyadic?_ofFields_normal FloatFormat.binary32 s e f
    (Nat.ne_of_gt he0) he hf
  change Model.toDyadic? (Model.ofFields FloatFormat.binary32 s e f) =
    some ⟨s, 8388608 + f, (e : Int) - 127 - 23⟩ at h
  have hexp : (e : Int) - 127 - 23 = (e : Int) - 150 := by omega
  simpa only [hexp] using h

abbrev raw32 (u : UInt32) : Model FloatFormat.binary32 :=
  Model.ofUInt32 u

def wordSign (u : UInt32) : Bool :=
  decide (2147483648 ≤ u.toNat)

def wordExp (u : UInt32) : Nat :=
  u.toNat / 8388608 % 256

def wordFrac (u : UInt32) : Nat :=
  u.toNat % 8388608

theorem raw32_bits (u : UInt32) : (raw32 u).bits = u.toBitVec := by
  change BitVec.ofNat 32 u.toNat = u.toBitVec
  exact BitVec.ofNat_uInt32ToNat u

theorem raw32_sign (u : UInt32) : Model.signBit (raw32 u) = wordSign u := by
  rw [Model.signBit_eq_msb, raw32_bits]
  exact BitVec.msb_eq_decide u.toBitVec

theorem raw32_exp (u : UInt32) : Model.expField (raw32 u) = wordExp u := by
  unfold Model.expField
  rw [raw32_bits]
  change ((u.toBitVec >>> 23) &&& (BitVec.ofNat 32 255)).toNat = wordExp u
  rw [BitVec.toNat_and, BitVec.toNat_ushiftRight]
  change (u.toNat >>> 23) &&& (2 ^ 8 - 1) = u.toNat / 8388608 % 256
  rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]

theorem raw32_frac (u : UInt32) : Model.fracField (raw32 u) = wordFrac u := by
  unfold Model.fracField
  rw [raw32_bits]
  change (u.toBitVec &&& (BitVec.ofNat 32 8388607)).toNat = wordFrac u
  rw [BitVec.toNat_and]
  change u.toNat &&& (2 ^ 23 - 1) = u.toNat % 2 ^ 23
  exact Nat.and_two_pow_sub_one_eq_mod u.toNat 23

theorem raw32_eq_fields (u : UInt32) :
    raw32 u = Model.ofFields FloatFormat.binary32 (wordSign u) (wordExp u)
      (wordFrac u) := by
  rw [← raw32_sign, ← raw32_exp, ← raw32_frac]
  exact (Model.ofFields_signBit_expField_fracField (raw32 u)).symm

theorem wordFrac_lt (u : UInt32) : wordFrac u < 8388608 :=
  Nat.mod_lt _ (by decide)

end R2W01c

/- R25 minimal Widen7 carrier. Runtime definitions are unchanged from R24 Widen7.
   Domain contains binary32 normals and signed zeros only. Nonzero subnormals
   and exponent-255 words are excluded. This source starts with status NOT_RUN. -/
namespace Submission.R24RepresentationWiden
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open R2W01c

@[inline] def expWord (u : UInt32) : UInt32 := (u >>> 23) &&& 255
@[inline] def fracWord (u : UInt32) : UInt32 := u &&& 0x7fffff
@[inline] def signWord (u : UInt32) : UInt64 := (u.toUInt64 >>> 31) <<< 63
@[inline] def expWide (u : UInt32) : UInt64 := (expWord u).toUInt64 + 896

@[inline] def widenBits (u : UInt32) : UInt64 :=
  if expWord u = 0 then signWord u
  else signWord u ||| (expWide u <<< 52) ||| ((fracWord u).toUInt64 <<< 29)

@[inline] def value (u : UInt32) : Float := Float.ofBits (widenBits u)

def Domain (u : UInt32) : Prop :=
  (0 < wordExp u ∧ wordExp u < 255) ∨ (wordExp u = 0 ∧ wordFrac u = 0)

abbrev raw64 (w : UInt64) : Model FloatFormat.binary64 := Model.ofBits w.toBitVec
abbrev native64 (x : Float) : Model FloatFormat.binary64 := Model.ofFloatModel x.toModel

theorem expWord_toNat (u : UInt32) : (expWord u).toNat = wordExp u := by
  rw [expWord, UInt32.toNat_and, UInt32.toNat_shiftRight]
  change (u.toNat >>> 23) &&& (2 ^ 8 - 1) = u.toNat / 8388608 % 2 ^ 8
  rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]

theorem fracWord_toNat (u : UInt32) : (fracWord u).toNat = wordFrac u := by
  rw [fracWord, UInt32.toNat_and]
  change u.toNat &&& (2 ^ 23 - 1) = u.toNat % 2 ^ 23
  exact Nat.and_two_pow_sub_one_eq_mod u.toNat 23

theorem wordExp_lt (u : UInt32) : wordExp u < 256 := Nat.mod_lt _ (by decide)

theorem signWord_toNat (u : UInt32) :
    (signWord u).toNat = u.toNat / 2147483648 * 9223372036854775808 := by
  rw [signWord, UInt64.toNat_shiftLeft, UInt64.toNat_shiftRight, UInt32.toNat_toUInt64]
  change ((u.toNat >>> 31) <<< 63) % 18446744073709551616 = _
  rw [Nat.shiftRight_eq_div_pow, Nat.shiftLeft_eq]
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  omega

theorem expWide_toNat (u : UInt32) : (expWide u).toNat = wordExp u + 896 := by
  rw [expWide, UInt64.toNat_add, UInt32.toNat_toUInt64, expWord_toNat]
  have he := wordExp_lt u
  change (wordExp u + 896) % 18446744073709551616 = _
  omega

theorem expWide_shift_toNat (u : UInt32) :
    (expWide u <<< 52).toNat = (wordExp u + 896) * 4503599627370496 := by
  rw [UInt64.toNat_shiftLeft, expWide_toNat]
  change ((wordExp u + 896) <<< 52) % 18446744073709551616 = _
  rw [Nat.shiftLeft_eq]
  have he := wordExp_lt u
  omega

theorem fracWide_shift_toNat (u : UInt32) :
    ((fracWord u).toUInt64 <<< 29).toNat = wordFrac u * 536870912 := by
  rw [UInt64.toNat_shiftLeft, UInt32.toNat_toUInt64, fracWord_toNat]
  change (wordFrac u <<< 29) % 18446744073709551616 = _
  rw [Nat.shiftLeft_eq]
  have hf := wordFrac_lt u
  omega

theorem widenBits_normal_toNat (u : UInt32) (he0 : 0 < wordExp u) :
    (widenBits u).toNat = u.toNat / 2147483648 * 9223372036854775808 +
      (wordExp u + 896) * 4503599627370496 + wordFrac u * 536870912 := by
  have hne : expWord u ≠ 0 := by
    intro h
    have hh := expWord_toNat u
    rw [h] at hh
    change 0 = wordExp u at hh
    omega
  unfold widenBits
  rw [if_neg hne, UInt64.toNat_or, UInt64.toNat_or, signWord_toNat,
    expWide_shift_toNat, fracWide_shift_toNat]
  have he := wordExp_lt u
  have hf := wordFrac_lt u
  have hE : (wordExp u + 896) * 4503599627370496 < 2 ^ 63 := by
    change (wordExp u + 896) * 4503599627370496 < 9223372036854775808
    omega
  have hF : wordFrac u * 536870912 < 2 ^ 52 := by
    calc
      _ < (2 ^ 23) * 536870912 := Nat.mul_lt_mul_of_pos_right hf (by norm_num)
      _ = 2 ^ 52 := by norm_num
  have hSE :
      (u.toNat / 2147483648 * 9223372036854775808) |||
          ((wordExp u + 896) * 4503599627370496) =
        u.toNat / 2147483648 * 9223372036854775808 +
          (wordExp u + 896) * 4503599627370496 := by
    rw [Nat.mul_comm (u.toNat / 2147483648) 9223372036854775808]
    exact (Nat.two_pow_add_eq_or_of_lt hE (u.toNat / 2147483648)).symm
  rw [hSE]
  have hbase : u.toNat / 2147483648 * 9223372036854775808 +
      (wordExp u + 896) * 4503599627370496 =
        2 ^ 52 * (u.toNat / 2147483648 * 2048 + wordExp u + 896) := by
    change _ = 4503599627370496 * _
    omega
  rw [hbase]
  exact (Nat.two_pow_add_eq_or_of_lt hF _).symm

theorem raw64_bits (w : UInt64) : (raw64 w).bits = w.toBitVec := rfl

theorem raw64_sign (w : UInt64) :
    Model.signBit (raw64 w) = decide (9223372036854775808 ≤ w.toNat) := by
  rw [Model.signBit_eq_msb, raw64_bits]
  exact BitVec.msb_eq_decide w.toBitVec

theorem raw64_exp (w : UInt64) :
    Model.expField (raw64 w) = w.toNat / 4503599627370496 % 2048 := by
  unfold Model.expField
  rw [raw64_bits]
  change ((w.toBitVec >>> 52) &&& (BitVec.ofNat 64 2047)).toNat = _
  rw [BitVec.toNat_and, BitVec.toNat_ushiftRight]
  change (w.toNat >>> 52) &&& (2 ^ 11 - 1) = w.toNat / 4503599627370496 % 2 ^ 11
  rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]

theorem raw64_frac (w : UInt64) :
    Model.fracField (raw64 w) = w.toNat % 4503599627370496 := by
  unfold Model.fracField
  rw [raw64_bits]
  change (w.toBitVec &&& (BitVec.ofNat 64 4503599627370495)).toNat = _
  rw [BitVec.toNat_and]
  change w.toNat &&& (2 ^ 52 - 1) = w.toNat % 2 ^ 52
  exact Nat.and_two_pow_sub_one_eq_mod w.toNat 52

theorem raw64_eq_fields (w : UInt64) :
    raw64 w = Model.ofFields FloatFormat.binary64
      (decide (9223372036854775808 ≤ w.toNat))
      (w.toNat / 4503599627370496 % 2048) (w.toNat % 4503599627370496) := by
  rw [← raw64_sign, ← raw64_exp, ← raw64_frac]
  exact (Model.ofFields_signBit_expField_fracField (raw64 w)).symm

theorem widenBits_normal_fields (u : UInt32) (he0 : 0 < wordExp u) :
    raw64 (widenBits u) = Model.ofFields FloatFormat.binary64 (wordSign u)
      (wordExp u + 896) (wordFrac u * 536870912) := by
  have hw := widenBits_normal_toNat u he0
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  have he := wordExp_lt u
  have hf := wordFrac_lt u
  have hs : decide (9223372036854775808 ≤ (widenBits u).toNat) = wordSign u := by
    apply Bool.eq_iff_iff.mpr
    simp only [wordSign, decide_eq_true_eq]
    rw [hw]
    omega
  have hE : (widenBits u).toNat / 4503599627370496 % 2048 = wordExp u + 896 := by
    rw [hw]
    omega
  have hF : (widenBits u).toNat % 4503599627370496 = wordFrac u * 536870912 := by
    rw [hw]
    omega
  rw [raw64_eq_fields, hs, hE, hF]

theorem normal_decode (u : UInt32) (hn : 0 < wordExp u ∧ wordExp u < 255) :
    Model.toDyadic? (raw64 (widenBits u)) =
      some ⟨wordSign u, (8388608 + wordFrac u) * 536870912,
        (wordExp u : Int) - 150 - 29⟩ := by
  rw [widenBits_normal_fields u hn.1]
  have hf := wordFrac_lt u
  have h := Model.toDyadic?_ofFields_normal FloatFormat.binary64
    (wordSign u) (wordExp u + 896) (wordFrac u * 536870912)
    (by omega) (by change wordExp u + 896 < 2047; omega)
    (by change wordFrac u * 536870912 < 4503599627370496; omega)
  change Model.toDyadic? (Model.ofFields FloatFormat.binary64 (wordSign u)
    (wordExp u + 896) (wordFrac u * 536870912)) =
    some ⟨wordSign u, 4503599627370496 + wordFrac u * 536870912,
      ((wordExp u + 896 : Nat) : Int) - 1023 - 52⟩ at h
  have hm : 4503599627370496 + wordFrac u * 536870912 =
      (8388608 + wordFrac u) * 536870912 := by omega
  have hexp : ((wordExp u + 896 : Nat) : Int) - 1023 - 52 =
      (wordExp u : Int) - 150 - 29 := by omega
  simpa only [hm, hexp] using h

theorem zero_word_cases (u : UInt32) (he : wordExp u = 0) (hf : wordFrac u = 0) :
    u = 0 ∨ u = 0x80000000 := by
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  have hz : u.toNat = 0 ∨ u.toNat = 2147483648 := by
    unfold wordExp at he
    unfold wordFrac at hf
    omega
  rcases hz with hz | hz
  · left; apply UInt32.toNat_inj.mp; exact hz
  · right; apply UInt32.toNat_inj.mp; exact hz

theorem widenBits_posZero : widenBits 0 = 0 := by decide
theorem widenBits_negZero : widenBits 0x80000000 = 0x8000000000000000 := by decide

theorem raw_finite (u : UInt32) (h : Domain u) :
    Model.isFinite (raw64 (widenBits u)) = true := by
  rcases h with hn | hz
  · exact Model.isFinite_eq_true_of_toDyadic?_some (normal_decode u hn)
  · rcases zero_word_cases u hz.1 hz.2 with rfl | rfl
    · rw [widenBits_posZero]
      change Model.isFinite (Model.zero FloatFormat.binary64 false) = true
      simp
    · rw [widenBits_negZero]
      change Model.isFinite (Model.zero FloatFormat.binary64 true) = true
      simp

theorem native_ofBits_of_decode (w : UInt64) {d : FloatLib.Numerics.Dyadic}
    (hd : Model.toDyadic? (raw64 w) = some d) :
    native64 (Float.ofBits w) = raw64 w := by
  have hc : Model.IsModelCanonical (raw64 w) :=
    R2W01c.modelCanonical_of_decode (by decide) (raw64 w) hd
  change Model.ofFloatModel
    (ExecFloat.Binary.toFloat (ExecFloat.Binary.ofBits64 w)).toModel = raw64 w
  rw [ExecFloat.Binary.toModel_toFloat_eq, Model.ofFloatModel_toFloatModel]
  exact Model.canonicalizeModel_eq_self _ hc

theorem native_model (u : UInt32) (h : Domain u) :
    native64 (value u) = raw64 (widenBits u) := by
  obtain ⟨d, hd⟩ := Model.exists_toDyadic?_of_isFinite (raw_finite u h)
  exact native_ofBits_of_decode _ hd

theorem native_finite_of_decode (x : Float) {d : FloatLib.Numerics.Dyadic}
    (hd : Model.toDyadic? (native64 x) = some d) : x.isFinite = true := by
  rw [Model.toDyadic?_ieee_eq_model FloatFormat.binary64 (by decide),
    Model.toModel_ofFloatModel] at hd
  change x.toModel.unpack.isFinite = true
  cases hx : x.toModel.unpack <;>
    simp_all [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.isFinite]

theorem native_finite (u : UInt32) (h : Domain u) : (value u).isFinite = true := by
  obtain ⟨d, hd⟩ := Model.exists_toDyadic?_of_isFinite (raw_finite u h)
  apply native_finite_of_decode
  rw [native_model u h]
  exact hd

theorem shift29_toReal (s : Bool) (m : Nat) (e : Int) :
    (FloatLib.Numerics.Dyadic.mk s (m * 536870912) (e - 29)).toReal =
      (FloatLib.Numerics.Dyadic.mk s m e).toReal := by
  have hp : (536870912 : ℝ) * (2 : ℝ) ^ (e - 29) = (2 : ℝ) ^ e := by
    have hc : (536870912 : ℝ) = (2 : ℝ) ^ (29 : Int) := by norm_num
    rw [hc, ← zpow_add₀ (by norm_num : (2 : ℝ) ≠ 0)]
    congr 1
    omega
  have hcast (n : Nat) : ((Int.ofNat n : Int) : ℝ) = (n : ℝ) := by
    rw [Int.ofNat_eq_natCast, Int.cast_natCast]
  have hcNum : ((536870912 : Nat) : ℝ) = (536870912 : ℝ) := by norm_num
  cases s with
  | false =>
    simpa only [FloatLib.Numerics.Dyadic.toReal, FloatLib.Numerics.Dyadic.signedSignificand,
      Bool.false_eq_true, ite_false, ite_true, hcast, Nat.cast_mul, hcNum, mul_assoc] using
      congrArg (fun x : ℝ => (m : ℝ) * x) hp
  | true =>
    simpa only [FloatLib.Numerics.Dyadic.toReal, FloatLib.Numerics.Dyadic.signedSignificand,
      Bool.false_eq_true, ite_false, ite_true, Int.cast_neg, hcast,
      Nat.cast_mul, hcNum, neg_mul, mul_assoc] using
      congrArg (fun x : ℝ => -(m : ℝ) * x) hp

theorem native_value (u : UInt32) (h : Domain u) :
    Model.toReal (native64 (value u)) =
      Model.toReal (Model.ofUInt32 (fmt := FloatFormat.binary32) u) := by
  rw [native_model u h]
  rcases h with hn | hz
  · have hd32 : Model.toDyadic? (raw32 u) =
        some ⟨wordSign u, 8388608 + wordFrac u, (wordExp u : Int) - 150⟩ := by
      rw [raw32_eq_fields]
      exact fields32_toDyadic _ _ _ hn.1 hn.2 (wordFrac_lt u)
    change Model.toReal (raw64 (widenBits u)) = Model.toReal (raw32 u)
    rw [Model.toReal_eq, normal_decode u hn, Model.toReal_eq, hd32]
    exact shift29_toReal _ _ _
  · rcases zero_word_cases u hz.1 hz.2 with rfl | rfl
    · rw [widenBits_posZero]
      change Model.toReal (Model.zero FloatFormat.binary64 false) =
        Model.toReal (Model.zero FloatFormat.binary32 false)
      simp
    · rw [widenBits_negZero]
      change Model.toReal (Model.zero FloatFormat.binary64 true) =
        Model.toReal (Model.zero FloatFormat.binary32 true)
      simp

theorem actual_native_value (u : UInt32) (h : Domain u) :
    Model.toReal (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat (value u))) =
      Model.toReal (Model.ofUInt32 (fmt := FloatFormat.binary32) u) := by
  rw [ExecFloat.Binary.toModel_ofFloat]
  exact native_value u h

theorem signed_zero_bits : (value 0).toBits = 0 ∧
    (value 0x80000000).toBits = 0x8000000000000000 := by decide

end Submission.R24RepresentationWiden

namespace Submission.FastMul

@[inline] def sx (k x : UInt64) : UInt64 := bif x >>> k == 0 then x else x >>> k


@[inline] def sr (k x r : UInt64) : UInt64 := bif x >>> k == 0 then r else r + k


@[inline] def fastLog2 (x0 : UInt64) : UInt64 :=
  let x1 := sx 32 x0
  let r1 := sr 32 x0 0
  let x2 := sx 16 x1
  let r2 := sr 16 x1 r1
  let x3 := sx 8 x2
  let r3 := sr 8 x2 r2
  let x4 := sx 4 x3
  let r4 := sr 4 x3 r3
  let x5 := sx 2 x4
  let r5 := sr 2 x4 r4
  sr 1 x5 r5

end Submission.FastMul

namespace Submission.R24PortableF64

@[inline] def widenBits (word : UInt32) : UInt64 :=
  let sign := (word.toUInt64 &&& 0x80000000) <<< 32
  let e := (word >>> 23) &&& 255
  let f := (word &&& 0x7fffff).toUInt64
  if e == 0 then
    if f == 0 then sign
    else
      let leading := Submission.FastMul.fastLog2 f
      sign ||| ((leading + 874) <<< 52) |||
        ((f - ((1 : UInt64) <<< leading)) <<< (52 - leading))
  else sign ||| ((e.toUInt64 + 896) <<< 52) ||| (f <<< 29)

end Submission.R24PortableF64

/- Connect the unchanged actual PortableF64 normal/zero branches to Widen7.
   Requires the exact three FastMul log2 runtime definitions and actual
   R24PortableF64.widenBits. No nonzero subnormal claim is made here. -/
namespace Submission.R25ActualWiden
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open R2W01c
open Submission.R24RepresentationWiden

theorem actual_sign_eq (u : UInt32) :
    (u.toUInt64 &&& 0x80000000) <<< 32 = signWord u := by
  apply UInt64.toNat_inj.mp
  rw [UInt64.toNat_shiftLeft, UInt64.toNat_and, UInt32.toNat_toUInt64,
    signWord_toNat]
  change ((u.toNat &&& 2 ^ 31) <<< 32) % 18446744073709551616 =
    u.toNat / 2147483648 * 9223372036854775808
  rw [Nat.and_two_pow, Nat.testBit_eq_decide_div_mod_eq, Nat.shiftLeft_eq]
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  by_cases h : u.toNat < 2147483648
  · have hd : u.toNat / 2147483648 = 0 := Nat.div_eq_of_lt h
    norm_num [hd]
  · have hd : u.toNat / 2147483648 = 1 := by omega
    norm_num [hd]

theorem actual_widenBits_eq (u : UInt32) (h : Domain u) :
    Submission.R24PortableF64.widenBits u = widenBits u := by
  rcases h with hn | hz
  · have he : expWord u ≠ 0 := by
      intro hx
      have hnat := expWord_toNat u
      rw [hx] at hnat
      change 0 = wordExp u at hnat
      omega
    have he' : (u >>> 23) &&& 255 ≠ 0 := he
    simp only [Submission.R24PortableF64.widenBits, beq_iff_eq, he', ite_false]
    rw [actual_sign_eq]
    simp only [widenBits, he, ite_false, expWide, expWord, fracWord]
  · rcases zero_word_cases u hz.1 hz.2 with rfl | rfl <;> decide

theorem actual_native_model (u : UInt32) (h : Domain u) :
    native64 (Float.ofBits (Submission.R24PortableF64.widenBits u)) =
      raw64 (widenBits u) := by
  rw [actual_widenBits_eq u h]
  exact native_model u h

theorem actual_native_finite (u : UInt32) (h : Domain u) :
    (Float.ofBits (Submission.R24PortableF64.widenBits u)).isFinite = true := by
  rw [actual_widenBits_eq u h]
  exact native_finite u h

theorem actual_native_value (u : UInt32) (h : Domain u) :
    Model.toReal (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat
      (Float.ofBits (Submission.R24PortableF64.widenBits u)))) =
      Model.toReal (Model.ofUInt32 (fmt := FloatFormat.binary32) u) := by
  rw [actual_widenBits_eq u h]
  exact Submission.R24RepresentationWiden.actual_native_value u h

theorem actual_signed_zero_bits :
    (Float.ofBits (Submission.R24PortableF64.widenBits 0)).toBits = 0 ∧
    (Float.ofBits (Submission.R24PortableF64.widenBits 0x80000000)).toBits =
      0x8000000000000000 := by decide

end Submission.R25ActualWiden

namespace Submission.FastMul

theorem log2_shift (n k : Nat) (h : n >>> k ≠ 0) : n.log2 = k + (n >>> k).log2 := by
  have hn : n ≠ 0 := by rintro rfl; simp at h
  rw [Nat.log2_eq_iff hn]
  rw [Nat.shiftRight_eq_div_pow] at h ⊢
  have h1 := Nat.log2_self_le h
  have h2 := Nat.lt_log2_self (n := n / 2 ^ k)
  have hk : 0 < 2 ^ k := Nat.two_pow_pos k
  constructor
  · calc 2 ^ (k + (n / 2 ^ k).log2) = 2 ^ k * 2 ^ (n / 2 ^ k).log2 := Nat.pow_add 2 _ _
      _ ≤ 2 ^ k * (n / 2 ^ k) := Nat.mul_le_mul_left _ h1
      _ ≤ n := Nat.mul_div_le n (2 ^ k)
  · calc n < 2 ^ k * (n / 2 ^ k + 1) := Nat.lt_mul_div_succ n hk
      _ ≤ 2 ^ k * 2 ^ ((n / 2 ^ k).log2 + 1) := Nat.mul_le_mul_left _ h2
      _ = 2 ^ (k + (n / 2 ^ k).log2 + 1) := by rw [← Nat.pow_add]; ring_nf


theorem log2_lt_64 (x : UInt64) : x.toNat.log2 < 64 := by
  rcases Nat.eq_zero_or_pos x.toNat with h | h
  · simp [h]
  · exact (Nat.log2_lt (by omega)).mpr x.toNat_lt


theorem step (x0 r x k : UInt64) (hk : k.toNat ≤ 32) (hk0 : 0 < k.toNat)
    (hinv : x0.toNat.log2 = r.toNat + x.toNat.log2) (hb : x.toNat < 2 ^ (2 * k.toNat)) :
    x0.toNat.log2 = (sr k x r).toNat + (sx k x).toNat.log2 ∧ (sx k x).toNat < 2 ^ k.toNat := by
  have hs : (x >>> k).toNat = x.toNat >>> k.toNat := by
    rw [UInt64.toNat_shiftRight, Nat.mod_eq_of_lt (by omega)]
  unfold sx sr
  by_cases hz : x >>> k = 0
  · simp only [hz, beq_self_eq_true, Bool.cond_true]
    refine ⟨hinv, ?_⟩
    have h0 : x.toNat >>> k.toNat = 0 := by rw [← hs, hz]; rfl
    rw [Nat.shiftRight_eq_div_pow, Nat.div_eq_zero_iff] at h0
    rcases h0 with h0 | h0
    · exact absurd h0 (Nat.two_pow_pos _).ne'
    · exact h0
  · have hz' : (x >>> k == 0) = false := by simpa using hz
    simp only [hz', Bool.cond_false]
    have hne : x.toNat >>> k.toNat ≠ 0 := by
      rw [← hs]
      intro h
      exact hz (UInt64.toNat_inj.mp (by simpa using h))
    have hl := log2_shift x.toNat k.toNat hne
    have h64 := log2_lt_64 x0
    constructor
    · rw [UInt64.toNat_add, Nat.mod_eq_of_lt (by omega), hs]
      omega
    · rw [hs, Nat.shiftRight_eq_div_pow]
      apply Nat.div_lt_of_lt_mul
      rw [← Nat.pow_add]
      exact lt_of_lt_of_eq hb (by congr 1; omega)


theorem log2_lt_two (n : Nat) (h : n < 2) : n.log2 = 0 := by
  interval_cases n <;> decide


theorem fastLog2_eq (x : UInt64) : fastLog2 x = x.log2 := by
  apply UInt64.toNat_inj.mp
  rw [show x.log2.toNat = x.toNat.log2 from rfl]
  have b0 : x.toNat < 2 ^ (2 * (32 : UInt64).toNat) := x.toNat_lt
  obtain ⟨e1, b1⟩ := step x 0 x 32 (by decide) (by decide) (by simp) b0
  obtain ⟨e2, b2⟩ := step x _ _ 16 (by decide) (by decide) e1 (by simpa using b1)
  obtain ⟨e3, b3⟩ := step x _ _ 8 (by decide) (by decide) e2 (by simpa using b2)
  obtain ⟨e4, b4⟩ := step x _ _ 4 (by decide) (by decide) e3 (by simpa using b3)
  obtain ⟨e5, b5⟩ := step x _ _ 2 (by decide) (by decide) e4 (by simpa using b4)
  obtain ⟨e6, b6⟩ := step x _ _ 1 (by decide) (by decide) e5 (by simpa using b5)
  rw [log2_lt_two (sx 1 (sx 2 (sx 4 (sx 8 (sx 16 (sx 32 x)))))).toNat (by simpa using b6)] at e6
  unfold fastLog2
  dsimp only
  omega

end Submission.FastMul

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

/- Total finite-input value bridge for the actual, unchanged widening function.
   This theorem is not a prepare/getter or Tail accumulation invariant. -/
namespace Submission.R25FiniteWiden
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open R2W01c
open Submission.R24RepresentationWiden

theorem n_eq_wordFrac (u : UInt32) :
    Submission.R24SubnormalWiden.n u = wordFrac u := by
  exact fracWord_toNat u

theorem subnormal_actual_value (u : UInt32)
    (he : expWord u = 0) (hn : 0 < Submission.R24SubnormalWiden.n u) :
    (Float.ofBits (Submission.R24PortableF64.widenBits u)).isFinite = true ∧
      Model.toReal (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat
        (Float.ofBits (Submission.R24PortableF64.widenBits u)))) =
        Model.toReal (Model.ofUInt32 (fmt := FloatFormat.binary32) u) := by
  have hs := Submission.R24SubnormalWiden.subnormal_finite_value u he hn
  have heNat : wordExp u = 0 := by
    have hh := expWord_toNat u
    rw [he] at hh
    change 0 = wordExp u at hh
    exact hh.symm
  have hf : wordFrac u ≠ 0 := by
    rw [n_eq_wordFrac] at hn
    omega
  refine ⟨hs.1, ?_⟩
  rw [ExecFloat.Binary.toModel_ofFloat]
  change Model.toReal (Submission.R24SubnormalWiden.native
    (Float.ofBits (Submission.R24PortableF64.widenBits u))) = Model.toReal (raw32 u)
  rw [hs.2, raw32_eq_fields, heNat,
    Model.toReal_ofFields_subnormal FloatFormat.binary32 (wordSign u) (wordFrac u)
      hf (wordFrac_lt u)]
  by_cases hsign : 2147483648 ≤ u.toNat <;>
    simp [wordSign, hsign, n_eq_wordFrac]

theorem finite_domain_split (u : UInt32) (hf : expWord u ≠ 255) :
    Domain u ∨ (expWord u = 0 ∧ 0 < Submission.R24SubnormalWiden.n u) := by
  have hlt := wordExp_lt u
  have h255 : wordExp u ≠ 255 := by
    intro h
    apply hf
    apply UInt32.toNat_inj.mp
    change (expWord u).toNat = 255
    rw [expWord_toNat, h]
  by_cases he : wordExp u = 0
  · by_cases hfrac : wordFrac u = 0
    · exact Or.inl (Or.inr ⟨he, hfrac⟩)
    · right
      constructor
      · apply UInt32.toNat_inj.mp
        change (expWord u).toNat = 0
        rw [expWord_toNat, he]
      · rw [n_eq_wordFrac]
        omega
  · exact Or.inl (Or.inl ⟨by omega, by omega⟩)

/-- Every finite binary32 word, including subnormals and signed zeros, widens to
a finite native binary64 with the original binary32 real value. -/
theorem finite_actual_value (u : UInt32) (hf : expWord u ≠ 255) :
    (Float.ofBits (Submission.R24PortableF64.widenBits u)).isFinite = true ∧
      Model.toReal (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat
        (Float.ofBits (Submission.R24PortableF64.widenBits u)))) =
        Model.toReal (Model.ofUInt32 (fmt := FloatFormat.binary32) u) := by
  rcases finite_domain_split u hf with h | ⟨he, hn⟩
  · exact ⟨Submission.R25ActualWiden.actual_native_finite u h,
      Submission.R25ActualWiden.actual_native_value u h⟩
  · exact subnormal_actual_value u he hn

end Submission.R25FiniteWiden
