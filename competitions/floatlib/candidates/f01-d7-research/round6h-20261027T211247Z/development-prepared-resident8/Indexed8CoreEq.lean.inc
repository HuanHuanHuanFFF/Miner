/- Requires Indexed8OutputEq3adbd313 and Indexed8LoopEq-v2ccee65d4.
   NOT_RUN. Exact existing machine-fit fallback and shape/underflow guards. -/
namespace Submission.R22IndexedResident8
open FloatLib.Floats Competition

theorem mk_eq_of_arrays {α : Type} {n : Nat} {left right : Array α}
    (hl : left.size = n) (hr : right.size = n) (h : left = right) :
    (Vector.mk left hl : Vector α n) = Vector.mk right hr := by
  cases h
  rfl

theorem core_eq (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : 1 < n) (hp : 2 ≤ p) :
    core batch m n p A B hn hp = R22Resident8.core batch m n p A B := by
  unfold core R22Resident8.core
  split
  · apply mk_eq_of_arrays
    exact output_eq _ _ _ _ _ _ _ _
  · rfl

theorem guarded_eq (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    guarded batch m n p A B = R22Resident8.guarded batch m n p A B := by
  unfold guarded R22Resident8.guarded
  by_cases hz : (A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small) = true
  · simp only [if_pos hz]
  · by_cases he : 1 < n ∧ 4 ≤ m ∧ 2 ≤ p
    · simp only [if_neg hz, dif_pos he, if_pos he, core_eq]
    · simp only [if_neg hz, dif_neg he, if_neg he]

end Submission.R22IndexedResident8
