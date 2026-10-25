/- Source-level proof attempts for development-word-add-runtime2.lean.
   NOT_COMPILED; no full add_spec or final candidate is claimed. -/
namespace Submission.R14WordAdd

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

theorem normal_field (u : UInt32)
    (h : R14ExponentShift.ex u - 1 ≤ (253 : UInt32)) :
    0 < R2W01c.wordExp u ∧ R2W01c.wordExp u < 255 := by
  have hb := R14ExponentShift.ex_bound u
  rw [UInt32.le_iff_toNat_le, UInt32.toNat_sub] at h
  change (4294967295 + (R14ExponentShift.ex u).toNat) % 4294967296 ≤ 253 at h
  rw [R14ExponentShift.ex_nat] at h hb
  omega

theorem sorted_exponents (u v : UInt32) :
    R2W01c.wordExp (high u v) = max (R2W01c.wordExp u) (R2W01c.wordExp v) ∧
    R2W01c.wordExp (low u v) = min (R2W01c.wordExp u) (R2W01c.wordExp v) := by
  by_cases h : R14ExponentShift.ex u < R14ExponentShift.ex v
  · have hn : R2W01c.wordExp u < R2W01c.wordExp v := by
      have hh := UInt32.lt_iff_toNat_lt.mp h
      simpa only [R14ExponentShift.ex_nat] using hh
    simp only [high, low, if_pos h]
    exact ⟨(Nat.max_eq_right (Nat.le_of_lt hn)).symm,
      (Nat.min_eq_left (Nat.le_of_lt hn)).symm⟩
  · have hn : R2W01c.wordExp v ≤ R2W01c.wordExp u := by
      have hh : ¬ (R14ExponentShift.ex u).toNat < (R14ExponentShift.ex v).toNat := by
        simpa only [UInt32.lt_iff_toNat_lt] using h
      rw [R14ExponentShift.ex_nat, R14ExponentShift.ex_nat] at hh
      omega
    simp only [high, low, if_neg h]
    exact ⟨(Nat.max_eq_left hn).symm, (Nat.min_eq_right hn).symm⟩

theorem gap_nat (u v : UInt32) :
    (gap u v).toNat = max (R2W01c.wordExp u) (R2W01c.wordExp v) -
      min (R2W01c.wordExp u) (R2W01c.wordExp v) := by
  have hs := sorted_exponents u v
  have hle : R14ExponentShift.ex (low u v) ≤ R14ExponentShift.ex (high u v) := by
    rw [UInt32.le_iff_toNat_le, R14ExponentShift.ex_nat, R14ExponentShift.ex_nat, hs.1, hs.2]
    exact Nat.le_trans (Nat.min_le_left _ _) (Nat.le_max_left _ _)
  rw [gap, UInt32.toNat_sub_of_le _ _ hle, R14ExponentShift.ex_nat,
    R14ExponentShift.ex_nat, hs.1, hs.2]

theorem sameSign_eq (u v : UInt32) :
    sameSign u v = (R2W01c.wordSign u == R2W01c.wordSign v) := by
  rw [sameSign, R14ExponentShift.sign_eq]
  cases R2W01c.wordSign u <;> cases R2W01c.wordSign v <;> rfl

theorem sameSign_true (u v : UInt32) (h : sameSign u v = true) :
    R2W01c.wordSign u = R2W01c.wordSign v := by
  rw [sameSign_eq, beq_iff_eq] at h
  exact h

theorem eligible_conditions (u v : UInt32) (h : eligible u v = true) :
    (0 < R2W01c.wordExp u ∧ R2W01c.wordExp u < 255) ∧
    (0 < R2W01c.wordExp v ∧ R2W01c.wordExp v < 255) ∧
    (gap u v).toNat ≤ 7 ∧
    (R2W01c.wordSign u = R2W01c.wordSign v ∨ 2 ≤ (gap u v).toNat) := by
  simp only [eligible, Bool.and_eq_true, Bool.or_eq_true, decide_eq_true_eq] at h
  rcases h with ⟨⟨hu, hv⟩, hg, hs⟩
  refine ⟨normal_field u hu, normal_field v hv, ?_, ?_⟩
  · have hh := UInt32.le_iff_toNat_le.mp hg
    exact hh
  · rcases hs with hs | hs
    · exact Or.inl (sameSign_true u v hs)
    · have hh := UInt32.le_iff_toNat_le.mp hs
      exact Or.inr hh

end Submission.R14WordAdd
