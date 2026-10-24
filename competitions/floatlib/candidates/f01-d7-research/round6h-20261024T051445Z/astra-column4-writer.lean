namespace Packed4
theorem finish_lane (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (B : Vector F4 n) (l : Fin 4)
    (hb : ∀ k : Fin n, lane (B.get k) l =
      ExecFloat.Binary.toFloat32 (Braw.getD (baseB+k.val*p) posZero)) :
    Packed10.finish n baseA baseB p Araw Braw
      (lane (Packed4Index.runDot n baseA (Araw.map ExecFloat.Binary.toFloat32) B) l) =
      NativeFinal.dot n baseA baseB p Araw Braw := by
  rw [Packed4Index.runDot_eq]
  have h := dot4_lane n baseA baseB p Araw Braw B l hb 0 zero32 zero32 zero32 zero32
  have hz : lane (⟨zero32,zero32,zero32,zero32⟩ : F4) l = zero32 := lane_zero4 l
  rw [hz] at h
  exact Packed10.finish_eq_dot n baseA baseB p Araw Braw _ h
end Packed4

namespace Narrow4
@[inline] def batchIndex (batch m : Nat) (r : Fin (batch*m)) : Fin batch :=
  ⟨r.val/m,(Nat.div_lt_iff_lt_mul (Nat.pos_of_lt_mul_left r.isLt)).2 r.isLt⟩
@[inline] def firstGroup (p : Nat) (hp : 0<p) : Fin (Packed4.groups p) :=
  ⟨0,by unfold Packed4.groups; omega⟩
@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (hp0 : 0<p) (hp4 : p≤4) (nativeA : Array Float32)
    (packedB : Vector (Vector (Vector Packed4.F4 n) (Packed4.groups p)) batch)
    (out : Array Binary32) (r : Fin (batch*m)) : Array Binary32 :=
  let b := batchIndex batch m r
  let rawA := r.val*n
  let rawB := b.val*n*p
  let result := Packed4Index.runDot n rawA nativeA ((packedB.get b).get (firstGroup p hp0))
  RowStream.emit p (fun j => Packed10.finish n rawA (rawB+j.val) p A.toArray B.toArray
    (Packed4.lane result ⟨j.val,Nat.lt_of_lt_of_le j.isLt hp4⟩)) out
theorem row_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (hp0 : 0<p) (hp4 : p≤4) (r : Fin (batch*m)) (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) (r.val*p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((r.val+1)*p)
      (row batch m n p A B hp0 hp4 (A.toArray.map ExecFloat.Binary.toFloat32)
        (Packed4.packB batch n p B) out r) := by
  have hm : 0<m := Nat.pos_of_lt_mul_left r.isLt
  rw [Nat.add_mul,Nat.one_mul]
  unfold row
  try dsimp only
  apply RowStream.emit_prefix
  · exact hout
  · intro j
    rw [RowStream.point_row batch m n p A B r.val j.val hm hp0 j.isLt]
    apply Packed4.finish_lane
    intro k
    rw [Packed4.packB_lane batch n p B (batchIndex batch m r) (firstGroup p hp0) k
      ⟨j.val,Nat.lt_of_lt_of_le j.isLt hp4⟩ (by simpa only [firstGroup,Nat.mul_zero,Nat.zero_add] using j.isLt)]
    simp only [firstGroup,Nat.mul_zero,Nat.zero_add]
    rw [index_address ((batchIndex batch m r).val*n) k.val p j.val]
@[inline] def output (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (hp0 : 0<p) (hp4 : p≤4) : Array Binary32 :=
  let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
  let packedB := Packed4.packB batch n p B
  Fin.foldl (batch*m) (row batch m n p A B hp0 hp4 nativeA packedB)
    (Array.mkEmpty (batch*m*p))
theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (hp0 : 0<p) (hp4 : p≤4) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch*m*p) (output batch m n p A B hp0 hp4) := by
  exact RowStream.foldl_inv (batch*m)
    (row batch m n p A B hp0 hp4 (A.toArray.map ExecFloat.Binary.toFloat32) (Packed4.packB batch n p B))
    (fun r acc => RowStream.Prefix (RowStream.point batch m n p A B) (r*p) acc)
    (fun r acc hacc => row_prefix batch m n p A B hp0 hp4 r acc hacc)
    (Array.mkEmpty (batch*m*p)) ⟨by simp,by intro j hj; simp at hj⟩
def core (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (hp0 : 0<p) (hp4 : p≤4) : Vector Binary32 (batch*m*p) :=
  ⟨output batch m n p A B hp0 hp4,(output_prefix batch m n p A B hp0 hp4).1⟩
theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (hp0 : 0<p) (hp4 : p≤4) : core batch m n p A B hp0 hp4 = referenceBmm batch m n p A B := by
  exact (RowStream.prefix_vector_eq_ofFn (RowStream.point batch m n p A B)
    (batch*m*p) (output batch m n p A B hp0 hp4) (output_prefix batch m n p A B hp0 hp4)).trans
    (RowStream.points_eq_reference batch m n p A B)
end Narrow4
