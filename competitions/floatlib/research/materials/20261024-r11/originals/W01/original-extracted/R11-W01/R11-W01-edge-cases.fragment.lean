/- R11-W01 optional diagnostic fragment. Append after the exact Kernel,
   or compile after a separately imported exact compiled Kernel in a diagnostic
   file. NOT_RUN. Do not include this in the submitted <=256000-byte source. -/
namespace Submission.R11W01Diagnostics
open FloatLib.Floats Competition

example (batch n p : Nat) (A : Vector Binary32 (batch*0*n))
    (B : Vector Binary32 (batch*n*p)) :
    bmm batch 0 n p A B = bmmBeforeR11Cross batch 0 n p A B := by
  unfold bmm
  split
  · rename_i h
    have h4 : 4 ≤ 0 := by simpa only [Nat.mul_zero] using h.2.1
    omega
  · rfl

example (batch m n : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*0)) :
    bmm batch m n 0 A B = bmmBeforeR11Cross batch m n 0 A B := by
  unfold bmm
  split
  · rename_i h
    have hp : (0 : Nat) = 2 := h.1
    omega
  · rfl

example (batch m p : Nat) (A : Vector Binary32 (batch*m*0))
    (B : Vector Binary32 (batch*0*p)) :
    bmm batch m 0 p A B = bmmBeforeR11Cross batch m 0 p A B := by
  unfold bmm
  split
  · rename_i h
    have hn : (0 : Nat) < 0 := h.2.2.1
    omega
  · rfl

example (m n p : Nat) (A : Vector Binary32 (0*m*n))
    (B : Vector Binary32 (0*n*p)) :
    bmm 0 m n p A B = bmmBeforeR11Cross 0 m n p A B := by
  unfold bmm
  split
  · rename_i h
    have h4 : 4 ≤ 0 := by simpa only [Nat.zero_mul] using h.2.1
    omega
  · rfl

example (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*p)) (hn : ¬n < USize.size) :
    bmm batch m n p A B = bmmBeforeR11Cross batch m n p A B := by
  unfold bmm
  split
  · rename_i h
    exact (hn h.2.2.2.1).elim
  · rfl

/- This is the explicit all-input chain already used under the real guard. -/
example (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*p)) (hn : n<USize.size) (hp : p≤2) :
    (R11CrossRows.core batch m n p A B hn hp).get =
      bmmSpec batch m n p A.get B.get := by
  rw [R11CrossRows.core_eq_rows, DirectRows.core_eq,
    DirectSmall.core_eq_reference]
  exact referenceBmm_spec batch m n p A B

end Submission.R11W01Diagnostics
