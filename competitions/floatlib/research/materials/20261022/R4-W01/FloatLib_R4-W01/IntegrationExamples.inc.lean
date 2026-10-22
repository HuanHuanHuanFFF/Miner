namespace Submission.RowPairBounds

example {α β : Type} {batch m n b i : Nat}
    (A : Vector α (batch * m * n)) (toNative : α → β)
    (hb : b < batch) (hi : i < m) (hn : 0 < n) :
    (b * m + 2 * (i / 2)) * n + (i % 2) * n + (n - 1) <
      (A.toArray.map toNative).size := by
  simpa only [Array.size_map, Vector.size_toArray] using
    (selected_span (n := n) hb hi hn)

example {α β : Type} {batch m n b h : Nat}
    (A : Vector α (batch * m * n)) (toNative : α → β)
    (hb : b < batch) (hrow : 2 * h + 1 < m) (hn : 0 < n) :
    (b * m + 2 * h) * n + n + (n - 1) < (A.toArray.map toNative).size := by
  simpa only [Array.size_map, Vector.size_toArray] using
    (row1_span (n := n) hb hrow hn)

end Submission.RowPairBounds
