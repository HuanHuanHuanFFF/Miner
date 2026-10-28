theorem nat_bias (p t : Nat) (ht : t = 23 ∨ t = 24) :
    roundShiftRightEven p t =
      (p + 2 ^ (t - 1) - 1 + (p >>> t) % 2) >>> t := by
  rcases ht with rfl | rfl
  · rw [roundShiftRightEven_eq_roundQuotientEven]
    change roundQuotientEven p 8388608 =
      (p + 4194304 - 1 + (p >>> 23) % 2) >>> 23
    simpa only [Nat.shiftRight_eq_div_pow, Nat.reducePow, Nat.reduceSub, Nat.reduceMul] using
      quotient_bias p 4194304 (by decide)
  · rw [roundShiftRightEven_eq_roundQuotientEven]
    change roundQuotientEven p 16777216 =
      (p + 8388608 - 1 + (p >>> 24) % 2) >>> 24
    simpa only [Nat.shiftRight_eq_div_pow, Nat.reducePow, Nat.reduceSub, Nat.reduceMul] using
      quotient_bias p 8388608 (by decide)
