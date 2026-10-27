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
