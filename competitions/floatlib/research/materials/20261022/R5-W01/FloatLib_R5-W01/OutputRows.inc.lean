namespace Submission.OutputRows

def rowIndex {rows cols : Nat} (q : Fin (rows * cols)) : Fin rows :=
  ⟨q.val / cols,
    (Nat.div_lt_iff_lt_mul (Nat.pos_of_lt_mul_left q.isLt)).2 q.isLt⟩

def colIndex {rows cols : Nat} (q : Fin (rows * cols)) : Fin cols :=
  ⟨q.val % cols, Nat.mod_lt q.val (Nat.pos_of_lt_mul_left q.isLt)⟩

/-- Materialize the rows, then concatenate them in row order. -/
def rowsOfFn {α : Type} (rows cols : Nat)
    (f : Fin rows → Fin cols → α) : Vector α (rows * cols) :=
  (Vector.ofFn (fun i : Fin rows => Vector.ofFn (f i))).flatten

theorem rowsOfFn_getElem {α : Type} {rows cols : Nat}
    (f : Fin rows → Fin cols → α) (q : Nat) (hq : q < rows * cols) :
    (rowsOfFn rows cols f)[q]'hq =
      f (rowIndex ⟨q, hq⟩) (colIndex ⟨q, hq⟩) := by
  simp only [rowsOfFn, Vector.getElem_flatten, Vector.getElem_ofFn,
    rowIndex, colIndex]

theorem rowsOfFn_get {α : Type} {rows cols : Nat}
    (f : Fin rows → Fin cols → α) (q : Fin (rows * cols)) :
    (rowsOfFn rows cols f).get q = f (rowIndex q) (colIndex q) := by
  change (rowsOfFn rows cols f)[q.val]'q.isLt = _
  exact rowsOfFn_getElem f q.val q.isLt

theorem rowsOfFn_eq_ofFn {α : Type} (rows cols : Nat)
    (f : Fin rows → Fin cols → α) :
    rowsOfFn rows cols f =
      Vector.ofFn (fun q : Fin (rows * cols) => f (rowIndex q) (colIndex q)) := by
  apply Vector.ext
  intro q hq
  simp only [rowsOfFn_getElem, Vector.getElem_ofFn]

end Submission.OutputRows

namespace Submission.Packed10OutputRows

open FloatLib.Floats Competition

def outputRows (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (tiles : Vector (Vector (Vector Packed10.F10 (Packed10.groups p)) m) batch) :
    Vector Binary32 (batch * m * p) :=
  let Araw := A.toArray
  let Braw := B.toArray
  let batches : Vector (Vector Binary32 (m * p)) batch :=
    Vector.ofFn fun b =>
      let batchTiles := tiles.get b
      let aBatch := b.val * m
      let bBatch := b.val * n * p
      OutputRows.rowsOfFn m p fun i =>
        let rowTiles := batchTiles.get i
        let baseA := (aBatch + i.val) * n
        fun j =>
          let g : Fin (Packed10.groups p) :=
            ⟨j.val / 10, Packed10.groups_pos_of_col p j.val j.isLt⟩
          let l : Fin 10 := ⟨j.val % 10, Nat.mod_lt _ (by decide)⟩
          Packed10.finish n baseA (bBatch + j.val) p Araw Braw
            (Packed10.lane (rowTiles.get g) l)
  batches.flatten.cast (Nat.mul_assoc batch m p).symm

theorem outputRows_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (tiles : Vector (Vector (Vector Packed10.F10 (Packed10.groups p)) m) batch) :
    outputRows batch m n p A B tiles =
      Vector.ofFn (Packed10.outputFromTiles batch m n p A B tiles) := by
  apply Vector.ext
  intro q hq
  have hp : p ≠ 0 := by
    intro hp
    simp [hp] at hq
  have hmp : m * p ≠ 0 := by
    intro hmp
    have hq' : q < batch * (m * p) := by
      simpa only [Nat.mul_assoc] using hq
    simp [hmp] at hq'
  simp only [outputRows, OutputRows.rowsOfFn, Vector.getElem_cast,
    Vector.getElem_flatten, Vector.getElem_ofFn,
    Packed10.outputFromTiles, Packed10.inlineDecodeC, hmp, hp, if_false]

def coreRows (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
  let packedB := Packed10.packB batch n p B
  let tiles := Packed10.tileResults batch m n p nativeA packedB
  outputRows batch m n p A B tiles

theorem coreRows_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    coreRows batch m n p A B = Packed10.core batch m n p A B := by
  unfold coreRows Packed10.core
  dsimp only
  exact outputRows_eq batch m n p A B _

theorem coreRows_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    coreRows batch m n p A B = referenceBmm batch m n p A B := by
  exact (coreRows_eq batch m n p A B).trans
    (Packed10.core_eq_reference batch m n p A B)

def bmmRows (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if batch * m * p = 0 then referenceBmm batch m n p A B
  else if n = 0 then referenceBmm batch m n p A B
  else coreRows batch m n p A B

theorem bmmRows_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    bmmRows batch m n p A B = referenceBmm batch m n p A B := by
  unfold bmmRows
  split
  · rfl
  · split
    · rfl
    · exact coreRows_eq_reference batch m n p A B

theorem bmmRows_spec : ∀ (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmmRows batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  rw [bmmRows_eq_reference]
  exact referenceBmm_spec batch m n p A B

end Submission.Packed10OutputRows
