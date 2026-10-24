-- CONDITIONAL proof-only replacement; Lean NOT_RUN.
-- Replace the original natLoop_lane declaration within Submission.R11CrossRows.
-- Only needed if the exact compiler rejects its default decrease tactic.
theorem natLoop_lane (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (k : Nat) (s : F8) (l : Fin 8) :
    lane (natLoop n (pack n p a0 a1 a2 a3 b0 b1 b2 b3 A B) k s) l =
      NativeFinal.dotLoop n (select4 a0 a1 a2 a3 (l.val%4))
        (select4 b0 b1 b2 b3 (l.val%4)+l.val/4) p A B k (lane s l) := by
  rw [natLoop]
  split
  · rename_i hk
    rw [NativeFinal.dotLoop, dif_pos hk]
    dsimp only
    have ih := natLoop_lane n p a0 a1 a2 a3 b0 b1 b2 b3 A B (k+1)
      (update s ((pack n p a0 a1 a2 a3 b0 b1 b2 b3 A B).get ⟨k,hk⟩)) l
    rw [lane_update, pack_a, pack_b] at ih
    exact ih
  · rename_i hk
    rw [NativeFinal.dotLoop, dif_neg hk]
termination_by n-k
decreasing_by omega
