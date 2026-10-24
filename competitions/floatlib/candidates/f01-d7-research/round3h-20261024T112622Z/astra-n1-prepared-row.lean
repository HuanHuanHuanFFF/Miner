/- R13 bounded revisit of row-local A conversion. Unlike the old R10 row-cache,
   retain the original +0 add and raw replay, and write directly to the final array. -/
namespace Submission.R13N1Prepared
open FloatLib.Floats Competition

@[inline] def onePreparedDot (baseA baseB p : Nat) (A B : Array Binary32)
    (fa : Float32) : Binary32 :=
  let fb := ExecFloat.Binary.toFloat32 (B.getD baseB posZero)
  let result := Float32.ofBits 0 + fa * fb
  if hf : R7W04.nonNaN result = true then ExecFloat.Binary.ofFloat32 result
  else R7NaNReplay.replayEarly 1 baseA baseB p A B

theorem onePreparedDot_eq (baseA baseB p : Nat) (A B : Array Binary32)
    (fa : Float32) (ha : fa = ExecFloat.Binary.toFloat32 (A.getD baseA posZero)) :
    onePreparedDot baseA baseB p A B fa = NativeFinal.dot 1 baseA baseB p A B := by
  rw [ha]
  simp [onePreparedDot, NativeFinal.dot, NativeFinal.dotLoop]

@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (out : Array Binary32) (r : Fin (batch * m)) : Array Binary32 :=
  let baseA := r.val * n
  let baseB := r.val / m * n * p
  let fa := ExecFloat.Binary.toFloat32 (A.toArray.getD baseA posZero)
  RowStream.emit p (fun j =>
    onePreparedDot baseA (baseB + j.val) p A.toArray B.toArray fa) out

theorem row_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (out : Array Binary32) (r : Fin (batch * m)) (hn : n = 1) :
    row batch m n p A B out r = DirectContinuous.row batch m n p A B out r := by
  subst n
  dsimp only [row, DirectContinuous.row]
  apply congrArg (fun read : Fin p → Binary32 => RowStream.emit p read out)
  funext j
  exact onePreparedDot_eq _ _ _ _ _ _ rfl

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Array Binary32 :=
  Fin.foldl (batch * m) (row batch m n p A B)
    (Array.mkEmpty (batch * m * p))

theorem output_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n = 1) :
    output batch m n p A B = DirectContinuous.output batch m n p A B := by
  unfold output DirectContinuous.output
  apply congrArg (fun step : Array Binary32 → Fin (batch * m) → Array Binary32 =>
    Fin.foldl (batch * m) step (Array.mkEmpty (batch * m * p)))
  funext out r
  exact row_eq batch m n p A B out r hn

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n = 1) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch * m * p)
      (output batch m n p A B) := by
  rw [output_eq batch m n p A B hn]
  exact DirectContinuous.output_prefix batch m n p A B

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n = 1) :
    Vector Binary32 (batch * m * p) :=
  ⟨output batch m n p A B, (output_prefix batch m n p A B hn).1⟩

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n = 1) :
    core batch m n p A B hn = referenceBmm batch m n p A B := by
  exact (RowStream.prefix_vector_eq_ofFn (RowStream.point batch m n p A B)
    (batch * m * p) (output batch m n p A B) (output_prefix batch m n p A B hn)).trans
    (RowStream.points_eq_reference batch m n p A B)

def dispatch (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if h : n = 1 ∧ 2 < p then core batch m n p A B h.1
  else bmmBeforeR11Cross batch m n p A B

theorem dispatch_spec : ∀ (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p)),
    (dispatch batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold dispatch
  split
  · rw [core_eq_reference]
    exact referenceBmm_spec batch m n p A B
  · exact bmmBeforeR11Cross_spec batch m n p A B

end Submission.R13N1Prepared
