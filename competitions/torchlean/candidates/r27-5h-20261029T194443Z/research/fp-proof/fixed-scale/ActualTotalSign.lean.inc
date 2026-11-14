/- Append only after the exact guarded checker source has passed. This is a
consumer refinement, not a replacement premise for the complete kernel. -/
namespace Submission.R27GuardedEndpoints
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange
open Submission.R25OrderKey Submission.R25Checker

/-- Acceptance fixes the sign of the real integer total, even though a rounded
endpoint need not enclose that total. The fixed-point monotonicity bridge is used. -/
theorem actual_accepted_total_sign (s r : Float) (q : UInt32) (T e : Int)
    (hr : r.isFinite = true)
    (herr : |nativeValue s - (T : Real) * (2 : Real) ^ e| ≤ nativeValue r)
    (hacc : Submission.R24PortableF64.certify s r s.toBits q = true) :
    decide (T < 0) = negative32 q := by
  have ha : certify s r s.toBits q = true := by
    simpa only [certify_eq_runtime] using hacc
  obtain ⟨he0, he255, _⟩ := accepted_components s r s.toBits q ha
  obtain ⟨hlf, huf, hlnz, hunz⟩ := midpoint_finite_nonzero q he0 he255
  have hsigns := Submission.R26CheckerConsequences.midpoint_signs q he0 he255
  have hp := (magnitudeReal_pos_iff (magnitude (lowerWord q))).mpr hlnz
  have hn := (magnitudeReal_pos_iff (magnitude (upperWord q))).mpr hunz
  have hc := actual_acceptance_contains_exact_of_error s r q
    ((T : Real) * (2 : Real) ^ e) hr herr hacc
  have he : 0 < (2 : Real) ^ e := zpow_pos (by norm_num) e
  rw [raw_value _ hlf, raw_value _ huf, hsigns.1, hsigns.2] at hc
  cases hsign : negative32 q
  · simp only [hsign, Bool.false_eq_true, ite_false] at hc
    have ht : ¬ T < 0 := by
      intro ht
      have htr : (T : Real) < 0 := by exact_mod_cast ht
      nlinarith [hc.1]
    simp only [ht, decide_false]
  · simp only [hsign, ite_true] at hc
    have htr : (T : Real) < 0 := by nlinarith [hc.2]
    have ht : T < 0 := by exact_mod_cast htr
    simp only [ht, decide_true]

end Submission.R27GuardedEndpoints
