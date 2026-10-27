/- Intended inside Submission.R7NaNReplay after replayFold_absorb.
   Requires the concrete R7Native/NotNaNProbe declarations before this namespace.
   Prepared next-stage mechanism; not yet integrated or compiled. -/

theorem nativeStep_eq (acc : Float32) (x y : Binary32)
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

/-- Replay the prefix in native arithmetic; repair one exact step at a NaN event.
The non-quiet repair branch keeps a complete exact suffix, without assuming it unreachable. -/
def nativeReplayLoop (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (k : Nat) (acc : Float32) : Binary32 :=
  if hk : k < n then
    let x := Araw.getD (baseA + k) posZero
    let y := Braw.getD (baseB + k * p) posZero
    let next := acc + ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y
    if hn : next.isNaN = false then
      nativeReplayLoop n baseA baseB p Araw Braw (k + 1) next
    else
      let repaired := replayStep n baseA baseB p Araw Braw
        (ExecFloat.Binary.ofFloat32 acc) ⟨k, hk⟩
      if R7W01.execQuietGuard repaired then repaired
      else Fin.foldl.loop n (replayStep n baseA baseB p Araw Braw) repaired (k + 1)
  else ExecFloat.Binary.ofFloat32 acc
termination_by n - k

theorem nativeReplayLoop_eq (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (k : Nat) (acc : Float32) :
    nativeReplayLoop n baseA baseB p Araw Braw k acc =
      Fin.foldl.loop n (replayStep n baseA baseB p Araw Braw)
        (ExecFloat.Binary.ofFloat32 acc) k := by
  rw [nativeReplayLoop]
  split
  · rename_i hk
    dsimp only
    split
    · rename_i hn
      rw [Fin.foldl.loop, dif_pos hk]
      have ih := nativeReplayLoop_eq n baseA baseB p Araw Braw (k + 1)
        (acc + ExecFloat.Binary.toFloat32 (Araw.getD (baseA + k) posZero) *
          ExecFloat.Binary.toFloat32 (Braw.getD (baseB + k * p) posZero))
      rw [nativeStep_eq _ _ _ hn] at ih
      exact ih
    · dsimp only
      split
      · rename_i hq
        rw [Fin.foldl.loop, dif_pos hk]
        exact (replayFold_absorb n baseA baseB p Araw Braw (k + 1) _ hq).symm
      · rw [Fin.foldl.loop, dif_pos hk]
  · rename_i hk
    rw [Fin.foldl.loop, dif_neg hk]
termination_by n - k

def nativeReplay (n baseA baseB p : Nat) (Araw Braw : Array Binary32) : Binary32 :=
  nativeReplayLoop n baseA baseB p Araw Braw 0 (Float32.ofBits 0)

theorem nativeReplay_eq (n baseA baseB p : Nat) (Araw Braw : Array Binary32) :
    nativeReplay n baseA baseB p Araw Braw =
      Fin.foldl n (replayStep n baseA baseB p Araw Braw) posZero := by
  exact nativeReplayLoop_eq n baseA baseB p Araw Braw 0 (Float32.ofBits 0)

