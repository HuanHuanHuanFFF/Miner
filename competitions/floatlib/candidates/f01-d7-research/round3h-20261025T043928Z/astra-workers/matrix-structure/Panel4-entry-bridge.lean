/- R15 proof/entry asset, NOT_COMPILED and not wired into Submission.bmm.
   Reuses exact R11 Panel4, projection, lane40, layout, and factored-tail assets.
   Runtime prepares packed B globally; A is prepared only inside Panel4.block
   or Panel4Tail.tail. Global A.map appears only in proofs and is erased. -/
namespace Submission.R15PanelEntry
open FloatLib.Floats Competition

@[inline] def buildTiles (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (hn : n < USize.size) (b : Fin batch) (h : Fin (m / 4)) :
    R11WideLayout.Tiles p :=
  let base := (b.val * m + 4 * h.val) * n
  Panel4.block n p base (base + n) (base + 2 * n) (base + 3 * n)
    A.toArray (packedB.get b) hn

theorem buildTiles_projects (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (hn : n < USize.size) (b : Fin batch) (h : Fin (m / 4)) :
    R11WideLayout.Projects batch m n p A B R11WideRows4.lane40 b (4 * h.val)
      (buildTiles batch m n p A (Packed10.packB batch n p B) hn b h) := by
  apply R11WideLayout.Projects_of_row_projection batch m n p A B
    R11WideRows4.projectRow R11WideRows4.lane40 R11WideRows4.lane40_eq
  intro g r
  simp only [buildTiles, Panel4Bridge.block_row, Panel4Bridge.baseFor_rows, Nat.add_mul]

@[inline] def writeBatch (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (hn : n < USize.size) (out : Array Binary32) (b : Fin batch) : Array Binary32 :=
  let afterBlocks := Fin.foldl (m / 4) (fun acc h =>
    let tiles := buildTiles batch m n p A packedB hn b h
    R11WideLayout.emitBlock batch m n p A B R11WideRows4.lane40
      b (4 * h.val) tiles acc) out
  Panel4Tail.tail A B packedB b (4 * (m / 4)) afterBlocks

theorem writeBatch_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (hn : n < USize.size) (out : Array Binary32) (b : Fin batch) :
    writeBatch batch m n p A B packedB hn out b =
      R11WideLayout.writeBatch batch m n p A B R11WideRows4.lane40
        (A.toArray.map ExecFloat.Binary.toFloat32) packedB
        (buildTiles batch m n p A packedB hn) out b := by
  unfold writeBatch R11WideLayout.writeBatch
  exact Panel4Tail.tail_eq A B packedB b (4 * (m / 4)) _

theorem writeBatch_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (hn : n < USize.size) (out : Array Binary32) (b : Fin batch)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) (b.val * m * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((b.val + 1) * m * p)
      (writeBatch batch m n p A B (Packed10.packB batch n p B) hn out b) := by
  rw [writeBatch_eq]
  exact R11WideLayout.writeBatch_prefix batch m n p A B R11WideRows4.lane40
    (buildTiles batch m n p A (Packed10.packB batch n p B) hn)
    (fun bb h => buildTiles_projects batch m n p A B hn bb h) out b hout

@[inline] def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n < USize.size) : Array Binary32 :=
  let packedB := Packed10.packB batch n p B
  Fin.foldl batch (writeBatch batch m n p A B packedB hn)
    (Array.mkEmpty (batch * m * p))

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n < USize.size) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch * m * p)
      (output batch m n p A B hn) := by
  exact RowStream.foldl_inv batch
    (writeBatch batch m n p A B (Packed10.packB batch n p B) hn)
    (fun b acc => RowStream.Prefix (RowStream.point batch m n p A B) (b * m * p) acc)
    (fun b acc hacc => writeBatch_prefix batch m n p A B hn acc b hacc)
    (Array.mkEmpty (batch * m * p))
    ⟨by simp, by intro j hj; simp at hj⟩

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n < USize.size) :
    Vector Binary32 (batch * m * p) :=
  ⟨output batch m n p A B hn, (output_prefix batch m n p A B hn).1⟩

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n < USize.size) :
    core batch m n p A B hn = referenceBmm batch m n p A B := by
  exact (RowStream.prefix_vector_eq_ofFn (RowStream.point batch m n p A B)
    (batch * m * p) (output batch m n p A B hn) (output_prefix batch m n p A B hn)).trans
    (RowStream.points_eq_reference batch m n p A B)

end Submission.R15PanelEntry
