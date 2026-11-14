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


namespace Submission.R24PortableF64

structure Prepared where
  raw : Array UInt32
  values : FloatArray
  maxIndex : UInt32
  valid : Bool

@[inline] def index32 (word : UInt32) : UInt32 :=
  let e := (word >>> 23) &&& 255
  if e == 0 then 0 else e - 1

def prepare (raw : Array UInt32) : Prepared := Id.run do
  if raw.size > 1073741824 then
    return ⟨raw, FloatArray.emptyWithCapacity 0, 0, false⟩
  let mut values := FloatArray.emptyWithCapacity raw.size
  let mut peak : UInt32 := 0
  let mut valid := true
  for word in raw do
    let e := (word >>> 23) &&& 255
    if e == 255 then
      valid := false
      values := values.push (Float.ofBits 0)
    else
      let idx := if e == 0 then 0 else e - 1
      if peak < idx then peak := idx
      values := values.push (Float.ofBits (widenBits word))
  return ⟨raw, values, peak, valid⟩

end Submission.R24PortableF64


/- Proof-only views of the original mutable preparation loop. -/
namespace Submission.R25PrepareAgreement
open Submission.R24PortableF64
open Submission.R24RepresentationWiden (expWord)

abbrev State := FloatArray × UInt32 × Bool

def body (word : UInt32) (s : State) : Id (ForInStep State) :=
  let e := (word >>> 23) &&& 255
  if e == 255 then
    pure (.yield (s.1.push (Float.ofBits 0), s.2.1, false))
  else
    let idx := if e == 0 then 0 else e - 1
    if s.2.1 < idx then
      pure (.yield (s.1.push (Float.ofBits (widenBits word)), idx, s.2.2))
    else
      pure (.yield (s.1.push (Float.ofBits (widenBits word)), s.2.1, s.2.2))

def step (s : State) (word : UInt32) : State := (body word s).run.value

def stored (word : UInt32) : Float :=
  if expWord word == 255 then Float.ofBits 0 else Float.ofBits (widenBits word)

theorem body_yields (word : UInt32) (s : State) :
    body word s = pure (.yield (step s word)) := by
  unfold step body
  split_ifs <;> rfl

theorem prepare_overflow (raw : Array UInt32) (h : 1073741824 < raw.size) :
    prepare raw = ⟨raw, FloatArray.emptyWithCapacity 0, 0, false⟩ := by
  simp only [prepare, h, ite_true]

theorem prepare_valid_sizecap (raw : Array UInt32) (h : (prepare raw).valid = true) :
    raw.size ≤ 1073741824 := by
  by_contra hn
  have hp := prepare_overflow raw (by omega)
  rw [hp] at h
  cases h

/- The source-level connection to the original producer is this equality.
   No conclusion below bypasses it by assuming a replacement producer. -/
theorem prepare_eq_forIn (raw : Array UInt32) (h : raw.size ≤ 1073741824) :
    prepare raw =
      let s := (ForIn.forIn raw
        ((FloatArray.emptyWithCapacity raw.size, (0 : UInt32), true) : State) body : Id State).run
      ⟨raw, s.1, s.2.1, s.2.2⟩ := by
  have hlarge : ¬ 1073741824 < raw.size := by omega
  simpa only [prepare, hlarge, ite_false, body]

theorem prepare_eq_fold (raw : Array UInt32) (h : raw.size ≤ 1073741824) :
    prepare raw =
      let s := raw.foldl step (FloatArray.emptyWithCapacity raw.size, 0, true)
      ⟨raw, s.1, s.2.1, s.2.2⟩ := by
  rw [prepare_eq_forIn raw h]
  have hb : body = (fun word s => (pure (.yield (step s word)) : Id (ForInStep State))) := by
    funext word s
    exact body_yields word s
  simpa only [hb, Array.forIn_pure_yield_eq_foldl]

theorem step_values (s : State) (word : UInt32) :
    (step s word).1.data = s.1.data.push (stored word) := by
  rcases s with ⟨⟨values⟩, peak, valid⟩
  unfold step body stored expWord
  split_ifs <;> rfl

theorem step_valid (s : State) (word : UInt32) :
    (step s word).2.2 = true ↔ s.2.2 = true ∧ expWord word ≠ 255 := by
  unfold step body expWord
  split_ifs <;> simp_all [beq_iff_eq]

theorem fold_values (xs : List UInt32) (s : State) :
    (xs.foldl step s).1.data.toList = s.1.data.toList ++ xs.map stored := by
  induction xs generalizing s with
  | nil => simp only [List.foldl_nil, List.map_nil, List.append_nil]
  | cons word xs ih =>
    rw [List.foldl_cons, ih, step_values, Array.toList_push, List.map_cons]
    simp only [List.append_assoc, List.singleton_append]

theorem fold_valid (xs : List UInt32) (s : State) :
    (xs.foldl step s).2.2 = true ↔
      s.2.2 = true ∧ ∀ word ∈ xs, expWord word ≠ 255 := by
  induction xs generalizing s with
  | nil => simp
  | cons word xs ih =>
    rw [List.foldl_cons, ih, step_valid]
    simp only [List.forall_mem_cons, and_assoc]

theorem prepare_raw (raw : Array UInt32) : (prepare raw).raw = raw := by
  by_cases h : raw.size ≤ 1073741824
  · rw [prepare_eq_forIn raw h]
  · rw [prepare_overflow raw (by omega)]

theorem prepare_values_data (raw : Array UInt32) (h : raw.size ≤ 1073741824) :
    (prepare raw).values.data = raw.map stored := by
  rw [prepare_eq_fold raw h]
  change (raw.foldl step (FloatArray.emptyWithCapacity raw.size, 0, true)).1.data = _
  apply Array.toList_inj.mp
  rw [← Array.foldl_toList, fold_values, Array.toList_map]
  simp only [FloatArray.emptyWithCapacity, List.nil_append]

private theorem size_data (a : FloatArray) : a.size = a.data.size := by
  cases a
  rfl

private theorem get_data (a : FloatArray) (i : Nat) : a.get! i = a.data[i]! := by
  cases a
  rfl

theorem prepare_values_size (raw : Array UInt32) (h : raw.size ≤ 1073741824) :
    (prepare raw).values.size = raw.size := by
  rw [size_data, prepare_values_data raw h, Array.size_map]

theorem prepare_valid_iff (raw : Array UInt32) (h : raw.size ≤ 1073741824) :
    (prepare raw).valid = true ↔ ∀ word ∈ raw.toList, expWord word ≠ 255 := by
  rw [prepare_eq_fold raw h]
  change (raw.foldl step (FloatArray.emptyWithCapacity raw.size, 0, true)).2.2 = true ↔ _
  rw [← Array.foldl_toList, fold_valid]
  simp

theorem prepare_valid_rawfinite (raw : Array UInt32) (h : (prepare raw).valid = true)
    (i : Nat) (hi : i < raw.size) : expWord raw[i] ≠ 255 := by
  have hf := (prepare_valid_iff raw (prepare_valid_sizecap raw h)).mp h
  exact hf raw[i] (Array.getElem_mem_toList hi)

theorem prepare_get (raw : Array UInt32) (h : (prepare raw).valid = true)
    (i : Nat) (hi : i < raw.size) :
    (prepare raw).values.get! i = Float.ofBits (widenBits raw[i]) := by
  have hcap := prepare_valid_sizecap raw h
  have hf := prepare_valid_rawfinite raw h i hi
  rw [get_data, prepare_values_data raw hcap]
  rw [getElem!_pos _ i (by simpa only [Array.size_map] using hi), Array.getElem_map]
  simp only [stored, beq_iff_eq, hf, ite_false]

theorem prepare_getter_interface (raw : Array UInt32) (h : (prepare raw).valid = true) :
    (prepare raw).raw = raw ∧
    raw.size ≤ 1073741824 ∧
    (prepare raw).values.size = raw.size ∧
    ∀ (i : Nat) (hi : i < raw.size),
      expWord raw[i] ≠ 255 ∧
      (prepare raw).values.get! i = Float.ofBits (widenBits raw[i]) := by
  have hcap := prepare_valid_sizecap raw h
  exact ⟨prepare_raw raw, hcap, prepare_values_size raw hcap,
    fun i hi => ⟨prepare_valid_rawfinite raw h i hi, prepare_get raw h i hi⟩⟩

end Submission.R25PrepareAgreement


namespace Submission.R26PreparePeak
open Submission.R24PortableF64
open Submission.R24RepresentationWiden (expWord)
open Submission.R25PrepareAgreement

theorem exponent_lt (word : UInt32) : (expWord word).toNat < 256 := by
  unfold expWord
  rw [UInt32.toNat_and, UInt32.toNat_shiftRight]
  change (word.toNat >>> 23) &&& (2 ^ 8 - 1) < 2 ^ 8
  rw [Nat.and_two_pow_sub_one_eq_mod]
  exact Nat.mod_lt _ (by decide)

theorem index_nat (word : UInt32) :
    (index32 word).toNat = (expWord word).toNat - 1 := by
  by_cases he : expWord word = 0
  · simp [index32, expWord] at he ⊢
    simp [he]
  · have heNat : 0 < (expWord word).toNat := by
      have hn : (expWord word).toNat ≠ 0 := by
        intro hz
        apply he
        apply UInt32.toNat_inj.mp
        simpa using hz
      omega
    have hle : (1 : UInt32) ≤ expWord word := by
      apply UInt32.le_iff_toNat_le.mpr
      simpa using heNat
    change ((if expWord word == 0 then 0 else expWord word - 1) : UInt32).toNat = _
    rw [if_neg (by simpa using he)]
    rw [UInt32.toNat_sub_of_le _ _ hle]
    rfl

theorem index_bound (word : UInt32) (hf : expWord word ≠ 255) :
    (index32 word).toNat ≤ 253 := by
  have he := exponent_lt word
  have hne : (expWord word).toNat ≠ 255 := by
    intro h
    apply hf
    apply UInt32.toNat_inj.mp
    simpa using h
  rw [index_nat]
  omega

theorem step_peak (s : State) (word : UInt32) :
    (step s word).2.1 =
      if expWord word = 255 then s.2.1
      else if s.2.1 < index32 word then index32 word else s.2.1 := by
  unfold step body expWord index32
  simp only [beq_iff_eq]
  split_ifs <;> rfl

theorem step_peak_bound (s : State) (word : UInt32) (hs : s.2.1.toNat ≤ 253) :
    (step s word).2.1.toNat ≤ 253 := by
  rw [step_peak]
  split_ifs with he hi
  · exact hs
  · exact index_bound word he
  · exact hs

theorem step_peak_mono (s : State) (word : UInt32) :
    s.2.1.toNat ≤ (step s word).2.1.toNat := by
  rw [step_peak]
  split_ifs with he hi
  · exact Nat.le_refl _
  · exact (UInt32.lt_iff_toNat_lt.mp hi).le
  · exact Nat.le_refl _

theorem step_peak_contains (s : State) (word : UInt32) (hf : expWord word ≠ 255) :
    (index32 word).toNat ≤ (step s word).2.1.toNat := by
  rw [step_peak, if_neg hf]
  split_ifs with hi
  · exact Nat.le_refl _
  · have hnot : ¬ s.2.1.toNat < (index32 word).toNat := by
      simpa only [UInt32.lt_iff_toNat_lt] using hi
    omega

theorem fold_peak_bound (xs : List UInt32) (s : State) (hs : s.2.1.toNat ≤ 253) :
    (xs.foldl step s).2.1.toNat ≤ 253 := by
  induction xs generalizing s with
  | nil => exact hs
  | cons word xs ih =>
    rw [List.foldl_cons]
    exact ih _ (step_peak_bound s word hs)

theorem fold_peak_mono (xs : List UInt32) (s : State) :
    s.2.1.toNat ≤ (xs.foldl step s).2.1.toNat := by
  induction xs generalizing s with
  | nil => exact Nat.le_refl _
  | cons word xs ih =>
    rw [List.foldl_cons]
    exact (step_peak_mono s word).trans (ih _)

theorem fold_peak_contains (xs : List UInt32) (s : State) (word : UInt32)
    (hm : word ∈ xs) (hf : expWord word ≠ 255) :
    (index32 word).toNat ≤ (xs.foldl step s).2.1.toNat := by
  induction xs generalizing s with
  | nil => simp at hm
  | cons head tail ih =>
    rw [List.foldl_cons]
    rcases List.mem_cons.mp hm with h | h
    · subst word
      exact (step_peak_contains s head hf).trans (fold_peak_mono tail _)
    · exact ih _ h

theorem prepare_peak_bound (raw : Array UInt32) : (prepare raw).maxIndex.toNat ≤ 253 := by
  by_cases h : raw.size ≤ 1073741824
  · rw [prepare_eq_fold raw h]
    change (raw.foldl step (FloatArray.emptyWithCapacity raw.size, 0, true)).2.1.toNat ≤ 253
    rw [← Array.foldl_toList]
    exact fold_peak_bound _ _ (by decide)
  · rw [prepare_overflow raw (by omega)]
    decide

theorem prepare_index_bound (raw : Array UInt32) (hv : (prepare raw).valid = true)
    (i : Nat) (hi : i < raw.size) :
    (index32 raw[i]).toNat ≤ (prepare raw).maxIndex.toNat := by
  have hcap := prepare_valid_sizecap raw hv
  have hf := prepare_valid_rawfinite raw hv i hi
  rw [prepare_eq_fold raw hcap]
  change (index32 raw[i]).toNat ≤
    (raw.foldl step (FloatArray.emptyWithCapacity raw.size, 0, true)).2.1.toNat
  rw [← Array.foldl_toList]
  exact fold_peak_contains _ _ raw[i] (Array.getElem_mem_toList hi) hf

theorem prepare_full_interface (raw : Array UInt32) (hv : (prepare raw).valid = true) :
    (prepare raw).raw = raw ∧
    raw.size ≤ 1073741824 ∧
    (prepare raw).values.size = raw.size ∧
    (prepare raw).maxIndex.toNat ≤ 253 ∧
    ∀ (i : Nat) (hi : i < raw.size),
      expWord raw[i] ≠ 255 ∧
      (prepare raw).values.get! i = Float.ofBits (widenBits raw[i]) ∧
      (index32 raw[i]).toNat ≤ (prepare raw).maxIndex.toNat := by
  have hcap := prepare_valid_sizecap raw hv
  exact ⟨prepare_raw raw, hcap, prepare_values_size raw hcap, prepare_peak_bound raw,
    fun i hi => ⟨prepare_valid_rawfinite raw hv i hi, prepare_get raw hv i hi,
      prepare_index_bound raw hv i hi⟩⟩

end Submission.R26PreparePeak


namespace Submission.R24PortableF64
@[inline] def ceilLog2 (n : Nat) : UInt64 :=
  if n ≤ 1 then 0
  else Submission.FastMul.fastLog2 (UInt64.ofNat n - 1) + 1
def sumRemaining (a b : FloatArray) (index : Nat) (acc : Float) (remaining : Nat) : Float :=
  match remaining with
  | 0 => acc
  | rest + 1 =>
    sumRemaining a b (index + 1) (acc + a.get! index * b.get! index) rest

end Submission.R24PortableF64


namespace Submission.R26PreparedParameters
open Submission.R24PortableF64
open Submission.R25PrepareAgreement
open Submission.R26PreparePeak

theorem ceilLog2_nat (n : Nat) (hcap : n ≤ 1073741824) :
    (ceilLog2 n).toNat = if n ≤ 1 then 0 else (n - 1).log2 + 1 := by
  by_cases hn : n ≤ 1
  · simp only [ceilLog2, hn, ite_true]
    rfl
  · have hn64 : (UInt64.ofNat n).toNat = n :=
      UInt64.toNat_ofNat_of_lt' (by omega)
    have hone : (1 : UInt64) ≤ UInt64.ofNat n := by
      rw [UInt64.le_iff_toNat_le, hn64]
      change 1 ≤ n
      omega
    have hsub : (UInt64.ofNat n - 1).toNat = n - 1 := by
      rw [UInt64.toNat_sub_of_le _ _ hone, hn64]
      rfl
    have hlog : (n - 1).log2 < 30 :=
      (Nat.log2_lt (by omega : n - 1 ≠ 0)).mpr (by omega)
    simp only [ceilLog2, hn, ite_false]
    rw [UInt64.toNat_add, Submission.FastMul.fastLog2_eq]
    change ((UInt64.ofNat n - 1).toNat.log2 + 1) % 18446744073709551616 = _
    rw [hsub]
    exact Nat.mod_eq_of_lt (by omega)

theorem ceilLog2_bound (n : Nat) (hcap : n ≤ 1073741824) :
    (ceilLog2 n).toNat ≤ 30 := by
  rw [ceilLog2_nat n hcap]
  split_ifs with hn
  · decide
  · have hl : (n - 1).log2 < 30 :=
      (Nat.log2_lt (by omega : n - 1 ≠ 0)).mpr (by omega)
    omega

theorem ceilLog2_covers (n : Nat) (hcap : n ≤ 1073741824) :
    n ≤ 2 ^ (ceilLog2 n).toNat := by
  rw [ceilLog2_nat n hcap]
  split_ifs with hn
  · simpa using hn
  · have hl : n - 1 < 2 ^ ((n - 1).log2 + 1) := Nat.lt_log2_self
    omega

theorem prepared_H_nat (rawX rawY : Array UInt32) :
    ((prepare rawX).maxIndex.toUInt64 + (prepare rawY).maxIndex.toUInt64).toNat =
      (prepare rawX).maxIndex.toNat + (prepare rawY).maxIndex.toNat := by
  have hx := prepare_peak_bound rawX
  have hy := prepare_peak_bound rawY
  rw [UInt64.toNat_add, UInt32.toNat_toUInt64, UInt32.toNat_toUInt64]
  change (_ + _) % 18446744073709551616 = _
  exact Nat.mod_eq_of_lt (by omega)

theorem prepared_H_bound (rawX rawY : Array UInt32) :
    ((prepare rawX).maxIndex.toUInt64 + (prepare rawY).maxIndex.toUInt64).toNat ≤ 506 := by
  rw [prepared_H_nat]
  have hx := prepare_peak_bound rawX
  have hy := prepare_peak_bound rawY
  omega

theorem actual_parameters (rawX rawY : Array UInt32)
    (hv : (prepare rawX).valid = true) :
    let H := (prepare rawX).maxIndex.toUInt64 + (prepare rawY).maxIndex.toUInt64
    let L := ceilLog2 (prepare rawX).raw.size
    H.toNat ≤ 506 ∧ L.toNat ≤ 30 ∧ (prepare rawX).raw.size ≤ 2 ^ L.toNat := by
  dsimp only
  rw [prepare_raw]
  have hcap := prepare_valid_sizecap rawX hv
  exact ⟨prepared_H_bound rawX rawY, ceilLog2_bound _ hcap, ceilLog2_covers _ hcap⟩

end Submission.R26PreparedParameters


namespace R2W01c
namespace NativeBridge

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open Float.Model.UnpackedFloat
open FloatLib.Floats.Formats.BinaryInterchange.Model






theorem le_targetExponent_totalExponent_iff (spec : Float.Model.Format)
    (mantissa : Nat) (exponent : Int) :
    exponent ≤ spec.targetExponent (Float.Model.totalExponent mantissa exponent) ↔
      exponent ≤ spec.minExponent ∨ 2 ^ spec.mantissaBitsWithoutImplicit ≤ mantissa := by
  have hlog : spec.mantissaBitsWithoutImplicit ≤ mantissa.log2 ↔
      2 ^ spec.mantissaBitsWithoutImplicit ≤ mantissa := by
    rcases Nat.eq_zero_or_pos mantissa with rfl | hmantissa
    · have hwidth := spec.hm
      have hpow := Nat.two_pow_pos spec.mantissaBitsWithoutImplicit
      rw [Nat.log2_zero]
      omega
    · exact Nat.le_log2 hmantissa.ne'
  rw [← hlog]
  simp only [Float.Model.Format.targetExponent, Float.Model.totalExponent,
    Float.Model.Format.mantissaBits]
  omega





theorem add_le_targetExponent_totalExponent_mul (spec : Float.Model.Format)
    {mantissa₁ mantissa₂ : Nat} {exponent₁ exponent₂ : Int}
    (hmantissa₁ : 0 < mantissa₁) (hmantissa₂ : 0 < mantissa₂)
    (hle₁ :
      exponent₁ ≤ spec.targetExponent (Float.Model.totalExponent mantissa₁ exponent₁))
    (hle₂ :
      exponent₂ ≤ spec.targetExponent (Float.Model.totalExponent mantissa₂ exponent₂)) :
    exponent₁ + exponent₂ ≤
      spec.targetExponent
        (Float.Model.totalExponent (mantissa₁ * mantissa₂) (exponent₁ + exponent₂)) := by
  rw [le_targetExponent_totalExponent_iff] at hle₁ hle₂ ⊢
  have hmin : spec.minExponent ≤ 0 := by
    have hwidth := spec.hm
    have hpow : (1 : Int) ≤ 2 ^ (spec.exponentBits - 1) := by
      exact_mod_cast Nat.two_pow_pos (spec.exponentBits - 1)
    simp only [Float.Model.Format.minExponent, Float.Model.Format.mantissaBits]
    omega
  rcases hle₁ with hle₁ | hle₁
  · rcases hle₂ with hle₂ | hle₂
    · exact Or.inl (by omega)
    · exact Or.inr (hle₂.trans (Nat.le_mul_of_pos_left mantissa₂ hmantissa₁))
  · exact Or.inr (hle₁.trans (Nat.le_mul_of_pos_right mantissa₁ hmantissa₂))





theorem le_targetExponent_totalExponent_of_toModel_eq_finite {fmt : FloatFormat} (x : Model fmt)
    {sign : Sign} {mantissa : Nat} {exponent : Int} {hmantissa : 0 < mantissa}
    (hx : toModel x = .finite sign mantissa exponent hmantissa) :
    exponent ≤
      (FloatFormat.toModel fmt).targetExponent (Float.Model.totalExponent mantissa exponent) := by
  rw [le_targetExponent_totalExponent_iff, toModel_minExponent]
  change exponent ≤ FloatFormat.ieeeMinSubnormalExponent fmt ∨ 2 ^ fmt.fracWidth ≤ mantissa
  have hdecode := ieeeToDyadic?_eq_unpackedToDyadic?_toModel x
  rw [hx] at hdecode
  simp only [unpackedToDyadic?, ieeeToDyadic?] at hdecode
  split_ifs at hdecode
  · simp only [Option.some.injEq, FloatLib.Numerics.Dyadic.mk.injEq] at hdecode
    exact absurd hdecode.2.1.symm hmantissa.ne'
  · simp only [Option.some.injEq, FloatLib.Numerics.Dyadic.mk.injEq] at hdecode
    exact Or.inl hdecode.2.2.symm.le
  · simp only [Option.some.injEq, FloatLib.Numerics.Dyadic.mk.injEq] at hdecode
    refine Or.inr ?_
    rw [← hdecode.2.1, pow2_eq_two_pow]
    exact Nat.le_add_right _ _



theorem modelMulFinite {fmt : FloatFormat} (hfmt : fmt.isIEEE = true)
    (x y : Model fmt) (hx : (Model.toModel x).isFinite = true)
    (hy : (Model.toModel y).isFinite = true) :
    Model.mul x y =
      Model.ofModel fmt
        (Float.Model.UnpackedFloat.mul (FloatFormat.toModel fmt)
          (Model.toModel x) (Model.toModel y)) := by
  have hzero := FloatFormat.supportsSignedZero_eq_true_of_isIEEE fmt hfmt
  cases hxmodel : Model.toModel x <;> cases hymodel : Model.toModel y <;>
    simp only [hxmodel, hymodel, Float.Model.UnpackedFloat.isFinite,
      Bool.false_eq_true] at hx hy
  case zero.zero sign₁ sign₂ =>
    rw [Model.Proof.mul_eq_spec, Model.Spec.mul,
      Model.toDyadic?_ieee_eq_model fmt hfmt x,
      Model.toDyadic?_ieee_eq_model fmt hfmt y, hxmodel, hymodel]
    cases sign₁ <;> cases sign₂ <;>
      simp [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.mul,
        Model.modelSignBit, Model.zero, Model.posZero_eq_ofModel_zero,
        Model.negZero_eq_ofModel_zero, hzero,
        show Sign.negative * Sign.negative = Sign.positive from rfl,
        show Sign.negative * Sign.positive = Sign.negative from rfl,
        show Sign.positive * Sign.negative = Sign.negative from rfl,
        show Sign.positive * Sign.positive = Sign.positive from rfl]
  case zero.finite sign₁ sign₂ mantissa₂ exponent₂ hmantissa₂ =>
    rw [Model.Proof.mul_eq_spec, Model.Spec.mul,
      Model.toDyadic?_ieee_eq_model fmt hfmt x,
      Model.toDyadic?_ieee_eq_model fmt hfmt y, hxmodel, hymodel]
    cases sign₁ <;> cases sign₂ <;>
      simp [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.mul,
        Model.modelSignBit, Model.zero, Model.posZero_eq_ofModel_zero,
        Model.negZero_eq_ofModel_zero, hzero,
        show Sign.negative * Sign.negative = Sign.positive from rfl,
        show Sign.negative * Sign.positive = Sign.negative from rfl,
        show Sign.positive * Sign.negative = Sign.negative from rfl,
        show Sign.positive * Sign.positive = Sign.positive from rfl]
  case finite.zero sign₁ mantissa₁ exponent₁ hmantissa₁ sign₂ =>
    rw [Model.Proof.mul_eq_spec, Model.Spec.mul,
      Model.toDyadic?_ieee_eq_model fmt hfmt x,
      Model.toDyadic?_ieee_eq_model fmt hfmt y, hxmodel, hymodel]
    cases sign₁ <;> cases sign₂ <;>
      simp [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.mul,
        Model.modelSignBit, Model.zero, Model.posZero_eq_ofModel_zero,
        Model.negZero_eq_ofModel_zero, hzero,
        show Sign.negative * Sign.negative = Sign.positive from rfl,
        show Sign.negative * Sign.positive = Sign.negative from rfl,
        show Sign.positive * Sign.negative = Sign.negative from rfl,
        show Sign.positive * Sign.positive = Sign.positive from rfl]
  case finite.finite sign₁ mantissa₁ exponent₁ hmantissa₁ sign₂ mantissa₂ exponent₂ hmantissa₂ =>
    have hle := add_le_targetExponent_totalExponent_mul (FloatFormat.toModel fmt)
      hmantissa₁ hmantissa₂
      (le_targetExponent_totalExponent_of_toModel_eq_finite x hxmodel)
      (le_targetExponent_totalExponent_of_toModel_eq_finite y hymodel)
    have hr (sign : Sign) :
        Float.Model.UnpackedFloat.roundWithAccuracy (FloatFormat.toModel fmt) sign
          (mantissa₁ * mantissa₂) (exponent₁ + exponent₂) .exact =
        Float.Model.UnpackedFloat.round (FloatFormat.toModel fmt) sign
          (mantissa₁ * mantissa₂) (exponent₁ + exponent₂) :=
      Model.roundWithAccuracy_exact_eq_round_of_le_targetExponent _ _ _ _ hle
    rw [Model.Proof.mul_eq_spec, Model.Spec.mul,
      Model.toDyadic?_ieee_eq_model fmt hfmt x,
      Model.toDyadic?_ieee_eq_model fmt hfmt y, hxmodel, hymodel]
    cases sign₁ <;> cases sign₂ <;>
      simp [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.mul,
        Model.roundDyadic, hfmt, Model.ieeeRoundDyadic,
        Model.modelSignBit, Model.modelSign, hmantissa₁.ne', hmantissa₂.ne',
        hr,
        show Sign.negative * Sign.negative = Sign.positive from rfl,
        show Sign.negative * Sign.positive = Sign.negative from rfl,
        show Sign.positive * Sign.negative = Sign.negative from rfl,
        show Sign.positive * Sign.positive = Sign.positive from rfl]

end NativeBridge
end R2W01c


/-
R24 portable binary64 native multiplication bridge.
The complete retained B2 prefix and its four public endpoints are unchanged.
This reuses B2's format-polymorphic modelMulFinite proof; it does not assume
an opaque Float32/Float cast and does not depend on the uncompiled widen1 helper.
-/
namespace Submission.R24NativeMul

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

abbrev F64 := FloatFormat.binary64
abbrev F32 := FloatFormat.binary32
abbrev view (x : Float) : Model F64 := Model.ofFloatModel x.toModel
noncomputable abbrev value (x : Float) : Real := Model.toReal (view x)
abbrev raw32 (u : UInt32) : Model F32 := Model.ofUInt32 u

/-- Actual native Float multiplication agrees with Model.mul on every finite
input, including signed zeros. The result is allowed to overflow. -/
theorem native_mul_toModel (x y : Float)
    (hx : x.isFinite = true) (hy : y.isFinite = true) :
    ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat (x * y)) =
      Model.mul (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat x))
        (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat y)) := by
  rw [ExecFloat.Binary.toModel_ofFloat, ExecFloat.Binary.toModel_ofFloat,
    ExecFloat.Binary.toModel_ofFloat]
  change Model.ofFloatModel (Float.Model.mul x.toModel y.toModel) = _
  rw [Float.Model.mul, Model.ofFloatModel_pack]
  have h := R2W01c.NativeBridge.modelMulFinite (fmt := F64)
    (by decide) (Model.ofFloatModel x.toModel) (Model.ofFloatModel y.toModel)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite,
      Float.Model.isFinite] using hx)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite,
      Float.Model.isFinite] using hy)
  rw [Model.toModel_ofFloatModel, Model.toModel_ofFloatModel] at h
  exact h.symm

private theorem mul_view (x y : Float)
    (hx : x.isFinite = true) (hy : y.isFinite = true) :
    view (x * y) = Model.mul (view x) (view y) := by
  change Model.ofFloatModel (Float.Model.mul x.toModel y.toModel) = _
  rw [Float.Model.mul, Model.ofFloatModel_pack]
  have h := R2W01c.NativeBridge.modelMulFinite (fmt := F64)
    (by decide) (Model.ofFloatModel x.toModel) (Model.ofFloatModel y.toModel)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite,
      Float.Model.isFinite] using hx)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite,
      Float.Model.isFinite] using hy)
  rw [Model.toModel_ofFloatModel, Model.toModel_ofFloatModel] at h
  exact h.symm

private theorem model_finite (x : Float) (hx : x.isFinite = true) :
    Model.isFinite (view x) = true := by
  have hxmodel : (Model.toModel (view x)).isFinite = true := by
    simpa only [view, Model.toModel_ofFloatModel, Float.isFinite,
      Float.Model.isFinite] using hx
  have hsome : (Model.toDyadic? (view x)).isSome = true := by
    rw [Model.toDyadic?_ieee_eq_model F64 (by decide)]
    cases hm : Model.toModel (view x) <;>
      simp_all [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.isFinite]
  cases hd : Model.toDyadic? (view x) with
  | none => simp [hd] at hsome
  | some d => exact Model.isFinite_eq_true_of_toDyadic?_some hd

private theorem native_finite (x : Float) (hx : Model.isFinite (view x) = true) :
    x.isFinite = true := by
  obtain ⟨d, hd⟩ := Model.exists_toDyadic?_of_isFinite hx
  rw [Model.toDyadic?_ieee_eq_model F64 (by decide),
    Model.toModel_ofFloatModel] at hd
  change x.toModel.unpack.isFinite = true
  cases hm : x.toModel.unpack <;>
    simp_all [Model.unpackedToDyadic?, Float.Model.UnpackedFloat.isFinite]

/-- A symbolic exact-product bound gives finiteness and the real RNE64
semantics of the actual native multiplication; output finiteness is proved. -/
theorem native_mul_finite_roundAt (x y : Float)
    (hx : x.isFinite = true) (hy : y.isFinite = true)
    (hbound : |value x| * |value y| ≤ Model.toReal (Model.posMaxFinite F64)) :
    (x * y).isFinite = true ∧
      value (x * y) = Model.roundAt F64 (value x * value y) := by
  have hmx := model_finite x hx
  have hmy := model_finite y hy
  have hp := Model.isFinite_mul_of_abs_mul_le_posMaxFinite
    (view x) (view y) (by decide) hmx hmy hbound
  have hpview : Model.isFinite (view (x * y)) = true := by
    rw [mul_view x y hx hy]
    exact hp
  refine ⟨native_finite (x * y) hpview, ?_⟩
  change Model.toReal (view (x * y)) = _
  rw [mul_view x y hx hy]
  exact Model.toReal_mul_eq_roundAt (view x) (view y) (by decide) hmx hmy hp

private theorem max32_squared_le_max64 :
    Model.toReal (Model.posMaxFinite F32) * Model.toReal (Model.posMaxFinite F32) ≤
      Model.toReal (Model.posMaxFinite F64) := by
  change Model.toReal (Model.ofFields F32 false 254 8388607) *
      Model.toReal (Model.ofFields F32 false 254 8388607) ≤
    Model.toReal (Model.ofFields F64 false 2046 4503599627370495)
  simp only [Model.toReal_ofFields_normal F32 false 254 8388607
      (by decide) (by decide) (by decide),
    Model.toReal_ofFields_normal F64 false 2046 4503599627370495
      (by decide) (by decide) (by decide)]
  change ((1 : Real) * 16777215 * Model.bpow 104) *
      ((1 : Real) * 16777215 * Model.bpow 104) ≤
    (1 : Real) * 9007199254740991 * Model.bpow 971
  simp only [one_mul]
  have hcoef : (16777215 : Real) * 16777215 ≤ 9007199254740991 := by norm_num
  have hpow : Model.bpow 208 ≤ Model.bpow 971 :=
    Model.bpow_le_bpow_of_le (by decide)
  calc
    ((16777215 : Real) * Model.bpow 104) * (16777215 * Model.bpow 104) =
        (16777215 * 16777215) * Model.bpow 208 := by
      rw [show (208 : Int) = 104 + 104 by decide, Model.bpow_add]
      ring
    _ ≤ (9007199254740991 : Real) * Model.bpow 208 :=
      mul_le_mul_of_nonneg_right hcoef (Model.bpow_nonneg 208)
    _ ≤ (9007199254740991 : Real) * Model.bpow 971 :=
      mul_le_mul_of_nonneg_left hpow (by norm_num)

private theorem f32_product_bound (a b : Model F32)
    (ha : Model.isFinite a = true) (hb : Model.isFinite b = true) :
    |Model.toReal a| * |Model.toReal b| ≤ Model.toReal (Model.posMaxFinite F64) := by
  have hA := Model.abs_toReal_le_posMaxFinite_of_isIEEE_of_isFinite a (by decide) ha
  have hB := Model.abs_toReal_le_posMaxFinite_of_isIEEE_of_isFinite b (by decide) hb
  have hnonneg : 0 ≤ Model.toReal (Model.posMaxFinite F32) :=
    (abs_nonneg (Model.toReal a)).trans hA
  exact (mul_le_mul hA hB (abs_nonneg _) hnonneg).trans max32_squared_le_max64

private theorem f32_product_grid (a b : Model F32)
    (ha : Model.isFinite a = true) (hb : Model.isFinite b = true) :
    FloatLib.Floats.Formats.Flocq.genericFormat FloatLib.Numerics.binaryRadix
      (Model.fexpOf F64) (Model.toReal a * Model.toReal b) := by
  obtain ⟨da, hda⟩ := Model.exists_toDyadic?_of_isFinite ha
  obtain ⟨db, hdb⟩ := Model.exists_toDyadic?_of_isFinite hb
  let d : FloatLib.Numerics.Dyadic :=
    ⟨Bool.xor da.negative db.negative, da.significand * db.significand,
      da.exponent + db.exponent⟩
  have hma := Model.toDyadic?_significand_lt a hda
  have hmb := Model.toDyadic?_significand_lt b hdb
  change da.significand < 2 ^ 24 at hma
  change db.significand < 2 ^ 24 at hmb
  have hsig : d.significand < 2 ^ (F64.fracWidth + 1) := by
    change da.significand * db.significand < 2 ^ 53
    calc
      da.significand * db.significand < 2 ^ 24 * 2 ^ 24 := Nat.mul_lt_mul'' hma hmb
      _ < 2 ^ 53 := by norm_num
  have hea := Model.minSubnormalExponent_le_toDyadic? a hda
  have heb := Model.minSubnormalExponent_le_toDyadic? b hdb
  change (-149 : Int) ≤ da.exponent at hea
  change (-149 : Int) ≤ db.exponent at heb
  have he : F64.minSubnormalExponent ≤ d.exponent := by
    change (-1074 : Int) ≤ da.exponent + db.exponent
    omega
  have hg := Model.Dyadic.genericFormat_of_significand_lt F64 d hsig he
  have hv : d.toReal = Model.toReal a * Model.toReal b := by
    simpa only [d, Model.toReal_eq, hda, hdb] using Model.Dyadic.toReal_mul da db
  rw [hv] at hg
  exact hg

/-- Once two native inputs have finite binary32 values, native binary64 MUL
is finite and exact. The product's 48-bit/grid and magnitude facts are proved,
not assumed. This theorem does not assert correctness of any widening cast. -/
theorem native_mul_exact_from_raw32_values (x y : Float) (a b : UInt32)
    (hx : x.isFinite = true) (hy : y.isFinite = true)
    (ha : Model.isFinite (raw32 a) = true) (hb : Model.isFinite (raw32 b) = true)
    (hxa : value x = Model.toReal (raw32 a))
    (hyb : value y = Model.toReal (raw32 b)) :
    (x * y).isFinite = true ∧
      value (x * y) = Model.toReal (raw32 a) * Model.toReal (raw32 b) := by
  have hbound : |value x| * |value y| ≤ Model.toReal (Model.posMaxFinite F64) := by
    rw [hxa, hyb]
    exact f32_product_bound (raw32 a) (raw32 b) ha hb
  obtain ⟨hfinite, hround⟩ := native_mul_finite_roundAt x y hx hy hbound
  refine ⟨hfinite, ?_⟩
  rw [hround, hxa, hyb]
  exact FloatLib.Floats.Formats.Flocq.round_preserves_generic
    FloatLib.Floats.Formats.Flocq.nearestEven _
    (f32_product_grid (raw32 a) (raw32 b) ha hb)

end Submission.R24NativeMul


/- R24 portable actual Float64 fold. Input values are arbitrary finite Float
   values, bounded by a power of two; no widening or multiplication theorem is
   assumed. New declarations are NOT_RUN until the fixed helper gate checks them. -/
namespace Submission.R24RepresentationSum
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Floats.Formats.Flocq

abbrev native (x : Float) : Model FloatFormat.binary64 := Model.ofFloatModel x.toModel
noncomputable def rval (x : Float) : ℝ := Model.toReal (native x)
noncomputable def p2 (e : Int) : ℝ := bpow FloatLib.Numerics.binaryRadix e
noncomputable def exactSum (xs : List Float) : ℝ := (xs.map rval).sum

def loop : List Float → Float → Float
  | [], acc => acc
  | x :: xs, acc => loop xs (acc + x)

def sum (xs : List Float) : Float := loop xs (Float.ofBits 0)

theorem p2_pos (e : Int) : 0 < p2 e := bpow.pos _ _

theorem p2_mono {a b : Int} (h : a ≤ b) : p2 a ≤ p2 b :=
  (bpow_le_bpow_iff FloatLib.Numerics.binaryRadix a b).2 h

theorem p2_add (a b : Int) : p2 (a + b) = p2 a * p2 b :=
  bpow.add_exp _ _ _

theorem p2_nat (n : Nat) : p2 (n : Int) = ((2 ^ n : Nat) : ℝ) := by
  simp [p2, bpow, FloatLib.Numerics.binaryRadix, FloatLib.Numerics.Radix.toReal]

theorem scaled_count_le (j L : Nat) (k : Int) (hj : j ≤ 2 ^ L) :
    (j : ℝ) * p2 k ≤ p2 (k + (L : Int)) := by
  have hjR : (j : ℝ) ≤ ((2 ^ L : Nat) : ℝ) := by exact_mod_cast hj
  calc
    (j : ℝ) * p2 k ≤ ((2 ^ L : Nat) : ℝ) * p2 k :=
      mul_le_mul_of_nonneg_right hjR (p2_pos k).le
    _ = p2 (k + (L : Int)) := by
      rw [← p2_nat, ← p2_add]
      congr 1
      omega

theorem native_finite_eq (x : Float) : Model.isFinite (native x) = x.isFinite := by
  rw [← Model.toDyadic?_isSome_eq_isFinite,
    Model.toDyadic?_ieee_eq_model FloatFormat.binary64 (by decide),
    Model.toModel_ofFloatModel]
  change (Model.unpackedToDyadic? x.toModel.unpack).isSome = x.toModel.unpack.isFinite
  cases x.toModel.unpack <;> rfl

theorem native_add (x y : Float) (hx : x.isFinite = true) (hy : y.isFinite = true) :
    native (x + y) = Model.add (native x) (native y) := by
  change Model.ofFloatModel (Float.Model.add x.toModel y.toModel) = _
  rw [Float.Model.add, Model.ofFloatModel_pack]
  have h := Model.add_eq_ofModel_add_of_isFinite (fmt := FloatFormat.binary64)
    (by decide) (Model.ofFloatModel x.toModel) (Model.ofFloatModel y.toModel)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite,
      Float.Model.isFinite] using hx)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite,
      Float.Model.isFinite] using hy)
  rw [Model.toModel_ofFloatModel, Model.toModel_ofFloatModel] at h
  exact h.symm

theorem max_finite_large : p2 286 ≤ Model.toReal (Model.posMaxFinite FloatFormat.binary64) := by
  change p2 286 ≤ Model.toReal
    (Model.ofFields FloatFormat.binary64 false 2046 4503599627370495)
  rw [Model.toReal_ofFields_normal FloatFormat.binary64 false 2046 4503599627370495
    (by decide) (by decide) (by decide)]
  change p2 286 ≤ (1 : ℝ) * 9007199254740991 * p2 971
  rw [one_mul]
  have hpow : p2 286 ≤ p2 971 := p2_mono (by omega)
  have hp := p2_pos 971
  nlinarith

theorem native_add_finite_real (x y : Float)
    (hx : x.isFinite = true) (hy : y.isFinite = true)
    (hb : |rval x| + |rval y| ≤ p2 286) :
    (x + y).isFinite = true ∧
      rval (x + y) = Model.roundAt FloatFormat.binary64 (rval x + rval y) := by
  have hxm : Model.isFinite (native x) = true := by rw [native_finite_eq, hx]
  have hym : Model.isFinite (native y) = true := by rw [native_finite_eq, hy]
  have hbm : |Model.toReal (native x)| + |Model.toReal (native y)| ≤
      Model.toReal (Model.posMaxFinite FloatFormat.binary64) := hb.trans max_finite_large
  constructor
  · rw [← native_finite_eq, native_add x y hx hy]
    exact Model.isFinite_add_of_abs_add_le_posMaxFinite (native x) (native y)
      (by decide) hxm hym hbm
  · change Model.toReal (native (x + y)) =
      Model.roundAt FloatFormat.binary64 (Model.toReal (native x) + Model.toReal (native y))
    rw [native_add x y hx hy]
    exact Model.toReal_add_eq_roundAt_of_abs_add_le_posMaxFinite (native x) (native y)
      (by decide) hxm hym hbm

/- A bounded integer times the given power of two belongs to the actual
   binary64 gradual-underflow grid. This closes the j*M exactness premise. -/
theorem round_grid (j : Nat) (k : Int) (hj : j ≤ 2 ^ 30) (hk : -250 ≤ k) :
    Model.roundAt FloatFormat.binary64 ((j : ℝ) * p2 k) = (j : ℝ) * p2 k := by
  let d : FloatLib.Numerics.Dyadic := ⟨false, j, k⟩
  have hs : d.significand < 2 ^ (FloatFormat.binary64.fracWidth + 1) := by
    change j < 2 ^ 53
    exact lt_of_le_of_lt hj (by norm_num)
  have he : FloatFormat.binary64.minSubnormalExponent ≤ d.exponent := by
    change (-1074 : Int) ≤ k
    omega
  have hg := Model.Dyadic.genericFormat_of_significand_lt FloatFormat.binary64 d hs he
  have hv : d.toReal = (j : ℝ) * p2 k := by
    change (FloatLib.Numerics.Dyadic.mk false j k).toReal = _
    rw [FloatLib.Numerics.Dyadic.toReal_mk_false]
    rfl
  rw [hv] at hg
  exact round_preserves_generic nearestEven _ hg

/- This is obtained from the library's real RNE half-ULP bound, not assumed
   as a property of a hypothetical step operation. The looser full-ULP
   bound deliberately avoids extra one-bit engineering. -/
theorem round_error_power (x : ℝ) (K : Int) (hK : -250 ≤ K) (hx : |x| < p2 K) :
    |Model.roundAt FloatFormat.binary64 x - x| ≤ p2 (K - 53) := by
  by_cases hz : x = 0
  · subst x
    rw [Model.roundAt_zero, sub_self, abs_zero]
    exact (p2_pos _).le
  · have hm : magnitude FloatLib.Numerics.binaryRadix x ≤ K :=
      magnitude_le_of_abs_lt_bpow _ _ _ hz hx
    have hc : cexp FloatLib.Numerics.binaryRadix (Model.fexpOf FloatFormat.binary64) x ≤
        K - 53 := by
      change max (magnitude FloatLib.Numerics.binaryRadix x - 53) (-1074) ≤ K - 53
      exact max_le (by omega) (by omega)
    have hu : ulp FloatLib.Numerics.binaryRadix (Model.fexpOf FloatFormat.binary64) x ≤
        p2 (K - 53) := by
      rw [ulp.of_ne_zero _ _ _ hz]
      exact p2_mono hc
    have he := error_bound_ulp (β := FloatLib.Numerics.binaryRadix)
      (fexp := Model.fexpOf FloatFormat.binary64) nearestEven x
    have hn := ulp.nonneg FloatLib.Numerics.binaryRadix (Model.fexpOf FloatFormat.binary64) x
    change |Model.roundAt FloatFormat.binary64 x - x| ≤
      ulp FloatLib.Numerics.binaryRadix (Model.fexpOf FloatFormat.binary64) x / 2 at he
    exact he.trans (by linarith)

theorem exactSum_nil : exactSum [] = 0 := rfl
theorem exactSum_cons (x : Float) (xs : List Float) :
    exactSum (x :: xs) = rval x + exactSum xs := rfl

theorem zero_native : native (Float.ofBits 0) = Model.zero FloatFormat.binary64 false := by
  decide

theorem zero_value : rval (Float.ofBits 0) = 0 := by
  unfold rval
  rw [zero_native, Model.toReal_zero]

theorem zero_finite : (Float.ofBits 0).isFinite = true := by decide

/- Actual loop invariant: the native addition, result finiteness, real RNE
   step, exact grid bounds, and local error are all proved inside the step. -/
theorem loop_invariant (xs : List Float) (acc : Float) (j L : Nat) (k : Int)
    (hklo : -250 ≤ k) (hkhi : k ≤ 256) (hL : L ≤ 30)
    (hcount : j + xs.length ≤ 2 ^ L)
    (hacc : acc.isFinite = true) (hmag : |rval acc| ≤ (j : ℝ) * p2 k)
    (hxs : ∀ x ∈ xs, x.isFinite = true ∧ |rval x| < p2 k) :
    (loop xs acc).isFinite = true ∧
      |rval (loop xs acc)| ≤ ((j + xs.length : Nat) : ℝ) * p2 k ∧
      |rval (loop xs acc) - (rval acc + exactSum xs)| ≤
        (xs.length : ℝ) * p2 (k + (L : Int) - 53) := by
  induction xs generalizing acc j with
  | nil =>
    simpa only [loop, List.length_nil, Nat.add_zero, exactSum_nil, add_zero,
      sub_self, abs_zero, Nat.cast_zero, zero_mul, le_refl, and_true] using And.intro hacc hmag
  | cons x xs ih =>
    have hx := hxs x (by simp)
    have htail : ∀ y ∈ xs, y.isFinite = true ∧ |rval y| < p2 k := by
      intro y hy
      exact hxs y (by simp [hy])
    have hj : j + 1 ≤ 2 ^ L := by simp only [List.length_cons] at hcount; omega
    have hj30 : j + 1 ≤ 2 ^ 30 :=
      hj.trans (Nat.pow_le_pow_right (by decide) hL)
    have hnextCount : (j + 1) + xs.length ≤ 2 ^ L := by
      simp only [List.length_cons] at hcount
      omega
    have htri : |rval acc| + |rval x| < ((j + 1 : Nat) : ℝ) * p2 k := by
      have hh := add_lt_add_of_le_of_lt hmag hx.2
      convert hh using 1 <;> push_cast <;> ring
    have hglobal : ((j + 1 : Nat) : ℝ) * p2 k ≤ p2 (k + (L : Int)) :=
      scaled_count_le _ _ _ hj
    have htop : p2 (k + (L : Int)) ≤ p2 286 := p2_mono (by omega)
    have hstep := native_add_finite_real acc x hacc hx.1
      (htri.le.trans (hglobal.trans htop))
    have hinput : |rval acc + rval x| < ((j + 1 : Nat) : ℝ) * p2 k :=
      (abs_add_le _ _).trans_lt htri
    have hgrid := round_grid (j + 1) k hj30 hklo
    have hnextMag : |rval (acc + x)| ≤ ((j + 1 : Nat) : ℝ) * p2 k := by
      rw [hstep.2]
      obtain ⟨hlo, hhi⟩ := abs_le.mp hinput.le
      have a := Model.roundAt_mono FloatFormat.binary64 hlo
      have b := Model.roundAt_mono FloatFormat.binary64 hhi
      rw [Model.roundAt_neg, hgrid] at a
      rw [hgrid] at b
      exact abs_le.mpr ⟨a, b⟩
    have herr : |rval (acc + x) - (rval acc + rval x)| ≤
        p2 (k + (L : Int) - 53) := by
      rw [hstep.2]
      exact round_error_power _ _ (by omega) (hinput.trans_le hglobal)
    have hout := ih (acc + x) (j + 1) hnextCount hstep.1 hnextMag htail
    refine ⟨hout.1, ?_, ?_⟩
    · simpa only [loop, List.length_cons, Nat.add_assoc, Nat.add_comm, Nat.add_left_comm]
        using hout.2.1
    · have heq : rval (loop xs (acc + x)) - (rval acc + exactSum (x :: xs)) =
          (rval (loop xs (acc + x)) - (rval (acc + x) + exactSum xs)) +
            (rval (acc + x) - (rval acc + rval x)) := by
        rw [exactSum_cons]
        ring
      change |rval (loop xs (acc + x)) - (rval acc + exactSum (x :: xs))| ≤ _
      rw [heq]
      calc
        _ ≤ |rval (loop xs (acc + x)) - (rval (acc + x) + exactSum xs)| +
              |rval (acc + x) - (rval acc + rval x)| := abs_add_le _ _
        _ ≤ (xs.length : ℝ) * p2 (k + (L : Int) - 53) +
              p2 (k + (L : Int) - 53) := add_le_add hout.2.2 herr
        _ = ((x :: xs).length : ℝ) * p2 (k + (L : Int) - 53) := by
          simp only [List.length_cons, Nat.cast_add, Nat.cast_one]
          ring

theorem sum_enclosure (xs : List Float) (L : Nat) (k : Int)
    (hklo : -250 ≤ k) (hkhi : k ≤ 256) (hL : L ≤ 30)
    (hcount : xs.length ≤ 2 ^ L)
    (hxs : ∀ x ∈ xs, x.isFinite = true ∧ |rval x| < p2 k) :
    (sum xs).isFinite = true ∧
      |rval (sum xs) - exactSum xs| ≤ p2 (k + 2 * (L : Int) - 53) := by
  have h := loop_invariant xs (Float.ofBits 0) 0 L k hklo hkhi hL
    (by simpa using hcount) zero_finite (by simp [zero_value]) hxs
  refine ⟨h.1, ?_⟩
  have he : |rval (sum xs) - exactSum xs| ≤
      (xs.length : ℝ) * p2 (k + (L : Int) - 53) := by
    simpa only [sum, zero_value, zero_add] using h.2.2
  have hc : (xs.length : ℝ) ≤ ((2 ^ L : Nat) : ℝ) := by exact_mod_cast hcount
  calc
    _ ≤ (xs.length : ℝ) * p2 (k + (L : Int) - 53) := he
    _ ≤ ((2 ^ L : Nat) : ℝ) * p2 (k + (L : Int) - 53) :=
      mul_le_mul_of_nonneg_right hc (p2_pos _).le
    _ = p2 (k + 2 * (L : Int) - 53) := by
      rw [← p2_nat, ← p2_add]
      congr 1
      ring

end Submission.R24RepresentationSum


/- R24 actual radius-word and native endpoint semantics.
   This is a portable helper fragment, not a replacement public kernel.
   Endpoint values are nearest-even results; no outward-rounding premise. -/
namespace Submission.R24RadiusEndpoints

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

abbrev F64 := FloatFormat.binary64
abbrev raw (w : UInt64) : Model F64 := Model.ofBits w.toBitVec
abbrev native (x : Float) : Model F64 := Model.ofFloatModel x.toModel
noncomputable def rval (x : Float) : Real := Model.toReal (native x)
noncomputable def p2 (e : Int) : Real :=
  FloatLib.Floats.Formats.Flocq.bpow FloatLib.Numerics.binaryRadix e

@[inline] def radiusWord (H L : UInt64) : UInt64 := (H + (L + L) + 720) <<< 52
@[inline] def radius (H L : UInt64) : Float := Float.ofBits (radiusWord H L)
abbrev radiusExp (H L : UInt64) : Int := (H.toNat : Int) + 2 * (L.toNat : Int) - 303

private theorem p2_pos (e : Int) : 0 < p2 e :=
  FloatLib.Floats.Formats.Flocq.bpow.pos _ _

private theorem p2_mono {a b : Int} (h : a ≤ b) : p2 a ≤ p2 b :=
  (FloatLib.Floats.Formats.Flocq.bpow_le_bpow_iff FloatLib.Numerics.binaryRadix a b).2 h

private theorem p2_add (a b : Int) : p2 (a + b) = p2 a * p2 b :=
  FloatLib.Floats.Formats.Flocq.bpow.add_exp _ _ _

private theorem p2_nat (n : Nat) : p2 (n : Int) = ((2 ^ n : Nat) : Real) := by
  simp [p2, FloatLib.Floats.Formats.Flocq.bpow,
    FloatLib.Numerics.binaryRadix, FloatLib.Numerics.Radix.toReal]

private theorem native_finite_eq (x : Float) : Model.isFinite (native x) = x.isFinite := by
  rw [← Model.toDyadic?_isSome_eq_isFinite,
    Model.toDyadic?_ieee_eq_model F64 (by decide), Model.toModel_ofFloatModel]
  change (Model.unpackedToDyadic? x.toModel.unpack).isSome = x.toModel.unpack.isFinite
  cases x.toModel.unpack <;> rfl

private theorem native_ofBits_decode (w : UInt64) {d : FloatLib.Numerics.Dyadic}
    (hd : Model.toDyadic? (raw w) = some d) : native (Float.ofBits w) = raw w := by
  have hc := R2W01c.modelCanonical_of_decode (by decide) (raw w) hd
  change Model.ofFloatModel (Float.Model.ofBits w) = raw w
  rw [Float.Model.ofBits, Model.ofFloatModel_pack]
  change Model.canonicalizeModel (raw w) = raw w
  exact Model.canonicalizeModel_eq_self _ hc

private theorem radiusWord_nat (H L : UInt64)
    (hH : H.toNat ≤ 506) (hL : L.toNat ≤ 30) :
    (radiusWord H L).toNat = (H.toNat + L.toNat + L.toNat + 720) * 4503599627370496 := by
  have hLL : (L + L).toNat = L.toNat + L.toNat := by
    rw [UInt64.toNat_add]
    change (L.toNat + L.toNat) % 18446744073709551616 = _
    omega
  have hE : (H + (L + L) + 720).toNat = H.toNat + L.toNat + L.toNat + 720 := by
    rw [UInt64.toNat_add, UInt64.toNat_add, hLL]
    change ((H.toNat + (L.toNat + L.toNat)) % 18446744073709551616 + 720) %
      18446744073709551616 = _
    omega
  rw [radiusWord, UInt64.toNat_shiftLeft, hE]
  change ((H.toNat + L.toNat + L.toNat + 720) <<< 52) %
    18446744073709551616 = _
  rw [Nat.shiftLeft_eq]
  omega

private theorem raw_power_fields (w : UInt64) (E : Nat)
    (hE : E < 2047) (hw : w.toNat = E * 4503599627370496) :
    raw w = Model.ofFields F64 false E 0 := by
  have hs : Model.signBit (raw w) = false := by
    rw [Model.signBit_eq_msb, BitVec.msb_eq_decide]
    change decide (9223372036854775808 ≤ w.toNat) = false
    apply Bool.eq_iff_iff.mpr
    simp only [decide_eq_true_eq, Bool.false_eq_true]
    omega
  have he : Model.expField (raw w) = E := by
    unfold Model.expField
    change ((w.toBitVec >>> 52) &&& (BitVec.ofNat 64 2047)).toNat = E
    rw [BitVec.toNat_and, BitVec.toNat_ushiftRight]
    change (w.toNat >>> 52) &&& (2 ^ 11 - 1) = E
    rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow, hw]
    omega
  have hf : Model.fracField (raw w) = 0 := by
    unfold Model.fracField
    change (w.toBitVec &&& (BitVec.ofNat 64 4503599627370495)).toNat = 0
    rw [BitVec.toNat_and]
    change w.toNat &&& (2 ^ 52 - 1) = 0
    rw [Nat.and_two_pow_sub_one_eq_mod, hw]
    omega
  rw [← hs, ← he, ← hf]
  exact (Model.ofFields_signBit_expField_fracField (raw w)).symm

private theorem radius_decode (H L : UInt64)
    (hH : H.toNat ≤ 506) (hL : L.toNat ≤ 30) :
    Model.toDyadic? (raw (radiusWord H L)) =
      some ⟨false, 4503599627370496,
        ((H.toNat + L.toNat + L.toNat + 720 : Nat) : Int) - 1023 - 52⟩ := by
  rw [raw_power_fields (radiusWord H L) (H.toNat + L.toNat + L.toNat + 720)
    (by omega) (radiusWord_nat H L hH hL)]
  exact Model.toDyadic?_ofFields_normal F64 false
    (H.toNat + L.toNat + L.toNat + 720) 0 (by omega) (by omega) (by decide)

/-- The actual UInt64 additions/shift and Float.ofBits radius are finite,
positive, and denote the prescribed power of two. -/
theorem radius_finite_value (H L : UInt64)
    (hH : H.toNat ≤ 506) (hL : L.toNat ≤ 30) :
    (radius H L).isFinite = true ∧
      rval (radius H L) = p2 (radiusExp H L) ∧ 0 < rval (radius H L) := by
  have hd := radius_decode H L hH hL
  have hn : native (radius H L) = raw (radiusWord H L) := native_ofBits_decode _ hd
  have hfin : (radius H L).isFinite = true := by
    rw [← native_finite_eq, hn]
    exact Model.isFinite_eq_true_of_toDyadic?_some hd
  have hv : rval (radius H L) = p2 (radiusExp H L) := by
    unfold rval
    rw [hn, Model.toReal_eq, hd]
    simp only [Model.Dyadic.toReal_eq_signedSignificand,
      FloatLib.Numerics.Dyadic.signedSignificand, Bool.false_eq_true, ite_false,
      Int.cast_natCast]
    change (4503599627370496 : Real) *
      p2 (((H.toNat + L.toNat + L.toNat + 720 : Nat) : Int) - 1023 - 52) = _
    have h52 : p2 52 = (4503599627370496 : Real) := by simpa using p2_nat 52
    rw [← h52, ← p2_add]
    congr 1
    unfold radiusExp
    push_cast
    omega
  refine ⟨hfin, hv, ?_⟩
  rw [hv]
  exact p2_pos _

private theorem native_add (x y : Float) (hx : x.isFinite = true) (hy : y.isFinite = true) :
    native (x + y) = Model.add (native x) (native y) := by
  change Model.ofFloatModel (Float.Model.add x.toModel y.toModel) = _
  rw [Float.Model.add, Model.ofFloatModel_pack]
  have h := Model.add_eq_ofModel_add_of_isFinite (fmt := F64)
    (by decide) (Model.ofFloatModel x.toModel) (Model.ofFloatModel y.toModel)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite, Float.Model.isFinite] using hx)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite, Float.Model.isFinite] using hy)
  rw [Model.toModel_ofFloatModel, Model.toModel_ofFloatModel] at h
  exact h.symm

private theorem native_sub (x y : Float) (hx : x.isFinite = true) (hy : y.isFinite = true) :
    native (x - y) = Model.sub (native x) (native y) := by
  change Model.ofFloatModel (Float.Model.sub x.toModel y.toModel) = _
  rw [Float.Model.sub, Model.ofFloatModel_pack]
  have h := Model.sub_eq_ofModel_sub_of_isFinite (fmt := F64)
    (by decide) (Model.ofFloatModel x.toModel) (Model.ofFloatModel y.toModel)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite, Float.Model.isFinite] using hx)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite, Float.Model.isFinite] using hy)
  rw [Model.toModel_ofFloatModel, Model.toModel_ofFloatModel] at h
  exact h.symm

private theorem max_finite_large : p2 287 ≤ Model.toReal (Model.posMaxFinite F64) := by
  change p2 287 ≤ Model.toReal (Model.ofFields F64 false 2046 4503599627370495)
  rw [Model.toReal_ofFields_normal F64 false 2046 4503599627370495
    (by decide) (by decide) (by decide)]
  change p2 287 ≤ (1 : Real) * 9007199254740991 * p2 971
  rw [one_mul]
  have hpow : p2 287 ≤ p2 971 := p2_mono (by decide)
  have hp := p2_pos 971
  nlinarith

/-- Actual native subtraction/addition endpoints are finite and equal the
respective RNE64 values. Their finiteness is derived, not a premise. -/
theorem native_endpoints_finite_real (s : Float) (H L : UInt64)
    (hH : H.toNat ≤ 506) (hL : L.toNat ≤ 30)
    (hs : s.isFinite = true) (hsize : |rval s| ≤ p2 286) :
    (s - radius H L).isFinite = true ∧
      (s + radius H L).isFinite = true ∧
      rval (s - radius H L) = Model.roundAt F64 (rval s - p2 (radiusExp H L)) ∧
      rval (s + radius H L) = Model.roundAt F64 (rval s + p2 (radiusExp H L)) := by
  obtain ⟨hr, hrv, hrpos⟩ := radius_finite_value H L hH hL
  have he : radiusExp H L ≤ 263 := by unfold radiusExp; omega
  have hsmall : |rval (radius H L)| ≤ p2 286 := by
    rw [abs_of_pos hrpos, hrv]
    exact (p2_mono he).trans (p2_mono (by decide : (263 : Int) ≤ 286))
  have hsum : p2 286 + p2 286 = p2 287 := by
    rw [show (287 : Int) = 286 + 1 by decide, p2_add]
    have h1 : p2 1 = 2 := by simpa using p2_nat 1
    rw [h1]
    ring
  have hbound : |rval s| + |rval (radius H L)| ≤ Model.toReal (Model.posMaxFinite F64) :=
    ((add_le_add hsize hsmall).trans_eq hsum).trans max_finite_large
  have hms : Model.isFinite (native s) = true := by rw [native_finite_eq, hs]
  have hmr : Model.isFinite (native (radius H L)) = true := by rw [native_finite_eq, hr]
  have hsub := Model.isFinite_sub_of_abs_add_le_posMaxFinite
    (native s) (native (radius H L)) (by decide) hms hmr hbound
  have hadd := Model.isFinite_add_of_abs_add_le_posMaxFinite
    (native s) (native (radius H L)) (by decide) hms hmr hbound
  refine ⟨?_, ?_, ?_, ?_⟩
  · rw [← native_finite_eq, native_sub s (radius H L) hs hr]
    exact hsub
  · rw [← native_finite_eq, native_add s (radius H L) hs hr]
    exact hadd
  · unfold rval
    rw [native_sub s (radius H L) hs hr,
      Model.toReal_sub_eq_roundAt _ _ (by decide) hms hmr hsub]
    change Model.roundAt F64 (rval s - rval (radius H L)) = _
    rw [hrv]
  · unfold rval
    rw [native_add s (radius H L) hs hr,
      Model.toReal_add_eq_roundAt _ _ (by decide) hms hmr hadd]
    change Model.roundAt F64 (rval s + rval (radius H L)) = _
    rw [hrv]

end Submission.R24RadiusEndpoints


namespace Submission.R26TailAgreement
open Submission.R24PortableF64
open Submission.R24RepresentationSum

def actualTerms (a b : FloatArray) (index count : Nat) : List Float :=
  (List.range' index count).map (fun i => a.get! i * b.get! i)

theorem sumRemaining_eq_loop (a b : FloatArray) (count index : Nat) (acc : Float) :
    sumRemaining a b index acc count = loop (actualTerms a b index count) acc := by
  induction count generalizing index acc with
  | zero => rfl
  | succ count ih =>
    simpa only [sumRemaining, actualTerms, List.range'_succ, List.map_cons, loop] using
      ih (index + 1) (acc + a.get! index * b.get! index)

theorem actualTerms_length (a b : FloatArray) (index count : Nat) :
    (actualTerms a b index count).length = count := by
  simp only [actualTerms, List.length_map, List.length_range']

theorem sumRemaining_zero_eq_sum (a b : FloatArray) (count : Nat) :
    sumRemaining a b 0 (Float.ofBits 0) count = sum (actualTerms a b 0 count) := by
  exact sumRemaining_eq_loop a b count 0 (Float.ofBits 0)

end Submission.R26TailAgreement


namespace Submission.R26ProducerNumerics
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open R2W01c
open Submission.R24PortableF64
open Submission.R24RepresentationWiden (expWord expWord_toNat wordExp_lt)
open Submission.R25PrepareAgreement
open Submission.R26PreparePeak

noncomputable def p2 (e : Int) : Real := Model.bpow e
noncomputable def rawValue (u : UInt32) : Real := Model.toReal (raw32 u)

theorem raw_finite (u : UInt32) (hf : expWord u ≠ 255) :
    Model.isFinite (raw32 u) = true := by
  have he := wordExp_lt u
  have hne : wordExp u ≠ 255 := by
    intro h
    apply hf
    apply UInt32.toNat_inj.mp
    simpa only [expWord_toNat] using h
  rw [raw32_eq_fields]
  exact Model.isFinite_ofFields_ieee FloatFormat.binary32 (by decide) _ _ _ (by
    change wordExp u < 255
    omega)

theorem prepare_get_finite_value (raw : Array UInt32) (hv : (prepare raw).valid = true)
    (i : Nat) (hi : i < raw.size) :
    ((prepare raw).values.get! i).isFinite = true ∧
      Model.toReal (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat
        ((prepare raw).values.get! i))) = rawValue raw[i] := by
  rw [prepare_get raw hv i hi]
  exact Submission.R25FiniteWiden.finite_actual_value raw[i]
    (prepare_valid_rawfinite raw hv i hi)

theorem prepared_product_exact (rawX rawY : Array UInt32)
    (hx : (prepare rawX).valid = true) (hy : (prepare rawY).valid = true)
    (i : Nat) (hix : i < rawX.size) (hiy : i < rawY.size) :
    ((prepare rawX).values.get! i * (prepare rawY).values.get! i).isFinite = true ∧
      Submission.R24NativeMul.value
        ((prepare rawX).values.get! i * (prepare rawY).values.get! i) =
      rawValue rawX[i] * rawValue rawY[i] := by
  have hxv := prepare_get_finite_value rawX hx i hix
  have hyv := prepare_get_finite_value rawY hy i hiy
  have hfx := raw_finite rawX[i] (prepare_valid_rawfinite rawX hx i hix)
  have hfy := raw_finite rawY[i] (prepare_valid_rawfinite rawY hy i hiy)
  apply Submission.R24NativeMul.native_mul_exact_from_raw32_values
    _ _ rawX[i] rawY[i] hxv.1 hyv.1 hfx hfy
  · simpa only [ExecFloat.Binary.toModel_ofFloat] using hxv.2
  · simpa only [ExecFloat.Binary.toModel_ofFloat] using hyv.2

theorem signed_abs (s : Bool) (m : Nat) (e : Int) :
    |(if s then (-1 : Real) else 1) * (m : Real) * Model.bpow e| =
      (m : Real) * Model.bpow e := by
  cases s <;>
    simp [abs_mul, abs_of_nonneg (Nat.cast_nonneg m),
      abs_of_nonneg (Model.bpow_nonneg e)]

theorem raw_magnitude (u : UInt32) (hf : expWord u ≠ 255) :
    |rawValue u| < p2 ((index32 u).toNat - (125 : Int)) := by
  have he := wordExp_lt u
  have hfrac := wordFrac_lt u
  have hne : wordExp u ≠ 255 := by
    intro h
    apply hf
    apply UInt32.toNat_inj.mp
    simpa only [expWord_toNat] using h
  rw [index_nat, expWord_toNat]
  unfold rawValue
  rw [raw32_eq_fields]
  by_cases hz : wordExp u = 0
  · rw [hz]
    change |Model.toReal (Model.ofFields FloatFormat.binary32 (wordSign u) 0 (wordFrac u))| <
      Model.bpow (-125)
    by_cases hfz : wordFrac u = 0
    · rw [hfz]
      change |Model.toReal (Model.zero FloatFormat.binary32 (wordSign u))| < _
      rw [Model.toReal_zero, abs_zero]
      exact Model.bpow_pos _
    · rw [Model.toReal_ofFields_subnormal FloatFormat.binary32 (wordSign u)
        (wordFrac u) hfz hfrac, signed_abs]
      change (wordFrac u : Real) * Model.bpow (-149) < Model.bpow (-125)
      have hc : (wordFrac u : Real) < (16777216 : Real) := by exact_mod_cast (by omega : wordFrac u < 16777216)
      calc
        _ < (16777216 : Real) * Model.bpow (-149) :=
          mul_lt_mul_of_pos_right hc (Model.bpow_pos _)
        _ = Model.bpow (-125) := by
          have hp : Model.bpow 24 = (16777216 : Real) := by
            norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
              FloatLib.Numerics.binaryRadix, FloatLib.Numerics.Radix.toReal]
          rw [← hp, ← Model.bpow_add]
          norm_num
  · have hpos : 0 < wordExp u := by omega
    rw [Model.toReal_ofFields_normal FloatFormat.binary32 (wordSign u) (wordExp u)
      (wordFrac u) hz (by change wordExp u < 255; omega) hfrac]
    change |(if wordSign u then (-1 : Real) else 1) *
      ((8388608 + wordFrac u : Nat) : Real) * Model.bpow ((wordExp u : Int) - 127 - 23)| < _
    rw [signed_abs]
    have hc : ((8388608 + wordFrac u : Nat) : Real) < (16777216 : Real) := by
      exact_mod_cast (by omega : 8388608 + wordFrac u < 16777216)
    calc
      _ < (16777216 : Real) * Model.bpow ((wordExp u : Int) - 127 - 23) :=
        mul_lt_mul_of_pos_right hc (Model.bpow_pos _)
      _ = p2 (((wordExp u - 1 : Nat) : Int) - 125) := by
        have hp : Model.bpow 24 = (16777216 : Real) := by
          norm_num [Model.bpow, FloatLib.Floats.Formats.Flocq.bpow,
            FloatLib.Numerics.binaryRadix, FloatLib.Numerics.Radix.toReal]
        rw [← hp, ← Model.bpow_add]
        unfold p2
        congr 1
        omega

theorem prepared_raw_magnitude (raw : Array UInt32) (hv : (prepare raw).valid = true)
    (i : Nat) (hi : i < raw.size) :
    |rawValue raw[i]| < p2 ((prepare raw).maxIndex.toNat - (125 : Int)) := by
  have hb := raw_magnitude raw[i] (prepare_valid_rawfinite raw hv i hi)
  have hp := prepare_index_bound raw hv i hi
  refine hb.trans_le ?_
  exact Model.bpow_le_bpow_of_le (by omega)

end Submission.R26ProducerNumerics


namespace Submission.R26ProducerEnclosure
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open Submission.R24PortableF64
open Submission.R25PrepareAgreement
open Submission.R26PreparePeak
open Submission.R26PreparedParameters
open Submission.R26ProducerNumerics
open Submission.R26TailAgreement

abbrev actualH (x y : Array UInt32) : UInt64 :=
  (prepare x).maxIndex.toUInt64 + (prepare y).maxIndex.toUInt64

abbrev actualL (x : Array UInt32) : UInt64 := ceilLog2 (prepare x).raw.size

noncomputable def exactRawSum (x y : Array UInt32) : Real :=
  ((List.range' 0 x.size).map (fun i => rawValue x[i]! * rawValue y[i]!)).sum

theorem prepared_product_bounded (x y : Array UInt32)
    (hx : (prepare x).valid = true) (hy : (prepare y).valid = true)
    (i : Nat) (hix : i < x.size) (hiy : i < y.size) :
    ((prepare x).values.get! i * (prepare y).values.get! i).isFinite = true ∧
      |Submission.R24RepresentationSum.rval
        ((prepare x).values.get! i * (prepare y).values.get! i)| <
      Submission.R24RepresentationSum.p2 ((actualH x y).toNat - (250 : Int)) := by
  have hp := prepared_product_exact x y hx hy i hix hiy
  have hmx := prepared_raw_magnitude x hx i hix
  have hmy := prepared_raw_magnitude y hy i hiy
  refine ⟨hp.1, ?_⟩
  change |Submission.R24NativeMul.value
    ((prepare x).values.get! i * (prepare y).values.get! i)| < _
  rw [hp.2, abs_mul]
  calc
    _ ≤ |rawValue x[i]| * p2 ((prepare y).maxIndex.toNat - (125 : Int)) :=
      mul_le_mul_of_nonneg_left hmy.le (abs_nonneg _)
    _ < p2 ((prepare x).maxIndex.toNat - (125 : Int)) *
        p2 ((prepare y).maxIndex.toNat - (125 : Int)) :=
      mul_lt_mul_of_pos_right hmx (Model.bpow_pos _)
    _ = Submission.R24RepresentationSum.p2 ((actualH x y).toNat - (250 : Int)) := by
      change Model.bpow _ * Model.bpow _ = Model.bpow _
      rw [← Model.bpow_add, prepared_H_nat]
      congr 1
      push_cast
      ring

theorem actualTerms_spec (x y : Array UInt32)
    (hx : (prepare x).valid = true) (hy : (prepare y).valid = true)
    (hsize : x.size = y.size) :
    ∀ term ∈ actualTerms (prepare x).values (prepare y).values 0 x.size,
      term.isFinite = true ∧
      |Submission.R24RepresentationSum.rval term| <
        Submission.R24RepresentationSum.p2 ((actualH x y).toNat - (250 : Int)) := by
  intro term hm
  obtain ⟨i, hi, rfl⟩ := List.mem_map.mp hm
  have hix : i < x.size := by
    have h := (List.mem_range'.mp hi).2
    omega
  have hiy : i < y.size := by omega
  exact prepared_product_bounded x y hx hy i hix hiy

theorem actualTerms_exactSum (x y : Array UInt32)
    (hx : (prepare x).valid = true) (hy : (prepare y).valid = true)
    (hsize : x.size = y.size) :
    Submission.R24RepresentationSum.exactSum
      (actualTerms (prepare x).values (prepare y).values 0 x.size) = exactRawSum x y := by
  unfold Submission.R24RepresentationSum.exactSum actualTerms exactRawSum
  rw [List.map_map]
  congr 1
  apply List.map_congr_left
  intro i hi
  have hix : i < x.size := by
    have h := (List.mem_range'.mp hi).2
    omega
  have hiy : i < y.size := by omega
  have hp := prepared_product_exact x y hx hy i hix hiy
  simpa only [Function.comp_apply, getElem!_pos _ i hix, getElem!_pos _ i hiy] using hp.2

theorem actual_tail_enclosure (x y : Array UInt32)
    (hx : (prepare x).valid = true) (hy : (prepare y).valid = true)
    (hsize : x.size = y.size) :
    let out := sumRemaining (prepare x).values (prepare y).values 0 (Float.ofBits 0) x.size
    out.isFinite = true ∧
      |Submission.R24RepresentationSum.rval out - exactRawSum x y| ≤
        Submission.R24RepresentationSum.p2
          ((actualH x y).toNat + 2 * ((actualL x).toNat : Int) - 303) := by
  have hp := actual_parameters x y hx
  have hcap := prepare_valid_sizecap x hx
  have hL : (actualL x).toNat ≤ 30 := hp.2.1
  have hH : (actualH x y).toNat ≤ 506 := hp.1
  have hc : x.size ≤ 2 ^ (actualL x).toNat := by
    simpa only [prepare_raw] using hp.2.2
  have hs := Submission.R24RepresentationSum.sum_enclosure
    (actualTerms (prepare x).values (prepare y).values 0 x.size)
    (actualL x).toNat ((actualH x y).toNat - (250 : Int))
    (by omega) (by omega) hL
    (by simpa only [actualTerms_length] using hc) (actualTerms_spec x y hx hy hsize)
  dsimp only
  rw [sumRemaining_zero_eq_sum]
  rw [actualTerms_exactSum x y hx hy hsize] at hs
  have hexp : ((actualH x y).toNat - (250 : Int)) +
      2 * ((actualL x).toNat : Int) - 53 =
      (actualH x y).toNat + 2 * ((actualL x).toNat : Int) - 303 := by ring
  simpa only [hexp] using hs

theorem actual_tail_magnitude (x y : Array UInt32)
    (hx : (prepare x).valid = true) (hy : (prepare y).valid = true)
    (hsize : x.size = y.size) :
    |Submission.R24RepresentationSum.rval
      (sumRemaining (prepare x).values (prepare y).values 0 (Float.ofBits 0) x.size)| ≤
      Submission.R24RepresentationSum.p2 286 := by
  have hp := actual_parameters x y hx
  have hc : x.size ≤ 2 ^ (actualL x).toNat := by
    simpa only [prepare_raw] using hp.2.2
  have hi := Submission.R24RepresentationSum.loop_invariant
    (actualTerms (prepare x).values (prepare y).values 0 x.size) (Float.ofBits 0) 0
    (actualL x).toNat ((actualH x y).toNat - (250 : Int))
    (by omega) (by have hh := hp.1; omega) hp.2.1
    (by simpa only [Nat.zero_add, actualTerms_length] using hc)
    Submission.R24RepresentationSum.zero_finite
    (by simp only [Submission.R24RepresentationSum.zero_value, abs_zero,
      Nat.cast_zero, zero_mul, le_refl]) (actualTerms_spec x y hx hy hsize)
  have hmag : |Submission.R24RepresentationSum.rval
      (sumRemaining (prepare x).values (prepare y).values 0 (Float.ofBits 0) x.size)| ≤
      (x.size : Real) * Submission.R24RepresentationSum.p2 ((actualH x y).toNat - (250 : Int)) := by
    simpa only [sumRemaining_eq_loop, actualTerms_length, Nat.zero_add] using hi.2.1
  refine hmag.trans ((Submission.R24RepresentationSum.scaled_count_le
    x.size (actualL x).toNat ((actualH x y).toNat - (250 : Int)) hc).trans ?_)
  apply Submission.R24RepresentationSum.p2_mono
  have hh := hp.1
  have hl := hp.2.1
  omega

theorem actual_radius_finite_value (x y : Array UInt32)
    (hx : (prepare x).valid = true) :
    let H := actualH x y
    let L := actualL x
    let r := Float.ofBits ((H + (L + L) + 720) <<< 52)
    r.isFinite = true ∧
      Submission.R24RadiusEndpoints.rval r =
        Submission.R24RadiusEndpoints.p2 ((H.toNat : Int) + 2 * (L.toNat : Int) - 303) ∧
      0 < Submission.R24RadiusEndpoints.rval r := by
  have hp := actual_parameters x y hx
  exact Submission.R24RadiusEndpoints.radius_finite_value (actualH x y) (actualL x) hp.1 hp.2.1

theorem actual_endpoints_finite_real (x y : Array UInt32)
    (hx : (prepare x).valid = true) (hy : (prepare y).valid = true)
    (hsize : x.size = y.size) :
    let s := sumRemaining (prepare x).values (prepare y).values 0 (Float.ofBits 0) x.size
    let H := actualH x y
    let L := actualL x
    let r := Float.ofBits ((H + (L + L) + 720) <<< 52)
    (s - r).isFinite = true ∧ (s + r).isFinite = true ∧
      Submission.R24RadiusEndpoints.rval (s - r) =
        Model.roundAt FloatFormat.binary64
          (Submission.R24RadiusEndpoints.rval s - Submission.R24RadiusEndpoints.p2
            ((H.toNat : Int) + 2 * (L.toNat : Int) - 303)) ∧
      Submission.R24RadiusEndpoints.rval (s + r) =
        Model.roundAt FloatFormat.binary64
          (Submission.R24RadiusEndpoints.rval s + Submission.R24RadiusEndpoints.p2
            ((H.toNat : Int) + 2 * (L.toNat : Int) - 303)) := by
  have hp := actual_parameters x y hx
  have hs := actual_tail_enclosure x y hx hy hsize
  have hm := actual_tail_magnitude x y hx hy hsize
  exact Submission.R24RadiusEndpoints.native_endpoints_finite_real
    (sumRemaining (prepare x).values (prepare y).values 0 (Float.ofBits 0) x.size)
    (actualH x y) (actualL x) hp.1 hp.2.1 hs.1 hm

end Submission.R26ProducerEnclosure
