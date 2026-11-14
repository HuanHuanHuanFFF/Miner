import Submission

namespace BranchlessRNESeed
open FloatLib.Numerics

private theorem quotient_bias (p half : Nat) (hhalf : 0 < half) :
    roundQuotientEven p (2 * half) =
      (p + half - 1 + (p / (2 * half)) % 2) / (2 * half) := by
  let q := p / (2 * half)
  let r := p % (2 * half)
  have hr : r < 2 * half := Nat.mod_lt _ (by omega)
  have hparity : q % 2 < 2 := Nat.mod_lt _ (by decide)
  have hp : p = (2 * half) * q + r := (Nat.div_add_mod p (2 * half)).symm
  have hb : p + half - 1 + q % 2 =
      (r + half - 1 + q % 2) + (2 * half) * q := by omega
  change (if 2 * r < 2 * half then q
    else if 2 * half < 2 * r then q + 1
    else if q % 2 == 0 then q else q + 1) =
      (p + half - 1 + q % 2) / (2 * half)
  rw [hb, Nat.add_mul_div_left _ _ (by omega)]
  simp only [beq_iff_eq]
  split_ifs with hbelow habove heven
  · have hd : (r + half - 1 + q % 2) / (2 * half) = 0 :=
      Nat.div_eq_of_lt (by omega)
    rw [hd]
    omega
  · have hd : (r + half - 1 + q % 2) / (2 * half) = 1 :=
      Nat.div_eq_of_lt_le (by omega) (by omega)
    rw [hd]
    omega
  · have hd : (r + half - 1 + q % 2) / (2 * half) = 0 :=
      Nat.div_eq_of_lt (by omega)
    rw [hd]
    omega
  · have hd : (r + half - 1 + q % 2) / (2 * half) = 1 :=
      Nat.div_eq_of_lt_le (by omega) (by omega)
    rw [hd]
    omega

theorem nat_bias (p t : Nat) (ht : t = 23 ∨ t = 24) :
    roundShiftRightEven p t =
      (p + 2 ^ (t - 1) - 1 + (p >>> t) % 2) >>> t := by
  rcases ht with rfl | rfl
  · simpa [roundShiftRightEven_eq_roundQuotientEven, Nat.shiftRight_eq_div_pow] using
      quotient_bias p 4194304 (by decide)
  · simpa [roundShiftRightEven_eq_roundQuotientEven, Nat.shiftRight_eq_div_pow] using
      quotient_bias p 8388608 (by decide)


theorem nat_grouped_bias (p t : Nat) (ht : t=23 ∨ t=24) :
    roundShiftRightEven p t =
      (p+(2^(t-1)-1)+(p >>> t)%2) >>> t := by
  have hpos := Nat.two_pow_pos (t-1)
  have he : p+2^(t-1)-1 = p+(2^(t-1)-1) := by omega
  simpa only [he] using nat_bias p t ht

end BranchlessRNESeed

namespace R19PostBias
open FloatLib.Numerics

def shift (p : Nat) : Nat := if p < 140737488355328 then 23 else 24
def biased (p : Nat) : Nat := p + (2 ^ (shift p - 1) - 1) + (p >>> shift p) % 2

/-- Uses the retained uncompiled bias proof, not an independent new proof. -/
theorem biased_quotient (p : Nat) :
    biased p >>> shift p = roundShiftRightEven p (shift p) := by
  have hk : shift p = 23 ∨ shift p = 24 := by
    unfold shift
    split <;> simp_all
  exact (BranchlessRNESeed.nat_grouped_bias p (shift p) hk).symm

theorem biased_bounds (p : Nat)
    (hlo : 70368744177664 ≤ p) (hhi : p ≤ 281474943156225) :
    70368744177664 ≤ biased p ∧ biased p ≤ 281474951544833 := by
  have hpar : (p >>> shift p) % 2 < 2 := Nat.mod_lt _ (by decide)
  unfold biased
  by_cases hp : p < 140737488355328
  · simp only [shift,if_pos hp]
    norm_num only [Nat.reduceSub,Nat.reducePow]
    simp only [shift,if_pos hp] at hpar
    omega
  · simp only [shift,if_neg hp]
    norm_num only [Nat.reduceSub,Nat.reducePow]
    simp only [shift,if_neg hp] at hpar
    omega

end R19PostBias
