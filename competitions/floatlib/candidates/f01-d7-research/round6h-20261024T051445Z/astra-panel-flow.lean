/- R12 NOT_RUN replacement tail/output region inside R11WideLayout.
Full panels prepare A locally; the final0..3 rows prepare only their local slice.
The raw arrays remain alive for exact NaN replay. -/
def prepareTail (rows n rawBase : Nat) (Araw : Array Binary32) : Array Float32 :=
  Array.ofFn fun q : Fin (rows*n) =>
    ExecFloat.Binary.toFloat32 (Araw.getD (rawBase+q.val) posZero)
theorem prepareTail_getD (rows n rawBase : Nat) (Araw : Array Binary32)
    (i : Nat) (hi : i<rows*n) :
    (prepareTail rows n rawBase Araw).getD i Packed10.zero32 =
      ExecFloat.Binary.toFloat32 (Araw.getD (rawBase+i) posZero) := by
  simp [prepareTail,Array.getD,hi,Array.size_ofFn,Array.getElem_ofFn]
theorem prepareTail_read (rows n rawBase : Nat) (Araw : Array Binary32)
    (r : Fin rows) (k : Fin n) :
    (prepareTail rows n rawBase Araw).getD (r.val*n+k.val) Packed10.zero32 =
      (Araw.map ExecFloat.Binary.toFloat32).getD (rawBase+r.val*n+k.val) Packed10.zero32 := by
  have hs:=Nat.mul_le_mul_right n r.isLt
  rw [Nat.succ_mul] at hs
  have hi : r.val*n+k.val<rows*n := by have hk:=k.isLt; omega
  rw [prepareTail_getD rows n rawBase Araw _ hi,Packed10.nativeA_getD]
  simp only [Nat.add_assoc]
/-- Existing Packed10 handles only the remaining0..3 rows, using one local A preparation.
Global packedB and original raw A/B are shared; no full nativeA map is prepared here. -/
def emitTail (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) (b : Fin batch)
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (first : Nat) (out : Array Binary32) : Array Binary32 :=
  let nativeTail := prepareTail (m-first) n ((b.val*m+first)*n) A.toArray
  Fin.foldl (m-first) (fun acc i =>
    RowStream.row batch m n p A B nativeTail packedB (i.val*n) acc
      (rowIndex batch m b ⟨first+i.val,by have hi:=i.isLt; omega⟩)) out
theorem emitTail_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) (b : Fin batch)
    (first : Nat) (hfirst : first≤m) (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) ((b.val*m+first)*p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((b.val+1)*m*p)
      (emitTail batch m n p A B b (Packed10.packB batch n p B) first out) := by
  have h := RowStream.foldl_inv (m-first)
    (fun acc i => RowStream.row batch m n p A B
      (prepareTail (m-first) n ((b.val*m+first)*n) A.toArray)
      (Packed10.packB batch n p B) (i.val*n) acc
      (rowIndex batch m b ⟨first+i.val,by have hi:=i.isLt; omega⟩))
    (fun i acc => RowStream.Prefix (RowStream.point batch m n p A B) ((b.val*m+first+i)*p) acc)
    (fun i acc hacc => by
      have hread : ∀ k : Fin n,
          (prepareTail (m-first) n ((b.val*m+first)*n) A.toArray).getD
            (i.val*n+k.val) Packed10.zero32 =
          (A.toArray.map ExecFloat.Binary.toFloat32).getD
            ((rowIndex batch m b ⟨first+i.val,by have hi:=i.isLt; omega⟩).val*n+k.val) Packed10.zero32 := by
        intro k
        simpa only [rowIndex,Nat.add_mul,Nat.add_assoc] using
          prepareTail_read (m-first) n ((b.val*m+first)*n) A.toArray i k
      have hr := RowStream.row_prefix batch m n p A B
        (prepareTail (m-first) n ((b.val*m+first)*n) A.toArray) (i.val*n)
        (rowIndex batch m b ⟨first+i.val,by have hi:=i.isLt; omega⟩) hread acc
        (by simpa only [rowIndex,Nat.add_assoc] using hacc)
      simpa only [rowIndex,Nat.add_assoc] using hr)
    out (by simpa only [Nat.add_zero] using hout)
  have hend : b.val*m+first+(m-first)=(b.val+1)*m := by
    rw [Nat.add_mul,Nat.one_mul]
    omega
  simpa only [emitTail,hend] using h
/-- Each panel and its result vector are evaluated once per complete four-row block.
Only packedB is global preparation; the result cache is released after four-row output. -/
@[inline] def writeBatch (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (buildTiles : Fin batch → Fin (m/4) → Tiles p)
    (out : Array Binary32) (b : Fin batch) : Array Binary32 :=
  let afterBlocks := Fin.foldl (m/4) (fun acc h =>
    let tiles := buildTiles b h
    emitBlock batch m n p A B lane40 b (4*h.val) tiles acc) out
  emitTail batch m n p A B b packedB (4*(m/4)) afterBlocks
theorem writeBatch_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (buildTiles : Fin batch → Fin (m/4) → Tiles p)
    (hproj : ∀ (b : Fin batch) (h : Fin (m/4)),
      Projects batch m n p A B lane40 b (4*h.val) (buildTiles b h))
    (out : Array Binary32) (b : Fin batch)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) (b.val*m*p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((b.val+1)*m*p)
      (writeBatch batch m n p A B lane40 (Packed10.packB batch n p B) buildTiles out b) := by
  have hblocks := RowStream.foldl_inv (m/4)
    (fun acc h => emitBlock batch m n p A B lane40 b (4*h.val) (buildTiles b h) acc)
    (fun h acc => RowStream.Prefix (RowStream.point batch m n p A B) ((b.val*m+4*h)*p) acc)
    (fun h acc hacc => by
      have hh:=h.isLt
      have hblock : 4*h.val+4≤m := by omega
      simpa only [Nat.mul_add,Nat.mul_one,Nat.add_assoc] using
        emitBlock_prefix batch m n p A B lane40 b (4*h.val) (buildTiles b h) hblock (hproj b h) acc hacc)
    out (by simpa only [Nat.mul_zero,Nat.add_zero] using hout)
  have hfirst : 4*(m/4)≤m := by omega
  exact emitTail_prefix batch m n p A B b (4*(m/4)) hfirst _ hblocks
@[inline] def output (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (buildTiles : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch →
      Fin batch → Fin (m/4) → Tiles p) : Array Binary32 :=
  let packedB := Packed10.packB batch n p B
  Fin.foldl batch (writeBatch batch m n p A B lane40 packedB (buildTiles packedB))
    (Array.mkEmpty (batch*m*p))
theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (buildTiles : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch →
      Fin batch → Fin (m/4) → Tiles p)
    (hproj : ∀ (b : Fin batch) (h : Fin (m/4)), Projects batch m n p A B lane40 b (4*h.val)
      (buildTiles (Packed10.packB batch n p B) b h)) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch*m*p)
      (output batch m n p A B lane40 buildTiles) := by
  exact RowStream.foldl_inv batch
    (writeBatch batch m n p A B lane40 (Packed10.packB batch n p B)
      (buildTiles (Packed10.packB batch n p B)))
    (fun b acc => RowStream.Prefix (RowStream.point batch m n p A B) (b*m*p) acc)
    (fun b acc hacc => writeBatch_prefix batch m n p A B lane40 _ hproj acc b hacc)
    (Array.mkEmpty (batch*m*p)) ⟨by simp,by intro j hj; simp at hj⟩
