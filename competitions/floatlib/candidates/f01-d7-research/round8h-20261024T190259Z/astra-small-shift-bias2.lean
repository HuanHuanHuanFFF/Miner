/- Draft / NOT_RUN. Pure-word add companion. This fragment includes its own
   namespace and does not modify the frozen t=23/24 R14BiasRNE source.
   Bias arithmetic is exact only under the explicit no-wrap bound below. -/
namespace Submission.R14SmallShiftBias

open FloatLib.Numerics

theorem nat_bias (p t : Nat) (ht0 : 1 ≤ t) (ht8 : t ≤ 8) :
    roundShiftRightEven p t =
      (p + 2 ^ (t - 1) - 1 + (p >>> t) % 2) >>> t := by
  interval_cases t <;>
    rw [roundShiftRightEven_eq_roundQuotientEven] <;>
    unfold roundQuotientEven <;>
    norm_num [Nat.shiftRight_eq_div_pow] <;>
    simp only [beq_iff_eq] <;>
    split_ifs <;> omega

@[inline] def biased (p t : UInt64) : UInt64 :=
  (p + ((1 : UInt64) <<< (t - 1)) - 1 + ((p >>> t) &&& 1)) >>> t

theorem word_bias (p t : UInt64) (hp : p.toNat < 281474976710656)
    (ht0 : 1 ≤ t.toNat) (ht8 : t.toNat ≤ 8) :
    biased p t = FixedWord.roundShiftRightEven p t.toNat := by
  let half : UInt64 := (1 : UInt64) <<< (t - 1)
  let parity : UInt64 := (p >>> t) &&& 1
  have ht64 : t.toNat < 64 := by omega
  have htOne : (1 : UInt64) ≤ t := by
    rw [UInt64.le_iff_toNat_le]
    exact ht0
  have hsub : (t - 1).toNat = t.toNat - 1 := by
    rw [UInt64.toNat_sub_of_le _ _ htOne]
    rfl
  have hp2 : 2 ^ (t.toNat - 1) ≤ 128 := by
    have h : 2 ^ (t.toNat - 1) ≤ 2 ^ 7 := Nat.pow_le_pow_right (by decide)
      (show t.toNat - 1 ≤ 7 by omega)
    norm_num at h
    exact h
  have hp2pos : 0 < 2 ^ (t.toNat - 1) := Nat.two_pow_pos _
  have hhalf : half.toNat = 2 ^ (t.toNat - 1) := by
    dsimp only [half]
    rw [UInt64.toNat_shiftLeft, hsub,
      Nat.mod_eq_of_lt (show t.toNat - 1 < 64 by omega)]
    change (1 <<< (t.toNat - 1)) % 18446744073709551616 = _
    rw [Nat.shiftLeft_eq, Nat.one_mul]
    exact Nat.mod_eq_of_lt (by omega)
  have hhalfBounds : 1 ≤ half.toNat ∧ half.toNat ≤ 128 := by
    rw [hhalf]
    omega
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
  exact (nat_bias p.toNat t.toNat ht0 ht8).symm

end Submission.R14SmallShiftBias
