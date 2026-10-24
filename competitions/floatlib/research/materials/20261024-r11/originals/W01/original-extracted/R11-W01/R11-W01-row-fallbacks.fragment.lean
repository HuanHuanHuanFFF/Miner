/- R11-W01 proof-only diagnostic alternatives. NOT_RUN.
   No runtime definition below. Do not apply both this theorem and the existing
   identically named rowWord_eq. First block is a replacement body candidate,
   not a confirmed fix. The concrete bounds theorem may be appended for local
   audit and omitted from the submitted file. -/
namespace Submission.R11CrossRows
open FloatLib.Floats Competition

theorem rowWord_eq (batch m n p : Nat) (A B : Array Binary32) (hn : n<USize.size)
    (r : Fin (batch*m)) (j : Fin p) (hp : p≤2) :
    rowWord batch m p (words batch m n p A B hn) r j hp =
      NativeFinal.dot n ((r.val/m*m+r.val%m)*n) (r.val/m*n*p+j.val) p A B := by
  unfold rowWord words
  dsimp only
  rw [Packed10.vector_get_ofFn, blockRows_word]
  dsimp only
  have hr : r.val/m*m+r.val%m=r.val := by
    simpa only [Nat.mul_comm] using Nat.div_add_mod r.val m
  simp only [row_decomposition, hr]

/-- Exact two raw-read obligations for an emitted output and consumed k. -/
theorem r11w01_selected_read_bounds (batch m n p : Nat)
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

end Submission.R11CrossRows
