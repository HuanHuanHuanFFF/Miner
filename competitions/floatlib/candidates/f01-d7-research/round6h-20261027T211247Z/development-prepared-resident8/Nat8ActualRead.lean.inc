/- Requires Nat8PointwiseRead65101d8d and Nat8CacheViewHRead41e6dbec,
   including their exact external Pair8CacheProof dependency. NOT_RUN. -/
namespace Submission.R22Resident8Projection
open FloatLib.Floats Competition

theorem readRow_pack_eq_dot (batch n p b baseA : Nat) (A B : Array Binary32)
    (hb : b < batch) (r : Fin 4) (j : Fin p) :
    readRow (R22Resident8.tiles p n baseA (b * n * p)
      (b * n * R22Pair8.groups p) A B (R22Pair8.packB batch n p B)) r j =
    NativeFinal.dot n (baseA + r.val * n) (b * n * p + j.val) p A B := by
  apply readRow_eq_dot
  have parts := column_parts p j
  let g : Fin (R22Pair8.groups p) := ⟨j.val / 2, parts.1⟩
  let c : Fin 2 := ⟨j.val % 2, parts.2.1⟩
  have hj : 2 * g.val + c.val = j.val := parts.2.2.1
  have hcol : 2 * g.val + c.val < p := by have h := j.isLt; omega
  have hs := R22CacheSelected.cacheView_hread batch n p b B hb g c hcol
  intro i
  have haddress : b * n * p + 2 * g.val + c.val + i.val * p =
      b * n * p + j.val + i.val * p := by omega
  simpa only [haddress] using hs i

end Submission.R22Resident8Projection
