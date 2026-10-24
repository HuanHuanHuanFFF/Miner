/- NOT_RUN future bridge. Requires the compiled Panel4Bridge projection version,
the retained lane40/lane40_eq and the accepted R11WideLayout interfaces.
No active output function or dispatcher is added. -/
namespace Submission.Panel4Bridge
open FloatLib.Floats Competition

theorem block_projects (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (hn : n<USize.size) (b : Fin batch) (first : Nat) :
    R11WideLayout.Projects batch m n p A B R11WideRows4.lane40 b first
      (Panel4.block n p ((b.val*m+first)*n)
        ((b.val*m+first)*n+n) ((b.val*m+first)*n+2*n) ((b.val*m+first)*n+3*n)
        A.toArray ((Packed10.packB batch n p B).get b) hn) := by
  apply R11WideLayout.Projects_of_row_projection batch m n p A B
    R11WideRows4.projectRow R11WideRows4.lane40 R11WideRows4.lane40_eq
  intro g r
  simp only [block_row, baseFor_rows, Nat.add_mul]

end Submission.Panel4Bridge
