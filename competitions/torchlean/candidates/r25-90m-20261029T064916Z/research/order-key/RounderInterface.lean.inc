/- Follow-on integration only; not part of the pending v2 proof probe.
Requires ProducerInterface and the exact old R24 RawMidpoint proof closure.
All old and new proof dependencies still require pinned Lean acceptance. -/
namespace Submission.R25Checker
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

theorem eWord_eq_raw (q : UInt32) :
    eWord q = Model.NativeBinary32.expField q :=
  R24RawMidpoint.magnitude_exp q

theorem lowerWord_eq_raw (q : UInt32) :
    lowerWord q = R24RawMidpoint.lowerWord q := rfl

theorem upperWord_eq_raw (q : UInt32) :
    upperWord q = R24RawMidpoint.upperWord q := rfl

theorem accepted_normal (s r : Float) (sw : UInt64) (q : UInt32)
    (h : R24PortableF64.certify s r sw q = true) :
    1 ≤ (Model.NativeBinary32.expField q).toNat ∧
      (Model.NativeBinary32.expField q).toNat ≤ 254 := by
  have hc : certify s r sw q = true := by simpa only [certify_eq_runtime] using h
  obtain ⟨he0, he255, _⟩ := accepted_components s r sw q hc
  have he := eWord_bound q
  have hn0 : (eWord q).toNat ≠ 0 := by
    intro hn
    apply he0
    apply UInt32.toNat_inj.mp
    exact hn
  have hn255 : (eWord q).toNat ≠ 255 := by
    intro hn
    apply he255
    apply UInt32.toNat_inj.mp
    exact hn
  rw [eWord_eq_raw] at he hn0 hn255
  omega

/-- The complete checker-to-rounder composition once the producer establishes
the two actual native endpoints enclose the exact rationally scaled input.
No claim that the current runtime producer already meets this hypothesis. -/
theorem actual_acceptance_roundRatScaled
    (sum radius : Float) (sumWord : UInt64) (q : UInt32)
    (sign : Bool) (num den : Nat) (source : Int) (S : Real) (hd : 0 < den)
    (hsource : S = Model.signedScaledRatToReal sign num den source)
    (hEnclosure : R25OrderKey.nativeValue (sum - radius) ≤ S ∧
      S ≤ R25OrderKey.nativeValue (sum + radius))
    (hAccepted : R24PortableF64.certify sum radius sumWord q = true) :
    Model.NativeBinary32.roundRatScaled sign num den source = q := by
  have hcell := accepted_contains_exact sum radius sumWord q S hEnclosure hAccepted
  have hc : certify sum radius sumWord q = true := by
    simpa only [certify_eq_runtime] using hAccepted
  obtain ⟨he0, he255, _⟩ := accepted_components sum radius sumWord q hc
  have he := accepted_normal sum radius sumWord q hAccepted
  have hl : R24MidpointReal.nativeReal (R24RawMidpoint.lowerWord q) < S := by
    rw [← lowerWord_eq_raw]
    change R25OrderKey.nativeValue (Float.ofBits (lowerWord q)) < S
    rw [lower_native_value q he0 he255]
    exact hcell.1
  have hu : S < R24MidpointReal.nativeReal (R24RawMidpoint.upperWord q) := by
    rw [← upperWord_eq_raw]
    change S < R25OrderKey.nativeValue (Float.ofBits (upperWord q))
    rw [upper_native_value q he0 he255]
    exact hcell.2
  exact R24RawMidpoint.roundRatScaled_of_endpoint_bounds q sign num den source S
    hd he.1 he.2 hsource hl hu

end Submission.R25Checker

