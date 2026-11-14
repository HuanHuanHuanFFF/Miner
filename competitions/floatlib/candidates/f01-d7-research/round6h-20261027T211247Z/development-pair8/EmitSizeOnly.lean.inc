
namespace Submission.R21StreamingPair
open FloatLib.Floats Competition
theorem emit_size (p : Nat) (read : Fin p → Binary32) (out : Array Binary32) :
    (RowStream.emit p read out).size = out.size + p := by
  unfold RowStream.emit
  exact RowStream.foldl_inv (β := Array Binary32) p
    (fun (acc : Array Binary32) (j : Fin p) => acc.push (read j))
    (fun k (acc : Array Binary32) => acc.size = out.size + k)
    (by
      intro j acc h
      simp only [Array.size_push, h]
      omega)
    out (by omega)

end Submission.R21StreamingPair
