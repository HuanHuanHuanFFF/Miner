import ContractTensor

namespace Submission.Packed4.MatrixBounds

open FloatLib.Floats

/-- A valid batch and row select a valid flattened row. -/
theorem row_lt {batch m b i : Nat} (hb : b < batch) (hi : i < m) :
    b * m + i < batch * m := by
  calc
    b * m + i < b * m + m := Nat.add_lt_add_left hi (b * m)
    _ = (b + 1) * m := by simp only [Nat.add_mul, Nat.one_mul]
    _ ≤ batch * m := Nat.mul_le_mul_right m (by omega)

/-- The exclusive end of a valid row is at most the matrix length. -/
theorem row_end_le {batch m n b i : Nat} (hb : b < batch) (hi : i < m) :
    (b * m + i) * n + n ≤ batch * m * n := by
  have hr := row_lt hb hi
  calc
    (b * m + i) * n + n = (b * m + i + 1) * n := by
      simp only [Nat.add_mul, Nat.one_mul]
    _ ≤ batch * m * n := Nat.mul_le_mul_right n (by omega)

/-- Every position in a valid row lies in the matrix. -/
theorem point_bound {batch m n b i k : Nat}
    (hb : b < batch) (hi : i < m) (hk : k < n) :
    (b * m + i) * n + k < batch * m * n := by
  calc
    (b * m + i) * n + k < (b * m + i) * n + n :=
      Nat.add_lt_add_left hk ((b * m + i) * n)
    _ ≤ batch * m * n := row_end_le hb hi

/-- The final position of a nonempty valid row lies in the matrix. -/
theorem row_span {batch m n b i : Nat}
    (hb : b < batch) (hi : i < m) (hn : 0 < n) :
    (b * m + i) * n + (n - 1) < batch * m * n := by
  exact point_bound hb hi (by omega)

/-- One valid row contains n entries, even when n is zero. -/
theorem row_count_le {batch m n b i : Nat} (hb : b < batch) (hi : i < m) :
    n ≤ batch * m * n := by
  have he := row_end_le (n := n) hb hi
  omega

/-- Mapping changes elements but preserves the input vector length. -/
theorem nativeA_size (batch m n : Nat) (A : Vector Binary32 (batch * m * n)) :
    (A.toArray.map ExecFloat.Binary.toFloat32).size = batch * m * n := by
  rw [Array.size_map]
  exact A.size_toArray

/-- A matrix length check supplies all row admission evidence. -/
theorem array_row_bounds (batch m n : Nat) (A : Array Float32)
    (hsize : A.size = batch * m * n) (b : Fin batch) (i : Fin m)
    (hn : 0 < n) (hAS : A.size < USize.size) :
    n < USize.size ∧
      (b.val * m + i.val) * n < USize.size ∧
      (b.val * m + i.val) * n + (n - 1) < A.size := by
  have htotal : batch * m * n < USize.size := by
    simpa only [hsize] using hAS
  have hc := row_count_le (n := n) b.isLt i.isLt
  have hbase : (b.val * m + i.val) * n < batch * m * n := by
    simpa only [Nat.add_zero] using
      (point_bound (k := 0) b.isLt i.isLt hn)
  have hlast := row_span b.isLt i.isLt hn
  refine ⟨Nat.lt_of_le_of_lt hc htotal, Nat.lt_trans hbase htotal, ?_⟩
  simpa only [hsize] using hlast

/-- The original typed input supplies the array length evidence. -/
theorem native_row_bounds (batch m n : Nat)
    (A : Vector Binary32 (batch * m * n)) (b : Fin batch) (i : Fin m)
    (hn : 0 < n)
    (hAS : (A.toArray.map ExecFloat.Binary.toFloat32).size < USize.size) :
    n < USize.size ∧
      (b.val * m + i.val) * n < USize.size ∧
      (b.val * m + i.val) * n + (n - 1) <
        (A.toArray.map ExecFloat.Binary.toFloat32).size := by
  exact array_row_bounds batch m n (A.toArray.map ExecFloat.Binary.toFloat32)
    (nativeA_size batch m n A) b i hn hAS

/-- The same single length check also bounds every actual row address. -/
theorem array_point_bounds (batch m n : Nat) (A : Array Float32)
    (hsize : A.size = batch * m * n) (b : Fin batch) (i : Fin m)
    (k : Nat) (hk : k < n) (hAS : A.size < USize.size) :
    (b.val * m + i.val) * n + k < A.size ∧
      (b.val * m + i.val) * n + k < USize.size := by
  have ha : (b.val * m + i.val) * n + k < A.size := by
    simpa only [hsize] using (point_bound b.isLt i.isLt hk)
  exact ⟨ha, Nat.lt_trans ha hAS⟩

end Submission.Packed4.MatrixBounds
