/- Own small-batch scheduler experiment over source12's already proved native
   operators. Reuse four output columns without constructing the prealigned P
   array for a one-row input. Arithmetic, bias, zero replay and fallback stay
   in the existing YaUc4/YaU implementations. -/
def r27RawColumns (rows inW outW : Nat) (relu : Bool)
    (input weights bias : Array Word) : Array Word :=
  let bx := Array.ofFn (n := rows) fun row => Yc input inW row.val
  let bw := Array.ofFn (n := outW) fun col => Yc weights inW col.val
  let scalar := fun row col => act relu
    (YaU input weights bias inW row col bx[row]! bw[col]!)
  let columns := fun row col =>
    let values := YaUc4 input weights bias inW row col bx[row]!
      bw[col]! bw[col + 1]! bw[col + 2]! bw[col + 2 + 1]!
    ((act relu values.1.1, act relu values.1.2),
      (act relu values.2.1, act relu values.2.2))
  Yak4 rows outW scalar columns (fun _ => true) 0 (Array.mkEmpty (rows * outW))

theorem r27RawColumns_eq : r27RawColumns = linearSpec := by
  funext rows inW outW relu input weights bias
  unfold r27RawColumns linearSpec linearWith
  dsimp only
  rw [Zk4 rows outW _ _ _ (by intro row col; simp only [Yuc4])
    rows 0 _ (by omega)]
  change YT rows outW _ = _
  rw [ZB rows outW (rows * outW) rfl]
  congr 1
  funext output
  have positive : 0 < rows * outW := lt_of_le_of_lt (Nat.zero_le _) output.isLt
  have width_positive : 0 < outW := Nat.pos_of_mul_pos_left positive
  have row_bound : output.val / outW < rows :=
    Nat.div_lt_of_lt_mul (by simpa [Nat.mul_comm] using output.isLt)
  have col_bound : output.val % outW < outW := Nat.mod_lt _ width_positive
  rw [gO rows (fun row => Yc input inW row) _ row_bound,
    gO outW (fun col => Yc weights inW col) _ col_bound, ZcB]

def r27LinearSmallBatch (rows inW outW : Nat) (relu : Bool)
    (input weights bias : Array Word) : Array Word :=
  if rows == 1 then r27RawColumns rows inW outW relu input weights bias
  else YaV rows inW outW relu input weights bias

theorem r27LinearSmallBatch_eq : r27LinearSmallBatch = linearSpec := by
  funext rows inW outW relu input weights bias
  unfold r27LinearSmallBatch
  split
  · rw [r27RawColumns_eq]
  · rw [ZcC]
