/- Requires Nat8Projection-v1. Pure projection/base facts; NOT_RUN. -/
namespace Submission.R22Resident8Projection
open FloatLib.Floats Competition

theorem rowBase_consecutive (base n : Nat) (r : Fin 4) :
    rowBase base (base + n) (base + 2 * n) (base + 3 * n) r = base + r.val * n := by
  rcases r with ⟨r, hr⟩
  have h : r = 0 ∨ r = 1 ∨ r = 2 ∨ r = 3 := by omega
  rcases h with rfl | rfl | rfl | rfl <;>
    simp only [rowBase, Nat.zero_mul, Nat.one_mul, Nat.add_zero]

theorem projectRow_diagonal (z : Float32) (r : Fin 4) :
    projectRow ⟨z,z,z,z,z,z,z,z⟩ r = ⟨z,z⟩ := by
  rcases r with ⟨r, hr⟩
  have h : r = 0 ∨ r = 1 ∨ r = 2 ∨ r = 3 := by omega
  rcases h with rfl | rfl | rfl | rfl <;> rfl

theorem select_diagonal (z : Float32) (c : Nat) : R15ThinPairs.select ⟨z,z⟩ c = z := by
  unfold R15ThinPairs.select
  split <;> rfl

end Submission.R22Resident8Projection
