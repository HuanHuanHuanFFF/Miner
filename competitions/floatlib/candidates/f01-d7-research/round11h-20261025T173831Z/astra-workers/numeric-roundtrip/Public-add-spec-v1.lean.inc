namespace Submission.R18AddSpec
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

theorem ex_nat (u : UInt32) :
    (Model.NativeBinary32.expField u).toNat = R2W01c.wordExp u :=
  FastMul.expField_toNat u

theorem normal_field (u : UInt32) (h : Model.NativeBinary32.expField u - 1 ≤ (253 : UInt32)) :
    0 < R2W01c.wordExp u ∧ R2W01c.wordExp u < 255 := by
  have hb : R2W01c.wordExp u < 256 := Nat.mod_lt _ (by decide)
  rw [UInt32.le_iff_toNat_le, UInt32.toNat_sub] at h
  change (4294967295 + (Model.NativeBinary32.expField u).toNat) % 4294967296 ≤ 253 at h
  rw [ex_nat] at h
  omega

theorem sorted_spec (f : Binary32 → Binary32 → Binary32)
    (hf : ∀ x y, f x y = ExecFloat.Spec.add x y) (x y : Binary32) (hi lo : UInt32)
    (hH : 0 < R2W01c.wordExp hi ∧ R2W01c.wordExp hi < 255)
    (hL : 0 < R2W01c.wordExp lo ∧ R2W01c.wordExp lo < 255)
    (ho : R2W01c.wordExp lo ≤ R2W01c.wordExp hi)
    (hp : (x.raw.1 = hi ∧ y.raw.1 = lo) ∨ (x.raw.1 = lo ∧ y.raw.1 = hi)) :
    R17NumericAdd.sortedAdd f x y hi lo (Model.NativeBinary32.expField hi)
      (Model.NativeBinary32.expField lo) = ExecFloat.Spec.add x y := by
  let eh := Model.NativeBinary32.expField hi
  let el := Model.NativeBinary32.expField lo
  let d := eh - el
  let same := R2W01c.wordSign hi == R2W01c.wordSign lo
  let adj : UInt32 := if same then 0 else 1
  let n := if same then (R2W01b.mantissa hi <<< d) + R2W01b.mantissa lo
    else (R2W01b.mantissa hi <<< d) - R2W01b.mantissa lo
  let r := n.toFloat32.toUInt32
  let base := d - adj
  let bump : UInt32 := if (1 : UInt32) <<< (base + 24) ≤ r then 1 else 0
  let sh := base + bump
  let e := (eh - adj) + bump
  have hEH : eh.toNat = R2W01c.wordExp hi := ex_nat hi
  have hEL : el.toNat = R2W01c.wordExp lo := ex_nat lo
  have horder : el ≤ eh := UInt32.le_iff_toNat_le.mpr (by rw [hEH, hEL]; exact ho)
  have hD : d.toNat = R2W01c.wordExp hi - R2W01c.wordExp lo := by
    dsimp only [d]
    rw [UInt32.toNat_sub_of_le _ _ horder, hEH, hEL]
  have hma := R2W01c.mantissa_bounds hi
  have hmb := R2W01c.mantissa_bounds lo
  unfold R17NumericAdd.sortedAdd
  simp only [R18SortedWord.sign_eq]
  change (if decide (d ≤ (7 : UInt32)) && decide (adj ≤ d) then
    if (8388608 : UInt32) ≤ n then
      if e ≤ (254 : UInt32) then R7W02.fromRaw (FastMul.mkW (R2W01c.wordSign hi) e (r >>> sh))
      else f x y
    else f x y
  else f x y) = _
  split
  · rename_i hd
    have hg : d.toNat ≤ 7 := by
      have h := (Bool.and_eq_true.mp hd).1
      exact UInt32.le_iff_toNat_le.mp (of_decide_eq_true h)
    have had : adj.toNat ≤ d.toNat := by
      have h := (Bool.and_eq_true.mp hd).2
      exact UInt32.le_iff_toNat_le.mp (of_decide_eq_true h)
    have hdom : R2W01c.wordSign hi = R2W01c.wordSign lo ∨ 1 ≤ d.toNat := by
      by_cases hs : R2W01c.wordSign hi = R2W01c.wordSign lo
      · exact Or.inl hs
      · right
        have ha : adj = 1 := by simp [adj, same, hs]
        rw [ha] at had
        exact had
    have hN := R18SortedWord.magnitude_word_nat hi lo d hg hdom
    have hb := A16L.magnitude_bounds _ _ _ _ _ hma.1 hma.2 hmb.1 hmb.2 hg hdom
    split
    · rename_i hn
      have hnlo : 8388608 ≤ n.toNat := UInt32.le_iff_toNat_le.mp hn
      have hnhi : n.toNat ≤ 2164260735 := by rw [show n.toNat = _ from hN]; exact hb.2
      have hs : sh.toNat = R16UInt32Roundtrip.roundedShift n.toNat := by
        by_cases hsign : R2W01c.wordSign hi = R2W01c.wordSign lo
        · have ha : adj = 0 := by simp [adj, same, hsign]
          have hm : n.toNat = (R2W01b.mantissa hi).toNat * 2 ^ d.toNat + (R2W01b.mantissa lo).toNat := by
            rw [show n.toNat = _ from hN]
            simp [A16L.magnitude, hsign, Nat.shiftLeft_eq]
          simpa only [sh, base, bump, ha, r, UInt32.sub_zero] using
            R17Threshold.same_word_shift_from_inputs n d _ _ hma.1 hma.2 hmb.1 hmb.2 hg hm
        · have ha : adj = 1 := by simp [adj, same, hsign]
          have hg0 : 1 ≤ d.toNat := hdom.resolve_left hsign
          have hm : n.toNat = (R2W01b.mantissa hi).toNat * 2 ^ d.toNat - (R2W01b.mantissa lo).toNat := by
            rw [show n.toNat = _ from hN]
            simp [A16L.magnitude, hsign, Nat.shiftLeft_eq]
          simpa only [sh, base, bump, ha, r] using
            R17Threshold.opposite_word_shift_from_inputs n d _ _ hma.1 hma.2 hmb.1 hmb.2 hg0 hg hm hnlo
      split
      · rename_i he
        have hbp : bump.toNat ≤ 1 := by dsimp only [bump]; split <;> decide
        have hE := R17NumericOutput.word_exponent_shift_relation eh el d adj bump
          (by rw [hEH]; omega) hg (by rw [hEH, hEL, hD]; omega) had hbp
        have hE' : e.toNat = R2W01c.wordExp lo + sh.toNat := by
          simpa only [e, sh, base, hEL] using hE
        have hehi : e.toNat < 255 := by
          have h := UInt32.le_iff_toNat_le.mp he
          change e.toNat ≤ 254 at h
          omega
        apply R17NumericOutput.numeric_add_of_alignment x y n sh e (R2W01c.wordSign hi)
          (R2W01c.wordExp lo) hnlo hnhi hs hE' (by omega) hehi
        rcases hp with hp | hp
        · rw [hp.1, hp.2]
          exact R18SortedWord.high_low_model hi lo d hH hL ho hD hg hdom
        · rw [hp.1, hp.2]
          exact R18SortedWord.low_high_model hi lo d hH hL ho hD hg hdom
      · exact hf x y
    · exact hf x y
  · exact hf x y

theorem guarded_spec (f : Binary32 → Binary32 → Binary32)
    (hf : ∀ x y, f x y = ExecFloat.Spec.add x y) (x y : Binary32) :
    R17NumericAdd.guardedAdd f x y = ExecFloat.Spec.add x y := by
  unfold R17NumericAdd.guardedAdd
  dsimp only
  split
  · rename_i hn
    have hn' : (Model.NativeBinary32.expField x.raw.1 - 1 ≤ (253 : UInt32)) ∧
        (Model.NativeBinary32.expField y.raw.1 - 1 ≤ (253 : UInt32)) := by
      simpa only [Bool.and_eq_true, decide_eq_true_eq] using hn
    have hx := normal_field x.raw.1 hn'.1
    have hy := normal_field y.raw.1 hn'.2
    split
    · rename_i ho
      apply sorted_spec f hf x y y.raw.1 x.raw.1 hy hx ?_ (Or.inr ⟨rfl, rfl⟩)
      rw [UInt32.lt_iff_toNat_lt, ex_nat, ex_nat] at ho
      omega
    · rename_i ho
      apply sorted_spec f hf x y x.raw.1 y.raw.1 hx hy ?_ (Or.inl ⟨rfl, rfl⟩)
      rw [UInt32.lt_iff_toNat_lt, ex_nat, ex_nat] at ho
      omega
  · exact hf x y
end Submission.R18AddSpec
