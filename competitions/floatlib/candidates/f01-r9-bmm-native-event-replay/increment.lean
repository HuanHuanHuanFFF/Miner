/- R9 BMM-only native replay. Existing exact W05 quiet-event proof removes
   the old draft's runtime quiet test and unreachable exact-suffix branch. -/

theorem r9_nativeStep_eq (acc : Float32) (x y : Binary32)
    (hn : (acc + ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y).isNaN = false) :
    ExecFloat.Binary.ofFloat32
        (acc + ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y) =
      Submission.add (ExecFloat.Binary.ofFloat32 acc) (Submission.mul x y) := by
  have ha := NotNaNProbe.add_inputs acc
    (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y) hn
  have hm := NotNaNProbe.mul_inputs
    (ExecFloat.Binary.toFloat32 x) (ExecFloat.Binary.toFloat32 y) ha.2
  rw [R7Native.ofFloat32Add _ _ ha.1 ha.2,
    R7Native.ofFloat32Mul _ _ hm.1 hm.2,
    NotNaNProbe.roundtrip x hm.1, NotNaNProbe.roundtrip y hm.2,
    Submission.add_eq, Submission.mul_eq]

theorem r9_repairQuiet (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (k : Fin n) (acc : Float32)
    (hevent : (acc + ExecFloat.Binary.toFloat32 (Araw.getD (baseA + k.val) posZero) *
      ExecFloat.Binary.toFloat32 (Braw.getD (baseB + k.val * p) posZero)).isNaN = true) :
    R7W01.execQuietGuard
      (replayStep n baseA baseB p Araw Braw (ExecFloat.Binary.ofFloat32 acc) k) = true := by
  have h := R7W05.repairDotStep_isQNaN acc
    (Araw.getD (baseA + k.val) posZero) (Braw.getD (baseB + k.val * p) posZero) hevent
  simpa only [R7W01.execQuietGuard, R7W01.quietGuard,
    FloatLib.Floats.Formats.BinaryInterchange.Model.isQNaN_eq_nan_and_not_signaling,
    replayStep, R7W05.repairDotStep, Submission.add_eq, Submission.mul_eq] using h

/-- Only a rejected native endpoint enters this replay. Keep the accumulator
native until the first NaN event, then return one exact quiet repaired step. -/
def r9_nativeReplayLoop (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (k : Nat) (acc : Float32) : Binary32 :=
  if hk : k < n then
    let x := Araw.getD (baseA + k) posZero
    let y := Braw.getD (baseB + k * p) posZero
    let next := acc + ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y
    if hn : next.isNaN = false then
      r9_nativeReplayLoop n baseA baseB p Araw Braw (k + 1) next
    else replayStep n baseA baseB p Araw Braw (ExecFloat.Binary.ofFloat32 acc) ⟨k, hk⟩
  else ExecFloat.Binary.ofFloat32 acc
termination_by n - k

theorem r9_nativeReplayLoop_eq (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (k : Nat) (acc : Float32) :
    r9_nativeReplayLoop n baseA baseB p Araw Braw k acc =
      Fin.foldl.loop n (replayStep n baseA baseB p Araw Braw)
        (ExecFloat.Binary.ofFloat32 acc) k := by
  rw [r9_nativeReplayLoop]
  split
  · rename_i hk
    dsimp only
    split
    · rename_i hn
      rw [Fin.foldl.loop, dif_pos hk]
      have ih := r9_nativeReplayLoop_eq n baseA baseB p Araw Braw (k + 1)
        (acc + ExecFloat.Binary.toFloat32 (Araw.getD (baseA + k) posZero) *
          ExecFloat.Binary.toFloat32 (Braw.getD (baseB + k * p) posZero))
      have hs := r9_nativeStep_eq acc (Araw.getD (baseA + k) posZero)
        (Braw.getD (baseB + k * p) posZero) hn
      exact ih.trans (congrArg
        (fun q : Binary32 => Fin.foldl.loop n (replayStep n baseA baseB p Araw Braw) q (k + 1)) hs)
    · rename_i hn
      have hevent : (acc + ExecFloat.Binary.toFloat32 (Araw.getD (baseA + k) posZero) *
          ExecFloat.Binary.toFloat32 (Braw.getD (baseB + k * p) posZero)).isNaN = true := by
        by_contra he
        exact hn (Bool.eq_false_of_not_eq_true he)
      have hq := r9_repairQuiet n baseA baseB p Araw Braw ⟨k, hk⟩ acc hevent
      rw [Fin.foldl.loop, dif_pos hk]
      exact (replayFold_absorb n baseA baseB p Araw Braw (k + 1) _ hq).symm
  · rename_i hk
    rw [Fin.foldl.loop, dif_neg hk]
termination_by n - k

def r9_nativeReplay (n baseA baseB p : Nat) (Araw Braw : Array Binary32) : Binary32 :=
  r9_nativeReplayLoop n baseA baseB p Araw Braw 0 (Float32.ofBits 0)

theorem r9_nativeReplay_eq (n baseA baseB p : Nat) (Araw Braw : Array Binary32) :
    r9_nativeReplay n baseA baseB p Araw Braw =
      Fin.foldl n (replayStep n baseA baseB p Araw Braw) posZero := by
  exact r9_nativeReplayLoop_eq n baseA baseB p Araw Braw 0 (Float32.ofBits 0)

