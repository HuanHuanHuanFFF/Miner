/- Requires exact Pair8CacheProof2850a16c before this leaf. NOT_RUN. -/
namespace Submission.R22CacheSelected
open FloatLib.Floats Competition

theorem pack_selected (batch n p : Nat) (B : Array Binary32)
    (row : Fin (batch * n)) (g : Fin (R22Pair8.groups p)) (c : Fin 2)
    (hcol : 2 * g.val + c.val < p) :
    R15ThinPairs.select ((R22Pair8.packB batch n p B).getD
      (row.val * R22Pair8.groups p + g.val) R22Pair8.zeroPair) c.val =
      ExecFloat.Binary.toFloat32 (B.getD (row.val * p + 2 * g.val + c.val) posZero) := by
  rcases c with ⟨c, hc⟩
  have h : c = 0 ∨ c = 1 := by omega
  rcases h with rfl | rfl
  · simpa only [R15ThinPairs.select, ↓reduceIte, Nat.add_zero] using
      R22Pair8.packB_s0 batch n p B row g
  · simpa only [R15ThinPairs.select, if_neg Nat.one_ne_zero] using
      R22Pair8.packB_s1 batch n p B row g hcol

theorem index_joins (n p b g k c : Nat) :
    b * n * R22Pair8.groups p + g + k * R22Pair8.groups p =
      (b * n + k) * R22Pair8.groups p + g ∧
    b * n * p + 2 * g + c + k * p = (b * n + k) * p + 2 * g + c := by
  constructor <;> simp only [Nat.add_mul] <;> omega

end Submission.R22CacheSelected
