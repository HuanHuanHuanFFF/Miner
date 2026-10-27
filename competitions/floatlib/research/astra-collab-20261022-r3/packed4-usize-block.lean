namespace Packed4Index

open Packed4

theorem addNat (a b : USize) (h : a.toNat + b.toNat < USize.size) :
    (a + b).toNat = a.toNat + b.toNat := by
  rw [USize.toNat_add]
  exact Nat.mod_eq_of_lt h

theorem stepNat {n k : USize} (hk : k < n) : (k + 1).toNat = k.toNat + 1 := by
  rw [USize.toNat_add, USize.toNat_one]
  have hkn := USize.lt_iff_toNat_lt.mp hk
  have hn := USize.toNat_lt_size n
  apply Nat.mod_eq_of_lt
  change k.toNat + 1 < USize.size
  omega

theorem next_decreases {n k : USize} (hk : k < n) :
    n.toNat - (k + 1).toNat < n.toNat - k.toNat := by
  rw [stepNat hk]
  have hkn := USize.lt_iff_toNat_lt.mp hk
  omega

theorem boundA (base n k size : Nat) (h : base + (n - 1) < size) (hk : k < n) :
    base + k < size := by omega

theorem ugetA_getD (A : Array Float32) (i : USize) (h : i.toNat < A.size) :
    A.uget i h = A.getD i.toNat zero32 := by
  simp [Array.uget, Array.getD, h]

theorem ugetB_get {n : Nat} (B : Vector F4 n) (i : USize)
    (hi : i.toNat < n) :
    B.toArray.uget i (by simpa only [B.size_toArray] using hi) =
      B.get ⟨i.toNat, hi⟩ := by
  rfl

/-- The bounds are established once; each iteration reads with machine-word indices. -/
def loop {n : Nat} (count baseA : USize) (A : Array Float32) (B : Vector F4 n)
    (hn : count.toNat = n)
    (hA : baseA.toNat + (count.toNat - 1) < A.size)
    (hAS : A.size < USize.size)
    (k : USize) (s0 s1 s2 s3 : Float32) : F4 :=
  if hk : k < count then
    have hkn : k.toNat < n := by
      rw [← hn]
      exact USize.lt_iff_toNat_lt.mp hk
    have ha := boundA baseA.toNat count.toNat k.toNat A.size hA
      (USize.lt_iff_toNat_lt.mp hk)
    let a := A.uget (baseA + k)
      (by rw [addNat baseA k (Nat.lt_trans ha hAS)]; exact ha)
    let v := B.toArray.uget k (by simpa only [B.size_toArray] using hkn)
    loop count baseA A B hn hA hAS (k + 1)
      (s0 + a * v.s0) (s1 + a * v.s1)
      (s2 + a * v.s2) (s3 + a * v.s3)
  else ⟨s0, s1, s2, s3⟩
termination_by count.toNat - k.toNat
decreasing_by
  apply next_decreases
  assumption

theorem loop_eq {n : Nat} (count baseA : USize) (A : Array Float32) (B : Vector F4 n)
    (hn : count.toNat = n)
    (hA : baseA.toNat + (count.toNat - 1) < A.size)
    (hAS : A.size < USize.size)
    (k : USize) (s0 s1 s2 s3 : Float32) :
    loop count baseA A B hn hA hAS k s0 s1 s2 s3 =
      Packed4.dot4 n baseA.toNat A B k.toNat s0 s1 s2 s3 := by
  rw [loop]
  split
  · rename_i hk
    have hkn : k.toNat < n := by
      rw [← hn]
      exact USize.lt_iff_toNat_lt.mp hk
    have ha := boundA baseA.toNat count.toNat k.toNat A.size hA
      (USize.lt_iff_toNat_lt.mp hk)
    rw [Packed4.dot4, dif_pos hkn]
    dsimp only
    rw [loop_eq, stepNat hk]
    simp only [ugetA_getD, addNat baseA k (Nat.lt_trans ha hAS), ugetB_get]
  · rename_i hk
    have hkn : ¬ k.toNat < n := by
      rw [← hn]
      simpa only [USize.lt_iff_toNat_lt] using hk
    rw [Packed4.dot4, dif_neg hkn]
termination_by count.toNat - k.toNat
decreasing_by
  apply next_decreases
  assumption

@[inline] def within (n baseA : Nat) (A : Array Float32) (B : Vector F4 n)
    (hn : n < USize.size) (ha : baseA < USize.size)
    (hA : baseA + (n - 1) < A.size) (hAS : A.size < USize.size) : F4 :=
  loop (USize.ofNat n) (USize.ofNat baseA) A B
    (USize.toNat_ofNat_of_lt' hn)
    (by simpa only [USize.toNat_ofNat_of_lt' hn, USize.toNat_ofNat_of_lt' ha] using hA)
    hAS 0 zero32 zero32 zero32 zero32

theorem within_eq (n baseA : Nat) (A : Array Float32) (B : Vector F4 n)
    (hn : n < USize.size) (ha : baseA < USize.size)
    (hA : baseA + (n - 1) < A.size) (hAS : A.size < USize.size) :
    within n baseA A B hn ha hA hAS =
      Packed4.dot4 n baseA A B 0 zero32 zero32 zero32 zero32 := by
  simp only [within, loop_eq, USize.toNat_ofNat_of_lt' hn,
    USize.toNat_ofNat_of_lt' ha, USize.toNat_zero]

@[inline] def runDot (n baseA : Nat) (A : Array Float32) (B : Vector F4 n) : F4 :=
  if h : n < USize.size ∧ baseA < USize.size ∧
      baseA + (n - 1) < A.size ∧ A.size < USize.size then
    within n baseA A B h.1 h.2.1 h.2.2.1 h.2.2.2
  else Packed4.dot4 n baseA A B 0 zero32 zero32 zero32 zero32

theorem runDot_eq (n baseA : Nat) (A : Array Float32) (B : Vector F4 n) :
    runDot n baseA A B =
      Packed4.dot4 n baseA A B 0 zero32 zero32 zero32 zero32 := by
  unfold runDot
  split
  · rename_i h
    exact within_eq n baseA A B h.1 h.2.1 h.2.2.1 h.2.2.2
  · rfl

end Packed4Index

