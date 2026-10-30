import ContractExact

namespace Submission.R26ExactRawTotal
open ExactRuntime FloatLib.Numerics
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange
open Model.Reduction

noncomputable def wordValue (w : UInt32) : Real :=
  Model.toReal (Model.ofUInt32 (fmt := Fmt) w)

noncomputable def slice (a b : Array UInt32) (index count : Nat) : Real :=
  ((List.range' index count).map (fun i => wordValue a[i]! * wordValue b[i]!)).sum

private theorem contribution_real {fmt : FloatFormat} (x : Model fmt) :
    (Semantics.finiteContribution x : Real) = Model.toReal x := by
  rw [Model.toReal_eq]
  unfold Semantics.finiteContribution
  cases hd : Model.toDyadic? x <;> simp [hd, Dyadic.cast_toRat]

theorem finiteSlice_real (a b : Array UInt32) (index count : Nat)
    (ha : index + count ≤ (a.map (Model.ofUInt32 (fmt := Fmt))).size)
    (hb : index + count ≤ (b.map (Model.ofUInt32 (fmt := Fmt))).size) :
    (Semantics.finiteDotSlice (a.map (Model.ofUInt32 (fmt := Fmt)))
      (b.map (Model.ofUInt32 (fmt := Fmt))) index count ha hb : Real) =
      slice a b index count := by
  induction count generalizing index with
  | zero => simp [Semantics.finiteDotSlice, slice]
  | succ count ih =>
    have hia : index < a.size := by simp only [Array.size_map] at ha; omega
    have hib : index < b.size := by simp only [Array.size_map] at hb; omega
    rw [Semantics.finiteDotSlice]
    push_cast
    rw [ih (index + 1) (by omega) (by omega)]
    simp only [Array.getElem_map, contribution_real, slice, List.range'_succ,
      List.map_cons, List.sum_cons, wordValue, getElem!_pos a index hia,
      getElem!_pos b index hib]

/-- Exact real sum of the actual indexed words equals the official integer
accumulator's scale. This is a bridge to dsum, not an arbitrary ghost total. -/
theorem slice_eq_scaled_dsum (a b : Array UInt32) (index count : Nat)
    (ha : index + count ≤ (a.map (Model.ofUInt32 (fmt := Fmt))).size)
    (hb : index + count ≤ (b.map (Model.ofUInt32 (fmt := Fmt))).size)
    (hfin : ∀ k, index ≤ k → k < index + count →
      expOf a[k]! ≠ 255 ∧ expOf b[k]! ≠ 255) :
    slice a b index count = (dsum a b index count : Real) * (2 : Real) ^ (-298 : Int) := by
  have h := congrArg (fun r : Rat => (r : Real)) (finiteDotSlice_eq a b index count ha hb hfin)
  rw [finiteSlice_real a b index count ha hb] at h
  push_cast at h
  exact h

end Submission.R26ExactRawTotal
