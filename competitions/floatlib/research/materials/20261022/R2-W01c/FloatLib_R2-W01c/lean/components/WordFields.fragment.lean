namespace R2W01c

open FloatLib.Floats.Formats.BinaryInterchange
open R2W01b

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
  simp only [Model.signBit_eq_msb, raw32_bits, BitVec.msb_eq_decide, wordSign]

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

theorem mantissa_toNat (u : UInt32) :
    (mantissa u).toNat = 8388608 + wordFrac u := by
  rw [mantissa, UInt32.toNat_or, UInt32.toNat_and]
  change (u.toNat &&& (2 ^ 23 - 1)) ||| 2 ^ 23 = 8388608 + wordFrac u
  rw [Nat.and_two_pow_sub_one_eq_mod,
    Nat.or_two_pow_eq_add_of_lt (Nat.mod_lt u.toNat (by decide : 0 < 2 ^ 23))]
  exact Nat.add_comm _ _

theorem mantissa_bounds (u : UInt32) :
    8388608 ≤ (mantissa u).toNat ∧ (mantissa u).toNat < 16777216 := by
  rw [mantissa_toNat]
  have hf := wordFrac_lt u
  omega

theorem normal_wordExp_bounds (u : UInt32) (hn : NormalBand u) :
    24 ≤ wordExp u ∧ wordExp u < 255 := by
  rcases hn with ⟨hl, hh⟩
  rw [UInt32.le_iff_toNat_le, magnitude_toNat] at hl
  rw [UInt32.lt_iff_toNat_lt, magnitude_toNat] at hh
  change 201326592 ≤ u.toNat % 2147483648 at hl
  change u.toNat % 2147483648 < 2139095040 at hh
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  unfold wordExp
  omega

theorem tableIndex_nat (u : UInt32) :
    (tableIndex u).toNat = u.toNat / 8388608 := by
  rw [tableIndex, UInt32.toNat_shiftRight]
  change u.toNat >>> 23 = u.toNat / 8388608
  exact Nat.shiftRight_eq_div_pow u.toNat 23

theorem tableExp_nat (u : UInt32) :
    (tableIndex u &&& 255).toNat = wordExp u := by
  rw [UInt32.toNat_and, tableIndex_nat]
  change (u.toNat / 8388608) &&& (2 ^ 8 - 1) =
    u.toNat / 8388608 % 2 ^ 8
  exact Nat.and_two_pow_sub_one_eq_mod _ 8

theorem high_bit_of_lt512 (n : Nat) (hn : n < 512) :
    n &&& 256 = n / 256 * 256 := by
  change n &&& 2 ^ 8 = n / 256 * 256
  rw [Nat.and_two_pow, Nat.testBit_eq_decide_div_mod_eq]
  change (decide (n / 256 % 2 = 1)).toNat * 256 = n / 256 * 256
  by_cases h : n < 256
  · have hd : n / 256 = 0 := Nat.div_eq_of_lt h
    simp [hd]
  · have hd : n / 256 = 1 := by omega
    simp [hd]

theorem tableSign_nat (u : UInt32) :
    ((tableIndex u &&& 256) <<< 23).toNat =
      u.toNat / 2147483648 * 2147483648 := by
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  have hj : u.toNat / 8388608 < 512 := by omega
  rw [UInt32.toNat_shiftLeft, UInt32.toNat_and, tableIndex_nat]
  change (((u.toNat / 8388608) &&& 256) <<< 23) % 4294967296 = _
  rw [high_bit_of_lt512 _ hj, Nat.shiftLeft_eq]
  change (u.toNat / 8388608 / 256 * 256 * 8388608) % 4294967296 = _
  omega

theorem scaleBits_nat (u : UInt32) (hn : NormalBand u) :
    (scaleBits (tableIndex u)).toNat =
      u.toNat / 2147483648 * 2147483648 + (wordExp u - 23) * 8388608 := by
  have he := normal_wordExp_bounds u hn
  have het := tableExp_nat u
  have helo : (24 : UInt32) ≤ (tableIndex u &&& 255) := by
    rw [UInt32.le_iff_toNat_le, het]
    exact he.1
  have hehi : (tableIndex u &&& 255) ≤ (254 : UInt32) := by
    rw [UInt32.le_iff_toNat_le, het]
    change wordExp u ≤ 254
    omega
  have hg :
      (decide (24 ≤ (tableIndex u &&& 255)) &&
        decide ((tableIndex u &&& 255) ≤ 254)) = true := by
    simp only [Bool.and_eq_true, decide_eq_true_eq]
    exact ⟨helo, hehi⟩
  have hsub : ((tableIndex u &&& 255) - 23).toNat = wordExp u - 23 := by
    have hle : (23 : UInt32) ≤ (tableIndex u &&& 255) := by
      rw [UInt32.le_iff_toNat_le, het]
      change 23 ≤ wordExp u
      omega
    simpa only [het] using
      UInt32.toNat_sub_of_le (tableIndex u &&& 255) 23 hle
  have hshift : (((tableIndex u &&& 255) - 23) <<< 23).toNat =
      (wordExp u - 23) * 8388608 := by
    rw [UInt32.toNat_shiftLeft, hsub]
    change ((wordExp u - 23) <<< 23) % 4294967296 = _
    rw [Nat.shiftLeft_eq]
    change ((wordExp u - 23) * 8388608) % 4294967296 = _
    exact Nat.mod_eq_of_lt (by omega)
  unfold scaleBits
  dsimp only
  rw [if_pos hg, UInt32.toNat_or, tableSign_nat, hshift]
  have hlo : (wordExp u - 23) * 8388608 < 2 ^ 31 := by
    change (wordExp u - 23) * 8388608 < 2147483648
    omega
  rw [Nat.mul_comm (u.toNat / 2147483648) 2147483648]
  exact (Nat.two_pow_add_eq_or_of_lt hlo (u.toNat / 2147483648)).symm

theorem scale_wordSign (u : UInt32) (hn : NormalBand u) :
    wordSign (scaleBits (tableIndex u)) = wordSign u := by
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  have he := normal_wordExp_bounds u hn
  apply Bool.eq_iff_iff.mpr
  simp only [wordSign, decide_eq_true_eq]
  rw [scaleBits_nat u hn]
  omega

theorem scale_wordExp (u : UInt32) (hn : NormalBand u) :
    wordExp (scaleBits (tableIndex u)) = wordExp u - 23 := by
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  have he := normal_wordExp_bounds u hn
  change (scaleBits (tableIndex u)).toNat / 8388608 % 256 = wordExp u - 23
  rw [scaleBits_nat u hn]
  omega

theorem scale_wordFrac (u : UInt32) (hn : NormalBand u) :
    wordFrac (scaleBits (tableIndex u)) = 0 := by
  have hu := u.toNat_lt_size
  change u.toNat < 4294967296 at hu
  have he := normal_wordExp_bounds u hn
  change (scaleBits (tableIndex u)).toNat % 8388608 = 0
  rw [scaleBits_nat u hn]
  omega

theorem normal_raw32_decode (u : UInt32) (hn : NormalBand u) :
    Model.toDyadic? (raw32 u) =
      some ⟨wordSign u, (mantissa u).toNat, (wordExp u : Int) - 150⟩ := by
  have he := normal_wordExp_bounds u hn
  rw [raw32_eq_fields, mantissa_toNat]
  exact fields32_toDyadic (wordSign u) (wordExp u) (wordFrac u)
    (by omega) he.2 (wordFrac_lt u)

theorem scale_raw32_decode (u : UInt32) (hn : NormalBand u) :
    Model.toDyadic? (raw32 (scaleBits (tableIndex u))) =
      some ⟨wordSign u, 8388608, (wordExp u : Int) - 173⟩ := by
  have he := normal_wordExp_bounds u hn
  rw [raw32_eq_fields, scale_wordSign u hn, scale_wordExp u hn, scale_wordFrac u hn]
  have hd := fields32_toDyadic (wordSign u) (wordExp u - 23) 0
    (by omega) (by omega) (by decide)
  have hexp : ((wordExp u - 23 : Nat) : Int) - 150 =
      (wordExp u : Int) - 173 := by omega
  simpa only [Nat.add_zero, hexp] using hd

end R2W01c
