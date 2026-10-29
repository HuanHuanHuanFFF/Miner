/- Append after the checked R25 key and actual checker fragment.
The enclosure hypothesis is the precise remaining producer obligation. -/
namespace Submission.R25Checker

/-- A producer enclosure plus actual runtime acceptance gives the strict cell
bounds consumed by the rounder proof. The exact sum can be any real S. -/
theorem accepted_contains_exact (sum radius : Float) (sumWord : UInt64) (q : UInt32)
    (S : Real)
    (hEnclosure : R25OrderKey.nativeValue (sum - radius) ≤ S ∧
      S ≤ R25OrderKey.nativeValue (sum + radius))
    (hAccepted : R24PortableF64.certify sum radius sumWord q = true) :
    R25OrderKey.value (lowerWord q) < S ∧ S < R25OrderKey.value (upperWord q) := by
  have h := actual_acceptance_bounds sum radius sumWord q hAccepted
  exact ⟨lt_of_lt_of_le h.1 hEnclosure.1, lt_of_le_of_lt hEnclosure.2 h.2⟩

/-- A lower raw midpoint used through native ofBits has the same exact value.
Finiteness is derived from the actual binary32 normality guards. -/
theorem lower_native_value (q : UInt32) (he0 : eWord q ≠ 0) (he255 : eWord q ≠ 255) :
    R25OrderKey.nativeValue (Float.ofBits (lowerWord q)) = R25OrderKey.value (lowerWord q) :=
  R25OrderKey.value_ofBits _ (midpoint_finite_nonzero q he0 he255).1

theorem upper_native_value (q : UInt32) (he0 : eWord q ≠ 0) (he255 : eWord q ≠ 255) :
    R25OrderKey.nativeValue (Float.ofBits (upperWord q)) = R25OrderKey.value (upperWord q) :=
  R25OrderKey.value_ofBits _ (midpoint_finite_nonzero q he0 he255).2.1

end Submission.R25Checker

