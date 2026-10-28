/- Erased-proof read interface for Pair8/cd0e. NOT_RUN; no runtime edits. -/
namespace Submission.R22Pair8CheckedRead
open FloatLib.Floats Competition

theorem cache_index_lt {base n G size k j : Nat}
    (hend : base+n*G ≤ size) (hk : k<n) (hj : j<G) : base+k*G+j < size := by
  have h := Nat.mul_le_mul_right G (Nat.succ_le_of_lt hk)
  simp only [Nat.succ_mul] at h
  omega

theorem read_eq_getD {α : Type} (cache : Array α) (z : α) (i : Nat)
    (hi : i<cache.size) : cache[i] = cache.getD i z := by
  simp [Array.getD,hi]

theorem advance_map_eq {α β : Type} (cache : Array α) (z : α) (s : Array β)
    (base n G k : Nat) (hs : s.size=G) (hend : base+n*G ≤ cache.size) (hk : k<n)
    (step : α → β → β) :
    s.mapFinIdx (fun j cell hj =>
      step (cache[base+k*G+j]'(cache_index_lt hend hk (by omega))) cell) =
    s.mapIdx (fun j cell => step (cache.getD (base+k*G+j) z) cell) := by
  apply Array.mapFinIdx_eq_mapIdx
  intro j hj
  have hi : base+k*G+j < cache.size := cache_index_lt hend hk (by omega)
  simp [Array.getD,hi]

theorem pack_span (batch n p : Nat) (B : Array Binary32) (b : Fin batch) :
    b.val*n*R22Pair8.groups p+n*R22Pair8.groups p ≤ (R22Pair8.packB batch n p B).size := by
  rw [R22Pair8.packB_size]
  have h := Nat.mul_le_mul_right (n*R22Pair8.groups p) (Nat.succ_le_of_lt b.isLt)
  simpa only [Nat.succ_mul,Nat.mul_assoc] using h

end Submission.R22Pair8CheckedRead
