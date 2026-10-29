/- Pull strict raw-midpoint comparisons back through actual nearest64 endpoints.
   No outward-rounding premise is used. -/
namespace Submission.R26RnePullback
open Submission.R25OrderKey Submission.R25Checker
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

private theorem strict_lower (x : Real) (w : UInt64) (hf : finite64 w = true)
    (h : value w < Model.roundAt F64 x) : value w < x := by
  by_contra hn
  have hm := Model.roundAt_mono F64 (le_of_not_gt hn)
  change Model.roundAt F64 x ≤ Model.roundAt F64 (Model.toReal (raw w)) at hm
  rw [Model.roundAt_toReal_eq (raw w) (finite64_model w hf)] at hm
  exact (not_lt_of_ge hm) h

private theorem strict_upper (x : Real) (w : UInt64) (hf : finite64 w = true)
    (h : Model.roundAt F64 x < value w) : x < value w := by
  by_contra hn
  have hm := Model.roundAt_mono F64 (le_of_not_gt hn)
  change Model.roundAt F64 (Model.toReal (raw w)) ≤ Model.roundAt F64 x at hm
  rw [Model.roundAt_toReal_eq (raw w) (finite64_model w hf)] at hm
  exact (not_lt_of_ge hm) h

/-- This matches the actual producer's error and nearest-endpoint outputs.
The exact target is in the strict cell even though native endpoints need not
round outward. Normality and finite representable midpoint facts are derived. -/
theorem accepted_contains_exact (s r : Float) (sw : UInt64) (q : UInt32)
    (S R : Real)
    (herr : |nativeValue s - S| ≤ R)
    (hlo : nativeValue (s - r) = Model.roundAt F64 (nativeValue s - R))
    (hhi : nativeValue (s + r) = Model.roundAt F64 (nativeValue s + R))
    (hacc : certify s r sw q = true) :
    value (lowerWord q) < S ∧ S < value (upperWord q) := by
  obtain ⟨he0, he255, _⟩ := accepted_components s r sw q hacc
  obtain ⟨hlf, huf, _, _⟩ := midpoint_finite_nonzero q he0 he255
  have hb := accepted_native_bounds s r sw q hacc
  rw [hlo, hhi] at hb
  have hl := strict_lower (nativeValue s - R) (lowerWord q) hlf hb.1
  have hu := strict_upper (nativeValue s + R) (upperWord q) huf hb.2
  obtain ⟨hel, heu⟩ := abs_le.mp herr
  constructor <;> linarith

end Submission.R26RnePullback
