/- Prepared optional next mechanism inside Submission.R7SumRepair, after suffixLoop_eq.
   It compares two concrete scanners without a quiet premise; only the existing
   suffixLoop_eq theorem transports their result to real addition under qQuiet.
   No integrated candidate or Lean acceptance is claimed for this draft. -/

theorem suffixLoop_no_signaling {n : Nat} (x : Vector Binary32 n) (k : Nat)
    (acc : Binary32)
    (htail : ∀ i : Fin n, k ≤ i.val → R7W02.rawSNaN (x.get i).raw.1 = false) :
    suffixLoop x k acc = acc := by
  rw [suffixLoop]
  split
  · rename_i hk
    have hs := htail ⟨k, hk⟩ (by omega)
    have hstep : R7W02.step acc (x.get ⟨k, hk⟩) = acc := by
      simp [R7W02.step, hs]
    rw [hstep]
    exact suffixLoop_no_signaling x (k + 1) acc (fun i hi => htail i (by omega))
  · rfl
termination_by n - k

theorem suffixLoop_last_signaling {n : Nat} (x : Vector Binary32 n)
    (k j : Nat) (acc : Binary32) (hkj : k ≤ j) (hj : j < n)
    (hs : R7W02.rawSNaN (x.get ⟨j, hj⟩).raw.1 = true)
    (htail : ∀ i : Fin n, j < i.val → R7W02.rawSNaN (x.get i).raw.1 = false) :
    suffixLoop x k acc = R7W02.fromRaw (R7W02.quietRaw (x.get ⟨j, hj⟩).raw.1) := by
  have hk : k < n := by omega
  rw [suffixLoop, dif_pos hk]
  by_cases he : k = j
  · subst k
    have hstep : R7W02.step acc (x.get ⟨j, hj⟩) =
        R7W02.fromRaw (R7W02.quietRaw (x.get ⟨j, hj⟩).raw.1) := by
      simp [R7W02.step, hs]
    rw [hstep]
    exact suffixLoop_no_signaling x (j + 1) _ (fun i hi => htail i (by omega))
  · exact suffixLoop_last_signaling x (k + 1) j _ (by omega) hj hs htail
termination_by n - k

/-- Read the existing Vector backwards; no reverse/map/index list is allocated.
Stop at the last signaling original word, otherwise retain the supplied seed word. -/
def reverseSuffixLoop {n : Nat} (x : Vector Binary32 n) (start count : Nat)
    (hc : count ≤ n) (acc : Binary32) : Binary32 :=
  if hs : start < count then
    let last : Fin n := ⟨count - 1, by omega⟩
    if R7W02.rawSNaN (x.get last).raw.1 then
      R7W02.fromRaw (R7W02.quietRaw (x.get last).raw.1)
    else reverseSuffixLoop x start (count - 1) (by omega) acc
  else acc
termination_by count

theorem reverseSuffixLoop_eq {n : Nat} (x : Vector Binary32 n) (start count : Nat)
    (hc : count ≤ n) (acc : Binary32)
    (htail : ∀ i : Fin n, count ≤ i.val → R7W02.rawSNaN (x.get i).raw.1 = false) :
    reverseSuffixLoop x start count hc acc = suffixLoop x start acc := by
  rw [reverseSuffixLoop]
  split
  · rename_i hs
    dsimp only
    split
    · rename_i hnan
      exact (suffixLoop_last_signaling x start (count - 1) acc (by omega)
        (by omega) hnan (fun i hi => htail i (by omega))).symm
    · rename_i hnan
      have hfalse : R7W02.rawSNaN (x.get ⟨count - 1, by omega⟩).raw.1 = false := by
        cases h : R7W02.rawSNaN (x.get ⟨count - 1, by omega⟩).raw.1 <;> simp_all
      have htail' : ∀ i : Fin n, count - 1 ≤ i.val →
          R7W02.rawSNaN (x.get i).raw.1 = false := by
        intro i hi
        by_cases he : i.val = count - 1
        · have hi' : i = (⟨count - 1, by omega⟩ : Fin n) := Fin.ext he
          simpa only [hi'] using hfalse
        · exact htail i (by omega)
      exact reverseSuffixLoop_eq x start (count - 1) (by omega) acc htail'
  · rename_i hs
    exact (suffixLoop_no_signaling x start acc (fun i hi => htail i (by omega))).symm
termination_by count

def reverseSuffix {n : Nat} (x : Vector Binary32 n) (start : Nat)
    (acc : Binary32) : Binary32 := reverseSuffixLoop x start n (by omega) acc

theorem reverseSuffix_eq {n : Nat} (x : Vector Binary32 n) (start : Nat)
    (acc : Binary32) : reverseSuffix x start acc = suffixLoop x start acc := by
  exact reverseSuffixLoop_eq x start n (by omega) acc (fun i hi => by omega)
