namespace R7SumRepair

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

@[inline] def step {n : Nat} (x : Vector Binary32 n)
    (acc : Binary32) (i : Fin n) : Binary32 := Submission.add acc (x.get i)

/-- A quiet sum must still inspect later signaling inputs, preserving their full words. -/
def suffixLoop {n : Nat} (x : Vector Binary32 n) (k : Nat) (acc : Binary32) : Binary32 :=
  if hk : k < n then
    suffixLoop x (k + 1) (R7W02.step acc (x.get ⟨k, hk⟩))
  else acc
termination_by n - k

theorem suffixLoop_eq {n : Nat} (x : Vector Binary32 n) (k : Nat) (acc : Binary32)
    (hq : Model.isQNaN (ExecFloat.Binary.toModel acc) = true) :
    suffixLoop x k acc = Fin.foldl.loop n (step x) acc k := by
  rw [suffixLoop]
  split
  · rename_i hk
    rw [Fin.foldl.loop, dif_pos hk]
    have ih := suffixLoop_eq x (k + 1) (R7W02.step acc (x.get ⟨k, hk⟩))
      (R7W02.step_isQNaN acc (x.get ⟨k, hk⟩) hq)
    rw [R7W02.step_eq_add acc (x.get ⟨k, hk⟩) hq, ← Submission.add_eq] at ih
    exact ih
  · rename_i hk
    rw [Fin.foldl.loop, dif_neg hk]
termination_by n - k

theorem nativeStep_eq (acc : Float32) (x : Binary32)
    (hn : (acc + ExecFloat.Binary.toFloat32 x).isNaN = false) :
    ExecFloat.Binary.ofFloat32 (acc + ExecFloat.Binary.toFloat32 x) =
      Submission.add (ExecFloat.Binary.ofFloat32 acc) x := by
  have ha := NotNaNProbe.add_inputs acc (ExecFloat.Binary.toFloat32 x) hn
  rw [R7Native.ofFloat32Add _ _ ha.1 ha.2,
    NotNaNProbe.roundtrip x ha.2, Submission.add_eq]

/-- Called only after an existing full native sum rejected a NaN endpoint.
Keep this second prefix native, repair one raw step, then use the proved quiet suffix scan. -/
def nativeLoop {n : Nat} (x : Vector Binary32 n) (k : Nat) (acc : Float32) : Binary32 :=
  if hk : k < n then
    let value := x.get ⟨k, hk⟩
    let next := acc + ExecFloat.Binary.toFloat32 value
    if hn : next.isNaN = false then nativeLoop x (k + 1) next
    else
      let repaired := Submission.add (ExecFloat.Binary.ofFloat32 acc) value
      if R7W01.execQuietGuard repaired then suffixLoop x (k + 1) repaired
      else Fin.foldl.loop n (step x) repaired (k + 1)
  else ExecFloat.Binary.ofFloat32 acc
termination_by n - k

theorem nativeLoop_eq {n : Nat} (x : Vector Binary32 n) (k : Nat) (acc : Float32) :
    nativeLoop x k acc =
      Fin.foldl.loop n (step x) (ExecFloat.Binary.ofFloat32 acc) k := by
  rw [nativeLoop]
  split
  · rename_i hk
    dsimp only
    split
    · rename_i hn
      rw [Fin.foldl.loop, dif_pos hk]
      have ih := nativeLoop_eq x (k + 1)
        (acc + ExecFloat.Binary.toFloat32 (x.get ⟨k, hk⟩))
      rw [nativeStep_eq _ _ hn] at ih
      exact ih
    · dsimp only
      split
      · rename_i hq
        rw [Fin.foldl.loop, dif_pos hk]
        have hquiet : Model.isQNaN (ExecFloat.Binary.toModel
            (Submission.add (ExecFloat.Binary.ofFloat32 acc) (x.get ⟨k, hk⟩))) = true := by
          simp [Model.isQNaN_eq_nan_and_not_signaling,
            R7W01.quietGuard_nan _ hq, R7W01.quietGuard_not_signaling _ hq]
        exact suffixLoop_eq x (k + 1) _ hquiet
      · rw [Fin.foldl.loop, dif_pos hk]
  · rename_i hk
    rw [Fin.foldl.loop, dif_neg hk]
termination_by n - k

def run {n : Nat} (x : Vector Binary32 n) : Binary32 :=
  nativeLoop x 0 (Float32.ofBits 0)

theorem run_spec : ∀ (n : Nat) (x : Vector Binary32 n), run x = sumSpec x.get := by
  intro n x
  have h := nativeLoop_eq x 0 (Float32.ofBits 0)
  change run x = Fin.foldl n (step x) posZero at h
  have hstep : step x = fun (acc : Binary32) (i : Fin n) =>
      ExecFloat.add acc (x.get i) := by
    funext acc i
    exact congrArg (fun f : Binary32 → Binary32 → Binary32 => f acc (x.get i))
      Submission.add_eq
  rw [hstep, Fin.foldl_eq_finRange_foldl] at h
  exact h

end R7SumRepair
