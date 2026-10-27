/- R20 post-freeze mathematical interface; NOT_RUN, not a performance implementation.
   Concrete safe Array.modify/constructor-reuse implementation is owned by representation worker.
   Append after the unchanged B2 source. No new public arithmetic or axioms. -/
namespace Submission.R20WideRowRefinement
open FloatLib.Floats Competition

def storageLoop {S : Type} (n : Nat) (step : Nat → S → S) (k : Nat) (s : S) : S :=
  if hk : k<n then storageLoop n step (k+1) (step k s) else s
termination_by n-k

/-- The implementation obligation is only a complete row-step projection.
    It must be proved for the actual state representation before this can certify a kernel. -/
theorem storageLoop_lane {S : Type} (n columns p baseA baseB : Nat)
    (A B : Array Binary32) (view : S → Fin columns → Float32) (step : Nat → S → S)
    (hstep : ∀ (k : Nat), k<n → ∀ (s : S) (j : Fin columns),
      view (step k s) j = view s j +
        ExecFloat.Binary.toFloat32 (A.getD (baseA+k) posZero) *
        ExecFloat.Binary.toFloat32 (B.getD (baseB+j.val+k*p) posZero))
    (k : Nat) (s : S) (j : Fin columns) :
    view (storageLoop n step k s) j =
      NativeFinal.dotLoop n baseA (baseB+j.val) p A B k (view s j) := by
  have eN := @storageLoop.eq_def S n step k s
  have eD := @NativeFinal.dotLoop.eq_def n baseA (baseB+j.val) p A B k (view s j)
  by_cases hk : k<n
  · rw [eN, eD]
    simp only [hk, dite_true]
    have ih := storageLoop_lane n columns p baseA baseB A B view step hstep
      (k+1) (step k s) j
    simpa only [hstep k hk] using ih
  · rw [eN, eD]
    simp only [hk, dite_false]
termination_by n-k
decreasing_by all_goals omega

theorem finish_lane {S : Type} (n columns p baseA baseB : Nat)
    (A B : Array Binary32) (view : S → Fin columns → Float32) (step : Nat → S → S)
    (hstep : ∀ (k : Nat), k<n → ∀ (s : S) (j : Fin columns),
      view (step k s) j = view s j +
        ExecFloat.Binary.toFloat32 (A.getD (baseA+k) posZero) *
        ExecFloat.Binary.toFloat32 (B.getD (baseB+j.val+k*p) posZero))
    (initial : S) (hzero : ∀ j : Fin columns, view initial j = Packed10.zero32)
    (j : Fin columns) :
    Packed10.finish n baseA (baseB+j.val) p A B (view (storageLoop n step 0 initial) j) =
      NativeFinal.dot n baseA (baseB+j.val) p A B := by
  apply Packed10.finish_eq_dot
  simpa only [hzero] using storageLoop_lane n columns p baseA baseB A B view step hstep
    0 initial j

end Submission.R20WideRowRefinement
