namespace R7SinglePassSum

open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

/-- The existing decoder's low test cannot reject an infinity or NaN magnitude. -/
theorem low_reject_finite (a : UInt32)
    (h : ¬ ((0x0bffffff : UInt32) ≤ a - 1)) :
    a < (0x7f800000 : UInt32) := by
  by_cases hz : a = 0
  · subst a
    exact False.elim (h (by decide))
  · have hpos : 0 < a := UInt32.pos_iff_ne_zero.mpr hz
    have hone : (1 : UInt32) ≤ a := by
      change 1 ≤ a.toNat
      change 0 < a.toNat at hpos
      omega
    have hnat : ¬ 201326591 ≤ (a - 1).toNat := h
    rw [UInt32.toNat_sub_of_le a 1 hone] at hnat
    change a.toNat < 2139095040
    change ¬ 201326591 ≤ a.toNat - 1 at hnat
    omega

theorem raw_nonNaN_of_le (u : UInt32)
    (h : R2W01b.magnitude u ≤ (0x7f800000 : UInt32)) :
    R7W12.rawNotNaN u = true := by
  unfold R7W12.rawNotNaN
  rw [decide_eq_true_eq]
  exact h

theorem raw_nan_of_high_reject (u : UInt32)
    (h : ¬ R2W01b.magnitude u < (0x7f800000 : UInt32))
    (hi : R2W01b.magnitude u ≠ (0x7f800000 : UInt32)) :
    R7W12.rawNotNaN u = false := by
  have hgt : ¬ R2W01b.magnitude u ≤ (0x7f800000 : UInt32) := by
    simp only [UInt32.lt_iff_toNat_lt, UInt32.le_iff_toNat_le,
      ← UInt32.toNat_inj] at h hi ⊢
    omega
  exact decide_eq_false hgt

theorem table_eq (u : UInt32)
    (hl : (0x0bffffff : UInt32) ≤ R2W01b.magnitude u - 1)
    (hh : R2W01b.magnitude u < (0x7f800000 : UInt32)) :
    R2W01b.tableProduct u = Float32.ofBits u := by
  have h := R2W01c.convert_eq u
  have hg : R2W01b.fastOK u = true := by simp [R2W01b.fastOK, hl, hh]
  simpa only [R2W01b.convert, if_pos hg] using h

/-- The native accumulator may already be canonical NaN. Only the original input is classified. -/
theorem native_step_eq (acc : Float32) (q : Binary32) (value : Float32)
    (hv : value = ExecFloat.Binary.toFloat32 q)
    (hq : R7W12.rawNotNaN q.raw.1 = true) :
    ExecFloat.Binary.ofFloat32 (acc + value) =
      Submission.add (ExecFloat.Binary.ofFloat32 acc) q := by
  have hn : (ExecFloat.Binary.toFloat32 q).isNaN = false := by
    have h := R7W12.rawNotNaN_eq_native_classifier q
    rw [hq] at h
    cases hh : (ExecFloat.Binary.toFloat32 q).isNaN <;> simp_all
  rw [hv, R7W12.ofFloat32_add, NotNaNProbe.roundtrip q hn, Submission.add_eq]

/-- A first raw NaN input produces a quiet result, including after earlier invalid arithmetic. -/
theorem repair_quiet (acc : Float32) (q : Binary32)
    (hq : R7W12.rawNotNaN q.raw.1 = false) :
    Model.isQNaN (ExecFloat.Binary.toModel
      (Submission.add (ExecFloat.Binary.ofFloat32 acc) q)) = true := by
  have hn : (ExecFloat.Binary.toFloat32 q).isNaN = true := by
    have h := R7W12.rawNotNaN_eq_native_classifier q
    rw [hq] at h
    cases hh : (ExecFloat.Binary.toFloat32 q).isNaN <;> simp_all
  have he : (R7W05.nativeSumStep acc q).isNaN = true := by
    unfold R7W05.nativeSumStep
    rw [R7W05.native_add_nan_right _ _ hn]
    rfl
  simpa only [R7W05.repairSumStep, Submission.add_eq] using
    R7W05.repairSumStep_isQNaN acc q he

/-- Preserve existing decoder decisions; classify Inf versus NaN only in its high cold branch. -/
def natLoop {n : Nat} (x : Vector Binary32 n) (k : Nat) (acc : Float32) : Binary32 :=
  if hk : k < n then
    let q := x.get ⟨k, hk⟩
    let u := q.raw.1
    let a := R2W01b.magnitude u
    if hl : (0x0bffffff : UInt32) ≤ a - 1 then
      if hh : a < (0x7f800000 : UInt32) then
        natLoop x (k + 1) (acc + R2W01b.tableProduct u)
      else if hi : a = (0x7f800000 : UInt32) then
        natLoop x (k + 1) (acc + Float32.ofBits u)
      else R7SumRepair.suffixLoop x (k + 1)
        (Submission.add (ExecFloat.Binary.ofFloat32 acc) q)
    else natLoop x (k + 1) (acc + Float32.ofBits u)
  else ExecFloat.Binary.ofFloat32 acc
termination_by n - k

theorem natLoop_eq {n : Nat} (x : Vector Binary32 n) (k : Nat) (acc : Float32) :
    natLoop x k acc =
      Fin.foldl.loop n (R7SumRepair.step x) (ExecFloat.Binary.ofFloat32 acc) k := by
  rw [natLoop]
  split
  · rename_i hk
    rw [Fin.foldl.loop, dif_pos hk]
    dsimp only
    split
    · rename_i hl
      split
      · rename_i hh
        have hi := natLoop_eq x (k + 1)
          (acc + R2W01b.tableProduct (x.get ⟨k, hk⟩).raw.1)
        rw [native_step_eq acc (x.get ⟨k, hk⟩) _
          (table_eq _ hl hh) (raw_nonNaN_of_le _ (UInt32.le_of_lt hh))] at hi
        exact hi
      · rename_i hh
        split
        · rename_i hinf
          have hle : R2W01b.magnitude (x.get ⟨k, hk⟩).raw.1 ≤
              (0x7f800000 : UInt32) := by
            rw [hinf]
          have hi := natLoop_eq x (k + 1)
            (acc + Float32.ofBits (x.get ⟨k, hk⟩).raw.1)
          rw [native_step_eq acc (x.get ⟨k, hk⟩) _ rfl (raw_nonNaN_of_le _ hle)] at hi
          exact hi
        · rename_i hinf
          exact R7SumRepair.suffixLoop_eq x (k + 1) _
            (repair_quiet acc (x.get ⟨k, hk⟩) (raw_nan_of_high_reject _ hh hinf))
    · rename_i hl
      have hle := UInt32.le_of_lt (low_reject_finite _ hl)
      have hi := natLoop_eq x (k + 1)
        (acc + Float32.ofBits (x.get ⟨k, hk⟩).raw.1)
      rw [native_step_eq acc (x.get ⟨k, hk⟩) _ rfl (raw_nonNaN_of_le _ hle)] at hi
      exact hi
  · rename_i hk
    rw [Fin.foldl.loop, dif_neg hk]
termination_by n - k

/-- Machine-indexed ordinary prefix, with a cold transition to the proven raw suffix scan. -/
def loop {n : Nat} (x : Vector Binary32 n) (count : USize)
    (hn : count.toNat = n) (k : USize) (acc : Float32) : Binary32 :=
  if hk : k < count then
    have hkn : k.toNat < n := by rw [← hn]; exact USize.lt_iff_toNat_lt.mp hk
    let q := x.toArray.uget k (by simpa only [x.size_toArray] using hkn)
    let u := q.raw.1
    let a := R2W01b.magnitude u
    if hl : (0x0bffffff : UInt32) ≤ a - 1 then
      if hh : a < (0x7f800000 : UInt32) then
        loop x count hn (k + 1) (acc + R2W01b.tableProduct u)
      else if hi : a = (0x7f800000 : UInt32) then
        loop x count hn (k + 1) (acc + Float32.ofBits u)
      else R7SumRepair.suffixLoop x (k.toNat + 1)
        (Submission.add (ExecFloat.Binary.ofFloat32 acc) q)
    else loop x count hn (k + 1) (acc + Float32.ofBits u)
  else ExecFloat.Binary.ofFloat32 acc
termination_by count.toNat - k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)

theorem loop_eq {n : Nat} (x : Vector Binary32 n) (count : USize)
    (hn : count.toNat = n) (k : USize) (acc : Float32) :
    loop x count hn k acc = natLoop x k.toNat acc := by
  rw [loop]
  split
  · rename_i hk
    have hkn : k.toNat < n := by rw [← hn]; exact USize.lt_iff_toNat_lt.mp hk
    rw [natLoop, dif_pos hkn]
    dsimp only
    split
    · split
      · rw [loop_eq, Packed10Index.stepNat hk]
        rfl
      · split
        · rw [loop_eq, Packed10Index.stepNat hk]
          rfl
        · rfl
    · rw [loop_eq, Packed10Index.stepNat hk]
      rfl
  · rename_i hk
    have hkn : ¬ k.toNat < n := by
      rw [← hn]
      simpa only [USize.lt_iff_toNat_lt] using hk
    rw [natLoop, dif_neg hkn]
termination_by count.toNat - k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)

@[inline] def run {n : Nat} (x : Vector Binary32 n) : Binary32 :=
  if hn : n < USize.size then
    loop x (USize.ofNat n) (USize.toNat_ofNat_of_lt' hn) 0 (Float32.ofBits 0)
  else natLoop x 0 (Float32.ofBits 0)

theorem run_spec : ∀ (n : Nat) (x : Vector Binary32 n), run x = sumSpec x.get := by
  intro n x
  have hrun : run x = natLoop x 0 (Float32.ofBits 0) := by
    unfold run
    split
    · rw [loop_eq, USize.toNat_zero]
    · rfl
  rw [hrun, natLoop_eq]
  have hstep : R7SumRepair.step x = fun (acc : Binary32) (i : Fin n) =>
      ExecFloat.add acc (x.get i) := by
    funext acc i
    exact congrArg (fun f : Binary32 → Binary32 → Binary32 => f acc (x.get i))
      Submission.add_eq
  change Fin.foldl n (R7SumRepair.step x) posZero = sumSpec x.get
  rw [hstep, Fin.foldl_eq_finRange_foldl]

end R7SinglePassSum
