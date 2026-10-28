/- Leaf transport attempt for exact8e. NOT_COMPILED; not a public BMM proof.
   No runtime declaration from8e is edited or replaced. -/
namespace Submission.R22IndexedResident8
open FloatLib.Floats Competition

theorem uget_getD {α : Type} (A : Array α) (i : USize) (hi : i.toNat < A.size) (d : α) :
    A.uget i hi = A.getD i.toNat d := by
  simp [Array.uget, Array.getD, hi]

abbrev ReadsA (n base : Nat) (A : Array Binary32) : Prop :=
  ∀ j : USize, j < USize.ofNat n →
    (USize.ofNat base + j).toNat < A.size ∧
    (USize.ofNat (base + n) + j).toNat < A.size ∧
    (USize.ofNat (base + 2 * n) + j).toNat < A.size ∧
    (USize.ofNat (base + 3 * n) + j).toNat < A.size

abbrev ReadsB (count k cursor stride : USize) (cache : Array BP) : Prop :=
  ∀ t : Nat, k.toNat + t < count.toNat → (advance cursor stride t).toNat < cache.size

theorem wordLoop_eq (p n baseA baseC : Nat) (A : Array Binary32) (cache : Array BP)
    (bound : TileBounds p n baseA baseC A.size cache.size) (hA : ReadsA n baseA A)
    (k cursor : USize) (hB : ReadsB (USize.ofNat n) k cursor (USize.ofNat (R22Pair8.groups p)) cache)
    (hcur : cursor = advance (USize.ofNat baseC) (USize.ofNat (R22Pair8.groups p)) k.toNat)
    (q00 q10 q20 q30 q01 q11 q21 q31 : Float32) :
    wordLoop (USize.ofNat n) (USize.ofNat baseA) (USize.ofNat (baseA + n))
      (USize.ofNat (baseA + 2 * n)) (USize.ofNat (baseA + 3 * n))
      (USize.ofNat (R22Pair8.groups p)) A cache hA k cursor hB q00 q10 q20 q30 q01 q11 q21 q31 =
    R22Resident8.loop n baseA (baseA + n) (baseA + 2 * n) (baseA + 3 * n)
      (R22Pair8.groups p) A cache k.toNat (baseC + k.toNat * R22Pair8.groups p)
      q00 q10 q20 q30 q01 q11 q21 q31 := by
  by_cases hk : k < USize.ofNat n
  · have hkn : k.toNat < n := by
      simpa only [USize.toNat_ofNat_of_lt' bound.nword] using USize.lt_iff_toNat_lt.mp hk
    have hal := bound.alast
    have haw := bound.aword
    have hcl := bound.blast
    have hcw := bound.cword
    have hb0 : baseA < USize.size := by omega
    have hb1 : baseA + n < USize.size := by omega
    have hb2 : baseA + 2 * n < USize.size := by omega
    have hb3 : baseA + 3 * n < USize.size := by omega
    have hbc : baseC < USize.size := by omega
    have hg : R22Pair8.groups p < USize.size := by
      have hm := Nat.mul_le_mul_right (R22Pair8.groups p)
        (show 1 ≤ n - 1 by have hn := bound.positive; omega)
      simp only [Nat.one_mul] at hm
      omega
    have hc_read : baseC + k.toNat * R22Pair8.groups p < cache.size := by
      have hm := Nat.mul_le_mul_right (R22Pair8.groups p) (show k.toNat ≤ n - 1 by omega)
      omega
    have hcursor : cursor.toNat = baseC + k.toNat * R22Pair8.groups p := by
      rw [hcur]
      exact advance_toNat baseC (R22Pair8.groups p) hbc hg k.toNat (Nat.lt_trans hc_read hcw)
    have index (base : Nat) (hb : base < USize.size) (hl : base + (n - 1) < A.size) :
        (USize.ofNat base + k).toNat = base + k.toNat := by
      have ha := Packed10Index.boundA base n k.toNat A.size hl hkn
      rw [Packed10Index.addNat _ _ (by rw [USize.toNat_ofNat_of_lt' hb]; exact Nat.lt_trans ha haw),
        USize.toNat_ofNat_of_lt' hb]
    have hi0 := index baseA hb0 (by omega)
    have hi1 := index (baseA + n) hb1 (by omega)
    have hi2 := index (baseA + 2 * n) hb2 (by omega)
    have hi3 := index (baseA + 3 * n) hb3 hal
    have nextB : ReadsB (USize.ofNat n) (k + 1)
        (cursor + USize.ofNat (R22Pair8.groups p)) (USize.ofNat (R22Pair8.groups p)) cache := by
      intro t ht
      rw [advance_shift]
      apply hB (t + 1)
      rw [Packed10Index.stepNat hk] at ht
      omega
    have nextCur : cursor + USize.ofNat (R22Pair8.groups p) =
        advance (USize.ofNat baseC) (USize.ofNat (R22Pair8.groups p)) (k + 1).toNat := by
      rw [Packed10Index.stepNat hk, hcur]
      rfl
    rw [wordLoop, dif_pos hk, R22Resident8.loop, dif_pos hkn]
    dsimp only
    rw [wordLoop_eq p n baseA baseC A cache bound hA (k + 1)
      (cursor + USize.ofNat (R22Pair8.groups p)) nextB nextCur]
    simp only [uget_getD, hi0, hi1, hi2, hi3, hcursor, Packed10Index.stepNat hk,
      Nat.add_mul, Nat.one_mul, Nat.add_assoc]
  · have hkn : ¬k.toNat < n := by
      simpa only [USize.lt_iff_toNat_lt, USize.toNat_ofNat_of_lt' bound.nword] using hk
    rw [wordLoop, dif_neg hk, R22Resident8.loop, dif_neg hkn]
termination_by n - k.toNat
decreasing_by
  have hh : k < USize.ofNat n := by assumption
  simpa only [USize.toNat_ofNat_of_lt' bound.nword] using Packed10Index.next_decreases hh

theorem within_eq (p n baseA baseC : Nat) (A : Array Binary32) (cache : Array BP)
    (bound : TileBounds p n baseA baseC A.size cache.size) :
    within p n baseA baseC A cache bound =
      R22Resident8.loop n baseA (baseA + n) (baseA + 2 * n) (baseA + 3 * n)
        (R22Pair8.groups p) A cache 0 baseC
        Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
        Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 := by
  unfold within
  rw [wordLoop_eq p n baseA baseC A cache bound]
  all_goals simp only [USize.toNat_zero, advance, Nat.zero_mul, Nat.add_zero]

end Submission.R22IndexedResident8
