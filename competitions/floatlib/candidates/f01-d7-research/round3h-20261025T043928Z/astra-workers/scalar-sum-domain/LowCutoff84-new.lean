/- R15: conservative exponent-only scalar shortcut.
   Existing arbitrary-product roundP_zero proof is inserted before this block.
   This fragment is a new uncompiled integration, not accepted Lean evidence. -/

theorem cutoff_nat (a b : UInt32)
    (h : expField a + expField b ≤ (84 : UInt32)) :
    (expField a).toNat + (expField b).toNat ≤ 84 := by
  have ha : (expField a).toNat < 2 ^ 8 := by
    simpa only [FastMul.toUInt32_ofUInt32] using expField_lt (ofUInt32 a)
  have hb : (expField b).toNat < 2 ^ 8 := by
    simpa only [FastMul.toUInt32_ofUInt32] using expField_lt (ofUInt32 b)
  have hsum : (expField a).toNat + (expField b).toNat < 2 ^ 32 := by
    norm_num at ha hb ⊢
    omega
  rw [UInt32.le_iff_toNat_le, UInt32.toNat_add, Nat.mod_eq_of_lt hsum] at h
  exact h

theorem cutoff_special_false (a b : UInt32)
    (h : expField a + expField b ≤ (84 : UInt32)) :
    FastMul.special a b = false := by
  have hh := cutoff_nat a b h
  have ha : expField a ≠ 0xff := by
    intro he
    have hn := congrArg UInt32.toNat he
    change (expField a).toNat = 255 at hn
    omega
  have hb : expField b ≠ 0xff := by
    intro he
    have hn := congrArg UInt32.toNat he
    change (expField b).toNat = 255 at hn
    omega
  simp [FastMul.special, FastMul.sm1_eq, ha, hb]

theorem scale_sum_le (a b : UInt32)
    (h : expField a + expField b ≤ (84 : UInt32)) :
    (finiteScale (expField a) + finiteScale (expField b)).toNat ≤ 84 := by
  have hh := cutoff_nat a b h
  have ha : (finiteScale (expField a)).toNat ≤ (expField a).toNat := by
    rw [finiteScale_toNat]
    split <;> omega
  have hb : (finiteScale (expField b)).toNat ≤ (expField b).toNat := by
    rw [finiteScale_toNat]
    split <;> omega
  rw [UInt64.toNat_add]
  change ((finiteScale (expField a)).toNat + (finiteScale (expField b)).toNat) %
    18446744073709551616 ≤ 84
  rw [Nat.mod_eq_of_lt (by omega)]
  omega

theorem shortcut_eq_low (x y : Binary32)
    (h : expField x.raw.1 + expField y.raw.1 ≤ (84 : UInt32)) :
    FastMul.ofBits
      (if Bool.xor (signBit x.raw.1) (signBit y.raw.1) then 0x80000000 else 0) =
      LowScale.mul x y := by
  rw [LowScale.mul_eq]
  have hs := cutoff_special_false x.raw.1 y.raw.1 h
  simp only [FastMul.mul, hs, Bool.false_eq_true, ite_false, FastMul.core]
  congr 1
  exact (roundP_zero _ _ _ (scale_sum_le x.raw.1 y.raw.1 h)).symm
