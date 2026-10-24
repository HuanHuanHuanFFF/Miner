def bmmWithR11Cross (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*p)) : Vector Binary32 (batch*m*p) :=
  if h : p=2 ∧ 4≤batch*m ∧ 0<n ∧ n<USize.size ∧
      A.toArray.size<USize.size ∧ B.toArray.size<USize.size ∧ batch*m*p<USize.size then
    R11CrossRows.core batch m n p A B h.2.2.2.1 (Nat.le_of_eq h.1)
  else bmmBeforeWideRows batch m n p A B

theorem bmmWithR11Cross_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*p)),
    (bmmWithR11Cross batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold bmmWithR11Cross
  split
  · rw [R11CrossRows.core_eq_rows, DirectRows.core_eq, DirectSmall.core_eq_reference]
    exact referenceBmm_spec batch m n p A B
  · exact bmmBeforeWideRows_spec batch m n p A B

