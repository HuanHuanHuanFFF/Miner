/- R11-W01 diagnostic appendix. NOT_RUN.
Append after the exact Kernel in a separate audit file.
Do not submit this appendix as part of the <=256000-byte Kernel.
These are checks/derived theorems, not new runtime definitions or assumptions. -/
namespace Submission.R11W01Diagnostics
open FloatLib.Floats Competition

-- The original four public specification types, checked without weakening.
example : ∀ x y : Binary32, Submission.add x y = ExecFloat.Spec.add x y :=
  Submission.add_spec

example : ∀ x y : Binary32, Submission.mul x y = ExecFloat.Spec.mul x y :=
  Submission.mul_spec

example : ∀ (n : Nat) (x : Vector Binary32 n),
    Submission.sum x = sumSpec x.get :=
  Submission.sum_spec

example : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*p)),
    (Submission.bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get :=
  Submission.bmm_spec

-- Real selected raw reads: no arbitrary read function or correctness hypothesis.
theorem selected_read_bounds (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (r : Fin (batch*m)) (j : Fin p) (k : Fin n) :
    r.val*n+k.val < A.toArray.size ∧
      (r.val/m*n*p+j.val)+k.val*p < B.toArray.size := by
  have hm : 0<m := by
    by_contra h
    have hm0 : m=0 := by omega
    have hr := r.isLt
    simp only [hm0, Nat.mul_zero] at hr
    omega
  have hb : r.val/m < batch := (Nat.div_lt_iff_lt_mul hm).2 r.isLt
  have ha1 : (r.val+1)*n ≤ batch*m*n :=
    Nat.mul_le_mul_right n (Nat.succ_le_of_lt r.isLt)
  simp only [Nat.add_mul, Nat.one_mul] at ha1
  have ha : r.val*n+k.val < batch*m*n := by
    have hk := k.isLt
    omega
  have hb1 : (r.val/m+1)*n ≤ batch*n :=
    Nat.mul_le_mul_right n (Nat.succ_le_of_lt hb)
  simp only [Nat.add_mul, Nat.one_mul] at hb1
  have hbk : r.val/m*n+k.val < batch*n := by
    have hk := k.isLt
    omega
  have hb2 : (r.val/m*n+k.val+1)*p ≤ batch*n*p :=
    Nat.mul_le_mul_right p (Nat.succ_le_of_lt hbk)
  simp only [Nat.add_mul, Nat.one_mul] at hb2
  have hb3 : (r.val/m*n*p+j.val)+k.val*p < batch*n*p := by
    have hj := j.isLt
    omega
  constructor
  · simpa only [A.size_toArray] using ha
  · simpa only [B.size_toArray] using hb3

-- Derive the actual machine read premise and no-wrap fact.
theorem packet_machine_read (n : Nat) (v : Vector R11CrossRows.P12 n)
    (count k : USize) (hn : count.toNat=n) (hk : k<count) :
    v.toArray.uget k (by
      rw [v.size_toArray, ← hn]
      exact USize.lt_iff_toNat_lt.mp hk) =
      v.get ⟨k.toNat, by rw [← hn]; exact USize.lt_iff_toNat_lt.mp hk⟩ ∧
      (k+1).toNat=k.toNat+1 ∧
      count.toNat-(k+1).toNat < count.toNat-k.toNat := by
  exact ⟨rfl, Packed10Index.stepNat hk, Packed10Index.next_decreases hk⟩

-- The source's complete concrete core-to-original-spec chain.
theorem core_original_spec (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (hn : n<USize.size) (hp : p≤2) :
    (R11CrossRows.core batch m n p A B hn hp).get =
      bmmSpec batch m n p A.get B.get := by
  rw [R11CrossRows.core_eq_rows, DirectRows.core_eq,
    DirectSmall.core_eq_reference]
  exact referenceBmm_spec batch m n p A B

end Submission.R11W01Diagnostics

#check @Submission.R11CrossRows.pack_a
#check @Submission.R11CrossRows.pack_b
#check @Submission.R11CrossRows.natLoop_lane
#check @Submission.R11CrossRows.wordLoop_eq
#check @Submission.R11CrossRows.dot8_lane
#check @Submission.R11CrossRows.finish8_word
#check @Submission.R11CrossRows.blockAt_word
#check @Submission.R11CrossRows.blockRows_word
#check @Submission.R11CrossRows.rowWord_eq
#check @Submission.R11CrossRows.core_eq_rows
#check @Submission.add_spec
#check @Submission.mul_spec
#check @Submission.sum_spec
#check @Submission.bmm_spec

#print axioms Submission.add_spec
#print axioms Submission.mul_spec
#print axioms Submission.sum_spec
#print axioms Submission.bmm_spec
#print axioms Submission.R11W01Diagnostics.selected_read_bounds
#print axioms Submission.R11W01Diagnostics.packet_machine_read
#print axioms Submission.R11W01Diagnostics.core_original_spec
