
/- Independent exact RNE lemma requested by the integer-normal development route. -/
namespace Submission.R14BiasRNE

open FloatLib.Numerics

private theorem quotient_bias (p half : Nat) (hhalf : 0 < half) :
    roundQuotientEven p (2 * half) =
      (p + half - 1 + (p / (2 * half)) % 2) / (2 * half) := by
  let q := p / (2 * half)
  let r := p % (2 * half)
  have hr : r < 2 * half := Nat.mod_lt _ (by omega)
  have hparity : q % 2 < 2 := Nat.mod_lt _ (by decide)
  have hp : p = (2 * half) * q + r := (Nat.div_add_mod p (2 * half)).symm
  have hb : p + half - 1 + q % 2 =
      (r + half - 1 + q % 2) + (2 * half) * q := by omega
  change (if 2 * r < 2 * half then q
    else if 2 * half < 2 * r then q + 1
    else if q % 2 == 0 then q else q + 1) =
      (p + half - 1 + q % 2) / (2 * half)
  rw [hb, Nat.add_mul_div_left _ _ (by omega)]
  simp only [beq_iff_eq]
  split_ifs with hbelow habove heven
  · have hd : (r + half - 1 + q % 2) / (2 * half) = 0 :=
      Nat.div_eq_of_lt (by omega)
    rw [hd]
    omega
  · have hd : (r + half - 1 + q % 2) / (2 * half) = 1 :=
      Nat.div_eq_of_lt_le (by omega) (by omega)
    rw [hd]
    omega
  · have hd : (r + half - 1 + q % 2) / (2 * half) = 0 :=
      Nat.div_eq_of_lt (by omega)
    rw [hd]
    omega
  · have hd : (r + half - 1 + q % 2) / (2 * half) = 1 :=
      Nat.div_eq_of_lt_le (by omega) (by omega)
    rw [hd]
    omega

theorem nat_bias (p t : Nat) (ht : t = 23 ∨ t = 24) :
    roundShiftRightEven p t =
      (p + 2 ^ (t - 1) - 1 + (p >>> t) % 2) >>> t := by
  rcases ht with rfl | rfl
  · simpa [roundShiftRightEven_eq_roundQuotientEven, Nat.shiftRight_eq_div_pow] using
      quotient_bias p 4194304 (by decide)
  · simpa [roundShiftRightEven_eq_roundQuotientEven, Nat.shiftRight_eq_div_pow] using
      quotient_bias p 8388608 (by decide)

@[inline] def biased (p t : UInt64) : UInt64 :=
  (p + ((1 : UInt64) <<< (t - 1)) - 1 + ((p >>> t) &&& 1)) >>> t

theorem word_bias (p t : UInt64) (hp : p.toNat < 281474976710656)
    (ht : t = 23 ∨ t = 24) :
    biased p t = FixedWord.roundShiftRightEven p t.toNat := by
  have htNat : t.toNat = 23 ∨ t.toNat = 24 := by
    rcases ht with rfl | rfl <;> norm_num
  have ht0 : 1 ≤ t.toNat := by omega
  have ht24 : t.toNat ≤ 24 := by omega
  let half : UInt64 := (1 : UInt64) <<< (t - 1)
  let parity : UInt64 := (p >>> t) &&& 1
  have ht64 : t.toNat < 64 := by omega
  have htOne : (1 : UInt64) ≤ t := by
    rw [UInt64.le_iff_toNat_le]
    exact ht0
  have hsub : (t - 1).toNat = t.toNat - 1 := by
    rw [UInt64.toNat_sub_of_le _ _ htOne]
    rfl
  have hp2 : 2 ^ (t.toNat - 1) ≤ 8388608 := by
    have h : 2 ^ (t.toNat - 1) ≤ 2 ^ 23 := Nat.pow_le_pow_right (by decide)
      (show t.toNat - 1 ≤ 23 by omega)
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
  have hhalfBounds : 1 ≤ half.toNat ∧ half.toNat ≤ 8388608 := by
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
  exact (nat_bias p.toNat t.toNat htNat).symm

end Submission.R14BiasRNE
