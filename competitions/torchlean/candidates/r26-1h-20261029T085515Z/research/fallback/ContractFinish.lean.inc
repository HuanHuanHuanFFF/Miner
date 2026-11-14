namespace Submission.R26WordBlock
open ExactRuntime FloatLib.Numerics
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

def rawWords (n : Nat) (f : Nat → UInt32) : Array UInt32 :=
  Array.ofFn (n := n) fun i => f i.val

theorem rawWords_get (n : Nat) (f : Nat → UInt32) (k : Nat) (hk : k < n) :
    (rawWords n f)[k]! = f k := by
  rw [getElem!_pos _ k (by simpa [rawWords] using hk)]
  simp [rawWords]

theorem dotOf_finite_finish (n : Nat) (fa fb : Nat → UInt32)
    (hfin : ∀ k, k < n → expOf (fa k) ≠ 255 ∧ expOf (fb k) ≠ 255) :
    dotOf n fa fb = finishWord (dsum (rawWords n fa) (rawWords n fb) 0 n) (-298)
      (decide (n ≠ 0) && dallNZ (rawWords n fa) (rawWords n fb) 0 n) := by
  let A := rawWords n fa
  let B := rawWords n fb
  let L := A.map (Model.ofUInt32 (fmt := Fmt))
  let R := B.map (Model.ofUInt32 (fmt := Fmt))
  let T := dsum A B 0 n
  have hAs : A.size = n := by simp [A, rawWords]
  have hBs : B.size = n := by simp [B, rawWords]
  have hLs : L.size = n := by simp [L, hAs]
  have hRs : R.size = n := by simp [R, hBs]
  have hLR : L.size = R.size := by omega
  have hall : ∀ k, 0 ≤ k → k < n → expOf A[k]! ≠ 255 ∧ expOf B[k]! ≠ 255 := by
    intro k _ hk
    simpa only [A, B, rawWords_get n fa k hk, rawWords_get n fb k hk] using hfin k hk
  have hLfin : ∀ k (hk : k < L.size), Model.isFinite L[k] = true := by
    intro k hk
    have hkA : k < A.size := by omega
    have hf := (hall k (by omega) (by omega)).1
    rw [getElem!_pos A k hkA] at hf
    simpa [L, isFinite_ofUInt32] using hf
  have hRfin : ∀ k (hk : k < R.size), Model.isFinite R[k] = true := by
    intro k hk
    have hkB : k < B.size := by omega
    have hf := (hall k (by omega) (by omega)).2
    rw [getElem!_pos B k hkB] at hf
    simpa [R, isFinite_ofUInt32] using hf
  have hslice : Model.Reduction.Semantics.finiteDotSlice L R 0 L.size (by simp)
      (by simp [hLR]) = (T : Rat) * 2 ^ (-298 : Int) := by
    have h := finiteDotSlice_eq A B 0 L.size (by simp [L]) (by simp [L, hAs, hBs])
      (fun k h1 h2 => hall k h1 (by omega))
    simpa only [hLs] using h
  have hexact := Model.Reduction.Internal.dotState_exact_toRat
    (destination := Fmt) L R hLR hLfin hRfin
  change dotSpec A B = finishWord T (-298) (decide (n ≠ 0) && dallNZ A B 0 n)
  unfold dotSpec Model.dot
  by_cases hT : T = 0
  · have hzero : (Model.Reduction.Internal.dotState L R hLR :
        Model.Reduction.Internal.State Fmt).exact.significand = 0 := by
      rw [← Dyadic.toRat_eq_zero_iff, hexact, hslice, hT]
      simp
    rw [Model.Reduction.dotWithStatus_eq_zero_of_finite Fmt L R .nearestEven hLR hLfin hRfin
      hzero, hT, finishWord_zero]
    unfold Model.Reduction.Internal.dotState
    obtain ⟨h1, h2⟩ := dotStateLoop_flags A B {} 0 L.size (by simp [L])
      (by simp [L, hAs, hBs]) (fun k h1 h2 => hall k h1 (by omega))
    simp only [Bool.false_or, Bool.true_and] at h1 h2
    simp only [Except.map, h1, h2, hLs]
  · have hnz : Model.Reduction.Semantics.finiteDot L.toList R.toList ≠ .ok 0 := by
      rw [Model.Reduction.Semantics.finiteDot_toList_eq_slice L R hLR]
      intro hz
      injection hz with hz
      rw [hslice] at hz
      simp at hz
      exact hT hz
    rw [Model.Reduction.dotWithStatus_eq_round_of_finite_nonzero Fmt L R .nearestEven hLR
      hLfin hRfin hnz]
    simp only [Except.map]
    exact (finishWord_of_ne _ _ _ _ hT (by rw [hexact, hslice])).symm

theorem guardedFinish_correct (guard : Bool) (n : Nat) (fa fb a b : Nat → UInt32)
    (bias exponent : Int) (nz : Bool) (shipped : Unit → UInt32)
    (hship : shipped () = dotOf n fa fb)
    (hsize : guard = true → n ≤ 1048576)
    (hfinite : guard = true → ∀ k, k < n → expOf (fa k) ≠ 255 ∧ expOf (fb k) ≠ 255)
    (hvalue : guard = true → finishWord (exactTerms a b n 0 + bias) exponent nz =
      finishWord (dsum (rawWords n fa) (rawWords n fb) 0 n) (-298)
        (decide (n ≠ 0) && dallNZ (rawWords n fa) (rawWords n fb) 0 n)) :
    guardedFinish guard n a b bias exponent nz shipped = dotOf n fa fb := by
  cases guard
  · simpa only [guardedFinish_false] using hship
  · rw [guardedFinish_true, preparedFinish_exact n a b (hsize rfl), hvalue rfl]
    exact (dotOf_finite_finish n fa fb (hfinite rfl)).symm

end Submission.R26WordBlock
