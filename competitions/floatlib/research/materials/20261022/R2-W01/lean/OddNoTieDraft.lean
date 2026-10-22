import ContractTensor

/-!
UNCOMPILED DRAFT. No Lean executable is available.
Here `shift` is the exponent in the power-of-two divisor, not the divisor itself.
The hypothesis `n % 2 = 1` is the computational form of oddness.
No FloatLib rounding result is assumed or proved by these arithmetic lemmas.
-/

namespace R2W01OddNoTieDraft

/-- A remainder equal to half a multiple of four would make the original
natural number even, contradicting the supplied odd-parity certificate. -/
theorem odd_mod_four_mul_ne_half (n k : Nat) (hodd : n % 2 = 1) :
    n % (4 * k) ≠ 2 * k := by
  intro hhalf
  have heven : n = 2 * (k + 2 * k * (n / (4 * k))) := by
    calc
      n = n % (4 * k) + (4 * k) * (n / (4 * k)) :=
        (Nat.mod_add_div n (4 * k)).symm
      _ = 2 * (k + 2 * k * (n / (4 * k))) := by
        rw [hhalf]
        ring
  have hmod : n % 2 = 0 := by
    rw [heven]
    simp
  omega

/-- An odd significand shifted right by at least two bits cannot land at the
halfway remainder. The exceptional one-bit shift is intentionally excluded. -/
theorem odd_mod_two_pow_ne_half (n shift : Nat)
    (hodd : n % 2 = 1) (hshift : 2 ≤ shift) :
    n % 2 ^ shift ≠ 2 ^ (shift - 1) := by
  have hpow : 2 ^ shift = 4 * 2 ^ (shift - 2) := by
    calc
      2 ^ shift = 2 ^ ((shift - 2) + 2) := by
        congr 1
        omega
      _ = 4 * 2 ^ (shift - 2) := by simp [pow_add, Nat.mul_comm]
  have hhalf : 2 ^ (shift - 1) = 2 * 2 ^ (shift - 2) := by
    calc
      2 ^ (shift - 1) = 2 ^ ((shift - 2) + 1) := by
        congr 1
        omega
      _ = 2 * 2 ^ (shift - 2) := by simp [pow_succ, Nat.mul_comm]
  rw [hpow, hhalf]
  exact odd_mod_four_mul_ne_half n (2 ^ (shift - 2)) hodd

/-- The same exclusion in the exact form tested by nearest-even quotient
rounding: twice the remainder is not the denominator. -/
theorem odd_mod_two_pow_twice_ne_denominator (n shift : Nat)
    (hodd : n % 2 = 1) (hshift : 2 ≤ shift) :
    2 * (n % 2 ^ shift) ≠ 2 ^ shift := by
  intro htie
  have hpow : 2 ^ shift = 2 * 2 ^ (shift - 1) := by
    calc
      2 ^ shift = 2 ^ ((shift - 1) + 1) := by
        congr 1
        omega
      _ = 2 * 2 ^ (shift - 1) := by simp [pow_succ, Nat.mul_comm]
  apply odd_mod_two_pow_ne_half n shift hodd hshift
  omega

end R2W01OddNoTieDraft
