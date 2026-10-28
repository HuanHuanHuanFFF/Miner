import Submission

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
  · rw [roundShiftRightEven_eq_roundQuotientEven]
    change roundQuotientEven p 8388608 =
      (p + 4194304 - 1 + (p >>> 23) % 2) >>> 23
    simpa only [Nat.shiftRight_eq_div_pow, Nat.reducePow, Nat.reduceSub, Nat.reduceMul] using
      quotient_bias p 4194304 (by decide)
  · rw [roundShiftRightEven_eq_roundQuotientEven]
    change roundQuotientEven p 16777216 =
      (p + 8388608 - 1 + (p >>> 24) % 2) >>> 24
    simpa only [Nat.shiftRight_eq_div_pow, Nat.reducePow, Nat.reduceSub, Nat.reduceMul] using
      quotient_bias p 8388608 (by decide)


theorem nat_grouped_bias (p t : Nat) (ht : t=23 ∨ t=24) :
    roundShiftRightEven p t =
      (p+(2^(t-1)-1)+(p >>> t)%2) >>> t := by
  have hpos := Nat.two_pow_pos (t-1)
  have he : p+2^(t-1)-1 = p+(2^(t-1)-1) := by omega
  simpa only [he] using nat_bias p t ht

end BranchlessRNESeed


namespace R19PostBias
open FloatLib.Numerics

def shift (p : Nat) : Nat := if p < 140737488355328 then 23 else 24
def biased (p : Nat) : Nat := p + (2 ^ (shift p - 1) - 1) + (p >>> shift p) % 2

/-- Uses the retained uncompiled bias proof, not an independent new proof. -/
theorem biased_quotient (p : Nat) :
    biased p >>> shift p = roundShiftRightEven p (shift p) := by
  have hk : shift p = 23 ∨ shift p = 24 := by
    unfold shift
    split <;> simp_all
  exact (BranchlessRNESeed.nat_grouped_bias p (shift p) hk).symm

theorem biased_bounds (p : Nat)
    (hlo : 70368744177664 ≤ p) (hhi : p ≤ 281474943156225) :
    70368744177664 ≤ biased p ∧ biased p ≤ 281474951544833 := by
  have hpar : (p >>> shift p) % 2 < 2 := Nat.mod_lt _ (by decide)
  unfold biased
  by_cases hp : p < 140737488355328
  · simp only [shift,if_pos hp]
    norm_num only [Nat.reduceSub,Nat.reducePow]
    simp only [shift,if_pos hp] at hpar
    omega
  · simp only [shift,if_neg hp]
    norm_num only [Nat.reduceSub,Nat.reducePow]
    simp only [shift,if_neg hp] at hpar
    omega

private theorem low_bias_upper (p r : Nat) (hp : p < 140737488355328) (hr : r < 2) :
    p + 4194303 + r < 140737496743936 := by
  have hb : p + 4194303 + r ≤ 140737488355328 + 4194303 + 1 :=
    Nat.add_le_add (Nat.add_le_add (Nat.le_of_lt hp) (Nat.le_refl _))
      (Nat.le_of_lt_succ hr)
  exact lt_of_le_of_lt hb (by decide)

private theorem below_boundary (b : Nat) (hb : b < 140737488355328) :
    b / 140737488355328 = 0 ∧ b / 8388608 ≠ 16777216 := by
  have hq : b / 8388608 < 16777216 :=
    (Nat.div_lt_iff_lt_mul (by decide)).2 (by
      simpa only [Nat.reduceMul] using hb)
  exact ⟨Nat.div_eq_of_lt hb, Nat.ne_of_lt hq⟩

private theorem at_boundary (b : Nat)
    (hlo : 140737488355328 ≤ b) (hhi : b < 140737496743936) :
    b / 140737488355328 = 1 ∧
      b / 8388608 = 16777216 ∧ b / 16777216 = 8388608 := by
  refine ⟨?_, ?_, ?_⟩
  · apply Nat.div_eq_of_lt_le
    · simpa only [Nat.one_mul] using hlo
    · exact lt_trans hhi (by decide)
  · apply Nat.div_eq_of_lt_le
    · simpa only [Nat.reduceMul] using hlo
    · simpa only [Nat.reduceAdd, Nat.reduceMul] using hhi
  · apply Nat.div_eq_of_lt_le
    · simpa only [Nat.reduceMul] using hlo
    · exact lt_trans hhi (by decide)

private theorem upper_half (b : Nat)
    (hlo : 140737488355328 ≤ b) (hhi : b ≤ 281474951544833) :
    b / 140737488355328 = 1 ∧ b / 16777216 ≠ 16777216 := by
  have hq : b / 16777216 < 16777216 :=
    (Nat.div_lt_iff_lt_mul (by decide)).2 (lt_of_le_of_lt hhi (by decide))
  refine ⟨?_, Nat.ne_of_lt hq⟩
  apply Nat.div_eq_of_lt_le
  · simpa only [Nat.one_mul] using hlo
  · exact lt_of_le_of_lt hhi (by decide)

private theorem normalized_low (b : Nat) (hb : b < 140737496743936) :
    b >>> 47 = (if b >>> 23 = 16777216 then 1 else 0) ∧
      b >>> (23 + (b >>> 47)) =
        (if b >>> 23 = 16777216 then 8388608 else b >>> 23) := by
  simp only [Nat.shiftRight_eq_div_pow]
  by_cases h : b < 140737488355328
  · have h0 := (below_boundary b h).1
    have hn := (below_boundary b h).2
    constructor
    · simpa only [h0, if_neg hn] using (rfl : (0 : Nat) = 0)
    · simpa only [h0, if_neg hn, Nat.add_zero] using (rfl : b / 8388608 = b / 8388608)
  · have hs := at_boundary b (Nat.le_of_not_gt h) hb
    constructor
    · simpa only [hs.1, hs.2.1, ↓reduceIte] using (rfl : (1 : Nat) = 1)
    · simpa only [hs.1, hs.2.1, ↓reduceIte] using hs.2.2

private theorem normalized_high (b : Nat)
    (hlo : 140737488355328 ≤ b) (hhi : b ≤ 281474951544833) :
    b >>> 47 = 1 + (if b >>> 24 = 16777216 then 1 else 0) ∧
      b >>> (23 + (b >>> 47)) =
        (if b >>> 24 = 16777216 then 8388608 else b >>> 24) := by
  simp only [Nat.shiftRight_eq_div_pow]
  have hs := upper_half b hlo hhi
  constructor
  · simpa only [hs.1, if_neg hs.2, Nat.add_zero] using (rfl : (1 : Nat) = 1)
  · simpa only [hs.1, if_neg hs.2] using (rfl : b / 16777216 = b / 16777216)

theorem normalized_quotient (p : Nat)
    (hlo : 70368744177664 ≤ p) (hhi : p ≤ 281474943156225) :
    let q := roundShiftRightEven p (shift p)
    let h := biased p >>> 47
    h = (if p < 140737488355328 then 0 else 1) + (if q = 16777216 then 1 else 0) ∧
      biased p >>> (23 + h) = (if q = 16777216 then 8388608 else q) := by
  have hb := biased_bounds p hlo hhi
  have hq := biased_quotient p
  dsimp only
  by_cases hp : p < 140737488355328
  · have hk : shift p = 23 := by simp only [shift, if_pos hp]
    have hsmall : biased p < 140737496743936 := by
      unfold biased
      rw [hk]
      change p + 4194303 + (p >>> 23) % 2 < 140737496743936
      exact low_bias_upper p _ hp (Nat.mod_lt _ (by decide))
    rw [hk] at hq ⊢
    rw [← hq]
    simpa only [if_pos hp, Nat.zero_add] using normalized_low (biased p) hsmall
  · have hk : shift p = 24 := by simp only [shift, if_neg hp]
    have hge : p ≤ biased p := by
      unfold biased
      exact Nat.le_trans (Nat.le_add_right _ _) (Nat.le_add_right _ _)
    have hlarge : 140737488355328 ≤ biased p :=
      Nat.le_trans (Nat.le_of_not_gt hp) hge
    rw [hk] at hq ⊢
    rw [← hq]
    simpa only [if_neg hp] using normalized_high (biased p) hlarge hb.2
end R19PostBias


namespace Submission.R19DirectBiasWord
open FloatLib.Numerics

/-- Exact unrounded bias sum; body reuses the retained seed's no-wrap proof. -/
theorem biased_sum_nat (p t : UInt64) (hp : p.toNat ≤ 281474943156225)
    (ht : t=23 ∨ t=24) :
    (p+(((1 : UInt64) <<< (t-1))-1)+((p >>> t) &&& 1)).toNat =
      p.toNat+(2^(t.toNat-1)-1)+(p.toNat >>> t.toNat)%2 := by
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
  change (p+bias+parity).toNat = _
  rw [hsum,hhalf,hparity]

def biasedWord (p : UInt64) : UInt64 :=
  if p < (140737488355328 : UInt64) then p+4194303+((p >>> 23) &&& 1)
  else p+8388607+((p >>> 24) &&& 1)

theorem biasedWord_nat (p : UInt64) (hp : p.toNat ≤ 281474943156225) :
    (biasedWord p).toNat = R19PostBias.biased p.toNat := by
  have hc : p < (140737488355328 : UInt64) ↔ p.toNat < 140737488355328 := by
    rw [UInt64.lt_iff_toNat_lt] <;> rfl
  by_cases hn : p.toNat < 140737488355328
  · have hw := hc.mpr hn
    have h := biased_sum_nat p 23 hp (Or.inl rfl)
    change (p+4194303+((p >>> 23) &&& 1)).toNat =
      p.toNat+4194303+(p.toNat >>> 23)%2 at h
    simpa only [biasedWord,if_pos hw,R19PostBias.biased,R19PostBias.shift,if_pos hn,
      Nat.reduceSub,Nat.reducePow] using h
  · have hw : ¬ p < (140737488355328 : UInt64) := fun h => hn (hc.mp h)
    have h := biased_sum_nat p 24 hp (Or.inr rfl)
    change (p+8388607+((p >>> 24) &&& 1)).toNat =
      p.toNat+8388607+(p.toNat >>> 24)%2 at h
    simpa only [biasedWord,if_neg hw,R19PostBias.biased,R19PostBias.shift,if_neg hn,
      Nat.reduceSub,Nat.reducePow] using h

def highWord (p : UInt64) : UInt64 := biasedWord p >>> 47
def shiftWord (p : UInt64) : UInt64 := 23+highWord p
def mantissaWord (p : UInt64) : UInt32 := (biasedWord p >>> shiftWord p).toUInt32

theorem highWord_nat (p : UInt64) (hp : p.toNat ≤ 281474943156225) :
    (highWord p).toNat = R19PostBias.biased p.toNat >>> 47 := by
  rw [highWord,UInt64.toNat_shiftRight,biasedWord_nat p hp] <;> rfl

theorem highWord_le_one (p : UInt64)
    (hlo : 70368744177664 ≤ p.toNat) (hhi : p.toNat ≤ 281474943156225) :
    (highWord p).toNat ≤ 1 := by
  have hb := R19PostBias.biased_bounds p.toNat hlo hhi
  rw [highWord_nat p hhi,Nat.shiftRight_eq_div_pow]
  omega

theorem shiftWord_nat (p : UInt64)
    (hlo : 70368744177664 ≤ p.toNat) (hhi : p.toNat ≤ 281474943156225) :
    (shiftWord p).toNat = 23+(R19PostBias.biased p.toNat >>> 47) := by
  have hh := highWord_le_one p hlo hhi
  rw [shiftWord,UInt64.toNat_add,highWord_nat p hhi]
  change (23+(R19PostBias.biased p.toNat >>> 47)) % 18446744073709551616 = _
  rw [highWord_nat p hhi] at hh
  exact Nat.mod_eq_of_lt (by omega)

theorem mantissaWord_nat (p : UInt64)
    (hlo : 70368744177664 ≤ p.toNat) (hhi : p.toNat ≤ 281474943156225) :
    (mantissaWord p).toNat =
      if roundShiftRightEven p.toNat (R19PostBias.shift p.toNat) = 16777216 then 8388608
      else roundShiftRightEven p.toNat (R19PostBias.shift p.toNat) := by
  have hh := highWord_le_one p hlo hhi
  have hn := highWord_nat p hhi
  have hs := shiftWord_nat p hlo hhi
  have hb := R19PostBias.biased_bounds p.toNat hlo hhi
  have hr := R19PostBias.normalized_quotient p.toNat hlo hhi
  have hs64 : (shiftWord p).toNat < 64 := by omega
  have hw : (biasedWord p >>> shiftWord p).toNat =
      R19PostBias.biased p.toNat >>> (23+(R19PostBias.biased p.toNat >>> 47)) := by
    rw [UInt64.toNat_shiftRight,Nat.mod_eq_of_lt hs64,biasedWord_nat p hhi,hs]
  have hfit : (biasedWord p >>> shiftWord p).toNat < 4294967296 := by
    rw [hw]
    have hc : R19PostBias.biased p.toNat >>> 47 = 0 ∨ R19PostBias.biased p.toNat >>> 47 = 1 := by omega
    rcases hc with hc | hc <;>
      rw [hc] <;>
      norm_num only [Nat.reduceAdd,Nat.shiftRight_eq_div_pow,Nat.reducePow] <;> omega
  unfold mantissaWord
  simp only [Submission.FastMul.toUInt32_eq,UInt32.toNat_ofNat']
  rw [Nat.mod_eq_of_lt hfit,hw]
  exact hr.2

end Submission.R19DirectBiasWord


namespace Submission.R19BiasShape
open FloatLib.Numerics

def rounded (p : Nat) : Nat := roundShiftRightEven p (p.log2-23)
def carry (p : Nat) : Nat := if rounded p=16777216 then 1 else 0
def mantissa (p : Nat) : Nat := if rounded p=16777216 then 8388608 else rounded p

theorem carry_le (p : Nat) : carry p ≤ 1 := by
  unfold carry
  split <;> omega

theorem leading_bounds (p : Nat)
    (hlo : 70368744177664 ≤ p) (hhi : p < 281474976710656) :
    46 ≤ p.log2 ∧ p.log2 ≤ 47 := by
  have hn : p ≠ 0 := by omega
  have hl : 46 ≤ p.log2 := (Nat.le_log2 hn).2 (by norm_num; exact hlo)
  have hh : p.log2 < 48 := (Nat.log2_lt hn).2 (by norm_num; exact hhi)
  omega

theorem no_carry_at_47 (p : Nat)
    (hmax : p ≤ 281474943156225) (hlog : p.log2 = 47) : carry p = 0 := by
  have hq : p / 16777216 ≤ 16777214 := by omega
  have hr := roundShiftRightEven_le_shiftRight_add1 p 24
  norm_num [Nat.shiftRight_eq_div_pow] at hr
  have hb : rounded p ≤ 16777215 := by
    unfold rounded
    rw [hlog]
    change roundShiftRightEven p 24 ≤ 16777215
    omega
  have hn : rounded p ≠ 16777216 := by omega
  simp [carry, hn]

theorem mantissa_bounds (p : Nat)
    (hlo : 70368744177664 ≤ p) (hhi : p < 281474976710656) :
    8388608 ≤ mantissa p ∧ mantissa p < 16777216 := by
  have hn : p ≠ 0 := by omega
  have hl := leading_bounds p hlo hhi
  have hlow := Nat.log2_self_le hn
  have hupp := Nat.lt_log2_self (n := p)
  have hquotient :
      8388608 ≤ Nat.shiftRight p (p.log2 - 23) ∧
      Nat.shiftRight p (p.log2 - 23) < 16777216 := by
    have hc : p.log2 = 46 ∨ p.log2 = 47 := by omega
    rcases hc with hc | hc <;>
      simp only [hc] at hlow hupp ⊢ <;>
      norm_num [Nat.shiftRight_eq_div_pow] at hlow hupp ⊢ <;> omega
  have hrlo := shiftRight_le_roundShiftRightEven p (p.log2 - 23)
  have hrhi := roundShiftRightEven_le_shiftRight_add1 p (p.log2 - 23)
  by_cases hc : rounded p = 16777216
  · simp [mantissa, hc]
  · simp only [mantissa, hc, ↓reduceIte]
    change roundShiftRightEven p (p.log2 - 23) ≠ 16777216 at hc
    unfold rounded
    omega

theorem literal_shift_eq (p : Nat)
    (hlo : 70368744177664 ≤ p) (hhi : p ≤ 281474943156225) :
    R19PostBias.shift p = p.log2-23 := by
  have hn : p ≠ 0 := by omega
  have hl := leading_bounds p hlo (by omega)
  by_cases hp : p < 140737488355328
  · have h47 : p.log2 < 47 := (Nat.log2_lt hn).2 (by norm_num; exact hp)
    simp only [R19PostBias.shift,if_pos hp]
    omega
  · have h47 : 47 ≤ p.log2 := (Nat.le_log2 hn).2 (by norm_num; omega)
    simp only [R19PostBias.shift,if_neg hp]
    omega

theorem normal_scale_nat (s : UInt32) (hs : 128 ≤ s.toNat) :
    (s.toUInt64-2).toNat = s.toNat-2 := by
  have hle : (2 : UInt64) ≤ s.toUInt64 := by
    rw [UInt64.le_iff_toNat_le,UInt32.toNat_toUInt64]
    change 2 ≤ s.toNat
    omega
  rw [UInt64.toNat_sub_of_le _ _ hle,UInt32.toNat_toUInt64]
  all_goals rfl

theorem leading_nat (p : UInt64) :
    (FastMul.fastLog2 p).toNat = p.toNat.log2 := by
  rw [FastMul.fastLog2_eq] <;> rfl

theorem position_nat (p : UInt64) (s : UInt32)
    (hlo : 70368744177664 ≤ p.toNat) (hhi : p.toNat ≤ 281474943156225)
    (hs0 : 128 ≤ s.toNat) (hs1 : s.toNat ≤ 380) :
    (FastMul.fastLog2 p+(s.toUInt64-2)).toNat = p.toNat.log2+s.toNat-2 := by
  have hl := leading_bounds p.toNat hlo (by omega)
  rw [UInt64.toNat_add,leading_nat,normal_scale_nat s hs0]
  change (p.toNat.log2+(s.toNat-2)) % 18446744073709551616 = _
  rw [Nat.mod_eq_of_lt (by omega)]
  omega

theorem shift_word_nat (p : UInt64)
    (hlo : 70368744177664 ≤ p.toNat) (hhi : p.toNat ≤ 281474943156225) :
    (FastMul.fastLog2 p-23).toNat = p.toNat.log2-23 := by
  have hl := leading_bounds p.toNat hlo (by omega)
  have hle : (23 : UInt64) ≤ FastMul.fastLog2 p := by
    rw [UInt64.le_iff_toNat_le,leading_nat]
    change 23 ≤ p.toNat.log2
    omega
  rw [UInt64.toNat_sub_of_le _ _ hle,leading_nat]
  all_goals rfl

theorem rounded_word_nat (p : UInt64)
    (hlo : 70368744177664 ≤ p.toNat) (hhi : p.toNat ≤ 281474943156225) :
    (FastMul.rseAny p (FastMul.fastLog2 p-23)).toNat = rounded p.toNat := by
  rw [FastMul.rseAny_eq,FixedWord.roundShiftRightEven_toNat,shift_word_nat p hlo hhi]
  all_goals rfl

theorem normalized_position_le (p : UInt64) (s : UInt32)
    (hlo : 70368744177664 ≤ p.toNat) (hhi : p.toNat ≤ 281474943156225)
    (hs0 : 128 ≤ s.toNat) (hs1 : s.toNat ≤ 380) :
    let r := FastMul.rseAny p (FastMul.fastLog2 p-23)
    let position := FastMul.fastLog2 p+(s.toUInt64-2)
    (if r == 16777216 then position+1 else position).toNat ≤ 425 := by
  have hl := leading_bounds p.toNat hlo (by omega)
  have hp := position_nat p s hlo hhi hs0 hs1
  have hr := rounded_word_nat p hlo hhi
  dsimp only
  split
  · rename_i hc
    have hw : FastMul.rseAny p (FastMul.fastLog2 p-23) = (16777216 : UInt64) := by
      exact beq_iff_eq.mp hc
    have hn : rounded p.toNat = 16777216 := by
      rw [← hr,hw] <;> rfl
    have h46 : p.toNat.log2 = 46 := by
      by_contra h
      have h47 : p.toNat.log2 = 47 := by omega
      have hz := no_carry_at_47 p.toNat hhi h47
      simp [carry,hn] at hz
    rw [UInt64.toNat_add,hp]
    change (p.toNat.log2+s.toNat-2+1) % 18446744073709551616 ≤ 425
    rw [Nat.mod_eq_of_lt (by omega)]
    omega
  · rw [hp]
    omega

theorem roundP_normal (sign : Bool) (p : UInt64) (s : UInt32)
    (hlo : 70368744177664 ≤ p.toNat) (hhi : p.toNat ≤ 281474943156225)
    (hs0 : 128 ≤ s.toNat) (hs1 : s.toNat ≤ 380) :
    FastMul.roundP sign p (s.toUInt64-2) =
      let r := FastMul.rseAny p (FastMul.fastLog2 p-23)
      let position := FastMul.fastLog2 p+(s.toUInt64-2)
      let normalizedPosition := if r == 16777216 then position+1 else position
      let normalizedMantissa := if r == 16777216 then 8388608 else r
      FastMul.mkW sign (normalizedPosition-171).toUInt32 (FastMul.fracW normalizedMantissa) := by
  have hl := leading_bounds p.toNat hlo (by omega)
  have hp := position_nat p s hlo hhi hs0 hs1
  have hz : p ≠ 0 := by
    intro h
    subst p
    norm_num at hlo
  have hposition : ¬ FastMul.fastLog2 p+(s.toUInt64-2) < (172 : UInt64) := by
    rw [UInt64.lt_iff_toNat_lt,hp]
    change ¬ p.toNat.log2+s.toNat-2 < 172
    omega
  have hleading : ¬ FastMul.fastLog2 p < (23 : UInt64) := by
    rw [UInt64.lt_iff_toNat_lt,leading_nat]
    change ¬ p.toNat.log2 < 23
    omega
  have hover := normalized_position_le p s hlo hhi hs0 hs1
  have hnoOverflow : ¬ (if FastMul.rseAny p (FastMul.fastLog2 p-23) == 16777216 then
      FastMul.fastLog2 p+(s.toUInt64-2)+1 else FastMul.fastLog2 p+(s.toUInt64-2)) > (425 : UInt64) := by
    change ¬ (425 : UInt64) < (if FastMul.rseAny p (FastMul.fastLog2 p-23) == 16777216 then
      FastMul.fastLog2 p+(s.toUInt64-2)+1 else FastMul.fastLog2 p+(s.toUInt64-2))
    rw [UInt64.lt_iff_toNat_lt]
    change ¬ 425 < (if FastMul.rseAny p (FastMul.fastLog2 p-23) == 16777216 then
      FastMul.fastLog2 p+(s.toUInt64-2)+1 else FastMul.fastLog2 p+(s.toUInt64-2)).toNat
    exact Nat.not_lt_of_ge hover
  simp only [beq_iff_eq] at hnoOverflow
  simp only [FastMul.roundP,beq_iff_eq,hz,if_false,hposition,hleading,hnoOverflow]

end Submission.R19BiasShape



namespace Submission.R19DirectBias
open Competition

/-- Existing ties-to-even bias formula; new retained-product caller shape.
    No change to normal/S128..380 domain or fallback. NOT_COMPILED. -/
@[inline] def normalCore (sum u v : UInt32) : UInt32 :=
  let a := (u &&& (0x7fffff : UInt32)) ||| (0x800000 : UInt32)
  let b := (v &&& (0x7fffff : UInt32)) ||| (0x800000 : UInt32)
  let p : UInt64 := a.toUInt64 * b.toUInt64
  let biased := if p < (0x800000000000 : UInt64) then
      p + (0x3fffff : UInt64) + ((p >>> 23) &&& 1)
    else p + (0x7fffff : UInt64) + ((p >>> 24) &&& 1)
  let high := biased >>> 47
  let q := (biased >>> ((23 : UInt64) + high)).toUInt32
  let e := sum - (127 : UInt32) + high.toUInt32
  ((u ^^^ v) &&& (0x80000000 : UInt32)) ||| (e <<< 23) ||| (q - (0x800000 : UInt32))

@[inline] def guardedMul (fallback : Binary32 → Binary32 → Binary32)
    (x y : Binary32) : Binary32 :=
  let u := x.raw.1
  let v := y.raw.1
  let eu := (u >>> 23) &&& (255 : UInt32)
  let ev := (v >>> 23) &&& (255 : UInt32)
  if eu - 1 ≤ (253 : UInt32) ∧ ev - 1 ≤ (253 : UInt32) then
    let s := eu + ev
    if s - 128 ≤ (252 : UInt32) then R7W02.fromRaw (normalCore s u v)
    else fallback x y
  else fallback x y

@[noinline] def diagnosticEntry (x y : Binary32) : Binary32 :=
  guardedMul Submission.mul x y
end Submission.R19DirectBias


namespace Submission.R19BiasShape
open FloatLib.Numerics
open R19DirectBiasWord

theorem high_nat (p : UInt64)
    (hlo : 70368744177664 ≤ p.toNat) (hhi : p.toNat ≤ 281474943156225) :
    (highWord p).toNat = p.toNat.log2-46+carry p.toNat := by
  have h := (R19PostBias.normalized_quotient p.toNat hlo hhi).1
  have hl := leading_bounds p.toNat hlo (by omega)
  have hk := literal_shift_eq p.toNat hlo hhi
  rw [highWord_nat p hhi]
  rw [hk] at h
  change (R19PostBias.biased p.toNat >>> 47) =
    p.toNat.log2-46+(if rounded p.toNat=16777216 then 1 else 0)
  change (R19PostBias.biased p.toNat >>> 47) =
    (if p.toNat < 140737488355328 then 0 else 1)+
      (if rounded p.toNat=16777216 then 1 else 0) at h
  have hp0 : p.toNat ≠ 0 := by omega
  by_cases hp : p.toNat < 140737488355328
  · have hl47 : p.toNat.log2 < 47 := (Nat.log2_lt hp0).2 (by norm_num; exact hp)
    simp only [if_pos hp] at h
    omega
  · have hl47 : 47 ≤ p.toNat.log2 := (Nat.le_log2 hp0).2 (by norm_num; omega)
    simp only [if_neg hp] at h
    omega

def oldMantissa (p : UInt64) : UInt64 :=
  let r := FastMul.rseAny p (FastMul.fastLog2 p-23)
  if r == 16777216 then 8388608 else r

def oldPosition (p : UInt64) (s : UInt32) : UInt64 :=
  let r := FastMul.rseAny p (FastMul.fastLog2 p-23)
  let n := FastMul.fastLog2 p+(s.toUInt64-2)
  if r == 16777216 then n+1 else n

theorem oldMantissa_nat (p : UInt64)
    (hlo : 70368744177664 ≤ p.toNat) (hhi : p.toNat ≤ 281474943156225) :
    (oldMantissa p).toNat = mantissa p.toNat := by
  have hr := rounded_word_nat p hlo hhi
  have hc : FastMul.rseAny p (FastMul.fastLog2 p-23) = (16777216 : UInt64) ↔
      rounded p.toNat=16777216 := by
    rw [← UInt64.toNat_inj,hr]
    rfl
  simp only [oldMantissa,mantissa,beq_iff_eq,hc]
  split <;> simp_all only [hr]
  all_goals rfl

theorem oldPosition_nat (p : UInt64) (s : UInt32)
    (hlo : 70368744177664 ≤ p.toNat) (hhi : p.toNat ≤ 281474943156225)
    (hs0 : 128 ≤ s.toNat) (hs1 : s.toNat ≤ 380) :
    (oldPosition p s).toNat = p.toNat.log2+s.toNat-2+carry p.toNat := by
  have hl := leading_bounds p.toNat hlo (by omega)
  have hp := position_nat p s hlo hhi hs0 hs1
  have hr := rounded_word_nat p hlo hhi
  have hc : FastMul.rseAny p (FastMul.fastLog2 p-23) = (16777216 : UInt64) ↔
      rounded p.toNat=16777216 := by
    rw [← UInt64.toNat_inj,hr]
    rfl
  simp only [oldPosition,carry,beq_iff_eq,hc]
  split
  · rw [UInt64.toNat_add,hp]
    change (p.toNat.log2+s.toNat-2+1) % 18446744073709551616 = _
    exact Nat.mod_eq_of_lt (by omega)
  · simpa only [Nat.add_zero] using hp

theorem mantissaWord_eq_old (p : UInt64)
    (hlo : 70368744177664 ≤ p.toNat) (hhi : p.toNat ≤ 281474943156225) :
    mantissaWord p = (oldMantissa p).toUInt32 := by
  have hm := mantissa_bounds p.toNat hlo (by omega)
  apply UInt32.toNat.inj
  rw [mantissaWord_nat p hlo hhi,literal_shift_eq p.toNat hlo hhi]
  change mantissa p.toNat = (oldMantissa p).toUInt32.toNat
  rw [FastMul.toUInt32_eq,UInt32.toNat_ofNat',oldMantissa_nat p hlo hhi,
    Nat.mod_eq_of_lt (by omega)]

def exponentWord (s : UInt32) (p : UInt64) : UInt32 := s-127+(highWord p).toUInt32

theorem exponentWord_nat (p : UInt64) (s : UInt32)
    (hlo : 70368744177664 ≤ p.toNat) (hhi : p.toNat ≤ 281474943156225)
    (hs0 : 128 ≤ s.toNat) (hs1 : s.toNat ≤ 380) :
    (exponentWord s p).toNat = s.toNat-127+(highWord p).toNat := by
  have hh := highWord_le_one p hlo hhi
  have hle : (127 : UInt32) ≤ s := by
    rw [UInt32.le_iff_toNat_le]
    change 127 ≤ s.toNat
    omega
  rw [exponentWord,UInt32.toNat_add,UInt32.toNat_sub_of_le _ _ hle,
    FastMul.toUInt32_eq,UInt32.toNat_ofNat',
    Nat.mod_eq_of_lt (show (highWord p).toNat < 4294967296 by omega)]
  change (s.toNat-127+(highWord p).toNat) % 4294967296 = _
  exact Nat.mod_eq_of_lt (by omega)

theorem exponentWord_eq_old (p : UInt64) (s : UInt32)
    (hlo : 70368744177664 ≤ p.toNat) (hhi : p.toNat ≤ 281474943156225)
    (hs0 : 128 ≤ s.toNat) (hs1 : s.toNat ≤ 380) :
    exponentWord s p = (oldPosition p s-171).toUInt32 := by
  have hl := leading_bounds p.toNat hlo (by omega)
  have hc := carry_le p.toNat
  have hp := oldPosition_nat p s hlo hhi hs0 hs1
  have hle : (171 : UInt64) ≤ oldPosition p s := by
    rw [UInt64.le_iff_toNat_le,hp]
    change 171 ≤ p.toNat.log2+s.toNat-2+carry p.toNat
    omega
  apply UInt32.toNat.inj
  rw [exponentWord_nat p s hlo hhi hs0 hs1,high_nat p hlo hhi,
    FastMul.toUInt32_eq,UInt32.toNat_ofNat',UInt64.toNat_sub_of_le _ _ hle,hp]
  change s.toNat-127+(p.toNat.log2-46+carry p.toNat) =
    (p.toNat.log2+s.toNat-2+carry p.toNat-171) % 4294967296
  rw [Nat.mod_eq_of_lt (by omega)]
  omega

theorem fractionWord_eq_old (p : UInt64)
    (hlo : 70368744177664 ≤ p.toNat) (hhi : p.toNat ≤ 281474943156225) :
    mantissaWord p-8388608 = FastMul.fracW (oldMantissa p) := by
  have hm := mantissa_bounds p.toNat hlo (by omega)
  have hn := oldMantissa_nat p hlo hhi
  have hq : (mantissaWord p).toNat = mantissa p.toNat := by
    rw [mantissaWord_nat p hlo hhi,literal_shift_eq p.toNat hlo hhi]
    rfl
  have hle : (8388608 : UInt32) ≤ mantissaWord p := by
    rw [UInt32.le_iff_toNat_le,hq]
    exact hm.1
  apply UInt32.toNat.inj
  rw [UInt32.toNat_sub_of_le _ _ hle,hq,FastMul.fracW_eq,UInt32.toNat_ofNat',hn]
  change mantissa p.toNat-8388608 = (mantissa p.toNat-8388608) % 4294967296
  exact (Nat.mod_eq_of_lt (by omega)).symm

theorem output_bounds (p : UInt64) (s : UInt32)
    (hlo : 70368744177664 ≤ p.toNat) (hhi : p.toNat ≤ 281474943156225)
    (hs0 : 128 ≤ s.toNat) (hs1 : s.toNat ≤ 380) :
    (exponentWord s p).toNat < 256 ∧ (mantissaWord p-8388608).toNat < 8388608 := by
  have hh := highWord_le_one p hlo hhi
  have hm := mantissa_bounds p.toNat hlo (by omega)
  have hq : (mantissaWord p).toNat = mantissa p.toNat := by
    rw [mantissaWord_nat p hlo hhi,literal_shift_eq p.toNat hlo hhi]
    rfl
  have hle : (8388608 : UInt32) ≤ mantissaWord p := by
    rw [UInt32.le_iff_toNat_le,hq]
    exact hm.1
  rw [exponentWord_nat p s hlo hhi hs0 hs1,UInt32.toNat_sub_of_le _ _ hle,hq]
  change s.toNat-127+(highWord p).toNat < 256 ∧ mantissa p.toNat-8388608 < 8388608
  omega

end Submission.R19BiasShape


namespace Submission.R19DirectBias
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
open Model.NativeBinary32 R19DirectBiasWord R19BiasShape

theorem low_mask_eq_self (n : UInt32) (k : Nat) (hk : k < 32) (hn : n.toNat < 2^k) :
    n &&& UInt32.ofNat (2^k-1) = n := by
  apply UInt32.toNat.inj
  simp only [UInt32.toNat_and,UInt32.toNat_ofNat']
  have hmask : 2^k-1 < 4294967296 := by
    have hpow : 2^k ≤ 2^31 := Nat.pow_le_pow_right (by decide) (by omega)
    norm_num at hpow
    omega
  rw [Nat.mod_eq_of_lt hmask,Nat.and_two_pow_sub_one_eq_mod,Nat.mod_eq_of_lt hn]

theorem mkW_eq_unmasked (sign : Bool) (e f : UInt32)
    (he : e.toNat < 256) (hf : f.toNat < 8388608) :
    FastMul.mkW sign e f =
      (if sign then (0x80000000 : UInt32) else 0) ||| (e <<< 23) ||| f := by
  have hem := low_mask_eq_self e 8 (by decide) he
  have hfm := low_mask_eq_self f 23 (by decide) hf
  change e &&& (255 : UInt32) = e at hem
  change f &&& (8388607 : UInt32) = f at hfm
  unfold FastMul.mkW
  rw [hem,hfm]

theorem product_bounds (u v : UInt32) :
    let p := (R2W01b.mantissa u).toUInt64 * (R2W01b.mantissa v).toUInt64
    70368744177664 ≤ p.toNat ∧ p.toNat ≤ 281474943156225 := by
  have hu := R2W01c.mantissa_bounds u
  have hv := R2W01c.mantissa_bounds v
  have hl := Nat.mul_le_mul hu.1 hv.1
  have hh := Nat.mul_le_mul (show (R2W01b.mantissa u).toNat ≤ 16777215 by omega)
    (show (R2W01b.mantissa v).toNat ≤ 16777215 by omega)
  norm_num at hl hh
  dsimp only
  rw [UInt64.toNat_mul,UInt32.toNat_toUInt64,UInt32.toNat_toUInt64,
    Nat.mod_eq_of_lt (by omega)]
  exact ⟨hl,hh⟩

set_option maxHeartbeats 1000000 in
theorem normalCore_eq_roundP (s u v : UInt32) (sign : Bool)
    (hs0 : 128 ≤ s.toNat) (hs1 : s.toNat ≤ 380)
    (hsign : ((u ^^^ v) &&& (0x80000000 : UInt32)) =
      (if sign then (0x80000000 : UInt32) else 0)) :
    normalCore s u v = FastMul.roundP sign
      ((R2W01b.mantissa u).toUInt64 * (R2W01b.mantissa v).toUInt64) (s.toUInt64-2) := by
  let p := (R2W01b.mantissa u).toUInt64 * (R2W01b.mantissa v).toUInt64
  have hp := product_bounds u v
  have hb := output_bounds p s hp.1 hp.2 hs0 hs1
  rw [roundP_normal sign p s hp.1 hp.2 hs0 hs1]
  change ((u ^^^ v) &&& (0x80000000 : UInt32)) |||
      (exponentWord s p <<< 23) ||| (mantissaWord p-8388608) =
    FastMul.mkW sign (oldPosition p s-171).toUInt32 (FastMul.fracW (oldMantissa p))
  rw [hsign,← mkW_eq_unmasked sign _ _ hb.1 hb.2,
    exponentWord_eq_old p s hp.1 hp.2 hs0 hs1,fractionWord_eq_old p hp.1 hp.2]

theorem finiteMantissa_eq (u : UInt32) (hu : expField u ≠ 0) :
    finiteMantissa (expField u) (fracField u) = (R2W01b.mantissa u).toUInt64 := by
  apply UInt64.toNat.inj
  simp only [finiteMantissa,beq_iff_eq,hu,if_false,UInt64.toNat_or,
    UInt32.toNat_toUInt64]
  rw [R2W01b.mantissa,UInt32.toNat_or]
  rfl

theorem exp_bound (u : UInt32) : (expField u).toNat < 256 := by
  rw [FastMul.expField_toNat]
  exact Nat.mod_lt _ (by decide)

theorem finiteScale_sum (u v : UInt32)
    (hu : 0 < (expField u).toNat) (hv : 0 < (expField v).toNat)
    (hs : 128 ≤ (expField u+expField v).toNat) :
    finiteScale (expField u)+finiteScale (expField v) =
      (expField u+expField v).toUInt64-2 := by
  have hub := exp_bound u
  have hvb := exp_bound v
  have hu0 : expField u ≠ 0 := by intro h; rw [h] at hu; norm_num at hu
  have hv0 : expField v ≠ 0 := by intro h; rw [h] at hv; norm_num at hv
  have hsum : (expField u+expField v).toNat = (expField u).toNat+(expField v).toNat := by
    rw [UInt32.toNat_add,Nat.mod_eq_of_lt (by omega)]
  apply UInt64.toNat.inj
  rw [normal_scale_nat _ hs,UInt64.toNat_add,UnderflowZero.finiteScale_toNat,
    UnderflowZero.finiteScale_toNat,if_neg hu0,if_neg hv0,hsum]
  rw [Nat.mod_eq_of_lt (by omega)]
  omega

theorem signBit_eq_bit (u : UInt32) : signBit u = u.toBitVec.getLsbD 31 := by
  have hm : u &&& (0x80000000 : UInt32) =
      if u.toBitVec.getLsbD 31 then (0x80000000 : UInt32) else 0 := by
    apply UInt32.toBitVec_inj.mp
    rw [UInt32.toBitVec_and]
    change u.toBitVec &&& BitVec.twoPow 32 31 = _
    rw [BitVec.and_twoPow]
    cases u.toBitVec.getLsbD 31 <;> rfl
  unfold signBit
  rw [hm]
  cases u.toBitVec.getLsbD 31 <;> rfl

theorem sign_word_eq (u v : UInt32) :
    ((u ^^^ v) &&& (0x80000000 : UInt32)) =
      (if Bool.xor (signBit u) (signBit v) then (0x80000000 : UInt32) else 0) := by
  apply UInt32.toBitVec_inj.mp
  rw [UInt32.toBitVec_and,UInt32.toBitVec_xor]
  change (u.toBitVec ^^^ v.toBitVec) &&& BitVec.twoPow 32 31 = _
  rw [BitVec.and_twoPow]
  have hm : (u.toBitVec ^^^ v.toBitVec).getLsbD 31 = Bool.xor (signBit u) (signBit v) := by
    calc
      _ = (u.toBitVec ^^^ v.toBitVec).msb := by
        simpa using (BitVec.msb_eq_getLsbD_last (u.toBitVec ^^^ v.toBitVec)).symm
      _ = _ := by
        rw [BitVec.msb_xor,signBit_eq_bit,signBit_eq_bit]
        congr 1 <;> simpa using BitVec.msb_eq_getLsbD_last _
  rw [hm]
  cases Bool.xor (signBit u) (signBit v) <;> rfl

theorem normalCore_eq_core (u v : UInt32)
    (hu : 0 < (expField u).toNat) (hv : 0 < (expField v).toNat)
    (hs0 : 128 ≤ (expField u+expField v).toNat)
    (hs1 : (expField u+expField v).toNat ≤ 380) :
    normalCore (expField u+expField v) u v = FastMul.core u v := by
  have hu0 : expField u ≠ 0 := by intro h; rw [h] at hu; norm_num at hu
  have hv0 : expField v ≠ 0 := by intro h; rw [h] at hv; norm_num at hv
  rw [normalCore_eq_roundP _ u v _ hs0 hs1 (sign_word_eq u v)]
  simp only [FastMul.core]
  rw [finiteMantissa_eq u hu0,finiteMantissa_eq v hv0,finiteScale_sum u v hu hv hs0]

theorem normal_guard (e : UInt32) (h : e-1 ≤ (253 : UInt32)) :
    0 < e.toNat ∧ e.toNat < 255 := by
  have he := e.toNat_lt
  rw [UInt32.le_iff_toNat_le,UInt32.toNat_sub] at h
  change (4294967295+e.toNat) % 4294967296 ≤ 253 at h
  omega

theorem sum_guard (s : UInt32) (h : s-128 ≤ (252 : UInt32)) :
    128 ≤ s.toNat ∧ s.toNat ≤ 380 := by
  have hs := s.toNat_lt
  rw [UInt32.le_iff_toNat_le,UInt32.toNat_sub] at h
  change (4294967168+s.toNat) % 4294967296 ≤ 252 at h
  omega

theorem guardedMul_spec (fallback : Binary32 → Binary32 → Binary32)
    (hf : ∀ x y, fallback x y = ExecFloat.Spec.mul x y) (x y : Binary32) :
    guardedMul fallback x y = ExecFloat.Spec.mul x y := by
  unfold guardedMul
  dsimp only
  split
  · rename_i hn
    have hu := normal_guard _ hn.1
    have hv := normal_guard _ hn.2
    split
    · rename_i hs
      have hb := sum_guard _ hs
      change 0 < (expField x.raw.1).toNat ∧ (expField x.raw.1).toNat < 255 at hu
      change 0 < (expField y.raw.1).toNat ∧ (expField y.raw.1).toNat < 255 at hv
      change 128 ≤ (expField x.raw.1+expField y.raw.1).toNat ∧
        (expField x.raw.1+expField y.raw.1).toNat ≤ 380 at hb
      change R7W02.fromRaw (normalCore (expField x.raw.1+expField y.raw.1) x.raw.1 y.raw.1) = _
      rw [normalCore_eq_core _ _ hu.1 hv.1 hb.1 hb.2]
      have hu255 : expField x.raw.1 ≠ (255 : UInt32) := by
        intro h; rw [h] at hu; norm_num at hu
      have hv255 : expField y.raw.1 ≠ (255 : UInt32) := by
        intro h; rw [h] at hv; norm_num at hv
      have hspecial : FastMul.special x.raw.1 y.raw.1 = false := by
        simp [FastMul.special,FastMul.sm1_eq,hu255,hv255]
      calc
        _ = FastMul.ofBits (FastMul.core x.raw.1 y.raw.1) := by
          apply Configured.Family.toModel_injective
          rfl
        _ = FastMul.mul x y := by simp only [FastMul.mul,hspecial,Bool.false_eq_true,if_false]
        _ = ExecFloat.Spec.mul x y := FastMul.mul_spec x y
    · exact hf x y
  · exact hf x y

end Submission.R19DirectBias

#print axioms Submission.add_spec
#print axioms Submission.mul_spec
#print axioms Submission.sum_spec
#print axioms Submission.bmm_spec
#print axioms BranchlessRNESeed.nat_bias
#print axioms BranchlessRNESeed.nat_grouped_bias
#print axioms R19PostBias.biased_quotient
#print axioms R19PostBias.biased_bounds
#print axioms R19PostBias.normalized_quotient
#print axioms Submission.R19DirectBiasWord.biased_sum_nat
#print axioms Submission.R19DirectBiasWord.biasedWord_nat
#print axioms Submission.R19DirectBiasWord.highWord_nat
#print axioms Submission.R19DirectBiasWord.highWord_le_one
#print axioms Submission.R19DirectBiasWord.shiftWord_nat
#print axioms Submission.R19DirectBiasWord.mantissaWord_nat
#print axioms Submission.R19BiasShape.carry_le
#print axioms Submission.R19BiasShape.leading_bounds
#print axioms Submission.R19BiasShape.no_carry_at_47
#print axioms Submission.R19BiasShape.mantissa_bounds
#print axioms Submission.R19BiasShape.literal_shift_eq
#print axioms Submission.R19BiasShape.normal_scale_nat
#print axioms Submission.R19BiasShape.leading_nat
#print axioms Submission.R19BiasShape.position_nat
#print axioms Submission.R19BiasShape.shift_word_nat
#print axioms Submission.R19BiasShape.rounded_word_nat
#print axioms Submission.R19BiasShape.normalized_position_le
#print axioms Submission.R19BiasShape.roundP_normal
#print axioms Submission.R19BiasShape.high_nat
#print axioms Submission.R19BiasShape.oldMantissa_nat
#print axioms Submission.R19BiasShape.oldPosition_nat
#print axioms Submission.R19BiasShape.mantissaWord_eq_old
#print axioms Submission.R19BiasShape.exponentWord_nat
#print axioms Submission.R19BiasShape.exponentWord_eq_old
#print axioms Submission.R19BiasShape.fractionWord_eq_old
#print axioms Submission.R19BiasShape.output_bounds
#print axioms Submission.R19DirectBias.low_mask_eq_self
#print axioms Submission.R19DirectBias.mkW_eq_unmasked
#print axioms Submission.R19DirectBias.product_bounds
#print axioms Submission.R19DirectBias.normalCore_eq_roundP
#print axioms Submission.R19DirectBias.finiteMantissa_eq
#print axioms Submission.R19DirectBias.exp_bound
#print axioms Submission.R19DirectBias.finiteScale_sum
#print axioms Submission.R19DirectBias.signBit_eq_bit
#print axioms Submission.R19DirectBias.sign_word_eq
#print axioms Submission.R19DirectBias.normalCore_eq_core
#print axioms Submission.R19DirectBias.normal_guard
#print axioms Submission.R19DirectBias.sum_guard
#print axioms Submission.R19DirectBias.guardedMul_spec
