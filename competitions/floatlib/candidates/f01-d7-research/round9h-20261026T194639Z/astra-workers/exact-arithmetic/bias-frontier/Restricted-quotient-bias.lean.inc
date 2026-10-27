private theorem remainder_bias (q r half : Nat)
    (hhalf : half = 4194304 ∨ half = 8388608) (hr : r < 2*half) :
    (if 2*r < 2*half then q else if 2*half < 2*r then q+1
      else if q%2 == 0 then q else q+1) =
      (r+(half-1)+q%2)/(2*half)+q := by
  have hparity : q%2 < 2 := Nat.mod_lt _ (by decide)
  rcases hhalf with rfl | rfl <;>
    norm_num only [Nat.reduceMul,Nat.reduceSub] at * <;>
    simp only [beq_iff_eq] <;>
    split_ifs <;> omega

private theorem quotient_bias (p half : Nat)
    (hhalf : half = 4194304 ∨ half = 8388608) :
    roundQuotientEven p (2 * half) =
      (p + half - 1 + (p / (2 * half)) % 2) / (2 * half) := by
  have hpos : 0 < half := by rcases hhalf with rfl | rfl <;> decide
  have hden : 0 < 2*half := Nat.mul_pos (by decide) hpos
  have hsub : p+half-1 = p+(half-1) := by omega
  let q := p/(2*half)
  let r := p%(2*half)
  have hp : p=(2*half)*q+r := (Nat.div_add_mod p (2*half)).symm
  have hb : p+half-1+q%2 = (r+(half-1)+q%2)+(2*half)*q := by
    rw [hsub,hp]
    ring
  change (if 2*r < 2*half then q else if 2*half < 2*r then q+1
    else if q%2 == 0 then q else q+1) = (p+half-1+q%2)/(2*half)
  rw [hb,Nat.add_mul_div_left (r+(half-1)+q%2) q hden]
  exact remainder_bias q r half hhalf (Nat.mod_lt _ hden)
