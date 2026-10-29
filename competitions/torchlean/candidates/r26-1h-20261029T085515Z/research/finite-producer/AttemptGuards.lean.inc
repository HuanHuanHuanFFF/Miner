namespace Submission.R26AttemptGuards
open Submission.R24PortableF64

abbrev cachedSum (x y : Prepared) : Float :=
  sumRemaining x.values y.values 0 (Float.ofBits 0) x.raw.size

abbrev cachedRadius (x y : Prepared) : Float :=
  let L := ceilLog2 x.raw.size
  let H := x.maxIndex.toUInt64 + y.maxIndex.toUInt64
  Float.ofBits ((H + (L + L) + 720) <<< 52)

theorem attemptPrepared_guards (x y : Prepared) (hnz : attemptPrepared x y ≠ 0) :
    0 < x.raw.size ∧ x.raw.size = y.raw.size ∧ x.raw.size ≤ 1073741824 ∧
      x.valid = true ∧ y.valid = true := by
  have hn : x.raw.size ≠ 0 := by
    intro h
    simp [attemptPrepared, h] at hnz
  have hs : x.raw.size = y.raw.size := by
    by_contra h
    simp [attemptPrepared, h] at hnz
  have hc : x.raw.size ≤ 1073741824 := by
    by_contra h
    have hlarge : 1073741824 < x.raw.size := by omega
    simp [attemptPrepared, hlarge] at hnz
  have hv : x.valid && y.valid = true := by
    by_contra h
    have hf : x.valid && y.valid = false := Bool.eq_false_of_not_eq_true h
    simp [attemptPrepared, hf] at hnz
  exact ⟨by omega, hs, hc, (Bool.and_eq_true.mp hv).1, (Bool.and_eq_true.mp hv).2⟩

theorem attemptPrepared_acceptance (x y : Prepared) (hnz : attemptPrepared x y ≠ 0) :
    certify (cachedSum x y) (cachedRadius x y) (cachedSum x y).toBits
      (attemptPrepared x y) = true := by
  obtain ⟨hn, hs, hc, hx, hy⟩ := attemptPrepared_guards x y hnz
  have hnotzero : x.raw.size ≠ 0 := by omega
  have hnotlarge : ¬ 1073741824 < x.raw.size := by omega
  have heq : attemptPrepared x y =
      if certify (cachedSum x y) (cachedRadius x y) (cachedSum x y).toBits
        (proposal (cachedSum x y).toBits) then proposal (cachedSum x y).toBits else 0 := by
    simp only [attemptPrepared, cachedSum, cachedRadius, beq_iff_eq,
      hnotzero, hs, bne_self_eq_false, Bool.false_or, hnotlarge, hx, hy,
      Bool.true_and, Bool.not_true, ite_false, ite_true]
  by_cases hh : certify (cachedSum x y) (cachedRadius x y) (cachedSum x y).toBits
      (proposal (cachedSum x y).toBits) = true
  · simpa only [heq, hh, ite_true] using hh
  · have hf : certify (cachedSum x y) (cachedRadius x y) (cachedSum x y).toBits
        (proposal (cachedSum x y).toBits) = false := Bool.eq_false_of_not_eq_true hh
    rw [heq, hf] at hnz
    exact False.elim (hnz rfl)

end Submission.R26AttemptGuards
