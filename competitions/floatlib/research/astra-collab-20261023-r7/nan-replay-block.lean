/-- The original exact software step, retaining the tuned scalar entry points. -/
@[inline] def replayStep (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (acc : Binary32) (i : Fin n) : Binary32 :=
  Submission.add acc (Submission.mul (Araw.getD (baseA + i.val) posZero)
    (Braw.getD (baseB + i.val * p) posZero))

theorem replayStep_absorb (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (acc : Binary32) (i : Fin n) (hq : R7W01.execQuietGuard acc = true) :
    replayStep n baseA baseB p Araw Braw acc i = acc := by
  unfold replayStep
  rw [Submission.add_eq, Submission.mul_eq]
  exact R7W01.exec_add_mul_absorb _ _ _
    (R7W01.quietGuard_nan _ hq) (R7W01.quietGuard_not_signaling _ hq)

theorem replayFold_absorb (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (k : Nat) (acc : Binary32) (hq : R7W01.execQuietGuard acc = true) :
    Fin.foldl.loop n (replayStep n baseA baseB p Araw Braw) acc k = acc := by
  rw [Fin.foldl.loop]
  split
  · rename_i hk
    rw [replayStep_absorb n baseA baseB p Araw Braw acc ⟨k, hk⟩ hq]
    exact replayFold_absorb n baseA baseB p Araw Braw (k + 1) acc hq
  · rfl
termination_by n - k

/-- No index list is allocated, and a quiet result stops before further array reads. -/
def replayLoop (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (k : Nat) (acc : Binary32) : Binary32 :=
  if hk : k < n then
    if R7W01.execQuietGuard acc then acc
    else replayLoop n baseA baseB p Araw Braw (k + 1)
      (replayStep n baseA baseB p Araw Braw acc ⟨k, hk⟩)
  else acc
termination_by n - k

theorem replayLoop_eq (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (k : Nat) (acc : Binary32) :
    replayLoop n baseA baseB p Araw Braw k acc =
      Fin.foldl.loop n (replayStep n baseA baseB p Araw Braw) acc k := by
  rw [replayLoop]
  split
  · rename_i hk
    split
    · rename_i hq
      exact (replayFold_absorb n baseA baseB p Araw Braw k acc hq).symm
    · rw [Fin.foldl.loop, dif_pos hk]
      exact replayLoop_eq n baseA baseB p Araw Braw (k + 1) _
  · rename_i hk
    rw [Fin.foldl.loop, dif_neg hk]
termination_by n - k

def replayEarly (n baseA baseB p : Nat) (Araw Braw : Array Binary32) : Binary32 :=
  replayLoop n baseA baseB p Araw Braw 0 posZero

theorem replayEarly_eq (n baseA baseB p : Nat) (Araw Braw : Array Binary32) :
    replayEarly n baseA baseB p Araw Braw =
      Fin.foldl n (replayStep n baseA baseB p Araw Braw) posZero := by
  exact replayLoop_eq n baseA baseB p Araw Braw 0 posZero

/-- Apply the extra early check only to the already-rejected NaN endpoint. -/
def replay (n baseA baseB p : Nat) (Araw Braw : Array Binary32) (result : Float32) : Binary32 :=
  if result.isNaN then replayEarly n baseA baseB p Araw Braw
  else Fin.foldl n (replayStep n baseA baseB p Araw Braw) posZero

theorem replay_eq (n baseA baseB p : Nat) (Araw Braw : Array Binary32) (result : Float32) :
    replay n baseA baseB p Araw Braw result =
      Fin.foldl n (fun acc i => Submission.add acc
        (Submission.mul (Araw.getD (baseA + i.val) posZero)
          (Braw.getD (baseB + i.val * p) posZero))) posZero := by
  unfold replay
  split
  · exact replayEarly_eq n baseA baseB p Araw Braw
  · rfl

