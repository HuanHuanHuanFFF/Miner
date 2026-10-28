/- R22 fixed-three-bit and far-gap Nat interfaces. NOT_RUN.
   No Model.add/public ADD claim, runtime, or candidate is added. -/
namespace Submission.R22BroadWordMath
open FloatLib.Numerics

theorem nat_bias3 (n : Nat) :
    (n + 3 + (n / 8) % 2) / 8 = roundShiftRightEven n 3 := by
  have hdecomp := Nat.div_add_mod n 8
  have hrem := Nat.mod_lt n (by decide : 0 < 8)
  have hparity := Nat.mod_lt (n / 8) (by decide : 0 < 2)
  rw [roundShiftRightEven_eq_roundQuotientEven]
  change (n + 3 + (n / 8) % 2) / 8 =
    (if 2 * (n % 8) < 8 then n / 8 else if 8 < 2 * (n % 8) then n / 8 + 1
      else if (n / 8) % 2 == 0 then n / 8 else n / 8 + 1)
  simp only [beq_iff_eq]
  split_ifs <;> omega

theorem u32_bias3_correct (n : UInt32) (hn : n.toNat < 2 ^ 28) :
    (n + (3 : UInt32) + ((n >>> (3 : UInt32)) &&& (1 : UInt32))).toNat =
      n.toNat + 3 + (n.toNat / 8) % 2 ∧
    ((n + (3 : UInt32) + ((n >>> (3 : UInt32)) &&& (1 : UInt32))) >>> (3 : UInt32)).toNat =
      roundShiftRightEven n.toNat 3 := by
  change n.toNat < 268435456 at hn
  let parity : UInt32 := (n >>> (3 : UInt32)) &&& (1 : UInt32)
  have hparity : parity.toNat = (n.toNat / 8) % 2 := by
    dsimp only [parity]
    rw [UInt32.toNat_and, UInt32.toNat_shiftRight]
    change (n.toNat >>> 3) &&& 1 = (n.toNat / 8) % 2
    rw [Nat.shiftRight_eq_div_pow]
    exact Nat.and_two_pow_sub_one_eq_mod (n.toNat / 8) 1
  have hp : parity.toNat ≤ 1 := by
    rw [hparity]
    have h := Nat.mod_lt (n.toNat / 8) (by decide : 0 < 2)
    omega
  have hplus : (n + (3 : UInt32)).toNat = n.toNat + 3 := by
    rw [UInt32.toNat_add]
    change (n.toNat + 3) % 4294967296 = n.toNat + 3
    exact Nat.mod_eq_of_lt (by omega)
  have hsum : (n + (3 : UInt32) + parity).toNat = n.toNat + 3 + parity.toNat := by
    rw [UInt32.toNat_add, hplus]
    change (n.toNat + 3 + parity.toNat) % 4294967296 = n.toNat + 3 + parity.toNat
    exact Nat.mod_eq_of_lt (by omega)
  constructor
  · simpa only [hparity] using hsum
  · change ((n + (3 : UInt32) + parity) >>> (3 : UInt32)).toNat = _
    rw [UInt32.toNat_shiftRight]
    change (n + (3 : UInt32) + parity).toNat >>> 3 = _
    rw [hsum, hparity, Nat.shiftRight_eq_div_pow]
    exact nat_bias3 n.toNat

theorem far_round_absorb (hi lo d : Nat) (hlo : lo < 2 ^ 24) (hd : 25 ≤ d) :
    roundShiftRightEven (hi * 2 ^ d + lo) d = hi := by
  have hp : (2 : Nat) ^ 25 ≤ 2 ^ d := Nat.pow_le_pow_right (by decide : 0 < 2) hd
  change lo < 16777216 at hlo
  change 33554432 ≤ 2 ^ d at hp
  have hsmall : 2 * lo < 2 ^ d := by omega
  have hlt : lo < 2 ^ d := by omega
  have hpos : 0 < 2 ^ d := Nat.two_pow_pos d
  have hq : (hi * 2 ^ d + lo) / 2 ^ d = hi := by
    rw [Nat.mul_comm hi (2 ^ d), Nat.mul_add_div hpos, Nat.div_eq_of_lt hlt, Nat.add_zero]
  have hr : (hi * 2 ^ d + lo) % 2 ^ d = lo := Nat.mul_add_mod_of_lt hlt
  simp only [roundShiftRightEven_eq_roundQuotientEven, roundQuotientEven,
    hq, hr, hsmall, ite_true]

end Submission.R22BroadWordMath
