/- R22 public-entry integration. The pair runtime is the exact R21/4e36 source.
   This new writer/public composition is NOT_RUN until checked on the pinned runner. -/
namespace Submission.R21StreamingMatrix
open FloatLib.Floats Competition

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  ⟨matrixOutput batch m n p A B, (matrixOutput_prefix batch m n p A B).1⟩

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = referenceBmm batch m n p A B := by
  exact matrixVector_eq_reference batch m n p A B

end Submission.R21StreamingMatrix

namespace Submission
open FloatLib.Floats Competition

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small then
    UnderflowZero.zeros batch m p
  else R21StreamingMatrix.core batch m n p A B

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold bmm
  split
  · rename_i h
    have hh : A.toArray.all UnderflowZero.small = true ∧
        B.toArray.all UnderflowZero.small = true := by
      simpa only [Bool.and_eq_true] using h
    rw [UnderflowZero.zeros_eq_reference batch m n p A B hh.1 hh.2]
    exact referenceBmm_spec batch m n p A B
  · rw [R21StreamingMatrix.core_eq_reference]
    exact referenceBmm_spec batch m n p A B

end Submission
