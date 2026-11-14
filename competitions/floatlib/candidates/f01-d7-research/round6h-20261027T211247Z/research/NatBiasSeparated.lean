import Submission

/- NOT_RUN. Diagnostic replacement for the isolated24f0 seed only.
   The integer solver sees fresh remainder/parity parameters, not p/div/mod
   coupled to symbolic multiplication. Original statement and runtime unchanged. -/
namespace BranchlessRNESeed
open FloatLib.Numerics

private theorem add_half_sub_one (p half : Nat) (hhalf : 0 < half) :
    p + half - 1 = p + (half - 1) := by omega

private theorem bias_increment (r half odd : Nat)
    (hhalf : 0 < half) (hr : r < 2 * half) (hodd : odd < 2) :
    (if 2 * r < 2 * half then 0
      else if 2 * half < 2 * r then 1 else if odd = 0 then 0 else 1) =
        (r + (half - 1) + odd) / (2 * half) := by
  split_ifs with hbelow habove heven
  · exact (Nat.div_eq_of_lt (by omega)).symm
  · exact (Nat.div_eq_of_lt_le (by omega) (by omega)).symm
  · exact (Nat.div_eq_of_lt (by omega)).symm
  · exact (Nat.div_eq_of_lt_le (by omega) (by omega)).symm

private theorem quotient_bias (p half : Nat) (hhalf : 0 < half) :
    roundQuotientEven p (2 * half) =
      (p + half - 1 + (p / (2 * half)) % 2) / (2 * half) := by
  let q := p / (2 * half)
  let r := p % (2 * half)
  have hd : 0 < 2 * half := Nat.mul_pos (by decide) hhalf
  have hr : r < 2 * half := Nat.mod_lt _ hd
  have hodd : q % 2 < 2 := Nat.mod_lt _ (by decide)
  have hp : p = (2 * half) * q + r := (Nat.div_add_mod p (2 * half)).symm
  have hb : p + half - 1 + q % 2 =
      (r + (half - 1) + q % 2) + (2 * half) * q := by
    calc
      p + half - 1 + q % 2 = p + (half - 1) + q % 2 := by
        rw [add_half_sub_one p half hhalf]
      _ = ((2 * half) * q + r) + (half - 1) + q % 2 :=
        congrArg (fun z => z + (half - 1) + q % 2) hp
      _ = (r + (half - 1) + q % 2) + (2 * half) * q := by ac_rfl
  have hdiv : (p + half - 1 + q % 2) / (2 * half) =
      (r + (half - 1) + q % 2) / (2 * half) + q := by
    rw [hb, Nat.add_mul_div_left _ _ hd]
  have hround : roundQuotientEven p (2 * half) =
      q + (if 2 * r < 2 * half then 0
        else if 2 * half < 2 * r then 1 else if q % 2 = 0 then 0 else 1) := by
    change (if 2 * r < 2 * half then q
      else if 2 * half < 2 * r then q + 1 else if q % 2 == 0 then q else q + 1) = _
    simp only [beq_iff_eq]
    split_ifs <;> simp only [Nat.add_zero]
  rw [bias_increment r half (q % 2) hhalf hr hodd] at hround
  exact hround.trans ((Nat.add_comm _ _).trans hdiv.symm)

theorem nat_bias (p t : Nat) (ht : t = 23 ∨ t = 24) :
    roundShiftRightEven p t =
      (p + 2 ^ (t - 1) - 1 + (p >>> t) % 2) >>> t := by
  rcases ht with rfl | rfl
  · rw [roundShiftRightEven_eq_roundQuotientEven]
    norm_num only [Nat.reducePow, Nat.reduceSub]
    have h := quotient_bias p 4194304 (by decide)
    norm_num only [Nat.reduceMul] at h
    simpa only [Nat.shiftRight_eq_div_pow, Nat.reducePow] using h
  · rw [roundShiftRightEven_eq_roundQuotientEven]
    norm_num only [Nat.reducePow, Nat.reduceSub]
    have h := quotient_bias p 8388608 (by decide)
    norm_num only [Nat.reduceMul] at h
    simpa only [Nat.shiftRight_eq_div_pow, Nat.reducePow] using h

end BranchlessRNESeed
