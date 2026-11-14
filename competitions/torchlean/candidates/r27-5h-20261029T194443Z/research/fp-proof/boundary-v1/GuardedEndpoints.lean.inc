/- Derive the endpoint equations from the actual finite guards. This avoids
   asking the producer for separate endpoint-enclosure or magnitude premises. -/
namespace Submission.R27GuardedEndpoints
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange
open Submission.R25OrderKey Submission.R25Checker

private theorem native_finite_eq (x : Float) :
    Model.isFinite (native x) = x.isFinite := by
  rw [← Model.toDyadic?_isSome_eq_isFinite,
    Model.toDyadic?_ieee_eq_model F64 (by decide), Model.toModel_ofFloatModel]
  change (Model.unpackedToDyadic? x.toModel.unpack).isSome = x.toModel.unpack.isFinite
  cases x.toModel.unpack <;> rfl

private theorem native_add (x y : Float) (hx : x.isFinite = true)
    (hy : y.isFinite = true) :
    native (x + y) = Model.add (native x) (native y) := by
  change Model.ofFloatModel (Float.Model.add x.toModel y.toModel) = _
  rw [Float.Model.add, Model.ofFloatModel_pack]
  have h := Model.add_eq_ofModel_add_of_isFinite (fmt := F64)
    (by decide) (Model.ofFloatModel x.toModel) (Model.ofFloatModel y.toModel)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite, Float.Model.isFinite] using hx)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite, Float.Model.isFinite] using hy)
  rw [Model.toModel_ofFloatModel, Model.toModel_ofFloatModel] at h
  exact h.symm

private theorem native_sub (x y : Float) (hx : x.isFinite = true)
    (hy : y.isFinite = true) :
    native (x - y) = Model.sub (native x) (native y) := by
  change Model.ofFloatModel (Float.Model.sub x.toModel y.toModel) = _
  rw [Float.Model.sub, Model.ofFloatModel_pack]
  have h := Model.sub_eq_ofModel_sub_of_isFinite (fmt := F64)
    (by decide) (Model.ofFloatModel x.toModel) (Model.ofFloatModel y.toModel)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite, Float.Model.isFinite] using hx)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite, Float.Model.isFinite] using hy)
  rw [Model.toModel_ofFloatModel, Model.toModel_ofFloatModel] at h
  exact h.symm

theorem accepted_endpoint_equations (s r : Float) (q : UInt32)
    (hr : r.isFinite = true)
    (hacc : Submission.R24PortableF64.certify s r s.toBits q = true) :
    nativeValue (s - r) = Model.roundAt F64 (nativeValue s - nativeValue r) ∧
      nativeValue (s + r) = Model.roundAt F64 (nativeValue s + nativeValue r) := by
  have hc : certify s r s.toBits q = true := by
    simpa only [certify_eq_runtime] using hacc
  obtain ⟨_, _, hsf, hlof, hhif, _, _⟩ := accepted_components s r s.toBits q hc
  have hms : Model.isFinite (native s) = true := finite64_model s.toBits hsf
  have hmlo : Model.isFinite (native (s - r)) = true :=
    finite64_model (s - r).toBits hlof
  have hmhi : Model.isFinite (native (s + r)) = true :=
    finite64_model (s + r).toBits hhif
  have hs : s.isFinite = true := by rw [← native_finite_eq]; exact hms
  have hmr : Model.isFinite (native r) = true := by rw [native_finite_eq, hr]
  have hsub : Model.isFinite (Model.sub (native s) (native r)) = true := by
    rw [← native_sub s r hs hr]
    exact hmlo
  have hadd : Model.isFinite (Model.add (native s) (native r)) = true := by
    rw [← native_add s r hs hr]
    exact hmhi
  constructor
  · unfold nativeValue
    rw [native_sub s r hs hr]
    exact Model.toReal_sub_eq_roundAt _ _ (by decide) hms hmr hsub
  · unfold nativeValue
    rw [native_add s r hs hr]
    exact Model.toReal_add_eq_roundAt _ _ (by decide) hms hmr hadd

/-- Only actual finite radius and forward error remain as producer obligations.
    Native endpoint RNE equations are derived from actual checker guards. -/
theorem actual_acceptance_contains_exact_of_error (s r : Float) (q : UInt32)
    (S : Real) (hr : r.isFinite = true)
    (herr : |nativeValue s - S| ≤ nativeValue r)
    (hacc : Submission.R24PortableF64.certify s r s.toBits q = true) :
    value (lowerWord q) < S ∧ S < value (upperWord q) := by
  have he := accepted_endpoint_equations s r q hr hacc
  exact Submission.R27ActualBoundary.actual_acceptance_contains_exact
    s r s.toBits q S (nativeValue r) herr he.1 he.2 hacc

end Submission.R27GuardedEndpoints
