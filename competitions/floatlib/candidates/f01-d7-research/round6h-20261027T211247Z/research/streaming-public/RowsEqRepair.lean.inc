theorem rows_eq_batchStep (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (bi : Fin batch) (out : Array Binary32) :
    rows m n p bi.val A.toArray B.toArray out =
      R21StreamingMatrix.batchStep batch m n p A B out bi := by
  have hpairs : pairs m n p bi.val A.toArray B.toArray out =
      Fin.foldl (m / 2) (R21StreamingMatrix.pairStep batch m n p A B bi) out := rfl
  have emit_len (len len' base : Nat) (h : len = len') (acc : Array Binary32) :
      RowStream.emit len (fun j => NativeFinal.dot n base
        (bi.val * n * p + j.val) p A.toArray B.toArray) acc =
      RowStream.emit len' (fun j => NativeFinal.dot n base
        (bi.val * n * p + j.val) p A.toArray B.toArray) acc := by
    cases h
    rfl
  dsimp only [rows, R21StreamingMatrix.batchStep, R21StreamingMatrix.oddRow]
  rw [hpairs]
  by_cases hodd : m % 2 = 1
  · rw [if_pos hodd]
    have hm : 0 < m := by omega
    have haddr : bi.val * m + m - 1 = bi.val * m + (m - 1) := by omega
    rw [haddr]
    exact emit_len (m % 2 * p) p _ (by rw [hodd, Nat.one_mul]) _
  · rw [if_neg hodd]
    have hrem : m % 2 = 0 := by
      have hlt := Nat.mod_lt m (by decide : 0 < 2)
      omega
    calc
      _ = RowStream.emit 0 (fun j => NativeFinal.dot n ((bi.val * m + m - 1) * n)
          (bi.val * n * p + j.val) p A.toArray B.toArray)
          (Fin.foldl (m / 2) (R21StreamingMatrix.pairStep batch m n p A B bi) out) :=
        emit_len (m % 2 * p) 0 _ (by rw [hrem, Nat.zero_mul]) _
      _ = _ := rfl
