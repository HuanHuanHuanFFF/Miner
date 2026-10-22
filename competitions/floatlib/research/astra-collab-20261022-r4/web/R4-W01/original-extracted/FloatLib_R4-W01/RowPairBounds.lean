import ContractTensor

namespace Submission.RowPairBounds

/-- Every valid row selects a valid row pair. -/
theorem pair_index_lt {m i : Nat} (hi : i < m) :
    i / 2 < (m + 1) / 2 := by
  omega

theorem row_decomposition (i : Nat) : 2 * (i / 2) + i % 2 = i := by
  omega

/-- Selecting one row of a pair recovers the original matrix row address. -/
theorem selected_base (b m n i : Nat) :
    (b * m + 2 * (i / 2)) * n + (i % 2) * n = (b * m + i) * n := by
  rw [← Nat.add_mul, Nat.add_assoc, row_decomposition]

/-- The second stream starts at the next row. -/
theorem second_base (b m n h : Nat) :
    (b * m + 2 * h) * n + n = (b * m + (2 * h + 1)) * n := by
  simp only [Nat.add_mul, Nat.one_mul, Nat.add_assoc]

theorem row_lt {batch m b i : Nat} (hb : b < batch) (hi : i < m) :
    b * m + i < batch * m := by
  calc
    b * m + i < b * m + m := Nat.add_lt_add_left hi (b * m)
    _ = (b + 1) * m := by simp only [Nat.add_mul, Nat.one_mul]
    _ ≤ batch * m := Nat.mul_le_mul_right m (by omega)

/-- The exclusive end of a valid row does not exceed the input length. -/
theorem row_end_le {batch m n b i : Nat} (hb : b < batch) (hi : i < m) :
    (b * m + i) * n + n ≤ batch * m * n := by
  have hr := row_lt hb hi
  calc
    (b * m + i) * n + n = (b * m + i + 1) * n := by
      simp only [Nat.add_mul, Nat.one_mul]
    _ ≤ batch * m * n := Nat.mul_le_mul_right n (by omega)

theorem point_bound {batch m n b i k : Nat}
    (hb : b < batch) (hi : i < m) (hk : k < n) :
    (b * m + i) * n + k < batch * m * n := by
  calc
    (b * m + i) * n + k < (b * m + i) * n + n :=
      Nat.add_lt_add_left hk ((b * m + i) * n)
    _ ≤ batch * m * n := row_end_le hb hi

theorem row_span {batch m n b i : Nat}
    (hb : b < batch) (hi : i < m) (hn : 0 < n) :
    (b * m + i) * n + (n - 1) < batch * m * n := by
  exact point_bound hb hi (by omega)

theorem row0_point {batch m n b h k : Nat}
    (hb : b < batch) (hrow : 2 * h < m) (hk : k < n) :
    (b * m + 2 * h) * n + k < batch * m * n := by
  exact point_bound hb hrow hk

theorem row0_span {batch m n b h : Nat}
    (hb : b < batch) (hrow : 2 * h < m) (hn : 0 < n) :
    (b * m + 2 * h) * n + (n - 1) < batch * m * n := by
  exact row_span hb hrow hn

theorem row1_point {batch m n b h k : Nat}
    (hb : b < batch) (hrow : 2 * h + 1 < m) (hk : k < n) :
    (b * m + 2 * h) * n + n + k < batch * m * n := by
  rw [second_base]
  exact point_bound hb hrow hk

theorem row1_span {batch m n b h : Nat}
    (hb : b < batch) (hrow : 2 * h + 1 < m) (hn : 0 < n) :
    (b * m + 2 * h) * n + n + (n - 1) < batch * m * n := by
  rw [second_base]
  exact row_span hb hrow hn

theorem selected_point {batch m n b i k : Nat}
    (hb : b < batch) (hi : i < m) (hk : k < n) :
    (b * m + 2 * (i / 2)) * n + (i % 2) * n + k < batch * m * n := by
  rw [selected_base]
  exact point_bound hb hi hk

theorem selected_span {batch m n b i : Nat}
    (hb : b < batch) (hi : i < m) (hn : 0 < n) :
    (b * m + 2 * (i / 2)) * n + (i % 2) * n + (n - 1) < batch * m * n := by
  rw [selected_base]
  exact row_span hb hi hn

theorem pair_first_valid {m h : Nat} (hh : h < (m + 1) / 2) :
    2 * h < m := by
  omega

/-- A row pair's second row is either valid or exactly the matrix row boundary. -/
theorem pair_second_cases {m h : Nat} (hh : h < (m + 1) / 2) :
    2 * h + 1 < m ∨ 2 * h + 1 = m := by
  have hfirst := pair_first_valid hh
  omega

/-- An unobserved tail stream starts at the next batch boundary. -/
theorem tail_second_base (b m n h : Nat) (htail : 2 * h + 1 = m) :
    (b * m + 2 * h) * n + n = (b + 1) * m * n := by
  rw [second_base, htail]
  simp only [Nat.add_mul, Nat.one_mul]

/-- Before the last batch, the tail stream is the next batch's first valid row. -/
theorem tail_next_span {batch m n b h : Nat}
    (hnext : b + 1 < batch) (htail : 2 * h + 1 = m) (hn : 0 < n) :
    (b * m + 2 * h) * n + n + (n - 1) < batch * m * n := by
  rw [tail_second_base b m n h htail]
  have hm : 0 < m := by omega
  simpa only [Nat.add_zero] using (row_span (i := 0) hnext hm hn)

/-- In the final batch, every tail-stream address is outside the whole input. -/
theorem tail_last_point_outside {batch m n b h k : Nat}
    (hlast : b + 1 = batch) (htail : 2 * h + 1 = m) :
    batch * m * n ≤ (b * m + 2 * h) * n + n + k := by
  rw [tail_second_base b m n h htail, hlast]
  omega

/-- The final unobserved stream cannot meet a strict full-span admission test. -/
theorem tail_last_span_fails {batch m n b h : Nat}
    (hlast : b + 1 = batch) (htail : 2 * h + 1 = m) :
    ¬ (b * m + 2 * h) * n + n + (n - 1) < batch * m * n := by
  have ho := tail_last_point_outside (n := n) (k := n - 1) hlast htail
  omega

end Submission.RowPairBounds
