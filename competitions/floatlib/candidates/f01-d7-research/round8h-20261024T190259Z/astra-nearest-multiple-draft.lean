/- Draft / NOT_RUN. Exact RNE absorption lemmas over Nat. No runtime changes.
   Strict half-distance excludes ties; retained separately from general bias. -/
namespace Submission.R14NearestMultiple

open FloatLib.Numerics

theorem add_small (q d r : Nat) (hd : 0 < d) (hr : 2 * r < d) :
    roundQuotientEven (q * d + r) d = q := by
  have hr0 : r < d := by omega
  have hq : (q * d + r) / d = q :=
    Nat.div_eq_of_lt_le (by omega) (by rw [Nat.add_mul, Nat.one_mul]; omega)
  have hm : (q * d + r) % d = r := by
    rw [Nat.mod_eq_sub_div_mul, hq]
    omega
  simp only [roundQuotientEven, hq, hm, if_pos hr]

theorem sub_small (q d r : Nat) (hq0 : 0 < q) (hd : 0 < d)
    (hr0 : 0 < r) (hr : 2 * r < d) :
    roundQuotientEven (q * d - r) d = q := by
  have hq1 : q - 1 + 1 = q := by omega
  have hmul : q * d = (q - 1) * d + d := by
    calc q * d = (q - 1 + 1) * d := by rw [hq1]
         _ = (q - 1) * d + d := by rw [Nat.add_mul, Nat.one_mul]
  have hq : (q * d - r) / d = q - 1 :=
    Nat.div_eq_of_lt_le (by omega) (by rw [hq1]; omega)
  have hm : (q * d - r) % d = d - r := by
    rw [Nat.mod_eq_sub_div_mul, hq]
    omega
  have hnotbelow : ¬ 2 * (d - r) < d := by omega
  have habove : d < 2 * (d - r) := by omega
  simp only [roundQuotientEven, hq, hm, if_neg hnotbelow, if_pos habove]
  omega

theorem shift_add_small (q r t : Nat) (hr : 2 * r < 2 ^ t) :
    roundShiftRightEven (q * 2 ^ t + r) t = q := by
  rw [roundShiftRightEven_eq_roundQuotientEven]
  exact add_small q (2 ^ t) r (Nat.two_pow_pos _) hr

theorem shift_sub_small (q r t : Nat) (hq : 0 < q) (hr0 : 0 < r)
    (hr : 2 * r < 2 ^ t) :
    roundShiftRightEven (q * 2 ^ t - r) t = q := by
  rw [roundShiftRightEven_eq_roundQuotientEven]
  exact sub_small q (2 ^ t) r hq (Nat.two_pow_pos _) hr0 hr

end Submission.R14NearestMultiple
