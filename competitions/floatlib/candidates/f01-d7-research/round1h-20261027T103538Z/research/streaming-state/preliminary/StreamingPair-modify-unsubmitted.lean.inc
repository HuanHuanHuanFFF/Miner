/- R21 complete two-row state path. Public B2 remains unchanged. -/
namespace Submission.R21StreamingPair
open FloatLib.Floats Competition

abbrev Cell := R15ThinPairs.F2
abbrev State (p : Nat) := Vector Cell p

@[inline] def updateCell (a0 a1 b : Float32) (s : Cell) : Cell :=
  { s with s0 := s.s0 + a0 * b, s1 := s.s1 + a1 * b }

@[inline] def updateSlot {p : Nat} (s : State p) (j : Fin p)
    (a0 a1 b : Float32) : State p :=
  ⟨s.toArray.modify j.val (updateCell a0 a1 b), by
    simpa only [Array.size_modify] using s.size_toArray⟩

theorem updateSlot_get {p : Nat} (s : State p) (i j : Fin p) (a0 a1 b : Float32) :
    (updateSlot s i a0 a1 b).get j =
      if i.val = j.val then updateCell a0 a1 b (s.get j) else s.get j := by
  change (s.toArray.modify i.val (updateCell a0 a1 b))[j.val] = _
  rw [Array.getElem_modify]
  rfl

def sweep (p rowB : Nat) (B : Array Binary32) (a0 a1 : Float32)
    (i : Nat) (s : State p) : State p :=
  if hi : i < p then
    let b := ExecFloat.Binary.toFloat32 (B.getD (rowB + i) posZero)
    sweep p rowB B a0 a1 (i + 1) (updateSlot s ⟨i, hi⟩ a0 a1 b)
  else s
termination_by p - i

theorem sweep_get (p rowB : Nat) (B : Array Binary32) (a0 a1 : Float32)
    (i : Nat) (s : State p) (j : Fin p) :
    (sweep p rowB B a0 a1 i s).get j =
      if i ≤ j.val then
        updateCell a0 a1 (ExecFloat.Binary.toFloat32 (B.getD (rowB + j.val) posZero)) (s.get j)
      else s.get j := by
  have he := @sweep.eq_def p rowB B a0 a1 i s
  by_cases hi : i < p
  · rw [he]
    simp only [dif_pos hi]
    rw [sweep_get p rowB B a0 a1 (i + 1) (updateSlot s ⟨i, hi⟩ a0 a1
      (ExecFloat.Binary.toFloat32 (B.getD (rowB + i) posZero))) j]
    simp only [updateSlot_get]
    by_cases hij : i = j.val
    · have hle : i ≤ j.val := by omega
      have hnot : ¬ i + 1 ≤ j.val := by omega
      simp only [hij, hle, hnot, if_true, if_false]
    · by_cases hle : i ≤ j.val
      · have hnext : i + 1 ≤ j.val := by omega
        simp only [hij, hle, hnext, if_true, if_false]
      · have hnext : ¬ i + 1 ≤ j.val := by omega
        simp only [hij, hle, hnext, if_false]
  · rw [he]
    simp only [dif_neg hi]
    have hnot : ¬ i ≤ j.val := by have hj := j.isLt; omega
    simp only [hnot, if_false]
termination_by p - i
decreasing_by all_goals omega

@[inline] def advance (p baseA0 baseA1 baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) : State p :=
  let a0 := ExecFloat.Binary.toFloat32 (A.getD (baseA0 + k) posZero)
  let a1 := ExecFloat.Binary.toFloat32 (A.getD (baseA1 + k) posZero)
  sweep p (baseB + k * p) B a0 a1 0 s

theorem advance_get (p baseA0 baseA1 baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) (j : Fin p) :
    (advance p baseA0 baseA1 baseB A B k s).get j =
      updateCell (ExecFloat.Binary.toFloat32 (A.getD (baseA0 + k) posZero))
        (ExecFloat.Binary.toFloat32 (A.getD (baseA1 + k) posZero))
        (ExecFloat.Binary.toFloat32 (B.getD (baseB + j.val + k * p) posZero)) (s.get j) := by
  unfold advance
  rw [sweep_get]
  have haddr : baseB + k * p + j.val = baseB + j.val + k * p := by omega
  simp only [Nat.zero_le, if_true, haddr]

@[inline] def view0 {p : Nat} (s : State p) (j : Fin p) : Float32 := (s.get j).s0
@[inline] def view1 {p : Nat} (s : State p) (j : Fin p) : Float32 := (s.get j).s1

theorem advance_view0 (p baseA0 baseA1 baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) (j : Fin p) :
    view0 (advance p baseA0 baseA1 baseB A B k s) j = view0 s j +
      ExecFloat.Binary.toFloat32 (A.getD (baseA0 + k) posZero) *
      ExecFloat.Binary.toFloat32 (B.getD (baseB + j.val + k * p) posZero) := by
  simpa only [view0, updateCell] using congrArg (fun x : Cell => x.s0)
    (advance_get p baseA0 baseA1 baseB A B k s j)

theorem advance_view1 (p baseA0 baseA1 baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) (j : Fin p) :
    view1 (advance p baseA0 baseA1 baseB A B k s) j = view1 s j +
      ExecFloat.Binary.toFloat32 (A.getD (baseA1 + k) posZero) *
      ExecFloat.Binary.toFloat32 (B.getD (baseB + j.val + k * p) posZero) := by
  simpa only [view1, updateCell] using congrArg (fun x : Cell => x.s1)
    (advance_get p baseA0 baseA1 baseB A B k s j)

def initial (p : Nat) : State p :=
  ⟨Array.replicate p (⟨Packed10.zero32, Packed10.zero32⟩ : Cell), by simp⟩

theorem initial_view0 (p : Nat) (j : Fin p) : view0 (initial p) j = Packed10.zero32 := by
  simp [view0, initial, Vector.get]

theorem initial_view1 (p : Nat) (j : Fin p) : view1 (initial p) j = Packed10.zero32 := by
  simp [view1, initial, Vector.get]

def loop (p n baseA0 baseA1 baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) : State p :=
  if hk : k < n then
    loop p n baseA0 baseA1 baseB A B (k + 1) (advance p baseA0 baseA1 baseB A B k s)
  else s
termination_by n - k

theorem loop_eq_storage (p n baseA0 baseA1 baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) :
    loop p n baseA0 baseA1 baseB A B k s =
      R20WideRowRefinement.storageLoop n (advance p baseA0 baseA1 baseB A B) k s := by
  have he := @loop.eq_def p n baseA0 baseA1 baseB A B k s
  have hg := @R20WideRowRefinement.storageLoop.eq_def (State p) n
    (advance p baseA0 baseA1 baseB A B) k s
  by_cases hk : k < n
  · rw [he, hg]
    simp only [dif_pos hk]
    exact loop_eq_storage p n baseA0 baseA1 baseB A B (k + 1) _
  · rw [he, hg]
    simp only [dif_neg hk]
termination_by n - k
decreasing_by all_goals omega

theorem finish0 (p n baseA0 baseA1 baseB : Nat) (A B : Array Binary32) (j : Fin p) :
    Packed10.finish n baseA0 (baseB + j.val) p A B
      (view0 (loop p n baseA0 baseA1 baseB A B 0 (initial p)) j) =
      NativeFinal.dot n baseA0 (baseB + j.val) p A B := by
  rw [loop_eq_storage]
  exact R20WideRowRefinement.finish_lane n p p baseA0 baseB A B view0
    (advance p baseA0 baseA1 baseB A B)
    (fun k _ s j => advance_view0 p baseA0 baseA1 baseB A B k s j)
    (initial p) (initial_view0 p) j

theorem finish1 (p n baseA0 baseA1 baseB : Nat) (A B : Array Binary32) (j : Fin p) :
    Packed10.finish n baseA1 (baseB + j.val) p A B
      (view1 (loop p n baseA0 baseA1 baseB A B 0 (initial p)) j) =
      NativeFinal.dot n baseA1 (baseB + j.val) p A B := by
  rw [loop_eq_storage]
  exact R20WideRowRefinement.finish_lane n p p baseA1 baseB A B view1
    (advance p baseA0 baseA1 baseB A B)
    (fun k _ s j => advance_view1 p baseA0 baseA1 baseB A B k s j)
    (initial p) (initial_view1 p) j

@[noinline] def controlRows (p n baseA0 baseA1 baseB : Nat) (A B : Array Binary32)
    (out : Array Binary32) : Array Binary32 :=
  let out := RowStream.emit p (fun j => NativeFinal.dot n baseA0 (baseB + j.val) p A B) out
  RowStream.emit p (fun j => NativeFinal.dot n baseA1 (baseB + j.val) p A B) out

@[noinline] def streamedRows (p n baseA0 baseA1 baseB : Nat) (A B : Array Binary32)
    (out : Array Binary32) : Array Binary32 :=
  if p = 0 then out else
    let s := loop p n baseA0 baseA1 baseB A B 0 (initial p)
    let out := RowStream.emit p (fun j =>
      Packed10.finish n baseA0 (baseB + j.val) p A B (view0 s j)) out
    RowStream.emit p (fun j =>
      Packed10.finish n baseA1 (baseB + j.val) p A B (view1 s j)) out

theorem streamedRows_eq_control (p n baseA0 baseA1 baseB : Nat) (A B : Array Binary32)
    (out : Array Binary32) :
    streamedRows p n baseA0 baseA1 baseB A B out = controlRows p n baseA0 baseA1 baseB A B out := by
  by_cases hp : p = 0
  · subst p
    rfl
  · simp only [streamedRows, hp, if_false, controlRows, finish0, finish1]

theorem emit_size (p : Nat) (read : Fin p → Binary32) (out : Array Binary32) :
    (RowStream.emit p read out).size = out.size + p := by
  apply RowStream.foldl_inv p (fun acc j => acc.push (read j))
    (fun k acc => acc.size = out.size + k)
  · intro j acc h
    simp only [Array.size_push, h]
    omega
  · omega

theorem controlRows_size (p n baseA0 baseA1 baseB : Nat) (A B : Array Binary32)
    (out : Array Binary32) :
    (controlRows p n baseA0 baseA1 baseB A B out).size = out.size + 2 * p := by
  simp only [controlRows, emit_size]
  omega

theorem streamedRows_size (p n baseA0 baseA1 baseB : Nat) (A B : Array Binary32)
    (out : Array Binary32) :
    (streamedRows p n baseA0 baseA1 baseB A B out).size = out.size + 2 * p := by
  rw [streamedRows_eq_control, controlRows_size]

@[noinline] def controlPair (n p : Nat) (A : Vector Binary32 (2 * n))
    (B : Vector Binary32 (n * p)) : Vector Binary32 (2 * p) :=
  ⟨controlRows p n 0 n 0 A.toArray B.toArray (Array.mkEmpty (2 * p)), by
    rw [controlRows_size]
    simp⟩

@[noinline] def streamedPair (n p : Nat) (A : Vector Binary32 (2 * n))
    (B : Vector Binary32 (n * p)) : Vector Binary32 (2 * p) :=
  ⟨streamedRows p n 0 n 0 A.toArray B.toArray (Array.mkEmpty (2 * p)), by
    rw [streamedRows_size]
    simp⟩

theorem streamedPair_eq_control (n p : Nat) (A : Vector Binary32 (2 * n))
    (B : Vector Binary32 (n * p)) : streamedPair n p A B = controlPair n p A B := by
  unfold streamedPair controlPair
  congr 1
  exact streamedRows_eq_control p n 0 n 0 A.toArray B.toArray (Array.mkEmpty (2 * p))

end Submission.R21StreamingPair
