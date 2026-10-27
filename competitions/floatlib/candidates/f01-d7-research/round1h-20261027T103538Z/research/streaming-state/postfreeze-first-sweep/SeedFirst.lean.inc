/- Isolated R21 post-freeze experiment. Append after exact streaming-state v1.
   No complete candidate or CI request is produced from this fragment. -/
namespace Submission.R21StreamingSeed
open FloatLib.Floats Competition
open R21StreamingPair

def seedFirst (p baseA0 baseA1 baseB : Nat) (A B : Array Binary32) : State p :=
  let a0 := ExecFloat.Binary.toFloat32 (A.getD baseA0 posZero)
  let a1 := ExecFloat.Binary.toFloat32 (A.getD baseA1 posZero)
  Vector.ofFn fun j =>
    let b := ExecFloat.Binary.toFloat32 (B.getD (baseB + j.val) posZero)
    (⟨Packed10.zero32 + a0 * b, Packed10.zero32 + a1 * b⟩ : Cell)

theorem seedFirst_get (p baseA0 baseA1 baseB : Nat) (A B : Array Binary32) (j : Fin p) :
    (seedFirst p baseA0 baseA1 baseB A B).get j =
      updateCell (ExecFloat.Binary.toFloat32 (A.getD baseA0 posZero))
        (ExecFloat.Binary.toFloat32 (A.getD baseA1 posZero))
        (ExecFloat.Binary.toFloat32 (B.getD (baseB + j.val) posZero))
        (⟨Packed10.zero32, Packed10.zero32⟩ : Cell) := by
  simp only [seedFirst, Packed10.vector_get_ofFn, updateCell]

theorem seedFirst_eq_advance (p baseA0 baseA1 baseB : Nat) (A B : Array Binary32) :
    seedFirst p baseA0 baseA1 baseB A B =
      advance p baseA0 baseA1 baseB A B 0 (initial p) := by
  apply Vector.ext
  intro i hi
  change (seedFirst p baseA0 baseA1 baseB A B).get ⟨i, hi⟩ =
    (advance p baseA0 baseA1 baseB A B 0 (initial p)).get ⟨i, hi⟩
  rw [seedFirst_get, advance_get]
  have hz : (initial p).get ⟨i, hi⟩ = (⟨Packed10.zero32, Packed10.zero32⟩ : Cell) := by
    change (Array.replicate p (⟨Packed10.zero32, Packed10.zero32⟩ : Cell))[i] = _
    simp only [Array.getElem_replicate]
  rw [hz]
  simp only [Nat.add_zero, Nat.zero_mul]

theorem loop_after_seed (p n baseA0 baseA1 baseB : Nat) (A B : Array Binary32)
    (hn : 0 < n) :
    loop p n baseA0 baseA1 baseB A B 1 (seedFirst p baseA0 baseA1 baseB A B) =
      loop p n baseA0 baseA1 baseB A B 0 (initial p) := by
  rw [seedFirst_eq_advance]
  have h := @loop.eq_def p n baseA0 baseA1 baseB A B 0 (initial p)
  simpa only [dif_pos hn, Nat.zero_add] using h.symm

def seededRows (p n baseA0 baseA1 baseB : Nat) (A B : Array Binary32)
    (out : Array Binary32) : Array Binary32 :=
  if p = 0 then out else
    if n = 0 then controlRows p n baseA0 baseA1 baseB A B out else
      let s := loop p n baseA0 baseA1 baseB A B 1 (seedFirst p baseA0 baseA1 baseB A B)
      let out := RowStream.emit p (fun j =>
        Packed10.finish n baseA0 (baseB + j.val) p A B (view0 s j)) out
      RowStream.emit p (fun j =>
        Packed10.finish n baseA1 (baseB + j.val) p A B (view1 s j)) out

theorem seededRows_eq_streamedRows (p n baseA0 baseA1 baseB : Nat) (A B : Array Binary32)
    (out : Array Binary32) :
    seededRows p n baseA0 baseA1 baseB A B out = streamedRows p n baseA0 baseA1 baseB A B out := by
  by_cases hp : p = 0
  · subst p
    rfl
  · by_cases hn : n = 0
    · subst n
      simp only [seededRows, hp, if_false, if_true]
      exact (streamedRows_eq_control p 0 baseA0 baseA1 baseB A B out).symm
    · have hpos : 0 < n := Nat.pos_of_ne_zero hn
      simp only [seededRows, streamedRows, hp, hn, if_false]
      rw [loop_after_seed p n baseA0 baseA1 baseB A B hpos]

end Submission.R21StreamingSeed
