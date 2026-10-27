/- Draft / NOT_RUN. Generic mathematical extension of the two finite-shift
   fragments. No runtime function or new candidate. Positive shift is essential.
   Nat.add_mul_div_left / div_eq_of_lt_le checked in pinned Lean Div/Basic.lean. -/
namespace Submission.R14GeneralBias

open FloatLib.Numerics

theorem quotient_bias (p half : Nat) (hhalf : 0 < half) :
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

theorem nat_bias (p t : Nat) (ht : 1 ≤ t) :
    roundShiftRightEven p t =
      (p + 2 ^ (t - 1) - 1 + (p >>> t) % 2) >>> t := by
  have hpow : 2 ^ t = 2 * 2 ^ (t - 1) := by
    have h := Nat.pow_succ 2 (t - 1)
    rw [show t - 1 + 1 = t by omega] at h
    simpa only [Nat.mul_comm] using h
  simpa only [roundShiftRightEven_eq_roundQuotientEven,
    Nat.shiftRight_eq_div_pow, hpow] using
    quotient_bias p (2 ^ (t - 1)) (Nat.two_pow_pos _)

end Submission.R14GeneralBias
