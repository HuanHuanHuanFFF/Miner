/- R12 NOT_RUN replacement region inside Submission.RowStream.
The numeric array/base may be local; raw finish bases always denote original words.
Read equality is a Prop premise, never a Float32 reader callback in the MAC loop. -/
theorem dot10_read_eq (n localBase rawBase : Nat) (localA source : Array Float32)
    (B : Vector Packed10.F10 n)
    (hread : ∀ i : Fin n, localA.getD (localBase+i.val) Packed10.zero32 =
      source.getD (rawBase+i.val) Packed10.zero32)
    (k : Nat) (s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 : Float32) :
    Packed10.dot10 n localBase localA B k s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 =
      Packed10.dot10 n rawBase source B k s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 := by
  by_cases hk : k<n
  · conv_lhs => rw [Packed10.dot10]
    conv_rhs => rw [Packed10.dot10]
    simp only [dif_pos hk]
    rw [hread ⟨k,hk⟩]
    exact dot10_read_eq n localBase rawBase localA source B hread (k+1) _ _ _ _ _ _ _ _ _ _
  · conv_lhs => rw [Packed10.dot10]
    conv_rhs => rw [Packed10.dot10]
    simp only [dif_neg hk]
termination_by n-k
decreasing_by omega
theorem runDot_read_eq (n localBase rawBase : Nat) (localA source : Array Float32)
    (B : Vector Packed10.F10 n)
    (hread : ∀ i : Fin n, localA.getD (localBase+i.val) Packed10.zero32 =
      source.getD (rawBase+i.val) Packed10.zero32) :
    Packed10Index.runDot n localBase localA B = Packed10Index.runDot n rawBase source B := by
  rw [Packed10Index.runDot_eq, Packed10Index.runDot_eq]
  exact dot10_read_eq n localBase rawBase localA source B hread 0 _ _ _ _ _ _ _ _ _ _
@[inline] def batchIndex (batch m : Nat) (r : Fin (batch*m)) : Fin batch :=
  ⟨r.val/m, (Nat.div_lt_iff_lt_mul (Nat.pos_of_lt_mul_left r.isLt)).2 r.isLt⟩
/-- Raw A/B bases remain separate from the numeric A offset. All arrays are direct parameters. -/
@[inline] def group (n p numericBase rawBaseA rawBaseB : Nat) (Araw Braw : Array Binary32)
    (nativeA : Array Float32) (batchB : Vector (Vector Packed10.F10 n) (Packed10.groups p))
    (out : Array Binary32) (g : Fin (Packed10.groups p)) : Array Binary32 :=
  let result := Packed10Index.runDot n numericBase nativeA (batchB.get g)
  let count := min 10 (p-10*g.val)
  emit count (fun l =>
    let j := 10*g.val+l.val
    Packed10.finish n rawBaseA (rawBaseB+j) p Araw Braw
      (Packed10.lane result ⟨l.val,Nat.lt_of_lt_of_le l.isLt (Nat.min_le_left _ _)⟩)) out
theorem group_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (nativeA : Array Float32) (numericBase : Nat) (r : Fin (batch*m))
    (hread : ∀ i : Fin n, nativeA.getD (numericBase+i.val) Packed10.zero32 =
      (A.toArray.map ExecFloat.Binary.toFloat32).getD (r.val*n+i.val) Packed10.zero32)
    (g : Fin (Packed10.groups p)) (out : Array Binary32)
    (hout : Prefix (point batch m n p A B) (r.val*p+min (10*g.val) p) out) :
    Prefix (point batch m n p A B) (r.val*p+min (10*(g.val+1)) p)
      (group n p numericBase (r.val*n) ((batchIndex batch m r).val*n*p) A.toArray B.toArray
        nativeA ((Packed10.packB batch n p B).get (batchIndex batch m r)) out g) := by
  have hm : 0<m := Nat.pos_of_lt_mul_left r.isLt
  have hg : 10*g.val<p := by have hh:=g.isLt; unfold Packed10.groups at hh; omega
  have hp : 0<p := by omega
  have hstart : min (10*g.val) p=10*g.val := by omega
  have hend : r.val*p+min (10*(g.val+1)) p =
      (r.val*p+10*g.val)+min 10 (p-10*g.val) := by omega
  rw [hend]
  unfold group
  try dsimp only
  apply emit_prefix
  · simpa only [hstart] using hout
  · intro l
    have hcol : 10*g.val+l.val<p := by have hl:=l.isLt; omega
    rw [show r.val*p+10*g.val+l.val=r.val*p+(10*g.val+l.val) by omega,
      point_row batch m n p A B r.val (10*g.val+l.val) hm hp hcol,
      runDot_read_eq n numericBase (r.val*n) nativeA (A.toArray.map ExecFloat.Binary.toFloat32)
        (((Packed10.packB batch n p B).get (batchIndex batch m r)).get g) hread,
      Packed10Index.runDot_eq]
    apply Packed10.finish_dot10_lane
    intro k
    rw [Packed10.packB_lane batch n p B (batchIndex batch m r) g k
      ⟨l.val,Nat.lt_of_lt_of_le l.isLt (Nat.min_le_left _ _)⟩ hcol]
    rw [index_address ((batchIndex batch m r).val*n) k.val p (10*g.val+l.val)]
/-- Choose numeric/raw bases and the batch B vector once before the column loop. -/
@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (nativeA : Array Float32)
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (numericBase : Nat) (out : Array Binary32) (r : Fin (batch*m)) : Array Binary32 :=
  let b := batchIndex batch m r
  let rawBaseA := r.val*n
  let rawBaseB := b.val*n*p
  let batchB := packedB.get b
  Fin.foldl (Packed10.groups p) (group n p numericBase rawBaseA rawBaseB A.toArray B.toArray nativeA batchB) out
theorem row_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (nativeA : Array Float32) (numericBase : Nat) (r : Fin (batch*m))
    (hread : ∀ i : Fin n, nativeA.getD (numericBase+i.val) Packed10.zero32 =
      (A.toArray.map ExecFloat.Binary.toFloat32).getD (r.val*n+i.val) Packed10.zero32)
    (out : Array Binary32) (hout : Prefix (point batch m n p A B) (r.val*p) out) :
    Prefix (point batch m n p A B) ((r.val+1)*p)
      (row batch m n p A B nativeA (Packed10.packB batch n p B) numericBase out r) := by
  have hlast : min (10*Packed10.groups p) p=p := by unfold Packed10.groups; omega
  have h := foldl_inv (Packed10.groups p)
    (group n p numericBase (r.val*n) ((batchIndex batch m r).val*n*p) A.toArray B.toArray
      nativeA ((Packed10.packB batch n p B).get (batchIndex batch m r)))
    (fun g acc => Prefix (point batch m n p A B) (r.val*p+min (10*g) p) acc)
    (fun g acc hacc => group_prefix batch m n p A B nativeA numericBase r hread g acc hacc) out
    (by simpa only [Nat.mul_zero,Nat.zero_min,Nat.add_zero] using hout)
  simpa only [row,hlast,Nat.add_mul,Nat.one_mul] using h
def output (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) : Array Binary32 :=
  let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
  let packedB := Packed10.packB batch n p B
  Fin.foldl (batch*m) (fun acc r => row batch m n p A B nativeA packedB (r.val*n) acc r)
    (Array.mkEmpty (batch*m*p))
theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    Prefix (point batch m n p A B) (batch*m*p) (output batch m n p A B) := by
  exact foldl_inv (batch*m)
    (fun acc r => row batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32)
      (Packed10.packB batch n p B) (r.val*n) acc r)
    (fun r acc => Prefix (point batch m n p A B) (r*p) acc)
    (fun r acc hacc => row_prefix batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32)
      (r.val*n) r (fun _ => rfl) acc hacc)
    (Array.mkEmpty (batch*m*p)) ⟨by simp,by intro j hj; simp at hj⟩
