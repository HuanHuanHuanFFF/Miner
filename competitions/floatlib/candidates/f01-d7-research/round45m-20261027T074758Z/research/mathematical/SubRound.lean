import ContractTensor

/- NOT_RUN: an exact Nat interface, not a FloatLib add/SUM proof. The only
   arithmetic automation is on remainder bounds, after quotient removal. -/
namespace R20SubRound
open FloatLib.Numerics

theorem round_block_below (q r d : Nat) (hd : 0 < d) (hr : r < d)
    (hbelow : 2*r < d) : roundQuotientEven (d*q+r) d = q := by
  have hdiv : (d*q+r)/d = q := by
    rw [Nat.mul_add_div hd, Nat.div_eq_of_lt hr, Nat.add_zero]
  have hmod : (d*q+r)%d = r := by
    rw [Nat.mul_add_mod, Nat.mod_eq_of_lt hr]
  simp only [roundQuotientEven,hdiv,hmod,if_pos hbelow]

theorem round_block_above (q r d : Nat) (hd : 0 < d) (hr : r < d)
    (habove : d < 2*r) : roundQuotientEven (d*q+r) d = q+1 := by
  have hdiv : (d*q+r)/d = q := by
    rw [Nat.mul_add_div hd, Nat.div_eq_of_lt hr, Nat.add_zero]
  have hmod : (d*q+r)%d = r := by
    rw [Nat.mul_add_mod, Nat.mod_eq_of_lt hr]
  have hn : ¬ 2*r < d := Nat.not_lt_of_ge (Nat.le_of_lt habove)
  simp only [roundQuotientEven,hdiv,hmod,if_neg hn,if_pos habove]

/-- Positive exact lattice point minus strictly less than half a lattice unit.
    No associativity or aggregate rounding assumption is used. -/
theorem round_mul_sub (m small d : Nat) (hm : 0 < m) (hd : 0 < d)
    (hsmall : 2*small < d) : roundQuotientEven (d*m-small) d = m := by
  by_cases hz : small = 0
  · subst small
    simpa only [Nat.sub_zero,Nat.add_zero] using
      round_block_below m 0 d hd hd (by simpa using hd)
  · have hsmallPos : 0 < small := by omega
    have hle : small ≤ d := by omega
    have hrem : d-small < d := by omega
    have habove : d < 2*(d-small) := by omega
    cases m with
    | zero => omega
    | succ q =>
      have he : d*(q+1)-small = d*q+(d-small) := by
        rw [Nat.mul_add_one,Nat.add_sub_assoc hle]
      change roundQuotientEven (d*(q+1)-small) d = q+1
      rw [he]
      exact round_block_above q (d-small) d hd hrem habove

theorem rne_shift_sub (m small gap : Nat) (hm : 0 < m)
    (hsmall : 2*small < 2^gap) :
    roundShiftRightEven ((m <<< gap)-small) gap = m := by
  rw [roundShiftRightEven_eq_roundQuotientEven,Nat.shiftLeft_eq]
  rw [Nat.mul_comm m (2^gap)]
  exact round_mul_sub m small (2^gap) hm (Nat.two_pow_pos gap) hsmall

/-- At an exact binade edge the real rounder drops one fewer bit and obtains
    2^24, which is the carry case. Rounding only at `gap` would miss this. -/
theorem binade_actual_drop (small gap : Nat) (hg : 1 ≤ gap)
    (hsmall : 2*small < 2^(gap-1)) :
    roundShiftRightEven (((2^23 : Nat) <<< gap)-small) (gap-1) = 2^24 := by
  have he : ((2^23 : Nat) <<< gap) = ((2^24 : Nat) <<< (gap-1)) := by
    simp only [Nat.shiftLeft_eq,← Nat.pow_add]
    have hx : 23+gap = 24+(gap-1) := by omega
    rw [hx]
  rw [he]
  exact rne_shift_sub (2^24) small (gap-1) (by decide) hsmall

end R20SubRound
