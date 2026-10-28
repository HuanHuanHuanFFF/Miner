/- Requires exact Pair8CacheProof2850a16c, Nat8CacheSelecteda457ed45,
   and accepted Nat8Projection-v179574fb1. NOT_RUN; no runtime change. -/
namespace Submission.R22CacheSelected
open FloatLib.Floats Competition

theorem cacheView_hread (batch n p b : Nat) (B : Array Binary32)
    (hb : b < batch) (g : Fin (R22Pair8.groups p)) (c : Fin 2)
    (hcol : 2 * g.val + c.val < p) :
    ∀ i : Fin n,
      R15ThinPairs.select
        ((R22Resident8Projection.cacheView n p
          (b * n * R22Pair8.groups p + g.val) (R22Pair8.packB batch n p B)).get i) c.val =
      ExecFloat.Binary.toFloat32
        (B.getD (b * n * p + 2 * g.val + c.val + i.val * p) posZero) := by
  intro i
  rw [R22Resident8Projection.cacheView_get]
  have hrow : b * n + i.val < batch * n := by
    have hm := Nat.mul_le_mul_right n (show b + 1 ≤ batch by omega)
    rw [Nat.add_mul, Nat.one_mul] at hm
    have hi := i.isLt
    omega
  have hs := pack_selected batch n p B ⟨b * n + i.val, hrow⟩ g c hcol
  change R15ThinPairs.select
      ((R22Pair8.packB batch n p B).getD
        ((b * n + i.val) * R22Pair8.groups p + g.val) R22Pair8.zeroPair) c.val =
    ExecFloat.Binary.toFloat32
      (B.getD ((b * n + i.val) * p + 2 * g.val + c.val) posZero) at hs
  have hj := index_joins n p b g.val i.val c.val
  rw [← hj.1, ← hj.2] at hs
  exact hs

end Submission.R22CacheSelected
