import ContractExact

namespace Submission.R26FiniteDotFinish
open ExactRuntime FloatLib.Numerics
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange
open Model.Reduction

/-- The official dot of finite actual arrays is the official nonzero integer
finisher, independently of any proposed native arithmetic. -/
theorem dotSpec_eq_finishWord_nonzero (a b : Array UInt32) (negZero : Bool)
    (hsize : a.size = b.size)
    (ha : ∀ i (hi : i < a.size), expOf a[i] ≠ 255)
    (hb : ∀ i (hi : i < b.size), expOf b[i] ≠ 255)
    (hT : dsum a b 0 a.size ≠ 0) :
    dotSpec a b = finishWord (dsum a b 0 a.size) (-298) negZero := by
  let A := a.map (Model.ofUInt32 (fmt := Fmt))
  let B := b.map (Model.ofUInt32 (fmt := Fmt))
  have hAB : A.size = B.size := by simpa [A, B] using hsize
  have hAF : ∀ i (hi : i < A.size), Model.isFinite A[i] = true := by
    intro i hi
    have hai : i < a.size := by simpa [A] using hi
    simpa only [A, Array.getElem_map] using
      Model.isFinite_eq_true_of_toDyadic?_some (toDyadic_ofUInt32 a[i] (ha i hai))
  have hBF : ∀ i (hi : i < B.size), Model.isFinite B[i] = true := by
    intro i hi
    have hbi : i < b.size := by simpa [B] using hi
    simpa only [B, Array.getElem_map] using
      Model.isFinite_eq_true_of_toDyadic?_some (toDyadic_ofUInt32 b[i] (hb i hbi))
  let st : Internal.State Fmt := Internal.dotState A B hAB
  have hfin : ∀ k, 0 ≤ k → k < 0 + a.size → expOf a[k]! ≠ 255 ∧ expOf b[k]! ≠ 255 := by
    intro k _ hk
    have hka : k < a.size := by omega
    have hkb : k < b.size := by omega
    simpa only [getElem!_pos a k hka, getElem!_pos b k hkb] using ⟨ha k hka, hb k hkb⟩
  have hslice : Semantics.finiteDotSlice A B 0 A.size (by omega) (by omega) =
      (dsum a b 0 a.size : Rat) * (2 : Rat) ^ (-298 : Int) := by
    simpa only [A, B, Array.size_map] using
      (finiteDotSlice_eq a b 0 a.size (by simp) (by simp [hsize]) hfin)
  have hd : st.exact.toRat = (dsum a b 0 a.size : Rat) * (2 : Rat) ^ (-298 : Int) := by
    rw [Internal.dotState_exact_toRat A B hAB hAF hBF]
    exact hslice
  have hprod : (dsum a b 0 a.size : Rat) * (2 : Rat) ^ (-298 : Int) ≠ 0 :=
    mul_ne_zero (by exact_mod_cast hT) (zpow_ne_zero _ (by norm_num))
  have hnonzero : Semantics.finiteDot A.toList B.toList ≠ .ok 0 := by
    rw [Semantics.finiteDot_toList_eq_slice A B hAB]
    intro hz
    have hzrat := Except.ok.inj hz
    rw [hslice] at hzrat
    exact hprod hzrat
  unfold dotSpec
  change (match Model.dot Fmt A B .nearestEven with
    | .ok z => toWord z
    | .error _ => 0) = _
  unfold Model.dot
  rw [Model.Reduction.dotWithStatus_eq_round_of_finite_nonzero
    Fmt A B .nearestEven hAB hAF hBF hnonzero]
  simp only [Except.map]
  exact (finishWord_of_ne st.exact (dsum a b 0 a.size) (-298) negZero hT hd).symm

end Submission.R26FiniteDotFinish
