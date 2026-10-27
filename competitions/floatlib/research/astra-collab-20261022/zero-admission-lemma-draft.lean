import ContractTensor

namespace Submission.ZeroAdmission

/-- Unsigned subtraction admits zero and the normal-scale interval together. -/
theorem admitted_word (a : UInt32) :
    ((0x0bffffff : UInt32) ≤ a - 1 ∧ a < (0x7f800000 : UInt32)) ↔
      a = 0 ∨ ((0x0c000000 : UInt32) ≤ a ∧ a < (0x7f800000 : UInt32)) := by
  by_cases hz : a = 0
  · subst a
    decide
  · have hn : a.toNat ≠ 0 := by
      intro h
      apply hz
      apply UInt32.toNat_inj.mp
      exact h
    have h1 : (1 : UInt32) ≤ a := by
      rw [UInt32.le_iff_toNat_le]
      change 1 ≤ a.toNat
      omega
    have hsub := UInt32.toNat_sub_of_le a 1 h1
    simp only [hz, false_or]
    simp only [UInt32.le_iff_toNat_le, UInt32.lt_iff_toNat_lt, hsub]
    change (201326591 ≤ a.toNat - 1 ∧ a.toNat < 2139095040) ↔
      (201326592 ≤ a.toNat ∧ a.toNat < 2139095040)
    omega

end Submission.ZeroAdmission
