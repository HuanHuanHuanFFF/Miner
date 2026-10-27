/- OPTIONAL RESERVE / NOT_COMPILED_THIS_COMPOSITION.
   Insert while namespace Submission is open, after R15LowCutoff helpers;
   replace its exported mul + mul_spec with the final two declarations here.
   Do not append duplicate exported declarations.
   LowZero proofs copied from exact full-gated e139, namespace rename only.
   This is not a request for another full D and not a speed claim. -/
namespace R15ResidualZero

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32

theorem outer_finite (a b : UInt32)
    (h : expField a + expField b < (128 : UInt32)) :
    expField a ≠ 0xff ∧ expField b ≠ 0xff := by
  have ha : (expField a).toNat < 2 ^ 8 := by
    simpa only [FastMul.toUInt32_ofUInt32] using expField_lt (ofUInt32 a)
  have hb : (expField b).toNat < 2 ^ 8 := by
    simpa only [FastMul.toUInt32_ofUInt32] using expField_lt (ofUInt32 b)
  have hsum : (expField a).toNat + (expField b).toNat < 2 ^ 32 := by
    norm_num at ha hb ⊢
    omega
  rw [UInt32.lt_iff_toNat_lt, UInt32.toNat_add,
    Nat.mod_eq_of_lt hsum] at h
  change (expField a).toNat + (expField b).toNat < 128 at h
  constructor
  · intro he
    have he' : (expField a).toNat = 255 := by
      simpa using congrArg UInt32.toNat he
    omega
  · intro he
    have he' : (expField b).toNat = 255 := by
      simpa using congrArg UInt32.toNat he
    omega

theorem outer_special_false (a b : UInt32)
    (h : expField a + expField b < (128 : UInt32)) :
    FastMul.special a b = false := by
  have hf := outer_finite a b h
  simp [FastMul.special, FastMul.sm1_eq, hf.1, hf.2]


@[inline] def signedZero (sign : Bool) : UInt32 :=
  if sign then 0x80000000 else 0

theorem mantissa_zero (a : UInt32) (h : R2W01b.magnitude a = 0) :
    finiteMantissa (expField a) (fracField a) = (0 : UInt64) := by
  cases (R2W01b.magnitude_zero_iff a).mp h with
  | inl ha =>
    subst a
    decide
  | inr ha =>
    subst a
    decide

theorem product_zero (a b : UInt32)
    (hz : R2W01b.magnitude a = 0 ∨ R2W01b.magnitude b = 0) :
    finiteMantissa (expField a) (fracField a) *
      finiteMantissa (expField b) (fracField b) = (0 : UInt64) := by
  cases hz with
  | inl ha => simp only [mantissa_zero a ha, UInt64.zero_mul]
  | inr hb => simp only [mantissa_zero b hb, UInt64.mul_zero]

theorem core_zero (a b : UInt32)
    (hz : R2W01b.magnitude a = 0 ∨ R2W01b.magnitude b = 0) :
    FastMul.core a b = signedZero (Bool.xor (signBit a) (signBit b)) := by
  simp [FastMul.core, product_zero a b hz, FastMul.roundP, signedZero]

theorem zero_eq_low (x y : Binary32)
    (h : expField x.raw.1 + expField y.raw.1 < (128 : UInt32))
    (hz : R2W01b.magnitude x.raw.1 = 0 ∨ R2W01b.magnitude y.raw.1 = 0) :
    FastMul.ofBits (signedZero (Bool.xor (signBit x.raw.1) (signBit y.raw.1))) =
      LowScale.mul x y := by
  rw [LowScale.mul_eq]
  have hs := outer_special_false x.raw.1 y.raw.1 h
  simp [FastMul.mul, hs, core_zero x.raw.1 y.raw.1 hz]

end R15ResidualZero

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
    else if R2W01b.magnitude x.raw.1 = 0 ∨ R2W01b.magnitude y.raw.1 = 0 then
      FastMul.ofBits (R15ResidualZero.signedZero
        (Bool.xor
          (FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.signBit x.raw.1)
          (FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.signBit y.raw.1)))
    else LowScale.mul x y
  else nativeMul x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  unfold mul
  dsimp only
  split
  · rename_i hlow
    split
    · rename_i hcut
      rw [R15LowCutoff.shortcut_eq_low x y hcut]
      exact LowScale.mul_spec x y
    · split
      · rename_i hzero
        rw [R15ResidualZero.zero_eq_low x y hlow hzero]
        exact LowScale.mul_spec x y
      · exact LowScale.mul_spec x y
  · exact nativeMul_spec x y
