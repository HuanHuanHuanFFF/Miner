/- R22 signed-zero completion for the E0 field theorem. NOT_RUN. -/
namespace Submission.R22SameExponentMath
open FloatLib.Floats FloatLib.Numerics
open FloatLib.Floats.Formats.BinaryInterchange

theorem zero_fields_decode (s : Bool) :
    Model.toDyadic? (Model.ofFields FloatFormat.binary32 s 0 0) =
      some ⟨s, 0, 0⟩ := by
  have hf : Model.isFinite (Model.ofFields FloatFormat.binary32 s 0 0) = true := by
    cases s <;> decide
  have h := Model.toDyadic?_ofFields_of_isFinite FloatFormat.binary32 s 0 0
    (by decide) (by decide) hf
  simpa using h

theorem zero_round (s : Bool) (e : Int) :
    Model.roundDyadic FloatFormat.binary32 ⟨s, 0, e⟩ =
      Model.ofFields FloatFormat.binary32 s 0 0 := by
  rw [← Model.NativeBinary32.ofUInt32_roundDyadic]
  cases s <;> rfl

theorem subnormal_fields_add (s : Bool) (f g : Nat)
    (hf : f < 8388608) (hg : g < 8388608) :
    Model.Spec.add (Model.ofFields FloatFormat.binary32 s 0 f)
      (Model.ofFields FloatFormat.binary32 s 0 g) =
      Model.ofFields FloatFormat.binary32 s ((f + g) / 8388608)
        ((f + g) % 8388608) := by
  by_cases hf0 : f = 0
  · subst f
    by_cases hg0 : g = 0
    · subst g
      simp [Model.Spec.add, zero_fields_decode, Model.addDyadic,
        Dyadic.add, Dyadic.addFields, zero_round]
    · have hdg := Model.toDyadic?_ofFields_subnormal FloatFormat.binary32 s g hg0 hg
      change Model.toDyadic? (Model.ofFields FloatFormat.binary32 s 0 g) =
        some ⟨s, g, -149⟩ at hdg
      unfold Model.Spec.add
      rw [zero_fields_decode, hdg]
      simpa [Model.addDyadic, Dyadic.add, Dyadic.addFields, hg0] using
        low_lattice_round s g (by omega)
  · by_cases hg0 : g = 0
    · subst g
      have hdf := Model.toDyadic?_ofFields_subnormal FloatFormat.binary32 s f hf0 hf
      change Model.toDyadic? (Model.ofFields FloatFormat.binary32 s 0 f) =
        some ⟨s, f, -149⟩ at hdf
      unfold Model.Spec.add
      rw [hdf, zero_fields_decode]
      simpa [Model.addDyadic, Dyadic.add, Dyadic.addFields, hf0] using
        low_lattice_round s f (by omega)
    · exact subnormal_fields_nonzero_add s f g hf0 hg0 hf hg

end Submission.R22SameExponentMath
