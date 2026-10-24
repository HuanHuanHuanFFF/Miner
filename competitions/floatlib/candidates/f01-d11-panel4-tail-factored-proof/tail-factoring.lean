/- NOT_RUN proof/implementation asset, not a new Kernel or an active entry.
Requires the retained Packed10/Packed10Index/RowStream interfaces of749b.
All appearances of a global native map below are in proofs, not tail runtime. -/
namespace Submission.Panel4Tail
open FloatLib.Floats Competition

/-- At most three rows in the intended caller; total reads retain +0 defaults. -/
def prepare (rows n rawBase : Nat) (Araw : Array Binary32) : Array Float32 :=
  Array.ofFn fun q : Fin (rows * n) =>
    ExecFloat.Binary.toFloat32 (Araw.getD (rawBase + q.val) posZero)

theorem prepare_getD (rows n rawBase : Nat) (Araw : Array Binary32)
    (i : Nat) (hi : i < rows * n) :
    (prepare rows n rawBase Araw).getD i Packed10.zero32 =
      ExecFloat.Binary.toFloat32 (Araw.getD (rawBase + i) posZero) := by
  simp [prepare, Array.getD, hi, Array.size_ofFn, Array.getElem_ofFn]

theorem prepare_read (rows n rawBase : Nat) (Araw : Array Binary32)
    (r : Fin rows) (k : Fin n) :
    (prepare rows n rawBase Araw).getD (r.val * n + k.val) Packed10.zero32 =
      (Araw.map ExecFloat.Binary.toFloat32).getD (rawBase + r.val * n + k.val) Packed10.zero32 := by
  have hs := Nat.mul_le_mul_right n r.isLt
  rw [Nat.succ_mul] at hs
  have hi : r.val * n + k.val < rows * n := by have hk := k.isLt; omega
  rw [prepare_getD rows n rawBase Araw _ hi, Packed10.nativeA_getD]
  simp only [Nat.add_assoc]

/-- Only equality of the actually read A words is needed. No FP reassociation. -/
theorem dot10_shift (n localBase rawBase : Nat) (tailA source : Array Float32)
    (B : Vector Packed10.F10 n)
    (hread : ∀ i : Fin n, tailA.getD (localBase + i.val) Packed10.zero32 =
      source.getD (rawBase + i.val) Packed10.zero32)
    (k : Nat) (s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 : Float32) :
    Packed10.dot10 n localBase tailA B k s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 =
      Packed10.dot10 n rawBase source B k s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 := by
  by_cases hk : k < n
  · conv_lhs => rw [Packed10.dot10]
    conv_rhs => rw [Packed10.dot10]
    simp only [dif_pos hk]
    rw [hread ⟨k, hk⟩]
    exact dot10_shift n localBase rawBase tailA source B hread (k + 1)
      _ _ _ _ _ _ _ _ _ _
  · conv_lhs => rw [Packed10.dot10]
    conv_rhs => rw [Packed10.dot10]
    simp only [dif_neg hk]
termination_by n - k
decreasing_by omega

theorem runDot_shift (n localBase rawBase : Nat) (tailA source : Array Float32)
    (B : Vector Packed10.F10 n)
    (hread : ∀ i : Fin n, tailA.getD (localBase + i.val) Packed10.zero32 =
      source.getD (rawBase + i.val) Packed10.zero32) :
    Packed10Index.runDot n localBase tailA B = Packed10Index.runDot n rawBase source B := by
  rw [Packed10Index.runDot_eq, Packed10Index.runDot_eq]
  exact dot10_shift n localBase rawBase tailA source B hread 0 _ _ _ _ _ _ _ _ _ _

theorem runDot_prepared (rows n rawBase : Nat) (Araw : Array Binary32)
    (r : Fin rows) (B : Vector Packed10.F10 n) :
    Packed10Index.runDot n (r.val * n) (prepare rows n rawBase Araw) B =
      Packed10Index.runDot n (rawBase + r.val * n) (Araw.map ExecFloat.Binary.toFloat32) B := by
  apply runDot_shift
  intro k
  exact prepare_read rows n rawBase Araw r k

variable {batch m n p : Nat}
variable (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
variable (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
variable (b : Fin batch) (first : Nat)

@[inline] def group (tailA : Array Float32) (r : Fin (m-first))
    (out : Array Binary32) (g : Fin (Packed10.groups p)) : Array Binary32 :=
  let result := Packed10Index.runDot n (r.val*n) tailA ((packedB.get b).get g)
  RowStream.emit (min 10 (p-10*g.val)) (fun l =>
    Packed10.finish n ((b.val*m+first+r.val)*n) (b.val*n*p+10*g.val+l.val)
      p A.toArray B.toArray (Packed10.lane result
        ⟨l.val, Nat.lt_of_lt_of_le l.isLt (Nat.min_le_left _ _)⟩)) out

@[inline] def row (tailA : Array Float32) (out : Array Binary32) (r : Fin (m-first)) :=
  Fin.foldl (Packed10.groups p) (group A B packedB b first tailA r) out

theorem group_eq (r : Fin (m-first)) (out : Array Binary32) (g : Fin (Packed10.groups p)) :
    group A B packedB b first (prepare (m-first) n ((b.val*m+first)*n) A.toArray) r out g =
      RowStream.group batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32) packedB
        (R11WideLayout.rowIndex batch m b ⟨first+r.val, by have h:=r.isLt; omega⟩) out g := by
  have hr : first+r.val<m := by have h:=r.isLt; omega
  have hm : 0<m := by omega
  have hd : (b.val*m+(first+r.val))/m=b.val := by
    rw [Nat.mul_comm b.val m, Nat.mul_add_div hm, Nat.div_eq_of_lt hr, Nat.add_zero]
  simp only [group, RowStream.group, R11WideLayout.rowIndex, Nat.add_assoc, hd]
  rw [runDot_prepared]
  simp only [Nat.add_mul, Nat.add_assoc]

theorem row_eq (out : Array Binary32) (r : Fin (m-first)) :
    row A B packedB b first (prepare (m-first) n ((b.val*m+first)*n) A.toArray) out r =
      RowStream.row batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32) packedB out
        (R11WideLayout.rowIndex batch m b ⟨first+r.val, by have h:=r.isLt; omega⟩) := by
  unfold row RowStream.row
  apply congrArg (fun f => Fin.foldl (Packed10.groups p) f out)
  funext acc g
  exact group_eq A B packedB b first r acc g

def tail (out : Array Binary32) : Array Binary32 :=
  let tailA := prepare (m-first) n ((b.val*m+first)*n) A.toArray
  Fin.foldl (m-first) (row A B packedB b first tailA) out

theorem tail_eq (out : Array Binary32) :
    tail A B packedB b first out = R11WideLayout.emitTail batch m n p A B b
      (A.toArray.map ExecFloat.Binary.toFloat32) packedB first out := by
  simp only [tail, R11WideLayout.emitTail]
  apply congrArg (fun f => Fin.foldl (m-first) f out)
  funext acc r
  exact row_eq A B packedB b first acc r

theorem tail_prefix (hfirst : first≤m) (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) ((b.val*m+first)*p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((b.val+1)*m*p)
      (tail A B (Packed10.packB batch n p B) b first out) := by
  rw [tail_eq]
  exact R11WideLayout.emitTail_prefix batch m n p A B b first hfirst out hout

end Submission.Panel4Tail
