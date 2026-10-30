import ContractExact

namespace Submission.R27Reciprocal

-- R is floor((B-1)/d), so multiply-high underestimates by at most one.
-- This theorem is about mathematical integers, independent of word wrapping.
theorem reciprocal_bounds (B a d : Nat) (hB : 0 < B) (ha : a < B) (hd : 0 < d) :
    let R := (B - 1) / d
    let q := a * R / B
    q * d ≤ a ∧ a < (q + 2) * d := by
  dsimp only
  let R := (B - 1) / d
  let q := a * R / B
  change q * d ≤ a ∧ a < (q + 2) * d
  have hR0 : R * d ≤ B - 1 := by
    simpa only [R] using Nat.div_mul_le_self (B - 1) d
  have hR1 : B ≤ (R + 1) * d := by
    have he := Nat.mod_add_div (B - 1) d
    have hr := Nat.mod_lt (B - 1) hd
    change (B - 1) % d + d * R = B - 1 at he
    rw [Nat.add_mul, Nat.one_mul, Nat.mul_comm R d]
    omega
  have hq0 : q * B ≤ a * R := by
    simpa only [q] using Nat.div_mul_le_self (a * R) B
  have hq1 : a * R < (q + 1) * B := by
    have he := Nat.mod_add_div (a * R) B
    have hr := Nat.mod_lt (a * R) hB
    change a * R % B + B * q = a * R at he
    rw [Nat.add_mul, Nat.one_mul, Nat.mul_comm q B]
    omega
  have low : (q * d) * B ≤ a * B := calc
    (q * d) * B = (q * B) * d := by ring
    _ ≤ (a * R) * d := Nat.mul_le_mul_right d hq0
    _ = a * (R * d) := by ring
    _ ≤ a * B := Nat.mul_le_mul_left a (by omega)
  have high : a * B < ((q + 2) * d) * B := calc
    a * B ≤ a * ((R + 1) * d) := Nat.mul_le_mul_left a hR1
    _ = (a * R) * d + a * d := by ring
    _ < ((q + 1) * B) * d + B * d :=
      Nat.add_lt_add (Nat.mul_lt_mul_of_pos_right hq1 hd)
        (Nat.mul_lt_mul_of_pos_right ha hd)
    _ = ((q + 2) * d) * B := by ring
  constructor
  · by_contra h
    have h' : a * B < (q * d) * B :=
      Nat.mul_lt_mul_of_pos_right (by omega) hB
    omega
  · by_contra h
    have h' : ((q + 2) * d) * B ≤ a * B := Nat.mul_le_mul_right B (by omega)
    omega

def corrected (B a d : Nat) : Nat × Nat :=
  let q := a * ((B - 1) / d) / B
  let r := a - q * d
  if d ≤ r then (q + 1, r - d) else (q, r)

theorem corrected_exact (B a d : Nat) (hB : 0 < B) (ha : a < B) (hd : 0 < d) :
    corrected B a d = (a / d, a % d) := by
  have hb := reciprocal_bounds B a d hB ha hd
  let q := a * ((B - 1) / d) / B
  change q * d ≤ a ∧ a < (q + 2) * d at hb
  let r := a - q * d
  have he : r + q * d = a := Nat.sub_add_cancel hb.1
  have hr : r < 2 * d := by
    have hu := hb.2
    rw [Nat.add_mul] at hu
    omega
  change (if d ≤ r then (q + 1, r - d) else (q, r)) = _
  by_cases hc : d ≤ r
  · rw [if_pos hc]
    have hq : a / d = q + 1 := Nat.div_eq_of_lt_le
      (by rw [Nat.add_mul, Nat.one_mul]; omega)
      (by simpa [Nat.add_assoc] using hb.2)
    have hm := Nat.mod_add_div a d
    rw [hq, Nat.mul_add, Nat.mul_one, Nat.mul_comm d q] at hm
    have hm' : a % d = r - d := by omega
    rw [hq, hm']
  · rw [if_neg hc]
    have hq : a / d = q := Nat.div_eq_of_lt_le hb.1
      (by rw [Nat.add_mul, Nat.one_mul]; omega)
    have hm := Nat.mod_add_div a d
    rw [hq, Nat.mul_comm d q] at hm
    have hm' : a % d = r := by omega
    rw [hq, hm']

end Submission.R27Reciprocal
