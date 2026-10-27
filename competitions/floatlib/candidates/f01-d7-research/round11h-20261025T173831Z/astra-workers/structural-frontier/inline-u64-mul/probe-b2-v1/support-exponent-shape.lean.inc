namespace Submission.R14ExponentShift

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

def product (mx my : UInt32) : Nat := mx.toNat * my.toNat
def middleExponent (p : Nat) : Nat := p.log2 + R14NatNormal.carry p + 127
def storedFraction (p : Nat) : Nat := R14NatNormal.mantissa p - 8388608

theorem product_bounds (mx my : UInt32)
    (hx0 : 8388608 ≤ mx.toNat) (hx : mx.toNat < 16777216)
    (hy0 : 8388608 ≤ my.toNat) (hy : my.toNat < 16777216) :
    70368744177664 ≤ product mx my ∧ product mx my ≤ 281474943156225 := by
  have hl := Nat.mul_le_mul hx0 hy0
  have hh := Nat.mul_le_mul (show mx.toNat ≤ 16777215 by omega)
    (show my.toNat ≤ 16777215 by omega)
  norm_num at hl hh
  exact ⟨hl, hh⟩

theorem middle_bounds (p : Nat)
    (hp0 : 70368744177664 ≤ p) (hp : p ≤ 281474943156225) :
    173 ≤ middleExponent p ∧ middleExponent p ≤ 174 ∧ storedFraction p < 8388608 := by
  have hh : p < 281474976710656 := by omega
  have hl := R14NatNormal.leading_bounds p hp0 hh
  have hc := R14NatNormal.carry_le p
  have hm := R14NatNormal.mantissa_bounds p hp0 hh
  have hcases : p.log2 = 46 ∨ p.log2 = 47 := by omega
  unfold middleExponent storedFraction
  rcases hcases with h46 | h47
  · rw [h46]
    omega
  · have hc0 := R14NatNormal.no_carry_at_47 p hp h47
    rw [h47, hc0]
    omega

end Submission.R14ExponentShift
