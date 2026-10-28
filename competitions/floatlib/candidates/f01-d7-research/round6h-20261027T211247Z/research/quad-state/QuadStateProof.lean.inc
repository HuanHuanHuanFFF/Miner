/- Proof-only refinement for the exact R22StreamingQuad runtime.
   Uses R20WideRowRefinement from the accepted R21 4e36 carrier. NOT_RUN. -/
namespace Submission.R22StreamingQuad
open FloatLib.Floats Competition

theorem advance_get (p n baseA baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) (j : Fin p) :
    (advance p n baseA baseB A B k s).get j =
      update (ExecFloat.Binary.toFloat32 (A.getD (baseA+k) posZero))
        (ExecFloat.Binary.toFloat32 (A.getD (baseA+n+k) posZero))
        (ExecFloat.Binary.toFloat32 (A.getD (baseA+2*n+k) posZero))
        (ExecFloat.Binary.toFloat32 (A.getD (baseA+3*n+k) posZero))
        (ExecFloat.Binary.toFloat32 (B.getD (baseB+j.val+k*p) posZero)) (s.get j) := by
  change (s.toArray.mapIdx (fun i cell => update
    (ExecFloat.Binary.toFloat32 (A.getD (baseA+k) posZero))
    (ExecFloat.Binary.toFloat32 (A.getD (baseA+n+k) posZero))
    (ExecFloat.Binary.toFloat32 (A.getD (baseA+2*n+k) posZero))
    (ExecFloat.Binary.toFloat32 (A.getD (baseA+3*n+k) posZero))
    (ExecFloat.Binary.toFloat32 (B.getD (baseB+k*p+i) posZero)) cell))[j.val] = _
  rw [Array.getElem_mapIdx]
  have haddr : baseB+k*p+j.val = baseB+j.val+k*p := by omega
  rw [haddr]
  rfl

@[inline] def view0 {p : Nat} (s : State p) (j : Fin p) : Float32 := (s.get j).s0

theorem advance_view0 (p n baseA baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) (j : Fin p) :
    view0 (advance p n baseA baseB A B k s) j = view0 s j +
      ExecFloat.Binary.toFloat32 (A.getD (baseA+k) posZero) *
      ExecFloat.Binary.toFloat32 (B.getD (baseB+j.val+k*p) posZero) := by
  simpa only [view0,update] using congrArg (fun x : Cell => x.s0)
    (advance_get p n baseA baseB A B k s j)

theorem initial_view0 (p : Nat) (j : Fin p) : view0 (initial p) j = Packed10.zero32 := by
  change ((Array.replicate p (⟨Packed10.zero32,Packed10.zero32,
    Packed10.zero32,Packed10.zero32⟩ : Cell))[j.val]).s0 = _
  simp only [Array.getElem_replicate]

@[inline] def view1 {p : Nat} (s : State p) (j : Fin p) : Float32 := (s.get j).s1

theorem advance_view1 (p n baseA baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) (j : Fin p) :
    view1 (advance p n baseA baseB A B k s) j = view1 s j +
      ExecFloat.Binary.toFloat32 (A.getD ((baseA+n)+k) posZero) *
      ExecFloat.Binary.toFloat32 (B.getD (baseB+j.val+k*p) posZero) := by
  simpa only [view1,update] using congrArg (fun x : Cell => x.s1)
    (advance_get p n baseA baseB A B k s j)

theorem initial_view1 (p : Nat) (j : Fin p) : view1 (initial p) j = Packed10.zero32 := by
  change ((Array.replicate p (⟨Packed10.zero32,Packed10.zero32,
    Packed10.zero32,Packed10.zero32⟩ : Cell))[j.val]).s1 = _
  simp only [Array.getElem_replicate]

@[inline] def view2 {p : Nat} (s : State p) (j : Fin p) : Float32 := (s.get j).s2

theorem advance_view2 (p n baseA baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) (j : Fin p) :
    view2 (advance p n baseA baseB A B k s) j = view2 s j +
      ExecFloat.Binary.toFloat32 (A.getD ((baseA+2*n)+k) posZero) *
      ExecFloat.Binary.toFloat32 (B.getD (baseB+j.val+k*p) posZero) := by
  simpa only [view2,update] using congrArg (fun x : Cell => x.s2)
    (advance_get p n baseA baseB A B k s j)

theorem initial_view2 (p : Nat) (j : Fin p) : view2 (initial p) j = Packed10.zero32 := by
  change ((Array.replicate p (⟨Packed10.zero32,Packed10.zero32,
    Packed10.zero32,Packed10.zero32⟩ : Cell))[j.val]).s2 = _
  simp only [Array.getElem_replicate]

@[inline] def view3 {p : Nat} (s : State p) (j : Fin p) : Float32 := (s.get j).s3

theorem advance_view3 (p n baseA baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) (j : Fin p) :
    view3 (advance p n baseA baseB A B k s) j = view3 s j +
      ExecFloat.Binary.toFloat32 (A.getD ((baseA+3*n)+k) posZero) *
      ExecFloat.Binary.toFloat32 (B.getD (baseB+j.val+k*p) posZero) := by
  simpa only [view3,update] using congrArg (fun x : Cell => x.s3)
    (advance_get p n baseA baseB A B k s j)

theorem initial_view3 (p : Nat) (j : Fin p) : view3 (initial p) j = Packed10.zero32 := by
  change ((Array.replicate p (⟨Packed10.zero32,Packed10.zero32,
    Packed10.zero32,Packed10.zero32⟩ : Cell))[j.val]).s3 = _
  simp only [Array.getElem_replicate]

theorem loop_eq_storage (p n baseA baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) :
    loop p n baseA baseB A B k s =
      R20WideRowRefinement.storageLoop n (advance p n baseA baseB A B) k s := by
  have he := @loop.eq_def p n baseA baseB A B k s
  have hg := @R20WideRowRefinement.storageLoop.eq_def (State p) n
    (advance p n baseA baseB A B) k s
  by_cases hk : k<n
  · rw [he,hg]
    simp only [dif_pos hk]
    exact loop_eq_storage p n baseA baseB A B (k+1) _
  · rw [he,hg]
    simp only [dif_neg hk]
termination_by n-k
decreasing_by all_goals omega

theorem loop_view0 (p n baseA baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) (j : Fin p) :
    view0 (loop p n baseA baseB A B k s) j =
      NativeFinal.dotLoop n baseA (baseB+j.val) p A B k (view0 s j) := by
  rw [loop_eq_storage]
  exact R20WideRowRefinement.storageLoop_lane n p p baseA baseB A B view0
    (advance p n baseA baseB A B)
    (fun k _ s j => advance_view0 p n baseA baseB A B k s j) k s j

theorem finish0 (p n baseA baseB : Nat) (A B : Array Binary32) (j : Fin p) :
    Packed10.finish n baseA (baseB+j.val) p A B
      ((loop p n baseA baseB A B 0 (initial p)).get j).s0 =
      NativeFinal.dot n baseA (baseB+j.val) p A B := by
  apply Packed10.finish_eq_dot
  simpa only [initial_view0] using
    loop_view0 p n baseA baseB A B 0 (initial p) j

theorem loop_view1 (p n baseA baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) (j : Fin p) :
    view1 (loop p n baseA baseB A B k s) j =
      NativeFinal.dotLoop n (baseA+n) (baseB+j.val) p A B k (view1 s j) := by
  rw [loop_eq_storage]
  exact R20WideRowRefinement.storageLoop_lane n p p (baseA+n) baseB A B view1
    (advance p n baseA baseB A B)
    (fun k _ s j => advance_view1 p n baseA baseB A B k s j) k s j

theorem finish1 (p n baseA baseB : Nat) (A B : Array Binary32) (j : Fin p) :
    Packed10.finish n (baseA+n) (baseB+j.val) p A B
      ((loop p n baseA baseB A B 0 (initial p)).get j).s1 =
      NativeFinal.dot n (baseA+n) (baseB+j.val) p A B := by
  apply Packed10.finish_eq_dot
  simpa only [initial_view1] using
    loop_view1 p n baseA baseB A B 0 (initial p) j

theorem loop_view2 (p n baseA baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) (j : Fin p) :
    view2 (loop p n baseA baseB A B k s) j =
      NativeFinal.dotLoop n (baseA+2*n) (baseB+j.val) p A B k (view2 s j) := by
  rw [loop_eq_storage]
  exact R20WideRowRefinement.storageLoop_lane n p p (baseA+2*n) baseB A B view2
    (advance p n baseA baseB A B)
    (fun k _ s j => advance_view2 p n baseA baseB A B k s j) k s j

theorem finish2 (p n baseA baseB : Nat) (A B : Array Binary32) (j : Fin p) :
    Packed10.finish n (baseA+2*n) (baseB+j.val) p A B
      ((loop p n baseA baseB A B 0 (initial p)).get j).s2 =
      NativeFinal.dot n (baseA+2*n) (baseB+j.val) p A B := by
  apply Packed10.finish_eq_dot
  simpa only [initial_view2] using
    loop_view2 p n baseA baseB A B 0 (initial p) j

theorem loop_view3 (p n baseA baseB : Nat) (A B : Array Binary32)
    (k : Nat) (s : State p) (j : Fin p) :
    view3 (loop p n baseA baseB A B k s) j =
      NativeFinal.dotLoop n (baseA+3*n) (baseB+j.val) p A B k (view3 s j) := by
  rw [loop_eq_storage]
  exact R20WideRowRefinement.storageLoop_lane n p p (baseA+3*n) baseB A B view3
    (advance p n baseA baseB A B)
    (fun k _ s j => advance_view3 p n baseA baseB A B k s j) k s j

theorem finish3 (p n baseA baseB : Nat) (A B : Array Binary32) (j : Fin p) :
    Packed10.finish n (baseA+3*n) (baseB+j.val) p A B
      ((loop p n baseA baseB A B 0 (initial p)).get j).s3 =
      NativeFinal.dot n (baseA+3*n) (baseB+j.val) p A B := by
  apply Packed10.finish_eq_dot
  simpa only [initial_view3] using
    loop_view3 p n baseA baseB A B 0 (initial p) j

theorem rows4_eq_control (p n baseA baseB : Nat) (A B : Array Binary32)
    (out : Array Binary32) :
    rows4 p n baseA baseB A B out =
      RowStream.emit p (fun j => NativeFinal.dot n (baseA+3*n) (baseB+j.val) p A B)
        (RowStream.emit p (fun j => NativeFinal.dot n (baseA+2*n) (baseB+j.val) p A B)
          (RowStream.emit p (fun j => NativeFinal.dot n (baseA+n) (baseB+j.val) p A B)
            (RowStream.emit p (fun j => NativeFinal.dot n baseA (baseB+j.val) p A B) out))) := by
  by_cases hp : p=0
  · subst p
    rfl
  · simp only [rows4,hp,if_false,finish0,finish1,finish2,finish3]

end Submission.R22StreamingQuad
