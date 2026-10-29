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
theorem eNat (u : UInt32) : (expWord u).toNat = wordExp u := by
  exact tableExp_nat u
theorem fNat (u : UInt32) : (fracWord u).toNat = wordFrac u := by
  rw [fracWord, UInt32.toNat_and]
  change u.toNat &&& (2 ^ 23 - 1) = u.toNat % 2 ^ 23
  exact Nat.and_two_pow_sub_one_eq_mod u.toNat 23
theorem eLt (u : UInt32) : wordExp u < 256 := Nat.mod_lt _ (by decide)
theorem sNat (u : UInt32) :
    (signWord u).toNat = u.toNat / 2147483648 * 9223372036854775808 := by
  rw [signWord, UInt64.toNat_shiftLeft, UInt64.toNat_shiftRight, UInt32.toNat_toUInt64]
  change ((u.toNat >>> 31) <<< 63) % 18446744073709551616 = _
  rw [Nat.shiftRight_eq_div_pow, Nat.shiftLeft_eq]
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  omega
theorem ewNat (u : UInt32) : (expWide u).toNat = wordExp u + 896 := by
  rw [expWide, UInt64.toNat_add, UInt32.toNat_toUInt64, eNat]
  have he := eLt u
  change (wordExp u + 896) % 18446744073709551616 = _
  omega
theorem esNat (u : UInt32) :
    (expWide u <<< 52).toNat = (wordExp u + 896) * 4503599627370496 := by
  rw [UInt64.toNat_shiftLeft, ewNat]
  change ((wordExp u + 896) <<< 52) % 18446744073709551616 = _
  rw [Nat.shiftLeft_eq]
  have he := eLt u
  omega
theorem fsNat (u : UInt32) :
    ((fracWord u).toUInt64 <<< 29).toNat = wordFrac u * 536870912 := by
  rw [UInt64.toNat_shiftLeft, UInt32.toNat_toUInt64, fNat]
  change (wordFrac u <<< 29) % 18446744073709551616 = _
  rw [Nat.shiftLeft_eq]
  have hf := wordFrac_lt u
  omega
theorem wideNat (u : UInt32) (he0 : 0 < wordExp u) :
    (widenBits u).toNat = u.toNat / 2147483648 * 9223372036854775808 +
      (wordExp u + 896) * 4503599627370496 + wordFrac u * 536870912 := by
  have hne : expWord u ≠ 0 := by
    intro h
    have hh := eNat u
    rw [h] at hh
    change 0 = wordExp u at hh
    omega
  unfold widenBits
  rw [if_neg hne, UInt64.toNat_or, UInt64.toNat_or, sNat,
    esNat, fsNat]
  have he := eLt u
  have hf := wordFrac_lt u
  have hE : (wordExp u + 896) * 4503599627370496 < 2 ^ 63 := by
    change (wordExp u + 896) * 4503599627370496 < 9223372036854775808
    omega
  have hF : wordFrac u * 536870912 < 2 ^ 52 := by
    change wordFrac u * 536870912 < 4503599627370496
    omega
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
theorem bits (w : UInt64) : (raw64 w).bits = w.toBitVec := rfl
theorem sign (w : UInt64) :
    Model.signBit (raw64 w) = decide (9223372036854775808 ≤ w.toNat) := by
  rw [Model.signBit_eq_msb, bits]
  exact BitVec.msb_eq_decide w.toBitVec
theorem exp (w : UInt64) :
    Model.expField (raw64 w) = w.toNat / 4503599627370496 % 2048 := by
  unfold Model.expField
  rw [bits]
  change ((w.toBitVec >>> 52) &&& (BitVec.ofNat 64 2047)).toNat = _
  rw [BitVec.toNat_and, BitVec.toNat_ushiftRight]
  change (w.toNat >>> 52) &&& (2 ^ 11 - 1) = w.toNat / 4503599627370496 % 2 ^ 11
  rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]
theorem frac (w : UInt64) :
    Model.fracField (raw64 w) = w.toNat % 4503599627370496 := by
  unfold Model.fracField
  rw [bits]
  change (w.toBitVec &&& (BitVec.ofNat 64 4503599627370495)).toNat = _
  rw [BitVec.toNat_and]
  change w.toNat &&& (2 ^ 52 - 1) = w.toNat % 2 ^ 52
  exact Nat.and_two_pow_sub_one_eq_mod w.toNat 52
theorem fields (w : UInt64) :
    raw64 w = Model.ofFields FloatFormat.binary64
      (decide (9223372036854775808 ≤ w.toNat))
      (w.toNat / 4503599627370496 % 2048) (w.toNat % 4503599627370496) := by
  rw [← sign, ← exp, ← frac]
  exact (Model.ofFields_signBit_expField_fracField (raw64 w)).symm
theorem wideFields (u : UInt32) (he0 : 0 < wordExp u) :
    raw64 (widenBits u) = Model.ofFields FloatFormat.binary64 (wordSign u)
      (wordExp u + 896) (wordFrac u * 536870912) := by
  have hw := wideNat u he0
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  have he := eLt u
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
  rw [fields, hs, hE, hF]
theorem normal_decode (u : UInt32) (hn : 0 < wordExp u ∧ wordExp u < 255) :
    Model.toDyadic? (raw64 (widenBits u)) =
      some ⟨wordSign u, (8388608 + wordFrac u) * 536870912,
        (wordExp u : Int) - 150 - 29⟩ := by
  rw [wideFields u hn.1]
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
theorem wideZ : widenBits 0 = 0 := by decide
theorem wideNZ : widenBits 0x80000000 = 0x8000000000000000 := by decide
theorem raw_finite (u : UInt32) (h : Domain u) :
    Model.isFinite (raw64 (widenBits u)) = true := by
  rcases h with hn | hz
  · exact Model.isFinite_eq_true_of_toDyadic?_some (normal_decode u hn)
  · rcases zero_word_cases u hz.1 hz.2 with rfl | rfl
    · rw [wideZ]
      change Model.isFinite (Model.zero FloatFormat.binary64 false) = true
      simp
    · rw [wideNZ]
      change Model.isFinite (Model.zero FloatFormat.binary64 true) = true
      simp
theorem ofBitsModel (w : UInt64) {d : FloatLib.Numerics.Dyadic}
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
  exact ofBitsModel _ hd
theorem native_finite (u : UInt32) (h : Domain u) : (value u).isFinite = true := by
  rw [← Submission.R24RepresentationSum.native_finite_eq]
  change Model.isFinite (native64 (value u)) = true
  rw [native_model u h]
  exact raw_finite u h
theorem shiftReal (s : Bool) (m : Nat) (e : Int) :
    (FloatLib.Numerics.Dyadic.mk s (m * 536870912) (e - 29)).toReal =
      (FloatLib.Numerics.Dyadic.mk s m e).toReal := by
  let d : FloatLib.Numerics.Dyadic := ⟨s, m, e⟩
  have hs :
      ((FloatLib.Numerics.Dyadic.mk s (m * 536870912) (e - 29)).signedSignificand : ℝ) =
        (d.signedSignificand : ℝ) *
          FloatLib.Floats.Formats.Flocq.bpow FloatLib.Numerics.binaryRadix 29 := by
    simpa only [Nat.shiftLeft_eq] using Model.Dyadic.signedSignificand_shiftLeft d 29
  rw [Model.Dyadic.toReal_eq_signedSignificand, hs, mul_assoc,
    ← FloatLib.Floats.Formats.Flocq.bpow.add_exp]
  have he : (29 : Int) + (e - 29) = e := by omega
  rw [he]
  exact (Model.Dyadic.toReal_eq_signedSignificand d).symm
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
    exact shiftReal _ _ _
  · rcases zero_word_cases u hz.1 hz.2 with rfl | rfl
    · rw [wideZ]
      change Model.toReal (Model.zero FloatFormat.binary64 false) =
        Model.toReal (Model.zero FloatFormat.binary32 false)
      simp
    · rw [wideNZ]
      change Model.toReal (Model.zero FloatFormat.binary64 true) =
        Model.toReal (Model.zero FloatFormat.binary32 true)
      simp
end Submission.R24RepresentationWiden
