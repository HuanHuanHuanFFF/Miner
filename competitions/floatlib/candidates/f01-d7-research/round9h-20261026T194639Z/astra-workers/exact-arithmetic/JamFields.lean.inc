namespace Submission.R19Jam17
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

theorem recover (p : Nat)
    (hlo : 70368744177664 ≤ p) (hhi : p ≤ 281474943156225) :
    let r := R14NatNormal.rounded p * 2 ^ (p.log2 - 40)
    r / 1073741824 = R14ExponentShift.middleExponent p - 173 ∧
      r / 2 ^ (6 + r / 1073741824) = R14NatNormal.mantissa p := by
  have hl := R14NatNormal.leading_bounds p hlo (by omega)
  have hb := R14WordAddRounding.rounded_bounds p (by omega) (by omega)
  have cases : p.log2 = 46 ∨ p.log2 = 47 := by omega
  rcases cases with he | he
  · by_cases hc : R14NatNormal.rounded p = 16777216
    · norm_num [he,hc,R14ExponentShift.middleExponent,R14NatNormal.carry,R14NatNormal.mantissa]
    · have hr : (R14NatNormal.rounded p * 64) / 1073741824 = 0 := by omega
      simp only [he]
      norm_num only [Nat.reduceSub,Nat.reducePow]
      rw [hr]
      simp [R14ExponentShift.middleExponent,R14NatNormal.carry,R14NatNormal.mantissa,he,hc]
  · have hc0 := R14NatNormal.no_carry_at_47 p hhi he
    have hc : R14NatNormal.rounded p ≠ 16777216 := by
      intro h
      simp [R14NatNormal.carry,h] at hc0
    have hr : (R14NatNormal.rounded p * 128) / 1073741824 = 1 := by omega
    simp only [he]
    norm_num only [Nat.reduceSub,Nat.reducePow]
    rw [hr]
    simp [R14ExponentShift.middleExponent,R14NatNormal.carry,R14NatNormal.mantissa,he,hc]

def productWord (a b : UInt32) : UInt64 := a.toUInt64 * b.toUInt64
def numericProduct (a b : UInt32) : UInt32 := (jamWord (productWord a b)).toFloat32.toUInt32
def highWord (a b : UInt32) : UInt32 := numericProduct a b >>> 30
def shiftWord (a b : UInt32) : UInt32 := 6 + highWord a b
def mantissaWord (a b : UInt32) : UInt32 := numericProduct a b >>> shiftWord a b
def fractionWord (a b : UInt32) : UInt32 := mantissaWord a b - 8388608
def exponentWord (sum a b : UInt32) : UInt32 := sum - 127 + highWord a b

theorem productWord_nat (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    (productWord a b).toNat = R14ExponentShift.product a b := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  unfold productWord R14ExponentShift.product
  rw [UInt64.toNat_mul,UInt32.toNat_toUInt64,UInt32.toNat_toUInt64]
  exact Nat.mod_eq_of_lt (by change R14ExponentShift.product a b < _; omega)

theorem numericProduct_nat (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    (numericProduct a b).toNat =
      R14NatNormal.rounded (R14ExponentShift.product a b) *
        2 ^ ((R14ExponentShift.product a b).log2 - 40) := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  have hw := productWord_nat a b ha0 ha hb0 hb
  have hr := jam_roundtrip (productWord a b) (by rw [hw]; exact hp.1) (by rw [hw]; exact hp.2)
  simpa only [numericProduct,hw,R14NatNormal.rounded] using hr

theorem highWord_nat (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    (highWord a b).toNat = R14ExponentShift.middleExponent (R14ExponentShift.product a b)-173 := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  rw [highWord,UInt32.toNat_shiftRight,numericProduct_nat a b ha0 ha hb0 hb]
  change (R14NatNormal.rounded (R14ExponentShift.product a b) *
    2 ^ ((R14ExponentShift.product a b).log2 - 40)) >>> 30 = _
  rw [Nat.shiftRight_eq_div_pow]
  exact (recover _ hp.1 hp.2).1

theorem shiftWord_nat (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    (shiftWord a b).toNat = 6 + R14ExponentShift.middleExponent (R14ExponentShift.product a b)-173 := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  have he := R14ExponentShift.middle_bounds _ hp.1 hp.2
  rw [shiftWord,UInt32.toNat_add,highWord_nat a b ha0 ha hb0 hb]
  change (6+(R14ExponentShift.middleExponent (R14ExponentShift.product a b)-173)) % 4294967296 = _
  rw [Nat.mod_eq_of_lt (by omega)]
  omega

theorem mantissaWord_nat (a b : UInt32)
    (ha0 : 8388608 ≤ a.toNat) (ha : a.toNat < 16777216)
    (hb0 : 8388608 ≤ b.toNat) (hb : b.toNat < 16777216) :
    (mantissaWord a b).toNat = R14NatNormal.mantissa (R14ExponentShift.product a b) := by
  have hp := R14ExponentShift.product_bounds a b ha0 ha hb0 hb
  have he := R14ExponentShift.middle_bounds _ hp.1 hp.2
  have hs := shiftWord_nat a b ha0 ha hb0 hb
  have hrec := recover _ hp.1 hp.2
  have hsf : (shiftWord a b).toNat < 32 := by omega
  rw [mantissaWord,UInt32.toNat_shiftRight,Nat.mod_eq_of_lt hsf,
    numericProduct_nat a b ha0 ha hb0 hb,Nat.shiftRight_eq_div_pow]
  have heq : (shiftWord a b).toNat =
      6 + (R14NatNormal.rounded (R14ExponentShift.product a b) *
        2 ^ ((R14ExponentShift.product a b).log2-40)) / 1073741824 := by
    rw [hrec.1]
    omega
  rw [heq]
  exact hrec.2

end Submission.R19Jam17
