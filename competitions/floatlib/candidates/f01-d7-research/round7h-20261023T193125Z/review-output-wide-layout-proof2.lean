/- NOT_RUN design/proof asset. Append after compact RowStream and the exact
wide4 probe. This file is not a second Kernel or an implemented BMM entry.
The projection premise below is the explicit remaining interface owned by Astra.
It is a theorem parameter, never an added global assumption. -/
namespace Submission.R11WideLayout

open FloatLib.Floats Competition

abbrev Tiles (p : Nat) := Vector R11WideRows4.F40 (Packed10.groups p)

/-- Once n>0 and a complete four-row block exists, all four A spans are valid.
With global A.size<USize.size, each of these bases also fits a machine word. -/
theorem nativeA_span (batch m n : Nat)
    (A : Vector Binary32 (batch * m * n)) (b : Fin batch)
    (first : Nat) (hblock : first + 4 ≤ m) (r : Fin 4) (hn : 0 < n) :
    (b.val * m + first + r.val) * n + (n - 1) <
      (A.toArray.map ExecFloat.Binary.toFloat32).size := by
  have hr := r.isLt
  have hb := Nat.mul_le_mul_right m b.isLt
  rw [Nat.succ_mul] at hb
  have hrow : b.val * m + first + r.val < batch * m := by omega
  have hs := Nat.mul_le_mul_right n (Nat.succ_le_of_lt hrow)
  rw [Nat.succ_mul] at hs
  simp only [Array.size_map, A.size_toArray]
  omega

/-- Independent of old optional O2 helpers, which may be pruned. -/
def groupFor (p : Nat) (j : Fin p) : Fin (Packed10.groups p) :=
  ⟨j.val / 10, by have hj := j.isLt; unfold Packed10.groups; omega⟩

def laneFor (p : Nat) (j : Fin p) : Fin 10 :=
  ⟨j.val % 10, Nat.mod_lt _ (by decide)⟩

theorem columnFor (p : Nat) (j : Fin p) :
    10 * (groupFor p j).val + (laneFor p j).val = j.val := by
  dsimp only [groupFor, laneFor]
  omega

/-- The exact projection contract: one computed F40, four old F10 dot results.
The actual buildTiles must be evaluated once per block, not substituted as a
function that recomputes the wide loop for every scalar output. -/
def Projects (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (b : Fin batch) (first : Nat) (tiles : Tiles p) : Prop :=
  ∀ (g : Fin (Packed10.groups p)) (r : Fin 4) (l : Fin 10),
    lane40 (tiles.get g) r l = Packed10.lane
      (Packed10Index.runDot n ((b.val * m + first + r.val) * n)
        (A.toArray.map ExecFloat.Binary.toFloat32)
        (((Packed10.packB batch n p B).get b).get g)) l

theorem Projects_of_row_projection (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (row40 : R11WideRows4.F40 → Fin 4 → Packed10.F10)
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (hlane : ∀ v r l, lane40 v r l = Packed10.lane (row40 v r) l)
    (b : Fin batch) (first : Nat) (tiles : Tiles p)
    (hrows : ∀ g r, row40 (tiles.get g) r =
      Packed10Index.runDot n ((b.val * m + first + r.val) * n)
        (A.toArray.map ExecFloat.Binary.toFloat32)
        (((Packed10.packB batch n p B).get b).get g)) :
    Projects batch m n p A B lane40 b first tiles := by
  intro g r l
  rw [hlane, hrows]

@[inline] def emitRow (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (b : Fin batch) (first : Nat) (tiles : Tiles p)
    (out : Array Binary32) (r : Fin 4) : Array Binary32 :=
  RowStream.emit p (fun j =>
    Packed10.finish n ((b.val * m + first + r.val) * n)
      (b.val * n * p + j.val) p A.toArray B.toArray
      (lane40 (tiles.get (groupFor p j)) r (laneFor p j))) out

theorem finish_lane_eq_point (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (b : Fin batch) (first : Nat) (tiles : Tiles p)
    (hblock : first + 4 ≤ m) (hproj : Projects batch m n p A B lane40 b first tiles)
    (r : Fin 4) (j : Fin p) :
    Packed10.finish n ((b.val * m + first + r.val) * n)
      (b.val * n * p + j.val) p A.toArray B.toArray
      (lane40 (tiles.get (groupFor p j)) r (laneFor p j)) =
      RowStream.point batch m n p A B ((b.val * m + first + r.val) * p + j.val) := by
  have hr := r.isLt
  have hm : 0 < m := by omega
  have hp : 0 < p := Nat.zero_lt_of_lt j.isLt
  have hrow : first + r.val < m := by omega
  have hdiv : (b.val * m + first + r.val) / m = b.val := by
    rw [show b.val * m + first + r.val = b.val * m + (first + r.val) by omega,
      Nat.mul_comm b.val m, Nat.mul_add_div hm, Nat.div_eq_of_lt hrow, Nat.add_zero]
  rw [hproj (groupFor p j) r (laneFor p j), Packed10Index.runDot_eq]
  rw [RowStream.point_row batch m n p A B (b.val * m + first + r.val)
    j.val hm hp j.isLt, hdiv]
  apply Packed10.finish_dot10_lane
  intro k
  have hcol : 10 * (groupFor p j).val + (laneFor p j).val < p := by
    rw [columnFor]
    exact j.isLt
  rw [Packed10.packB_lane batch n p B b (groupFor p j) k (laneFor p j) hcol]
  rw [index_address (b.val * n) k.val p
    (10 * (groupFor p j).val + (laneFor p j).val), columnFor]

theorem emitRow_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (b : Fin batch) (first : Nat) (tiles : Tiles p)
    (hblock : first + 4 ≤ m) (hproj : Projects batch m n p A B lane40 b first tiles)
    (out : Array Binary32) (r : Fin 4)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val * m + first + r.val) * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val * m + first + r.val + 1) * p)
      (emitRow batch m n p A B lane40 b first tiles out r) := by
  have h := RowStream.emit_prefix (RowStream.point batch m n p A B)
    ((b.val * m + first + r.val) * p) p
    (fun j => Packed10.finish n ((b.val * m + first + r.val) * n)
      (b.val * n * p + j.val) p A.toArray B.toArray
      (lane40 (tiles.get (groupFor p j)) r (laneFor p j))) out hout
    (fun j => finish_lane_eq_point batch m n p A B lane40 b first tiles hblock hproj r j)
  simpa only [emitRow, Nat.add_mul, Nat.one_mul] using h

def emitBlock (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (b : Fin batch) (first : Nat) (tiles : Tiles p) (out : Array Binary32) : Array Binary32 :=
  Fin.foldl 4 (emitRow batch m n p A B lane40 b first tiles) out

theorem emitBlock_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (b : Fin batch) (first : Nat) (tiles : Tiles p)
    (hblock : first + 4 ≤ m) (hproj : Projects batch m n p A B lane40 b first tiles)
    (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) ((b.val * m + first) * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((b.val * m + first + 4) * p)
      (emitBlock batch m n p A B lane40 b first tiles out) := by
  exact RowStream.foldl_inv 4 (emitRow batch m n p A B lane40 b first tiles)
    (fun r acc => RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val * m + first + r) * p) acc)
    (fun r acc hacc => by
      simpa only [Nat.add_assoc] using
        emitRow_prefix batch m n p A B lane40 b first tiles hblock hproj acc r hacc)
    out (by simpa only [Nat.add_zero] using hout)

def rowIndex (batch m : Nat) (b : Fin batch) (i : Fin m) : Fin (batch * m) :=
  ⟨b.val * m + i.val, by
    have h := Nat.mul_le_mul_right m b.isLt
    rw [Nat.succ_mul] at h
    omega⟩

/-- Existing Packed10 path handles exactly the remaining zero to three rows.
nativeA and packedB are the same global values used by buildTiles. -/
def emitTail (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (b : Fin batch)
    (nativeA : Array Float32)
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (first : Nat) (out : Array Binary32) : Array Binary32 :=
  Fin.foldl (m - first) (fun acc i =>
    RowStream.row batch m n p A B nativeA packedB acc
      (rowIndex batch m b ⟨first + i.val, by have hi := i.isLt; omega⟩)) out

theorem emitTail_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (b : Fin batch)
    (first : Nat) (hfirst : first ≤ m) (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) ((b.val * m + first) * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((b.val + 1) * m * p)
      (emitTail batch m n p A B b (A.toArray.map ExecFloat.Binary.toFloat32)
        (Packed10.packB batch n p B) first out) := by
  have h := RowStream.foldl_inv (m - first)
    (fun acc i => RowStream.row batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32)
      (Packed10.packB batch n p B) acc
      (rowIndex batch m b ⟨first + i.val, by have hi := i.isLt; omega⟩))
    (fun i acc => RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val * m + first + i) * p) acc)
    (fun i acc hacc => by
      have hrow := RowStream.row_prefix batch m n p A B
        (rowIndex batch m b ⟨first + i.val, by have hi := i.isLt; omega⟩) acc
        (by simpa only [rowIndex, Nat.add_assoc] using hacc)
      simpa only [rowIndex, Nat.add_assoc] using
        hrow)
    out (by simpa only [Nat.add_zero] using hout)
  have hend : b.val * m + first + (m - first) = (b.val + 1) * m := by
    rw [Nat.add_mul, Nat.one_mul]
    omega
  simpa only [emitTail, hend] using h

/-- buildTiles closes over the single global nativeA/packedB preparation.
It returns an evaluated vector once per complete four-row block. -/
def writeBatch (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (nativeA : Array Float32)
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (buildTiles : Fin batch → Fin (m / 4) → Tiles p)
    (out : Array Binary32) (b : Fin batch) : Array Binary32 :=
  let afterBlocks := Fin.foldl (m / 4) (fun acc h =>
    let tiles := buildTiles b h
    emitBlock batch m n p A B lane40 b (4 * h.val) tiles acc) out
  emitTail batch m n p A B b nativeA packedB (4 * (m / 4)) afterBlocks

theorem writeBatch_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (buildTiles : Fin batch → Fin (m / 4) → Tiles p)
    (hproj : ∀ (b : Fin batch) (h : Fin (m / 4)),
      Projects batch m n p A B lane40 b (4 * h.val) (buildTiles b h))
    (out : Array Binary32) (b : Fin batch)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) (b.val * m * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((b.val + 1) * m * p)
      (writeBatch batch m n p A B lane40 (A.toArray.map ExecFloat.Binary.toFloat32)
        (Packed10.packB batch n p B) buildTiles out b) := by
  have hblocks := RowStream.foldl_inv (m / 4)
    (fun acc h => emitBlock batch m n p A B lane40 b (4 * h.val) (buildTiles b h) acc)
    (fun h acc => RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val * m + 4 * h) * p) acc)
    (fun h acc hacc => by
      have hh := h.isLt
      have hblock : 4 * h.val + 4 ≤ m := by omega
      simpa only [Nat.mul_add, Nat.mul_one, Nat.add_assoc] using
        emitBlock_prefix batch m n p A B lane40 b (4 * h.val) (buildTiles b h)
          hblock (hproj b h) acc hacc)
    out (by simpa only [Nat.mul_zero, Nat.add_zero] using hout)
  have hfirst : 4 * (m / 4) ≤ m := by omega
  exact emitTail_prefix batch m n p A B b (4 * (m / 4)) hfirst _ hblocks

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (buildTiles : Array Float32 →
      Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch →
      Fin batch → Fin (m / 4) → Tiles p) : Array Binary32 :=
  let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
  let packedB := Packed10.packB batch n p B
  Fin.foldl batch (writeBatch batch m n p A B lane40 nativeA packedB
    (buildTiles nativeA packedB)) (Array.mkEmpty (batch * m * p))

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (buildTiles : Array Float32 →
      Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch →
      Fin batch → Fin (m / 4) → Tiles p)
    (hproj : ∀ (b : Fin batch) (h : Fin (m / 4)), Projects batch m n p A B lane40 b (4 * h.val)
      (buildTiles (A.toArray.map ExecFloat.Binary.toFloat32) (Packed10.packB batch n p B) b h)) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch * m * p)
      (output batch m n p A B lane40 buildTiles) := by
  exact RowStream.foldl_inv batch
    (writeBatch batch m n p A B lane40 (A.toArray.map ExecFloat.Binary.toFloat32)
      (Packed10.packB batch n p B)
      (buildTiles (A.toArray.map ExecFloat.Binary.toFloat32) (Packed10.packB batch n p B)))
    (fun b acc => RowStream.Prefix (RowStream.point batch m n p A B) (b * m * p) acc)
    (fun b acc hacc => writeBatch_prefix batch m n p A B lane40 _ hproj acc b hacc)
    (Array.mkEmpty (batch * m * p))
    ⟨by simp, by intro j hj; simp at hj⟩

end Submission.R11WideLayout
