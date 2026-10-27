namespace R6NormalMul

open FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32

/-- Products of two normal 24-bit significands have leading bit 46 or 47. -/
@[inline] def leading (x : UInt64) : UInt64 :=
  if 0x400000000000 ≤ x ∧ x < (0x1000000000000 : UInt64) then
    if x < (0x800000000000 : UInt64) then 46 else 47
  else FastMul.fastLog2 x

theorem leading_eq (x : UInt64) : leading x = FastMul.fastLog2 x := by
  unfold leading
  split
  · rename_i h
    have hlo := h.1
    have hhi := h.2
    rw [UInt64.le_iff_toNat_le] at hlo
    rw [UInt64.lt_iff_toNat_lt] at hhi
    change 70368744177664 ≤ x.toNat at hlo
    change x.toNat < 281474976710656 at hhi
    split
    · rename_i hm
      rw [UInt64.lt_iff_toNat_lt] at hm
      change x.toNat < 140737488355328 at hm
      rw [FastMul.fastLog2_eq]
      apply UInt64.toNat_inj.mp
      change 46 = x.toNat.log2
      symm
      apply (Nat.log2_eq_iff (by omega : x.toNat ≠ 0)).mpr
      constructor <;> norm_num <;> omega
    · rename_i hm
      rw [UInt64.lt_iff_toNat_lt] at hm
      change ¬ x.toNat < 140737488355328 at hm
      rw [FastMul.fastLog2_eq]
      apply UInt64.toNat_inj.mp
      change 47 = x.toNat.log2
      symm
      apply (Nat.log2_eq_iff (by omega : x.toNat ≠ 0)).mpr
      constructor <;> norm_num <;> omega
  · rfl

