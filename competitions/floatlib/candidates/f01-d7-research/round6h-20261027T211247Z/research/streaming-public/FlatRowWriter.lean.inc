/- Exact transport for a flat tail q < rows*p. NOT_RUN. -/
namespace Submission.R22BlockWriter
open FloatLib.Floats Competition

theorem emit_flat_rows_prefix (batch m n p offset rows : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (bi : Fin batch) (hrows : offset + rows ≤ m) (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) ((bi.val * m + offset) * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((bi.val * m + offset + rows) * p)
      (RowStream.emit (rows * p) (fun q => NativeFinal.dot n
        ((bi.val * m + offset + q.val / p) * n)
        (bi.val * n * p + q.val % p) p A.toArray B.toArray) out) := by
  have h := RowStream.emit_prefix (RowStream.point batch m n p A B)
    ((bi.val * m + offset) * p) (rows * p)
    (fun q => NativeFinal.dot n ((bi.val * m + offset + q.val / p) * n)
      (bi.val * n * p + q.val % p) p A.toArray B.toArray) out hout (by
      intro q
      have hp : 0 < p := Nat.pos_of_lt_mul_left q.isLt
      have hquot : q.val / p < rows := (Nat.div_lt_iff_lt_mul hp).2 q.isLt
      have hi : offset + q.val / p < m := by omega
      have hm : 0 < m := by omega
      have hq : (bi.val * m + offset + q.val / p) / m = bi.val := by
        rw [Nat.add_assoc, Nat.mul_comm bi.val m, Nat.mul_add_div hm,
          Nat.div_eq_of_lt hi, Nat.add_zero]
      have hpoint := RowStream.point_row batch m n p A B
        (bi.val * m + offset + q.val / p) (q.val % p) hm hp (Nat.mod_lt q.val hp)
      rw [hq] at hpoint
      have hindex : (bi.val * m + offset + q.val / p) * p + q.val % p =
          (bi.val * m + offset) * p + q.val := by
        rw [Nat.add_mul, Nat.add_assoc, Nat.div_add_mod']
      rw [hindex] at hpoint
      exact hpoint.symm)
  simpa only [Nat.add_mul] using h

end Submission.R22BlockWriter
