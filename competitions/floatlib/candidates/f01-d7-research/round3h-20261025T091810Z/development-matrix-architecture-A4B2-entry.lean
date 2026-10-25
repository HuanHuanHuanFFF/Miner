/- R16 A4B2 real row-major writer and full-entry proof attempt, NOT_COMPILED.
   Depends on exact622d and A4B2-core.lean. No global native A array.
   The final zero to three rows retain accepted B2 and its raw replay bases. -/
namespace Submission.R16A4B2
open FloatLib.Floats Competition

def Projects (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (b : Fin batch) (first : Nat) (tiles : Tiles p) : Prop :=
  ∀ (g : Fin (R15ThinPairs.groups p)) (r : Fin 4),
    projectRow (tiles.get g) r =
      R15PackedB2.loop n ((b.val*m+first+r.val)*n) A.toArray
        ((R15PackedB2.packB batch n p B).get (R15PackedB2.tileIndex batch p b g))
        0 Packed10.zero32 Packed10.zero32

theorem buildTiles_projects (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (hn : n<USize.size) (b : Fin batch) (first : Nat) :
    Projects batch m n p A B b first
      (buildTiles batch m n p A (R15PackedB2.packB batch n p B) hn b first) := by
  intro g r
  exact buildTiles_row batch m n p A (R15PackedB2.packB batch n p B) hn b first g r

theorem finish_lane (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (b : Fin batch) (first : Nat) (tiles : Tiles p)
    (hproj : Projects batch m n p A B b first tiles)
    (g : Fin (R15ThinPairs.groups p)) (r : Fin 4) (l : Nat) (hl : l<2) :
    Packed10.finish n ((b.val*m+first+r.val)*n) (b.val*n*p+2*g.val+l) p
      A.toArray B.toArray (lane (tiles.get g) r l) =
      NativeFinal.dot n ((b.val*m+first+r.val)*n) (b.val*n*p+2*g.val+l) p
        A.toArray B.toArray := by
  rw [lane_eq,hproj g r,R15PackedB2.packed_loop_eq]
  exact R15ThinPairs.finish_select n ((b.val*m+first+r.val)*n)
    (b.val*n*p+2*g.val) p A.toArray B.toArray l hl

@[inline] def emitGroup (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (b : Fin batch) (first : Nat) (tiles : Tiles p) (r : Fin 4)
    (out : Array Binary32) (g : Fin (R15ThinPairs.groups p)) : Array Binary32 :=
  let baseA := (b.val*m+first+r.val)*n
  let baseB := b.val*n*p+2*g.val
  let result := tiles.get g
  RowStream.emit (min 2 (p-2*g.val)) (fun l =>
    Packed10.finish n baseA (baseB+l.val) p A.toArray B.toArray
      (lane result r l.val)) out

theorem emitGroup_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (b : Fin batch) (first : Nat) (tiles : Tiles p)
    (hblock : first+4≤m) (hproj : Projects batch m n p A B b first tiles)
    (r : Fin 4) (g : Fin (R15ThinPairs.groups p)) (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val*m+first+r.val)*p+min (2*g.val) p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val*m+first+r.val)*p+min (2*(g.val+1)) p)
      (emitGroup batch m n p A B b first tiles r out g) := by
  have hr := r.isLt
  have hm : 0<m := by omega
  have hrow : first+r.val<m := by omega
  have hdiv : (b.val*m+first+r.val)/m=b.val := by
    rw [show b.val*m+first+r.val=b.val*m+(first+r.val) by omega,
      Nat.mul_comm b.val m,Nat.mul_add_div hm,Nat.div_eq_of_lt hrow,Nat.add_zero]
  have hg : 2*g.val<p := by
    have hg := g.isLt
    unfold R15ThinPairs.groups at hg
    omega
  have hp : 0<p := by omega
  have hstart : min (2*g.val) p=2*g.val := by omega
  have hend : (b.val*m+first+r.val)*p+min (2*(g.val+1)) p =
      ((b.val*m+first+r.val)*p+2*g.val)+min 2 (p-2*g.val) := by omega
  rw [hend]
  unfold emitGroup
  dsimp only
  apply RowStream.emit_prefix
  · simpa only [hstart] using hout
  · intro l
    have hcol : 2*g.val+l.val<p := by have hl:=l.isLt; omega
    rw [show (b.val*m+first+r.val)*p+2*g.val+l.val =
      (b.val*m+first+r.val)*p+(2*g.val+l.val) by omega,
      RowStream.point_row batch m n p A B (b.val*m+first+r.val)
        (2*g.val+l.val) hm hp hcol,hdiv]
    have h := finish_lane batch m n p A B b first tiles hproj g r l.val
      (Nat.lt_of_lt_of_le l.isLt (Nat.min_le_left _ _))
    simpa only [Nat.add_assoc] using h

@[inline] def emitRow (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (b : Fin batch) (first : Nat) (tiles : Tiles p)
    (out : Array Binary32) (r : Fin 4) : Array Binary32 :=
  Fin.foldl (R15ThinPairs.groups p) (emitGroup batch m n p A B b first tiles r) out

theorem emitRow_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (b : Fin batch) (first : Nat) (tiles : Tiles p)
    (hblock : first+4≤m) (hproj : Projects batch m n p A B b first tiles)
    (out : Array Binary32) (r : Fin 4)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val*m+first+r.val)*p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val*m+first+r.val+1)*p)
      (emitRow batch m n p A B b first tiles out r) := by
  have hlast : min (2*R15ThinPairs.groups p) p=p := by unfold R15ThinPairs.groups; omega
  have h := RowStream.foldl_inv (R15ThinPairs.groups p)
    (emitGroup batch m n p A B b first tiles r)
    (fun g acc => RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val*m+first+r.val)*p+min (2*g) p) acc)
    (fun g acc hacc => emitGroup_prefix batch m n p A B b first tiles hblock hproj r g acc hacc)
    out (by simpa only [Nat.mul_zero,Nat.zero_min,Nat.add_zero] using hout)
  simpa only [emitRow,hlast,Nat.add_mul,Nat.one_mul] using h

@[inline] def emitBlock (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (b : Fin batch) (first : Nat) (tiles : Tiles p) (out : Array Binary32) : Array Binary32 :=
  Fin.foldl 4 (emitRow batch m n p A B b first tiles) out

theorem emitBlock_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (b : Fin batch) (first : Nat) (tiles : Tiles p)
    (hblock : first+4≤m) (hproj : Projects batch m n p A B b first tiles)
    (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) ((b.val*m+first)*p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((b.val*m+first+4)*p)
      (emitBlock batch m n p A B b first tiles out) := by
  exact RowStream.foldl_inv 4 (emitRow batch m n p A B b first tiles)
    (fun r acc => RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val*m+first+r)*p) acc)
    (fun r acc hacc => by
      simpa only [Nat.add_assoc] using
        emitRow_prefix batch m n p A B b first tiles hblock hproj acc r hacc)
    out (by simpa only [Nat.add_zero] using hout)

def rowIndex (batch m : Nat) (b : Fin batch) (i : Fin m) : Fin (batch*m) :=
  ⟨b.val*m+i.val,by
    have h:=Nat.mul_le_mul_right m b.isLt
    rw [Nat.succ_mul] at h
    omega⟩

@[inline] def emitTail (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (b : Fin batch) (packedB : PackedB batch n p) (first : Nat)
    (out : Array Binary32) : Array Binary32 :=
  Fin.foldl (m-first) (fun acc i =>
    R15PackedB2.row batch m n p A B packedB acc
      (rowIndex batch m b ⟨first+i.val,by have hi:=i.isLt;omega⟩)) out

theorem emitTail_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (b : Fin batch) (first : Nat) (hfirst : first≤m) (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) ((b.val*m+first)*p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((b.val+1)*m*p)
      (emitTail batch m n p A B b (R15PackedB2.packB batch n p B) first out) := by
  have h := RowStream.foldl_inv (m-first)
    (fun acc i => R15PackedB2.row batch m n p A B (R15PackedB2.packB batch n p B) acc
      (rowIndex batch m b ⟨first+i.val,by have hi:=i.isLt;omega⟩))
    (fun i acc => RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val*m+first+i)*p) acc)
    (fun i acc hacc => by
      rw [R15PackedB2.row_eq]
      have hr := R15ThinPairs.row_prefix batch m n p A B
        (rowIndex batch m b ⟨first+i.val,by have hi:=i.isLt;omega⟩) acc
        (by simpa only [rowIndex,Nat.add_assoc] using hacc)
      simpa only [rowIndex,Nat.add_assoc] using hr)
    out (by simpa only [Nat.add_zero] using hout)
  have hend : b.val*m+first+(m-first)=(b.val+1)*m := by
    rw [Nat.add_mul,Nat.one_mul]
    omega
  simpa only [emitTail,hend] using h

@[inline] def writeBatch (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (packedB : PackedB batch n p) (hn : n<USize.size)
    (out : Array Binary32) (b : Fin batch) : Array Binary32 :=
  let afterBlocks := Fin.foldl (m/4) (fun acc h =>
    let tiles := buildTiles batch m n p A packedB hn b (4*h.val)
    emitBlock batch m n p A B b (4*h.val) tiles acc) out
  emitTail batch m n p A B b packedB (4*(m/4)) afterBlocks

theorem writeBatch_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (hn : n<USize.size) (out : Array Binary32) (b : Fin batch)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) (b.val*m*p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((b.val+1)*m*p)
      (writeBatch batch m n p A B (R15PackedB2.packB batch n p B) hn out b) := by
  have hblocks := RowStream.foldl_inv (m/4)
    (fun acc h => emitBlock batch m n p A B b (4*h.val)
      (buildTiles batch m n p A (R15PackedB2.packB batch n p B) hn b (4*h.val)) acc)
    (fun h acc => RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val*m+4*h)*p) acc)
    (fun h acc hacc => by
      have hh:=h.isLt
      have hblock : 4*h.val+4≤m := by omega
      simpa only [Nat.mul_add,Nat.mul_one,Nat.add_assoc] using
        emitBlock_prefix batch m n p A B b (4*h.val)
          (buildTiles batch m n p A (R15PackedB2.packB batch n p B) hn b (4*h.val))
          hblock (buildTiles_projects batch m n p A B hn b (4*h.val)) acc hacc)
    out (by simpa only [Nat.mul_zero,Nat.add_zero] using hout)
  have hfirst : 4*(m/4)≤m := by omega
  exact emitTail_prefix batch m n p A B b (4*(m/4)) hfirst _ hblocks

@[inline] def output (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (hn : n<USize.size) : Array Binary32 :=
  let packedB := R15PackedB2.packB batch n p B
  Fin.foldl batch (writeBatch batch m n p A B packedB hn) (Array.mkEmpty (batch*m*p))

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) (hn : n<USize.size) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch*m*p)
      (output batch m n p A B hn) := by
  exact RowStream.foldl_inv batch
    (writeBatch batch m n p A B (R15PackedB2.packB batch n p B) hn)
    (fun b acc => RowStream.Prefix (RowStream.point batch m n p A B) (b*m*p) acc)
    (fun b acc hacc => writeBatch_prefix batch m n p A B hn acc b hacc)
    (Array.mkEmpty (batch*m*p)) ⟨by simp,by intro j hj;simp at hj⟩

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) (hn : n<USize.size) :
    Vector Binary32 (batch*m*p) :=
  ⟨output batch m n p A B hn,(output_prefix batch m n p A B hn).1⟩

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) (hn : n<USize.size) :
    core batch m n p A B hn = referenceBmm batch m n p A B := by
  exact (RowStream.prefix_vector_eq_ofFn (RowStream.point batch m n p A B)
    (batch*m*p) (output batch m n p A B hn) (output_prefix batch m n p A B hn)).trans
    (RowStream.points_eq_reference batch m n p A B)

def dispatch (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) : Vector Binary32 (batch*m*p) :=
  if h : 2≤p ∧ 1<n ∧ 4≤m ∧ n<USize.size then core batch m n p A B h.2.2.2
  else R15PackedB2.dispatch batch m n p A B

theorem dispatch_spec : ∀ (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)),
    (dispatch batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold dispatch
  split
  · rw [core_eq_reference]
    exact referenceBmm_spec batch m n p A B
  · exact R15PackedB2.dispatch_spec batch m n p A B

end Submission.R16A4B2
