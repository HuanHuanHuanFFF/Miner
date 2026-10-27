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
    rw [UInt64.lt_iff_toNat_lt]
    change ¬ 425 < (if FastMul.rseAny p (FastMul.fastLog2 p-23) == 16777216 then
      FastMul.fastLog2 p+(s.toUInt64-2)+1 else FastMul.fastLog2 p+(s.toUInt64-2)).toNat
    exact Nat.not_lt_of_ge hover
  simp only [beq_iff_eq] at hnoOverflow
  simp only [FastMul.roundP,beq_iff_eq,hz,if_false,hposition,hleading,hnoOverflow]

end Submission.R19BiasShape

