theorem r27MYbc_eq : r27MYbc = MYbc := by
  funext rows n eps x gain bias
  unfold r27MYbc MYbc
  split
  · dsimp only
    rw [ZB rows n (rows * n) rfl, ZB rows n (rows * n) rfl]
    congr 1
    funext output
    have row_bound : output.val / n < rows :=
      Nat.div_lt_of_lt_mul (by simpa [Nat.mul_comm] using output.isLt)
    rw [gO rows (fun row => R27Reciprocal.prepare
      ((if n < 4096 then n.toUInt64 else 0) *
        Yf (Array.ofFn (n := rows) (fun r => Y8f x n eps r.val))[row]!.2.2))
      (output.val / n) row_bound]
    rw [r27Ya7G_eq]
  · rfl
