
/- Independent exact RNE lemma requested by the integer-normal development route. -/
namespace Submission.R14BiasRNE

open FloatLib.Numerics

theorem nat_bias (p t : Nat) (ht : t = 23 ∨ t = 24) :
    roundShiftRightEven p t =
      (p + 2 ^ (t - 1) - 1 + (p >>> t) % 2) >>> t := by
  rcases ht with rfl | rfl
  all_goals
    rw [roundShiftRightEven_eq_roundQuotientEven]
    unfold roundQuotientEven
    norm_num [Nat.shiftRight_eq_div_pow]
    simp only [beq_iff_eq]
    split_ifs <;> omega

@[inline] def biased (p t : UInt64) : UInt64 :=
  (p + ((1 : UInt64) <<< (t - 1)) - 1 + ((p >>> t) &&& 1)) >>> t

theorem word_bias (p t : UInt64) (hp : p.toNat < 281474976710656)
    (ht : t = 23 ∨ t = 24) :
    biased p t = FixedWord.roundShiftRightEven p t.toNat := by
  let half : UInt64 := (1 : UInt64) <<< (t - 1)
  let parity : UInt64 := (p >>> t) &&& 1
  have htNat : t.toNat = 23 ∨ t.toNat = 24 := by
    rcases ht with rfl | rfl <;> norm_num
  have ht64 : t.toNat < 64 := by omega
  have hhalf : half.toNat = 2 ^ (t.toNat - 1) := by
    rcases ht with rfl | rfl <;> decide
  have hhalfBounds : 4194304 ≤ half.toNat ∧ half.toNat ≤ 8388608 := by
    rcases ht with rfl | rfl <;> decide
  have hshift : (p >>> t).toNat = p.toNat >>> t.toNat := by
    rw [UInt64.toNat_shiftRight, Nat.mod_eq_of_lt ht64]
  have hparity : parity.toNat = (p.toNat >>> t.toNat) % 2 := by
    dsimp only [parity]
    rw [UInt64.toNat_and, hshift]
    change (p.toNat >>> t.toNat) &&& (2 ^ 1 - 1) = (p.toNat >>> t.toNat) % 2
    exact Nat.and_two_pow_sub_one_eq_mod _ 1
  have hparityBound : parity.toNat ≤ 1 := by rw [hparity]; omega
  have hplus : (p + half).toNat = p.toNat + half.toNat := by
    rw [UInt64.toNat_add, Nat.mod_eq_of_lt (by omega)]
  have hone : (1 : UInt64) ≤ p + half := by
    rw [UInt64.le_iff_toNat_le, hplus]
    change 1 ≤ p.toNat + half.toNat
    omega
  have hminus : (p + half - 1).toNat = p.toNat + half.toNat - 1 := by
    rw [UInt64.toNat_sub_of_le _ _ hone, hplus]
    rfl
  have hbias : (p + half - 1 + parity).toNat =
      p.toNat + half.toNat - 1 + parity.toNat := by
    rw [UInt64.toNat_add, hminus, Nat.mod_eq_of_lt (by omega)]
  apply UInt64.toNat_inj.mp
  change ((p + half - 1 + parity) >>> t).toNat =
    (FixedWord.roundShiftRightEven p t.toNat).toNat
  rw [UInt64.toNat_shiftRight, Nat.mod_eq_of_lt ht64, hbias,
    FixedWord.roundShiftRightEven_toNat, hhalf, hparity]
  exact (nat_bias p.toNat t.toNat htNat).symm

end Submission.R14BiasRNE
