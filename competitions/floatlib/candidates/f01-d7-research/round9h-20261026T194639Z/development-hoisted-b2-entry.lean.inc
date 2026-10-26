/- R19 hoisted indexing entry draft. Insert after R15PackedB2.row_eq,
   immediately before output. Proof arguments erase; no new data preparation. -/
namespace Indexed

theorem row_last_lt (batch m n : Nat) (hn : 0 < n)
    (A : Vector Binary32 (batch * m * n)) (r : Fin (batch * m)) :
    r.val * n + (n - 1) < A.toArray.size := by
  rw [A.size_toArray]
  have h := Nat.mul_le_mul_right n (Nat.succ_le_of_lt r.isLt)
  simp only [Nat.succ_mul, Nat.add_mul, Nat.one_mul] at h
  omega

@[inline] def rowDot (batch m n : Nat) (A : Vector Binary32 (batch * m * n))
    (hn : 0 < n) (hAS : A.toArray.size < USize.size)
    (r : Fin (batch * m)) (B : Vector B2 n) : R15ThinPairs.F2 :=
  have hA := row_last_lt batch m n hn A r
  have hnword : n < USize.size := by omega
  have hbase : r.val * n < USize.size := by omega
  within n (r.val * n) A.toArray B hnword hbase hA hAS

theorem rowDot_eq (batch m n : Nat) (A : Vector Binary32 (batch * m * n))
    (hn : 0 < n) (hAS : A.toArray.size < USize.size)
    (r : Fin (batch * m)) (B : Vector B2 n) :
    rowDot batch m n A hn hAS r B =
      loop n (r.val * n) A.toArray B 0 Packed10.zero32 Packed10.zero32 := by
  unfold rowDot
  exact within_eq _ _ _ _ _ _ _ _

end Indexed

@[inline] def groupWithin (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (hn : 0 < n) (hAS : A.toArray.size < USize.size)
    (packedB : Vector (Vector B2 n) (batch * R15ThinPairs.groups p))
    (r : Fin (batch * m)) (out : Array Binary32) (g : Fin (R15ThinPairs.groups p)) :
    Array Binary32 :=
  have hm : 0 < m := Nat.pos_of_lt_mul_left r.isLt
  let b : Fin batch := ⟨r.val / m, (Nat.div_lt_iff_lt_mul hm).2 r.isLt⟩
  let baseA := r.val * n
  let baseB := b.val * n * p + 2 * g.val
  let result := Indexed.rowDot batch m n A hn hAS r (packedB.get (tileIndex batch p b g))
  let count := min 2 (p - 2 * g.val)
  RowStream.emit count (fun l =>
    Packed10.finish n baseA (baseB + l.val) p A.toArray B.toArray
      (R15ThinPairs.select result l.val)) out

theorem groupWithin_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (hn : 0 < n) (hAS : A.toArray.size < USize.size)
    (packedB : Vector (Vector B2 n) (batch * R15ThinPairs.groups p))
    (r : Fin (batch * m)) (out : Array Binary32) (g : Fin (R15ThinPairs.groups p)) :
    groupWithin batch m n p A B hn hAS packedB r out g =
      group batch m n p A B packedB r out g := by
  simp only [groupWithin, group, Indexed.rowDot_eq]

@[inline] def rowWithin (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (hn : 0 < n) (hAS : A.toArray.size < USize.size)
    (packedB : Vector (Vector B2 n) (batch * R15ThinPairs.groups p))
    (out : Array Binary32) (r : Fin (batch * m)) : Array Binary32 :=
  Fin.foldl (R15ThinPairs.groups p) (groupWithin batch m n p A B hn hAS packedB r) out

theorem rowWithin_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (hn : 0 < n) (hAS : A.toArray.size < USize.size)
    (packedB : Vector (Vector B2 n) (batch * R15ThinPairs.groups p))
    (out : Array Binary32) (r : Fin (batch * m)) :
    rowWithin batch m n p A B hn hAS packedB out r =
      row batch m n p A B packedB out r := by
  unfold rowWithin row
  apply congrArg (fun step : Array Binary32 → Fin (R15ThinPairs.groups p) → Array Binary32 =>
    Fin.foldl (R15ThinPairs.groups p) step out)
  funext acc g
  exact groupWithin_eq batch m n p A B hn hAS packedB r acc g

