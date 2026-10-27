/- R21 writer interface, NOT_RUN. Requires exact R20 WideRowRefinement/dd00510c.
   No runtime implementation or public dispatcher is changed. -/
namespace Submission.R21TerminalWriter
open FloatLib.Floats Competition
open R20WideRowRefinement (storageLoop)

theorem emit_finish_eq {S : Type} (n columns p baseA baseB : Nat)
    (A B : Array Binary32) (view : S → Fin columns → Float32) (step : Nat → S → S)
    (hstep : ∀ (k : Nat), k<n → ∀ (s : S) (j : Fin columns),
      view (step k s) j = view s j +
        ExecFloat.Binary.toFloat32 (A.getD (baseA+k) posZero) *
        ExecFloat.Binary.toFloat32 (B.getD (baseB+j.val+k*p) posZero))
    (initial : S) (hzero : ∀ j : Fin columns, view initial j = Packed10.zero32)
    (out : Array Binary32) :
    RowStream.emit columns (fun j =>
      Packed10.finish n baseA (baseB+j.val) p A B
        (view (storageLoop n step 0 initial) j)) out =
      RowStream.emit columns (fun j => NativeFinal.dot n baseA (baseB+j.val) p A B) out := by
  apply congrArg (fun read : Fin columns → Binary32 => RowStream.emit columns read out)
  funext j
  exact R20WideRowRefinement.finish_lane n columns p baseA baseB A B view step
    hstep initial hzero j

/-- First row is completely emitted before the second row. -/
theorem emit_two_rows_eq (p : Nat) (read0 read1 ref0 ref1 : Fin p → Binary32)
    (h0 : ∀ j, read0 j=ref0 j) (h1 : ∀ j, read1 j=ref1 j)
    (out : Array Binary32) :
    RowStream.emit p read1 (RowStream.emit p read0 out) =
      RowStream.emit p ref1 (RowStream.emit p ref0 out) := by
  have e0 : read0=ref0 := funext h0
  have e1 : read1=ref1 := funext h1
  rw [e0, e1]

/-- Output-size/order transport, valid also for p=0. -/
theorem emit_two_rows_prefix (f : Nat → Binary32) (start p : Nat)
    (read0 read1 : Fin p → Binary32) (out : Array Binary32)
    (hout : RowStream.Prefix f start out)
    (h0 : ∀ j, read0 j=f (start+j.val))
    (h1 : ∀ j, read1 j=f (start+p+j.val)) :
    RowStream.Prefix f (start+2*p)
      (RowStream.emit p read1 (RowStream.emit p read0 out)) := by
  have first := RowStream.emit_prefix f start p read0 out hout h0
  have second := RowStream.emit_prefix f (start+p) p read1
    (RowStream.emit p read0 out) first h1
  have hlen : (start+p)+p=start+2*p := by omega
  simpa only [hlen] using second

theorem batch_row_quotient (bi m i : Nat) (hm : 0<m) (hi : i<m) :
    (bi*m+i)/m=bi := by
  rw [Nat.mul_comm bi m, Nat.mul_add_div hm, Nat.div_eq_of_lt hi, Nat.add_zero]

theorem paired_rows_same_batch (bi m i : Nat) (hm : 0<m) (hi : i+1<m) :
    (bi*m+i)/m=bi ∧ (bi*m+i+1)/m=bi := by
  constructor
  · exact batch_row_quotient bi m i hm (by omega)
  · simpa only [Nat.add_assoc] using batch_row_quotient bi m (i+1) hm hi

theorem adjacent_A_base (r n : Nat) : (r+1)*n=r*n+n := by
  simp only [Nat.add_mul, Nat.one_mul]

end Submission.R21TerminalWriter
