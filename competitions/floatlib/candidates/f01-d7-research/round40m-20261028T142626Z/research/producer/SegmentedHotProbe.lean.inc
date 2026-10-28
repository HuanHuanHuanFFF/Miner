
/- NOT_RUN codegen discriminator, not a BMM replacement. This function ends
   before the first update on a cold iteration and returns the exact state.
   A future outer driver must perform that iteration once and resume at k+1.
   The boundary record is deliberate charged work, not an allocation claim. -/
namespace Submission.R23SegmentedHot
open FloatLib.Floats Competition
open R22IndexedResident8

structure Exit where
  k : USize
  cursor : USize
  q00 : Float32
  q10 : Float32
  q20 : Float32
  q30 : Float32
  q01 : Float32
  q11 : Float32
  q21 : Float32
  q31 : Float32

def run (count a0 a1 a2 a3 stride : USize) (A : Array Binary32) (cache : Array R22Pair8.BP)
    (hA : ∀ j : USize, j < count →
      (a0 + j).toNat < A.size ∧ (a1 + j).toNat < A.size ∧
      (a2 + j).toNat < A.size ∧ (a3 + j).toNat < A.size)
    (k cursor : USize)
    (hB : ∀ t : Nat, k.toNat + t < count.toNat → (advance cursor stride t).toNat < cache.size)
    (q00 q10 q20 q30 q01 q11 q21 q31 : Float32) : Exit :=
  if hk : k < count then
    let u0 := (A.uget (a0 + k) (hA k hk).1).raw.1
    let u1 := (A.uget (a1 + k) (hA k hk).2.1).raw.1
    let u2 := (A.uget (a2 + k) (hA k hk).2.2.1).raw.1
    let u3 := (A.uget (a3 + k) (hA k hk).2.2.2).raw.1
    if R2W01b.fastOK u0 && R2W01b.fastOK u1 && R2W01b.fastOK u2 && R2W01b.fastOK u3 then
      have hb : cursor.toNat < cache.size := by
        have h := hB 0 (by have hh := USize.lt_iff_toNat_lt.mp hk; omega)
        simpa only [advance] using h
      have nextB : ∀ t : Nat, (k + 1).toNat + t < count.toNat →
          (advance (cursor + stride) stride t).toNat < cache.size := by
        intro t ht
        rw [advance_shift]
        apply hB (t + 1)
        rw [Packed10Index.stepNat hk] at ht
        omega
      let f0 := R2W01b.tableProduct u0
      let f1 := R2W01b.tableProduct u1
      let f2 := R2W01b.tableProduct u2
      let f3 := R2W01b.tableProduct u3
      let b := cache.uget cursor hb
      run count a0 a1 a2 a3 stride A cache hA (k + 1) (cursor + stride) nextB
        (q00 + f0 * b.s0) (q10 + f1 * b.s0) (q20 + f2 * b.s0) (q30 + f3 * b.s0)
        (q01 + f0 * b.s1) (q11 + f1 * b.s1) (q21 + f2 * b.s1) (q31 + f3 * b.s1)
    else ⟨k, cursor, q00, q10, q20, q30, q01, q11, q21, q31⟩
  else ⟨k, cursor, q00, q10, q20, q30, q01, q11, q21, q31⟩
termination_by count.toNat - k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)

end Submission.R23SegmentedHot
