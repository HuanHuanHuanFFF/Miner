/- After exact B2. Proof-only endpoint interface; NOT_RUN. -/
namespace Submission.R22EndpointRounding
open FloatLib.Numerics

theorem nat_rne_zero_of_lt_half (p shift : Nat)
    (hs : 0 < shift) (hp : p < 2 ^ (shift - 1)) :
    roundShiftRightEven p shift = 0 := by
  have hs0 : shift ≠ 0 := Nat.ne_of_gt hs
  have hfull : p < 2 ^ shift :=
    lt_of_lt_of_le hp (Nat.pow_le_pow_right (by decide) (Nat.sub_le shift 1))
  have hq : p >>> shift = 0 := by
    rw [Nat.shiftRight_eq_div_pow]
    exact Nat.div_eq_of_lt hfull
  rw [roundShiftRightEven_def]
  simp [hs0, hq, Nat.shiftLeft_eq, hp]

theorem rseAny_zero_of_lt_half (p shift : UInt64)
    (hs : 0 < shift.toNat) (hp : p.toNat < 2 ^ (shift.toNat - 1)) :
    FastMul.rseAny p shift = 0 := by
  apply UInt64.toNat_inj.mp
  rw [FastMul.rseAny_eq, FixedWord.roundShiftRightEven_toNat]
  exact nat_rne_zero_of_lt_half p.toNat shift.toNat hs hp

end Submission.R22EndpointRounding
