/- Total finite-input value bridge for the actual, unchanged widening function.
   This theorem is not a prepare/getter or Tail accumulation invariant. -/
namespace Submission.R25FiniteWiden
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open R2W01c
open Submission.R24RepresentationWiden

theorem n_eq_wordFrac (u : UInt32) :
    Submission.R24SubnormalWiden.n u = wordFrac u := by
  exact fracWord_toNat u

theorem subnormal_actual_value (u : UInt32)
    (he : expWord u = 0) (hn : 0 < Submission.R24SubnormalWiden.n u) :
    (Float.ofBits (Submission.R24PortableF64.widenBits u)).isFinite = true ∧
      Model.toReal (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat
        (Float.ofBits (Submission.R24PortableF64.widenBits u)))) =
        Model.toReal (Model.ofUInt32 (fmt := FloatFormat.binary32) u) := by
  have hs := Submission.R24SubnormalWiden.subnormal_finite_value u he hn
  have heNat : wordExp u = 0 := by
    have hh := expWord_toNat u
    rw [he] at hh
    change 0 = wordExp u at hh
    exact hh.symm
  have hf : wordFrac u ≠ 0 := by
    rw [n_eq_wordFrac] at hn
    omega
  refine ⟨hs.1, ?_⟩
  rw [ExecFloat.Binary.toModel_ofFloat]
  change Model.toReal (Submission.R24SubnormalWiden.native
    (Float.ofBits (Submission.R24PortableF64.widenBits u))) = Model.toReal (raw32 u)
  rw [hs.2, raw32_eq_fields, heNat,
    Model.toReal_ofFields_subnormal FloatFormat.binary32 (wordSign u) (wordFrac u)
      hf (wordFrac_lt u)]
  by_cases hsign : 2147483648 ≤ u.toNat <;>
    simp [wordSign, hsign, n_eq_wordFrac]

theorem finite_domain_split (u : UInt32) (hf : expWord u ≠ 255) :
    Domain u ∨ (expWord u = 0 ∧ 0 < Submission.R24SubnormalWiden.n u) := by
  have hlt := wordExp_lt u
  have h255 : wordExp u ≠ 255 := by
    intro h
    apply hf
    apply UInt32.toNat_inj.mp
    change (expWord u).toNat = 255
    rw [expWord_toNat, h]
  by_cases he : wordExp u = 0
  · by_cases hfrac : wordFrac u = 0
    · exact Or.inl (Or.inr ⟨he, hfrac⟩)
    · right
      constructor
      · apply UInt32.toNat_inj.mp
        change (expWord u).toNat = 0
        rw [expWord_toNat, he]
      · rw [n_eq_wordFrac]
        omega
  · exact Or.inl (Or.inl ⟨by omega, by omega⟩)

/-- Every finite binary32 word, including subnormals and signed zeros, widens to
a finite native binary64 with the original binary32 real value. -/
theorem finite_actual_value (u : UInt32) (hf : expWord u ≠ 255) :
    (Float.ofBits (Submission.R24PortableF64.widenBits u)).isFinite = true ∧
      Model.toReal (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat
        (Float.ofBits (Submission.R24PortableF64.widenBits u)))) =
        Model.toReal (Model.ofUInt32 (fmt := FloatFormat.binary32) u) := by
  rcases finite_domain_split u hf with h | ⟨he, hn⟩
  · exact ⟨Submission.R25ActualWiden.actual_native_finite u h,
      Submission.R25ActualWiden.actual_native_value u h⟩
  · exact subnormal_actual_value u he hn

end Submission.R25FiniteWiden
