namespace BranchlessRNESeed
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


theorem nat_grouped_bias (p t : Nat) (ht : t=23 ∨ t=24) :
    roundShiftRightEven p t =
      (p+(2^(t-1)-1)+(p >>> t)%2) >>> t := by
  have hpos := Nat.two_pow_pos (t-1)
  have he : p+2^(t-1)-1 = p+(2^(t-1)-1) := by omega
  simpa only [he] using nat_bias p t ht

@[inline] def grouped (p t : UInt64) : UInt64 :=
  (p+(((1 : UInt64) <<< (t-1))-1)+((p >>> t) &&& 1)) >>> t

theorem word_grouped (p t : UInt64) (hp : p.toNat ≤ 281474943156225)
    (ht : t=23 ∨ t=24) :
    grouped p t = FixedWord.roundShiftRightEven p t.toNat := by
  let half : UInt64 := (1 : UInt64) <<< (t-1)
  let bias : UInt64 := half-1
  let parity : UInt64 := (p >>> t) &&& 1
  have htNat : t.toNat=23 ∨ t.toNat=24 := by
    rcases ht with rfl | rfl <;> norm_num
  have ht64 : t.toNat < 64 := by omega
  have hhalf : half.toNat=2^(t.toNat-1) := by
    rcases ht with rfl | rfl <;> decide
  have hb : 4194304 ≤ half.toNat ∧ half.toNat ≤ 8388608 := by
    rcases ht with rfl | rfl <;> decide
  have hone : (1 : UInt64) ≤ half := by
    rw [UInt64.le_iff_toNat_le]
    change 1 ≤ half.toNat
    omega
  have hminus : bias.toNat=half.toNat-1 := by
    dsimp only [bias]
    rw [UInt64.toNat_sub_of_le _ _ hone]
    rfl
  have hshift : (p >>> t).toNat=p.toNat >>> t.toNat := by
    rw [UInt64.toNat_shiftRight,Nat.mod_eq_of_lt ht64]
  have hparity : parity.toNat=(p.toNat >>> t.toNat)%2 := by
    dsimp only [parity]
    rw [UInt64.toNat_and,hshift]
    change (p.toNat >>> t.toNat) &&& (2^1-1) = (p.toNat >>> t.toNat)%2
    exact Nat.and_two_pow_sub_one_eq_mod _ 1
  have hparityBound : parity.toNat ≤ 1 := by rw [hparity]; omega
  have hplus : (p+bias).toNat=p.toNat+(half.toNat-1) := by
    rw [UInt64.toNat_add,hminus,Nat.mod_eq_of_lt (by omega)]
  have hsum : (p+bias+parity).toNat=p.toNat+(half.toNat-1)+parity.toNat := by
    rw [UInt64.toNat_add,hplus,Nat.mod_eq_of_lt (by omega)]
  apply UInt64.toNat.inj
  change ((p+bias+parity) >>> t).toNat = (FixedWord.roundShiftRightEven p t.toNat).toNat
  rw [UInt64.toNat_shiftRight,Nat.mod_eq_of_lt ht64,hsum,
    FixedWord.roundShiftRightEven_toNat,hhalf,hparity]
  exact (nat_grouped_bias p.toNat t.toNat htNat).symm

theorem grouped_eq_existing_rse (p t : UInt64) (hp : p.toNat ≤ 281474943156225)
    (ht : t=23 ∨ t=24) :
    grouped p t = Submission.FastMul.rse p t := by
  calc
    _ = FixedWord.roundShiftRightEven p t.toNat := word_grouped p t hp ht
    _ = Submission.FastMul.rseAny p t := (Submission.FastMul.rseAny_eq p t).symm
    _ = Submission.FastMul.rse p t := by rcases ht with rfl | rfl <;> rfl

end BranchlessRNESeed
