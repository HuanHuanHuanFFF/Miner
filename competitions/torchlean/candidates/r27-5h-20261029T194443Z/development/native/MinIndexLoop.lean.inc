/- Own R27 refinement: compute the norm alignment exponent by a tail loop,
   eliminating construction/traversal of List.range. Existing statistics,
   denominator rounding and element output definitions remain unchanged. -/
def r27MinIndexLoop (x : Array Word) (base n j low : Nat) : Nat :=
  if j < n then
    let word := x[base + j]!
    r27MinIndexLoop x base n (j + 1)
      (if mantOf word = 0 then low else min low (idxOf word))
  else low
termination_by n - j

theorem r27MinIndexLoop_fold (x : Array Word) (base n count : Nat) :
    ∀ j low, n - j = count →
      r27MinIndexLoop x base n j low =
        (List.range' j count).foldl
          (fun acc index =>
            let word := x[base + index]!
            if mantOf word = 0 then acc else min acc (idxOf word)) low := by
  induction count with
  | zero =>
    intro j low remaining
    rw [r27MinIndexLoop, if_neg (by omega)]
    rfl
  | succ count ih =>
    intro j low remaining
    rw [r27MinIndexLoop, if_pos (by omega),
      ih (j + 1) _ (by omega), List.range'_succ]
    rfl

theorem r27MinIndex_eq (x : Array Word) (base n : Nat) :
    r27MinIndexLoop x base n 0 255 = Y2 x base n := by
  unfold Y2
  rw [r27MinIndexLoop_fold x base n n 0 255 (by omega), List.range_eq_range']
