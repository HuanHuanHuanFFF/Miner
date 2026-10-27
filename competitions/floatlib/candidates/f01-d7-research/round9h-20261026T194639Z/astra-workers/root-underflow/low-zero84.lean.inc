namespace R19LowZero

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32

@[inline] def signed (x y : Binary32) : Binary32 :=
  FastMul.ofBits
    (if Bool.xor (signBit x.raw.1) (signBit y.raw.1) then 0x80000000 else 0)

theorem bounds (a b : UInt32) (h : expField a + expField b ≤ (84 : UInt32)) :
    (expField a).toNat + (expField b).toNat ≤ 84 := by
  have ha : (expField a).toNat < 256 := by
    rw [FastMul.expField_toNat]
    omega
  have hb : (expField b).toNat < 256 := by
    rw [FastMul.expField_toNat]
    omega
  rw [UInt32.le_iff_toNat_le, UInt32.toNat_add] at h
  change ((expField a).toNat + (expField b).toNat) % 4294967296 ≤ 84 at h
  rw [Nat.mod_eq_of_lt (by omega)] at h
  exact h

theorem scale_bound (a b : UInt32)
    (h : (expField a).toNat + (expField b).toNat ≤ 84) :
    (finiteScale (expField a) + finiteScale (expField b)).toNat ≤ 84 := by
  have ha : (finiteScale (expField a)).toNat ≤ (expField a).toNat := by
    rw [UnderflowZero.finiteScale_toNat]
    split <;> omega
  have hb : (finiteScale (expField b)).toNat ≤ (expField b).toNat := by
    rw [UnderflowZero.finiteScale_toNat]
    split <;> omega
  rw [UInt64.toNat_add]
  change ((finiteScale (expField a)).toNat +
    (finiteScale (expField b)).toNat) % 18446744073709551616 ≤ 84
  exact (Nat.mod_le _ _).trans (by omega)

theorem eq_exec (x y : Binary32)
    (h : expField x.raw.1 + expField y.raw.1 ≤ (84 : UInt32)) :
    signed x y = ExecFloat.mul x y := by
  have hb := bounds x.raw.1 y.raw.1 h
  have hx : expField x.raw.1 ≠ (0xff : UInt32) := by
    intro he
    have hh := congrArg UInt32.toNat he
    change (expField x.raw.1).toNat = 255 at hh
    omega
  have hy : expField y.raw.1 ≠ (0xff : UInt32) := by
    intro he
    have hh := congrArg UInt32.toNat he
    change (expField y.raw.1).toNat = 255 at hh
    omega
  have hs : FastMul.special x.raw.1 y.raw.1 = false := by
    simp [FastMul.special, FastMul.sm1_eq, hx, hy]
  have he : ExecFloat.mul x y = FastMul.mul x y :=
    (ExecFloat.Proof.mul_eq_spec x y).trans (FastMul.mul_spec x y).symm
  rw [he]
  simp only [signed, FastMul.mul, hs, Bool.false_eq_true, ite_false, FastMul.core]
  congr 1
  exact (UnderflowZero.roundP_zero _ _ _ (scale_bound _ _ hb)).symm

end R19LowZero
