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
