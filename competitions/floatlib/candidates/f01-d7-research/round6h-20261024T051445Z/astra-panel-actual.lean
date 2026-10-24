namespace Submission.R11WideActual
open FloatLib.Floats Competition
@[inline] def buildTiles (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (hn : n<USize.size)
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (b : Fin batch) (h : Fin (m/4)) : R11WideLayout.Tiles p :=
  let base := (b.val*m+4*h.val)*n
  Panel4.block n p base (base+n) (base+2*n) (base+3*n) A.toArray (packedB.get b) hn
theorem buildTiles_projects (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (hn : n<USize.size) (b : Fin batch) (h : Fin (m/4)) :
    R11WideLayout.Projects batch m n p A B R11WideRows4.lane40 b (4*h.val)
      (buildTiles batch m n p A hn (Packed10.packB batch n p B) b h) := by
  apply R11WideLayout.Projects_of_row_projection batch m n p A B
    R11WideRows4.projectRow R11WideRows4.lane40 R11WideRows4.lane40_eq
  intro g r
  simp only [buildTiles,Panel4Bridge.block_row,Panel4Bridge.baseFor_rows,Nat.add_mul]
@[inline] def output (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) (hn : n<USize.size) : Array Binary32 :=
  R11WideLayout.output batch m n p A B R11WideRows4.lane40 (buildTiles batch m n p A hn)
theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) (hn : n<USize.size) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch*m*p) (output batch m n p A B hn) := by
  exact R11WideLayout.output_prefix batch m n p A B R11WideRows4.lane40
    (buildTiles batch m n p A hn) (buildTiles_projects batch m n p A B hn)
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
end Submission.R11WideActual
