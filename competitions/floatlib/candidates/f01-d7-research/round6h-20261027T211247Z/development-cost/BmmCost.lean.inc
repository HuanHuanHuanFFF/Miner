
namespace Submission.R22StreamingCost
open Competition

def pairs (m n p b : Nat) (A B : Array Binary32) (out : Array Binary32) : Array Binary32 :=
  Fin.foldl (m / 2) (fun acc r =>
    R21StreamingPair.streamedRows p n ((b * m + 2 * r.val) * n)
      ((b * m + 2 * r.val + 1) * n) (b * n * p) A B acc) out

theorem pairs_size (m n p b : Nat) (A B : Array Binary32) (out : Array Binary32) :
    (pairs m n p b A B out).size = out.size + (m / 2) * (2 * p) := by
  unfold pairs
  apply RowStream.foldl_inv (m / 2) _
    (fun k (acc : Array Binary32) => acc.size = out.size + k * (2 * p))
  · intro r acc h
    rw [R21StreamingPair.streamedRows_size, h, Nat.add_mul]
    simp only [Nat.one_mul, Nat.add_assoc]
  · simp

def rows (m n p b : Nat) (A B : Array Binary32) (out : Array Binary32) : Array Binary32 :=
  let out := pairs m n p b A B out
  RowStream.emit ((m % 2) * p) (fun j => NativeFinal.dot n
    ((b * m + m - 1) * n) (b * n * p + j.val) p A B) out

theorem rows_size (m n p b : Nat) (A B : Array Binary32) (out : Array Binary32) :
    (rows m n p b A B out).size = out.size + m * p := by
  have hd : m / 2 * 2 + m % 2 = m := by omega
  simp only [rows, R21StreamingPair.emit_size, pairs_size]
  calc
    out.size + m / 2 * (2 * p) + m % 2 * p =
        out.size + (m / 2 * 2 + m % 2) * p := by
      simp only [Nat.add_mul, Nat.mul_assoc, Nat.add_assoc]
    _ = out.size + m * p := by rw [hd]

def output (batch m n p : Nat) (A B : Array Binary32) : Array Binary32 :=
  Fin.foldl batch (fun acc b => rows m n p b.val A B acc) (Array.mkEmpty (batch * m * p))

theorem output_size (batch m n p : Nat) (A B : Array Binary32) :
    (output batch m n p A B).size = batch * m * p := by
  unfold output
  have h := RowStream.foldl_inv batch (fun acc b => rows m n p b.val A B acc)
    (fun k (acc : Array Binary32) => acc.size = k * (m * p))
    (by
      intro b acc h
      rw [rows_size, h, Nat.add_mul]
      simp)
    (Array.mkEmpty (batch * m * p)) (by simp)
  simpa only [Nat.mul_assoc] using h

def core (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  ⟨output batch m n p A.toArray B.toArray, output_size batch m n p A.toArray B.toArray⟩

def guarded (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small then
    UnderflowZero.zeros batch m p
  else if 1 < n ∧ 2 ≤ m ∧ 2 ≤ p then core batch m n p A B
  else Submission.bmm batch m n p A B

end Submission.R22StreamingCost
