
set_option maxRecDepth 8192
namespace Submission.R14ExponentShift
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
@[inline] def ex (u : UInt32) : UInt32 := Model.NativeBinary32.expField u

theorem ex_nat (u : UInt32) : (ex u).toNat = R2W01c.wordExp u := by
  rw [ex, Model.NativeBinary32.expField, UInt32.toNat_and, UInt32.toNat_shiftRight]
  change (u.toNat >>> 23) &&& (2 ^ 8 - 1) = u.toNat / 8388608 % 256
  rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]

theorem ex_bound (u : UInt32) : (ex u).toNat < 256 := by
  rw [ex_nat]
  exact Nat.mod_lt _ (by decide)

theorem sum_nat (u v : UInt32) :
    (ex u + ex v).toNat = R2W01c.wordExp u + R2W01c.wordExp v := by
  have hu := ex_bound u
  have hv := ex_bound v
  rw [UInt32.toNat_add, Nat.mod_eq_of_lt (by omega), ex_nat, ex_nat]

@[inline] def sign (u v : UInt32) : Bool :=
  Bool.xor (decide ((2147483648 : UInt32) ≤ u)) (decide ((2147483648 : UInt32) ≤ v))

theorem sign_eq (u v : UInt32) :
    sign u v = Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v) := by
  simp only [sign, R2W01c.wordSign, UInt32.le_iff_toNat_le]
  rfl


end Submission.R14ExponentShift


/- Draft: source dependency is retained df5c plus no other R14 fragment.
This version works directly in the actual Nat/Int word-rounder specification. -/
namespace Submission.R14NatNormal

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

def rounded (p : Nat) : Nat := roundShiftRightEven p (p.log2 - 23)
def carry (p : Nat) : Nat := if rounded p = 16777216 then 1 else 0
def mantissa (p : Nat) : Nat := if rounded p = 16777216 then 8388608 else rounded p

theorem carry_le (p : Nat) : carry p ≤ 1 := by
  unfold carry
  split <;> omega

/-- A normal finite rounding has the same mantissa at every admissible exponent.
The hypotheses explicitly include the carry in the upper boundary. -/
theorem native_round_normal (sign : Bool) (p : Nat) (e : Int)
    (hp : p ≠ 0) (hl : 23 ≤ p.log2)
    (hmin : -126 ≤ (p.log2 : Int) + e)
    (hmax : (p.log2 : Int) + e + (carry p : Int) ≤ 127) :
    Model.NativeBinary32.roundDyadic ⟨sign, p, e⟩ =
      Model.NativeBinary32.mkBits sign
        (Int.toNat ((p.log2 : Int) + e + (carry p : Int) + 127))
        (mantissa p - 8388608) := by
  have hnormal : ¬(p.log2 : Int) + e < -126 := by omega
  by_cases hc : roundShiftRightEven p (p.log2 - 23) = 16777216
  · have hc1 : carry p = 1 := by simp [carry, rounded, hc]
    have hf : ¬(p.log2 : Int) + e + 1 > 127 := by
      rw [hc1] at hmax
      norm_num at hmax
      omega
    simp [Model.NativeBinary32.roundDyadic, Model.pow2_eq_two_pow,
      hp, hl, hnormal, hf, carry, rounded, mantissa, hc]
  · have hc0 : carry p = 0 := by simp [carry, rounded, hc]
    have hf : ¬(p.log2 : Int) + e > 127 := by
      rw [hc0] at hmax
      norm_num at hmax
      omega
    simp [Model.NativeBinary32.roundDyadic, Model.pow2_eq_two_pow,
      hp, hl, hnormal, hf, carry, rounded, mantissa, hc]

theorem model_round_normal (sign : Bool) (p : Nat) (e : Int)
    (hp : p ≠ 0) (hl : 23 ≤ p.log2)
    (hmin : -126 ≤ (p.log2 : Int) + e)
    (hmax : (p.log2 : Int) + e + (carry p : Int) ≤ 127) :
    Model.roundDyadic FloatFormat.binary32 ⟨sign, p, e⟩ =
      Model.ofFields FloatFormat.binary32 sign
        (Int.toNat ((p.log2 : Int) + e + (carry p : Int) + 127))
        (mantissa p - 8388608) := by
  rw [← Model.NativeBinary32.ofUInt32_roundDyadic,
    native_round_normal sign p e hp hl hmin hmax,
    Model.NativeBinary32.ofUInt32_mkBits]

/-- Unlike the old NormalBand helper, this covers every normal raw exponent1..254. -/
theorem raw_normal_decode (u : UInt32)
    (he0 : 0 < R2W01c.wordExp u) (hehi : R2W01c.wordExp u < 255) :
    Model.toDyadic? (R2W01c.rawModel u) =
      some ⟨R2W01c.wordSign u, (R2W01b.mantissa u).toNat,
        (R2W01c.wordExp u : Int) - 150⟩ := by
  rw [R2W01c.rawModel_eq_ofUInt32]
  change Model.toDyadic? (R2W01c.raw32 u) = _
  rw [R2W01c.raw32_eq_fields, R2W01c.mantissa_toNat]
  exact R2W01c.fields32_toDyadic (R2W01c.wordSign u) (R2W01c.wordExp u)
    (R2W01c.wordFrac u) he0 hehi (R2W01c.wordFrac_lt u)


end Submission.R14NatNormal


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
    rw [parity, UInt64.toNat_and, hshift]
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
