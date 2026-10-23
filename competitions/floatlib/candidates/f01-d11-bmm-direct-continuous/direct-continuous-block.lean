namespace Submission.DirectContinuous

open FloatLib.Floats Competition

/-- Read the original inputs and finish each scalar dot directly into one array. -/
@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (out : Array Binary32) (r : Fin (batch * m)) : Array Binary32 :=
  let baseA := r.val * n
  let baseB := r.val / m * n * p
  RowStream.emit p (fun j =>
    NativeFinal.dot n baseA (baseB + j.val) p A.toArray B.toArray) out

theorem row_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (out : Array Binary32) (r : Fin (batch * m))
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) (r.val * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((r.val + 1) * p)
      (row batch m n p A B out r) := by
  have hm : 0 < m := Nat.pos_of_lt_mul_left r.isLt
  have h := RowStream.emit_prefix (RowStream.point batch m n p A B)
    (r.val * p) p
    (fun j : Fin p => NativeFinal.dot n (r.val * n)
      (r.val / m * n * p + j.val) p A.toArray B.toArray) out hout
    (by
      intro j
      have hp : 0 < p := Nat.zero_lt_of_lt j.isLt
      exact (RowStream.point_row batch m n p A B r.val j.val hm hp j.isLt).symm)
  simpa only [row, Nat.add_mul, Nat.one_mul] using h

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Array Binary32 :=
  Fin.foldl (batch * m) (row batch m n p A B)
    (Array.mkEmpty (batch * m * p))

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch * m * p)
      (output batch m n p A B) := by
  exact RowStream.foldl_inv (batch * m) (row batch m n p A B)
    (fun r acc => RowStream.Prefix (RowStream.point batch m n p A B) (r * p) acc)
    (fun r acc hacc => row_prefix batch m n p A B acc r hacc)
    (Array.mkEmpty (batch * m * p))
    ⟨by simp, by intro j hj; simp at hj⟩

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  ⟨output batch m n p A B, (output_prefix batch m n p A B).1⟩

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = referenceBmm batch m n p A B := by
  exact (RowStream.prefix_vector_eq_ofFn (RowStream.point batch m n p A B)
    (batch * m * p) (output batch m n p A B) (output_prefix batch m n p A B)).trans
    (RowStream.points_eq_reference batch m n p A B)

end Submission.DirectContinuous
