/- R19 structural-only draft. Insert inside Submission.R15PackedB2 immediately
   before group. Exact raw A and packed B are retained; no A preparation or tiles.
   NOT_COMPILED: the complete source must pass the original gate on a runner. -/
namespace Indexed

theorem ugetA_getD (A : Array Binary32) (i : USize) (h : i.toNat < A.size) :
    A.uget i h = A.getD i.toNat posZero := by
  simp [Array.uget, Array.getD, h]

theorem ugetB_get {n : Nat} (B : Vector B2 n) (i : USize)
    (hi : i.toNat < n) :
    B.toArray.uget i (by simpa only [B.size_toArray] using hi) =
      B.get ⟨i.toNat, hi⟩ := by
  rfl

def wordLoop {n : Nat} (count baseA : USize) (A : Array Binary32)
    (B : Vector B2 n) (hn : count.toNat = n)
    (hA : baseA.toNat + (count.toNat - 1) < A.size)
    (hAS : A.size < USize.size) (k : USize) (s0 s1 : Float32) : R15ThinPairs.F2 :=
  if hk : k < count then
    have hkn : k.toNat < n := by
      rw [← hn]
      exact USize.lt_iff_toNat_lt.mp hk
    have ha := Packed10Index.boundA baseA.toNat count.toNat k.toNat A.size hA
      (USize.lt_iff_toNat_lt.mp hk)
    let a := ExecFloat.Binary.toFloat32 (A.uget (baseA + k)
      (by rw [Packed10Index.addNat baseA k (Nat.lt_trans ha hAS)]; exact ha))
    let b := B.toArray.uget k (by simpa only [B.size_toArray] using hkn)
    wordLoop count baseA A B hn hA hAS (k + 1) (s0 + a * b.s0) (s1 + a * b.s1)
  else ⟨s0, s1⟩
termination_by count.toNat - k.toNat
decreasing_by
  apply Packed10Index.next_decreases
  assumption

theorem wordLoop_eq {n : Nat} (count baseA : USize) (A : Array Binary32)
    (B : Vector B2 n) (hn : count.toNat = n)
    (hA : baseA.toNat + (count.toNat - 1) < A.size)
    (hAS : A.size < USize.size) (k : USize) (s0 s1 : Float32) :
    wordLoop count baseA A B hn hA hAS k s0 s1 =
      loop n baseA.toNat A B k.toNat s0 s1 := by
  rw [wordLoop]
  split
  · rename_i hk
    have hkn : k.toNat < n := by
      rw [← hn]
      exact USize.lt_iff_toNat_lt.mp hk
    have ha := Packed10Index.boundA baseA.toNat count.toNat k.toNat A.size hA
      (USize.lt_iff_toNat_lt.mp hk)
    rw [loop, dif_pos hkn]
    dsimp only
    rw [wordLoop_eq, Packed10Index.stepNat hk]
    simp only [ugetA_getD, Packed10Index.addNat baseA k (Nat.lt_trans ha hAS), ugetB_get]
    rfl
  · rename_i hk
    have hkn : ¬ k.toNat < n := by
      rw [← hn]
      simpa only [USize.lt_iff_toNat_lt] using hk
    rw [loop, dif_neg hkn]
termination_by count.toNat - k.toNat
decreasing_by
  apply Packed10Index.next_decreases
  assumption

@[inline] def within (n baseA : Nat) (A : Array Binary32) (B : Vector B2 n)
    (hn : n < USize.size) (ha : baseA < USize.size)
    (hA : baseA + (n - 1) < A.size) (hAS : A.size < USize.size) : R15ThinPairs.F2 :=
  wordLoop (USize.ofNat n) (USize.ofNat baseA) A B
    (USize.toNat_ofNat_of_lt' hn)
    (by simpa only [USize.toNat_ofNat_of_lt' hn, USize.toNat_ofNat_of_lt' ha] using hA)
    hAS 0 Packed10.zero32 Packed10.zero32

theorem within_eq (n baseA : Nat) (A : Array Binary32) (B : Vector B2 n)
    (hn : n < USize.size) (ha : baseA < USize.size)
    (hA : baseA + (n - 1) < A.size) (hAS : A.size < USize.size) :
    within n baseA A B hn ha hA hAS =
      loop n baseA A B 0 Packed10.zero32 Packed10.zero32 := by
  simp only [within, wordLoop_eq, USize.toNat_ofNat_of_lt' hn,
    USize.toNat_ofNat_of_lt' ha, USize.toNat_zero]

@[inline] def runDot (n baseA : Nat) (A : Array Binary32) (B : Vector B2 n) : R15ThinPairs.F2 :=
  if h : n < USize.size ∧ baseA < USize.size ∧
      baseA + (n - 1) < A.size ∧ A.size < USize.size then
    within n baseA A B h.1 h.2.1 h.2.2.1 h.2.2.2
  else loop n baseA A B 0 Packed10.zero32 Packed10.zero32

theorem runDot_eq (n baseA : Nat) (A : Array Binary32) (B : Vector B2 n) :
    runDot n baseA A B = loop n baseA A B 0 Packed10.zero32 Packed10.zero32 := by
  unfold runDot
  split
  · rename_i h
    exact within_eq n baseA A B h.1 h.2.1 h.2.2.1 h.2.2.2
  · rfl

end Indexed

