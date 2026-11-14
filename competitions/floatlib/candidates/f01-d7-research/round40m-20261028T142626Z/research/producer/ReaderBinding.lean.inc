
/- Integration seam, NOT_RUN. Requires exact R22 nat8-projection and
   indexed8-loop-probe2 leaves plus R23IndexedProducer.packB_read. -/
namespace Submission.R23IndexedProducer
open FloatLib.Floats Competition

theorem cacheView_read (batch n p : Nat) (B : Array Binary32) (b : Fin batch)
    (g : Fin (R22Pair8.groups p)) (k : Fin n) (c : Fin 2) (hc : 2 * g.val + c.val < p) :
    R15ThinPairs.select ((R22Resident8Projection.cacheView n p
      (b.val * n * R22Pair8.groups p + g.val) (R22Pair8.packB batch n p B)).get k) c.val =
      ExecFloat.Binary.toFloat32 (B.getD (b.val * n * p + 2 * g.val + c.val + k.val * p) posZero) := by
  rw [R22Resident8Projection.cacheView_get]
  exact packB_read batch n p B b g k c hc

theorem zero_lane (r : Fin 4) (c : Fin 2) :
    R15ThinPairs.select (R22Resident8Projection.projectRow
      (⟨Packed10.zero32, Packed10.zero32, Packed10.zero32, Packed10.zero32,
        Packed10.zero32, Packed10.zero32, Packed10.zero32, Packed10.zero32⟩ : R22Pair8.Cell) r)
      c.val = Packed10.zero32 := by
  rcases r with ⟨r, hr⟩
  have hcases : r = 0 ∨ r = 1 ∨ r = 2 ∨ r = 3 := by omega
  rcases hcases with rfl | rfl | rfl | rfl <;>
    simp [R22Resident8Projection.projectRow, R15ThinPairs.select]

theorem within_lane (batch n p baseA : Nat) (A B : Array Binary32) (b : Fin batch)
    (g : Fin (R22Pair8.groups p))
    (bound : R22IndexedResident8.TileBounds p n baseA
      (b.val * n * R22Pair8.groups p + g.val) A.size (R22Pair8.packB batch n p B).size)
    (r : Fin 4) (c : Fin 2) (hc : 2 * g.val + c.val < p) :
    R15ThinPairs.select (R22Resident8Projection.projectRow
      (R22IndexedResident8.within p n baseA (b.val * n * R22Pair8.groups p + g.val)
        A (R22Pair8.packB batch n p B) bound) r) c.val =
      NativeFinal.dotLoop n
        (R22Resident8Projection.rowBase baseA (baseA + n) (baseA + 2 * n) (baseA + 3 * n) r)
        (b.val * n * p + 2 * g.val + c.val) p A B 0 Packed10.zero32 := by
  rw [R22IndexedResident8.within_eq]
  have h := R22Resident8Projection.loop_lane n p
    baseA (baseA + n) (baseA + 2 * n) (baseA + 3 * n)
    (b.val * n * p + 2 * g.val) (b.val * n * R22Pair8.groups p + g.val)
    A B (R22Pair8.packB batch n p B) r c
    (fun k => cacheView_read batch n p B b g k c hc) 0
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
  simpa only [Nat.zero_mul, Nat.add_zero, zero_lane] using h

theorem finish_lane (batch n p baseA : Nat) (A B : Array Binary32) (b : Fin batch)
    (g : Fin (R22Pair8.groups p))
    (bound : R22IndexedResident8.TileBounds p n baseA
      (b.val * n * R22Pair8.groups p + g.val) A.size (R22Pair8.packB batch n p B).size)
    (r : Fin 4) (c : Fin 2) (hc : 2 * g.val + c.val < p) :
    Packed10.finish n
      (R22Resident8Projection.rowBase baseA (baseA + n) (baseA + 2 * n) (baseA + 3 * n) r)
      (b.val * n * p + 2 * g.val + c.val) p A B
      (R15ThinPairs.select (R22Resident8Projection.projectRow
        (R22IndexedResident8.within p n baseA (b.val * n * R22Pair8.groups p + g.val)
          A (R22Pair8.packB batch n p B) bound) r) c.val) =
      NativeFinal.dot n
        (R22Resident8Projection.rowBase baseA (baseA + n) (baseA + 2 * n) (baseA + 3 * n) r)
        (b.val * n * p + 2 * g.val + c.val) p A B := by
  exact Packed10.finish_eq_dot _ _ _ _ _ _ _ (within_lane batch n p baseA A B b g bound r c hc)

end Submission.R23IndexedProducer
