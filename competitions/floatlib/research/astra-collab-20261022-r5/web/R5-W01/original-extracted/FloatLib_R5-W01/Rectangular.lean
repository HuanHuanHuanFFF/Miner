import ContractTensor

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
