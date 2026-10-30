-- Self-authored adapter from this role's alternate Nat proof to D's word proof.
-- Only use after the alternate root compiles; preserve D's primitive runtime.
namespace R27ReciprocalProof

theorem reciprocal_estimate_bounds (base numerator divisor : Nat)
    (base_pos : 0 < base) (numerator_bound : numerator < base)
    (divisor_pos : 0 < divisor) :
    let reciprocal := (base - 1) / divisor
    let estimate := numerator * reciprocal / base
    estimate * divisor ≤ numerator ∧ numerator < (estimate + 2) * divisor :=
  Submission.R27Reciprocal.reciprocal_bounds base numerator divisor
    base_pos numerator_bound divisor_pos

theorem reciprocal_divrem (base numerator divisor : Nat)
    (base_pos : 0 < base) (numerator_bound : numerator < base)
    (divisor_pos : 0 < divisor) :
    let reciprocal := (base - 1) / divisor
    let estimate := numerator * reciprocal / base
    let remainder := numerator - estimate * divisor
    (if divisor ≤ remainder then (estimate + 1, remainder - divisor)
      else (estimate, remainder)) = (numerator / divisor, numerator % divisor) := by
  exact Submission.R27Reciprocal.corrected_exact base numerator divisor
    base_pos numerator_bound divisor_pos

end R27ReciprocalProof
