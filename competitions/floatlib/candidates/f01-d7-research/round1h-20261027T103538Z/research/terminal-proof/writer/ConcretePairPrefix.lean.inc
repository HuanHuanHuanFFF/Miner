/- R21 post-freeze proof-only integration interface. NOT_RUN.
   Requires R21StreamingPair.streamedRows_eq_control and WriterTransport/fb9e9abe.
   The actual streaming runtime remains owned by representation worker. -/
namespace Submission.R21ConcretePairPrefix
open FloatLib.Floats Competition

theorem streamed_pair_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (bi : Fin batch) (i : Nat) (hi : i+1<m) (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) ((bi.val*m+i)*p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((bi.val*m+i+2)*p)
      (R21StreamingPair.streamedRows p n ((bi.val*m+i)*n) ((bi.val*m+i+1)*n)
        (bi.val*n*p) A.toArray B.toArray out) := by
  let r := bi.val*m+i
  have hm : 0<m := by omega
  have hq0 : r/m=bi.val := by
    exact R21TerminalWriter.batch_row_quotient bi.val m i hm (by omega)
  have hq1 : (r+1)/m=bi.val := by
    exact (R21TerminalWriter.paired_rows_same_batch bi.val m i hm hi).2
  change RowStream.Prefix (RowStream.point batch m n p A B) ((r+2)*p)
    (R21StreamingPair.streamedRows p n (r*n) ((r+1)*n)
      (bi.val*n*p) A.toArray B.toArray out)
  rw [R21StreamingPair.streamedRows_eq_control]
  unfold R21StreamingPair.controlRows
  have hcursor : r*p+2*p=(r+2)*p := by rw [Nat.add_mul]
  rw [← hcursor]
  refine R21TerminalWriter.emit_two_rows_prefix (RowStream.point batch m n p A B)
    (r*p) p
    (fun j => NativeFinal.dot n (r*n) (bi.val*n*p+j.val) p A.toArray B.toArray)
    (fun j => NativeFinal.dot n ((r+1)*n) (bi.val*n*p+j.val) p A.toArray B.toArray)
    out hout ?_ ?_
  · intro j
    have hp : 0<p := Nat.zero_lt_of_lt j.isLt
    have hpoint := RowStream.point_row batch m n p A B r j.val hm hp j.isLt
    rw [hq0] at hpoint
    exact hpoint.symm
  · intro j
    have hp : 0<p := Nat.zero_lt_of_lt j.isLt
    have hpoint := RowStream.point_row batch m n p A B (r+1) j.val hm hp j.isLt
    rw [hq1] at hpoint
    simpa only [Nat.add_mul, Nat.one_mul, Nat.add_assoc] using hpoint.symm

end Submission.R21ConcretePairPrefix
