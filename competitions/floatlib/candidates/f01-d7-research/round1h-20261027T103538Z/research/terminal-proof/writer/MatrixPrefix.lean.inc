/- R21 post-freeze full writer proof attempt. NOT_RUN.
   Requires B's unchanged matrix driver/ba2dfe46 and streaming pair proof.
   This is a reference-equivalence interface, not a new selected public entry. -/
namespace Submission.R21StreamingMatrix
open FloatLib.Floats Competition

theorem pairStep_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (bi : Fin batch) (g : Fin (m/2)) (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B)
      (bi.val*m*p+2*g.val*p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B)
      ((bi.val*m*p+2*g.val*p)+2*p) (pairStep batch m n p A B bi out g) := by
  have h := R21ConcretePairPrefix.streamed_pair_prefix batch m n p A B bi (2*g.val)
    (R21BatchPairTransport.pair_rows_valid m g) out
    (by simpa only [Nat.add_mul] using hout)
  simpa only [pairStep, Nat.add_mul, Nat.add_assoc] using h

theorem batchStep_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (bi : Fin batch) (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) (bi.val*m*p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((bi.val+1)*m*p)
      (batchStep batch m n p A B out bi) := by
  unfold batchStep oddRow
  have hend : bi.val*m*p+m*p=(bi.val+1)*m*p := by
    simp only [Nat.add_mul, Nat.one_mul]
  rw [← hend]
  refine R21BatchPairTransport.pairs_then_tail_prefix (RowStream.point batch m n p A B)
    (bi.val*m*p) m p (pairStep batch m n p A B bi)
    (fun g acc hacc => pairStep_prefix batch m n p A B bi g acc hacc)
    (fun j => NativeFinal.dot n ((bi.val*m+(m-1))*n)
      (bi.val*n*p+j.val) p A.toArray B.toArray) ?_ out hout
  intro hodd j
  have hm : 0<m := by omega
  have hp : 0<p := Nat.zero_lt_of_lt j.isLt
  have hlast : m-1<m := Nat.sub_lt hm (by decide : 0<1)
  have hq := R21TerminalWriter.batch_row_quotient bi.val m (m-1) hm hlast
  have hpoint := RowStream.point_row batch m n p A B (bi.val*m+(m-1))
    j.val hm hp j.isLt
  rw [hq] at hpoint
  have hlastEq : m-1=2*(m/2) := by
    have h := Nat.div_add_mod m 2
    omega
  simpa only [hlastEq, Nat.add_mul, Nat.add_assoc] using hpoint.symm

theorem matrixOutput_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch*m*p)
      (matrixOutput batch m n p A B) := by
  unfold matrixOutput
  exact RowStream.foldl_inv (β := Array Binary32) batch (batchStep batch m n p A B)
    (fun bi acc => RowStream.Prefix (RowStream.point batch m n p A B) (bi*m*p) acc)
    (fun bi acc hacc => batchStep_prefix batch m n p A B bi acc hacc)
    (Array.mkEmpty (batch*m*p))
    ⟨by simp, by intro j hj; simp at hj⟩

theorem matrixVector_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    (⟨matrixOutput batch m n p A B, (matrixOutput_prefix batch m n p A B).1⟩ :
      Vector Binary32 (batch*m*p)) = referenceBmm batch m n p A B := by
  exact (RowStream.prefix_vector_eq_ofFn (RowStream.point batch m n p A B)
    (batch*m*p) (matrixOutput batch m n p A B) (matrixOutput_prefix batch m n p A B)).trans
    (RowStream.points_eq_reference batch m n p A B)

end Submission.R21StreamingMatrix
