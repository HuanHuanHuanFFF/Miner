/- R21 isolated full-call driver interface. No public dispatcher is changed.
   Pairing restarts inside every batch; an odd final row uses the original dot. -/
namespace Submission.R21StreamingMatrix
open FloatLib.Floats Competition

@[inline] def pairStep (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (bi : Fin batch) (out : Array Binary32) (g : Fin (m / 2)) : Array Binary32 :=
  let i := 2 * g.val
  R21StreamingPair.streamedRows p n ((bi.val * m + i) * n)
    ((bi.val * m + i + 1) * n) (bi.val * n * p) A.toArray B.toArray out

@[inline] def oddRow (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (bi : Fin batch) (out : Array Binary32) : Array Binary32 :=
  if m % 2 = 1 then
    RowStream.emit p (fun j => NativeFinal.dot n
      ((bi.val * m + (m - 1)) * n) (bi.val * n * p + j.val) p A.toArray B.toArray) out
  else out

@[inline] def batchStep (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (out : Array Binary32) (bi : Fin batch) : Array Binary32 :=
  let out := Fin.foldl (m / 2) (pairStep batch m n p A B bi) out
  oddRow batch m n p A B bi out

@[noinline] def matrixOutput (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p)) :
    Array Binary32 :=
  Fin.foldl batch (batchStep batch m n p A B) (Array.mkEmpty (batch * m * p))

@[noinline] def controlOutput (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p)) :
    Array Binary32 :=
  DirectContinuous.output batch m n p A B

end Submission.R21StreamingMatrix
