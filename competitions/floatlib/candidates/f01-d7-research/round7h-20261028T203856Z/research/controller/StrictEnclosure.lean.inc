/- R24 portable strict-endpoint core, fixed ContractTensor-imported FloatLib.
   These roots prove the nearest64 pullback, not raw-word cell construction,
   actual native endpoint evaluation, RNE32 cell membership or kernel adoption.
   No external monotonicity/fixed-point axiom or outward-rounding premise. -/
namespace Submission.R24StrictEnclosure

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

abbrev F64 := FloatFormat.binary64

theorem strict_lower_pullback (x : Real) (lower : Model F64)
    (hfinite : Model.isFinite lower = true)
    (h : Model.toReal lower < Model.roundAt F64 x) :
    Model.toReal lower < x := by
  by_contra hn
  have hx : x ≤ Model.toReal lower := le_of_not_gt hn
  have hm := Model.roundAt_mono F64 hx
  rw [Model.roundAt_toReal_eq lower hfinite] at hm
  exact (not_lt_of_ge hm) h

theorem strict_upper_pullback (x : Real) (upper : Model F64)
    (hfinite : Model.isFinite upper = true)
    (h : Model.roundAt F64 x < Model.toReal upper) :
    x < Model.toReal upper := by
  by_contra hn
  have hx : Model.toReal upper ≤ x := le_of_not_gt hn
  have hm := Model.roundAt_mono F64 hx
  rw [Model.roundAt_toReal_eq upper hfinite] at hm
  exact (not_lt_of_ge hm) h

theorem strict_enclosure_of_rounded_bounds
    (s target radius : Real) (lower upper : Model F64)
    (hlfinite : Model.isFinite lower = true)
    (hufinite : Model.isFinite upper = true)
    (herror : |s - target| ≤ radius)
    (hlower : Model.toReal lower < Model.roundAt F64 (s - radius))
    (hupper : Model.roundAt F64 (s + radius) < Model.toReal upper) :
    Model.toReal lower < target ∧ target < Model.toReal upper := by
  have hl := strict_lower_pullback (s - radius) lower hlfinite hlower
  have hu := strict_upper_pullback (s + radius) upper hufinite hupper
  obtain ⟨hel, heu⟩ := abs_le.mp herror
  constructor <;> linarith

end Submission.R24StrictEnclosure
