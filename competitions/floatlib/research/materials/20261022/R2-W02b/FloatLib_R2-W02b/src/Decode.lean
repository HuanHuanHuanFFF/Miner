namespace Packed4

open Competition

/-- Every inhabited row-major output index decodes to valid tensor coordinates. -/
theorem decode_bounds (batch m p : Nat) (q : Fin (batch * m * p)) :
    (bmmDecodeC m p q.val).1 < batch ∧
      (bmmDecodeC m p q.val).2.1 < m ∧
      (bmmDecodeC m p q.val).2.2 < p := by
  have hq : q.val < batch * (m * p) := by
    simpa only [Nat.mul_assoc] using q.isLt
  have hmp : m * p ≠ 0 := by
    intro h
    rw [h, Nat.mul_zero] at hq
    omega
  have hp : p ≠ 0 := by
    intro h
    apply hmp
    simp only [h, Nat.mul_zero]
  have hmpPos : 0 < m * p := by omega
  have hpPos : 0 < p := by omega
  simp only [bmmDecodeC, hmp, hp, if_false]
  refine ⟨?_, ?_, ?_⟩
  · exact (Nat.div_lt_iff_lt_mul hmpPos).2 hq
  · exact (Nat.div_lt_iff_lt_mul hpPos).2 (Nat.mod_lt q.val hmpPos)
  · exact Nat.mod_lt _ hpPos

end Packed4
