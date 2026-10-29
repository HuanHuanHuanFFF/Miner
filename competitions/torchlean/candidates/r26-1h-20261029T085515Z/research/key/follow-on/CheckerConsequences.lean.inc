namespace Submission.R26CheckerConsequences
open Submission.R25OrderKey Submission.R25Checker

private theorem negative_of_nat_lt (w : UInt64)
    (hw : w.toNat < 9223372036854775808) : negative w = false := by
  simp [negative]
  omega

private theorem negative_or_sign (w : UInt64)
    (hw : w.toNat < 9223372036854775808) :
    negative (w ||| 0x8000000000000000) = true := by
  have hp : w.toNat < 2 ^ 63 := hw
  have hn : (w ||| 0x8000000000000000).toNat =
      w.toNat + 9223372036854775808 := by
    rw [UInt64.toNat_or]
    exact Nat.or_two_pow_eq_add_of_lt hp
  simp only [negative, hn, decide_eq_true_eq]
  omega

/-- Normality guards force both actual raw midpoint signs to match q. -/
theorem midpoint_signs (q : UInt32) (he0 : eWord q ≠ 0) (he255 : eWord q ≠ 255) :
    negative (lowerWord q) = negative32 q ∧
    negative (upperWord q) = negative32 q := by
  have hb := unsigned_bounds q he0 he255
  have hlo : (below q).toNat < 9223372036854775808 := by omega
  have hhi : (above q).toNat < 9223372036854775808 := by omega
  cases hs : negative32 q <;>
    simp only [lowerWord, upperWord, hs, Bool.false_eq_true, ite_false, ite_true]
  · exact ⟨negative_of_nat_lt _ hlo, negative_of_nat_lt _ hhi⟩
  · exact ⟨negative_or_sign _ hhi, negative_or_sign _ hlo⟩

/-- Strict containment follows from the executable acceptance expression. -/
theorem accepted_contains_exact (s r : Float) (sw : UInt64) (q : UInt32) (S : Real)
    (henc : nativeValue (s - r) ≤ S ∧ S ≤ nativeValue (s + r))
    (hacc : certify s r sw q = true) :
    value (lowerWord q) < S ∧ S < value (upperWord q) := by
  have h := accepted_native_bounds s r sw q hacc
  exact ⟨lt_of_lt_of_le h.1 henc.1, lt_of_le_of_lt henc.2 h.2⟩

/-- A normal proposal accepted by this checker cannot enclose an exact zero.
The nonzero result is derived from the guard and enclosure, not assumed. -/
theorem accepted_exact_nonzero (s r : Float) (sw : UInt64) (q : UInt32) (S : Real)
    (henc : nativeValue (s - r) ≤ S ∧ S ≤ nativeValue (s + r))
    (hacc : certify s r sw q = true) : S ≠ 0 := by
  obtain ⟨he0, he255, _⟩ := accepted_components s r sw q hacc
  obtain ⟨hlf, huf, hlnz, hunz⟩ := midpoint_finite_nonzero q he0 he255
  have hs := midpoint_signs q he0 he255
  have hp := (magnitudeReal_pos_iff (magnitude (lowerWord q))).mpr hlnz
  have hn := (magnitudeReal_pos_iff (magnitude (upperWord q))).mpr hunz
  have hc := accepted_contains_exact s r sw q S henc hacc
  rw [raw_value _ hlf, raw_value _ huf, hs.1, hs.2] at hc
  cases hsign : negative32 q <;> simp only [hsign, Bool.false_eq_true, ite_false, ite_true] at hc <;>
    intro hz <;> subst S <;> linarith

/-- The actual integer total is nonzero whenever its scaled real value is
certified. No correctness premise about the proposal itself is needed. -/
theorem accepted_total_nonzero (s r : Float) (sw : UInt64) (q : UInt32) (T e : Int)
    (henc : nativeValue (s - r) ≤ (T : Real) * (2 : Real) ^ e ∧
      (T : Real) * (2 : Real) ^ e ≤ nativeValue (s + r))
    (hacc : certify s r sw q = true) : T ≠ 0 := by
  have hn := accepted_exact_nonzero s r sw q ((T : Real) * (2 : Real) ^ e) henc hacc
  intro hz
  apply hn
  simp [hz]

end Submission.R26CheckerConsequences
