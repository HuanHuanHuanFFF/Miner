import ContractExact

/- Exact integer foundation for a reciprocal division refinement. No axiom,
   native_decide, sorry, floating-point approximation or runtime substitution. -/
namespace R27ReciprocalProof

theorem reciprocal_estimate_bounds (base numerator divisor : Nat)
    (base_pos : 0 < base) (numerator_bound : numerator < base)
    (divisor_pos : 0 < divisor) :
    let reciprocal := (base - 1) / divisor
    let estimate := numerator * reciprocal / base
    estimate * divisor ≤ numerator ∧ numerator < (estimate + 2) * divisor := by
  dsimp only
  let reciprocal := (base - 1) / divisor
  let estimate := numerator * reciprocal / base
  have reciprocal_low : reciprocal * divisor ≤ base - 1 :=
    Nat.div_mul_le_self (base - 1) divisor
  have reciprocal_high : base ≤ (reciprocal + 1) * divisor := by
    have remainder_bound := Nat.mod_lt (base - 1) divisor_pos
    have decomposition := Nat.div_add_mod (base - 1) divisor
    dsimp [reciprocal]
    nlinarith
  have estimate_low : estimate * base ≤ numerator * reciprocal :=
    Nat.div_mul_le_self (numerator * reciprocal) base
  have estimate_high : numerator * reciprocal < (estimate + 1) * base := by
    have remainder_bound := Nat.mod_lt (numerator * reciprocal) base_pos
    have decomposition := Nat.div_add_mod (numerator * reciprocal) base
    dsimp [estimate]
    nlinarith
  constructor
  · have h1 := Nat.mul_le_mul_right divisor estimate_low
    have h2 := Nat.mul_le_mul_left numerator reciprocal_low
    nlinarith
  · have h1 := Nat.mul_le_mul_left numerator reciprocal_high
    have h2 := Nat.mul_lt_mul_of_pos_right estimate_high divisor_pos
    have h3 := Nat.mul_lt_mul_of_pos_right numerator_bound divisor_pos
    nlinarith

theorem reciprocal_divrem (base numerator divisor : Nat)
    (base_pos : 0 < base) (numerator_bound : numerator < base)
    (divisor_pos : 0 < divisor) :
    let reciprocal := (base - 1) / divisor
    let estimate := numerator * reciprocal / base
    let remainder := numerator - estimate * divisor
    (if divisor ≤ remainder then (estimate + 1, remainder - divisor)
     else (estimate, remainder)) = (numerator / divisor, numerator % divisor) := by
  dsimp only
  let reciprocal := (base - 1) / divisor
  let estimate := numerator * reciprocal / base
  obtain ⟨lower, upper⟩ := reciprocal_estimate_bounds base numerator divisor
    base_pos numerator_bound divisor_pos
  change estimate * divisor ≤ numerator at lower
  change numerator < (estimate + 2) * divisor at upper
  have decomposition := Nat.div_add_mod numerator divisor
  have remainder_bound := Nat.mod_lt numerator divisor_pos
  by_cases correction : divisor ≤ numerator - estimate * divisor
  · rw [if_pos correction]
    have original_subtraction := Nat.sub_add_cancel lower
    have correction_subtraction := Nat.sub_add_cancel correction
    have equation : numerator = (estimate + 1) * divisor +
        (numerator - estimate * divisor - divisor) := by nlinarith
    have small : numerator - estimate * divisor - divisor < divisor := by nlinarith
    have quotient : estimate + 1 = numerator / divisor := by
      by_cases left : estimate + 1 < numerator / divisor
      · have gap : estimate + 2 ≤ numerator / divisor := by omega
        have scaled := Nat.mul_le_mul_right divisor gap
        nlinarith
      · by_cases right : numerator / divisor < estimate + 1
        · have gap : numerator / divisor + 1 ≤ estimate + 1 := by omega
          have scaled := Nat.mul_le_mul_right divisor gap
          nlinarith
        · omega
    simp only [quotient]
    congr 1
    nlinarith
  · rw [if_neg correction]
    have original_subtraction := Nat.sub_add_cancel lower
    have equation : numerator = estimate * divisor +
        (numerator - estimate * divisor) := by omega
    have small : numerator - estimate * divisor < divisor := by omega
    have quotient : estimate = numerator / divisor := by
      by_cases left : estimate < numerator / divisor
      · have gap : estimate + 1 ≤ numerator / divisor := by omega
        have scaled := Nat.mul_le_mul_right divisor gap
        nlinarith
      · by_cases right : numerator / divisor < estimate
        · have gap : numerator / divisor + 1 ≤ estimate := by omega
          have scaled := Nat.mul_le_mul_right divisor gap
          nlinarith
        · omega
    simp only [quotient]
    congr 1
    nlinarith

end R27ReciprocalProof
