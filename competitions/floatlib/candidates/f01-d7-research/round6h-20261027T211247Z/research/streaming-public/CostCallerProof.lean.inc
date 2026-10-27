/- Proof-only transport for D's exact R22StreamingCost caller. NOT_RUN. -/
namespace Submission.R22StreamingCost
open FloatLib.Floats Competition

theorem rows_eq_batchStep (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (bi : Fin batch) (out : Array Binary32) :
    rows m n p bi.val A.toArray B.toArray out =
      R21StreamingMatrix.batchStep batch m n p A B out bi := by
  by_cases hodd : m % 2 = 1
  · have hm : 0 < m := by omega
    have haddr : bi.val * m + m - 1 = bi.val * m + (m - 1) := by omega
    simp only [rows, pairs, R21StreamingMatrix.batchStep, R21StreamingMatrix.oddRow,
      R21StreamingMatrix.pairStep, hodd, Nat.one_mul, if_true, haddr]
  · have hrem : m % 2 = 0 := by
      have hlt := Nat.mod_lt m (by decide : 0 < 2)
      omega
    simp only [rows, pairs, R21StreamingMatrix.batchStep, R21StreamingMatrix.oddRow,
      R21StreamingMatrix.pairStep, hodd, if_false, hrem, Nat.zero_mul,
      RowStream.emit, Fin.foldl_zero]

theorem output_eq_matrixOutput (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p)) :
    output batch m n p A.toArray B.toArray = R21StreamingMatrix.matrixOutput batch m n p A B := by
  unfold output R21StreamingMatrix.matrixOutput
  apply congrArg (fun step : Array Binary32 → Fin batch → Array Binary32 =>
    Fin.foldl batch step (Array.mkEmpty (batch * m * p)))
  funext acc bi
  exact rows_eq_batchStep batch m n p A B bi acc

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = referenceBmm batch m n p A B := by
  calc
    core batch m n p A B =
        (⟨R21StreamingMatrix.matrixOutput batch m n p A B,
          (R21StreamingMatrix.matrixOutput_prefix batch m n p A B).1⟩ :
          Vector Binary32 (batch * m * p)) := by
      unfold core
      congr 1
      exact output_eq_matrixOutput batch m n p A B
    _ = referenceBmm batch m n p A B :=
      R21StreamingMatrix.matrixVector_eq_reference batch m n p A B

theorem guarded_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (guarded batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold guarded
  split
  · rename_i h
    have hh : A.toArray.all UnderflowZero.small = true ∧
        B.toArray.all UnderflowZero.small = true := by
      simpa only [Bool.and_eq_true] using h
    rw [UnderflowZero.zeros_eq_reference batch m n p A B hh.1 hh.2]
    exact referenceBmm_spec batch m n p A B
  · split
    · rw [core_eq_reference]
      exact referenceBmm_spec batch m n p A B
    · exact bmmBeforeR22Streaming_spec batch m n p A B

end Submission.R22StreamingCost
