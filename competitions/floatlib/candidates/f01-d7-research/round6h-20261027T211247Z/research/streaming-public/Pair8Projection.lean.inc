/- Unified valid-lane step/loop interface for exact Pair8/cd0e3399. NOT_RUN.
   CacheAgreement is a proof premise, to be instantiated from Pair8CacheProof. -/
namespace Submission.R22Pair8
open FloatLib.Floats Competition

def CacheAgreement (n p baseB baseC : Nat) (B : Array Binary32) (cache : Array BP) : Prop :=
  ∀ k, k < n → ∀ j : Fin p,
    (if j.val % 2 = 0 then (cache.getD (baseC + k * groups p + j.val / 2) zeroPair).s0
     else (cache.getD (baseC + k * groups p + j.val / 2) zeroPair).s1) =
      ExecFloat.Binary.toFloat32 (B.getD (baseB + j.val + k * p) posZero)

def view {p : Nat} (row : Fin 4) (s : State p) (j : Fin p) : Float32 :=
  if row.val = 0 then view0 s j else if row.val = 1 then view1 s j
  else if row.val = 2 then view2 s j else view3 s j

theorem advance_get (p n baseA baseC : Nat) (A : Array Binary32) (cache : Array BP)
    (k : Nat) (s : State p) (g : Fin (groups p)) :
    (advance p n baseA baseC A cache k s).get g =
      update (ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero))
        (ExecFloat.Binary.toFloat32 (A.getD (baseA + n + k) posZero))
        (ExecFloat.Binary.toFloat32 (A.getD (baseA + 2 * n + k) posZero))
        (ExecFloat.Binary.toFloat32 (A.getD (baseA + 3 * n + k) posZero))
        (cache.getD (baseC + k * groups p + g.val) zeroPair).s0
        (cache.getD (baseC + k * groups p + g.val) zeroPair).s1 (s.get g) := by
  change (s.toArray.mapIdx (fun i old =>
    let b := cache.getD (baseC + k * groups p + i) zeroPair
    update (ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero))
      (ExecFloat.Binary.toFloat32 (A.getD (baseA + n + k) posZero))
      (ExecFloat.Binary.toFloat32 (A.getD (baseA + 2 * n + k) posZero))
      (ExecFloat.Binary.toFloat32 (A.getD (baseA + 3 * n + k) posZero)) b.s0 b.s1 old))[g.val] = _
  rw [Array.getElem_mapIdx]
  rfl

theorem advance_projection (p n baseA baseB baseC : Nat) (A B : Array Binary32)
    (cache : Array BP) (hcache : CacheAgreement n p baseB baseC B cache)
    (row : Fin 4) (k : Nat) (hk : k < n) (s : State p) (j : Fin p) :
    view row (advance p n baseA baseC A cache k s) j = view row s j +
      ExecFloat.Binary.toFloat32 (A.getD (baseA + row.val * n + k) posZero) *
      ExecFloat.Binary.toFloat32 (B.getD (baseB + j.val + k * p) posZero) := by
  have hb := hcache k hk j
  rcases row with ⟨r, hr⟩
  have hcases : r = 0 ∨ r = 1 ∨ r = 2 ∨ r = 3 := by omega
  rcases hcases with rfl | rfl | rfl | rfl
  all_goals simp [view]
  all_goals
    dsimp only [view0, view1, view2, view3, cell]
    rw [advance_get]
    by_cases he : j.val % 2 = 0
    · simp only [he, ite_true] at hb
      simp [he, update, hb]
    · simp only [he, ite_false] at hb
      simp [he, update, hb]

theorem initial_projection (p : Nat) (row : Fin 4) (j : Fin p) :
    view row (initial p) j = Packed10.zero32 := by
  have hc : cell (initial p) j = (⟨Packed10.zero32, Packed10.zero32,
      Packed10.zero32, Packed10.zero32, Packed10.zero32, Packed10.zero32,
      Packed10.zero32, Packed10.zero32⟩ : Cell) := by
    change (Array.replicate (groups p) (⟨Packed10.zero32, Packed10.zero32,
      Packed10.zero32, Packed10.zero32, Packed10.zero32, Packed10.zero32,
      Packed10.zero32, Packed10.zero32⟩ : Cell))[j.val / 2] = _
    simp only [Array.getElem_replicate]
  simp [view, view0, view1, view2, view3, hc]

theorem loop_eq_storage (p n baseA baseC : Nat) (A : Array Binary32) (cache : Array BP)
    (k : Nat) (s : State p) :
    loop p n baseA baseC A cache k s =
      R20WideRowRefinement.storageLoop n (advance p n baseA baseC A cache) k s := by
  have he := @loop.eq_def p n baseA baseC A cache k s
  have hg := @R20WideRowRefinement.storageLoop.eq_def (State p) n
    (advance p n baseA baseC A cache) k s
  by_cases hk : k < n
  · rw [he, hg]
    simp only [dif_pos hk]
    exact loop_eq_storage p n baseA baseC A cache (k + 1) _
  · rw [he, hg]
    simp only [dif_neg hk]
termination_by n - k
decreasing_by all_goals omega

theorem loop_projection (p n baseA baseB baseC : Nat) (A B : Array Binary32)
    (cache : Array BP) (hcache : CacheAgreement n p baseB baseC B cache)
    (row : Fin 4) (k : Nat) (s : State p) (j : Fin p) :
    view row (loop p n baseA baseC A cache k s) j =
      NativeFinal.dotLoop n (baseA + row.val * n) (baseB + j.val) p A B k (view row s j) := by
  rw [loop_eq_storage]
  exact R20WideRowRefinement.storageLoop_lane n p p (baseA + row.val * n) baseB A B
    (view row) (advance p n baseA baseC A cache)
    (fun k hk s j => advance_projection p n baseA baseB baseC A B cache hcache row k hk s j)
    k s j

theorem finish_projection (p n baseA baseB baseC : Nat) (A B : Array Binary32)
    (cache : Array BP) (hcache : CacheAgreement n p baseB baseC B cache)
    (row : Fin 4) (j : Fin p) :
    Packed10.finish n (baseA + row.val * n) (baseB + j.val) p A B
      (view row (loop p n baseA baseC A cache 0 (initial p)) j) =
      NativeFinal.dot n (baseA + row.val * n) (baseB + j.val) p A B := by
  apply Packed10.finish_eq_dot
  simpa only [initial_projection] using
    loop_projection p n baseA baseB baseC A B cache hcache row 0 (initial p) j

end Submission.R22Pair8
