namespace R15LowCutoff

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32

/- Reused exact proof bodies from the full-gated df5c UnderflowZero component;
   finiteScale proof originally ported from FloatLib Team, MIT. -/
theorem finiteScale_toNat (exponent : UInt32) :
    (finiteScale exponent).toNat =
      if exponent = 0 then 0 else exponent.toNat - 1 := by
  by_cases hexponent : exponent = 0
  · subst exponent
    simp [finiteScale, FloatLib.Numerics.FixedWord.finiteScale]
  · have hwidened : exponent.toUInt64 ≠ 0 := by
      intro hzero
      apply hexponent
      apply UInt32.toNat_inj.mp
      have := congrArg UInt64.toNat hzero
      simpa using this
    rw [finiteScale, FloatLib.Numerics.FixedWord.finiteScale_toNat]
    simp [hexponent, hwidened]

/-- A shift of at least65 returns zero even for an arbitrary 64-bit product. -/
theorem rseAny_zero (product scale : UInt64) (hs : scale.toNat ≤ 84) :
    FastMul.rseAny product (149 - scale) = 0 := by
  have hscale : scale ≤ (149 : UInt64) := by
    rw [UInt64.le_iff_toNat_le]
    change scale.toNat ≤ 149
    omega
  have ht : (149 - scale).toNat = 149 - scale.toNat := by
    rw [UInt64.toNat_sub_of_le _ _ hscale]
    rfl
  have h0 : (149 - scale : UInt64) ≠ 0 := by
    intro h
    have hh := congrArg UInt64.toNat h
    rw [ht] at hh
    change 149 - scale.toNat = 0 at hh
    omega
  have h64 : ¬ (149 - scale : UInt64) < 64 := by
    rw [UInt64.lt_iff_toNat_lt, ht]
    change ¬ 149 - scale.toNat < 64
    omega
  have he64 : (149 - scale : UInt64) ≠ 64 := by
    intro h
    have hh := congrArg UInt64.toNat h
    rw [ht] at hh
    change 149 - scale.toNat = 64 at hh
    omega
  simp [FastMul.rseAny, h0, h64, he64]

/-- No mantissa bound is needed: even a full UInt64 rounds to zero here. -/
theorem roundP_zero (sign : Bool) (product scale : UInt64) (hs : scale.toNat ≤ 84) :
    FastMul.roundP sign product scale = (if sign then 0x80000000 else 0) := by
  have hl : (FastMul.fastLog2 product).toNat < 64 := by
    rw [FastMul.fastLog2_eq]
    exact FastMul.log2_lt_64 product
  have hposition : FastMul.fastLog2 product + scale < (172 : UInt64) := by
    rw [UInt64.lt_iff_toNat_lt, UInt64.toNat_add]
    change ((FastMul.fastLog2 product).toNat + scale.toNat) %
      18446744073709551616 < 172
    rw [Nat.mod_eq_of_lt (by omega)]
    omega
  have hscale : scale < (149 : UInt64) := by
    rw [UInt64.lt_iff_toNat_lt]
    change scale.toNat < 149
    omega
  have hf := rseAny_zero product scale hs
  simp [FastMul.roundP, hposition, hscale, hf]

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

end R15LowCutoff

@[inline] def mul (x y : Binary32) : Binary32 :=
  let ex := FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField x.raw.1
  let ey := FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField y.raw.1
  if ex + ey < (128 : UInt32) then
    if ex + ey ≤ (84 : UInt32) then
      FastMul.ofBits
        (if Bool.xor
            (FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.signBit x.raw.1)
            (FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.signBit y.raw.1)
          then 0x80000000 else 0)
    else LowScale.mul x y
  else nativeMul x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  unfold mul
  dsimp only
  split
  · split
    · rename_i hcut
      rw [R15LowCutoff.shortcut_eq_low x y hcut]
      exact LowScale.mul_spec x y
    · exact LowScale.mul_spec x y
  · exact nativeMul_spec x y
