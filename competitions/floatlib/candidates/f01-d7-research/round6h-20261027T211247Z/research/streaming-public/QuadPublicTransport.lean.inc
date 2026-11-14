/- Proof-only public transport for D's exact R22StreamingQuad runtime. NOT_RUN.
   Requires B's rows4_eq_control and FourWriterDirect + FlatRowWriter.
   It adds no runtime definition and does not rebind the public bmm. -/
namespace Submission.R22StreamingQuad
open FloatLib.Floats Competition

theorem dot_eq_point (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (bi : Fin batch) (i : Nat) (hi : i < m) (j : Fin p) :
    NativeFinal.dot n ((bi.val * m + i) * n) (bi.val * n * p + j.val) p A.toArray B.toArray =
      RowStream.point batch m n p A B ((bi.val * m + i) * p + j.val) := by
  have hm : 0 < m := Nat.zero_lt_of_lt hi
  have hp : 0 < p := Nat.zero_lt_of_lt j.isLt
  have hq : (bi.val * m + i) / m = bi.val := by
    rw [Nat.mul_comm bi.val m, Nat.mul_add_div hm, Nat.div_eq_of_lt hi, Nat.add_zero]
  have h := RowStream.point_row batch m n p A B (bi.val * m + i) j.val hm hp j.isLt
  rw [hq] at h
  exact h.symm

theorem rows4_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (bi : Fin batch) (g : Fin (m / 4)) (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) ((bi.val * m + 4 * g.val) * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((bi.val * m + 4 * (g.val + 1)) * p)
      (rows4 p n ((bi.val * m + 4 * g.val) * n) (bi.val * n * p) A.toArray B.toArray out) := by
  have hg := g.isLt
  have hbound : 4 * g.val + 4 ≤ m := by omega
  simp only [rows4_eq_control]
  have h := R22BlockWriter.emit_four_rows_prefix (RowStream.point batch m n p A B)
    ((bi.val * m + 4 * g.val) * p) p
    (fun j => NativeFinal.dot n ((bi.val * m + 4 * g.val) * n)
      (bi.val * n * p + j.val) p A.toArray B.toArray)
    (fun j => NativeFinal.dot n ((bi.val * m + 4 * g.val) * n + n)
      (bi.val * n * p + j.val) p A.toArray B.toArray)
    (fun j => NativeFinal.dot n ((bi.val * m + 4 * g.val) * n + 2 * n)
      (bi.val * n * p + j.val) p A.toArray B.toArray)
    (fun j => NativeFinal.dot n ((bi.val * m + 4 * g.val) * n + 3 * n)
      (bi.val * n * p + j.val) p A.toArray B.toArray)
    out hout
    (by
      intro j
      exact dot_eq_point batch m n p A B bi (4 * g.val) (by omega) j)
    (by
      intro j
      have h := dot_eq_point batch m n p A B bi (4 * g.val + 1) (by omega) j
      simpa only [Nat.add_mul, Nat.one_mul, Nat.add_assoc] using h)
    (by
      intro j
      have h := dot_eq_point batch m n p A B bi (4 * g.val + 2) (by omega) j
      simpa only [Nat.add_mul, Nat.add_assoc] using h)
    (by
      intro j
      have h := dot_eq_point batch m n p A B bi (4 * g.val + 3) (by omega) j
      simpa only [Nat.add_mul, Nat.add_assoc] using h)
  simpa only [Nat.mul_add, Nat.mul_one, Nat.add_mul, Nat.add_assoc] using h

theorem groups_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (bi : Fin batch) (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) (bi.val * m * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((bi.val * m + 4 * (m / 4)) * p)
      (groups m n p bi.val A.toArray B.toArray out) := by
  unfold groups
  exact RowStream.foldl_inv (β := Array Binary32) (m / 4)
    (fun acc g => rows4 p n ((bi.val * m + 4 * g.val) * n)
      (bi.val * n * p) A.toArray B.toArray acc)
    (fun g acc => RowStream.Prefix (RowStream.point batch m n p A B) ((bi.val * m + 4 * g) * p) acc)
    (fun g acc hacc => rows4_prefix batch m n p A B bi g acc hacc)
    out (by simpa only [Nat.mul_zero, Nat.add_zero] using hout)

theorem rows_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (bi : Fin batch) (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) (bi.val * m * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((bi.val + 1) * m * p)
      (rows m n p bi.val A.toArray B.toArray out) := by
  have hdiv : m / 4 * 4 + m % 4 = m := by omega
  have hg := groups_prefix batch m n p A B bi out hout
  have hg' : RowStream.Prefix (RowStream.point batch m n p A B)
      ((bi.val * m + m / 4 * 4) * p) (groups m n p bi.val A.toArray B.toArray out) := by
    simpa only [Nat.mul_comm 4 (m / 4)] using hg
  have ht := R22BlockWriter.emit_flat_rows_prefix batch m n p (m / 4 * 4) (m % 4)
    A B bi (by omega) (groups m n p bi.val A.toArray B.toArray out) hg'
  have hindex : (bi.val * m + m / 4 * 4 + m % 4) * p = (bi.val + 1) * m * p := by
    rw [Nat.add_assoc, hdiv]
    simp only [Nat.add_mul, Nat.one_mul]
  simpa only [rows, hindex] using ht

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p)) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch * m * p)
      (output batch m n p A.toArray B.toArray) := by
  unfold output
  exact RowStream.foldl_inv (β := Array Binary32) batch
    (fun acc bi => rows m n p bi.val A.toArray B.toArray acc)
    (fun bi acc => RowStream.Prefix (RowStream.point batch m n p A B) (bi * m * p) acc)
    (fun bi acc hacc => rows_prefix batch m n p A B bi acc hacc)
    (Array.mkEmpty (batch * m * p))
    ⟨by simp, by intro j hj; simp at hj⟩

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = referenceBmm batch m n p A B := by
  exact (RowStream.prefix_vector_eq_ofFn (RowStream.point batch m n p A B)
    (batch * m * p) (output batch m n p A.toArray B.toArray)
    (output_prefix batch m n p A B)).trans (RowStream.points_eq_reference batch m n p A B)

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
    · exact Submission.bmm_spec batch m n p A B

end Submission.R22StreamingQuad
